# func_00247820 — parked

VRAM: 0x00247820 (file_off 0x147820)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00247820.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00247820/func_00247820.c`

Disassembly:

```
.align 3
nonmatching func_00247820, 0x60

glabel func_00247820
    /* 147820 00247820 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 147824 00247824 5500023C */  lui        $2, %hi(D_0054AB40)
    /* 147828 00247828 0000B0FF */  sd         $16, 0x0($29)
    /* 14782C 0024782C 1000B1FF */  sd         $17, 0x10($29)
    /* 147830 00247830 2400103C */  lui        $16, %hi(func_00247A00)
    /* 147834 00247834 007A1026 */  addiu      $16, $16, %lo(func_00247A00)
    /* 147838 00247838 2D888000 */  daddu      $17, $4, $0
    /* 14783C 0024783C 40AB51AC */  sw         $17, %lo(D_0054AB40)($2)
    /* 147840 00247840 2D280002 */  daddu      $5, $16, $0
    /* 147844 00247844 2000BFFF */  sd         $31, 0x20($29)
    /* 147848 00247848 7400040C */  jal        func_001001D0
    /* 14784C 0024784C 01000424 */   addiu     $4, $0, 0x1
    /* 147850 00247850 2D280002 */  daddu      $5, $16, $0
    /* 147854 00247854 7400040C */  jal        func_001001D0
    /* 147858 00247858 02000424 */   addiu     $4, $0, 0x2
    /* 14785C 0024785C 2D280002 */  daddu      $5, $16, $0
    /* 147860 00247860 7400040C */  jal        func_001001D0
    /* 147864 00247864 03000424 */   addiu     $4, $0, 0x3
    /* 147868 00247868 2D102002 */  daddu      $2, $17, $0
    /* 14786C 0024786C 2000BFDF */  ld         $31, 0x20($29)
    /* 147870 00247870 1000B1DF */  ld         $17, 0x10($29)
    /* 147874 00247874 0000B0DF */  ld         $16, 0x0($29)
    /* 147878 00247878 0800E003 */  jr         $31
    /* 14787C 0024787C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_00247820
```
