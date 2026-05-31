# func_001D9E10 — parked

VRAM: 0x001D9E10 (file_off 0x0D9E10)
Asm source: asm/nonmatchings/src/motionManager/func_001D9E10.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/motionManager.c`

**Seed:** `tough_nuts/func_001D9E10/func_001D9E10.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633F3C, 1

.align 3
nonmatching func_001D9E10, 0x7C

glabel func_001D9E10
    /* D9E10 001D9E10 F0FFBD27 */  addiu      $29, $29, -0x10
    /* D9E14 001D9E14 0000BFFF */  sd         $31, 0x0($29)
    /* D9E18 001D9E18 2E46040C */  jal        func_001118B8
    /* D9E1C 001D9E1C 0B000424 */   addiu     $4, $0, 0xB
    /* D9E20 001D9E20 05000524 */  addiu      $5, $0, 0x5
    /* D9E24 001D9E24 80000624 */  addiu      $6, $0, 0x80
    /* D9E28 001D9E28 EA47040C */  jal        func_00111FA8
    /* D9E2C 001D9E2C 01000424 */   addiu     $4, $0, 0x1
    /* D9E30 001D9E30 C813040C */  jal        func_00104F20
    /* D9E34 001D9E34 00000000 */   nop
    /* D9E38 001D9E38 9E14040C */  jal        func_00105278
    /* D9E3C 001D9E3C 00000000 */   nop
    /* D9E40 001D9E40 F60E090C */  jal        func_00243BD8
    /* D9E44 001D9E44 2D204000 */   daddu     $4, $2, $0
    /* D9E48 001D9E48 4CB6828F */  lw         $2, (D_00633F3C) /* gp_rel: (D_00633F3C) */
    /* D9E4C 001D9E4C B8014EC4 */  lwc1       $f14, 0x1B8($2)
    /* D9E50 001D9E50 B0014CC4 */  lwc1       $f12, 0x1B0($2)
    /* D9E54 001D9E54 C214040C */  jal        func_00105308
    /* D9E58 001D9E58 B4014DC4 */   lwc1      $f13, 0x1B4($2)
    /* D9E5C 001D9E5C 0041013C */  lui        $1, (0x41000000 >> 16)
    /* D9E60 001D9E60 00608144 */  mtc1       $1, $f12
    /* D9E64 001D9E64 46630046 */  mov.s      $f13, $f12
    /* D9E68 001D9E68 2C14040C */  jal        func_001050B0
    /* D9E6C 001D9E6C 86630046 */   mov.s     $f14, $f12
    /* D9E70 001D9E70 A253070C */  jal        func_001D4E88
    /* D9E74 001D9E74 FF000424 */   addiu     $4, $0, 0xFF
    /* D9E78 001D9E78 9A14040C */  jal        func_00105268
    /* D9E7C 001D9E7C 00000000 */   nop
    /* D9E80 001D9E80 0000BFDF */  ld         $31, 0x0($29)
    /* D9E84 001D9E84 8C3D0408 */  j          func_0010F630
    /* D9E88 001D9E88 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_001D9E10
    /* D9E8C 001D9E8C 00000000 */  nop
```
