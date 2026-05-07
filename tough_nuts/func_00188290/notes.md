# func_00188290 — parked

VRAM: 0x00188290 (file offset 0x088290)
Asm source: asm/cod/088228.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** mult+addu sequencing

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00188290
    /* 88290 00188290 A090838F */  lw         $v1, %gp_rel(D_00631990)($gp)
    /* 88294 00188294 94010424 */  addiu      $a0, $zero, 0x194
    /* 88298 00188298 5F00023C */  lui        $v0, %hi(D_005F2FB8)
    /* 8829C 0018829C 18186400 */  mult       $v1, $v1, $a0
    /* 882A0 001882A0 B82F4224 */  addiu      $v0, $v0, %lo(D_005F2FB8)
    /* 882A4 001882A4 21104300 */  addu       $v0, $v0, $v1
    /* 882A8 001882A8 8A200608 */  j          func_00188228
    /* 882AC 001882AC 1801448C */   lw        $a0, 0x118($v0)
endlabel func_00188290
```
