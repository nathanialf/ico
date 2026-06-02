.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — privileged call wrapper + sync + ei
 * (no own sp prologue; caller is expected to allocate the 0x10 frame
 * before calling; epilogue restores). */
nonmatching func_0024BFAC, 0x20

glabel func_0024BFAC
    /* 14BFAC 0024BFAC 0000BFFF */  sd         $ra, 0x0($sp)
    /* 14BFB0 0024BFB0 5401040C */  jal        func_00100550
    /* 14BFB4 0024BFB4 2D20C000 */   daddu     $a0, $a2, $zero
    /* 14BFB8 0024BFB8 0F000000 */  sync
    /* 14BFBC 0024BFBC 38000042 */  ei /* handwritten instruction */
    /* 14BFC0 0024BFC0 0000BFDF */  ld         $ra, 0x0($sp)
    /* 14BFC4 0024BFC4 0800E003 */  jr         $ra
    /* 14BFC8 0024BFC8 1000BD27 */   addiu     $sp, $sp, 0x10
endlabel func_0024BFAC
