# Matching prompt — ico (PS2)

Reuse this verbatim (paste it as the first message of a fresh Claude Code
session) to launch a matching work session on this repo.

---

Continue the **ICO** clean-room decomp at `/primary/dev/ico`. Working
directive: match as many ELF functions as possible, plug away at the
percentage. Same clean-room rules as before — no disc data, no extracted
assets, no leaked-source-derived code, no AI co-author trailer on
commits.

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
  `asm/nonmatchings/<func>/`. Skips splat and full-ELF linking — runs
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

## Per-function loop

1. Pick a `[0xADDR, asm]` line in `config/ico.us.yaml`. Prefer small,
   leaf-ish ranges. Look at the `.s` file to gauge complexity.
2. Change the line to `[0xADDR, c, name]`. Re-run `make setup`. Splat
   moves the asm to `asm/nonmatchings/name/<func>.s` (this subtree IS
   tracked) and expects `src/name.c`.
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

1. Revert the yaml line to `[0xADDR, asm]`. Run `make setup` to confirm
   the tree is clean.
2. Move the best-attempt `src/name.c` to `tough_nuts/<func>/<func>.c`.
3. Write `tough_nuts/<func>/notes.md` with: failure mode, permuter
   plateau score, structural hints from the asm, what's been tried.
4. Add a one-line entry to `docs/MATCHING_NOTES.md`.
5. Commit the parking-doc only — no broken `src/` left behind.

## Leverage building

When a tough nut cracks, the *recipe* is often higher leverage than the
function itself. Codify recurring patterns in `decomp/NOTES.md`. If a
trick generalizes across ≥2 functions, lift it into saved memory so
future sessions inherit it.

## Stop conditions and wrap-up

- Keep the working tree clean.
- ELF SHA-1 must match at session end (`make` exits 0).
- `git status` empty before the last commit lands.
- Do not emit an "iteration results" or "session summary" — the commit
  log is the record.

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
