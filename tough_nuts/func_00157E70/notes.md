# func_00157E70 — parked

VRAM: 0x00157E70 (file_off 0x057E70)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/func_00157E70.s

## Attempt at 2026-06-22

**Reason parked:** override=permute

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/func_00157E70/func_00157E70.c`

Disassembly:

```
.align 3
nonmatching func_00157E70, 0x144

glabel func_00157E70
    /* 57E70 00157E70 80FFBD27 */  addiu      $29, $29, -0x80
    /* 57E74 00157E74 3000B0FF */  sd         $16, 0x30($29)
    /* 57E78 00157E78 6800B5E7 */  swc1       $f21, 0x68($29)
    /* 57E7C 00157E7C 2D808000 */  daddu      $16, $4, $0
    /* 57E80 00157E80 6000B4E7 */  swc1       $f20, 0x60($29)
    /* 57E84 00157E84 466D0046 */  mov.s      $f21, $f13
    /* 57E88 00157E88 4000B1FF */  sd         $17, 0x40($29)
    /* 57E8C 00157E8C 7000B6E7 */  swc1       $f22, 0x70($29)
    /* 57E90 00157E90 5000BFFF */  sd         $31, 0x50($29)
    /* 57E94 00157E94 4813040C */  jal        func_00104D20
    /* 57E98 00157E98 06650046 */   mov.s     $f20, $f12
    /* 57E9C 00157E9C 2041013C */  lui        $1, (0x41200000 >> 16)
    /* 57EA0 00157EA0 00B08144 */  mtc1       $1, $f22
    /* 57EA4 00157EA4 080002C6 */  lwc1       $f2, 0x8($16)
    /* 57EA8 00157EA8 000000C6 */  lwc1       $f0, 0x0($16)
    /* 57EAC 00157EAC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 57EB0 00157EB0 00088144 */  mtc1       $1, $f1
    /* 57EB4 00157EB4 1400B4E7 */  swc1       $f20, 0x14($29)
    /* 57EB8 00157EB8 1000A0E7 */  swc1       $f0, 0x10($29)
    /* 57EBC 00157EBC 1800A2E7 */  swc1       $f2, 0x18($29)
    /* 57EC0 00157EC0 1C00A1E7 */  swc1       $f1, 0x1C($29)
    /* 57EC4 00157EC4 1000A2DF */  ld         $2, 0x10($29)
    /* 57EC8 00157EC8 1800A3DF */  ld         $3, 0x18($29)
    /* 57ECC 00157ECC 2400B5E7 */  swc1       $f21, 0x24($29)
    /* 57ED0 00157ED0 2000A0E7 */  swc1       $f0, 0x20($29)
    /* 57ED4 00157ED4 2800A2E7 */  swc1       $f2, 0x28($29)
    /* 57ED8 00157ED8 2C00A1E7 */  swc1       $f1, 0x2C($29)
    /* 57EDC 00157EDC 0000A2FF */  sd         $2, 0x0($29)
    /* 57EE0 00157EE0 0800A3FF */  sd         $3, 0x8($29)
    /* 57EE4 00157EE4 2000A2DF */  ld         $2, 0x20($29)
    /* 57EE8 00157EE8 2800A3DF */  ld         $3, 0x28($29)
    /* 57EEC 00157EEC 1000A2FF */  sd         $2, 0x10($29)
    /* 57EF0 00157EF0 1E14040C */  jal        func_00105078
    /* 57EF4 00157EF4 1800A3FF */   sd        $3, 0x18($29)
    /* 57EF8 00157EF8 A862040C */  jal        _UnitMatrix
    /* 57EFC 00157EFC 2D204000 */   daddu     $4, $2, $0
    /* 57F00 00157F00 1647040C */  jal        gif_SpriteOffset
    /* 57F04 00157F04 0B000424 */   addiu     $4, $0, 0xB
    /* 57F08 00157F08 2800103C */  lui        $16, %hi(D_0027E730)
    /* 57F0C 00157F0C 1000B127 */  addiu      $17, $29, 0x10
    /* 57F10 00157F10 30E71026 */  addiu      $16, $16, %lo(D_0027E730)
    /* 57F14 00157F14 2D202002 */  daddu      $4, $17, $0
    /* 57F18 00157F18 2D380002 */  daddu      $7, $16, $0
    /* 57F1C 00157F1C 2D280002 */  daddu      $5, $16, $0
    /* 57F20 00157F20 2D400000 */  daddu      $8, $0, $0
    /* 57F24 00157F24 7C47070C */  jal        func_001D1DF0
    /* 57F28 00157F28 2D30A003 */   daddu     $6, $29, $0
    /* 57F2C 00157F2C 4813040C */  jal        func_00104D20
    /* 57F30 00157F30 00000000 */   nop
    /* 57F34 00157F34 2A14040C */  jal        func_001050A8
    /* 57F38 00157F38 2D20A003 */   daddu     $4, $29, $0
    /* 57F3C 00157F3C 06B30046 */  mov.s      $f12, $f22
    /* 57F40 00157F40 2D200002 */  daddu      $4, $16, $0
    /* 57F44 00157F44 04000524 */  addiu      $5, $0, 0x4
    /* 57F48 00157F48 7679040C */  jal        reg_dispBoxLine
    /* 57F4C 00157F4C 04000624 */   addiu     $6, $0, 0x4
    /* 57F50 00157F50 1A14040C */  jal        MatrixDrive_PopMatrix
    /* 57F54 00157F54 00000000 */   nop
    /* 57F58 00157F58 4813040C */  jal        func_00104D20
    /* 57F5C 00157F5C 00000000 */   nop
    /* 57F60 00157F60 2A14040C */  jal        func_001050A8
    /* 57F64 00157F64 2D202002 */   daddu     $4, $17, $0
    /* 57F68 00157F68 06B30046 */  mov.s      $f12, $f22
    /* 57F6C 00157F6C 2D200002 */  daddu      $4, $16, $0
    /* 57F70 00157F70 04000524 */  addiu      $5, $0, 0x4
    /* 57F74 00157F74 7679040C */  jal        reg_dispBoxLine
    /* 57F78 00157F78 04000624 */   addiu     $6, $0, 0x4
    /* 57F7C 00157F7C 1A14040C */  jal        MatrixDrive_PopMatrix
    /* 57F80 00157F80 00000000 */   nop
    /* 57F84 00157F84 743E040C */  jal        func_0010F9D0
    /* 57F88 00157F88 00000000 */   nop
    /* 57F8C 00157F8C 1A14040C */  jal        MatrixDrive_PopMatrix
    /* 57F90 00157F90 00000000 */   nop
    /* 57F94 00157F94 5000BFDF */  ld         $31, 0x50($29)
    /* 57F98 00157F98 4000B1DF */  ld         $17, 0x40($29)
    /* 57F9C 00157F9C 3000B0DF */  ld         $16, 0x30($29)
    /* 57FA0 00157FA0 7000B6C7 */  lwc1       $f22, 0x70($29)
    /* 57FA4 00157FA4 6800B5C7 */  lwc1       $f21, 0x68($29)
    /* 57FA8 00157FA8 6000B4C7 */  lwc1       $f20, 0x60($29)
    /* 57FAC 00157FAC 0800E003 */  jr         $31
    /* 57FB0 00157FB0 8000BD27 */   addiu     $29, $29, 0x80
endlabel func_00157E70
    /* 57FB4 00157FB4 00000000 */  nop
```
