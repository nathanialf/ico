# sceCdDelayThread — parked

VRAM: 0x002484D0 (file_off 0x1484D0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/sceCdDelayThread.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/sceCdDelayThread/sceCdDelayThread.c`

Disassembly:

```
.align 3
nonmatching sceCdDelayThread, 0x68

glabel sceCdDelayThread
    /* 1484D0 002484D0 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 1484D4 002484D4 01000224 */  addiu      $2, $0, 0x1
    /* 1484D8 002484D8 3000B1FF */  sd         $17, 0x30($29)
    /* 1484DC 002484DC FFFF9130 */  andi       $17, $4, 0xFFFF
    /* 1484E0 002484E0 2000B0FF */  sd         $16, 0x20($29)
    /* 1484E4 002484E4 0400A2AF */  sw         $2, 0x4($29)
    /* 1484E8 002484E8 0800A0AF */  sw         $0, 0x8($29)
    /* 1484EC 002484EC 1400A0AF */  sw         $0, 0x14($29)
    /* 1484F0 002484F0 4000BFFF */  sd         $31, 0x40($29)
    /* 1484F4 002484F4 4801040C */  jal        CreateSema
    /* 1484F8 002484F8 2D20A003 */   daddu     $4, $29, $0
    /* 1484FC 002484FC 2D804000 */  daddu      $16, $2, $0
    /* 148500 00248500 2500053C */  lui        $5, %hi(func_002484A4 + 0x4)
    /* 148504 00248504 2D300002 */  daddu      $6, $16, $0
    /* 148508 00248508 2D202002 */  daddu      $4, $17, $0
    /* 14850C 0024850C A800040C */  jal        SetAlarm
    /* 148510 00248510 A884A524 */   addiu     $5, $5, %lo(func_002484A4 + 0x4)
    /* 148514 00248514 5801040C */  jal        WaitSema
    /* 148518 00248518 2D200002 */   daddu     $4, $16, $0
    /* 14851C 0024851C 4C01040C */  jal        DeleteSema
    /* 148520 00248520 2D200002 */   daddu     $4, $16, $0
    /* 148524 00248524 4000BFDF */  ld         $31, 0x40($29)
    /* 148528 00248528 3000B1DF */  ld         $17, 0x30($29)
    /* 14852C 0024852C 2000B0DF */  ld         $16, 0x20($29)
    /* 148530 00248530 0800E003 */  jr         $31
    /* 148534 00248534 5000BD27 */   addiu     $29, $29, 0x50
endlabel sceCdDelayThread
```
