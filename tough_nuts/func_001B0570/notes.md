
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_001B0570/0B0570.c`

Disassembly excerpt:

```
glabel func_001B0570
    /* B0570 001B0570 7000023C */  lui        $v0, %hi(D_00706110)
    /* B0574 001B0574 1D000424 */  addiu      $a0, $zero, 0x1D
    /* B0578 001B0578 10614324 */  addiu      $v1, $v0, %lo(D_00706110)
    /* B057C 001B057C 00000000 */  nop
.align 2
  .L001B0580:
    /* B0580 001B0580 0000628C */  lw         $v0, 0x0($v1)
    /* B0584 001B0584 04004010 */  beqz       $v0, .L001B0598
    /* B0588 001B0588 FFFF8424 */   addiu     $a0, $a0, -0x1
    /* B058C 001B058C 0C00628C */  lw         $v0, 0xC($v1)
    /* B0590 001B0590 01004234 */  ori        $v0, $v0, 0x1
    /* B0594 001B0594 0C0062AC */  sw         $v0, 0xC($v1)
.align 2
  .L001B0598:
    /* B0598 001B0598 F9FF8104 */  bgez       $a0, .L001B0580
    /* B059C 001B059C 20006324 */   addiu     $v1, $v1, 0x20
    /* B05A0 001B05A0 0800E003 */  jr         $ra
    /* B05A4 001B05A4 00000000 */   nop
endlabel func_001B0570
```
