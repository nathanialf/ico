
---

## Attempt at 2026-05-12

**Reason parked:** bc1f delay slot fills with lwc1 D_006317FC; -fno-delayed-branch loses bc1fl/sub.s pairing

Seed: `tough_nuts/func_0023C2F0/13C2F0.c`

Disassembly excerpt:

```
glabel func_0023C2F0
    /* 13C2F0 0023C2F0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 13C2F4 0023C2F4 0000B0FF */  sd         $s0, 0x0($sp)
    /* 13C2F8 0023C2F8 1000BFFF */  sd         $ra, 0x10($sp)
    /* 13C2FC 0023C2FC D833060C */  jal        func_0018CF60
    /* 13C300 0023C300 2D808000 */   daddu     $s0, $a0, $zero
    /* 13C304 0023C304 080041C4 */  lwc1       $f1, 0x8($v0)
    /* 13C308 0023C308 088F82C7 */  lwc1       $f2, %gp_rel(D_006317F8)($gp)
    /* 13C30C 0023C30C 34080246 */  c.lt.s     $f1, $f2
    /* 13C310 0023C310 04000045 */  bc1f       .L0023C324
    /* 13C314 0023C314 00000000 */   nop
    /* 13C318 0023C318 00088044 */  mtc1       $zero, $f1
    /* 13C31C 0023C31C 0E000010 */  b          .L0023C358
    /* 13C320 0023C320 00000000 */   nop
.align 2
  .L0023C324:
    /* 13C324 0023C324 0C8F80C7 */  lwc1       $f0, %gp_rel(D_006317FC)($gp)
    /* 13C328 0023C328 34000146 */  c.lt.s     $f0, $f1
    /* 13C32C 0023C32C 00000000 */  nop
    /* 13C330 0023C330 05000245 */  bc1fl      .L0023C348
    /* 13C334 0023C334 41080246 */   sub.s     $f1, $f1, $f2
    /* 13C338 0023C338 803F013C */  lui        $at, (0x3F800000 >> 16)
    /* 13C33C 0023C33C 00088144 */  mtc1       $at, $f1
    /* 13C340 0023C340 05000010 */  b          .L0023C358
    /* 13C344 0023C344 00000000 */   nop
.align 2
  .L0023C348:
    /* 13C348 0023C348 108F80C7 */  lwc1       $f0, %gp_rel(D_00631800)($gp)
    /* 13C34C 0023C34C 00000000 */  nop
    /* 13C350 0023C350 00000000 */  nop
    /* 13C354 0023C354 43080046 */  div.s      $f1, $f1, $f0
.align 2
  .L0023C358:
    /* 13C358 0023C358 803F013C */  lui        $at, (0x3F800000 >> 16)
    /* 13C35C 0023C35C 00008144 */  mtc1       $at, $f0
    /* 13C360 0023C360 FFFF0224 */  addiu      $v0, $zero, -0x1
    /* 13C364 0023C364 1000BFDF */  ld         $ra, 0x10($sp)
    /* 13C368 0023C368 01000146 */  sub.s      $f0, $f0, $f1
    /* 13C36C 0023C36C 180000E6 */  swc1       $f0, 0x18($s0)
    /* 13C370 0023C370 0000B0DF */  ld         $s0, 0x0($sp)
    /* 13C374 0023C374 0800E003 */  jr         $ra
    /* 13C378 0023C378 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0023C2F0
```
