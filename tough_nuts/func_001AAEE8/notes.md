
---

## Attempt at 2026-05-12

**Reason parked:** table lookup + movn: structurally matches; addu operand order differs (a1/a0 vs a0/a1)

Seed: `tough_nuts/func_001AAEE8/0AAEE8.c`

Disassembly excerpt:

```
glabel func_001AAEE8
    /* AAEE8 001AAEE8 3C000224 */  addiu      $v0, $zero, 0x3C
    /* AAEEC 001AAEEC 5D00053C */  lui        $a1, %hi(D_005D49E0)
    /* AAEF0 001AAEF0 18208200 */  mult       $a0, $a0, $v0
    /* AAEF4 001AAEF4 E049A524 */  addiu      $a1, $a1, %lo(D_005D49E0)
    /* AAEF8 001AAEF8 2E00063C */  lui        $a2, %hi(D_002E7710)
    /* AAEFC 001AAEFC 8080023C */  lui        $v0, (0x80808000 >> 16)
    /* AAF00 001AAF00 1077C624 */  addiu      $a2, $a2, %lo(D_002E7710)
    /* AAF04 001AAF04 00804234 */  ori        $v0, $v0, (0x80808000 & 0xFFFF)
    /* AAF08 001AAF08 00FF0724 */  addiu      $a3, $zero, -0x100
    /* AAF0C 001AAF0C 2128A400 */  addu       $a1, $a1, $a0
    /* AAF10 001AAF10 2000A38C */  lw         $v1, 0x20($a1)
    /* AAF14 001AAF14 40180300 */  sll        $v1, $v1, 1
    /* AAF18 001AAF18 21186600 */  addu       $v1, $v1, $a2
    /* AAF1C 001AAF1C 00006494 */  lhu        $a0, 0x0($v1)
    /* AAF20 001AAF20 0800E003 */  jr         $ra
    /* AAF24 001AAF24 0B10E400 */   movn      $v0, $a3, $a0
endlabel func_001AAEE8
```
