#!/usr/bin/env python3
"""
extern_sdata_lit4.py — convert all .sdata/.lit4 defs to extern in
tracked TUs that contain INCLUDE_ASM consumers.

Policy (memory lit4_gp_rel_extern): in any coalesced TU's tracked
.c/.h, every .sdata/.lit4 def must be an `extern` decl so ee-gcc
emits compact %gp_rel codegen for INCLUDE_ASM'd consumers. The
typed def regenerates in the gitignored <TU>_data.c sidecar.

Idempotent: skips defs already converted to extern. Run from repo
root. Prints a summary; exits 0 even if nothing changed.
"""
import re, glob, os, sys
from pathlib import Path

REPO = Path(__file__).resolve().parent.parent
ROOTS = ['src', 'ios', 'sound', 'isys']

# Match the def head; the initializer is parsed separately so we can
# skip past `;` inside string literals (e.g., `const char D_X[8] = ";1";`).
DEF_HEAD_RE = re.compile(
    r'__attribute__\(\(section\("(\.(?:sdata|lit4)\.0x[0-9A-Fa-f]+)"\)\)\)\s+'  # attr
    r'(.+?)'                                                                      # type
    r'(D_[0-9A-Fa-f]+(?:\[[^\]]*\])?)'                                           # name
    r'\s*=\s*',                                                                   # =
    re.MULTILINE,
)


def _skip_initializer(text: str, start: int) -> int:
    """Return the index just past the terminating ';' of an initializer
    starting at `start`. Handles string + char literals (including escape
    sequences) and balanced braces. Raises ValueError if no terminator."""
    i = start
    n = len(text)
    brace_depth = 0
    while i < n:
        c = text[i]
        if c == '"' or c == "'":
            quote = c
            i += 1
            while i < n:
                if text[i] == '\\':
                    i += 2
                    continue
                if text[i] == quote:
                    i += 1
                    break
                i += 1
            continue
        if c == '{':
            brace_depth += 1
            i += 1
            continue
        if c == '}':
            brace_depth -= 1
            i += 1
            continue
        if c == ';' and brace_depth == 0:
            return i + 1
        i += 1
    raise ValueError(f'unterminated initializer at offset {start}')


def convert_file(path: Path) -> tuple[int, str]:
    """Return (n_converted, new_text). n=0 means no change."""
    text = path.read_text()
    converted = 0
    out = []
    last = 0
    for m in DEF_HEAD_RE.finditer(text):
        end = _skip_initializer(text, m.end())
        out.append(text[last:m.start()])
        type_part = m.group(2).strip()
        name = m.group(3)
        out.append(f'extern {type_part} {name};')
        last = end
        converted += 1
    out.append(text[last:])
    return converted, ''.join(out)


def main() -> int:
    candidates: list[Path] = []
    for r in ROOTS:
        for f in glob.glob(str(REPO / r / '*.c')):
            p = Path(f)
            if p.name.endswith('_data.c'):
                continue
            text = p.read_text()
            if 'INCLUDE_ASM(' in text:
                candidates.append(p)
                h = p.with_suffix('.h')
                if h.exists():
                    candidates.append(h)

    total = 0
    changed_files = 0
    for p in candidates:
        n, new = convert_file(p)
        if n > 0:
            p.write_text(new)
            print(f'  {p.relative_to(REPO)}: extern\'d {n}')
            total += n
            changed_files += 1
    print(f'\nTotal: extern\'d {total} defs across {changed_files} files '
          f'(out of {len(candidates)} INCLUDE_ASM TUs).')
    return 0


if __name__ == '__main__':
    sys.exit(main())
