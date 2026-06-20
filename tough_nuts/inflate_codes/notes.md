# inflate_codes — parked

VRAM: 0x00132FC0 (file_off 0x032FC0)
Asm source: asm/aug6/nonmatchings/fumi/ios/inflate/inflate_codes.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=40). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/ios/inflate.c`

**Seed:** `tough_nuts/inflate_codes/inflate_codes.c`

Disassembly:

```
.align 3
nonmatching inflate_codes, 0x110

glabel inflate_codes
    /* 32FC0 00132FC0 80FFBD27 */  addiu      $29, $29, -0x80
    /* 32FC4 00132FC4 4000B4FF */  sd         $20, 0x40($29)
    /* 32FC8 00132FC8 2000B2FF */  sd         $18, 0x20($29)
    /* 32FCC 00132FCC FFFF1424 */  addiu      $20, $0, -0x1
    /* 32FD0 00132FD0 2D90C000 */  daddu      $18, $6, $0
    /* 32FD4 00132FD4 1000B1FF */  sd         $17, 0x10($29)
    /* 32FD8 00132FD8 6000B6FF */  sd         $22, 0x60($29)
    /* 32FDC 00132FDC FF075126 */  addiu      $17, $18, 0x7FF
    /* 32FE0 00132FE0 5000B5FF */  sd         $21, 0x50($29)
    /* 32FE4 00132FE4 2A109202 */  slt        $2, $20, $18
    /* 32FE8 00132FE8 3000B3FF */  sd         $19, 0x30($29)
    /* 32FEC 00132FEC 2DA8A000 */  daddu      $21, $5, $0
    /* 32FF0 00132FF0 0000B0FF */  sd         $16, 0x0($29)
    /* 32FF4 00132FF4 0B884202 */  movn       $17, $18, $2
    /* 32FF8 00132FF8 7000BFFF */  sd         $31, 0x70($29)
    /* 32FFC 00132FFC 2D808000 */  daddu      $16, $4, $0
    /* 33000 00133000 01001324 */  addiu      $19, $0, 0x1
    /* 33004 00133004 5500163C */  lui        $22, %hi(D_00550E48)
    /* 33008 00133008 1001038E */  lw         $3, 0x110($16)
    /* 3300C 0013300C 00000000 */  nop
.align 2
  .L00133010:
    /* 33010 00133010 C32A1100 */  sra        $5, $17, 11
    /* 33014 00133014 1401088E */  lw         $8, 0x114($16)
    /* 33018 00133018 2D30A002 */  daddu      $6, $21, $0
    /* 3301C 0013301C FF076424 */  addiu      $4, $3, 0x7FF
    /* 33020 00133020 2A108302 */  slt        $2, $20, $3
    /* 33024 00133024 0B206200 */  movn       $4, $3, $2
    /* 33028 00133028 78968727 */  addiu      $7, $28, %gp_rel(D_0062A268)
    /* 3302C 0013302C C3220400 */  sra        $4, $4, 11
    /* 33030 00133030 3826090C */  jal        func_002498E0
    /* 33034 00133034 21200401 */   addu      $4, $8, $4
    /* 33038 00133038 04000010 */  b          .L0013304C
    /* 3303C 0013303C 00000000 */   nop
.align 2
  .L00133040:
    /* 33040 00133040 B6F3040C */  jal        iosSemaCreate
    /* 33044 00133044 689693AF */   sw        $19, %gp_rel(D_0062A258)($28)
    /* 33048 00133048 689680AF */  sw         $0, %gp_rel(D_0062A258)($28)
.align 2
  .L0013304C:
    /* 3304C 0013304C 3024090C */  jal        func_002490C0
    /* 33050 00133050 01000424 */   addiu     $4, $0, 0x1
    /* 33054 00133054 FAFF4014 */  bnez       $2, .L00133040
    /* 33058 00133058 00000000 */   nop
    /* 3305C 0013305C 2C27090C */  jal        func_00249CB0
    /* 33060 00133060 00000000 */   nop
    /* 33064 00133064 2D284000 */  daddu      $5, $2, $0
    /* 33068 00133068 0A00A050 */  beql       $5, $0, .L00133094
    /* 3306C 0013306C 1001038E */   lw        $3, 0x110($16)
    /* 33070 00133070 0801028E */  lw         $2, 0x108($16)
    /* 33074 00133074 02110200 */  srl        $2, $2, 4
    /* 33078 00133078 01004230 */  andi       $2, $2, 0x1
    /* 3307C 0013307C 05004054 */  bnel       $2, $0, .L00133094
    /* 33080 00133080 1001038E */   lw        $3, 0x110($16)
    /* 33084 00133084 F290060C */  jal        debug_assertMessage
    /* 33088 00133088 480EC426 */   addiu     $4, $22, %lo(D_00550E48)
    /* 3308C 0013308C E0FF0010 */  b          .L00133010
    /* 33090 00133090 1001038E */   lw        $3, 0x110($16)
.align 2
  .L00133094:
    /* 33094 00133094 0C01028E */  lw         $2, 0x10C($16)
    /* 33098 00133098 21187200 */  addu       $3, $3, $18
    /* 3309C 0013309C 7000BFDF */  ld         $31, 0x70($29)
    /* 330A0 001330A0 100103AE */  sw         $3, 0x110($16)
    /* 330A4 001330A4 2A106200 */  slt        $2, $3, $2
    /* 330A8 001330A8 6000B6DF */  ld         $22, 0x60($29)
    /* 330AC 001330AC 01004238 */  xori       $2, $2, 0x1
    /* 330B0 001330B0 5000B5DF */  ld         $21, 0x50($29)
    /* 330B4 001330B4 4000B4DF */  ld         $20, 0x40($29)
    /* 330B8 001330B8 3000B3DF */  ld         $19, 0x30($29)
    /* 330BC 001330BC 2000B2DF */  ld         $18, 0x20($29)
    /* 330C0 001330C0 1000B1DF */  ld         $17, 0x10($29)
    /* 330C4 001330C4 0000B0DF */  ld         $16, 0x0($29)
    /* 330C8 001330C8 0800E003 */  jr         $31
    /* 330CC 001330CC 8000BD27 */   addiu     $29, $29, 0x80
endlabel inflate_codes
```
