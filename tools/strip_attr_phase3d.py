#!/usr/bin/env python3
"""strip_attr_phase3d.py — remove `__attribute__((section(".X.0xVMA")))`
wrappers from a TU's tracked typed defs, for sections where the TU is
flagged `promotable=true` in decomp/data_tu_boundaries.json.

Usage:
    tools/strip_attr_phase3d.py src/DmaPacket.c
    tools/strip_attr_phase3d.py --dry-run src/queen.c
    tools/strip_attr_phase3d.py --sections .rodata src/Basic.c

Idempotent. A second invocation on the same TU finds zero remaining
attrs and exits 0 (still counted as a successful strip).

For each tracked file (the TU's .c + sibling .h):
  - Find every `__attribute__((section(".<sec>.0x<VMA>"))) ` prefix.
  - If `<sec>` is in the TU's promotable sections AND `<VMA>` lies in
    the TU's range for that section, remove the prefix.

Run `tools/build.sh setup && tools/build.sh slinky && ninja` after to
regen boundaries (`stripped` flips to true), regen the slinky.ld slot
block, and verify SHA-1.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
BOUNDARIES_JSON = REPO / "decomp" / "data_tu_boundaries.json"

# `__attribute__((section(".<sec>.0xVMA"))) <type-prefix> <symbol>` — we
# also capture the type prefix between the attr and the symbol so we
# can patch read-only-string corner cases (e.g. force `const` on `char`
# arrays when stripping `.rodata` attrs).
ATTR_RE = re.compile(
    r'__attribute__\(\(section\("\.(?P<sec>\w+)\.0x(?P<vma>[0-9A-Fa-f]+)"\)\)\)\s+'
    r'(?P<pre>(?:[A-Za-z_]\w*\s+)+\**\s*)'
    r'(?P<name>D_[0-9A-Fa-f]{8})\b'
)


def load_boundaries() -> dict:
    if not BOUNDARIES_JSON.exists():
        raise SystemExit(
            "strip_attr_phase3d: decomp/data_tu_boundaries.json missing — "
            "run tools/build_data_tu_boundaries.py first."
        )
    return json.loads(BOUNDARIES_JSON.read_text())


def promotable_ranges(tu: str, sections_filter: set[str] | None,
                      boundaries: dict
                      ) -> dict[str, list[tuple[int, int]]]:
    """Return {section: [(lo_vma, hi_vma), ...]} for sections that are
    promotable for this TU (optionally filtered by `sections_filter`)."""
    out: dict[str, list[tuple[int, int]]] = {}
    sections = boundaries.get(tu, {})
    for sec, info in sections.items():
        if sections_filter is not None and sec not in sections_filter:
            continue
        if not info.get("promotable"):
            continue
        ranges = info.get("ranges", [])
        out[sec] = [
            (int(r["lo_vma"], 16), int(r["hi_vma"], 16)) for r in ranges
        ]
    return out


def strip_file(path: Path, ranges: dict[str, list[tuple[int, int]]],
               dry_run: bool) -> dict[str, int]:
    """Strip attr wrappers whose `(sec, vma)` falls in a promotable
    range. Returns per-section count of strips performed."""
    counts: dict[str, int] = {sec: 0 for sec in ranges}
    text = path.read_text()
    def replacer(m: re.Match) -> str:
        sec = "." + m.group("sec")
        if sec not in ranges:
            return m.group(0)
        try:
            vma = int(m.group("vma"), 16)
        except ValueError:
            return m.group(0)
        for lo, hi in ranges[sec]:
            if lo <= vma < hi:
                counts[sec] = counts.get(sec, 0) + 1
                pre = m.group("pre")
                name = m.group("name")
                # When stripping `.rodata` attrs from a `char` (or
                # `unsigned char`) array without `const`, ee-gcc would
                # default-place it in `.data` (mutable) instead of
                # `.rodata`, landing the bytes at the wrong VMA. Add
                # `const` so the section choice matches the original.
                if sec == ".rodata" and "const" not in pre:
                    tokens = pre.split()
                    if tokens and tokens[-1] in ("char", "wchar_t"):
                        pre = "const " + pre
                    elif (len(tokens) >= 2 and tokens[-2] == "unsigned"
                          and tokens[-1] == "char"):
                        pre = "const " + pre
                return pre + name
        return m.group(0)
    new_text = ATTR_RE.sub(replacer, text)
    if new_text != text and not dry_run:
        path.write_text(new_text)
    return counts


def tu_sources(tu: str) -> list[Path]:
    """The .c file + its sibling .h, if any."""
    out: list[Path] = []
    if tu.endswith(".c"):
        c = REPO / tu
        if c.exists():
            out.append(c)
        h = REPO / (tu[:-2] + ".h")
        if h.exists():
            out.append(h)
    return out


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("tus", nargs="+",
                    help="TU paths (e.g. src/DmaPacket.c)")
    ap.add_argument("--sections", nargs="+",
                    help="Restrict to these sections (e.g. .rodata .sdata)")
    ap.add_argument("--dry-run", action="store_true",
                    help="Preview strips without editing files")
    args = ap.parse_args()

    boundaries = load_boundaries()
    sec_filter = set(args.sections) if args.sections else None

    total_per_sec: dict[str, int] = {}
    for tu in args.tus:
        ranges = promotable_ranges(tu, sec_filter, boundaries)
        if not ranges:
            print(f"{tu}: no promotable sections "
                  f"(filter={sorted(sec_filter) if sec_filter else 'all'})")
            continue
        files = tu_sources(tu)
        if not files:
            print(f"{tu}: no tracked source files found", file=sys.stderr)
            continue
        tu_per_sec: dict[str, int] = {sec: 0 for sec in ranges}
        for f in files:
            counts = strip_file(f, ranges, args.dry_run)
            for sec, n in counts.items():
                tu_per_sec[sec] = tu_per_sec.get(sec, 0) + n
        verb = "would strip" if args.dry_run else "stripped"
        bits = ", ".join(f"{sec}={n}" for sec, n in tu_per_sec.items() if n)
        if not bits:
            bits = "0 attrs (already stripped)"
        print(f"{tu}: {verb} {bits}")
        for sec, n in tu_per_sec.items():
            total_per_sec[sec] = total_per_sec.get(sec, 0) + n

    if len(args.tus) > 1 and total_per_sec:
        bits = ", ".join(f"{sec}={n}" for sec, n in sorted(total_per_sec.items()))
        verb = "would strip" if args.dry_run else "stripped"
        print(f"\nTotal: {verb} {bits}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
