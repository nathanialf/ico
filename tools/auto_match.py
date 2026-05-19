#!/usr/bin/env python3
"""
tools/auto_match.py — batch orchestrator built on classify_asm + claim + quick_diff.

For each candidate (an asm `.s` file path, or a `func_X` name):
  1. Find the .s and parse vram + size from the `nonmatching` declaration.
  2. Run classify_asm to pick the top recipe.
  3. Scaffold the C template into a per-candidate plan.
  4. (in --apply mode) Write src/cod/<file_off>.c, invoke tools/claim.py
     to flip the yaml entry, then run `tools/build.sh setup` ONCE for the
     whole batch (per feedback_match_batching nuclear-clean discipline),
     then `tools/quick_diff.sh` each candidate and tabulate the results.
  5. (in --apply --park-on-fail mode) For functions that did not match,
     invoke tools/park.sh to move them into tough_nuts/ rather than leave
     broken .c files around (per feedback_park_failed_matches).

Modes:
  --dry-run     (DEFAULT) print the plan; no filesystem changes.
  --scaffold-only  write scaffolds to /tmp/auto_match/ for review;
                no yaml/build touch.
  --apply       full pipeline (write src/cod/, claim, setup, quick_diff).
  --park-on-fail   with --apply: park failed matches via tools/park.sh.

Honored guardrails:
  - Default is non-destructive.
  - `--apply` will refuse if working tree has uncommitted edits to
    src/cod/ unless `--force` is given.
  - Setup uses an explicit subprocess timeout (per feedback_make_timeout).
  - Scaffold-only candidates that produce no template are skipped, never
    fabricated.
  - Never `rm src/cod/<file>.c` — failed matches go through tools/park.sh.

Usage:
    tools/auto_match.py asm/.../func_X.s asm/.../func_Y.s   # dry-run
    tools/auto_match.py --scaffold-only --bucket asm/nonmatchings/src/Foo/
    tools/auto_match.py --apply --from candidates.txt
    tools/auto_match.py --apply --park-on-fail func_001AB000
"""

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
import tempfile
from dataclasses import dataclass, field
from pathlib import Path

# Reuse classify_asm's plumbing rather than reimplementing it.
sys.path.insert(0, str(Path(__file__).resolve().parent))
import classify_asm  # type: ignore  # noqa: E402

REPO_ROOT = Path(__file__).resolve().parent.parent
ASM_NONMATCHINGS = REPO_ROOT / "asm" / "nonmatchings"
SRC_COD = REPO_ROOT / "src" / "cod"
QUICK_DIFF = REPO_ROOT / "tools" / "quick_diff.sh"
CLAIM_PY = REPO_ROOT / "tools" / "claim.py"
PARK_SH = REPO_ROOT / "tools" / "park.sh"
BUILD_SH = REPO_ROOT / "tools" / "build.sh"

# Build setup can take a long time; capped per feedback_make_timeout.
BUILD_TIMEOUT_S = 30 * 60

# cod-segment file_off ↔ vram conversion. All matching candidates live here.
COD_FILE_OFF_TO_VRAM = 0x100000

# Source roots a function body can legitimately live under. If a func name
# appears as a real C definition / Pattern-C macro invocation in any of
# these, it's claimed; if it's INCLUDE_ASM'd, it's the canonical
# "unmatched inside coalesced TU" marker.
SEARCH_ROOTS = ("src", "include", "tough_nuts")

ICO_YAML = REPO_ROOT / "config" / "ico.us.yaml"
_YAML_ENTRY_RE = re.compile(
    r"^\s+-\s+\[\s*(0x[0-9A-Fa-f]+)\s*,\s*(\w+)(?:\s*,\s*([^\]]+))?\s*\]"
)


@dataclass
class Candidate:
    asm_path: Path
    func_name: str
    vram: int           # 0x001A2758
    file_off: int       # vram - 0x100000
    size: int           # bytes
    signals: classify_asm.Signals = field(default=None)  # type: ignore
    recipe_id: str = ""
    recipe_title: str = ""
    scaffold: str = ""  # rendered C
    outcome: str = ""   # "matched" / "diffs" / "no-recipe" / "no-template" / "skipped"
    diff_summary: str = ""


# ---------------------------------------------------------------------------
# Unmatched-detection — filter out functions that already have a claim
# somewhere in the source tree before they ever enter the candidate list.
# ---------------------------------------------------------------------------

def _find_include_asm_site(func_name: str) -> str:
    """If `func_name` is INCLUDE_ASM'd inside a coalesced TU, return a
    short `<path>:<line>` hint pointing at the line to replace. Returns
    empty string if no such site exists (pure asm subseg or otherwise)."""
    src = REPO_ROOT / "src"
    if not src.is_dir():
        return ""
    try:
        r = subprocess.run(
            ["grep", "-rn", "-w", func_name, str(src)],
            capture_output=True, text=True, check=False,
        )
    except FileNotFoundError:
        return ""
    for line in r.stdout.splitlines():
        if "INCLUDE_ASM(" in line and func_name in line:
            # line is "<path>:<lineno>:<content>"
            try:
                path, lineno, _ = line.split(":", 2)
                rel = Path(path).relative_to(REPO_ROOT)
                return f"{rel}:{lineno}  (replace INCLUDE_ASM with scaffold)"
            except (ValueError, IndexError):
                return line.split(":", 1)[0]
    return ""


def _load_yaml_intervals() -> list[tuple[int, str, str]]:
    """Parse `config/ico.us.yaml` into a list of (vram_start, type, name)
    intervals sorted by vram. Only entries with `0x...` file_offs in the
    cod range are converted to vram (file_off + 0x100000); others are
    skipped since they aren't matching candidates anyway."""
    out: list[tuple[int, str, str]] = []
    if not ICO_YAML.exists():
        return out
    for line in ICO_YAML.read_text().splitlines():
        m = _YAML_ENTRY_RE.match(line)
        if not m:
            continue
        file_off = int(m.group(1), 16)
        subseg_type = m.group(2)
        name = (m.group(3) or "").strip()
        out.append((file_off + COD_FILE_OFF_TO_VRAM, subseg_type, name))
    out.sort(key=lambda e: e[0])
    return out


def _subseg_for_vram(
    vram: int, intervals: list[tuple[int, str, str]]
) -> tuple[str, str] | None:
    """Largest interval[i].vram <= vram. Returns (type, name) or None."""
    if not intervals:
        return None
    import bisect
    keys = [e[0] for e in intervals]
    idx = bisect.bisect_right(keys, vram) - 1
    if idx < 0:
        return None
    _, t, n = intervals[idx]
    return t, n


# Patterns used to decide whether a grep hit represents an actual claim.
def _include_asm_re(func: str) -> re.Pattern:
    return re.compile(rf"INCLUDE_ASM\([^)]*\b{re.escape(func)}\b")


def _c_def_re(func: str) -> re.Pattern:
    # `<rettype> func_X(args) {` — definition opening
    return re.compile(
        rf"^\s*\w[\w\s*]*\b{re.escape(func)}\s*\([^;]*\)\s*\{{",
        re.MULTILINE,
    )


def _macro_inv_re(func: str) -> re.Pattern:
    # Pattern-C: `SYSCALL_WRAPPER(func_X, 0x53)` etc. at column 0.
    return re.compile(rf"^[A-Z][A-Z_0-9]*\(\s*{re.escape(func)}\b", re.MULTILINE)


def is_unmatched(func_name: str, vram: int,
                 intervals: list[tuple[int, str, str]] | None = None) -> tuple[bool, str]:
    """Return (is_unmatched, reason). `reason` is a short human-readable
    string the caller can surface in skip messages.
    """
    if intervals is None:
        intervals = _load_yaml_intervals()
    seg = _subseg_for_vram(vram, intervals)
    if seg is None:
        return True, "no covering yaml subseg"
    subseg_type, subseg_name = seg
    if subseg_type == "hasm":
        return False, f"hasm subseg ({subseg_name}) — matched via Pattern A"
    if subseg_type == "asm":
        return True, f"asm subseg ({subseg_name}) — no claim yet"
    if subseg_type != "c":
        # bin/data/etc — not a matching candidate
        return False, f"non-c subseg type ({subseg_type})"

    # `c` subseg — disambiguate by source content.
    include_asm = _include_asm_re(func_name)
    c_def = _c_def_re(func_name)
    macro_inv = _macro_inv_re(func_name)
    found_any = False
    for root in SEARCH_ROOTS:
        rpath = REPO_ROOT / root
        if not rpath.is_dir():
            continue
        try:
            r = subprocess.run(
                ["grep", "-rln", "-w", func_name, str(rpath)],
                capture_output=True, text=True, check=False,
            )
        except FileNotFoundError:
            return True, "grep unavailable; defaulting to unmatched"
        for p in r.stdout.splitlines():
            found_any = True
            text = Path(p).read_text(errors="replace")
            if include_asm.search(text):
                return True, f"INCLUDE_ASM in {Path(p).relative_to(REPO_ROOT)}"
            if c_def.search(text):
                return False, f"C definition in {Path(p).relative_to(REPO_ROOT)}"
            if macro_inv.search(text):
                return False, f"Pattern-C macro in {Path(p).relative_to(REPO_ROOT)}"
            if "tough_nuts" in p:
                return False, f"parked seed at {Path(p).relative_to(REPO_ROOT)}"
    if found_any:
        # Func name appeared somewhere (extern decl / call site) but no
        # claim pattern matched. Be conservative and treat as claimed —
        # the cost of skipping a real candidate is one human review;
        # the cost of including a claimed func is wasted setup runs.
        return False, "name appears in source (extern/call); treating as claimed"
    return True, "no body found in any source root"


# ---------------------------------------------------------------------------
# Candidate resolution
# ---------------------------------------------------------------------------

def _resolve_arg(arg: str) -> Path | None:
    """Accept either an .s path or a `func_X` name. Returns a Path or None."""
    p = Path(arg)
    if p.exists() and p.suffix == ".s":
        return p
    if arg.startswith("func_"):
        hits = list(ASM_NONMATCHINGS.rglob(f"{arg}.s"))
        if len(hits) == 1:
            return hits[0]
        if len(hits) > 1:
            print(f"warn: multiple .s for {arg}: {hits}", file=sys.stderr)
            return hits[0]
    return None


def _parse_decl(asm_path: Path) -> tuple[int, int] | None:
    """Pull vram + size from the `nonmatching func_X, 0xN` line."""
    text = asm_path.read_text()
    m = re.search(r"nonmatching\s+func_([0-9A-Fa-f]+),\s*(0x[0-9A-Fa-f]+)",
                  text)
    if not m:
        return None
    return int(m.group(1), 16), int(m.group(2), 16)


def build_candidate(
    arg: str,
    intervals: list[tuple[int, str, str]] | None = None,
    force: bool = False,
) -> Candidate | None:
    """Resolve `arg` (path or func name) into a Candidate, or return None
    if the function is already claimed/matched. Pass `force=True` to
    bypass the unmatched-detection (useful when iterating on a known
    near-miss the user named explicitly).
    """
    asm = _resolve_arg(arg)
    if asm is None:
        print(f"skip: cannot resolve {arg!r}", file=sys.stderr)
        return None
    decl = _parse_decl(asm)
    if decl is None:
        print(f"skip: {asm} has no `nonmatching` decl", file=sys.stderr)
        return None
    vram, size = decl
    file_off = vram - 0x100000
    sig = classify_asm.extract_signals(asm)
    func_name = sig.name or f"func_{vram:08X}"

    if not force:
        unmatched, reason = is_unmatched(func_name, vram, intervals=intervals)
        if not unmatched:
            print(f"skip: {func_name} is claimed — {reason}", file=sys.stderr)
            return None

    return Candidate(asm_path=asm, func_name=func_name,
                     vram=vram, file_off=file_off, size=size, signals=sig)


# ---------------------------------------------------------------------------
# Scaffolding
# ---------------------------------------------------------------------------

def attach_scaffold(c: Candidate, cookbook: dict[str, "classify_asm.Recipe"]) -> None:
    """Attach a starter scaffold to `c`. Prefer the cookbook recipe; fall
    back to an asm-derived structural scaffold so the user/AI always gets
    something compilable to iterate on — never an empty result for a
    truly-unmatched candidate."""
    hits = classify_asm.score(c.signals)
    asm_text = c.asm_path.read_text(errors="replace")
    if hits:
        top = hits[0][0]
        c.recipe_id = top.id
        c.recipe_title = top.name
        recipe = cookbook.get(top.id)
        if recipe is not None and recipe.template:
            c.scaffold = classify_asm.scaffold(recipe, c.func_name, signals=c.signals)
            return
        # Recipe matched but has no template (e.g. §1.3 PARK, §3.3 park,
        # §0.0 natural-C). Still emit the structural fallback so the
        # human has the asm inline + an inferred signature.
        c.outcome = "no-template"
    else:
        c.outcome = "no-recipe"

    c.scaffold = classify_asm.fallback_scaffold(c.signals, asm_text)


# ---------------------------------------------------------------------------
# Apply mode — destructive steps
# ---------------------------------------------------------------------------

def working_tree_dirty(paths: list[Path]) -> list[str]:
    """Return list of dirty files among `paths` (relative to repo root)."""
    rels = [str(p.relative_to(REPO_ROOT)) for p in paths if p.exists()]
    if not rels:
        return []
    try:
        out = subprocess.run(
            ["git", "status", "--porcelain", *rels],
            cwd=REPO_ROOT, capture_output=True, text=True, check=False,
        )
    except FileNotFoundError:
        return []
    return [line[3:] for line in out.stdout.splitlines() if line.strip()]


def write_scaffolds(cands: list[Candidate]) -> int:
    """Write scaffolded .c files to src/cod/<file_off>.c. Returns count."""
    SRC_COD.mkdir(parents=True, exist_ok=True)
    n = 0
    for c in cands:
        if not c.scaffold:
            continue
        target = SRC_COD / f"{c.file_off:06X}.c"
        target.write_text(c.scaffold)
        n += 1
    return n


def claim_all(cands: list[Candidate]) -> int:
    """Flip yaml entries for each scaffolded candidate via tools/claim.py.

    We use the single-claim form here because the batch TOML manifest
    would require re-serializing the (already-on-disk) scaffold body,
    and the single form happily reads stdin.
    """
    failed = 0
    for c in cands:
        if not c.scaffold:
            continue
        src_file = SRC_COD / f"{c.file_off:06X}.c"
        body = src_file.read_text()
        cmd = [
            sys.executable, str(CLAIM_PY), "single",
            "--vram", hex(c.vram),
            "--size", hex(c.size),
            "--comment", f"auto_match §{c.recipe_id} {c.recipe_title}",
        ]
        r = subprocess.run(cmd, input=body, text=True,
                           cwd=REPO_ROOT, capture_output=True)
        if r.returncode != 0:
            print(f"claim {c.func_name} FAILED:\n{r.stdout}\n{r.stderr}",
                  file=sys.stderr)
            failed += 1
        else:
            print(f"  claimed {c.func_name} (vram={hex(c.vram)} size={hex(c.size)})")
    return failed


def nuclear_setup() -> bool:
    """`rm asm/cod/*.s && tools/build.sh setup` per feedback_match_batching."""
    asm_cod = REPO_ROOT / "asm" / "cod"
    if asm_cod.exists():
        for p in asm_cod.glob("*.s"):
            p.unlink()
        print(f"  cleaned {asm_cod}/*.s")
    print("  running tools/build.sh setup ...")
    try:
        r = subprocess.run(
            ["bash", str(BUILD_SH), "setup"],
            cwd=REPO_ROOT, timeout=BUILD_TIMEOUT_S, capture_output=True, text=True,
        )
    except subprocess.TimeoutExpired:
        print(f"setup TIMED OUT after {BUILD_TIMEOUT_S}s", file=sys.stderr)
        return False
    if r.returncode != 0:
        print("setup FAILED:", file=sys.stderr)
        print(r.stderr[-2000:], file=sys.stderr)
        return False
    return True


def run_quick_diff(c: Candidate) -> None:
    """Run quick_diff.sh; set c.outcome to 'matched' / 'diffs' / 'build-error'."""
    r = subprocess.run(
        ["bash", str(QUICK_DIFF), c.func_name],
        cwd=REPO_ROOT, capture_output=True, text=True,
    )
    if r.returncode != 0:
        c.outcome = "build-error"
        c.diff_summary = (r.stderr or r.stdout).strip().splitlines()[-1:][0] \
            if (r.stderr or r.stdout).strip() else "(no output)"
        return
    if "MATCH (canonical instruction stream identical)" in r.stdout:
        c.outcome = "matched"
        return
    c.outcome = "diffs"
    # Extract approximate diff width to give a useful summary.
    diff_lines = [l for l in r.stdout.splitlines()
                  if " | " in l or " > " in l or " < " in l]
    c.diff_summary = f"~{len(diff_lines)} differing lines"


def park_failed(cands: list[Candidate]) -> int:
    n = 0
    for c in cands:
        if c.outcome not in {"diffs", "build-error"}:
            continue
        reason = f"auto_match {c.outcome} after §{c.recipe_id} scaffold ({c.diff_summary})"
        r = subprocess.run(
            ["bash", str(PARK_SH), hex(c.vram), reason],
            cwd=REPO_ROOT, capture_output=True, text=True,
        )
        if r.returncode == 0:
            n += 1
            print(f"  parked {c.func_name} → tough_nuts/")
        else:
            print(f"park {c.func_name} FAILED:\n{r.stderr}", file=sys.stderr)
    return n


# ---------------------------------------------------------------------------
# Reporting
# ---------------------------------------------------------------------------

def print_plan(cands: list[Candidate]) -> None:
    print(f"\nplan ({len(cands)} candidates):")
    print(f"  {'func':<22} {'vram':<10} {'size':<8} {'recipe':<10} {'outcome'}")
    for c in cands:
        recipe = f"§{c.recipe_id}" if c.recipe_id else "—"
        oc = c.outcome or "scaffold"
        print(f"  {c.func_name:<22} {hex(c.vram):<10} {hex(c.size):<8} {recipe:<10} {oc}")


def print_results(cands: list[Candidate]) -> None:
    tally = {"matched": 0, "diffs": 0, "no-recipe": 0, "no-template": 0,
             "build-error": 0, "skipped": 0}
    print(f"\nresults ({len(cands)} candidates):")
    print(f"  {'func':<22} {'recipe':<10} {'outcome':<14} detail")
    for c in cands:
        tally[c.outcome] = tally.get(c.outcome, 0) + 1
        recipe = f"§{c.recipe_id}" if c.recipe_id else "—"
        detail = c.diff_summary if c.outcome in {"diffs", "build-error"} else ""
        print(f"  {c.func_name:<22} {recipe:<10} {c.outcome:<14} {detail}")
    print(f"\n  summary: " + ", ".join(f"{k}={v}" for k, v in tally.items() if v))


# ---------------------------------------------------------------------------
# Driver
# ---------------------------------------------------------------------------

def main(argv: list[str]) -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("targets", nargs="*",
                    help="asm .s paths or func_X names")
    ap.add_argument("--from", dest="from_file",
                    help="read targets from a file, one per line")
    ap.add_argument("--bucket",
                    help="recurse a dir, treating every func_*.s as a target")

    mode = ap.add_mutually_exclusive_group()
    mode.add_argument("--dry-run", action="store_true",
                      help="(default) print plan only, no changes")
    mode.add_argument("--scaffold-only", action="store_true",
                      help="write scaffolds to /tmp/auto_match/ for review")
    mode.add_argument("--apply", action="store_true",
                      help="full pipeline (write src/cod, claim, setup, quick_diff)")

    ap.add_argument("--park-on-fail", action="store_true",
                    help="with --apply: park unmatched via tools/park.sh")
    ap.add_argument("--force", action="store_true",
                    help="allow --apply even if working tree is dirty")
    ap.add_argument("--top", type=int, default=1,
                    help="recipe rank to scaffold (default 1 = top)")
    ap.add_argument("--include-claimed", action="store_true",
                    help="bypass the unmatched-detection (use when iterating "
                         "on a known near-miss that's already in src/)")
    args = ap.parse_args(argv[1:])

    # Collect targets.
    targets: list[str] = list(args.targets)
    if args.from_file:
        targets += [l.strip() for l in Path(args.from_file).read_text().splitlines()
                    if l.strip() and not l.startswith("#")]
    if args.bucket:
        bdir = Path(args.bucket)
        if not bdir.is_dir():
            print(f"not a directory: {bdir}", file=sys.stderr)
            return 2
        targets += [str(p) for p in sorted(bdir.rglob("func_*.s"))]

    if not targets:
        ap.print_usage(sys.stderr)
        return 2

    # Load yaml once so the unmatched-detection isn't re-parsing per candidate.
    intervals = _load_yaml_intervals()

    cands: list[Candidate] = []
    skipped = 0
    for t in targets:
        c = build_candidate(t, intervals=intervals, force=args.include_claimed)
        if c:
            cands.append(c)
        else:
            skipped += 1
    if not cands:
        print(f"no resolvable candidates ({skipped} skipped/claimed)",
              file=sys.stderr)
        return 1
    if skipped:
        print(f"({skipped} target(s) filtered as already-claimed; pass "
              f"--include-claimed to bypass)", file=sys.stderr)

    cookbook = classify_asm.parse_cookbook()
    for c in cands:
        attach_scaffold(c, cookbook)

    # --- dry-run (default): print plan + ALL scaffolds to stdout.
    # Most candidates that survive the unmatched-detection filter live
    # inside a coalesced TU (`src/<TU>.c`), so the scaffold can't just
    # be written to `src/cod/<off>.c` — the human (or another tool)
    # has to splice the body into the TU file in place of the
    # `INCLUDE_ASM(...,func_X)` line. Printing every scaffold to stdout
    # makes that splice direct: copy, find the matching INCLUDE_ASM,
    # replace.
    if not (args.scaffold_only or args.apply):
        print_plan(cands)
        emitted = 0
        for c in cands:
            if not c.scaffold:
                continue
            splice_hint = _find_include_asm_site(c.func_name)
            print(f"\n--- scaffold {emitted+1}/{sum(1 for x in cands if x.scaffold)}: "
                  f"{c.func_name} (§{c.recipe_id}) ---")
            if splice_hint:
                print(f"# splice target: {splice_hint}")
            print(c.scaffold)
            emitted += 1
        if emitted == 0:
            print("\n(no scaffold-capable candidates in this batch)")
        return 0

    # --- scaffold-only: write to a tmp dir for review ---
    if args.scaffold_only:
        out = Path(tempfile.mkdtemp(prefix="auto_match_"))
        for c in cands:
            if not c.scaffold:
                continue
            (out / f"{c.file_off:06X}_{c.func_name}.c").write_text(c.scaffold)
        print_plan(cands)
        print(f"\nscaffolds written to {out}/")
        return 0

    # --- apply: full pipeline ---
    if args.apply:
        # Safety: refuse if there are dirty src/cod/ files that would be clobbered.
        dirty = working_tree_dirty([SRC_COD])
        if dirty and not args.force:
            print("refusing --apply: src/cod/ has uncommitted changes:",
                  file=sys.stderr)
            for d in dirty[:10]:
                print(f"  {d}", file=sys.stderr)
            print("  (pass --force to override)", file=sys.stderr)
            return 3

        n_written = write_scaffolds(cands)
        print(f"wrote {n_written} scaffolds under src/cod/")
        n_failed_claim = claim_all(cands)
        if n_failed_claim:
            print(f"WARNING: {n_failed_claim} claim(s) failed; continuing",
                  file=sys.stderr)

        if not nuclear_setup():
            print("setup failed — aborting before quick_diff", file=sys.stderr)
            return 4

        for c in cands:
            if c.outcome in {"no-recipe", "no-template"}:
                continue
            run_quick_diff(c)

        print_results(cands)

        if args.park_on_fail:
            n_parked = park_failed(cands)
            print(f"\nparked {n_parked} failed match(es)")

        return 0

    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
