#!/usr/bin/env python3
"""
tools/m2c_scaffold.py — generate a goto-CFG C scaffold from a splat .s via m2c.

The structural trace is the mechanical part of matching; this removes the agent
from it. It adapts splat's asm to what m2c (lib/m2c) expects, then invokes m2c:

  * strip the `/* fileoff vram hex */` comment prefixes splat emits,
  * rewrite `jr $31` -> `jr $ra` (m2c's arch_mips compares the return reg to
    Register("ra") BY NAME; `$31` is misread as a jump-table dispatch),
  * drop `.extern`/`nonmatching`/`.align` lines (keep `glabel`/`endlabel`),
  * run `m2c.py --target mipsel-gcc-c` context-free (raw `*(s32*)(p+0x..)`
    accesses — fine for a scaffold; refine to structs while matching).

m2c emits structured if/while C, not literal gotos — that's a fine starting
point; reshape it into the goto-CFG-mirror the cookbook recommends as you
match. This is a SCAFFOLD, not a match: it will not be byte-correct.

Usage:
    tools/m2c_scaffold.py <func_X>                 # resolve the .s by name
    tools/m2c_scaffold.py <asm_root>/.../func_X.s  # explicit .s path
    tools/m2c_scaffold.py <func_X> -o src/<TU>.scaffold.c
"""
from __future__ import annotations
import argparse
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
from ico_version import detect_version, asm_root  # noqa: E402

# splat's asm tree for this target (yaml `asm_path`): asm/ on the retail
# branches (pal, us), asm/aug6/ on the prototype.
ASM_ROOT = asm_root(ROOT, detect_version(ROOT))
M2C = ROOT / "lib" / "m2c" / "m2c.py"

_PREFIX = re.compile(r"/\*.*?\*/")           # /* fileoff vram hex */ (and any /* */)
_JR31 = re.compile(r"\bjr\s+\$31\b")
_DROP = re.compile(r"^\s*(\.extern|\.align|nonmatching|\.set|\.size|\.globl|\.global)\b")


def resolve_asm(arg: str) -> Path | None:
    p = Path(arg)
    if p.suffix == ".s" and p.exists():
        return p.resolve()
    # search the splat asm trees for func_X.s
    name = arg if arg.endswith(".s") else f"{arg}.s"
    for base in (f"{ASM_ROOT}/nonmatchings", f"{ASM_ROOT}/matchings"):
        hits = list((ROOT / base).rglob(name))
        if hits:
            return hits[0].resolve()
    return None


def adapt(text: str) -> str:
    out = []
    for line in text.splitlines():
        if _DROP.match(line):
            continue
        line = _PREFIX.sub("", line)
        line = _JR31.sub("jr $ra", line)
        if line.strip():
            out.append(line.rstrip())
    return "\n".join(out) + "\n"


def run_m2c(adapted: str) -> tuple[int, str, str]:
    with tempfile.NamedTemporaryFile("w", suffix=".s", delete=False) as f:
        f.write(adapted)
        path = f.name
    try:
        py = ROOT / ".venv" / "bin" / "python"
        py = str(py) if py.exists() else sys.executable
        proc = subprocess.run(
            [py, str(M2C), "--target", "mipsel-gcc-c", path],
            capture_output=True, text=True, cwd=str(ROOT),
        )
        return proc.returncode, proc.stdout, proc.stderr
    finally:
        Path(path).unlink(missing_ok=True)


def main() -> int:
    ap = argparse.ArgumentParser(description="m2c scaffold from a splat .s")
    ap.add_argument("target", help="func name or path to a .s file")
    ap.add_argument("-o", "--output", help="write scaffold here (default: stdout)")
    args = ap.parse_args()

    asm = resolve_asm(args.target)
    if asm is None:
        print(f"m2c_scaffold: could not resolve a .s for {args.target!r}", file=sys.stderr)
        return 3
    rc, out, err = run_m2c(adapt(asm.read_text()))
    header = (f"/* m2c scaffold from {asm.relative_to(ROOT)} (target mipsel-gcc-c, context-free).\n"
              f" * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */\n")
    body = header + out
    if rc != 0 or "Decompilation failure" in out:
        print(f"m2c_scaffold: m2c reported a problem:\n{err}\n{out}", file=sys.stderr)
        # still emit whatever it produced (often a partial scaffold) for review
    if args.output:
        Path(args.output).write_text(body)
        print(f"wrote {args.output} ({len(out.splitlines())} lines from m2c)", file=sys.stderr)
    else:
        sys.stdout.write(body)
    return 0 if rc == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
