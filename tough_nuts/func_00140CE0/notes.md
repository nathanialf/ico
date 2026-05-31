# func_00140CE0 — parked

VRAM: 0x00140CE0 (file_off 0x040CE0)
Asm source: asm/nonmatchings/sound/adpcm_init/func_00140CE0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (NOP,REG)

**TU:** `sound/adpcm_init.c`

**Seed:** `tough_nuts/func_00140CE0/func_00140CE0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CB8, 1
.extern D_00633CB0, 1

.align 3
nonmatching func_00140CE0, 0x74

glabel func_00140CE0
    /* 40CE0 00140CE0 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 40CE4 00140CE4 C8B38427 */  .4byte 0x2784B3C8  /* la $4, (D_00633CB8) */ /* gp_rel: (D_00633CB8) */
    /* 40CE8 00140CE8 0000BFFF */  sd         $31, 0x0($29)
    /* 40CEC 00140CEC 2D280000 */  daddu      $5, $0, $0
    /* 40CF0 00140CF0 2D308000 */  daddu      $6, $4, $0
    /* 40CF4 00140CF4 00000000 */  nop
.align 2
  .L00140CF8:
    /* 40CF8 00140CF8 0000828C */  lw         $2, 0x0($4)
    /* 40CFC 00140CFC 0B004010 */  beqz       $2, .L00140D2C
    /* 40D00 00140D00 2D18C000 */   daddu     $3, $6, $0
    /* 40D04 00140D04 0100A524 */  addiu      $5, $5, 0x1
    /* 40D08 00140D08 04006624 */  addiu      $6, $3, 0x4
    /* 40D0C 00140D0C 0200A228 */  slti       $2, $5, 0x2
    /* 40D10 00140D10 F9FF4014 */  bnez       $2, .L00140CF8
    /* 40D14 00140D14 04008424 */   addiu     $4, $4, 0x4
    /* 40D18 00140D18 5500043C */  lui        $4, %hi(D_00557B90)
    /* 40D1C 00140D1C 8A9B060C */  jal        func_001A6E28
    /* 40D20 00140D20 907B8424 */   addiu     $4, $4, %lo(D_00557B90)
    /* 40D24 00140D24 08000010 */  b          .L00140D48
    /* 40D28 00140D28 2D100000 */   daddu     $2, $0, $0
.align 2
  .L00140D2C:
    /* 40D2C 00140D2C 0500023C */  lui        $2, (0x5C000 >> 16)
    /* 40D30 00140D30 C0B3838F */  lw         $3, (D_00633CB0) /* gp_rel: (D_00633CB0) */
    /* 40D34 00140D34 00C04234 */  ori        $2, $2, (0x5C000 & 0xFFFF)
    /* 40D38 00140D38 01000424 */  addiu      $4, $0, 0x1
    /* 40D3C 00140D3C 1810A200 */  mult       $2, $5, $2
    /* 40D40 00140D40 0000C4AC */  sw         $4, 0x0($6)
    /* 40D44 00140D44 21106200 */  addu       $2, $3, $2
.align 2
  .L00140D48:
    /* 40D48 00140D48 0000BFDF */  ld         $31, 0x0($29)
    /* 40D4C 00140D4C 0800E003 */  jr         $31
    /* 40D50 00140D50 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_00140CE0
    /* 40D54 00140D54 00000000 */  nop
```
