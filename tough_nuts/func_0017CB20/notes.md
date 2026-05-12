
---

## Attempt at 2026-05-08

**Reason parked:** near-miss: gas pulls daddu $a1,$sp into jal delay slot instead of sw zero,4($sp); 1-instr scheduling diff

Seed: `tough_nuts/func_0017CB20/07CB20.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017CB20; check asm/matchings/cod/07CB20/)
```

---

## Attempt at 2026-05-08

**Reason parked:** buf-pack 2-call: ee-gcc swaps daddu a1 vs sw zero in jal delay slot vs original

Seed: `tough_nuts/func_0017CB20/07CB20.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0017CB20; check asm/matchings/cod/07CB20/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss schedule: built puts daddu a1,sp in jr delay; expected has a1=sp before jal with sw zero in delay

Seed: `tough_nuts/func_0017CB20/07CB20.c.new`

Disassembly excerpt:

```
glabel func_0017CB20
    /* 7CB20 0017CB20 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* 7CB24 0017CB24 1000B0FF */  sd         $s0, 0x10($sp)
    /* 7CB28 0017CB28 2000BFFF */  sd         $ra, 0x20($sp)
    /* 7CB2C 0017CB2C 62F8050C */  jal        func_0017E188
    /* 7CB30 0017CB30 2D80A000 */   daddu     $s0, $a1, $zero
    /* 7CB34 0017CB34 05004010 */  beqz       $v0, .L0017CB4C
    /* 7CB38 0017CB38 2D200002 */   daddu     $a0, $s0, $zero
    /* 7CB3C 0017CB3C 0000A2AF */  sw         $v0, 0x0($sp)
    /* 7CB40 0017CB40 2D28A003 */  daddu      $a1, $sp, $zero
    /* 7CB44 0017CB44 1CAB040C */  jal        func_0012AC70
    /* 7CB48 0017CB48 0400A0AF */   sw        $zero, 0x4($sp)
.align 2
  .L0017CB4C:
    /* 7CB4C 0017CB4C 2000BFDF */  ld         $ra, 0x20($sp)
    /* 7CB50 0017CB50 1000B0DF */  ld         $s0, 0x10($sp)
    /* 7CB54 0017CB54 0800E003 */  jr         $ra
    /* 7CB58 0017CB58 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_0017CB20
```

---

## Attempt at 2026-05-12

**Reason parked:** buf store order: built moves sw zero,4 before jal; target has sw zero,4 in jal delay

Seed: `tough_nuts/func_0017CB20/07CB20.c.new`

Disassembly excerpt:

```
glabel func_0017CB20
    /* 7CB20 0017CB20 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* 7CB24 0017CB24 1000B0FF */  sd         $s0, 0x10($sp)
    /* 7CB28 0017CB28 2000BFFF */  sd         $ra, 0x20($sp)
    /* 7CB2C 0017CB2C 62F8050C */  jal        func_0017E188
    /* 7CB30 0017CB30 2D80A000 */   daddu     $s0, $a1, $zero
    /* 7CB34 0017CB34 05004010 */  beqz       $v0, .L0017CB4C
    /* 7CB38 0017CB38 2D200002 */   daddu     $a0, $s0, $zero
    /* 7CB3C 0017CB3C 0000A2AF */  sw         $v0, 0x0($sp)
    /* 7CB40 0017CB40 2D28A003 */  daddu      $a1, $sp, $zero
    /* 7CB44 0017CB44 1CAB040C */  jal        func_0012AC70
    /* 7CB48 0017CB48 0400A0AF */   sw        $zero, 0x4($sp)
.align 2
  .L0017CB4C:
    /* 7CB4C 0017CB4C 2000BFDF */  ld         $ra, 0x20($sp)
    /* 7CB50 0017CB50 1000B0DF */  ld         $s0, 0x10($sp)
    /* 7CB54 0017CB54 0800E003 */  jr         $ra
    /* 7CB58 0017CB58 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_0017CB20
```
