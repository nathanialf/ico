#!/usr/bin/env python3
"""tools/gen_resplat.py — Phase 2 retail-v2 TU resplat generator.

Converts config/ico.us.yaml's single `[0x000000, asm, src/cod/000000]` .text
blob into per-TU `c` subsegments, incrementally, in strict link order — and
writes the all-INCLUDE_ASM scaffold `.c` file for each newly-added TU.

Inputs (both read-only):
  * config/symbol_addrs.us.txt       -- authoritative function addr/name list.
        TU membership is determined by ADDRESS RANGE against the boundaries
        file below, not by the `// <path>.c` trailer comment or the
        `// ---- <path>` marker alone: ~71 hand-seeded symbols (splat-lost-
        symbol fixups, `_start`, ...) sit above the generated banner and
        carry no trailer, but their addresses still fall inside a game TU's
        span and must be included in that TU's scaffold.
  * baserom/us_text_tu_boundaries.txt -- 216 game TU spans + 2 vendor spans,
        in link order. Authoritative for span edges and order.

State: the c-subsegment prefix already committed in config/ico.us.yaml (i.e.
how many leading TUs, in link order, are already `[..., c, ...]` instead of
folded into the trailing asm filler). Re-derived from the yaml on every run,
so this tool is idempotent and safe to re-invoke with the same or a larger
`--through`.

Usage:
    tools/gen_resplat.py --through 27      # cumulative: TUs [0..27) are `c`
    tools/gen_resplat.py --batch 1         # shorthand: --through 1*27
    tools/gen_resplat.py --batch 1 --batch-size 27
    tools/gen_resplat.py --list            # print the 216 TU index/path table
    tools/gen_resplat.py --through 27 --dry-run

Exceptions: a TU that cannot be folded in (bad span edge, jtbl issue, etc.)
can be listed in config/resplat_exceptions.txt (one path per line, e.g.
`src/box.c`); such a TU is emitted as its own standalone `[offset, asm, ...]`
subsegment (not merged into the trailing filler) so later TUs can still be
converted around it, and no scaffold .c is written for it.
"""
import argparse
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
YAML_PATH = ROOT / "config" / "ico.us.yaml"
SYMBOL_ADDRS_PATH = ROOT / "config" / "symbol_addrs.us.txt"
BOUNDARIES_PATH = ROOT / "baserom" / "us_text_tu_boundaries.txt"
EXCEPTIONS_PATH = ROOT / "config" / "resplat_exceptions.txt"

VRAM_BASE = 0x00100000

HEAD_MARKER = "- [0x000000, asm, src/cod/000000]"
VU_COMMENT_MARKER = "# .vutext"

FUNC_RE = re.compile(
    r"^(?P<name>\w+)\s*=\s*(?P<addr>0x[0-9A-Fa-f]+);\s*//\s*type:func\b"
)
BOUND_RE = re.compile(
    r"^(?P<start>0x[0-9A-Fa-f]+)\s+(?P<end>0x[0-9A-Fa-f]+)\s+(?P<path>\S+)"
    r"(?:\s+#\s*(?P<comment>.*))?$"
)


class TU:
    def __init__(self, start, end, path, comment):
        self.start = start
        self.end = end
        self.path = path
        self.comment = comment or ""
        self.funcs = []  # list of (addr, name), sorted

    @property
    def offset(self):
        return self.start - VRAM_BASE

    @property
    def name(self):
        # yaml subsegment "name" field == path without the .c extension
        assert self.path.endswith(".c"), self.path
        return self.path[:-2]


def parse_boundaries():
    tus = []
    for line in BOUNDARIES_PATH.read_text().splitlines():
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        m = BOUND_RE.match(line)
        if not m:
            continue
        tus.append(
            TU(
                int(m.group("start"), 16),
                int(m.group("end"), 16),
                m.group("path"),
                m.group("comment"),
            )
        )
    return tus


def parse_symbol_funcs():
    """All `type:func` (addr, name) pairs, in file order, regardless of
    whether they carry a `// <path>` trailer."""
    out = []
    for line in SYMBOL_ADDRS_PATH.read_text().splitlines():
        m = FUNC_RE.match(line)
        if m:
            out.append((int(m.group("addr"), 16), m.group("name")))
    return out


def assign_funcs_to_tus(tus, funcs):
    """O(n log n): sort funcs by addr, sweep against sorted TU spans."""
    game_tus = [t for t in tus if t.path != "(vendor)"]
    game_tus_sorted = sorted(game_tus, key=lambda t: t.start)
    funcs_sorted = sorted(funcs, key=lambda f: f[0])

    i = 0
    n = len(game_tus_sorted)
    for addr, name in funcs_sorted:
        while i < n and addr >= game_tus_sorted[i].end:
            i += 1
        if i < n and game_tus_sorted[i].start <= addr < game_tus_sorted[i].end:
            game_tus_sorted[i].funcs.append((addr, name))
        # else: vendor / VU / outside game .text -- not our concern here
    for t in game_tus_sorted:
        t.funcs.sort(key=lambda f: f[0])
    return game_tus


def sanity_check(game_tus, all_tus):
    problems = []
    for idx, t in enumerate(game_tus):
        if not t.funcs:
            problems.append(f"{t.path}: no functions found in span at all")
            continue
        first_addr = t.funcs[0][0]
        if first_addr != t.start:
            problems.append(
                f"{t.path}: first func at 0x{first_addr:X} != span start 0x{t.start:X}"
            )
    # contiguity across the full boundaries list (game + vendor), in file
    # order. A few bytes of inter-TU alignment padding (0/4 observed) is
    # normal and gets absorbed into the preceding subsegment's implicit end;
    # only flag overlaps (negative gap) or suspiciously large gaps.
    for a, b in zip(all_tus, all_tus[1:]):
        gap = b.start - a.end
        if gap < 0 or gap > 4:
            problems.append(
                f"gap/overlap between {a.path}(end 0x{a.end:X}) and "
                f"{b.path}(start 0x{b.start:X}) -- gap=0x{gap:X}"
            )
    if problems:
        print("SANITY CHECK FAILURES:", file=sys.stderr)
        for p in problems:
            print(f"  - {p}", file=sys.stderr)
        sys.exit(1)


def load_exceptions():
    if not EXCEPTIONS_PATH.exists():
        return set()
    out = set()
    for line in EXCEPTIONS_PATH.read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            out.add(line)
    return out


def vendor_tail(all_tus):
    vendor_spans = [t for t in all_tus if t.path == "(vendor)"]
    assert len(vendor_spans) == 2, vendor_spans
    return vendor_spans[1]


def build_yaml_block(game_tus, through, exceptions, all_tus):
    """Return the list of yaml-subsegment text lines (each already newline-
    terminated) representing TUs [0..through) as `c` (or standalone `asm` if
    excepted), followed by exactly one trailing `asm` filler line covering
    everything not yet converted (which degrades to exactly the vendor-tail
    span once through == len(game_tus))."""
    lines = []
    for t in game_tus[:through]:
        off = t.offset
        if t.path in exceptions:
            lines.append(
                f"      - [0x{off:X}, asm, src/cod/{off:06X}]  "
                f"# EXCEPTION: {t.path} kept asm ({t.comment})\n"
            )
        else:
            lines.append(
                f"      - [0x{off:X}, c, {t.name}]  "
                f"# {len(t.funcs)} funcs, {t.comment.split(',')[-1].strip()}\n"
            )

    if through < len(game_tus):
        frontier = game_tus[through]
        off = frontier.offset
        remaining = len(game_tus) - through
        lines.append(
            f"      - [0x{off:X}, asm, src/cod/{off:06X}]  "
            f"# {remaining} game TUs not yet converted, + vendor tail\n"
        )
    else:
        vt = vendor_tail(all_tus)
        off = vt.offset
        lines.append(
            f"      - [0x{off:X}, asm, src/cod/{off:06X}]  "
            f"# vendor tail ({vt.comment})\n"
        )
    return lines


def rewrite_yaml(new_block, dry_run=False):
    text = YAML_PATH.read_text()
    lines = text.splitlines(keepends=True)

    head_idx = next(i for i, l in enumerate(lines) if HEAD_MARKER in l)
    vu_idx = next(
        i for i, l in enumerate(lines) if VU_COMMENT_MARKER in l and i > head_idx
    )

    new_lines = lines[: head_idx + 1] + new_block + lines[vu_idx:]
    new_text = "".join(new_lines)

    if dry_run:
        print("".join(new_block))
        return
    YAML_PATH.write_text(new_text)


def scaffold_c_lines(t):
    lines = ['#include "common.h"', ""]
    for _addr, name in t.funcs:
        lines.append(f'INCLUDE_ASM("asm/nonmatchings/{t.name}", {name});')
        lines.append("")
    return "\n".join(lines) + "\n"


def write_scaffolds(game_tus, through, exceptions):
    written = []
    for t in game_tus[:through]:
        if t.path in exceptions:
            continue
        c_path = ROOT / f"{t.name}.c"
        if c_path.exists():
            continue
        c_path.parent.mkdir(parents=True, exist_ok=True)
        c_path.write_text(scaffold_c_lines(t))
        written.append((t, c_path))
    return written


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--through", type=int, help="cumulative TU count to convert to `c` (0-based count, e.g. 27)")
    ap.add_argument("--batch", type=int, help="shorthand: --through BATCH*batch-size")
    ap.add_argument("--batch-size", type=int, default=27)
    ap.add_argument("--list", action="store_true", help="print TU index/path table and exit")
    ap.add_argument("--dry-run", action="store_true", help="print the generated yaml block, write nothing")
    args = ap.parse_args()

    all_tus = parse_boundaries()
    funcs = parse_symbol_funcs()
    game_tus = assign_funcs_to_tus(all_tus, funcs)
    sanity_check(game_tus, all_tus)

    if args.list:
        for i, t in enumerate(game_tus):
            print(f"{i:3d} 0x{t.start:08X} 0x{t.end:08X} {t.path}  # {len(t.funcs)} funcs")
        return

    if args.batch is not None:
        through = args.batch * args.batch_size
    elif args.through is not None:
        through = args.through
    else:
        ap.error("need --through, --batch, or --list")
        return

    through = max(0, min(through, len(game_tus)))
    exceptions = load_exceptions()

    block = build_yaml_block(game_tus, through, exceptions, all_tus)
    rewrite_yaml(block, dry_run=args.dry_run)

    if args.dry_run:
        return

    written = write_scaffolds(game_tus, through, exceptions)
    total_include_asm = sum(len(t.funcs) for t, _ in written)
    print(f"through={through}/{len(game_tus)}  new scaffold TUs={len(written)}  "
          f"new INCLUDE_ASM lines={total_include_asm}")
    for t, p in written:
        print(f"  {t.path:40s} -> {p.relative_to(ROOT)}  ({len(t.funcs)} funcs)")
    if exceptions:
        print(f"exceptions active: {sorted(exceptions)}")


if __name__ == "__main__":
    main()
