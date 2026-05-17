#!/usr/bin/env python3
"""
promote_score0.py — sweep `lib/decomp-permuter/runs/` for score-0 hits
that haven't been promoted back into the matching pipeline yet.

A score-0 hit means the permuter found C source that compiles to
byte-identical instructions vs `target.s`. Auto-promotion isn't
automatic (auto_permute.sh stops at "MATCH:" log lines and waits for
operator review). This tool is the operator's review + apply path.

Walks `lib/decomp-permuter/runs/func_<VRAM>/output-0-N/score.txt`
for **N >= 1 only** (per `feedback_score0_promotion`: `output-0-base`
score=0 means "the seed already compiled, but it's a stale baseline",
not "a match was found"). Picks the lowest-N hit per function.

Default mode is **dry-run** — prints a TOML manifest preview
compatible with `tools/claim.py batch`. `--apply` runs the full
pipeline:

  1. Refuse if `git status --porcelain` shows changes in `src/cod/`
     or `config/ico.us.yaml` (operator must commit/stash first).
  2. Refuse if the run dir's mtime < 60 s (permuter might still be
     writing; wait).
  3. Hand the manifest to `tools/claim.py batch`.
  4. Run `tools/quick_diff.sh func_<VRAM>` on each promotion —
     must report clean. If not, revert the claim and log to
     `decomp/promote_failures.log`.
  5. On success: `git mv tough_nuts/func_<VRAM>/
     tough_nuts/.promoted/func_<VRAM>/`. The .promoted directory
     is the receipt; don't delete (same retention principle as
     tough_nuts itself).

Flags:

  --tu <path>     limit to one TU (resolves via decomp/tu_map.json)
  --apply         actually promote (default: dry-run preview)
  --limit N       cap promotions per invocation
  --json          machine-readable preview output

The dry-run is safe to run any time. **`--apply` should not run
during active coalesce work** — promoting a function changes its
yaml subseg from `asm` to `c`, which will conflict with whatever
the coalesce worker is doing to that function's TU. Coordinate.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import subprocess
import sys
import time
from pathlib import Path

try:
    import yaml
except ImportError:
    sys.exit("promote_score0: missing PyYAML.")

REPO = Path(__file__).resolve().parent.parent
RUNS_DIR = REPO / "lib" / "decomp-permuter" / "runs"
TOUGH_NUTS = REPO / "tough_nuts"
PROMOTED_DIR = TOUGH_NUTS / ".promoted"
TU_MAP_JSON = REPO / "decomp" / "tu_map.json"
YAML_PATH = REPO / "config" / "ico.us.yaml"
FAILURE_LOG = REPO / "decomp" / "promote_failures.log"
CLAIM_PY = REPO / "tools" / "claim.py"
QUICK_DIFF = REPO / "tools" / "quick_diff.sh"

VRAM_BASE = 0x00100000
MIN_RUN_DIR_AGE_SECS = 60


# ----------------------------------- scanning

_FUNC_NAME_RE = re.compile(r"^func_([0-9A-Fa-f]{8})$")


def _vram_from_func_name(name: str) -> int | None:
    m = _FUNC_NAME_RE.match(name)
    if not m:
        return None
    return int(m.group(1), 16)


def _output_dir_score(out_dir: Path) -> str | None:
    score_file = out_dir / "score.txt"
    if not score_file.exists():
        return None
    return score_file.read_text().strip()


def _best_score0_output(run_dir: Path) -> Path | None:
    """Lowest-N output-0-N (N>=1) with score=0. None if none qualify."""
    candidates = []
    for sub in run_dir.glob("output-0-*"):
        if sub.name == "output-0-base":
            continue
        try:
            n = int(sub.name.rsplit("-", 1)[-1])
        except ValueError:
            continue
        if _output_dir_score(sub) == "0":
            candidates.append((n, sub))
    if not candidates:
        return None
    candidates.sort()
    return candidates[0][1]


def _load_tu_for_vram() -> dict[int, str | None]:
    if not TU_MAP_JSON.exists():
        return {}
    out: dict[int, str | None] = {}
    for f in json.loads(TU_MAP_JSON.read_text()):
        out[f["vram"]] = f.get("tu")
    return out


def _load_size_for_vram() -> dict[int, int]:
    """Approximate per-function size from next-vma deltas. Same trick
    tu_status uses."""
    if not TU_MAP_JSON.exists():
        return {}
    vmas = sorted(f["vram"] for f in json.loads(TU_MAP_JSON.read_text())
                  if "vram" in f)
    out: dict[int, int] = {}
    for i, v in enumerate(vmas):
        nxt = vmas[i + 1] if i + 1 < len(vmas) else v + 0x40
        out[v] = max(0, nxt - v)
    return out


def _yaml_subseg_for_vma(vma: int) -> tuple[str, str] | None:
    """Walk the yaml's text subsegments and return (stype, name) for
    the one covering vma. None if not found."""
    doc = yaml.safe_load(YAML_PATH.read_text())
    items: list[tuple[int, str, str]] = []
    for seg in doc.get("segments", []):
        if isinstance(seg, list):
            continue
        for sub in seg.get("subsegments", []):
            if isinstance(sub, list) and len(sub) >= 2:
                off = sub[0]
                stype = sub[1]
                name = sub[2] if len(sub) >= 3 else ""
            elif isinstance(sub, dict):
                off = sub.get("vram", 0)
                stype = sub.get("type", "")
                name = sub.get("name", "")
            else:
                continue
            if stype in {"asm", "c", "hasm"}:
                items.append((off + VRAM_BASE, stype, name))
    items.sort()
    found = None
    for v, stype, name in items:
        if v <= vma:
            found = (stype, name)
        else:
            break
    return found


# ----------------------------------- promotion plan

def build_plan(tu_filter: str | None) -> list[dict]:
    """Scan permuter runs and assemble a promotion plan. Each entry:
    {func_name, vram, file_off, size, tu, parked_src, promoted_src,
     run_subdir, mtime, current_stype, current_name, blocked_reason?}.
    """
    if not RUNS_DIR.is_dir():
        return []
    tu_for_vram = _load_tu_for_vram()
    size_for_vram = _load_size_for_vram()
    plan = []
    for run_dir in sorted(RUNS_DIR.glob("func_*")):
        name = run_dir.name
        vram = _vram_from_func_name(name)
        if vram is None:
            continue
        out_dir = _best_score0_output(run_dir)
        if out_dir is None:
            continue
        promoted_src = out_dir / "source.c"
        if not promoted_src.exists():
            continue
        parked_src = TOUGH_NUTS / name / f"{vram - VRAM_BASE:06X}.c"
        # Some parked seeds use the function name instead of the offset.
        if not parked_src.exists():
            alt = TOUGH_NUTS / name / f"{name}.c"
            parked_src = alt if alt.exists() else parked_src
        if not parked_src.exists():
            blocked = "no parked source in tough_nuts/"
        else:
            blocked = None
        cur = _yaml_subseg_for_vma(vram)
        if cur is None:
            blocked = blocked or "no yaml subseg covers this vma"
            cur = ("", "")
        elif cur[0] != "asm":
            blocked = (blocked or
                       f"yaml already typed {cur[0]} (name={cur[1]!r}); "
                       "already promoted or owned by coalesce")
        size = size_for_vram.get(vram, 0)
        tu = tu_for_vram.get(vram)
        if tu_filter:
            wanted = tu_filter if tu_filter.endswith(".c") else tu_filter + ".c"
            if tu != wanted:
                continue
        plan.append({
            "func_name": name,
            "vram": f"0x{vram:08X}",
            "vram_int": vram,
            "file_off": f"0x{vram - VRAM_BASE:06X}",
            "size": size,
            "tu": tu,
            "parked_src": str(parked_src.relative_to(REPO)) if parked_src.exists() else None,
            "promoted_src": str(promoted_src.relative_to(REPO)),
            "run_subdir": str(out_dir.relative_to(REPO)),
            "mtime": os.path.getmtime(out_dir),
            "current_stype": cur[0],
            "current_name": cur[1],
            "blocked_reason": blocked,
        })
    return plan


# ----------------------------------- preview

def render_toml_manifest(entries: list[dict]) -> str:
    """Render the actionable entries as a claim.py-compatible TOML
    batch manifest. Bodies are read from each promoted_src on demand."""
    lines = []
    lines.append("# Score-0 promotion batch (auto-generated preview)")
    lines.append("# Hand to: tools/claim.py batch --manifest <this-file>")
    lines.append("")
    for e in entries:
        if e["blocked_reason"]:
            continue
        body = (REPO / e["promoted_src"]).read_text()
        lines.append("[[claim]]")
        lines.append(f"vram = {e['vram_int']}  # {e['vram']}  {e['func_name']}")
        lines.append(f"size = {e['size']}  # 0x{e['size']:X}")
        lines.append(f"comment = \"promoted from {e['run_subdir']}\"")
        # Heredoc-style body. Triple-quote, with any inner \"\"\" escaped.
        safe = body.replace('"""', '\\"\\"\\"')
        lines.append('body = """')
        lines.append(safe.rstrip())
        lines.append('"""')
        lines.append("")
    return "\n".join(lines)


def render_table(entries: list[dict]) -> str:
    if not entries:
        return "(no promotable entries found)\n"
    lines = []
    lines.append(f"{'func':<20} {'vram':>10} {'size':>6} "
                 f"{'tu':<32} status")
    lines.append("-" * 90)
    for e in entries:
        tu = e["tu"] or "(untagged)"
        if e["blocked_reason"]:
            status = f"BLOCKED: {e['blocked_reason']}"
        else:
            age = time.time() - e["mtime"]
            status = f"ready (run age {age/60:.1f}m)"
        lines.append(f"{e['func_name']:<20} {e['vram']:>10} "
                     f"{e['size']:>6} {tu[:32]:<32} {status}")
    return "\n".join(lines) + "\n"


# ----------------------------------- apply

def _git_clean_critical_paths() -> bool:
    out = subprocess.run(
        ["git", "status", "--porcelain", "src/cod", "config/ico.us.yaml"],
        cwd=REPO, capture_output=True, text=True,
    )
    return out.stdout.strip() == ""


def _apply_one(entry: dict) -> tuple[bool, str]:
    """Promote a single entry. Return (ok, message)."""
    age = time.time() - entry["mtime"]
    if age < MIN_RUN_DIR_AGE_SECS:
        return (False, f"run dir age {age:.1f}s < {MIN_RUN_DIR_AGE_SECS}s")
    # Build a one-entry TOML manifest in a temp file.
    import tempfile
    manifest = render_toml_manifest([entry])
    with tempfile.NamedTemporaryFile("w", suffix=".toml", delete=False) as tf:
        tf.write(manifest)
        manifest_path = tf.name
    try:
        r = subprocess.run(
            [sys.executable, str(CLAIM_PY), "batch",
             "--manifest", manifest_path],
            cwd=REPO, capture_output=True, text=True,
        )
        if r.returncode != 0:
            return (False, f"claim.py batch failed: {r.stderr.strip()[:200]}")
        # Verify with quick_diff.
        r2 = subprocess.run(
            ["bash", str(QUICK_DIFF), entry["func_name"]],
            cwd=REPO, capture_output=True, text=True,
        )
        if "MATCH" not in r2.stdout:
            # Revert the claim before bailing.
            _revert_claim(entry)
            return (False, "quick_diff did not report MATCH")
        # Move parked tough_nuts entry to .promoted/.
        PROMOTED_DIR.mkdir(parents=True, exist_ok=True)
        src_park = TOUGH_NUTS / entry["func_name"]
        if src_park.is_dir():
            dst_park = PROMOTED_DIR / entry["func_name"]
            subprocess.run(["git", "mv", str(src_park), str(dst_park)],
                           cwd=REPO, check=False)
        return (True, "promoted + quick_diff clean")
    finally:
        try:
            os.unlink(manifest_path)
        except OSError:
            pass


def _revert_claim(entry: dict) -> None:
    """Undo a claim that was applied but failed verification."""
    subprocess.run(
        ["git", "checkout", "--", "config/ico.us.yaml"],
        cwd=REPO, check=False, capture_output=True,
    )
    cod_path = REPO / "src" / "cod" / f"{entry['file_off'].lower()[2:]}.c"
    if cod_path.exists():
        cod_path.unlink()


# ----------------------------------- main

def main(argv: list[str] | None = None) -> int:
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[1])
    ap.add_argument("--tu", default=None,
                    help="limit to one TU (e.g. src/Basic.c)")
    ap.add_argument("--apply", action="store_true",
                    help="actually promote (default: dry-run)")
    ap.add_argument("--limit", type=int, default=0,
                    help="cap promotions per invocation (0 = unlimited)")
    ap.add_argument("--json", action="store_true",
                    help="JSON output instead of human-readable")
    ap.add_argument("--show-blocked", action="store_true",
                    help="include BLOCKED entries in the report")
    args = ap.parse_args(argv)

    plan = build_plan(args.tu)
    if args.limit:
        plan = plan[: args.limit]

    if args.json:
        print(json.dumps([
            {k: v for k, v in e.items() if k != "vram_int"}
            for e in plan
        ], indent=2))
        return 0

    actionable = [e for e in plan if not e["blocked_reason"]]
    print(f"# score-0 promotion sweep — {len(plan)} candidates "
          f"({len(actionable)} actionable, "
          f"{len(plan) - len(actionable)} blocked)",
          file=sys.stderr)

    if args.show_blocked:
        sys.stdout.write(render_table(plan))
    else:
        sys.stdout.write(render_table(actionable))

    if not args.apply:
        print("\n# Dry-run: not applying. Pass --apply to promote.",
              file=sys.stderr)
        if actionable:
            sys.stdout.write("\n# TOML manifest preview "
                             "(would be handed to claim.py batch):\n")
            sys.stdout.write(render_toml_manifest(actionable[:3]))
            if len(actionable) > 3:
                print(f"# … {len(actionable) - 3} more entries elided",
                      file=sys.stderr)
        return 0

    # ----- apply path -----
    if not _git_clean_critical_paths():
        sys.exit("promote_score0: refuse to --apply with dirty "
                 "src/cod/ or config/ico.us.yaml. Commit or stash first.")

    n_ok = 0
    n_fail = 0
    for e in actionable:
        ok, msg = _apply_one(e)
        if ok:
            n_ok += 1
            print(f"OK   {e['func_name']}: {msg}", file=sys.stderr)
        else:
            n_fail += 1
            print(f"FAIL {e['func_name']}: {msg}", file=sys.stderr)
            with FAILURE_LOG.open("a") as fh:
                fh.write(f"{time.strftime('%Y-%m-%dT%H:%M:%S')}  "
                         f"{e['func_name']}  {msg}\n")
    print(f"# promotion done: {n_ok} ok, {n_fail} failed", file=sys.stderr)
    return 0 if n_fail == 0 else 1


if __name__ == "__main__":
    sys.exit(main())
