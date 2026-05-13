
---

## Attempt at 2026-05-08

**Reason parked:** 2-call+store: ee-gcc skips daddu v1,v0,zero (uses v0 directly); original copies v0 to v1 first

Seed: `tough_nuts/func_001AA4F0/0AA4F0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001AA4F0; check asm/matchings/cod/0AA4F0/)
```

---

## Attempt at 2026-05-13

**Reason parked:** v0→v1 copy missing before gp_rel store of return value

Seed: `tough_nuts/func_001AA4F0/0AA4F0.c.new`

Disassembly excerpt:

```
glabel func_001AA4F0
    /* AA4F0 001AA4F0 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* AA4F4 001AA4F4 2D388000 */  daddu      $a3, $a0, $zero
    /* AA4F8 001AA4F8 1000B1FF */  sd         $s1, 0x10($sp)
    /* AA4FC 001AA4FC 6100063C */  lui        $a2, %hi(D_00615B48)
    /* AA500 001AA500 0000B0FF */  sd         $s0, 0x0($sp)
    /* AA504 001AA504 2D88A000 */  daddu      $s1, $a1, $zero
    /* AA508 001AA508 6F00103C */  lui        $s0, %hi(D_006EE030)
    /* AA50C 001AA50C 6300053C */  lui        $a1, %hi(D_00632C88)
    /* AA510 001AA510 30E01026 */  addiu      $s0, $s0, %lo(D_006EE030)
    /* AA514 001AA514 2000BFFF */  sd         $ra, 0x20($sp)
    /* AA518 001AA518 2D200002 */  daddu      $a0, $s0, $zero
    /* AA51C 001AA51C 882CA524 */  addiu      $a1, $a1, %lo(D_00632C88)
    /* AA520 001AA520 7E93090C */  jal        func_00264DF8
    /* AA524 001AA524 485BC624 */   addiu     $a2, $a2, %lo(D_00615B48)
    /* AA528 001AA528 2D200002 */  daddu      $a0, $s0, $zero
    /* AA52C 001AA52C E01C090C */  jal        func_00247380
    /* AA530 001AA530 2D282002 */   daddu     $a1, $s1, $zero
    /* AA534 001AA534 2D184000 */  daddu      $v1, $v0, $zero
    /* AA538 001AA538 2000BFDF */  ld         $ra, 0x20($sp)
    /* AA53C 001AA53C 1000B1DF */  ld         $s1, 0x10($sp)
    /* AA540 001AA540 0000B0DF */  ld         $s0, 0x0($sp)
    /* AA544 001AA544 90A383AF */  sw         $v1, %gp_rel(D_00632C80)($gp)
    /* AA548 001AA548 0800E003 */  jr         $ra
    /* AA54C 001AA54C 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_001AA4F0
```
