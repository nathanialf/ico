#!/usr/bin/env python3
"""tools/lever.py — deterministic, quick_diff-scored SOURCE transforms.

The matching PLAYBOOK names several MECHANICAL levers — reorder a run of init
stores; pin a value to a specific register. Applying them by hand is slow, and
the store-order brute force (feedback_brute_force_store_order_plus_anchor) was
literally done by hand across N! orderings. quick_diff is ~100 ms, so this is
automatable AND far more targeted than the random permuter: every variant is
the developer's own C with ONE source-level change, scored by the same
reloc-normalized real_count (tools/match_diff.py) the loop already trusts.

Modes
  reorder <TU> <func> --lines A:B   Permute lines A..B (1-based, inclusive),
                                    treating each as an atomic statement, and
                                    rank by real_count. Use on a contiguous run
                                    of independent field stores / inits (the
                                    classic "init-store order" wall).
  pin     <TU> <func> --line N      Sweep a REG("$rN") pin on the decl at line
                                    N across candidate registers (default
                                    $2..$8) plus the un-pinned baseline.

Both modes RESTORE the file when done; pass --apply to leave the
lowest-scoring variant in place (ties keep the earliest / un-pinned form).
The func arg is the func_XXX name; the TU is the quick_diff <NAME> (e.g.
`gobj`, `Light`). Always confirm the winner with `ninja` before committing.
"""
from __future__ import annotations
import argparse
import itertools
import math
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

# Mirror tools/quick_diff.sh's TU -> source resolution.
_SRC_PATTERNS = ("src/{tu}.c", "tough_nuts/{tu}/{tu}.c",
                 "sound/{tu}.c", "ios/{tu}.c", "isys/{tu}.c")
DEFAULT_REGS = ["$2", "$3", "$4", "$5", "$6", "$7", "$8"]
FAIL = 10 ** 9   # sort key for compile-fail / error variants


def resolve_tu_path(tu: str) -> Path | None:
    for pat in _SRC_PATTERNS:
        p = ROOT / pat.format(tu=tu)
        if p.exists():
            return p
    return None


def score(tu: str, func: str) -> int | None:
    """real_count for the current on-disk source, or None on compile-fail."""
    r = subprocess.run(
        [sys.executable, str(ROOT / "tools" / "match_diff.py"), "--count", tu, func],
        capture_output=True, text=True, cwd=str(ROOT),
    )
    try:
        v = int(r.stdout.strip())
    except ValueError:
        return None
    return None if v < 0 else v


def _evaluate(path: Path, tu: str, func: str, variants, label_of):
    """Write each variant's lines, score it, restore the original. Returns a
    list of (score, label, lines) sorted best-first; prints progress to stderr."""
    original = path.read_text()
    results = []
    try:
        for i, lines in enumerate(variants):
            path.write_text("\n".join(lines))
            s = score(tu, func)
            label = label_of(i, lines)
            results.append((FAIL if s is None else s, label, lines))
            shown = "compile-fail" if s is None else f"real_count={s}"
            print(f"  [{i+1}] {label}: {shown}", file=sys.stderr)
    finally:
        path.write_text(original)
    results.sort(key=lambda t: t[0])
    return results


def _report_and_maybe_apply(path: Path, results, apply: bool, baseline: int | None):
    best_score, best_label, best_lines = results[0]
    print("\n=== ranked (best first) ===")
    for s, label, _ in results:
        tag = "compile-fail" if s >= FAIL else f"real_count={s}"
        print(f"  {tag:<22} {label}")
    if baseline is not None:
        print(f"\nbaseline (original): real_count={baseline}")
    if apply:
        if best_score >= FAIL:
            print("\nNOT applying: best variant does not compile.", file=sys.stderr)
            return 2
        path.write_text("\n".join(best_lines))
        print(f"\nAPPLIED winner ({best_label}, real_count={best_score}) to {path.relative_to(ROOT)}")
        print("Confirm with `ninja` before committing.")
    else:
        print(f"\nWinner: {best_label} (real_count={best_score}). "
              f"Re-run with --apply to write it.")
    return 0


def cmd_reorder(args) -> int:
    path = resolve_tu_path(args.tu)
    if path is None:
        print(f"cannot resolve TU source for {args.tu!r}", file=sys.stderr); return 2
    lines = path.read_text().split("\n")
    a, b = (int(x) for x in args.lines.split(":"))
    if not (1 <= a <= b <= len(lines)):
        print(f"--lines {a}:{b} out of range (file has {len(lines)} lines)",
              file=sys.stderr); return 2
    block = lines[a - 1:b]
    k = len(block)
    nperm = math.factorial(k)
    if nperm > args.max:
        print(f"{k} lines = {nperm} permutations > --max {args.max}. Narrow the "
              f"range or raise --max (each variant is one ~100ms quick_diff).",
              file=sys.stderr)
        return 2
    print(f"reorder: {k} lines ({nperm} permutations) at {path.relative_to(ROOT)}:{a}-{b}",
          file=sys.stderr)
    for ln in block:
        print(f"    | {ln.strip()}", file=sys.stderr)

    perms = list(itertools.permutations(range(k)))

    def make(order):
        out = lines[:]
        out[a - 1:b] = [block[i] for i in order]
        return out

    def label_of(i, _lines):
        order = perms[i]
        return "original" if order == tuple(range(k)) else "order=" + ",".join(str(o + 1) for o in order)

    variants = [make(o) for o in perms]
    results = _evaluate(path, args.tu, args.func, variants, label_of)
    baseline = next((s for s, l, _ in results if l == "original"), None)
    baseline = None if baseline is not None and baseline >= FAIL else baseline
    return _report_and_maybe_apply(path, results, args.apply, baseline)


_DECL_RE = re.compile(r"^(\s*)(.*?)\s*=\s*(.*;)\s*$")
_REG_RE = re.compile(r'REG\("\$\w+"\)')


def _pin_line(src: str, reg: str | None) -> str | None:
    """Rewrite a `<type> <name> = <rhs>;` decl to pin <name> to `reg`
    (or strip the pin if reg is None). Returns None if the line isn't a
    simple decl-with-initializer."""
    if _REG_RE.search(src):
        if reg is None:
            # strip "register " + REG(...) back to a plain decl
            s = _REG_RE.sub("", src)
            s = re.sub(r"\bregister\s+", "", s, count=1)
            return re.sub(r"\s{2,}", " ", s)
        return _REG_RE.sub(f'REG("{reg}")', src)
    m = _DECL_RE.match(src)
    if not m:
        return None
    indent, lhs, rhs = m.groups()
    lhs = re.sub(r"\bregister\s+", "", lhs).strip()
    if reg is None:
        return f"{indent}{lhs} = {rhs}"
    return f'{indent}register {lhs} REG("{reg}") = {rhs}'


def cmd_pin(args) -> int:
    path = resolve_tu_path(args.tu)
    if path is None:
        print(f"cannot resolve TU source for {args.tu!r}", file=sys.stderr); return 2
    lines = path.read_text().split("\n")
    n = args.line
    if not (1 <= n <= len(lines)):
        print(f"--line {n} out of range (file has {len(lines)} lines)",
              file=sys.stderr); return 2
    target = lines[n - 1]
    regs = args.regs.split(",") if args.regs else DEFAULT_REGS
    # baseline (un-pinned) first, then each candidate register.
    candidates: list[str | None] = [None] + regs
    print(f"pin-sweep at {path.relative_to(ROOT)}:{n}", file=sys.stderr)
    print(f"    | {target.strip()}", file=sys.stderr)

    rewrites = []
    for reg in candidates:
        rw = _pin_line(target, reg)
        if rw is None:
            print(f"line {n} is not a simple `<decl> = <init>;` — cannot pin",
                  file=sys.stderr)
            return 2
        rewrites.append((reg, rw))

    def make(i):
        out = lines[:]
        out[n - 1] = rewrites[i][1]
        return out

    def label_of(i, _lines):
        reg = rewrites[i][0]
        return "unpinned" if reg is None else f'REG("{reg}")'

    variants = [make(i) for i in range(len(rewrites))]
    results = _evaluate(path, args.tu, args.func, variants, label_of)
    baseline = next((s for s, l, _ in results if l == "unpinned"), None)
    baseline = None if baseline is not None and baseline >= FAIL else baseline
    return _report_and_maybe_apply(path, results, args.apply, baseline)


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="mode", required=True)

    r = sub.add_parser("reorder", help="permute a contiguous run of statement lines")
    r.add_argument("tu"); r.add_argument("func")
    r.add_argument("--lines", required=True, help="A:B (1-based, inclusive)")
    r.add_argument("--max", type=int, default=720, help="max permutations (default 720 = 6!)")
    r.add_argument("--apply", action="store_true")
    r.set_defaults(fn=cmd_reorder)

    p = sub.add_parser("pin", help="sweep a REG() pin on a decl across registers")
    p.add_argument("tu"); p.add_argument("func")
    p.add_argument("--line", type=int, required=True, help="1-based line of the decl")
    p.add_argument("--regs", default="", help="comma list, e.g. $2,$3,$5 (default $2..$8)")
    p.add_argument("--apply", action="store_true")
    p.set_defaults(fn=cmd_pin)

    args = ap.parse_args(argv[1:])
    return args.fn(args)


if __name__ == "__main__":
    sys.exit(main(sys.argv))
