# func_001E6D68 — parked

VRAM: 0x001E6D68 (file_off 0x0E6D68)
Asm source: asm/matchings/particleEffect/func_001E6D68.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (ADDU_RS)

**TU:** `src/particleEffect.c`

**Seed:** `tough_nuts/func_001E6D68/func_001E6D68.c`

Disassembly:

```
.align 3
nonmatching func_001E6D68, 0x38

glabel func_001E6D68
    /* E6D68 001E6D68 D0FFBD27 */  addiu      $29, $29, -0x30
    /* E6D6C 001E6D6C 0000B0FF */  sd         $16, 0x0($29)
    /* E6D70 001E6D70 2D808000 */  daddu      $16, $4, $0
    /* E6D74 001E6D74 1000B1FF */  sd         $17, 0x10($29)
    /* E6D78 001E6D78 2000BFFF */  sd         $31, 0x20($29)
    /* E6D7C 001E6D7C C017040C */  jal        func_00105F00
    /* E6D80 001E6D80 2D88C000 */   daddu     $17, $6, $0
    /* E6D84 001E6D84 10000426 */  addiu      $4, $16, 0x10
    /* E6D88 001E6D88 2D282002 */  daddu      $5, $17, $0
    /* E6D8C 001E6D8C 2000BFDF */  ld         $31, 0x20($29)
    /* E6D90 001E6D90 1000B1DF */  ld         $17, 0x10($29)
    /* E6D94 001E6D94 0000B0DF */  ld         $16, 0x0($29)
    /* E6D98 001E6D98 0C360408 */  j          func_0010D830
    /* E6D9C 001E6D9C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001E6D68
```
