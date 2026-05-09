#!/usr/bin/env python3
"""
postprocess_asm.py — apply post-split fixups to splat-emitted asm.

Splat 0.40.0 has a few known mis-emissions on the ICO ELF that we patch
here so the round-trip is byte-identical:

  1. .sdata ends mid-string. The .sdata section size is 0x22C6 (not 4-byte
     aligned), and splat rounds the last data symbol down to a .word, so
     the trailing two bytes ("E\0", completing the asciz "FALSE\0") at
     0x00633BC4 are dropped. We patch the .sdata.s tail to emit those
     two bytes.

Future R5900-mnemonic / VU-asm fixups would also live here.

Idempotent — run as part of `make setup` after `splat split`.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent

# (path, sentinel, replacement, reason)
SDATA_TAIL_FIX = (
    REPO_ROOT / "asm" / "data" / "cod" / "531900.sdata.s",
    re.compile(
        r"^(?P<head>dlabel D_00633BC0\n"
        r"\s*/\*\s*533BC0\s+00633BC0\s+46414C53\s*\*/\s*\.word\s+0x534C4146)\s*\n"
        r"(?P<tail>enddlabel D_00633BC0\b)",
        re.MULTILINE,
    ),
    # Replace the lone .word with: .word + 2-byte tail (".byte 0x45, 0x00").
    # GNU as accepts that combination cleanly inside a section.
    "{head}\n    /* 533BC4 00633BC4 4500     */ .byte 0x45, 0x00\n{tail}",
    "splat sdata-tail truncation (0x22C6 size, last 2 bytes dropped)",
)


def patch_sdata_tail() -> int:
    path, pat, repl, reason = SDATA_TAIL_FIX
    if not path.exists():
        return 0
    text = path.read_text()
    if "/* 533BC4 00633BC4" in text:
        return 0  # already patched
    m = pat.search(text)
    if m is None:
        # Splat output may have changed shape — surface this as a failure
        # so the round-trip mismatch doesn't get silently re-introduced.
        print(
            f"postprocess_asm: WARN — could not locate the splat-truncated "
            f"D_00633BC0 .word in {path.relative_to(REPO_ROOT)} "
            f"({reason!r}); .rom may not round-trip.",
            file=sys.stderr,
        )
        return 0
    new = text[: m.start()] + repl.format(head=m.group("head"), tail=m.group("tail")) + text[m.end():]
    path.write_text(new)
    return 1


_GPREL_RE = re.compile(
    r"\(([A-Za-z_][\w]*)\)\s*/\*\s*gp_rel:\s*\(\1\)\s*\*/"
)


def patch_gp_rel_per_function() -> int:
    """Rewrite splat per-function `(SYM) /* gp_rel: (SYM) */` to
    `%gp_rel(SYM)($gp) /* gp_rel: (SYM) */`.

    Splat 0.40.0 emits the bare-paren form for gp-relative loads/stores
    in per-function .s files (under asm/matchings/). With `.set noat`
    that expands to a $at-using lui/lo macro and fails to assemble.
    The %gp_rel form encodes to the original gp_rel instruction bytes
    and assembles cleanly with .set noat.

    Idempotent: skips lines already containing %gp_rel.
    """
    # Only patch asm/matchings/ — asm/nonmatchings/ files are pulled into
    # src/ via INCLUDE_ASM and assembled by ee-as 2.96, which accepts the
    # bare-paren form natively but rejects %gp_rel(SYM)($gp). Modern gas
    # (which assembles asm/matchings/ via the splat per-function path)
    # needs the %gp_rel rewrite.
    matchings = REPO_ROOT / "asm" / "matchings"
    if not matchings.exists():
        return 0
    changed = 0
    for path in matchings.rglob("*.s"):
        text = path.read_text()
        if "%gp_rel(" in text and " gp_rel: (" not in text:
            continue
        new = _GPREL_RE.sub(r"%gp_rel(\1)($gp) /* gp_rel: (\1) */", text)
        if new != text:
            path.write_text(new)
            changed += 1
    return changed


_VU_SPECIAL_RE = re.compile(
    r"(?<![A-Za-z0-9_$])(?<!\$)(ACC|Q|R|I)(?=[ \t,]|$)"
)


def patch_vu0_special_regs_per_function() -> int:
    """Rewrite splat-emitted bare `ACC`, `Q`, `R`, `I` operands to `$ACC`,
    `$Q`, `$R`, `$I`.

    Modern gas (binutils 2.44, including ps2dev's binutils-gdb fork) only
    accepts the dollar-prefixed form for the R5900 VU0 special regs. Splat
    0.40.0's matchings/ output emits them bare (the segment-level c.py
    correctly emits them with `$`, but codesubsegment.py:142 forces the
    bare form for `c` subsegments).

    Idempotent: the negative-lookbehind on `$` prevents double-prefix.
    """
    matchings = REPO_ROOT / "asm" / "matchings"
    if not matchings.exists():
        return 0
    changed = 0
    for path in matchings.rglob("*.s"):
        text = path.read_text()
        # Only touch lines containing a v* mnemonic or COP2 move
        # (cfc2/ctc2/qmfc2/qmtc2). This avoids any chance of clobbering
        # something else that happens to spell "ACC" or "Q".
        new_lines = []
        for line in text.splitlines(keepends=True):
            if re.search(r"\b(v[a-z]+(\.\w+)?|cfc2(\.ni)?|ctc2(\.ni)?|qmfc2(\.ni)?|qmtc2(\.ni)?)\b", line):
                line = _VU_SPECIAL_RE.sub(r"$\1", line)
            new_lines.append(line)
        new = "".join(new_lines)
        if new != text:
            path.write_text(new)
            changed += 1
    return changed


def main() -> int:
    changed = 0
    changed += patch_sdata_tail()
    changed += patch_gp_rel_per_function()
    changed += patch_vu0_special_regs_per_function()
    print(f"postprocess_asm: {changed} file(s) rewritten")
    return 0


if __name__ == "__main__":
    sys.exit(main())
