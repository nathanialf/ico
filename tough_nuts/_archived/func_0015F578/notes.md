
---

## Attempt at 2026-05-12

**Reason parked:** very close: scheduling and reg alloc differs in the unaligned copy section; target preserves D_00282660 in a0+t0 split, built uses v0 only

Seed: `tough_nuts/func_0015F578/05F578.c`

Disassembly excerpt:

```
glabel func_0015F578
    /* 5F578 0015F578 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 5F57C 0015F57C 0000A4AF */  sw         $a0, 0x0($sp)
    /* 5F580 0015F580 6300043C */  lui        $a0, %hi(D_006322F0)
    /* 5F584 0015F584 1000BFFF */  sd         $ra, 0x10($sp)
    /* 5F588 0015F588 8A9B060C */  jal        func_001A6E28
    /* 5F58C 0015F58C F0228424 */   addiu     $a0, $a0, %lo(D_006322F0)
    /* 5F590 0015F590 0000A38F */  lw         $v1, 0x0($sp)
    /* 5F594 0015F594 2800043C */  lui        $a0, %hi(D_00282660)
    /* 5F598 0015F598 5C01628C */  lw         $v0, 0x15C($v1)
    /* 5F59C 0015F59C 60268824 */  addiu      $t0, $a0, %lo(D_00282660)
    /* 5F5A0 0015F5A0 07000369 */  ldl        $v1, 0x7($t0)
    /* 5F5A4 0015F5A4 0000036D */  ldr        $v1, 0x0($t0)
    /* 5F5A8 0015F5A8 0800068D */  lw         $a2, 0x8($t0)
    /* 5F5AC 0015F5AC C70143B0 */  sdl        $v1, 0x1C7($v0)
    /* 5F5B0 0015F5B0 C00143B4 */  sdr        $v1, 0x1C0($v0)
    /* 5F5B4 0015F5B4 C80146AC */  sw         $a2, 0x1C8($v0)
    /* 5F5B8 0015F5B8 0000A48F */  lw         $a0, 0x0($sp)
    /* 5F5BC 0015F5BC 5862050C */  jal        func_00158960
    /* 5F5C0 0015F5C0 2D280000 */   daddu     $a1, $zero, $zero
    /* 5F5C4 0015F5C4 1000BFDF */  ld         $ra, 0x10($sp)
    /* 5F5C8 0015F5C8 0800E003 */  jr         $ra
    /* 5F5CC 0015F5CC 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0015F578
```
