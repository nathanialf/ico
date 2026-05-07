# func_001D4DA8 — parked

VRAM: 0x001D4DA8 (file offset 0x0D4DA8)
Asm source: asm/cod/0D4DA4.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** gp_rel pre-load ordering

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001D4DA8
    /* D4DA8 001D4DA8 0500A010 */  beqz       $a1, .L001D4DC0
    /* D4DAC 001D4DAC 28B6828F */   lw        $v0, %gp_rel(D_00633F18)($gp)
    /* D4DB0 001D4DB0 2CB6828F */  lw         $v0, %gp_rel(D_00633F1C)($gp)
    /* D4DB4 001D4DB4 21104400 */  addu       $v0, $v0, $a0
    /* D4DB8 001D4DB8 0800E003 */  jr         $ra
    /* D4DBC 001D4DBC 2CB682AF */   sw        $v0, %gp_rel(D_00633F1C)($gp)
.align 2
  .L001D4DC0:
    /* D4DC0 001D4DC0 21104400 */  addu       $v0, $v0, $a0
    /* D4DC4 001D4DC4 0800E003 */  jr         $ra
    /* D4DC8 001D4DC8 28B682AF */   sw        $v0, %gp_rel(D_00633F18)($gp)
endlabel func_001D4DA8
```
