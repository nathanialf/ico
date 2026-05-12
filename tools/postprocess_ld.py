#!/usr/bin/env python3
"""
postprocess_ld.py — patch splat's emitted linker script to honor original
ELF section alignments that splat 0.40.0 doesn't propagate from its
yaml `align:` keys.

The original ICO baseelf places .sbss at a 0x100-aligned VRAM and .bss at
a 0x80-aligned VRAM (sh_addralign in the source ELF doesn't tell the full
story — the original linker enforced these alignments explicitly).
Splat's default `. = ALIGN(., 16)` underpads, leaving build/ico.rom 10
bytes shorter than baserom/baseelf.rom and shifting every BSS-region
pointer by 0x30.

Run as part of `make setup` after `splat split`. Idempotent — looks for
the marker comment on each insertion and skips if already present.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
LD = REPO_ROOT / "config" / "ico.us.ld"

# Two kinds of patches:
#   - section-start: align the global `.` BEFORE a section declaration so the
#     section's load address is honored. Required for NOLOAD sections, where
#     ALIGN inside the section body doesn't propagate to the section start.
#   - clear-stale: drop stale ALIGN lines from a previous (broken) run of
#     this script that inserted the alignment inside the section body.

# Each entry: (anchor_pattern, align, marker, kind)
#   anchor_pattern is matched against a single line (with surrounding whitespace).
PATCHES = [
    # Align the global location counter before the .cod_bss section starts so
    # that .cod_bss (and therefore the first symbol inside it, .sbss, which
    # the original linker placed at 0x633C00) lands at the right VRAM.
    (".cod_bss (NOLOAD) :", 0x100, "fix-align-cod-bss-section", "section-start"),
]

# Lines to delete from earlier broken patch runs.
STALE_LINE_PATTERNS = [
    re.compile(r"^\s*\.\s*=\s*ALIGN\(\.,\s*0x100\);\s*/\*\s*sbss alignment fix\s*\*/\s*$"),
    re.compile(r"^\s*\.\s*=\s*ALIGN\(\.,\s*0x100\);\s*/\*\s*fix-align-sbss\s*\*/\s*$"),
    re.compile(r"^\s*\.\s*=\s*ALIGN\(\.,\s*0x80\);\s*/\*\s*fix-align-bss\s*\*/\s*$"),
]

# Drop splat's `. = ALIGN(., 16);` immediately before `cod_SDATA_END = .;`.
# The original ICO ELF's LOAD section ends at exactly the last byte of
# .sdata (0x633BC6 — not 16-byte aligned); splat's pad pushes the .rom 10
# bytes longer. We keep all OTHER inter-section ALIGNs since they reflect
# real section alignment requirements.
SDATA_END_ALIGN_KILLER = re.compile(
    r"^\s*\.\s*=\s*ALIGN\(\.,\s*16\);\s*\n"
    r"(\s*cod_SDATA_END\s*=\s*\.\s*;)",
    re.MULTILINE,
)

# Inject `*(SORT_BY_NAME(.X.0x*))` into each data section so any .o file
# (asm or src) contributing a per-VMA named section like `.sdata.0x00631BC0`
# lands at the right VMA. Without this, the per-.o `(.X*)` directives that
# splat emits pull sections in linker-script order — fine when only the
# asm blanket .o contributes, but a src .o (from migrated sdata in a
# matched .c) would land at offset 0 of the section instead of at its
# original VMA.
#
# `tools/rewrite_data_named_sections.py` produces the per-VMA-named
# sections in the asm-side data .o; the SORT_BY_NAME directive here
# sorts across all .o files so src-side migrations slot into the right
# position. When only the asm .o contributes, the sort produces the
# same VMA-order layout as the unsorted per-.o emission, so the
# round-trip stays byte-identical.
SORT_TARGETS = [
    (".data",   "cod_DATA_START"),
    (".rodata", "cod_RODATA_START"),
    (".lit4",   "cod_LIT4_START"),
    (".sdata",  "cod_SDATA_START"),
]
SORT_MARKER_PREFIX = "/* sort-by-name "


def inject_sort_by_name(text: str) -> tuple[str, int]:
    applied = 0
    for sect_name, start_anchor in SORT_TARGETS:
        marker = f"{SORT_MARKER_PREFIX}{sect_name} */"
        if marker in text:
            continue
        anchor_re = re.compile(
            rf"^(?P<indent>[ \t]*){re.escape(start_anchor)}\s*=\s*\.\s*;\s*$",
            re.MULTILINE,
        )
        m = anchor_re.search(text)
        if m is None:
            # Section not present in the ld script — skip silently
            # (e.g. user trimmed the segment). Don't fail the build.
            continue
        indent = m.group("indent")
        # Insert the SORT_BY_NAME pull *after* the START symbol so it
        # appears at the very top of the section body. GNU ld emits
        # each input section once; subsequent per-.o globs won't
        # double-emit.
        injection = (
            f'{indent}{marker}\n'
            f'{indent}*(SORT_BY_NAME(.{sect_name[1:]}.0x*));\n'
        )
        insert_at = m.end() + 1  # past the newline
        text = text[:insert_at] + injection + text[insert_at:]
        applied += 1
    return text, applied


def clear_stale(text: str) -> tuple[str, int]:
    cleared = 0
    out_lines: list[str] = []
    for line in text.splitlines(keepends=True):
        if any(p.match(line) for p in STALE_LINE_PATTERNS):
            cleared += 1
            continue
        out_lines.append(line)
    return "".join(out_lines), cleared


def apply_section_start_patches(text: str) -> tuple[str, int]:
    applied = 0
    for anchor, align, marker, _kind in PATCHES:
        if marker in text:
            continue
        # Insert a top-level `. = ALIGN(., <N>)` immediately before the
        # section declaration line, preserving the section line's indentation.
        pat = re.compile(rf"^(\s*){re.escape(anchor)}\s*$", re.MULTILINE)
        align_line_template = "{indent}. = ALIGN(., 0x{align:X}); /* {marker} */\n"
        def _sub(m: re.Match) -> str:
            indent = m.group(1)
            return (
                align_line_template.format(indent=indent, align=align, marker=marker)
                + m.group(0)
            )
        new_text, n = pat.subn(_sub, text, count=1)
        if n != 1:
            raise SystemExit(
                f"postprocess_ld: anchor {anchor!r} not found "
                f"(splat output changed?)"
            )
        text = new_text
        applied += 1
    return text, applied


def kill_sdata_end_align(text: str) -> tuple[str, int]:
    """Remove the trailing ALIGN(., 16) before cod_SDATA_END = .;"""
    new_text, n = SDATA_END_ALIGN_KILLER.subn(r"\1", text, count=1)
    return new_text, n


# Splat emits one explicit `build/<path>.o(.<section>*);` line per .o
# per data section (~2468 lines × 4 sections = ~9872 lines). Empirical
# audit (mips-linux-gnu-objdump -h over all build/**/*.o) shows ZERO .o
# files carry non-empty plain `.data`/`.sdata`/`.rodata`/`.lit4` —
# every byte goes into the typed `.<section>.0x<VMA>` sections from
# `tools/rewrite_data_named_sections.py`, which the `*(SORT_BY_NAME(...))`
# pattern at the top of each section already pulls in. The explicit
# per-.o lines are redundant overhead: GNU ld still walks each one
# looking for matching sections, multiplying link time. Strip them.
EXPLICIT_DATA_INPUT_RE = re.compile(
    r"^\s+build/[^\n]*\.o\(\.(?:data|sdata|rodata|lit4)\*\);\s*\n",
    re.MULTILINE,
)


def strip_explicit_data_inputs(text: str) -> tuple[str, int]:
    """Drop the redundant per-.o explicit input lines for data sections."""
    new_text, n = EXPLICIT_DATA_INPUT_RE.subn("", text)
    return new_text, n


def patch(text: str) -> tuple[str, int, int]:
    text, cleared = clear_stale(text)
    text, applied = apply_section_start_patches(text)
    text, killed = kill_sdata_end_align(text)
    text, sorted_n = inject_sort_by_name(text)
    text, stripped = strip_explicit_data_inputs(text)
    return text, applied + killed + sorted_n + stripped, cleared


def main() -> int:
    if not LD.exists():
        print(f"postprocess_ld: {LD} not found (skipping — run `make split`)")
        return 0
    original = LD.read_text()
    new, applied, cleared = patch(original)
    if applied or cleared or new != original:
        LD.write_text(new)
        msg = f"postprocess_ld: {LD.name}"
        if cleared:
            msg += f" cleared {cleared} stale line(s)"
        if applied:
            msg += f" applied {applied} patch(es)"
        print(msg)
    else:
        print(f"postprocess_ld: {LD.name} already patched (no changes)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
