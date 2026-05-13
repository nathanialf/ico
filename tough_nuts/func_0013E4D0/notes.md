
---

## Attempt at 2026-05-09

**Reason parked:** stores D_00633CA4/CA0 schedule into beqz delay slot — needs specific idiom

Seed: `tough_nuts/func_0013E4D0/03E4D0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013E4D0; check asm/matchings/cod/03E4D0/)
```

---

## Attempt at 2026-05-13

**Reason parked:** ee-as picks daddu v1,v0,zero+beq early instead of sw s0+beq

Seed: `tough_nuts/func_0013E4D0/03E4D0.c.new`

Disassembly excerpt:

```
glabel func_0013E4D0
    /* 3E4D0 0013E4D0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 3E4D4 0013E4D4 74010524 */  addiu      $a1, $zero, 0x174
    /* 3E4D8 0013E4D8 0000B0FF */  sd         $s0, 0x0($sp)
    /* 3E4DC 0013E4DC 5500063C */  lui        $a2, %hi(D_00557A10)
    /* 3E4E0 0013E4E0 2D808000 */  daddu      $s0, $a0, $zero
    /* 3E4E4 0013E4E4 1000BFFF */  sd         $ra, 0x10($sp)
    /* 3E4E8 0013E4E8 18000502 */  mult       $zero, $s0, $a1
    /* 3E4EC 0013E4EC 1897848F */  lw         $a0, %gp_rel(D_00632008)($gp)
    /* 3E4F0 0013E4F0 107AC624 */  addiu      $a2, $a2, %lo(D_00557A10)
    /* 3E4F4 0013E4F4 12280000 */  mflo       $a1
    /* 3E4F8 0013E4F8 3EE8040C */  jal        func_0013A0F8
    /* 3E4FC 0013E4FC AE000724 */   addiu     $a3, $zero, 0xAE
    /* 3E500 0013E500 B4B390AF */  sw         $s0, %gp_rel(D_00633CA4)($gp)
    /* 3E504 0013E504 2D200000 */  daddu      $a0, $zero, $zero
    /* 3E508 0013E508 0B000012 */  beqz       $s0, .L0013E538
    /* 3E50C 0013E50C B0B382AF */   sw        $v0, %gp_rel(D_00633CA0)($gp)
    /* 3E510 0013E510 2D184000 */  daddu      $v1, $v0, $zero
    /* 3E514 0013E514 FFFF0524 */  addiu      $a1, $zero, -0x1
.align 2
  .L0013E518:
    /* 3E518 0013E518 000060AC */  sw         $zero, 0x0($v1)
    /* 3E51C 0013E51C 01008424 */  addiu      $a0, $a0, 0x1
    /* 3E520 0013E520 5C0160AC */  sw         $zero, 0x15C($v1)
    /* 3E524 0013E524 2B109000 */  sltu       $v0, $a0, $s0
    /* 3E528 0013E528 080065AC */  sw         $a1, 0x8($v1)
    /* 3E52C 0013E52C 040065AC */  sw         $a1, 0x4($v1)
    /* 3E530 0013E530 F9FF4014 */  bnez       $v0, .L0013E518
    /* 3E534 0013E534 74016324 */   addiu     $v1, $v1, 0x174
.align 2
  .L0013E538:
    /* 3E538 0013E538 1000BFDF */  ld         $ra, 0x10($sp)
    /* 3E53C 0013E53C 0000B0DF */  ld         $s0, 0x0($sp)
    /* 3E540 0013E540 0800E003 */  jr         $ra
    /* 3E544 0013E544 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0013E4D0
```
