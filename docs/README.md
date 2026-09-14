# `docs/`: what each document is for

An index, not a summary. Every file is listed once, with what it is for and
whether it is **tracked** (in git), **local-only** (gitignored; on this machine
the same physical file is shared by the `main` / `ntsc` / `aug6` worktrees, so
an edit here changes it on every branch) or **generated** (rewritten by a tool,
never hand-edit).

This is the project's one documentation directory. The former `decomp/` was
folded into it; a `decomp/…` path in an older commit message or note means the
same file here.

`main` targets PAL retail (SCES-50760). See `CLAUDE.md` for the three-branch
layout and the matching rules; `tools/README.md` for the tools themselves.

## Where to look for X

| I want to… | Read |
|---|---|
| match a function, find the C for an asm shape | `docs/COOKBOOK.md` (shape→recipe, §1–13) |
| understand *why* the compiler/assembler/linker does something | `docs/NOTES.md` |
| match a hard / plateaued function (whole-function convergence) | `COOKBOOK.md` §13 + the `decomp-convergence` skill |
| know what was already tried on a specific function | `docs/MATCHING_NOTES.md` |
| pick the next target | `docs/easy_pickups.md` (regenerate: `tools/easy_pickups.py`) |
| carve typed data out of an asm blob | `docs/carve_ledger.md` (rules first, PAL phase at the end) |
| find a function's real name / its TU / its source order | `config/symbol_addrs.pal.txt`, `docs/pal_source_tree.md` (generators: `tools/gen_pal_symbol_addrs.py`, `tools/gen_pal_source_tree.py`) |
| know why a ported body was reverted | `docs/port_ledger_pal.md`, `docs/port_ledger_pal_aug6.md` |
| work on a developer header | `docs/HEADERS.md`, `docs/mv_defs_h.md` |
| touch `.vutext` / the VU1 microprograms | `docs/MATCH_VU.md` |
| know what may and may not be used as an input | `docs/LEGAL.md` |
| build from a clean clone | `docs/BUILDING.md` |
| find a technique that used to be documented and is gone | `docs/ARCHIVE_retired_notes.md` |

## Every file here

| file | status | what it is |
|---|---|---|
| `README.md` | tracked | this index |
| `COOKBOOK.md` | local-only | the shape→C-recipe lookup, sectioned §1–13. Canonical home for recipes; auto-memories cite its section numbers, so numbering is stable |
| `NOTES.md` | local-only | the catalog of *mechanisms*: EE/R5900, ee-gcc, ee-as, splat and linker quirks. Canonical home for "why" |
| `ARCHIVE_retired_notes.md` | local-only | everything removed from the working docs in the 2026-09-04 audit, verbatim, each with the reason. Reference only. Do not copy back without re-deriving |
| `MATCH_VU.md` | local-only | `.vutext`: the five hand-typed VU1 microprograms, their DVP labels from the PAL listing, and `tools/assemble_vu0.py` |
| `HEADERS.md` | tracked | the developer headers reconstructed into the per-programmer `ico2/<prog>/include/` trees: naming rule, hosts, and the inlining check |
| `mv_defs_h.md` | tracked | recovery record for `ico2/ito/include/mv_defs.h` (aug6-era names; the header itself is now real) |
| `PROGRAMMERS.md` | tracked | per-programmer source dirs → subsystem and per-author idioms. Use it for idioms; the PAL listing supplies boundaries |
| `VENDOR.md` | tracked | vendor-code policy: what counts as vendor, the legal split, how the dashboard accounts for it. Policy is binding; the USA-era numbers are marked as such |
| `carve_ledger.md` | tracked | data-carve RULES (alignment floor, one run per TU+section, blockers, the full-run model) + this branch's landed carves |
| `port_ledger_pal.md` | tracked | ntsc→pal port accounting: what landed, what reverted and why |
| `port_ledger_pal_aug6.md` | tracked | aug6→pal port accounting, same shape |
| `easy_pickups.md` | **generated** | the queue: near-miss ports and smallest unmatched functions (`tools/easy_pickups.py`) |
| `pal_source_tree.{md,json}` | **generated**, local-only | PAL functions per file in source order, `#include`-coalesced TUs, header inline helpers (`tools/gen_pal_source_tree.py`) |
| `struct_shapes.{md,json}` | generated (`.json` tracked) | recovered per-object struct shapes, regenerated per target (`tools/dump_all_struct_shapes.py`) |
| `header_candidates.md`, `multi_tu_slices.md` | local-only | working notes from the header / TU-slice investigations |
| `LEGAL.md` | local-only | **read before contributing.** What may be in the repo, what may never be, and the symbol-map decisions for each target |
| `BUILDING.md` | local-only | clean-clone walkthrough: setup, disc, extract, `tools/build.sh setup`, `ninja` |
| `MATCHING_NOTES.md` | local-only | per-function deferred targets: what was tried, the residual, the untried hypothesis. USA/aug6-era provenance is flagged in its header |
| `PROGRESS.md` | **generated** | per-section progress table (`tools/build.sh progress`) |
| `index.html`, `progress.json` | **generated** | the progress dashboard (`tools/progress_tree.py`) |

`index.html`, `progress.json` and `PROGRESS.md` are the only files GitHub Pages
publishes; `.github/scripts/build_pages_site.sh` names that set in `SITE_FILES`.
Everything else here is working documentation and stays unpublished.

## Rules of the road for these docs

- **Mechanisms → `NOTES.md`. Recipes → `COOKBOOK.md`. Per-function residue →
  `MATCHING_NOTES.md`.** If a note is in the wrong file it will not be found.
- **Never document a crutch.** CLAUDE.md's ban covers anything that emits no
  bytes and exists to steer codegen. If a technique is banned, the mechanism may
  stay; the recipe goes.
- **A `func_00XXXXXX` is a per-target VMA.** It means nothing on another branch.
  Names from `config/symbol_addrs.pal.txt` travel; addresses do not.
- **Do not hand-edit a generated file.** Fix the generator.
