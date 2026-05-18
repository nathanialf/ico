#!/usr/bin/env python3
"""
postprocess_fill_blez_delay.py — wrap branch + intended-delay-slot
pair with `.set noreorder` so gas honours gcc's emission order.

ee-gcc 2.9 emits conditional branches in `.set reorder` mode with the
next instruction intended as the delay-slot fill, e.g.:

    bne   $3, $20, $L54
    lw    $2, 80($17)        ; gcc-intended delay-slot fill
    blez  $2, $L54
    move  $16, $0            ; gcc-intended delay-slot fill

Modern gas (both ee-as 2.10 and mips-linux-gnu-as) is conservative on
non-`jal` branches in `.set reorder` mode — it inserts a nop in the
delay slot rather than promoting the next instruction. This pass
rewrites the pattern to:

    .set noreorder
    bne   $3, $20, $L54
    lw    $2, 80($17)
    .set reorder

which forces gas to keep gcc's order verbatim. The `lw` ends up in the
delay slot, matching the original codegen.

Gated by config/fill_blez_delay.txt.

"Safe" = the next instruction is plain (no branch, no label),
doesn't write the branch comparison register, and isn't already
inside an explicit `.set noreorder` block.

Idempotent: if the surrounding directives are already present this
pass is a no-op.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


SAFE_MNEMONICS = {
    "move", "daddu", "addu", "addiu", "addi", "lw", "lh", "lb",
    "lbu", "lhu", "ld", "sll", "srl", "sra", "ori", "andi", "xori",
    "or", "and", "xor", "nor", "li", "lui", "subu", "neg", "negu",
    "sd", "sw", "sh", "sb",
}

BRANCH_RE = re.compile(
    r"^[ \t]*(blez|bgez|bltz|bgtz|bnel|beql|blezl|bgezl|bltzl|bgtzl)\b\s+(.*)$",
)
INSN_RE = re.compile(r"^[ \t]*([a-z][a-z0-9.]*)\b\s*(.*)$")


def operand_regs(text: str) -> list[str]:
    return re.findall(r"\$\w+", text)


def is_inside_noreorder(lines: list[str], idx: int) -> bool:
    """Walk backwards: are we inside an active `.set noreorder` block?"""
    for j in range(idx - 1, -1, -1):
        s = lines[j].strip()
        if s.startswith(".set"):
            if "noreorder" in s:
                return True
            if "reorder" in s:
                return False
        # Function boundary
        if s.endswith(":") and not s.startswith("."):
            return False
    return False


def patch(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    changed = False
    out: list[str] = []
    i = 0
    n = len(lines)
    while i < n:
        line = lines[i]
        m = BRANCH_RE.match(line.rstrip("\n"))
        if not m or i + 1 >= n:
            out.append(line)
            i += 1
            continue

        # Skip if already inside a noreorder block (gcc emitted explicitly)
        if is_inside_noreorder(lines, i):
            out.append(line)
            i += 1
            continue

        branch_op = m.group(1)
        branch_args = m.group(2).strip()

        # Examine the candidate "delay-slot" instruction
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
        if mnem not in SAFE_MNEMONICS:
            out.append(line)
            i += 1
            continue

        # Safety: cand shouldn't write a register read by the branch
        cand_args = ci.group(2)
        cand_dst = None
        cand_op_list = operand_regs(cand_args)
        if cand_op_list:
            cand_dst = cand_op_list[0]

        # Branch comparison registers — only the leading "$N" tokens
        # of branch_args before the label. Strip after first comma for
        # blez-family (single reg), two for beq/bne.
        # Conservatively take ALL $regs in branch_args.
        branch_regs = set(operand_regs(branch_args))
        if cand_dst and cand_dst in branch_regs:
            out.append(line)
            i += 1
            continue

        # Wrap with .set noreorder ... .set reorder
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
        sys.exit("usage: postprocess_fill_blez_delay.py <file.s>")
    patch(Path(sys.argv[1]))


if __name__ == "__main__":
    main()
