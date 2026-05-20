
---

## Attempt at 2026-05-08

**Reason parked:** ee-gcc -O2 emits 'move s1,a0;andi s1,s1,0xFFFF' (2 insns) where expected uses 'andi s1,a0,0xFFFF' (1 insn); function-pointer locals don't reduce

Seed: `tough_nuts/func_0024FBF8/14FBF8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0024FBF8; check asm/matchings/cod/14FBF8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** retry: gcc still emits daddu s1+andi instead of single andi s1,a0,0xFFFF

Seed: `tough_nuts/func_0024FBF8/14FBF8.c.new`

Disassembly excerpt:

```
glabel func_0024FBF8
    /* 14FBF8 0024FBF8 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* 14FBFC 0024FBFC 0000B0FF */  sd         $s0, 0x0($sp)
    /* 14FC00 0024FC00 1000B1FF */  sd         $s1, 0x10($sp)
    /* 14FC04 0024FC04 2500103C */  lui        $s0, %hi(func_0024FBD0)
    /* 14FC08 0024FC08 FFFF9130 */  andi       $s1, $a0, 0xFFFF
    /* 14FC0C 0024FC0C 2000BFFF */  sd         $ra, 0x20($sp)
    /* 14FC10 0024FC10 0401040C */  jal        func_00100410
    /* 14FC14 0024FC14 D0FB1026 */   addiu     $s0, $s0, %lo(func_0024FBD0)
    /* 14FC18 0024FC18 2D202002 */  daddu      $a0, $s1, $zero
    /* 14FC1C 0024FC1C 2D280002 */  daddu      $a1, $s0, $zero
    /* 14FC20 0024FC20 A800040C */  jal        func_001002A0
    /* 14FC24 0024FC24 2D304000 */   daddu     $a2, $v0, $zero
    /* 14FC28 0024FC28 2000BFDF */  ld         $ra, 0x20($sp)
    /* 14FC2C 0024FC2C 1000B1DF */  ld         $s1, 0x10($sp)
    /* 14FC30 0024FC30 0000B0DF */  ld         $s0, 0x0($sp)
    /* 14FC34 0024FC34 10010408 */  j          func_00100440
    /* 14FC38 0024FC38 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_0024FBF8
```
