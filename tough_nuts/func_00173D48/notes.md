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
