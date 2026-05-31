# func_0013A200 — parked

VRAM: 0x0013A200 (file_off 0x03A200)
Asm source: asm/matchings/ios/memory/func_0013A200.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (DEFEAT_TCO)

**TU:** `ios/memory.c`

**Seed:** `tough_nuts/func_0013A200/func_0013A200.c`

Disassembly:

```
.align 3
nonmatching func_0013A200, 0x1C

glabel func_0013A200
    /* 3A200 0013A200 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 3A204 0013A204 0000BFFF */  sd         $31, 0x0($29)
    /* 3A208 0013A208 8CE3040C */  jal        func_00138E30
    /* 3A20C 0013A20C 00000000 */   nop
    /* 3A210 0013A210 0000BFDF */  ld         $31, 0x0($29)
    /* 3A214 0013A214 0800E003 */  jr         $31
    /* 3A218 0013A218 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0013A200
```
