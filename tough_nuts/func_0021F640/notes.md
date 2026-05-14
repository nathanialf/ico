
---

## Attempt at 2026-05-12

**Reason parked:** spin-wait+setbit: gcc reorders sw a0 into beq delay slot

Seed: `tough_nuts/func_0021F640/11F640.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0021F640; check asm/matchings/cod/11F640/)
```

---

## Attempt at 2026-05-14

**Reason parked:** near-miss: loop body alignment padding missing; size 0x10 less than expected

Seed: `tough_nuts/func_0021F640/11F640.c.new`

Disassembly excerpt:

```
glabel func_0021F640
    /* 11F640 0021F640 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 11F644 0021F644 1000BFFF */  sd         $ra, 0x10($sp)
    /* 11F648 0021F648 0000A4AF */  sw         $a0, 0x0($sp)
    /* 11F64C 0021F64C 04000010 */  b          .L0021F660
    /* 11F650 0021F650 00000000 */   nop
    /* 11F654 0021F654 00000000 */  nop
.align 2
  .L0021F658:
    /* 11F658 0021F658 A80E080C */  jal        func_00203AA0
    /* 11F65C 0021F65C 01000424 */   addiu     $a0, $zero, 0x1
.align 2
  .L0021F660:
    /* 11F660 0021F660 8CF4050C */  jal        func_0017D230
    /* 11F664 0021F664 54040424 */   addiu     $a0, $zero, 0x454
    /* 11F668 0021F668 FBFF4010 */  beqz       $v0, .L0021F658
    /* 11F66C 0021F66C 00000000 */   nop
    /* 11F670 0021F670 96EC050C */  jal        func_0017B258
    /* 11F674 0021F674 BA000424 */   addiu     $a0, $zero, 0xBA
    /* 11F678 0021F678 1000BFDF */  ld         $ra, 0x10($sp)
    /* 11F67C 0021F67C 0800E003 */  jr         $ra
    /* 11F680 0021F680 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0021F640
```
