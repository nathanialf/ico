#!/usr/bin/env python3
"""Convert hex-encoded D_<VMA> data defs in tracked src/*.c to readable
'content' forms, preserving the exact byte image (SHA-safe).

Three independent passes (select with flags):

  --floats   `[const] {unsigned,signed,} int D_X = 0xHHHHHHHH;`  whose
             pattern is a plausibly-authored float constant -> `float
             D_X = <decimal>f;`.  Also `int[] D_X = {0x..}` arrays whose
             every element is a float-or-zero -> `float D_X[] = {...}`.
             SHA-safe: same size (4B/elem), same alignment, same -G8
             section (.sdata/.data D_X); ee-gcc re-emits the identical
             .word.  Each literal is byte-verified before it is written.

  --strings  curated short-string scalars/arrays whose bytes are pure
             printable ASCII (or the 2 EUC-JP marker words) -> `char
             D_X[N] = "...";` with the array dim pinned to the original
             byte count so the section size is unchanged.

  --eucjp-comments  insert a `/* EUC-JP: "decoded" */` line above every
             octal-escaped Japanese `char D_X[] = "..."` literal that
             lacks one.  Pure comment, never touches bytes.

Default is --dry-run (report only).  Pass --apply to edit files.
"""
from __future__ import annotations
import argparse, glob, re, struct, sys, os

# ----- float interpretation -------------------------------------------------
NICE_LO, NICE_HI = 1e-7, 1e9

def pattern_float_literal(p):
    """Return a C float literal that encodes EXACTLY to 32-bit pattern p
    and looks like an authored constant, else None."""
    b = struct.pack('<I', p & 0xFFFFFFFF)
    f = struct.unpack('<f', b)[0]
    if f != f or f in (float('inf'), float('-inf')):
        return None                      # NaN / Inf
    if f == 0.0:
        return None                      # leave 0 as int (ambiguous null/flag)
    if not (NICE_LO <= abs(f) <= NICE_HI):
        return None                      # denormal / huge -> not a float const
    def ok(s):
        return struct.pack('<f', struct.unpack('<f', struct.pack('<f', float(s)))[0]) == b
    best = None; best_prec = 99
    for prec in range(1, 10):
        s = f"{f:.{prec}g}"
        if ok(s):
            best = s; best_prec = prec
            break
    if best is None:
        best = repr(f)
        if not ok(best):
            return None
    # Disambiguate float vs string: a pattern whose 4 bytes are all
    # printable ASCII *and* needs >=7 significant digits to round-trip
    # is far more likely an authored string (e.g. "NULL", "%lf ") than a
    # float constant.  Clean floats ("0.7" -> bytes "333?") round-trip in
    # few digits and stay floats.
    if best_prec >= 7 and all(0x20 <= c < 0x7f for c in b):
        return None
    # prefer plain fixed notation over exponent for readable magnitudes
    if 'e' in best or 'E' in best:
        fx = f"{f:.6f}".rstrip('0').rstrip('.')
        if ok(fx) and len(fx) <= 12:
            best = fx
    if '.' not in best and 'e' not in best and 'E' not in best:
        best += '.0'
    return best + 'f'

# ----- parsing --------------------------------------------------------------
SCALAR = re.compile(
    r'^(?P<i>\s*)(?P<const>const\s+)?(?P<type>unsigned\s+int|signed\s+int|int)\s+'
    r'(?P<name>D_[0-9A-Fa-f]{6,8})\s*=\s*(?P<val>0x[0-9A-Fa-f]+|\d+)\s*;\s*$')
ARRAY = re.compile(
    r'^(?P<i>\s*)(?P<const>const\s+)?(?P<type>unsigned\s+int|int)\s+'
    r'(?P<name>D_[0-9A-Fa-f]{6,8})\s*\[(?P<dim>\d+)\]\s*=\s*\{(?P<body>[^}]*)\}\s*;\s*$')
CHARLIT = re.compile(
    r'^(?P<i>\s*)(?P<const>const\s+)?(?:unsigned\s+)?char\s+'
    r'(?P<name>D_[0-9A-Fa-f]{6,8})\s*\[(?P<dim>\d*)\]\s*=\s*(?P<str>".*")\s*;\s*$')

def parse_word(tok):
    tok = tok.strip()
    return int(tok, 16) if tok.lower().startswith('0x') else int(tok, 10)

# ----- string helpers -------------------------------------------------------
def c_escape(b: bytes) -> str:
    """Octal-escape a byte string to a pure-ASCII C literal."""
    out = []
    prev_oct = False
    for c in b:
        if c == 0x0a:
            out.append('\\n'); prev_oct = False
        elif c == 0x09:
            out.append('\\t'); prev_oct = False
        elif c == 0x0d:
            out.append('\\r'); prev_oct = False
        elif c == 0x22:
            out.append('\\"'); prev_oct = False
        elif c == 0x5c:
            out.append('\\\\'); prev_oct = False
        elif 0x20 <= c < 0x7f:
            # a digit right after an octal escape would extend it -> re-escape
            if prev_oct and chr(c) in '01234567':
                out.append(f'\\{c:03o}'); prev_oct = True
            else:
                out.append(chr(c)); prev_oct = False
        else:
            out.append(f'\\{c:03o}'); prev_oct = True
    return '"' + ''.join(out) + '"'

def unescape_c(s: str) -> bytes:
    body = ''.join(re.findall(r'"((?:\\.|[^"\\])*)"', s))
    out = bytearray(); i = 0
    while i < len(body):
        c = body[i]
        if c == '\\':
            n = body[i+1]
            if n in 'nrt0':
                out.append({'n':10,'r':13,'t':9,'0':0}[n]); i += 2
            elif n in '01234567':
                j = i+1; oc = ''
                while j < len(body) and len(oc) < 3 and body[j] in '01234567':
                    oc += body[j]; j += 1
                out.append(int(oc, 8) & 0xff); i = j
            else:
                out.append(ord(n)); i += 2
        else:
            out.append(ord(c)); i += 1
    return bytes(out)

def is_jp(s: str) -> bool:
    return any(0x3040 <= ord(ch) <= 0x30ff or 0x4e00 <= ord(ch) <= 0x9fff
               or ord(ch) in (0x25cb, 0x00d7, 0x25b3, 0x25a0, 0x3001, 0x3002,
                              0xff01, 0xff1f) for ch in s)

# ----- passes ---------------------------------------------------------------
def words_of_scalar(m):
    return [parse_word(m.group('val'))]

def convert_floats(line):
    m = SCALAR.match(line)
    if m:
        p = parse_word(m.group('val')) & 0xFFFFFFFF
        lit = pattern_float_literal(p)
        if lit is None:
            return None
        assert struct.pack('<f', struct.unpack('<f', struct.pack('<f', float(lit[:-1])))[0]) \
            == struct.pack('<I', p)
        return f"{m.group('i')}{m.group('const') or ''}float {m.group('name')} = {lit};\n"
    m = ARRAY.match(line)
    if m:
        words = [parse_word(t) & 0xFFFFFFFF for t in m.group('body').split(',') if t.strip()]
        if not words:
            return None
        lits = []
        nonzero = 0
        for w in words:
            if w == 0:
                lits.append('0.0f'); continue
            l = pattern_float_literal(w)
            if l is None:
                return None
            lits.append(l); nonzero += 1
        if nonzero == 0:
            return None
        body = ', '.join(lits)
        return (f"{m.group('i')}{m.group('const') or ''}float "
                f"{m.group('name')}[{m.group('dim')}] = {{ {body} }};\n")
    return None

def scalar_bytes(m):
    return struct.pack('<I', parse_word(m.group('val')) & 0xFFFFFFFF)

# Printable-but-not-text scalars: halves of 8-byte doubles (PObj's
# "8-byte double constants") and the misaligned head of PObj's 256-byte
# ctype table.  Bytes are numeric data, not strings.
STRING_EXCLUDE = {
    'D_005524C4', 'D_005524CC', 'D_00553244',   # double low-words ("x'U" etc.)
    'D_0062FC7C',                               # ctype-table misaligned head
}

def convert_strings(line):
    # scalar: 4 bytes -> char[4]
    m = SCALAR.match(line)
    if m:
        if m.group('name') in STRING_EXCLUDE:
            return None
        # ee-gcc 2.9 force-aligns char ARRAYS to 8 (`.align 3`) while the
        # original `unsigned int` scalar is `.align 2` (4).  A char[4] is
        # therefore over-aligned; at a VMA that is not 8-aligned the
        # linker pads it forward and shifts the whole .sdata tail (breaks
        # SHA-1).  Only convert when the symbol's own VMA is 8-aligned.
        if int(m.group('name')[2:], 16) % 8 != 0:
            return None
        b = scalar_bytes(m)
        if pattern_float_literal(parse_word(m.group('val')) & 0xFFFFFFFF):
            return None                          # it's a float, not a string
        core = b.rstrip(b'\x00')
        if len(core) < 2:
            return None
        printable = all(32 <= c < 127 or c in (9,10,13) for c in core)
        jp = False
        if not printable:
            try:
                s = core.decode('euc_jp'); jp = is_jp(s)
            except Exception:
                pass
            if not jp:
                return None
        core = b.rstrip(b'\x00')
        lit = c_escape(core)
        assert unescape_c(lit) == core, (m.group('name'), b.hex())
        return f"{m.group('i')}{m.group('const') or ''}char {m.group('name')}[4] = {lit};\n"
    return None

def add_eucjp_comment(lines, idx):
    m = CHARLIT.match(lines[idx])
    if not m:
        return None
    b = unescape_c(m.group('str'))
    try:
        s = b.rstrip(b'\x00').decode('euc_jp')
    except Exception:
        return None
    if not is_jp(s):
        return None
    if idx > 0 and 'EUC-JP' in lines[idx-1]:
        return None
    indent = m.group('i')
    disp = s.replace('\n', '\\n').replace('\t', '\\t').replace('*/', '* /')
    return f'{indent}/* EUC-JP: "{disp}" */\n'

# ----- driver ---------------------------------------------------------------
def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('--floats', action='store_true')
    ap.add_argument('--strings', action='store_true')
    ap.add_argument('--eucjp-comments', action='store_true')
    ap.add_argument('--apply', action='store_true')
    ap.add_argument('--files', nargs='*', default=None)
    args = ap.parse_args()
    files = args.files or sorted(glob.glob('src/*.c'))
    totals = {'floats':0, 'strings':0, 'eucjp':0}
    for path in files:
        with open(path, encoding='utf-8', errors='replace') as fh:
            lines = fh.readlines()
        changed = False
        out = []
        i = 0
        while i < len(lines):
            line = lines[i]
            if args.eucjp_comments:
                c = add_eucjp_comment(lines, i)
                if c:
                    out.append(c); totals['eucjp'] += 1; changed = True
            new = None
            if args.floats:
                new = convert_floats(line)
                if new: totals['floats'] += 1
            if new is None and args.strings:
                new = convert_strings(line)
                if new: totals['strings'] += 1
            if new and new != line:
                if not args.apply:
                    print(f"{path}:{i+1}\n  - {line.rstrip()}\n  + {new.rstrip()}")
                out.append(new); changed = True
            else:
                out.append(line)
            i += 1
        if changed and args.apply:
            with open(path, 'w', encoding='utf-8') as fh:
                fh.writelines(out)
    print(f"\n== {'APPLIED' if args.apply else 'DRY-RUN'}: "
          f"floats={totals['floats']} strings={totals['strings']} "
          f"eucjp_comments={totals['eucjp']} ==")

if __name__ == '__main__':
    os.chdir(os.path.dirname(os.path.dirname(os.path.abspath(__file__))))
    main()
