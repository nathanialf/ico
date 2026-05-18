.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — startup/exit syscall pair (0x23 then 0x0)
 * with 14 nops between, presumably to give the kernel a fixed PC range
 * to land on for return-from-syscall in either direction. */
.align 3
nonmatching func_001000C0, 0x50

glabel func_001000C0
    /* C0 001000C0 23000324 */  addiu      $v1, $zero, 0x23
    /* C4 001000C4 0C000000 */  syscall    0 /* handwritten instruction */
    /* C8 001000C8 00000000 */  nop
    /* CC 001000CC 00000000 */  nop
    /* D0 001000D0 00000000 */  nop
    /* D4 001000D4 00000000 */  nop
    /* D8 001000D8 00000000 */  nop
    /* DC 001000DC 00000000 */  nop
    /* E0 001000E0 00000000 */  nop
    /* E4 001000E4 00000000 */  nop
    /* E8 001000E8 00000000 */  nop
    /* EC 001000EC 00000000 */  nop
    /* F0 001000F0 00000000 */  nop
    /* F4 001000F4 00000000 */  nop
    /* F8 001000F8 00000000 */  nop
    /* FC 001000FC 00000000 */  nop
    /* 100 00100100 00000324 */  addiu      $v1, $zero, 0x0
    /* 104 00100104 0C000000 */  syscall    0 /* handwritten instruction */
    /* 108 00100108 0800E003 */  jr         $ra
    /* 10C 0010010C 00000000 */   nop
endlabel func_001000C0
