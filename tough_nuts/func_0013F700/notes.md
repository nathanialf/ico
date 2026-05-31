# func_0013F700 — parked

VRAM: 0x0013F700 (file_off 0x03F700)
Asm source: asm/matchings/isys/gobj_process/func_0013F700.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `isys/gobj_process.c`

**Seed:** `tough_nuts/func_0013F700/func_0013F700.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632008, 1
.extern D_00633CAC, 1
.extern D_00633CA8, 1

.align 3
nonmatching func_0013F700, 0x78

glabel func_0013F700
    /* 3F700 0013F700 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 3F704 0013F704 94000524 */  addiu      $5, $0, 0x94
    /* 3F708 0013F708 0000B0FF */  sd         $16, 0x0($29)
    /* 3F70C 0013F70C 5500063C */  lui        $6, %hi(D_00557AD0)
    /* 3F710 0013F710 2D808000 */  daddu      $16, $4, $0
    /* 3F714 0013F714 1000BFFF */  sd         $31, 0x10($29)
    /* 3F718 0013F718 18000502 */  mult       $0, $16, $5
    /* 3F71C 0013F71C 1897848F */  lw         $4, %gp_rel(D_00632008)($gp) /* gp_rel: (D_00632008) */
    /* 3F720 0013F720 D07AC624 */  addiu      $6, $6, %lo(D_00557AD0)
    /* 3F724 0013F724 12280000 */  mflo       $5
    /* 3F728 0013F728 3EE8040C */  jal        func_0013A0F8
    /* 3F72C 0013F72C 49000724 */   addiu     $7, $0, 0x49
    /* 3F730 0013F730 2D284000 */  daddu      $5, $2, $0
    /* 3F734 0013F734 BCB390AF */  sw         $16, %gp_rel(D_00633CAC)($gp) /* gp_rel: (D_00633CAC) */
    /* 3F738 0013F738 B8B385AF */  sw         $5, %gp_rel(D_00633CA8)($gp) /* gp_rel: (D_00633CA8) */
    /* 3F73C 0013F73C 0A000012 */  beqz       $16, .L0013F768
    /* 3F740 0013F740 2D200000 */   daddu     $4, $0, $0
    /* 3F744 0013F744 00000000 */  nop
.align 2
  .L0013F748:
    /* 3F748 0013F748 94000224 */  addiu      $2, $0, 0x94
    /* 3F74C 0013F74C 18188200 */  mult       $3, $4, $2
    /* 3F750 0013F750 01008424 */  addiu      $4, $4, 0x1
    /* 3F754 0013F754 21106500 */  addu       $2, $3, $5
    /* 3F758 0013F758 2B189000 */  sltu       $3, $4, $16
    /* 3F75C 0013F75C 000040AC */  sw         $0, 0x0($2)
    /* 3F760 0013F760 F9FF6014 */  bnez       $3, .L0013F748
    /* 3F764 0013F764 00000000 */   nop
.align 2
  .L0013F768:
    /* 3F768 0013F768 1000BFDF */  ld         $31, 0x10($29)
    /* 3F76C 0013F76C 0000B0DF */  ld         $16, 0x0($29)
    /* 3F770 0013F770 0800E003 */  jr         $31
    /* 3F774 0013F774 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0013F700
```
