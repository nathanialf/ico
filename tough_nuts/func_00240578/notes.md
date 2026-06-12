# func_00240578 — parked

VRAM: 0x00240578 (file_off 0x140578)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00240578.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00240578/func_00240578.c`

Disassembly:

```
.align 3
nonmatching func_00240578, 0x68

glabel func_00240578
    /* 140578 00240578 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 14057C 0024057C 0000B0FF */  sd         $16, 0x0($29)
    /* 140580 00240580 2D808000 */  daddu      $16, $4, $0
    /* 140584 00240584 3000B3FF */  sd         $19, 0x30($29)
    /* 140588 00240588 2000B2FF */  sd         $18, 0x20($29)
    /* 14058C 0024058C 2D980001 */  daddu      $19, $8, $0
    /* 140590 00240590 1000B1FF */  sd         $17, 0x10($29)
    /* 140594 00240594 2D90E000 */  daddu      $18, $7, $0
    /* 140598 00240598 4000BFFF */  sd         $31, 0x40($29)
    /* 14059C 0024059C 2000090C */  jal        func_00240080
    /* 1405A0 002405A0 2D88C000 */   daddu     $17, $6, $0
    /* 1405A4 002405A4 2D282002 */  daddu      $5, $17, $0
    /* 1405A8 002405A8 2000090C */  jal        func_00240080
    /* 1405AC 002405AC 10000426 */   addiu     $4, $16, 0x10
    /* 1405B0 002405B0 2D284002 */  daddu      $5, $18, $0
    /* 1405B4 002405B4 2000090C */  jal        func_00240080
    /* 1405B8 002405B8 20000426 */   addiu     $4, $16, 0x20
    /* 1405BC 002405BC 30000426 */  addiu      $4, $16, 0x30
    /* 1405C0 002405C0 2D286002 */  daddu      $5, $19, $0
    /* 1405C4 002405C4 4000BFDF */  ld         $31, 0x40($29)
    /* 1405C8 002405C8 3000B3DF */  ld         $19, 0x30($29)
    /* 1405CC 002405CC 2000B2DF */  ld         $18, 0x20($29)
    /* 1405D0 002405D0 1000B1DF */  ld         $17, 0x10($29)
    /* 1405D4 002405D4 0000B0DF */  ld         $16, 0x0($29)
    /* 1405D8 002405D8 20000908 */  j          func_00240080
    /* 1405DC 002405DC 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_00240578
```
