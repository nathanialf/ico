# tools/ index

One line per tool, and every tool in the directory is listed. Everything here
works on the branch's target as reported by `tools/ico_version.py` (`main` =
PAL retail).

The sweep harness, the loop drivers (`match_drive.py`, `match_loop.py`,
`decomp_chain.py`), the permuter wrappers, the shape classifiers and the
one-off analysis scripts were deleted: this branch runs the loop by hand
against `quick_diff.sh` and `match_diff.py`. Per-function compiler flags and
per-func `.s` postprocess allowlists are a retired, banned matching lever, see
CLAUDE.md "Crutches are BANNED" before reintroducing that shape of tool.

## Build + gate chain

| tool | what it does |
|---|---|
| `setup.sh` | idempotent bootstrap: venv, submodules, EE toolchain, ghidra, git hooks |
| `install_hooks.sh` | installs the pre-commit and pre-push hooks (`ninja` SHA-1 gate + `check_no_rom.sh`) |
| `extract_elf.sh` / `extract_elf.py` | disc → `baserom/<ver>/baseelf.{elf,rom}` + SHA-1 check + reference maps |
| `ico_version.py` / `ico_version.sh` | the single source of truth for the branch's target slug and paths |
| `build.sh` | `setup` (verify ELF, run splat, emit build.ninja) / `progress` (rewrite tables) |
| `patch_splat.py` | applies this repo's local splat patches |
| `gen_ninja.py` | generates `build.ninja` from `config/ico.<ver>.d`; auto-regens on input change |
| `compile_c.sh` | THE C compile rule: ee-gcc 2.9-991111 + the period ee-as, plus always-on ROM parity |
| `preprocess_old_as.py` | flattens INCLUDE_ASM siblings + translates `%gp_rel` for the period assembler |
| `postprocess_split_jtbls.py` | puts each gcc switch jtbl on its own `.rodata.0x<VMA>` so the linker can place it |
| `assemble_vu0.py` | `.vutext` assembler for the five hand-typed `ico2/*.S` microprograms |
| `verify_elf.py` | the gate: SHA-1 of `build/ico.rom` against `config/sha1sums.txt` |
| `check_no_rom.sh` | IP guard: refuses disc data / extracted assets in the tree |
| `format.sh` / `format_layout.py` | clang-format every tracked `.c` (whitespace only; the SHA gate proves it never changes the ROM) |
| `progress.py` / `progress_tree.py` | regenerate README.md / `docs/PROGRESS.md` / `docs/progress.json` |
| `requirements.txt` | the venv's pinned Python dependencies |

## Matching loop

| tool | what it does |
|---|---|
| `quick_diff.sh` | ~100 ms compile+diff inner loop; agrees with the ninja build by construction |
| `match_diff.py` | reloc-normalized diff + `real_count`, the authoritative per-function score |
| `mask_gp_rel.py` | reloc-normalizes `$gp`-relative operands so diffs aren't noise (called by `quick_diff.sh`) |
| `tag_diff.py` | per-tag breakdown of a diff (called by `quick_diff.sh` and `match_diff.py`) |
| `tu_check.py` | re-diffs EVERY matched function in a TU so an edit can't silently break a sibling |

The 30-iteration stall gate is kept by hand: 30 consecutive distinct
hypotheses with no `real_count` improvement, any improvement resetting the
count. There is no driver that tracks it for you.

## Data carving

| tool | what it does |
|---|---|
| `find_carves.py` | proposes carvable data runs and reports what blocks each one |
| `map_data_tus.py` | assigns data symbols to owning TUs |
| `emit_run_defs.py` | byte-verified C definitions for a carved run's standalone symbols |

## PAL generators (`main` only)

| tool | what it does |
|---|---|
| `gen_pal_symbol_addrs.py` | correlates the disc's `SRCFILE.TXT` listing to the shipped ELF → `config/symbol_addrs.pal.txt` + per-TU `.text` spans |
| `gen_pal_data_symbols.py` | names data symbols from the disc's `MAIN.MAP` → `config/symbol_addrs.pal.data.txt` |
| `gen_pal_source_tree.py` | writes the local-only `docs/pal_source_tree.{md,json}` census |
| `easy_pickups.py` | ranks the cheapest remaining unmatched functions (`docs/easy_pickups.md`) |
| `dump_all_struct_shapes.py` | mines every function `.s` for (offset, width, sign, stride) per symbol → `docs/struct_shapes.{json,md}` |

## Tests

| tool | what it does |
|---|---|
| `test_match_diff.py` | unit tests for `match_diff.py` |
| `test_assemble_vu0.py` | unit tests for `assemble_vu0.py` |
