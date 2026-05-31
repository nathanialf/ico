# func_0011E708 — parked

VRAM: 0x0011E708 (file_off 0x01E708)
Asm source: asm/matchings/cod/01E708/func_0011E708.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (DEFEAT_TCO)

**TU:** `src/RegistPacket.c`

**Seed:** `tough_nuts/func_0011E708/func_0011E708.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632028, 1

.align 3
nonmatching func_0011E708, 0x20

glabel func_0011E708
    /* 1E708 0011E708 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 1E70C 0011E70C 3897888F */  lw         $8, %gp_rel(D_00632028)($gp) /* gp_rel: (D_00632028) */
    /* 1E710 0011E710 0000BFFF */  sd         $31, 0x0($29)
    /* 1E714 0011E714 6876040C */  jal        func_0011D9A0
    /* 1E718 0011E718 00000000 */   nop
    /* 1E71C 0011E71C 0000BFDF */  ld         $31, 0x0($29)
    /* 1E720 0011E720 0800E003 */  jr         $31
    /* 1E724 0011E724 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0011E708
```
