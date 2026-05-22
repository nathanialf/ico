# func_001BE558 — parked

VRAM: 0x001BE558 (file_off 0x0BE558)
Asm source: asm/nonmatchings/src/box/func_001BE558.s

## Attempt at 2026-05-22

**Reason parked:** iter 8: structure matches modulo FP scheduling + 5 byte diffs; XOR == arg test, 10-entry jtbl with 2 unique labels; needs slinky regen for jtbl_006186E0 placement

**TU:** `src/box.c`

**Seed:** `tough_nuts/func_001BE558/func_001BE558.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631168, 1

.align 3
nonmatching func_001BE558, 0x150

glabel func_001BE558
    /* BE558 001BE558 F0FEBD27 */  addiu      $29, $29, -0x110
    /* BE55C 001BE55C F041013C */  lui        $1, (0x41F00000 >> 16)
    /* BE560 001BE560 00088144 */  mtc1       $1, $f1
    /* BE564 001BE564 F000B2FF */  sd         $18, 0xF0($29)
    /* BE568 001BE568 E000B1FF */  sd         $17, 0xE0($29)
    /* BE56C 001BE56C 0001BFFF */  sd         $31, 0x100($29)
    /* BE570 001BE570 2D88A000 */  daddu      $17, $5, $0
    /* BE574 001BE574 D000B0FF */  sd         $16, 0xD0($29)
    /* BE578 001BE578 5C01228E */  lw         $2, 0x15C($17)
    /* BE57C 001BE57C D80340C4 */  lwc1       $f0, 0x3D8($2)
    /* BE580 001BE580 34080046 */  c.lt.s     $f1, $f0
    /* BE584 001BE584 00000000 */  nop
    /* BE588 001BE588 02000145 */  bc1t       .L001BE594
    /* BE58C 001BE58C 2D908000 */   daddu     $18, $4, $0
    /* BE590 001BE590 06080046 */  mov.s      $f0, $f1
.align 2
  .L001BE594:
    /* BE594 001BE594 C000B027 */  addiu      $16, $29, 0xC0
    /* BE598 001BE598 7000A0E7 */  swc1       $f0, 0x70($29)
    /* BE59C 001BE59C 2D200002 */  daddu      $4, $16, $0
    /* BE5A0 001BE5A0 4211040C */  jal        func_00104508
    /* BE5A4 001BE5A4 2D282002 */   daddu     $5, $17, $0
    /* BE5A8 001BE5A8 5C01228E */  lw         $2, 0x15C($17)
    /* BE5AC 001BE5AC 2D20A003 */  daddu      $4, $29, $0
    /* BE5B0 001BE5B0 2041013C */  lui        $1, (0x41200000 >> 16)
    /* BE5B4 001BE5B4 00108144 */  mtc1       $1, $f2
    /* BE5B8 001BE5B8 2D280002 */  daddu      $5, $16, $0
    /* BE5BC 001BE5BC 700240C4 */  lwc1       $f0, 0x270($2)
    /* BE5C0 001BE5C0 C400A1C7 */  lwc1       $f1, 0xC4($29)
    /* BE5C4 001BE5C4 00000246 */  add.s      $f0, $f0, $f2
    /* BE5C8 001BE5C8 40080046 */  add.s      $f1, $f1, $f0
    /* BE5CC 001BE5CC C017040C */  jal        func_00105F00
    /* BE5D0 001BE5D0 C400A1E7 */   swc1      $f1, 0xC4($29)
    /* BE5D4 001BE5D4 2D280002 */  daddu      $5, $16, $0
    /* BE5D8 001BE5D8 C017040C */  jal        func_00105F00
    /* BE5DC 001BE5DC 1000A427 */   addiu     $4, $29, 0x10
    /* BE5E0 001BE5E0 FFFF0224 */  addiu      $2, $0, -0x1
    /* BE5E4 001BE5E4 7400B2AF */  sw         $18, 0x74($29)
    /* BE5E8 001BE5E8 7800A2AF */  sw         $2, 0x78($29)
    /* BE5EC 001BE5EC 2D20A003 */  daddu      $4, $29, $0
    /* BE5F0 001BE5F0 32A1050C */  jal        func_001684C8
    /* BE5F4 001BE5F4 7C00A0AF */   sw        $0, 0x7C($29)
    /* BE5F8 001BE5F8 8800A28F */  lw         $2, 0x88($29)
    /* BE5FC 001BE5FC 25004010 */  beqz       $2, .L001BE694
    /* BE600 001BE600 0001BFDF */   ld        $31, 0x100($29)
    /* BE604 001BE604 5C01258E */  lw         $5, 0x15C($17)
    /* BE608 001BE608 D804A28C */  lw         $2, 0x4D8($5)
    /* BE60C 001BE60C F9FF4424 */  addiu      $4, $2, -0x7
    /* BE610 001BE610 0A00832C */  sltiu      $3, $4, 0xA
    /* BE614 001BE614 0B006010 */  beqz       $3, .L001BE644
    /* BE618 001BE618 6200023C */   lui       $2, %hi(jtbl_006186E0)
    /* BE61C 001BE61C 80180400 */  sll        $3, $4, 2
    /* BE620 001BE620 E0864224 */  addiu      $2, $2, %lo(jtbl_006186E0)
    /* BE624 001BE624 21186200 */  addu       $3, $3, $2
    /* BE628 001BE628 0000648C */  lw         $4, 0x0($3)
    /* BE62C 001BE62C 08008000 */  jr         $4
    /* BE630 001BE630 00000000 */   nop
.align 2
  jlabel .L001BE634
    /* BE634 001BE634 8001A28C */  lw         $2, 0x180($5)
    /* BE638 001BE638 26105200 */  xor        $2, $2, $18
    /* BE63C 001BE63C 02000010 */  b          .L001BE648
    /* BE640 001BE640 0100422C */   sltiu     $2, $2, 0x1
.align 2
  jlabel .L001BE644
    /* BE644 001BE644 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L001BE648:
    /* BE648 001BE648 11004010 */  beqz       $2, .L001BE690
    /* BE64C 001BE64C 7000ACC7 */   lwc1      $f12, 0x70($29)
    /* BE650 001BE650 2D282002 */  daddu      $5, $17, $0
    /* BE654 001BE654 4842013C */  lui        $1, (0x42480000 >> 16)
    /* BE658 001BE658 00008144 */  mtc1       $1, $f0
    /* BE65C 001BE65C 2D204002 */  daddu      $4, $18, $0
    /* BE660 001BE660 788881C7 */  lwc1       $f1, (D_00631168) /* gp_rel: (D_00631168) */
    /* BE664 001BE664 01000624 */  addiu      $6, $0, 0x1
    /* BE668 001BE668 00630046 */  add.s      $f12, $f12, $f0
    /* BE66C 001BE66C C842013C */  lui        $1, (0x42C80000 >> 16)
    /* BE670 001BE670 00688144 */  mtc1       $1, $f13
    /* BE674 001BE674 003F013C */  lui        $1, (0x3F000000 >> 16)
    /* BE678 001BE678 00708144 */  mtc1       $1, $f14
    /* BE67C 001BE67C 00788044 */  mtc1       $0, $f15
    /* BE680 001BE680 120F040C */  jal        func_00103C48
    /* BE684 001BE684 02630146 */   mul.s     $f12, $f12, $f1
    /* BE688 001BE688 160A040C */  jal        func_00102858
    /* BE68C 001BE68C 2D204002 */   daddu     $4, $18, $0
.align 2
  .L001BE690:
    /* BE690 001BE690 0001BFDF */  ld         $31, 0x100($29)
.align 2
  .L001BE694:
    /* BE694 001BE694 F000B2DF */  ld         $18, 0xF0($29)
    /* BE698 001BE698 E000B1DF */  ld         $17, 0xE0($29)
    /* BE69C 001BE69C D000B0DF */  ld         $16, 0xD0($29)
    /* BE6A0 001BE6A0 0800E003 */  jr         $31
    /* BE6A4 001BE6A4 1001BD27 */   addiu     $29, $29, 0x110
endlabel func_001BE558
```
