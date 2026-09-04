#!/usr/bin/env python3
"""
tools/tag_diff.py — pattern-match a built-vs-expected asm diff against
known cookbook anti-patterns and surface the fix hint.

Shared by `tools/quick_diff.sh` (per-iteration inner loop, ~100 ms) and
`tools/first_diff.py` (full-build SHA-fail post-mortem). Same rule list
either way; the human/AI sees the suggested cookbook section + config
line / C reformulation at every diff cycle instead of re-deriving it.

Input shape (CLI):
    tag_diff.py <expected.txt> <built.txt>

Each input file is one instruction per line (mnemonic + operands, no
addresses, no encoded bytes). Both must have the same intent (i.e.,
both are stripped to compare). Lines that match between the two files
are skipped; diverging spans are passed through each rule.

Output: zero or more `[§N.M] <description>` lines on stdout, one per
firing rule, plus a `see decomp/COOKBOOK.md#NM` link.

Rules are catalogued at module level in RULES. Each rule has:
  - id           — cookbook section ("8.21")
  - name         — short description ("beq + nop where original fills")
  - match(diff)  — predicate taking a list of (expected, built) line
                   pairs and returning True if the pattern fires
  - hint         — one-line fix suggestion (a SOURCE-SHAPE lever; crutch
                    pins/barriers and per-file postprocess allowlists are
                    retired and banned — see CLAUDE.md)

To add a rule: append an entry to RULES. Also add the matching
`**Diff fingerprint:**` line to the cookbook recipe (mirror discipline
documented in MATCH.md §"Cookbook hygiene").
"""

from __future__ import annotations

import re
import sys
from dataclasses import dataclass, field
from pathlib import Path
from typing import Callable


# ---------------------------------------------------------------------------
# Diff-pair model — each element is (expected_line, built_line).
# Either side may be None when the diff is one-sided (insertion/deletion).
# ---------------------------------------------------------------------------

DiffPair = tuple[str | None, str | None]


# ---------------------------------------------------------------------------
# Helper predicates — shared across rules
# ---------------------------------------------------------------------------

def _mnem(line: str | None) -> str | None:
    """Extract the mnemonic from a raw asm line; returns None if no insn."""
    if not line:
        return None
    m = re.match(r"^\s*([a-z][a-z0-9.]*)\b", line)
    return m.group(1) if m else None


def _on_left_only(pairs: list[DiffPair], mnem: str) -> bool:
    """Does `mnem` appear on the expected (left) side but not the built side?"""
    return any(
        _mnem(e) == mnem and _mnem(b) != mnem
        for e, b in pairs
    )


def _on_right_only(pairs: list[DiffPair], mnem: str) -> bool:
    return any(
        _mnem(b) == mnem and _mnem(e) != mnem
        for e, b in pairs
    )


def _both_have(pairs: list[DiffPair], left_mnem: str, right_mnem: str) -> bool:
    """Pair where left has `left_mnem` and right has `right_mnem`."""
    return any(
        _mnem(e) == left_mnem and _mnem(b) == right_mnem
        for e, b in pairs
    )


def _has_pair(pairs: list[DiffPair], pred: Callable[[str, str], bool]) -> bool:
    return any(e and b and pred(e, b) for e, b in pairs)


# ---------------------------------------------------------------------------
# Rules
# ---------------------------------------------------------------------------

@dataclass
class Rule:
    id: str
    name: str
    match: Callable[[list[DiffPair]], bool]
    hint: str


def _rule_beq_nop_fill(pairs: list[DiffPair]) -> bool:
    """built has `beq/bne X; nop; sw...`, expected has `beq/bne X; sw...`."""
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if _mnem(b0) in {"beq", "bne", "beqz", "bnez"} \
                and _mnem(b1) == "nop" \
                and _mnem(e0) == _mnem(b0) \
                and _mnem(e1) in {"sw", "sd", "sh", "sb"}:
            return True
    return False


def _rule_blez_nop_fill(pairs: list[DiffPair]) -> bool:
    """built has `blez/bgez/bltz/bgtz X; nop; <X>` where expected fills."""
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if _mnem(b0) in {"blez", "bgez", "bltz", "bgtz", "blezl", "bgezl",
                         "bltzl", "bgtzl", "beql", "bnel"} \
                and _mnem(b1) == "nop" \
                and _mnem(e0) == _mnem(b0) \
                and _mnem(e1) not in {"nop", None}:
            return True
    return False


def _rule_branch_likely_mnemonic(pairs: list[DiffPair]) -> bool:
    """beq/bne (one side) vs beql/bnel (other side), otherwise identical operands."""
    LIKELY = {"beql": "beq", "bnel": "bne"}
    for e, b in pairs:
        em, bm = _mnem(e), _mnem(b)
        if em in LIKELY and bm == LIKELY[em]:
            return True
        if bm in LIKELY and em == LIKELY[bm]:
            return True
    return False


def _rule_gp_rel_addiu_vs_daddiu(pairs: list[DiffPair]) -> bool:
    """`daddiu $rT,$gp,...` (expected) vs `addiu $rT,$gp,...` (built) — false positive."""
    for e, b in pairs:
        if e and b and "%gp_rel" in (e + b):
            em, bm = _mnem(e), _mnem(b)
            if {em, bm} == {"daddiu", "addiu"}:
                return True
    return False


def _rule_swap_addu_to_rt(pairs: list[DiffPair]) -> bool:
    """`addu $X,$X,$Y` (built) vs `addu $X,$Y,$X` (expected) — operand swap."""
    pat = re.compile(r"addu\s+\$(\w+),\s*\$(\w+),\s*\$(\w+)")
    for e, b in pairs:
        if not (e and b):
            continue
        em = pat.search(e)
        bm = pat.search(b)
        if em and bm:
            ex, ey, ez = em.groups()
            bx, by, bz = bm.groups()
            if ex == bx and ((ey == bz and ez == by) or (ey == by and ez == bz and ey != by)):
                return True
    return False


def _rule_v1_daddu_after_jal(pairs: list[DiffPair]) -> bool:
    """Expected has `daddu $v1,$v0,$0` (or `move $v1,$v0`) after a jal,
    built lacks the dead copy → recover the dev's value-reuse shape (route
    the call result through a second genuinely-read local); pins are banned."""
    for i in range(len(pairs)):
        e, _ = pairs[i]
        if e and re.search(r"(daddu\s+\$3,\$2,\$0|move\s+\$3,\$2)\b", e):
            # Check if built has the same; if not, fire
            _, b = pairs[i]
            if not b or not re.search(r"(daddu\s+\$3,\$2,\$0|move\s+\$3,\$2)\b", b):
                return True
    return False


def _rule_unsigned_mask(pairs: list[DiffPair]) -> bool:
    """`addiu $rT,$0,0xFFC0` (built) vs `lui $rT,0xFFFF` + `ori` (expected)."""
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if e0 and e1 and re.search(r"lui\s+\$\w+,\s*0x[fF][fF][fF][fF]\b", e0) \
                and _mnem(e1) == "ori" \
                and _mnem(b0) in {"addiu"} \
                and "0xff" in (b0 or "").lower():
            return True
    return False


def _rule_signed_shift_movn(pairs: list[DiffPair]) -> bool:
    """`movn`/`slt+movn` in built vs `sra X,2; srl X,2` in expected."""
    has_movn = any(_mnem(b) == "movn" for _, b in pairs)
    has_sra_srl = any(_mnem(e) in {"sra", "srl"} for e, _ in pairs)
    return has_movn and has_sra_srl


def _rule_sltu_movz_bool_collapse(pairs: list[DiffPair]) -> bool:
    """Built has `sltu+movz`, expected has multiple distinct `jr ra` paths."""
    has_sltu_in_built = any(_mnem(b) == "sltu" for _, b in pairs)
    has_movz_or_movn = any(_mnem(b) in {"movz", "movn"} for _, b in pairs)
    return has_sltu_in_built and has_movz_or_movn


def _rule_swap_zero_ret_ld_ra(pairs: list[DiffPair]) -> bool:
    """`daddu $2,$0,$0` before `ld $31` (built) vs after (expected)."""
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if b0 and re.search(r"(daddu\s+\$2,\$0,\$0|move\s+\$2,\$0)", b0) \
                and b1 and re.search(r"ld\s+\$31,", b1) \
                and e0 and re.search(r"ld\s+\$31,", e0):
            return True
    return False


def _rule_trailing_nop(pairs: list[DiffPair]) -> bool:
    """Built ends with `j $31; nop`, expected ends without the trailing nop."""
    # Check the last two pairs.
    if len(pairs) < 2:
        return False
    e_last, b_last = pairs[-1]
    e_prev, b_prev = pairs[-2]
    return (b_prev and re.search(r"j\s+\$(31|ra)\b", b_prev)
            and _mnem(b_last) == "nop"
            and (not e_last or _mnem(e_last) != "nop"))


def _rule_fcc_compare_missing_nop(pairs: list[DiffPair]) -> bool:
    """c.lt.s/c.le.s/c.eq.s present, expected has explicit nop after."""
    FCC = {"c.lt.s", "c.le.s", "c.eq.s", "c.lt.d", "c.le.d", "c.eq.d"}
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if _mnem(e0) in FCC and _mnem(e1) == "nop" \
                and _mnem(b0) in FCC and _mnem(b1) != "nop":
            return True
    return False


def _rule_fpr_letter_swap(pairs: list[DiffPair]) -> bool:
    """`lwc1 $fA,OFF(...)` (expected) vs `lwc1 $fB,OFF(...)` (built) — same
    mnemonic and offsets, only the FP register letter differs. Same pattern
    on the very next swc1/use. A source-shape FP regalloc tie — reorder the
    float decls/uses or free the original register; REG() pins are banned."""
    fp_op = re.compile(r"^(lwc1|swc1|mov\.s|mfc1|mtc1)\s+\$f(\d+)\b")
    saw = False
    for e, b in pairs:
        if not (e and b):
            continue
        em = fp_op.match(e)
        bm = fp_op.match(b)
        if not (em and bm):
            continue
        if em.group(1) != bm.group(1):
            continue
        if em.group(2) == bm.group(2):
            continue
        # Operands after register should match
        e_rest = e[em.end():]
        b_rest = b[bm.end():]
        if e_rest == b_rest:
            saw = True
    return saw


def _rule_swc1_in_jal_delay(pairs: list[DiffPair]) -> bool:
    """built has `jal X; swc1 $fN, OFF(...)` (store fills jal delay), expected
    has the swc1 BEFORE the jal and something else (addiu / lw / mov) in the
    delay. Common when an unrelated trailing store competes with call-arg
    setup for the slot."""
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if _mnem(b0) == "jal" and _mnem(b1) in {"swc1", "sw", "sd"}:
            if _mnem(e0) == "jal" and _mnem(e1) not in {"swc1", "sw", "sd"}:
                return True
    return False


def _rule_alternating_reload_regs(pairs: list[DiffPair]) -> bool:
    """Chain of `lw $rT, OFF($rs)` reloads where expected alternates between
    two registers (`$v0`/`$v1`) but built uses a single register. Indicates
    the original codegen rotated temporaries across back-to-back independent
    loads of the same memory; gcc by default coalesces them onto one temp."""
    lw_pat = re.compile(r"^lw\s+\$(\w+),\s*(-?\d+|0x[0-9a-fA-F]+)\(\$(\w+)\)")
    expected_dests: list[str] = []
    built_dests: list[str] = []
    expected_offs: list[str] = []
    built_offs: list[str] = []
    for e, b in pairs:
        if e and (m := lw_pat.match(e)):
            expected_dests.append(m.group(1))
            expected_offs.append(m.group(2) + "(" + m.group(3) + ")")
        if b and (m := lw_pat.match(b)):
            built_dests.append(m.group(1))
            built_offs.append(m.group(2) + "(" + m.group(3) + ")")
    # Need ≥3 lw's on the same source address on both sides; expected uses
    # ≥2 distinct dest regs, built uses 1.
    if len(expected_dests) < 3 or len(built_dests) < 3:
        return False
    if expected_offs[:3] != built_offs[:3]:
        return False  # different addresses; not the same pattern
    return (len(set(expected_dests)) >= 2
            and len(set(built_dests)) == 1)


def _rule_lui_addiu_late(pairs: list[DiffPair]) -> bool:
    """rodata-pointer `lui+addiu` of a D_X address materializes right before
    a jal (built) instead of earlier (expected). Heuristic: expected has the
    lui at an earlier diff position than built, OR built clusters `lui+addiu+jal`
    while expected has them split apart."""
    # Cheap proxy: built has `lui $a1,0x..; addiu $a1,$a1,..; jal` and
    # expected has them broken up by intervening ops.
    for i in range(len(pairs) - 2):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        e2, b2 = pairs[i + 2]
        if _mnem(b0) == "lui" and _mnem(b1) == "addiu" and _mnem(b2) == "jal":
            if not (_mnem(e0) == "lui" and _mnem(e1) == "addiu"
                    and _mnem(e2) == "jal"):
                # Expected has different scheduling here
                return True
    return False


# --- taxonomy expansion: codegen-shape tags for the agentic loop -----------
# These complement the byte-pattern rules above with the structural shapes the
# match_loop plateau policy keys on (regalloc-swap / fp-licm are "permuter
# territory"; frame-size / far-global / branch-direction are hand-fixable).

_OPRE = re.compile(r"^\s*([a-z][a-z0-9.]*)\s+(.*)$")
_REGTOK = re.compile(r"^\$?(?:v[01]|a[0-3]|t[0-9]|s[0-7]|f[0-9]+)$")  # swappable regs
_BRANCH = {"beq", "bne", "beqz", "bnez", "beql", "bnel", "blez", "bgez",
           "bltz", "bgtz", "b", "j"}


def _ops(line: str | None):
    """(mnemonic, [operand tokens]) or (None, []) if not an instruction."""
    if not line:
        return None, []
    m = _OPRE.match(line)
    if not m:
        mm = _mnem(line)
        return mm, []
    return m.group(1), [t for t in re.split(r"[,\s]+", m.group(2)) if t]


def _rule_regalloc_swap(pairs: list[DiffPair]) -> bool:
    """Same op/operands, ONE register token swapped, recurring ≥2× — a
    register-allocation tie-break (sceneManager v0/v1, motionManager2 s5/s6)."""
    from collections import Counter
    swaps: Counter = Counter()
    for e, b in pairs:
        if not (e and b):
            continue
        em, eo = _ops(e); bm, bo = _ops(b)
        if em is None or em != bm or len(eo) != len(bo):
            continue
        diffs = [(x, y) for x, y in zip(eo, bo) if x != y]
        if len(diffs) == 1 and _REGTOK.match(diffs[0][0]) and _REGTOK.match(diffs[0][1]):
            swaps[frozenset(diffs[0])] += 1
    return any(c >= 2 for c in swaps.values())


def _rule_fp_licm(pairs: list[DiffPair]) -> bool:
    """A callee-saved $f20-$f23 the original keeps via `lwc1` but the build
    fills via `mtc1` (or vice versa) — loop-invariant FP hoist mismatch. Global
    scan (not pair-positional), since line zipping misaligns after insertions."""
    fp = re.compile(r"\$f2[0-3]\b")
    exp_lwc1, exp_mtc1, blt_lwc1, blt_mtc1 = set(), set(), set(), set()
    for e, b in pairs:
        for line, lw, mt in ((e, exp_lwc1, exp_mtc1), (b, blt_lwc1, blt_mtc1)):
            if not line:
                continue
            m = fp.search(line)
            if not m:
                continue
            if _mnem(line) == "lwc1":
                lw.add(m.group(0))
            elif _mnem(line) == "mtc1":
                mt.add(m.group(0))
    return bool((exp_lwc1 & blt_mtc1) or (blt_lwc1 & exp_mtc1))


def _rule_delay_slot_occupant(pairs: list[DiffPair]) -> bool:
    """A branch whose delay slot is the epilogue `ld ra`/`ld $31` on one side
    but useful fall-through work on the other (sceneManager epilogue split)."""
    def is_ld_ra(line):
        return _mnem(line) == "ld" and re.search(r"\bld\s+(ra|\$31)\b", line or "")
    for i in range(len(pairs) - 1):
        e0, b0 = pairs[i]
        e1, b1 = pairs[i + 1]
        if _mnem(e0) in _BRANCH and _mnem(b0) in _BRANCH:
            if is_ld_ra(e1) != is_ld_ra(b1):   # exactly one side fills with ld ra
                return True
    return False


def _rule_branch_direction(pairs: list[DiffPair]) -> bool:
    """Opposite branch sense (beq↔bne / beqz↔bnez / bc1f↔bc1t) on the same
    compared operands — body-inline vs body-out-of-line (a C-structure call)."""
    OPP = [{"beq", "bne"}, {"beqz", "bnez"}, {"bc1f", "bc1t"}, {"beql", "bnel"}]
    for e, b in pairs:
        if not (e and b):
            continue
        em, eo = _ops(e); bm, bo = _ops(b)
        if em == bm:
            continue
        ereg = [o for o in eo if _REGTOK.match(o)]
        breg = [o for o in bo if _REGTOK.match(o)]
        if any({em, bm} == o for o in OPP) and ereg and ereg == breg:
            return True
    return False


def _rule_frame_size(pairs: list[DiffPair]) -> bool:
    """Prologue `addiu sp,sp,-N` with a different N — usually a missing
    callee-saved reg / high-part hoist (→ §5.7) cascading the whole frame."""
    fr = re.compile(r"^(?:d?addiu)\s+sp,sp,(-?\d+|-?0x[0-9a-f]+)")
    for e, b in pairs:
        if not (e and b):
            continue
        me, mb = fr.match(e), fr.match(b)
        if me and mb and me.group(1) != mb.group(1):
            return True
    return False


def _rule_far_global_gp_rel(pairs: list[DiffPair]) -> bool:
    """Built reaches a global via gp_rel `(gp)` where the original materializes
    it with `lui`+%lo — a far in-TU small global (asm-label alias, §5.7)."""
    return _has_pair(pairs, lambda e, b: _mnem(e) == "lui" and "(gp)" in b) \
        or _has_pair(pairs, lambda e, b: _mnem(b) == "lui" and "(gp)" in e)


RULES: list[Rule] = [
    Rule("8.21", "beq/bne delay slot has nop where original packs a sw",
         _rule_beq_nop_fill,
         "delay-slot occupancy is SOURCE SHAPE (the fill_*_delay.txt allowlists are retired): place the body so the ROM's occupant is the fall-through (§3.6), funnel same-const returns through one label (§8.28), or a `volatile *` param the data model supports (§8.32)"),
    Rule("8.5", "blez/bgez/bltz/bgtz/branch-likely delay slot has nop",
         _rule_blez_nop_fill,
         "same as §8.4: source shape, not an allowlist (retired) — §3.6 placement / §8.28 shared label / §8.32 volatile the data model supports"),
    Rule("3.3 / 8.6", "branch-likely mnemonic mismatch (beq↔beql / bne↔bnel)",
         _rule_branch_likely_mnemonic,
         "park (§3.3) — ee-gcc 2.9 now usually picks bnel naturally for known-safe annul shapes; if not, see §8.6"),
    Rule("5.3", "gp_rel addiu vs daddiu (quick_diff false positive)",
         _rule_gp_rel_addiu_vs_daddiu,
         "commit — the bytes match the original ELF"),
    Rule("2.1", "missing `daddu $v1,$v0,$0` after jal",
         _rule_v1_daddu_after_jal,
         "route the call result through a second genuinely-read local (the dev's value-reuse shape), or the post-call `(x ^ y) == 0` compare that coalesces ret→v0 — REG()/KEEP_LIVE are banned crutches"),
    Rule("8.11", "addu operand order swap",
         _rule_swap_addu_to_rt,
         "keep the base register as the addu DESTINATION in C: compound update `base += idx*stride` (§2.3) or the `base = base - (-(prod))` spelling — the inline-asm addu spelling is retired (all 7 sites)"),
    Rule("5.2", "single addiu vs lui+ori for a 32-bit mask",
         _rule_unsigned_mask,
         "write the mask as an unsigned 32-bit literal (e.g. 0xFFFFFFC0u)"),
    Rule("4.2", "signed div/shift collapsed to movn",
         _rule_signed_shift_movn,
         "rewrite as (unsigned int)(signed >> 2) >> 2"),
    Rule("3.1", "sltu+movz bool collapse",
         _rule_sltu_movz_bool_collapse,
         "split null-chain returns via `goto fail/succ:` labels"),
    Rule("8.3", "ld $31 / daddu $2,$0,$0 epilogue swap",
         _rule_swap_zero_ret_ld_ra,
         "convert multiple `return 0;` paths to single `goto end; ... end: return 0;`"),
    Rule("8.12", "trailing nop after `j $31`",
         _rule_trailing_nop,
         "trailing-nop handling is always-on assembler parity now (quick_diff/compile_c strip + match_diff strip_trailing_align_nops); a residual here is a REAL size/padding diff — verify with ninja"),
    Rule("8.15", "FCC compare without trailing nop",
         _rule_fcc_compare_missing_nop,
         "the FCC-compare nop promotion is always-on assembler parity now (quick_diff/compile_c); a residual here is source shape around the compare — see §8.15"),
    Rule("2.7", "FP register letter swap ($fA ↔ $fB, otherwise identical)",
         _rule_fpr_letter_swap,
         "gcc picked a different free FP reg — a source-shape regalloc tie: "
         "reorder the float decl/store order (store order cascades regalloc), "
         "or free/occupy the original register via genuine value reuse. "
         "Register pins are banned."),
    Rule("8.22", "swc1 in jal delay slot where expected has addiu/lw",
         _rule_swc1_in_jal_delay,
         "make gcc fill the delay with the call-arg setup by SOURCE shape: move "
         "the unrelated store earlier / bind it to its dependent expression, "
         "or a `volatile` object the data model independently supports "
         "(§8.32). Empty-asm barriers are banned crutches."),
    Rule("5.9", "rodata lui+addiu materialized late next to jal",
         _rule_lui_addiu_late,
         "capture the global address into a local the code genuinely reads "
         "later (`T *p = D_X;` with real uses through p), or index the "
         "global DIRECTLY so %hi hoists early (§5.8/§5.10) — KEEP_LIVE "
         "is a banned crutch."),
    Rule("2.8", "alternating $v0/$v1 reload pattern vs single-reg built",
         _rule_alternating_reload_regs,
         "derive TWO pointer locals from DIFFERENT roots (dual-root address "
         "derivation defeats the gcse CSE that funnels every reload into one "
         "reg — §5.8), and alternate which local each access goes through. "
         "Register pins are banned crutches."),
    # --- taxonomy expansion (codegen-shape tags) ---------------------------
    Rule("regalloc-swap", "register-allocation swap (same op, one reg differs, recurring)",
         _rule_regalloc_swap,
         "a source-shape regalloc tie — REASSIGN the dead arg register the "
         "original reuses (`a0 = D[0];` param reuse), route the second "
         "constant/intermediate through an early temp, or swap store order "
         "(§2.3/§5.8). If it recurs across the whole function, check "
         "match_diff's `register_map` → decomp-convergence. Pins are banned."),
    Rule("fp-licm", "loop-invariant FP value kept in $f2x (lwc1) vs re-materialized (mtc1)",
         _rule_fp_licm,
         "gcc's FP loop-invariant hoist picked a different value to keep "
         "callee-saved. Do NOT force it with a `float thresh = ...` var (it "
         "regresses); this is usually permuter territory. §2.6 only if a single "
         "fresh FP load is in the wrong register."),
    Rule("delay-slot-occupant", "epilogue ld ra folded into an early-exit branch delay vs fall-through work",
         _rule_delay_slot_occupant,
         "gcc folded the epilogue `ld ra` into the early-exit branch delay where "
         "the original fills it with fall-through work. Reshape the guards "
         "(nested-if so the loop/work is the fall-through), or funnel the returns "
         "through one label (§8.3 C fix — the unfold_ra_delay allowlist is retired). "
         "Often permuter territory after a couple structure tries."),
    Rule("branch-direction", "opposite branch sense — body inline vs out-of-line",
         _rule_branch_direction,
         "flip the C structure so the body is the branch target the original "
         "uses: `if (cond) { body }` vs early `if (!cond) return;`, or an "
         "explicit `goto` (§3.x / body_out_of_line_branch_direction)."),
    Rule("frame-size", "prologue sp delta differs (missing callee-saved reg / hoist)",
         _rule_frame_size,
         "a far global reached via a CACHED pointer collapsed a callee-saved "
         "reg the original keeps; access it as a DIRECT indexed array `D_X[i]` "
         "so gcc hoists its %hi into $sN and the frame matches (§5.7 / "
         "far_global_direct_index_hoists_hi)."),
    Rule("5.7", "far in-TU global via gp_rel where original uses %hi/%lo",
         _rule_far_global_gp_rel,
         "asm-label alias: `extern T D_alias[] __asm__(\"D_real\");` and "
         "reference via the alias → %hi/%lo, not gp_rel (§5.7)."),
]


# ---------------------------------------------------------------------------
# Diff-pair extraction
# ---------------------------------------------------------------------------

def pairs_from_files(expected: Path, built: Path) -> list[DiffPair]:
    """Read both files line-by-line into a paired list. Lines that match
    are still included (rules may need both-sides-equal context to
    decide). For one-sided diffs the missing side is None."""
    elines = expected.read_text().splitlines()
    blines = built.read_text().splitlines()
    n = max(len(elines), len(blines))
    out: list[DiffPair] = []
    for i in range(n):
        e = elines[i] if i < len(elines) else None
        b = blines[i] if i < len(blines) else None
        out.append((e, b))
    return out


def pairs_from_text(expected: str, built: str) -> list[DiffPair]:
    elines = expected.splitlines()
    blines = built.splitlines()
    n = max(len(elines), len(blines))
    return [(elines[i] if i < len(elines) else None,
             blines[i] if i < len(blines) else None) for i in range(n)]


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------

def tag(pairs: list[DiffPair]) -> list[Rule]:
    """Return every rule that fires on the given diff pairs."""
    return [r for r in RULES if r.match(pairs)]


def format_hits(hits: list[Rule], prefix: str = "") -> str:
    if not hits:
        return ""
    lines = []
    for r in hits:
        lines.append(f"{prefix}[§{r.id}] {r.name}")
        lines.append(f"{prefix}        → {r.hint}")
        # Cookbook anchors — emit one per primary section id (a rule may
        # span multiple, e.g. "3.3 / 8.6"). markdown autolinks strip the
        # dot in section numbers.
        ids = [s.strip() for s in r.id.split("/")]
        anchors = ", ".join(f"COOKBOOK.md#{i.replace('.', '')}" for i in ids)
        lines.append(f"{prefix}        see {anchors}")
    return "\n".join(lines)


def main(argv: list[str]) -> int:
    if len(argv) != 3:
        print("usage: tag_diff.py <expected.txt> <built.txt>", file=sys.stderr)
        return 2
    expected, built = Path(argv[1]), Path(argv[2])
    if not expected.exists() or not built.exists():
        print(f"tag_diff: missing file", file=sys.stderr)
        return 1
    pairs = pairs_from_files(expected, built)
    hits = tag(pairs)
    if not hits:
        return 0
    print(format_hits(hits))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
