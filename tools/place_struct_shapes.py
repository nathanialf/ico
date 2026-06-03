#!/usr/bin/env python3
"""place_struct_shapes.py — emit recovered struct typedefs into owning TUs.

Reads the corpus-wide struct shapes (decomp/struct_shapes.json) and the
data->TU assignment (decomp/data_tu_map.json), and writes, for every TU
that owns shape-carrying data symbols, the recovered
`typedef struct { ... } S_<VMA>;` blocks directly into that TU's tracked
`.c` file (NOT a header, NOT the _data.c sidecar).

The typedefs are unused scaffolding: they introduce no symbol and reference
nothing, so they cannot change codegen or the byte-exact link. They give
matching authors a clean-room typed handle (`((S_<VMA> *)D_<VMA>)`) for the
sparse field layout mined from access mnemonics.

Blocks are wrapped in a BEGIN/END banner so re-running replaces the region
idempotently rather than appending duplicates.

Usage:
  tools/place_struct_shapes.py            # all owning TUs
  tools/place_struct_shapes.py <tu.c>...  # only the named TU file(s)
  tools/place_struct_shapes.py --check    # report counts, write nothing
"""
from __future__ import annotations

import json
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
SHAPES = ROOT / "decomp" / "struct_shapes.json"
TU_MAP = ROOT / "decomp" / "data_tu_map.json"

BEGIN = "/* recovered struct shapes */"
END = "/* end struct shapes */"


def c_type(width: int, signed: bool) -> str:
    base = {1: "char", 2: "short", 4: "int", 8: "long long"}.get(width)
    if base is None:
        return f"/* width {width} */ unsigned char"
    if width == 1:
        return "char" if signed else "unsigned char"
    return base if signed else f"unsigned {base}"


def merge_fields(fields: list[dict]) -> list[dict]:
    """Collapse accesses sharing an offset into one member.

    The same byte offset is often touched at several widths/signs (e.g. a
    byte read and a word read of the same field). A C struct needs one
    member per name, so pick the widest access (it spans the others) and
    the dominant sign, summing the access counts. Mixed-width offsets are
    flagged so the reader knows the merge happened.
    """
    by_off: dict[int, list[dict]] = defaultdict(list)
    for f in fields:
        by_off[f["off"]].append(f)
    out = []
    for off in sorted(by_off):
        group = by_off[off]
        width = max(g["width"] for g in group)
        # dominant sign among accesses at the widest width; tie -> unsigned
        widest = [g for g in group if g["width"] == width]
        signed_votes = sum(g["count"] for g in widest if g["signed"])
        unsigned_votes = sum(g["count"] for g in widest if not g["signed"])
        signed = signed_votes > unsigned_votes
        out.append({
            "off": off,
            "width": width,
            "signed": signed,
            "count": sum(g["count"] for g in group),
            "mixed": len({g["width"] for g in group}) > 1,
        })
    return out


def render_typedef(sym: str, info: dict) -> str:
    vma = sym[2:]  # strip "D_"
    lines = [f"typedef struct {{"]
    for f in merge_fields(info["fields"]):
        off = f["off"]
        ct = c_type(f["width"], f["signed"])
        lines.append(f"    {ct:<18} f_{off:X};  /* 0x{off:02X} */")
    stride = info.get("stride")
    trailer = f"  /* stride 0x{stride:X} */" if stride else ""
    lines.append(f"}} S_{vma};{trailer}")
    return "\n".join(lines)


def render_block(syms: list[tuple[str, dict]]) -> str:
    out = [BEGIN]
    for sym, info in syms:
        out.append(render_typedef(sym, info))
        out.append("")
    out.append(END)
    return "\n".join(out) + "\n"


def splice(text: str, block: str) -> str:
    """Replace an existing banner region, else append at end of file."""
    if BEGIN in text and END in text:
        pre = text[: text.index(BEGIN)]
        post = text[text.index(END) + len(END):]
        # drop a single trailing newline left after END so we don't pile up blanks
        post = post.lstrip("\n")
        joined = pre.rstrip("\n") + "\n\n" + block
        if post:
            joined += "\n" + post
        return joined
    sep = "" if text.endswith("\n\n") else ("\n" if text.endswith("\n") else "\n\n")
    return text + sep + "\n" + block


def main(argv: list[str]) -> int:
    check = "--check" in argv
    only = [a for a in argv if not a.startswith("--")]

    globals_ = json.loads(SHAPES.read_text())["globals"]
    # data_tu_map.json is the explicit data->TU assignment (populated on the
    # retail branch). On aug6 it is empty, so we fall back to the per-symbol
    # path-derived `tu` hint that dump_all_struct_shapes.py now records in
    # struct_shapes.json. Tolerate a missing/empty map.
    tumap = json.loads(TU_MAP.read_text()) if TU_MAP.exists() else {}
    if not isinstance(tumap, dict):
        tumap = {}

    keep_all = "--all" in argv
    by_tu: dict[str, list[tuple[str, dict]]] = defaultdict(list)
    skipped_scalar = skipped_neg = 0
    for sym, info in globals_.items():
        # A single field at offset 0 with no array stride is a plain scalar
        # global, not a struct — skip unless --all is given.
        is_struct = len(info["fields"]) >= 2 or info.get("stride")
        if not is_struct and not keep_all:
            skipped_scalar += 1
            continue
        # Negative field offsets mean the symbol is indexed backward from its
        # base — it points into the middle of a larger struct, not at offset 0.
        # That can't be modeled as a struct-at-base, so skip it.
        if any(f["off"] < 0 for f in info["fields"]):
            skipped_neg += 1
            continue
        # owning TU: prefer an explicit data_tu_map entry, else the per-symbol
        # path-derived hint from struct_shapes.json. Normalize to the .c path.
        entry = tumap.get(sym)
        tu = entry.get("tu") if isinstance(entry, dict) else None
        if not tu:
            tu = info.get("tu")
        if not tu or tu == "_unassigned":
            continue
        if not tu.endswith(".c"):
            tu += ".c"
        by_tu[tu].append((sym, info))

    # stable order: most-accessed first within a TU
    for tu in by_tu:
        by_tu[tu].sort(key=lambda kv: (-kv[1]["accesses"], kv[0]))

    targets = sorted(by_tu)
    if only:
        want = {o if o.endswith(".c") else o for o in only}
        targets = [t for t in targets if t in want or Path(t).name in want]

    total = 0
    for tu in targets:
        syms = by_tu[tu]
        path = ROOT / tu
        if not path.exists():
            print(f"  SKIP (no file): {tu}  ({len(syms)} syms)")
            continue
        total += len(syms)
        if check:
            print(f"  {len(syms):4d}  {tu}")
            continue
        block = render_block(syms)
        new = splice(path.read_text(), block)
        path.write_text(new)
        print(f"  wrote {len(syms):4d} typedefs -> {tu}")

    print(f"{'would place' if check else 'placed'} {total} typedefs across "
          f"{len(targets)} TUs"
          + (f"  (skipped {skipped_scalar} scalar globals, "
             f"{skipped_neg} negative-base)" if not keep_all else
             f"  (skipped {skipped_neg} negative-base)"))
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv[1:]))
