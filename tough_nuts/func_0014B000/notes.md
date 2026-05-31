# func_0014B000 — parked

VRAM: 0x0014B000 (file_off 0x04B000)
Asm source: asm/matchings/cod/04B000/func_0014B000.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (MATERIALIZE)

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B000/func_0014B000.c`

Disassembly:

```
.align 3
nonmatching func_0014B000, 0x44

glabel func_0014B000
    /* 4B000 0014B000 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 4B004 0014B004 1000BFFF */  sd         $31, 0x10($29)
    /* 4B008 0014B008 09008010 */  beqz       $4, .L0014B030
    /* 4B00C 0014B00C 0000B0FF */   sd        $16, 0x0($29)
    /* 4B010 0014B010 6100103C */  lui        $16, %hi(D_006124F8)
    /* 4B014 0014B014 32D0070C */  jal        func_001F40C8
    /* 4B018 0014B018 F8241026 */   addiu     $16, $16, %lo(D_006124F8)
    /* 4B01C 0014B01C 24000324 */  addiu      $3, $0, 0x24
    /* 4B020 0014B020 18104300 */  mult       $2, $2, $3
    /* 4B024 0014B024 21800202 */  addu       $16, $16, $2
    /* 4B028 0014B028 02000010 */  b          .L0014B034
    /* 4B02C 0014B02C 1C00028E */   lw        $2, 0x1C($16)
.align 2
  .L0014B030:
    /* 4B030 0014B030 2D100000 */  daddu      $2, $0, $0
.align 2
  .L0014B034:
    /* 4B034 0014B034 1000BFDF */  ld         $31, 0x10($29)
    /* 4B038 0014B038 0000B0DF */  ld         $16, 0x0($29)
    /* 4B03C 0014B03C 0800E003 */  jr         $31
    /* 4B040 0014B040 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0014B000
```
