
---

## Attempt at 2026-05-12

**Reason parked:** byte-clear loop with reload: gcc emits double blez (hoisted check)

Seed: `tough_nuts/func_00109E48/009E48.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00109E48; check asm/matchings/cod/009E48/)
```

---

## Attempt at 2026-05-12

**Reason parked:** byte-clear loop: instruction sequence matches but i=0 in blez delay vs before lw count; scheduler stubborn

Seed: `tough_nuts/func_00109E48/009E48.c.new`

Disassembly excerpt:

```
glabel func_00109E48
    /* 9E48 00109E48 5C01838C */  lw         $v1, 0x15C($a0)
    /* 9E4C 00109E4C 2D280000 */  daddu      $a1, $zero, $zero
    /* 9E50 00109E50 8800628C */  lw         $v0, 0x88($v1)
    /* 9E54 00109E54 0A004018 */  blez       $v0, .L00109E80
    /* 9E58 00109E58 F007668C */   lw        $a2, 0x7F0($v1)
    /* 9E5C 00109E5C 00000000 */  nop
.align 2
  .L00109E60:
    /* 9E60 00109E60 2110C500 */  addu       $v0, $a2, $a1
    /* 9E64 00109E64 000040A0 */  sb         $zero, 0x0($v0)
    /* 9E68 00109E68 0100A524 */  addiu      $a1, $a1, 0x1
    /* 9E6C 00109E6C 5C01838C */  lw         $v1, 0x15C($a0)
    /* 9E70 00109E70 8800628C */  lw         $v0, 0x88($v1)
    /* 9E74 00109E74 2A10A200 */  slt        $v0, $a1, $v0
    /* 9E78 00109E78 F9FF4014 */  bnez       $v0, .L00109E60
    /* 9E7C 00109E7C 00000000 */   nop
.align 2
  .L00109E80:
    /* 9E80 00109E80 0800E003 */  jr         $ra
    /* 9E84 00109E84 00000000 */   nop
endlabel func_00109E48
```

---

## Attempt at 2026-05-13

**Reason parked:** 1-insn diff: gcc places move $5,$0 in blez delay slot but expected has it before lw count

Seed: `tough_nuts/func_00109E48/009E48.c.new`

Disassembly excerpt:

```
glabel func_00109E48
    /* 9E48 00109E48 5C01838C */  lw         $v1, 0x15C($a0)
    /* 9E4C 00109E4C 2D280000 */  daddu      $a1, $zero, $zero
    /* 9E50 00109E50 8800628C */  lw         $v0, 0x88($v1)
    /* 9E54 00109E54 0A004018 */  blez       $v0, .L00109E80
    /* 9E58 00109E58 F007668C */   lw        $a2, 0x7F0($v1)
    /* 9E5C 00109E5C 00000000 */  nop
.align 2
  .L00109E60:
    /* 9E60 00109E60 2110C500 */  addu       $v0, $a2, $a1
    /* 9E64 00109E64 000040A0 */  sb         $zero, 0x0($v0)
    /* 9E68 00109E68 0100A524 */  addiu      $a1, $a1, 0x1
    /* 9E6C 00109E6C 5C01838C */  lw         $v1, 0x15C($a0)
    /* 9E70 00109E70 8800628C */  lw         $v0, 0x88($v1)
    /* 9E74 00109E74 2A10A200 */  slt        $v0, $a1, $v0
    /* 9E78 00109E78 F9FF4014 */  bnez       $v0, .L00109E60
    /* 9E7C 00109E7C 00000000 */   nop
.align 2
  .L00109E80:
    /* 9E80 00109E80 0800E003 */  jr         $ra
    /* 9E84 00109E84 00000000 */   nop
endlabel func_00109E48
```

---

## Attempt at 2026-05-31

**Reason parked:** remove-all-postprocesses: park to asm (ROM bytes); retires its emission postprocess

Seed: `tough_nuts/func_00109E48/009E48.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00109E48; check asm/matchings/cod/009E48/)
```
