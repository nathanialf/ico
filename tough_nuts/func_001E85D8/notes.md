# func_001E85D8 — parked

VRAM: 0x001E85D8 (file_off 0x0E85D8)
Asm source: asm/matchings/src/particleEffect/func_001E85D8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (ADDU_RS,KEEP_LIVE)

**TU:** `src/particleEffect.c`

**Seed:** `tough_nuts/func_001E85D8/func_001E85D8.c`

Disassembly:

```
.align 3
nonmatching func_001E85D8, 0x3C

glabel func_001E85D8
    /* E85D8 001E85D8 2D108000 */  daddu      $2, $4, $0
    /* E85DC 001E85DC 0B004004 */  bltz       $2, .L001E860C
    /* E85E0 001E85E0 18000424 */   addiu     $4, $0, 0x18
    /* E85E4 001E85E4 7100033C */  lui        $3, %hi(D_007097F0)
    /* E85E8 001E85E8 18204400 */  mult       $4, $2, $4
    /* E85EC 001E85EC F0976324 */  addiu      $3, $3, %lo(D_007097F0)
    /* E85F0 001E85F0 01000524 */  addiu      $5, $0, 0x1
    /* E85F4 001E85F4 21186400 */  addu       $3, $3, $4
    /* E85F8 001E85F8 1400628C */  lw         $2, 0x14($3)
    /* E85FC 001E85FC 380045AC */  sw         $5, 0x38($2)
    /* E8600 001E8600 2D204000 */  daddu      $4, $2, $0
    /* E8604 001E8604 EA9C0708 */  j          func_001E73A8
    /* E8608 001E8608 3C004CE4 */   swc1      $f12, 0x3C($2)
.align 2
  .L001E860C:
    /* E860C 001E860C 0800E003 */  jr         $31
    /* E8610 001E8610 00000000 */   nop
endlabel func_001E85D8
    /* E8614 001E8614 00000000 */  nop
```
