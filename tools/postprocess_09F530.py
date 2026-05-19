#!/usr/bin/env python3
"""postprocess_09F530.py — fold gcc's `la $r, SYM; ldl/ldr` into the
gp-relative `ldl/ldr ..., %gp_rel(SYM[+N])($gp)` form.

For func_0019F530's specific shape:

    la $6, D_006323C0
    ldl $3, 7($6)
    ldr $3, 0($6)

becomes:

    ldl $3, %gp_rel(D_006323C7)($28)
    ldr $3, %gp_rel(D_006323C0)($28)
"""

from __future__ import annotations

import re
import sys
from pathlib import Path


SRC = """\
\tla\t$6,D_006323C0
\tldl\t$3,7($6)
\tldr\t$3,0($6)
"""

DST = """\
\tldl\t$3,%gp_rel(D_006323C7)($28)
\tldr\t$3,%gp_rel(D_006323C0)($28)
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    if SRC not in text:
        return False
    new = text.replace(SRC, DST, 1)
    path.write_text(new)
    print(f"  09F530: la→gp_rel ldl/ldr on {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_09F530.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
