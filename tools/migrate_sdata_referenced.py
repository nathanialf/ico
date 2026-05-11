#!/usr/bin/env python3
"""
migrate_sdata_referenced.py — for every sdata symbol that a matched
src/cod/*.c references via `extern`, add a definition to
src/cod/sdata_pool.c (using `__attribute__((section(".sdata.0xVMA")))`)
and append the symbol name to config/migrated_data_symbols.txt.

The migrated symbols' bytes then come from the src .o instead of the
asm-side blanket sdata.o; the linker uses SORT_BY_NAME to place each
section at its original VMA. The function .c files only see `extern`
declarations, so ee-gcc 2.9 keeps emitting %gp_rel for the references
(the small-data hint is preserved). See tools/rewrite_data_named_sections.py
and the matching `Migrate sdata symbols ...` commit for the architecture.

This script is idempotent: re-running picks up newly-referenced symbols
and skips any already in the migrated list. It only adds — never
removes — entries. Run after claiming new matches that introduce
fresh `extern D_006XXXXX` declarations.

Output:
  * src/cod/sdata_pool.c — appended/extended with new definitions.
  * config/migrated_data_symbols.txt — appended with new symbol names.

Validation: caller runs `make` afterwards to confirm the round-trip
still produces the byte-identical .rom.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = REPO_ROOT / "src" / "cod"
ASM_SDATA = REPO_ROOT / "asm" / "data" / "cod" / "531900.sdata.s"
POOL_C = REPO_ROOT / "src" / "cod" / "sdata_pool.c"
MIGRATED_LIST = REPO_ROOT / "config" / "migrated_data_symbols.txt"

SDATA_VMA_LOW = 0x00631900
SDATA_VMA_HIGH = 0x00633BC6  # exclusive

# Match `extern <type-soup> D_006XXXXX[ ...];` declarations in src .c.
# We use the symbol's VMA suffix to filter to the sdata range; the type
# itself isn't needed for the migration definition (we always emit
# `.word <value>` via the natural initial value below).
EXTERN_RE = re.compile(
    r'\bextern\b[^;]*?\b(D_(?P<vma>[0-9A-Fa-f]{8}))\b',
)

# Match a `dlabel D_006XXXXX ... enddlabel D_006XXXXX` block. We pull
# the `.word`/`.float`/`.byte` etc lines for the initial-value bytes.
DLABEL_RE = re.compile(
    r'^dlabel\s+D_(?P<vma>[0-9A-Fa-f]{8})\s*\n(?P<body>.*?)^enddlabel\s+D_\1\s*$',
    re.MULTILINE | re.DOTALL,
)


def _collect_referenced_sdata_symbols() -> set[str]:
    """Walk src/cod/*.c for `extern D_NNN` declarations; return the
    subset whose VMA falls in the .sdata range."""
    syms: set[str] = set()
    for c_path in SRC_DIR.glob("*.c"):
        if c_path.name == POOL_C.name:
            continue
        text = c_path.read_text()
        for m in EXTERN_RE.finditer(text):
            vma = int(m.group("vma"), 16)
            if SDATA_VMA_LOW <= vma < SDATA_VMA_HIGH:
                syms.add(f"D_{m.group('vma').upper()}")
    return syms


def _load_migrated() -> set[str]:
    if not MIGRATED_LIST.exists():
        return set()
    out: set[str] = set()
    for line in MIGRATED_LIST.read_text().splitlines():
        line = line.split("#", 1)[0].strip()
        if line:
            out.add(line)
    return out


def _parse_asm_blocks() -> dict[str, tuple[int, list[str]]]:
    """Return {symbol: (vma, content_lines)} for every dlabel in
    asm/data/cod/531900.sdata.s. content_lines are the raw .word/.byte/
    .asciz/etc lines (with their address comments) between dlabel and
    enddlabel."""
    if not ASM_SDATA.exists():
        return {}
    text = ASM_SDATA.read_text()
    out: dict[str, tuple[int, list[str]]] = {}
    for m in DLABEL_RE.finditer(text):
        vma = int(m.group("vma"), 16)
        sym = f"D_{m.group('vma').upper()}"
        lines = [l for l in m.group("body").splitlines() if l.strip()]
        out[sym] = (vma, lines)
    return out


def _parse_value_for_definition(lines: list[str]) -> tuple[str, str] | None:
    """Given the data-directive lines of a dlabel block, return
    (c_type, c_initializer) suitable for emitting:
      `<c_type> <sym> = <c_initializer>;`
    inside a `.sdata.0xVMA` named section.

    Only handles the common cases: single .word/.float/.byte/.short and
    multi-word arrays. Returns None for shapes we don't yet auto-handle
    (e.g. asciz strings, structs). Caller can then fall back to an asm
    pool file or leave the symbol on the asm side.
    """
    # Strip address-comment prefix from each line.
    plain = []
    for l in lines:
        s = re.sub(r"^[ \t]*/\*[^*]*\*/\s*", "", l).strip()
        s = re.sub(r"#.*$", "", s).strip()
        if not s or s.startswith("/*"):
            continue
        plain.append(s)
    if not plain:
        return None

    # Single .word integer — emit as `unsigned int = 0xVALUE;`.
    if len(plain) == 1:
        m = re.match(r"\.(?:word|long|4byte)\s+(0x[0-9A-Fa-f]+|-?\d+)$", plain[0])
        if m:
            return ("unsigned int", m.group(1))
        m = re.match(r"\.float\s+(\S+.*)$", plain[0])
        if m:
            # Convert the float literal to its 4-byte IEEE encoding via
            # `.4byte` — splat's adjacent hex comment would give us the
            # exact bits, but we just trust gcc to re-encode the float.
            return ("float", m.group(1))
        m = re.match(r"\.byte\s+(0x[0-9A-Fa-f]+|-?\d+)$", plain[0])
        if m:
            return ("unsigned char", m.group(1))
        m = re.match(r"\.(?:short|hword|half|2byte)\s+(0x[0-9A-Fa-f]+|-?\d+)$", plain[0])
        if m:
            return ("unsigned short", m.group(1))

    # Multi-word: emit as `unsigned int[N] = { ... };`. Skip if any
    # operand looks like a non-constant (symbol reference like `func_X`
    # or `D_X`) — those need a forward declaration and we leave them
    # on the asm side for now.
    words: list[str] = []
    for line in plain:
        m = re.match(r"\.(?:word|long|4byte)\s+(.+)$", line)
        if not m:
            return None
        operand = m.group(1)
        for elt in operand.split(","):
            elt = elt.strip()
            if not elt:
                continue
            # Reject symbol references — only accept integer literals.
            if not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", elt):
                return None
            words.append(elt)
    if not words:
        return None
    inner = ", ".join(words)
    return ("unsigned int", f"{{ {inner} }}")


def _emit_definition(sym: str, vma: int, value_pair) -> list[str] | None:
    """Render the C definition line(s) for sdata_pool.c. Returns a list
    because multi-word symbols are split into one definition per VMA
    (see comment below) — `None` if we can't represent the shape.

    WHY THE SPLIT: ee-gcc 2.9 emits `.align 3` (8-byte alignment) for
    any array-shaped initializer regardless of `__attribute__((aligned(4)))`
    placement. That bumps the named section's alignment to 8, which
    breaks layout for symbols whose VMA is only 4-aligned
    (e.g. D_00631AF4: the linker pads to 8-aligned 0x631AF8, shifting
    the rest of .sdata).

    Workaround: emit each 4-byte word as its own single-int symbol in
    its own per-VMA named section. Each single-int gets `.align 2`
    (4-byte) so section alignment stays at 4 — the linker can place
    it at any 4-aligned VMA without inserting padding. The original
    symbol name (`D_<VMA>`) attaches to the FIRST word; continuation
    words use `_pad_<VMA>` names (also globals, but never referenced
    from src so they're effectively private).
    """
    if value_pair is None:
        return None
    c_type, c_init = value_pair[0], value_pair[1]
    if not c_init.startswith("{"):
        # Single-element: straightforward.
        return [
            f'__attribute__((section(".sdata.0x{vma:08X}"))) '
            f'{c_type} {sym} = {c_init};'
        ]

    # Multi-element initializer: parse out the comma-separated values
    # and emit one single-int definition per VMA.
    inner = c_init.strip().lstrip("{").rstrip("}").strip()
    elems = [e.strip() for e in inner.split(",") if e.strip()]
    out: list[str] = []
    for i, val in enumerate(elems):
        word_vma = vma + i * 4
        name = sym if i == 0 else f"_pad_{word_vma:08X}"
        out.append(
            f'__attribute__((section(".sdata.0x{word_vma:08X}"))) '
            f'unsigned int {name} = {val};'
        )
    return out


def _read_pool() -> tuple[str, set[str]]:
    if not POOL_C.exists():
        return "", set()
    text = POOL_C.read_text()
    have = set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b', text))
    return text, have


def main() -> int:
    referenced = _collect_referenced_sdata_symbols()
    migrated = _load_migrated()
    pool_text, pool_have = _read_pool()
    asm_blocks = _parse_asm_blocks()

    to_migrate = sorted(referenced - migrated - pool_have)
    if not to_migrate:
        print("migrate_sdata: nothing to migrate (all referenced sdata symbols already in pool).")
        return 0

    new_defs: list[str] = []
    new_names: list[str] = []
    skipped: list[tuple[str, str]] = []
    for sym in to_migrate:
        block = asm_blocks.get(sym)
        if block is None:
            skipped.append((sym, "not found in asm sdata"))
            continue
        vma, lines = block
        value = _parse_value_for_definition(lines)
        if value is None:
            skipped.append((sym, "unrecognized initializer shape"))
            continue
        lines_out = _emit_definition(sym, vma, value)
        if lines_out is None:
            skipped.append((sym, "emit failed"))
            continue
        new_defs.extend(lines_out)
        new_names.append(sym)

    if new_defs:
        if pool_text and not pool_text.endswith("\n"):
            pool_text += "\n"
        pool_text += "\n" + "\n".join(new_defs) + "\n"
        POOL_C.write_text(pool_text)

        with MIGRATED_LIST.open("a") as f:
            for sym in new_names:
                f.write(sym + "\n")

    print(f"migrate_sdata: migrated {len(new_names)} symbol(s).")
    for sym in new_names:
        print(f"  + {sym}")
    if skipped:
        print(f"migrate_sdata: skipped {len(skipped)} symbol(s):")
        for sym, reason in skipped[:20]:
            print(f"  - {sym}: {reason}")
        if len(skipped) > 20:
            print(f"  ... ({len(skipped) - 20} more)")
    return 0


if __name__ == "__main__":
    sys.exit(main())
