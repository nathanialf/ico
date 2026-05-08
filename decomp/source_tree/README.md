# `decomp/source_tree/` — original ICO source-tree skeleton

Empty placeholders mirroring the *original* directory layout of
ICO's source as recovered from `__FILE__` strings in
`baserom/baseelf.elf` `.rodata`. **Build does not touch this**;
it is a planning / reference artifact.

**96 file(s) across 5 director(ies):**

- `include/` — 2 file(s) — Public headers shared across the tree.
- `ios/` — 7 file(s) — I/O system — wrappers around SCE SDK libs (cdvd, pad, mc, sif).
- `isys/` — 2 file(s) — Interactive system — GObj per-frame game-object framework.
- `sound/` — 2 file(s) — EE-side sound init / ADPCM. IOP-side audio lives in another ELF.
- `src/` — 83 file(s) — Game code — actor logic, render pipeline, scene/file management.

## Why this exists

Each `.c`/`.h` here is a one-line placeholder recording the rodata
vma of its `__FILE__` literal. That vma is the *anchor* for
tying matched `.text` functions back to their original TU: any
function that loads the anchor address (via `lui+addiu` or
`%gp_rel`) belongs to this TU.

When we begin grouping `cod/<offset>` subsegments into per-TU
buckets, this directory is the target layout. Until then, it
serves as a checklist of TUs and a record of recovery state.

## Regenerating

```sh
.venv/bin/python tools/build_source_tree.py
```

Idempotent. New paths that surface in `.rodata` (e.g. after a
future SDK change or additional inspection) will appear as new
placeholders. Hand-edits to placeholders or READMEs are
overwritten — extend `tools/build_source_tree.py` itself to
change blurbs or subsystem groupings.

## Caveats

- TUs without any `assert()` produce no `__FILE__` literal and
  do not appear here. Such TUs surface only as gaps between
  identified TUs in `.text` ordering.
- Inlined functions assert with the *inliner's* `__FILE__`, so
  helpers that got inlined into a different TU will be tagged
  to the inliner. Usually fine.
- A few `<file>.c.inc` entries are inline-included fragments
  rather than standalone TUs — see `../source_tree.md`.
