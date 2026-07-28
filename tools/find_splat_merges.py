#!/usr/bin/env python3
"""tools/find_splat_merges.py — interior-prologue splat-merge boundary detector.

Splat carves `.text` into functions using the symbol table.  Where the ROM's
symbol table lost a boundary (retail-v2 inherited none of the aug6 tree's
`splat-merge …split` entries), splat glues two or more real functions into a
single `glabel`, and the resulting `asm/nonmatchings/<tu>/<head>.s` silently
contains N functions.  Those hidden bodies can never be matched, because the
C file only ever declares the head.

The detector is purely local (conv-6, validated 31/31).  Reachability analysis
is the WRONG tool: jump tables and trailing `.p2align` pads false-positive on
it.  The reliable signatures are:

  A. an interior `addiu $29, $29, -N` whose address is not the target of any
     `.L…` label in the file  → a merged function's stack prologue;
  B. the instruction after a *non-final* `jr $31` (+ delay slot), or after a
     non-final tail-call `j <sym>`, when that address is not a label target
     → the start of the next (possibly frameless) merged function.

Cross-check: the aug6 prototype tree already carved essentially every one of
these families, so `config/symbol_addrs.aug6.txt` in the aug6 checkout carries
a `splat-merge …split` entry for the twin.  A candidate whose aug6 twin TU
holds splits attributed to the same head function is near-certain.

Usage:
    tools/find_splat_merges.py                    # sweep every live nonmatching
    tools/find_splat_merges.py --tu src/boyact    # one TU
    tools/find_splat_merges.py --all-files        # include stale .s (matched funcs)
    tools/find_splat_merges.py --format=symbols   # emit symbol_addrs.us.txt lines
    tools/find_splat_merges.py --json out.json
"""

import argparse
import json
import os
import re
import subprocess
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
AUG6_ROOT = Path(os.environ.get("PORT_AUG6_ROOT", "/primary/dev/ico"))

INSN_RE = re.compile(
    r"^\s*/\* ([0-9A-Fa-f]+) ([0-9A-Fa-f]{8}) ([0-9A-Fa-f]{8}) \*/\s+(\S+)\s*(.*)$"
)
LABEL_RE = re.compile(r"^\s*(\.L[0-9A-Fa-f]+|[A-Za-z_.$][\w.$]*):\s*$")
GLABEL_RE = re.compile(r"^\s*g?label\s+(\S+)")
NONMATCHING_RE = re.compile(r"^\s*nonmatching\s+(\S+),\s*(0x[0-9A-Fa-f]+)")
INCLUDE_ASM_RE = re.compile(r'INCLUDE_ASM\("([^"]+)",\s*(\w+)')

SRC_DIRS = ("src", "isys", "ios", "ito", "sound")


# ---------------------------------------------------------------- asm parsing
def parse_s(path):
    """-> dict(name, size, insns=[(vma, mnem, args)], labels=set(vma))"""
    insns = []
    labels = set()
    name = None
    size = None
    pending_labels = []
    for line in path.read_text(errors="replace").splitlines():
        m = NONMATCHING_RE.match(line)
        if m:
            name, size = m.group(1), int(m.group(2), 16)
            continue
        m = GLABEL_RE.match(line)
        if m:
            if name is None:
                name = m.group(1)
            continue
        m = INSN_RE.match(line)
        if m:
            vma = int(m.group(2), 16)
            for _ in pending_labels:
                labels.add(vma)
            pending_labels = []
            insns.append((vma, m.group(4), m.group(5).strip()))
            continue
        m = LABEL_RE.match(line)
        if m:
            pending_labels.append(m.group(1))
    return {"name": name, "size": size, "insns": insns, "labels": labels}


PROLOGUE_RE = re.compile(r"^\$29,\s*\$29,\s*-0x[0-9A-Fa-f]+")


def is_prologue(mnem, args):
    return mnem in ("addiu", "daddiu") and PROLOGUE_RE.match(args) is not None


def is_return(mnem, args):
    return mnem == "jr" and args.split(",")[0].strip() == "$31"


def is_tailcall(mnem, args):
    # `j <symbol>` (not `j .L…`) as a sibling-call tail
    return mnem == "j" and not args.strip().startswith(".L")


UNCOND = ("b", "j", "jr")


def is_uncond(mnem):
    return mnem in UNCOND


def detect(rec):
    """-> [ {vma, evidence} ] candidate boundaries inside one .s

    An instruction starts a hidden function when control cannot arrive at it:
    it is not the head, no `.L…` label names it (labels cover jump-table
    targets, which is why raw reachability false-positives without this), and
    its predecessor cannot fall through — i.e. the instruction two back is an
    unconditional `b` / `j` / `jr` whose delay slot is the predecessor.
    `.p2align` pad `nop`s sit in exactly that position, so a flagged `nop` run
    is skipped forward to the first real instruction (or dropped at EOF).
    """
    insns, labels = rec["insns"], rec["labels"]
    n = len(insns)
    out = {}
    # A jump-table dispatch (`jr $N`, N != 31) sends control to case blocks
    # whose entry addresses live in `.rodata` and therefore carry no `.L…`
    # label in this file: every case block reads as "unreachable".  Flag the
    # file so those candidates can be down-ranked instead of trusted.
    rec["jtbl"] = any(
        m == "jr" and a.split(",")[0].strip() not in ("$31",) for _, m, a in insns
    ) or any("jtbl_" in a for _, _, a in insns)
    for i in range(1, n):
        vma, mnem, args = insns[i]
        if vma in labels:
            continue
        if not (i >= 2 and is_uncond(insns[i - 2][1])):
            continue          # ordinary fall-through
        term = insns[i - 2]
        # walk past `.p2align` padding
        k = i
        while k < n and insns[k][1] == "nop":
            k += 1
        if k >= n:
            continue          # trailing pad only
        if insns[k][0] in labels:
            continue
        why = "jr $31" if is_return(*term[1:]) else (
            f"tail {term[1]} {term[2]}" if term[1] == "j" else f"{term[1]} {term[2]}")
        ev = f"unreachable after {why} at 0x{term[0]:08X}"
        if is_prologue(*insns[k][1:]):
            ev = "unlabeled interior prologue; " + ev
        out.setdefault(insns[k][0], []).append(ev)
    res = []
    for v, evs in sorted(out.items()):
        ev = "; ".join(evs)
        if "prologue" in ev:
            conf = "high"
        elif rec["jtbl"]:
            conf = "low"        # almost certainly a jump-table case block
        else:
            conf = "med"
        res.append({"vma": v, "evidence": ev, "conf": conf})
    return res


# --------------------------------------------------------------- live filter
def live_include_asm():
    """-> {(tu_stem, func) : c_file} for every INCLUDE_ASM currently compiled."""
    live = {}
    for d in SRC_DIRS:
        p = ROOT / d
        if not p.is_dir():
            continue
        for c in p.rglob("*.c"):
            for m in INCLUDE_ASM_RE.finditer(c.read_text(errors="replace")):
                stem = m.group(1).replace("asm/nonmatchings/", "")
                live[(stem, m.group(2))] = str(c.relative_to(ROOT))
    return live


# ------------------------------------------------------------ aug6 crosscheck
AUG6_SPLIT_RE = re.compile(
    r"^(\w+)\s*=\s*0x([0-9A-Fa-f]+);.*//\s*([\w/.]+)\s*//\s*splat-merge[^(]*\(([^)]+?)\s*(?:act-thread\s*)?coroutine\)"
)
AUG6_SPLIT_LOOSE = re.compile(
    r"^(\w+)\s*=\s*0x([0-9A-Fa-f]+);.*//\s*([\w/.]+)\s*//\s*splat-merge.*?\(([^)]*)\)"
)


def aug6_splits():
    """-> {aug6_stem: [ (sym, vma, head) ]}"""
    f = AUG6_ROOT / "config" / "symbol_addrs.aug6.txt"
    out = defaultdict(list)
    if not f.exists():
        return out
    for line in f.read_text(errors="replace").splitlines():
        if "splat-merge" not in line:
            continue
        m = AUG6_SPLIT_RE.match(line) or AUG6_SPLIT_LOOSE.match(line)
        if not m:
            continue
        sym, vma, tu, head = m.group(1), int(m.group(2), 16), m.group(3), m.group(4)
        stem = tu[:-2] if tu.endswith(".c") else tu           # fumi/src/boyact
        short = stem.split("/", 1)[1] if "/" in stem else stem  # src/boyact
        head = head.replace("act-thread ", "").strip()
        out[short].append({"sym": sym, "vma": vma, "head": head, "aug6_tu": stem})
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--tu", help="restrict to one TU stem, e.g. src/boyact")
    ap.add_argument("--all-files", action="store_true",
                    help="also scan stale .s of already-matched functions")
    ap.add_argument("--format", choices=("table", "symbols"), default="table")
    ap.add_argument("--json", help="write the candidate table as JSON")
    ap.add_argument("--min-conf", choices=("high", "med", "low"), default="med",
                    help="report threshold; `low` are jump-table case blocks")
    args = ap.parse_args()

    live = live_include_asm()
    splits = aug6_splits()

    rows = []
    base = ROOT / "asm" / "nonmatchings"
    for p in sorted(base.rglob("*.s")):
        stem = str(p.parent.relative_to(base))
        if args.tu and stem != args.tu:
            continue
        rec = parse_s(p)
        if not rec["insns"]:
            continue
        head = rec["name"] or p.stem
        is_live = (stem, head) in live
        if not is_live and not args.all_files:
            continue
        cands = detect(rec)
        if not cands:
            continue
        aug6 = splits.get(stem, [])
        aug6_same_head = [s for s in aug6 if s["head"] == head]
        rank = {"high": 0, "med": 1, "low": 2}
        for c in cands:
            if rank[c["conf"]] > rank[args.min_conf]:
                continue
            rows.append({
                "tu": stem,
                "file": str(p.relative_to(ROOT)),
                "head": head,
                "head_vma": rec["insns"][0][0],
                "head_size": rec["size"],
                "vma": c["vma"],
                "offset": c["vma"] - rec["insns"][0][0],
                "evidence": c["evidence"],
                "conf": c["conf"],
                "jtbl_file": rec["jtbl"],
                "live": is_live,
                "aug6_tu_splits": len(aug6),
                "aug6_head_splits": len(aug6_same_head),
                "aug6_syms": [s["sym"] for s in aug6_same_head],
            })

    if args.json:
        Path(args.json).write_text(json.dumps(rows, indent=1))

    if args.format == "symbols":
        seen = set()
        for r in rows:
            if r["vma"] in seen:
                continue
            seen.add(r["vma"])
            print(f'func_{r["vma"]:08X} = 0x{r["vma"]:08X}; '
                  f'// type:func  // {r["tu"]}.c  '
                  f'// splat-merge split ({r["head"]} coroutine)')
        return

    bytu = defaultdict(list)
    for r in rows:
        bytu[r["tu"]].append(r)
    print(f"{'TU':<26} {'head':<32} {'VMA':>10} {'+off':>7} conf  aug6  evidence")
    print("-" * 118)
    for tu in sorted(bytu):
        for r in bytu[tu]:
            cc = ("HEAD-MATCH" if r["aug6_head_splits"]
                  else ("tu:%d" % r["aug6_tu_splits"] if r["aug6_tu_splits"] else "-"))
            print(f'{tu:<26} {r["head"]:<32} 0x{r["vma"]:08X} '
                  f'{r["offset"]:>7} {r["conf"]:>4} {cc:>10}  {r["evidence"]}')
    heads = {(r["tu"], r["head"]) for r in rows}
    print("-" * 118)
    print(f"{len(rows)} candidate boundaries in {len(heads)} functions "
          f"across {len(bytu)} TUs")


if __name__ == "__main__":
    sys.exit(main())
