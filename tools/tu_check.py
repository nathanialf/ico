#!/usr/bin/env python3
"""tools/tu_check.py — whole-TU regression check for the matching loop.

quick_diff/match_diff verify ONE function in isolation, but the SHA-1 gate is
the whole TU/ELF, and several postprocesses mutate the entire compiled .s at
once (tools/compile_c.sh). So an edit to one function — or a TU-global
postprocess added for it — can silently break an already-matched SIBLING, and
you only find out at the final `ninja` (a ~2400-object build). This re-runs the
reloc-normalized match_diff on EVERY matched C function in a TU and reports any
that regressed, so a collision surfaces the moment it happens instead of at the
end.

    tools/tu_check.py <TU>          # check every matched func in src/<TU>.c
    tools/tu_check.py <TU> --quiet  # print only regressions
    tools/tu_check.py <TU> --json   # machine-readable

Exit status is nonzero if any matched func has real_count != 0.
"""
from __future__ import annotations
import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Mirror tools/quick_diff.sh's TU -> source resolution.
_SRC_PATTERNS = ("src/{tu}.c", "tough_nuts/{tu}/{tu}.c",
                 "sound/{tu}.c", "ios/{tu}.c", "isys/{tu}.c")

# A C definition opener: `<rettype...> func_<hex>(<args>) {`. The trailing `{`
# (not `;`) excludes prototypes/externs; INCLUDE_ASM lines have no return type.
_C_DEF_RE = re.compile(
    r"^[A-Za-z_][\w *]*\b(func_[0-9A-Fa-f]+)\s*\([^;{]*\)\s*\{", re.M)


def resolve_tu_path(tu: str) -> Path | None:
    for pat in _SRC_PATTERNS:
        p = ROOT / pat.format(tu=tu)
        if p.exists():
            return p
    return None


def matched_funcs(tu: str) -> list[str]:
    """Names of functions DEFINED in C in this TU (matched, not INCLUDE_ASM).
    Read with errors='replace' so TUs carrying EUC-JP debug strings (which
    `file` calls binary and plain grep silently skips) are scanned correctly."""
    p = resolve_tu_path(tu)
    if p is None:
        return []
    text = p.read_text(errors="replace")
    seen, out = set(), []
    for m in _C_DEF_RE.finditer(text):
        fn = m.group(1)
        if fn not in seen:
            seen.add(fn); out.append(fn)
    return out


def real_count(tu: str, func: str) -> int | None:
    r = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "match_diff.py"), "--count", tu, func],
        capture_output=True, text=True, cwd=str(ROOT))
    try:
        return int(r.stdout.strip())
    except ValueError:
        return None


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("tu")
    ap.add_argument("--quiet", action="store_true", help="print only regressions")
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args(argv[1:])

    if resolve_tu_path(args.tu) is None:
        print(f"tu_check: no source for TU {args.tu!r}", file=sys.stderr)
        return 2
    funcs = matched_funcs(args.tu)
    if not funcs:
        print(f"tu_check: no matched C functions in {args.tu}", file=sys.stderr)
        return 0

    results = {fn: real_count(args.tu, fn) for fn in funcs}
    regressions = {fn: rc for fn, rc in results.items() if rc != 0}

    if args.json:
        print(json.dumps({"tu": args.tu, "checked": len(funcs),
                          "results": results,
                          "regressions": sorted(regressions)}, indent=2))
    else:
        for fn in funcs:
            rc = results[fn]
            ok = rc == 0
            if args.quiet and ok:
                continue
            tag = "OK" if ok else ("COMPILE-FAIL" if rc is None else f"REGRESSED rc={rc}")
            print(f"  {fn:<22} {tag}")
        n = len(regressions)
        print(f"\n{args.tu}: {len(funcs)} matched func(s), "
              f"{n} regression(s)" + (" — siblings broken!" if n else " — all clean"))
    return 1 if regressions else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
