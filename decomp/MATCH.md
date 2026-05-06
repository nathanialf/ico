# Matching prompt — ico (PS2)

Reuse this verbatim (paste it as the first message of a fresh Claude Code
session) to launch a matching work session on this repo.

---

Continue the **ICO** clean-room decomp at `/primary/dev/ico`. Working
directive: match as many ELF functions as possible, plug away at the
percentage. Same clean-room rules as before — no disc data, no extracted
assets, no leaked-source-derived code, no AI co-author trailer on
commits.

## Do not stop matching

**Run until the Claude usage cap stops you, or until the user explicitly
tells you to stop. Do not stop early, ever.** The only acceptable end-of-
stream is the cap or a direct user instruction.

Things that are **not** reasons to stop:

- Hitting a "natural seam" — current cluster cleared, deferred list
  felt thin, nothing obvious in `tools/find_siblings.py` (when it
  exists) or in `asm/cod/000000.s`.
- "N matches landed this iteration, that's a good place to pause."
  There is no good place to pause that isn't the cap or a user prompt.
- Round-trip went red and you can't immediately see why. Diagnose with
  `tools/first_diff.py`, revert if needed, keep going.
- The current target plateaued. Park it under `tough_nuts/` and pick
  another.

When the obvious seam runs out, broaden the search using the full
toolkit: rescan `asm/cod/000000.s` for more leaves, retry an older
deferred entry under newly acquired leverage, launch
`lib/decomp-permuter` on a near-miss, or pick a medium-size unmatched
function and start it. Reporting "I stopped because the obvious seam
ran out" or "I stopped because momentum felt right" is a session bug,
not a finish line.

**Do not emit "iteration results" / "final state" / "session summary"
text.** No bullet lists recapping matches and tough-nuts at the end of
a chunk of work, no "build green at SHA X" sign-off, no totals. That
summary text functions as a self-imposed stopping point. The only
acceptable end-of-stream is the cap or a user prompt; the work itself
(commits, `decomp/NOTES.md` edits, parked tough-nuts) is the record.
Brief mid-stream status notes ("matched func_X", "parking func_Y",
"moving on to subseg Z") are fine — but the moment a listed/numbered
recap shows up, the session has bugged out. Just keep matching.

**Read first** (in this order):

1. `CLAUDE.md` — IP rules, toolchain, build commands, conventions.
2. `decomp/NOTES.md` — every PS2 EE / compiler / splat / linker quirk
   catalogued so far. Most "near-miss" diffs are an instance of a
   pattern in here.
3. `docs/MATCHING_NOTES.md` — per-function tough-nuts and deferred
   targets.
4. `docs/LEGAL.md` — clean-room boundary, what's allowed as a reference,
   what's forbidden as an input.

## Toolkit

Run `--help` on each tool before first use; expect the inventory to grow
over time.

**Fast inner-loop diff (use these BEFORE `make split && make`):**

- `tools/quick_diff.sh <func_name>` — compile one .c (from `src/` or
  `tough_nuts/`) and side-by-side diff against the target asm in
  `asm/matchings/<func>/`. Skips splat and full-ELF linking — runs
  in ~100 ms vs ~30–60 s for `make setup && make`. This is the
  iteration loop for tough nuts.
- `tools/first_diff.py` — when SHA-1 fails, prints the first diverging
  instruction with the function name and call targets resolved through
  the mapfile. Run after a failed `make`.

**Splitting and linker plumbing:**

- `config/ico.us.yaml` — splat configuration. Convert `[0xADDR, asm]` to
  `[0xADDR, c, name]` to claim a subsegment for matching.
- `make setup` — runs splat + post-processing. Re-run after every yaml
  edit.

**Analysis:**

- Ghidra (`tools/ghidra/`) — interactive RE on `baserom/baseelf.elf`.
- `m2c` (`lib/m2c/`) — asm → C scaffold. R5900 MMI/VU may be
  unsupported; fall back to manual decompilation.
- `lib/asm-differ/` — function-level diffing while editing.
- `lib/decomp-permuter/` — randomized rewrites for near-miss matches.

## Picking the next target

**Default: read `docs/candidates.md`.** It's auto-regenerated at the end
of every `make setup` from a cached parse of `asm/cod/*.s`, sorted by
hard-pattern penalty / instruction count / size, with parked functions
already excluded. Eight pre-baked shape buckets cover the common shapes
I keep targeting (4-insn 0x10 leaf, 5-insn 0x14 store-and-forward, 8-insn
0x20 1-jal wrapper, etc.). `grep -E '^\| `func_'` and pick promising rows.

Only fall back to `tools/find_leaves.py` for ad-hoc shape filters that
aren't in the pre-baked buckets. The tool is a per-file pickle-cached
walker (so subsequent calls are fast), but the candidates file is
faster still and persistent.

## Per-function loop

1. Pick a `[0xADDR, asm]` line in `config/ico.us.yaml`. Prefer small,
   leaf-ish ranges. Look at the `.s` file to gauge complexity.
2. Change the line to `[0xADDR, c, name]` (and split the surrounding
   asm subsegment so the new `c` line has explicit asm neighbours).
   Re-run `make setup`. Splat emits the per-function baseline at
   `asm/matchings/name/<func>.s` (gitignored — regenerable from the
   ELF) and expects `src/name.c`.
3. Write the C. Iterate fast with `tools/quick_diff.sh name` until the
   diff is empty or trivially close.
4. Run `make` for the full byte-identical SHA-1 check. If it fails,
   run `tools/first_diff.py` and address the first divergence.
5. If stuck near-match: try `lib/decomp-permuter/` (timeout 300 s for a
   first attempt). If still stuck, park.
6. Once it matches, run `make progress`, run `./tools/check_no_rom.sh`,
   commit. No AI co-author trailer.

## Tough-nut parking

When a function plateaus (permuter exhausted, no obvious structural fix):

**Use `tools/park.sh <vram> "<reason>"`.** It does steps 1-3 below in one
go: moves the best-attempt `src/cod/<file_off>.c` into
`tough_nuts/<func>/<file_off>.c`, writes a `notes.md` with the reason
and a disassembly excerpt for permuter context, and reverts the yaml
line back to `asm`.

After parking, run `make setup && make` to confirm the asm fallback
round-trips, then commit. The auto-permuter (`tools/auto_permute*.sh`)
picks up the new `tough_nuts/` seed on its next pass.

Manual steps (what `park.sh` does):

1. Revert the yaml line to `[0xADDR, asm]`. Run `make setup` to confirm
   the tree is clean.
2. Move the best-attempt `src/name.c` to `tough_nuts/<func>/<func>.c`.
3. Write `tough_nuts/<func>/notes.md` with: failure mode, permuter
   plateau score, structural hints from the asm, what's been tried.
4. Commit the parking-doc only — no broken `src/` left behind.

## Leverage building

When a tough nut cracks, the *recipe* is often higher leverage than the
function itself. Codify recurring patterns in `decomp/NOTES.md`. If a
trick generalizes across ≥2 functions, lift it into saved memory so
future sessions inherit it.

## Wrap-up (only when stopping for cap or user prompt)

When the cap is imminent or the user has told you to stop:

- Keep the working tree clean — revert any half-finished `src/` files
  rather than committing broken state.
- ELF SHA-1 must match at session end (`make` exits 0). If it doesn't,
  revert the last edit until it does.
- `git status` empty before the last commit lands.
- Do **not** emit an "iteration results" or "session summary" — the
  commit log is the record. See "Do not stop matching" above.

## If running unattended

(This section is the seam from which a future `decomp/HEADLESS.md` will
be split off. Skip if running interactively.)

- No `/loop`, no `ScheduleWakeup`, no user Q&A.
- Per-iteration commit cadence: one commit per matched function or per
  parked tough-nut.
- Stop condition: <15 min of usage budget left, or three consecutive
  iterations with no matches and no progress on tough nuts.
- Append a one-line entry to `decomp/RUN_LOG.md` (gitignored) per
  outcome: ISO-8601-Z timestamp, target, matched / deferred, commit
  SHA, one-liner.
