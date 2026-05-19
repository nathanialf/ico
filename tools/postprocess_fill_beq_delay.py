#!/usr/bin/env python3
"""
postprocess_fill_beq_delay.py — wrap a `beq`/`bne` + intended-delay-slot
pair with `.set noreorder` so gas honours gcc's emission order.

Sibling of postprocess_fill_blez_delay.py, but for the plain `beq`/`bne`
families. §8.5 deliberately EXCLUDES `beq`/`bne` because most original
ICO codegen left those delay slots unfilled. This pass covers the
opposite case — a specific function where the original ICO codegen DID
fill the `beq`/`bne` delay slot, and ee-as 2.10's conservative reorder
keeps inserting a nop instead.

Pattern (gcc-emitted under `.set reorder`):

    beq   $2, $0, $L5
    sw    $2, 24($3)        ; gcc-intended delay-slot fill

ee-as output (without postprocess):

    beq   $2, $0, $L5
    nop                     ; gas refused to fill
    sw    $2, 24($3)

After this pass:

    .set noreorder
    beq   $2, $0, $L5
    sw    $2, 24($3)        ; gas forced to emit verbatim → in delay slot
    .set reorder

Stores are always delay-slot-safe relative to the branch's compare
registers because a `sw`/`sd`/etc. doesn't write a GPR — the source
operand is READ before the branch resolves.

Gated by per-file allowlist in config/fill_beq_delay.txt.

Idempotent.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


# Mnemonics that are always safe to schedule into a `beq`/`bne` delay
# slot regardless of register operands: stores (no GPR write), and
# common single-cycle ops whose destination isn't reused by the branch.
# Stores are a separate set because they have NO destination GPR.
STORE_MNEMONICS = {"sw", "sh", "sb", "sd", "swc1", "sdc1", "sq"}
SAFE_NONSTORE = {
    "move", "daddu", "addu", "addiu", "addi", "lw", "lh", "lb",
    "lbu", "lhu", "ld", "sll", "srl", "sra", "ori", "andi", "xori",
    "or", "and", "xor", "nor", "li", "lui", "subu", "neg", "negu",
    "lwc1", "ldc1",
}

# beq, bne, beqz, bnez. beql/bnel are handled by fill_blez_delay.
BRANCH_RE = re.compile(
    r"^[ \t]*(beq|bne|beqz|bnez)\b\s+(.*)$",
)
INSN_RE = re.compile(r"^[ \t]*([a-z][a-z0-9.]*)\b\s*(.*)$")


def operand_regs(text: str) -> list[str]:
    return re.findall(r"\$\w+", text)


def is_inside_noreorder(lines: list[str], idx: int) -> bool:
    for j in range(idx - 1, -1, -1):
        s = lines[j].strip()
        if s.startswith(".set"):
            if "noreorder" in s:
                return True
            if "reorder" in s:
                return False
        if s.endswith(":") and not s.startswith("."):
            return False
    return False


def patch(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    out: list[str] = []
    changed = False
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        m = BRANCH_RE.match(line.rstrip("\n"))
        if not m or i + 1 >= n:
            out.append(line)
            i += 1
            continue
        if is_inside_noreorder(lines, i):
            out.append(line)
            i += 1
            continue

        cand_line = lines[i + 1].rstrip("\n")
        cand_stripped = cand_line.strip()
        if not cand_stripped or cand_stripped.endswith(":"):
            out.append(line)
            i += 1
            continue
        if cand_stripped.startswith(("#", ".")):
            out.append(line)
            i += 1
            continue

        ci = INSN_RE.match(cand_line)
        if not ci:
            out.append(line)
            i += 1
            continue
        mnem = ci.group(1)
        is_store = mnem in STORE_MNEMONICS
        if mnem not in SAFE_NONSTORE and not is_store:
            out.append(line)
            i += 1
            continue

        # For non-store insns, refuse if cand writes a reg the branch reads
        # (lw $X, ...; beq $X, ...). Stores skip this since they don't
        # write a GPR — the source reg is READ before the branch fires.
        if not is_store:
            cand_args = ci.group(2)
            cand_op_list = operand_regs(cand_args)
            cand_dst = cand_op_list[0] if cand_op_list else None
            branch_regs = set(operand_regs(m.group(2)))
            if cand_dst and cand_dst in branch_regs:
                out.append(line)
                i += 1
                continue

        lead = re.match(r"^([ \t]*)", line).group(1) or "\t"
        out.append(f"{lead}.set\tnoreorder\n")
        out.append(line)
        out.append(lines[i + 1])
        out.append(f"{lead}.set\treorder\n")
        changed = True
        i += 2

    if changed:
        path.write_text("".join(out))
    return changed


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_fill_beq_delay.py <file.s>")
    patch(Path(sys.argv[1]))


if __name__ == "__main__":
    main()
