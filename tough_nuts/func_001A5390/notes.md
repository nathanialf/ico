# func_001A5390 — parked

VRAM: 0x001A5390 (file_off 0x0A5390)
Asm source: asm/aug6/nonmatchings/common/src/debug_exception/func_001A5390.s

## Attempt at 2026-06-24

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=19). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/debug_exception.c`

**Seed:** `tough_nuts/func_001A5390/func_001A5390.c`

Disassembly:

```
.align 3
nonmatching func_001A5390, 0x130

glabel func_001A5390
    /* A5390 001A5390 B0FFBD27 */  addiu      $29, $29, -0x50
    /* A5394 001A5394 2D388000 */  daddu      $7, $4, $0
    /* A5398 001A5398 4000BFFF */  sd         $31, 0x40($29)
    /* A539C 001A539C 1000E28C */  lw         $2, 0x10($7)
    /* A53A0 001A53A0 03004004 */  bltz       $2, .L001A53B0
    /* A53A4 001A53A4 10004324 */   addiu     $3, $2, 0x10
    /* A53A8 001A53A8 42000010 */  b          .L001A54B4
    /* A53AC 001A53AC 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001A53B0:
    /* A53B0 001A53B0 1100622C */  sltiu      $2, $3, 0x11
    /* A53B4 001A53B4 28004010 */  beqz       $2, .L001A5458
    /* A53B8 001A53B8 6100023C */   lui       $2, %hi(jtbl_0060DD70)
    /* A53BC 001A53BC 80180300 */  sll        $3, $3, 2
    /* A53C0 001A53C0 70DD4224 */  addiu      $2, $2, %lo(jtbl_0060DD70)
    /* A53C4 001A53C4 21186200 */  addu       $3, $3, $2
    /* A53C8 001A53C8 0000648C */  lw         $4, 0x0($3)
    /* A53CC 001A53CC 08008000 */  jr         $4
    /* A53D0 001A53D0 00000000 */   nop
.align 2
  jlabel .L001A53D4
    /* A53D4 001A53D4 36000010 */  b          .L001A54B0
    /* A53D8 001A53D8 01000524 */   addiu     $5, $0, 0x1
.align 2
  jlabel .L001A53DC
    /* A53DC 001A53DC 1000E68C */  lw         $6, 0x10($7)
    /* A53E0 001A53E0 6100053C */  lui        $5, %hi(D_0060DC90)
    /* A53E4 001A53E4 1F000010 */  b          .L001A5464
    /* A53E8 001A53E8 90DCA524 */   addiu     $5, $5, %lo(D_0060DC90)
.align 2
  jlabel .L001A53EC
    /* A53EC 001A53EC 6100053C */  lui        $5, %hi(D_0060DCC0)
    /* A53F0 001A53F0 7C04E624 */  addiu      $6, $7, 0x47C
    /* A53F4 001A53F4 1B000010 */  b          .L001A5464
    /* A53F8 001A53F8 C0DCA524 */   addiu     $5, $5, %lo(D_0060DCC0)
.align 2
  jlabel .L001A53FC
    /* A53FC 001A53FC 6100053C */  lui        $5, %hi(D_0060DCD8)
    /* A5400 001A5400 5404E624 */  addiu      $6, $7, 0x454
    /* A5404 001A5404 17000010 */  b          .L001A5464
    /* A5408 001A5408 D8DCA524 */   addiu     $5, $5, %lo(D_0060DCD8)
.align 2
  jlabel .L001A540C
    /* A540C 001A540C 4C00E88C */  lw         $8, 0x4C($7)
    /* A5410 001A5410 6100053C */  lui        $5, %hi(D_0060DCF0)
    /* A5414 001A5414 2400E68C */  lw         $6, 0x24($7)
    /* A5418 001A5418 F0DCA524 */  addiu      $5, $5, %lo(D_0060DCF0)
    /* A541C 001A541C 5000E78C */  lw         $7, 0x50($7)
    /* A5420 001A5420 6284090C */  jal        func_00261188
    /* A5424 001A5424 2D20A003 */   daddu     $4, $29, $0
    /* A5428 001A5428 11000010 */  b          .L001A5470
    /* A542C 001A542C 6300073C */   lui       $7, %hi(D_0062CC48)
.align 2
  jlabel .L001A5430
    /* A5430 001A5430 6100053C */  lui        $5, %hi(D_0060DD20)
    /* A5434 001A5434 7C04E624 */  addiu      $6, $7, 0x47C
    /* A5438 001A5438 0A000010 */  b          .L001A5464
    /* A543C 001A543C 20DDA524 */   addiu     $5, $5, %lo(D_0060DD20)
.align 2
  jlabel .L001A5440
    /* A5440 001A5440 6100053C */  lui        $5, %hi(D_0060DD40)
    /* A5444 001A5444 2D20A003 */  daddu      $4, $29, $0
    /* A5448 001A5448 6284090C */  jal        func_00261188
    /* A544C 001A544C 40DDA524 */   addiu     $5, $5, %lo(D_0060DD40)
    /* A5450 001A5450 07000010 */  b          .L001A5470
    /* A5454 001A5454 6300073C */   lui       $7, %hi(D_0062CC48)
.align 2
  jlabel .L001A5458
    /* A5458 001A5458 1000E68C */  lw         $6, 0x10($7)
    /* A545C 001A545C 6100053C */  lui        $5, %hi(D_0060DD50)
    /* A5460 001A5460 50DDA524 */  addiu      $5, $5, %lo(D_0060DD50)
.align 2
  .L001A5464:
    /* A5464 001A5464 6284090C */  jal        func_00261188
    /* A5468 001A5468 2D20A003 */   daddu     $4, $29, $0
    /* A546C 001A546C 6300073C */  lui        $7, %hi(D_0062CC48)
.align 2
  .L001A5470:
    /* A5470 001A5470 FFFF063C */  lui        $6, (0xFFFFFF00 >> 16)
    /* A5474 001A5474 48CCE724 */  addiu      $7, $7, %lo(D_0062CC48)
    /* A5478 001A5478 50000424 */  addiu      $4, $0, 0x50
    /* A547C 001A547C 46000524 */  addiu      $5, $0, 0x46
    /* A5480 001A5480 00FFC634 */  ori        $6, $6, (0xFFFFFF00 & 0xFFFF)
    /* A5484 001A5484 E090060C */  jal        debugEEExceptionMain
    /* A5488 001A5488 2D40A003 */   daddu     $8, $29, $0
    /* A548C 001A548C 2700023C */  lui        $2, %hi(D_002715D4)
    /* A5490 001A5490 FFFF0424 */  addiu      $4, $0, -0x1
    /* A5494 001A5494 D415438C */  lw         $3, %lo(D_002715D4)($2)
    /* A5498 001A5498 2D288000 */  daddu      $5, $4, $0
    /* A549C 001A549C 20006230 */  andi       $2, $3, 0x20
    /* A54A0 001A54A0 40006330 */  andi       $3, $3, 0x40
    /* A54A4 001A54A4 2B100200 */  sltu       $2, $0, $2
    /* A54A8 001A54A8 0B108300 */  movn       $2, $4, $3
    /* A54AC 001A54AC 0A280200 */  movz       $5, $0, $2
.align 2
  .L001A54B0:
    /* A54B0 001A54B0 2D10A000 */  daddu      $2, $5, $0
.align 2
  .L001A54B4:
    /* A54B4 001A54B4 4000BFDF */  ld         $31, 0x40($29)
    /* A54B8 001A54B8 0800E003 */  jr         $31
    /* A54BC 001A54BC 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_001A5390
```
