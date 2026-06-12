# func_00246690 — parked

VRAM: 0x00246690 (file_off 0x146690)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00246690.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00246690/func_00246690.c`

Disassembly:

```
.align 3
nonmatching func_00246690, 0x70

glabel func_00246690
    /* 146690 00246690 5500033C */  lui        $3, %hi(D_0054AB34)
    /* 146694 00246694 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 146698 00246698 34AB628C */  lw         $2, %lo(D_0054AB34)($3)
    /* 14669C 0024669C 2D288000 */  daddu      $5, $4, $0
    /* 1466A0 002466A0 2000BFFF */  sd         $31, 0x20($29)
    /* 1466A4 002466A4 11004004 */  bltz       $2, .L002466EC
    /* 1466A8 002466A8 1000B0FF */   sd        $16, 0x10($29)
    /* 1466AC 002466AC 7100073C */  lui        $7, %hi(D_0070F680)
    /* 1466B0 002466B0 7100043C */  lui        $4, %hi(D_0070F600)
    /* 1466B4 002466B4 80F6E5AC */  sw         $5, %lo(D_0070F680)($7)
    /* 1466B8 002466B8 7100103C */  lui        $16, %hi(D_0070F640)
    /* 1466BC 002466BC 00F68424 */  addiu      $4, $4, %lo(D_0070F600)
    /* 1466C0 002466C0 80F6E724 */  addiu      $7, $7, %lo(D_0070F680)
    /* 1466C4 002466C4 0000A0AF */  sw         $0, 0x0($29)
    /* 1466C8 002466C8 01000524 */  addiu      $5, $0, 0x1
    /* 1466CC 002466CC 2D300000 */  daddu      $6, $0, $0
    /* 1466D0 002466D0 04000824 */  addiu      $8, $0, 0x4
    /* 1466D4 002466D4 40F60926 */  addiu      $9, $16, %lo(D_0070F640)
    /* 1466D8 002466D8 04000A24 */  addiu      $10, $0, 0x4
    /* 1466DC 002466DC 5E0A090C */  jal        func_00242978
    /* 1466E0 002466E0 2D580000 */   daddu     $11, $0, $0
    /* 1466E4 002466E4 02004104 */  bgez       $2, .L002466F0
    /* 1466E8 002466E8 40F6028E */   lw        $2, %lo(D_0070F640)($16)
.align 2
  .L002466EC:
    /* 1466EC 002466EC 2D100000 */  daddu      $2, $0, $0
.align 2
  .L002466F0:
    /* 1466F0 002466F0 2000BFDF */  ld         $31, 0x20($29)
    /* 1466F4 002466F4 1000B0DF */  ld         $16, 0x10($29)
    /* 1466F8 002466F8 0800E003 */  jr         $31
    /* 1466FC 002466FC 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_00246690
```
