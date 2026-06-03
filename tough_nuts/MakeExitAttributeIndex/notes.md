# MakeExitAttributeIndex — parked

VRAM: 0x00165088 (file_off 0x065088)
Asm source: asm/aug6/nonmatchings/fumi/src/fieldCollision/MakeExitAttributeIndex.s

## Attempt at 2026-06-03

**Reason parked:** rc6 TOOLCHAIN gap (not source-shape): unaligned 64-bit load of gp_rel global D_0062A6A0. ee-gcc emits 'uld $3,D_0062A6A0'; BOTH assemblers (2.96 + 2.9-991111, verified via minimal .s) expand uld to 'daddiu at,gp,sym; ldl 7(at); ldr 0(at)' while ROM folds 'ldl %gp_rel(sym+7)($28); ldr %gp_rel(sym)($28)'. use_old_as does NOT fix. ~14 source forms (packed struct/union/array/aligned(1)/asm-alias/temp/memcpy) all emit uld. Override-park on empirical toolchain finding; needs a uld-fold peephole or period toolchain. See uld_gprel_fold_gap memory + ~9 sibling funcs.

**TU:** `fumi/src/fieldCollision.c`

**Seed:** `tough_nuts/MakeExitAttributeIndex/MakeExitAttributeIndex.c`

Disassembly:

```
.align 3
nonmatching MakeExitAttributeIndex, 0x20

glabel MakeExitAttributeIndex
    /* 65088 00165088 2D108000 */  daddu      $2, $4, $0
    /* 6508C 0016508C 940040AC */  sw         $0, 0x94($2)
    /* 65090 00165090 B79A836B */  ldl        $3, %gp_rel(D_0062A6A7)($28)
    /* 65094 00165094 B09A836F */  ldr        $3, %gp_rel(D_0062A6A0)($28)
    /* 65098 00165098 930043B0 */  sdl        $3, 0x93($2)
    /* 6509C 0016509C 8C0043B4 */  sdr        $3, 0x8C($2)
    /* 650A0 001650A0 10930508 */  j          GetEdgeOfFloor
    /* 650A4 001650A4 00000000 */   nop
endlabel MakeExitAttributeIndex
```
