#!/usr/bin/env python3
"""
postprocess_v0_zero_in_bne_delay.py — lift `daddu $2,$0,$0` from the
epilogue into the preceding `bne $2,$0,$L`'s delay slot, in the same
function.

ee-gcc 2.9 with `-fno-schedule-insns` emits the return-value clear
(`daddu $2,$0,$0`) between `ld $31, OFF($sp)` and `ld $sN, OFF2($sp)`
in the epilogue. The original ICO codegen, however, schedules that
instruction into the delay slot of the early-exit branch (`bne $2,$0,
$L`) at the top of the function, leaving the epilogue as a clean
`ld $31; ld $sN; jr $31` sequence.

gas's reorder pass refuses to fill the bne delay slot with a daddu
that writes the bne's input register, even though MIPS semantics
guarantee the branch decision uses the pre-delay-slot value. We
therefore have to wrap the bne+daddu pair in an explicit
`.set noreorder/nomacro` block so gas accepts the manual fill.

Pattern (gcc-emitted, before this pass):

    \\tbne\\t$2,$0,$L_target
    \\t.set\\tnoreorder
    \\t.set\\tnomacro
    \\tb\\t$L_end
    \\t<delay-slot insn>
    \\t.set\\tmacro
    \\t.set\\treorder
    ... [body for the bne-taken side]
    $L_end:
    \\tld\\t$31, OFF($sp)
    \\tdaddu $2,$0,$0          <-- TO LIFT
    \\tld\\t$sN, OFF2($sp)
    ...

Becomes:

    \\t.set\\tnoreorder
    \\t.set\\tnomacro
    \\tbne\\t$2,$0,$L_target
    \\tdaddu $2,$0,$0          <-- LIFTED into bne delay slot
    \\tb\\t$L_end
    \\t<delay-slot insn>
    \\t.set\\tmacro
    \\t.set\\treorder
    ... [body]
    $L_end:
    \\tld\\t$31, OFF($sp)
    \\tld\\t$sN, OFF2($sp)
    ...

The pattern is tight on purpose: the daddu must be a `$2,$0,$0` (the
return-zero shape), it must sit between `ld $31` and `ld $sN`, and
the preceding bne must come right before a `.set noreorder/nomacro`
block — exactly the gcc shape under `-fno-schedule-insns`.

Per-file allowlist in config/v0_zero_in_bne_delay.txt. Idempotent.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


# Names that ee-gcc may emit for the SP register; ee-as later normalizes
# `$sp` to `$29` via a sed pass in tools/compile_c.sh, but this
# postprocess runs BEFORE that translation.
_SP = r"\$(?:29|sp)"
_RA = r"\$(?:31|ra)"

# ee-gcc emits `move $2,$0` for the return-value clear; tools/compile_c.sh
# sed-translates that to `daddu $2,$0,$0` AFTER this postprocess, so we
# accept both forms here.
_V0_ZERO = r"(?:daddu[ \t]+\$2,\$0,\$0|move[ \t]+\$2,\$0)"

# `bne $2,$0,$L<n>` (or `bnez $2,$L<n>`) followed immediately by a
# `.set noreorder/nomacro` block. Accept both `bne $R,$0,…` and the
# `bnez $R,…` shorthand gas accepts.
BNE_NOREORDER = re.compile(
    r"(?P<lead>[ \t]+)(?:bne[ \t]+\$2,\$0,|bnez[ \t]+\$2,)(?P<label>\$L\d+)\n"
    r"(?P<set_block_open>[ \t]+\.set[ \t]+noreorder\n[ \t]+\.set[ \t]+nomacro\n)"
)

# In the epilogue: ld $ra; daddu $2,$0,$0 (or move $2,$0); ld $sN.
EPILOGUE_DADDU = re.compile(
    r"([ \t]+ld[ \t]+" + _RA + r",\s*\d+\(" + _SP + r"\)\n)"
    r"([ \t]+" + _V0_ZERO + r"\n)"
    r"([ \t]+ld[ \t]+\$(?:1[6-9]|2[0-3]),\s*\d+\(" + _SP + r"\)\n)"
)


def patch(path: Path) -> bool:
    text = path.read_text()

    # Step 1: confirm both halves of the pattern exist.
    m_bne = BNE_NOREORDER.search(text)
    if not m_bne:
        return False
    m_ep = EPILOGUE_DADDU.search(text, m_bne.end())
    if not m_ep:
        return False

    # Step 2: remove the epilogue daddu line.
    new_epilogue = m_ep.group(1) + m_ep.group(3)
    text = text[: m_ep.start()] + new_epilogue + text[m_ep.end() :]

    # Step 3: rewrite the bne block — move the .set noreorder/nomacro
    # BEFORE the bne, and inject the return-value-zero move as the bne
    # delay-slot fill. Emit `move $2,$0` to mirror gcc's natural form;
    # tools/compile_c.sh's later sed converts it to `daddu $2,$0,$0`.
    m_bne = BNE_NOREORDER.search(text)
    if not m_bne:
        return False
    lead = m_bne.group("lead")
    label = m_bne.group("label")
    set_block_open = m_bne.group("set_block_open")
    replacement = (
        f"{set_block_open}"
        f"{lead}bne\t$2,$0,{label}\n"
        f"{lead}move\t$2,$0\n"
    )
    text = text[: m_bne.start()] + replacement + text[m_bne.end() :]

    path.write_text(text)
    return True


def listed(allowlist_path: Path, basename: str) -> bool:
    if not allowlist_path.exists():
        return False
    for line in allowlist_path.read_text().splitlines():
        s = line.strip()
        if s and not s.startswith("#") and s == basename:
            return True
    return False


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_v0_zero_in_bne_delay.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1

    repo_root = Path(__file__).resolve().parent.parent
    allowlist = repo_root / "config" / "v0_zero_in_bne_delay.txt"
    if not listed(allowlist, path.stem):
        return 0

    if patch(path):
        print(f"  v0-zero-in-bne-delay: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
