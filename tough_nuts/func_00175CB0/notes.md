# func_00175CB0 — parked

VRAM: 0x00175CB0 (file offset 0x075CB0)
Asm source: asm/cod/075CB0.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sw+lw elimination

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00175CB0
    /* 75CB0 00175CB0 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 75CB4 00175CB4 0000A4AF */  sw         $a0, 0x0($sp)
    /* 75CB8 00175CB8 1000BFFF */  sd         $ra, 0x10($sp)
    /* 75CBC 00175CBC 2D200000 */  daddu      $a0, $zero, $zero
    /* 75CC0 00175CC0 0000A28F */  lw         $v0, 0x0($sp)
    /* 75CC4 00175CC4 6401438C */  lw         $v1, 0x164($v0)
    /* 75CC8 00175CC8 A80E080C */  jal        func_00203AA0
    /* 75CCC 00175CCC 3C0360AC */   sw        $zero, 0x33C($v1)
    /* 75CD0 00175CD0 1000BFDF */  ld         $ra, 0x10($sp)
    /* 75CD4 00175CD4 0800E003 */  jr         $ra
    /* 75CD8 00175CD8 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00175CB0
```
