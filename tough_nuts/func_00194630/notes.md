
---

## Attempt at 2026-05-09

**Reason parked:** byte-diffs:6

Seed: `tough_nuts/func_00194630/094630.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00194630; check asm/matchings/cod/094630/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss schedule: sd ra/daddu a0 placement — expected before sw zero,4(sp); built after

Seed: `tough_nuts/func_00194630/094630.c.new`

Disassembly excerpt:

```
glabel func_00194630
    /* 94630 00194630 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 94634 00194634 2D108000 */  daddu      $v0, $a0, $zero
    /* 94638 00194638 1000BFFF */  sd         $ra, 0x10($sp)
    /* 9463C 0019463C 2D20A003 */  daddu      $a0, $sp, $zero
    /* 94640 00194640 0400A0AF */  sw         $zero, 0x4($sp)
    /* 94644 00194644 2D28A003 */  daddu      $a1, $sp, $zero
    /* 94648 00194648 080040C4 */  lwc1       $f0, 0x8($v0)
    /* 9464C 0019464C 000041C4 */  lwc1       $f1, 0x0($v0)
    /* 94650 00194650 0800A0E7 */  swc1       $f0, 0x8($sp)
    /* 94654 00194654 5E0E090C */  jal        func_00243978
    /* 94658 00194658 0000A1E7 */   swc1      $f1, 0x0($sp)
    /* 9465C 0019465C 0000ACC7 */  lwc1       $f12, 0x0($sp)
    /* 94660 00194660 7679090C */  jal        func_0025E5D8
    /* 94664 00194664 0800ADC7 */   lwc1      $f13, 0x8($sp)
    /* 94668 00194668 1000BFDF */  ld         $ra, 0x10($sp)
    /* 9466C 0019466C 0800E003 */  jr         $ra
    /* 94670 00194670 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00194630
```
