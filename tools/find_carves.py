#!/usr/bin/env python3
"""
find_carves.py — mechanically find the data symbols a TU should carve.

Given a TU (e.g. ``omori/src/camera-set-manager``), list every DATA symbol its
functions reference and classify whether it is safe to carve into that TU's
``.c``.  The classification rests on two mechanical signals that together
resolve the two things the SHA-1 gate CANNOT tell you on its own:

  * section (from the target ELF) — a NOBITS section (.bss/.sbss) cannot be
    carved per-TU because placement depends on whole-section link-order
    accumulation.  Only PROGBITS (.data/.rodata/.lit4/.sdata) carries bytes.
  * consumer set (who references the symbol) — a SINGLE-consumer symbol is
    unambiguously owned by the one TU that uses it, so carving it there is
    correct.  A MULTI-consumer (shared) symbol's true owner is the .o that
    *defines* it, which a stripped target does not record; carving it into a
    referencing TU would build byte-identical yet mis-attribute another TU's
    data.  The gate can't catch that, so we don't auto-carve it.

Verdicts:
  CARVE   PROGBITS + single-consumer  -> safe to pull into the TU.
  SHARED  PROGBITS + multi-consumer   -> owner ambiguous; review, don't auto.
  BLOCKED NOBITS (.bss/.sbss)         -> not per-TU carvable (documented).

Usage:
  tools/find_carves.py <tu>                 # report
  tools/find_carves.py <tu> --emit          # + yaml split lines & C scaffold
                                            #   for the CARVE rows
  tools/find_carves.py <tu> --consumers     # list the referencing TUs

Sources (no leaked data): symbol VMAs are encoded in splat's auto names
(D_<vma>/jtbl_<vma>); sections come from baserom/aug6/baseelf.elf (the build
oracle); the consumer map is a scan of asm/aug6/**.s + */src/**.c.
"""
import argparse
import os
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
ELF = os.path.join(ROOT, "baserom/aug6/baseelf.elf")

# splat auto-names with the VMA in the name; the only ones whose address we can
# trust without a symbol table.  Named (human) data symbols are rare here and
# are reported but not address-resolved.
SYM_RE = re.compile(r"\b(D|jtbl|jpt|jlbl|L)_([0-9A-Fa-f]{6,8})\b")


def load_sections(elf_path):
    """Return [(name, vma_start, vma_end, is_nobits)] for SHF_ALLOC sections."""
    data = open(elf_path, "rb").read()
    e_shoff = struct.unpack_from("<I", data, 0x20)[0]
    e_shentsize = struct.unpack_from("<H", data, 0x2E)[0]
    e_shnum = struct.unpack_from("<H", data, 0x30)[0]
    e_shstrndx = struct.unpack_from("<H", data, 0x32)[0]

    def shdr(i):
        o = e_shoff + i * e_shentsize
        name, typ, flags, addr, off, size = struct.unpack_from("<IIIIII", data, o)
        return name, typ, flags, addr, off, size

    str_off = shdr(e_shstrndx)[4]

    def name_at(n):
        end = data.index(b"\0", str_off + n)
        return data[str_off + n : end].decode()

    secs = []
    SHT_NOBITS = 8
    SHF_ALLOC = 0x2
    for i in range(e_shnum):
        name, typ, flags, addr, off, size = shdr(i)
        if not (flags & SHF_ALLOC) or size == 0:
            continue
        secs.append((name_at(name), addr, addr + size, off, typ == SHT_NOBITS))
    secs.sort(key=lambda s: s[1])
    return secs, data


def section_of(secs, vma):
    for name, start, end, off, nobits in secs:
        if start <= vma < end:
            return name, start, off, nobits
    return None


def tu_of_path(path):
    """Map a source/asm path to its TU stem (e.g. omori/src/camera-set-manager)."""
    p = path.replace("\\", "/")
    m = re.search(r"asm/aug6/(?:nonmatchings|matchings)/(.+)/[^/]+\.s$", p)
    if m:
        return m.group(1)
    m = re.search(r"((?:[^/]+/)*[^/]+)\.c$", p)
    if m:
        return m.group(1)
    return p


def scan_consumers():
    """Scan every .s disassembly + src .c once.

    Returns (consumers, blob_refs):
      consumers[sym] = set of KNOWN TUs that reference it (matched .c +
                       nonmatchings/<tu>/ .s) — these resolve ownership.
      blob_refs[sym] = count of refs from the monolithic unmatched-code blob
                       (asm/aug6/src/cod/*.s); owner unknown, reported as a
                       caveat but NOT counted toward shared-ness.
    """
    consumers = {}
    blob_refs = {}
    # one grep over the full asm disassembly, one over each src root that exists
    targets = [("asm/aug6", "*.s")]
    for d in ("omori", "ito", "sugipon", "fumi", "seki", "common", "script"):
        if os.path.isdir(os.path.join(ROOT, d)):
            targets.append((d, "*.c"))
    for base, inc in targets:
        try:
            out = subprocess.run(
                ["grep", "-roE", SYM_RE.pattern, base, f"--include={inc}"],
                cwd=ROOT, capture_output=True, text=True,
            ).stdout
        except Exception:
            continue
        for line in out.splitlines():
            i = line.find(":")
            if i < 0:
                continue
            path, sym = line[:i], line[i + 1 :]
            # asm/aug6/data/** is the raw section blob that DEFINES the bytes,
            # not a consumer — skip it, else every TU-local symbol looks shared.
            if "/aug6/data/" in path:
                continue
            # asm/aug6/src/cod/*.s is the monolithic unmatched-code blob: owner
            # unknown, so note it as a caveat rather than a TU consumer.
            if "/aug6/src/cod/" in path:
                blob_refs[sym] = blob_refs.get(sym, 0) + 1
                continue
            consumers.setdefault(sym, set()).add(tu_of_path(path))
    return consumers, blob_refs


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("tu", help="TU stem, e.g. omori/src/camera-set-manager")
    ap.add_argument("--emit", action="store_true",
                    help="print yaml split lines + C scaffold for CARVE rows")
    ap.add_argument("--consumers", action="store_true",
                    help="list the referencing TUs for each symbol")
    args = ap.parse_args()
    tu = args.tu.rstrip("/")

    secs, elf = load_sections(ELF)
    consumers, blob_refs = scan_consumers()

    def sym_vma(s):
        m = SYM_RE.fullmatch(s)
        return int(m.group(2), 16) if m else None

    # all data-section VMAs (for extent = gap to next symbol)
    data_vmas = set()
    for s in consumers:
        v = sym_vma(s)
        if v is None:
            continue
        sec = section_of(secs, v)
        if sec and not sec[0].startswith(".text"):
            data_vmas.add(v)
    data_vmas = sorted(data_vmas)

    def next_vma(vma):
        import bisect
        i = bisect.bisect_right(data_vmas, vma)
        return data_vmas[i] if i < len(data_vmas) else None

    # symbols this TU references, restricted to data sections
    rows = []
    for sym, tus in consumers.items():
        if tu not in tus:
            continue
        m = SYM_RE.fullmatch(sym)
        if not m:
            continue
        vma = int(m.group(2), 16)
        sec = section_of(secs, vma)
        if not sec or sec[0].startswith(".text"):
            continue
        secname, secstart, secoff, nobits = sec
        nv = next_vma(vma)
        secend = [s for s in secs if s[0] == secname][0][2]
        end = min(nv, secend) if nv else secend
        size = end - vma
        nconsumers = len(tus)
        blob = blob_refs.get(sym, 0)
        if nobits:
            verdict = "BLOCKED"
        elif nconsumers == 1:
            verdict = "CARVE"
        else:
            verdict = "SHARED"
        rows.append((vma, sym, secname, size, nconsumers, verdict,
                     sorted(tus), nobits, secoff, blob))
    rows.sort()

    if not rows:
        print(f"{tu}: references no data symbols.")
        return

    print(f"== {tu}: {len(rows)} referenced data symbol(s) ==")
    print(f"{'VMA':>10}  {'symbol':<16} {'section':<9} {'size':>5} {'TUs':>4}  verdict")
    for vma, sym, secname, size, nc, verdict, tus, nobits, secoff, blob in rows:
        note = f"  (+{blob} unmatched-blob ref)" if blob and verdict == "CARVE" else ""
        print(f"0x{vma:08X}  {sym:<16} {secname:<9} {size:>5}  {nc:>3}  {verdict}{note}")
        if args.consumers and nc > 1:
            others = [t for t in tus if t != tu]
            print(f"             also: {', '.join(others)}")

    n_carve = sum(1 for r in rows if r[5] == "CARVE")
    n_shared = sum(1 for r in rows if r[5] == "SHARED")
    n_block = sum(1 for r in rows if r[5] == "BLOCKED")
    print(f"\nCARVE={n_carve}  SHARED={n_shared}  BLOCKED={n_block}"
          f"   (CARVE = PROGBITS + referenced by only this matched TU)")

    if args.emit:
        carves = [r for r in rows if r[5] == "CARVE"]
        if not carves:
            print("\n(no clean CARVE rows to emit)")
            return
        print("\n--- yaml split lines (insert into the matching section blob) ---")
        for vma, sym, secname, size, nc, verdict, tus, nobits, secoff, blob in carves:
            fileoff = vma - 0x100000
            print(f"      - [0x{fileoff:X}, {secname.lstrip('.')}, {tu}]  "
                  f"# carved {sym} (VMA 0x{vma:X}, 0x{size:X} bytes)")
        print("\n--- C scaffold (verify type/extent by hand) ---")
        for vma, sym, secname, size, nc, verdict, tus, nobits, secoff, blob in carves:
            raw = elf[secoff + (vma - section_of(secs, vma)[1]):
                      secoff + (vma - section_of(secs, vma)[1]) + size]
            print(f"// {sym} @0x{vma:X} ({secname}, 0x{size:X} bytes)")
            if size == 4:
                u = struct.unpack("<I", raw)[0]
                f = struct.unpack("<f", raw)[0]
                print(f"//   word=0x{u:08X}  float={f:g}")
            elif raw and all(b == 0 or 32 <= b < 127 for b in raw):
                print(f"//   ascii={raw!r}")
            else:
                print(f"//   bytes={raw.hex()}")


if __name__ == "__main__":
    main()
