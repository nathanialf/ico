# func_001F3A28 — near-miss rc3 (weapon.c) — PARKED at 75-stall

VRAM 0x001F3A28, file_off 0x0F3A28. TU src/weapon (coalesced). FP, frame 0xC0.

## What it is
Debug circle-draw: 16 line segments (radius 30, center y=130, fixed-pt angle
0x10000=full turn). func_0010E9A0=cos, func_0010E950=sin (short angle -> float).
Per iter builds 2 vertices {x,pad,y,w} (DbgVtx, 8-aligned), draws via func_001D4A58.

## Progress rc71 -> rc3 (cracked)
- frame-size shifted-IV: angB = `(int)angA + 0x1000` (angA-sourced), NOT (short)(i+K).
- struct copy ldl/ldr -> ld/sd: `DbgVtx __attribute__((aligned(8)))`.
- FP const regs: compute y(uses 130.0) before w(1.0) -> 130->f22, 1.0->f21.
- stack layout: `DbgVtx buf[3]`; build buf[1]/buf[2], copy down to buf[0]/buf[1].
- scheduling (PERMUTER): `do { } while (0);` barrier after `i += 0x1000` -> rc9->8.
- int angB lever: `int angB = (int)angA + 0x1000` (int, no re-trunc) -> rc8->3.

## Residual (rc3, 2 sites) — the wall
  ROM:   addiu s1,s2,0x1000 ; daddu s2,s1   (i+0x1000 ONCE in s1, i=s1, angB=(short)s1)
  built: addiu s2,s2,0x1000 ; addiu s1,s0,0x1000  (i+= ; angB-base = angA+0x1000 from s0)
gcc strength-reduces ANY i-sourced `(short)(i+K)` into a shared `i<<16` shifted IV
(rc31-36) OR merges angB-from-i with i (under-frame, rc32). The only non-shift,
separate-reg shape is angA-sourced (s0). ROM emits both angles as 2 INDEPENDENT
sll/sra (no shifted IV) sourced from i (s2) — a gcc cost-model divergence not
reproducible in clean C.

## Streak: 78 distinct hyps (stall-limit 75) + 1 permuter shot (gave the barrier).
Ruled out: every (short)(i+K) form, next-reuse, pass-int-to-short-param, decoupled
short-ang IV, oldi-snapshot, int-angB-from-i (merges), static-inline setVtx helper
(rc64 worse), all 24 store-orders x2 vertices, register hints, ~12 barrier positions,
bound forms, pad-as-float, setup-call reorders, draw-arg temps. COOKBOOK §3.10
(in-loop mult reassign) is the mult-walk SR, not the (short)-shift case.

## Next levers
- offline auto_permute.sh on this rc3 seed (it found the barrier in 5min).
- the i-sourced-angB-without-shift is the whole game; needs a gcc cost-model nudge
  not yet found (every clean i-source shape either shifts or merges).
