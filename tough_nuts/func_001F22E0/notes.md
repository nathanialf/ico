# func_001F22E0 — parked

VRAM: 0x001F22E0 (file_off 0x0F22E0)
Asm source: asm/matchings/cod/0F22E0/func_001F22E0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE,REG)

**TU:** `src/torch.c`

**Seed:** `tough_nuts/func_001F22E0/func_001F22E0.c`

Disassembly:

```
.align 3
nonmatching func_001F22E0, 0x3C

glabel func_001F22E0
    /* F22E0 001F22E0 E0FFBD27 */  addiu      $29, $29, -0x20
    /* F22E4 001F22E4 15000524 */  addiu      $5, $0, 0x15
    /* F22E8 001F22E8 0000B0FF */  sd         $16, 0x0($29)
    /* F22EC 001F22EC 2D808000 */  daddu      $16, $4, $0
    /* F22F0 001F22F0 1000BFFF */  sd         $31, 0x10($29)
    /* F22F4 001F22F4 1F00043C */  lui        $4, %hi(func_001F2320)
    /* F22F8 001F22F8 D00E080C */  jal        func_00203B40
    /* F22FC 001F22FC 20238424 */   addiu     $4, $4, %lo(func_001F2320)
    /* F2300 001F2300 2D184000 */  daddu      $3, $2, $0
    /* F2304 001F2304 000000AE */  sw         $0, 0x0($16)
    /* F2308 001F2308 200070AC */  sw         $16, 0x20($3)
    /* F230C 001F230C 1000BFDF */  ld         $31, 0x10($29)
    /* F2310 001F2310 0000B0DF */  ld         $16, 0x0($29)
    /* F2314 001F2314 0800E003 */  jr         $31
    /* F2318 001F2318 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001F22E0
```
