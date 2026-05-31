# func_00190298 — parked

VRAM: 0x00190298 (file_off 0x090298)
Asm source: asm/matchings/cod/090298/func_00190298.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (REG)

**TU:** `src/chain.c`

**Seed:** `tough_nuts/func_00190298/func_00190298.c`

Disassembly:

```
.align 3
nonmatching func_00190298, 0x30

glabel func_00190298
    /* 90298 00190298 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 9029C 0019029C 1000BFFF */  sd         $31, 0x10($29)
    /* 902A0 001902A0 0000B0FF */  sd         $16, 0x0($29)
    /* 902A4 001902A4 5C01828C */  lw         $2, 0x15C($4)
    /* 902A8 001902A8 4034060C */  jal        func_0018D100
    /* 902AC 001902AC 0008508C */   lw        $16, 0x800($2)
    /* 902B0 001902B0 01000224 */  addiu      $2, $0, 0x1
    /* 902B4 001902B4 1000BFDF */  ld         $31, 0x10($29)
    /* 902B8 001902B8 600002A2 */  sb         $2, 0x60($16)
    /* 902BC 001902BC 0000B0DF */  ld         $16, 0x0($29)
    /* 902C0 001902C0 0800E003 */  jr         $31
    /* 902C4 001902C4 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00190298
```
