#!/usr/bin/env python3
"""dump_struct_accesses.py — survey load/store access patterns for one
rodata/data symbol, so a developer can type a designated-initializer
struct that matches the consumer side.

Usage: tools/dump_struct_accesses.py D_<VMA> [D_<VMA> ...]

For each requested symbol, this tool:
  1. Looks up the owning TU via `decomp/data_tu_map.json`.
  2. Finds every function assigned to that TU via `decomp/tu_map.json`.
  3. Scans those functions' `asm/cod/<vma>.s` files for instructions
     that reference the symbol (`%hi(D_X)` / `%lo(D_X)` / `%lo(D_X+OFF)`
     / `%gp_rel(D_X)`) and the loads/stores that follow.
  4. Aggregates the access pattern: which (offset, width, signedness)
     tuples occur, how many times, and (when detectable) what the
     outer indexing stride looks like.

Output is a table you read to type the symbol as a designated-init
struct array. No types are inferred — the developer reads the table
and writes the C.

Example:
    $ tools/dump_struct_accesses.py D_00554D60
    D_00554D60 in src/Light  (TU's text range: 0x101000 - 0x1023C0)
    Scanned 12 functions, found 47 references.

    offset  width  signed  count  insn(s)
    ------  -----  ------  -----  -------
    0x00       4   u       18     lw
    0x04       4   u       18     lw
    0x08       4   u       11     lw
    0x0C       4   f       11     lwc1
    stride: 0x10 (detected via outer addiu pattern, 4 sites)

    Suggested shape:
        typedef struct {
            void *a;        // 0x00
            void *b;        // 0x04
            int   c;        // 0x08
            float d;        // 0x0C
        } D_X_Entry;
        D_X_Entry D_00554D60[N] = { ... };
"""
from __future__ import annotations

import json
import re
import sys
from collections import Counter, defaultdict
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
DATA_TU_MAP = REPO / "decomp" / "data_tu_map.json"
TU_MAP = REPO / "decomp" / "tu_map.json"
ASM_COD = REPO / "asm" / "cod"

# Load instructions and their widths/signedness on R5900.
LOAD_INSNS = {
    "lb":   (1, "s", "i"),  "lbu":  (1, "u", "i"),
    "lh":   (2, "s", "i"),  "lhu":  (2, "u", "i"),
    "lw":   (4, "s", "i"),  "lwu":  (4, "u", "i"),
    "ld":   (8, "s", "i"),  "ldl":  (8, "s", "i"),  "ldr": (8, "s", "i"),
    "lq":   (16, "s", "i"),
    "lwc1": (4, "s", "f"),
    "lwl":  (4, "s", "i"),  "lwr":  (4, "s", "i"),
}
STORE_INSNS = {
    "sb": (1, "i"), "sh": (2, "i"), "sw": (4, "i"), "sd": (8, "i"),
    "sq": (16, "i"), "swc1": (4, "f"),
    "sdl": (8, "i"), "sdr": (8, "i"), "swl": (4, "i"), "swr": (4, "i"),
}

# Match `%hi(D_X)` / `%lo(D_X)` / `%lo(D_X+0xN)` / `%gp_rel(D_X)`.
SYM_REF_RE = re.compile(
    r'%(hi|lo|gp_rel)\((D_[0-9A-Fa-f]{8})(?:\s*\+\s*(0x[0-9A-Fa-f]+))?\)'
)
# Strip the comment column splat emits: `/* 1234 5678 ABCD */ <insn> ...`.
COMMENT_RE = re.compile(r'/\*[^*]*\*/')
# Capture the mnemonic and operand list of an instruction line.
INSN_RE = re.compile(r'^\s*([a-z][a-z0-9.]*)\s+(.*?)\s*$')


def _load_data_tu_map() -> dict[str, str]:
    if not DATA_TU_MAP.exists():
        sys.exit(f"dump_struct_accesses: missing {DATA_TU_MAP}; "
                 "run tools/build_data_tu_map.py first.")
    raw = json.loads(DATA_TU_MAP.read_text())
    return {sym: rec["tu"] for sym, rec in raw.items()}


def _load_tu_funcs() -> dict[str, list[int]]:
    """Return {tu: [func_vma, ...]}. tu names are stored with `.c`
    suffix in tu_map.json but without in data_tu_map.json — we index
    by the dotless form so lookups from either source work."""
    if not TU_MAP.exists():
        sys.exit(f"dump_struct_accesses: missing {TU_MAP}; "
                 "run tools/identify_tus.py first.")
    raw = json.loads(TU_MAP.read_text())
    out: dict[str, list[int]] = defaultdict(list)
    for item in raw:
        tu = item.get("tu")
        if tu:
            key = tu[:-2] if tu.endswith(".c") else tu
            out[key].append(item["vram"])
    return out


def _asm_path_for_func(vma: int) -> Path | None:
    """Find the asm file containing func_<vma>. Splat emits one .s
    per subsegment, so the right file may have a stem ≤ vma."""
    candidates = sorted(ASM_COD.glob("*.s"))
    target = vma - 0x100000  # cod segment starts at 0x100000 file offset
    best: Path | None = None
    best_stem = -1
    for p in candidates:
        try:
            stem = int(p.stem, 16)
        except ValueError:
            continue
        if stem <= target and stem > best_stem:
            best_stem = stem
            best = p
    return best


def _scan_function(asm_path: Path, func_vma: int, sym: str
                   ) -> tuple[Counter, Counter]:
    """Walk the func body, accumulate:
        offsets[(offset, width, family)] += 1
        strides[stride] += 1

    `family` is 'i' (integer load/store) or 'f' (FPU). Stride detection
    looks for `addiu $X, $X, IMM` patterns inside loops where $X
    previously held the symbol address.
    """
    offsets: Counter = Counter()
    strides: Counter = Counter()
    if not asm_path.exists():
        return offsets, strides

    text = asm_path.read_text()
    # Find the function's body — from `glabel func_<vma>` to the next
    # `glabel`/`endlabel`/`.size`.
    fn_re = re.compile(rf'^glabel\s+func_{func_vma:08X}\b', re.MULTILINE)
    m = fn_re.search(text)
    if not m:
        return offsets, strides
    body_start = m.end()
    next_lbl = re.search(r'^(glabel|endlabel|\.size)\b', text[body_start:],
                         re.MULTILINE)
    body_end = body_start + (next_lbl.start() if next_lbl else len(text) - body_start)
    body = text[body_start:body_end]

    # Tracks which registers currently hold the symbol address.
    # Reset on register clobber, function call, branch.
    base_regs: dict[str, int] = {}  # reg -> offset-from-symbol
    last_loop_addiu: list[int] = []

    for raw_line in body.splitlines():
        line = COMMENT_RE.sub('', raw_line).strip()
        if not line or line.startswith('/*') or line.startswith('.'):
            continue
        insn_m = INSN_RE.match(line)
        if not insn_m:
            continue
        mnem = insn_m.group(1)
        ops = insn_m.group(2)
        # Find any sym refs on this line.
        refs = list(SYM_REF_RE.finditer(line))
        rel_refs = [r for r in refs if r.group(2) == sym]

        # Direct load with %lo or %gp_rel: extract from operand.
        if rel_refs and mnem in LOAD_INSNS:
            width, sgn, fam = LOAD_INSNS[mnem]
            # Offset baked into `%lo(D_X+0xN)` or 0.
            off = int(rel_refs[0].group(3), 16) if rel_refs[0].group(3) else 0
            offsets[(off, width, fam)] += 1
            continue
        if rel_refs and mnem in STORE_INSNS:
            width, fam = STORE_INSNS[mnem]
            off = int(rel_refs[0].group(3), 16) if rel_refs[0].group(3) else 0
            offsets[(off, width, fam)] += 1
            continue

        # `addiu $dst, $src, %lo(D_X[+OFF])` → $dst now holds base+off.
        if mnem == "addiu" and rel_refs:
            opl = [t.strip().rstrip(',') for t in ops.split(',')]
            if len(opl) >= 1:
                dst = opl[0]
                off = int(rel_refs[0].group(3), 16) if rel_refs[0].group(3) else 0
                base_regs[dst] = off
            continue

        # `daddu/addu $dst, $src1, $src2`: if either source holds a base,
        # the result is base + variable_index. Subsequent loads from
        # $dst report field-offsets within the addressed element.
        # `$zero`-add forms are pure copies.
        if mnem in ("daddu", "addu") and not rel_refs:
            opl = [t.strip().rstrip(',') for t in ops.split(',')]
            if len(opl) == 3:
                dst, src1, src2 = opl
                if src1 in base_regs and src2 == "$zero":
                    base_regs[dst] = base_regs[src1]
                    continue
                if src2 in base_regs and src1 == "$zero":
                    base_regs[dst] = base_regs[src2]
                    continue
                if src1 in base_regs or src2 in base_regs:
                    # base + index — field offsets land in the loads
                    # below. Index dimension is invisible to us; report
                    # offset 0 as the base position.
                    base_regs[dst] = 0
                    continue

        # Load/store via a known base register: `lw $rD, 0xN($rB)`.
        if mnem in LOAD_INSNS or mnem in STORE_INSNS:
            mref = re.search(r'(-?0x[0-9A-Fa-f]+|-?\d+)\(\s*(\$\w+)\s*\)', ops)
            if mref:
                base = mref.group(2)
                if base in base_regs:
                    disp_str = mref.group(1)
                    disp = int(disp_str, 16) if disp_str.startswith("0x") \
                           or disp_str.startswith("-0x") else int(disp_str)
                    if mnem in LOAD_INSNS:
                        width, _, fam = LOAD_INSNS[mnem]
                    else:
                        width, fam = STORE_INSNS[mnem]
                    total_off = base_regs[base] + disp
                    if 0 <= total_off < 0x10000:
                        offsets[(total_off, width, fam)] += 1
            continue

        # `addiu $X, $X, IMM` where $X is a base — likely stride.
        if mnem == "addiu":
            opl = [t.strip().rstrip(',') for t in ops.split(',')]
            if len(opl) == 3 and opl[0] == opl[1] and opl[0] in base_regs:
                imm_s = opl[2]
                try:
                    imm = int(imm_s, 16) if imm_s.startswith("0x") \
                          or imm_s.startswith("-0x") else int(imm_s)
                    if 4 <= abs(imm) <= 0x1000:
                        strides[abs(imm)] += 1
                        base_regs[opl[0]] += imm
                except ValueError:
                    pass
            continue

        # jal/jalr/branch: conservative reset of base regs (function call
        # invalidates caller-saved registers).
        if mnem.startswith("j") or mnem.startswith("b"):
            # Keep s0-s7 (callee-saved) but drop t0-t9, a0-a3, v0-v1.
            for r in list(base_regs.keys()):
                if not re.match(r'\$s[0-9]', r):
                    del base_regs[r]
            continue

    return offsets, strides


def _emit_report(sym: str, tu: str, scanned: int, ref_count: int,
                 offsets: Counter, strides: Counter) -> None:
    print(f"{sym} in {tu}")
    print(f"  Scanned {scanned} function(s), found {ref_count} reference(s).")
    if not offsets:
        print("  (no accesses found — symbol may be referenced only as "
              "pointer-passed, not field-accessed)")
        print()
        return
    print()
    print(f"  {'offset':<8} {'width':>5} {'kind':>5} {'count':>5}")
    print(f"  {'-' * 8} {'-' * 5} {'-' * 5} {'-' * 5}")
    for (off, width, fam), cnt in sorted(offsets.items()):
        kind = {"f": "f32", "i": {1: "i8", 2: "i16", 4: "i32",
                                  8: "i64", 16: "i128"}.get(width, "?")}[fam]
        print(f"  0x{off:04X}   {width:>5} {kind:>5} {cnt:>5}")
    if strides:
        top = strides.most_common(1)[0]
        print(f"  stride: 0x{top[0]:X} (seen {top[1]}× via outer addiu)")
    print()


def main() -> int:
    if len(sys.argv) < 2:
        sys.exit("usage: dump_struct_accesses.py D_<VMA> [D_<VMA> ...]")
    data_tu = _load_data_tu_map()
    tu_funcs = _load_tu_funcs()
    for arg in sys.argv[1:]:
        sym = arg.strip()
        if not re.fullmatch(r'D_[0-9A-Fa-f]{8}', sym):
            print(f"skipping {arg}: not a D_<8hex> symbol", file=sys.stderr)
            continue
        sym = sym[:2] + sym[2:].upper()
        tu = data_tu.get(sym) or "(unknown TU)"
        # The TU-funcs map is sparse (most funcs are still untagged).
        # Scan ALL asm/cod/*.s files for refs — it's only ~1500 files
        # and the regex prefilter rejects 99% in milliseconds.
        all_offsets: Counter = Counter()
        all_strides: Counter = Counter()
        scanned = 0
        ref_count = 0
        for ap in sorted(ASM_COD.glob("*.s")):
            text = ap.read_text()
            if sym not in text:
                continue
            # Find every glabel in this file and scan each as a function.
            for gm in re.finditer(r'^glabel\s+func_([0-9A-Fa-f]{8})',
                                  text, re.MULTILINE):
                fv = int(gm.group(1), 16)
                offsets, strides = _scan_function(ap, fv, sym)
                if offsets or strides:
                    scanned += 1
                    ref_count += sum(offsets.values())
                    all_offsets.update(offsets)
                    all_strides.update(strides)
        _emit_report(sym, tu, scanned, ref_count, all_offsets, all_strides)
    return 0


if __name__ == "__main__":
    sys.exit(main())
