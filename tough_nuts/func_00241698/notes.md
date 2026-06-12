# func_00241698 — parked

VRAM: 0x00241698 (file_off 0x141698)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00241698.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00241698/func_00241698.c`

Disassembly:

```
.align 3
nonmatching func_00241698, 0x58

glabel func_00241698
    /* 141698 00241698 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 14169C 0024169C 1000B1FF */  sd         $17, 0x10($29)
    /* 1416A0 002416A0 2D888000 */  daddu      $17, $4, $0
    /* 1416A4 002416A4 0000B0FF */  sd         $16, 0x0($29)
    /* 1416A8 002416A8 2000BFFF */  sd         $31, 0x20($29)
    /* 1416AC 002416AC 7A05090C */  jal        func_002415E8
    /* 1416B0 002416B0 2D80A000 */   daddu     $16, $5, $0
    /* 1416B4 002416B4 0000248E */  lw         $4, 0x0($17)
    /* 1416B8 002416B8 0070033C */  lui        $3, (0x70000000 >> 16)
    /* 1416BC 002416BC 25800302 */  or         $16, $16, $3
    /* 1416C0 002416C0 080022AE */  sw         $2, 0x8($17)
    /* 1416C4 002416C4 000090AC */  sw         $16, 0x0($4)
    /* 1416C8 002416C8 04008424 */  addiu      $4, $4, 0x4
    /* 1416CC 002416CC 0C0020AE */  sw         $0, 0xC($17)
    /* 1416D0 002416D0 04008224 */  addiu      $2, $4, 0x4
    /* 1416D4 002416D4 2000BFDF */  ld         $31, 0x20($29)
    /* 1416D8 002416D8 000022AE */  sw         $2, 0x0($17)
    /* 1416DC 002416DC 1000B1DF */  ld         $17, 0x10($29)
    /* 1416E0 002416E0 0000B0DF */  ld         $16, 0x0($29)
    /* 1416E4 002416E4 000080AC */  sw         $0, 0x0($4)
    /* 1416E8 002416E8 0800E003 */  jr         $31
    /* 1416EC 002416EC 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_00241698
```
