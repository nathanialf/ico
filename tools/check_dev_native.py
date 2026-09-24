#!/usr/bin/env python3
"""check_dev_native.py: refuse constructs a developer did not write.

Run by the pre-commit hook on staged C files (or on the whole tree with
--all).  Exit 1 on any hit.  The rules follow CLAUDE.md's crutch test and the
user's standing instruction of 2026-09-23 (dev-native code; asm and register
pins are fine only where the developers' own source was assembly).

  1. K&R (old-style) function definitions.  Allowed under sce/libc (newlib's
     public source is K&R) and at sites listed in tools/dev_native_allow.txt
     with their reason (a K&R definition the ROM forces: a caller that passes
     fewer arguments than the callee reads, with the definition first in the
     file, only compiles without a prototype).
  2. An empty `do { } while (0);` statement (a loop note with no code).
  3. Empty inline asm (`__asm__("")` in any spelling) and the retired pin
     macros KEEP_LIVE / ANCHOR / MEM_BARRIER / MATERIALIZE / REG($n).
  4. `register T x __asm__("$reg")` pins and `__asm__(` blocks in a function
     the January listing (baserom/pal/SRCFILE.TXT) proves was compiled C: its
     instructions carry three or more distinct source lines.  A block is
     always allowed when its template uses a machine-only instruction (VU0,
     COP2 moves, COP0, cache, sync, ei/di, syscall, MMI), since no C spells
     those; a function attributed to one or two lines was a hand asm
     statement; a function the listing does not carry (an archive member
     without line info) is reported as unverified, not refused.
  5. tools/compile_c.sh names exactly two assemblers, ee-as 2.9-991111
     (EE_AS_OLD, the game and the compiler-install libc/libm/libgcc) and SCE's
     2.10-ee-001003-1 (EE_AS_SDK, the SDK-install archives), and SELECTED_EE_AS
     is only ever one of those two, chosen by archive: no selection by TU or by
     function and no config opt-in (user ruling 2026-09-27, replacing the
     one-assembler ruling of 2026-09-23 after the disc's link was measured).
  6. A file-scope `__asm__(...)` block that defines (`.global NAME`) a function
     the listing attributes to three or more source lines of a .c file: that is
     a compiled-C function typed out as asm, a stub hidden from the
     NON_MATCHING count (mv_vibuf carried five until 2026-09-23); it is written
     as an INCLUDE_ASM stub instead.
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
LISTING = os.path.join(ROOT, 'baserom', 'pal', 'SRCFILE.TXT')
ALLOW = os.path.join(ROOT, 'tools', 'dev_native_allow.txt')

MACHINE_ONLY = re.compile(
    r'(?m)\b(v[a-z]+\.[xyzw]+|vnop|vrnext|vrinit|vrxor|vrget|vsqrt|vrsqrt|vdiv|vwaitq|vcallms|'
    r'lqc2|sqc2|qmfc2|qmtc2|ctc2|cfc2|mfc0|mtc0|eret|tlbwi|tlbwr|tlbp|tlbr|syscall|'
    r'mfhi1|mflo1|mthi1|mtlo1|mult1|multu1|div1|divu1|madd1|maddu1|'
    r'pcpy[lu]d|pext[lu][bhw]|pexc[hw]|ppac[bhw]|padd[bhw]|psub[bhw]|pand|por|pxor|pnor|'
    r'pmax[hw]|pmin[hw]|pmult[hw]|pmadd[hw]|pinth|pintl|pabs[hw]|plzcw|prot3w|pmfhl|pmthl)\b'
    r'|^\s*(sync(\.[lp])?|ei|di|cache\s+\w+|pref\s+\w+|lq\s|sq\s)'
    r'|\bVU0_[A-Z0-9_]+\s*\(')

KNR_HDR = re.compile(r'^[A-Za-z_][\w \*]*\b(\w+)\s*\(\s*([a-z_]\w*(?:\s*,\s*[a-z_]\w*)*)\s*\)\s*$')
DECL = re.compile(r'^\s*(int|char|unsigned|signed|float|double|short|long|void|struct|[A-Z]\w*)\b[^(]*;\s*$')
FN_HDR = re.compile(r'^(?!\s*(?:__asm__|asm)\b)(?:static\s+|inline\s+|__inline__\s+)*[A-Za-z_][\w \*]*\b(\w+)\s*\(')
PIN = re.compile(r'\bregister\b[^;]*__asm__\s*\(\s*"\$')
ASM_OPEN = re.compile(r'(__asm__|\basm\b)\s*(__volatile__|volatile)?\s*\(')
EMPTY_ASM = re.compile(r'(__asm__|\basm\b)\s*(__volatile__|volatile)?\s*\(\s*""\s*[:)]')
PIN_MACRO = re.compile(r'\b(KEEP_LIVE|ANCHOR|MEM_BARRIER|MATERIALIZE)\s*\(|\bREG\s*\(\s*\$')
# instructions no C spells, valid only inside an asm template (the assert trap and its kin)
ASM_ONLY = re.compile(r'\b(break|teq|tne|tge|tlt|tgeu|tltu)\b')


def staged_or_all(argv):
    if '--all' in argv or os.environ.get('FILES') == 'all':
        out = subprocess.run(['git', 'ls-files', 'ico2', 'sce', '--', '*.c', '*.inc'],
                             cwd=ROOT, capture_output=True, text=True).stdout.split()
        return out
    if os.environ.get('FILES'):
        out = []
        for f in os.environ['FILES'].split():
            # an absolute path, in this checkout or a worktree, keys the same repo-relative name
            m = re.search(r'(?:^|/)((?:ico2|sce)/.*)$', f)
            out.append((m.group(1), f) if m else (f, f))
        return out
    out = subprocess.run(['git', 'diff', '--cached', '--name-only', '--diff-filter=ACMR'],
                         cwd=ROOT, capture_output=True, text=True).stdout.split()
    return [f for f in out if re.search(r'\.(c|inc)$', f) and re.match(r'(ico2|sce)/', f)]


def load_listing():
    """function name -> (source file basename, number of distinct source lines)."""
    if not os.path.exists(LISTING):
        return None
    lines = {}
    files = {}
    cur = None
    with open(LISTING, errors='replace') as fh:
        for l in fh:
            m = re.match(r'^[0-9a-f]+ <(\w+)>:', l)
            if m:
                cur = m.group(1)
                continue
            m = re.match(r'^(/\S+?):(\d+)\s*$', l)
            if m and cur:
                lines.setdefault(cur, set()).add(int(m.group(2)))
                files.setdefault(cur, m.group(1).rsplit('/', 1)[-1])
    return {fn: (files.get(fn, ''), len(v)) for fn, v in lines.items()}


def load_allow():
    allow = set()
    if os.path.exists(ALLOW):
        for l in open(ALLOW):
            l = l.split('#', 1)[0].strip()
            if l:
                allow.add(l.split('|', 1)[0].strip())
    return allow


def enclosing_function(L, i):
    """the C function whose body holds line i, or None at file scope (a `}` in
    column 0 closes the previous function before any header is reached)."""
    for j in range(i, -1, -1):
        if j < i and L[j].rstrip() == '}':
            return None
        m = FN_HDR.match(L[j])
        if m and not L[j].rstrip().endswith(';') and m.group(1) not in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
            return m.group(1)
    return None


def asm_block_text(L, i):
    """the asm template from the opening line to the closing ');'."""
    buf = []
    depth = 0
    for j in range(i, min(i + 200, len(L))):
        buf.append(L[j])
        depth += L[j].count('(') - L[j].count(')')
        if j > i or ('(' in L[j] and depth <= 0):
            if depth <= 0 and ';' in L[j]:
                break
    return '\n'.join(buf)


def check_one_assembler(bad):
    """user ruling 2026-09-27: two assemblers selected per archive by the disc's link,
    never per TU, never per function, never by a config file."""
    path = os.path.join(ROOT, 'tools', 'compile_c.sh')
    if not os.path.exists(path):
        return
    ok = ('tools/cc/ee-gcc2.9-991111/bin/as', 'tools/cc/ee-gcc2.96/bin/as')
    for i, l in enumerate(open(path, errors='replace').read().split('\n')):
        code = l.split('#', 1)[0]
        if re.search(r'/bin/as\b|\bmips[\w-]*-as\b', code) and not any(o in code for o in ok):
            bad.append(f'tools/compile_c.sh:{i+1}: an assembler other than ee-as 2.9-991111 or SCE 2.10-ee is named in code')
        if re.search(r'SELECTED_EE_AS=', code) and 'EE_AS_OLD' not in code and 'EE_AS_SDK' not in code:
            bad.append(f'tools/compile_c.sh:{i+1}: SELECTED_EE_AS is set to something other than EE_AS_OLD or EE_AS_SDK')
        if re.search(r'config/use_\w*as', code):
            bad.append(f'tools/compile_c.sh:{i+1}: a config opt-in selects the assembler (selection is by archive only)')


def main(argv):
    files = staged_or_all(argv)
    listing = load_listing()
    allow = load_allow()
    bad = []
    warn = []
    check_one_assembler(bad)
    for f in files:
        if isinstance(f, tuple):
            f, path = f
        else:
            path = os.path.join(ROOT, f)
        if not os.path.exists(path):
            continue
        try:
            L = open(path, errors='replace').read().split('\n')
        except OSError:
            continue
        newlib = f.startswith('sce/libc/')
        for i, l in enumerate(L):
            m = KNR_HDR.match(l)
            if m and m.group(1) not in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
                j = i + 1
                decl = 0
                while j < len(L) and j < i + 12 and L[j].strip() != '{':
                    if DECL.match(L[j]):
                        decl += 1
                    j += 1
                if decl:
                    key = f'{f}:{m.group(1)}'
                    if not newlib and key not in allow:
                        bad.append(f'{f}:{i+1}: K&R definition of {m.group(1)} (allow it in tools/dev_native_allow.txt only with the ROM reason)')
            if re.match(r'^\s*do\s*\{\s*$', l) and i + 1 < len(L) and re.match(r'^\s*\}\s*while\s*\(0\)\s*;', L[i+1]):
                bad.append(f'{f}:{i+1}: empty do {{ }} while (0); (a loop note with no code)')
            if EMPTY_ASM.search(l):
                bad.append(f'{f}:{i+1}: empty inline asm')
            if PIN_MACRO.search(l):
                bad.append(f'{f}:{i+1}: retired pin macro')
            if PIN.search(l) or (ASM_OPEN.search(l) and not EMPTY_ASM.search(l)):
                fn = enclosing_function(L, i)
                if fn is None and not PIN.search(l):
                    # a file-scope asm block: every function it defines is judged by
                    # the listing on its own name (rule 6: a compiled-C function typed
                    # out as asm is a stub hidden from the NON_MATCHING count)
                    text = asm_block_text(L, i)
                    for g in re.findall(r'\.globa?l\s+(\w+)', text):
                        key = f'{f}:{g}'
                        if key in allow:
                            continue
                        if listing is None:
                            warn.append(f'{f}:{i+1}: file-scope asm defines {g}: listing not available, unverified')
                        elif g not in listing:
                            warn.append(f'{f}:{i+1}: file-scope asm defines {g}: no listing rows (archive member without line info), unverified')
                        else:
                            src, n = listing[g]
                            if not (src.endswith(('.s', '.S')) or n <= 2):
                                bad.append(f'{f}:{i+1}: file-scope asm defines {g}, which the listing attributes to {n} source lines of {src} (compiled C typed out as asm: make it an INCLUDE_ASM stub)')
                    continue
                key = f'{f}:{fn}'
                if key in allow:
                    continue
                text = '' if PIN.search(l) else asm_block_text(L, i)
                if text and (MACHINE_ONLY.search(text) or ASM_ONLY.search(text)):
                    continue
                if text:
                    # an asm block with ordinary instructions: allowed when the enclosing
                    # function is a VU0/MMI sequence (its body uses machine-only lines)
                    k = i + 1
                    while k < len(L) and not (FN_HDR.match(L[k]) and not L[k].rstrip().endswith(';')):
                        if MACHINE_ONLY.search(L[k]):
                            text = 'machine'
                            break
                        k += 1
                    if text == 'machine':
                        continue
                    text = ''
                    k = i - 1
                    while k >= 0 and not (FN_HDR.match(L[k]) and not L[k].rstrip().endswith(';')):
                        if MACHINE_ONLY.search(L[k]):
                            text = 'machine'
                            break
                        k -= 1
                    if text == 'machine':
                        continue
                if not text:
                    # a bare register pin: allowed when the same function body uses a
                    # machine-only instruction (an asm block or a VU0_ macro line)
                    k = i + 1
                    while k < len(L) and not (FN_HDR.match(L[k]) and not L[k].rstrip().endswith(';')):
                        if MACHINE_ONLY.search(L[k]) or (ASM_OPEN.search(L[k]) and MACHINE_ONLY.search(asm_block_text(L, k))):
                            text = 'machine'
                            break
                        k += 1
                    if text == 'machine':
                        continue
                if listing is None:
                    warn.append(f'{f}:{i+1}: asm/pin in {fn}: listing not available, unverified')
                    continue
                if fn not in listing:
                    warn.append(f'{f}:{i+1}: asm/pin in {fn}: no listing rows (archive member without line info), unverified')
                    continue
                src, n = listing[fn]
                if src.endswith(('.s', '.S')) or n <= 2:
                    continue
                bad.append(f'{f}:{i+1}: asm/pin in {fn}, which the listing attributes to {n} source lines of {src} (compiled C, not hand asm)')
    for w in warn:
        print('check_dev_native: warning: ' + w, file=sys.stderr)
    for b in bad:
        print('check_dev_native: ' + b, file=sys.stderr)
    print(f'check_dev_native: {"FAIL" if bad else "OK"} ({len(files)} files scanned, {len(bad)} refused, {len(warn)} unverified)', file=sys.stderr)
    return 1 if bad else 0


if __name__ == '__main__':
    sys.exit(main(sys.argv[1:]))
