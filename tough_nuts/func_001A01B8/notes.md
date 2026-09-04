# func_001A01B8 — parked

VRAM: 0x001A01B8 (file_off 0x0A01B8)
Asm source: asm/aug6/nonmatchings/common/src/charFileManager/func_001A01B8.s

## Attempt at 2026-06-22

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=10). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/charFileManager.c`

**Seed:** `tough_nuts/func_001A01B8/func_001A01B8.c`

Disassembly:

```
.align 3
nonmatching func_001A01B8, 0x13C

glabel func_001A01B8
    /* A01B8 001A01B8 70FFBD27 */  addiu      $29, $29, -0x90
    /* A01BC 001A01BC 2700093C */  lui        $9, %hi(D_00271240)
    /* A01C0 001A01C0 7000B6FF */  sd         $22, 0x70($29)
    /* A01C4 001A01C4 40122925 */  addiu      $9, $9, %lo(D_00271240)
    /* A01C8 001A01C8 6000B5FF */  sd         $21, 0x60($29)
    /* A01CC 001A01CC 0500023C */  lui        $2, (0x5C000 >> 16)
    /* A01D0 001A01D0 5000B4FF */  sd         $20, 0x50($29)
    /* A01D4 001A01D4 00C04234 */  ori        $2, $2, (0x5C000 & 0xFFFF)
    /* A01D8 001A01D8 4000B3FF */  sd         $19, 0x40($29)
    /* A01DC 001A01DC 2DA80001 */  daddu      $21, $8, $0
    /* A01E0 001A01E0 3000B2FF */  sd         $18, 0x30($29)
    /* A01E4 001A01E4 00441500 */  sll        $8, $21, 16
    /* A01E8 001A01E8 1000B0FF */  sd         $16, 0x10($29)
    /* A01EC 001A01EC 2D90E000 */  daddu      $18, $7, $0
    /* A01F0 001A01F0 8000BFFF */  sd         $31, 0x80($29)
    /* A01F4 001A01F4 2D804000 */  daddu      $16, $2, $0
    /* A01F8 001A01F8 2000B1FF */  sd         $17, 0x20($29)
    /* A01FC 001A01FC FFFF4732 */  andi       $7, $18, 0xFFFF
    /* A0200 001A0200 2D988000 */  daddu      $19, $4, $0
    /* A0204 001A0204 2538E800 */  or         $7, $7, $8
    /* A0208 001A0208 2000238D */  lw         $3, 0x20($9)
    /* A020C 001A020C 2A104600 */  slt        $2, $2, $6
    /* A0210 001A0210 0A80C200 */  movz       $16, $6, $2
    /* A0214 001A0214 2DA0A000 */  daddu      $20, $5, $0
    /* A0218 001A0218 01006324 */  addiu      $3, $3, 0x1
    /* A021C 001A021C 2DB04001 */  daddu      $22, $10, $0
    /* A0220 001A0220 200023AD */  sw         $3, 0x20($9)
    /* A0224 001A0224 2D20A003 */  daddu      $4, $29, $0
    /* A0228 001A0228 E209050C */  jal        soundDataAreaGet
    /* A022C 001A022C 0000A7AF */   sw        $7, 0x0($29)
    /* A0230 001A0230 23004014 */  bnez       $2, .L001A02C0
    /* A0234 001A0234 2D206002 */   daddu     $4, $19, $0
    /* A0238 001A0238 6100063C */  lui        $6, %hi(D_0060B4E0)
    /* A023C 001A023C 2C97848F */  lw         $4, %gp_rel(D_0062A31C)($28)
    /* A0240 001A0240 2D280002 */  daddu      $5, $16, $0
    /* A0244 001A0244 E0B4C624 */  addiu      $6, $6, %lo(D_0060B4E0)
    /* A0248 001A0248 CEE2040C */  jal        iosFree
    /* A024C 001A024C E8020724 */   addiu     $7, $0, 0x2E8
    /* A0250 001A0250 2D884000 */  daddu      $17, $2, $0
    /* A0254 001A0254 2D300002 */  daddu      $6, $16, $0
    /* A0258 001A0258 2D206002 */  daddu      $4, $19, $0
    /* A025C 001A025C EEC7040C */  jal        iosCdvdLoad
    /* A0260 001A0260 2D282002 */   daddu     $5, $17, $0
    /* A0264 001A0264 6100043C */  lui        $4, %hi(D_0060BA30)
    /* A0268 001A0268 2D380002 */  daddu      $7, $16, $0
    /* A026C 001A026C 2D308002 */  daddu      $6, $20, $0
    /* A0270 001A0270 30BA8424 */  addiu      $4, $4, %lo(D_0060BA30)
    /* A0274 001A0274 F290060C */  jal        debug_StdPrintfDummy
    /* A0278 001A0278 2D284002 */   daddu     $5, $18, $0
    /* A027C 001A027C 38E7070C */  jal        AdpcmUseAreaGet
    /* A0280 001A0280 00000000 */   nop
    /* A0284 001A0284 2D400002 */  daddu      $8, $16, $0
    /* A0288 001A0288 2D484000 */  daddu      $9, $2, $0
    /* A028C 001A028C 2D500000 */  daddu      $10, $0, $0
    /* A0290 001A0290 2D284002 */  daddu      $5, $18, $0
    /* A0294 001A0294 2D30A002 */  daddu      $6, $21, $0
    /* A0298 001A0298 2D38C002 */  daddu      $7, $22, $0
    /* A029C 001A029C 2AE5070C */  jal        AdpcmOpen
    /* A02A0 001A02A0 2D202002 */   daddu     $4, $17, $0
    /* A02A4 001A02A4 2D804000 */  daddu      $16, $2, $0
    /* A02A8 001A02A8 3CE4040C */  jal        iosMallocCheckLeak2
    /* A02AC 001A02AC 2D202002 */   daddu     $4, $17, $0
    /* A02B0 001A02B0 1EE6070C */  jal        AdpcmClose
    /* A02B4 001A02B4 2C00048E */   lw        $4, 0x2C($16)
    /* A02B8 001A02B8 05000010 */  b          .L001A02D0
    /* A02BC 001A02BC 8000BFDF */   ld        $31, 0x80($29)
.align 2
  .L001A02C0:
    /* A02C0 001A02C0 2D300002 */  daddu      $6, $16, $0
    /* A02C4 001A02C4 EEC7040C */  jal        iosCdvdLoad
    /* A02C8 001A02C8 2D280000 */   daddu     $5, $0, $0
    /* A02CC 001A02CC 8000BFDF */  ld         $31, 0x80($29)
.align 2
  .L001A02D0:
    /* A02D0 001A02D0 7000B6DF */  ld         $22, 0x70($29)
    /* A02D4 001A02D4 6000B5DF */  ld         $21, 0x60($29)
    /* A02D8 001A02D8 5000B4DF */  ld         $20, 0x50($29)
    /* A02DC 001A02DC 4000B3DF */  ld         $19, 0x40($29)
    /* A02E0 001A02E0 3000B2DF */  ld         $18, 0x30($29)
    /* A02E4 001A02E4 2000B1DF */  ld         $17, 0x20($29)
    /* A02E8 001A02E8 1000B0DF */  ld         $16, 0x10($29)
    /* A02EC 001A02EC 0800E003 */  jr         $31
    /* A02F0 001A02F0 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_001A01B8
    /* A02F4 001A02F4 00000000 */  nop
```
