
---

## Attempt at 2026-05-08

**Reason parked:** GIF-tag wrapper: ee-gcc 2.9 -O2 collapses (p+1)+1 to addiu v0,a0,8 instead of split addiu a0,a0,4; addiu v0,a0,4

Seed: `tough_nuts/func_00245120/145120.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00245120; check asm/matchings/cod/145120/)
```

---

## Attempt at 2026-05-13

**Reason parked:** 2 cosmetic scheduling diffs: daddu s1 and or s0 placements

Seed: `tough_nuts/func_00245120/145120.c.new`

Disassembly excerpt:

```
glabel func_00245120
    /* 145120 00245120 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* 145124 00245124 1000B1FF */  sd         $s1, 0x10($sp)
    /* 145128 00245128 2D888000 */  daddu      $s1, $a0, $zero
    /* 14512C 0024512C 0000B0FF */  sd         $s0, 0x0($sp)
    /* 145130 00245130 2000BFFF */  sd         $ra, 0x20($sp)
    /* 145134 00245134 3214090C */  jal        func_002450C8
    /* 145138 00245138 2D80A000 */   daddu     $s0, $a1, $zero
    /* 14513C 0024513C 0000248E */  lw         $a0, 0x0($s1)
    /* 145140 00245140 0010033C */  lui        $v1, (0x10000000 >> 16)
    /* 145144 00245144 25800302 */  or         $s0, $s0, $v1
    /* 145148 00245148 080022AE */  sw         $v0, 0x8($s1)
    /* 14514C 0024514C 000090AC */  sw         $s0, 0x0($a0)
    /* 145150 00245150 04008424 */  addiu      $a0, $a0, 0x4
    /* 145154 00245154 0C0020AE */  sw         $zero, 0xC($s1)
    /* 145158 00245158 04008224 */  addiu      $v0, $a0, 0x4
    /* 14515C 0024515C 2000BFDF */  ld         $ra, 0x20($sp)
    /* 145160 00245160 000022AE */  sw         $v0, 0x0($s1)
    /* 145164 00245164 1000B1DF */  ld         $s1, 0x10($sp)
    /* 145168 00245168 0000B0DF */  ld         $s0, 0x0($sp)
    /* 14516C 0024516C 000080AC */  sw         $zero, 0x0($a0)
    /* 145170 00245170 0800E003 */  jr         $ra
    /* 145174 00245174 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_00245120
```

---

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B macros (KEEP_LIVE,REG)

Seed: `tough_nuts/func_00245120/145120.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00245120; check asm/matchings/cod/145120/)
```
