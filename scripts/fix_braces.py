import os
import re
from pathlib import Path


def collect_cpp_paths_from_main(tex_path: Path) -> list[Path]:
    """
    Parse main.tex and collect all C++ source file paths that are included via \\code{...}.
    Only paths ending with .cpp are returned.
    """
    content = tex_path.read_text(encoding="utf-8")
    # Look for LaTeX commands of the form \code{path/to/file.cpp}
    matches = re.findall(r"\\code\{([^}]+)\}", content)
    cpp_rel_paths = sorted({m for m in matches if m.endswith(".cpp")})

    root = tex_path.parent
    cpp_paths: list[Path] = []
    for rel in cpp_rel_paths:
        p = root / Path(rel.replace("/", os.sep))
        if p.is_file():
            cpp_paths.append(p)
    return cpp_paths


def join_brace_lines_in_file(path: Path) -> bool:
    """
    For the given C++ source file, join lines of the form:

        <code ...>
        {

    into:

        <code ...> {

    i.e. remove the newline before a lone opening brace.

    Returns True if the file was modified, False otherwise.
    """
    text = path.read_text(encoding="utf-8")
    lines = text.splitlines()
    changed = False

    new_lines: list[str] = []
    i = 0
    while i < len(lines):
        line = lines[i]

        if i + 1 < len(lines):
            next_line = lines[i + 1]
            # next line is a lone opening brace (optionally with trailing spaces)
            if re.fullmatch(r"\s*\{\s*", next_line):
                # current line has some non-brace, non-space content
                if re.search(r"[^\s\{\}]", line):
                    # join the two lines as "line {"
                    new_lines.append(line.rstrip() + " {")
                    i += 2
                    changed = True
                    continue

        new_lines.append(line)
        i += 1

    if changed:
        # Preserve trailing newline convention
        path.write_text("\n".join(new_lines) + "\n", encoding="utf-8")
    return changed


def main() -> None:
    root = Path(__file__).resolve().parents[1]
    tex_path = root / "main.tex"
    if not tex_path.is_file():
        raise FileNotFoundError(f"Cannot find main.tex at {tex_path}")

    cpp_paths = collect_cpp_paths_from_main(tex_path)
    print(f"Found {len(cpp_paths)} C++ files referenced via \\code in main.tex.")

    total_changed = 0
    for p in cpp_paths:
        if join_brace_lines_in_file(p):
            total_changed += 1
            print(f"Updated brace style in: {p.relative_to(root)}")

    print(f"Done. Modified {total_changed} files.")


if __name__ == "__main__":
    main()


