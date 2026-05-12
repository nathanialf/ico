
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc emits two jr ra (size 0x28) but expected single merged jr ra (size 0x24)

Seed: `tough_nuts/func_00154420/054420.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00154420; check asm/matchings/cod/054420/)
```

---

## Attempt at 2026-05-08

**Reason parked:** early-exit chain: ee-gcc converts to movn idiom; original uses beqz+single jr ra fall-through

Seed: `tough_nuts/func_00154420/054420.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00154420; check asm/matchings/cod/054420/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss regalloc + branch structure: built loads chain via v0/v1, expected via v1/a0; built emits early-return path with bne+sltiu+jr+addiu, expected has beq+addiu+sltiu+jr layout

Seed: `tough_nuts/func_00154420/054420.c.new`

Disassembly excerpt:

```
glabel func_00154420
    /* 54420 00154420 F491838F */  lw         $v1, %gp_rel(D_00631AE4)($gp)
    /* 54424 00154424 6401648C */  lw         $a0, 0x164($v1)
    /* 54428 00154428 3000848C */  lw         $a0, 0x30($a0)
    /* 5442C 0015442C 5D00832C */  sltiu      $v1, $a0, 0x5D
    /* 54430 00154430 02006010 */  beqz       $v1, .L0015443C
    /* 54434 00154434 01000224 */   addiu     $v0, $zero, 0x1
    /* 54438 00154438 5B00822C */  sltiu      $v0, $a0, 0x5B
.align 2
  .L0015443C:
    /* 5443C 0015443C 0800E003 */  jr         $ra
    /* 54440 00154440 00000000 */   nop
endlabel func_00154420
```

---

## Attempt at 2026-05-12

**Reason parked:** regalloc: built uses v0/v1 for ptr chain, expected uses v1/a0; also sltiu pulled into jr delay slot

Seed: `tough_nuts/func_00154420/054420.c.new`

Disassembly excerpt:

```
glabel func_00154420
    /* 54420 00154420 F491838F */  lw         $v1, %gp_rel(D_00631AE4)($gp)
    /* 54424 00154424 6401648C */  lw         $a0, 0x164($v1)
    /* 54428 00154428 3000848C */  lw         $a0, 0x30($a0)
    /* 5442C 0015442C 5D00832C */  sltiu      $v1, $a0, 0x5D
    /* 54430 00154430 02006010 */  beqz       $v1, .L0015443C
    /* 54434 00154434 01000224 */   addiu     $v0, $zero, 0x1
    /* 54438 00154438 5B00822C */  sltiu      $v0, $a0, 0x5B
.align 2
  .L0015443C:
    /* 5443C 0015443C 0800E003 */  jr         $ra
    /* 54440 00154440 00000000 */   nop
endlabel func_00154420
```

---

## Attempt at 2026-05-12

**Reason parked:** ee-gcc emits movn (sltu+sltiu+movn) instead of target's beq+sltiu+jr; conditional-move folding can't be prevented

Seed: `tough_nuts/func_00154420/054420.c.new`

Disassembly excerpt:

```
glabel func_00154420
    /* 54420 00154420 F491838F */  lw         $v1, %gp_rel(D_00631AE4)($gp)
    /* 54424 00154424 6401648C */  lw         $a0, 0x164($v1)
    /* 54428 00154428 3000848C */  lw         $a0, 0x30($a0)
    /* 5442C 0015442C 5D00832C */  sltiu      $v1, $a0, 0x5D
    /* 54430 00154430 02006010 */  beqz       $v1, .L0015443C
    /* 54434 00154434 01000224 */   addiu     $v0, $zero, 0x1
    /* 54438 00154438 5B00822C */  sltiu      $v0, $a0, 0x5B
.align 2
  .L0015443C:
    /* 5443C 0015443C 0800E003 */  jr         $ra
    /* 54440 00154440 00000000 */   nop
endlabel func_00154420
```
