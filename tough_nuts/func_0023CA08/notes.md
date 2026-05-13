
---

## Attempt at 2026-05-12

**Reason parked:** 3-float write: lui+mtc1 (1800.0) emit order differs (after gp_rel loads vs before)

Seed: `tough_nuts/func_0023CA08/13CA08.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023CA08; check asm/matchings/cod/13CA08/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: same scheduler issue as 23CCB8 — interleaved compute+store vs all-loads-first

Seed: `tough_nuts/func_0023CA08/13CA08.c.new`

Disassembly excerpt:

```
glabel func_0023CA08
    /* 13CA08 0023CA08 3400838C */  lw         $v1, 0x34($a0)
    /* 13CA0C 0023CA0C 01000224 */  addiu      $v0, $zero, 0x1
    /* 13CA10 0023CA10 E144013C */  lui        $at, (0x44E10000 >> 16)
    /* 13CA14 0023CA14 00188144 */  mtc1       $at, $f3
    /* 13CA18 0023CA18 4C8F82C7 */  lwc1       $f2, %gp_rel(D_0063183C)($gp)
    /* 13CA1C 0023CA1C 508F80C7 */  lwc1       $f0, %gp_rel(D_00631840)($gp)
    /* 13CA20 0023CA20 803F013C */  lui        $at, (0x3F800000 >> 16)
    /* 13CA24 0023CA24 00088144 */  mtc1       $at, $f1
    /* 13CA28 0023CA28 080060E4 */  swc1       $f0, 0x8($v1)
    /* 13CA2C 0023CA2C 000063E4 */  swc1       $f3, 0x0($v1)
    /* 13CA30 0023CA30 040062E4 */  swc1       $f2, 0x4($v1)
    /* 13CA34 0023CA34 0800E003 */  jr         $ra
    /* 13CA38 0023CA38 180081E4 */   swc1      $f1, 0x18($a0)
endlabel func_0023CA08
```
