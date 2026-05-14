
---

## Attempt at 2026-05-14

**Reason parked:** TU c-claim too wide; src has only some funcs but asm/matchings has more — link fails on missing ghosts and cascades to gp_rel overflow

Seed: `tough_nuts/func_001010C8/0010C8.c`

Disassembly excerpt:

```
glabel func_001010C8
    /* 10C8 001010C8 0010033C */  lui        $v1, (0x1000F130 >> 16)
    /* 10CC 001010CC 30F16334 */  ori        $v1, $v1, (0x1000F130 & 0xFFFF)
.align 2
  .L001010D0:
    /* 10D0 001010D0 0000628C */  lw         $v0, 0x0($v1)
    /* 10D4 001010D4 00804230 */  andi       $v0, $v0, 0x8000
    /* 10D8 001010D8 00000000 */  nop
    /* 10DC 001010DC 00000000 */  nop
    /* 10E0 001010E0 00000000 */  nop
    /* 10E4 001010E4 FAFF4014 */  bnez       $v0, .L001010D0
    /* 10E8 001010E8 00000000 */   nop
    /* 10EC 001010EC 0010033C */  lui        $v1, (0x1000F180 >> 16)
    /* 10F0 001010F0 2D108000 */  daddu      $v0, $a0, $zero
    /* 10F4 001010F4 80F16334 */  ori        $v1, $v1, (0x1000F180 & 0xFFFF)
    /* 10F8 001010F8 0800E003 */  jr         $ra
    /* 10FC 001010FC 000064A0 */   sb        $a0, 0x0($v1)
endlabel func_001010C8
```
