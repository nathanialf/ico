# func_00205B50 — parked

VRAM: 0x00205B50 (file offset 0x105B50)
Asm source: asm/cod/105B4C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** mult result regalloc

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00205B50
    /* 105B50 00205B50 34000224 */  addiu      $v0, $zero, 0x34
    /* 105B54 00205B54 4D00033C */  lui        $v1, %hi(D_004CAEC0)
    /* 105B58 00205B58 18208200 */  mult       $a0, $a0, $v0
    /* 105B5C 00205B5C C0AE6324 */  addiu      $v1, $v1, %lo(D_004CAEC0)
    /* 105B60 00205B60 21186400 */  addu       $v1, $v1, $a0
    /* 105B64 00205B64 2800628C */  lw         $v0, 0x28($v1)
    /* 105B68 00205B68 0800E003 */  jr         $ra
    /* 105B6C 00205B6C 2B100200 */   sltu      $v0, $zero, $v0
endlabel func_00205B50
```
