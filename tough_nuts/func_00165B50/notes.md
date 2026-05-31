# func_00165B50 — parked

VRAM: 0x00165B50 (file_off 0x065B50)
Asm source: asm/matchings/cod/065B50/func_00165B50.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/enemy_act.c`

**Seed:** `tough_nuts/func_00165B50/func_00165B50.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632390, 1

.align 3
nonmatching func_00165B50, 0x30

glabel func_00165B50
    /* 65B50 00165B50 6401828C */  lw         $2, 0x164($4)
    /* 65B54 00165B54 7006438C */  lw         $3, 0x670($2)
    /* 65B58 00165B58 0400C010 */  beqz       $6, .L00165B6C
    /* 65B5C 00165B5C 000265AC */   sw        $5, 0x200($3)
    /* 65B60 00165B60 6401828C */  lw         $2, 0x164($4)
    /* 65B64 00165B64 03000010 */  b          .L00165B74
    /* 65B68 00165B68 0000C48C */   lw        $4, 0x0($6)
.align 2
  .L00165B6C:
    /* 65B6C 00165B6C 6401828C */  lw         $2, 0x164($4)
    /* 65B70 00165B70 A09A848F */  lw         $4, %gp_rel(D_00632390)($gp) /* gp_rel: (D_00632390) */
.align 2
  .L00165B74:
    /* 65B74 00165B74 7006438C */  lw         $3, 0x670($2)
    /* 65B78 00165B78 0800E003 */  jr         $31
    /* 65B7C 00165B7C 0C0264AC */   sw        $4, 0x20C($3)
endlabel func_00165B50
```
