# func_002480F0 — parked

VRAM: 0x002480F0 (file_off 0x1480F0)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_002480F0.s

## Attempt at 2026-06-04

**Reason parked:** rc4 far-global ternary near-miss: base=(a0<0)?D_00710DE4:D_00710DEC; *(base+a0*8)=0. Incomplete-array decl gives %hi/%lo (fixed gp_rel). Residual: base loads into v0(=%hi reg) not a0 (the freed arg reg the ROM reuses) — addu dest/operand cascade. 6 forms (base+off/off+base/compound/inline/reassign-a0). Permuter target.

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_002480F0/func_002480F0.c`

Disassembly:

```
.align 3
nonmatching func_002480F0, 0x28

glabel func_002480F0
    /* 1480F0 002480F0 04008104 */  bgez       $4, .L00248104
    /* 1480F4 002480F4 C0180400 */   sll       $3, $4, 3
    /* 1480F8 002480F8 7100023C */  lui        $2, %hi(D_00710DE4)
    /* 1480FC 002480FC 03000010 */  b          .L0024810C
    /* 148100 00248100 E40D448C */   lw        $4, %lo(D_00710DE4)($2)
.align 2
  .L00248104:
    /* 148104 00248104 7100023C */  lui        $2, %hi(D_00710DEC)
    /* 148108 00248108 EC0D448C */  lw         $4, %lo(D_00710DEC)($2)
.align 2
  .L0024810C:
    /* 14810C 0024810C 21186400 */  addu       $3, $3, $4
    /* 148110 00248110 0800E003 */  jr         $31
    /* 148114 00248114 000060AC */   sw        $0, 0x0($3)
endlabel func_002480F0
```
