#!/usr/bin/env python3
"""tools/scope_pp.py — run a .s postprocess on only specific functions' blocks.

Several postprocesses in tools/compile_c.sh mutate the WHOLE compiled .s of a
coalesced TU, so one added for a single func also rewrites its siblings (the
collision class lint_postprocess_collisions.py flags). This wraps any such
postprocess so it touches only the `.ent <func>` … `.end <func>` block(s) named
on the TU's config line, leaving every sibling byte-identical.

    tools/scope_pp.py <s_file> <func1,func2,...> -- <tool> [args...]

The tool is invoked once per named func on a temp file holding just that
function's block (in place, the tool's last arg), and the result is spliced
back. Bytes are round-tripped via latin-1 so EUC-JP rodata elsewhere in the .s
is preserved exactly.
"""
from __future__ import annotations
import os
import re
import subprocess
import sys
import tempfile


def main(argv: list[str]) -> int:
    try:
        sep = argv.index("--")
    except ValueError:
        print("usage: scope_pp.py <s> <f1,f2,..> -- <tool> [args]", file=sys.stderr)
        return 2
    s_file = argv[1]
    funcs = [f for f in argv[2].split(",") if f]
    tool = argv[sep + 1:]
    if not tool:
        print("scope_pp.py: no tool given", file=sys.stderr)
        return 2

    def run(path: str) -> None:
        subprocess.run(tool + [path], check=True)

    if not funcs:                       # no scoping -> whole file
        run(s_file)
        return 0

    lines = open(s_file, encoding="latin-1").read().split("\n")
    for f in funcs:
        ent = re.compile(r"\.ent[ \t]+" + re.escape(f) + r"\b")
        end = re.compile(r"\.end[ \t]+" + re.escape(f) + r"\b")
        start = stop = None
        for i, l in enumerate(lines):
            if start is None and ent.search(l):
                start = i
            elif start is not None and end.search(l):
                stop = i
                break
        if start is None or stop is None:
            print(f"scope_pp.py: no .ent/.end block for {f} in {s_file}",
                  file=sys.stderr)
            continue
        tf = tempfile.NamedTemporaryFile("w", suffix=".s", delete=False,
                                         encoding="latin-1")
        tf.write("\n".join(lines[start:stop + 1]))
        tf.close()
        try:
            run(tf.name)
            new = open(tf.name, encoding="latin-1").read().split("\n")
        finally:
            os.unlink(tf.name)
        if new and new[-1] == "":        # trailing newline artifact
            new = new[:-1]
        lines[start:stop + 1] = new
    open(s_file, "w", encoding="latin-1").write("\n".join(lines))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
