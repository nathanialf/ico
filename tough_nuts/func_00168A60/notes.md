# func_00168A60 — parked

VRAM: 0x00168A60 (file offset 0x068A60)
Asm source: asm/cod/068A3C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** conditional-return deref pattern (sibling of 168A40)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00168A60
    /* 68A60 00168A60 9400828C */  lw         $v0, 0x94($a0)
    /* 68A64 00168A64 03004010 */  beqz       $v0, .L00168A74
    /* 68A68 00168A68 2D100000 */   daddu     $v0, $zero, $zero
    /* 68A6C 00168A6C 0800E003 */  jr         $ra
    /* 68A70 00168A70 9800828C */   lw        $v0, 0x98($a0)
.align 2
  .L00168A74:
    /* 68A74 00168A74 0800E003 */  jr         $ra
    /* 68A78 00168A78 00000000 */   nop
endlabel func_00168A60
```
