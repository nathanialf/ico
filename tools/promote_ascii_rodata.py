#!/usr/bin/env python3
"""promote_ascii_rodata.py — promote printable-ASCII debug strings from
auto-regenerated `*_data.c` sidecars into their tracked main TU file as
typed `const char` literals.

Companion to `promote_jp_rodata.py`. The JP promoter picks up
EUC-JP strings; this one picks up pure-ASCII strings (typically the
ANSI-color-coded debug strings like `\\x1b[31m...\\x1b[0m`) that the
JP promoter rejects for lack of JP codepoints. The two are
mutually exclusive by construction: ASCII bytes are all in
[0x20, 0x7E] (plus tab/LF/CR/ESC), so any string the ASCII
predicate accepts cannot contain the high-bit bytes EUC-JP needs.

Usage:
    tools/promote_ascii_rodata.py                 # all TUs
    tools/promote_ascii_rodata.py Basic clothTest # subset
    tools/promote_ascii_rodata.py --dry-run       # preview only
"""
from __future__ import annotations
import argparse
import glob
import os
import re
import struct
import sys


# Tab, LF, CR, ESC (for ANSI color codes), plus printable ASCII.
ASCII_OK_SET = frozenset(b"\t\n\r\x1b") | frozenset(range(0x20, 0x7F))
MIN_STRING_LEN = 4


def ascii_decode_ok(b: bytes) -> tuple[bool, str]:
    """Return (ok, preview_string). True iff `b` strips to a non-empty
    sequence of allowed ASCII bytes followed by NUL termination, length
    >= MIN_STRING_LEN before the NULs."""
    if not b:
        return False, ''
    s_end = len(b)
    while s_end > 0 and b[s_end - 1] == 0:
        s_end -= 1
    if s_end < MIN_STRING_LEN:
        return False, ''
    candidate = b[:s_end]
    if 0 in candidate:
        return False, ''
    for byte in candidate:
        if byte not in ASCII_OK_SET:
            return False, ''
    # Build a printable preview for the comment — replace ESC with
    # `<ESC>` so reviewers can read the intent at a glance.
    preview = (candidate
               .decode('ascii', errors='replace')
               .replace('\x1b', '<ESC>')
               .replace('\n', '<LF>')
               .replace('\r', '<CR>')
               .replace('\t', '<TAB>'))
    return True, preview


def c_escape(raw: bytes) -> str:
    """Emit a C string literal body. Same shape as promote_jp_rodata."""
    out = []
    for b in raw:
        if b == 0x0A:
            out.append('\\n')
        elif b == 0x09:
            out.append('\\t')
        elif b == 0x0D:
            out.append('\\r')
        elif b == 0x22:
            out.append('\\"')
        elif b == 0x5C:
            out.append('\\\\')
        elif 0x20 <= b <= 0x7E:
            out.append(chr(b))
        else:
            out.append(f'\\{b:03o}')
    return ''.join(out)


PAT = re.compile(
    r'__attribute__\(\(section\("\.(rodata|data|lit4|sdata)\.0x([0-9A-Fa-f]+)"\)\)\)\s+'
    r'(const\s+)?(unsigned\s+int|unsigned\s+char|int|char)\s+'
    r'D_([0-9A-Fa-f]{8})(\[(\d+)\])?\s*=\s*\{([^}]*)\};'
)


def scan_sidecar(path):
    """Yield (vma, section, n, raw, preview) for each ASCII symbol."""
    text = open(path).read()
    for m in PAT.finditer(text):
        section = m.group(1)
        vma = int(m.group(2), 16)
        ctype = m.group(4)
        body = m.group(8)
        items = [x.strip() for x in body.split(',') if x.strip()]
        raw = b''
        try:
            if 'int' in ctype:
                for it in items:
                    v = int(it, 0)
                    raw += struct.pack('<I', v & 0xFFFFFFFF)
            elif 'char' in ctype:
                for it in items:
                    v = int(it, 0)
                    raw += bytes([v & 0xFF])
        except ValueError:
            continue
        if not raw:
            continue
        ok, preview = ascii_decode_ok(raw)
        if not ok:
            continue
        yield (vma, section, len(raw), raw, preview)


def find_main(tu):
    for cand in (f'src/{tu}.c',):
        if os.path.exists(cand):
            return cand
    for p in glob.glob(f'src/**/{tu}.c', recursive=True):
        return p
    return None


def already_has(main_text, vma):
    return f'D_{vma:08X}' in main_text and f'.0x{vma:08X}' in main_text


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument('tus', nargs='*',
                    help='restrict to listed TUs (basename, e.g. Basic)')
    ap.add_argument('--dry-run', action='store_true',
                    help='preview what would be promoted; no file edits')
    args = ap.parse_args()

    tus_filter = set(args.tus)
    sidecars = sorted(glob.glob('src/**/*_data.c', recursive=True))
    total_added = 0
    total_files = 0
    for sc in sidecars:
        tu = os.path.basename(sc)[:-len('_data.c')]
        if tus_filter and tu not in tus_filter:
            continue
        main_path = find_main(tu)
        if main_path is None:
            continue
        main_text = open(main_path).read()
        new_lines = []
        for vma, section, n, raw, preview in scan_sidecar(sc):
            if already_has(main_text, vma):
                continue
            esc = c_escape(raw.rstrip(b'\x00'))
            new_lines.append(
                f'/* ASCII preview: "{preview}" */\n'
                f'__attribute__((section(".{section}.0x{vma:08X}"))) '
                f'const char D_{vma:08X}[{n}] = "{esc}";'
            )
        if not new_lines:
            continue
        block = (
            '\n/* ASCII debug strings — re-derived from EE rodata bytes.\n'
            ' * Octal escapes preserve byte-identical layout without\n'
            ' * requiring source-encoding compiler flags. */\n'
            + '\n'.join(new_lines)
            + '\n'
        )
        if args.dry_run:
            print(f'-- {main_path}: would append {len(new_lines)} symbols')
            for line in new_lines:
                print('   ' + line.splitlines()[0])
        else:
            if not main_text.endswith('\n'):
                block = '\n' + block
            with open(main_path, 'a', encoding='utf-8') as f:
                f.write(block)
            print(f'{main_path}: appended {len(new_lines)} symbols')
        total_added += len(new_lines)
        total_files += 1
    verb = 'would add' if args.dry_run else 'added'
    print(f'\nTotal: {total_added} symbols {verb} across {total_files} TU(s)')


if __name__ == '__main__':
    main()
