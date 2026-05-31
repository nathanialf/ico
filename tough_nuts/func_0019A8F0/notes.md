# func_0019A8F0 — parked

VRAM: 0x0019A8F0 (file_off 0x09A8F0)
Asm source: asm/matchings/src/queen/func_0019A8F0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE_FP2,NOREORDER_BARRIER)

**TU:** `src/queen.c`

**Seed:** `tough_nuts/func_0019A8F0/func_0019A8F0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_0063106C, 1
.extern D_00631070, 1
.extern D_00631074, 1
.extern D_00633DD8, 1

.align 3
nonmatching func_0019A8F0, 0xB0

glabel func_0019A8F0
    /* 9A8F0 0019A8F0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 9A8F4 0019A8F4 2700033C */  lui        $3, %hi(D_00274ED4)
    /* 9A8F8 0019A8F8 1000B1FF */  sd         $17, 0x10($29)
    /* 9A8FC 0019A8FC D44E628C */  lw         $2, %lo(D_00274ED4)($3)
    /* 9A900 0019A900 2D888000 */  daddu      $17, $4, $0
    /* 9A904 0019A904 2000BFFF */  sd         $31, 0x20($29)
    /* 9A908 0019A908 04004014 */  bnez       $2, .L0019A91C
    /* 9A90C 0019A90C 0000B0FF */   sd        $16, 0x0($29)
    /* 9A910 0019A910 E8B4828F */  lw         $2, (D_00633DD8) /* gp_rel: (D_00633DD8) */
    /* 9A914 0019A914 01004224 */  addiu      $2, $2, 0x1
    /* 9A918 0019A918 E8B482AF */  sw         $2, (D_00633DD8) /* gp_rel: (D_00633DD8) */
.align 2
  .L0019A91C:
    /* 9A91C 0019A91C F28F070C */  jal        func_001E3FC8
    /* 9A920 0019A920 2D202002 */   daddu     $4, $17, $0
    /* 9A924 0019A924 2D202002 */  daddu      $4, $17, $0
    /* 9A928 0019A928 23000524 */  addiu      $5, $0, 0x23
    /* 9A92C 0019A92C 2C000624 */  addiu      $6, $0, 0x2C
    /* 9A930 0019A930 30EE060C */  jal        func_001BB8C0
    /* 9A934 0019A934 99010724 */   addiu     $7, $0, 0x199
    /* 9A938 0019A938 5C01228E */  lw         $2, 0x15C($17)
    /* 9A93C 0019A93C 0008508C */  lw         $16, 0x800($2)
    /* 9A940 0019A940 0C00038E */  lw         $3, 0xC($16)
    /* 9A944 0019A944 0B006010 */  beqz       $3, .L0019A974
    /* 9A948 0019A948 00000000 */   nop
    /* 9A94C 0019A94C 4040013C */  lui        $1, (0x40400000 >> 16)
    /* 9A950 0019A950 00608144 */  mtc1       $1, $f12
    /* 9A954 0019A954 7C878DC7 */  lwc1       $f13, (D_0063106C) /* gp_rel: (D_0063106C) */
    /* 9A958 0019A958 8620070C */  jal        func_001C8218
    /* 9A95C 0019A95C 1000048E */   lw        $4, 0x10($16)
    /* 9A960 0019A960 A040013C */  lui        $1, (0x40A00000 >> 16)
    /* 9A964 0019A964 00608144 */  mtc1       $1, $f12
    /* 9A968 0019A968 80878DC7 */  lwc1       $f13, (D_00631070) /* gp_rel: (D_00631070) */
    /* 9A96C 0019A96C 8620070C */  jal        func_001C8218
    /* 9A970 0019A970 1400048E */   lw        $4, 0x14($16)
.align 2
  .L0019A974:
    /* 9A974 0019A974 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* 9A978 0019A978 00608144 */  mtc1       $1, $f12
    /* 9A97C 0019A97C 2D202002 */  daddu      $4, $17, $0
    /* 9A980 0019A980 84878EC7 */  lwc1       $f14, (D_00631074) /* gp_rel: (D_00631074) */
    /* 9A984 0019A984 01000524 */  addiu      $5, $0, 0x1
    /* 9A988 0019A988 2000BFDF */  ld         $31, 0x20($29)
    /* 9A98C 0019A98C 46630046 */  mov.s      $f13, $f12
    /* 9A990 0019A990 1000B1DF */  ld         $17, 0x10($29)
    /* 9A994 0019A994 0000B0DF */  ld         $16, 0x0($29)
    /* 9A998 0019A998 540F0408 */  j          func_00103D50
    /* 9A99C 0019A99C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0019A8F0
```
