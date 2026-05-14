#!/usr/bin/env python3
"""
Split array defs in *_data.c sidecars whose VMA is not 8-aligned, since
ee-gcc 2.9 forces 2**3 section alignment on any array (regardless of
element type) but only 2**N (matching element natural alignment) on
scalars. Sections claiming 4-aligned VMAs end up linker-bumped to the
next 8-byte boundary, accumulating drift.

Transform:
  unsigned int X[N] = { v0, v1, v2, ... };   @ vma (vma % 8 != 0)
becomes:
  unsigned int X = v0;                       @ vma
  unsigned int _pad_VMA4[N-1] = { v1, v2, ... };  @ vma+4 (now 8-aligned)

If N == 1, just emit scalar.

Same approach for `unsigned char[N]` at 4-aligned-only VMAs — emit
trailing bytes one-by-one until reaching an 8-aligned VMA, then array.
"""
import re, sys
from pathlib import Path

PAT = re.compile(
    r'__attribute__\(\(section\("\.(?P<sect>[\w.]+?)\.0x(?P<vma>[0-9A-Fa-f]+)"\)\)\)\s+'
    r'(?P<ty>unsigned\s+(?:int|char|short)|void\s*\*)\s*'
    r'(?P<sym>\w+)\s*\[(?P<n>\d+)\]\s*=\s*\{(?P<body>[^}]*)\}\s*;\s*$'
)

ELEM_SIZE = {'unsigned int': 4, 'unsigned char': 1, 'unsigned short': 2, 'void *': 4}


def _normalize_ty(ty: str) -> str:
    """Collapse internal whitespace so `void *` and `void*` map to the
    same key in ELEM_SIZE."""
    if 'void' in ty and '*' in ty:
        return 'void *'
    return ' '.join(ty.split())


def split_line(line: str) -> list[str]:
    m = PAT.match(line)
    if not m:
        return [line]
    sect = m.group('sect')
    vma = int(m.group('vma'), 16)
    ty = _normalize_ty(m.group('ty'))
    sym = m.group('sym')
    n = int(m.group('n'))
    body = m.group('body').strip()
    if vma % 8 == 0:
        return [line]

    # Parse element values from body
    elems = [e.strip() for e in body.split(',') if e.strip()]
    if len(elems) != n:
        # Could be { 0 } shorthand expanding; for those, just leave as-is.
        return [line]
    es = ELEM_SIZE[ty]
    out = []
    cursor_vma = vma
    cursor_i = 0
    while cursor_i < n:
        if cursor_vma % 8 == 0:
            # Remaining elements can be array form
            remaining = n - cursor_i
            if remaining == 1:
                out.append(
                    f'__attribute__((section(".{sect}.0x{cursor_vma:08X}"))) '
                    f'{ty} {sym if cursor_i == 0 else f"_pad_{cursor_vma:08X}"} = {elems[cursor_i]};'
                )
                cursor_i += 1
                cursor_vma += es
                continue
            arr_name = sym if cursor_i == 0 else f"_pad_{cursor_vma:08X}"
            out.append(
                f'__attribute__((section(".{sect}.0x{cursor_vma:08X}"))) '
                f'{ty} {arr_name}[{remaining}] = {{ {", ".join(elems[cursor_i:])} }};'
            )
            cursor_i = n
            cursor_vma = vma + es * n
            continue
        # Emit scalar for this element
        name = sym if cursor_i == 0 else f"_pad_{cursor_vma:08X}"
        out.append(
            f'__attribute__((section(".{sect}.0x{cursor_vma:08X}"))) '
            f'{ty} {name} = {elems[cursor_i]};'
        )
        cursor_i += 1
        cursor_vma += es
    return out


def process(path: Path) -> int:
    text = path.read_text()
    out_lines = []
    changed = 0
    for line in text.splitlines():
        new = split_line(line)
        if len(new) > 1 or (new and new[0] != line):
            changed += 1
        out_lines.extend(new)
    if changed:
        path.write_text('\n'.join(out_lines) + '\n')
    return changed


def main():
    import glob
    # Walk every source root: src/, plus the original ICO sibling
    # subsystems ios/, sound/, isys/ (relocated to repo root).
    files: list[str] = []
    for root in ("src", "ios", "sound", "isys"):
        files += sorted(glob.glob(f"{root}/**/*_data.c", recursive=True))
    files.sort()
    total = 0
    for f in files:
        c = process(Path(f))
        if c:
            print(f'{f}: split {c} array defs')
            total += c
    print(f'\nTotal splits: {total}')


if __name__ == '__main__':
    main()
