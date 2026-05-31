# func_00175C18 — parked

VRAM: 0x00175C18 (file_off 0x075C18)
Asm source: asm/matchings/src/commonact/func_00175C18.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/commonact.c`

**Seed:** `tough_nuts/func_00175C18/func_00175C18.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE8, 1

.align 3
nonmatching func_00175C18, 0x54

glabel func_00175C18
    /* 75C18 00175C18 F891838F */  lw         $3, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* 75C1C 00175C1C 6401638C */  lw         $3, 0x164($3)
    /* 75C20 00175C20 180062DC */  ld         $2, 0x18($3)
    /* 75C24 00175C24 3E110200 */  dsrl32     $2, $2, 4
    /* 75C28 00175C28 01004230 */  andi       $2, $2, 0x1
    /* 75C2C 00175C2C 03004054 */  bnel       $2, $0, .L00175C3C
    /* 75C30 00175C30 3000648C */   lw        $4, 0x30($3)
    /* 75C34 00175C34 0800E003 */  jr         $31
    /* 75C38 00175C38 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L00175C3C:
    /* 75C3C 00175C3C 45000324 */  addiu      $3, $0, 0x45
    /* 75C40 00175C40 08008314 */  bne        $4, $3, .L00175C64
    /* 75C44 00175C44 2D100000 */   daddu     $2, $0, $0
    /* 75C48 00175C48 2900033C */  lui        $3, %hi(D_002883D0)
    /* 75C4C 00175C4C D0836324 */  addiu      $3, $3, %lo(D_002883D0)
    /* 75C50 00175C50 5D006490 */  lbu        $4, 0x5D($3)
    /* 75C54 00175C54 03008010 */  beqz       $4, .L00175C64
    /* 75C58 00175C58 00000000 */   nop
    /* 75C5C 00175C5C 58006290 */  lbu        $2, 0x58($3)
    /* 75C60 00175C60 0100422C */  sltiu      $2, $2, 0x1
.align 2
  .L00175C64:
    /* 75C64 00175C64 0800E003 */  jr         $31
    /* 75C68 00175C68 00000000 */   nop
endlabel func_00175C18
    /* 75C6C 00175C6C 00000000 */  nop
```
