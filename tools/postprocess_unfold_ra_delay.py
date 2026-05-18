#!/usr/bin/env python3
"""
postprocess_unfold_ra_delay.py — un-fold gcc's `ld $31` from a beq
early-exit delay slot back into the shared epilogue.

ee-gcc 2.9's reorg pass fills early-exit branch delay slots with the
epilogue's `ld $31, OFF($sp)`, then re-targets the branch ONE
instruction past where it would have landed.  Pattern:

    .set noreorder
    .set nomacro
        beq    $X, $0, $L_late      # branches PAST the ld $31
        ld     $31, OFF($sp)        # delay slot, folded from epilogue
    .set macro
    .set reorder
    ...
    $L_early:
        ld     $31, OFF($sp)        # original epilogue start
    $L_late:
        ld     $17, ...
        ld     $16, ...
        j      $31
        addu   $sp, $sp, ...

Some original ICO codegen does NOT do this fold — it places a
zero-register move (e.g. `daddu $16, $0, $0` for the loop induction
variable) in the delay slot and routes the branch to the FULL
epilogue:

    beq    $X, $0, $L_early
    daddu  $16, $0, $0
    ...
    $L_early:
        ld $31, OFF($sp)            # branch lands here
        ld $17, ...                  # mine: branch lands here instead

This postprocess undoes the fold:
  1) Find `beq <reg>, $0, $L_late\\n  ld $31, NN($sp)` in a .set
     noreorder block, where $L_late immediately follows a label
     $L_early whose first instruction is `ld $31, NN($sp)`.
  2) Locate a `daddu $Y, $0, $0` elsewhere in the same function (gcc
     emits one for the OTHER early-exit branch with the same i=0
     init); reuse $Y.
  3) Replace the `ld $31, NN($sp)` in delay slot with `daddu $Y, $0, $0`.
  4) Redirect the beq target from $L_late to $L_early.

Idempotent: only fires when the input pattern matches, never when the
output pattern is already present.

Per-file allowlist in config/unfold_ra_delay.txt.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

# Matches the entire function (from .ent to .end) so we can search
# within a single function only.
FUNC_PATTERN = re.compile(
    r"(\.ent\s+(\w+)\n.*?\.end\s+\2\n)",
    re.DOTALL,
)

# beq with $L_late target + ld $31 fold in delay slot
BEQ_FOLD_PATTERN = re.compile(
    r"([ \t]*\.set\s+noreorder\s*\n"
    r"[ \t]*\.set\s+nomacro\s*\n"
    r"[ \t]*)(beq[ \t]+\$\d+,\s*\$0,\s*\$L\d+)\s*\n"
    r"[ \t]*ld[ \t]+\$31,\s*(\d+)\(\$(?:29|sp)\)\s*\n"
    r"([ \t]*\.set\s+macro\s*\n[ \t]*\.set\s+reorder)",
)

# Label followed by `ld $31, NN($29)` and then another label
EPILOGUE_PAIR_PATTERN = re.compile(
    r"(\$L\d+):\s*\n[ \t]*ld[ \t]+\$31,\s*(\d+)\(\$(?:29|sp)\)\s*\n(\$L\d+):"
)

# Any zero-init move for the loop induction var — used to find $Y.
# ee-gcc emits `move $Y, $0` (later sed-translated to daddu); accept both.
ZERO_INIT_PATTERN = re.compile(
    r"(?:daddu\s+\$(\d+)\s*,\s*\$0\s*,\s*\$0|move\s+\$(\d+)\s*,\s*\$0)\b"
)


def patch_function(body: str) -> tuple[str, bool]:
    """Return (new_body, changed?) for one function body."""

    # Find an existing zero-init for the loop variable elsewhere in
    # this function (e.g. delay slot of the second early-exit).  ee-gcc
    # emits `move $Y, $0`; sed later rewrites it to `daddu $Y, $0, $0`.
    # We run BEFORE the sed pass, so accept either form to find $Y.
    daddu_match = ZERO_INIT_PATTERN.search(body)
    if not daddu_match:
        return body, False
    reg_num = daddu_match.group(1) or daddu_match.group(2)

    # Find the beq+fold pattern.
    beq_match = BEQ_FOLD_PATTERN.search(body)
    if not beq_match:
        return body, False

    beq_insn = beq_match.group(2)  # "beq $2, $0, $L20"
    ra_offset = beq_match.group(3)
    indent = beq_match.group(1)
    set_macro = beq_match.group(4)

    # Parse the beq's target label.
    target_match = re.search(r"\$L\d+", beq_insn)
    if not target_match:
        return body, False
    late_label = target_match.group(0)

    # Find $L_early: ld $31, NN($29); $L_late: in the function.
    # The ld $31 offset must match the folded one.
    for ep in EPILOGUE_PAIR_PATTERN.finditer(body):
        early_label, ld_off, found_late = ep.group(1), ep.group(2), ep.group(3)
        if found_late == late_label and ld_off == ra_offset:
            # Build replacement: redirect beq to $L_early, replace
            # delay slot ld $31 with daddu $reg_num, $0, $0.
            new_beq = beq_insn.replace(late_label, early_label)
            indent_inner = "\t"  # gcc emits with tab indent
            # Emit `move $reg, $0` here so the later sed-rewrite to
            # `daddu $reg, $0, $0` happens consistently with the rest
            # of the file.
            replacement = (
                f"{indent}{new_beq}\n"
                f"{indent_inner}move\t${reg_num},$0\n"
                f"{set_macro}"
            )
            new_body = body[: beq_match.start()] + replacement + body[beq_match.end() :]
            return new_body, True

    return body, False


def patch(path: Path) -> bool:
    text = path.read_text()
    changed_any = False
    out_parts: list[str] = []
    pos = 0

    for fm in FUNC_PATTERN.finditer(text):
        out_parts.append(text[pos : fm.start()])
        body = fm.group(0)
        new_body, changed = patch_function(body)
        out_parts.append(new_body)
        pos = fm.end()
        if changed:
            changed_any = True

    out_parts.append(text[pos:])
    if changed_any:
        path.write_text("".join(out_parts))
    return changed_any


def listed(allowlist_path: Path, basename: str) -> bool:
    if not allowlist_path.exists():
        return False
    for line in allowlist_path.read_text().splitlines():
        stripped = line.strip()
        if stripped and not stripped.startswith("#") and stripped == basename:
            return True
    return False


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_unfold_ra_delay.py <path-to.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        print(f"file not found: {path}", file=sys.stderr)
        return 1

    repo_root = Path(__file__).resolve().parent.parent
    allowlist = repo_root / "config" / "unfold_ra_delay.txt"
    base = path.stem  # e.g. "weapon" for build/src/weapon.s
    if not listed(allowlist, base):
        return 0

    patched = patch(path)
    if patched:
        print(f"  unfold-ra-delay: patched {path}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
