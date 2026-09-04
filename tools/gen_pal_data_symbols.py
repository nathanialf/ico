#!/usr/bin/env python3
"""gen_pal_data_symbols.py — recover PAL DATA symbol names for the retail ELF.

WHAT THIS DOES
--------------
`tools/gen_pal_symbol_addrs.py` recovers .text: 5288 of 5502 PAL function
names.  It leaves every DATA object as a splat auto-name (`D_<VMA>` /
`jtbl_<VMA>`).  This tool recovers data names, and writes:

  * config/symbol_addrs.pal.data.txt   (tracked) -- one entry per placed
        symbol (a `size:` and no `type:` -- splat 0.40 has no `data` type),
        with the owning TU and an evidence tier.  Listed in
        config/ico.pal.yaml's `symbol_addrs_path` beside the function file, so
        the two generators never touch each other's output.
  * baserom/pal/data_member_runs.txt   (untracked) -- the per-(member,section)
        ROM run this tool determined, and whether its size agrees with the map.
  * .port_cache/pal_data_names.json    (untracked) -- old -> new mapping with
        tier and evidence, consumed by --rename to rewrite the C sources.

USAGE
-----
    tools/gen_pal_data_symbols.py --report   # diagnostics only, write nothing
    tools/gen_pal_data_symbols.py            # write all three outputs
    tools/gen_pal_data_symbols.py --rename   # ... and rewrite C/asm references

PROVENANCE -- read before trusting a name
-----------------------------------------
Names come from baserom/pal/MAIN.MAP, the GNU ld link map shipped on the
retail SCES-50760 disc (docs/LEGAL.md: a fact observable in media you own,
re-derived, never a committed table).  ADDRESSES are never copied from it.

!! MAIN.MAP IS A DIFFERENT LINK !!  Its .text is 0x16a29c against the shipped
ELF's 0x189bc4; its .data is 0x2db338 against 0x2be680; its .rodata 0xde418
against 0xeb780.  Members grew and shrank between the two links (the .lit4
carve batch measured only 6 of 13 member sizes agreeing -- decomp/carve_ledger
"PAL phase 1").  So the map supplies, per ico2000.a member:

  * WHICH named objects the member defines, and
  * their OFFSETS INSIDE the member (addr - member start), and
  * the member's link ORDER and its size in *that* link.

and nothing else.  Every emitted address is a PAL rom address.

METHOD
------
1. ROM STREAM.  Every `dlabel` in the splat data blobs (asm/data/**/*.s) is a
   rom-native symbol: an address some instruction actually forms.  Sizes are
   the delta to the next label in the same section.

2. OWNERSHIP.  Each D_ symbol is mapped to the TUs that reference it, by
   scanning the C sources and every `.s` under asm/ except the blobs
   themselves.  A symbol referenced by exactly one TU is that TU's ANCHOR.
   (This is tools/map_data_tus.py's evidence layer, widened to the `asm`-typed
   subsegments that have no asm/nonmatchings tree.)

3. WINDOW.  Members are placed in link order, so member i's rom run starts
   after member i-1's last anchor and ends before member i+1's first anchor.
   That bounds each member's base address to a window.

4. OFFSET-PATTERN ANCHORING (the actual lever).  A member's map symbols sit at
   fixed offsets o1<o2<...<ok from the member base.  Search the window for a
   base B with {B+o1, ..., B+ok} all landing on real rom labels.  With k>=2
   that is a rigid k-point pattern match; a unique hit inside the window, with
   at least one of the hit addresses exclusively owned by the member's own TU,
   is an anchor.  Nothing is emitted at an address the rom does not already
   have a label for -- naming is then a pure rename and cannot move a byte.

TIERS (colon-free -- splat parses `key:value` in these comments as attributes)
  * map-anchor   -- k>=2, unique base in the window, own-TU ownership hit.
  * map-size     -- k==1; base fixed by the member's rom run whose size agrees
                    with the map's member size.  Weaker: verify before use.
  * map-ordinal  -- position forced by link order inside an anchored run.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parent
MAP = ROOT / "baserom" / "pal" / "MAIN.MAP"
YAML = ROOT / "config" / "ico.pal.yaml"
TU_BOUNDS = ROOT / "baserom" / "pal" / "text_tu_boundaries.txt"
OUT_SYMS = ROOT / "config" / "symbol_addrs.pal.data.txt"
OUT_RUNS = ROOT / "baserom" / "pal" / "data_member_runs.txt"
OUT_JSON = ROOT / ".port_cache" / "pal_data_names.json"

SECTIONS = ("data", "rodata", "lit4", "sdata", "sbss", "bss")
VRAM_OFF = 0x100000

# ------------------------------------------------------------------ MAIN.MAP --
OUTSEC_RE = re.compile(r"^\.(\w[\w.]*)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s*$")
INSEC_RE = re.compile(
    r"^ \.(\w[\w.]*)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+)\s*$")
SYM_RE = re.compile(r"^ {10,}0x([0-9a-f]+)\s+(\S+)\s*$")
MEMBER_RE = re.compile(r"^(?:.*/)?([\w.+-]+)\.a\(([\w.+-]+)\.o\)$")


def parse_map():
    """{section: [member dict]} in link order.

    member = {archive, name, start, size, syms:[(addr,name)]}
    """
    out = defaultdict(list)
    cur_sec = None
    cur_mem = None
    for line in MAP.read_text(encoding="utf-8", errors="replace").splitlines():
        m = OUTSEC_RE.match(line)
        if m:
            cur_sec = m.group(1)
            cur_mem = None
            continue
        if line.startswith(".") and not line.startswith(" "):
            # an output section with no size (e.g. ".lit8") or a new one
            cur_sec = line.split()[0].lstrip(".") or None
            cur_mem = None
            continue
        m = INSEC_RE.match(line)
        if m and cur_sec is not None and m.group(1) in (cur_sec, "s" + cur_sec,
                                                        "scommon", "common"):
            mm = MEMBER_RE.match(m.group(4))
            cur_mem = {
                "archive": mm.group(1) if mm else None,
                "name": (mm.group(2) if mm else os.path.basename(m.group(4))),
                "start": int(m.group(2), 16),
                "size": int(m.group(3), 16),
                "syms": [],
            }
            out[cur_sec].append(cur_mem)
            continue
        if line.lstrip().startswith("*fill*"):
            continue
        m = SYM_RE.match(line)
        if m and cur_mem is not None:
            name = m.group(2)
            if name.endswith("=.") or "=" in name or name.startswith("*"):
                continue
            cur_mem["syms"].append((int(m.group(1), 16), name))
    for sec in out:
        for mem in out[sec]:
            mem["syms"].sort()
    return out


# ------------------------------------------------------------------ ROM side --
DLABEL_RE = re.compile(r"^(?:dlabel|jlabel)\s+(\w+)")
SECT_RE = re.compile(r'^\.section\s+\.(\w+)')
ADDR_RE = re.compile(r"^\s*/\* ((?:[0-9A-F]+ ?)+)\*/")


def rom_inventory():
    """{section: sorted [(vma, name, is_jtbl)]} from the splat data blobs.

    Addresses come from the `/* romoff vma [word] */` (or `/* vma */`) comment
    on the label's first line, never from the label spelling -- once this tool
    has renamed a symbol its name no longer carries its VMA, and the inventory
    has to keep working on a renamed tree (idempotence).
    """
    out = defaultdict(list)
    for path in sorted((ROOT / "asm" / "data").rglob("*.s")):
        sect = None
        pend = None
        for line in path.read_text(encoding="utf-8",
                                   errors="replace").splitlines():
            m = SECT_RE.match(line)
            if m:
                sect = m.group(1)
                pend = None
                continue
            m = DLABEL_RE.match(line)
            if m and sect:
                pend = m.group(1)
                continue
            if pend:
                m = ADDR_RE.match(line)
                if m:
                    toks = m.group(1).split()
                    vma = int(toks[1] if len(toks) >= 2 else toks[0], 16)
                    out[sect].append((vma, pend, pend.startswith("jtbl")))
                    pend = None
    for sec in out:
        out[sec].sort()
    return out


def elf_section_ends():
    """{section: (addr, addr+size)} from the PAL ELF's own section headers.

    The yaml data blobs are 0x80-aligned and run past each section's real data
    end; that end is a hard bound -- no member may own an address across it.
    """
    d = (ROOT / "baserom" / "pal" / "baseelf.elf").read_bytes()
    shoff, = struct.unpack_from("<I", d, 0x20)
    shent, shnum, shstrndx = struct.unpack_from("<HHH", d, 0x2E)
    stro, = struct.unpack_from("<I", d, shoff + shstrndx * shent + 0x10)
    out = {}
    for i in range(shnum):
        o = shoff + i * shent
        nm, = struct.unpack_from("<I", d, o)
        name = d[stro + nm:d.index(b"\0", stro + nm)].decode().lstrip(".")
        addr, = struct.unpack_from("<I", d, o + 0x0C)
        size, = struct.unpack_from("<I", d, o + 0x14)
        if name in SECTIONS:
            out[name] = (addr, addr + size)
    return out


def section_bounds():
    """{section: (vma_start, vma_end)} from the yaml subsegment list."""
    rows = []
    pat = re.compile(r"^\s*-\s*[\[{]\s*(?:0x([0-9A-Fa-f]+)|type:\s*(\w+))")
    seg = re.compile(r"-\s*\[0x([0-9A-Fa-f]+),\s*\.?(\w+),")
    dictseg = re.compile(r"type:\s*(\w+),\s*vram:\s*0x([0-9A-Fa-f]+)")
    for line in YAML.read_text(encoding="utf-8").splitlines():
        line = line.split("#")[0]
        m = seg.search(line)
        if m:
            rows.append((int(m.group(1), 16) + VRAM_OFF, m.group(2)))
            continue
        m = dictseg.search(line)
        if m:
            rows.append((int(m.group(2), 16), m.group(1)))
    rows.sort()
    bounds = {}
    for i, (vma, typ) in enumerate(rows):
        if typ not in SECTIONS:
            continue
        end = rows[i + 1][0] if i + 1 < len(rows) else None
        if typ in bounds:
            bounds[typ] = (bounds[typ][0], end if end else bounds[typ][1])
        else:
            bounds[typ] = (vma, end)
    return bounds


IDENT_RE = re.compile(r"[A-Za-z_]\w*")


def consumers(known):
    """symbol name -> set of TU paths that reference it.

    `known` is the set of data-label names currently in the blobs, so the scan
    keeps working after this tool has renamed some of them: matching on a name
    set rather than on the `D_<VMA>` spelling is what makes a re-run
    reproduce the same ownership evidence as the first run.
    """
    refs = defaultdict(set)

    def scan(path, tu):
        try:
            text = path.read_text(encoding="utf-8", errors="replace")
        except OSError:
            return
        for s in set(IDENT_RE.findall(text)) & known:
            refs[s].add(tu)

    for root in ("src", "ios", "isys", "ito", "sound"):
        for p in (ROOT / root).rglob("*.c"):
            scan(p, str(p.relative_to(ROOT))[:-2])
    asm = ROOT / "asm"
    for p in asm.rglob("*.s"):
        rel = p.relative_to(asm)
        parts = rel.parts
        if parts[0] == "data":
            continue
        if parts[0] in ("nonmatchings", "matchings"):
            tu = "/".join(parts[1:-1])
        else:
            tu = str(rel)[:-2]
        if tu:
            scan(p, tu)
    return refs


def tu_paths():
    """member basename -> TU path, from the recovered .text spans."""
    out = {}
    dup = set()
    for line in TU_BOUNDS.read_text(encoding="utf-8").splitlines():
        if line.startswith("#") or not line.strip():
            continue
        parts = line.split()
        path = parts[2]
        if path == "(vendor)" or path.startswith("src/cod/"):
            continue
        base = os.path.basename(path)
        if base in out and out[base] != path:
            dup.add(base)
        out[base] = path
    for d in dup:
        out.pop(d, None)
    return out


# ----------------------------------------------------------------- placement --
NEG = -1 << 40


def segment(labels, owners, members, w_hit=3, w_miss=3):
    """Monotone (link-order) assignment of rom labels to map members.

    Emission score: +w_hit when a label's sole referencing TU is the member's
    own TU, -w_miss when it is some OTHER member's TU in this section, 0 when
    the label is unreferenced or shared.  A Viterbi forward/backward pass then
    yields, per member, the labels that CAN lie in it on some optimal path and
    the labels that MUST.  A single outlier reference cannot move a boundary;
    a stretch of shared labels leaves the boundary ambiguous, which is the
    honest answer rather than a guess.
    """
    L, M = len(labels), len(members)
    tu_of = [m.get("tu") for m in members]
    memtus = {t for t in tu_of if t}
    s = [[0] * M for _ in range(L)]
    for li, a in enumerate(labels):
        o = owners.get(a)
        if o and o in memtus:
            row = s[li]
            for mi in range(M):
                row[mi] = w_hit if tu_of[mi] == o else -w_miss
    F = [[NEG] * M for _ in range(L)]
    F[0][:] = s[0]
    for li in range(1, L):
        run, prev, cur, row = NEG, F[li - 1], F[li], s[li]
        for mi in range(M):
            if prev[mi] > run:
                run = prev[mi]
            cur[mi] = run + row[mi]
    Bk = [[NEG] * M for _ in range(L)]
    Bk[L - 1][:] = s[L - 1]
    for li in range(L - 2, -1, -1):
        run, nxt, cur, row = NEG, Bk[li + 1], Bk[li], s[li]
        for mi in range(M - 1, -1, -1):
            if nxt[mi] > run:
                run = nxt[mi]
            cur[mi] = run + row[mi]
    OPT = max(F[L - 1])
    can_lo, can_hi = [None] * M, [None] * M
    only = [[] for _ in range(M)]
    for li in range(L):
        poss = [mi for mi in range(M)
                if F[li][mi] > NEG // 2 and Bk[li][mi] > NEG // 2
                and F[li][mi] + Bk[li][mi] - s[li][mi] == OPT]
        for mi in poss:
            if can_lo[mi] is None:
                can_lo[mi] = li
            can_hi[mi] = li
        if len(poss) == 1:
            only[poss[0]].append(li)
    out = []
    for mi in range(M):
        must = only[mi]
        out.append((can_lo[mi], can_hi[mi],
                    must[0] if must else None, must[-1] if must else None))
    return out, OPT


MIN_HITS = 2     # a multi-symbol member needs this many offsets to land
MIN_FRAC = 0.40  # ... and this fraction of its named symbols
MIN_SPAN = 0.50  # ... spanning this fraction of their offset range
# A vendor archive member has NO ownership evidence layer: text_tu_boundaries
# lumps the libraries into `(vendor)` spans, so segment() scores it 0
# everywhere and its search window is the whole section.  Only a large rigid
# pattern is self-evidencing there -- a 2-point pattern in a wide window is a
# coin flip, measured: libscedemo.o's argv_copy/argc_copy pair fits two bases
# 0x14 apart at the end of .sbss and the earlier one is the right one.
VENDOR_HITS = 4
VENDOR_FRAC = 0.60


def place_section(sec, members, rom, bounds, refs, tumap, data_end=None):
    """(placements, memberinfo, stats) for one output section.

    placements: [(vma, name, size, tu, tier, member, evidence)]
    memberinfo: [(member, base, run_lo, run_hi, verdict, hits, k)]
    """
    labels = [a for a, _n, _j in rom]
    lset = set(labels)
    sec_lo, sec_hi = bounds
    hard_end = data_end or sec_hi
    nxt = {a: (labels[i + 1] if i + 1 < len(labels) else hard_end)
           for i, a in enumerate(labels)}
    owners = {}
    for a, n, _j in rom:
        o = refs.get(n, set())
        owners[a] = next(iter(o)) if len(o) == 1 else None
    for m in members:
        m["tu"] = tumap.get(m["name"]) if m["archive"] == "ico2000" else None

    res, _opt = segment(labels, owners, members)
    M = len(members)
    placements, info = [], []
    stats = defaultdict(int)
    prev_end = sec_lo
    for mi, mem in enumerate(members):
        cl, ch, ml, mh = res[mi]
        pb = sec_lo
        for j in range(mi - 1, -1, -1):
            if res[j][3] is not None:
                pb = labels[res[j][3]] + 1
                break
        pb = max(pb, prev_end)
        rb = hard_end                     # no placement may reach this
        for j in range(mi + 1, M):
            if res[j][2] is not None:
                rb = labels[res[j][2]]
                break
        run_hi = hard_end                 # first addr the next member can own
        for j in range(mi + 1, M):
            if res[j][0] is not None:
                run_hi = labels[res[j][0]]
                break
        run_lo = labels[cl] if cl is not None else None
        k = len(mem["syms"])
        if k == 0:
            info.append((mem, None, run_lo, run_hi, "no-map-syms", 0, 0))
            continue
        if ml is not None:
            b_cap = labels[ml]
        elif ch is not None:
            b_cap = labels[ch]
        else:
            b_cap = rb
        if b_cap < pb:
            b_cap = pb
        offs = [a - mem["start"] for a, _ in mem["syms"]]
        o0 = min(offs)
        win = [a for a in labels if pb + o0 <= a < rb]
        cnt = defaultdict(list)
        for a in win:
            for o in offs:
                b = a - o
                if pb <= b <= b_cap:
                    cnt[b].append(o)
        base = tier = None
        hits = []
        if cnt:
            top = max(len(v) for v in cnt.values())
            best = [(b, v) for b, v in cnt.items() if len(v) == top]
            def corrob(b, h):
                # the base is corroborated when the member's OWN territory --
                # a label the segmentation assigns to it and to nothing else --
                # falls inside the span this base implies, or when one of the
                # landed offsets is itself exclusively this TU's.
                if mem["tu"] is None:
                    return True
                if ml is not None and b <= labels[ml] <= b + max(offs):
                    return True
                return any(owners.get(b + o) == mem["tu"] for o in h)

            own = [x for x in best if corrob(x[0], x[1])]
            need_h, need_f = ((MIN_HITS, MIN_FRAC) if mem["tu"]
                              else (VENDOR_HITS, VENDOR_FRAC))
            if len(own) == 1 and top >= need_h and top >= need_f * k:
                b, h = own[0]
                full = (max(offs) - min(offs)) or 1
                if (max(h) - min(h)) >= MIN_SPAN * full:
                    base, tier, hits = b, "map-anchor", sorted(h)
            if base is None and k == 1:
                fit = [(b, v) for b, v in cnt.items()
                       if run_hi - b == mem["size"]]
                if len(fit) == 1:
                    base, tier, hits = fit[0][0], "map-size", fit[0][1]
                elif pb == b_cap and pb in cnt:
                    base, tier, hits = pb, "map-ordinal", cnt[pb]
        if base is None and mi == 0 and sec_lo in cnt:
            # `*(.sect)` places the first input section at the output section
            # start: a link fact, not an inference.  Position forced by link
            # order alone is exactly the map-ordinal tier.
            base, tier, hits = sec_lo, "map-ordinal", cnt[sec_lo]
        if base is None:
            stats["unplaced-ambiguous" if cnt else "unplaced-no-base"] += k
            info.append((mem, None, run_lo, run_hi,
                         "ambiguous" if cnt else "no-base", 0, k))
            continue
        stats[tier] += len(hits)
        stats["unplaced-unlabelled"] += k - len(hits)
        info.append((mem, base, base, run_hi, tier, len(hits), k))
        prev_end = base + max(hits) + 1
        ev = f"{len(hits)}of{k}"
        for (a, name), o in zip(mem["syms"], offs):
            if o not in hits:
                continue
            v = base + o
            placements.append((v, name, nxt[v] - v, mem["tu"] or "(vendor)",
                               tier, mem["name"], ev))
    return placements, info, stats


# --------------------------------------------------------------------- emit --
BANNER = "// ==== BEGIN GENERATED — tools/gen_pal_data_symbols.py ===="
HEADER = """\
// Visit https://github.com/ethteck/splat/wiki/Adding-Symbols for documentation.
// PAL target (SCES_507.60) — DATA symbols.  Regenerated by
// tools/gen_pal_data_symbols.py; listed alongside config/symbol_addrs.pal.txt
// in config/ico.pal.yaml's symbol_addrs_path.  The FUNCTION generator
// (tools/gen_pal_symbol_addrs.py) never reads or writes this file, and this
// one never touches that one.
//
// PROVENANCE — read before trusting a name.
//
//   Names come from baserom/pal/MAIN.MAP, the GNU ld link map shipped on the
//   retail SCES-50760 disc.  It is a DIFFERENT LINK from the shipped ELF
//   (.text 0x16a29c vs 0x189bc4, .data 0x2db338 vs 0x2be680, .rodata 0xde418
//   vs 0xeb780), so NO ADDRESS BELOW IS COPIED FROM IT.  The map supplies, per
//   ico2000.a member, which objects it defines and their offsets inside the
//   member; every VMA below is a PAL rom address, recovered by aligning the
//   member to the rom's own label stream (see the tool's docstring).
//
//   A name is emitted only where the rom ALREADY has a label at the derived
//   address, so this file renames rom-native symbols and can never move a
//   byte.  Objects the rom never forms an address for stay unnamed.
//
// TIERS
//   map-anchor  — >=2 of the member's named offsets land on rom labels at one
//                 uniquely-best base, corroborated by the member's own
//                 reference territory.  Strong.
//   map-size    — single-symbol member; base fixed by its rom run size
//                 agreeing with the map's member size.  Verify before use.
//   map-ordinal — base forced by link order alone (the window held exactly one
//                 position).  Weakest; verify before use.
//
// splat 0.40 rejects `type:data` (its type list is jtbl/label/func plus the
// scalar spellings; anything else must start with a capital letter), so these
// entries carry no `type:` at all -- splat keeps its inferred rendering and
// the entry is a pure rename.  `size:` is the rom-native delta to the next
// label, i.e. what splat computes for the symbol anyway.
"""


def emit(placed, path):
    lines = [HEADER, BANNER, ""]
    for vma, name, size, tu, tier, mem, ev in sorted(placed):
        # splat 0.40 has no `data` symbol type -- its type list is
        # jtbl/label/func plus the scalar spellings, and anything else must
        # start with a capital letter.  A data object with no `type:` is
        # exactly what we want: splat keeps its own inferred rendering, so the
        # entry only renames.  `size:` is the rom-native delta to the next
        # label, which is what splat would compute anyway.
        lines.append(f"{name} = 0x{vma:08X}; // size:0x{size:X}"
                     f"  // {tu}  // {tier} {ev} from {mem}.o")
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


IDENT_ROOTS = ("src", "ios", "isys", "ito", "sound", "include")


def rename_sources(mapping, dry=False):
    """Identifier-boundary rename of the old D_/jtbl_ names in the C tree."""
    if not mapping:
        return 0, 0
    pat = re.compile(r"\b(" + "|".join(map(re.escape, mapping)) + r")\b")
    nfiles = nsubs = 0
    for root in IDENT_ROOTS:
        d = ROOT / root
        if not d.is_dir():
            continue
        for p in list(d.rglob("*.c")) + list(d.rglob("*.h")):
            txt = p.read_text(encoding="utf-8", errors="surrogateescape")
            new, n = pat.subn(lambda m: mapping[m.group(1)], txt)
            if n:
                nfiles += 1
                nsubs += n
                if not dry:
                    p.write_text(new, encoding="utf-8",
                                 errors="surrogateescape")
    return nfiles, nsubs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--report", action="store_true", help="write nothing")
    ap.add_argument("--rename", action="store_true",
                    help="also rewrite D_ references in the C tree")
    args = ap.parse_args()

    taken = set()
    for f in ("symbol_addrs.pal.txt", "undefined_syms_auto.pal.txt",
              "undefined_funcs_auto.pal.txt", "undefined_funcs_extra.pal.txt"):
        fp = ROOT / "config" / f
        if fp.exists():
            for line in fp.read_text(encoding="utf-8").splitlines():
                m = re.match(r"\s*(\w+)\s*=", line)
                if m:
                    taken.add(m.group(1))

    mp = parse_map()
    rom = rom_inventory()
    bounds = section_bounds()
    refs = consumers({n for sec in rom for _a, n, _j in rom[sec]})
    tumap = tu_paths()
    ends = elf_section_ends()

    all_placed = []
    runs_txt = [
        "# PAL (SCES-50760) per-(member, section) DATA runs — link order.",
        "# Generated by tools/gen_pal_data_symbols.py — untracked.",
        "# rom_run is what the label-stream segmentation forced; map_size is",
        "# baserom/pal/MAIN.MAP's size for that member in ITS (different) link.",
        "# Columns: section member tu rom_lo rom_hi rom_size map_size agree"
        " verdict hits/named",
    ]
    report = []
    for sec in SECTIONS:
        if sec not in bounds or sec not in mp:
            continue
        placed, info, stats = place_section(
            sec, mp[sec], rom.get(sec, []), bounds[sec], refs, tumap,
            ends.get(sec, (0, 0))[1] or None)
        clash = [p for p in placed if p[1] in taken]
        placed = [p for p in placed if p[1] not in taken]
        if clash:
            stats["unplaced-name-collision"] = len(clash)
            stats["collides"] = ",".join(sorted(p[1] for p in clash))
        all_placed += placed
        # second pass: run ends, now that bases are known
        based = [(i, r[1]) for i, r in enumerate(info) if r[1] is not None]
        end_of = {}
        for k, (i, b) in enumerate(based):
            end_of[i] = based[k + 1][1] if k + 1 < len(based) else bounds[sec][1]
        agree = tot = 0
        for i, (mem, base, rlo, rhi, verdict, hits, k) in enumerate(info):
            if mem["archive"] != "ico2000":
                continue
            lo = base if base is not None else rlo
            hi = end_of.get(i, rhi)
            ok = "-"
            if lo is not None and hi is not None and hi > lo:
                tot += 1
                ok = "yes" if (hi - lo) == mem["size"] else "no"
                agree += ok == "yes"
            runs_txt.append(
                f"{sec} {mem['name']} {mem['tu'] or '-'} "
                f"{lo and hex(lo) or '-'} {hi and hex(hi) or '-'} "
                f"{(hi - lo) if (lo and hi and hi > lo) else 0:#x} "
                f"{mem['size']:#x} {ok} {verdict} {hits}/{k}")
        nmap = sum(len(m["syms"]) for m in mp[sec])
        report.append((sec, nmap, len(placed), dict(stats), agree, tot))

    if not args.report:
        emit(all_placed, OUT_SYMS)
        OUT_RUNS.write_text("\n".join(runs_txt) + "\n", encoding="utf-8")
        romname = {}
        for sec in rom:
            for a, n, _j in rom[sec]:
                romname[a] = n
        mapping = {}
        meta = {}
        for vma, name, size, tu, tier, mem, ev in all_placed:
            # Key on BOTH the splat auto-name for the VMA and whatever the
            # blob currently calls the label: a re-run sees the already-renamed
            # blob, but the C tree may still hold the `D_<VMA>` spelling.
            olds = {f"D_{vma:08X}", f"jtbl_{vma:08X}"}
            cur = romname.get(vma)
            if cur:
                olds.add(cur)
            olds.discard(name)
            for old in olds:
                mapping[old] = name
            if cur:
                meta[cur] = {"new": name, "vma": f"0x{vma:08X}",
                             "size": f"0x{size:X}", "tu": tu, "tier": tier,
                             "member": f"{mem}.o", "evidence": ev}
        OUT_JSON.parent.mkdir(exist_ok=True)
        OUT_JSON.write_text(json.dumps(meta, indent=1, sort_keys=True) + "\n",
                            encoding="utf-8")
        if args.rename:
            nf, ns = rename_sources(mapping)
            print(f"renamed {ns} references in {nf} files")

    print(f"{'sect':8} {'mapsyms':>7} {'placed':>6}  member-size agreement  "
          f"breakdown")
    for sec, nmap, npl, stats, agree, tot in report:
        pct = f"{agree}/{tot}" + (f" ({100*agree//tot}%)" if tot else "")
        print(f"{sec:8} {nmap:7} {npl:6}  {pct:>21}  {stats}")
    print(f"TOTAL placed {len(all_placed)} of "
          f"{sum(r[1] for r in report)} map data symbols")
    return 0


if __name__ == "__main__":
    sys.exit(main())
