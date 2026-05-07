# func_001F6E00 — parked

VRAM: 0x001F6E00 (file offset 0x0F6E00)
Asm source: asm/cod/0F6DB8.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sd-addiu order

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001F6E00
    /* F6E00 001F6E00 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* F6E04 001F6E04 6200063C */  lui        $a2, %hi(D_0061A8A8)
    /* F6E08 001F6E08 0000BFFF */  sd         $ra, 0x0($sp)
    /* F6E0C 001F6E0C A8A8C624 */  addiu      $a2, $a2, %lo(D_0061A8A8)
    /* F6E10 001F6E10 5EE7040C */  jal        func_00139D78
    /* F6E14 001F6E14 A8010724 */   addiu     $a3, $zero, 0x1A8
    /* F6E18 001F6E18 0000BFDF */  ld         $ra, 0x0($sp)
    /* F6E1C 001F6E1C 0800E003 */  jr         $ra
    /* F6E20 001F6E20 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_001F6E00
```
