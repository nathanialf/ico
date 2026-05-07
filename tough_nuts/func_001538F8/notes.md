# func_001538F8 — parked

VRAM: 0x001538F8 (file offset 0x0538F8)
Asm source: asm/cod/0538F4.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** bnezl vs beqz branch sense

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001538F8
    /* 538F8 001538F8 F491828F */  lw         $v0, %gp_rel(D_00631AE4)($gp)
    /* 538FC 001538FC 04004010 */  beqz       $v0, .L00153910
    /* 53900 00153900 00000000 */   nop
    /* 53904 00153904 6401438C */  lw         $v1, 0x164($v0)
    /* 53908 00153908 0800E003 */  jr         $ra
    /* 5390C 0015390C 4001628C */   lw        $v0, 0x140($v1)
.align 2
  .L00153910:
    /* 53910 00153910 0800E003 */  jr         $ra
    /* 53914 00153914 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_001538F8
```
