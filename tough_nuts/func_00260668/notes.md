# func_00260668 — parked

VRAM: 0x00260668 (file_off 0x160668)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00260668.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00260668/func_00260668.c`

Disassembly:

```
.align 3
nonmatching func_00260668, 0x50

glabel func_00260668
    /* 160668 00260668 70FFBD27 */  addiu      $29, $29, -0x90
    /* 16066C 0026066C 55000C3C */  lui        $12, %hi(D_0054D504)
    /* 160670 00260670 5800A5FF */  sd         $5, 0x58($29)
    /* 160674 00260674 6000A6FF */  sd         $6, 0x60($29)
    /* 160678 00260678 2D288000 */  daddu      $5, $4, $0
    /* 16067C 0026067C 0000BFFF */  sd         $31, 0x0($29)
    /* 160680 00260680 5800A627 */  addiu      $6, $29, 0x58
    /* 160684 00260684 6800A7FF */  sd         $7, 0x68($29)
    /* 160688 00260688 7000A8FF */  sd         $8, 0x70($29)
    /* 16068C 0026068C 7800A9FF */  sd         $9, 0x78($29)
    /* 160690 00260690 8000AAFF */  sd         $10, 0x80($29)
    /* 160694 00260694 8800ABFF */  sd         $11, 0x88($29)
    /* 160698 00260698 04D5828D */  lw         $2, %lo(D_0054D504)($12)
    /* 16069C 0026069C 0800438C */  lw         $3, 0x8($2)
    /* 1606A0 002606A0 540062AC */  sw         $2, 0x54($3)
    /* 1606A4 002606A4 408B090C */  jal        func_00262D00
    /* 1606A8 002606A8 0800448C */   lw        $4, 0x8($2)
    /* 1606AC 002606AC 0000BFDF */  ld         $31, 0x0($29)
    /* 1606B0 002606B0 0800E003 */  jr         $31
    /* 1606B4 002606B4 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_00260668
```
