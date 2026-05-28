# func_001FB7F8 — parked

VRAM: 0x001FB7F8 (file_off 0x0FB7F8)
Asm source: asm/nonmatchings/src/DisplayList/func_001FB7F8.s

## Attempt at 2026-05-28

**Reason parked:** best real_count=5; FUNCTION BODY IS BYTE-EXACT. Sole residual: gp-load of D_00633810 into a0 after prologue vs original v0 BEFORE prologue + bgtz-delay-fill 'daddu a0,v0' copy. Tool-confirmed 30-stall (31 distinct hyps): reg-pin sweep ($2..$8 all worse), membar/anchor/volatile, both -fno-schedule-insns[2], far-global alias, dual-alias (breaks s0-cache), goto/ternary/-- forms, store reorders. Pure sched2-hoist/coalescing -> permuter. Seed has D_00633818 incomplete-array alias (fixes the %hi/%lo, 8->5).

**TU:** `src/DisplayList.c`

**Seed:** `tough_nuts/func_001FB7F8/func_001FB7F8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633810, 1
.extern D_00633F70, 1

nonmatching func_001FB7F8, 0x88

glabel func_001FB7F8
    /* FB7F8 001FB7F8 20AF828F */  lw         $2, (D_00633810) /* gp_rel: (D_00633810) */
    /* FB7FC 001FB7FC E0FFBD27 */  addiu      $29, $29, -0x20
    /* FB800 001FB800 1000BFFF */  sd         $31, 0x10($29)
    /* FB804 001FB804 0000B0FF */  sd         $16, 0x0($29)
    /* FB808 001FB808 1100401C */  bgtz       $2, .L001FB850
    /* FB80C 001FB80C 2D204000 */   daddu     $4, $2, $0
    /* FB810 001FB810 6200043C */  lui        $4, %hi(D_0061ABC8)
    /* FB814 001FB814 8A9B060C */  jal        func_001A6E28
    /* FB818 001FB818 C8AB8424 */   addiu     $4, $4, %lo(D_0061ABC8)
    /* FB81C 001FB81C 6200103C */  lui        $16, %hi(D_0061AB88)
    /* FB820 001FB820 20020524 */  addiu      $5, $0, 0x220
    /* FB824 001FB824 88AB1026 */  addiu      $16, $16, %lo(D_0061AB88)
    /* FB828 001FB828 DAB5060C */  jal        func_001AD768
    /* FB82C 001FB82C 2D200002 */   daddu     $4, $16, $0
    /* FB830 001FB830 2D200002 */  daddu      $4, $16, $0
    /* FB834 001FB834 6300063C */  lui        $6, %hi(D_00633818)
    /* FB838 001FB838 1000BFDF */  ld         $31, 0x10($29)
    /* FB83C 001FB83C 1838C624 */  addiu      $6, $6, %lo(D_00633818)
    /* FB840 001FB840 0000B0DF */  ld         $16, 0x0($29)
    /* FB844 001FB844 20020524 */  addiu      $5, $0, 0x220
    /* FB848 001FB848 FC8F0908 */  j          func_00263FF0
    /* FB84C 001FB84C 2000BD27 */   addiu     $29, $29, 0x20
.align 2
  .L001FB850:
    /* FB850 001FB850 FFFF8424 */  addiu      $4, $4, -0x1
    /* FB854 001FB854 7100023C */  lui        $2, %hi(D_00710F80)
    /* FB858 001FB858 800F4224 */  addiu      $2, $2, %lo(D_00710F80)
    /* FB85C 001FB85C 80180400 */  sll        $3, $4, 2
    /* FB860 001FB860 21186200 */  addu       $3, $3, $2
    /* FB864 001FB864 1000BFDF */  ld         $31, 0x10($29)
    /* FB868 001FB868 0000628C */  lw         $2, 0x0($3)
    /* FB86C 001FB86C 0000B0DF */  ld         $16, 0x0($29)
    /* FB870 001FB870 20AF84AF */  sw         $4, (D_00633810) /* gp_rel: (D_00633810) */
    /* FB874 001FB874 80B682AF */  sw         $2, (D_00633F70) /* gp_rel: (D_00633F70) */
    /* FB878 001FB878 0800E003 */  jr         $31
    /* FB87C 001FB87C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001FB7F8
```
