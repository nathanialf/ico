# func_00176198 — parked

VRAM: 0x00176198 (file_off 0x076198)
Asm source: asm/nonmatchings/src/girl_act/func_00176198.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO,NOP)

**TU:** `src/girl_act.c`

**Seed:** `tough_nuts/func_00176198/func_00176198.c`

Disassembly:

```
.align 3
nonmatching func_00176198, 0x20

glabel func_00176198
    /* 76198 00176198 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 7619C 0017619C 1000BFFF */  sd         $31, 0x10($29)
    /* 761A0 001761A0 0000A4AF */  sw         $4, 0x0($29)
    /* 761A4 001761A4 EA28050C */  jal        func_0014A3A8
    /* 761A8 001761A8 00000000 */   nop
    /* 761AC 001761AC 1000BFDF */  ld         $31, 0x10($29)
    /* 761B0 001761B0 0800E003 */  jr         $31
    /* 761B4 001761B4 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00176198
```
