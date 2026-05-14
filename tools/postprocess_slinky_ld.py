#!/usr/bin/env python3
"""
postprocess_slinky_ld.py — patch the slinky-generated linker script so
it builds a SHA-1-identical ELF alongside the current
postprocess_ld.py-patched splat output.

slinky emits per-`.o` input-section globs in declared order, e.g.

    .data : AT(data_ROM_START)
    {
        data_DATA_START = .;
        build/src/A.o(.data*);
        build/src/B.o(.data*);
        ...
    }

That model is correct for the *target* state (per-TU plain `.X`
sections, each .o owning one contiguous VMA range), but it doesn't
yet match the current source layout where every `.o` carries scattered
typed `.X.0xVMA` sections that today's `*(SORT_BY_NAME(.X.0x*))` in
`config/ico.us.ld` sorts globally.

Bridge: inject a single `*(SORT_BY_NAME(.X.0x*))` line at the top of
each data/rodata/lit4/sdata block. GNU ld places each input section
at its first matching output reference — so the typed sections are
absorbed in VMA order *before* the per-`.o` globs run, and the
per-`.o` globs end up matching only the empty plain `.X` sections each
relocatable .o carries by default. As TUs migrate to plain sections
in Phase 3d, the per-`.o` globs start carrying actual content and the
SORT_BY_NAME catch-all shrinks. When SORT_BY_NAME is empty the
injector can be retired (Phase 3e).

Also trims the trailing `. = ALIGN(., 16)` slinky emits at the end of
the `.sdata` block — baseelf's `.sdata` ends at exactly `0x633BC6`
(not 16-aligned), and the pad pushes `.rom` 10 bytes longer.

Idempotent. Run as part of `tools/build.sh slinky`.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
LD = REPO / "config" / "ico.us.slinky.ld"

# (start_symbol, section_name) pairs for each section needing SORT_BY_NAME.
SORT_INJECTIONS = [
    ("data_DATA_START",     ".data"),
    ("rodata_RODATA_START", ".rodata"),
    ("lit4_LIT4_START",     ".lit4"),
    ("sdata_SDATA_START",   ".sdata"),
]

# Marker comment so the injection is idempotent — second run sees the
# marker and skips.
SORT_MARKER_PREFIX = "/* sort-by-name "

# Trailing ALIGN(., 16) before sdata_SDATA_END = .;
SDATA_END_ALIGN_RE = re.compile(
    r"\n\s*\.\s*=\s*ALIGN\(\.,\s*16\);\s*\n(\s*sdata_SDATA_END\s*=\s*\.\s*;)",
)


def inject_sort_by_name(text: str) -> tuple[str, int]:
    applied = 0
    for start_sym, sect in SORT_INJECTIONS:
        marker = f"{SORT_MARKER_PREFIX}{sect} */"
        if marker in text:
            continue
        anchor = re.compile(
            rf"(?P<line>\s*{re.escape(start_sym)}\s*=\s*\.\s*;\s*\n)",
        )
        m = anchor.search(text)
        if m is None:
            raise SystemExit(
                f"postprocess_slinky_ld: anchor {start_sym!r} not found "
                f"in {LD.name} (slinky output format changed?)"
            )
        indent = re.match(r"(\s*)", m.group("line").lstrip("\n")).group(1)
        injection = (
            f"{indent}{marker}\n"
            f"{indent}*(SORT_BY_NAME({sect}.0x*));\n"
        )
        insert_at = m.end()
        text = text[:insert_at] + injection + text[insert_at:]
        applied += 1
    return text, applied


def kill_sdata_end_align(text: str) -> tuple[str, int]:
    new_text, n = SDATA_END_ALIGN_RE.subn(r"\n\1", text, count=1)
    return new_text, n


def main() -> int:
    if not LD.exists():
        print(f"postprocess_slinky_ld: {LD} not found "
              "(run `tools/build.sh slinky` first)")
        return 0
    original = LD.read_text()
    text, sorted_n = inject_sort_by_name(original)
    text, killed = kill_sdata_end_align(text)
    if text != original:
        LD.write_text(text)
        bits = []
        if sorted_n:
            bits.append(f"injected {sorted_n} SORT_BY_NAME")
        if killed:
            bits.append("stripped sdata trailing ALIGN")
        print(f"postprocess_slinky_ld: {LD.name} — {', '.join(bits)}")
    else:
        print(f"postprocess_slinky_ld: {LD.name} already patched")
    return 0


if __name__ == "__main__":
    sys.exit(main())
