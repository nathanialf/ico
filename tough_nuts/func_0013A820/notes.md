# func_0013A820 — parked

VRAM: 0x0013A820 (file_off 0x03A820)
Asm source: asm/matchings/ios/pad/func_0013A820.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (REG)

**TU:** `ios/pad.c`

**Seed:** `tough_nuts/func_0013A820/func_0013A820.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632108, 1
.extern D_00631950, 1

.align 3
nonmatching func_0013A820, 0x48

glabel func_0013A820
    /* 3A820 0013A820 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 3A824 0013A824 02000224 */  addiu      $2, $0, 0x2
    /* 3A828 0013A828 0B008214 */  bne        $4, $2, .L0013A858
    /* 3A82C 0013A82C 0000BFFF */   sd        $31, 0x0($29)
    /* 3A830 0013A830 0012023C */  lui        $2, (0x12001000 >> 16)
    /* 3A834 0013A834 1898858F */  lw         $5, %gp_rel(D_00632108)($gp) /* gp_rel: (D_00632108) */
    /* 3A838 0013A838 00104234 */  ori        $2, $2, (0x12001000 & 0xFFFF)
    /* 3A83C 0013A83C 000043DC */  ld         $3, 0x0($2)
    /* 3A840 0013A840 3000A48C */  lw         $4, 0x30($5)
    /* 3A844 0013A844 7A1B0300 */  dsrl       $3, $3, 13
    /* 3A848 0013A848 01006330 */  andi       $3, $3, 0x1
    /* 3A84C 0013A84C 01006338 */  xori       $3, $3, 0x1
    /* 3A850 0013A850 C603040C */  jal        func_00100F18
    /* 3A854 0013A854 609083AF */   sw        $3, %gp_rel(D_00631950)($gp) /* gp_rel: (D_00631950) */
.align 2
  .L0013A858:
    /* 3A858 0013A858 0000BFDF */  ld         $31, 0x0($29)
    /* 3A85C 0013A85C 2D100000 */  daddu      $2, $0, $0
    /* 3A860 0013A860 0800E003 */  jr         $31
    /* 3A864 0013A864 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0013A820
```
