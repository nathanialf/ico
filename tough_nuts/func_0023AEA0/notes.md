# func_0023AEA0 — parked

VRAM: 0x0023AEA0 (file offset 0x13AEA0)
Asm source: asm/cod/13AD68.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sw 0x16C ordering

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0023AEA0
    /* 13AEA0 0023AEA0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 13AEA4 0023AEA4 0000A4AF */  sw         $a0, 0x0($sp)
    /* 13AEA8 0023AEA8 1000BFFF */  sd         $ra, 0x10($sp)
    /* 13AEAC 0023AEAC 62F8050C */  jal        func_0017E188
    /* 13AEB0 0023AEB0 B5010424 */   addiu     $a0, $zero, 0x1B5
    /* 13AEB4 0023AEB4 01000324 */  addiu      $v1, $zero, 0x1
    /* 13AEB8 0023AEB8 B6010424 */  addiu      $a0, $zero, 0x1B6
    /* 13AEBC 0023AEBC 62F8050C */  jal        func_0017E188
    /* 13AEC0 0023AEC0 6C0143AC */   sw        $v1, 0x16C($v0)
    /* 13AEC4 0023AEC4 1000BFDF */  ld         $ra, 0x10($sp)
    /* 13AEC8 0023AEC8 6C0140AC */  sw         $zero, 0x16C($v0)
    /* 13AECC 0023AECC 0800E003 */  jr         $ra
    /* 13AED0 0023AED0 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0023AEA0
```
