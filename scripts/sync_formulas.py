#!/usr/bin/env python3
"""
Synchronise math formulas from `数学.md` into `main.tex`.

The updated markdown now contains the LaTeX source for every formula, so this
script extracts each `$...$` expression, stores it as a small `.tex` snippet,
and rewrites the `\formulaimage{...}` placeholders in `main.tex` into inline or
display math macros that directly input those snippets.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path
from typing import List, Tuple

ROOT = Path(__file__).resolve().parents[1]
MATH_FILE = ROOT / "数学.md"
MAIN_FILE = ROOT / "main.tex"
TEX_DIR = ROOT / "assets/formulas_tex"


def sanitize_expression(expr: str) -> str:
    """Strip size commands and wrap CJK text with \\text{}."""
    for token in (r"\large", r"\Large", r"\small", r"\normalsize"):
        expr = expr.replace(token, "")

    expr = expr.replace("＝", "=")

    def wrap(match: re.Match[str]) -> str:
        return r"\text{" + match.group(0) + "}"

    expr = re.sub(r"([\u4e00-\u9fff。，、《》！？：；“”]+)", wrap, expr)
    return expr.strip()


def extract_formulas() -> List[Tuple[str, bool]]:
    """Extract (expression, is_display) pairs from 数学.md."""
    text = MATH_FILE.read_text(encoding="utf-8").replace("\r\n", "\n")

    placeholder = "\uFFFF"
    text_tmp = text.replace(r"\$", placeholder)

    pattern = re.compile(r"\$(?!\$)(.+?)(?<!\$)\$", re.S)
    formulas: List[Tuple[str, bool]] = []

    def prev_non_ws(s: str) -> str | None:
        for ch in reversed(s):
            if ch in " \t\r":
                continue
            return ch
        return None

    def next_non_ws(s: str) -> str | None:
        for ch in s:
            if ch in " \t\r":
                continue
            return ch
        return None

    for match in pattern.finditer(text_tmp):
        expr = match.group(1).strip().replace(placeholder, "$")
        expr = sanitize_expression(expr)
        left_char = prev_non_ws(text_tmp[: match.start()])
        right_char = next_non_ws(text_tmp[match.end() :])
        display = (left_char in (None, "\n")) and (right_char in (None, "\n"))
        formulas.append((expr, display))

    return formulas


def replace_placeholders(formulas: List[Tuple[str, bool]]) -> int:
    TEX_DIR.mkdir(parents=True, exist_ok=True)

    main_text = MAIN_FILE.read_text(encoding="utf-8")
    pattern = re.compile(r"\\formulaimage\{[^}]+\}")
    matches = list(pattern.finditer(main_text))
    existing_files = sorted(TEX_DIR.glob("formula_*.tex"))

    target_count = len(matches) if matches else len(existing_files)
    if target_count == 0:
        print("[sync_formulas] No placeholders or existing formula files to update.")
        return 0

    if len(formulas) < target_count:
        raise RuntimeError(
            f"Formula count mismatch: need {target_count} expressions but only detected {len(formulas)}."
        )
    if len(formulas) > target_count:
        print(
            f"[sync_formulas] Warning: detected {len(formulas)} math expressions but only {target_count} placeholders/files. "
            "Extra expressions at the end will be ignored."
        )
        formulas = formulas[:target_count]

    used = formulas[:target_count]

    for idx, (expr, _) in enumerate(used, 1):
        path = TEX_DIR / f"formula_{idx:03d}.tex"
        path.write_text(expr + "\n", encoding="utf-8")

    if matches:
        idx = 0

        def repl(_: re.Match[str]) -> str:
            nonlocal idx
            _, display = used[idx]
            idx += 1
            macro = r"\displayformula" if display else r"\inlineformula"
            rel = TEX_DIR.relative_to(ROOT).as_posix()
            path = f"./{rel}/formula_{idx:03d}.tex"
            return f"{macro}{{{path}}}"

        new_main = pattern.sub(repl, main_text)
        MAIN_FILE.write_text(new_main, encoding="utf-8")

    return len(used)


def main() -> None:
    if not MATH_FILE.exists():
        raise SystemExit(f"{MATH_FILE} not found")
    formulas = extract_formulas()
    if not formulas:
        raise SystemExit("No formulas detected in 数学.md")
    replaced = replace_placeholders(formulas)
    print(f"Replaced {replaced} formulas.")


if __name__ == "__main__":
    try:
        main()
    except Exception as exc:  # pragma: no cover - helper script
        print(f"[sync_formulas] ERROR: {exc}", file=sys.stderr)
        sys.exit(1)

