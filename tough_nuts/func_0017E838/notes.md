
---

## Attempt at 2026-05-08

**Reason parked:** swc1+sw_zero+lw a0 scheduling order differs from target

Seed: `tough_nuts/func_0017E838/07E838.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017E838; check asm/matchings/cod/07E838/)
```

---

## Attempt at 2026-05-08

**Reason parked:** 3-float pack: ee-gcc reorders sw zero before swc1 + interleaves lw a0; original keeps source order

Seed: `tough_nuts/func_0017E838/07E838.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017E838; check asm/matchings/cod/07E838/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss: gcc interleaves int prep (sw zero/lw a0) with float stores; expected groups all 3 swc1 first, then sw zero/lw a0. KEEP_LIVE_MEM fixes float ordering but defers sd ra.

Seed: `tough_nuts/func_0017E838/07E838.c.new`

Disassembly excerpt:

```
glabel func_0017E838
    /* 7E838 0017E838 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 7E83C 0017E83C 1000BFFF */  sd         $ra, 0x10($sp)
    /* 7E840 0017E840 2D28A003 */  daddu      $a1, $sp, $zero
    /* 7E844 0017E844 0000ACE7 */  swc1       $f12, 0x0($sp)
    /* 7E848 0017E848 0400ADE7 */  swc1       $f13, 0x4($sp)
    /* 7E84C 0017E84C 0800AEE7 */  swc1       $f14, 0x8($sp)
    /* 7E850 0017E850 0C00A0AF */  sw         $zero, 0xC($sp)
    /* 7E854 0017E854 5C01848C */  lw         $a0, 0x15C($a0)
    /* 7E858 0017E858 C017040C */  jal        func_00105F00
    /* 7E85C 0017E85C 70068424 */   addiu     $a0, $a0, 0x670
    /* 7E860 0017E860 1000BFDF */  ld         $ra, 0x10($sp)
    /* 7E864 0017E864 0800E003 */  jr         $ra
    /* 7E868 0017E868 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0017E838
```
