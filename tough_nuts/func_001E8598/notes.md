# func_001E8598 — parked

VRAM: 0x001E8598 (file_off 0x0E8598)
Asm source: asm/nonmatchings/src/particleEffect/func_001E8598.s

## Attempt at 2026-05-20

**Reason parked:** 3-way bltz/null-check tail-call dispatch; trailing func_001E6D68 tail expects 3 args but caller sets only $4 — args carry-over issue

**TU:** `src/particleEffect.c`

**Seed:** `tough_nuts/func_001E8598/func_001E8598.c`

Disassembly:

```
.align 3
nonmatching func_001E8598, 0x40

glabel func_001E8598
    /* E8598 001E8598 0D008004 */  bltz       $4, .L001E85D0
    /* E859C 001E859C 18000224 */   addiu     $2, $0, 0x18
    /* E85A0 001E85A0 7100033C */  lui        $3, %hi(D_007097F0)
    /* E85A4 001E85A4 18208200 */  mult       $4, $4, $2
    /* E85A8 001E85A8 F0976724 */  addiu      $7, $3, %lo(D_007097F0)
    /* E85AC 001E85AC 21108700 */  addu       $2, $4, $7
    /* E85B0 001E85B0 0000438C */  lw         $3, 0x0($2)
    /* E85B4 001E85B4 04006014 */  bnez       $3, .L001E85C8
    /* E85B8 001E85B8 2110E400 */   addu      $2, $7, $4
    /* E85BC 001E85BC 6200043C */  lui        $4, %hi(D_00619E40)
    /* E85C0 001E85C0 8A9B0608 */  j          func_001A6E28
    /* E85C4 001E85C4 409E8424 */   addiu     $4, $4, %lo(D_00619E40)
.align 2
  .L001E85C8:
    /* E85C8 001E85C8 5A9B0708 */  j          func_001E6D68
    /* E85CC 001E85CC 1400448C */   lw        $4, 0x14($2)
.align 2
  .L001E85D0:
    /* E85D0 001E85D0 0800E003 */  jr         $31
    /* E85D4 001E85D4 00000000 */   nop
endlabel func_001E8598
```
