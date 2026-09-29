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
single-jtbl-per-TU behavior the per-TU section glob in the linker
script already handles.

One case is left entirely unsplit (2026-09-27, chain 2 pass 85): a TU
with a single `.rodata` carve row in config/ico.<ver>.yaml, a single jtbl
block that is the FIRST `.rdata` block gcc emits, and NO named
`-fdata-sections` rodata section (`.section .rodata.<name>`) anywhere in
the file. Such a TU gets one `(.rodata*)` glob, and the compiler's single
`.rdata` section is the ROM's layout: the table, its pad and the anonymous
constants after it (initialiser templates, doubles, strings) sit where
gcc's own `.align` directives put them. Splitting the table out leaves
those constants in a second section whose own alignment (16 when it holds
a 16-byte object) moves them off their ROM address (motionManager's
dispSkeltonHierarchy templates: the ROM has them 8-aligned right after the
table). The three conditions are exactly what keeps the merged section
equal to the ROM: with named sections between the blocks (queen, four
anonymous blocks before the table in motionManager2) the split stays, as
measured on the whole tree the same day. The driver passes the TU's
repo-relative source path as the second argument; with no second argument
the split runs as before.

Since 2026-09-29 (girl_act, pass sgw2) the one-row case is general: a TU
with exactly ONE `.rodata` carve row and no named `.rodata.<name>` object
keeps every jump table in the compiler's section unsplit whenever that
section carries data after a table. The row owns the TU's whole .rodata run, so the section as gcc and
the assembler lay it out (strings, tables, anonymous constants, interned
doubles, in emission order) is the ROM's layout, and splitting would pull
the tables out from between the data (girl_act: eight tables among its
strings). Where every table comes after the section's data the split stays,
since it only moves the tables' 16-byte alignment off the section: measured
the same day, unsplitting libkernl_25EF18 (strings, then one table) moved
its run from 0x636628 to 0x636630. Named sections keep the split too, as
the first case above says: unsplitting motionManager2 (a table after four
named sections) and queen (27 named sections, data after its table) broke
both layouts. The three conditions above still decide a TU that has no
`.rodata` row at all.

A second case keeps ONE table in the compiler's section (2026-09-28, chain 1
pass 155): in a TU with several `.rodata` rows, the unnamed `.rodata` goes to
the row marked `plain-rodata` (tools/gen_ninja.py). When a jtbl's VMA is the
start of that plain row and the row's `syms:` list does not name it, the
table stays in the unnamed section, with the pad and the anonymous constants
gcc emits after it, exactly as the ROM lays them out (motionManager: once
_getFinalMatrix's table at 0x61FBE0 is compiled, _getGeometryOfMotion's table
at 0x620030 must stay with dispSkeltonHierarchy's 8-aligned templates). Every
other table is still split.

Idempotent: re-applies harmlessly because any block already on a
`.rodata.0x<VMA>` section is left alone.
"""
from __future__ import annotations

import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

GLOBL_RE = re.compile(r"^\s*\.globl\s+(\S+)")
# Any C-identifier label; the `== last_globl` guard in _map_labels_to_functions
# restricts it to the actually-.globl'd function entry, so named-symbol funcs
# (e.g. pac_continueTag) get their $L labels mapped too — not just func_XXXX ones.
FUNC_LABEL_RE = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*:")
L_LABEL_RE = re.compile(r"^\s*(\$L\d+)\s*:")
RDATA_RE = re.compile(r"^\s*\.r(?:o)?data\s*$")
RODATA_VMA_RE = re.compile(r"^\s*\.rodata\.0x[0-9A-Fa-f]+\b")
WORD_LABEL_RE = re.compile(r"^\s*\.word\s+(\$L\d+)\b")
SECTION_END_RE = re.compile(r"^\s*\.(text|rodata|rdata|data|sdata|bss|sbss|lit4|section)\b")
JTBL_REF_RE = re.compile(r"%hi\(jtbl_([0-9A-Fa-f]{8})\)")


def _function_jtbl_refs(func_name: str) -> list[str]:
    """Return jtbl VMAs (hex, no '0x') referenced by `func_name`, in
    source order. Looks in asm/[<version>/]{matchings,nonmatchings}."""
    version = os.environ.get("VERSION", "")
    bases = []
    if version:
        bases += [ROOT / "asm" / version / "matchings",
                  ROOT / "asm" / version / "nonmatchings"]
    bases += [ROOT / "asm" / "matchings", ROOT / "asm" / "nonmatchings"]
    for base in bases:
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


def transform(text: str, keep: frozenset[str] = frozenset()) -> str:
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
        if vma in keep:
            # the table heads its TU's plain-rodata row: it stays in `.rdata`
            out.append(ln)
            i += 1
            continue

        # Replace .rdata with .rodata.0x<VMA>.
        # Preserve leading whitespace of the original directive.
        prefix = re.match(r"^(\s*)", ln).group(1)
        out.append(f'{prefix}.section .rodata.0x{vma},"a",@progbits\n')
        i += 1

    return "".join(out)


def _rodata_row_count(tu_src: str) -> int:
    """Number of `.rodata` carve rows the version yaml gives the TU named by
    its repo-relative source path (`ico2/sugipon/src/motionManager.c`)."""
    tu = re.sub(r"\.c$", "", tu_src.replace("\\", "/"))
    if tu.startswith(str(ROOT) + "/"):
        tu = tu[len(str(ROOT)) + 1:]
    yamls = sorted((ROOT / "config").glob("ico.*.yaml"))
    if not yamls:
        return 0
    n = 0
    for line in yamls[0].read_text().splitlines():
        m = re.match(r"\s*-\s*\[0x[0-9A-Fa-f]+,\s*\.rodata,\s*(\S+?)\]", line)
        if m and m.group(1) == tu:
            n += 1
    return n


def _plain_row_tables(tu_src: str) -> frozenset[str]:
    """VMAs (8 hex digits, upper case) of the TU's `plain-rodata` rows whose
    `syms:` list does not name that VMA: a jtbl there stays unsplit."""
    tu = re.sub(r"\.c$", "", tu_src.replace("\\", "/"))
    if tu.startswith(str(ROOT) + "/"):
        tu = tu[len(str(ROOT)) + 1:]
    yamls = sorted((ROOT / "config").glob("ico.*.yaml"))
    if not yamls:
        return frozenset()
    keep = set()
    for line in yamls[0].read_text().splitlines():
        m = re.match(r"\s*-\s*\[0x([0-9A-Fa-f]+),\s*\.rodata,\s*(\S+?)\]\s*(#.*)?$", line)
        if not m or m.group(2) != tu or "plain-rodata" not in (m.group(3) or ""):
            continue
        vma = "%08X" % (int(m.group(1), 16) + 0x100000)
        sm = re.search(r"syms:\s*([\w,\s]+?)(?:\s{2,}|;|$)", m.group(3))
        named = {x.upper().replace("0X", "") for x in re.split(r"[,\s]+", sm.group(1)) if x} if sm else set()
        if vma not in named:
            keep.add(vma)
    return frozenset(keep)


def _has_named_rodata(text: str) -> bool:
    """True when -fdata-sections gave a named rodata object its own
    `.section .rodata.<name>`."""
    return any(re.match(r"^\s*\.section\s+\.rodata\.", l) for l in text.splitlines())


DATA_DIRECTIVE_RE = re.compile(r"^\s*\.(ascii|asciz|byte|half|short|word|dword|float|double|space)\b")


def _tables_interleave(text: str) -> bool:
    """True when the compiler's `.rdata` carries data after a jump table:
    splitting the tables out would then reorder the section."""
    lines = text.splitlines()
    seen_table = False
    for k, l in enumerate(lines):
        if not RDATA_RE.match(l):
            continue
        is_jtbl = False
        has_data = False
        j = k + 1
        while j < len(lines):
            if SECTION_END_RE.match(lines[j]) and not RDATA_RE.match(lines[j]):
                break
            if WORD_LABEL_RE.match(lines[j]):
                is_jtbl = True
            elif DATA_DIRECTIVE_RE.match(lines[j]):
                has_data = True
            j += 1
        if is_jtbl:
            seen_table = True
        elif has_data and seen_table:
            return True
    return False


def _keep_compiler_section(text: str) -> bool:
    """True when the file has exactly one jtbl block, it is the first `.rdata`
    block, and no named `.section .rodata.<name>` appears anywhere."""
    lines = text.splitlines()
    if any(re.match(r"^\s*\.section\s+\.rodata\.", l) for l in lines):
        return False
    jtbl_blocks = 0
    first_is_jtbl = None
    for k, l in enumerate(lines):
        if not RDATA_RE.match(l):
            continue
        j = k + 1
        is_jtbl = False
        while j < len(lines):
            if SECTION_END_RE.match(lines[j]) and not RDATA_RE.match(lines[j]):
                break
            if WORD_LABEL_RE.match(lines[j]):
                is_jtbl = True
                break
            j += 1
        if first_is_jtbl is None:
            first_is_jtbl = is_jtbl
        jtbl_blocks += is_jtbl
    return jtbl_blocks == 1 and bool(first_is_jtbl)


def main(argv: list[str]) -> int:
    if len(argv) not in (2, 3):
        print("usage: postprocess_split_jtbls.py <path.s> [<tu source .c>]", file=sys.stderr)
        return 2
    p = Path(argv[1])
    src = p.read_text()
    if len(argv) == 3:
        rows = _rodata_row_count(argv[2])
        # one `.rodata` row owns the TU's whole run: when the compiler's
        # section carries data after a table and no named rodata object
        # sits beside it, the tables stay where gcc put them
        if (rows == 1 and _tables_interleave(src) and not _has_named_rodata(src)) or (
            rows < 2 and _keep_compiler_section(src)
        ):
            return 0
    keep = _plain_row_tables(argv[2]) if len(argv) == 3 else frozenset()
    out = transform(src, keep)
    if out != src:
        p.write_text(out)
    return 0


if __name__ == "__main__":
    raise SystemExit(main(sys.argv))
