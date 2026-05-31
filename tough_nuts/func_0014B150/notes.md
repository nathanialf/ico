# func_0014B150 — parked

VRAM: 0x0014B150 (file_off 0x04B150)
Asm source: asm/matchings/cod/04B150/func_0014B150.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE_MEM)

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014B150/func_0014B150.c`

Disassembly:

```
.align 3
nonmatching func_0014B150, 0x14

glabel func_0014B150
    /* 4B150 0014B150 6401828C */  lw         $2, 0x164($4)
    /* 4B154 0014B154 9C0040AC */  sw         $0, 0x9C($2)
    /* 4B158 0014B158 980040AC */  sw         $0, 0x98($2)
    /* 4B15C 0014B15C 0800E003 */  jr         $31
    /* 4B160 0014B160 A00040AC */   sw        $0, 0xA0($2)
endlabel func_0014B150
```
