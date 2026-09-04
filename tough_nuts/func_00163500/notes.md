# func_00163500 — parked

VRAM: 0x00163500 (file_off 0x063500)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/func_00163500.s

## Attempt at 2026-07-07

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/func_00163500/func_00163500.c`

Disassembly:

```
.align 3
nonmatching func_00163500, 0xB4

glabel func_00163500
    /* 63500 00163500 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 63504 00163504 4842013C */  lui        $1, (0x42480000 >> 16)
    /* 63508 00163508 00608144 */  mtc1       $1, $f12
    /* 6350C 0016350C 0000A4AF */  sw         $4, 0x0($29)
    /* 63510 00163510 2D380000 */  daddu      $7, $0, $0
    /* 63514 00163514 2000BFFF */  sd         $31, 0x20($29)
    /* 63518 00163518 0000A28F */  lw         $2, 0x0($29)
    /* 6351C 0016351C 1000B0FF */  sd         $16, 0x10($29)
    /* 63520 00163520 0000A38F */  lw         $3, 0x0($29)
    /* 63524 00163524 0000A58F */  lw         $5, 0x0($29)
    /* 63528 00163528 6401508C */  lw         $16, 0x164($2)
    /* 6352C 0016352C 6401648C */  lw         $4, 0x164($3)
    /* 63530 00163530 6401A28C */  lw         $2, 0x164($5)
    /* 63534 00163534 00010626 */  addiu      $6, $16, 0x100
    /* 63538 00163538 7806838C */  lw         $3, 0x678($4)
    /* 6353C 0016353C 2C01058E */  lw         $5, 0x12C($16)
    /* 63540 00163540 7006498C */  lw         $9, 0x670($2)
    /* 63544 00163544 000465AC */  sw         $5, 0x400($3)
    /* 63548 00163548 0000A48F */  lw         $4, 0x0($29)
    /* 6354C 0016354C 7A8F050C */  jal        DispCollisionPC
    /* 63550 00163550 1C022891 */   lbu       $8, 0x21C($9)
    /* 63554 00163554 FF004230 */  andi       $2, $2, 0xFF
    /* 63558 00163558 0F004014 */  bnez       $2, .L00163598
    /* 6355C 0016355C 00000000 */   nop
    /* 63560 00163560 5500043C */  lui        $4, %hi(D_00553320)
    /* 63564 00163564 F290060C */  jal        debug_StdPrintfDummy
    /* 63568 00163568 20338424 */   addiu     $4, $4, %lo(D_00553320)
    /* 6356C 0016356C 080100AE */  sw         $0, 0x108($16)
    /* 63570 00163570 1E000424 */  addiu      $4, $0, 0x1E
    /* 63574 00163574 3C0300AE */  sw         $0, 0x33C($16)
    /* 63578 00163578 000100AE */  sw         $0, 0x100($16)
    /* 6357C 0016357C 6004080C */  jal        _ACTWait
    /* 63580 00163580 040100AE */   sw        $0, 0x104($16)
    /* 63584 00163584 0000A48F */  lw         $4, 0x0($29)
    /* 63588 00163588 F867050C */  jal        BoxBarSoundOn
    /* 6358C 0016358C ED000524 */   addiu     $5, $0, 0xED
    /* 63590 00163590 6004080C */  jal        _ACTWait
    /* 63594 00163594 2D200000 */   daddu     $4, $0, $0
.align 2
  .L00163598:
    /* 63598 00163598 0000A48F */  lw         $4, 0x0($29)
    /* 6359C 0016359C F867050C */  jal        BoxBarSoundOn
    /* 635A0 001635A0 46010524 */   addiu     $5, $0, 0x146
    /* 635A4 001635A4 6004080C */  jal        _ACTWait
    /* 635A8 001635A8 01000424 */   addiu     $4, $0, 0x1
    /* 635AC 001635AC FAFF0010 */  b          .L00163598
    /* 635B0 001635B0 00000000 */   nop
endlabel func_00163500
    /* 635B4 001635B4 00000000 */  nop
```
