# func_0014A510 — parked

VRAM: 0x0014A510 (file_off 0x04A510)
Asm source: asm/aug6/nonmatchings/fumi/src/act-wish/func_0014A510.s

## Attempt at 2026-06-29

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=12). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/act-wish.c`

**Seed:** `tough_nuts/func_0014A510/func_0014A510.c`

Disassembly:

```
.align 3
nonmatching func_0014A510, 0x154

glabel func_0014A510
    /* 4A510 0014A510 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 4A514 0014A514 2D180000 */  daddu      $3, $0, $0
    /* 4A518 0014A518 3000B2FF */  sd         $18, 0x30($29)
    /* 4A51C 0014A51C 2000B1FF */  sd         $17, 0x20($29)
    /* 4A520 0014A520 2E00123C */  lui        $18, %hi(D_002E0100)
    /* 4A524 0014A524 1000B0FF */  sd         $16, 0x10($29)
    /* 4A528 0014A528 5D00113C */  lui        $17, %hi(D_005CA4B0)
    /* 4A52C 0014A52C 4000B3FF */  sd         $19, 0x40($29)
    /* 4A530 0014A530 2D80A000 */  daddu      $16, $5, $0
    /* 4A534 0014A534 0000A6AF */  sw         $6, 0x0($29)
    /* 4A538 0014A538 07107000 */  srav       $2, $16, $3
    /* 4A53C 0014A53C 00000000 */  nop
.align 2
  .L0014A540:
    /* 4A540 0014A540 01004230 */  andi       $2, $2, 0x1
    /* 4A544 0014A544 3C004010 */  beqz       $2, .L0014A638
    /* 4A548 0014A548 80980300 */   sll       $19, $3, 2
    /* 4A54C 0014A54C 2D500000 */  daddu      $10, $0, $0
    /* 4A550 0014A550 01006D24 */  addiu      $13, $3, 0x1
    /* 4A554 0014A554 00014526 */  addiu      $5, $18, %lo(D_002E0100)
    /* 4A558 0014A558 94001924 */  addiu      $25, $0, 0x94
    /* 4A55C 0014A55C 2D70A003 */  daddu      $14, $29, $0
    /* 4A560 0014A560 FFFF1834 */  ori        $24, $0, 0xFFFF
    /* 4A564 0014A564 FFFF0F3C */  lui        $15, %hi(D_FFFF0001)
    /* 4A568 0014A568 B0A42C26 */  addiu      $12, $17, %lo(D_005CA4B0)
    /* 4A56C 0014A56C 40040B24 */  addiu      $11, $0, 0x440
    /* 4A570 0014A570 18185901 */  mult       $3, $10, $25
    /* 4A574 0014A574 00000000 */  nop
.align 2
  .L0014A578:
    /* 4A578 0014A578 21107300 */  addu       $2, $3, $19
    /* 4A57C 0014A57C 21104500 */  addu       $2, $2, $5
    /* 4A580 0014A580 0000468C */  lw         $6, 0x0($2)
    /* 4A584 0014A584 2A180603 */  slt        $3, $24, $6
    /* 4A588 0014A588 20006010 */  beqz       $3, .L0014A60C
    /* 4A58C 0014A58C 2140CF00 */   addu      $8, $6, $15
    /* 4A590 0014A590 2D380000 */  daddu      $7, $0, $0
    /* 4A594 0014A594 80100800 */  sll        $2, $8, 2
    /* 4A598 0014A598 21104C00 */  addu       $2, $2, $12
    /* 4A59C 0014A59C 0000438C */  lw         $3, 0x0($2)
    /* 4A5A0 0014A5A0 0C006B10 */  beq        $3, $11, .L0014A5D4
    /* 4A5A4 0014A5A4 2D300001 */   daddu     $6, $8, $0
    /* 4A5A8 0014A5A8 01004925 */  addiu      $9, $10, 0x1
    /* 4A5AC 0014A5AC 00000000 */  nop
.align 2
  .L0014A5B0:
    /* 4A5B0 0014A5B0 0100C624 */  addiu      $6, $6, %lo(D_FFFF0001)
    /* 4A5B4 0014A5B4 0100E724 */  addiu      $7, $7, 0x1
    /* 4A5B8 0014A5B8 80100600 */  sll        $2, $6, 2
    /* 4A5BC 0014A5BC 21104C00 */  addu       $2, $2, $12
    /* 4A5C0 0014A5C0 0000438C */  lw         $3, 0x0($2)
    /* 4A5C4 0014A5C4 FAFF6B14 */  bne        $3, $11, .L0014A5B0
    /* 4A5C8 0014A5C8 00000000 */   nop
    /* 4A5CC 0014A5CC 02000010 */  b          .L0014A5D8
    /* 4A5D0 0014A5D0 00000000 */   nop
.align 2
  .L0014A5D4:
    /* 4A5D4 0014A5D4 01004925 */  addiu      $9, $10, 0x1
.align 2
  .L0014A5D8:
    /* 4A5D8 0014A5D8 0300E054 */  bnel       $7, $0, .L0014A5E8
    /* 4A5DC 0014A5DC 0000C28D */   lw        $2, 0x0($14)
    /* 4A5E0 0014A5E0 0B000010 */  b          .L0014A610
    /* 4A5E4 0014A5E4 40040624 */   addiu     $6, $0, 0x440
.align 2
  .L0014A5E8:
    /* 4A5E8 0014A5E8 0100E050 */  beql       $7, $0, .L0014A5F0
    /* 4A5EC 0014A5EC CD010000 */   break     0, 7
.align 2
  .L0014A5F0:
    /* 4A5F0 0014A5F0 1A004700 */  div        $0, $2, $7
    /* 4A5F4 0014A5F4 10180000 */  mfhi       $3
    /* 4A5F8 0014A5F8 21180301 */  addu       $3, $8, $3
    /* 4A5FC 0014A5FC 80180300 */  sll        $3, $3, 2
    /* 4A600 0014A600 21186C00 */  addu       $3, $3, $12
    /* 4A604 0014A604 02000010 */  b          .L0014A610
    /* 4A608 0014A608 0000668C */   lw        $6, 0x0($3)
.align 2
  .L0014A60C:
    /* 4A60C 0014A60C 01004925 */  addiu      $9, $10, 0x1
.align 2
  .L0014A610:
    /* 4A610 0014A610 0300CB10 */  beq        $6, $11, .L0014A620
    /* 4A614 0014A614 80100A00 */   sll       $2, $10, 2
    /* 4A618 0014A618 21104400 */  addu       $2, $2, $4
    /* 4A61C 0014A61C 000046AC */  sw         $6, 0x0($2)
.align 2
  .L0014A620:
    /* 4A620 0014A620 2D502001 */  daddu      $10, $9, $0
    /* 4A624 0014A624 47004229 */  slti       $2, $10, 0x47
    /* 4A628 0014A628 D3FF4014 */  bnez       $2, .L0014A578
    /* 4A62C 0014A62C 18185901 */   mult      $3, $10, $25
    /* 4A630 0014A630 03000010 */  b          .L0014A640
    /* 4A634 0014A634 2D18A001 */   daddu     $3, $13, $0
.align 2
  .L0014A638:
    /* 4A638 0014A638 01006D24 */  addiu      $13, $3, 0x1
    /* 4A63C 0014A63C 2D18A001 */  daddu      $3, $13, $0
.align 2
  .L0014A640:
    /* 4A640 0014A640 25006228 */  slti       $2, $3, 0x25
    /* 4A644 0014A644 BEFF4054 */  bnel       $2, $0, .L0014A540
    /* 4A648 0014A648 07107000 */   srav      $2, $16, $3
    /* 4A64C 0014A64C 4000B3DF */  ld         $19, 0x40($29)
    /* 4A650 0014A650 3000B2DF */  ld         $18, 0x30($29)
    /* 4A654 0014A654 2000B1DF */  ld         $17, 0x20($29)
    /* 4A658 0014A658 1000B0DF */  ld         $16, 0x10($29)
    /* 4A65C 0014A65C 0800E003 */  jr         $31
    /* 4A660 0014A660 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_0014A510
    /* 4A664 0014A664 00000000 */  nop
```
