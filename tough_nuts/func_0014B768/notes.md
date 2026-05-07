# func_0014B768 — parked

VRAM: 0x0014B768 (file offset 0x04B768)
Asm source: asm/cod/04B5B4.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sw 0x174/0x170 store ordering

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0014B768
    /* 4B768 0014B768 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 4B76C 0014B76C 1000BFFF */  sd         $ra, 0x10($sp)
    /* 4B770 0014B770 0000B0FF */  sd         $s0, 0x0($sp)
    /* 4B774 0014B774 6401908C */  lw         $s0, 0x164($a0)
    /* 4B778 0014B778 7001048E */  lw         $a0, 0x170($s0)
    /* 4B77C 0014B77C 06008010 */  beqz       $a0, .L0014B798
    /* 4B780 0014B780 1000BFDF */   ld        $ra, 0x10($sp)
    /* 4B784 0014B784 B249070C */  jal        func_001D26C8
    /* 4B788 0014B788 00000000 */   nop
    /* 4B78C 0014B78C 740100AE */  sw         $zero, 0x174($s0)
    /* 4B790 0014B790 700100AE */  sw         $zero, 0x170($s0)
    /* 4B794 0014B794 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L0014B798:
    /* 4B798 0014B798 0000B0DF */  ld         $s0, 0x0($sp)
    /* 4B79C 0014B79C 0800E003 */  jr         $ra
    /* 4B7A0 0014B7A0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0014B768
```
