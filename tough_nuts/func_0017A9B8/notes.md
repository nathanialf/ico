# func_0017A9B8 — parked

VRAM: 0x0017A9B8 (file_off 0x07A9B8)
Asm source: asm/matchings/cod/07A9B8/func_0017A9B8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO)

**TU:** `src/way_util.c`

**Seed:** `tough_nuts/func_0017A9B8/func_0017A9B8.c`

Disassembly:

```
.align 3
nonmatching func_0017A9B8, 0x1C

glabel func_0017A9B8
    /* 7A9B8 0017A9B8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 7A9BC 0017A9BC 0000BFFF */  sd         $31, 0x0($29)
    /* 7A9C0 0017A9C0 64E2050C */  jal        func_00178990
    /* 7A9C4 0017A9C4 FFFF0524 */   addiu     $5, $0, -0x1
    /* 7A9C8 0017A9C8 0000BFDF */  ld         $31, 0x0($29)
    /* 7A9CC 0017A9CC 0800E003 */  jr         $31
    /* 7A9D0 0017A9D0 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0017A9B8
```
