#!/usr/bin/env python3
"""tools/park_tu.py — park a function from a coalesced TU into tough_nuts/.

The legacy tools/park.sh handles src/cod/<file_off>.c (one function per
file, retail `main`). Coalesced TUs (many functions in one .c) need a
different flow: extract the seed without disturbing the rest of the TU.
This is the parker the aug6 prototype branch uses — its whole dev tree is
coalesced TUs (fumi/src/boyact.c, sugipon/src/pool.c, …) whose functions
carry the dev's REAL names (ACTChkAttackIgnore_BOY), not func_<hex>.

It saves the **whole TU file** as the seed under
  tough_nuts/<func>/<func>.c
permute_run.sh's strip_other_fns.py reduces it to just the target
function at run time, so the surrounding TU context (extern decls,
typedefs, matched siblings) doesn't bloat permuter's mutation surface.

By default it ALSO reverts the target function's body in the TU back to
its exact INCLUDE_ASM stub, so the working tree builds byte-identical via
the asm fallback (the build dir stays green for the commit + permuter
steps of the skill's park ritual). Pass --no-revert to leave the TU
untouched (the old manual-revert contract).

Usage:
    tools/park_tu.py <func> <TU.c> "<reason>" [--no-revert]

Examples:
    tools/park_tu.py ACTChkAttackIgnore_BOY fumi/src/boyact.c "rc3 sched tail"
    tools/park_tu.py func_0014A560 src/cod/04A560.c "12-diff beql floor"  (retail)

Effects:
    - Writes tough_nuts/<func>/<func>.c  (full TU snapshot — the seed)
    - Writes tough_nuts/<func>/notes.md  (VRAM, TU path, reason, asm)
    - Reverts the <func> body in <TU.c> to INCLUDE_ASM (unless --no-revert)
"""

import datetime as _dt
import pathlib
import re
import sys

VRAM_BASE = 0x100000
ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from ico_version import detect_version  # noqa: E402


def asm_roots(version: str) -> list[pathlib.Path]:
    """Per-version asm trees to search, nonmatchings first."""
    base = ROOT / ("asm" if version == "us" else f"asm/{version}")
    return [base / "nonmatchings", base / "matchings"]


def find_asm(func_name: str, version: str) -> tuple[str, str, str | None]:
    """Locate <func>.s. Returns (rel_path, excerpt, include_asm_dir) where
    include_asm_dir is the directory argument an INCLUDE_ASM() uses (e.g.
    'asm/aug6/nonmatchings/fumi/src/boyact'), or None if not found."""
    for base in asm_roots(version):
        if not base.exists():
            continue
        for p in base.rglob(f"{func_name}.s"):
            return (str(p.relative_to(ROOT)),
                    p.read_text(errors="replace"),
                    str(p.parent.relative_to(ROOT)))
    # Retail fallback: scan asm/cod/*.s for glabel func_X … endlabel func_X.
    asm_cod = ROOT / "asm" / "cod"
    if asm_cod.exists():
        glabel = re.compile(rf"^glabel\s+{re.escape(func_name)}\b")
        endlabel = re.compile(rf"^endlabel\s+{re.escape(func_name)}\b")
        for p in asm_cod.glob("*.s"):
            lines = p.read_text(errors="replace").splitlines()
            in_fn, buf = False, []
            for ln in lines:
                if glabel.match(ln):
                    in_fn = True
                if in_fn:
                    buf.append(ln)
                if endlabel.match(ln):
                    return (str(p.relative_to(ROOT)), "\n".join(buf), None)
    return ("(asm not found)", "", None)


def lookup_vram(func_name: str, version: str) -> int | None:
    """VRAM of a function. func_<hex> encodes it directly; otherwise read it
    from config/symbol_addrs.<version>.txt (`<func> = 0x...;`)."""
    m = re.match(r"^func_([0-9A-Fa-f]{8})$", func_name)
    if m:
        return int(m.group(1), 16)
    sa = ROOT / "config" / f"symbol_addrs.{version}.txt"
    if sa.exists():
        rx = re.compile(rf"^\s*{re.escape(func_name)}\s*=\s*0x([0-9A-Fa-f]+)")
        for line in sa.read_text(errors="replace").splitlines():
            mm = rx.match(line)
            if mm:
                return int(mm.group(1), 16)
    return None


def func_def_span(src: str, func: str) -> tuple[int, int] | None:
    """Brace-matched span [start, end) of `func`'s C definition (not its
    INCLUDE_ASM stub), or None if it's only a stub / not defined. Mirrors
    tools/match_loop.py:func_body so park and the loop agree on extent."""
    start = -1
    for m in re.finditer(r'\b' + re.escape(func) + r'\s*\(', src):
        p = m.start()
        anchor = max(src.rfind(';', 0, p), src.rfind('}', 0, p)) + 1
        if 'INCLUDE_ASM' in src[anchor:p]:
            continue
        start = anchor
    if start < 0:
        return None
    # Skip leading whitespace so the replacement stub sits at column 0.
    while start < len(src) and src[start] in " \t\n":
        start += 1
    b = src.find('{', start)
    if b < 0:
        return None
    depth = 0
    for i in range(b, len(src)):
        if src[i] == '{':
            depth += 1
        elif src[i] == '}':
            depth -= 1
            if depth == 0:
                return (start, i + 1)
    return None


def main() -> int:
    argv = [a for a in sys.argv[1:] if a != "--no-revert"]
    do_revert = "--no-revert" not in sys.argv[1:]
    if len(argv) < 3:
        print(__doc__, file=sys.stderr)
        return 2
    func_name, tu_arg, reason = argv[0], argv[1], " ".join(argv[2:])

    if not re.match(r"^[A-Za-z_][A-Za-z0-9_]*$", func_name):
        print(f"park_tu: bad function name {func_name!r}", file=sys.stderr)
        return 2

    tu_path = pathlib.Path(tu_arg)
    if not tu_path.is_absolute():
        tu_path = ROOT / tu_path
    if not tu_path.is_file():
        print(f"park_tu: TU file not found: {tu_path}", file=sys.stderr)
        return 2

    version = detect_version(ROOT)
    tu_text = tu_path.read_text()
    if func_name not in tu_text:
        print(f"park_tu: {tu_path.relative_to(ROOT)} contains no reference "
              f"to {func_name}", file=sys.stderr)
        return 3

    vram = lookup_vram(func_name, version)
    vram_str = f"0x{vram:08X}" if vram is not None else "(unknown)"
    off_str = f"0x{vram - VRAM_BASE:06X}" if vram is not None else "(unknown)"

    nuts_dir = ROOT / "tough_nuts" / func_name
    nuts_dir.mkdir(parents=True, exist_ok=True)

    # Save the seed (the TU snapshot WITH the attempted C body), before revert.
    seed_path = nuts_dir / f"{func_name}.c"
    if seed_path.exists():
        n = 1
        while (nuts_dir / f"{func_name}.{n}.c").exists():
            n += 1
        seed_path = nuts_dir / f"{func_name}.{n}.c"
    seed_path.write_text(tu_text)

    asm_rel, asm_text, include_dir = find_asm(func_name, version)
    # Fallback include dir from the TU path (subseg name == repo-rel TU stem).
    if include_dir is None:
        base = "asm" if version == "us" else f"asm/{version}"
        stem = tu_path.relative_to(ROOT).with_suffix("").as_posix()
        include_dir = f"{base}/nonmatchings/{stem}"

    notes_path = nuts_dir / "notes.md"
    header_existed = notes_path.exists()
    with notes_path.open("a") as f:
        if not header_existed:
            f.write(f"# {func_name} — parked\n\n")
            f.write(f"VRAM: {vram_str} (file_off {off_str})\n")
            f.write(f"Asm source: {asm_rel}\n\n")
        else:
            f.write("\n---\n\n")
        f.write(f"## Attempt at {_dt.date.today().isoformat()}\n\n")
        f.write(f"**Reason parked:** {reason}\n\n")
        f.write(f"**TU:** `{tu_path.relative_to(ROOT)}`\n\n")
        f.write(f"**Seed:** `{seed_path.relative_to(ROOT)}`\n\n")
        if asm_text:
            f.write("Disassembly:\n\n```\n")
            f.write(asm_text.rstrip())
            f.write("\n```\n")

    print(f"park_tu: seed  -> {seed_path.relative_to(ROOT)}")
    print(f"park_tu: notes -> {notes_path.relative_to(ROOT)}")

    reverted = False
    if do_revert:
        span = func_def_span(tu_text, func_name)
        if span is None:
            print(f"park_tu: {func_name} is already an INCLUDE_ASM stub in "
                  f"{tu_path.relative_to(ROOT)} (nothing to revert).")
        else:
            stub = f'INCLUDE_ASM("{include_dir}", {func_name});'
            new_text = tu_text[:span[0]] + stub + tu_text[span[1]:]
            tu_path.write_text(new_text)
            reverted = True
            print(f"park_tu: reverted {func_name} body -> {stub}")

    print()
    print("park_tu: NEXT STEPS")
    if not reverted and do_revert is False:
        print(f"  0. Manually replace the {func_name} body in "
              f"{tu_path.relative_to(ROOT)} with")
        print(f'     INCLUDE_ASM("{include_dir}", {func_name});')
    print("  1. ninja  # confirm SHA-1 round-trip with the asm fallback")
    print(f"  2. git add tough_nuts/{func_name}/ {tu_path.relative_to(ROOT)}")
    print(f"     git commit -m 'Park {func_name} ({reason})'")
    print()
    print("  Permuter (tools/auto_permute.sh / the Step-4 backgrounded shot)")
    print("  picks up the seed; score-0 hits land in")
    print(f"  lib/decomp-permuter/runs/{func_name}/output-0-*/source.c.")
    return 0


if __name__ == "__main__":
    sys.exit(main())
