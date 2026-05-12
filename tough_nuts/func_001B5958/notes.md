
---

## Attempt at 2026-05-08

**Reason parked:** scheduling differs: target lwc1 f12 first then lw a0 in delay slot; gcc reverses to lw a0 first then lwc1 f12 in delay slot

Seed: `tough_nuts/func_001B5958/0B5958.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001B5958; check asm/matchings/cod/0B5958/)
```

---

## Attempt at 2026-05-08

**Reason parked:** if-then-call: ee-gcc reverses lw a0 / lwc1 f12 order vs original (1-byte diff in delay slot fill)

Seed: `tough_nuts/func_001B5958/0B5958.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001B5958; check asm/matchings/cod/0B5958/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss schedule: gas puts lwc1 f12 in jr-ra delay slot (built) vs lw a0 (expected). Both valid emissions, gcc 2.9 picks lw a0 first and lwc1 fills delay slot.

Seed: `tough_nuts/func_001B5958/0B5958.c.new`

Disassembly excerpt:

```
glabel func_001B5958
    /* B5958 001B5958 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* B595C 001B595C 0000BFFF */  sd         $ra, 0x0($sp)
    /* B5960 001B5960 2648060C */  jal        func_00192098
    /* B5964 001B5964 00000000 */   nop
    /* B5968 001B5968 07004014 */  bnez       $v0, .L001B5988
    /* B596C 001B596C 0000BFDF */   ld        $ra, 0x0($sp)
    /* B5970 001B5970 1C888CC7 */  lwc1       $f12, %gp_rel(D_0063110C)($gp)
    /* B5974 001B5974 8040013C */  lui        $at, (0x40800000 >> 16)
    /* B5978 001B5978 00688144 */  mtc1       $at, $f13
    /* B597C 001B597C E67F060C */  jal        func_0019FF98
    /* B5980 001B5980 54A7848F */   lw        $a0, %gp_rel(D_00633044)($gp)
    /* B5984 001B5984 0000BFDF */  ld         $ra, 0x0($sp)
.align 2
  .L001B5988:
    /* B5988 001B5988 FFFF0224 */  addiu      $v0, $zero, -0x1
    /* B598C 001B598C 0800E003 */  jr         $ra
    /* B5990 001B5990 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001B5958
```

---

## Attempt at 2026-05-12

**Reason parked:** 1-byte diff: arg setup order swapped between lwc1 f12 and lw a0 (delay slot choice)

Seed: `tough_nuts/func_001B5958/0B5958.c.new`

Disassembly excerpt:

```
glabel func_001B5958
    /* B5958 001B5958 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* B595C 001B595C 0000BFFF */  sd         $ra, 0x0($sp)
    /* B5960 001B5960 2648060C */  jal        func_00192098
    /* B5964 001B5964 00000000 */   nop
    /* B5968 001B5968 07004014 */  bnez       $v0, .L001B5988
    /* B596C 001B596C 0000BFDF */   ld        $ra, 0x0($sp)
    /* B5970 001B5970 1C888CC7 */  lwc1       $f12, %gp_rel(D_0063110C)($gp)
    /* B5974 001B5974 8040013C */  lui        $at, (0x40800000 >> 16)
    /* B5978 001B5978 00688144 */  mtc1       $at, $f13
    /* B597C 001B597C E67F060C */  jal        func_0019FF98
    /* B5980 001B5980 54A7848F */   lw        $a0, %gp_rel(D_00633044)($gp)
    /* B5984 001B5984 0000BFDF */  ld         $ra, 0x0($sp)
.align 2
  .L001B5988:
    /* B5988 001B5988 FFFF0224 */  addiu      $v0, $zero, -0x1
    /* B598C 001B598C 0800E003 */  jr         $ra
    /* B5990 001B5990 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001B5958
```
