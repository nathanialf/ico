
---

## Attempt at 2026-05-12

**Reason parked:** reg allocation differs (counter in t0 vs a2); structure correct

Seed: `tough_nuts/func_00187950/087950.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00187950; check asm/matchings/cod/087950/)
```

---

## Attempt at 2026-05-13

**Reason parked:** reg alloc: i/lo/hi pinned wrong; mine uses a3/v0/v1 vs expected t0/a3/a0

Seed: `tough_nuts/func_00187950/087950.c.new`

Disassembly excerpt:

```
glabel func_00187950
    /* 87950 00187950 2D400000 */  daddu      $t0, $zero, $zero
    /* 87954 00187954 0B00A018 */  blez       $a1, .L00187984
    /* 87958 00187958 2D300000 */   daddu     $a2, $zero, $zero
    /* 8795C 0018795C 3800878C */  lw         $a3, 0x38($a0)
    /* 87960 00187960 3C00848C */  lw         $a0, 0x3C($a0)
    /* 87964 00187964 00000000 */  nop
.align 2
  .L00187968:
    /* 87968 00187968 23188700 */  subu       $v1, $a0, $a3
    /* 8796C 0018796C 01000825 */  addiu      $t0, $t0, 0x1
    /* 87970 00187970 2130C300 */  addu       $a2, $a2, $v1
    /* 87974 00187974 2A100501 */  slt        $v0, $t0, $a1
    /* 87978 00187978 00000000 */  nop
    /* 8797C 0018797C FAFF4014 */  bnez       $v0, .L00187968
    /* 87980 00187980 00000000 */   nop
.align 2
  .L00187984:
    /* 87984 00187984 0800E003 */  jr         $ra
    /* 87988 00187988 2D10C000 */   daddu     $v0, $a2, $zero
endlabel func_00187950
```
