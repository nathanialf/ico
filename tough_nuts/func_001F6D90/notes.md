# func_001F6D90 — parked

VRAM: 0x001F6D90 (file_off 0x0F6D90)
Asm source: asm/matchings/Basic/func_001F6D90.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO)

**TU:** `src/Basic.c`

**Seed:** `tough_nuts/func_001F6D90/func_001F6D90.c`

Disassembly:

```
.align 3
nonmatching func_001F6D90, 0x20

glabel func_001F6D90
    /* F6D90 001F6D90 F0FFBD27 */  addiu      $29, $29, -0x10
    /* F6D94 001F6D94 03008010 */  beqz       $4, .L001F6DA4
    /* F6D98 001F6D98 0000BFFF */   sd        $31, 0x0($29)
    /* F6D9C 001F6D9C 66E5040C */  jal        func_00139598
    /* F6DA0 001F6DA0 00000000 */   nop
.align 2
  .L001F6DA4:
    /* F6DA4 001F6DA4 0000BFDF */  ld         $31, 0x0($29)
    /* F6DA8 001F6DA8 0800E003 */  jr         $31
    /* F6DAC 001F6DAC 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_001F6D90
```
