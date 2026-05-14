
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_00257850/157850.c`

Disassembly excerpt:

```
glabel func_00257850
    /* 157850 00257850 5500023C */  lui        $v0, %hi(D_005524A4)
    /* 157854 00257854 02000524 */  addiu      $a1, $zero, 0x2
    /* 157858 00257858 A424438C */  lw         $v1, %lo(D_005524A4)($v0)
    /* 15785C 0025785C 4000648C */  lw         $a0, 0x40($v1)
    /* 157860 00257860 0800828C */  lw         $v0, 0x8($a0)
    /* 157864 00257864 04004510 */  beq        $v0, $a1, .L00257878
    /* 157868 00257868 5500023C */   lui       $v0, %hi(D_005525C4)
    /* 15786C 0025786C C425438C */  lw         $v1, %lo(D_005525C4)($v0)
    /* 157870 00257870 080085AC */  sw         $a1, 0x8($a0)
    /* 157874 00257874 AC0083AC */  sw         $v1, 0xAC($a0)
.align 2
  .L00257878:
    /* 157878 00257878 5500033C */  lui        $v1, %hi(D_00552D40)
    /* 15787C 0025787C 01000224 */  addiu      $v0, $zero, 0x1
    /* 157880 00257880 0800E003 */  jr         $ra
    /* 157884 00257884 402D62AC */   sw        $v0, %lo(D_00552D40)($v1)
endlabel func_00257850
```
