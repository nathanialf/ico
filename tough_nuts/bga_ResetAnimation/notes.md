
---

## Attempt at 2026-05-08

**Reason parked:** wrap-gp-1jal list-walk: ee-gcc emits jal-delay arg-setup; original preloads a0 pre-loop and reuses bnez delay for next-iter a0

Seed: `tough_nuts/bga_ResetAnimation/0FAA58.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for bga_ResetAnimation; check asm/matchings/cod/0FAA58/)
```

---

## Attempt at 2026-05-13

**Reason parked:** ld ra early + daddu a0,s0 in delay vs before jal

Seed: `tough_nuts/bga_ResetAnimation/0FAA58.c.new`

Disassembly excerpt:

```
glabel bga_ResetAnimation
    /* FAA58 001FAA58 2700033C */  lui        $v1, %hi(D_00274ED4)
    /* FAA5C 001FAA5C E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* FAA60 001FAA60 D44E628C */  lw         $v0, %lo(D_00274ED4)($v1)
    /* FAA64 001FAA64 1000BFFF */  sd         $ra, 0x10($sp)
    /* FAA68 001FAA68 0000B0FF */  sd         $s0, 0x0($sp)
    /* FAA6C 001FAA6C 0A004014 */  bnez       $v0, .L001FAA98
    /* FAA70 001FAA70 74B680AF */   sw        $zero, %gp_rel(D_00633F64)($gp)
    /* FAA74 001FAA74 CCAE908F */  lw         $s0, %gp_rel(D_006337BC)($gp)
    /* FAA78 001FAA78 07000012 */  beqz       $s0, .L001FAA98
    /* FAA7C 001FAA7C CCAE80AF */   sw        $zero, %gp_rel(D_006337BC)($gp)
    /* FAA80 001FAA80 2D200002 */  daddu      $a0, $s0, $zero
    /* FAA84 001FAA84 00000000 */  nop
.align 2
  .L001FAA88:
    /* FAA88 001FAA88 64DB070C */  jal        func_001F6D90
    /* FAA8C 001FAA8C 5401108E */   lw        $s0, 0x154($s0)
    /* FAA90 001FAA90 FDFF0016 */  bnez       $s0, .L001FAA88
    /* FAA94 001FAA94 2D200002 */   daddu     $a0, $s0, $zero
.align 2
  .L001FAA98:
    /* FAA98 001FAA98 1000BFDF */  ld         $ra, 0x10($sp)
    /* FAA9C 001FAA9C 0000B0DF */  ld         $s0, 0x0($sp)
    /* FAAA0 001FAAA0 0800E003 */  jr         $ra
    /* FAAA4 001FAAA4 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel bga_ResetAnimation
```

---

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B macros (NOP)

Seed: `tough_nuts/bga_ResetAnimation/0FAA58.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for bga_ResetAnimation; check asm/matchings/cod/0FAA58/)
```
