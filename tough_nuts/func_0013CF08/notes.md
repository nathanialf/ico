
---

## Attempt at 2026-05-08

**Reason parked:** bound-checked array store: ee-gcc emits unsigned -1 via lui+ori (2 insns) instead of addiu -1 (1 insn); also bnel vs beq direction

Seed: `tough_nuts/func_0013CF08/03CF08.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013CF08; check asm/matchings/cod/03CF08/)
```

---

## Attempt at 2026-05-08

**Reason parked:** bounded array store: ee-gcc emits beqz+regular shape; original uses bnel branch-likely

Seed: `tough_nuts/func_0013CF08/03CF08.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013CF08; check asm/matchings/cod/03CF08/)
```

---

## Attempt at 2026-05-12

**Reason parked:** bnel branch-likely vs beq; shadow copy daddu a2,a0,0 added by gcc

Seed: `tough_nuts/func_0013CF08/03CF08.c.new`

Disassembly excerpt:

```
glabel func_0013CF08
    /* 3CF08 0013CF08 A098838F */  lw         $v1, %gp_rel(D_00632190)($gp)
    /* 3CF0C 0013CF0C 0000628C */  lw         $v0, 0x0($v1)
    /* 3CF10 0013CF10 2B108200 */  sltu       $v0, $a0, $v0
    /* 3CF14 0013CF14 03004054 */  bnel       $v0, $zero, .L0013CF24
    /* 3CF18 0013CF18 0400638C */   lw        $v1, 0x4($v1)
    /* 3CF1C 0013CF1C 04000010 */  b          .L0013CF30
    /* 3CF20 0013CF20 FFFF0424 */   addiu     $a0, $zero, -0x1
.align 2
  .L0013CF24:
    /* 3CF24 0013CF24 80100400 */  sll        $v0, $a0, 2
    /* 3CF28 0013CF28 21104300 */  addu       $v0, $v0, $v1
    /* 3CF2C 0013CF2C 000045AC */  sw         $a1, 0x0($v0)
.align 2
  .L0013CF30:
    /* 3CF30 0013CF30 0800E003 */  jr         $ra
    /* 3CF34 0013CF34 2D108000 */   daddu     $v0, $a0, $zero
endlabel func_0013CF08
```
