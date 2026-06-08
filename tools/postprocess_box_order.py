#!/usr/bin/env python3
"""
postprocess_box_order.py — reproduce the shipped box.o trace-reorder.

box.c (`#include "switch.c.inc"`) compiles with -ffunction-sections (see
config/extra_cflags.txt `BOX`) so every function lands in its own
`.text.<func>` section. The dev's release build reordered these functions
(trace-guided, I-cache locality) into the interleaved layout the shipped ROM
has. splat emits a single `build/sugipon/src/box.o(.text*)` glob, which would
place the functions in source order — wrong. This patch replaces that glob
with an explicit per-function list in shipped-VMA order (from
config/symbol_addrs.aug6.txt), reproducing the reorder.

Run after `splat split` (wired into tools/build.sh, aug6 path). Idempotent:
splat regenerates the single glob each split; this re-expands it. If the
expanded block is already present it is regenerated in place.
"""
from __future__ import annotations
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
LD = ROOT / "config" / "ico.aug6.ld"
SYMS = ROOT / "config" / "symbol_addrs.aug6.txt"

# box.o VMA range (shipped): switchOnSE .. just before boy
LO, HI = 0x001B93F0, 0x001BE548
OBJ = "build/sugipon/src/box.o"
BEGIN = "        /* BEGIN box trace-reorder (postprocess_box_order.py) */"
END = "        /* END box trace-reorder */"


def ordered_funcs() -> list[str]:
    rows = []
    for ln in SYMS.read_text().splitlines():
        m = re.match(r"(\w+)\s*=\s*0x([0-9A-Fa-f]+);.*type:func", ln)
        if m:
            a = int(m.group(2), 16)
            if LO <= a < HI:
                rows.append((a, m.group(1)))
    rows.sort()
    return [n for _, n in rows]


def build_block(funcs: list[str]) -> str:
    lines = [BEGIN]
    lines += [f"        {OBJ}(.text.{f});" for f in funcs]
    # catch the residual plain .text (labels.inc symbol defs) + any stray section
    lines.append(f"        {OBJ}(.text*);")
    lines.append(END)
    return "\n".join(lines)


def main() -> int:
    funcs = ordered_funcs()
    if len(funcs) < 70:
        print(f"postprocess_box_order: only {len(funcs)} funcs in box.o range — abort", file=sys.stderr)
        return 1
    text = LD.read_text()
    block = build_block(funcs)

    if BEGIN in text:  # already expanded (re-run without a fresh splat) — regenerate
        text = re.sub(re.escape(BEGIN) + r".*?" + re.escape(END), block, text, count=1, flags=re.S)
    else:
        single = re.compile(r"^[ \t]*" + re.escape(f"{OBJ}(.text*);") + r"[ \t]*$", re.M)
        if not single.search(text):
            print("postprocess_box_order: box.o(.text*) glob not found in ld — abort", file=sys.stderr)
            return 1
        text = single.sub(block.replace("\\", "\\\\"), text, count=1)

    LD.write_text(text)
    print(f"postprocess_box_order: ordered {len(funcs)} box.o function sections by VMA")
    return 0


if __name__ == "__main__":
    sys.exit(main())
