
---

## Attempt at 2026-05-12

**Reason parked:** count-zeros loop: structural movz matches but register roles differ (a0/a1/a2 swap)

Seed: `tough_nuts/func_001CE9B8/0CE9B8.c`

Disassembly excerpt:

```
glabel func_001CE9B8
    /* CE9B8 001CE9B8 5C01828C */  lw         $v0, 0x15C($a0)
    /* CE9BC 001CE9BC 8800448C */  lw         $a0, 0x88($v0)
    /* CE9C0 001CE9C0 0C008018 */  blez       $a0, .L001CE9F4
    /* CE9C4 001CE9C4 2D280000 */   daddu     $a1, $zero, $zero
    /* CE9C8 001CE9C8 0008428C */  lw         $v0, 0x800($v0)
    /* CE9CC 001CE9CC 2D308000 */  daddu      $a2, $a0, $zero
    /* CE9D0 001CE9D0 1400448C */  lw         $a0, 0x14($v0)
    /* CE9D4 001CE9D4 00000000 */  nop
.align 2
  .L001CE9D8:
    /* CE9D8 001CE9D8 0000838C */  lw         $v1, 0x0($a0)
    /* CE9DC 001CE9DC 0100A224 */  addiu      $v0, $a1, 0x1
    /* CE9E0 001CE9E0 04008424 */  addiu      $a0, $a0, 0x4
    /* CE9E4 001CE9E4 FFFFC624 */  addiu      $a2, $a2, -0x1
    /* CE9E8 001CE9E8 0A284300 */  movz       $a1, $v0, $v1
    /* CE9EC 001CE9EC FAFFC014 */  bnez       $a2, .L001CE9D8
    /* CE9F0 001CE9F0 00000000 */   nop
.align 2
  .L001CE9F4:
    /* CE9F4 001CE9F4 0800E003 */  jr         $ra
    /* CE9F8 001CE9F8 2D10A000 */   daddu     $v0, $a1, $zero
endlabel func_001CE9B8
```
