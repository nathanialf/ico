# func_001A63C8 — parked

VRAM: 0x001A63C8 (file_off 0x0A63C8)
Asm source: asm/aug6/nonmatchings/common/src/debug_exception/func_001A63C8.s

## Attempt at 2026-06-24

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=1). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/debug_exception.c`

**Seed:** `tough_nuts/func_001A63C8/func_001A63C8.c`

Disassembly:

```
.align 3
nonmatching func_001A63C8, 0x13C

glabel func_001A63C8
    /* A63C8 001A63C8 40FFBD27 */  addiu      $29, $29, -0xC0
    /* A63CC 001A63CC A000B4FF */  sd         $20, 0xA0($29)
    /* A63D0 001A63D0 7000B1FF */  sd         $17, 0x70($29)
    /* A63D4 001A63D4 2DA08000 */  daddu      $20, $4, $0
    /* A63D8 001A63D8 6000B0FF */  sd         $16, 0x60($29)
    /* A63DC 001A63DC 1000B127 */  addiu      $17, $29, 0x10
    /* A63E0 001A63E0 B000BFFF */  sd         $31, 0xB0($29)
    /* A63E4 001A63E4 2D800000 */  daddu      $16, $0, $0
    /* A63E8 001A63E8 9000B3FF */  sd         $19, 0x90($29)
    /* A63EC 001A63EC E4F9040C */  jal        isysGObjRemoveObjDL
    /* A63F0 001A63F0 8000B2FF */   sd        $18, 0x80($29)
    /* A63F4 001A63F4 2D304000 */  daddu      $6, $2, $0
    /* A63F8 001A63F8 2200C010 */  beqz       $6, .L001A6484
    /* A63FC 001A63FC 6100133C */   lui       $19, %hi(D_0060E1C0)
    /* A6400 001A6400 D8A29227 */  addiu      $18, $28, %gp_rel(D_0062AEC8)
    /* A6404 001A6404 0C00C58C */  lw         $5, 0xC($6)
.align 2
  .L001A6408:
    /* A6408 001A6408 04000224 */  addiu      $2, $0, 0x4
    /* A640C 001A640C 0C00A210 */  beq        $5, $2, .L001A6440
    /* A6410 001A6410 0500A228 */   slti      $2, $5, 0x5
    /* A6414 001A6414 07004010 */  beqz       $2, .L001A6434
    /* A6418 001A6418 0300A228 */   slti      $2, $5, 0x3
    /* A641C 001A641C 12004010 */  beqz       $2, .L001A6468
    /* A6420 001A6420 00000000 */   nop
    /* A6424 001A6424 1000A018 */  blez       $5, .L001A6468
    /* A6428 001A6428 64000324 */   addiu     $3, $0, 0x64
    /* A642C 001A642C 06000010 */  b          .L001A6448
    /* A6430 001A6430 2A00043C */   lui       $4, %hi(D_0029F060)
.align 2
  .L001A6434:
    /* A6434 001A6434 2E000224 */  addiu      $2, $0, 0x2E
    /* A6438 001A6438 0B00A214 */  bne        $5, $2, .L001A6468
    /* A643C 001A643C 00000000 */   nop
.align 2
  .L001A6440:
    /* A6440 001A6440 64000324 */  addiu      $3, $0, 0x64
    /* A6444 001A6444 2A00043C */  lui        $4, %hi(D_0029F060)
.align 2
  .L001A6448:
    /* A6448 001A6448 1818A300 */  mult       $3, $5, $3
    /* A644C 001A644C C0101000 */  sll        $2, $16, 3
    /* A6450 001A6450 60F08424 */  addiu      $4, $4, %lo(D_0029F060)
    /* A6454 001A6454 21105100 */  addu       $2, $2, $17
    /* A6458 001A6458 040046AC */  sw         $6, 0x4($2)
    /* A645C 001A645C 01001026 */  addiu      $16, $16, 0x1
    /* A6460 001A6460 21186400 */  addu       $3, $3, $4
    /* A6464 001A6464 000043AC */  sw         $3, 0x0($2)
.align 2
  .L001A6468:
    /* A6468 001A6468 F8F9040C */  jal        func_0013E7E0
    /* A646C 001A646C 2D20C000 */   daddu     $4, $6, $0
    /* A6470 001A6470 2D304000 */  daddu      $6, $2, $0
    /* A6474 001A6474 E4FFC054 */  bnel       $6, $0, .L001A6408
    /* A6478 001A6478 0C00C58C */   lw        $5, 0xC($6)
    /* A647C 001A647C 02000010 */  b          .L001A6488
    /* A6480 001A6480 00000000 */   nop
.align 2
  .L001A6484:
    /* A6484 001A6484 D8A29227 */  addiu      $18, $28, %gp_rel(D_0062AEC8)
.align 2
  .L001A6488:
    /* A6488 001A6488 01008056 */  bnel       $20, $0, .L001A6490
    /* A648C 001A648C D8A280AF */   sw        $0, %gp_rel(D_0062AEC8)($28)
.align 2
  .L001A6490:
    /* A6490 001A6490 0000B0AF */  sw         $16, 0x0($29)
    /* A6494 001A6494 C0E16426 */  addiu      $4, $19, %lo(D_0060E1C0)
    /* A6498 001A6498 0800B2AF */  sw         $18, 0x8($29)
    /* A649C 001A649C 0A000524 */  addiu      $5, $0, 0xA
    /* A64A0 001A64A0 32000624 */  addiu      $6, $0, 0x32
    /* A64A4 001A64A4 0B000724 */  addiu      $7, $0, 0xB
    /* A64A8 001A64A8 1000A827 */  addiu      $8, $29, 0x10
    /* A64AC 001A64AC 08000924 */  addiu      $9, $0, 0x8
    /* A64B0 001A64B0 2D500000 */  daddu      $10, $0, $0
    /* A64B4 001A64B4 7A93060C */  jal        func_001A4DE8
    /* A64B8 001A64B8 01000B24 */   addiu     $11, $0, 0x1
    /* A64BC 001A64BC 2D804000 */  daddu      $16, $2, $0
    /* A64C0 001A64C0 D8A2828F */  lw         $2, %gp_rel(D_0062AEC8)($28)
    /* A64C4 001A64C4 04004004 */  bltz       $2, .L001A64D8
    /* A64C8 001A64C8 C0100200 */   sll       $2, $2, 3
    /* A64CC 001A64CC 2118A203 */  addu       $3, $29, $2
    /* A64D0 001A64D0 3A67050C */  jal        actCommonStone
    /* A64D4 001A64D4 1400648C */   lw        $4, 0x14($3)
.align 2
  .L001A64D8:
    /* A64D8 001A64D8 27181000 */  nor        $3, $0, $16
    /* A64DC 001A64DC FFFF0224 */  addiu      $2, $0, -0x1
    /* A64E0 001A64E0 B000BFDF */  ld         $31, 0xB0($29)
    /* A64E4 001A64E4 0B100300 */  movn       $2, $0, $3
    /* A64E8 001A64E8 A000B4DF */  ld         $20, 0xA0($29)
    /* A64EC 001A64EC 9000B3DF */  ld         $19, 0x90($29)
    /* A64F0 001A64F0 8000B2DF */  ld         $18, 0x80($29)
    /* A64F4 001A64F4 7000B1DF */  ld         $17, 0x70($29)
    /* A64F8 001A64F8 6000B0DF */  ld         $16, 0x60($29)
    /* A64FC 001A64FC 0800E003 */  jr         $31
    /* A6500 001A6500 C000BD27 */   addiu     $29, $29, 0xC0
endlabel func_001A63C8
    /* A6504 001A6504 00000000 */  nop
```
