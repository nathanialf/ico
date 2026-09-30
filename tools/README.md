# tools/ index

One line per tool; every tool in the directory is listed. Every tool works on
the branch's target as reported by `tools/ico_version.py` (`main` = PAL
retail).

The sweep harness, the loop drivers (`match_drive.py`, `match_loop.py`,
`decomp_chain.py`), the permuter wrappers, the shape classifiers and the
one-off analysis scripts were deleted. This branch runs the loop by hand
against `quick_diff.sh` and `match_diff.py`. Per-function compiler flags and
per-func `.s` postprocess allowlists are a retired, banned matching lever;
read CLAUDE.md "Crutches are BANNED" before reintroducing a tool of that
shape.

## Build + gate chain

| tool | what it does |
|---|---|
| `setup.sh` | idempotent bootstrap: venv, submodules, EE toolchain, ghidra, git hooks; builds the plain build's ld 2.10 and dvp-as from public source under `tools/cc/` |
| `binutils-2.10-ee.patch` | the R5900 machine and DVP overlay section types for GNU ld 2.10, backported from ps2dev's binutils-2.14-PS2.patch; applied by `setup.sh` |
| `binutils-2.10-dvp-ld.patch` | the Cygnus "sky" ld's DVP rule for GNU ld 2.10: each `.DVP.overlay.*` orphan gets its own output section at address 0 (from the GPL ee-gcc 2.9-991111 combined tree's `ld/emultempl/elf32.em`); applied by `setup.sh` after the first |
| `install_hooks.sh` | installs the pre-commit and pre-push hooks (`ninja` SHA-1 gate + `check_no_rom.sh`) |
| `extract_elf.sh` / `extract_elf.py` | disc -> `baserom/<ver>/baseelf.{elf,rom}` + SHA-1 check + reference maps |
| `ico_version.py` / `ico_version.sh` | the single source of truth for the branch's target slug and paths |
| `build.sh` | `setup` (verify ELF, assemble `ico2/vusrc/*.dsm` with dvp-as into the `ico2/*.s` splat's hasm rows read, run splat, emit build.ninja) / `progress` (rewrite tables) |
| `patch_splat.py` | applies this repo's local splat patches |
| `gen_ninja.py` | generates `build.ninja` from `config/ico.<ver>.d`; auto-regens on input change |
| `gen_ninja_plain.py` | generates `build.plain.ninja` from `config/link_order.pal.txt` + `config/link.pal.ld` (the build without splat's `.d`/`.ld`, objects under `build/plain/`); links with ld 2.10 (elf32-littlemips) and assembles `ico2/vusrc/*.dsm` with dvp-as; replaces `gen_ninja.py` at the cut-over |
| `compile_c.sh` | THE C compile rule: ee-gcc 2.9-991111 + the period ee-as, plus always-on ROM parity |
| `preprocess_old_as.py` | flattens INCLUDE_ASM siblings + translates `%gp_rel` for the period assembler |
| `postprocess_split_jtbls.py` | puts each gcc switch jtbl on its own `.rodata.0x<VMA>` so the linker can place it |
| `verify_elf.py` | SHA-1 of the base ROM against `config/sha1sums.txt` (`build.sh setup`) |
| `check_elf.py` | the gate (`--gate`: every allocated section against the base ELF by address + the ROM SHA-1, the ninja verify step) and the progress tables (`--progress`: README.md / `docs/PROGRESS.md` / `docs/progress.json`) |
| `check_no_rom.sh` | IP guard: refuses disc data / extracted assets in the tree |
| `format.sh` / `format_layout.py` | clang-format every tracked `.c` (whitespace only; the SHA gate proves it never changes the ROM) |
| `requirements.txt` | the venv's pinned Python dependencies |

## Matching loop

| tool | what it does |
|---|---|
| `strict_cmp.py` | word-for-word comparison of one function against its ROM stub after `quick_diff.sh`, the harvest gate beside `ninja` |
| `quick_diff.sh` | ~100 ms compile+diff inner loop; agrees with the ninja build by construction |
| `match_diff.py` | reloc-normalized diff + `real_count`, the authoritative per-function score |
| `mask_gp_rel.py` | reloc-normalizes `$gp`-relative operands so diffs aren't noise (called by `quick_diff.sh`) |
| `tu_check.py` | re-diffs EVERY matched function in a TU so an edit can't silently break a sibling |

There is no stall gate and no iteration budget: a function stays with its
chain until it is byte-identical, and a pass that ends before that records
the function's exact state for the next pass.

## Data carving

| tool | what it does |
|---|---|
| `map_data_tus.py` | assigns data symbols to owning TUs |

## PAL generators (`main` only)

| tool | what it does |
|---|---|
| `gen_pal_symbol_addrs.py` | correlates the disc's `SRCFILE.TXT` listing to the shipped ELF -> `config/symbol_addrs.pal.txt` + per-TU `.text` spans |
| `gen_pal_data_symbols.py` | names data symbols from the disc's `MAIN.MAP` -> `config/symbol_addrs.pal.data.txt` |
| `gen_pal_source_tree.py` | writes the local-only `docs/pal_source_tree.{md,json}` census |

## Tests

| tool | what it does |
|---|---|
| `test_match_diff.py` | unit tests for `match_diff.py` |
