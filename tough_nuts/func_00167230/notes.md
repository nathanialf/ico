# func_00167230 — parked

VRAM: 0x00167230 (file_off 0x067230)
Asm source: asm/nonmatchings/src/fieldCollision/func_00167230.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (NOP)

**TU:** `src/fieldCollision.c`

**Seed:** `tough_nuts/func_00167230/func_00167230.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006323C0, 1
.extern D_006323C7, 1

.align 3
nonmatching func_00167230, 0x28

glabel func_00167230
    /* 67230 00167230 2D108000 */  daddu      $2, $4, $0
    /* 67234 00167234 B00040AC */  sw         $0, 0xB0($2)
    /* 67238 00167238 940040AC */  sw         $0, 0x94($2)
    /* 6723C 0016723C 880040AC */  sw         $0, 0x88($2)
    /* 67240 00167240 D79A836B */  ldl        $3, (D_006323C7) /* gp_rel: (D_006323C7) */
    /* 67244 00167244 D09A836F */  ldr        $3, (D_006323C0) /* gp_rel: (D_006323C0) */
    /* 67248 00167248 870043B0 */  sdl        $3, 0x87($2)
    /* 6724C 0016724C 800043B4 */  sdr        $3, 0x80($2)
    /* 67250 00167250 849B0508 */  j          func_00166E10
    /* 67254 00167254 00000000 */   nop
endlabel func_00167230
```

## Update 2026-05-31 (clean-C, no crutch)

Clean C reaches **rc6**, and EVERYTHING matches except the gp_rel-unaligned-fold:
`daddu v0,a0,zero` (base copy, a0 kept for tail-call), the 3 `sw zero` field
zeroes, the `sdl/sdr` packed store to self+0x80, and the `j func_00166E10` void
tail-call ALL align. Sole residual:
```
exp: ldl v1,%gp_rel(D_006323C7); ldr v1,%gp_rel(D_006323C0)   (direct gp_rel)
got: addiu at,gp,%gp_rel(D_006323C0); ldl v1,7(at); ldr v1,0(at)
```
Clean shape that gets rc6:
```c
struct PackedLL_67230 { long long v; } __attribute__((packed));
extern struct PackedLL_67230 D_006323C0;
void func_00167230(int *self) {
    *(int*)((char*)self+0xB0)=0; *(int*)((char*)self+0x94)=0; *(int*)((char*)self+0x88)=0;
    *(struct PackedLL_67230*)((char*)self+0x80) = D_006323C0;   /* ldl/ldr + sdl/sdr */
    func_00166E10(self);
}
```
WALL: ee-gcc 2.9 folds %gp_rel into an ALIGNED `ld` (aligned(1) typedef → `ld
v1,0(gp)` direct, but wrong — ROM uses ldl/ldr) but NOT into the unaligned
`ldl/ldr` (materializes `addiu at,gp` first). The ROM compiler folded it. Tried:
whole-struct-copy, aligned(1) typedef, member-to-member, explicit ll local — all
keep the addiu base. This is the gp_rel-unaligned-fold wall; the original parked
seed forced it with raw `__asm__("ldl %0,%%gp_rel(...)($28)")`. Same idiom in
sibling func_00167258. Leave for offline auto_permute / a future gp_rel-fold lever.
