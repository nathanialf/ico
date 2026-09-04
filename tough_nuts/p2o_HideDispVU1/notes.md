# GetYUnitVectorOfQuaternion — parked

VRAM: 0x0010E8B8 (file_off 0x00E8B8)
Asm source: asm/aug6/nonmatchings/seki/src/DisplayP2O/GetYUnitVectorOfQuaternion.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=14). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `seki/src/DisplayP2O.c`

**Seed:** `tough_nuts/GetYUnitVectorOfQuaternion/GetYUnitVectorOfQuaternion.c`

Disassembly:

```
.align 3
nonmatching GetYUnitVectorOfQuaternion, 0x8C

glabel GetYUnitVectorOfQuaternion
    /* E8B8 0010E8B8 D0FFBD27 */  addiu      $29, $29, -0x30
    /* E8BC 0010E8BC 0040013C */  lui        $1, (0x40000000 >> 16)
    /* E8C0 0010E8C0 00608144 */  mtc1       $1, $f12
    /* E8C4 0010E8C4 1000B0FF */  sd         $16, 0x10($29)
    /* E8C8 0010E8C8 2000BFFF */  sd         $31, 0x20($29)
    /* E8CC 0010E8CC 2D808000 */  daddu      $16, $4, $0
    /* E8D0 0010E8D0 0800A4C4 */  lwc1       $f4, 0x8($5)
    /* E8D4 0010E8D4 0000A0C4 */  lwc1       $f0, 0x0($5)
    /* E8D8 0010E8D8 0C00A3C4 */  lwc1       $f3, 0xC($5)
    /* E8DC 0010E8DC 82210446 */  mul.s      $f6, $f4, $f4
    /* E8E0 0010E8E0 82000046 */  mul.s      $f2, $f0, $f0
    /* E8E4 0010E8E4 0400A5C4 */  lwc1       $f5, 0x4($5)
    /* E8E8 0010E8E8 C2190046 */  mul.s      $f7, $f3, $f0
    /* E8EC 0010E8EC 0C00A0AF */  sw         $0, 0xC($29)
    /* E8F0 0010E8F0 42280446 */  mul.s      $f1, $f5, $f4
    /* E8F4 0010E8F4 2D28A003 */  daddu      $5, $29, $0
    /* E8F8 0010E8F8 80100646 */  add.s      $f2, $f2, $f6
    /* E8FC 0010E8FC 02000546 */  mul.s      $f0, $f0, $f5
    /* E900 0010E900 C2180446 */  mul.s      $f3, $f3, $f4
    /* E904 0010E904 41080746 */  sub.s      $f1, $f1, $f7
    /* E908 0010E908 87100046 */  neg.s      $f2, $f2
    /* E90C 0010E90C 00000346 */  add.s      $f0, $f0, $f3
    /* E910 0010E910 0800A1E7 */  swc1       $f1, 0x8($29)
    /* E914 0010E914 0400A2E7 */  swc1       $f2, 0x4($29)
    /* E918 0010E918 0662040C */  jal        _ScaleVectorXYZ
    /* E91C 0010E91C 0000A0E7 */   swc1      $f0, 0x0($29)
    /* E920 0010E920 040000C6 */  lwc1       $f0, 0x4($16)
    /* E924 0010E924 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* E928 0010E928 00088144 */  mtc1       $1, $f1
    /* E92C 0010E92C 2000BFDF */  ld         $31, 0x20($29)
    /* E930 0010E930 00000146 */  add.s      $f0, $f0, $f1
    /* E934 0010E934 040000E6 */  swc1       $f0, 0x4($16)
    /* E938 0010E938 1000B0DF */  ld         $16, 0x10($29)
    /* E93C 0010E93C 0800E003 */  jr         $31
    /* E940 0010E940 3000BD27 */   addiu     $29, $29, 0x30
endlabel GetYUnitVectorOfQuaternion
    /* E944 0010E944 00000000 */  nop
```
