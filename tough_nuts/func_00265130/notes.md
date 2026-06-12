# func_00265130 — parked

VRAM: 0x00265130 (file_off 0x165130)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00265130.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (near-miss); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00265130/func_00265130.c`

Disassembly:

```
.align 3
nonmatching func_00265130, 0x54

glabel func_00265130
    /* 165130 00265130 5500023C */  lui        $2, %hi(D_0054D504)
    /* 165134 00265134 FF7F033C */  lui        $3, (0x7FFFFFFF >> 16)
    /* 165138 00265138 04D5488C */  lw         $8, %lo(D_0054D504)($2)
    /* 16513C 0026513C 90FFBD27 */  addiu      $29, $29, -0x70
    /* 165140 00265140 2D388000 */  daddu      $7, $4, $0
    /* 165144 00265144 FFFF6334 */  ori        $3, $3, (0x7FFFFFFF & 0xFFFF)
    /* 165148 00265148 08020224 */  addiu      $2, $0, 0x208
    /* 16514C 0026514C 6000BFFF */  sd         $31, 0x60($29)
    /* 165150 00265150 0C00A2A7 */  sh         $2, 0xC($29)
    /* 165154 00265154 2D20A003 */  daddu      $4, $29, $0
    /* 165158 00265158 1000A7AF */  sw         $7, 0x10($29)
    /* 16515C 0026515C 1400A3AF */  sw         $3, 0x14($29)
    /* 165160 00265160 5400A8AF */  sw         $8, 0x54($29)
    /* 165164 00265164 0000A7AF */  sw         $7, 0x0($29)
    /* 165168 00265168 408B090C */  jal        func_00262D00
    /* 16516C 0026516C 0800A3AF */   sw        $3, 0x8($29)
    /* 165170 00265170 0000A38F */  lw         $3, 0x0($29)
    /* 165174 00265174 6000BFDF */  ld         $31, 0x60($29)
    /* 165178 00265178 000060A0 */  sb         $0, 0x0($3)
    /* 16517C 0026517C 0800E003 */  jr         $31
    /* 165180 00265180 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_00265130
    /* 165184 00265184 00000000 */  nop
```
