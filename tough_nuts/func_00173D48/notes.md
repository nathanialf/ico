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
