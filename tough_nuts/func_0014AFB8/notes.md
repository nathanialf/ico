
---

## Attempt at 2026-05-12

**Reason parked:** count loaded direct to a2 vs expected v1 intermediate; rest matches

Seed: `tough_nuts/func_0014AFB8/04AFB8.c`

Disassembly excerpt:

```
glabel func_0014AFB8
    /* 4AFB8 0014AFB8 6B00023C */  lui        $v0, %hi(D_006AA4B0)
    /* 4AFBC 0014AFBC B0A44224 */  addiu      $v0, $v0, %lo(D_006AA4B0)
    /* 4AFC0 0014AFC0 B004438C */  lw         $v1, 0x4B0($v0)
    /* 4AFC4 0014AFC4 0C006018 */  blez       $v1, .L0014AFF8
    /* 4AFC8 0014AFC8 2D200000 */   daddu     $a0, $zero, $zero
    /* 4AFCC 0014AFCC 2D306000 */  daddu      $a2, $v1, $zero
    /* 4AFD0 0014AFD0 2D184000 */  daddu      $v1, $v0, $zero
    /* 4AFD4 0014AFD4 00000000 */  nop
.align 2
  .L0014AFD8:
    /* 4AFD8 0014AFD8 0000628C */  lw         $v0, 0x0($v1)
    /* 4AFDC 0014AFDC 03004514 */  bne        $v0, $a1, .L0014AFEC
    /* 4AFE0 0014AFE0 01008424 */   addiu     $a0, $a0, 0x1
    /* 4AFE4 0014AFE4 0800E003 */  jr         $ra
    /* 4AFE8 0014AFE8 20036290 */   lbu       $v0, 0x320($v1)
.align 2
  .L0014AFEC:
    /* 4AFEC 0014AFEC 2A108600 */  slt        $v0, $a0, $a2
    /* 4AFF0 0014AFF0 F9FF4014 */  bnez       $v0, .L0014AFD8
    /* 4AFF4 0014AFF4 04006324 */   addiu     $v1, $v1, 0x4
.align 2
  .L0014AFF8:
    /* 4AFF8 0014AFF8 0800E003 */  jr         $ra
    /* 4AFFC 0014AFFC 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0014AFB8
```
