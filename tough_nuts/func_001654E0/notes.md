# func_001654E0 — parked

VRAM: 0x001654E0 (file_off 0x0654E0)
Asm source: asm/nonmatchings/src/enemy_act/func_001654E0.s

## Attempt at 2026-05-31

**Reason parked:** rc12 far-global-array predicate near-miss. Guard if(self->0x164->0x670->0x1DC==0)return 0; then bit18/bit21 test on D_002A4C48[self->0x8] (stride 0x4C, field 0x48), return 1. The BODY matches standalone as sibling func_001652F8 (goto-CFG goto zero/one). Adding the guard breaks it: (1) stride const (addiu 76) hoists into the guard branch delay instead of the idx=self->0x8 load (SAME wall as parked func_0014A6B8); (2) guard emits beq not bnel (branch-likely heuristic, see [[branch_likely_emission]]); (3) the body's bit18 branch inverts bne->beq due to guard block-layout. 3 forms (goto-CFG/nested-if/explicit-idx) all rc12. Same class as func_0014A6B8. Needs a sched/branch-likely lever or permuter. NOT a floor, stall 2.

**TU:** `src/enemy_act.c`

**Seed:** `tough_nuts/func_001654E0/func_001654E0.c`

Disassembly:

```
.align 3
nonmatching func_001654E0, 0x60

glabel func_001654E0
    /* 654E0 001654E0 2D288000 */  daddu      $5, $4, $0
    /* 654E4 001654E4 6401A28C */  lw         $2, 0x164($5)
    /* 654E8 001654E8 7006438C */  lw         $3, 0x670($2)
    /* 654EC 001654EC DC01648C */  lw         $4, 0x1DC($3)
    /* 654F0 001654F0 03008054 */  bnel       $4, $0, .L00165500
    /* 654F4 001654F4 0800A38C */   lw        $3, 0x8($5)
.align 2
  .L001654F8:
    /* 654F8 001654F8 0800E003 */  jr         $31
    /* 654FC 001654FC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L00165500:
    /* 65500 00165500 4C000424 */  addiu      $4, $0, 0x4C
    /* 65504 00165504 2A00023C */  lui        $2, %hi(D_002A4C48)
    /* 65508 00165508 18186400 */  mult       $3, $3, $4
    /* 6550C 0016550C 484C4224 */  addiu      $2, $2, %lo(D_002A4C48)
    /* 65510 00165510 21186200 */  addu       $3, $3, $2
    /* 65514 00165514 4800648C */  lw         $4, 0x48($3)
    /* 65518 00165518 82140400 */  srl        $2, $4, 18
    /* 6551C 0016551C 01004230 */  andi       $2, $2, 0x1
    /* 65520 00165520 F5FF4014 */  bnez       $2, .L001654F8
    /* 65524 00165524 42150400 */   srl       $2, $4, 21
    /* 65528 00165528 01004230 */  andi       $2, $2, 0x1
    /* 6552C 0016552C 01004238 */  xori       $2, $2, 0x1
    /* 65530 00165530 F1FF4014 */  bnez       $2, .L001654F8
    /* 65534 00165534 01000224 */   addiu     $2, $0, 0x1
    /* 65538 00165538 0800E003 */  jr         $31
    /* 6553C 0016553C 00000000 */   nop
endlabel func_001654E0
```
