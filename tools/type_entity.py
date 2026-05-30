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

    def rec(struct, off, width):
        fields.add((struct, off, width))

    # 1) field access: *(T *)(*(C **)(X + 0x15C) + N)
    def f1(m):
        t, x, off = m.group("t"), m.group("x"), int(m.group("off"), 16)
        rec("Sub15C", off, WIDTH.get(t.strip(), 4))
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

    # 5) int-array idiom field:  *(int*)( (T*)VAR[0x15C/4] + N )  isn't common;
    #    handle  (T *)VAR[0x15C / 4]  ->  (T *)((GObj*)(VAR))->p_15C
    text = re.sub(
        rf"\(\s*(?P<t>{PTRC})\s*\*\)\s*(?P<x>[A-Za-z_]\w*)\[\s*0x15C\s*/\s*4\s*\]",
        lambda m: f"({m.group('t')} *)((GObj *)({m.group('x')}))->p_15C",
        text)
    # 6) bare int-array value:  VAR[0x15C / 4]  ->  (int)((GObj*)(VAR))->p_15C
    text = re.sub(
        rf"(?<![.\w])(?P<x>[A-Za-z_]\w*)\[\s*0x15C\s*/\s*4\s*\]",
        lambda m: f"(int)((GObj *)({m.group('x')}))->p_15C",
        text)
    # 6b) bare pointer-as-int load (no +N; runs after #3):
    #     *(int *)(X + 0x15C)  ->  (int)((GObj*)(X))->p_15C
    text = re.sub(
        rf"\*\(\s*int\s*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x15C\s*\)",
        lambda m: f"(int)((GObj *)({m.group('x')}))->p_15C",
        text)

    # ---- 0x800 level: Sub15C -> p_800 -> Obj800 (X is the sub pointer) ----
    def f7(m):
        t, x, off = m.group("t"), m.group("x"), int(m.group("off"), 16)
        rec("Obj800", off, WIDTH.get(t.strip(), 4))
        return f"((Sub15C *)({x}))->p_800->{field_name(off)}"
    text = re.sub(
        rf"\*\(\s*(?P<t>{PTRC})\s*\*\)\(\s*\*\(\s*{PTRC}\s*\*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x800\s*\)\s*\+\s*(?P<off>{HEX})\s*\)",
        f7, text)
    text = re.sub(
        rf"\*\(\s*{PTRC}\s*\*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x800\s*\)\s*\+\s*(?P<off>{HEX})",
        lambda m: f"(char *)((Sub15C *)({m.group('x')}))->p_800 + {m.group('off')}",
        text)
    text = re.sub(
        rf"\*\(\s*int\s*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x800\s*\)\s*\+\s*(?P<off>{HEX})",
        lambda m: f"(int)((Sub15C *)({m.group('x')}))->p_800 + {m.group('off')}",
        text)
    text = re.sub(
        rf"\*\(\s*{PTRC}\s*\*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x800\s*\)",
        lambda m: f"((Sub15C *)({m.group('x')}))->p_800",
        text)
    text = re.sub(
        rf"\(\s*(?P<t>{PTRC})\s*\*\)\s*(?P<x>[A-Za-z_]\w*)\[\s*0x800\s*/\s*4\s*\]",
        lambda m: f"({m.group('t')} *)((Sub15C *)({m.group('x')}))->p_800",
        text)
    text = re.sub(
        rf"(?<![.\w])(?P<x>[A-Za-z_]\w*)\[\s*0x800\s*/\s*4\s*\]",
        lambda m: f"(int)((Sub15C *)({m.group('x')}))->p_800",
        text)
    text = re.sub(
        rf"\*\(\s*int\s*\*\)\(\s*(?P<x>{SELF})\s*\+\s*0x800\s*\)",
        lambda m: f"(int)((Sub15C *)({m.group('x')}))->p_800",
        text)

    return text


# -------- per-function file segmentation (so one sensitive func doesn't
# -------- revert a whole multi-func TU) --------
FUNC_START = re.compile(r"^[A-Za-z_][\w \*]*?\b(func_[0-9A-Fa-f]+)\s*\(", re.M)


def split_functions(text: str):
    """Yield (kind, chunk) where kind is 'func'(name) or None. Brace-matched."""
    segs = []
    i = 0
    for m in FUNC_START.finditer(text):
        # find the opening brace of the body
        b = text.find("{", m.start())
        if b < 0:
            continue
        # skip prototypes: `func_X(...);` before any '{'
        semi = text.find(";", m.start())
        if 0 <= semi < b:
            continue
        depth = 0
        j = b
        while j < len(text):
            c = text[j]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    j += 1
                    break
            j += 1
        segs.append((m.group(1), m.start(), j))
    # stitch into ordered (name|None, text) list
    out = []
    pos = 0
    for name, s, e in segs:
        if s > pos:
            out.append((None, text[pos:s]))
        out.append((name, text[s:e]))
        pos = e
    if pos < len(text):
        out.append((None, text[pos:]))
    return out


def gen_fields(all_fields: set, struct: str) -> dict:
    """offset -> widest width, for the given struct."""
    by_off = {}
    for s, off, w in all_fields:
        if s != struct:
            continue
        by_off[off] = max(by_off.get(off, 0), w)
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
        if "0x15C" in t or "0x800" in t:
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
        for struct in ("Sub15C", "Obj800"):
            fs = gen_fields(fields, struct)
            print(f"{struct}: {len(fs)} fields")
            for off, w in sorted(fs.items()):
                print(f"  0x{off:X} w{w}")
        return 0

    # --apply : per-function, so one sensitive func can't block a whole TU.
    explicit = [ROOT / a for a in args if a != "--apply"]
    files = explicit or targets
    py = str(ROOT / ".venv" / "bin" / "python")

    def verify_func(tu, fn):
        r = subprocess.run([py, str(ROOT / "tools" / "match_diff.py"),
                            "--count", tu, fn], capture_output=True, text=True,
                           cwd=str(ROOT))
        return r.stdout.strip() == "0"

    nfunc_ok = nfunc_bad = nfiles = 0
    for p in files:
        orig = p.read_text(errors="replace")
        segs = split_functions(orig)
        tu = tu_name(p)
        transformed = {}     # name -> new text
        cands = []
        for name, txt in segs:
            if name is None:
                continue
            fs = set()
            nt = transforms(txt, fs)
            if nt != txt:
                cands.append((name, nt, fs))
        if not cands:
            continue

        def build():
            return ensure_include("".join(
                transformed.get(name, txt) for name, txt in segs))

        kept = False
        for name, nt, _fs in cands:
            transformed[name] = nt
            p.write_text(build())
            if verify_func(tu, name):
                nfunc_ok += 1
                kept = True
            else:
                del transformed[name]
                nfunc_bad += 1
        p.write_text(build() if transformed else orig)
        if transformed:
            nfiles += 1
    print(f"files touched: {nfiles}  funcs converted: {nfunc_ok}  "
          f"funcs left (sensitive): {nfunc_bad}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
