# func_0014AF70 — parked

VRAM: 0x0014AF70 (file_off 0x04AF70)
Asm source: asm/nonmatchings/src/act-parallel-control/func_0014AF70.s

## Attempt at 2026-05-20

**Reason parked:** search loop w/ early-return; built emits different control flow shape (single-test prologue vs duplicated tests in original)

**TU:** `src/act-parallel-control.c`

**Seed:** `tough_nuts/func_0014AF70/func_0014AF70.c`

Disassembly:

```
.align 3
nonmatching func_0014AF70, 0x48

glabel func_0014AF70
    /* 4AF70 0014AF70 6B00023C */  lui        $2, %hi(D_006AA4B0)
    /* 4AF74 0014AF74 B0A44224 */  addiu      $2, $2, %lo(D_006AA4B0)
    /* 4AF78 0014AF78 B004438C */  lw         $3, 0x4B0($2)
    /* 4AF7C 0014AF7C 0C006018 */  blez       $3, .L0014AFB0
    /* 4AF80 0014AF80 2D200000 */   daddu     $4, $0, $0
    /* 4AF84 0014AF84 2D306000 */  daddu      $6, $3, $0
    /* 4AF88 0014AF88 2D184000 */  daddu      $3, $2, $0
    /* 4AF8C 0014AF8C 00000000 */  nop
.align 2
  .L0014AF90:
    /* 4AF90 0014AF90 0000628C */  lw         $2, 0x0($3)
    /* 4AF94 0014AF94 03004514 */  bne        $2, $5, .L0014AFA4
    /* 4AF98 0014AF98 01008424 */   addiu     $4, $4, 0x1
    /* 4AF9C 0014AF9C 0800E003 */  jr         $31
    /* 4AFA0 0014AFA0 90016290 */   lbu       $2, 0x190($3)
.align 2
  .L0014AFA4:
    /* 4AFA4 0014AFA4 2A108600 */  slt        $2, $4, $6
    /* 4AFA8 0014AFA8 F9FF4014 */  bnez       $2, .L0014AF90
    /* 4AFAC 0014AFAC 04006324 */   addiu     $3, $3, 0x4
.align 2
  .L0014AFB0:
    /* 4AFB0 0014AFB0 0800E003 */  jr         $31
    /* 4AFB4 0014AFB4 2D100000 */   daddu     $2, $0, $0
endlabel func_0014AF70
```
