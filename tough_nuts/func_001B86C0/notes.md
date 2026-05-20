# func_001B86C0 — parked

VRAM: 0x001B86C0 (file_off 0x0B86C0)
Asm source: asm/nonmatchings/src/staffroll/func_001B86C0.s

## Attempt at 2026-05-20

**Reason parked:** div-pair scheduling: expected interleaves D_00633EE8=1 sw between operations; built reg alloc uses v0/v1 not a0/a1

**TU:** `src/staffroll.c`

**Seed:** `tough_nuts/func_001B86C0/func_001B86C0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633EE0, 1
.extern D_00633EE4, 1
.extern D_00633EE8, 1
.extern D_006331B4, 1
.extern D_00633EDC, 1

.align 3
nonmatching func_001B86C0, 0x60

glabel func_001B86C0
    /* B86C0 001B86C0 4C00053C */  lui        $5, %hi(D_004BD980)
    /* B86C4 001B86C4 1E000424 */  addiu      $4, $0, 0x1E
    /* B86C8 001B86C8 80D9A38C */  lw         $3, %lo(D_004BD980)($5)
    /* B86CC 001B86CC 01000224 */  addiu      $2, $0, 0x1
    /* B86D0 001B86D0 F8B582AF */  sw         $2, (D_00633EE8) /* gp_rel: (D_00633EE8) */
    /* B86D4 001B86D4 1E000524 */  addiu      $5, $0, 0x1E
    /* B86D8 001B86D8 00146324 */  addiu      $3, $3, 0x1400
    /* B86DC 001B86DC 01008050 */  beql       $4, $0, .L001B86E4
    /* B86E0 001B86E0 CD010000 */   break     0, 7
.align 2
  .L001B86E4:
    /* B86E4 001B86E4 1A006400 */  div        $0, $3, $4
    /* B86E8 001B86E8 ECB5828F */  lw         $2, (D_00633EDC) /* gp_rel: (D_00633EDC) */
    /* B86EC 001B86EC FF000624 */  addiu      $6, $0, 0xFF
    /* B86F0 001B86F0 80FD4224 */  addiu      $2, $2, -0x280
    /* B86F4 001B86F4 12180000 */  mflo       $3
    /* B86F8 001B86F8 1A004400 */  div        $0, $2, $4
    /* B86FC 001B86FC 00008344 */  mtc1       $3, $f0
    /* B8700 001B8700 20008046 */  cvt.s.w    $f0, $f0
    /* B8704 001B8704 F0B580E7 */  swc1       $f0, (D_00633EE0) /* gp_rel: (D_00633EE0) */
    /* B8708 001B8708 C4A886AF */  sw         $6, (D_006331B4) /* gp_rel: (D_006331B4) */
    /* B870C 001B870C 12100000 */  mflo       $2
    /* B8710 001B8710 00088244 */  mtc1       $2, $f1
    /* B8714 001B8714 60088046 */  cvt.s.w    $f1, $f1
    /* B8718 001B8718 0800E003 */  jr         $31
    /* B871C 001B871C F4B581E7 */   swc1      $f1, (D_00633EE4) /* gp_rel: (D_00633EE4) */
endlabel func_001B86C0
```
