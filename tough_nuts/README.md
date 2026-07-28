# tough_nuts/ — known-unmatchable functions, with seed C

Each subdirectory `tough_nuts/<func_NAME>/` is **one parked function**:
a function we believe is unmatchable with the current toolchain, with:

- A best-effort seed `<func_NAME>.c` (operator-readable, faithful to
  the original asm — no clever transforms).
- A `notes.md` describing the failure mode (e.g. la-macro 64-bit
  expansion, daddu-vs-or, no-TCO sibling-call, ret-1+sdata regalloc).

This directory is the **single source of truth** for parked functions.
It's used by:

1. `tools/find_leaves.py --exclude-parked` — drops every name in
   `tough_nuts/*/` from the candidate list so the same dead-end
   functions stop coming back in routine queries.
2. `tools/auto_permute.sh` — iterates `tough_nuts/*/` and runs the
   decomp-permuter against each seed, promoting improved candidates
   back into the seed file across passes.
3. `tools/self-monitor.sh` — surfaces the best permuter score per
   parked function in the dashboard.

## Adding a new parked function

1. Create `tough_nuts/<func_NAME>/`.
2. Drop in a `<func_NAME>.c` seed — operator's honest best guess at
   what would compile to the right shape if the compiler weren't
   misbehaving. Don't over-engineer; permuter handles regalloc /
   scheduling tweaks.
3. Write `notes.md` describing the failure mode. Reference the failure
   pattern (often a sibling already documented) and cite original asm.
4. Commit with a message like `Park <func> — <one-line reason>`.

## Re-evaluating

Re-check periodically as compiler identification firms up (see
`decomp/NOTES.md` "Compiler fingerprint" section). Most current
parked functions are gated on the la-macro 64-bit / daddu-vs-or /
no-TCO / regalloc questions, which all point at "compiler isn't
ee-gcc 2.96."

If a parked function later matches by hand (or via the permuter),
remove the directory and let `tools/claim.py` promote into
`src/cod/<file_off>.c`.

## Seed filename conventions

`tools/permute_run.sh` will discover seeds in this order under
`tough_nuts/<func>/`:

1. `<func>.c` (e.g. `func_00105278.c`) — preferred new convention.
2. `<file_off_HEX>.c` / `<file_off_lower>.c` (e.g. `005278.c`) —
   legacy convention, still supported.
3. First `*.c` found in the directory (fallback).

Use `<func>.c`. It's unambiguous and matches the directory name.
