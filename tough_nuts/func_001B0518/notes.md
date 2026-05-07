# func_001B0518 — parked

VRAM: 0x001B0518 (file offset 0x0B0518)
Asm source: asm/cod/0AFB98.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** ori+bne instruction ordering

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001B0518
    /* B0518 001B0518 0C00828C */  lw         $v0, 0xC($a0)
    /* B051C 001B051C 80B5838F */  lw         $v1, %gp_rel(D_00633E70)($gp)
    /* B0520 001B0520 01004234 */  ori        $v0, $v0, 0x1
    /* B0524 001B0524 02008314 */  bne        $a0, $v1, .L001B0530
    /* B0528 001B0528 0C0082AC */   sw        $v0, 0xC($a0)
    /* B052C 001B052C 80B580AF */  sw         $zero, %gp_rel(D_00633E70)($gp)
.align 2
  .L001B0530:
    /* B0530 001B0530 0800E003 */  jr         $ra
    /* B0534 001B0534 00000000 */   nop
endlabel func_001B0518
```
