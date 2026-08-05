#!/usr/bin/env python3
"""
tools/classify_asm.py — fingerprint a splat-emitted .s and suggest
matching recipes from decomp/COOKBOOK.md. Optionally emit the recipe's
C template as a starting-point .c file.

Usage:
    tools/classify_asm.py <asm/.../func_X.s>          # one file
    tools/classify_asm.py --bucket <dir/>             # every .s in dir
    tools/classify_asm.py --top N <file.s>            # show top N (default 3)
    tools/classify_asm.py --json <file.s>             # dump raw signals
    tools/classify_asm.py --scaffold <file.s>         # ALSO emit C scaffold
    tools/classify_asm.py --recipe 1.2 --name func_X  # scaffold by recipe id

The classifier reads a single .s once, extracts a "signals" dict
(frame size, jal count, branch-likely set, MMI ops, FP ops, gp_rel uses,
etc.), then applies a list of RULES. Each rule is a (predicate list,
weight, recipe section). A rule fires when ALL its predicates pass; the
recipe's confidence = sum(weights of firing rules sharing the recipe id).

When --scaffold is set, the cookbook is parsed for ```c blocks under
the top-scoring recipe, the function name is substituted in, the right
`#include` headers are prepended, and a comment block is emitted
naming the jal targets the human still needs to fill in. The result is
a *starting point* — compilable shell that quick_diff will reject; the
human still iterates from there.

This file is intentionally pure-stdlib and self-contained. Add new
recipes by appending to RULES. Add new signal dimensions by extending
extract_signals(). When the cookbook grows a new §N.M, add a matching
rule here. Templates live in COOKBOOK.md — no duplicate template store.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable


# ---------------------------------------------------------------------------
# Signal extraction
# ---------------------------------------------------------------------------

# Strip the splat per-insn comment: `/* file_off vram bytes_le */`.
# What remains starts at the mnemonic (possibly preceded by one space if
# it's a delay-slot instruction).
COMMENT_RE = re.compile(r"^\s*/\*[^*]*\*/\s*")
NONMATCHING_RE = re.compile(r"^\s*nonmatching\s+(\S+),\s*(0x[0-9A-Fa-f]+)")
GLABEL_RE = re.compile(r"^\s*glabel\s+(\S+)")
ENDLABEL_RE = re.compile(r"^\s*endlabel\s+(\S+)")
LABEL_RE = re.compile(r"^\s*\.?L?[\w$]+:\s*$")
DIRECTIVE_RE = re.compile(r"^\s*\.(?:align|p2align|set|ent|end|extern|word|byte|skip|space)\b")

BRANCH_LIKELY = {"beql", "bnel", "blezl", "bgezl", "bltzl", "bgtzl"}
UNALIGNED_LL = {"ldl", "ldr", "sdl", "sdr"}
MMI_OPS = {
    "lq", "sq", "pextlw", "pextlh", "pextlb", "pextuw", "pextuh", "pextub",
    "pcpyld", "pcpyud", "pcpyh", "pmaddh", "pmaddw", "pmaddhz", "pmsubh",
    "pmulth", "pmultw", "pinteh", "pinth", "ppach", "ppacw", "ppacb",
    "paddh", "paddw", "paddb", "psubh", "psubw", "psubb", "psllh", "psllw",
    "psrah", "psraw", "psrlh", "psrlw", "pand", "por", "pxor", "pnor",
    "qmfc2", "qmtc2",
}
FP_LOAD_STORE = {"lwc1", "swc1", "ldc1", "sdc1"}
FP_ARITH = {
    "add.s", "sub.s", "mul.s", "div.s", "sqrt.s", "abs.s", "neg.s",
    "cvt.s.w", "cvt.w.s", "cvt.s.d", "cvt.d.s", "rsqrt.s",
    "mov.s", "mtc1", "mfc1",
}
FCC_COMPARES = {"c.lt.s", "c.le.s", "c.eq.s", "c.lt.d", "c.le.d", "c.eq.d"}
ARG_REGS = {f"$4", f"$5", f"$6", f"$7"}    # $a0..$a3
TEMP_REGS = {f"$8", f"$9", f"$10", f"$11", f"$12", f"$13", f"$14", f"$15"}  # $t0..$t7


@dataclass
class Signals:
    path: str
    name: str = ""
    size: int = 0           # byte size from `nonmatching` decl
    insn_count: int = 0
    insns: list[tuple[str, str, bool]] = field(default_factory=list)
    # ^ list of (mnemonic, operand_str, is_delay_slot)
    frame_size: int | None = None
    jal_count: int = 0
    jal_targets: list[str] = field(default_factory=list)
    has_sibcall: bool = False    # final non-delay insn is `j func_*`
    has_jr_ra: bool = False
    branch_likely: set[str] = field(default_factory=set)
    mmi_ops: set[str] = field(default_factory=set)
    unaligned_ll: set[str] = field(default_factory=set)
    fp_ops: set[str] = field(default_factory=set)
    fcc_compares: int = 0
    gp_rel_uses: int = 0
    gp_rel_bare: int = 0    # splat's `(SYM) /* gp_rel: */` form
    has_vu0: bool = False
    arg_save_run: int = 0   # consecutive `sd $aN,OFF($sp)` saves at top
    a0_arg_spill: bool = False    # `sw $4, OFF($sp)` near top + later `lw $4`
    has_a0_reload: bool = False
    post_jal_v1_daddu: bool = False
    early_exit_ld_ra_in_delay: bool = False
    clear_v0_between_lds: bool = False
    has_la_macro: bool = False     # `la $rT, SYM` (not gp_rel)
    has_ldl_ldr_sdl_sdr: bool = False
    final_j_31: bool = False       # ends in `j $31`
    has_sq_a1: bool = False        # `sq $5, ...` (caller-passed qword)
    sd_ra_after_lui_addiu: bool = False  # prologue shape from §8.9
    # Derived signals (populated by _derive_signals after the main scan).
    lq_count: int = 0
    sq_count: int = 0
    has_bltzl_negu: bool = False        # §4.3 __builtin_abs idiom
    has_sw_pair_around_j31: bool = False  # §8.17 sw_pair
    has_addu_sp_in_j31_delay: bool = False  # §8.13 shared_sp_restore (sp-only)
    has_v0_eq_v1_late: bool = False     # §8.19 coalesce_v1_v0
    consecutive_lq_then_sq: bool = False  # §6.7 QCOPY64_PARALLEL
    has_dual_lui_back_to_back: bool = False  # §8.7 lui_const_swap candidate
    looks_like_natural_c: bool = False  # nothing distinctive — write natural C


def _strip(line: str) -> str:
    """Strip splat's per-instruction comment, leaving `mnemonic operands`."""
    return COMMENT_RE.sub("", line).rstrip("\n").rstrip()


def _is_delay_line(line: str) -> bool:
    """Splat indents delay-slot insns one extra space after the comment."""
    m = re.match(r"^\s*/\*[^*]*\*/(\s+)", line)
    return bool(m and len(m.group(1)) >= 3)


def _frame_size_from(operands: str) -> int | None:
    """Parse `$29, $29, -N` style sp adjustment, return positive frame size.

    Alternation order matters: try the hex form (`-?0x..`) before the
    decimal form (`-?\\d+`), since `\\d+` happily matches "0" and stops
    at the "x".
    """
    m = re.match(r"\$(?:29|sp),\s*\$(?:29|sp),\s*(-?0x[0-9A-Fa-f]+|-?\d+)", operands)
    if not m:
        return None
    val = int(m.group(1), 0)
    return -val if val < 0 else None  # only sp-allocate (negative) counts


def extract_signals(path: Path) -> Signals:
    s = Signals(path=str(path))
    text = path.read_text()
    lines = text.splitlines()

    in_func = False
    consecutive_arg_saves = 0
    saw_first_addiu_sp = False
    last_was_jal = False
    last_branch_was_early_exit = False
    last_seen_branch_was_beq_v_zero = False
    pending_post_jal_check = False

    for i, raw in enumerate(lines):
        m_nm = NONMATCHING_RE.match(raw)
        if m_nm:
            s.name = m_nm.group(1)
            s.size = int(m_nm.group(2), 16)
            continue

        m_gl = GLABEL_RE.match(raw)
        if m_gl:
            in_func = True
            if not s.name:
                s.name = m_gl.group(1)
            continue

        m_el = ENDLABEL_RE.match(raw)
        if m_el:
            in_func = False
            continue

        if not in_func:
            continue

        if LABEL_RE.match(raw) or DIRECTIVE_RE.match(raw):
            consecutive_arg_saves = 0
            last_was_jal = False
            continue

        body = _strip(raw)
        if not body:
            continue

        parts = body.split(None, 1)
        if not parts:
            continue
        mnemonic = parts[0]
        operands = parts[1] if len(parts) > 1 else ""
        is_delay = _is_delay_line(raw)

        s.insns.append((mnemonic, operands, is_delay))
        s.insn_count += 1

        # Frame size from first non-delay sp adjust.
        if (
            s.frame_size is None
            and not saw_first_addiu_sp
            and mnemonic in {"addiu", "subu", "daddiu"}
            and re.match(r"\$(?:29|sp),", operands)
        ):
            fs = _frame_size_from(operands)
            if fs is not None:
                s.frame_size = fs
                saw_first_addiu_sp = True

        # Argument save run (sd $aN, OFF($sp)) — varargs detector.
        if mnemonic == "sd":
            sm = re.match(r"\$(\d+),\s*0x?[\dA-Fa-f]+\(\$(?:sp|29)\)", operands)
            if sm and 5 <= int(sm.group(1)) <= 11:  # $a1..$a3, $t0..$t3
                consecutive_arg_saves += 1
                s.arg_save_run = max(s.arg_save_run, consecutive_arg_saves)
            else:
                consecutive_arg_saves = 0
        else:
            consecutive_arg_saves = 0

        # a0 spill+reload detection (1.2 wrapper signature).
        if mnemonic == "sw" and re.match(r"\$4,\s*0x?0?\(\$(?:sp|29)\)", operands):
            s.a0_arg_spill = True
        if mnemonic == "lw" and re.match(r"\$4,\s*0x?0?\(\$(?:sp|29)\)", operands):
            if s.a0_arg_spill:
                s.has_a0_reload = True

        # Jal tracking + post-jal $v1 daddu.
        if mnemonic == "jal":
            s.jal_count += 1
            tgt = operands.split()[0] if operands else ""
            if tgt:
                s.jal_targets.append(tgt.rstrip(","))
            pending_post_jal_check = True
            last_was_jal = True
            continue
        elif pending_post_jal_check and not is_delay:
            # First non-delay insn after jal.
            if (
                mnemonic in {"daddu", "move"}
                and re.match(r"\$3,\s*\$2", operands)
            ):
                s.post_jal_v1_daddu = True
            pending_post_jal_check = False

        # Branch families.
        if mnemonic in BRANCH_LIKELY:
            s.branch_likely.add(mnemonic)
        if mnemonic in {"beq", "beql"} and re.match(r"\$\d+,\s*\$0,", operands):
            last_seen_branch_was_beq_v_zero = True
            last_branch_was_early_exit = True
        elif mnemonic.startswith(("b", "j")) and mnemonic != "jal":
            last_seen_branch_was_beq_v_zero = False
            last_branch_was_early_exit = False

        # `ld $31, OFF($sp)` in a delay slot right after early-exit beq.
        if is_delay and last_branch_was_early_exit and mnemonic == "ld":
            if re.match(r"\$31,\s*0x?[\dA-Fa-f]+\(\$(?:sp|29)\)", operands):
                s.early_exit_ld_ra_in_delay = True
            last_branch_was_early_exit = False

        # MMI / unaligned / FP / FCC / VU0.
        if mnemonic in MMI_OPS:
            s.mmi_ops.add(mnemonic)
        if mnemonic in UNALIGNED_LL:
            s.unaligned_ll.add(mnemonic)
            s.has_ldl_ldr_sdl_sdr = True
        if mnemonic in FP_LOAD_STORE | FP_ARITH:
            s.fp_ops.add(mnemonic)
        if mnemonic in FCC_COMPARES:
            s.fcc_compares += 1
        if re.match(r"v[a-z]+(\.[wxyz]+)?$", mnemonic) or mnemonic.startswith(("qmfc2", "qmtc2", "cfc2", "ctc2", "vcallms")):
            s.has_vu0 = True

        # gp_rel uses.
        if "%gp_rel(" in operands:
            s.gp_rel_uses += 1
        elif re.search(r",\s*\([\w]+\)\s*$", body) and "gp_rel" in raw:
            s.gp_rel_bare += 1

        # la macro (non-gp_rel form).
        if mnemonic == "la":
            s.has_la_macro = True

        # sq $a1 in a leaf — pattern from §6.2.
        if mnemonic == "sq" and re.match(r"\$5,", operands):
            s.has_sq_a1 = True

        # jr $31 / final j $31.
        if mnemonic == "jr" and re.match(r"\$(?:31|ra)\b", operands):
            s.has_jr_ra = True
        if mnemonic == "j" and re.match(r"\$(?:31|ra)\b", operands):
            s.final_j_31 = True
        if mnemonic == "j" and operands.startswith("func_"):
            s.has_sibcall = True

    _derive_signals(s)
    return s


# ---------------------------------------------------------------------------
# Derived signals — multi-line patterns scanned post-hoc over s.insns
# ---------------------------------------------------------------------------

def _derive_signals(s: Signals) -> None:
    insns = s.insns
    s.lq_count = sum(1 for m, _, _ in insns if m == "lq")
    s.sq_count = sum(1 for m, _, _ in insns if m == "sq")
    s.has_bltzl_negu = _has_bltzl_negu(insns)
    s.has_sw_pair_around_j31 = _has_sw_pair_around_j31(insns)
    s.has_addu_sp_in_j31_delay = _has_addu_sp_in_j31_delay(insns)
    s.has_v0_eq_v1_late = _has_v0_eq_v1_late(insns)
    s.consecutive_lq_then_sq = _consecutive_lq_then_sq(insns)
    s.has_dual_lui_back_to_back = _has_dual_lui_back_to_back(insns)
    # "Natural C" heuristic: smaller wrapper with no exotic ops, no MMI,
    # no FP, no FCC, no VU, no unaligned, no branch-likely. The classifier
    # has nothing better to suggest, so a generic recipe-less write is
    # the right starting point.
    s.looks_like_natural_c = (
        s.insn_count <= 64
        and not s.mmi_ops
        and not s.fp_ops
        and not s.has_vu0
        and not s.unaligned_ll
        and not s.branch_likely
        and not s.has_a0_reload
        and not s.post_jal_v1_daddu
        and not s.has_sq_a1
        and s.fcc_compares == 0
        and not s.has_bltzl_negu
        and not s.has_v0_eq_v1_late
    )


def _has_bltzl_negu(insns: list[tuple[str, str, bool]]) -> bool:
    """Look for `bltzl $r, L; negu $r, $r` (branch-likely abs idiom)."""
    for i, (m, _o, _d) in enumerate(insns[:-1]):
        if m == "bltzl":
            nm, _, nd = insns[i + 1]
            if nm == "negu" and nd:
                return True
    return False


def _has_sw_pair_around_j31(insns: list[tuple[str, str, bool]]) -> bool:
    """`sw $rX,OFF($base) ; j $31 ; sw $rY,OFF2($base)` same base reg."""
    for i, (m, o, _d) in enumerate(insns):
        if m != "j" or not re.match(r"\$(?:31|ra)\b", o):
            continue
        # Walk back skipping nothing useful (.set lines are filtered out).
        if i == 0 or i + 1 >= len(insns):
            continue
        pm, po, _ = insns[i - 1]
        nm, no, nd = insns[i + 1]
        if pm != "sw" or nm != "sw" or not nd:
            continue
        pb = re.search(r"\(\$(\d+)\)", po)
        nb = re.search(r"\(\$(\d+)\)", no)
        if pb and nb and pb.group(1) == nb.group(1):
            return True
    return False


def _has_addu_sp_in_j31_delay(insns: list[tuple[str, str, bool]]) -> bool:
    """`j $31 ; addu/subu $sp,$sp,+N` in delay (shared_sp_restore --sp-only)."""
    for i, (m, o, _d) in enumerate(insns[:-1]):
        if m != "j" or not re.match(r"\$(?:31|ra)\b", o):
            continue
        nm, no, nd = insns[i + 1]
        if not nd:
            continue
        if nm in {"addu", "subu", "addiu", "daddiu"} and re.match(
            r"\$(?:29|sp),\s*\$(?:29|sp),\s*\+?\d", no
        ):
            return True
    return False


def _has_v0_eq_v1_late(insns: list[tuple[str, str, bool]]) -> bool:
    """`move $2,$3` (or `daddu $2,$3,$0`) in the last few instructions —
    §8.19 coalesce_v1_v0 signature."""
    for m, o, _d in insns[-10:]:
        if m in {"move", "daddu"} and re.match(r"\$2,\s*\$3(?:,\s*\$0)?\b", o):
            return True
    return False


def _consecutive_lq_then_sq(insns: list[tuple[str, str, bool]]) -> bool:
    """4+ consecutive `lq` followed by 4+ consecutive `sq` — QCOPY64_PARALLEL."""
    lq_runs = []
    sq_runs = []
    cur, last = 0, None
    for m, _, _ in insns:
        if m == "lq":
            cur = cur + 1 if last == "lq" else 1
            last = "lq"
            lq_runs.append(cur)
        elif m == "sq":
            cur = cur + 1 if last == "sq" else 1
            last = "sq"
            sq_runs.append(cur)
        else:
            cur, last = 0, None
    return max(lq_runs or [0]) >= 4 and max(sq_runs or [0]) >= 4


def _has_dual_lui_back_to_back(insns: list[tuple[str, str, bool]]) -> bool:
    """Two `lui $rA,%hi(D1)` / `lui $rB,%hi(D2)` close together — common
    when gcc materializes two distinct hi-base addresses in one prologue
    block (candidate for §8.7 lui_const_swap or §13 105628-style reorder)."""
    last_lui_idx = None
    for i, (m, o, _) in enumerate(insns):
        if m == "lui" and "%hi(" in o:
            if last_lui_idx is not None and i - last_lui_idx <= 3:
                return True
            last_lui_idx = i
    return False


# ---------------------------------------------------------------------------
# Rule layer
# ---------------------------------------------------------------------------

@dataclass
class Rule:
    id: str
    name: str
    section: str        # cookbook anchor, e.g. "12"
    predicates: list[Callable[[Signals], bool]]
    weight: float = 1.0
    note: str = ""


def R(id, name, section, *predicates, weight=1.0, note=""):
    return Rule(id=id, name=name, section=section, predicates=list(predicates),
                weight=weight, note=note)


RULES: list[Rule] = [
    # --- §1 Wrappers ---
    R("1.1", "Constant-arg / pass-through TCO leaf", "11",
      lambda s: s.insn_count <= 4,
      lambda s: s.has_sibcall,
      lambda s: not s.frame_size,
      lambda s: s.jal_count == 0,
      weight=1.0,
      note="2-insn tail-call leaf (j FUNC + addiu/lw delay)"),

    R("1.2", "1-jal wrapper, spill+reload", "12",
      lambda s: s.jal_count == 1,
      lambda s: s.has_a0_reload,
      lambda s: 0x10 <= (s.frame_size or 0) <= 0x40,
      weight=1.0,
      note="sw $a0 + lw $a0 around the jal"),

    R("1.3", "1-jal wrapper, spill-only (no reload) — PARK", "13",
      lambda s: s.jal_count == 1,
      lambda s: s.a0_arg_spill,
      lambda s: not s.has_a0_reload,
      weight=0.9,
      note="No known C recipe — park via tools/park.sh"),

    R("1.4", "2-jal callee-save reused across calls", "14",
      lambda s: s.jal_count == 2,
      lambda s: any(m == "lw" and re.search(r"\$1[6-9]", o)
                    for m, o, d in s.insns if d),
      weight=0.85,
      note="`lw $sN` in delay slot of first jal"),

    R("1.5", "Wrapper that defeats sibcall (jal + jr ra)", "15",
      lambda s: s.jal_count >= 1,
      lambda s: s.has_jr_ra,
      lambda s: not s.has_sibcall,
      lambda s: s.insn_count <= 12,
      weight=0.7,
      note="Add DEFEAT_TCO() after the call"),

    R("1.6", "Force-void-return TCO", "16",
      lambda s: s.has_sibcall,
      lambda s: s.insn_count <= 16,
      lambda s: s.jal_count == 0,
      weight=0.5,
      note="Declare void; keep `return f();` in body"),

    R("1.7", "vsprintf-style varargs forwarder", "17",
      lambda s: s.arg_save_run >= 6,
      lambda s: s.jal_count == 1,
      weight=1.0,
      note="7 consecutive `sd $aN/$tN, OFF($sp)` + addiu $a1,$sp,OFF"),

    # --- §2 Regalloc nudges ---
    R("2.1", "Force daddu $v1, $v0, $0 after jal", "21",
      lambda s: s.post_jal_v1_daddu,
      weight=1.0,
      note="REG(\"$3\") + KEEP_LIVE(q)"),

    R("2.4", "Force alias $a1 = $a0 at function entry", "24",
      lambda s: any(m in {"daddu", "move"} and re.match(r"\$5,\s*\$4", o)
                    for m, o, d in s.insns[:8]),
      lambda s: s.has_sibcall,
      weight=0.8,
      note="register int *alias REG(\"$5\") = self; MATERIALIZE(alias)"),

    # --- §3 Branch shape ---
    R("3.3", "beql/bnel-only diff — park", "33",
      lambda s: bool(s.branch_likely),
      weight=0.4,
      note="If diff is purely branch-likely vs plain, park (no C fix)"),

    # --- §5 Pointer / gp_rel ---
    R("5.3", "gp_rel addiu/daddiu false positive", "53",
      lambda s: s.gp_rel_uses >= 1,
      weight=0.3,
      note="If only diff is addiu vs daddiu on gp_rel loads, commit"),

    # --- §6 Unaligned / MMI ---
    R("6.1", "Unaligned 64-bit copy (ldl/ldr/sdl/sdr)", "61",
      lambda s: {"ldl", "ldr", "sdl", "sdr"} <= s.unaligned_ll
                or {"ldl", "ldr"} <= s.unaligned_ll,
      lambda s: s.insn_count <= 20,    # leaf-size: prologue + ldl/ldr/sdl/sdr + epilogue
      lambda s: s.jal_count == 0,      # no calls = it's the whole purpose
      weight=1.0,
      note="Wrap long long in __attribute__((packed)) struct"),

    R("6.2", "Non-VU `sq $a1, 0(p)` leaf", "62",
      lambda s: s.has_sq_a1,
      lambda s: not s.has_vu0,
      weight=1.0,
      note="Single-line inline asm `sq $5, 0(%0)`"),

    R("6.3", "lwu emission required", "63",
      lambda s: any(m == "lwu" for m, _, _ in s.insns),
      weight=1.0,
      note="ee-gcc 2.9 never emits lwu — inline asm required"),

    R("6.5", "16-byte qword copy (lq+sq)", "65",
      lambda s: s.lq_count == 1 and s.sq_count == 1,
      lambda s: s.insn_count <= 8,
      lambda s: not s.has_vu0,
      weight=0.9,
      note="r5900.h QCOPY16(scratch)"),

    R("6.6", "64-byte serial qcopy (4×lq+sq interleaved)", "66",
      lambda s: s.lq_count >= 4 and s.sq_count >= 4,
      lambda s: not s.consecutive_lq_then_sq,    # interleaved, not parallel
      lambda s: not s.has_vu0,
      weight=0.7,
      note="r5900.h QCOPY64_SERIAL"),

    R("6.7", "64-byte parallel qcopy (4×lq then 4×sq)", "67",
      lambda s: s.consecutive_lq_then_sq,
      lambda s: not s.has_vu0,
      weight=0.95,
      note="r5900.h QCOPY64_PARALLEL(s0..s3) — latency-hiding qcopy"),

    # --- §7 Float ---
    R("7.1", "Mixed int+float call, int arg in jal delay", "71",
      lambda s: s.jal_count >= 1,
      lambda s: bool({"mtc1", "lwc1"} & s.fp_ops),
      lambda s: any(m == "lw" and re.match(r"\$4,", o)
                    for m, o, d in s.insns if d),
      weight=0.7,
      note="KEEP_LIVE_FP / KEEP_LIVE_FP2 between float setup and call"),

    R("7.3", "fabsf/isnanf/copysignf bit-twiddle", "73",
      lambda s: "mfc1" in s.fp_ops,
      lambda s: any(m == "lui" and "0x7fff" in o for m, o, _ in s.insns),
      weight=0.9,
      note="matching.h FABSF_BIT_TWIDDLE / COPYSIGNF_BIT_TWIDDLE / ISNANF_BIT_TWIDDLE"),

    # --- §8 Scheduler postprocesses ---
    R("8.2", "early-exit `ld $31` folded into branch delay → unfold_ra_delay", "82",
      lambda s: s.early_exit_ld_ra_in_delay,
      weight=0.9,
      note="Add TU basename to config/unfold_ra_delay.txt"),

    R("8.5", "blez/bgez/bltz/bgtz/branch-likely with intended delay fill", "85",
      lambda s: bool(s.branch_likely
                     or any(m in {"blez", "bgez", "bltz", "bgtz"}
                            for m, _, _ in s.insns)),
      weight=0.4,
      note="If gas inserts nop where gcc-emit had a fill, try fill_blez_delay.txt"),

    R("8.15", "FCC compares present — may need fcc_nop", "815",
      lambda s: s.fcc_compares >= 1,
      weight=0.4,
      note="If missing FCC hazard nop after c.lt.s, add to config/fcc_nop.txt"),

    # --- §4 Conditional / arithmetic idioms ---
    R("4.3", "__builtin_abs (bltzl + negu)", "43",
      lambda s: s.has_bltzl_negu,
      weight=0.95,
      note="`__builtin_abs(x)` — NOT `if (x<0) x=-x` (compiles to movn)"),

    # --- §8 More postprocesses ---
    R("8.13", "shared_sp_restore (--sp-only) candidate", "813",
      lambda s: s.has_addu_sp_in_j31_delay,
      lambda s: s.has_jr_ra or s.final_j_31,
      weight=0.6,
      note="If next func is a 4-byte `addiu sp,+N` stub, add to config/shared_sp_restore.txt"),

    R("8.17", "sw pair around j $31 (sw_pair)", "817",
      lambda s: s.has_sw_pair_around_j31,
      weight=0.7,
      note="If diff is just two sw stores swapped around the jr, mark both stores with *(volatile T *)& casts"),

    R("8.19", "coalesce_v1_v0 candidate (`move $2,$3` near end)", "819",
      lambda s: s.has_v0_eq_v1_late,
      lambda s: s.insn_count <= 24,
      weight=0.7,
      note="If $v1 is unused elsewhere, add to config/coalesce_v1_v0.txt"),

    R("8.7", "dual lui — possible §8.7 lui_const_swap or §13 reorder", "87",
      lambda s: s.has_dual_lui_back_to_back,
      lambda s: s.insn_count <= 40,    # only suggest on small funcs
      weight=0.15,
      note="If diff is regalloc swap on the dead lui's reg, try lui_const_swap"),

    # --- §12 Build gotchas ---
    R("12.4", "VU0 ops present — bare ACC/Q/R spelling required", "124",
      lambda s: s.has_vu0,
      weight=1.0,
      note="Write VU0 asm with the period assembler's BARE ACC/Q/R operands "
           "(preprocess_old_as.py translates include/vu0.h's $-form). There is "
           "NO modern-gas path — it was retired 2026-08-05 because it filled "
           "delay slots ee-as leaves bare, faking 8 matches."),

    # --- Fallback: nothing distinctive — just write natural C ---
    R("0.0", "natural C — no recipe needed", "",
      lambda s: s.looks_like_natural_c,
      lambda s: s.insn_count >= 3,    # exclude single-nop trampolines
      weight=0.1,
      note="No exotic patterns detected. Write naive C; iterate with quick_diff."),
]


# ---------------------------------------------------------------------------
# Scoring + presentation
# ---------------------------------------------------------------------------

def score(signals: Signals) -> list[tuple[Rule, float]]:
    hits: list[tuple[Rule, float]] = []
    for rule in RULES:
        try:
            if all(pred(signals) for pred in rule.predicates):
                hits.append((rule, rule.weight))
        except Exception:
            # A predicate threw on malformed input — skip the rule, don't crash.
            continue
    hits.sort(key=lambda rw: -rw[1])
    return hits


def fmt_signals_summary(s: Signals) -> str:
    bits = [
        f"{s.insn_count} insns",
        f"size={s.size:#x}" if s.size else "size=?",
        f"frame={s.frame_size:#x}" if s.frame_size else "frame=0",
        f"{s.jal_count} jal",
    ]
    if s.has_sibcall:
        bits.append("sibcall")
    if s.has_vu0:
        bits.append("VU0")
    if s.mmi_ops:
        bits.append(f"MMI({len(s.mmi_ops)})")
    if s.fp_ops:
        bits.append("FP")
    if s.fcc_compares:
        bits.append(f"{s.fcc_compares} FCC")
    if s.branch_likely:
        bits.append(f"likely:{','.join(sorted(s.branch_likely))}")
    if s.gp_rel_uses:
        bits.append(f"{s.gp_rel_uses} gp_rel")
    return ", ".join(bits)


def print_report(signals: Signals, top: int = 3) -> None:
    print(f"{signals.name or Path(signals.path).stem} — {fmt_signals_summary(signals)}")
    hits = score(signals)
    if not hits:
        print("  no recipes matched.")
        return
    print("  candidate recipes (decomp/COOKBOOK.md):")
    for rule, w in hits[:top]:
        anchor = f"#{rule.section}" if rule.section else ""
        print(f"    §{rule.id:<6} {rule.name}  [w={w:.2f}]  → COOKBOOK.md{anchor}")
        if rule.note:
            print(f"             — {rule.note}")
    # Warnings: rules below the cutoff but present can still inform.
    spillover = hits[top:top + 3]
    if spillover:
        print("  also matched (lower confidence):")
        for rule, w in spillover:
            print(f"    §{rule.id:<6} {rule.name}  [w={w:.2f}]")


# ---------------------------------------------------------------------------
# Cookbook scaffolding
# ---------------------------------------------------------------------------

REPO_ROOT = Path(__file__).resolve().parent.parent
COOKBOOK_PATH = REPO_ROOT / "decomp" / "COOKBOOK.md"

# Match a recipe header like "### 1.2 1-jal wrapper with spill+reload".
RECIPE_HEADER_RE = re.compile(r"^###\s+(\d+\.\d+)\s+(.+?)\s*$")
CODE_FENCE_OPEN = re.compile(r"^```c\s*$")
CODE_FENCE_CLOSE = re.compile(r"^```\s*$")


@dataclass
class Recipe:
    id: str          # "1.2"
    title: str
    template: str    # first ```c block under the header
    headers: list[str] = field(default_factory=list)


def parse_cookbook(path: Path = COOKBOOK_PATH) -> dict[str, Recipe]:
    """Walk COOKBOOK.md, return a {recipe_id: Recipe} map.

    The first ```c block following each `### N.M ...` header is taken as
    the canonical template. Subsequent blocks (often "bad" contrasts) are
    ignored. Headers needed (matching.h, regpin.h, r5900.h) are inferred
    by grepping the template for the marker tokens.
    """
    if not path.exists():
        return {}
    out: dict[str, Recipe] = {}
    current: Recipe | None = None
    in_code = False
    buf: list[str] = []
    for raw in path.read_text().splitlines():
        m = RECIPE_HEADER_RE.match(raw)
        if m:
            current = Recipe(id=m.group(1), title=m.group(2), template="")
            out[current.id] = current
            in_code = False
            buf = []
            continue
        if current is None:
            continue
        if not in_code and CODE_FENCE_OPEN.match(raw):
            # First ```c block under this header — start capture only if
            # we haven't captured yet.
            if not current.template:
                in_code = True
                buf = []
            continue
        if in_code and CODE_FENCE_CLOSE.match(raw):
            current.template = "\n".join(buf)
            current.headers = _detect_headers(current.template)
            in_code = False
            continue
        if in_code:
            buf.append(raw)
    return out


def _detect_headers(template: str) -> list[str]:
    """Infer which include/*.h files the template needs."""
    needed = []
    if re.search(r"\b(DEFEAT_TCO|KEEP_LIVE(_MEM|_FP2?)?|MATERIALIZE|"
                 r"NOREORDER_BARRIER|NOP|TRAILING_PAD_NOP|"
                 r"VOLATILE_RELOAD_CALL|DEAD_DADDU_V0_SP|"
                 r"FABSF_BIT_TWIDDLE|COPYSIGNF_BIT_TWIDDLE|"
                 r"ISNANF_BIT_TWIDDLE)\b", template):
        needed.append("matching.h")
    if re.search(r"\bREG\(", template):
        needed.append("regpin.h")
    if re.search(r"\b(SYNC|EI|QCOPY\w+|LQ16_FROM|SQ16_TO|MAP_A0_TO_SPR)\b",
                 template):
        needed.append("r5900.h")
    return needed


# Wrapper-name placeholders — only the unambiguous ones get substituted
# with the real function name. `func_X` / `func_Y` / `func_target` /
# `func_callee` / `func_first` / `func_last` etc. are deliberately left
# alone: in some recipes they refer to the wrapper, in others to a
# callee, and getting it wrong inverts the meaning. The human edits
# those by hand using the TODO note in the scaffold header.
WRAPPER_NAMES = ("func_wrapper", "wrapper")

# Placeholders that are ALMOST CERTAINLY callees the human still needs
# to wire up. Surfaced in the scaffold header note so the reader knows
# they're not done.
CALLEE_PLACEHOLDERS = (
    "func_target", "func_callee", "func_first", "func_last",
    "func_X", "func_Y", "func_other",
)

INCLUDE_LINE_RE = re.compile(r'^#include\s+"[\w./]+\.h"\s*$')


def _strip_leading_includes(template: str) -> str:
    """Drop any `#include "x.h"` lines (and the blank line after them)
    from the start of a template body. They'll be re-added based on the
    template's actual macro usage, so leaving them creates duplicates.
    """
    lines = template.splitlines()
    while lines and (INCLUDE_LINE_RE.match(lines[0]) or not lines[0].strip()):
        # Only consume leading blanks if we've already consumed at least
        # one include (otherwise blank-prefixed templates lose their
        # opening blank).
        if lines[0].strip() == "":
            if not any(INCLUDE_LINE_RE.match(l) for l in lines[1:5]):
                break
        lines.pop(0)
    return "\n".join(lines)


# Helpers used by fallback_scaffold(): infer signature and pull externs
# directly from the signals dict. Keep it cheap — pure introspection of
# the already-parsed instructions, no second pass.

_GLOBAL_REF_RE = re.compile(r"%(?:hi|lo|gp_rel)\(([A-Za-z_][\w]*)\)")
# Bare-paren gp_rel form (asm/nonmatchings/.../<func>.s has these).
_GP_REL_BARE_RE = re.compile(r"\b(?:l[wbhd]u?|s[wbhd])\s+\$\d+,\s*\(([A-Za-z_][\w]*)\)")


def _infer_signature(s: Signals) -> str:
    """Best-effort C signature from the asm signal pattern."""
    # Argument-register usage. ee-gcc EE-EABI: $a0=$4, $a1=$5, $a2=$6, $a3=$7.
    arg_count = 0
    for reg_no, reg_name in [(4, "a0"), (5, "a1"), (6, "a2"), (7, "a3")]:
        used = any(re.search(rf"\$\b{reg_no}\b", o) for _, o, _ in s.insns[:16])
        if used:
            arg_count = max(arg_count, reg_no - 3)

    # Pointer-vs-int for $a0: if it's dereferenced via lw/sw/lhu/sb/etc.,
    # treat as int *. Otherwise plain int.
    a0_is_ptr = any(
        m in {"lw", "lh", "lhu", "lb", "lbu", "ld", "sw", "sh", "sb", "sd", "lwc1", "swc1"}
        and re.search(r"\$4\)", o)
        for m, o, _ in s.insns[:16]
    )

    # Return type: void if no insn writes $v0 ($2) after the prologue.
    # We treat the post-prologue area as everything after the first sd $ra
    # (or just the whole function for leaves).
    writes_v0 = any(
        re.match(r"\$2,", o) and m in {
            "addiu", "addu", "subu", "daddiu", "daddu", "or", "and", "xor",
            "lw", "lh", "lhu", "lb", "lbu", "ld", "sll", "srl", "sra", "lui",
            "move", "negu",
        }
        for m, o, _ in s.insns
    )
    rettype = "int" if (writes_v0 or s.has_sibcall) else "void"

    # Build signature.
    if arg_count == 0:
        return f"{rettype} {s.name}(void)"
    args = []
    for i in range(arg_count):
        if i == 0 and a0_is_ptr:
            args.append("int *a0")
        else:
            args.append(f"int a{i}")
    return f"{rettype} {s.name}({', '.join(args)})"


def _extracted_globals(s: Signals) -> list[str]:
    """Distinct D_<VMA> / named globals referenced via %hi/%lo/%gp_rel."""
    seen: list[str] = []
    for _, o, _ in s.insns:
        for m in _GLOBAL_REF_RE.finditer(o):
            n = m.group(1)
            if n.startswith("func_"):
                continue
            if n not in seen:
                seen.append(n)
        for m in _GP_REL_BARE_RE.finditer(o):
            n = m.group(1)
            if n not in seen:
                seen.append(n)
    return seen


def _format_asm_body(asm_text: str) -> str:
    """Indent the raw .s body as a /* ... */ comment block. We keep splat's
    per-instruction comments since they include the file offset / VRAM and
    the encoded bytes — useful context for byte-level matching."""
    lines = []
    in_func = False
    for raw in asm_text.splitlines():
        if re.match(r"^\s*glabel\s+", raw):
            in_func = True
        if in_func:
            lines.append(" * " + raw.rstrip())
        if re.match(r"^\s*endlabel\s+", raw):
            in_func = False
    return "\n".join(lines)


def fallback_scaffold(signals: Signals, asm_text: str) -> str:
    """Emit a starter .c body for a function that has no matching recipe.

    The shell includes:
      - extern declarations for every global the asm touches
      - extern declarations for every callee (from `jal` targets)
      - the inferred C signature
      - the splat-emitted asm as a comment block right above the body
      - an empty function body with a `TODO` marker

    The intent: the AI sees the full asm inline, plus a compilable shell
    it can flesh out without re-reading the .s file separately. Minor
    edits get you to byte match.
    """
    sig = _infer_signature(signals)
    globals_used = _extracted_globals(signals)
    callees = []
    seen = set()
    for t in signals.jal_targets:
        t = t.rstrip(",")
        if t and t != signals.name and t not in seen:
            callees.append(t)
            seen.add(t)

    parts: list[str] = []
    parts.append(
        f"/* Fallback scaffold — no cookbook recipe matched.\n"
        f" * Fingerprint: {fmt_signals_summary(signals)}\n"
        f" *\n"
        f" * The original asm is inlined as a comment below for reference.\n"
        f" * Fill in the body so it compiles to the same bytes; iterate via\n"
        f" * tools/quick_diff.sh or a full ninja for SHA check.\n"
        f" */\n"
    )
    # Extern declarations.
    if globals_used:
        for g in globals_used:
            parts.append(f"extern int {g};")
        parts.append("")
    if callees:
        for c in callees:
            parts.append(f"extern int {c}();")
        parts.append("")

    asm_body = _format_asm_body(asm_text)
    parts.append("/*\n" + asm_body + "\n */")
    parts.append(f"{sig}\n{{\n    /* TODO: fill in from asm above */\n}}\n")
    return "\n".join(parts)


def scaffold(recipe: Recipe, func_name: str, signals: Signals | None = None) -> str:
    """Render a recipe's template into a complete .c file body.

    Substitutes the real function name into the canonical wrapper
    placeholder, prepends the right `#include` lines, and emits a
    header comment listing jal targets + callee placeholders the human
    still has to wire up.
    """
    body = _strip_leading_includes(recipe.template)
    for placeholder in WRAPPER_NAMES:
        body = re.sub(rf"\b{re.escape(placeholder)}\b", func_name, body)

    # Detect which callee placeholders survived — those become explicit
    # TODOs in the header.
    todo_callees = [p for p in CALLEE_PLACEHOLDERS
                    if re.search(rf"\b{re.escape(p)}\b", body)]

    includes = "\n".join(f'#include "{h}"' for h in recipe.headers)
    header_note = f"/* COOKBOOK §{recipe.id} — {recipe.title}\n"
    if signals is not None:
        header_note += (
            f" * fingerprint: {fmt_signals_summary(signals)}\n"
        )
        if signals.jal_targets:
            uniq = []
            seen = set()
            for t in signals.jal_targets:
                if t not in seen:
                    uniq.append(t)
                    seen.add(t)
            header_note += f" * jal targets: {', '.join(uniq)}\n"
    if todo_callees:
        header_note += (
            f" * TODO: replace {', '.join(todo_callees)} with the real "
            f"callee name(s)\n"
            " *       (see jal targets above — the C param list and call "
            "shape\n"
            " *       still come from you).\n"
        )
    header_note += (
        " *\n"
        " * Generated by tools/classify_asm.py --scaffold. This is a\n"
        " * starting point, not a finished match. Run tools/quick_diff.sh\n"
        f" * {func_name} and iterate.\n"
        " */\n"
    )

    pieces = [header_note]
    if includes:
        pieces.append(includes + "\n")
    pieces.append(body.rstrip() + "\n")
    return "\n".join(pieces)


def _m2c_fallback(asm_path: Path) -> str | None:
    """Phase 3: when no cookbook recipe template fits the function's shape,
    generate a STRUCTURAL scaffold via the m2c adapter (tools/m2c_scaffold.py).
    Returns the scaffold text, or None if m2c produced nothing usable."""
    import subprocess
    tool = Path(__file__).resolve().parent / "m2c_scaffold.py"
    proc = subprocess.run([sys.executable, str(tool), str(asm_path)],
                          capture_output=True, text=True)
    return proc.stdout if proc.stdout.strip() else None


# ---------------------------------------------------------------------------
# Context bundle (--bundle): a self-contained per-function reasoning aid.
#
# Mechanises the standing "reason from the dev's data model, not syntax" rule:
# resolve every callee to a name+signature, every %hi/%lo/gp_rel global to a
# named symbol (with its struct field layout when known), surface the constants
# the function materialises, list the TU siblings, and inline the annotated .s —
# so the [REASONING] step of decomp-match / decomp-sweep has everything in one
# place instead of grepping the TU by hand. Read-only; reuses tools/_asmsig.py.
# ---------------------------------------------------------------------------

sys.path.insert(0, str(Path(__file__).resolve().parent))
try:
    import _asmsig  # noqa: E402
except Exception:  # pragma: no cover — bundle mode degrades, classifier still works
    _asmsig = None

# `lui $rX, 0xNNNN` / `ori $rX,$rX,0xMMMM` and friends that are NOT %hi/%lo.
_RAW_IMM_RE = re.compile(r"\b(0x[0-9A-Fa-f]+)\b")


def resolve_s_path(arg: str) -> Path | None:
    """Accept either a literal `.s` path or a bare function name (resolved via
    _asmsig.find_s, preferring matchings/ then nonmatchings/)."""
    p = Path(arg)
    if p.exists():
        return p
    if _asmsig is not None:
        return _asmsig.find_s(arg)
    return None


def _tu_stem_of(asm_path: Path) -> str | None:
    """nonmatchings/script/src/st08a/foo.s -> script/src/st08a (the sweep stem)."""
    for anchor in ("nonmatchings", "matchings"):
        if anchor in asm_path.parts:
            i = asm_path.parts.index(anchor)
            return str(Path(*asm_path.parts[i + 1:-1]))
    return None


def _unmatched_in_tu(tu_stem: str) -> set[str]:
    """INCLUDE_ASM stub names in <tu_stem>.c = the still-unmatched siblings."""
    c = REPO_ROOT / f"{tu_stem}.c"
    if not c.exists():
        return set()
    pat = re.compile(r'INCLUDE_ASM\("[^"]+",\s*(\w+)\)')
    return set(pat.findall(c.read_text(errors="replace")))


def build_bundle(signals: Signals, asm_path: Path) -> dict:
    name = signals.name or asm_path.stem
    tu_stem = _tu_stem_of(asm_path)
    vma = _asmsig.name_to_vma(name) if _asmsig else None

    # callees: jal targets -> best-effort signature
    callees = []
    seen = set()
    for t in signals.jal_targets:
        t = t.rstrip(",")
        if not t or t == name or t in seen:
            continue
        seen.add(t)
        sig = _asmsig.callee_sig(t) if _asmsig else f"{t}(?)"
        callees.append({"name": t, "sig": sig})

    # globals: %hi/%lo/gp_rel symbols -> name, tu, struct field layout
    globals_info = []
    for g in _extracted_globals(signals):
        info = {"name": g, "tu": None, "fields": None}
        if _asmsig:
            shape = _asmsig.struct_shape(g)
            if shape:
                info["tu"] = shape.get("tu")
                info["stride"] = shape.get("stride")
                info["fields"] = shape.get("fields")
            else:
                gv = _asmsig.name_to_vma(g)
                if gv is not None:
                    info["tu"] = _asmsig.resolve(gv).get("tu")
        globals_info.append(info)

    # constants materialised (raw immediates, excluding the small frame/offsets)
    consts = []
    cseen = set()
    for m, o, _ in signals.insns:
        if m in {"lui", "ori", "li", "lw", "addiu", "daddiu"} and "%" not in o:
            for im in _RAW_IMM_RE.findall(o):
                v = int(im, 16)
                if v >= 0x1000 and im not in cseen:   # skip tiny stack offsets
                    cseen.add(im)
                    consts.append(im)

    # siblings in the same TU
    siblings = []
    if tu_stem:
        unmatched = _unmatched_in_tu(tu_stem)
        sib_dir = asm_path.parent
        for s in sorted(sib_dir.glob("*.s")):
            if s.stem == name:
                continue
            siblings.append({"name": s.stem,
                             "matched": s.stem not in unmatched})

    return {
        "name": name, "vma": (f"0x{vma:08X}" if vma else None),
        "tu": tu_stem, "size": signals.size, "insn_count": signals.insn_count,
        "fingerprint": fmt_signals_summary(signals),
        "recipes": [{"id": r.id, "name": r.name, "section": r.section,
                     "note": r.note} for r, _ in score(signals)[:3]],
        "callees": callees, "globals": globals_info, "constants": consts,
        "siblings": siblings,
        "asm": _format_asm_body(asm_path.read_text(errors="replace")),
    }


def render_bundle_md(b: dict) -> str:
    L = []
    hdr = f"# {b['name']}"
    if b["vma"]:
        hdr += f"  ({b['vma']})"
    L.append(hdr)
    L.append(f"- TU: `{b['tu']}`   size: {b['size']:#x}   {b['insn_count']} insns")
    L.append(f"- fingerprint: {b['fingerprint']}")
    if b["recipes"]:
        L.append("\n## Recipe hints (decomp/COOKBOOK.md)")
        for r in b["recipes"]:
            anchor = f" → §{r['section']}" if r["section"] else ""
            L.append(f"- §{r['id']} {r['name']}{anchor}")
            if r["note"]:
                L.append(f"  - {r['note']}")
    if b["callees"]:
        L.append("\n## Callees")
        for c in b["callees"]:
            L.append(f"- `{c['sig']}`")
    if b["globals"]:
        L.append("\n## Globals / structs")
        for g in b["globals"]:
            line = f"- `{g['name']}`"
            if g.get("tu"):
                line += f"  (tu: {g['tu']})"
            if g.get("stride"):
                line += f"  stride={g['stride']}"
            L.append(line)
            if g.get("fields"):
                for f in g["fields"][:12]:
                    sgn = "s" if f.get("signed") else "u"
                    L.append(f"    off {f['off']:#x}  w{f['width']} {sgn}"
                             f"  x{f.get('count','?')}")
    if b["constants"]:
        L.append("\n## Constants materialised")
        L.append("  " + ", ".join(b["constants"]))
    if b["siblings"]:
        L.append("\n## TU siblings")
        for s in b["siblings"]:
            flag = "matched" if s["matched"] else "UNMATCHED"
            L.append(f"- {s['name']}  [{flag}]")
    L.append("\n## Disassembly")
    L.append("```")
    L.append(b["asm"])
    L.append("```")
    return "\n".join(L) + "\n"


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("path", nargs="?", help="asm .s file or func name (omit with --bucket)")
    ap.add_argument("--bucket", help="directory; classify every .s file under it")
    ap.add_argument("--top", type=int, default=3, help="show top-N recipes (default 3)")
    ap.add_argument("--bundle", action="store_true",
                    help="emit a self-contained per-function context bundle "
                         "(callees+sigs, globals+structs, siblings, asm)")
    ap.add_argument("--json", action="store_true", help="dump raw signals as JSON")
    ap.add_argument("--scaffold", action="store_true",
                    help="emit C scaffold for top-scoring recipe (stdout)")
    ap.add_argument("--write", metavar="PATH",
                    help="write C scaffold to PATH instead of stdout (implies --scaffold)")
    ap.add_argument("--recipe", metavar="ID",
                    help="bypass classification; scaffold this recipe id (e.g. 1.2)")
    ap.add_argument("--name", metavar="FUNC",
                    help="function name for --recipe (e.g. func_001A2758)")
    args = ap.parse_args(argv[1:])

    # --recipe + --name: direct scaffold mode, no .s file needed.
    if args.recipe:
        if not args.name:
            print("--recipe requires --name", file=sys.stderr)
            return 2
        cookbook = parse_cookbook()
        if args.recipe not in cookbook:
            print(f"no recipe §{args.recipe} in {COOKBOOK_PATH}", file=sys.stderr)
            return 1
        out = scaffold(cookbook[args.recipe], args.name)
        if args.write:
            Path(args.write).write_text(out)
            print(f"wrote {args.write}", file=sys.stderr)
        else:
            sys.stdout.write(out)
        return 0

    if args.bucket:
        d = Path(args.bucket)
        if not d.is_dir():
            print(f"not a directory: {d}", file=sys.stderr)
            return 2
        for p in sorted(d.rglob("func_*.s")):
            sig = extract_signals(p)
            if args.json:
                _emit_json(sig)
            else:
                print_report(sig, top=args.top)
                print()
        return 0

    if not args.path:
        ap.print_usage(sys.stderr)
        return 2

    # --bundle accepts a bare func name (resolved via _asmsig) or a .s path.
    if args.bundle:
        p = resolve_s_path(args.path)
        if p is None or not p.exists():
            print(f"could not resolve a .s for: {args.path}", file=sys.stderr)
            return 1
        sig = extract_signals(p)
        bundle = build_bundle(sig, p)
        if args.json:
            print(json.dumps(bundle, indent=2))
        else:
            sys.stdout.write(render_bundle_md(bundle))
        return 0

    p = Path(args.path)
    if not p.exists():
        print(f"file not found: {p}", file=sys.stderr)
        return 1
    sig = extract_signals(p)
    if args.json:
        _emit_json(sig)
        return 0

    print_report(sig, top=args.top)

    if args.scaffold or args.write:
        hits = score(sig)
        recipe = None
        if hits:
            recipe = parse_cookbook().get(hits[0][0].id)
        if hits and recipe and recipe.template:
            out = scaffold(recipe, sig.name, signals=sig)
            src = f"§{hits[0][0].id} cookbook template"
        else:
            # No cookbook recipe/template fits (large/novel/FP) — fall back to
            # the m2c structural scaffold (Phase 3) instead of fabricating.
            reason = "no recipe matched" if not hits \
                else f"§{hits[0][0].id} has no C template"
            out = _m2c_fallback(p)
            if out is None:
                print(f"\n(--scaffold: {reason}; m2c fallback produced nothing)",
                      file=sys.stderr)
                return 0
            src = f"m2c fallback ({reason})"
        if args.write:
            Path(args.write).write_text(out)
            print(f"\nwrote {args.write}  [{src}]", file=sys.stderr)
        else:
            print()
            print(f"--- scaffold ({src}) for {sig.name} ---")
            sys.stdout.write(out)
    return 0


def _emit_json(s: Signals) -> None:
    d = {
        "path": s.path, "name": s.name, "size": s.size,
        "insn_count": s.insn_count, "frame_size": s.frame_size,
        "jal_count": s.jal_count, "jal_targets": s.jal_targets,
        "has_sibcall": s.has_sibcall, "has_jr_ra": s.has_jr_ra,
        "branch_likely": sorted(s.branch_likely),
        "mmi_ops": sorted(s.mmi_ops),
        "unaligned_ll": sorted(s.unaligned_ll),
        "fp_ops": sorted(s.fp_ops),
        "fcc_compares": s.fcc_compares,
        "gp_rel_uses": s.gp_rel_uses, "gp_rel_bare": s.gp_rel_bare,
        "has_vu0": s.has_vu0, "arg_save_run": s.arg_save_run,
        "a0_arg_spill": s.a0_arg_spill, "has_a0_reload": s.has_a0_reload,
        "post_jal_v1_daddu": s.post_jal_v1_daddu,
        "early_exit_ld_ra_in_delay": s.early_exit_ld_ra_in_delay,
        "final_j_31": s.final_j_31, "has_sibcall_": s.has_sibcall,
        "has_sq_a1": s.has_sq_a1, "has_ldl_ldr_sdl_sdr": s.has_ldl_ldr_sdl_sdr,
    }
    print(json.dumps(d, indent=2))


if __name__ == "__main__":
    sys.exit(main(sys.argv))
