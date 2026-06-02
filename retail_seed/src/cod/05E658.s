.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten — infinite loop with dead "alternate body" emitted in the
 * same range. The b at +0x18 loops back forever; the code after it is
 * never reached from this function's entry. Pattern A (hasm) because the
 * dead-body shape with two prologues isn't expressible in C without
 * naked attribute (ee-gcc 2.9 lacks it). */
.align 3
nonmatching func_0015E658, 0x54

glabel func_0015E658
    /* 5E658 0015E658 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 5E65C 0015E65C 1000BFFF */  sd         $ra, 0x10($sp)
    /* 5E660 0015E660 0000A4AF */  sw         $a0, 0x0($sp)
    /* 5E664 0015E664 00000000 */  nop
.align 2
  .L0015E668:
    /* 5E668 0015E668 A80E080C */  jal        func_00203AA0
    /* 5E66C 0015E66C 01000424 */   addiu     $a0, $zero, 0x1
    /* 5E670 0015E670 FDFF0010 */  b          .L0015E668
    /* 5E674 0015E674 00000000 */   nop
    /* 5E678 0015E678 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 5E67C 0015E67C 1600023C */  lui        $v0, %hi(func_0015F698)
    /* 5E680 0015E680 0000A4AF */  sw         $a0, 0x0($sp)
    /* 5E684 0015E684 98F64224 */  addiu      $v0, $v0, %lo(func_0015F698)
    /* 5E688 0015E688 1000BFFF */  sd         $ra, 0x10($sp)
    /* 5E68C 0015E68C 2D200000 */  daddu      $a0, $zero, $zero
    /* 5E690 0015E690 0000A38F */  lw         $v1, 0x0($sp)
    /* 5E694 0015E694 6401658C */  lw         $a1, 0x164($v1)
    /* 5E698 0015E698 A80E080C */  jal        func_00203AA0
    /* 5E69C 0015E69C 1400A2AC */   sw        $v0, 0x14($a1)
    /* 5E6A0 0015E6A0 1000BFDF */  ld         $ra, 0x10($sp)
    /* 5E6A4 0015E6A4 0800E003 */  jr         $ra
    /* 5E6A8 0015E6A8 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_0015E658
