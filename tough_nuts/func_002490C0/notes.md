# sceCdSync — parked

VRAM: 0x002490C0 (file_off 0x1490C0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/sceCdSync.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/sceCdSync/sceCdSync.c`

Disassembly:

```
.align 3
nonmatching sceCdSync, 0xA0

glabel sceCdSync
    /* 1490C0 002490C0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 1490C4 002490C4 2000BFFF */  sd         $31, 0x20($29)
    /* 1490C8 002490C8 1000B1FF */  sd         $17, 0x10($29)
    /* 1490CC 002490CC 15008014 */  bnez       $4, .L00249124
    /* 1490D0 002490D0 0000B0FF */   sd        $16, 0x0($29)
    /* 1490D4 002490D4 5500023C */  lui        $2, %hi(D_0054ABD0)
    /* 1490D8 002490D8 D0AB438C */  lw         $3, %lo(D_0054ABD0)($2)
    /* 1490DC 002490DC 03006018 */  blez       $3, .L002490EC
    /* 1490E0 002490E0 6300043C */   lui       $4, %hi(D_006289D8)
    /* 1490E4 002490E4 7806040C */  jal        scePrintf
    /* 1490E8 002490E8 D8898424 */   addiu     $4, $4, %lo(D_006289D8)
.align 2
  .L002490EC:
    /* 1490EC 002490EC 5500113C */  lui        $17, %hi(D_0054ABF0)
    /* 1490F0 002490F0 03000010 */  b          .L00249100
    /* 1490F4 002490F4 5500103C */   lui       $16, %hi(D_0054BD90)
.align 2
  .L002490F8:
    /* 1490F8 002490F8 3421090C */  jal        sceCdDelayThread
    /* 1490FC 002490FC 3C000424 */   addiu     $4, $0, 0x3C
.align 2
  .L00249100:
    /* 149100 00249100 F0AB228E */  lw         $2, %lo(D_0054ABF0)($17)
    /* 149104 00249104 FCFF4014 */  bnez       $2, .L002490F8
    /* 149108 00249108 00000000 */   nop
    /* 14910C 0024910C DA0A090C */  jal        sceSifCheckStatRpc
    /* 149110 00249110 90BD0426 */   addiu     $4, $16, %lo(D_0054BD90)
    /* 149114 00249114 F8FF4014 */  bnez       $2, .L002490F8
    /* 149118 00249118 2D100000 */   daddu     $2, $0, $0
    /* 14911C 0024911C 0C000010 */  b          .L00249150
    /* 149120 00249120 2000BFDF */   ld        $31, 0x20($29)
.align 2
  .L00249124:
    /* 149124 00249124 5500023C */  lui        $2, %hi(D_0054ABF0)
    /* 149128 00249128 F0AB438C */  lw         $3, %lo(D_0054ABF0)($2)
    /* 14912C 0024912C 07006014 */  bnez       $3, .L0024914C
    /* 149130 00249130 01000224 */   addiu     $2, $0, 0x1
    /* 149134 00249134 5500043C */  lui        $4, %hi(D_0054BD90)
    /* 149138 00249138 DA0A090C */  jal        sceSifCheckStatRpc
    /* 14913C 0024913C 90BD8424 */   addiu     $4, $4, %lo(D_0054BD90)
    /* 149140 00249140 02004014 */  bnez       $2, .L0024914C
    /* 149144 00249144 01000224 */   addiu     $2, $0, 0x1
    /* 149148 00249148 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0024914C:
    /* 14914C 0024914C 2000BFDF */  ld         $31, 0x20($29)
.align 2
  .L00249150:
    /* 149150 00249150 1000B1DF */  ld         $17, 0x10($29)
    /* 149154 00249154 0000B0DF */  ld         $16, 0x0($29)
    /* 149158 00249158 0800E003 */  jr         $31
    /* 14915C 0024915C 3000BD27 */   addiu     $29, $29, 0x30
endlabel sceCdSync
```
