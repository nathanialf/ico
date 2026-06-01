# func_001321C8 — near-miss rc5 (iosCdvdMgrReadDir)

## rc6 -> rc5: permuter-found lever (5-min shot, user-authorized)
`new_var = D_00556A10; func_00264DF8(name, new_var, entry)` — a live-range split
of the A10 GLOBAL format-string address (the dev's `const char *fmt`). Fixes the
A10 emission order (A10 lui before namebuf addiu, matching ROM). The permuter's
best mutation (score 420->220); could NOT find the func_00265168 stack-remat.
KEY: GLOBAL-address splits work (separate pseudo); STACK-address splits (namebuf,
&size = sp+0x20 / sp+0x124) all FOLD via copy-prop — that's why namebuf can't be
made 1-ref by any clean spelling.


VRAM 0x001321C8  TU ios/cdvd.c (111 insns, frame 0x1d0).
ALGORITHM + FRAME correct. This pass drove rc51 -> 7 with clean dev shapes.

## Cracked this pass (rc51 -> rc7), all clean source shapes
1. **single-base D_0027E528 + reload D_00631F54 every use** (rc51->33): the id/size
   live at `D_0027E528[n*0x30] - 8 / -4` (== D_0027E520[n]). Reach them off the
   SINGLE D_0027E528 base. CRUCIAL: reload `D_00631F54` at every use (the
   increment too: `D_00631F54 = D_00631F54 + 1`, NOT `n+1`) so `n` never lives
   across the f1-read call. Keeping `n` live put it in callee-saved s2 and shoved
   `self` to s3 (the old rc65 wall). With the reload, `n` is a scratch reload and
   `self` stays s2.
2. **p = namebuf BEFORE the func_00264DF8 calls, pass p as the 2nd dest** (rc33->23):
   p crosses the calls -> callee-saved s0 (the namebuf walker), coalesces with the
   later D_0027E528 base.
3. **rounded = size / 0x800** (rc23->13): signed div-by-2048 emits the ROM's
   `addiu -1; slt(-1<size); movn; sra 11`. The hand bias (`size+0x7FF; if(size>=0)`)
   emitted `slti<0 + movz` — wrong idiom.
4. **nc = 24 shift-count carry trick** (rc13->9), lifted verbatim from the matched
   sibling func_00133218: `int t = ((int)c) << (nc = 24); ... nc = *p; c = nc;
   } while (nc != 0);`. Fixes the bnez-delay carry + the spurious nop.
5. **fuse both `return 1` via `goto end`** (rc9->7): `if (count-- <= 0) goto end;`
   ... `end: return 1;`. Puts `ld ra` before `addiu v0,1` in the shared epilogue.
6. **p = namebuf RESET before func_00265168 #1, pass p** (rc7->6): a hand
   live-range SPLIT of p (range A = init+walk dies at loop end; range B = reborn
   for the call). Perturbed global allocation so func_00264DF8 #2 now reads p(s0)
   like the ROM (was reading the namebuf invariant s4). This is the SAME lever
   class the permuter used on func_001FB768.

## THE ONE remaining cluster (rc6): namebuf/&size register SWAP (s4<->s5)
Everything else is byte-identical. The 6 diffs are ALL one root (after lever 6
fixed func_00264DF8 #2, the namebuf invariant is now 2-ref: p-init + func_00265168 #1):
- ROM: namebuf=s5, &size=s4.   built: namebuf=s4, &size=s5.
Preheader emission order is IDENTICAL; only the register assignment differs, plus
the two downstream consequences (func_00264DF8 #2 uses s0/p in ROM vs s4 in built;
func_00265168 #1 buffer is REMATERIALIZED `addiu a1,sp,0x20` in ROM vs `daddu a1,s4`
in built).

### Root cause (DIAGNOSTIC-CONFIRMED)
gcc 2.9 allocno priority ~ `floor_log2(n_refs)*freq/live_length`. The `namebuf`
invariant gets **3 refs** in the built (p-init + func_00264DF8 #2 via cprop +
func_00265168 #1) -> pri>0 -> grabs s4. `&size` has 1 ref -> `floor_log2(1)=0` ->
pri 0 -> loses, lands s5. In the ROM the namebuf invariant has **1 ref** (p-init
only); func_00264DF8 #2 uses p(s0) and func_00265168 #1 REMATS sp+0x20 as a
separate pseudo, so namebuf ties with &size at pri 0 and the allocno tie-break
hands &size the lower reg (s4) — exactly the ROM.

**Proof:** routing func_00265168 #1's buffer to a DIFFERENT address (`entry`,
sp+0) makes namebuf a 1-ref invariant and the preheader flips to the ROM's
`namebuf=s5 / &size=s4`. So reducing the namebuf invariant to 1 ref is necessary
AND sufficient for the swap.

### Why it resists (the actual blocker)
To get namebuf to 1 ref, func_00265168 #1's buffer must be a SEPARATE
rematerialized pseudo (sp+0x20), not the hoisted namebuf invariant. gcc's
GCSE/cprop merges every clean spelling of sp+0x20 into the one namebuf invariant
allocno. Shapes tried that ALL still merge (stayed rc7 / regressed):
- fresh local `nb = namebuf` right before the call (nested scope)
- `entry + 0x20` (== namebuf; CSE folds the equivalence)
- `(unsigned char*)&namebuf` (ADDR_EXPR form)
- `c = *p` instead of `namebuf[0]`
- `func_00264DF8(namebuf,...)` vs `func_00264DF8(p,...)` (equivalent, gcc picks s4)
- q-separate-walk (p pinned to namebuf for both calls, q walks) -> rc19 WORSE
- function-scope vs block-scope local declarations -> no change
- psize=&size early (gives &size 2 refs -> pri>0 but still < namebuf) -> rc24 WORSE

func_00133218 (matched sibling, same normalise+register) sidesteps this only
because its buf is at sp+0 (free `daddu reg,sp` remat everywhere); it cannot be
inlined here (it is a standalone called by jal from func_00132FF0/131818/1315A8/
132388 + cod/09F7A8, so it must stay a real symbol). The dev's func_001321C8
normalise is duplicated inline code gcc compiles fresh.

## Next levers (fresh eyes)
- This is a GCSE coalesce-break / live-range-split — the EXACT class the permuter
  cracked for func_001FB768 (an assignment-in-condition that broke a coalesce).
  Per repo discipline the permuter is USER-GATED and fires at a genuine stall;
  fire one bounded shot on the rc7 seed to surface the live-range-split lever,
  then re-apply it by hand.
- Any clean source shape that makes gcc treat func_00265168 #1's sp+0x20 buffer
  as a distinct (rematerializable) value from the p-init namebuf solves it
  outright — keep hunting a spelling GCSE won't fold.
- NOT a floor. Single regalloc swap, mechanism fully understood.
