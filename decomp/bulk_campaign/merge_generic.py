#!/usr/bin/env python3
"""Merge build/bulk/<BASE>/matched/*.md snippets into <TU>.c (generic version).

Usage: merge_generic.py <TU-stem> <results-dir> [--apply] [func ...]
  e.g.: merge_generic.py common/src/GobjProc build/bulk/GobjProc --apply

Each .md has '### decls' and '### code' fenced blocks. Replaces the function's
INCLUDE_ASM line with (decls + code), skipping decl lines whose symbol already
appears in the file outside INCLUDE_ASM strings.
"""
import re, sys, glob, os

ROOT = "/primary/dev/ico"

def parse_md(path):
    text = open(path).read()
    blocks = re.findall(r"###\s*(\w+)\s*\n+```c?\n(.*?)```", text, re.S)
    d = {name: body.rstrip("\n") for name, body in blocks}
    return d.get("decls", ""), d.get("code", "")

def decl_symbol(line):
    line = line.strip()
    if not line or line.startswith(("/*", "//", "#")):
        return None
    m = re.search(r"([A-Za-z_][A-Za-z0-9_]*)\s*(\[[^\]]*\])?\s*(\([^)]*\))?\s*;\s*$", line)
    return m.group(1) if m else None

def main():
    args = [a for a in sys.argv[1:] if not a.startswith("--")]
    apply_ = "--apply" in sys.argv
    if len(args) < 2:
        sys.exit(__doc__)
    tu_stem, results_dir = args[0], args[1]
    only = set(args[2:])
    tu_path = os.path.join(ROOT, tu_stem + ".c")
    match_dir = os.path.join(ROOT, results_dir, "matched")
    tu = open(tu_path).read()
    merged, skipped = [], []
    for path in sorted(glob.glob(os.path.join(match_dir, "*.md"))):
        func = os.path.basename(path)[:-3]
        if only and func not in only:
            continue
        inc = 'INCLUDE_ASM("asm/aug6/nonmatchings/%s", %s);' % (tu_stem, func)
        if inc not in tu:
            skipped.append((func, "no INCLUDE_ASM line (already merged?)"))
            continue
        decls, code = parse_md(path)
        if not code or func not in code:
            skipped.append((func, "bad md (no code block / wrong func)"))
            continue
        keep = []
        for line in decls.splitlines():
            sym = decl_symbol(line)
            if sym:
                pattern = r'^[^\n]*\b%s\b[^\n]*$' % re.escape(sym)
                mentions = [m for m in re.finditer(pattern, tu, re.M)
                            if "INCLUDE_ASM" not in m.group(0)]
                if mentions:
                    continue
            if line.strip():
                keep.append(line)
        repl = ("\n".join(keep) + "\n\n" if keep else "") + code
        tu = tu.replace(inc, repl)
        merged.append(func)
    if apply_:
        open(tu_path, "w").write(tu)
    print("merged: %d" % len(merged))
    for f in merged: print("  +", f)
    print("skipped: %d" % len(skipped))
    for f, why in skipped: print("  -", f, ":", why)
    if not apply_:
        print("(dry run; use --apply)")

if __name__ == "__main__":
    main()
