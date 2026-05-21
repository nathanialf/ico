# Phase 3d — retire `__attribute__((section(".rodata.0xVMA")))` from typed defs

## Empirical finding (2026-05-21)

Partial attr-tag stripping under the current `ico.us.slinky.ld` pipeline
**breaks SHA-1**. Test case: strip the single attr tag from
`src/DmaPacket.c`'s typed def, regen slinky.{yaml,ld}, relink →
`ec37acb909516fcb9b29d5e374e0fc7d8335bec5` (expected
`fbf50c75cd5911273511c4f9af90503ff8423582`).

### Why partial promotion fails

The slinky-generated `.rodata` output section is structured as:

```ld
.rodata : AT(rodata_ROM_START) {
    *(SORT_BY_NAME(.rodata.0x*));         # postprocess-injected catch-all
    build/src/<TU1>.o(.rodata*);          # per-.o glob, declared order
    build/src/<TU2>.o(.rodata*);
    ...
}
```

GNU ld's "first match wins" rule routes every input section to the
first matching output reference:

1. `SORT_BY_NAME(.rodata.0x*)` absorbs every `.rodata.0xVMA` named
   section from every `.o`, sorted by name (= VMA). Today this covers
   every byte of `.rodata` because every typed def is attr-tagged. The
   sorted block lays out contiguously starting at the segment base
   (`0x00553700`) — which happens to match the original VMA layout
   only because the original `.rodata` is gap-free across [0x553700,
   0x631900].
2. The per-`.o` `(.rodata*)` globs follow, claiming any *residual*
   plain `.rodata` content. Today these are empty.

When one TU strips its attr tag, that TU's bytes become plain
`.rodata` and are claimed by its per-`.o` glob. But the loc counter
at that point is past the end of the SORT_BY_NAME block — so the
plain bytes land at VMA ≥ 0x631900, **outside** `.rodata`. SHA breaks
catastrophically (millions of bytes shift).

### What "promotable" means in `data_tu_boundaries.json`

A TU's section is promotable iff its symbols form one contiguous VMA
range with no foreign-TU symbols interleaved. Counts as of
2026-05-21:

| Status | TUs | Bytes |
| --- | ---: | ---: |
| Promotable rodata | 36 | 16 128 |
| Not promotable rodata | 56 | 889 512 |
| **Total rodata in sidecars / typed defs** | **92** | **905 640** |

Even if Phase 3d's pipeline supported partial promotion, only 1.8 % of
`.rodata` bytes could be cleanly attr-stripped today.

## Two ways out

### Option A — all-or-nothing flip

When every rodata TU is promotable AND every typed def is stripped of
attr tags simultaneously, `SORT_BY_NAME(.rodata.0x*)` consumes zero
sections, the per-`.o` globs in VMA-sorted order recreate the original
layout via natural concatenation, and the catch-all retires.

Required work:

1. **Make all 56 non-promotable TUs promotable.** Per-symbol re-voting
   in `tools/build_data_tu_map.py` until every symbol's TU assignment
   is correct. Tools: `tools/identify_tus.py`, manual cross-reference
   from text-side `%hi/%lo` calls. Likely many sessions.
2. **Verify all-or-nothing flip on a test branch.** Strip every attr
   tag, regen slinky, relink, check SHA. Iterate on layout bugs (gaps,
   alignment) until SHA-clean.
3. **Land as one PR.** Partial intermediate states break SHA → cannot
   ship piecemeal.

Pros: clean end-state (no attr tags anywhere). Matches the
parappa2-style per-TU layout natively.

Cons: gigantic single PR; can't ship until *every* TU is sorted out;
TU re-mapping is the bottleneck.

### Option B — per-TU explicit placement

Redesign `ico.us.slinky.ld` so each promoted TU's plain `.rodata`
content has its own explicit-address section, and `SORT_BY_NAME`
covers only unpromoted TUs.

```ld
.rodata 0x00553700 : {
    /* Promoted TU 1: explicit slot */
    . = 0x00558848 - rodata_VRAM;       /* TU's lo_vma */
    KEEP(build/src/queen.o(.rodata*));

    /* Promoted TU 2: explicit slot */
    . = 0x0061AC60 - rodata_VRAM;
    KEEP(build/src/DmaPacket.o(.rodata*));

    /* Catch-all for non-promoted TUs */
    *(SORT_BY_NAME(.rodata.0x*));
}
```

Required work:

1. **Extend `tools/gen_slinky.py`** to read
   `decomp/data_tu_boundaries.json` and emit explicit-address slots
   for `promotable=true` TUs.
2. **Extend `tools/postprocess_slinky_ld.py`** to inject explicit-
   address markers in the output section.
3. **Per-TU strip + verify**: smallest TUs first (DmaPacket 16 B,
   act_bird 16 B, …), SHA-1 verify each.
4. **Iterate on layout edge cases** (alignment of explicit slots,
   gaps between TU ranges, etc.).

Pros: ships piecemeal — each TU is one PR, SHA-verified. Doesn't
block on TU re-mapping.

Cons: more tooling investment up front; output `.ld` is more complex;
hybrid state (some TUs plain, some attr-tagged) persists for a long
time during migration.

## Recommendation

**Option B for the immediate path.** Tooling investment is
~1-2 days, after which per-TU stripping is mechanical. The 36
already-promotable TUs (16 KB) can land within a week. The non-
promotable TUs accumulate as TU re-mapping work progresses, with no
need for a single giant flip.

Option A is the long-term end state (after every TU is promoted, the
explicit-slot scaffolding can retire). But it shouldn't gate
incremental progress.

## Open backlog

- [ ] `gen_slinky.py`: emit explicit-address slots for promotable TUs
      (Option B step 1).
- [ ] `postprocess_slinky_ld.py`: inject explicit-address markers
      (Option B step 2).
- [ ] Switch ninja `-T` to `ico.us.slinky.ld` (currently reverted —
      requires Option B pipeline first).
- [ ] Pilot strip on `src/DmaPacket.c` (smallest test case, 1 sym
      / 16 B). SHA-verify.
- [ ] Roll out across the 36 promotable TUs (16 KB total).
- [ ] TU re-mapping passes (`build_data_tu_map.py` + manual review)
      to promote more TUs into the promotable bucket.

## What this means for the current rodata bytes grind

The 686 KB of un-typed rodata sitting in gitignored sidecars **cannot
land as typed defs without attr tags** until Option B's pipeline is
built. Three options for forward progress in the interim:

1. **Wait on Option B.** Land no new rodata typed defs; resume the
   bytes grind after the pipeline supports plain-form defs.
2. **Land typed defs with attr tags (the current shape).** Bytes
   grind to 100 % attr-tagged. Phase 3d strips ALL attrs in one
   future pass.
3. **Mixed.** ASCII strings + small obvious types land now
   (attr-tagged); deep struct-RE work waits for Option B.

The 47 ASCII string promotions from earlier in this session sit in
the working tree — they're net-new attr-tagged. They're typed
clean-room reconstructions; the only "cost" is that Phase 3d's strip
pass will touch them too.

## Update (2026-05-21, session end)

Phase 3d pipeline now operational; 30 of 36 promotable rodata TUs and
1 sdata TU (DmaPacket) migrated to plain form. SHA-1 stable.
Commits `2760845`..`d20bfde` ship the slot generator, the strip
helper (`tools/strip_attr_phase3d.py`), and 4 strip waves.

### Sidecar-overlap deferred (6 TUs)

`src/pool.c`, `src/camera-editor.c`, `src/boyact.c`, `src/queen.c`,
`src/itou_boss.c` (rodata) and `src/PObj.c` (sdata) all hit the same
structural blocker: their TU's VMA range contains a foreign-`.o`
typed section (a sidecar leftover, or an asm-blanket jtbl like
`jtbl_00553E70`). The per-TU `<o>(.<sec>*)` promoted slot can't
interleave with intermediate foreign typed slots — it pulls bytes
contiguously and overlaps.

### Per-symbol slot experiment (deferred)

Attempted: switch to `-fdata-sections` globally so ee-gcc emits one
`.<sec>.D_<VMA>` section per plain typed def. Slot generator then
emits one slot per per-symbol section. This naturally interleaves
with foreign typed slots at intermediate VMAs.

`-fdata-sections` confirmed working with ee-gcc 2.9 — each typed def
gets its own section. Clean rebuild with all attr-tagged TUs +
per-symbol slot generator: SHA-1 round-trip clean. Pipeline change
landed in working tree but reverted due to compounding issues when
stripping the deferred TUs:

- **Small-const-to-sdata leak**: a `const float D_X[2]` (8 bytes)
  lands in `.sdata.D_<VMA>` under `-G 8` even when the original VMA
  is in `.rodata`. The per-symbol slot generator places it in the
  `.sdata` output block at the wrong VMA. Filter by VMA-range (added
  in the experiment) skips the symbol entirely → its bytes go
  unclaimed.
- **PObj.c strip moved sdata symbol byte offsets**: SHA-1 broke at
  `0x00101CC0` with `+0x8` shift in an `addiu` immediate. Cause
  not fully diagnosed before revert.

The path forward requires:

1. **Place `const` of any size into `.rodata` regardless of `-G`**:
   either find an ee-gcc flag or wrap with an explicit
   `__attribute__((section(".rodata")))` (non-VMA, just `.rodata`)
   on small const arrays during strip. Strip helper extension.
2. **Validate per-symbol slot generator across all sections** with
   the small-const fix in place. Iterate on cascading errors.
3. **Roll out the 6 deferred TUs** with the per-symbol pipeline.

The per-symbol slot generator code is preserved in the session's
git reflog if needed; revisit when context permits the full debug
iteration.
