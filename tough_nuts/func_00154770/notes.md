# func_00154770 — parked

VRAM: 0x00154770 (file offset 0x054770)
Asm source: asm/cod/054668.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** bnezl/beqz branch sense (similar to 1538F8)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00154770
    /* 54770 00154770 6B00033C */  lui        $v1, %hi(D_006AAB30)
    /* 54774 00154774 30AB6290 */  lbu        $v0, %lo(D_006AAB30)($v1)
    /* 54778 00154778 03004010 */  beqz       $v0, .L00154788
    /* 5477C 0015477C 30AB6424 */   addiu     $a0, $v1, %lo(D_006AAB30)
    /* 54780 00154780 0800E003 */  jr         $ra
    /* 54784 00154784 0400828C */   lw        $v0, 0x4($a0)
.align 2
  .L00154788:
    /* 54788 00154788 0800E003 */  jr         $ra
    /* 5478C 0015478C 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_00154770
```
