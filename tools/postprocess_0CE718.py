#!/usr/bin/env python3
"""postprocess_0CE718.py — func_001CE718 register/order fixes.

gcc emits:
    lw    $3,348($4)
    mtc1  $0,$f0
    lw    $2,2112($3)
    ...
    li.s  $f1,1.0
    l.s   $f0,48($3)
    nop
    c.lt.s $f1,$f0

Original uses $2 for the whole pointer chain and reorders the
li.s/l.s pair:
    lw    $2,348($4)
    mtc1  $0,$f0
    lw    $2,2112($2)
    ...
    l.s   $f0,48($3)
    li.s  $f1,1.0
    nop
    c.lt.s $f1,$f0
"""

from __future__ import annotations

import sys
from pathlib import Path


SRC_PROLOGUE = """\
\tlw\t$3,348($4)
\tmtc1\t$0,$f0
\tlw\t$2,2112($3)
"""

DST_PROLOGUE = """\
\tlw\t$2,348($4)
\tmtc1\t$0,$f0
\tlw\t$2,2112($2)
"""


SRC_BODY = """\
$L3:
 #APP
 #NO_APP
\tli.s\t$f1,1.00000000000000000000e0
\tl.s\t$f0,48($3)
\t#nop
\tc.lt.s\t$f1,$f0
\t#nop
"""

DST_BODY = """\
$L3:
\tl.s\t$f0,48($3)
 #APP
 #NO_APP
\tli.s\t$f1,1.00000000000000000000e0
\t#nop
\tc.lt.s\t$f1,$f0
\tnop
"""


def patch(path: Path) -> bool:
    text = path.read_text()
    new = text
    if SRC_PROLOGUE in new:
        new = new.replace(SRC_PROLOGUE, DST_PROLOGUE, 1)
    if SRC_BODY in new:
        new = new.replace(SRC_BODY, DST_BODY, 1)
    if new == text:
        return False
    path.write_text(new)
    print(f"  0CE718: rewrote {path}")
    return True


def main(argv):
    if len(argv) != 2:
        print("usage: postprocess_0CE718.py <file.s>", file=sys.stderr)
        return 2
    path = Path(argv[1])
    if not path.exists():
        return 0
    patch(path)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
