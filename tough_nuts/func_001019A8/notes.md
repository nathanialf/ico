
---

## Attempt at 2026-05-12

**Reason parked:** permuter score-0 file mismatch: addiu a1,sp,128 vs expected addiu a1,sp,88; va_list builtin_next_arg emits post-frame offset

Seed: `tough_nuts/func_001019A8/0019A8.c`

Disassembly excerpt:

```
glabel func_001019A8
    /* 19A8 001019A8 70FFBD27 */  addiu      $sp, $sp, -0x90
    /* 19AC 001019AC 5800A5FF */  sd         $a1, 0x58($sp)
    /* 19B0 001019B0 0000BFFF */  sd         $ra, 0x0($sp)
    /* 19B4 001019B4 5800A527 */  addiu      $a1, $sp, 0x58
    /* 19B8 001019B8 6000A6FF */  sd         $a2, 0x60($sp)
    /* 19BC 001019BC 6800A7FF */  sd         $a3, 0x68($sp)
    /* 19C0 001019C0 7000A8FF */  sd         $t0, 0x70($sp)
    /* 19C4 001019C4 7800A9FF */  sd         $t1, 0x78($sp)
    /* 19C8 001019C8 8000AAFF */  sd         $t2, 0x80($sp)
    /* 19CC 001019CC F804040C */  jal        func_001013E0
    /* 19D0 001019D0 8800ABFF */   sd        $t3, 0x88($sp)
    /* 19D4 001019D4 0000BFDF */  ld         $ra, 0x0($sp)
    /* 19D8 001019D8 0800E003 */  jr         $ra
    /* 19DC 001019DC 9000BD27 */   addiu     $sp, $sp, 0x90
endlabel func_001019A8
```

---

## Attempt at 2026-05-14

**Reason parked:** va_list emits addiu a1,sp,FRAME (144) not sp+0x58 (88) — score-0 was structural not values

Seed: `tough_nuts/func_001019A8/0019A8.c.new`

Disassembly excerpt:

```
glabel func_001019A8
    /* 19A8 001019A8 70FFBD27 */  addiu      $sp, $sp, -0x90
    /* 19AC 001019AC 5800A5FF */  sd         $a1, 0x58($sp)
    /* 19B0 001019B0 0000BFFF */  sd         $ra, 0x0($sp)
    /* 19B4 001019B4 5800A527 */  addiu      $a1, $sp, 0x58
    /* 19B8 001019B8 6000A6FF */  sd         $a2, 0x60($sp)
    /* 19BC 001019BC 6800A7FF */  sd         $a3, 0x68($sp)
    /* 19C0 001019C0 7000A8FF */  sd         $t0, 0x70($sp)
    /* 19C4 001019C4 7800A9FF */  sd         $t1, 0x78($sp)
    /* 19C8 001019C8 8000AAFF */  sd         $t2, 0x80($sp)
    /* 19CC 001019CC F804040C */  jal        func_001013E0
    /* 19D0 001019D0 8800ABFF */   sd        $t3, 0x88($sp)
    /* 19D4 001019D4 0000BFDF */  ld         $ra, 0x0($sp)
    /* 19D8 001019D8 0800E003 */  jr         $ra
    /* 19DC 001019DC 9000BD27 */   addiu     $sp, $sp, 0x90
endlabel func_001019A8
```
