
---

## Attempt at 2026-05-08

**Reason parked:** addr range check: ee-gcc allocates a/b to a1/a0 vs original a0/v1

Seed: `tough_nuts/func_001F1108/0F1108.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001F1108; check asm/matchings/cod/0F1108/)
```

---

## Attempt at 2026-05-13

**Reason parked:** structure mismatch: gcc emits 2-jump code vs movn-based form

Seed: `tough_nuts/func_001F1108/0F1108.c.new`

Disassembly excerpt:

```
glabel func_001F1108
    /* F1108 001F1108 28AE848F */  lw         $a0, %gp_rel(D_00633718)($gp)
    /* F110C 001F110C 2CAE838F */  lw         $v1, %gp_rel(D_0063371C)($gp)
    /* F1110 001F1110 2B106400 */  sltu       $v0, $v1, $a0
    /* F1114 001F1114 05004010 */  beqz       $v0, .L001F112C
    /* F1118 001F1118 00108524 */   addiu     $a1, $a0, 0x1000
    /* F111C 001F111C 0200023C */  lui        $v0, (0x28000 >> 16)
    /* F1120 001F1120 00804234 */  ori        $v0, $v0, (0x28000 & 0xFFFF)
    /* F1124 001F1124 21186200 */  addu       $v1, $v1, $v0
    /* F1128 001F1128 2B106400 */  sltu       $v0, $v1, $a0
.align 2
  .L001F112C:
    /* F112C 001F112C 03004014 */  bnez       $v0, .L001F113C
    /* F1130 001F1130 01000424 */   addiu     $a0, $zero, 0x1
    /* F1134 001F1134 2A106500 */  slt        $v0, $v1, $a1
    /* F1138 001F1138 0B200200 */  movn       $a0, $zero, $v0
.align 2
  .L001F113C:
    /* F113C 001F113C 0800E003 */  jr         $ra
    /* F1140 001F1140 2D108000 */   daddu     $v0, $a0, $zero
endlabel func_001F1108
```
