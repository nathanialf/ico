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


def _printable(c):
    return 32 <= c <= 126 or c in (9, 10, 13, 27)


def as_string_bytes(b):
    """True if the extent is one or more NUL-separated printable strings with
    zero padding — i.e. spellable as a single char[] literal."""
    if not b or b[-1] != 0 or not _printable(b[0]):
        return False
    i, saw = 0, False
    while i < len(b):
        if b[i] == 0:
            i += 1
            continue
        j = i
        while j < len(b) and b[j] != 0:
            if not _printable(b[j]):
                return False
            j += 1
        if j == len(b):
            return False  # unterminated
        saw = True
        i = j
    return saw


def c_literal(b):
    """Emit the extent as a C string literal (embedded NULs spelled \\0,
    trailing NUL padding left implicit) and VERIFY it round-trips."""
    # strip trailing zeros — the sized array zero-fills them
    end = len(b)
    while end > 0 and b[end - 1] == 0:
        end -= 1
    content = b[:end]
    out = []
    prev_was_octal = False
    for c in content:
        if c == 0:
            out.append("\\0")
            prev_was_octal = True
            continue
        ch = chr(c)
        if ch == "\\":
            out.append("\\\\")
        elif ch == '"':
            out.append('\\"')
        elif ch == "\n":
            out.append("\\n")
        elif ch == "\t":
            out.append("\\t")
        elif ch == "\r":
            out.append("\\r")
        elif c == 27:
            out.append("\\033")
            prev_was_octal = True
            continue
        elif prev_was_octal and ch.isdigit():
            # a digit after an octal escape would extend it — force a break
            out.append("\\%03o" % c)
            prev_was_octal = True
            continue
        else:
            out.append(ch)
        prev_was_octal = False
    lit = "".join(out)
    # verify: re-encode the literal the way ee-gcc will
    dec = []
    i = 0
    while i < len(lit):
        if lit[i] == "\\":
            nxt = lit[i + 1]
            if nxt in "01234567":
                j = i + 1
                o = ""
                while j < len(lit) and lit[j] in "01234567" and len(o) < 3:
                    o += lit[j]
                    j += 1
                dec.append(int(o, 8))
                i = j
                continue
            dec.append({"n": 10, "t": 9, "r": 13, "\\": 92, '"': 34}[nxt])
            i += 2
            continue
        dec.append(ord(lit[i]))
        i += 1
    dec += [0] * (len(b) - len(dec))
    assert bytes(dec) == b, f"literal round-trip failed: {lit!r}"
    return lit


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

    # Additional split points: any D_ symbol inside the run referenced from
    # ANY C source (matched code externs interior strings of splat's larger
    # extents — e.g. commonact's D_005588F0 inside D_005588D8's block).
    ref_re = re.compile(r"\bD_([0-9A-Fa-f]{8})\b")
    crefs = set()
    for root in ("src", "ios", "isys", "ito", "sound"):
        top = os.path.join(ROOT, root)
        for dirpath, _dirs, files in os.walk(top):
            for f in files:
                if not f.endswith(".c"):
                    continue
                try:
                    text = open(os.path.join(dirpath, f),
                                encoding="utf-8", errors="replace").read()
                except OSError:
                    continue
                for m in ref_re.finditer(text):
                    v = int(m.group(1), 16)
                    if run_start <= v < run_end and v not in stub_anchor:
                        crefs.add(v)

    # only split refs whose enclosing extent is a DEF extent — a ref inside a
    # stub's migrated span is emitted by the stub, not by C
    base = sorted(list(standalone.keys()) + list(stub_anchor.keys()))
    import bisect
    for v in sorted(crefs):
        if v in standalone:
            continue
        i = bisect.bisect_right(base, v) - 1
        if i >= 0 and base[i] in stub_anchor:
            continue
        standalone[v] = "D_%08X" % v

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
        if size <= 8:
            print(f'INCLUDE_RODATA("asm/nonmatchings/{tu}", {sym});'
                  f"  /* {size}B — a C def would land in .sdata under -G8; "
                  f"0x{vma:08X}..0x{nxt:08X} */")
        elif as_string_bytes(b):
            print(f'const char {sym}[0x{size:X}] = "{c_literal(b)}";'
                  f"  /* 0x{vma:08X}..0x{nxt:08X} */")
        else:
            words = struct.unpack(f"<{size // 4}I", b[: size // 4 * 4])
            body = " ".join(f"0x{w:08X}," for w in words)
            print(f"const unsigned int {sym}[0x{size // 4:X}] = {{ {body} }};"
                  f"  /* 0x{vma:08X}..0x{nxt:08X} */")


if __name__ == "__main__":
    main()
