# func_00104638 — parked

VRAM: 0x00104638 (file_off 0x004638)
Asm source: asm/matchings/src/geometryManager/func_00104638.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (MEM_BARRIER,REG)

**TU:** `src/geometryManager.c`

**Seed:** `tough_nuts/func_00104638/func_00104638.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00630908, 1
.extern D_00630904, 1

.align 3
nonmatching func_00104638, 0x60

glabel func_00104638
    /* 4638 00104638 148082C7 */  lwc1       $f2, (D_00630904) /* gp_rel: (D_00630904) */
    /* 463C 0010463C 2D100000 */  daddu      $2, $0, $0
    /* 4640 00104640 02000324 */  addiu      $3, $0, 0x2
    /* 4644 00104644 00000000 */  nop
.align 2
  .L00104648:
    /* 4648 00104648 000080C4 */  lwc1       $f0, 0x0($4)
    /* 464C 0010464C 34000246 */  c.lt.s     $f0, $f2
    /* 4650 00104650 03000045 */  bc1f       .L00104660
    /* 4654 00104654 00000000 */   nop
    /* 4658 00104658 07000010 */  b          .L00104678
    /* 465C 0010465C 000082E4 */   swc1      $f2, 0x0($4)
.align 2
  .L00104660:
    /* 4660 00104660 188081C7 */  lwc1       $f1, (D_00630908) /* gp_rel: (D_00630908) */
    /* 4664 00104664 34080046 */  c.lt.s     $f1, $f0
    /* 4668 00104668 00000000 */  nop
    /* 466C 0010466C 05000245 */  bc1fl      .L00104684
    /* 4670 00104670 0400A524 */   addiu     $5, $5, 0x4
    /* 4674 00104674 000081E4 */  swc1       $f1, 0x0($4)
.align 2
  .L00104678:
    /* 4678 00104678 01000224 */  addiu      $2, $0, 0x1
    /* 467C 0010467C 0000A0AC */  sw         $0, 0x0($5)
    /* 4680 00104680 0400A524 */  addiu      $5, $5, 0x4
.align 2
  .L00104684:
    /* 4684 00104684 FFFF6324 */  addiu      $3, $3, -0x1
    /* 4688 00104688 EFFF6104 */  bgez       $3, .L00104648
    /* 468C 0010468C 04008424 */   addiu     $4, $4, 0x4
    /* 4690 00104690 0800E003 */  jr         $31
    /* 4694 00104694 00000000 */   nop
endlabel func_00104638
```
