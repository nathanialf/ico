
---

## Attempt at 2026-05-09

**Reason parked:** permuter score-0 was false positive: byte mismatch

Seed: `tough_nuts/func_00264060/164060.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00264060; check asm/matchings/cod/164060/)
```

---

## Attempt at 2026-05-12

**Reason parked:** permuter score-0 file mismatch: addiu a2,sp,128 vs expected addiu a2,sp,80 — va_list builtin_next_arg emits post-frame offset

Seed: `tough_nuts/func_00264060/164060.c.new`

Disassembly excerpt:

```
glabel func_00264060
    /* 164060 00264060 80FFBD27 */  addiu      $sp, $sp, -0x80
    /* 164064 00264064 5000A6FF */  sd         $a2, 0x50($sp)
    /* 164068 00264068 0000BFFF */  sd         $ra, 0x0($sp)
    /* 16406C 0026406C 5000A627 */  addiu      $a2, $sp, 0x50
    /* 164070 00264070 5800A7FF */  sd         $a3, 0x58($sp)
    /* 164074 00264074 6000A8FF */  sd         $t0, 0x60($sp)
    /* 164078 00264078 6800A9FF */  sd         $t1, 0x68($sp)
    /* 16407C 0026407C 7000AAFF */  sd         $t2, 0x70($sp)
    /* 164080 00264080 0A97090C */  jal        func_00265C28
    /* 164084 00264084 7800ABFF */   sd        $t3, 0x78($sp)
    /* 164088 00264088 0000BFDF */  ld         $ra, 0x0($sp)
    /* 16408C 0026408C 0800E003 */  jr         $ra
    /* 164090 00264090 8000BD27 */   addiu     $sp, $sp, 0x80
endlabel func_00264060
```
