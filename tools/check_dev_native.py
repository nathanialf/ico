#!/usr/bin/env python3
"""check_dev_native.py: refuse constructs a developer did not write.

Run by the pre-commit hook on staged C files (or on the whole tree with
--all).  Exit 1 on any hit.  --self-test runs rule 8 on the file-scope
shapes a carve leaves (SELF_TEST) and on the forms it refuses.  The rules follow CLAUDE.md's crutch test and the
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
     is only ever one of those two, chosen by archive as the disc's link shows:
     no selection by TU or by function and no config opt-in.
  6. A file-scope `__asm__(...)` block that defines (`.global NAME`) a function
     the listing attributes to three or more source lines of a .c file: that is
     a compiled-C function typed out as asm, and it is written as C instead.
  7. A symbol alias: a declarator followed by an asm label
     (`extern int x __asm__("name");`), which binds one name to another
     symbol instead of declaring the symbol under its own name.

  8. The campaign stubs (config/stubs.<slug>.txt, tools/gen_stub_s.py).  The
     only asm a C file may carry for a function it does not yet compile is the
     exact line `INCLUDE_ASM(stem);` at file scope, and only while the list
     has a row of that stem naming this file (the stem is the row's name, or
     its file=<stem> when two statics share a name; the file is the row's TU,
     or its in=<file.c.inc>, which the TU must include, but the TU for a row
     marked inline, an inline function of that .c.inc, whose stub stands at
     the end of the TU); the row and the line go together, so a listed stem
     whose file lacks the line is refused too.  A literal row (lit4, rdlit,
     sdlit: the function's constants) rides on its function's line and has
     none of its own, except that a stem with a def literal row (an inline
     function's strings, written where it is defined) carries exactly one
     `INCLUDE_ASM_LIT(stem);` at file scope in the file that defines it (the
     TU, or the in= file) as well, and no other stem carries one.  Either
     line needs `#include "include_asm.h"` above it in its own file: without
     the macro the line compiles, with only a warning, as a K&R declaration
     of a function named INCLUDE_ASM, and the stub is never read.  A file-scope
     line is one outside every function body: a prototype on one line or
     several and a one-line `{}` function above it leave it at file scope.
     An INCLUDE_ASM in any other spelling, one for a stem the list does not
     carry, one on a tree whose list is empty, an `#include "include_asm.h"`
     with no listed stub beside it, and a `.include` in any other asm are
     refused.  The macro comes from build/<slug>/stubs/include_asm.h, which
     gen_stub_s.py writes with the stubs and the tree never tracks, so a file
     that includes it does not compile once the list is empty.  A `#line`
     after the INCLUDE_ASM line, which keeps a TU's __LINE__ numbering, is
     decided by the byte gate, not here.

What the ban list in CLAUDE.md names but no pattern can decide (dead stores,
declaration tricks, a do-while(0) wrapper with a body) stays with review.
"""
import os
import re
import subprocess
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, 'tools'))
from gen_stub_s import LIST as STUB_LIST, LITERALS, parse_stubs  # noqa: E402
# Rule 4's listing is the PAL disc's, the only disc that ships one; the
# shared tree is the PAL revision.
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
ALIAS = re.compile(r'[\w\])]\s*(__asm__|\basm\b)\s*\(\s*"[A-Za-z_.][\w.]*"\s*\)\s*(__attribute__\b.*)?[;,=]')
PIN_MACRO = re.compile(r'\b(KEEP_LIVE|ANCHOR|MEM_BARRIER|MATERIALIZE)\s*\(|\bREG\s*\(\s*\$')
# rule 8: the one stub form, and the other spellings that would bring in asm text
INCLUDE_ASM_LINE = re.compile(r'^INCLUDE_ASM\((\w+)\);$')
INCLUDE_ASM_LIT_LINE = re.compile(r'^INCLUDE_ASM_LIT\((\w+)\);$')
INCLUDE_ASM_HDR = re.compile(r'^\s*#\s*include\s+["<]include_asm\.h[">]')
ASM_INCLUDE = re.compile(r'\.include\b')
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


def code_chars(L, j, col=0):
    """(line, character) of the code from line j, column col on: comments,
    string and character literals and preprocessor lines left out, a '\\n'
    at each line's end."""
    blk = False
    for k in range(j, len(L)):
        l = L[k]
        if not blk and l.lstrip().startswith('#') and not (k == j and col):
            continue
        n, c = len(l), col if k == j else 0
        while c < n:
            if blk:
                e = l.find('*/', c)
                if e < 0:
                    break
                blk, c = False, e + 2
            elif l.startswith('/*', c):
                blk, c = True, c + 2
            elif l.startswith('//', c):
                break
            elif l[c] in '"\'':
                q, c = l[c], c + 1
                while c < n and l[c] != q:
                    c += 2 if l[c] == '\\' else 1
                c += 1
            else:
                yield k, l[c]
                c += 1
        yield k, '\n'


def header_kind(L, j, start):
    """What the item whose name's `(` ends at column start of line j is:
    ('decl', None) when its parameter list is followed by `;`, `,` or `=`
    (a prototype, on one line or several, an __attribute__ or asm label
    between), else ('def', the line of the body's first `{`, or None when
    the file ends first); a K&R definition's parameter declarations stand
    between the list and the `{`."""
    depth, after, word, knr = 1, False, '', False
    for k, ch in code_chars(L, j, start):
        if not after:
            depth += {'(': 1, ')': -1}.get(ch, 0)
            after = depth == 0
            continue
        if ch.isalnum() or ch == '_':
            word += ch
            continue
        if word:
            knr = knr or word not in ('__attribute__', '__asm__', 'asm')
            word = ''
        if ch == '{':
            return 'def', k
        if knr or ch.isspace():
            continue
        if ch in ';,=':
            return 'decl', None
        if ch == '(':
            # an __attribute__ ((...)) or asm label after the parameters
            depth, after = 1, False
    return 'def', None


def enclosing_function(L, i):
    """the C function whose body holds line i, or None at file scope.  A
    header is a line that starts an item naming a function with `(`; a
    prototype (its parameter list followed by `;`, on one line or several)
    is not one, and a function whose body closes above line i (a `}` in
    column 0, or a body that opens and closes on its own lines, such as a
    one-line `{}`) leaves line i at file scope."""
    for j in range(i, -1, -1):
        if j < i and L[j].rstrip() == '}':
            return None
        m = FN_HDR.match(L[j])
        if not m or L[j].rstrip().endswith(';') or m.group(1) in ('if', 'while', 'for', 'switch', 'return', 'sizeof'):
            continue
        kind, brace = header_kind(L, j, m.end())
        if kind == 'decl':
            continue
        if brace is not None and brace < i:
            depth = 0
            for k, ch in code_chars(L, brace):
                if k >= i:
                    break
                if ch == '{':
                    depth += 1
                elif ch == '}':
                    depth -= 1
                    if depth == 0:
                        return None
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
    """two assemblers selected per archive by the disc's link, never per TU,
    never per function, never by a config file."""
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


def check_stubs(f, L, stubs, bad, lit=frozenset()):
    """rule 8 on one file: each INCLUDE_ASM and INCLUDE_ASM_LIT line against
    the stub list (by stem), and each row whose line lives in this file (its
    TU, or its in=<file.c.inc>) against its lines.  lit holds the stems with
    a def literal row, whose INCLUDE_ASM_LIT line stands at the definition."""
    seen, seen_lit = set(), set()
    header = unheaded = False
    rel = os.path.relpath(STUB_LIST, ROOT)
    for i, l in enumerate(L):
        if 'INCLUDE_ASM' not in l and 'include_asm' not in l and '.include' not in l:
            continue
        m = INCLUDE_ASM_LINE.match(l.rstrip()) or INCLUDE_ASM_LIT_LINE.match(l.rstrip())
        if m and enclosing_function(L, i) is None:
            name = m.group(1)
            form = 'INCLUDE_ASM_LIT' if l.startswith('INCLUDE_ASM_LIT') else 'INCLUDE_ASM'
            done = seen_lit if form == 'INCLUDE_ASM_LIT' else seen
            # INCLUDE_ASM lives in the row's asm file (its in= file, or the
            # TU for an inline function of a .c.inc), INCLUDE_ASM_LIT where
            # the function is defined (its in= file, or the TU)
            want = (stubs[name].get('asm', stubs[name]['src']) if form == 'INCLUDE_ASM' else stubs[name]['src']) \
                if name in stubs else None
            if not header and not unheaded:
                # with the macro undefined, the line is a K&R declaration of
                # a function named INCLUDE_ASM: a warning, and no stub read
                unheaded = True
                bad.append(f'{f}:{i+1}: {form}({name}) with no #include "include_asm.h" above it (without the'
                           ' macro the line compiles, with only a warning, as a K&R declaration and reads no stub)')
            if not stubs:
                bad.append(f'{f}:{i+1}: {form}({name}) on a tree whose stub list is empty ({rel})')
            elif name not in stubs:
                bad.append(f'{f}:{i+1}: {form}({name}): no row of that stem in {rel}')
            elif want != f:
                bad.append(f'{f}:{i+1}: {form}({name}): its row names {want}, not this file')
            elif form == 'INCLUDE_ASM_LIT' and name not in lit:
                bad.append(f'{f}:{i+1}: INCLUDE_ASM_LIT({name}): {name} has no def literal row in {rel}')
            elif name in done:
                bad.append(f'{f}:{i+1}: {form}({name}) a second time')
            else:
                done.add(name)
        elif INCLUDE_ASM_HDR.match(l):
            header = True
        elif 'INCLUDE_ASM' in l:
            bad.append(f'{f}:{i+1}: INCLUDE_ASM in a form other than `INCLUDE_ASM(name);` or'
                       ' `INCLUDE_ASM_LIT(name);` alone on a file-scope line')
        elif ASM_INCLUDE.search(l) and f.endswith(('.c', '.h', '.inc')):
            bad.append(f'{f}:{i+1}: .include in an asm template (stubs come only through INCLUDE_ASM)')
    if header and not seen and not seen_lit:
        bad.append(f'{f}: includes include_asm.h with no listed stub')
    for name, r in stubs.items():
        if r.get('asm', r['src']) == f and name not in seen:
            bad.append(f'{f}: {rel}:{r["line"]} lists {r["name"]} for this file, which has no INCLUDE_ASM({name}); line')
        if r['src'] == f and name in lit and name not in seen_lit:
            bad.append(f'{f}: {rel}:{r["line"]} gives {r["name"]} def literal rows, and this file has no'
                       f' INCLUDE_ASM_LIT({name}); line')
        if r['tu'] == f and r['src'] != f:
            inc = os.path.relpath(r['src'], os.path.dirname(f))
            if not any(re.match(r'\s*#\s*include\s+"' + re.escape(inc) + '"', x) for x in L):
                bad.append(f'{f}: {rel}:{r["line"]} puts {r["name"]} in {r["src"]}, which this file does not include')


# --self-test: the file-scope shapes a carve leaves around INCLUDE_ASM (a
# prototype on one line or several, a one-line `{}` function, a declaration
# with an attribute) and the ones rule 8 refuses, as (name, file, text, the
# refusals expected, as substrings, in order)
H = '#include "include_asm.h"\n\n'
SELF_TEST = [
    ('multi-line prototype', 'ico2/a.c',
     H + 'int f(void)\n{\n    return 0;\n}\n\nint g(int a, float *b,\n      unsigned char c);\n\nINCLUDE_ASM(g);\n'
     '\nINCLUDE_ASM(h);\n', []),
    ('static multi-line prototype, two stubs', 'ico2/a.c',
     H + 'static int g(int a, void *b, float r,\n             unsigned char c);\n\nINCLUDE_ASM(h);\n\nINCLUDE_ASM(g);\n',
     []),
    ('one-line {} function between stubs', 'ico2/a.c',
     H + 'INCLUDE_ASM(g);\n\ninline void f(int *p) {}\n\nINCLUDE_ASM(h);\n', []),
    ('comment, extern and multi-line prototype', 'ico2/a.c',
     H + '/* declared here:\n   a note */\nextern const int t[];\n\nstatic void g(int *c, float x, float y,\n'
     '              void *q);\n\nINCLUDE_ASM(g);\n\nINCLUDE_ASM(h);\n', []),
    ('multi-line extern, prototype, static data', 'ico2/a.c',
     H + 'static int n; /* derived name */\nextern int k(char *t, int x,\n             int y);\nstatic int g(void);\n\n'
     'INCLUDE_ASM(g);\n\nstatic int m = -1;\n\nstatic int h(void);\n\nINCLUDE_ASM(h);\n', []),
    ('declaration with an attribute', 'ico2/a.c',
     H + 'static int s __attribute__((aligned(16)));\n\nINCLUDE_ASM(g);\n\nINCLUDE_ASM(h);\n', []),
    ('INCLUDE_ASM inside a body', 'ico2/a.c',
     H + 'int f(int a,\n      int b)\n{\nINCLUDE_ASM(g);\n}\n\nINCLUDE_ASM(h);\n',
     ['ico2/a.c:6: INCLUDE_ASM in a form other', 'lists g for this file']),
    ('INCLUDE_ASM inside a K&R body', 'ico2/a.c',
     H + 'int f(a, b)\nint a;\nint b;\n{\nINCLUDE_ASM(g);\n}\n\nINCLUDE_ASM(h);\n',
     ['ico2/a.c:7: INCLUDE_ASM in a form other', 'lists g for this file']),
    ('INCLUDE_ASM with no include_asm.h', 'ico2/a.c', 'int f(void);\n\nINCLUDE_ASM(g);\n\nINCLUDE_ASM(h);\n',
     ['ico2/a.c:3: INCLUDE_ASM(g) with no #include "include_asm.h" above it']),
    ('include_asm.h below the first INCLUDE_ASM', 'ico2/a.c',
     'INCLUDE_ASM(g);\n#include "include_asm.h"\nINCLUDE_ASM(h);\n',
     ['ico2/a.c:1: INCLUDE_ASM(g) with no #include "include_asm.h" above it']),
    ('INCLUDE_ASM_LIT with no include_asm.h', 'ico2/b.c',
     'INCLUDE_ASM_LIT(i);\n\nint f(void);\n\nINCLUDE_ASM(j);\n\nINCLUDE_ASM(i);\n',
     ['ico2/b.c:1: INCLUDE_ASM_LIT(i) with no #include "include_asm.h" above it']),
    ('INCLUDE_ASM_LIT at the definition, INCLUDE_ASM at the end', 'ico2/b.c',
     H + 'int f(void);\n\nINCLUDE_ASM_LIT(i);\n\nint f(void)\n{\n    return 0;\n}\n\nINCLUDE_ASM(j);\n'
     '\nINCLUDE_ASM(i);\n', []),
    ('INCLUDE_ASM_LIT with no def row', 'ico2/b.c',
     H + 'INCLUDE_ASM_LIT(i);\nINCLUDE_ASM_LIT(j);\n\nINCLUDE_ASM(i);\nINCLUDE_ASM(j);\n',
     ['INCLUDE_ASM_LIT(j): j has no def literal row']),
    ('def row with no INCLUDE_ASM_LIT', 'ico2/b.c', H + 'INCLUDE_ASM(i);\nINCLUDE_ASM(j);\n',
     ['gives i def literal rows']),
    ('INCLUDE_ASM_LIT twice', 'ico2/b.c',
     H + 'INCLUDE_ASM_LIT(i);\nINCLUDE_ASM_LIT(i);\nINCLUDE_ASM(i);\nINCLUDE_ASM(j);\n',
     ['INCLUDE_ASM_LIT(i) a second time']),
    ('a row in= its .c.inc: the line there', 'ico2/c_part.c.inc', H + 'INCLUDE_ASM(k);\n', []),
    ('a row in= its .c.inc: the TU includes it', 'ico2/c.c', '#include "c_part.c.inc"\n', []),
    ('a row in= its .c.inc: the line in the TU', 'ico2/c.c', H + '#include "c_part.c.inc"\nINCLUDE_ASM(k);\n',
     ['INCLUDE_ASM(k): its row names ico2/c_part.c.inc, not this file',
      'includes include_asm.h with no listed stub']),
    ('a row in= a .c.inc the TU does not include', 'ico2/c.c', 'int x;\n',
     ['puts k in ico2/c_part.c.inc, which this file does not include']),
    ('an inline row of a .c.inc: INCLUDE_ASM_LIT at its definition there', 'ico2/d_part.c.inc',
     H + 'inline int m(void);\n\nINCLUDE_ASM_LIT(m);\n', []),
    ('an inline row of a .c.inc: INCLUDE_ASM at the end of the TU', 'ico2/d.c',
     H + '#include "d_part.c.inc"\n\nint f(void)\n{\n    return 0;\n}\n\nINCLUDE_ASM(m);\n', []),
    ('an inline row of a .c.inc: INCLUDE_ASM in the .c.inc', 'ico2/d_part.c.inc',
     H + 'INCLUDE_ASM_LIT(m);\n\nINCLUDE_ASM(m);\n', ['INCLUDE_ASM(m): its row names ico2/d.c, not this file']),
]


def self_test():
    """rule 8 on the shapes above, against a list of six rows."""
    def row(stem, tu, src=None, line=1, inline=False):
        return dict(name=stem, stem=stem, tu=tu, src=src or tu, line=line, asm=tu if inline else src or tu)
    stubs = {'g': row('g', 'ico2/a.c'), 'h': row('h', 'ico2/a.c', line=2), 'i': row('i', 'ico2/b.c', line=3),
             'j': row('j', 'ico2/b.c', line=4), 'k': row('k', 'ico2/c.c', 'ico2/c_part.c.inc', line=5),
             'm': row('m', 'ico2/d.c', 'ico2/d_part.c.inc', line=6, inline=True)}
    failed = 0
    for name, f, text, want in SELF_TEST:
        bad = []
        mine = {k: r for k, r in stubs.items() if f in (r['tu'], r['src'])}
        check_stubs(f, text.split('\n'), mine, bad, {'i', 'm'})
        ok = len(bad) == len(want) and all(w in b for w, b in zip(want, bad))
        failed += not ok
        print(f'check_dev_native: self-test {"ok  " if ok else "FAIL"} {name}'
              + ('' if ok else ': ' + ('; '.join(bad) or 'nothing refused')), file=sys.stderr)
    print(f'check_dev_native: self-test {len(SELF_TEST) - failed} of {len(SELF_TEST)} as expected', file=sys.stderr)
    return 1 if failed else 0


def main(argv):
    if '--self-test' in argv:
        return self_test()
    files = staged_or_all(argv)
    # keyed by stem, the name INCLUDE_ASM spells; a literal row (lit4, rdlit,
    # sdlit) has no line of its own
    rows = parse_stubs()
    stubs = {r['stem']: r for r in rows if r['section'] not in LITERALS}
    lit = {r['stem'] for r in rows if r['at_def']}
    # a staged change to the stub list checks every file it names
    if '--all' not in argv and not os.environ.get('FILES'):
        staged = subprocess.run(['git', 'diff', '--cached', '--name-only'], cwd=ROOT,
                                capture_output=True, text=True).stdout.split()
        if os.path.relpath(STUB_LIST, ROOT) in staged:
            files += [t for t in dict.fromkeys(x for r in stubs.values() for x in (r['tu'], r['src']))
                      if t not in files]
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
        rel = f
        check_stubs(rel, L, stubs, bad, lit)
        newlib = rel.startswith('sce/libc/')
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
                # The sce/ archive asm exception: a member of an SDK archive under sce/
                # (never ico2/, never the public libc/libm/libgcc sources) may keep an empty
                # asm statement standing in for Sony's own text when the site is allowlisted
                # as `path:asm:function | reason` AND a RECONSTRUCTION comment sits within
                # the twelve lines above it; the allowlist row names the evidence.
                fn = enclosing_function(L, i)
                sdk = rel.startswith('sce/') and not rel.startswith(('sce/libc/', 'sce/libm/', 'sce/libgcc/'))
                marked = any('RECONSTRUCTION' in L[k] for k in range(max(0, i - 12), i))
                if not (sdk and fn and marked and f'{f}:asm:{fn}' in allow):
                    bad.append(f'{f}:{i+1}: empty inline asm')
            if PIN_MACRO.search(l):
                bad.append(f'{f}:{i+1}: retired pin macro')
            if ALIAS.search(l) and not PIN.search(l):
                bad.append(f'{f}:{i+1}: symbol alias (an asm label on a declaration)')
            if PIN.search(l) or (ASM_OPEN.search(l) and not EMPTY_ASM.search(l)):
                fn = enclosing_function(L, i)
                if fn is None and not PIN.search(l):
                    # a file-scope asm block: every function it defines is judged by
                    # the listing on its own name (rule 6: a compiled-C function typed
                    # out as asm is written as C instead)
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
                                bad.append(f'{f}:{i+1}: file-scope asm defines {g}, which the listing attributes to {n} source lines of {src} (compiled C typed out as asm: write it as C)')
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
