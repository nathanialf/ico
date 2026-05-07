# func_001E6D68 — parked

VRAM: 0x001E6D68 (file offset 0x0E6D68)
Asm source: asm/cod/0E6968.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sd reorder

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001E6D68
    /* E6D68 001E6D68 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* E6D6C 001E6D6C 0000B0FF */  sd         $s0, 0x0($sp)
    /* E6D70 001E6D70 2D808000 */  daddu      $s0, $a0, $zero
    /* E6D74 001E6D74 1000B1FF */  sd         $s1, 0x10($sp)
    /* E6D78 001E6D78 2000BFFF */  sd         $ra, 0x20($sp)
    /* E6D7C 001E6D7C C017040C */  jal        func_00105F00
    /* E6D80 001E6D80 2D88C000 */   daddu     $s1, $a2, $zero
    /* E6D84 001E6D84 10000426 */  addiu      $a0, $s0, 0x10
    /* E6D88 001E6D88 2D282002 */  daddu      $a1, $s1, $zero
    /* E6D8C 001E6D8C 2000BFDF */  ld         $ra, 0x20($sp)
    /* E6D90 001E6D90 1000B1DF */  ld         $s1, 0x10($sp)
    /* E6D94 001E6D94 0000B0DF */  ld         $s0, 0x0($sp)
    /* E6D98 001E6D98 0C360408 */  j          func_0010D830
    /* E6D9C 001E6D9C 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_001E6D68
```
