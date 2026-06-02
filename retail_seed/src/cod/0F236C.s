.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — infinite call loop with split-function
 * alternate entry point (alabel) that tail-calls a different target. */
nonmatching func_001F236C, 0x4

glabel func_001F236C
    /* F236C 001F236C 00000000 */  nop
endlabel func_001F236C

nonmatching func_001F2370, 0x20

glabel func_001F2370
    /* F2370 001F2370 F0FFBD27 */  addiu      $sp, $sp, -0x10
    /* F2374 001F2374 0000BFFF */  sd         $ra, 0x0($sp)
.align 2
  .L001F2378:
    /* F2378 001F2378 A80E080C */  jal        func_00203AA0
    /* F237C 001F237C 01000424 */   addiu     $a0, $zero, 0x1
    /* F2380 001F2380 FDFF0010 */  b          .L001F2378
    /* F2384 001F2384 00000000 */   nop
.align 2
  alabel func_001F2388
    /* F2388 001F2388 AA440708 */  j          func_001D12A8
    /* F238C 001F238C 40000524 */   addiu     $a1, $zero, 0x40
endlabel func_001F2370
