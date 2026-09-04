#!/usr/bin/env python3
"""
tools/sweep.py — surgical single-pass match harness for coalesced TUs.

Replaces one INCLUDE_ASM(...) stub with a candidate C body (apply), or
restores the stub (revert), touching ONLY the lines for that one function.
Never uses git, never restores a whole-file backup -> safe against parallel
matching workers editing sibling functions in the same TU.

The inserted block is fenced with sentinel comments so revert is a surgical
text swap:

    /*SWEEP<func>*/
    <candidate C>
    /*SWEEP-END<func>*/

Usage:
    tools/sweep.py apply  <tu_stem> <func> <c_snippet_file>
    tools/sweep.py revert <tu_stem> <func>      # stub back, drop the block
    tools/sweep.py keep   <tu_stem> <func>      # drop sentinels, keep the C

<tu_stem> is the yaml stem, e.g. fumi/isys/obj_manager (file = <tu_stem>.c).
"""
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ico_version import detect_version, asm_root  # noqa: E402

# Splat's asm tree root for this target (yaml `asm_path`): asm/ on the retail
# branches (pal, us), asm/aug6/ on the prototype.
ASM_ROOT = asm_root(ROOT, detect_version(ROOT))


def stub_line(tu_stem, func):
    return f'INCLUDE_ASM("{ASM_ROOT}/nonmatchings/{tu_stem}", {func});'


def cfile(tu_stem):
    return ROOT / f"{tu_stem}.c"


def fence_re(func):
    return re.compile(
        r"/\*SWEEP" + re.escape(func) + r"\*/\n.*?/\*SWEEP-END"
        + re.escape(func) + r"\*/\n?",
        re.DOTALL,
    )


def main():
    if len(sys.argv) < 4:
        print(__doc__)
        sys.exit(2)
    cmd, tu_stem, func = sys.argv[1], sys.argv[2], sys.argv[3]
    f = cfile(tu_stem)
    text = f.read_text()
    stub = stub_line(tu_stem, func)

    if cmd == "apply":
        snippet = Path(sys.argv[4]).read_text().rstrip("\n")
        block = f"/*SWEEP{func}*/\n{snippet}\n/*SWEEP-END{func}*/"
        if stub not in text:
            print(f"ERROR: stub for {func} not found in {f}", file=sys.stderr)
            sys.exit(1)
        text = text.replace(stub, block, 1)
    elif cmd == "revert":
        text, n = fence_re(func).subn(stub + "\n", text)
        if not n:
            print(f"ERROR: no SWEEP block for {func} in {f}", file=sys.stderr)
            sys.exit(1)
    elif cmd == "keep":
        text = re.sub(r"/\*SWEEP-?(END)?" + re.escape(func) + r"\*/\n?", "", text)
    else:
        print(f"unknown cmd {cmd}", file=sys.stderr)
        sys.exit(2)

    f.write_text(text)


if __name__ == "__main__":
    main()
