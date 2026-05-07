# func_002608E0 — parked

VRAM: 0x002608E0 (file offset 0x1608E0)
Asm source: asm/cod/160634.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** fabsf bit-twiddle pattern

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_002608E0
    /* 1608E0 002608E0 00600344 */  mfc1       $v1, $f12
    /* 1608E4 002608E4 FF7F023C */  lui        $v0, (0x7FFFFFFF >> 16)
    /* 1608E8 002608E8 FFFF4234 */  ori        $v0, $v0, (0x7FFFFFFF & 0xFFFF)
    /* 1608EC 002608EC 24186200 */  and        $v1, $v1, $v0
    /* 1608F0 002608F0 00008344 */  mtc1       $v1, $f0
    /* 1608F4 002608F4 0800E003 */  jr         $ra
    /* 1608F8 002608F8 00000000 */   nop
endlabel func_002608E0
```
