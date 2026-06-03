# func_00173D48 — near-miss (rc2), NOT yet 30-stalled

VRAM 0x00173D48, TU fumi/src/jimaku.c. 8-insn call wrapper.

ROM:
  addiu sp,-0x20 ; sd ra,0x10 ; sw a0,0x0 ; jal ACTLookTargetSystem_Exec ; nop
  ; ld ra,0x10 ; jr ra ; addiu sp,0x20
= store a0 to a stack local (no reload), save ra, call, nop delay, return.

Progress this session rc3->rc2. Findings:
- Sibling idiom: jimakuUndisp uses `void *volatile q = a0;`; the ClipWall*/
  readBufBeginPut wrappers in fumi use a trailing `__asm__ __volatile__("")`
  barrier to stop gcc hoisting the epilogue `ld ra` into the jal delay slot.
- `void *volatile q=a0; f(); __asm__ __volatile__("");` (NO-ARG call) = rc2.
  ONLY diff: the volatile store `sw a0,0(sp)` floats BEFORE `sd ra,0x10(sp)`;
  ROM has `sd ra` first. volatile emits the store ASAP -> too early.
- `...f(a0)...` (ARG call) keeps the correct `sd ra`-first order BUT gcc inserts
  `daddu v0,a0 ; sw v0,0(sp)` (a gratuitous a0->v0 copy) instead of `sw a0`.
  The copy appears whenever a0 is BOTH volatile-stored AND passed to the call.
- memory-clobber barrier (`"":::"memory"`) regresses (rc3, reload).
NEXT LEVERS: (a) make the no-arg volatile store schedule AFTER sd ra (anchor it
to the frame / different local layout); (b) kill the arg-version a0->v0 copy so
`sw $4` stores directly while $4 stays the call arg. Both are scheduling/regalloc
order nuances — a clean shape should exist (rc2, one swapped pair). NOT 30-stalled
(only ~8 hand iters); resume and continue to match or a formal 30-stall.

---

## Attempt at 2026-06-03

**Reason parked:** genuine 30-stall park per match_loop next (best=rc2). Only diff: prologue sw a0 / sd ra order (volatile store floats ahead of callee-save) + the jal-delay store-vs-nop; ~30 distinct volatile/barrier/struct forms tried. Left for offline auto_permute.

**TU:** `fumi/src/jimaku.c`

**Seed:** `tough_nuts/func_00173D48/func_00173D48.c`

Disassembly:

```
.align 3
nonmatching func_00173D48, 0x20

glabel func_00173D48
    /* 73D48 00173D48 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 73D4C 00173D4C 1000BFFF */  sd         $31, 0x10($29)
    /* 73D50 00173D50 0000A4AF */  sw         $4, 0x0($29)
    /* 73D54 00173D54 5623050C */  jal        ACTLookTargetSystem_Exec
    /* 73D58 00173D58 00000000 */   nop
    /* 73D5C 00173D5C 1000BFDF */  ld         $31, 0x10($29)
    /* 73D60 00173D60 0800E003 */  jr         $31
    /* 73D64 00173D64 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00173D48
```

## Resume 2026-06-03 (cont.) — genuine 30-stall PARK (match_loop next verdict)
Resumed at rc2; fired the (now-fixed) 5-min permuter shot (base score 60, NO
improvement, 0 errors — confirms the permuter race-fix). Hand-iterated ~30
DISTINCT forms from the reset baseline; `match_loop next` printed
`action: park` at `stall=30/30` (best=2), reason "the permuter would plateau;
PARK for the offline batch". Determined: ACTLookTargetSystem_Exec takes NO args
(sets $4 itself) → no-arg call is correct; the a0-home store needs a volatile
local, which floats the `sw a0` ahead of `sd ra` (ROM has sd ra first). Barrier
brackets (lead/mid/trail) either keep the store too early, push it into the jal
delay, or fill the delay with ld ra — none yields `sd ra; sw a0; jal; nop`.
use_old_as did NOT help (both assemblers fill the jal delay from the preceding
store). Parked for offline auto_permute per the next verdict.

---

## Resume 2026-06-03 (cont. #2) — ROOT CAUSE CORRECTED; assembler-parity blocker

Prior sessions mislabelled this an "rc2 prologue store-order source floor" and
said "use_old_as did not help." Both conclusions were WRONG. Re-derived from the
.s and the assemblers themselves:

* The clean dev shape is `void *volatile q = a0; ACTLookTargetSystem_Exec();`
  (NO __asm__ barrier — that was a crutch, now removed). `ACTLookTargetSystem_Exec`
  takes no args.
* gcc 2.9-991111 -O2 emits the CORRECT order: `sd ra` BEFORE `sw a0`, jal, then
  the epilogue. Assembled by **ee-as 2.9-991111** this is **byte-identical to
  ROM** (verified: jal delay = nop, sw a0 stays before jal). So the SOURCE IS
  SOLVED — there is no rc2, no store-order problem at the C level.
* The match is broken purely at ASSEMBLY time. jimaku is a mixed TU: its
  still-INCLUDE_ASM siblings (e.g. display_texture, iosCdvdBackGroundReadJimaku)
  contain splat's `%gp_rel(D_xxx)($28)`. BOTH period assemblers — ee-as 2.96 AND
  ee-as 2.9-991111 — reject `%gp_rel` ("Bad expression"; %hi/%lo are fine). So
  compile_c.sh falls back to **modern mips-linux-gnu-as**, which (like 2.96)
  fills the jal delay with the preceding `sw a0`. ROM (period assembler) left it
  nop. THIS is the only diff.
* `use_old_as jimaku` cannot help while those %gp_rel siblings exist (old-as
  can't even parse the TU). A universal `sw`-before-`jal` → nop postprocess is
  NOT legitimate: ROM jal delays are frequently filled with stores, so it is not
  the "0 of N" universal that the existing j-tailcall / FP-store parity awks are.

RESOLUTION PATH (no source work needed):
  (a) match all of jimaku's %gp_rel-bearing INCLUDE_ASM siblings → the TU is pure
      gcc output (gcc emits %hi/%lo, never %gp_rel) → add `jimaku` to
      config/use_old_as.txt → ee-as 2.9-991111 assembles it and the delay stays
      nop → byte match; OR
  (b) teach the old-as path to parse/translate `%gp_rel` (would unblock the whole
      assembler-parity match class on every mixed TU at once).

Status: tooling-blocked, NOT a 30-stall source park. Leave parked; revisit after
the jimaku %gp_rel siblings are done.
