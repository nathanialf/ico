
---

## Attempt at 2026-05-12

**Reason parked:** bc1f vs bc1fl differences; v0/v1 reg for ret value differs

Seed: `tough_nuts/func_0023C5F0/13C5F0.c`

Disassembly excerpt:

```
glabel func_0023C5F0
    /* 13C5F0 0023C5F0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 13C5F4 0023C5F4 0000B0FF */  sd         $s0, 0x0($sp)
    /* 13C5F8 0023C5F8 1000BFFF */  sd         $ra, 0x10($sp)
    /* 13C5FC 0023C5FC D833060C */  jal        func_0018CF60
    /* 13C600 0023C600 2D808000 */   daddu     $s0, $a0, $zero
    /* 13C604 0023C604 9643013C */  lui        $at, (0x43960000 >> 16)
    /* 13C608 0023C608 00088144 */  mtc1       $at, $f1
    /* 13C60C 0023C60C 000040C4 */  lwc1       $f0, 0x0($v0)
    /* 13C610 0023C610 34000146 */  c.lt.s     $f0, $f1
    /* 13C614 0023C614 00000000 */  nop
    /* 13C618 0023C618 0C000245 */  bc1fl      .L0023C64C
    /* 13C61C 0023C61C 2D100000 */   daddu     $v0, $zero, $zero
    /* 13C620 0023C620 080041C4 */  lwc1       $f1, 0x8($v0)
    /* 13C624 0023C624 5444013C */  lui        $at, (0x44540000 >> 16)
    /* 13C628 0023C628 00008144 */  mtc1       $at, $f0
    /* 13C62C 0023C62C 34000146 */  c.lt.s     $f0, $f1
    /* 13C630 0023C630 00000000 */  nop
    /* 13C634 0023C634 05000045 */  bc1f       .L0023C64C
    /* 13C638 0023C638 2D100000 */   daddu     $v0, $zero, $zero
    /* 13C63C 0023C63C CAED080C */  jal        func_0023B728
    /* 13C640 0023C640 2D200002 */   daddu     $a0, $s0, $zero
    /* 13C644 0023C644 02000010 */  b          .L0023C650
    /* 13C648 0023C648 1000BFDF */   ld        $ra, 0x10($sp)
.align 2
  .L0023C64C:
    /* 13C64C 0023C64C 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L0023C650:
    /* 13C650 0023C650 0000B0DF */  ld         $s0, 0x0($sp)
    /* 13C654 0023C654 0800E003 */  jr         $ra
    /* 13C658 0023C658 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0023C5F0
```
