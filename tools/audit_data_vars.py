#!/usr/bin/env python3
"""Read-only audit of tracked D_<VMA> data variables.

Scans src/*.c for hex-initialized arrays/scalars, reconstructs the
little-endian byte image, and classifies each as:
  - ASCII text  (printable, candidate for `char[]="..."` conversion)
  - EUC-JP text (>=1 Japanese codepoint, candidate + needs comment)
  - already-string (`const char`/`char` = "...")
  - zero-init buffer (`= {0}`)  -> bss-like, ignore
  - numeric data (genuine, leave as-is)

Emits a summary and (with --list CATEGORY) the per-symbol detail.
Touches nothing.
"""
import os, re, sys, glob, struct

DECL = re.compile(
    r'^\s*(?P<const>const\s+)?(?P<type>unsigned\s+int|signed\s+int|int|'
    r'unsigned\s+char|signed\s+char|char|unsigned\s+short|short|'
    r'unsigned\s+long\s+long|long\s+long|float)\s+'
    r'(?P<name>D_[0-9A-Fa-f]{6,8})\s*'
    r'(?:\[(?P<dim>\d*)\])?\s*=\s*(?P<init>.+?);\s*$')

TYPE_SZ = {
    'unsigned char':1,'signed char':1,'char':1,
    'unsigned short':2,'short':2,
    'unsigned int':4,'signed int':4,'int':4,'float':4,
    'unsigned long long':8,'long long':8,
}

def words_to_bytes(init, elemsz):
    """Parse a { ... } brace list or a scalar into little-endian bytes."""
    nums = re.findall(r'0x[0-9A-Fa-f]+|-?\d+', init)
    if not nums:
        return None
    out = bytearray()
    for n in nums:
        v = (int(n, 16) if n.lower().startswith('0x') else int(n, 10))
        v &= ((1 << (elemsz*8)) - 1)
        out += v.to_bytes(elemsz, 'little')
    return bytes(out)

def looks_like_nice_float(word):
    """True if a 4-byte word, read as float, is a 'nice' magnitude
    typical of a game constant — strong signal it's a float, not text."""
    f = struct.unpack('<f', word)[0]
    if f == 0.0:
        return True
    af = abs(f)
    # common constant range; excludes the denormals/huge values that
    # genuine ASCII words ("%d\n", "Off\0") decode to.
    return 1e-3 <= af <= 1e6

def classify_text(b, nwords):
    """nwords = number of source elements; 1 => scalar (float-prone)."""
    if b is None or len(b) == 0:
        return 'numeric', None
    # A lone 4-byte word that is a plausible float is almost certainly a
    # float constant, not a string — suppress the text false positive.
    if nwords == 1 and len(b) == 4 and looks_like_nice_float(b):
        return 'numeric', None
    core = b.rstrip(b'\x00')
    if not core:
        return 'numeric', None
    printable = sum(1 for c in core if 32 <= c < 127 or c in (9,10,13))
    if printable == len(core) and printable >= 3:
        try:
            return 'ascii', core.decode('ascii')
        except Exception:
            pass
    # EUC-JP: require at least one real Japanese codepoint AND, for lone
    # words, that it is not a plausible float.
    try:
        s = core.decode('euc_jp')
        has_jp = any(0x3040 <= ord(ch) <= 0x30ff or 0x4e00 <= ord(ch) <= 0x9fff
                     or ord(ch) in (0x25cb, 0x00d7, 0x25b3, 0x25a0) for ch in s)
        if has_jp and all((ord(ch) >= 0x20 or ch in '\n\t\r') for ch in s):
            if not (nwords == 1 and len(b) == 4 and looks_like_nice_float(b)):
                return 'eucjp', s
    except Exception:
        pass
    return 'numeric', None

def main():
    list_cat = None
    if '--list' in sys.argv:
        list_cat = sys.argv[sys.argv.index('--list')+1]
    cats = {'ascii':[], 'eucjp':[], 'string':[], 'zero':[], 'numeric':[]}
    for path in sorted(glob.glob('src/*.c')):
        with open(path, encoding='utf-8', errors='replace') as fh:
            for ln, line in enumerate(fh, 1):
                m = DECL.match(line)
                if not m:
                    continue
                name = m.group('name')
                init = m.group('init').strip()
                rec = (path, ln, name, m.group('type'), bool(m.group('const')))
                if init.startswith('"'):
                    cats['string'].append(rec + (init[:40],))
                    continue
                if init.startswith('{'):
                    inner = init.strip('{} ')
                    if inner in ('0', '0x0', '0x00', ''):
                        cats['zero'].append(rec + ('',))
                        continue
                elemsz = TYPE_SZ.get(m.group('type').replace('  ',' '), 4)
                nwords = len(re.findall(r'0x[0-9A-Fa-f]+|-?\d+', init))
                b = words_to_bytes(init, elemsz)
                cat, text = classify_text(b, nwords)
                cats[cat].append(rec + (repr(text)[:60] if text else '',))
    print("=== AUDIT SUMMARY (tracked src/*.c hex/scalar D_ defs) ===")
    for c in ('ascii','eucjp','string','zero','numeric'):
        print(f"  {c:10s}: {len(cats[c])}")
    print(f"  {'TOTAL':10s}: {sum(len(v) for v in cats.values())}")
    if list_cat:
        print(f"\n=== {list_cat} ===")
        for path, ln, name, typ, isc, extra in cats[list_cat]:
            print(f"{path}:{ln}: {'const ' if isc else ''}{typ} {name}  {extra}")

if __name__ == '__main__':
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    main()
