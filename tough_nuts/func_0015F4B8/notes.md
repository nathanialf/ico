# func_0015F4B8 — parked

VRAM: 0x0015F4B8 (file offset 0x05F4B8)
Asm source: asm/cod/05F244.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** lw a0 in delay slot

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0015F4B8
    /* 5F4B8 0015F4B8 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 5F4BC 0015F4BC 0000A4AF */  sw         $a0, 0x0($sp)
    /* 5F4C0 0015F4C0 0000A48F */  lw         $a0, 0x0($sp)
    /* 5F4C4 0015F4C4 1000BFFF */  sd         $ra, 0x10($sp)
    /* 5F4C8 0015F4C8 AA27050C */  jal        func_00149EA8
    /* 5F4CC 0015F4CC 00000000 */   nop
    /* 5F4D0 0015F4D0 1000BFDF */  ld         $ra, 0x10($sp)
    /* 5F4D4 0015F4D4 0800E003 */  jr         $ra
    /* 5F4D8 0015F4D8 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0015F4B8
```
