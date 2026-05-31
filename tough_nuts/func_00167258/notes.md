# func_00167258 — parked

VRAM: 0x00167258 (file_off 0x067258)
Asm source: asm/nonmatchings/src/fieldCollision/func_00167258.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (NOP)

**TU:** `src/fieldCollision.c`

**Seed:** `tough_nuts/func_00167258/func_00167258.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006323C0, 1
.extern D_006323C7, 1

.align 3
nonmatching func_00167258, 0x20

glabel func_00167258
    /* 67258 00167258 2D108000 */  daddu      $2, $4, $0
    /* 6725C 0016725C 940040AC */  sw         $0, 0x94($2)
    /* 67260 00167260 D79A836B */  ldl        $3, (D_006323C7) /* gp_rel: (D_006323C7) */
    /* 67264 00167264 D09A836F */  ldr        $3, (D_006323C0) /* gp_rel: (D_006323C0) */
    /* 67268 00167268 930043B0 */  sdl        $3, 0x93($2)
    /* 6726C 0016726C 8C0043B4 */  sdr        $3, 0x8C($2)
    /* 67270 00167270 849B0508 */  j          func_00166E10
    /* 67274 00167274 00000000 */   nop
endlabel func_00167258
```

## 2026-05-31 near-miss — packed-struct gets unaligned ops, gp_rel base-fold remains
Clean shape (NO inline asm) gets STRUCTURE correct:
  typedef struct { long long v; } __attribute__((packed)) U64_fc;
  extern U64_fc D_006323C0;
  void func_00167258(int *self){ *(int*)((char*)self+0x94)=0;
    *(U64_fc*)((char*)self+0x8C)=D_006323C0; func_00166E10(self); }
→ emits daddu v0,a0; sw zero,148(v0); ldl/ldr (load); sdl/sdr 147/140(v0) (store); j func_00166E10. CORRECT ops+offsets.
ONLY diff: SOURCE load base-fold. Built: `addiu a3,gp,%gp_rel(D); ldl v1,7(a3); ldr v1,0(a3)`.
Expected: `ldl v1,%gp_rel(D_006323C7)($gp); ldr v1,%gp_rel(D_006323C0)($gp)` (symbol folded directly into ldl/ldr off $gp).
Tried: extern long long (8-aligned)->aligned ld (worse); extern int + &cast -> base-fold; packed struct direct read -> base-fold (same).
NEXT: make gcc fold gp_rel into the unaligned ldl/ldr (no intermediate base reg). The OLD seed used inline asm for exactly this;
clean lever not yet found. Maybe a 4-aligned char[8] global, or a different small-global access pattern. Permuter after 30-stall.

## 2026-05-31 (turn 3) — gp_rel base-fold wall: 7 source forms, ee-gcc always materializes base
Goal remaining: SOURCE load must be `ldl v1,%gp_rel(D_006323C7)($gp); ldr v1,%gp_rel(D_006323C0)($gp)`
(symbol folded into ldl/ldr off $gp directly). Built always materializes base into a reg first.
Forms tried for the source (all wrong):
 1. extern long long (8-aligned)            -> aligned `ld` (no ldl/ldr)
 2. extern int + *(packed*)&D               -> ldl/ldr but `addiu a3,gp; ldl 7(a3)` (base-mat, gp_rel)
 3. packed struct, direct `=D`              -> ldl/ldr base-mat (gp_rel)
 4. typedef long long aligned(1), cast      -> aligned `ld`
 5. extern long long __attribute__(aligned1)-> aligned `ld`
 6. packed member scalar via `long long t=D.v` -> ldl/ldr base-mat (`addiu at,gp; ldl 7(at)`)
 7. extern char[] __asm__("D_006323C0") cast -> ldl/ldr but `lui a1,%hi` (FAR addr, WORSE)
CONCLUSION: ee-gcc 2.9 in THIS build never folds a gp_rel symbol into an unaligned ldl/ldr displacement;
it materializes the base every time. Packed struct is the ONLY way to get ldl/ldr at all (forms 2,3,6).
The DEST store (sdl/sdr 147/140(v0)) + flow + tail-call are ALL CORRECT with the packed struct.
NEXT: this is the gp_rel-unaligned-fold the inline-asm seed exists for; clean lever unknown after 7 forms.
Candidate for a permuter shot at 30-stall (currently ~7 distinct hyps). DEST-side is solved; only SOURCE base-fold remains.

## 2026-05-31 (turn 4, resume) — 8th form: __builtin_memcpy also base-mats
`__builtin_memcpy((char*)self+0x8C, D_006323C0, 8)` (extern char D_006323C0[8])
→ STILL `addiu a3,gp,0; ldl v1,7(a3); ldr v1,0(a3)` (base-mat) AND reorders the
tail-call j (rc6, worse than the packed-struct rc). The gp_rel→ldl/ldr fold is a
genuine ee-gcc-2.9-build addressing-mode limitation (8 clean forms now ruled
out); the real ICO compiler folded it but ours CSEs the base across ldl+ldr.
Clean shape unreachable in this build; inline-asm seed is the only match. Leave
parked for the DEFERRED crutch-strip workstream — NOT worth more heartbeat grind.
