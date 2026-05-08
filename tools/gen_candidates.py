#!/usr/bin/env python3
"""Generate `docs/candidates.md` — auto-curated unmatched-function list.

Browseable, regenerated on every `make setup`. Replaces ad-hoc
`tools/find_leaves.py` invocations during the matching loop.

Reads the same parsed-function cache as `find_leaves.py` (so the second
run after a splat is sub-second), bins functions into shape categories
that have proven productive in practice, ranks them by a "promise"
heuristic, and writes the top N per category as Markdown tables.

Usage:
    tools/gen_candidates.py            # writes docs/candidates.md
    tools/gen_candidates.py --out -    # write to stdout
    tools/gen_candidates.py --top 100  # change per-category cutoff

The script is intentionally cheap and idempotent. If anything goes
wrong it prints a single warning and exits 0 — `make setup` must not
fail because the candidates report could not be regenerated.
"""
from __future__ import annotations

import argparse
import datetime as _dt
import glob
import os
import re
import sys
import time
from pathlib import Path

# Reuse find_leaves' parser + cache. Same directory; absolute import via
# sys.path so this works whether invoked from the repo root or elsewhere.
_HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(_HERE))
from find_leaves import Func, load_funcs  # noqa: E402

REPO = _HERE.parent
DEFAULT_GLOB = "asm/cod/*.s"
DEFAULT_OUT = REPO / "docs" / "candidates.md"
TOUGH_NUTS_DIR = REPO / "tough_nuts"

# ---------------------------------------------------------------------------
# Categories
#
# Each entry is (slug, title, predicate). Predicate is a callable taking a
# Func and returning True if the function belongs in this bucket. The order
# below is the order they appear in the report. Buckets are mutually
# exclusive — a function is placed in the FIRST bucket whose predicate
# matches.
# ---------------------------------------------------------------------------

def _no_vu(fn: Func) -> bool:
    return not fn.has_vu()


def _has_vu(fn: Func) -> bool:
    return fn.has_vu()


def _has_spill_reload(fn: Func) -> bool:
    """Detects sw $a0,0($sp) immediately followed by lw $a0,0($sp) — the
    arg-spill+reload pattern that matches with `volatile unsigned int a0`."""
    for i in range(len(fn.insns) - 1):
        a = fn.insns[i]
        b = fn.insns[i + 1]
        if a.startswith("sw") and "0($sp)" in a and "$a0" in a \
           and b.startswith("lw") and "0($sp)" in b and "$a0" in b:
            return True
    return False


def _has_gp_rel(fn: Func) -> bool:
    return any("%gp_rel(" in ins for ins in fn.insns)


def _has_lui_lo(fn: Func) -> bool:
    return any("%hi(" in ins for ins in fn.insns)


def _has_branch(fn: Func) -> bool:
    return any(re.match(r"^(beq|bne|beqz|bnez|bgez|bltz|bgtz|blez)", ins)
               for ins in fn.insns)


CATEGORIES: list[tuple[str, str, callable]] = [
    # Tiny scalar leaves — bulk getter/setter / passthrough material.
    ("leaf-4-0x10",
     "4-insn / 0x10 leaf, no jal, no VU (bulk getter/setter)",
     lambda fn: fn.size == 0x10 and len(fn.insns) == 4 and fn.jal_count() == 0 and _no_vu(fn)),
    ("leaf-5-0x14",
     "5-insn / 0x14 leaf, no jal, no VU (store-and-forward)",
     lambda fn: fn.size == 0x14 and len(fn.insns) == 5 and fn.jal_count() == 0 and _no_vu(fn)),
    ("leaf-6-0x18",
     "6-insn / 0x18 leaf, no jal, no VU (sub-deref + store)",
     lambda fn: fn.size == 0x18 and len(fn.insns) == 6 and fn.jal_count() == 0 and _no_vu(fn)),
    ("leaf-7-0x1C",
     "7-insn / 0x1C leaf, no jal, no VU (accessor + multiplier/branch)",
     lambda fn: fn.size == 0x1C and len(fn.insns) == 7 and fn.jal_count() == 0 and _no_vu(fn)),
    # 1-jal wrappers.
    ("wrap-8-0x20",
     "8-insn / 0x20, exactly 1 jal, no VU (passthrough call)",
     lambda fn: fn.size == 0x20 and len(fn.insns) == 8 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-9-0x24",
     "9-insn / 0x24, exactly 1 jal, no VU (wrapper + arg setup)",
     lambda fn: fn.size == 0x24 and len(fn.insns) == 9 and fn.jal_count() == 1 and _no_vu(fn)),
    # Larger wrappers — 1-jal in 0x28..0x40 range. Frequently match by
    # restructuring args, using volatile-param spill/reload pattern, etc.
    ("wrap-1jal-0x28-0x30",
     "0x28-0x30, exactly 1 jal, no VU (wrapper w/ buffer or extra spill)",
     lambda fn: 0x28 <= fn.size <= 0x30 and fn.jal_count() == 1 and _no_vu(fn)),
    ("wrap-1jal-0x34-0x40",
     "0x34-0x40, exactly 1 jal, no VU (wrapper w/ stack buffer / arg pack)",
     lambda fn: 0x34 <= fn.size <= 0x40 and fn.jal_count() == 1 and _no_vu(fn)),
    # Spill+reload wrappers — strong signal for the volatile-param pattern.
    ("wrap-spill-reload",
     "Any size, has sw $a0,0($sp); lw $a0,0($sp), no VU "
     "(volatile unsigned int a0 + volatile int local)",
     lambda fn: _has_spill_reload(fn) and _no_vu(fn) and fn.jal_count() >= 1),
    # 2-jal small wrappers — typical func1(...) + func2(...) bodies, often
    # with the second call tail-called (`j` in original codegen).
    ("wrap-2jal-0x18-0x24",
     "0x18-0x24, exactly 2 jal, no VU (compact 2-call wrapper)",
     lambda fn: 0x18 <= fn.size <= 0x24 and fn.jal_count() == 2 and _no_vu(fn)),
    ("wrap-2jal-0x28-0x40",
     "0x28-0x40, exactly 2 jal, no VU (2-call wrapper, mid-size)",
     lambda fn: 0x28 <= fn.size <= 0x40 and fn.jal_count() == 2 and _no_vu(fn)),
    # 3-jal wrappers — including tail-call patterns (j on third call).
    ("wrap-3jal-mid",
     "0x28-0x40, exactly 3 jal, no VU (3-call wrapper, often w/ tail call)",
     lambda fn: 0x28 <= fn.size <= 0x40 and fn.jal_count() == 3 and _no_vu(fn)),
    # gp_rel D + 1-jal — common passthrough family (D[0] + a0 → call).
    ("wrap-gp-1jal",
     "1 jal + gp_rel %gp_rel(D), no VU (D[0] + arg passthrough)",
     lambda fn: fn.jal_count() == 1 and _has_gp_rel(fn) and _no_vu(fn)),
    # Cond-deref returners: leaf with branch + multiple loads (deref chains
    # like `if (a0->[X]) return a0->[Y]; else return 0;`).
    ("cond-deref-leaf",
     "Leaf (no jal) with branch, no VU (cond-return / deref+if)",
     lambda fn: fn.jal_count() == 0 and _has_branch(fn) and _no_vu(fn) and 0x14 <= fn.size <= 0x30),
    # 1-jal mid-size — captures larger wrappers between 0x40-0x60.
    ("wrap-1jal-0x40-0x60",
     "0x40-0x60, exactly 1 jal, no VU (mid-size wrapper)",
     lambda fn: 0x40 <= fn.size <= 0x60 and fn.jal_count() == 1 and _no_vu(fn)),
    # 2-jal mid-size — captures 2-call wrappers in 0x40-0x60.
    ("wrap-2jal-0x40-0x60",
     "0x40-0x60, exactly 2 jal, no VU (2-call mid-size wrapper)",
     lambda fn: 0x40 <= fn.size <= 0x60 and fn.jal_count() == 2 and _no_vu(fn)),
    # VU0 macros.
    ("vu-leaf-4-0x10",
     "4-insn / 0x10 leaf, no jal, has VU (VU0 macro)",
     lambda fn: fn.size == 0x10 and len(fn.insns) == 4 and fn.jal_count() == 0 and _has_vu(fn)),
    ("vu-leaf-56-0x14-0x18",
     "5-6 insn / 0x14-0x18 leaf, no jal, has VU (VU0 macro)",
     lambda fn: fn.size in (0x14, 0x18) and len(fn.insns) in (5, 6)
                and fn.jal_count() == 0 and _has_vu(fn)),
]

# ---------------------------------------------------------------------------
# Promise heuristic
#
# Lower score == more promising. Roughly:
#   - smaller size and fewer insns first;
#   - penalize "hard" patterns we know cause near-miss diffs.
# ---------------------------------------------------------------------------

# split la-macro: lui $vN, %hi(...) followed (eventually) by addiu $vN, $vN, %lo
LUI_HI_RE = re.compile(r"^lui\s+(\$\w+),\s*%hi\(")
ADDIU_LO_RE = re.compile(r"^addiu\s+(\$\w+),\s*\1,\s*%lo\(")
# daddu rX, $zero, $zero — odd "clear via daddu" pattern that ee-gcc misses
DADDU_ZERO_RE = re.compile(r"^daddu\s+\$\w+,\s*\$zero,\s*\$zero\b")
# float load/move pair often-matched-but-fragile
FLOAT_PAIR_RE = re.compile(r"^(mtc1|lwc1|swc1|cvt\.|mfc1)\b")


def _hard_pattern_penalty(fn: Func) -> int:
    penalty = 0
    # split la-macro
    insns = fn.insns
    for i, ins in enumerate(insns):
        m = LUI_HI_RE.match(ins)
        if not m:
            continue
        reg = m.group(1)
        # find matching addiu in later instructions
        for j in range(i + 1, len(insns)):
            n = ADDIU_LO_RE.match(insns[j])
            if n and n.group(1) == reg:
                if j != i + 1:
                    penalty += 2  # split macro
                break
    for ins in insns:
        if DADDU_ZERO_RE.match(ins):
            penalty += 1
        if FLOAT_PAIR_RE.match(ins):
            penalty += 1
    return penalty


def _promise_key(fn: Func) -> tuple:
    # primary: hard-pattern penalty (low first)
    # secondary: insn count
    # tertiary: size
    # quaternary: name (stable)
    return (_hard_pattern_penalty(fn), len(fn.insns), fn.size, fn.name)


# ---------------------------------------------------------------------------
# Output
# ---------------------------------------------------------------------------

def _short_path(path: str) -> str:
    p = Path(path)
    try:
        return str(p.relative_to(REPO))
    except ValueError:
        return path


def _first_mnemonics(fn: Func, n: int = 4) -> str:
    return " ".join(fn.mnemonics[:n])


def _render_table(funcs: list[Func]) -> list[str]:
    out = [
        "| Function | Size | Insns | jal | VU | First mnemonics | Source |",
        "|---|---:|---:|---:|:---:|---|---|",
    ]
    for fn in funcs:
        out.append(
            "| `{name}` | 0x{size:X} | {insns} | {jal} | {vu} | `{mn}` | {src}:{line} |".format(
                name=fn.name,
                size=fn.size,
                insns=len(fn.insns),
                jal=fn.jal_count(),
                vu="Y" if fn.has_vu() else "",
                mn=_first_mnemonics(fn),
                src=_short_path(fn.path),
                line=fn.line,
            )
        )
    return out


def _load_parked() -> set[str]:
    """Enumerate parked function names from `tough_nuts/<func>/` subdirs."""
    parked: set[str] = set()
    if not TOUGH_NUTS_DIR.is_dir():
        return parked
    for entry in TOUGH_NUTS_DIR.iterdir():
        if entry.is_dir() and entry.name.startswith("func_"):
            parked.add(entry.name)
    return parked


def build_report(funcs: list[Func], parked: set[str], top: int) -> str:
    now = _dt.datetime.now(_dt.timezone.utc).strftime("%Y-%m-%d %H:%M:%S UTC")
    lines: list[str] = []
    lines.append("# Matching candidates")
    lines.append("")
    lines.append("Auto-generated unmatched-function shortlist for the ICO matching loop.")
    lines.append("")
    lines.append("- Generated: " + now)
    lines.append("- Source: `tools/gen_candidates.py` (reads `tools/find_leaves.py` cache)")
    lines.append("- Regenerate: `tools/gen_candidates.py` (also runs at the end of `make setup`)")
    lines.append("- Filter: functions registered under `tough_nuts/<func>/` are excluded")
    lines.append(
        "- Functions: {tot} total in `{glob}`, {parked} parked, {pool} considered".format(
            tot=len(funcs),
            glob=DEFAULT_GLOB,
            parked=sum(1 for fn in funcs if fn.name in parked),
            pool=sum(1 for fn in funcs if fn.name not in parked),
        )
    )
    lines.append(
        "- Sort within each section: hard-pattern penalty asc, insn count asc, size asc, name asc."
    )
    lines.append("")
    lines.append("Hard-pattern penalty up-weights known near-miss shapes:")
    lines.append("split `la` macro (`lui %hi` ... `addiu %lo`), `daddu rX, $zero, $zero`,")
    lines.append("and `mtc1`/`lwc1`/`swc1`/`cvt.*`/`mfc1` float-pair sequences.")
    lines.append("")
    lines.append("## Sections")
    lines.append("")
    for slug, title, _pred in CATEGORIES:
        lines.append(f"- [{title}](#{slug})")
    lines.append("")

    # bucket assignment: first-match wins
    pool = [fn for fn in funcs if fn.name not in parked]
    used: set[int] = set()  # id() of placed Func objects
    buckets: dict[str, list[Func]] = {slug: [] for slug, _, _ in CATEGORIES}
    for fn in pool:
        for slug, _title, pred in CATEGORIES:
            if pred(fn):
                buckets[slug].append(fn)
                used.add(id(fn))
                break

    for slug, title, _pred in CATEGORIES:
        ranked = sorted(buckets[slug], key=_promise_key)
        total = len(ranked)
        shown = ranked[:top]
        lines.append(f'<a id="{slug}"></a>')
        lines.append(f"## {title}")
        lines.append("")
        lines.append(f"_{total} total in this bucket; showing top {len(shown)}._")
        lines.append("")
        if not shown:
            lines.append("(empty)")
            lines.append("")
            continue
        lines.extend(_render_table(shown))
        lines.append("")

    # uncategorized summary so we don't lose track of what's left
    leftover = [fn for fn in pool if id(fn) not in used]
    lines.append('<a id="uncategorized"></a>')
    lines.append("## Uncategorized (not in any shape bucket above)")
    lines.append("")
    lines.append(
        f"_{len(leftover)} unmatched functions are not in any shape bucket above._"
    )
    lines.append("")
    lines.append(
        "Tweak the buckets in `tools/gen_candidates.py` to surface more shapes."
    )
    lines.append("")

    return "\n".join(lines) + "\n"


def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("--path", default=DEFAULT_GLOB,
                    help=f"glob for splat asm (default: {DEFAULT_GLOB})")
    ap.add_argument("--out", default=str(DEFAULT_OUT),
                    help="output path, or '-' for stdout")
    ap.add_argument("--top", type=int, default=50,
                    help="max rows per category (default: 50)")
    ap.add_argument("--rebuild-cache", action="store_true",
                    help="ignore the find_leaves.py cache and re-parse")
    args = ap.parse_args(argv)

    paths = sorted(glob.glob(args.path))
    if not paths:
        print(f"gen_candidates: no files matched {args.path}; nothing to do",
              file=sys.stderr)
        return 0

    t0 = time.time()
    funcs = load_funcs(paths, rebuild=args.rebuild_cache)
    parked = _load_parked()
    text = build_report(funcs, parked, args.top)
    elapsed = time.time() - t0

    if args.out == "-":
        sys.stdout.write(text)
    else:
        out_path = Path(args.out)
        out_path.parent.mkdir(parents=True, exist_ok=True)
        out_path.write_text(text, encoding="utf-8")
        print(
            f"gen_candidates: wrote {out_path} "
            f"({len(funcs)} funcs, {len(parked)} parked, {elapsed:.2f}s)",
            file=sys.stderr,
        )
    return 0


if __name__ == "__main__":
    try:
        sys.exit(main())
    except Exception as exc:  # noqa: BLE001 — never break `make setup`
        print(f"gen_candidates: WARNING — generation failed: {exc}",
              file=sys.stderr)
        sys.exit(0)
