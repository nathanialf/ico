# func_001F6E00 — parked

VRAM: 0x001F6E00 (file_off 0x0F6E00)
Asm source: asm/matchings/Basic/func_001F6E00.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO,LA_SPLIT)

**TU:** `src/Basic.c`

**Seed:** `tough_nuts/func_001F6E00/func_001F6E00.c`

Disassembly:

```
.align 3
nonmatching func_001F6E00, 0x24

glabel func_001F6E00
    /* F6E00 001F6E00 F0FFBD27 */  addiu      $29, $29, -0x10
    /* F6E04 001F6E04 6200063C */  lui        $6, %hi(D_0061A8A8)
    /* F6E08 001F6E08 0000BFFF */  sd         $31, 0x0($29)
    /* F6E0C 001F6E0C A8A8C624 */  addiu      $6, $6, %lo(D_0061A8A8)
    /* F6E10 001F6E10 5EE7040C */  jal        func_00139D78
    /* F6E14 001F6E14 A8010724 */   addiu     $7, $0, 0x1A8
    /* F6E18 001F6E18 0000BFDF */  ld         $31, 0x0($29)
    /* F6E1C 001F6E1C 0800E003 */  jr         $31
    /* F6E20 001F6E20 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_001F6E00
    /* F6E24 001F6E24 00000000 */  nop
```
