#!/usr/bin/env python3
"""Find byte-identical func_* clusters with >=1 unmatched member.

Read-only investigation: parses build/ico.elf's symbol table for
{addr, size, name}, extracts each function's bytes from
baserom/baseelf.elf, hashes them, and reports duplicate groups.

A function is classified as:
  U  unmatched         — appears in asm/ outside asm/matchings/
  M  matched-snapshot  — appears only in asm/matchings/ (C body exists in src/)
  ?  fully matched     — no .s file under asm/

Run from project root:
    nm --defined-only -S build/ico.elf > /tmp/nm.txt
    python3 tools/find_dup_funcs.py
"""

import hashlib
import os
import re
import sys
from collections import defaultdict

PROJECT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASE = os.path.join(PROJECT, "baserom", "baseelf.elf")
ICO_ELF = os.path.join(PROJECT, "build", "ico.elf")
NM_CACHE = "/tmp/nm.txt"
TEXT_VMA = 0x00100000
TEXT_OFF = 0x1000
TEXT_END_VMA = TEXT_VMA + 0x16F5D4  # from readelf -S baseelf.elf

GLABEL_RE = re.compile(r"^glabel\s+(func_[0-9A-Fa-f]+)\s*$")


def scan_asm_tree():
    matched = {}
    unmatched = {}
    for dirpath, _, files in os.walk(os.path.join(PROJECT, "asm")):
        rel_dir = os.path.relpath(dirpath, os.path.join(PROJECT, "asm"))
        first = rel_dir.split(os.sep, 1)[0]
        is_matched_tree = first == "matchings"
        for fn in files:
            if not fn.endswith(".s"):
                continue
            path = os.path.join(dirpath, fn)
            try:
                with open(path, "r", errors="replace") as f:
                    for line in f:
                        m = GLABEL_RE.match(line)
                        if m:
                            n = m.group(1)
                            rel = os.path.relpath(path, PROJECT)
                            if is_matched_tree:
                                matched.setdefault(n, rel)
                            else:
                                unmatched.setdefault(n, rel)
            except OSError:
                pass
    return unmatched, matched


def load_nm():
    if not os.path.exists(NM_CACHE):
        sys.exit(
            f"missing {NM_CACHE}; run: "
            f"nm --defined-only -S {ICO_ELF} > {NM_CACHE}"
        )
    seen = {}
    with open(NM_CACHE) as f:
        for line in f:
            parts = line.split()
            if len(parts) < 4:
                continue
            addr_s, size_s, typ, name = parts[0], parts[1], parts[2], parts[3]
            if typ not in ("T", "t"):
                continue
            if not name.startswith("func_") or name.endswith(".NON_MATCHING"):
                continue
            try:
                addr = int(addr_s, 16)
                size = int(size_s, 16)
            except ValueError:
                continue
            if size == 0 or addr < TEXT_VMA or addr + size > TEXT_END_VMA:
                continue
            seen.setdefault(addr, (size, name))
    return [(a, s, n) for a, (s, n) in seen.items()]


def main():
    unmatched_paths, matched_paths = scan_asm_tree()
    funcs = load_nm()
    with open(BASE, "rb") as f:
        blob = f.read()

    groups = defaultdict(list)
    for addr, size, name in funcs:
        off = addr - TEXT_VMA + TEXT_OFF
        b = blob[off:off + size]
        if len(b) != size:
            continue
        groups[(size, hashlib.sha1(b).digest())].append((addr, name))

    dups = [(s, m) for (s, _), m in groups.items() if len(m) >= 2]
    actionable = [
        (s, m) for s, m in dups
        if any(n in unmatched_paths for _, n in m)
    ]

    big = sorted(
        [g for g in actionable if g[0] > 0x10],
        key=lambda t: (-t[0], -len(t[1])),
    )
    stubs = sorted(
        [g for g in actionable if g[0] <= 0x10],
        key=lambda t: (-t[0], -len(t[1])),
    )

    print(f"# scan: {len(unmatched_paths)} unmatched, "
          f"{len(matched_paths)} matched-snapshot names")
    print(f"# groups: {len(dups)} total dup groups, "
          f"{len(actionable)} with >=1 unmatched")
    print(f"# {len(big)} non-stub (size>0x10), {len(stubs)} stub (size<=0x10)")
    print()

    def emit(label, gs):
        print(f"## {label}")
        for size, members in gs:
            u = sum(1 for _, n in members if n in unmatched_paths)
            m = sum(1 for _, n in members
                    if n in matched_paths and n not in unmatched_paths)
            x = len(members) - u - m
            print(f"\n--- size=0x{size:X} ({size}B), n={len(members)}"
                  f" (U={u} M={m} ?={x}) ---")
            for addr, name in sorted(members):
                if name in unmatched_paths:
                    tag, p = "U", unmatched_paths[name]
                elif name in matched_paths:
                    tag, p = "M", matched_paths[name]
                else:
                    tag, p = "?", "(no .s under asm/)"
                print(f"  [{tag}] 0x{addr:08X} {name:24s} {p}")

    emit("NON-STUB GROUPS (size > 0x10)", big)
    print()
    emit("STUB GROUPS (size <= 0x10)", stubs)


if __name__ == "__main__":
    main()
