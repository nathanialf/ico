# func_001C6228 — parked

VRAM: 0x001C6228 (file_off 0x0C6228)
Asm source: asm/aug6/nonmatchings/sugipon/src/clothTest/func_001C6228.s

## Attempt at 2026-06-17

**Reason parked:** rc4 best clean (neg in asm + C add/div); residual = add.s hoisted before func_00240008 (callee-saved f20 sum gives scheduler free rein); confirmed scheduler-tie across 30 distinct pure-C hypotheses + asm-barrier variants (rc2 daddu-a0 tie). permuter-class per orig sweep.

**TU:** `sugipon/src/clothTest.c`

**Seed:** `tough_nuts/func_001C6228/func_001C6228.c`

Disassembly:

```
.align 3
nonmatching func_001C6228, 0xBC

glabel func_001C6228
    /* C6228 001C6228 B0FFBD27 */  addiu      $29, $29, -0x50
    /* C622C 001C622C 2000B1FF */  sd         $17, 0x20($29)
    /* C6230 001C6230 1000B0FF */  sd         $16, 0x10($29)
    /* C6234 001C6234 2D888000 */  daddu      $17, $4, $0
    /* C6238 001C6238 2D80A000 */  daddu      $16, $5, $0
    /* C623C 001C623C 3000BFFF */  sd         $31, 0x30($29)
    /* C6240 001C6240 4800B5E7 */  swc1       $f21, 0x48($29)
    /* C6244 001C6244 4000B4E7 */  swc1       $f20, 0x40($29)
    /* C6248 001C6248 000001DA */  lqc2       $vf1, 0x0($16)
    /* C624C 001C624C 0000C2D8 */  lqc2       $vf2, 0x0($6)
    /* C6250 001C6250 EA08C24B */  vmul.xyz   $vf3, $vf1, $vf2
    /* C6254 001C6254 C118034B */  vaddy.x    $vf3, $vf3, $vf3y
    /* C6258 001C6258 C218034B */  vaddz.x    $vf3, $vf3, $vf3z
    /* C625C 001C625C C318024B */  vaddw.x    $vf3, $vf3, $vf2w
    /* C6260 001C6260 00182248 */  qmfc2.ni   $2, $vf3
    /* C6264 001C6264 00A88244 */  mtc1       $2, $f21
    /* C6268 001C6268 10000526 */  addiu      $5, $16, 0x10
    /* C626C 001C626C 0000A1D8 */  lqc2       $vf1, 0x0($5)
    /* C6270 001C6270 0000C2D8 */  lqc2       $vf2, 0x0($6)
    /* C6274 001C6274 EA08C24B */  vmul.xyz   $vf3, $vf1, $vf2
    /* C6278 001C6278 C118034B */  vaddy.x    $vf3, $vf3, $vf3y
    /* C627C 001C627C C218034B */  vaddz.x    $vf3, $vf3, $vf3z
    /* C6280 001C6280 C318024B */  vaddw.x    $vf3, $vf3, $vf2w
    /* C6284 001C6284 00182248 */  qmfc2.ni   $2, $vf3
    /* C6288 001C6288 00A08244 */  mtc1       $2, $f20
    /* C628C 001C628C 07A50046 */  neg.s      $f20, $f20
    /* C6290 001C6290 2D300002 */  daddu      $6, $16, $0
    /* C6294 001C6294 0200090C */  jal        func_00240008
    /* C6298 001C6298 2D20A003 */   daddu     $4, $29, $0
    /* C629C 001C629C 00AD1446 */  add.s      $f20, $f21, $f20
    /* C62A0 001C62A0 2D20A003 */  daddu      $4, $29, $0
    /* C62A4 001C62A4 00000000 */  nop
    /* C62A8 001C62A8 00000000 */  nop
    /* C62AC 001C62AC 03AB1446 */  div.s      $f12, $f21, $f20
    /* C62B0 001C62B0 5A02090C */  jal        func_00240968
    /* C62B4 001C62B4 2D28A003 */   daddu     $5, $29, $0
    /* C62B8 001C62B8 2D202002 */  daddu      $4, $17, $0
    /* C62BC 001C62BC 2D280002 */  daddu      $5, $16, $0
    /* C62C0 001C62C0 5E17040C */  jal        MatrixDrive_TurnZObjectMatrixXY
    /* C62C4 001C62C4 2D30A003 */   daddu     $6, $29, $0
    /* C62C8 001C62C8 3000BFDF */  ld         $31, 0x30($29)
    /* C62CC 001C62CC 2000B1DF */  ld         $17, 0x20($29)
    /* C62D0 001C62D0 1000B0DF */  ld         $16, 0x10($29)
    /* C62D4 001C62D4 4800B5C7 */  lwc1       $f21, 0x48($29)
    /* C62D8 001C62D8 4000B4C7 */  lwc1       $f20, 0x40($29)
    /* C62DC 001C62DC 0800E003 */  jr         $31
    /* C62E0 001C62E0 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_001C6228
    /* C62E4 001C62E4 00000000 */  nop
```
