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
  - hint         — one-line fix suggestion (e.g. "add to config/X.txt")

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
    built lacks the dead copy → §2.1 KEEP_LIVE_V1."""
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


RULES: list[Rule] = [
    Rule("8.21", "beq/bne delay slot has nop where original packs a sw",
         _rule_beq_nop_fill,
         "add basename to config/fill_beq_delay.txt"),
    Rule("8.5", "blez/bgez/bltz/bgtz/branch-likely delay slot has nop",
         _rule_blez_nop_fill,
         "add basename to config/fill_blez_delay.txt"),
    Rule("3.3 / 8.6", "branch-likely mnemonic mismatch (beq↔beql / bne↔bnel)",
         _rule_branch_likely_mnemonic,
         "park (§3.3) OR force via config/bne_to_bnel.txt (§8.6)"),
    Rule("5.3", "gp_rel addiu vs daddiu (quick_diff false positive)",
         _rule_gp_rel_addiu_vs_daddiu,
         "commit — the bytes match the original ELF"),
    Rule("2.1", "missing `daddu $v1,$v0,$0` after jal",
         _rule_v1_daddu_after_jal,
         "REG(\"$3\") + KEEP_LIVE(q) per §2.1"),
    Rule("8.11", "addu operand order swap",
         _rule_swap_addu_to_rt,
         "add func to config/swap_addu_to_rt.txt or swap_addu_operands.txt"),
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
         "add file_off to config/swap_zero_ret_ld_ra.txt"),
    Rule("8.12", "trailing nop after `j $31`",
         _rule_trailing_nop,
         "add basename to config/no_trailing_nop.txt"),
    Rule("8.15", "FCC compare without trailing nop",
         _rule_fcc_compare_missing_nop,
         "add basename to config/fcc_nop.txt"),
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
