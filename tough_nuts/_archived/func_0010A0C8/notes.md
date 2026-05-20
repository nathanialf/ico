
---

## Attempt at 2026-05-08

**Reason parked:** header check + float copy: ee-gcc 23 insns; original 22 (likely beqz redundancy)

Seed: `tough_nuts/func_0010A0C8/00A0C8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0010A0C8; check asm/matchings/cod/00A0C8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** bnel vs beq for n check; gcc picks branch-likely

Seed: `tough_nuts/func_0010A0C8/00A0C8.c.new`

Disassembly excerpt:

```
glabel func_0010A0C8
    /* A0C8 0010A0C8 0100A280 */  lb         $v0, 0x1($a1)
    /* A0CC 0010A0CC 11004014 */  bnez       $v0, .L0010A114
    /* A0D0 0010A0D0 00000000 */   nop
    /* A0D4 0010A0D4 0300A390 */  lbu        $v1, 0x3($a1)
    /* A0D8 0010A0D8 0E006010 */  beqz       $v1, .L0010A114
    /* A0DC 0010A0DC 0200A290 */   lbu       $v0, 0x2($a1)
    /* A0E0 0010A0E0 C0100200 */  sll        $v0, $v0, 3
    /* A0E4 0010A0E4 10004224 */  addiu      $v0, $v0, 0x10
    /* A0E8 0010A0E8 08006010 */  beqz       $v1, .L0010A10C
    /* A0EC 0010A0EC 2110A200 */   addu      $v0, $a1, $v0
.align 2
  .L0010A0F0:
    /* A0F0 0010A0F0 000040C4 */  lwc1       $f0, 0x0($v0)
    /* A0F4 0010A0F4 FFFF6324 */  addiu      $v1, $v1, -0x1
    /* A0F8 0010A0F8 04004224 */  addiu      $v0, $v0, 0x4
    /* A0FC 0010A0FC 000080E4 */  swc1       $f0, 0x0($a0)
    /* A100 0010A100 04008424 */  addiu      $a0, $a0, 0x4
    /* A104 0010A104 FAFF6014 */  bnez       $v1, .L0010A0F0
    /* A108 0010A108 00000000 */   nop
.align 2
  .L0010A10C:
    /* A10C 0010A10C 0800E003 */  jr         $ra
    /* A110 0010A110 01000224 */   addiu     $v0, $zero, 0x1
.align 2
  .L0010A114:
    /* A114 0010A114 0800E003 */  jr         $ra
    /* A118 0010A118 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0010A0C8
```
