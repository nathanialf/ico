# func_0013B7E0 — parked

VRAM: 0x0013B7E0 (file_off 0x03B7E0)
Asm source: asm/nonmatchings/ios/pad/func_0013B7E0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (ANCHOR,MEM_BARRIER,REG)

**TU:** `ios/pad.c`

**Seed:** `tough_nuts/func_0013B7E0/func_0013B7E0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631970, 1

.align 3
nonmatching func_0013B7E0, 0x78

glabel func_0013B7E0
    /* 3B7E0 0013B7E0 70FFBD27 */  addiu      $29, $29, -0x90
    /* 3B7E4 0013B7E4 7000B1FF */  sd         $17, 0x70($29)
    /* 3B7E8 0013B7E8 6000B0FF */  sd         $16, 0x60($29)
    /* 3B7EC 0013B7EC 2D888000 */  daddu      $17, $4, $0
    /* 3B7F0 0013B7F0 8000BFFF */  sd         $31, 0x80($29)
    /* 3B7F4 0013B7F4 2000B027 */  addiu      $16, $29, 0x20
    /* 3B7F8 0013B7F8 2D200002 */  daddu      $4, $16, $0
    /* 3B7FC 0013B7FC 1000A0C4 */  lwc1       $f0, 0x10($5)
    /* 3B800 0013B800 0C00A1C4 */  lwc1       $f1, 0xC($5)
    /* 3B804 0013B804 07000046 */  neg.s      $f0, $f0
    /* 3B808 0013B808 1400A0AF */  sw         $0, 0x14($29)
    /* 3B80C 0013B80C 1000A1E7 */  swc1       $f1, 0x10($29)
    /* 3B810 0013B810 1C00A0AF */  sw         $0, 0x1C($29)
    /* 3B814 0013B814 1800A0E7 */  swc1       $f0, 0x18($29)
    /* 3B818 0013B818 1000A2DF */  ld         $2, 0x10($29)
    /* 3B81C 0013B81C 1800A3DF */  ld         $3, 0x18($29)
    /* 3B820 0013B820 8090858F */  lw         $5, (D_00631970) /* gp_rel: (D_00631970) */
    /* 3B824 0013B824 0000A2FF */  sd         $2, 0x0($29)
    /* 3B828 0013B828 0800A3FF */  sd         $3, 0x8($29)
    /* 3B82C 0013B82C 6C0E090C */  jal        sceVu0TransposeMatrix
    /* 3B830 0013B830 8000A524 */   addiu     $5, $5, 0x80
    /* 3B834 0013B834 2D202002 */  daddu      $4, $17, $0
    /* 3B838 0013B838 2D280002 */  daddu      $5, $16, $0
    /* 3B83C 0013B83C 2E0E090C */  jal        sceVu0ApplyMatrix
    /* 3B840 0013B840 2D30A003 */   daddu     $6, $29, $0
    /* 3B844 0013B844 8000BFDF */  ld         $31, 0x80($29)
    /* 3B848 0013B848 7000B1DF */  ld         $17, 0x70($29)
    /* 3B84C 0013B84C 6000B0DF */  ld         $16, 0x60($29)
    /* 3B850 0013B850 0800E003 */  jr         $31
    /* 3B854 0013B854 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_0013B7E0
```
