# func_001FC168 — parked

VRAM: 0x001FC168 (file offset 0x0FC168)
Asm source: asm/cod/0FC048.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** sd s0/s1 swap

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001FC168
    /* FC168 001FC168 D0FFBD27 */  addiu      $sp, $sp, -0x30
    /* FC16C 001FC16C 0000B0FF */  sd         $s0, 0x0($sp)
    /* FC170 001FC170 2D808000 */  daddu      $s0, $a0, $zero
    /* FC174 001FC174 1000B1FF */  sd         $s1, 0x10($sp)
    /* FC178 001FC178 2000BFFF */  sd         $ra, 0x20($sp)
    /* FC17C 001FC17C F2EF070C */  jal        func_001FBFC8
    /* FC180 001FC180 2D88A000 */   daddu     $s1, $a1, $zero
    /* FC184 001FC184 2D200002 */  daddu      $a0, $s0, $zero
    /* FC188 001FC188 2D282002 */  daddu      $a1, $s1, $zero
    /* FC18C 001FC18C 2000BFDF */  ld         $ra, 0x20($sp)
    /* FC190 001FC190 1000B1DF */  ld         $s1, 0x10($sp)
    /* FC194 001FC194 0000B0DF */  ld         $s0, 0x0($sp)
    /* FC198 001FC198 12F00708 */  j          func_001FC048
    /* FC19C 001FC19C 3000BD27 */   addiu     $sp, $sp, 0x30
endlabel func_001FC168
```
