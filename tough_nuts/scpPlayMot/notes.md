# scpPlayMot — parked

VRAM: 0x0017A5C0 (file_off 0x07A5C0)
Asm source: asm/aug6/nonmatchings/script/src/script/scpPlayMot.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=14). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `script/src/script.c`

**Seed:** `tough_nuts/scpPlayMot/scpPlayMot.c`

Disassembly:

```
.align 3
nonmatching scpPlayMot, 0x120

glabel scpPlayMot
    /* 7A5C0 0017A5C0 60FFBD27 */  addiu      $29, $29, -0xA0
    /* 7A5C4 0017A5C4 0000A4AF */  sw         $4, 0x0($29)
    /* 7A5C8 0017A5C8 7000BFFF */  sd         $31, 0x70($29)
    /* 7A5CC 0017A5CC 6000B4FF */  sd         $20, 0x60($29)
    /* 7A5D0 0017A5D0 5000B3FF */  sd         $19, 0x50($29)
    /* 7A5D4 0017A5D4 3000B1FF */  sd         $17, 0x30($29)
    /* 7A5D8 0017A5D8 2000B0FF */  sd         $16, 0x20($29)
    /* 7A5DC 0017A5DC 9000B6E7 */  swc1       $f22, 0x90($29)
    /* 7A5E0 0017A5E0 8800B5E7 */  swc1       $f21, 0x88($29)
    /* 7A5E4 0017A5E4 8000B4E7 */  swc1       $f20, 0x80($29)
    /* 7A5E8 0017A5E8 0000A28F */  lw         $2, 0x0($29)
    /* 7A5EC 0017A5EC 4000B2FF */  sd         $18, 0x40($29)
    /* 7A5F0 0017A5F0 6401528C */  lw         $18, 0x164($2)
    /* 7A5F4 0017A5F4 6CE3050C */  jal        func_00178DB0
    /* 7A5F8 0017A5F8 4404448E */   lw        $4, 0x444($18)
    /* 7A5FC 0017A5FC 23004010 */  beqz       $2, .L0017A68C
    /* 7A600 0017A600 2800143C */   lui       $20, %hi(D_00286910)
    /* 7A604 0017A604 480455C6 */  lwc1       $f21, 0x448($18)
    /* 7A608 0017A608 1000A427 */  addiu      $4, $29, 0x10
    /* 7A60C 0017A60C 0000B18F */  lw         $17, 0x0($29)
    /* 7A610 0017A610 07AD0046 */  neg.s      $f20, $f21
    /* 7A614 0017A614 2800143C */  lui        $20, %hi(D_00286910)
    /* 7A618 0017A618 00B08044 */  mtc1       $0, $f22
    /* 7A61C 0017A61C 3C11040C */  jal        GetRootMatrixTransOffset
    /* 7A620 0017A620 2D282002 */   daddu     $5, $17, $0
    /* 7A624 0017A624 1800133C */  lui        $19, %hi(func_0017C308)
.align 2
  .L0017A628:
    /* 7A628 0017A628 34B01446 */  c.lt.s     $f22, $f20
    /* 7A62C 0017A62C 00000000 */  nop
    /* 7A630 0017A630 06000045 */  bc1f       .L0017A64C
    /* 7A634 0017A634 2D800000 */   daddu     $16, $0, $0
    /* 7A638 0017A638 1400A0C7 */  lwc1       $f0, 0x14($29)
    /* 7A63C 0017A63C 00001546 */  add.s      $f0, $f0, $f21
    /* 7A640 0017A640 34A00046 */  c.lt.s     $f20, $f0
    /* 7A644 0017A644 05000010 */  b          .L0017A65C
    /* 7A648 0017A648 1400A0E7 */   swc1      $f0, 0x14($29)
.align 2
  .L0017A64C:
    /* 7A64C 0017A64C 1400A0C7 */  lwc1       $f0, 0x14($29)
    /* 7A650 0017A650 01001546 */  sub.s      $f0, $f0, $f21
    /* 7A654 0017A654 34001446 */  c.lt.s     $f0, $f20
    /* 7A658 0017A658 1400A0E7 */  swc1       $f0, 0x14($29)
.align 2
  .L0017A65C:
    /* 7A65C 0017A65C 03000045 */  bc1f       .L0017A66C
    /* 7A660 0017A660 2D202002 */   daddu     $4, $17, $0
    /* 7A664 0017A664 1400B4E7 */  swc1       $f20, 0x14($29)
    /* 7A668 0017A668 01001024 */  addiu      $16, $0, 0x1
.align 2
  .L0017A66C:
    /* 7A66C 0017A66C 48E4050C */  jal        func_00179120
    /* 7A670 0017A670 1000A527 */   addiu     $5, $29, 0x10
    /* 7A674 0017A674 6004080C */  jal        _ACTWait
    /* 7A678 0017A678 01000424 */   addiu     $4, $0, 0x1
    /* 7A67C 0017A67C EAFF0012 */  beqz       $16, .L0017A628
    /* 7A680 0017A680 10698226 */   addiu     $2, $20, %lo(D_00286910)
    /* 7A684 0017A684 04000010 */  b          .L0017A698
    /* 7A688 0017A688 08C36326 */   addiu     $3, $19, %lo(func_0017C308)
.align 2
  .L0017A68C:
    /* 7A68C 0017A68C 1800133C */  lui        $19, %hi(func_0017C308)
    /* 7A690 0017A690 10698226 */  addiu      $2, $20, %lo(D_00286910)
    /* 7A694 0017A694 08C36326 */  addiu      $3, $19, %lo(func_0017C308)
.align 2
  .L0017A698:
    /* 7A698 0017A698 0000A48F */  lw         $4, 0x0($29)
    /* 7A69C 0017A69C 89010524 */  addiu      $5, $0, 0x189
    /* 7A6A0 0017A6A0 B40042AE */  sw         $2, 0xB4($18)
    /* 7A6A4 0017A6A4 F867050C */  jal        BoxBarSoundOn
    /* 7A6A8 0017A6A8 040043AC */   sw        $3, 0x4($2)
    /* 7A6AC 0017A6AC 6004080C */  jal        _ACTWait
    /* 7A6B0 0017A6B0 2D200000 */   daddu     $4, $0, $0
    /* 7A6B4 0017A6B4 7000BFDF */  ld         $31, 0x70($29)
    /* 7A6B8 0017A6B8 6000B4DF */  ld         $20, 0x60($29)
    /* 7A6BC 0017A6BC 5000B3DF */  ld         $19, 0x50($29)
    /* 7A6C0 0017A6C0 4000B2DF */  ld         $18, 0x40($29)
    /* 7A6C4 0017A6C4 3000B1DF */  ld         $17, 0x30($29)
    /* 7A6C8 0017A6C8 2000B0DF */  ld         $16, 0x20($29)
    /* 7A6CC 0017A6CC 9000B6C7 */  lwc1       $f22, 0x90($29)
    /* 7A6D0 0017A6D0 8800B5C7 */  lwc1       $f21, 0x88($29)
    /* 7A6D4 0017A6D4 8000B4C7 */  lwc1       $f20, 0x80($29)
    /* 7A6D8 0017A6D8 0800E003 */  jr         $31
    /* 7A6DC 0017A6DC A000BD27 */   addiu     $29, $29, 0xA0
endlabel scpPlayMot
```
