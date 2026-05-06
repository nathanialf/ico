#!/usr/bin/env python3
"""
progress.py — regenerate README.md / docs/PROGRESS.md status tables.

Reads config/ico.us.yaml + the current src/ tree, computes per-section
matched-bytes ratios from claimed `c` subsegments, and rewrites the
status tables in README.md and docs/PROGRESS.md.

A subsegment counted as "matched" iff:
  - its yaml entry has type `c` (claimed for matching), and
  - the corresponding src/<name>.c file actually exists.

Sizes are pulled from baserom/baseelf.elf section headers so the
ratios stay accurate even if subsegment boundaries shift.

Output format: two-decimal-place percentages (e.g. `0.42 %`).
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

try:
    import yaml
except ImportError:
    sys.exit("progress.py: missing PyYAML. Run `.venv/bin/pip install pyyaml`.")

try:
    from elftools.elf.elffile import ELFFile
except ImportError:
    sys.exit("progress.py: missing pyelftools. Run "
             "`.venv/bin/pip install -r tools/requirements.txt`.")

REPO_ROOT = Path(__file__).resolve().parent.parent
YAML = REPO_ROOT / "config" / "ico.us.yaml"
BASEELF = REPO_ROOT / "baserom" / "baseelf.elf"
SRC_DIR = REPO_ROOT / "src"
README = REPO_ROOT / "README.md"
PROGRESS_DOC = REPO_ROOT / "docs" / "PROGRESS.md"

# Yaml subsegment types that correspond to each ELF section. Splat lumps
# .vutext under `textbin` because it's hand-written VU code rather than
# auto-disassembled MIPS — we account for it as its own row.
SECTION_TO_TYPES = {
    ".text":   {"asm", "c", "hasm"},
    ".vutext": {"textbin"},
    ".data":   {"data"},
    ".rodata": {"rodata"},
    ".lit4":   {"lit4"},
    ".sdata":  {"sdata"},
}
MATCHABLE_TYPES = {"c"}  # Future: hasm if we adopt hand-asm matching.


def _human_bytes(n: int) -> str:
    if n >= 1 << 20:
        return f"{n / (1 << 20):.2f} MB"
    if n >= 1 << 10:
        return f"{n / (1 << 10):.2f} KB"
    return f"{n} B"


def _load_section_sizes() -> dict[str, int]:
    """Map ELF section name -> size in bytes, from baserom/baseelf.elf."""
    if not BASEELF.exists():
        sys.exit(f"progress: {BASEELF} not found - run tools/extract_elf.sh first.")
    sizes: dict[str, int] = {}
    with BASEELF.open("rb") as f:
        elf = ELFFile(f)
        for sec in elf.iter_sections():
            sizes[sec.name] = sec["sh_size"]
    return sizes


def _walk_subsegments(yaml_doc: dict) -> list[tuple[int, str, str]]:
    """Return [(file_offset, type, name)] from the cod segment."""
    out: list[tuple[int, str, str]] = []
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list):
            continue  # closing sentinel like [0x533BC6]
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list):
                if len(sub) < 2:
                    continue
                offset = sub[0]
                stype = sub[1]
                name = sub[2] if len(sub) >= 3 else ""
            elif isinstance(sub, dict):
                offset = sub.get("vram", 0)
                stype = sub.get("type", "")
                name = sub.get("name", "")
            else:
                continue
            out.append((offset, stype, name))
    return out


def _claim_size(subs: list[tuple[int, str, str]], idx: int, default_end: int) -> int:
    """Distance from this subseg's offset to the next, in bytes."""
    cur_off = subs[idx][0]
    if idx + 1 < len(subs):
        return subs[idx + 1][0] - cur_off
    return max(0, default_end - cur_off)


def _section_for_type(stype: str) -> str | None:
    for sec, types in SECTION_TO_TYPES.items():
        if stype in types:
            return sec
    return None


def _src_exists(name: str) -> bool:
    return (SRC_DIR / f"{name}.c").exists()


def compute_progress() -> dict[str, tuple[int, int]]:
    """Return {section_name: (matched_bytes, total_bytes)}."""
    yaml_doc = yaml.safe_load(YAML.read_text())
    sizes = _load_section_sizes()
    subs = _walk_subsegments(yaml_doc)

    # The cod segment runs to the closing sentinel address (the last
    # top-level item). Splat seeds it as e.g. `[0x533BC6]`.
    final_off = 0
    for seg in yaml_doc.get("segments", []):
        if isinstance(seg, list) and len(seg) >= 1:
            final_off = max(final_off, seg[0])

    matched: dict[str, int] = {sec: 0 for sec in SECTION_TO_TYPES}
    for i, (_off, stype, name) in enumerate(subs):
        sec = _section_for_type(stype)
        if sec is None:
            continue
        size = _claim_size(subs, i, final_off)
        if stype in MATCHABLE_TYPES and name and _src_exists(name):
            matched[sec] += size

    totals = {sec: sizes.get(sec, 0) for sec in SECTION_TO_TYPES}
    return {sec: (matched[sec], totals[sec]) for sec in SECTION_TO_TYPES}


def _fmt_pct(matched: int, total: int) -> str:
    if total == 0:
        return "-"
    return f"{(100.0 * matched / total):.2f} %"


# ----- README table ---------------------------------------------------

README_BEGIN = "<!-- progress:begin -->"
README_END = "<!-- progress:end -->"

# Sections shown in the README rollup. .vutext / .lit4 / .sdata are
# small or non-matchable, omitted from the public-facing summary.
README_SECTIONS = [".text", ".data", ".rodata"]


def _render_readme_table(progress: dict[str, tuple[int, int]]) -> str:
    lines = [
        "| Section          | Matched | Total |",
        "| ---------------- | ------: | ----: |",
    ]
    for sec in README_SECTIONS:
        matched, total = progress.get(sec, (0, 0))
        lines.append(
            f"| `{sec}` | {_fmt_pct(matched, total):>7} | {_human_bytes(total)} |"
        )
    return "\n".join(lines)


def _splice_block(text: str, begin: str, end: str, body: str) -> str:
    """Replace the content between `begin` and `end` markers (inclusive)
    with `body`. Inserts the markers if missing.
    """
    if begin in text and end in text:
        pat = re.compile(re.escape(begin) + r".*?" + re.escape(end), re.DOTALL)
        return pat.sub(begin + "\n" + body + "\n" + end, text)
    return text + ("\n" if not text.endswith("\n") else "") + begin + "\n" + body + "\n" + end + "\n"


def _update_readme(progress: dict[str, tuple[int, int]]) -> bool:
    if not README.exists():
        return False
    text = README.read_text()
    table = _render_readme_table(progress)

    if README_BEGIN in text:
        new = _splice_block(text, README_BEGIN, README_END, table)
    else:
        # First-time: replace the seed table block and insert markers.
        # Match the table whose header row matches the README seed.
        seed = re.compile(
            r"\| Section\s+\| Matched \| Total \|\n"
            r"\|[-: ]+\|[-: ]+\|[-: ]+\|\n"
            r"(?:\|[^\n]*\|\n)+",
            re.MULTILINE,
        )
        replacement = README_BEGIN + "\n" + table + "\n" + README_END + "\n"
        if seed.search(text):
            new = seed.sub(replacement, text, count=1)
        else:
            return False  # no anchor - refuse to scribble blindly

    if new == text:
        return False
    README.write_text(new)
    return True


# ----- docs/PROGRESS.md table -----------------------------------------

PROGRESS_BEGIN = "<!-- progress:begin -->"
PROGRESS_END = "<!-- progress:end -->"


def _render_progress_table(progress: dict[str, tuple[int, int]]) -> str:
    lines = [
        "| Section | Matched bytes | Total bytes | % |",
        "| --- | ---: | ---: | ---: |",
    ]
    for sec in [".text", ".vutext", ".data", ".rodata", ".lit4", ".sdata"]:
        matched, total = progress.get(sec, (0, 0))
        lines.append(
            f"| `{sec}` | {matched} | {total} | {_fmt_pct(matched, total)} |"
        )
    return "\n".join(lines)


def _update_progress_doc(progress: dict[str, tuple[int, int]]) -> bool:
    if not PROGRESS_DOC.exists():
        return False
    text = PROGRESS_DOC.read_text()
    table = _render_progress_table(progress)

    if PROGRESS_BEGIN in text:
        new = _splice_block(text, PROGRESS_BEGIN, PROGRESS_END, table)
    else:
        seed = re.compile(
            r"\| Section \| Matched bytes \| Total bytes \| % \|\n"
            r"\|[-: ]+\|[-: ]+\|[-: ]+\|[-: ]+\|\n"
            r"(?:\|[^\n]*\|\n)+",
            re.MULTILINE,
        )
        replacement = PROGRESS_BEGIN + "\n" + table + "\n" + PROGRESS_END + "\n"
        if seed.search(text):
            new = seed.sub(replacement, text, count=1)
        else:
            return False

    if new == text:
        return False
    PROGRESS_DOC.write_text(new)
    return True


def main() -> int:
    if not YAML.exists():
        print(f"progress: {YAML} not found", file=sys.stderr)
        return 1
    progress = compute_progress()

    print("progress (matched / total):")
    for sec, (m, t) in progress.items():
        print(f"  {sec:<10} {m:>10} / {t:<10} {_fmt_pct(m, t):>8}")

    changed_readme = _update_readme(progress)
    changed_doc = _update_progress_doc(progress)
    if changed_readme:
        print(f"progress: rewrote {README.relative_to(REPO_ROOT)}")
    if changed_doc:
        print(f"progress: rewrote {PROGRESS_DOC.relative_to(REPO_ROOT)}")
    if not (changed_readme or changed_doc):
        print("progress: tables already up-to-date")
    return 0


if __name__ == "__main__":
    sys.exit(main())
