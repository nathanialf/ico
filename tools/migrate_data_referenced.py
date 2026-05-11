#!/usr/bin/env python3
"""
migrate_data_referenced.py — generalized version of
migrate_sdata_referenced.py. For every data symbol that a matched
src/cod/*.c references via `extern`, add a definition to the
corresponding pool file (using `__attribute__((section(".X.0xVMA")))`)
and append the symbol name to config/migrated_data_symbols.txt.

Handles all four migratable sections in one pass:

  * .sdata  → src/cod/sdata_pool.c
  * .lit4   → src/cod/lit4_pool.c
  * .rodata → src/cod/rodata_pool.c
  * .data   → src/cod/data_pool.c

The matched function .c files only see `extern` declarations, so
ee-gcc 2.9 keeps emitting %gp_rel for .sdata/.lit4 references and
lui+%hi/%lo for .rodata/.data references — the original codegen
shape is preserved regardless of where the symbol's bytes live.

See `tools/rewrite_data_named_sections.py` and `tools/postprocess_ld.py`
for the per-symbol-named-sections + SORT_BY_NAME plumbing that makes
this work.

Idempotent: skips any symbol already in the migrated list. Re-running
after claiming new matches picks up freshly-referenced symbols.
"""

from __future__ import annotations

import re
import sys
from pathlib import Path

REPO_ROOT = Path(__file__).resolve().parent.parent
SRC_DIR = REPO_ROOT / "src" / "cod"
MIGRATED_LIST = REPO_ROOT / "config" / "migrated_data_symbols.txt"

# (section_name, asm_file, vma_lo, vma_hi_exclusive, pool_c)
SECTIONS = [
    (".sdata",  REPO_ROOT / "asm" / "data" / "cod" / "531900.sdata.s",
     0x00631900, 0x00633BC6, REPO_ROOT / "src" / "cod" / "sdata_pool.c"),
    (".lit4",   REPO_ROOT / "asm" / "data" / "cod" / "530900.lit4.s",
     0x00630900, 0x006318D0, REPO_ROOT / "src" / "cod" / "lit4_pool.c"),
    (".rodata", REPO_ROOT / "asm" / "data" / "cod" / "453700.rodata.s",
     0x00553700, 0x006308A8, REPO_ROOT / "src" / "cod" / "rodata_pool.c"),
    (".data",   REPO_ROOT / "asm" / "data" / "cod" / "174700.data.s",
     0x00274700, 0x005536B8, REPO_ROOT / "src" / "cod" / "data_pool.c"),
]

EXTERN_RE = re.compile(
    r'\bextern\b[^;]*?\b(D_(?P<vma>[0-9A-Fa-f]{8}))\b',
)
DLABEL_RE = re.compile(
    r'^dlabel\s+D_(?P<vma>[0-9A-Fa-f]{8})\s*\n(?P<body>.*?)^enddlabel\s+D_\1\s*$',
    re.MULTILINE | re.DOTALL,
)
POOL_FILE_NAMES = {p.name for _, _, _, _, p in SECTIONS}


def _collect_referenced(vma_lo: int, vma_hi: int) -> set[str]:
    syms: set[str] = set()
    for c_path in SRC_DIR.glob("*.c"):
        if c_path.name in POOL_FILE_NAMES:
            continue
        for m in EXTERN_RE.finditer(c_path.read_text()):
            vma = int(m.group("vma"), 16)
            if vma_lo <= vma < vma_hi:
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


def _parse_asm_blocks(asm_file: Path) -> dict[str, tuple[int, list[str]]]:
    if not asm_file.exists():
        return {}
    text = asm_file.read_text()
    out: dict[str, tuple[int, list[str]]] = {}
    for m in DLABEL_RE.finditer(text):
        vma = int(m.group("vma"), 16)
        sym = f"D_{m.group('vma').upper()}"
        lines = [l for l in m.group("body").splitlines() if l.strip()]
        out[sym] = (vma, lines)
    return out


def _parse_value(lines: list[str]) -> tuple[str, str] | None:
    plain = []
    for l in lines:
        s = re.sub(r"^[ \t]*/\*[^*]*\*/\s*", "", l).strip()
        if not s or s.startswith("/*"):
            continue
        plain.append(s)
    if not plain:
        return None
    if len(plain) == 1:
        m = re.match(r"\.(?:word|long|4byte)\s+(0x[0-9A-Fa-f]+|-?\d+)$", plain[0])
        if m:
            return ("unsigned int", m.group(1))
        m = re.match(r"\.float\s+(.+?)\s*$", plain[0])
        if m:
            return ("float", m.group(1))
        m = re.match(r"\.byte\s+(0x[0-9A-Fa-f]+|-?\d+)$", plain[0])
        if m:
            return ("unsigned char", m.group(1))
        m = re.match(r"\.(?:short|hword|half|2byte)\s+(0x[0-9A-Fa-f]+|-?\d+)$", plain[0])
        if m:
            return ("unsigned short", m.group(1))
    # Multi-word literal array.
    words: list[str] = []
    is_float = False
    for line in plain:
        m = re.match(r"\.(?:word|long|4byte)\s+(.+)$", line)
        if m:
            for elt in m.group(1).split(","):
                elt = elt.strip()
                if not elt:
                    continue
                if not re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)", elt):
                    return None  # symbol reference — leave on asm side
                words.append(elt)
            continue
        m = re.match(r"\.float\s+(.+)$", line)
        if m:
            is_float = True
            for elt in m.group(1).split(","):
                elt = elt.strip()
                if elt:
                    words.append(elt)
            continue
        return None  # unsupported shape (e.g. asciz, mixed types)
    if not words:
        return None
    return ("float" if is_float else "unsigned int",
            "{ " + ", ".join(words) + " }")


def _emit(sym: str, vma: int, sect_name: str, value_pair) -> list[str]:
    """Emit one or more C definition lines for a symbol. Multi-word
    initializers are split into per-VMA single-element definitions to
    avoid ee-gcc 2.9's `.align 3` over-alignment for arrays (see
    sdata migration commit)."""
    if value_pair is None:
        return []
    c_type, c_init = value_pair
    if not c_init.startswith("{"):
        return [
            f'__attribute__((section("{sect_name}.0x{vma:08X}"))) '
            f'{c_type} {sym} = {c_init};'
        ]
    inner = c_init.strip().lstrip("{").rstrip("}").strip()
    elems = [e.strip() for e in inner.split(",") if e.strip()]
    out: list[str] = []
    elem_type = "float" if c_type == "float" else "unsigned int"
    for i, val in enumerate(elems):
        word_vma = vma + i * 4
        name = sym if i == 0 else f"_pad_{word_vma:08X}"
        out.append(
            f'__attribute__((section("{sect_name}.0x{word_vma:08X}"))) '
            f'{elem_type} {name} = {val};'
        )
    return out


def _read_pool(path: Path) -> tuple[str, set[str]]:
    if not path.exists():
        return "", set()
    text = path.read_text()
    have = set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b', text))
    return text, have


def _ensure_pool_header(text: str, sect_name: str) -> str:
    """If the pool file is empty, write a one-line `why` comment.
    Otherwise leave the existing header alone."""
    if text.strip():
        return text
    return (
        f"/* Migrated {sect_name} symbol definitions. Each global lives in a\n"
        f" * per-VMA named section so the linker can place it at its original\n"
        f" * VMA via SORT_BY_NAME (see tools/postprocess_ld.py). Matched .c\n"
        f" * function files only declare these symbols as `extern`, which\n"
        f" * keeps ee-gcc 2.9's small-data / lui+lo codegen unchanged. */\n"
    )


def main() -> int:
    migrated = _load_migrated()
    grand_total = 0
    grand_skipped = 0
    new_list_entries: list[str] = []

    for sect_name, asm_file, vma_lo, vma_hi, pool_c in SECTIONS:
        referenced = _collect_referenced(vma_lo, vma_hi)
        pool_text, pool_have = _read_pool(pool_c)
        asm_blocks = _parse_asm_blocks(asm_file)
        to_migrate = sorted(referenced - migrated - pool_have)
        if not to_migrate:
            print(f"migrate_data: {sect_name}: nothing new to migrate.")
            continue

        new_defs: list[str] = []
        new_names: list[str] = []
        skipped: list[tuple[str, str]] = []
        for sym in to_migrate:
            block = asm_blocks.get(sym)
            if block is None:
                skipped.append((sym, "not in asm"))
                continue
            vma, lines = block
            value = _parse_value(lines)
            lines_out = _emit(sym, vma, sect_name, value)
            if not lines_out:
                skipped.append((sym, "unrecognized shape"))
                continue
            new_defs.extend(lines_out)
            new_names.append(sym)

        if new_defs:
            pool_text = _ensure_pool_header(pool_text, sect_name)
            if pool_text and not pool_text.endswith("\n"):
                pool_text += "\n"
            pool_text += "\n" + "\n".join(new_defs) + "\n"
            pool_c.write_text(pool_text)
            new_list_entries.extend(new_names)

        print(f"migrate_data: {sect_name}: migrated {len(new_names)}, "
              f"skipped {len(skipped)}.")
        for sym in new_names[:5]:
            print(f"  + {sym}")
        if len(new_names) > 5:
            print(f"  ... ({len(new_names) - 5} more)")
        for sym, reason in skipped[:5]:
            print(f"  - {sym}: {reason}")
        if len(skipped) > 5:
            print(f"  ... ({len(skipped) - 5} more skipped)")

        grand_total += len(new_names)
        grand_skipped += len(skipped)

    if new_list_entries:
        with MIGRATED_LIST.open("a") as f:
            for sym in new_list_entries:
                f.write(sym + "\n")

    print(f"migrate_data: TOTAL migrated {grand_total}, skipped {grand_skipped}.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
