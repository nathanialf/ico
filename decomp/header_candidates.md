# Header migration plan — eliminate per-TU private headers

**Policy:** `src/<TU>.h` files are not allowed unless the corresponding
header is listed in `decomp/source_tree/`. Currently only
`include/charFileName.h` and `include/mv_defs.h` have source_tree
placeholders — no `src/*.h` is sanctioned. The 7 existing `src/*.h`
files are legacy from an earlier promotion attempt and need to be
migrated back into their `.c`.

## Why no per-TU `.h`

- Public per-TU headers aren't part of the original source layout
  (the `__FILE__` literal census shows none).
- Splitting rodata defs into a `.h` was a stylistic choice that
  predates the per-TU `_data.c` sidecar pattern. The sidecar already
  isolates the load-bearing data (`.sdata` / `.lit4` /
  gp_rel-referenced symbols — `feedback_lit4_gp_rel`).
- Plain rodata (string literals, lui+addiu-referenced arrays) has no
  codegen invariant requiring isolation; it lives fine inline in the
  `.c`. The target pattern is `src/EnemyInit.c` — rodata typed defs
  in the `.c` body, sdata declared `extern` (defined in the sidecar).

## Files to migrate

7 legacy headers to absorb back into their `.c`:

| header | TU has INCLUDE_ASM? | notes |
| --- | --- | --- |
| `src/Basic.h` | no | safe migration; rodata + externs only |
| `src/DmaPacket.h` | no | safe |
| `src/clothTest.h` | no | safe |
| `src/moveColTest.h` | no | safe |
| `src/particleLayout.h` | no | safe |
| `src/sugiTree.h` | no | safe (smallest — start here) |
| `src/attackhit.h` | **yes** | needs care — see below |

## Migration procedure (per TU)

For each `src/<TU>.h`:

1. Read `<TU>.h`. Drop the `#ifndef X / #define X / #endif` guards.
2. Inline the body (the `#include`s, rodata defs with section attrs,
   and `extern` decls) into `<TU>.c` at the top, after the leading
   file-header comment, before any function definitions. Keep
   declaration order stable.
3. Remove `#include "<TU>.h"` from `<TU>.c`.
4. `git rm src/<TU>.h`.
5. Rebuild: `ninja` and verify SHA-1 round-trip (must stay
   byte-identical). If the rebuilt ELF mismatches, the change broke
   something — diff and revert.
6. Re-run `tools/identify_tus.py` to confirm coverage is unchanged.

## attackhit.c special case

`attackhit.c` has 1 `INCLUDE_ASM` (currently parked under
`asm/nonmatchings/src/attackhit/`). The `feedback_lit4_gp_rel` rule
forbids putting `.lit4` or gp_rel-referenced `.sdata` definitions in
the same TU as `INCLUDE_ASM`'d functions. `attackhit.h` holds rodata
only (no `.lit4`, no `.sdata` defs — sdata is `extern` only), so
inlining it should be safe.

Still — migrate after the 6 safe cases. Rebuild and SHA-1 check
attackhit specifically; if gp_rel codegen for the INCLUDE_ASM'd
function regresses, the rodata defs need to stay in a separate
compilation unit (move them into `attackhit_data.c` rather than back
to `attackhit.c`).

## After migration

- Update `tools/build_source_tree.py` `tu_status` so `.h` presence
  is no longer a "completion" signal. (Already done.)
- Drop "private headers" mentions from `decomp/NOTES.md` if any
  still recommend the pattern.
- Future `tu_status.py` "complete" check is purely
  `0 INCLUDE_ASM in <TU>.c` — orthogonal to whether a `.h` exists.
