#!/usr/bin/env python3
"""tools/park_tu.py — park a function from a coalesced TU into tough_nuts/.

The legacy tools/park.sh handles src/cod/<file_off>.c (one function per
file). Coalesced TUs (src/<TU>.c with many functions in one file) need a
different flow: extract the seed without disturbing the rest of the TU.

This script saves the **whole TU file** as the seed under
  tough_nuts/<func>/<func>.c
permute_run.sh's strip_other_fns.py reduces it to just the target
function at run time, so the surrounding TU context (extern decls,
typedefs, matched siblings) doesn't bloat permuter's mutation surface.

Usage:
    tools/park_tu.py <func_X> <src/TU.c> "<reason>"

Effects:
    - Writes tough_nuts/<func_X>/<func_X>.c  (full TU snapshot)
    - Writes tough_nuts/<func_X>/notes.md    (VRAM, TU path, reason, asm)
    - Does NOT modify <TU.c>. Caller must manually revert the function
      body to INCLUDE_ASM and run ninja before committing.
"""

import datetime as _dt
import pathlib
import re
import sys


VRAM_BASE = 0x100000
ROOT = pathlib.Path(__file__).resolve().parent.parent


def find_asm_excerpt(func_name: str) -> tuple[str, str]:
    """Return (path, excerpt) for the .s file containing this function."""
    candidates = []
    for ext in ("nonmatchings", "matchings"):
        base = ROOT / "asm" / ext
        if not base.exists():
            continue
        for p in base.rglob(f"{func_name}.s"):
            candidates.append(p)
    if candidates:
        path = candidates[0]
        return (
            str(path.relative_to(ROOT)),
            path.read_text(errors="replace"),
        )
    # Fall back: scan asm/cod/*.s for glabel func_X
    asm_cod = ROOT / "asm" / "cod"
    if asm_cod.exists():
        glabel = re.compile(rf"^glabel\s+{re.escape(func_name)}\b")
        endlabel = re.compile(rf"^endlabel\s+{re.escape(func_name)}\b")
        for p in asm_cod.glob("*.s"):
            lines = p.read_text(errors="replace").splitlines()
            in_fn = False
            buf = []
            for ln in lines:
                if glabel.match(ln):
                    in_fn = True
                if in_fn:
                    buf.append(ln)
                if endlabel.match(ln):
                    return (str(p.relative_to(ROOT)), "\n".join(buf))
    return ("(asm not found)", "")


def main() -> int:
    if len(sys.argv) < 4:
        print(__doc__, file=sys.stderr)
        return 2
    func_name = sys.argv[1]
    tu_arg = sys.argv[2]
    reason = " ".join(sys.argv[3:])

    if not re.match(r"^func_[0-9A-Fa-f]{8}$", func_name):
        print(f"park_tu: bad function name {func_name!r}", file=sys.stderr)
        return 2

    tu_path = pathlib.Path(tu_arg)
    if not tu_path.is_absolute():
        tu_path = ROOT / tu_path
    if not tu_path.is_file():
        print(f"park_tu: TU file not found: {tu_path}", file=sys.stderr)
        return 2

    tu_text = tu_path.read_text()
    # Sanity check: TU must reference the function. Either as a definition
    # (`func_X(` somewhere on a line that isn't an INCLUDE_ASM) or it was
    # in the file via INCLUDE_ASM(...) at minimum (still useful as a seed
    # snapshot showing the TU context for later attempts).
    if func_name not in tu_text:
        print(
            f"park_tu: {tu_path.relative_to(ROOT)} contains no reference "
            f"to {func_name}",
            file=sys.stderr,
        )
        return 3

    vram_hex = func_name.removeprefix("func_").upper()
    vram_dec = int(vram_hex, 16)
    file_off = vram_dec - VRAM_BASE

    nuts_dir = ROOT / "tough_nuts" / func_name
    nuts_dir.mkdir(parents=True, exist_ok=True)

    seed_path = nuts_dir / f"{func_name}.c"
    if seed_path.exists():
        # Don't clobber — bump suffix so successive parks accumulate.
        n = 1
        while (nuts_dir / f"{func_name}.{n}.c").exists():
            n += 1
        seed_path = nuts_dir / f"{func_name}.{n}.c"
    seed_path.write_text(tu_text)

    asm_rel, asm_text = find_asm_excerpt(func_name)
    notes_path = nuts_dir / "notes.md"
    header_existed = notes_path.exists()
    today = _dt.date.today().isoformat()
    with notes_path.open("a") as f:
        if not header_existed:
            f.write(f"# {func_name} — parked\n\n")
            f.write(f"VRAM: 0x{vram_hex} (file_off 0x{file_off:06X})\n")
            f.write(f"Asm source: {asm_rel}\n\n")
        else:
            f.write("\n---\n\n")
        f.write(f"## Attempt at {today}\n\n")
        f.write(f"**Reason parked:** {reason}\n\n")
        f.write(f"**TU:** `{tu_path.relative_to(ROOT)}`\n\n")
        f.write(f"**Seed:** `{seed_path.relative_to(ROOT)}`\n\n")
        if asm_text:
            f.write("Disassembly:\n\n```\n")
            f.write(asm_text.rstrip())
            f.write("\n```\n")

    print(f"park_tu: seed -> {seed_path.relative_to(ROOT)}")
    print(f"park_tu: notes -> {notes_path.relative_to(ROOT)}")
    print()
    print(f"park_tu: NEXT STEPS")
    print(f"  1. Replace the {func_name} body in {tu_path.relative_to(ROOT)}")
    print(f"     with INCLUDE_ASM(\"asm/nonmatchings/...\", {func_name});")
    print(f"  2. ninja  # confirm SHA-1 round-trip with asm fallback")
    print(f"  3. git add tough_nuts/{func_name}/ {tu_path.relative_to(ROOT)}")
    print(f"     git commit -m 'Park {func_name} ({reason})'")
    print()
    print(f"  Permuter (tools/auto_permute.sh) will pick up the seed on its")
    print(f"  next pass and chew on it. Score-0 hits land in")
    print(f"  lib/decomp-permuter/runs/{func_name}/output-0-*/source.c.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
