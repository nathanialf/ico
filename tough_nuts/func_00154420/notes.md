# func_00154420 — parked

VRAM: 0x00154420 (file_off 0x054420)
Asm source: asm/matchings/cod/054420/func_00154420.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/boyact.c`

**Seed:** `tough_nuts/func_00154420/func_00154420.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00631AE4, 1

.align 3
nonmatching func_00154420, 0x24

glabel func_00154420
    /* 54420 00154420 F491838F */  lw         $3, %gp_rel(D_00631AE4)($gp) /* gp_rel: (D_00631AE4) */
    /* 54424 00154424 6401648C */  lw         $4, 0x164($3)
    /* 54428 00154428 3000848C */  lw         $4, 0x30($4)
    /* 5442C 0015442C 5D00832C */  sltiu      $3, $4, 0x5D
    /* 54430 00154430 02006010 */  beqz       $3, .L0015443C
    /* 54434 00154434 01000224 */   addiu     $2, $0, 0x1
    /* 54438 00154438 5B00822C */  sltiu      $2, $4, 0x5B
.align 2
  .L0015443C:
    /* 5443C 0015443C 0800E003 */  jr         $31
    /* 54440 00154440 00000000 */   nop
endlabel func_00154420
```
