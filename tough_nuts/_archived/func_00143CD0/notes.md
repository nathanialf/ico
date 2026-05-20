
---

## Attempt at 2026-05-12

**Reason parked:** linear search loop: gcc emits unsigned compare (sltu) vs expected signed (slt); also pre-loop check structure differs

Seed: `tough_nuts/func_00143CD0/043CD0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00143CD0; check asm/matchings/cod/043CD0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** search loop: target dual-tracks a1/a2 ptrs explicitly with daddu+addiu pattern; built uses bnel single ptr

Seed: `tough_nuts/func_00143CD0/043CD0.c.new`

Disassembly excerpt:

```
glabel func_00143CD0
    /* 43CD0 00143CD0 6B00023C */  lui        $v0, %hi(D_006A95B0)
    /* 43CD4 00143CD4 0000848C */  lw         $a0, 0x0($a0)
    /* 43CD8 00143CD8 B0954524 */  addiu      $a1, $v0, %lo(D_006A95B0)
    /* 43CDC 00143CDC 0003A724 */  addiu      $a3, $a1, 0x300
    /* 43CE0 00143CE0 2D30A000 */  daddu      $a2, $a1, $zero
    /* 43CE4 00143CE4 00000000 */  nop
.align 2
  .L00143CE8:
    /* 43CE8 00143CE8 0000A28C */  lw         $v0, 0x0($a1)
    /* 43CEC 00143CEC 07004410 */  beq        $v0, $a0, .L00143D0C
    /* 43CF0 00143CF0 2D18C000 */   daddu     $v1, $a2, $zero
    /* 43CF4 00143CF4 3000A524 */  addiu      $a1, $a1, 0x30
    /* 43CF8 00143CF8 2A10A700 */  slt        $v0, $a1, $a3
    /* 43CFC 00143CFC FAFF4014 */  bnez       $v0, .L00143CE8
    /* 43D00 00143D00 30006624 */   addiu     $a2, $v1, 0x30
    /* 43D04 00143D04 0800E003 */  jr         $ra
    /* 43D08 00143D08 2D100000 */   daddu     $v0, $zero, $zero
.align 2
  .L00143D0C:
    /* 43D0C 00143D0C 0800E003 */  jr         $ra
    /* 43D10 00143D10 2D10C000 */   daddu     $v0, $a2, $zero
endlabel func_00143CD0
```
