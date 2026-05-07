# func_00193F48 — parked

VRAM: 0x00193F48 (file offset 0x093F48)
Asm source: asm/cod/093EDC.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** mult+addu sequencing (similar to 188290)

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00193F48
    /* 93F48 00193F48 0800838C */  lw         $v1, 0x8($a0)
    /* 93F4C 00193F4C 2A00023C */  lui        $v0, %hi(D_002A4C48)
    /* 93F50 00193F50 4C000424 */  addiu      $a0, $zero, 0x4C
    /* 93F54 00193F54 484C4224 */  addiu      $v0, $v0, %lo(D_002A4C48)
    /* 93F58 00193F58 18186400 */  mult       $v1, $v1, $a0
    /* 93F5C 00193F5C 21186200 */  addu       $v1, $v1, $v0
    /* 93F60 00193F60 0800E003 */  jr         $ra
    /* 93F64 00193F64 420060A4 */   sh        $zero, 0x42($v1)
endlabel func_00193F48
```
