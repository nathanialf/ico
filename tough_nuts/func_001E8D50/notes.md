# func_001E8D50 — parked

VRAM: 0x001E8D50 (file offset 0x0E8D50)
Asm source: asm/cod/0E8D4C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** mult+addu regalloc

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001E8D50
    /* E8D50 001E8D50 18000324 */  addiu      $v1, $zero, 0x18
    /* E8D54 001E8D54 7100023C */  lui        $v0, %hi(D_007097F0)
    /* E8D58 001E8D58 18208300 */  mult       $a0, $a0, $v1
    /* E8D5C 001E8D5C F0974224 */  addiu      $v0, $v0, %lo(D_007097F0)
    /* E8D60 001E8D60 21104400 */  addu       $v0, $v0, $a0
    /* E8D64 001E8D64 0800E003 */  jr         $ra
    /* E8D68 001E8D68 040040AC */   sw        $zero, 0x4($v0)
endlabel func_001E8D50
```
