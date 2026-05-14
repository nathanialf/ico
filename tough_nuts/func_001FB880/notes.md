
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_001FB880/0FB880.c`

Disassembly excerpt:

```
glabel func_001FB880
    /* FB880 001FB880 80B6838F */  lw         $v1, %gp_rel(D_00633F70)($gp)
    /* FB884 001FB884 28000524 */  addiu      $a1, $zero, 0x28
    /* FB888 001FB888 7100023C */  lui        $v0, %hi(D_00710D10)
    /* FB88C 001FB88C 6200043C */  lui        $a0, %hi(D_0061ABF0)
    /* FB890 001FB890 18186500 */  mult       $v1, $v1, $a1
    /* FB894 001FB894 100D4224 */  addiu      $v0, $v0, %lo(D_00710D10)
    /* FB898 001FB898 F0AB8424 */  addiu      $a0, $a0, %lo(D_0061ABF0)
    /* FB89C 001FB89C 21186200 */  addu       $v1, $v1, $v0
    /* FB8A0 001FB8A0 0400668C */  lw         $a2, 0x4($v1)
    /* FB8A4 001FB8A4 2400658C */  lw         $a1, 0x24($v1)
    /* FB8A8 001FB8A8 2328A600 */  subu       $a1, $a1, $a2
    /* FB8AC 001FB8AC 02290500 */  srl        $a1, $a1, 4
    /* FB8B0 001FB8B0 8A9B0608 */  j          func_001A6E28
    /* FB8B4 001FB8B4 FFFFA524 */   addiu     $a1, $a1, -0x1
endlabel func_001FB880
```
