# func_001F0878 — parked

VRAM: 0x001F0878 (file_off 0x0F0878)
Asm source: asm/nonmatchings/cod/0F0878/func_001F0878.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/stormTest.c`

**Seed:** `tough_nuts/func_001F0878/func_001F0878.c`

Disassembly:

```
.align 3
nonmatching func_001F0878, 0x5C

glabel func_001F0878
    /* F0878 001F0878 C0FFBD27 */  addiu      $29, $29, -0x40
    /* F087C 001F087C FFFF0324 */  addiu      $3, $0, -0x1
    /* F0880 001F0880 2000B1FF */  sd         $17, 0x20($29)
    /* F0884 001F0884 2700053C */  lui        $5, %hi(D_00275850)
    /* F0888 001F0888 1000B0FF */  sd         $16, 0x10($29)
    /* F088C 001F088C 01001124 */  addiu      $17, $0, 0x1
    /* F0890 001F0890 3000BFFF */  sd         $31, 0x30($29)
    /* F0894 001F0894 2D808000 */  daddu      $16, $4, $0
    /* F0898 001F0898 5058A524 */  addiu      $5, $5, %lo(D_00275850)
    /* F089C 001F089C 5C01028E */  lw         $2, 0x15C($16)
    /* F08A0 001F08A0 700443AC */  sw         $3, 0x470($2)
    /* F08A4 001F08A4 5C01028E */  lw         $2, 0x15C($16)
    /* F08A8 001F08A8 600651AC */  sw         $17, 0x660($2)
    /* F08AC 001F08AC 5C01048E */  lw         $4, 0x15C($16)
    /* F08B0 001F08B0 C017040C */  jal        func_00105F00
    /* F08B4 001F08B4 70068424 */   addiu     $4, $4, 0x670
    /* F08B8 001F08B8 5C01028E */  lw         $2, 0x15C($16)
    /* F08BC 001F08BC 3000BFDF */  ld         $31, 0x30($29)
    /* F08C0 001F08C0 500551AC */  sw         $17, 0x550($2)
    /* F08C4 001F08C4 2000B1DF */  ld         $17, 0x20($29)
    /* F08C8 001F08C8 1000B0DF */  ld         $16, 0x10($29)
    /* F08CC 001F08CC 0800E003 */  jr         $31
    /* F08D0 001F08D0 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001F0878
```
