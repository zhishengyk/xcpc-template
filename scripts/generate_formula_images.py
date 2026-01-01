#!/usr/bin/env python3
"""
1. Parse `数学.md` and collect inline formula image URLs exported from Yuque.
2. Download the first N images (matching the `[公式]` placeholders in `main.tex`).
3. Convert them to PDF files so XeLaTeX can embed them without requiring external tools.
4. Replace all `[公式]` placeholders in `main.tex` with `\formulaimage{<path>}`.

The script is idempotent: it skips downloads/conversions that already exist and only rewrites
`main.tex` when necessary.
"""

from __future__ import annotations

import hashlib
import io
import re
import sys
import urllib.request
from pathlib import Path
from typing import Match

from reportlab.graphics import renderPDF
from svglib.svglib import svg2rlg

ROOT = Path(__file__).resolve().parents[1]
MAIN_TEX = ROOT / "main.tex"
MATH_MD = ROOT / "数学.md"
ASSET_DIR = ROOT / "assets" / "formulas"
IMAGE_PATTERN = re.compile(r"!\[image\]\(([^)]+)\)")


def collect_formula_urls() -> list[str]:
    content = MATH_MD.read_text(encoding="utf-8")
    return re.findall(r"!\[image\]\(([^)]+)\)", content)


def count_placeholders() -> int:
    main_text = MAIN_TEX.read_text(encoding="utf-8")
    return main_text.count("[公式]")


def collect_main_inline_urls(text: str) -> list[str]:
    return IMAGE_PATTERN.findall(text)


def convert_url_to_filename(url: str) -> Path:
    digest = hashlib.sha1(url.encode("utf-8")).hexdigest()
    return ASSET_DIR / f"url_{digest}.pdf"


def ensure_assets_dir() -> None:
    ASSET_DIR.mkdir(parents=True, exist_ok=True)


def normalize_url(raw: str) -> str:
    return raw.replace(r"\_", "_")


def download_and_convert(url: str, index: int | None = None) -> Path:
    url = normalize_url(url)
    pdf_path = (
        ASSET_DIR / f"formula_{index:03d}.pdf" if index is not None else convert_url_to_filename(url)
    )
    if pdf_path.exists():
        return pdf_path

    svg_bytes = urllib.request.urlopen(url, timeout=30).read()
    drawing = svg2rlg(io.BytesIO(svg_bytes))
    renderPDF.drawToFile(drawing, str(pdf_path))
    return pdf_path


def replace_placeholders(paths: list[Path]) -> None:
    text = MAIN_TEX.read_text(encoding="utf-8")
    iterator = iter(paths)

    def repl(_: re.Match) -> str:
        rel_path = next(iterator).relative_to(ROOT).as_posix()
        return rf"\formulaimage{{{rel_path}}}"

    new_text, count = re.subn(r"\[公式\]", repl, text)
    if count != len(paths):
        raise RuntimeError(f"Expected to replace {len(paths)} placeholders, got {count}")
    MAIN_TEX.write_text(new_text, encoding="utf-8")


def replace_inline_images(text: str) -> bool:
    urls = collect_main_inline_urls(text)
    if not urls:
        return False

    def repl(match: Match[str]) -> str:
        url = match.group(1)
        pdf_path = download_and_convert(url, index=None)
        rel_path = pdf_path.relative_to(ROOT).as_posix()
        return rf"\formulaimage{{{rel_path}}}"

    new_text, count = IMAGE_PATTERN.subn(repl, text)
    MAIN_TEX.write_text(new_text, encoding="utf-8")
    return count > 0


def main() -> None:
    ensure_assets_dir()
    urls = collect_formula_urls()
    needed = count_placeholders()
    if needed > 0:
        if len(urls) < needed:
            raise RuntimeError(
                f"Not enough formula images: need {needed}, but only found {len(urls)}."
            )

        paths: list[Path] = []
        for idx in range(needed):
            url = urls[idx]
            path = download_and_convert(url, idx + 1)
            paths.append(path)

        replace_placeholders(paths)
        print(f"Replaced {needed} placeholders with formula images.")
    else:
        print("No [公式] placeholders detected.")

    text = MAIN_TEX.read_text(encoding="utf-8")
    if replace_inline_images(text):
        print("Converted inline markdown image formulas.")
    else:
        print("No inline markdown image formulas found.")


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:  # pragma: no cover - helper script
        print(f"[generate_formula_images] ERROR: {exc}", file=sys.stderr)
        sys.exit(1)

