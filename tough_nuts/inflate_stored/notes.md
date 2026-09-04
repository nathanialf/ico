# inflate_stored — parked

VRAM: 0x001330D0 (file_off 0x0330D0)
Asm source: asm/aug6/nonmatchings/fumi/ios/iosCdvdBackGroundMgrInit/inflate_stored.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=40). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/ios/iosCdvdBackGroundMgrInit.c`

**Seed:** `tough_nuts/inflate_stored/inflate_stored.c`

Disassembly:

```
.align 3
nonmatching inflate_stored, 0x110

glabel inflate_stored
    /* 330D0 001330D0 80FFBD27 */  addiu      $29, $29, -0x80
    /* 330D4 001330D4 4000B4FF */  sd         $20, 0x40($29)
    /* 330D8 001330D8 2000B2FF */  sd         $18, 0x20($29)
    /* 330DC 001330DC FFFF1424 */  addiu      $20, $0, -0x1
    /* 330E0 001330E0 2D90C000 */  daddu      $18, $6, $0
    /* 330E4 001330E4 1000B1FF */  sd         $17, 0x10($29)
    /* 330E8 001330E8 6000B6FF */  sd         $22, 0x60($29)
    /* 330EC 001330EC FF075126 */  addiu      $17, $18, 0x7FF
    /* 330F0 001330F0 5000B5FF */  sd         $21, 0x50($29)
    /* 330F4 001330F4 2A109202 */  slt        $2, $20, $18
    /* 330F8 001330F8 3000B3FF */  sd         $19, 0x30($29)
    /* 330FC 001330FC 2DA8A000 */  daddu      $21, $5, $0
    /* 33100 00133100 0000B0FF */  sd         $16, 0x0($29)
    /* 33104 00133104 0B884202 */  movn       $17, $18, $2
    /* 33108 00133108 7000BFFF */  sd         $31, 0x70($29)
    /* 3310C 0013310C 2D808000 */  daddu      $16, $4, $0
    /* 33110 00133110 01001324 */  addiu      $19, $0, 0x1
    /* 33114 00133114 5500163C */  lui        $22, %hi(D_00550E68)
    /* 33118 00133118 1001038E */  lw         $3, 0x110($16)
    /* 3311C 0013311C 00000000 */  nop
.align 2
  .L00133120:
    /* 33120 00133120 C32A1100 */  sra        $5, $17, 11
    /* 33124 00133124 1401088E */  lw         $8, 0x114($16)
    /* 33128 00133128 2D30A002 */  daddu      $6, $21, $0
    /* 3312C 0013312C FF076424 */  addiu      $4, $3, 0x7FF
    /* 33130 00133130 2A108302 */  slt        $2, $20, $3
    /* 33134 00133134 0B206200 */  movn       $4, $3, $2
    /* 33138 00133138 78968727 */  addiu      $7, $28, %gp_rel(D_0062A268)
    /* 3313C 0013313C C3220400 */  sra        $4, $4, 11
    /* 33140 00133140 B026090C */  jal        func_00249AC0
    /* 33144 00133144 21200401 */   addu      $4, $8, $4
    /* 33148 00133148 04000010 */  b          .L0013315C
    /* 3314C 0013314C 00000000 */   nop
.align 2
  .L00133150:
    /* 33150 00133150 B6F3040C */  jal        iosSemaCreate
    /* 33154 00133154 689693AF */   sw        $19, %gp_rel(D_0062A258)($28)
    /* 33158 00133158 689680AF */  sw         $0, %gp_rel(D_0062A258)($28)
.align 2
  .L0013315C:
    /* 3315C 0013315C 3024090C */  jal        sceCdSync
    /* 33160 00133160 01000424 */   addiu     $4, $0, 0x1
    /* 33164 00133164 FAFF4014 */  bnez       $2, .L00133150
    /* 33168 00133168 00000000 */   nop
    /* 3316C 0013316C 2C27090C */  jal        func_00249CB0
    /* 33170 00133170 00000000 */   nop
    /* 33174 00133174 2D284000 */  daddu      $5, $2, $0
    /* 33178 00133178 0A00A050 */  beql       $5, $0, .L001331A4
    /* 3317C 0013317C 1001038E */   lw        $3, 0x110($16)
    /* 33180 00133180 0801028E */  lw         $2, 0x108($16)
    /* 33184 00133184 02110200 */  srl        $2, $2, 4
    /* 33188 00133188 01004230 */  andi       $2, $2, 0x1
    /* 3318C 0013318C 05004054 */  bnel       $2, $0, .L001331A4
    /* 33190 00133190 1001038E */   lw        $3, 0x110($16)
    /* 33194 00133194 F290060C */  jal        debug_StdPrintfDummy
    /* 33198 00133198 680EC426 */   addiu     $4, $22, %lo(D_00550E68)
    /* 3319C 0013319C E0FF0010 */  b          .L00133120
    /* 331A0 001331A0 1001038E */   lw        $3, 0x110($16)
.align 2
  .L001331A4:
    /* 331A4 001331A4 0C01028E */  lw         $2, 0x10C($16)
    /* 331A8 001331A8 21187200 */  addu       $3, $3, $18
    /* 331AC 001331AC 7000BFDF */  ld         $31, 0x70($29)
    /* 331B0 001331B0 100103AE */  sw         $3, 0x110($16)
    /* 331B4 001331B4 2A106200 */  slt        $2, $3, $2
    /* 331B8 001331B8 6000B6DF */  ld         $22, 0x60($29)
    /* 331BC 001331BC 01004238 */  xori       $2, $2, 0x1
    /* 331C0 001331C0 5000B5DF */  ld         $21, 0x50($29)
    /* 331C4 001331C4 4000B4DF */  ld         $20, 0x40($29)
    /* 331C8 001331C8 3000B3DF */  ld         $19, 0x30($29)
    /* 331CC 001331CC 2000B2DF */  ld         $18, 0x20($29)
    /* 331D0 001331D0 1000B1DF */  ld         $17, 0x10($29)
    /* 331D4 001331D4 0000B0DF */  ld         $16, 0x0($29)
    /* 331D8 001331D8 0800E003 */  jr         $31
    /* 331DC 001331DC 8000BD27 */   addiu     $29, $29, 0x80
endlabel inflate_stored
```
