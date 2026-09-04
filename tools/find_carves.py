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
(D_<vma>/jtbl_<vma>); sections come from the target ELF (baserom/baseelf.elf
for `us`, baserom/aug6/baseelf.elf for `aug6`) via tools/ico_version.py; the
consumer map is a scan of asm/[<version>/]**.s + TU source roots.

Version-aware: VERSION env (or auto-detect via ico_version.detect_version)
selects the asm root (`asm/` for us, `asm/aug6/` for aug6), the ELF, and the
TU source roots to scan. Behavior on aug6 is unchanged from before this TU
was made version-aware.
"""
import argparse
import os
import pathlib
import re
import struct
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
from ico_version import detect_version, baseelf_path  # noqa: E402

VERSION = detect_version(pathlib.Path(ROOT))
ELF = str(baseelf_path(pathlib.Path(ROOT), VERSION))
# asm root: retail (`us`) keeps asm/ flat; aug6 (and any other named version)
# nests under asm/<version>/ — same convention as tools/park_tu.py's
# asm_roots() and tools/match_drive.py's VERSION-keyed path.
ASM_ROOT = "asm" if VERSION in ("us", "pal") else f"asm/{VERSION}"
# TU source roots to scan for consumer .c files, per version. aug6's dev
# tree is split by original programmer (omori/ito/sugipon/fumi/seki/common/
# script); retail (`us`) is a flat src/ + ios/isys/ito/sound tree.
SRC_ROOTS = {
    "us": ("ios", "isys", "ito", "sound", "src"),
    "pal": ("ios", "isys", "ito", "sound", "src"),
    "aug6": ("omori", "ito", "sugipon", "fumi", "seki", "common", "script"),
}.get(VERSION, ("omori", "ito", "sugipon", "fumi", "seki", "common", "script"))

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


_ASM_TU_RE = re.compile(
    re.escape(ASM_ROOT) + r"/(?:nonmatchings|matchings)/(.+)/[^/]+\.s$")


def tu_of_path(path):
    """Map a source/asm path to its TU stem (e.g. omori/src/camera-set-manager)."""
    p = path.replace("\\", "/")
    m = _ASM_TU_RE.search(p)
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
    targets = [(ASM_ROOT, "*.s")]
    for d in SRC_ROOTS:
        if os.path.isdir(os.path.join(ROOT, d)):
            targets.append((d, "*.c"))
    data_marker = f"{ASM_ROOT}/data/"
    cod_marker = f"{ASM_ROOT}/src/cod/"
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
            ppath = path.replace("\\", "/")
            # <asm_root>/data/** is the raw section blob that DEFINES the
            # bytes, not a consumer — skip it, else every TU-local symbol
            # looks shared.
            if data_marker in ppath:
                continue
            # <asm_root>/src/cod/*.s is the monolithic unmatched-code blob:
            # owner unknown, so note it as a caveat rather than a TU consumer.
            if cod_marker in ppath:
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
        emit_runs(tu, carves, elf, secs)


def _raw(elf, secs, vma, size):
    _name, start, off, _nobits = section_of(secs, vma)
    return elf[off + (vma - start): off + (vma - start) + size]


_ASM_STUB_CACHE: dict = {}


def _asm_referrer(tu, sym):
    """Nonmatching .s stub of `tu` that references `sym`, or None."""
    if tu not in _ASM_STUB_CACHE:
        d = pathlib.Path(ROOT, ASM_ROOT, "nonmatchings", tu)
        _ASM_STUB_CACHE[tu] = ([(p, p.read_text(errors="ignore"))
                                for p in d.rglob("*.s")] if d.is_dir() else [])
    for path, text in _ASM_STUB_CACHE[tu]:
        if sym in text:
            return path.name
    return None


def _gate(secname, vma, size, raw):
    """Mechanical reasons a plain C definition would NOT land where the carve
    says. Every one of these was an actual SHA-gate failure before it was a
    check — see decomp/carve_ledger.md "Root cause"."""
    bad = []
    if not any(raw):
        bad.append("all-zero -> ee-gcc emits .bss/.sbss, not " + secname)
    if size % 4:
        bad.append(f"size {size} is not a word multiple")
    if secname == ".sdata" and size > 8:
        bad.append(f"{size}B > -G8 threshold -> ee-gcc emits .data, not .sdata")
    if secname == ".data" and size <= 8:
        bad.append(f"{size}B <= -G8 threshold -> ee-gcc emits .sdata, not .data")
    # ee-gcc: 4-byte scalar -> align 4; anything larger (arrays included) -> 8.
    need = 4 if size == 4 else 8
    if vma % need:
        bad.append(f"VMA 0x{vma:X} is not {need}-aligned -> ld pads, layout shifts")
    return bad


def emit_runs(tu, carves, elf, secs):
    """Print dot-form yaml + byte-verified C for each CONTIGUOUS carve run.

    Two hard constraints of the one-pass model are enforced here rather than
    discovered at the SHA gate:
      * a TU may hold only ONE carved run per section (splat emits a whole-object
        `<tu>.o(.<sect>*)` selector per carve subsegment and ld honours only the
        first, so a 2nd disjoint run silently collapses into the 1st);
      * every symbol in a run must be spelled so ee-gcc places it in the carved
        section at the carved address (see _gate).
    """
    by_sect = {}
    for row in sorted(carves):
        by_sect.setdefault(row[2], []).append(row)

    for secname, rows in by_sect.items():
        runs, cur = [], []
        for row in rows:
            if cur and cur[-1][0] + cur[-1][3] != row[0]:
                runs.append(cur)
                cur = []
            cur.append(row)
        if cur:
            runs.append(cur)

        print(f"\n=== {secname}: {len(runs)} contiguous run(s) ===")
        if len(runs) > 1:
            print(f"  NOTE: only ONE run per (TU, section) can be carved — pick "
                  f"the best one; the rest must stay in the blob "
                  f"(tools/gen_ninja.py hard-errors on a 2nd).")
        for run in runs:
            start = run[0][0]
            end = run[-1][0] + run[-1][3]
            bad = []
            for vma, sym, s, size, *_ in run:
                for b in _gate(s, vma, size, _raw(elf, secs, vma, size)):
                    bad.append(f"    {sym}: {b}")
                # `migrate_rodata_to_functions` makes splat embed a LOCAL
                # dlabel copy of any .rodata a still-INCLUDE_ASM function
                # references into that function's nonmatching .s the moment the
                # carve exists — a C definition of the same symbol then fails
                # assembly with "already defined". Detect it BEFORE the carve by
                # looking for the reference in the TU's surviving asm stubs.
                if s == ".rodata":
                    ref = _asm_referrer(tu, sym)
                    if ref:
                        bad.append(f"    {sym}: referenced by still-asm {ref} — "
                                   f"splat would migrate a duplicate dlabel copy; "
                                   f"port that function first")
                if s == ".lit4":
                    bad.append(f"    {sym}: named .lit4 float compiles to .sdata "
                               f"under -G8; a .lit4 pool slot cannot be carved "
                               f"(the per-TU rename config was retired 2026-09-04)")
            print(f"\n-- run 0x{start:X}..0x{end:X} ({end - start} bytes, "
                  f"{len(run)} syms){'  [BLOCKED]' if bad else ''}")
            if bad:
                print("\n".join(bad))
                continue
            print(f"      - [0x{start - 0x100000:X}, {secname}, {tu}]  "
                  f"# carved {run[0][1]}..{run[-1][1]} "
                  f"(VMA 0x{start:X}..0x{end:X}, {end - start} bytes, {len(run)} syms)")
            print(f"      - [0x{end - 0x100000:X}, {secname.lstrip('.')}, "
                  f"src/cod/{end - 0x100000:06X}]     # {secname} blob resume")
            print(f"\n/* {secname} — carved VMA 0x{start:X}..0x{end:X} "
                  f"({len(run)} symbols), bytes verified against the target ELF */")
            for vma, sym, s, size, *_ in run:
                raw = _raw(elf, secs, vma, size)
                words = struct.unpack("<%dI" % (size // 4), raw)
                if size == 4:
                    print(f"unsigned int {sym} = 0x{words[0]:08X};")
                    continue
                print(f"unsigned int {sym}[{size // 4}] = {{")
                for i in range(0, len(words), 4):
                    print("    " + " ".join(f"0x{w:08X}," for w in words[i:i + 4]))
                print("};")


if __name__ == "__main__":
    main()
