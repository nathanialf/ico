#!/usr/bin/env python3
"""map_data_tus.py — reconstruct per-TU ownership runs inside the data blobs.

For a given section family (default .rodata), inventory every symbol in the
splat blob disassemblies (asm/data/src/cod/*.<sect>.s), map each symbol to the
TUs that reference it (C sources + asm/nonmatchings stubs), then print the
address-ordered stream annotated with ownership so contiguous per-TU runs and
their boundaries become visible.  This is the evidence layer for converting
`src/cod` blob subsegments into full per-TU dot-form carves.

Ownership classes per symbol:
  TU <name>   exactly one referencing TU  -> anchor for that TU's run
  SHARED      2+ referencing TUs          -> position between same-TU anchors
                                             usually disambiguates
  UNREF       no reference found          -> boundary-gap filler (strings,
                                             padding, data used via computed
                                             addressing)
  CARVED <tu> already carved in the yaml

Usage:
  tools/map_data_tus.py                 # .rodata stream
  tools/map_data_tus.py --sect data
  tools/map_data_tus.py --runs         # collapsed runs only
"""
import argparse
import collections
import os
import re
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import pathlib  # noqa: E402
from ico_version import detect_version  # noqa: E402

VERSION = detect_version(pathlib.Path(ROOT))
YAML = os.path.join(ROOT, "config", f"ico.{VERSION}.yaml")

DLABEL_RE = re.compile(r"^(?:dlabel|jlabel)\s+(\w+)")
VMA_LINE_RE = re.compile(r"^\s*/\* ([0-9A-F]{6,8}) ([0-9A-F]{8}) ")
SYM_REF_RE = re.compile(r"\b(D_[0-9A-Fa-f]{8}|jtbl_[0-9A-Fa-f]{8})\b")
CARVE_RE = re.compile(
    r"- \[0x([0-9A-Fa-f]+), \.(\w+), ([\w/\-]+)\]")
BLOB_RE = re.compile(
    r"- \[0x([0-9A-Fa-f]+), (\w+), src/cod/([0-9A-Fa-f]+)\]")
CSEG_RE = re.compile(r"- \[0x([0-9A-Fa-f]+), c, ([\w/\-]+)\]")

VRAM_OFF = 0x100000  # rom -> vram for the cod data segment


def sym_vma(name):
    m = re.match(r"(?:D|jtbl)_([0-9A-Fa-f]{8})", name)
    return int(m.group(1), 16) if m else None


def inventory(sect):
    """[(vma, name)] address-ordered from blob .s files for the section."""
    out = []
    blobdir = os.path.join(ROOT, "asm", "data", "src", "cod")
    for fn in sorted(os.listdir(blobdir)):
        if not fn.endswith(f".{sect}.s"):
            continue
        path = os.path.join(blobdir, fn)
        cur = None
        for line in open(path, encoding="utf-8", errors="replace"):
            m = DLABEL_RE.match(line)
            if m:
                cur = m.group(1)
                v = sym_vma(cur)
                if v is None:
                    # named symbol: take VMA from the first byte line after
                    cur = (cur, None)
                    continue
                out.append((v, cur))
                cur = None
            elif isinstance(cur, tuple):
                mv = VMA_LINE_RE.match(line)
                if mv:
                    out.append((int(mv.group(2), 16), cur[0]))
                    cur = None
    out.sort()
    return out


def consumers():
    """sym -> set(tu) from C sources and asm/nonmatchings stubs."""
    refs = collections.defaultdict(set)
    src_roots = ("src", "ios", "isys", "ito", "sound")
    for root in src_roots:
        top = os.path.join(ROOT, root)
        for dirpath, _dirs, files in os.walk(top):
            for f in files:
                if not f.endswith(".c"):
                    continue
                tu = os.path.relpath(os.path.join(dirpath, f), ROOT)[:-2]
                try:
                    text = open(os.path.join(dirpath, f),
                                encoding="utf-8", errors="replace").read()
                except OSError:
                    continue
                for s in SYM_REF_RE.findall(text):
                    refs[s].add(tu)
    nm = os.path.join(ROOT, "asm", "nonmatchings")
    for dirpath, _dirs, files in os.walk(nm):
        for f in files:
            if not f.endswith(".s"):
                continue
            tu = os.path.relpath(dirpath, nm)
            try:
                text = open(os.path.join(dirpath, f),
                            encoding="utf-8", errors="replace").read()
            except OSError:
                continue
            for s in SYM_REF_RE.findall(text):
                refs[s].add(tu)
    return refs


def yaml_info(sect):
    """(carves [(vma, tu)], text_order [tu...]) from the yaml."""
    carves = []
    text_order = []
    for line in open(YAML, encoding="utf-8"):
        m = CARVE_RE.search(line)
        if m and m.group(2) == sect:
            carves.append((int(m.group(1), 16) + VRAM_OFF, m.group(3)))
        m = CSEG_RE.search(line)
        if m:
            text_order.append(m.group(2))
    return carves, text_order


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sect", default="rodata")
    ap.add_argument("--runs", action="store_true",
                    help="print collapsed ownership runs only")
    args = ap.parse_args()

    inv = inventory(args.sect)
    refs = consumers()
    carves, text_order = yaml_info(args.sect)
    text_rank = {tu: i for i, tu in enumerate(text_order)}

    stream = []  # (vma, sym, class, owner)
    for vma, sym in inv:
        tus = sorted(refs.get(sym, ()))
        # a stub in the SAME dir as its TU c file counts once
        if len(tus) == 1:
            stream.append((vma, sym, "TU", tus[0]))
        elif len(tus) > 1:
            stream.append((vma, sym, "SHARED", ",".join(tus)))
        else:
            stream.append((vma, sym, "UNREF", ""))
    for vma, tu in carves:
        stream.append((vma, f"<carve>", "CARVED", tu))
    stream.sort()

    if args.runs:
        # collapse: consecutive entries owned by the same TU (TU/CARVED),
        # folding SHARED/UNREF into the current run tentatively
        runs = []
        cur_tu, cur_start, pend = None, None, []
        for vma, sym, cls, owner in stream:
            if cls in ("TU", "CARVED"):
                if owner == cur_tu:
                    pend = []
                    continue
                runs.append((cur_start, vma, cur_tu, list(pend)))
                cur_tu, cur_start, pend = owner, vma, []
            else:
                pend.append((vma, sym, cls, owner))
        runs.append((cur_start, None, cur_tu, list(pend)))
        for start, end, tu, gap in runs:
            if tu is None:
                continue
            rk = text_rank.get(tu, -1)
            print(f"{start:08X}..{'%08X' % end if end else '     end'} "
                  f"{tu}  (text#{rk})"
                  + (f"  gap-tail:{len(gap)}" if gap else ""))
    else:
        for vma, sym, cls, owner in stream:
            print(f"{vma:08X} {cls:7s} {sym:24s} {owner}")


if __name__ == "__main__":
    main()
