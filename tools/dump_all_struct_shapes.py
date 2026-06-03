#!/usr/bin/env python3
"""dump_all_struct_shapes.py — recover struct SHAPES for the WHOLE binary.

A stripped target stores no struct layouts; they're only implicit in how the
code accesses memory. This tool mines every function `.s` (matched +
nonmatching) and, via a tiny per-function register-value abstraction,
attributes each load/store to the data symbol (or argument pointer) it
targets — recovering, for every struct, the (offset, width, signedness,
indexing stride) tuples that define its field layout.

It is the corpus-wide successor to `dump_struct_accesses.py` (which was
single-symbol and scanned a now-stale `asm/cod/<vma>.s` path). No types are
INFERRED beyond width/sign from the load mnemonic — the developer reads the
catalog and writes the C struct.

Outputs:
  decomp/struct_shapes.json  — machine-readable: per global symbol + per
                               (func,argN) pointer param → field table.
  decomp/struct_shapes.md    — readable catalog, most-referenced first, with a
                               suggested designated-initializer / struct typedef.

Usage:
  tools/dump_all_struct_shapes.py            # full corpus -> both outputs
  tools/dump_all_struct_shapes.py D_00565060 # print one symbol's shape
  tools/dump_all_struct_shapes.py --args     # also dump pointer-param shapes
"""
from __future__ import annotations

import json
import os
import re
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
# Version-aware asm layout: the aug6 prototype branch splits under
# asm/aug6/{matchings,nonmatchings}; the retail branch uses asm/{...}.
# Pick whichever exists so this runs unmodified on either target.
_VERSION = os.environ.get("VERSION", "aug6")
_AUG6_DIRS = [ROOT / "asm" / _VERSION / "matchings", ROOT / "asm" / _VERSION / "nonmatchings"]
if all(d.exists() for d in _AUG6_DIRS):
    ASM_DIRS = _AUG6_DIRS
else:
    ASM_DIRS = [ROOT / "asm" / "matchings", ROOT / "asm" / "nonmatchings"]
# NOTE: decomp/tu_map.json on aug6 is the STALE retail map (generic func_XXXX
# names, no MAIN.MAP symbols) — do NOT use it. The aug6 .s files already encode
# their owning TU in the path (asm/<ver>/nonmatchings/<tu>/<func>.s), so TU
# attribution is derived from the path instead (see owning_tu_from_path).
TU_MAP = ROOT / "decomp" / "tu_map.json"

# one disasm line: `/* off vma word */  mnem  ops`
LINE = re.compile(r"\*/\s+(\S+)\s*(.*)$")
HI = re.compile(r"%hi\(([A-Za-z_]\w*)\)")
LO = re.compile(r"%lo\(([A-Za-z_]\w*)\)")
# load/store: `$d, OFF($b)` (OFF hex/dec, optional sign)
MEM = re.compile(r"\$(\d+),\s*(-?(?:0x)?[0-9A-Fa-f]+)\(\$(\d+)\)")
GPREL = re.compile(r"\$(\d+),\s*\(([A-Za-z_]\w*)\)")          # lw $d,(SYM) gp_rel
IMM3 = re.compile(r"\$(\d+),\s*\$(\d+),\s*(-?(?:0x)?[0-9A-Fa-f]+)\b")  # op $d,$s,imm
REG3 = re.compile(r"\$(\d+),\s*\$(\d+),\s*\$(\d+)")            # op $d,$s,$t
REG2 = re.compile(r"\$(\d+),\s*\$(\d+)\b")

LOADS = {  # mnemonic -> (width, signed?)
    "lb": (1, True), "lbu": (1, False), "lh": (2, True), "lhu": (2, False),
    "lw": (4, False), "lwu": (4, False), "ld": (8, False), "lwc1": (4, None),
    "ldc1": (8, None), "lq": (16, False),
}
STORES = {
    "sb": (1, True), "sh": (2, True), "sw": (4, False), "sd": (8, False),
    "swc1": (4, None), "sdc1": (8, None), "sq": (16, False),
}
CALLER_SAVED = set([1, 2, 3] + list(range(4, 16)) + [24, 25])  # at,v0-v1,a0-t7,t8-t9


def num(tok: str) -> int:
    tok = tok.strip()
    neg = tok.startswith("-")
    if neg:
        tok = tok[1:]
    v = int(tok, 16) if tok.lower().startswith("0x") else int(tok, 16 if re.fullmatch(r"[0-9A-Fa-f]+", tok) and not tok.isdigit() else 10)
    # disasm offsets are hex without 0x sometimes; be lenient: try hex then dec
    return -v if neg else v


def _int(tok: str) -> int:
    tok = tok.strip()
    sign = -1 if tok.startswith("-") else 1
    tok = tok.lstrip("-")
    try:
        return sign * (int(tok, 16) if tok.lower().startswith("0x") else int(tok))
    except ValueError:
        return sign * int(tok, 16)


LABEL = re.compile(r"^\s*(?:\.L\w+|[gj]label\s+\S+|\w+):")


def parse_func(text: str):
    """Yield (mnem, ops) per instruction, and ('.LABEL', '') at block
    boundaries so the caller can reset register state (address
    materialization + use is block-local; carrying a base across a label
    causes stale far-offset mis-attributions)."""
    for raw in text.splitlines():
        m = LINE.search(raw)
        if m:
            yield m.group(1), m.group(2).strip()
        elif LABEL.match(raw) and "endlabel" not in raw and ".size" not in raw:
            yield ".LABEL", ""


def analyze_function(text: str, accesses, arg_accesses, func_name: str):
    """Per-function abstract interpretation; append to accesses/arg_accesses."""
    # reg value: ('hi',SYM) ('base',SYM) ('elem',SYM,stride|None)
    #            ('off',SYM,stride|None,delta) ('const',K) ('scaled',stride)
    #            ('arg',n)
    reg = {}
    # seed argument pointers a0-a3 = regs 4..7
    for i, r in enumerate((4, 5, 6, 7)):
        reg[r] = ("arg", i)

    def base_of(v):
        """Return (SYM, stride, delta) if v points into a symbol, else None."""
        if v is None:
            return None
        if v[0] == "base":
            return (v[1], 0, 0)
        if v[0] == "elem":
            return (v[1], v[2], 0)
        if v[0] == "off":
            return (v[1], v[2], v[3])
        return None

    for mnem, ops in parse_func(text):
        if mnem == ".LABEL":
            reg.clear()        # block boundary: drop all materialized bases
            continue
        base = mnem.split(".")[0]

        # ---- address materialization ----
        if base == "lui":
            m = HI.search(ops)
            mm = REG2.match(ops) or re.match(r"\$(\d+),", ops)
            d = int(re.match(r"\$(\d+)", ops).group(1)) if re.match(r"\$(\d+)", ops) else None
            if d is not None:
                reg[d] = ("hi", m.group(1)) if m else None
            continue
        if base in ("addiu", "daddiu"):
            md = re.match(r"\$(\d+),\s*\$(\d+),\s*(.*)", ops)
            if md:
                d, s, rest = int(md.group(1)), int(md.group(2)), md.group(3)
                lo = LO.search(rest)
                if lo and reg.get(s) == ("hi", lo.group(1)):
                    reg[d] = ("base", lo.group(1))
                elif lo:
                    reg[d] = None
                else:
                    # $d = $s + const
                    try:
                        k = _int(rest.split()[0].rstrip(","))
                    except Exception:
                        reg[d] = None
                        continue
                    sv = reg.get(s)
                    if s == 0:
                        reg[d] = ("const", k)
                    elif sv and sv[0] in ("base", "elem", "off"):
                        b = base_of(sv)
                        reg[d] = ("off", b[0], b[1], b[2] + k)
                    else:
                        reg[d] = None
            continue
        if base in ("ori", "li"):
            md = re.match(r"\$(\d+),\s*\$?(\d+|zero),\s*(.*)", ops) or re.match(r"\$(\d+),\s*(.*)", ops)
            # best-effort const; not critical
            continue

        # ---- index scaling ----
        if base in ("sll", "dsll", "dsll32"):
            md = re.match(r"\$(\d+),\s*\$(\d+),\s*(.*)", ops)
            if md:
                d = int(md.group(1))
                try:
                    sh = _int(md.group(3).split()[0].rstrip(","))
                except Exception:
                    sh = None
                if base == "dsll32" and sh is not None:
                    sh += 32
                reg[d] = ("scaled", 1 << sh) if sh is not None and sh < 24 else None
            continue
        if base in ("mult", "multu", "dmult", "dmultu"):
            md = REG3.match(ops)
            if md:
                d, s, t = int(md.group(1)), int(md.group(2)), int(md.group(3))
                kt, ks = reg.get(t), reg.get(s)
                if kt and kt[0] == "const":
                    reg[d] = ("scaled", kt[1])
                elif ks and ks[0] == "const":
                    reg[d] = ("scaled", ks[1])
                else:
                    reg[d] = None
            continue

        # ---- base + index ----
        if base in ("addu", "daddu", "add", "dadd"):
            md = REG3.match(ops)
            if md:
                d, s, t = int(md.group(1)), int(md.group(2)), int(md.group(3))
                vs, vt = reg.get(s), reg.get(t)
                # copy: daddu $d,$s,$0
                if t == 0:
                    reg[d] = vs
                    continue
                if s == 0:
                    reg[d] = vt
                    continue
                # base + scaled  -> elem
                def combine(a, b):
                    ba = base_of(a)
                    if ba and b and b[0] == "scaled":
                        return ("elem", ba[0], b[2] if False else b[1]) if False else ("elem", ba[0], b[1])
                    if ba and b and b[0] == "const":
                        return ("off", ba[0], ba[1], ba[2] + b[1])
                    if ba and (b is None or b[0] not in ("base", "elem", "off")):
                        return ("elem", ba[0], ba[1] if a[0] != "base" else None)
                    return None
                reg[d] = combine(vs, vt) or combine(vt, vs)
            continue

        # ---- register copies ----
        if base in ("move", "or", "nor") and base != "ori":
            md = REG3.match(ops)
            if md and base == "or":
                d, s, t = int(md.group(1)), int(md.group(2)), int(md.group(3))
                if t == 0:
                    reg[d] = reg.get(s)
                elif s == 0:
                    reg[d] = reg.get(t)
                else:
                    reg[d] = None
            continue

        # ---- memory accesses ----
        if base in LOADS or base in STORES:
            width, signed = (LOADS.get(base) or STORES.get(base))
            mm = MEM.search(ops)
            if mm:
                d, off, b = int(mm.group(1)), _int(mm.group(2)), int(mm.group(3))
                tgt = base_of(reg.get(b))
                if tgt:
                    sym, stride, delta = tgt
                    rec = accesses[sym]
                    rec["stride"].add(stride if stride else 0)
                    rec["fields"][(delta + off, width, signed)] += 1
                    rec["insns"][(delta + off)].add(base)
                elif reg.get(b) and reg[b][0] == "arg":
                    arg_accesses[(func_name, reg[b][1])]["fields"][(off, width, signed)] += 1
                # destination of a load is now an unknown value
                if base in LOADS:
                    reg[d] = None
                continue
            gm = GPREL.search(ops)
            if gm:
                d, sym = int(gm.group(1)), gm.group(2)
                rec = accesses[sym]
                rec["stride"].add(0)
                rec["fields"][(0, width, signed)] += 1
                rec["insns"][0].add(base)
                rec["gp_rel"] = True
                if base in LOADS:
                    reg[d] = None
            continue

        # ---- calls clobber caller-saved ----
        if base in ("jal", "jalr", "bal", "syscall"):
            for r in CALLER_SAVED:
                reg.pop(r, None)
            continue

        # ---- any other writer: invalidate its dest reg ----
        md = re.match(r"\$(\d+),", ops)
        if md and base not in ("beq", "bne", "blez", "bgtz", "bltz", "bgez",
                               "beql", "bnel", "sw", "sb", "sh", "sd", "swc1",
                               "sdc1", "sq", "j", "jr", "b"):
            reg[int(md.group(1))] = None


def tu_from_path(p: Path) -> str | None:
    """Derive the owning TU from an aug6 .s path:
    asm/<ver>/{matchings,nonmatchings}/<tu...>/<func>.s -> '<tu...>'."""
    parts = p.parts
    for anchor in ("matchings", "nonmatchings"):
        if anchor in parts:
            i = parts.index(anchor)
            tu = parts[i + 1:-1]  # drop the anchor and the <func>.s leaf
            return "/".join(tu) if tu else None
    return None


def owning_tus(sym_tu_counts):
    """Per-symbol owning-TU hint = the TU that references it most.
    Built from the .s paths (sym_tu_counts), NOT the stale retail tu_map.json."""
    out = {}
    for sym, counts in sym_tu_counts.items():
        if counts:
            out[sym] = max(counts.items(), key=lambda kv: kv[1])[0]
    return out


def width_type(width, signed):
    if signed is None:
        return {4: "float", 8: "double"}.get(width, f"f{width*8}")
    base = {1: "char", 2: "short", 4: "int", 8: "long long", 16: "u128"}.get(width, f"i{width*8}")
    if not signed and width in (1, 2):
        return "unsigned " + base
    if not signed and width == 4:
        return "unsigned int"
    return base


def suggest_struct(sym, rec):
    strides = sorted(s for s in rec["stride"] if s)
    stride = strides[-1] if strides else None
    fields = sorted(rec["fields"].items())
    lines = [f"typedef struct {{"]
    seen = {}
    for (off, width, signed), cnt in fields:
        # keep the widest access seen at each offset
        if off in seen and seen[off][0] >= width:
            continue
        seen[off] = (width, signed)
    for off in sorted(seen):
        width, signed = seen[off]
        ins = "/".join(sorted(rec["insns"].get(off, [])))
        lines.append(f"    {width_type(width, signed):<14} f_{off:X};"
                     f"  /* 0x{off:X}  {ins} */")
    size = f" /* 0x{stride:X} bytes */" if stride else ""
    name = f"S_{sym[2:]}" if sym.startswith("D_") else f"S_{sym}"
    lines.append(f"}} {name};{size}")
    if stride:
        lines.append(f"{name} {sym}[N];")
    return "\n".join(lines)


def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    do_args = "--args" in sys.argv[1:]
    accesses = defaultdict(lambda: {"stride": set(), "fields": defaultdict(int),
                                    "insns": defaultdict(set), "gp_rel": False})
    arg_accesses = defaultdict(lambda: {"fields": defaultdict(int)})

    files = []
    for d in ASM_DIRS:
        # aug6 .s files are named by their MAIN.MAP dev name (backStageSave.s),
        # not just func_<vma>.s — glob ALL .s, not only func_*.s.
        files += list(d.rglob("*.s"))
    sys.stderr.write(f"scanning {len(files)} function .s files...\n")
    sym_tu_counts = defaultdict(lambda: defaultdict(int))  # sym -> {tu: refcount}
    symref = re.compile(r"%(?:hi|lo|gp_rel)\(([A-Za-z_]\w*)\)|\(([A-Za-z_]\w*)\)\s*/\*\s*gp_rel")
    for i, f in enumerate(files):
        if i % 1000 == 0:
            sys.stderr.write(f"  {i}/{len(files)}\n")
        try:
            text = f.read_text(errors="replace")
            analyze_function(text, accesses, arg_accesses, f.stem)
            tu = tu_from_path(f)
            if tu:
                for m in symref.finditer(text):
                    sym_tu_counts[m.group(1) or m.group(2)][tu] += 1
        except Exception as e:
            sys.stderr.write(f"  WARN {f.name}: {e}\n")

    # single-symbol query mode
    if args:
        for sym in args:
            rec = accesses.get(sym)
            if not rec:
                print(f"{sym}: no field accesses found")
                continue
            print(suggest_struct(sym, rec))
            print(f"  ({sum(rec['fields'].values())} accesses, "
                  f"strides={sorted(rec['stride'])})")
        return 0

    tus = owning_tus(sym_tu_counts)
    # rank globals by total access count
    ranked = sorted(accesses.items(), key=lambda kv: -sum(kv[1]["fields"].values()))
    out_json = {"globals": {}, "arg_params": {}}
    md = ["# Recovered struct shapes (binary-wide)\n",
          "Generated by `tools/dump_all_struct_shapes.py` from access patterns",
          "in the disassembly. Field widths/signs are from load mnemonics;",
          "no types are inferred beyond that — read the table and type the C.\n",
          f"**{len(ranked)} distinct data symbols** carry field accesses.\n"]
    for sym, rec in ranked:
        nfields = len({off for (off, _w, _s) in rec["fields"]})
        total = sum(rec["fields"].values())
        strides = sorted(s for s in rec["stride"] if s)
        out_json["globals"][sym] = {
            "tu": tus.get(sym), "stride": strides[-1] if strides else None,
            "accesses": total, "n_fields": nfields, "gp_rel": rec["gp_rel"],
            "fields": [{"off": off, "width": w, "signed": s, "count": c}
                       for (off, w, s), c in sorted(rec["fields"].items())],
        }
        if nfields >= 2 or (strides):
            md.append(f"\n## {sym}  ({total} accesses, "
                      f"{nfields} fields{', stride 0x%X' % strides[-1] if strides else ''})"
                      + (f"  — {tus[sym]}" if tus.get(sym) else ""))
            md.append("```c")
            md.append(suggest_struct(sym, rec))
            md.append("```")

    (ROOT / "decomp" / "struct_shapes.json").write_text(json.dumps(out_json, indent=1))

    if do_args:
        for (fn, argn), rec in sorted(arg_accesses.items(),
                                      key=lambda kv: -len(kv[1]["fields"])):
            if len(rec["fields"]) < 2:
                continue
            out_json["arg_params"][f"{fn}:a{argn}"] = [
                {"off": off, "width": w, "signed": s, "count": c}
                for (off, w, s), c in sorted(rec["fields"].items())]
        (ROOT / "decomp" / "struct_shapes.json").write_text(json.dumps(out_json, indent=1))

    (ROOT / "decomp" / "struct_shapes.md").write_text("\n".join(md) + "\n")
    sys.stderr.write(f"wrote decomp/struct_shapes.{{json,md}} "
                     f"({len(ranked)} symbols)\n")
    return 0


if __name__ == "__main__":
    sys.exit(main())
