# Rodata-matching roadmap

Status as of 2026-05-12: `.rodata` at **7.47%** (67,665 / 905,640 bytes), `.data` at **0.00%**. Phase 1–5 tooling for typed rodata is in place; the bonus push to bulk-promote auto-typed pointer tables hit two bugs that are documented below as the next open problems to tackle.

This doc is **how to push further**, not a re-explanation of the current pipeline (see `decomp/MATCH_DATA.md` for that).

---

## What works today (verified, byte-clean)

| Tool | Purpose | Status |
|---|---|---|
| `tools/migrate_data_per_tu.py` | Auto-emit per-TU `_data.c` sidecars. `void *[]` shape gated by ≥25% pointer-density to avoid mis-typing string blobs; falls back to `unsigned int[]` then byte array | **Density-gated form is currently uncommitted in working tree** — see "Open #0" |
| `tools/quick_data_diff.py --all` | Compile + reloc-patch + byte-diff against `baseelf.elf` without a full link. R_MIPS_32 relocations resolved via `build/ico.us.map` | 91 files / 4648 symbols MATCH after density gate |
| `tools/dump_struct_accesses.py D_<VMA>` | Survey consumer-side load/store offsets, widths, FPU vs int, and stride. Foundation for hand-typed designated-init struct arrays | Works; tested on D_0055486C (single-word pointer table) |
| `tools/decode_sjis.py D_<VMA>` | Decode SJIS / EUC-JP. ICO uses EUC-JP (the tool tries both and picks the cleaner decode). Emits `JTEXT("\xNN...")` literal | Works; tested on D_00554C90 / D_00554CB8 |
| `tools/stub_rodata_inline.py D_<VMA>` | Move opaque bytes to `asm/rodata/<TU>/<sym>.s`, `INCLUDE_RODATA` reference inside the tracked source, strip the entry from `_data.c` | Works; tested on D_00614AA0 (56-byte debug chunk) |
| `JTEXT(s)` macro | `include/common.h` identity marker for Japanese hex-escape strings | Defined |
| `INCLUDE_RODATA(folder, name)` macro | `include/include_asm.h` — pre-existing | Defined |
| Memory: `monitor_long_builds`, updated `quick_data_diff` | Operational guidance for future sessions | Saved |

The full plan (`/primary/home/n/.claude/plans/glistening-sparking-ocean.md`) describes how these landed and what they replace.

---

## Open problems blocking further auto-promotion

### Open #0 — Commit-or-revert the density-gate tweak to `migrate_data_per_tu.py`

The density gate (require ≥25% of words in a block to resolve to known symbols before emitting `void *[]`, else fall through to `unsigned int[]`) lives in the working tree only — diff vs HEAD covers ~30 lines around `_emit_chunked`.

**Why it matters:** without the gate, the migrator mis-typed string-fragment blocks (e.g. `"camdata/cam0135.gcm"` split across 4-byte words where one fragment coincidentally matched a symbol's VMA) as pointer tables, producing 49 byte-divergent sidecar sections.

**Action:** review the diff, decide. If kept, commit alongside this doc.

### Open #1 — `_resolve_word_as_pointer` silently returns None for valid VMAs

`tools/dump_struct_accesses.py D_004B3140` shows the symbol's words include `0x00615A68`, `0x001A7270`, `0x00615A58`, `0x001A7BB0`, etc. These are all in the loaded VMA range (`0x00100000`–`0x00700000`) and follow the `D_*` / `func_*` naming convention — they should resolve.

The migrator's emit for D_004B3140 currently uses `unsigned int[78]` form, meaning every `_resolve_word_as_pointer` call returned None. The density gate then correctly skipped the `void *[]` path because zero words resolved.

**Hypothesis:** `mapfile_parser`'s `findSymbolByVramOrVrom` may need the linker map regenerated post-rewrite, or it's range-matching to a parent section instead of returning the exact symbol. The check `if sym.vram != w: return None` filters mid-symbol hits — too aggressive if the parser reports VMAs at section starts, not symbol starts.

**Action:** test in isolation:
```python
from mapfile_parser import mapfile
mf = mapfile.MapFile.newFromMapFile('build/ico.us.map')
print(mf.findSymbolByVramOrVrom(0x001A7270))  # should return func_001A7270
print(mf.findSymbolByVramOrVrom(0x00615A68))  # should return D_00615A68
```
If `.vram` is the parent section's start rather than the symbol's, swap the filter to use `sym.name` parsing for the VMA suffix.

### Open #2 — gp_rel relocation truncation when promoting pointer tables

Symptom (from the 2026-05-12 attempt):
```
build/asm/cod/011948.o: in function `func_00113C98':
(.text+0x23a0): relocation truncated to fit: R_MIPS_GPREL16 against `D_006337AB'
```

The asm-side `%gp_rel(D_006337AB)` reference comes from splat's disassembly, unchanged across the promotion attempt. The truncation indicates the linker placed D_006337AB outside the ±32 KB gp window, breaking the small-data relocation.

**Hypothesis:** when the typed extern decl `extern char D_006337AB[];` is added to a file that previously had no decl, ee-gcc may emit the symbol with a section attribute that conflicts with the SORT_BY_NAME placement, causing the linker to drop D_006337AB out of `.sdata`. Or: the `void *D_X[N]` def in a sister .c is being placed in a `.data.0xVMA` section but the symbol is being resolved from a different VMA elsewhere.

**Action:**
1. After a successful promotion of a single small symbol, dump the symbol table from the linker map and confirm D_006337AB's final VMA equals 0x006337AB.
2. If it shifted, trace which input file is emitting it at the wrong VMA and adjust the extern's section attribute (or fix the type to match the original decl).
3. The original decl is `extern int D_006337AB;` (scalar) in some `src/cod/*.c` — promoting a sister file's `void *[]` def that references this symbol might be the issue. Don't promote pointer tables that reference scalar small-data syms until this is resolved.

### Open #3 — `add_externs.py` is in `/tmp`, not committed

The helper I wrote for promoting pointer tables (which auto-adds `extern <type> D_X[];` decls for every locally-defined and referenced symbol) only lives at `/tmp/add_externs.py` and `/tmp/promote_ptr_tables.py`. If anyone wants to retry the promotion, they're starting from scratch.

**Action:** once Open #1 and #2 are resolved, port these scripts to `tools/` with:
- Marker-gated extern injection (only touch files containing `/* Pointer tables migrated from */`)
- Type-aware extern shape (`extern T D_X[];` for arrays, `extern T D_X;` for scalars — matches the local def's `[` vs `=` form)
- A `--dry-run` mode that lists planned changes before writing

---

## Specific symbols ready to promote (waiting on Opens #1, #2)

Once the resolver is fixed and gp_rel truncation diagnosed, the density-gated migrator already emits ~13 `void *[]` defs and ~438 `unsigned int[]` defs across the `_data.c` sidecars. Targets sorted by likely safety:

| Class | Count | Promotion strategy |
|---|---|---|
| `void *D_X[N]` with ≥80% pointer density | ~9 | Bulk-promote with extern decls. Each block is genuinely a pointer table the consumer indexes by element. |
| `void *D_X[N]` with 25–80% density | ~4 | Promote one at a time, manually verify the non-pointer words make sense (small ints, flags, sizes). |
| `unsigned int D_X[N]` (no pointer resolution) | ~438 | **Do not bulk-promote.** Each needs `tools/dump_struct_accesses.py` to determine if it's an int array, a packed struct array, or a misclassified string blob. Type as designated-init structs per `decomp/MATCH_DATA.md`. |
| SJIS strings (high-bit bytes, byte-array shape) | ~50–100 | Promote one at a time via `tools/decode_sjis.py`. ICO uses EUC-JP — the tool detects automatically. Wrap in `JTEXT("...")`. |
| Opaque chunks (no clear shape) | rest | Defer via `tools/stub_rodata_inline.py` (moves to `asm/rodata/<TU>/<sym>.s` with `INCLUDE_RODATA` reference). Doesn't move progress, but pins to TU. |

Avoid promoting:
- Any block where the consumer-side asm shows `%gp_rel(D_X)` — small-data symbols are entangled with gp window placement (Open #2).
- Blocks larger than ~2 KB whose density is 25–50% — high risk of mis-typed entries that compile but link to wrong VMAs.
- Anything in `_unassigned_data.c` — those symbols have wrong TU assignments (proximity-voted, not vote-counted).

---

## Bigger-picture improvements

These are not blocking but would multiply the leverage of the current tooling:

1. **Auto-promotion of dense pointer tables.** Once Open #1 is fixed, a script that promotes only `void *[]` defs with ≥80% density should be safe to run unattended. Combine with marker-gated extern injection (Open #3).

2. **Struct-shape inference from `dump_struct_accesses` output.** The current tool reports `(offset, width, family)` histograms. Adding a struct-emitter that proposes `typedef struct { ... } D_X_Entry;` from those histograms — with the developer reviewing — would turn the WORD_OTHER bucket (326 KB / 438 defs) into the next big win.

3. **Pre-rebuild reloc check.** `tools/quick_data_diff.py` now patches R_MIPS_32. Extending it to also flag `R_MIPS_GPREL16` truncations (without doing the full link) would catch Open #2 in the inner loop instead of at `ninja` time.

4. **Promote SJIS strings.** The `decode_sjis.py` tool exists; needs a batch wrapper that scans every `_data.c` for high-bit byte arrays, runs the decoder, and emits a candidate JTEXT line for the developer to confirm. Many tens of small wins (~20–50 bytes each).

5. **Update `decode_sjis.py` to write directly.** Currently the developer copy-pastes the literal. A `--write` mode that strips the `_data.c` entry and appends `const char D_X[N] = JTEXT(...)` to the sister .c would parallelize a tedious manual step.

6. **Auto-coalesce `_pad_<VMA>` continuations into the parent symbol.** The migrator currently emits synthetic `_pad_VMA` symbols for misaligned VMAs. The pointer-resolution path already coalesces these into the parent's array, but the byte-array path doesn't. Doing so would shrink `_data.c` files significantly and make hand-promotion easier.

---

## Verification protocol for any future work

Before claiming a `.rodata` win:

1. `tools/build.sh setup` to regenerate sidecars (always — never trust stale `_data.c`).
2. `tools/quick_data_diff.py --all` — confirm 0 MISMATCH against current state.
3. Apply changes.
4. `tools/quick_data_diff.py --all` again — confirm still 0 MISMATCH.
5. `ninja` — confirm full rebuild succeeds (this is where Open #2 will surface).
6. `tools/verify_elf.py --target build/ico.elf` — confirm SHA-1 matches `fbf50c75cd5911273511c4f9af90503ff8423582`.
7. `tools/progress.py` — record before/after delta.

**Never skip step 5.** quick_data_diff is necessary but not sufficient — only a full link catches relocation/section-placement issues.

For `Monitor` usage on the full-setup pipeline, use a **30-minute minimum timeout** (memory: `monitor_long_builds`). Splat-regen runs ~6–10 min, the full ninja link ~4 min.
