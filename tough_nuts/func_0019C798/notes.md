
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_0019C798/09C798.c`

Disassembly excerpt:

```
glabel func_0019C798
    /* 9C798 0019C798 0C9F8297 */  lhu        $v0, %gp_rel(D_006327FC)($gp)
    /* 9C79C 0019C79C F4B4838F */  lw         $v1, %gp_rel(D_00633DE4)($gp)
    /* 9C7A0 0019C7A0 D0074224 */  addiu      $v0, $v0, 0x7D0
    /* 9C7A4 0019C7A4 F0B4848F */  lw         $a0, %gp_rel(D_00633DE0)($gp)
    /* 9C7A8 0019C7A8 00106324 */  addiu      $v1, $v1, 0x1000
    /* 9C7AC 0019C7AC 0C9F82A7 */  sh         $v0, %gp_rel(D_006327FC)($gp)
    /* 9C7B0 0019C7B0 05008018 */  blez       $a0, .L0019C7C8
    /* 9C7B4 0019C7B4 F4B483AF */   sw        $v1, %gp_rel(D_00633DE4)($gp)
    /* 9C7B8 0019C7B8 FFFF8224 */  addiu      $v0, $a0, -0x1
    /* 9C7BC 0019C7BC 02004104 */  bgez       $v0, .L0019C7C8
    /* 9C7C0 0019C7C0 F0B482AF */   sw        $v0, %gp_rel(D_00633DE0)($gp)
    /* 9C7C4 0019C7C4 F0B480AF */  sw         $zero, %gp_rel(D_00633DE0)($gp)
.align 2
  .L0019C7C8:
    /* 9C7C8 0019C7C8 0800E003 */  jr         $ra
    /* 9C7CC 0019C7CC 00000000 */   nop
endlabel func_0019C798
```
