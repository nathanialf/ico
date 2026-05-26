#!/usr/bin/env python3
"""Fast byte-check for `-fdata-sections` D_<VMA> symbols (no link).

Compiles each given src/*.c via compile_c.sh, then for every section
named `.{data,sdata,rodata,lit4}.D_<VMA>` in the .o, compares its bytes
to baserom/baseelf.elf at 0x<VMA>.  Reports any mismatch.

This proves the typed C reproduces the ROM's per-symbol bytes; it does
NOT prove inter-symbol layout/alignment (a full `ninja` link covers
that).  For float<->int conversions (identical size+align) the section
check is sufficient; for size/align-changing edits, also link.
"""
import re, subprocess, sys, os
from pathlib import Path
from elftools.elf.elffile import ELFFile

SECRE = re.compile(r'^\.(?:data|sdata|rodata|lit4)\.D_([0-9A-Fa-f]{6,8})$')

def baseelf_bytes(elf, vma, n):
    for seg in elf.iter_segments():
        if seg['p_type'] != 'PT_LOAD':
            continue
        s = seg['p_vaddr']; e = s + seg['p_filesz']
        if s <= vma < e:
            off = vma - s
            return seg.data()[off:off+n]
    return None

def main(files):
    base = ELFFile(open('baserom/baseelf.elf', 'rb'))
    bad = total = 0
    for f in files:
        out = Path('build') / (Path(f).with_suffix('.o'))
        out.parent.mkdir(parents=True, exist_ok=True)
        r = subprocess.run(['tools/compile_c.sh', f, str(out)],
                           capture_output=True, text=True)
        if r.returncode != 0:
            print(f"COMPILE FAIL {f}\n{r.stderr[-500:]}"); bad += 1; continue
        o = ELFFile(open(out, 'rb'))
        for sec in o.iter_sections():
            m = SECRE.match(sec.name)
            if not m:
                continue
            vma = int(m.group(1), 16)
            got = sec.data()
            want = baseelf_bytes(base, vma, len(got))
            total += 1
            if want != got:
                bad += 1
                print(f"MISMATCH {f} {sec.name} @0x{vma:08X}\n"
                      f"  want {want.hex() if want else None}\n  got  {got.hex()}")
    print(f"\n== checked {total} D_ sections across {len(files)} files: "
          f"{'ALL MATCH' if bad==0 else str(bad)+' MISMATCH'} ==")
    return 1 if bad else 0

if __name__ == '__main__':
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    sys.exit(main(sys.argv[1:]))
