# func_00246968 — parked

VRAM: 0x00246968 (file_off 0x146968)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00246968.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00246968/func_00246968.c`

Disassembly:

```
.align 3
nonmatching func_00246968, 0x8C

glabel func_00246968
    /* 146968 00246968 B0FFBD27 */  addiu      $29, $29, -0x50
    /* 14696C 0024696C 2700023C */  lui        $2, %hi(D_00270A8C)
    /* 146970 00246970 3000B3FF */  sd         $19, 0x30($29)
    /* 146974 00246974 7100033C */  lui        $3, %hi(D_0070FA28)
    /* 146978 00246978 1000B1FF */  sd         $17, 0x10($29)
    /* 14697C 0024697C 8C0A5324 */  addiu      $19, $2, %lo(D_00270A8C)
    /* 146980 00246980 2000B2FF */  sd         $18, 0x20($29)
    /* 146984 00246984 28FA7124 */  addiu      $17, $3, %lo(D_0070FA28)
    /* 146988 00246988 4000BFFF */  sd         $31, 0x40($29)
    /* 14698C 0024698C 2D900000 */  daddu      $18, $0, $0
    /* 146990 00246990 0000B0FF */  sd         $16, 0x0($29)
    /* 146994 00246994 2D202002 */  daddu      $4, $17, $0
    /* 146998 00246998 2D286002 */  daddu      $5, $19, $0
    /* 14699C 0024699C 0981090C */  jal        func_00260424
    /* 1469A0 002469A0 04000624 */   addiu     $6, $0, 0x4
    /* 1469A4 002469A4 0B004010 */  beqz       $2, .L002469D4
    /* 1469A8 002469A8 5500103C */   lui       $16, %hi(D_0054AB3C)
    /* 1469AC 002469AC 2D202002 */  daddu      $4, $17, $0
    /* 1469B0 002469B0 3CAB058E */  lw         $5, %lo(D_0054AB3C)($16)
    /* 1469B4 002469B4 0981090C */  jal        func_00260424
    /* 1469B8 002469B8 04000624 */   addiu     $6, $0, 0x4
    /* 1469BC 002469BC 05004010 */  beqz       $2, .L002469D4
    /* 1469C0 002469C0 3CAB058E */   lw        $5, %lo(D_0054AB3C)($16)
    /* 1469C4 002469C4 2D206002 */  daddu      $4, $19, $0
    /* 1469C8 002469C8 0981090C */  jal        func_00260424
    /* 1469CC 002469CC 04000624 */   addiu     $6, $0, 0x4
    /* 1469D0 002469D0 2B900200 */  sltu       $18, $0, $2
.align 2
  .L002469D4:
    /* 1469D4 002469D4 2D104002 */  daddu      $2, $18, $0
    /* 1469D8 002469D8 4000BFDF */  ld         $31, 0x40($29)
    /* 1469DC 002469DC 3000B3DF */  ld         $19, 0x30($29)
    /* 1469E0 002469E0 2000B2DF */  ld         $18, 0x20($29)
    /* 1469E4 002469E4 1000B1DF */  ld         $17, 0x10($29)
    /* 1469E8 002469E8 0000B0DF */  ld         $16, 0x0($29)
    /* 1469EC 002469EC 0800E003 */  jr         $31
    /* 1469F0 002469F0 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_00246968
    /* 1469F4 002469F4 00000000 */  nop
```
