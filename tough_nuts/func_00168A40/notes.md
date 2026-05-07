# func_00168A40 — parked

VRAM: 0x00168A40 (file offset 0x068A40)
Asm source: asm/cod/068A3C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** conditional-return deref pattern, regalloc divergence

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00168A40
    /* 68A40 00168A40 8800828C */  lw         $v0, 0x88($a0)
    /* 68A44 00168A44 03004010 */  beqz       $v0, .L00168A54
    /* 68A48 00168A48 2D100000 */   daddu     $v0, $zero, $zero
    /* 68A4C 00168A4C 0800E003 */  jr         $ra
    /* 68A50 00168A50 9800828C */   lw        $v0, 0x98($a0)
.align 2
  .L00168A54:
    /* 68A54 00168A54 0800E003 */  jr         $ra
    /* 68A58 00168A58 00000000 */   nop
endlabel func_00168A40
```
