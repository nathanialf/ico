# func_001B58B0 — parked

VRAM: 0x001B58B0 (file_off 0x0B58B0)
Asm source: asm/aug6/nonmatchings/common/src/staffroll/func_001B58B0.s

## Attempt at 2026-06-22

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=17). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/staffroll.c`

**Seed:** `tough_nuts/func_001B58B0/func_001B58B0.c`

Disassembly:

```
.align 3
nonmatching func_001B58B0, 0x13C

glabel func_001B58B0
    /* B58B0 001B58B0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* B58B4 001B58B4 3000BFFF */  sd         $31, 0x30($29)
    /* B58B8 001B58B8 2000B2FF */  sd         $18, 0x20($29)
    /* B58BC 001B58BC 1000B1FF */  sd         $17, 0x10($29)
    /* B58C0 001B58C0 3AE0070C */  jal        dl_Swap
    /* B58C4 001B58C4 0000B0FF */   sd        $16, 0x0($29)
    /* B58C8 001B58C8 01004224 */  addiu      $2, $2, 0x1
    /* B58CC 001B58CC D4B580C7 */  lwc1       $f0, %gp_rel(D_0062C1C4)($28)
    /* B58D0 001B58D0 00108244 */  mtc1       $2, $f2
    /* B58D4 001B58D4 A0108046 */  cvt.s.w    $f2, $f2
    /* B58D8 001B58D8 D8B5868F */  lw         $6, %gp_rel(D_0062C1C8)($28)
    /* B58DC 001B58DC 00088644 */  mtc1       $6, $f1
    /* B58E0 001B58E0 60088046 */  cvt.s.w    $f1, $f1
    /* B58E4 001B58E4 00000000 */  nop
    /* B58E8 001B58E8 00000000 */  nop
    /* B58EC 001B58EC 03000246 */  div.s      $f0, $f0, $f2
    /* B58F0 001B58F0 36080046 */  c.le.s     $f1, $f0
    /* B58F4 001B58F4 00000000 */  nop
    /* B58F8 001B58F8 33000045 */  bc1f       .L001B59C8
    /* B58FC 001B58FC 7000123C */   lui       $18, %hi(D_00700770)
    /* B5900 001B5900 2D880000 */  daddu      $17, $0, $0
    /* B5904 001B5904 70074426 */  addiu      $4, $18, %lo(D_00700770)
    /* B5908 001B5908 2D180000 */  daddu      $3, $0, $0
    /* B590C 001B590C 00000000 */  nop
.align 2
  .L001B5910:
    /* B5910 001B5910 0000828C */  lw         $2, 0x0($4)
    /* B5914 001B5914 15004010 */  beqz       $2, .L001B596C
    /* B5918 001B5918 2D286000 */   daddu     $5, $3, $0
    /* B591C 001B591C 01003126 */  addiu      $17, $17, 0x1
    /* B5920 001B5920 1000A324 */  addiu      $3, $5, 0x10
    /* B5924 001B5924 2C01222A */  slti       $2, $17, 0x12C
    /* B5928 001B5928 F9FF4014 */  bnez       $2, .L001B5910
    /* B592C 001B592C 10008424 */   addiu     $4, $4, 0x10
    /* B5930 001B5930 6100043C */  lui        $4, %hi(D_0060FD60)
    /* B5934 001B5934 F290060C */  jal        debug_assertMessage
    /* B5938 001B5938 60FD8424 */   addiu     $4, $4, %lo(D_0060FD60)
    /* B593C 001B593C 6100103C */  lui        $16, %hi(D_0060FD78)
    /* B5940 001B5940 BD000524 */  addiu      $5, $0, 0xBD
    /* B5944 001B5944 78FD1026 */  addiu      $16, $16, %lo(D_0060FD78)
    /* B5948 001B5948 40AB060C */  jal        func_001AAD00
    /* B594C 001B594C 2D200002 */   daddu     $4, $16, $0
    /* B5950 001B5950 6300063C */  lui        $6, %hi(D_0062D2E8)
    /* B5954 001B5954 2D200002 */  daddu      $4, $16, $0
    /* B5958 001B5958 E8D2C624 */  addiu      $6, $6, %lo(D_0062D2E8)
    /* B595C 001B595C E080090C */  jal        func_00260380
    /* B5960 001B5960 BD000524 */   addiu     $5, $0, 0xBD
    /* B5964 001B5964 D8B5868F */  lw         $6, %gp_rel(D_0062C1C8)($28)
    /* B5968 001B5968 00291100 */  sll        $5, $17, 4
.align 2
  .L001B596C:
    /* B596C 001B596C 4C00023C */  lui        $2, %hi(D_004B8C90)
    /* B5970 001B5970 80180600 */  sll        $3, $6, 2
    /* B5974 001B5974 908C4224 */  addiu      $2, $2, %lo(D_004B8C90)
    /* B5978 001B5978 70074426 */  addiu      $4, $18, %lo(D_00700770)
    /* B597C 001B597C 21186200 */  addu       $3, $3, $2
    /* B5980 001B5980 0100C624 */  addiu      $6, $6, 0x1
    /* B5984 001B5984 0000628C */  lw         $2, 0x0($3)
    /* B5988 001B5988 2180A400 */  addu       $16, $5, $4
    /* B598C 001B598C 02004010 */  beqz       $2, .L001B5998
    /* B5990 001B5990 D8B586AF */   sw        $6, %gp_rel(D_0062C1C8)($28)
    /* B5994 001B5994 000003AE */  sw         $3, 0x0($16)
.align 2
  .L001B5998:
    /* B5998 001B5998 3AE0070C */  jal        dl_Swap
    /* B599C 001B599C 00000000 */   nop
    /* B59A0 001B59A0 C1014224 */  addiu      $2, $2, 0x1C1
    /* B59A4 001B59A4 0000038E */  lw         $3, 0x0($16)
    /* B59A8 001B59A8 00008244 */  mtc1       $2, $f0
    /* B59AC 001B59AC 20008046 */  cvt.s.w    $f0, $f0
    /* B59B0 001B59B0 09000426 */  addiu      $4, $16, 0x9
    /* B59B4 001B59B4 0000658C */  lw         $5, 0x0($3)
    /* B59B8 001B59B8 C6DD070C */  jal        func_001F7718
    /* B59BC 001B59BC 040000E6 */   swc1      $f0, 0x4($16)
    /* B59C0 001B59C0 080002A2 */  sb         $2, 0x8($16)
    /* B59C4 001B59C4 D8B5868F */  lw         $6, %gp_rel(D_0062C1C8)($28)
.align 2
  .L001B59C8:
    /* B59C8 001B59C8 94A8828F */  lw         $2, %gp_rel(D_0062B484)($28)
    /* B59CC 001B59CC 3000BFDF */  ld         $31, 0x30($29)
    /* B59D0 001B59D0 2A10C200 */  slt        $2, $6, $2
    /* B59D4 001B59D4 2000B2DF */  ld         $18, 0x20($29)
    /* B59D8 001B59D8 1000B1DF */  ld         $17, 0x10($29)
    /* B59DC 001B59DC 01004238 */  xori       $2, $2, 0x1
    /* B59E0 001B59E0 0000B0DF */  ld         $16, 0x0($29)
    /* B59E4 001B59E4 0800E003 */  jr         $31
    /* B59E8 001B59E8 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001B58B0
    /* B59EC 001B59EC 00000000 */  nop
```
