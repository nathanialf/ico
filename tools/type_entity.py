#!/usr/bin/env python3
"""type_entity.py — verified auto-conversion of GObj entity-hierarchy accesses.

Rewrites the common, provably-byte-identical `*(T*)(self + 0x15C)` idioms in
matched C to the shared `GObj`/`Sub15C` struct members (include/ico/types.h),
then COMPILES + match_diff-verifies each file and keeps the change only if the
file still matches rc0 — otherwise reverts that file. So a bad rewrite can
never land: the SHA-1 byte-match is the backstop.

Scope (single-level self->0x15C sub-object, which dominates the cod files):
  *(T *)(*(C **)(X + 0x15C) + N)   ->  ((GObj*)(X))->p_15C->f_N   (field)
  *(C **)(X + 0x15C) + N           ->  (char*)((GObj*)(X))->p_15C + N
  *(int *)(X + 0x15C) + N          ->  (int)((GObj*)(X))->p_15C + N
  *(C **)(X + 0x15C)               ->  ((GObj*)(X))->p_15C
It deliberately skips the `self[0x15C/4]` int-array idiom, REG-pinned locals,
and deeper chains — those it leaves for hand work (logged).

Usage:
  tools/type_entity.py --collect           # pass 1: print needed Sub15C fields
  tools/type_entity.py --apply [files...]  # pass 2: rewrite + verify + keep/revert
"""
from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
HEADER = ROOT / "include" / "ico" / "types.h"

# a "self" expression: an identifier, optionally wrapped in a single C cast.
SELF = r"(?:\([^()]*\)\s*)?[A-Za-z_]\w*"
PTRC = r"(?:char|int|void|short|float|unsigned char|unsigned int)"
HEX = r"0x[0-9A-Fa-f]+"

# field width from the outer cast type
WIDTH = {"char": 1, "unsigned char": 1, "short": 2, "unsigned short": 2,
         "int": 4, "unsigned int": 4, "void": 4, "float": 4, "long long": 8}


def field_name(off: int) -> str:
    return f"f_{off:X}"


def transforms(text: str, fields: set):
    """Apply the 0x15C transforms to `text`; record Sub15C (off,width) in
    `fields`. Returns rewritten text."""

    def rec(off, width):
        fields.add((off, width))

    # 1) field access: *(T *)(*(C **)(X + 0x15C) + N)
    def f1(m):
        t, x, off = m.group("t"), m.group("x"), int(m.group("off"), 16)
        rec(off, WIDTH.get(t.strip(), 4))
        return f"((GObj *)({x}))->p_15C->{field_name(off)}"
    text = re.sub(
        rf"\*\(\s*(?P<t>{PTRC})\s*\*\)\(\s*\*\(\s*{PTRC}\s*\*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x15C\s*\)\s*\+\s*(?P<off>{HEX})\s*\)",
        f1, text)

    # 2) pointer + N  ->  (char*)(...)->p_15C + N
    text = re.sub(
        rf"\*\(\s*{PTRC}\s*\*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x15C\s*\)\s*\+\s*(?P<off>{HEX})",
        lambda m: f"(char *)((GObj *)({m.group('x')}))->p_15C + {m.group('off')}",
        text)

    # 3) pointer-as-int + N  ->  (int)(...)->p_15C + N
    text = re.sub(
        rf"\*\(\s*int\s*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x15C\s*\)\s*\+\s*(?P<off>{HEX})",
        lambda m: f"(int)((GObj *)({m.group('x')}))->p_15C + {m.group('off')}",
        text)

    # 4) bare pointer load  *(C **)(X + 0x15C)  ->  (...)->p_15C
    text = re.sub(
        rf"\*\(\s*{PTRC}\s*\*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x15C\s*\)",
        lambda m: f"((GObj *)({m.group('x')}))->p_15C",
        text)

    return text


def gen_sub15c_fields(all_fields: set) -> str:
    """Emit the Sub15C field list (offset-ordered, auto-padded). Keeps the
    known p_800/p_24-style pointer fields handled in the static header; here we
    only emit scalar f_<off> members the converter discovered."""
    # widest access wins; drop fields inside a wider field's span
    by_off = {}
    for off, w in sorted(all_fields):
        if off in by_off:
            by_off[off] = max(by_off[off], w)
        else:
            by_off[off] = w
    return by_off


def find_targets():
    out = []
    for p in sorted(ROOT.glob("src/**/*.c")):
        if p.name.endswith("_data.c"):
            continue
        try:
            t = p.read_text(errors="replace")
        except OSError:
            continue
        if "0x15C" in t and "+ 0x15C" in t:
            out.append(p)
    return out


def tu_name(path: Path) -> str:
    # quick_diff TU name = path relative to src/, no extension
    return str(path.relative_to(ROOT / "src")).removesuffix(".c")


def verify(path: Path) -> bool:
    """match_diff every func defined in this file; True if all rc0."""
    tu = tu_name(path)
    funcs = re.findall(r"^\s*(?:[A-Za-z_][\w \*]*?)\b(func_[0-9A-Fa-f]+)\s*\(",
                       path.read_text(errors="replace"), re.M)
    funcs = [f for f in dict.fromkeys(funcs)]
    if not funcs:
        return True
    py = str(ROOT / ".venv" / "bin" / "python")
    for fn in funcs:
        r = subprocess.run([py, str(ROOT / "tools" / "match_diff.py"),
                            "--count", tu, fn], capture_output=True, text=True,
                           cwd=str(ROOT))
        if r.stdout.strip() != "0":
            return False
    return True


def ensure_include(text: str) -> str:
    if 'ico/types.h' in text:
        return text
    m = re.search(r'#include "include_asm.h"\n', text)
    if m:
        return text[:m.end()] + '#include "ico/types.h"\n' + text[m.end():]
    # else put after the first #include, or at top after the leading comment
    m = re.search(r'(#include [^\n]*\n)', text)
    if m:
        return text[:m.end()] + '#include "ico/types.h"\n' + text[m.end():]
    return '#include "ico/types.h"\n' + text


def main():
    args = sys.argv[1:]
    targets = find_targets()
    if args and args[0] == "--collect":
        fields = set()
        for p in targets:
            transforms(p.read_text(errors="replace"), fields)
        for off, w in sorted(gen_sub15c_fields(fields).items()):
            print(f"  Sub15C 0x{off:X} (w{w})")
        print(f"{len(targets)} files, {len(gen_sub15c_fields(fields))} distinct Sub15C fields")
        return 0

    # --apply
    explicit = [ROOT / a for a in args if a != "--apply"]
    files = explicit or targets
    converted, skipped, reverted = [], [], []
    for p in files:
        orig = p.read_text(errors="replace")
        fields = set()
        new = transforms(orig, fields)
        if new == orig:
            skipped.append(p.name)
            continue
        new = ensure_include(new)
        p.write_text(new)
        if verify(p):
            converted.append((p, fields))
        else:
            p.write_text(orig)
            reverted.append(p.name)
    print(f"converted: {len(converted)}  reverted(unsafe): {len(reverted)}  "
          f"unchanged: {len(skipped)}")
    if reverted:
        print("  reverted:", " ".join(reverted[:30]))
    # report the union of fields the kept conversions need
    allf = set()
    for _p, fs in converted:
        allf |= fs
    if allf:
        print("Sub15C fields needed by kept conversions:")
        for off, w in sorted(gen_sub15c_fields(allf).items()):
            print(f"  0x{off:X} w{w}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
