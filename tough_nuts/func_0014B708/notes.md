
---

## Attempt at 2026-05-09

**Reason parked:** buf init + tail-call complex; codegen mismatch on first try

Seed: `tough_nuts/func_0014B708/04B708.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0014B708; check asm/matchings/cod/04B708/)
```

---

## Attempt at 2026-05-14

**Reason parked:** near-miss: schedule of a1, sd ra, lw v0 reorders

Seed: `tough_nuts/func_0014B708/04B708.c.new`

Disassembly excerpt:

```
glabel func_0014B708
    /* 4B708 0014B708 C0FFBD27 */  addiu      $sp, $sp, -0x40
    /* 4B70C 0014B70C 10000624 */  addiu      $a2, $zero, 0x10
    /* 4B710 0014B710 2000B1FF */  sd         $s1, 0x20($sp)
    /* 4B714 0014B714 1000B0FF */  sd         $s0, 0x10($sp)
    /* 4B718 0014B718 2D88A000 */  daddu      $s1, $a1, $zero
    /* 4B71C 0014B71C 2D808000 */  daddu      $s0, $a0, $zero
    /* 4B720 0014B720 2D280000 */  daddu      $a1, $zero, $zero
    /* 4B724 0014B724 3000BFFF */  sd         $ra, 0x30($sp)
    /* 4B728 0014B728 7690090C */  jal        func_002641D8
    /* 4B72C 0014B72C 2D20A003 */   daddu     $a0, $sp, $zero
    /* 4B730 0014B730 803F013C */  lui        $at, (0x3F800000 >> 16)
    /* 4B734 0014B734 00008144 */  mtc1       $at, $f0
    /* 4B738 0014B738 2D200002 */  daddu      $a0, $s0, $zero
    /* 4B73C 0014B73C 5C01228E */  lw         $v0, 0x15C($s1)
    /* 4B740 0014B740 2D30A003 */  daddu      $a2, $sp, $zero
    /* 4B744 0014B744 0800A0E7 */  swc1       $f0, 0x8($sp)
    /* 4B748 0014B748 2E0E090C */  jal        func_002438B8
    /* 4B74C 0014B74C 0C00458C */   lw        $a1, 0xC($v0)
    /* 4B750 0014B750 3000BFDF */  ld         $ra, 0x30($sp)
    /* 4B754 0014B754 2000B1DF */  ld         $s1, 0x20($sp)
    /* 4B758 0014B758 1000B0DF */  ld         $s0, 0x10($sp)
    /* 4B75C 0014B75C 0800E003 */  jr         $ra
    /* 4B760 0014B760 4000BD27 */   addiu     $sp, $sp, 0x40
endlabel func_0014B708
```
