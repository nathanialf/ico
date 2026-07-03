# GetPObjAddress — parked

VRAM: 0x001A0050 (file_off 0x0A0050)
Asm source: asm/aug6/nonmatchings/common/src/charFileManager/GetPObjAddress.s

## Attempt at 2026-07-03

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=14). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/charFileManager.c`

**Seed:** `tough_nuts/GetPObjAddress/GetPObjAddress.c`

Disassembly:

```
.align 3
nonmatching GetPObjAddress, 0x168

glabel GetPObjAddress
    /* A0050 001A0050 70FFBD27 */  addiu      $29, $29, -0x90
    /* A0054 001A0054 2700033C */  lui        $3, %hi(D_00271240)
    /* A0058 001A0058 7000B6FF */  sd         $22, 0x70($29)
    /* A005C 001A005C 40126324 */  addiu      $3, $3, %lo(D_00271240)
    /* A0060 001A0060 6000B5FF */  sd         $21, 0x60($29)
    /* A0064 001A0064 2DB0A000 */  daddu      $22, $5, $0
    /* A0068 001A0068 5000B4FF */  sd         $20, 0x50($29)
    /* A006C 001A006C 2DA88000 */  daddu      $21, $4, $0
    /* A0070 001A0070 4000B3FF */  sd         $19, 0x40($29)
    /* A0074 001A0074 2DA0E000 */  daddu      $20, $7, $0
    /* A0078 001A0078 3000B2FF */  sd         $18, 0x30($29)
    /* A007C 001A007C 2D984001 */  daddu      $19, $10, $0
    /* A0080 001A0080 2000B1FF */  sd         $17, 0x20($29)
    /* A0084 001A0084 2D900001 */  daddu      $18, $8, $0
    /* A0088 001A0088 8000BFFF */  sd         $31, 0x80($29)
    /* A008C 001A008C 2D88C000 */  daddu      $17, $6, $0
    /* A0090 001A0090 1000B0FF */  sd         $16, 0x10($29)
    /* A0094 001A0094 2000628C */  lw         $2, 0x20($3)
    /* A0098 001A0098 01004224 */  addiu      $2, $2, 0x1
    /* A009C 001A009C 3C002012 */  beqz       $17, .L001A0190
    /* A00A0 001A00A0 200062AC */   sw        $2, 0x20($3)
    /* A00A4 001A00A4 0A000224 */  addiu      $2, $0, 0xA
    /* A00A8 001A00A8 07004212 */  beq        $18, $2, .L001A00C8
    /* A00AC 001A00AC 0B000224 */   addiu     $2, $0, 0xB
    /* A00B0 001A00B0 0B004216 */  bne        $18, $2, .L001A00E0
    /* A00B4 001A00B4 6100103C */   lui       $16, %hi(D_0060B4E0)
    /* A00B8 001A00B8 0000A0AF */  sw         $0, 0x0($29)
    /* A00BC 001A00BC 0400A0AF */  sw         $0, 0x4($29)
    /* A00C0 001A00C0 10000010 */  b          .L001A0104
    /* A00C4 001A00C4 00000000 */   nop
.align 2
  .L001A00C8:
    /* A00C8 001A00C8 01000224 */  addiu      $2, $0, 0x1
    /* A00CC 001A00CC 3C99838F */  lw         $3, %gp_rel(D_0062A52C)($28)
    /* A00D0 001A00D0 0000A2AF */  sw         $2, 0x0($29)
    /* A00D4 001A00D4 0400A3AF */  sw         $3, 0x4($29)
    /* A00D8 001A00D8 0A000010 */  b          .L001A0104
    /* A00DC 001A00DC 00000000 */   nop
.align 2
  .L001A00E0:
    /* A00E0 001A00E0 B8020524 */  addiu      $5, $0, 0x2B8
    /* A00E4 001A00E4 E0B41026 */  addiu      $16, $16, %lo(D_0060B4E0)
    /* A00E8 001A00E8 40AB060C */  jal        func_001AAD00
    /* A00EC 001A00EC 2D200002 */   daddu     $4, $16, $0
    /* A00F0 001A00F0 6300063C */  lui        $6, %hi(D_0062C9F0)
    /* A00F4 001A00F4 2D200002 */  daddu      $4, $16, $0
    /* A00F8 001A00F8 F0C9C624 */  addiu      $6, $6, %lo(D_0062C9F0)
    /* A00FC 001A00FC E080090C */  jal        func_00260380
    /* A0100 001A0100 B8020524 */   addiu     $5, $0, 0x2B8
.align 2
  .L001A0104:
    /* A0104 001A0104 0400A28F */  lw         $2, 0x4($29)
    /* A0108 001A0108 0F004014 */  bnez       $2, .L001A0148
    /* A010C 001A010C 2D800000 */   daddu     $16, $0, $0
    /* A0110 001A0110 06006016 */  bnez       $19, .L001A012C
    /* A0114 001A0114 6100063C */   lui       $6, %hi(D_0060B4E0)
    /* A0118 001A0118 2C97848F */  lw         $4, %gp_rel(D_0062A31C)($28)
    /* A011C 001A011C E0B4C624 */  addiu      $6, $6, %lo(D_0060B4E0)
    /* A0120 001A0120 2D282002 */  daddu      $5, $17, $0
    /* A0124 001A0124 05000010 */  b          .L001A013C
    /* A0128 001A0128 BE020724 */   addiu     $7, $0, 0x2BE
.align 2
  .L001A012C:
    /* A012C 001A012C 4097848F */  lw         $4, %gp_rel(D_0062A330)($28)
    /* A0130 001A0130 E0B4C624 */  addiu      $6, $6, %lo(D_0060B4E0)
    /* A0134 001A0134 2D282002 */  daddu      $5, $17, $0
    /* A0138 001A0138 C0020724 */  addiu      $7, $0, 0x2C0
.align 2
  .L001A013C:
    /* A013C 001A013C CEE2040C */  jal        iosFree
    /* A0140 001A0140 00000000 */   nop
    /* A0144 001A0144 2D804000 */  daddu      $16, $2, $0
.align 2
  .L001A0148:
    /* A0148 001A0148 2D20A002 */  daddu      $4, $21, $0
    /* A014C 001A014C 2D280002 */  daddu      $5, $16, $0
    /* A0150 001A0150 EEC7040C */  jal        iosCdvdLoad
    /* A0154 001A0154 2D302002 */   daddu     $6, $17, $0
    /* A0158 001A0158 08000012 */  beqz       $16, .L001A017C
    /* A015C 001A015C 6100043C */   lui       $4, %hi(D_0060BA00)
    /* A0160 001A0160 0000A78F */  lw         $7, 0x0($29)
    /* A0164 001A0164 2D200002 */  daddu      $4, $16, $0
    /* A0168 001A0168 2D304002 */  daddu      $6, $18, $0
    /* A016C 001A016C 2D406002 */  daddu      $8, $19, $0
    /* A0170 001A0170 9E0A050C */  jal        soundSeDefPlay
    /* A0174 001A0174 2D288002 */   daddu     $5, $20, $0
    /* A0178 001A0178 6100043C */  lui        $4, %hi(D_0060BA00)
.align 2
  .L001A017C:
    /* A017C 001A017C 2D288002 */  daddu      $5, $20, $0
    /* A0180 001A0180 00BA8424 */  addiu      $4, $4, %lo(D_0060BA00)
    /* A0184 001A0184 2D30C002 */  daddu      $6, $22, $0
    /* A0188 001A0188 F290060C */  jal        debug_assertMessage
    /* A018C 001A018C 2D382002 */   daddu     $7, $17, $0
.align 2
  .L001A0190:
    /* A0190 001A0190 8000BFDF */  ld         $31, 0x80($29)
    /* A0194 001A0194 7000B6DF */  ld         $22, 0x70($29)
    /* A0198 001A0198 6000B5DF */  ld         $21, 0x60($29)
    /* A019C 001A019C 5000B4DF */  ld         $20, 0x50($29)
    /* A01A0 001A01A0 4000B3DF */  ld         $19, 0x40($29)
    /* A01A4 001A01A4 3000B2DF */  ld         $18, 0x30($29)
    /* A01A8 001A01A8 2000B1DF */  ld         $17, 0x20($29)
    /* A01AC 001A01AC 1000B0DF */  ld         $16, 0x10($29)
    /* A01B0 001A01B0 0800E003 */  jr         $31
    /* A01B4 001A01B4 9000BD27 */   addiu     $29, $29, 0x90
endlabel GetPObjAddress
```
