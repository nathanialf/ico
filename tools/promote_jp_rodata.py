#!/usr/bin/env python3
"""promote_jp_rodata.py — promote EUC-JP debug strings from auto-regenerated
*_data.c sidecars into their tracked main TU file as typed `const char`
literals (octal escapes). The sidecars are gitignored and will drop the
duplicate definitions on the next migrate_data_per_tu run.

Usage: tools/promote_jp_rodata.py [TU ...]   # default: all TUs
"""
from __future__ import annotations
import re, os, struct, glob, sys


def euc_decode_ok(b):
    if not b:
        return False, ''
    s_end = len(b)
    while s_end > 0 and b[s_end - 1] == 0:
        s_end -= 1
    if s_end == 0:
        return False, ''
    candidate = b[:s_end]
    if 0 in candidate:
        return False, ''
    try:
        s = candidate.decode('euc_jp', errors='strict')
    except UnicodeDecodeError:
        return False, ''
    has_jp = any(
        0x3000 <= ord(c) <= 0x9FFF or 0xFF00 <= ord(c) <= 0xFFEF for c in s
    )
    return has_jp, s


def c_escape(raw: bytes) -> str:
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
    """Yield (vma, section, n, raw, decoded) for each Japanese symbol."""
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
        ok, dec = euc_decode_ok(raw)
        if not ok:
            continue
        yield (vma, section, len(raw), raw, dec)


def find_main(tu):
    for cand in (f'src/{tu}.c',):
        if os.path.exists(cand):
            return cand
    for p in glob.glob(f'src/**/{tu}.c', recursive=True):
        return p
    return None


def already_has(main_text, vma):
    return f'D_{vma:08X}' in main_text and f'.rodata.0x{vma:08X}' in main_text


def main():
    tus_filter = set(sys.argv[1:])
    sidecars = sorted(glob.glob('src/**/*_data.c', recursive=True))
    total_added = 0
    for sc in sidecars:
        tu = os.path.basename(sc)[:-len('_data.c')]
        if tus_filter and tu not in tus_filter:
            continue
        main = find_main(tu)
        if main is None:
            continue
        main_text = open(main).read()
        new_lines = []
        for vma, section, n, raw, dec in scan_sidecar(sc):
            if already_has(main_text, vma):
                continue
            esc = c_escape(raw.rstrip(b'\x00'))
            new_lines.append(
                f'/* EUC-JP: "{dec}" */\n'
                f'__attribute__((section(".{section}.0x{vma:08X}"))) '
                f'const char D_{vma:08X}[{n}] = "{esc}";'
            )
        if not new_lines:
            continue
        block = (
            '\n/* EUC-JP debug strings — re-derived from EE rodata bytes via\n'
            ' * EUC-JP decoding. Octal escapes preserve byte-identical layout\n'
            ' * without requiring source-encoding compiler flags. */\n'
            + '\n'.join(new_lines)
            + '\n'
        )
        if not main_text.endswith('\n'):
            block = '\n' + block
        with open(main, 'a', encoding='utf-8') as f:
            f.write(block)
        print(f'{main}: appended {len(new_lines)} symbols')
        total_added += len(new_lines)
    print(f'\nTotal: {total_added} symbols added')


if __name__ == '__main__':
    main()
