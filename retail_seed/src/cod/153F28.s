.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — MMI texture-byte expand:
 * for each row, read a 16-byte sample window via qfsrv, expand low/high
 * bytes to 16-bit via pextlb/pextub, store to dst. Uses addi (not addiu)
 * and mtsab for the qfsrv shift control. Pattern A is required since
 * ee-gcc 2.9 doesn't emit these MMI ops. */
nonmatching func_00253F28, 0x74

glabel func_00253F28
    /* 153F28 00253F28 1400858C */  lw         $a1, 0x14($a0)
    /* 153F2C 00253F2C 1800868C */  lw         $a2, 0x18($a0)
    /* 153F30 00253F30 0800878C */  lw         $a3, 0x8($a0)
    /* 153F34 00253F34 00008E8C */  lw         $t6, 0x0($a0)
    /* 153F38 00253F38 04008D8C */  lw         $t5, 0x4($a0)
    /* 153F3C 00253F3C 10008C8C */  lw         $t4, 0x10($a0)
    /* 153F40 00253F40 40580C00 */  sll        $t3, $t4, 1
    /* 153F44 00253F44 FFFF0F24 */  addiu      $t7, $zero, -0x1
    /* 153F48 00253F48 0000B805 */  mtsab      $t5, 0x0
.align 2
  .L00253F4C:
    /* 153F4C 00253F4C 0000A878 */  lq         $t0, 0x0($a1)
    /* 153F50 00253F50 FFFFE720 */  addi       $a3, $a3, -0x1 /* handwritten instruction */
    /* 153F54 00253F54 0000C978 */  lq         $t1, 0x0($a2)
    /* 153F58 00253F58 2128AC00 */  addu       $a1, $a1, $t4
    /* 153F5C 00253F5C E8562871 */  qfsrv      $t2, $t1, $t0
    /* 153F60 00253F60 88460A70 */  pextlb     $t0, $zero, $t2
    /* 153F64 00253F64 A84E0A70 */  pextub     $t1, $zero, $t2
    /* 153F68 00253F68 0000C87D */  sq         $t0, 0x0($t6)
    /* 153F6C 00253F6C 2130CC00 */  addu       $a2, $a2, $t4
    /* 153F70 00253F70 1000C97D */  sq         $t1, 0x10($t6)
    /* 153F74 00253F74 F5FFE01C */  bgtz       $a3, .L00253F4C
    /* 153F78 00253F78 2170CB01 */   addu      $t6, $t6, $t3
    /* 153F7C 00253F7C 8000A524 */  addiu      $a1, $a1, 0x80
    /* 153F80 00253F80 8000C624 */  addiu      $a2, $a2, 0x80
    /* 153F84 00253F84 0C00878C */  lw         $a3, 0xC($a0)
    /* 153F88 00253F88 2450E701 */  and        $t2, $t7, $a3
    /* 153F8C 00253F8C EFFF4015 */  bnez       $t2, .L00253F4C
    /* 153F90 00253F90 2D780000 */   daddu     $t7, $zero, $zero
    /* 153F94 00253F94 0800E003 */  jr         $ra
    /* 153F98 00253F98 00000000 */   nop
endlabel func_00253F28
