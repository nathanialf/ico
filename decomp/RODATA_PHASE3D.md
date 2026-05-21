# Phase 3d — retire `__attribute__((section()))` VMA-pinned wrappers

Status: **implemented and operational.** This doc captures the shipped
architecture; see commits `2760845`..`8cc2875` for the trail.

## What Phase 3d retires

Pre-Phase-3d, every typed clean-room data def in tracked `src/<TU>.c`
was wrapped in a VMA-pinned attribute:

```c
__attribute__((section(".rodata.0x00553700"))) const char D_00553700[16] = "...";
```

Per `project_rodata_naming_is_temporary.md`, the `.0xVMA` suffix is a
clean-room trick, not original style — it exists only because the
linker needs to know where to place each `.o`'s typed bytes.

The Phase 3d steady state strips that suffix wherever ee-gcc's default
placement (under `-G 8`) matches the original section, leaving plain
defs:

```c
const char D_00553700[16] = "...";
```

A small subset of typed defs **require** the attribute (gcc's default
placement differs from the original section). Those retain the form
as a legitimate developer placement directive — see "Survivors" below.

## The pipeline (operational)

Four pieces, all in `tools/`:

### 1. `compile_c.sh`: `-fdata-sections`

ee-gcc 2.9 emits each plain data def into its own `.<sec>.<symbol>`
section. `const char D_X[N] = "..."` → `.rodata.D_X` (etc.). This is
the key enabler — it makes per-symbol slot placement possible.

### 2. `postprocess_slinky_ld.py`: per-symbol slot generator

Replaces the original `*(SORT_BY_NAME(.X.0x*))` catch-all with one
explicit slot per typed section. Recognizes both forms:

- `.<sec>.0x<VMA>` (legacy attr-tag form, for symbols that still need
  the attribute)
- `.<sec>.D_<VMA>` (per-symbol form from `-fdata-sections`)

For each slot, emits `KEEP(<.o>(.<sec>.<suffix>))` in VMA-ascending
order inside the section's output block. VMA-range filter per output
section drops slots whose name-encoded VMA falls outside the section's
range (handles ee-gcc's small-data leak).

Special handling for `jtbl_<VMA>` symbols owned by C-matched functions:
emits a slot pulling `<func.o>(.<sec>)` (exact `.rodata`, not
`.rodata*`) at the jtbl's VMA, so gcc's per-`.o` emitted jtbl bytes
land where the asm blanket's stripped block used to be.

### 3. `rewrite_data_named_sections.py`: jtbl strip

When a function migrates from asm to C (real body in tracked source,
not `INCLUDE_ASM`), this script:
1. Scans tracked .c/.c.inc for `func_X(...) { ... }` definitions, minus
   any that are also `INCLUDE_ASM`'d (INCLUDE_ASM wins on conflict).
2. For each matched function, opens its `asm/matchings/**/func_X.s`
   baseline and extracts `%hi(jtbl_<VMA>)` references.
3. Adds those jtbls to the migrated-symbol strip set, so the asm
   blanket's `.rodata.0x<jtbl_VMA>` block (whose `.word .L<addr>`
   entries point to labels that no longer exist) gets removed.

### 4. `strip_attr_phase3d.py`: smart strip helper

Strips the attribute iff ee-gcc's default placement matches the
original section. Default placement table (under `-G 8`):

| qualifier  | size  | gcc default placement |
|------------|-------|----------------------|
| `const`    | ≤ 8   | `.sdata`             |
| `const`    | > 8   | `.rodata`            |
| mutable    | ≤ 8   | `.sdata`             |
| mutable    | > 8   | `.data`              |
| any        | any   | never `.lit4`        |

If `default_section == original_section`: strip the attr (the plain
def will land in the right section naturally).

If `default_section != original_section`: retain the attr. It's the
minimum-necessary placement directive an original C author would
write to override the default.

Helper also auto-inserts `const` on `char` / `unsigned char` arrays
when stripping `.rodata` attrs (without `const`, `char[N]` defaults
to `.data`, not `.rodata`). And reorders plain defs in VMA-ascending
order within each contiguous span, since ee-gcc's `-fdata-sections`
emits them in source-declaration order.

## Slot mechanism in the linker output

A typical post-strip `.rodata` slot block in `ico.us.slinky.ld`:

```ld
.rodata : AT(rodata_ROM_START) {
    FILL(0x00000000);
    _gp_unused = . + 0x7FF0;  /* ... */
    rodata_RODATA_START = .;
    /* phase3d-slots .rodata */
    KEEP(build/src/charFileManager.o(.rodata.0x00553700));  /* typed 0x00553700 */
    KEEP(build/src/charFileManager.o(.rodata.0x00553720));  /* typed 0x00553720 */
    KEEP(build/src/charFileManager.o(.rodata.D_00553730));  /* typed 0x00553730 */
    ...
    KEEP(build/src/cod/00DFB8.o(.rodata));                  /* jtbl 0x00553E70 */
    ...
    rodata_RODATA_END = .;
}
```

Slots are sorted strictly by VMA-ascending. The slot generator asserts
no duplicate VMAs (a duplicate is a real symbol conflict, not a
positioning bug). Natural location-counter advancement handles
contiguous layout; no explicit `. = ABS - VRAM` cursor needed because
the original ELF's data sections are gap-free.

## Survivors (intentional attributes)

Per the steady state:

- **`.lit4`** entries (~37 in tracked, ~975 in sidecars): always retain
  `__attribute__((section(".lit4.0x<VMA>")))`. gcc has no automatic
  `.lit4` placement — without the attr, 4-byte floats land in `.sdata`
  under `-G 8`.
- **Small `.rodata` consts** (≤ 8 bytes, ~44 across the project):
  retain `.rodata.0x<VMA>`. Under `-G 8` they'd otherwise leak to
  `.sdata`. Concentrations: `ios/cdvd.c` (20), `src/enemy_act.c` (7),
  `src/PObj.c` (5), `src/debug.c` (3), `src/attackhit.c` (3), 6 others.
- **`.data` of any size that's `const`** (~3 across the project):
  retain `.data.0x<VMA>`. gcc default would put it in `.rodata`.
- **Any typed def whose original VMA section ≠ gcc default**: same
  rule applies.

These are not clean-room hacks — they're the form an original C author
writes when overriding the compiler's default. They make it possible
for the build to reproduce the original ELF byte-for-byte without
contaminating the rest of the source with VMA-pinning noise.

## Section status (session-end)

| Section | typed_attr | typed_plain | % stripped |
|---|---:|---:|---:|
| `.rodata` | 67 981 | 9 680 | 12.46 % |
| `.sdata` | 12 | 446 | 97.38 % |
| `.lit4` | 148 | 0 | 0.00 % (all survivors) |
| `.data` | 76 | 0 | 0.00 % (all survivors) |

`.rodata` strip % is bounded by total tracked bytes (~77 KB). The
905 KB section size is mostly gitignored sidecar bytes (the bytes
grind) — those aren't a Phase 3d concern.

## Matched functions with jtbls

Phase 3d's jtbl pipeline tested end-to-end on:

- `func_0010DFB8` (252 B, 7-case switch — vec3 component negation), in
  `src/cod/00DFB8.c`. Owns `jtbl_00553E70`.
- `func_0014B270` (124 B, DMA register field setter), in
  `src/act-parallel-control.c`. Owns `jtbl_00558150`.

99 jtbl-owning functions remain unmatched in asm. Each will
auto-strip its jtbl from the blanket when matched, via the pipeline.

## What remains

- **Text matching**: 99 jtbl-owning + thousands of non-jtbl functions
  still in asm. Normal decomp work, not Phase 3d's concern.
- **`.rodata` bytes grind**: 686 KB un-typed in sidecars. Typed
  reconstruction as designated-init struct arrays (or simpler forms
  where natural). Slow because most large symbols need consumer-code
  RE to determine shape.
- **`.data` bytes grind**: 3 MB un-typed in sidecars. Same story,
  bigger surface.
- **TU re-mapping** (`tools/build_data_tu_map.py` improvements:
  string-literal voting, jtbl weight-10, bidirectional proximity):
  not strictly needed by Phase 3d anymore (per-symbol slots work
  on non-promotable TUs too), but improves the "promotable" count
  for future cleanup.

Phase 3d itself is complete as scaffolding. Future strips happen
automatically as new typed defs land in tracked source.
