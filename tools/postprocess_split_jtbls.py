#!/usr/bin/env python3
"""
postprocess_split_jtbls.py — split each gcc-emitted switch jtbl into its
own typed `.rodata.0x<VMA>` section so the linker can place them at the
correct VMAs.

ee-gcc 2.9 emits every switch jtbl into a single `.rdata` section; the
linker would otherwise concatenate them in one slot. When a TU has
multiple matched switch funcs (e.g. src/box.c: func_001BE558 +
func_001BF2C8), splat extracts the original jtbls into separate
`.rodata.0x<jtbl_vma>` sections; without splitting on the C-build side,
non-jtbl rodata that sits BETWEEN those jtbls in the original layout
(e.g. a string at the gap VMA) gets pushed forward, breaking SHA-1.

This pass:
  1. Walks `.text` to map every `$L<id>:` label to its owning function
     (via preceding `.globl <funcname>` directive).
  2. For each `.rdata`/`.rodata` block containing a jtbl (one or more
     `.word $L<id>` entries following a `$L<base>:` label), looks at
     the first target `$L<id>` to find the owning function name.
  3. Reads `asm/matchings/**/funcname.s` (or `nonmatchings/`) and pulls
     out every `%hi(jtbl_<VMA>)` reference in source order.
  4. Pops the next jtbl VMA off that list for the function and rewrites
     the `.rdata` directive to `.rodata.0x<VMA>` so the linker's typed
     KEEP entry at that VMA picks it up.

If no matchings .s exists yet (first compile pass) or the function has
no jtbl references, the block is left as `.rdata` — matches the
single-jtbl-per-TU behavior already supported by postprocess_slinky_ld.

Idempotent: re-applies harmlessly because any block already on a
`.rodata.0x<VMA>` section is left alone.
"""
from __future__ import annotations

import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

GLOBL_RE = re.compile(r"^\s*\.globl\s+(\S+)")
FUNC_LABEL_RE = re.compile(r"^\s*(func_[0-9A-Fa-f]{8})\s*:")
L_LABEL_RE = re.compile(r"^\s*(\$L\d+)\s*:")
RDATA_RE = re.compile(r"^\s*\.r(?:o)?data\s*$")
RODATA_VMA_RE = re.compile(r"^\s*\.rodata\.0x[0-9A-Fa-f]+\b")
WORD_LABEL_RE = re.compile(r"^\s*\.word\s+(\$L\d+)\b")
SECTION_END_RE = re.compile(r"^\s*\.(text|rodata|rdata|data|sdata|bss|sbss|lit4|section)\b")
JTBL_REF_RE = re.compile(r"%hi\(jtbl_([0-9A-Fa-f]{8})\)")


def _function_jtbl_refs(func_name: str) -> list[str]:
    """Return jtbl VMAs (hex, no '0x') referenced by `func_name`, in
    source order. Looks in asm/matchings then asm/nonmatchings."""
    for ext in ("matchings", "nonmatchings"):
        base = ROOT / "asm" / ext
        if not base.is_dir():
            continue
        for s_file in base.rglob(f"{func_name}.s"):
            try:
                text = s_file.read_text()
            except Exception:
                continue
            out: list[str] = []
            for m in JTBL_REF_RE.finditer(text):
                vma = m.group(1).upper()
                if not out or out[-1] != vma:
                    out.append(vma)
            if out:
                return out
    return []


def _map_labels_to_functions(lines: list[str]) -> dict[str, str]:
    """Walk the .s and return {label_name: owning_func_name} for every
    $L<n>: label inside a function. Functions are framed by an
    immediately-preceding `.globl funcname` directive followed by
    `funcname:`."""
    label_to_func: dict[str, str] = {}
    cur_func: str | None = None
    in_text = True  # gcc emits .text by default at start; flip on directives
    last_globl: str | None = None
    for ln in lines:
        # Track section
        if re.match(r"^\s*\.text\s*$", ln):
            in_text = True
            continue
        if RDATA_RE.match(ln) or RODATA_VMA_RE.match(ln):
            in_text = False
            continue
        if re.match(r"^\s*\.(data|sdata|bss|sbss|lit4|section)\b", ln):
            in_text = False
            continue

        m = GLOBL_RE.match(ln)
        if m:
            last_globl = m.group(1)
            continue

        m = FUNC_LABEL_RE.match(ln)
        if m and m.group(1) == last_globl:
            cur_func = m.group(1)
            continue

        if not in_text:
            continue

        m = L_LABEL_RE.match(ln)
        if m and cur_func is not None:
            label_to_func[m.group(1)] = cur_func

    return label_to_func


def transform(text: str) -> str:
    lines = text.splitlines(keepends=True)
    label_to_func = _map_labels_to_functions(lines)
    # Per-function index into its jtbl ref list.
    func_jtbl_cursor: dict[str, int] = {}
    func_jtbl_cache: dict[str, list[str]] = {}

    out: list[str] = []
    i = 0
    n = len(lines)
    while i < n:
        ln = lines[i]
        if not RDATA_RE.match(ln):
            out.append(ln)
            i += 1
            continue

        # Found a bare .rdata directive — scan forward to find the
        # jtbl's first .word target.
        j = i + 1
        first_target: str | None = None
        while j < n:
            jline = lines[j]
            # Stop at a section change (other than .rdata itself).
            if SECTION_END_RE.match(jline) and not RDATA_RE.match(jline):
                break
            m = WORD_LABEL_RE.match(jline)
            if m:
                first_target = m.group(1)
                break
            j += 1

        if first_target is None:
            out.append(ln)
            i += 1
            continue

        func = label_to_func.get(first_target)
        if func is None:
            out.append(ln)
            i += 1
            continue

        if func not in func_jtbl_cache:
            func_jtbl_cache[func] = _function_jtbl_refs(func)
            func_jtbl_cursor[func] = 0

        cursor = func_jtbl_cursor[func]
        refs = func_jtbl_cache[func]
        if cursor >= len(refs):
            # No matching jtbl ref to rewrite to.
            out.append(ln)
            i += 1
            continue

        vma = refs[cursor]
        func_jtbl_cursor[func] = cursor + 1

        # Replace .rdata with .rodata.0x<VMA>.
        # Preserve leading whitespace of the original directive.
        prefix = re.match(r"^(\s*)", ln).group(1)
        out.append(f'{prefix}.section .rodata.0x{vma},"a",@progbits\n')
        i += 1

    return "".join(out)


def main(argv: list[str]) -> int:
    if len(argv) != 2:
        print("usage: postprocess_split_jtbls.py <path.s>", file=sys.stderr)
        return 2
    p = Path(argv[1])
    src = p.read_text()
    out = transform(src)
    if out != src:
        p.write_text(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
