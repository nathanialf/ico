
---

## Attempt at 2026-05-08

**Reason parked:** alloc-by-idx wrapper: ee-gcc emits clean stores via v0; original chains daddu a2->a0->v0 for stores at _10/_8/_C in different order

Seed: `tough_nuts/func_001E8B68/0E8B68.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001E8B68; check asm/matchings/cod/0E8B68/)
```

---

## Attempt at 2026-05-13

**Reason parked:** expected uses a2 for e + extra copies (a0,v0); mine uses a3 directly

Seed: `tough_nuts/func_001E8B68/0E8B68.c.new`

Disassembly excerpt:

```
glabel func_001E8B68
    /* E8B68 001E8B68 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* E8B6C 001E8B6C 3897878F */  lw         $a3, %gp_rel(D_00632028)($gp)
    /* E8B70 001E8B70 1000B1FF */  sd         $s1, 0x10($sp)
    /* E8B74 001E8B74 0000B0FF */  sd         $s0, 0x0($sp)
    /* E8B78 001E8B78 2D88C000 */  daddu      $s1, $a2, $zero
    /* E8B7C 001E8B7C 2000BFFF */  sd         $ra, 0x20($sp)
    /* E8B80 001E8B80 FEA0070C */  jal        func_001E83F8
    /* E8B84 001E8B84 2D80A000 */   daddu     $s0, $a1, $zero
    /* E8B88 001E8B88 2D384000 */  daddu      $a3, $v0, $zero
    /* E8B8C 001E8B8C FFFF0224 */  addiu      $v0, $zero, -0x1
    /* E8B90 001E8B90 0B00E210 */  beq        $a3, $v0, .L001E8BC0
    /* E8B94 001E8B94 18000324 */   addiu     $v1, $zero, 0x18
    /* E8B98 001E8B98 7100023C */  lui        $v0, %hi(D_007097F0)
    /* E8B9C 001E8B9C 1818E300 */  mult       $v1, $a3, $v1
    /* E8BA0 001E8BA0 F0974224 */  addiu      $v0, $v0, %lo(D_007097F0)
    /* E8BA4 001E8BA4 01000524 */  addiu      $a1, $zero, 0x1
    /* E8BA8 001E8BA8 21304300 */  addu       $a2, $v0, $v1
    /* E8BAC 001E8BAC 2D20C000 */  daddu      $a0, $a2, $zero
    /* E8BB0 001E8BB0 1000D1AC */  sw         $s1, 0x10($a2)
    /* E8BB4 001E8BB4 2D108000 */  daddu      $v0, $a0, $zero
    /* E8BB8 001E8BB8 080085AC */  sw         $a1, 0x8($a0)
    /* E8BBC 001E8BBC 0C0050AC */  sw         $s0, 0xC($v0)
.align 2
  .L001E8BC0:
    /* E8BC0 001E8BC0 2000BFDF */  ld         $ra, 0x20($sp)
    /* E8BC4 001E8BC4 2D10E000 */  daddu      $v0, $a3, $zero
    /* E8BC8 001E8BC8 1000B1DF */  ld         $s1, 0x10($sp)
    /* E8BCC 001E8BCC 0000B0DF */  ld         $s0, 0x0($sp)
    /* E8BD0 001E8BD0 0800E003 */  jr         $ra
    /* E8BD4 001E8BD4 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_001E8B68
```
