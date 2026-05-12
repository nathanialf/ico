
---

## Attempt at 2026-05-08

**Reason parked:** wrap-gp-1jal alloc+head-insert: ee-gcc emits bnel for if(old) old->_94=d, original uses beqz+swc1 in delay slot

Seed: `tough_nuts/func_00117820/017820.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00117820; check asm/matchings/cod/017820/)
```

---

## Attempt at 2026-05-12

**Reason parked:** target.s won't assemble: 'macro used $at after .set noat' for gp_rel pseudo-op

Seed: `tough_nuts/func_00117820/017820.c.new`

Disassembly excerpt:

```
glabel func_00117820
    /* 17820 00117820 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 17824 00117824 5500063C */  lui        $a2, %hi(D_00554CA8)
    /* 17828 00117828 0000B0FF */  sd         $s0, 0x0($sp)
    /* 1782C 0011782C A84CC624 */  addiu      $a2, $a2, %lo(D_00554CA8)
    /* 17830 00117830 2D808000 */  daddu      $s0, $a0, $zero
    /* 17834 00117834 1000BFFF */  sd         $ra, 0x10($sp)
    /* 17838 00117838 3497848F */  lw         $a0, %gp_rel(D_00632024)($gp)
    /* 1783C 0011783C A0000524 */  addiu      $a1, $zero, 0xA0
    /* 17840 00117840 3EE8040C */  jal        func_0013A0F8
    /* 17844 00117844 D3020724 */   addiu     $a3, $zero, 0x2D3
    /* 17848 00117848 2D184000 */  daddu      $v1, $v0, $zero
    /* 1784C 0011784C 803F013C */  lui        $at, (0x3F800000 >> 16)
    /* 17850 00117850 00008144 */  mtc1       $at, $f0
    /* 17854 00117854 44B3828F */  lw         $v0, %gp_rel(D_00633C34)($gp)
    /* 17858 00117858 900070AC */  sw         $s0, 0x90($v1)
    /* 1785C 0011785C 2D204000 */  daddu      $a0, $v0, $zero
    /* 17860 00117860 02004010 */  beqz       $v0, .L0011786C
    /* 17864 00117864 800060E4 */   swc1      $f0, 0x80($v1)
    /* 17868 00117868 940043AC */  sw         $v1, 0x94($v0)
.align 2
  .L0011786C:
    /* 1786C 0011786C 1000BFDF */  ld         $ra, 0x10($sp)
    /* 17870 00117870 2D106000 */  daddu      $v0, $v1, $zero
    /* 17874 00117874 0000B0DF */  ld         $s0, 0x0($sp)
    /* 17878 00117878 980064AC */  sw         $a0, 0x98($v1)
    /* 1787C 0011787C 940060AC */  sw         $zero, 0x94($v1)
    /* 17880 00117880 44B383AF */  sw         $v1, %gp_rel(D_00633C34)($gp)
    /* 17884 00117884 0800E003 */  jr         $ra
    /* 17888 00117888 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00117820
```
