# func_00194840 — mail-add-data (3-call wrapper + abs<a3)

VRAM 0x00194840. TU: src/mail-add-data.c (coalesced). Asm:
asm/nonmatchings/src/mail-add-data/func_00194840.s

Best real_count: **17** (frame-size / gcc allocator quirk, see below).

## What it does
Two 16-byte stack scratch buffers (buf0 @ sp+0, buf1 @ sp+0x10):
- func_00243AE8(buf1, a0, a1)   (fill buf1 from a0,a1)
- buf1[1] = 0                   (sw zero, 0x14(sp))
- func_00243978(buf0, buf1)     (transform buf1 -> buf0; copy idiom, cf. geometryManager:87)
- r = func_00194508(buf0, a2)
- return abs(r) < a3
a2,a3 saved in callee-saved across the calls; 5-arg-ish (a0..a3).

## Levers that WORKED (28 -> 17)
1. `return __builtin_abs(r) < a3;` — the abs is `bltzl + negu` (annulled
   delay), NOT the branchless `movn` that `if(r<0)r=-r` gives. 28->21.
2. `register int sa2 REG("$16")=a2; register int sa3 REG("$17")=a3;` —
   pin a2->s0, a3->s1 (the callee-saved regs the original uses). 21->17.

## RESIDUAL 17 diffs (ONE root cause: &buf1 cached vs rematerialized)
gcc keeps `&buf1` (sp+0x10) in a THIRD callee-saved reg (s2) across
call1->call2 instead of rematerializing `addiu sp,16` at each use — so
the frame is 0x60 (s0,s1,s2,ra) vs the original's 0x50 (s0,s1,ra). The
original rematerializes BOTH buffer addresses each call (it rematerializes
&buf0=sp+0 trivially AND &buf1=sp+0x10 via addiu). gcc 2.9's allocator
chose to spill the sp+0x10 address to a callee-saved instead of
rematerializing the 1-insn addiu — a suboptimal-but-deterministic choice.
The whole 17 is the prologue/epilogue/save-offset cascade from that one
extra s2; fix the caching and it collapses to ~0.

Ruled out: single backing `int buf[8]` + index exprs (no change, gcc
still CSE+caches &buf[4]); 2 separate arrays (same). pins move the cache
to a different sN but don't stop it.

## Next: permuter / fresh idea
Need to stop gcc allocating &buf1(sp+0x10) to a callee-saved reg —
force rematerialization. Ideas: a structure that shortens &buf1's
live range so it's recomputed; or investigate whether the original used
the buffers in a different order/expression. Permuter seed is the rc17
form. CFLAGS = exact quick_diff CFLAGS (no per-file flag).
