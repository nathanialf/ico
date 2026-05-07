# func_0024D9B8 — parked

VRAM: 0x0024D9B8 (file offset 0x14D9B8)
Asm source: asm/cod/14BBC0.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** schedule: daddu register-zero ordering vs ee-gcc 2.9 emit

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0024D9B8
    /* 14D9B8 0024D9B8 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* 14D9BC 0024D9BC 5500023C */  lui        $v0, %hi(D_00552370)
    /* 14D9C0 0024D9C0 7100083C */  lui        $t0, %hi(D_00717BD8)
    /* 14D9C4 0024D9C4 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14D9C8 0024D9C8 702340AC */  sw         $zero, %lo(D_00552370)($v0)
    /* 14D9CC 0024D9CC D87B0825 */  addiu      $t0, $t0, %lo(D_00717BD8)
    /* 14D9D0 0024D9D0 4C37090C */  jal        func_0024DD30
    /* 14D9D4 0024D9D4 05000724 */   addiu     $a3, $zero, 0x5
    /* 14D9D8 0024D9D8 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14D9DC 0024D9DC 0800E003 */  jr         $ra
    /* 14D9E0 0024D9E0 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024D9B8
```
