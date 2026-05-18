#!/usr/bin/env python3
"""
postprocess_early_epilogue_restore.py — pull `ld $31`/`ld $16` saves
earlier in the epilogue when gcc places them too late.

ee-gcc 2.9 emits its epilogue restores wherever its scheduler thinks
they fit, often LATE — after the last buf-store and even interleaved
between trailing volatile stores. The original ICO codegen schedules
some restores EARLIER, so the trailing volatile stores form an
uninterrupted run.

This pass detects the pattern (in the gcc-emitted .s, before gas
reorder):

    sw $0, OFF1($3)
    s.s $fX, OFF2($3)
    [#APP / #NO_APP]            (optional, e.g. KEEP_LIVE barrier)
    lw $R, OFF3($S)
    ld $31, OFF4($sp)
    lw $3, OFF5($R)
    ld $S, OFF6($sp)
    [volatile] s.s $fY, OFF($3)
    [volatile] s.s $fY, OFF($3)
    ld $L, OFF7($sp)            (late restore to be pulled)
    [volatile] s.s $fY, OFF($3)

and reorders to put `ld $31` AND the late `ld $L` between `sw $0`
and `s.s $fX` so the trailing volatile-store run is uninterrupted.

Gated by config/early_epilogue_restore.txt.

Idempotent.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


SW_LINE = re.compile(r"^(?P<lead>[ \t]*)sw[ \t]+\$0,\s*\d+\(\$3\)\s*$")
SS_LINE = re.compile(r"^[ \t]*s\.s[ \t]+\$f\d+,\s*\d+\(\$3\)\s*$")
LD_RA   = re.compile(r"^(?P<lead>[ \t]*)ld[ \t]+\$31,\s*\d+\(\$sp\)\s*$")
LD_SREG = re.compile(r"^(?P<lead>[ \t]*)ld[ \t]+\$(?P<r>1[6-9]|2[0-3]),\s*\d+\(\$sp\)\s*$")


def patch(path: Path) -> bool:
    lines = path.read_text().splitlines(keepends=True)
    out = list(lines)
    changed = False

    n = len(out)
    for i in range(n - 2):
        if not SW_LINE.match(out[i]):
            continue
        if not SS_LINE.match(out[i + 1]):
            continue

        # Find the late ld $31 (must appear before any later 'jr/j $31')
        ra_idx = -1
        for j in range(i + 2, min(i + 30, n)):
            if LD_RA.match(out[j]):
                ra_idx = j
                break
            if re.match(r"^[ \t]*j(r|al)?[ \t]+\$31", out[j]):
                break
        if ra_idx < 0:
            continue

        # Find the LATEST ld $16-$23 — one that's interleaved with
        # volatile float stores or trailing right before jr. This is
        # the "stray late restore" we want to pull forward.
        late_idx = -1
        for j in range(ra_idx + 1, min(ra_idx + 40, n)):
            m = LD_SREG.match(out[j])
            if m:
                late_idx = j  # keep last match, not first
            if re.match(r"^[ \t]*j(r|al)?[ \t]+\$31", out[j]):
                break
        if late_idx < 0:
            continue

        # Skip the trivial-adjacent case where the late ld is already
        # right after ld $31 (already in the right place).
        if late_idx == ra_idx + 1:
            continue

        # Lift those two lines to between out[i] (sw) and out[i+1] (s.s)
        ra_line = out[ra_idx]
        late_line = out[late_idx]
        # Remove in reverse order
        del out[late_idx]
        del out[ra_idx]
        # Insert: out[i+1] becomes ra_line, then late_line, then original s.s
        out.insert(i + 1, ra_line)
        out.insert(i + 2, late_line)
        changed = True

        # Secondary fix: after the lifts, the surviving `ld $S, OFF($sp)`
        # restore for the second saved-reg ($17) often follows `lw $3, OFF($X)`
        # which has a load-use hazard on $X. gas-reorder fills the hazard
        # slot only if the independent restore is BEFORE the lw $3 in the
        # .s, so swap them.
        lw_x_idx = -1
        ld_s_idx = -1
        for j in range(i + 3, min(i + 30, len(out))):
            if re.match(r"^[ \t]*lw[ \t]+\$\d+,\s*\d+\(\$\d+\)\s*$", out[j]):
                # find a subsequent lw $3 (p_840 final) then ld $S
                pass
            m_lw3 = re.match(r"^[ \t]*lw[ \t]+\$3,\s*\d+\(\$\d+\)\s*$", out[j])
            if m_lw3:
                lw_x_idx = j
                # look for the next ld $S right after
                if j + 1 < len(out):
                    if LD_SREG.match(out[j + 1]):
                        ld_s_idx = j + 1
                break
            if re.match(r"^[ \t]*j(r|al)?[ \t]+\$31", out[j]):
                break
        if lw_x_idx >= 0 and ld_s_idx == lw_x_idx + 1:
            # Swap them
            out[lw_x_idx], out[ld_s_idx] = out[ld_s_idx], out[lw_x_idx]

        break  # one shot

    if changed:
        path.write_text("".join(out))
    return changed


def main():
    if len(sys.argv) != 2:
        sys.exit("usage: postprocess_early_epilogue_restore.py <file.s>")
    patch(Path(sys.argv[1]))


if __name__ == "__main__":
    main()
