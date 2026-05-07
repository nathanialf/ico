# func_00245DB8 — parked

VRAM: 0x00245DB8 (file offset 0x145DB8)
Asm source: asm/cod/1456F8.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** lui v0/v1 swap

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00245DB8
    /* 145DB8 00245DB8 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 145DBC 00245DBC 0000BFFF */  sd         $ra, 0x0($sp)
    /* 145DC0 00245DC0 D62E090C */  jal        func_0024BB58
    /* 145DC4 00245DC4 00000000 */   nop
    /* 145DC8 00245DC8 5500023C */  lui        $v0, %hi(D_005507D8)
    /* 145DCC 00245DCC 0000BFDF */  ld         $ra, 0x0($sp)
    /* 145DD0 00245DD0 D80740AC */  sw         $zero, %lo(D_005507D8)($v0)
    /* 145DD4 00245DD4 0800E003 */  jr         $ra
    /* 145DD8 00245DD8 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_00245DB8
```
