#!/usr/bin/env python3
"""emit_run_defs.py — byte-verified C defs for a carved run's standalone syms.

After a full-run rodata carve, `build.sh setup` leaves two emitter classes:
function stubs with migrated rodata (INCLUDE_ASM emits those bytes), and
standalone asm/nonmatchings/<tu>/D_*.s files splat could not attach to a
function.  The standalone ones are NOT wired into the build; each needs a C
definition in the TU source, inserted so source order equals VMA order.

This tool prints, for every standalone D_*.s of a TU:
  * its VMA extent [start, next_emitted_vma)
  * a `const` C definition sized to the full extent (zero-pad included),
    spelled as a string when the bytes are a single NUL-terminated ASCII
    string, else as unsigned int words
  * the anchor emitter (stub / matched func) it must precede in the file

Bytes come from baserom/baseelf.elf (authoritative), not the .s comments.
"""
import glob
import os
import re
import struct
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from ico_version import detect_version, baseelf_path  # noqa: E402
import pathlib  # noqa: E402

VERSION = detect_version(pathlib.Path(ROOT))
ELF = str(baseelf_path(pathlib.Path(ROOT), VERSION))


def elf_sections():
    data = open(ELF, "rb").read()
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    secs = []
    for i in range(e_shnum):
        o = e_shoff + i * e_shentsize
        _n, typ, _f, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        if typ != 8 and addr:
            secs.append((addr, off, size))
    return data, secs


def raw(data, secs, vma, size):
    for addr, off, ssz in secs:
        if addr <= vma and vma + size <= addr + ssz:
            return data[off + (vma - addr): off + (vma - addr) + size]
    raise SystemExit(f"VMA 0x{vma:X}+0x{size:X} not inside any PROGBITS section")


def is_c_string(b):
    """One printable-ASCII NUL-terminated string covering the whole extent
    (trailing bytes all zero)."""
    if not b or 0 not in b:
        return None
    n = b.index(0)
    s = b[:n]
    if not s:
        return None
    if any(c > 126 or (c < 32 and c not in (9, 10, 13)) for c in s):
        return None
    if any(c != 0 for c in b[n:]):
        return None
    return s.decode("ascii")


def c_escape(s):
    return (s.replace("\\", "\\\\").replace('"', '\\"')
             .replace("\n", "\\n").replace("\t", "\\t").replace("\r", "\\r"))


def main():
    tu = sys.argv[1]  # e.g. src/girl_act
    run_start = int(sys.argv[2], 16)
    run_end = int(sys.argv[3], 16)
    nmdir = os.path.join(ROOT, "asm", "nonmatchings", tu)

    # collect every emitted VMA: stub-migrated dlabels + standalone files
    standalone = {}   # vma -> sym
    stub_anchor = {}  # vma -> stub name (first rodata vma per stub)
    for path in glob.glob(os.path.join(nmdir, "*.s")):
        base = os.path.basename(path)[:-2]
        text = open(path, encoding="utf-8", errors="replace").read()
        dl = re.findall(r"^dlabel (\w+)$", text, re.M)
        vmas = [int(m, 16) for m in
                re.findall(r"/\* [0-9A-F]{6,8} ([0-9A-F]{8}) \*?", text)]
        rod = [int(m.group(1), 16) for m in
               re.finditer(r"/\* [0-9A-F]{6,8} ([0-9A-F]{8}) \*/ \.word|"
                           r"/\* [0-9A-F]{6,8} ([0-9A-F]{8}) \*/ \.asciz",
                           text) for m in [m] if m.group(1)]
        if re.match(r"D_[0-9A-F]{8}$", base):
            standalone[int(base[2:], 16)] = base
        elif dl:
            # function stub with migrated rodata: anchor at first dlabel vma
            first = None
            for d in dl:
                m = re.match(r"(?:D|jtbl)_([0-9A-Fa-f]{8})", d)
                if m:
                    v = int(m.group(1), 16)
                    if first is None or v < first:
                        first = v
            if first is not None:
                stub_anchor[first] = base

    emitted = sorted(list(standalone.keys()) + list(stub_anchor.keys()))
    data, secs = elf_sections()

    print(f"/* --- {tu} run 0x{run_start:X}..0x{run_end:X} --- */")
    for i, vma in enumerate(emitted):
        nxt = emitted[i + 1] if i + 1 < len(emitted) else run_end
        if vma in stub_anchor:
            print(f"/* 0x{vma:08X}  [stub {stub_anchor[vma]}] */")
            continue
        sym = standalone[vma]
        size = nxt - vma
        b = raw(data, secs, vma, size)
        s = is_c_string(b)
        if s is not None:
            print(f'const char {sym}[0x{size:X}] = "{c_escape(s)}";'
                  f"  /* 0x{vma:08X}..0x{nxt:08X} */")
        else:
            words = struct.unpack(f"<{size // 4}I", b[: size // 4 * 4])
            body = " ".join(f"0x{w:08X}," for w in words)
            print(f"const unsigned int {sym}[0x{size // 4:X}] = {{ {body} }};"
                  f"  /* 0x{vma:08X}..0x{nxt:08X} */")


if __name__ == "__main__":
    main()
