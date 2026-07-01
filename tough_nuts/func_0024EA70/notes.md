# func_0024EA70 — parked

VRAM: 0x0024EA70 (file_off 0x14EA70)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024EA70.s

## Attempt at 2026-07-01

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024EA70/func_0024EA70.c`

Disassembly:

```
.align 3
nonmatching func_0024EA70, 0x154

glabel func_0024EA70
    /* 14EA70 0024EA70 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14EA74 0024EA74 20000424 */  addiu      $4, $0, 0x20
    /* 14EA78 0024EA78 1000B1FF */  sd         $17, 0x10($29)
    /* 14EA7C 0024EA7C 5500113C */  lui        $17, %hi(D_0054C764)
    /* 14EA80 0024EA80 2000BFFF */  sd         $31, 0x20($29)
    /* 14EA84 0024EA84 0000B0FF */  sd         $16, 0x0($29)
    /* 14EA88 0024EA88 64C7228E */  lw         $2, %lo(D_0054C764)($17)
    /* 14EA8C 0024EA8C 4000438C */  lw         $3, 0x40($2)
    /* 14EA90 0024EA90 1C4A090C */  jal        func_00252870
    /* 14EA94 0024EA94 D40060AC */   sw        $0, 0xD4($3)
    /* 14EA98 0024EA98 2D284000 */  daddu      $5, $2, $0
    /* 14EA9C 0024EA9C 5500093C */  lui        $9, %hi(D_0054C8B4)
    /* 14EAA0 0024EAA0 0F00A430 */  andi       $4, $5, 0xF
    /* 14EAA4 0024EAA4 02190500 */  srl        $3, $5, 4
    /* 14EAA8 0024EAA8 02120500 */  srl        $2, $5, 8
    /* 14EAAC 0024EAAC 02450500 */  srl        $8, $5, 20
    /* 14EAB0 0024EAB0 FF0F4230 */  andi       $2, $2, 0xFFF
    /* 14EAB4 0024EAB4 0F006330 */  andi       $3, $3, 0xF
    /* 14EAB8 0024EAB8 5500053C */  lui        $5, %hi(D_0054C8B0)
    /* 14EABC 0024EABC 5500073C */  lui        $7, %hi(D_0054C8A4)
    /* 14EAC0 0024EAC0 5500063C */  lui        $6, %hi(D_0054C8A0)
    /* 14EAC4 0024EAC4 B4C824AD */  sw         $4, %lo(D_0054C8B4)($9)
    /* 14EAC8 0024EAC8 B0C8A3AC */  sw         $3, %lo(D_0054C8B0)($5)
    /* 14EACC 0024EACC F10A4428 */  slti       $4, $2, 0xAF1
    /* 14EAD0 0024EAD0 A0C8C8AC */  sw         $8, %lo(D_0054C8A0)($6)
    /* 14EAD4 0024EAD4 04008014 */  bnez       $4, .L0024EAE8
    /* 14EAD8 0024EAD8 A4C8E2AC */   sw        $2, %lo(D_0054C8A4)($7)
    /* 14EADC 0024EADC 6300043C */  lui        $4, %hi(D_00628ED8)
    /* 14EAE0 0024EAE0 483A090C */  jal        func_0024E920
    /* 14EAE4 0024EAE4 D88E8424 */   addiu     $4, $4, %lo(D_00628ED8)
.align 2
  .L0024EAE8:
    /* 14EAE8 0024EAE8 1E000424 */  addiu      $4, $0, 0x1E
    /* 14EAEC 0024EAEC 1C4A090C */  jal        func_00252870
    /* 14EAF0 0024EAF0 5500103C */   lui       $16, %hi(D_0054D020)
    /* 14EAF4 0024EAF4 2D284000 */  daddu      $5, $2, $0
    /* 14EAF8 0024EAF8 5500043C */  lui        $4, %hi(D_0054C8C0)
    /* 14EAFC 0024EAFC 42100500 */  srl        $2, $5, 1
    /* 14EB00 0024EB00 023B0500 */  srl        $7, $5, 12
    /* 14EB04 0024EB04 0100A330 */  andi       $3, $5, 0x1
    /* 14EB08 0024EB08 FF034230 */  andi       $2, $2, 0x3FF
    /* 14EB0C 0024EB0C 5500053C */  lui        $5, %hi(D_0054C8BC)
    /* 14EB10 0024EB10 5500063C */  lui        $6, %hi(D_0054C8B8)
    /* 14EB14 0024EB14 C0C883AC */  sw         $3, %lo(D_0054C8C0)($4)
    /* 14EB18 0024EB18 01000424 */  addiu      $4, $0, 0x1
    /* 14EB1C 0024EB1C BCC8A2AC */  sw         $2, %lo(D_0054C8BC)($5)
    /* 14EB20 0024EB20 1C4A090C */  jal        func_00252870
    /* 14EB24 0024EB24 B8C8C7AC */   sw        $7, %lo(D_0054C8B8)($6)
    /* 14EB28 0024EB28 09004010 */  beqz       $2, .L0024EB50
    /* 14EB2C 0024EB2C 20D002AE */   sw        $2, %lo(D_0054D020)($16)
    /* 14EB30 0024EB30 C448090C */  jal        func_00252310
    /* 14EB34 0024EB34 00000000 */   nop
    /* 14EB38 0024EB38 B848090C */  jal        func_002522E0
    /* 14EB3C 0024EB3C 0050043C */   lui       $4, (0x50000000 >> 16)
    /* 14EB40 0024EB40 C448090C */  jal        func_00252310
    /* 14EB44 0024EB44 00000000 */   nop
    /* 14EB48 0024EB48 06000010 */  b          .L0024EB64
    /* 14EB4C 0024EB4C 01000424 */   addiu     $4, $0, 0x1
.align 2
  .L0024EB50:
    /* 14EB50 0024EB50 5500053C */  lui        $5, %hi(D_0054C800)
    /* 14EB54 0024EB54 0050043C */  lui        $4, (0x50000000 >> 16)
    /* 14EB58 0024EB58 FE3B090C */  jal        func_0024EFF8
    /* 14EB5C 0024EB5C 00C8A524 */   addiu     $5, $5, %lo(D_0054C800)
    /* 14EB60 0024EB60 01000424 */  addiu      $4, $0, 0x1
.align 2
  .L0024EB64:
    /* 14EB64 0024EB64 1C4A090C */  jal        func_00252870
    /* 14EB68 0024EB68 5500103C */   lui       $16, %hi(D_0054D024)
    /* 14EB6C 0024EB6C 09004010 */  beqz       $2, .L0024EB94
    /* 14EB70 0024EB70 24D002AE */   sw        $2, %lo(D_0054D024)($16)
    /* 14EB74 0024EB74 C448090C */  jal        func_00252310
    /* 14EB78 0024EB78 00000000 */   nop
    /* 14EB7C 0024EB7C B848090C */  jal        func_002522E0
    /* 14EB80 0024EB80 0058043C */   lui       $4, (0x58000000 >> 16)
    /* 14EB84 0024EB84 C448090C */  jal        func_00252310
    /* 14EB88 0024EB88 00000000 */   nop
    /* 14EB8C 0024EB8C 05000010 */  b          .L0024EBA4
    /* 14EB90 0024EB90 00000000 */   nop
.align 2
  .L0024EB94:
    /* 14EB94 0024EB94 5500053C */  lui        $5, %hi(D_0054C840)
    /* 14EB98 0024EB98 0058043C */  lui        $4, (0x58000000 >> 16)
    /* 14EB9C 0024EB9C FE3B090C */  jal        func_0024EFF8
    /* 14EBA0 0024EBA0 40C8A524 */   addiu     $5, $5, %lo(D_0054C840)
.align 2
  .L0024EBA4:
    /* 14EBA4 0024EBA4 2A4B090C */  jal        func_00252CA8
    /* 14EBA8 0024EBA8 00000000 */   nop
    /* 14EBAC 0024EBAC 64C7248E */  lw         $4, %lo(D_0054C764)($17)
    /* 14EBB0 0024EBB0 2000BFDF */  ld         $31, 0x20($29)
    /* 14EBB4 0024EBB4 1000B1DF */  ld         $17, 0x10($29)
    /* 14EBB8 0024EBB8 0000B0DF */  ld         $16, 0x0($29)
    /* 14EBBC 0024EBBC F23A0908 */  j          func_0024EBC8
    /* 14EBC0 0024EBC0 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0024EA70
    /* 14EBC4 0024EBC4 00000000 */  nop
```
