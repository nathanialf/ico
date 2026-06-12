# func_00249160 — parked

VRAM: 0x00249160 (file_off 0x149160)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00249160.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00249160/func_00249160.c`

Disassembly:

```
.align 3
nonmatching func_00249160, 0x6C

glabel func_00249160
    /* 149160 00249160 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 149164 00249164 1000BFFF */  sd         $31, 0x10($29)
    /* 149168 00249168 11008014 */  bnez       $4, .L002491B0
    /* 14916C 0024916C 0000B0FF */   sd        $16, 0x0($29)
    /* 149170 00249170 5500023C */  lui        $2, %hi(D_0054ABD0)
    /* 149174 00249174 D0AB438C */  lw         $3, %lo(D_0054ABD0)($2)
    /* 149178 00249178 03006018 */  blez       $3, .L00249188
    /* 14917C 0024917C 6300043C */   lui       $4, %hi(D_006289E8)
    /* 149180 00249180 7806040C */  jal        func_001019E0
    /* 149184 00249184 E8898424 */   addiu     $4, $4, %lo(D_006289E8)
.align 2
  .L00249188:
    /* 149188 00249188 03000010 */  b          .L00249198
    /* 14918C 0024918C 5500103C */   lui       $16, %hi(D_0054C608)
.align 2
  .L00249190:
    /* 149190 00249190 3421090C */  jal        func_002484D0
    /* 149194 00249194 3C000424 */   addiu     $4, $0, 0x3C
.align 2
  .L00249198:
    /* 149198 00249198 DA0A090C */  jal        func_00242B68
    /* 14919C 0024919C 08C60426 */   addiu     $4, $16, %lo(D_0054C608)
    /* 1491A0 002491A0 FBFF4014 */  bnez       $2, .L00249190
    /* 1491A4 002491A4 2D100000 */   daddu     $2, $0, $0
    /* 1491A8 002491A8 05000010 */  b          .L002491C0
    /* 1491AC 002491AC 1000BFDF */   ld        $31, 0x10($29)
.align 2
  .L002491B0:
    /* 1491B0 002491B0 5500043C */  lui        $4, %hi(D_0054C608)
    /* 1491B4 002491B4 DA0A090C */  jal        func_00242B68
    /* 1491B8 002491B8 08C68424 */   addiu     $4, $4, %lo(D_0054C608)
    /* 1491BC 002491BC 1000BFDF */  ld         $31, 0x10($29)
.align 2
  .L002491C0:
    /* 1491C0 002491C0 0000B0DF */  ld         $16, 0x0($29)
    /* 1491C4 002491C4 0800E003 */  jr         $31
    /* 1491C8 002491C8 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00249160
    /* 1491CC 002491CC 00000000 */  nop
```
