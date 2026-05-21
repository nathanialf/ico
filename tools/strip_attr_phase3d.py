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

# `__attribute__((section(".<sec>.0xVMA"))) <type-prefix> <symbol>[N]?`
# Captures type prefix + optional `[N]` array size so we can decide
# between full strip and non-VMA-attribute rewrap.
ATTR_RE = re.compile(
    r'__attribute__\(\(section\("\.(?P<sec>\w+)\.0x(?P<vma>[0-9A-Fa-f]+)"\)\)\)\s+'
    r'(?P<pre>(?:[A-Za-z_]\w*\s+)+\**\s*)'
    r'(?P<name>D_[0-9A-Fa-f]{8})\b'
    r'(?P<arr>\s*\[\s*(?P<n>\d+)\s*\])?'
)

# Base C type → size in bytes. ee-gcc 2.9 on R5900 EABI (default).
_BASE_TYPE_SIZE = {
    "char": 1, "uchar": 1, "u8": 1, "s8": 1, "int8_t": 1, "uint8_t": 1,
    "short": 2, "ushort": 2, "u16": 2, "s16": 2, "int16_t": 2, "uint16_t": 2,
    "int": 4, "uint": 4, "long": 4, "ulong": 4, "u32": 4, "s32": 4,
    "int32_t": 4, "uint32_t": 4, "float": 4,
    "double": 8, "u64": 8, "s64": 8, "int64_t": 8, "uint64_t": 8,
}
_TYPE_MODIFIERS = {"const", "static", "volatile", "signed", "unsigned",
                   "register", "extern"}


def _sizeof_def(pre: str, n_array: int | None) -> int | None:
    """Best-effort sizeof for a typed def's storage. `pre` is the type
    prefix between the attribute and the symbol name (e.g.
    `const float `, `unsigned int `). `n_array` is the `[N]` count or
    None for a scalar. Returns total byte size, or None if the type
    isn't a recognized fundamental (e.g. a struct or pointer)."""
    n = 1 if n_array is None else n_array
    if "*" in pre:
        return 4 * n  # pointer (ee R5900 = 32-bit ABI)
    base = None
    for tok in pre.split():
        if tok in _TYPE_MODIFIERS:
            continue
        if tok in _BASE_TYPE_SIZE:
            base = tok
            break
    if base is None:
        return None
    return _BASE_TYPE_SIZE[base] * n


# Symbols ≤ this size land in `.sdata` under `-G 8` even when typed
# `const` whose original VMA is in `.rodata`. The strip helper must
# rewrite their VMA-pinned attr to a non-VMA `.rodata` placement
# attribute (a legitimate developer directive) instead of fully
# stripping — otherwise ee-gcc's small-data heuristic shifts the
# bytes off-VMA.
_SDATA_LEAK_THRESHOLD = 8


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
        # With the per-symbol slot pipeline, non-promotable TUs strip
        # fine too — each typed def becomes a per-symbol `.X.D_<VMA>`
        # section (via -fdata-sections) at its own VMA, interleaving
        # with foreign-TU symbols naturally. The legacy `promotable`
        # gate was for the old per-TU `(.X*)` glob mechanism.
        ranges = info.get("ranges", [])
        if not ranges:
            continue
        out[sec] = [
            (int(r["lo_vma"], 16), int(r["hi_vma"], 16)) for r in ranges
        ]
    return out


# Matches a complete plain-form typed def (post-strip), including the
# small-const survivor form `__attribute__((section(".rodata"))) <type>
# D_<VMA> = ...`. Both shapes land in the .o's plain `.rodata` (or
# `.<sec>`) section in source-declaration order, so they share one
# VMA-sorted span.
PLAIN_DEF_HEADER_RE = re.compile(
    r'(?m)^'
    r'(?:__attribute__\(\(section\("\.\w+"\)\)\)\s+)?'
    r'(?P<pre>(?:[A-Za-z_]\w*\s+)+\**\s*)'
    r'(?P<name>D_(?P<vma>[0-9A-Fa-f]{8}))\b'
    r'\s*(?:\[[^\]]*\])?\s*='
)


def _find_def_end(text: str, start: int) -> int:
    """Given the start of a `=` in a def, find the matching `;` at brace
    depth 0 (skipping string/char literals + escapes). Returns the
    index just past the `;`."""
    depth = 0
    i = start
    n = len(text)
    while i < n:
        c = text[i]
        if c == '"' or c == "'":
            quote = c
            i += 1
            while i < n:
                if text[i] == '\\':
                    i += 2
                    continue
                if text[i] == quote:
                    i += 1
                    break
                i += 1
            continue
        if c == '{':
            depth += 1
        elif c == '}':
            depth -= 1
        elif c == ';' and depth == 0:
            return i + 1
        i += 1
    return n


def _extract_plain_defs(text: str, ranges: dict[str, list[tuple[int, int]]]
                         ) -> list[tuple[int, int, int]]:
    """Find every plain-form typed def whose VMA falls in any
    promoted range. Returns [(vma, start, end), ...]. `start` is the
    beginning of the line (after leading whitespace); `end` is just
    past the `;`."""
    out: list[tuple[int, int, int]] = []
    for m in PLAIN_DEF_HEADER_RE.finditer(text):
        try:
            vma = int(m.group("vma"), 16)
        except ValueError:
            continue
        in_range = False
        for ranges_list in ranges.values():
            for lo, hi in ranges_list:
                if lo <= vma < hi:
                    in_range = True
                    break
            if in_range:
                break
        if not in_range:
            continue
        # Rewind start to beginning of line (skip leading whitespace
        # but keep the newline before so reordering preserves spacing).
        start = m.start()
        # Skip the `=` sign to find end of def body.
        eq_pos = text.find('=', start)
        if eq_pos == -1:
            continue
        end = _find_def_end(text, eq_pos + 1)
        out.append((vma, start, end))
    return out


def reorder_plain_defs(path: Path, ranges: dict[str, list[tuple[int, int]]],
                       dry_run: bool) -> int:
    """Re-emit the file with plain-form typed defs (those whose VMA
    falls in a promoted range) sorted by VMA ascending. Returns the
    number of defs reordered (0 if already in order)."""
    text = path.read_text()
    defs = _extract_plain_defs(text, ranges)
    if not defs:
        return 0
    # Group into contiguous spans. Two defs are in the same span if
    # the gap between them contains ONLY whitespace and C comments
    # (block or line). This lets us sort across decorative comments
    # ("/* migrated from foo_data.c */") without dragging in code.
    def _gap_is_safe(gap: str) -> bool:
        # Strip C block comments and // line comments, see if what
        # remains is pure whitespace.
        stripped = re.sub(r'/\*.*?\*/', '', gap, flags=re.DOTALL)
        stripped = re.sub(r'//[^\n]*', '', stripped)
        return stripped.strip() == ""
    spans: list[list[tuple[int, int, int]]] = []
    for vma, s, e in defs:
        if spans and _gap_is_safe(text[spans[-1][-1][2]:s]):
            spans[-1].append((vma, s, e))
        else:
            spans.append([(vma, s, e)])
    # Check whether any span is out of VMA order.
    out_of_order = False
    for span in spans:
        vmas = [v for v, _, _ in span]
        if vmas != sorted(vmas):
            out_of_order = True
            break
    if not out_of_order:
        return 0
    # Rebuild: per-span, sort by VMA and rewrite that range.
    new_text = text
    # Process spans in reverse so earlier offsets stay valid.
    for span in reversed(spans):
        vmas = [v for v, _, _ in span]
        if vmas == sorted(vmas):
            continue
        span_start = span[0][1]
        span_end = span[-1][2]
        # Extract each def body verbatim, sort by VMA, rejoin with the
        # original interstitial whitespace (assumed uniform: newlines).
        bodies = [(v, new_text[s:e]) for v, s, e in span]
        bodies.sort(key=lambda x: x[0])
        # Reuse the FIRST inter-def separator as the joiner. If the
        # span has only one def this branch isn't taken.
        sep_start = span[0][2]
        sep_end = span[1][1] if len(span) > 1 else sep_start
        sep = new_text[sep_start:sep_end]
        reordered = sep.join(b for _, b in bodies)
        new_text = new_text[:span_start] + reordered + new_text[span_end:]
    if new_text == text:
        return 0
    if not dry_run:
        path.write_text(new_text)
    return sum(1 for span in spans
               for vmas in [[v for v, _, _ in span]]
               if vmas != sorted(vmas))


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
                arr = m.group("arr") or ""
                n_arr = int(m.group("n")) if m.group("n") else None
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
                # Strip only when ee-gcc's default placement (under
                # -G 8) would match the original section. Otherwise
                # the attr is the legitimate placement directive
                # that an original developer would write and must be
                # retained.
                #
                # ee-gcc default placement table for `<pre> D_X = ...`:
                #   const  size ≤ 8 → .sdata     (-G 8 small)
                #   const  size > 8 → .rodata
                #   mutable size ≤ 8 → .sdata
                #   mutable size > 8 → .data
                #   (no default emission to .lit4 without explicit attr)
                size = _sizeof_def(pre, n_arr)
                is_const = "const" in pre.split()
                default_sec: str | None = None
                if size is not None:
                    if size <= _SDATA_LEAK_THRESHOLD:
                        default_sec = ".sdata"
                    elif is_const:
                        default_sec = ".rodata"
                    else:
                        default_sec = ".data"
                if default_sec != sec:
                    # Keep attr — not a normal default placement.
                    counts[sec] = counts.get(sec, 0) - 1
                    return m.group(0)
                return pre + name + arr
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
        reordered_total = 0
        for f in files:
            counts = strip_file(f, ranges, args.dry_run)
            for sec, n in counts.items():
                tu_per_sec[sec] = tu_per_sec.get(sec, 0) + n
            # After stripping, sort the now-plain defs in this file
            # by VMA. ee-gcc emits .rodata input-section content in
            # source declaration order; without VMA-ascending order,
            # symbols inside the .o land at wrong output VMAs even
            # though the slot itself starts at lo_vma correctly.
            reordered_total += reorder_plain_defs(f, ranges, args.dry_run)
        verb = "would strip" if args.dry_run else "stripped"
        bits = ", ".join(f"{sec}={n}" for sec, n in tu_per_sec.items() if n)
        if not bits:
            bits = "0 attrs (already stripped)"
        suffix = ""
        if reordered_total:
            suffix = f" (+ reordered {reordered_total} span(s) by VMA)"
        print(f"{tu}: {verb} {bits}{suffix}")
        for sec, n in tu_per_sec.items():
            total_per_sec[sec] = total_per_sec.get(sec, 0) + n

    if len(args.tus) > 1 and total_per_sec:
        bits = ", ".join(f"{sec}={n}" for sec, n in sorted(total_per_sec.items()))
        verb = "would strip" if args.dry_run else "stripped"
        print(f"\nTotal: {verb} {bits}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
