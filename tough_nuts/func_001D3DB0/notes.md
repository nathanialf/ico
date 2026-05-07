# func_001D3DB0 — parked

VRAM: 0x001D3DB0 (file offset 0x0D3DB0)
Asm source: asm/cod/0D3DB0.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** xori vs slt+xor compare

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001D3DB0
    /* D3DB0 001D3DB0 5C01838C */  lw         $v1, 0x15C($a0)
    /* D3DB4 001D3DB4 0008638C */  lw         $v1, 0x800($v1)
    /* D3DB8 001D3DB8 0400628C */  lw         $v0, 0x4($v1)
    /* D3DBC 001D3DBC 01004238 */  xori       $v0, $v0, 0x1
    /* D3DC0 001D3DC0 03004014 */  bnez       $v0, .L001D3DD0
    /* D3DC4 001D3DC4 00000000 */   nop
    /* D3DC8 001D3DC8 0800E003 */  jr         $ra
    /* D3DCC 001D3DCC 4000628C */   lw        $v0, 0x40($v1)
.align 2
  .L001D3DD0:
    /* D3DD0 001D3DD0 0800E003 */  jr         $ra
    /* D3DD4 001D3DD4 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_001D3DB0
```
