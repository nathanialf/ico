
---

## Attempt at 2026-05-08

**Reason parked:** same family as 1FC460 — ee-gcc 2.9 reorders sb/lw/sw sequence

Seed: `tough_nuts/func_001FC4C0/0FC4C0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001FC4C0; check asm/matchings/cod/0FC4C0/)
```

---

## Attempt at 2026-05-13

**Reason parked:** daddu s1,a0,zero placement between sd s1/s0 (ee-as scheduler)

Seed: `tough_nuts/func_001FC4C0/0FC4C0.c.new`

Disassembly excerpt:

```
glabel func_001FC4C0
    /* FC4C0 001FC4C0 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* FC4C4 001FC4C4 1000B1FF */  sd         $s1, 0x10($sp)
    /* FC4C8 001FC4C8 2D888000 */  daddu      $s1, $a0, $zero
    /* FC4CC 001FC4CC 0000B0FF */  sd         $s0, 0x0($sp)
    /* FC4D0 001FC4D0 2000BFFF */  sd         $ra, 0x20($sp)
    /* FC4D4 001FC4D4 F2EF070C */  jal        func_001FBFC8
    /* FC4D8 001FC4D8 2D80A000 */   daddu     $s0, $a1, $zero
    /* FC4DC 001FC4DC 40000292 */  lbu        $v0, 0x40($s0)
    /* FC4E0 001FC4E0 400022A2 */  sb         $v0, 0x40($s1)
    /* FC4E4 001FC4E4 3800038E */  lw         $v1, 0x38($s0)
    /* FC4E8 001FC4E8 340030AE */  sw         $s0, 0x34($s1)
    /* FC4EC 001FC4EC 380023AE */  sw         $v1, 0x38($s1)
    /* FC4F0 001FC4F0 380011AE */  sw         $s1, 0x38($s0)
    /* FC4F4 001FC4F4 4400028E */  lw         $v0, 0x44($s0)
    /* FC4F8 001FC4F8 3800238E */  lw         $v1, 0x38($s1)
    /* FC4FC 001FC4FC 02006014 */  bnez       $v1, .L001FC508
    /* FC500 001FC500 440022AE */   sw        $v0, 0x44($s1)
    /* FC504 001FC504 E49891AF */  sw         $s1, %gp_rel(D_006321D4)($gp)
.align 2
  .L001FC508:
    /* FC508 001FC508 2000BFDF */  ld         $ra, 0x20($sp)
    /* FC50C 001FC50C 1000B1DF */  ld         $s1, 0x10($sp)
    /* FC510 001FC510 0000B0DF */  ld         $s0, 0x0($sp)
    /* FC514 001FC514 0800E003 */  jr         $ra
    /* FC518 001FC518 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_001FC4C0
```
