
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_001FBC18/0FBC18.c`

Disassembly excerpt:

```
glabel func_001FBC18
    /* FBC18 001FBC18 4C00033C */  lui        $v1, %hi(D_004C7710)
    /* FBC1C 001FBC1C F8FF053C */  lui        $a1, (0xFFF80000 >> 16)
    /* FBC20 001FBC20 1077628C */  lw         $v0, %lo(D_004C7710)($v1)
    /* FBC24 001FBC24 10776324 */  addiu      $v1, $v1, %lo(D_004C7710)
    /* FBC28 001FBC28 1000648C */  lw         $a0, 0x10($v1)
    /* FBC2C 001FBC2C 80100200 */  sll        $v0, $v0, 2
    /* FBC30 001FBC30 21186200 */  addu       $v1, $v1, $v0
    /* FBC34 001FBC34 0400628C */  lw         $v0, 0x4($v1)
    /* FBC38 001FBC38 21208500 */  addu       $a0, $a0, $a1
    /* FBC3C 001FBC3C 23104400 */  subu       $v0, $v0, $a0
    /* FBC40 001FBC40 0800E003 */  jr         $ra
    /* FBC44 001FBC44 03110200 */   sra       $v0, $v0, 4
endlabel func_001FBC18
```
