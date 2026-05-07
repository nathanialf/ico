# func_0018CF60 — parked

VRAM: 0x0018CF60 (file offset 0x08CF60)
Asm source: asm/cod/08CF60.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** lui-in-delay-slot ordering

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_0018CF60
    /* 8CF60 0018CF60 409E828F */  lw         $v0, %gp_rel(D_00632730)($gp)
    /* 8CF64 0018CF64 03004014 */  bnez       $v0, .L0018CF74
    /* 8CF68 0018CF68 6D00023C */   lui       $v0, %hi(D_006D0680)
    /* 8CF6C 0018CF6C 0800E003 */  jr         $ra
    /* 8CF70 0018CF70 2D100000 */   daddu     $v0, $zero, $zero
.align 2
  .L0018CF74:
    /* 8CF74 0018CF74 0800E003 */  jr         $ra
    /* 8CF78 0018CF78 80064224 */   addiu     $v0, $v0, %lo(D_006D0680)
endlabel func_0018CF60
```
