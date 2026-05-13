
---

## Attempt at 2026-05-13

**Reason parked:** gcc emits bnel vs expected beql; otherwise body matches

Seed: `tough_nuts/func_00156488/056488.c`

Disassembly excerpt:

```
glabel func_00156488
    /* 56488 00156488 2D188000 */  daddu      $v1, $a0, $zero
    /* 5648C 0015648C 6401648C */  lw         $a0, 0x164($v1)
    /* 56490 00156490 2C00828C */  lw         $v0, 0x2C($a0)
    /* 56494 00156494 02004050 */  beql       $v0, $zero, .L001564A0
    /* 56498 00156498 D005858C */   lw        $a1, 0x5D0($a0)
    /* 5649C 0015649C 0000458C */  lw         $a1, 0x0($v0)
.align 2
  .L001564A0:
    /* 564A0 001564A0 F491828F */  lw         $v0, %gp_rel(D_00631AE4)($gp)
    /* 564A4 001564A4 07006214 */  bne        $v1, $v0, .L001564C4
    /* 564A8 001564A8 00000000 */   nop
    /* 564AC 001564AC 4001848C */  lw         $a0, 0x140($a0)
    /* 564B0 001564B0 04008010 */  beqz       $a0, .L001564C4
    /* 564B4 001564B4 00000000 */   nop
    /* 564B8 001564B8 5C01828C */  lw         $v0, 0x15C($a0)
    /* 564BC 001564BC E2CC0708 */  j          func_001F3388
    /* 564C0 001564C0 F40545AC */   sw        $a1, 0x5F4($v0)
.align 2
  .L001564C4:
    /* 564C4 001564C4 0800E003 */  jr         $ra
    /* 564C8 001564C8 00000000 */   nop
endlabel func_00156488
```
