#!/usr/bin/env python3
"""tools/lint_postprocess_collisions.py — flag TU-global postprocesses that can
collide between sibling functions in a coalesced TU.

~17 postprocess gates in tools/compile_c.sh are keyed by name and mutate the
WHOLE compiled .s. When the key is a TU (not a single func) and that coalesced
TU has more than one matched C function, a postprocess added for ONE function
also rewrites its siblings — silently breaking them. That is exactly the
func_001E0D50-vs-func_001E44C0 swap_addu conflict: the per-TU sed swapped a
commutative addu in BOTH funcs though only one wanted it.

This is the STATIC detector for that class (pair it with tools/tu_check.py for
the dynamic check). For each TU-keyed postprocess config it reports every
listed TU that now has >1 matched C function. Entries that name a specific
function (`func_<hex>`) are already scoped and never flagged.

    tools/lint_postprocess_collisions.py            # human report
    tools/lint_postprocess_collisions.py --json

Exit status is nonzero if any latent collision is found.
"""
from __future__ import annotations
import argparse
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
from tu_check import matched_funcs, resolve_tu_path  # noqa: E402

# The name-gated postprocess configs whose application mutates the whole .s
# (from tools/compile_c.sh's `listed "${X_TXT}"` gates). Pattern-driven sed
# rewrites are the most dangerous; the python ones are listed too since several
# scan for a shape and hit every match in the TU.
CONFIGS = [
    ("swap_addu_operands.txt", "HIGH"),   # sed: commutative-addu operand swap
    ("coalesce_v1_v0.txt",     "HIGH"),   # sed: rewrites ALL $3 -> $2 in the TU
    ("no_trailing_nop.txt",    "med"),
    ("shared_sp_restore.txt",  "med"),
    ("shared_jr_restore.txt",  "med"),
    ("fcc_nop.txt",            "med"),
    ("early_body_swap.txt",    "med"),
    ("early_epilogue_restore.txt", "med"),
    ("fill_blez_delay.txt",    "med"),
    ("fill_beq_delay.txt",     "med"),
    ("v0_zero_in_bne_delay.txt", "med"),
    ("lui_const_swap.txt",     "med"),
    ("move_sw_v0_before_lds.txt", "med"),
    # Intentionally NOT listed (not func-scoping collisions):
    #  - use_modern_as.txt selects the assembler (ee-as vs modern mips-as) for
    #    the whole .o, not a per-func .s mutation, so it can't clobber a
    #    sibling's bytes and isn't func-scopable.
    #  - unfold_ra_delay.txt's tool already iterates per-function (FUNC_PATTERN)
    #    and only patches funcs carrying the exact beq+ld$31 fold, so it can't
    #    affect a sibling that lacks the pattern.
    # Both are whole-TU by nature; guard them with tu_check.py instead.
]


def entries(cfg: Path) -> list[str]:
    """Gate key of each non-comment line, EXCEPT lines already scoped with
    `@func_<hex>` tokens — those are explicitly limited to named funcs and so
    cannot collide with siblings."""
    out = []
    for line in cfg.read_text(errors="replace").splitlines():
        s = line.split("#", 1)[0].strip()
        if not s:
            continue
        if "@func_" in s:          # explicitly func-scoped -> safe
            continue
        out.append(s.split()[0])
    return out


def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args(argv[1:])

    findings = []
    for name, sev in CONFIGS:
        cfg = ROOT / "config" / name
        if not cfg.exists():
            continue
        for key in entries(cfg):
            if key.startswith("func_"):
                continue                      # func-scoped: not a TU collision
            if resolve_tu_path(key) is None:
                continue                      # not a resolvable TU name
            fns = matched_funcs(key)
            if len(fns) > 1:
                findings.append({"config": name, "severity": sev, "tu": key,
                                 "matched_funcs": len(fns), "funcs": fns})

    findings.sort(key=lambda f: ({"HIGH": 0, "med": 1, "low": 2}[f["severity"]],
                                 -f["matched_funcs"]))
    if args.json:
        print(json.dumps(findings, indent=2))
    else:
        if not findings:
            print("no latent postprocess/TU collisions found.")
        else:
            print(f"{len(findings)} latent TU-global postprocess collision(s) "
                  f"(verify each with `tools/tu_check.py <TU>`):\n")
            for f in findings:
                print(f"  [{f['severity']:>4}] {f['config']:<26} TU {f['tu']} "
                      f"has {f['matched_funcs']} matched funcs "
                      f"-> postprocess hits all of them")
    return 1 if findings else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
