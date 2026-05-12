
---

## Attempt at 2026-05-08

**Reason parked:** func_00203B40 wrapper for func_001C34C0: same shape near-miss as func_001F22E0 (store-order + v0->v1 intermediate)

Seed: `tough_nuts/func_001C3720/0C3720.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001C3720; check asm/matchings/cod/0C3720/)
```

---

## Attempt at 2026-05-11

**Reason parked:** near-miss regalloc: built reuses v0 directly for sw s0; expected has daddu v1,v0 copy then sw s0 via v1. Tried regpin REG("$3"), KEEP_LIVE, long long return — none defeat gcc 2.9's v0 reuse.

Seed: `tough_nuts/func_001C3720/0C3720.c.new`

Disassembly excerpt:

```
glabel func_001C3720
    /* C3720 001C3720 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* C3724 001C3724 15000524 */  addiu      $a1, $zero, 0x15
    /* C3728 001C3728 0000B0FF */  sd         $s0, 0x0($sp)
    /* C372C 001C372C 2D808000 */  daddu      $s0, $a0, $zero
    /* C3730 001C3730 1000BFFF */  sd         $ra, 0x10($sp)
    /* C3734 001C3734 1C00043C */  lui        $a0, %hi(func_001C34C0)
    /* C3738 001C3738 D00E080C */  jal        func_00203B40
    /* C373C 001C373C C0348424 */   addiu     $a0, $a0, %lo(func_001C34C0)
    /* C3740 001C3740 2D184000 */  daddu      $v1, $v0, $zero
    /* C3744 001C3744 000000AE */  sw         $zero, 0x0($s0)
    /* C3748 001C3748 200070AC */  sw         $s0, 0x20($v1)
    /* C374C 001C374C 1000BFDF */  ld         $ra, 0x10($sp)
    /* C3750 001C3750 0000B0DF */  ld         $s0, 0x0($sp)
    /* C3754 001C3754 0800E003 */  jr         $ra
    /* C3758 001C3758 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_001C3720
```

---

## Attempt at 2026-05-12

**Reason parked:** missing daddu v1,v0,zero after jal; built uses v0 directly for h+0x20 store

Seed: `tough_nuts/func_001C3720/0C3720.c.new`

Disassembly excerpt:

```
glabel func_001C3720
    /* C3720 001C3720 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* C3724 001C3724 15000524 */  addiu      $a1, $zero, 0x15
    /* C3728 001C3728 0000B0FF */  sd         $s0, 0x0($sp)
    /* C372C 001C372C 2D808000 */  daddu      $s0, $a0, $zero
    /* C3730 001C3730 1000BFFF */  sd         $ra, 0x10($sp)
    /* C3734 001C3734 1C00043C */  lui        $a0, %hi(func_001C34C0)
    /* C3738 001C3738 D00E080C */  jal        func_00203B40
    /* C373C 001C373C C0348424 */   addiu     $a0, $a0, %lo(func_001C34C0)
    /* C3740 001C3740 2D184000 */  daddu      $v1, $v0, $zero
    /* C3744 001C3744 000000AE */  sw         $zero, 0x0($s0)
    /* C3748 001C3748 200070AC */  sw         $s0, 0x20($v1)
    /* C374C 001C374C 1000BFDF */  ld         $ra, 0x10($sp)
    /* C3750 001C3750 0000B0DF */  ld         $s0, 0x0($sp)
    /* C3754 001C3754 0800E003 */  jr         $ra
    /* C3758 001C3758 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_001C3720
```
