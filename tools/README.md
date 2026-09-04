# tools/ — index

One line per tool. Everything here works on the branch's target as reported by
`tools/ico_version.py` (`main` = PAL retail). Anything that only made sense for a
retired campaign (USA/aug6 port drivers, per-function compiler flags, per-func `.s`
postprocess allowlists, asset decoders) has been deleted — see CLAUDE.md
"Crutches are BANNED" before reintroducing that shape of tool.

## Build + gate chain

| tool | what it does |
|---|---|
| `setup.sh` | idempotent bootstrap: venv, submodules, EE toolchain, ghidra, git hooks |
| `install_hooks.sh` | installs the pre-commit hook (`ninja` SHA-1 gate + `check_no_rom.sh`) |
| `extract_elf.sh` / `extract_elf.py` | disc → `baserom/<ver>/baseelf.{elf,rom}` + SHA-1 check + reference maps |
| `ico_version.py` / `ico_version.sh` | the single source of truth for the branch's target slug and paths |
| `build.sh` | `setup` (verify ELF, run splat, emit build.ninja) / `progress` (rewrite tables) |
| `patch_splat.py` | applies this repo's local splat patches (see the `splat_local_patches` notes) |
| `gen_ninja.py` | generates `build.ninja` from `config/ico.<ver>.d`; auto-regens on input change |
| `compile_c.sh` | THE C compile rule: ee-gcc 2.9-991111 + the period ee-as, plus always-on ROM parity |
| `preprocess_old_as.py` | flattens INCLUDE_ASM siblings + translates `%gp_rel` for the period assembler |
| `postprocess_split_jtbls.py` | puts each gcc switch jtbl on its own `.rodata.0x<VMA>` so the linker can place it |
| `mask_gp_rel.py` | reloc-normalizes `$gp`-relative operands so diffs aren't noise |
| `verify_elf.py` | the gate: SHA-1 of `build/ico.rom` against `config/sha1sums.txt` |
| `data_diff.py` | per-symbol data comparison against the base ELF (reccmp-style) |
| `check_no_rom.sh` | IP guard: refuses disc data / extracted assets in the tree |
| `self-monitor.sh` | background tick: progress tables, sweep targets |
| `progress.py` / `progress_tree.py` | regenerate README.md / `docs/PROGRESS.md` / `docs/index.html` tables |
| `assemble_vu0.py` / `disasm_vu0.py` | `.vutext` assembler/disassembler for the hand-typed `src/*.S` microprograms |

## Matching loop (`decomp-match`, `decomp-sweep`, `decomp-convergence` skills)

| tool | what it does |
|---|---|
| `match_drive.py` | the DRIVER that owns the single-function loop; invokes you only at verdict `iterate` |
| `match_loop.py` | per-function state: stall counter, novelty gate, commit, park, clone |
| `match_diff.py` | reloc-normalized diff + `real_count` — the authoritative per-function score |
| `quick_diff.sh` | ~100 ms compile+diff inner loop; agrees with the ninja build by construction |
| `classify_asm.py` | tags an asm shape and names the cookbook recipe / lever to try |
| `lever.py` | applies and scores a named source-shape lever |
| `tag_diff.py` | per-tag breakdown of a diff |
| `first_diff.py` | locates the first diverging instruction |
| `sched_diff.py` | gcc pass dumps (sched1/sched2/dbr) sliced per function — scheduling diagnosis |
| `stack_diff.py` | stack-slot assignment comparison (reccmp-style) |
| `tu_check.py` | re-diffs EVERY matched function in a TU so an edit can't silently break a sibling |
| `_asmsig.py` | reloc/immediate-masked instruction signatures, shared by the clone/family tools |
| `templatize.py` | finds FAMILIES of same-shape functions — where one crack propagates furthest |
| `m2c_scaffold.py` | m2c asm→C scaffolding for a fresh function |
| `lookup_vma.py` | resolve a hex VMA to a symbol name + owning TU |
| `park_tu.py` | park a function out of a coalesced TU into `tough_nuts/` |
| `permute_run.sh` | bounded decomp-permuter run at a genuine stall=30 |
| `gen_permuter_settings.py` | regenerates the gitignored root `permuter_settings.toml` |
| `decomp_chain.py` / `loop_stop.sh` | chain/stop control for the unsupervised match loop |
| `sweep_targets.sh` / `sweep.py` / `sweep_try.sh` / `sweep_park.sh` / `sweep_stop.sh` | the breadth-first single-pass sweep harness |
| `test_match_diff.py` / `test_stack_diff.py` / `test_data_diff.py` / `test_assemble_vu0.py` | unit tests for the above |

## Data carving

| tool | what it does |
|---|---|
| `find_carves.py` | proposes carvable data runs and reports what blocks each one |
| `map_data_tus.py` | assigns data symbols to owning TUs |
| `emit_run_defs.py` | byte-verified C definitions for a carved run's standalone symbols |
| `decode_sjis.py` | decodes Shift-JIS / EUC-JP byte runs so carved strings keep their comments |
| `tu_status.py` | per-TU completion across `.text`/`.data`/`.rodata`/`.lit4`/`.sdata` |

## PAL generators (`main` only)

| tool | what it does |
|---|---|
| `gen_pal_symbol_addrs.py` | correlates the disc's `SRCFILE.TXT` listing to the shipped ELF → `config/symbol_addrs.pal.txt` + per-TU `.text` spans |
| `gen_pal_data_symbols.py` | names data symbols from the disc's `MAIN.MAP` → `config/symbol_addrs.pal.data.txt` |
| `gen_pal_source_tree.py` | writes the local-only `decomp/pal_source_tree.{md,json}` census |
| `easy_pickups.py` | ranks the cheapest remaining unmatched functions (`decomp/easy_pickups.md`) |

## Struct / type recovery

| tool | what it does |
|---|---|
| `dump_all_struct_shapes.py` | mines every function `.s` for (offset, width, sign, stride) per symbol → `decomp/struct_shapes.{json,md}` |
| `type_entity.py` | verified bulk rewrite of `*(T*)(self + 0x15C)` idioms to `GObj`/`Sub15C` members, reverting any file that stops matching |
