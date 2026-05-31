# func_001E6C30 — parked

VRAM: 0x001E6C30 (file_off 0x0E6C30)
Asm source: asm/nonmatchings/src/multiBgaManager/func_001E6C30.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/multiBgaManager.c`

**Seed:** `tough_nuts/func_001E6C30/func_001E6C30.c`

Disassembly:

```
.align 3
nonmatching func_001E6C30, 0x6C

glabel func_001E6C30
    /* E6C30 001E6C30 50000224 */  addiu      $2, $0, 0x50
    /* E6C34 001E6C34 D0FFBD27 */  addiu      $29, $29, -0x30
    /* E6C38 001E6C38 1838A200 */  mult       $7, $5, $2
    /* E6C3C 001E6C3C 1000B1FF */  sd         $17, 0x10($29)
    /* E6C40 001E6C40 0000B0FF */  sd         $16, 0x0($29)
    /* E6C44 001E6C44 FFFF0324 */  addiu      $3, $0, -0x1
    /* E6C48 001E6C48 2000BFFF */  sd         $31, 0x20($29)
    /* E6C4C 001E6C4C 2700113C */  lui        $17, %hi(D_00276140)
    /* E6C50 001E6C50 40613126 */  addiu      $17, $17, %lo(D_00276140)
    /* E6C54 001E6C54 2D28C000 */  daddu      $5, $6, $0
    /* E6C58 001E6C58 2180E400 */  addu       $16, $7, $4
    /* E6C5C 001E6C5C 400003AE */  sw         $3, 0x40($16)
    /* E6C60 001E6C60 C017040C */  jal        func_00105F00
    /* E6C64 001E6C64 10000426 */   addiu     $4, $16, 0x10
    /* E6C68 001E6C68 2700053C */  lui        $5, %hi(D_00275850)
    /* E6C6C 001E6C6C 20000426 */  addiu      $4, $16, 0x20
    /* E6C70 001E6C70 C017040C */  jal        func_00105F00
    /* E6C74 001E6C74 5058A524 */   addiu     $5, $5, %lo(D_00275850)
    /* E6C78 001E6C78 2D282002 */  daddu      $5, $17, $0
    /* E6C7C 001E6C7C 0C36040C */  jal        func_0010D830
    /* E6C80 001E6C80 30000426 */   addiu     $4, $16, 0x30
    /* E6C84 001E6C84 000000AE */  sw         $0, 0x0($16)
    /* E6C88 001E6C88 2000BFDF */  ld         $31, 0x20($29)
    /* E6C8C 001E6C8C 1000B1DF */  ld         $17, 0x10($29)
    /* E6C90 001E6C90 0000B0DF */  ld         $16, 0x0($29)
    /* E6C94 001E6C94 0800E003 */  jr         $31
    /* E6C98 001E6C98 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001E6C30
    /* E6C9C 001E6C9C 00000000 */  nop
```
