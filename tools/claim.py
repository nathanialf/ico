#!/usr/bin/env python3
"""
claim.py — claim one or more PS2 ICO functions into the matching loop.

Replaces the throwaway /tmp/claim_*.py scripts. For each claim it:
  1. Writes the C body to src/cod/<file_off>.c (file_off = vram - 0x100000).
  2. Updates config/ico.us.yaml: flips the matching `asm` entry to `c`,
     inserting an `asm` filler at file_off+size if none exists there.
  3. Skips entries already typed `c` (prints `# SKIP <off>`).

Usage:
  # single claim (C body on stdin)
  tools/claim.py single --vram 0x118460 --size 0x10 \
      --comment '16-byte lq/sq copy' < src.c

  # batch from a TOML manifest
  tools/claim.py batch --manifest claims.toml

The TOML manifest is an array of [[claim]] tables, each with keys:
  vram     (int, required)            e.g. 0x118460
  size     (int, required)            e.g. 0x10
  comment  (str, required)            e.g. "16-byte lq/sq copy"
  body     (multiline str, required)  literal C source

After running, kick off `make setup && make` to build & verify.
"""
from __future__ import annotations

import argparse
import re
import sys
import tomllib
from pathlib import Path
from typing import Optional

REPO = Path(__file__).resolve().parent.parent
SRC_DIR = REPO / "src" / "cod"
YAML_PATH = REPO / "config" / "ico.us.yaml"
SEG_START_MARKER = "    subsegments:\n"
SEG_END_MARKER = "  - [0x533BC6]"
VRAM_BASE = 0x100000

# Matches indented yaml subseg lines like:
#   - [0x018460, c,   cod/018460]            # comment
SUB_RE = re.compile(r"\s*- \[0x([0-9A-Fa-f]+),\s*(\w+)")


class Claim:
    __slots__ = ("vram", "size", "comment", "body")

    def __init__(self, vram: int, size: int, comment: str, body: str):
        self.vram = vram
        self.size = size
        self.comment = comment
        self.body = body

    @property
    def file_off(self) -> int:
        return self.vram - VRAM_BASE


def parse_int(s) -> int:
    if isinstance(s, int):
        return s
    s = str(s).strip()
    return int(s, 16) if s.lower().startswith("0x") else int(s, 0)


def read_yaml_block() -> tuple[str, list[tuple[Optional[int], str, Optional[str]]], str]:
    """Return (prefix, entries, suffix). entries is list of (offset, line, type)."""
    text = YAML_PATH.read_text()
    seg_start = text.index(SEG_START_MARKER) + len(SEG_START_MARKER)
    seg_end = text.index(SEG_END_MARKER)
    prefix = text[:seg_start]
    block = text[seg_start:seg_end]
    suffix = text[seg_end:]

    entries: list[tuple[Optional[int], str, Optional[str]]] = []
    # Preserve trailing newline structure: split keeps every line.
    # Drop the very last empty token if block ends with \n so we don't
    # produce a phantom blank entry; we'll re-add a single trailing \n.
    raw_lines = block.split("\n")
    if raw_lines and raw_lines[-1] == "":
        raw_lines.pop()
    for line in raw_lines:
        if not line.strip():
            entries.append((None, line, None))
            continue
        m = SUB_RE.match(line)
        if m:
            entries.append((int(m.group(1), 16), line, m.group(2)))
        else:
            entries.append((None, line, None))
    return prefix, entries, suffix


def write_yaml_block(prefix: str, entries: list, suffix: str) -> None:
    out = "\n".join(line for _, line, _ in entries) + "\n"
    YAML_PATH.write_text(prefix + out + suffix)


def fmt_c_line(file_off: int, vram: int, comment: str) -> str:
    return (
        f"      - [0x{file_off:06X}, c,   cod/{file_off:06X}]"
        f"            # func_{vram:08X}: {comment}"
    )


def fmt_asm_line(file_off: int) -> str:
    return f"      - [0x{file_off:06X}, asm, cod/{file_off:06X}]"


def apply_claim(
    claim: Claim,
    entries: list,
    offsets: set,
) -> str:
    """Mutate entries in place. Return a status string for logging."""
    file_off = claim.file_off
    vram = claim.vram

    # Find existing entry at this offset.
    found_idx: Optional[int] = None
    found_type: Optional[str] = None
    for i, (off, _, t) in enumerate(entries):
        if off == file_off:
            found_idx = i
            found_type = t
            break

    if found_type == "c":
        return f"# SKIP 0x{file_off:06X} (already c)"

    new_line = fmt_c_line(file_off, vram, claim.comment)
    fill_off = file_off + claim.size
    fill_line = fmt_asm_line(fill_off)

    if found_type is not None and found_type != "c":
        # flip in place (typically 'asm' -> 'c')
        entries[found_idx] = (file_off, new_line, "c")
        if fill_off not in offsets:
            entries.insert(
                found_idx + 1, (fill_off, fill_line, "asm")
            )
            offsets.add(fill_off)
        return f"# FLIP 0x{file_off:06X} ({found_type}->c)"

    # No entry at this offset — sorted insert.
    insert_idx = len(entries)
    for i, (eoff, _, _) in enumerate(entries):
        if eoff is not None and eoff > file_off:
            insert_idx = i
            break
    new_lines = [(file_off, new_line, "c")]
    if fill_off not in offsets:
        new_lines.append((fill_off, fill_line, "asm"))
    for o, _, _ in new_lines:
        offsets.add(o)
    entries[insert_idx:insert_idx] = new_lines
    return f"# INSERT 0x{file_off:06X}"


def write_c_file(claim: Claim) -> str:
    SRC_DIR.mkdir(parents=True, exist_ok=True)
    path = SRC_DIR / f"{claim.file_off:06X}.c"
    body = claim.body
    if not body.endswith("\n"):
        body += "\n"
    path.write_text(body)
    return f"# WROTE {path.relative_to(REPO)}"


def yaml_has_c_at(entries: list, file_off: int) -> bool:
    for off, _, t in entries:
        if off == file_off and t == "c":
            return True
    return False


def run_claims(claims: list[Claim]) -> int:
    if not claims:
        print("no claims provided", file=sys.stderr)
        return 1

    prefix, entries, suffix = read_yaml_block()
    offsets = {o for o, _, _ in entries if o is not None}

    n_done = 0
    for c in claims:
        # Avoid clobbering a .c that already corresponds to a c-typed entry.
        if yaml_has_c_at(entries, c.file_off):
            print(f"# SKIP 0x{c.file_off:06X} (already c, .c untouched)")
            continue
        print(write_c_file(c))
        print(apply_claim(c, entries, offsets))
        n_done += 1

    write_yaml_block(prefix, entries, suffix)
    print(f"# DONE {n_done}/{len(claims)} claim(s) applied")
    print("# next: make setup && make")
    return 0


def load_batch(manifest: Path) -> list[Claim]:
    data = tomllib.loads(manifest.read_text())
    claims: list[Claim] = []
    for raw in data.get("claim", []):
        claims.append(
            Claim(
                vram=parse_int(raw["vram"]),
                size=parse_int(raw["size"]),
                comment=str(raw["comment"]),
                body=str(raw["body"]),
            )
        )
    return claims


def main() -> int:
    ap = argparse.ArgumentParser(
        prog="claim.py",
        description="Claim PS2 ICO functions into the matching loop.",
    )
    sub = ap.add_subparsers(dest="cmd", required=True)

    sp_single = sub.add_parser("single", help="claim one function (C body on stdin)")
    sp_single.add_argument("--vram", required=True, help="VRAM address, e.g. 0x118460")
    sp_single.add_argument("--size", required=True, help="function size in bytes, e.g. 0x10")
    sp_single.add_argument("--comment", required=True, help="short yaml comment")
    sp_single.add_argument(
        "--body-file",
        help="read C body from this file instead of stdin",
    )

    sp_batch = sub.add_parser("batch", help="claim many from a TOML manifest")
    sp_batch.add_argument("--manifest", required=True, help="path to claims.toml")

    args = ap.parse_args()

    if args.cmd == "single":
        if args.body_file:
            body = Path(args.body_file).read_text()
        else:
            body = sys.stdin.read()
        if not body.strip():
            print("empty C body (stdin / --body-file)", file=sys.stderr)
            return 2
        claim = Claim(
            vram=parse_int(args.vram),
            size=parse_int(args.size),
            comment=args.comment,
            body=body,
        )
        return run_claims([claim])

    if args.cmd == "batch":
        claims = load_batch(Path(args.manifest))
        return run_claims(claims)

    return 2


if __name__ == "__main__":
    sys.exit(main())
