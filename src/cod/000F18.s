.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — syscall(-0x2F) lookup then dispatch */
nonmatching func_00100F18, 0x94

glabel func_00100F18
    /* F18 00100F18 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* F1C 00100F1C 1000BFFF */  sd         $ra, 0x10($sp)
    /* F20 00100F20 0000B0FF */  sd         $s0, 0x0($sp)
    /* F24 00100F24 D1FF0324 */  addiu      $v1, $zero, -0x2F
    /* F28 00100F28 0C000000 */  syscall    0 /* handwritten instruction */
    /* F2C 00100F2C 2D804000 */  daddu      $s0, $v0, $zero
    /* F30 00100F30 05000412 */  beq        $s0, $a0, .L00100F48
    /* F34 00100F34 0001022E */   sltiu     $v0, $s0, 0x100
    /* F38 00100F38 1801040C */  jal        func_00100460
    /* F3C 00100F3C 00000000 */   nop
    /* F40 00100F40 17000010 */  b          .L00100FA0
    /* F44 00100F44 1000BFDF */   ld        $ra, 0x10($sp)
.align 2
  .L00100F48:
    /* F48 00100F48 04004010 */  beqz       $v0, .L00100F5C
    /* F4C 00100F4C 2700023C */   lui       $v0, %hi(D_00274EB0)
    /* F50 00100F50 B04E438C */  lw         $v1, %lo(D_00274EB0)($v0)
    /* F54 00100F54 03006014 */  bnez       $v1, .L00100F64
    /* F58 00100F58 6300033C */   lui       $v1, %hi(D_00634558)
.align 2
  .L00100F5C:
    /* F5C 00100F5C 0F000010 */  b          .L00100F9C
    /* F60 00100F60 FFFF0224 */   addiu     $v0, $zero, -0x1
.align 2
  .L00100F64:
    /* F64 00100F64 6300053C */  lui        $a1, %hi(D_00634550)
    /* F68 00100F68 58456324 */  addiu      $v1, $v1, %lo(D_00634558)
    /* F6C 00100F6C 5045A48C */  lw         $a0, %lo(D_00634550)($a1)
    /* F70 00100F70 0400628C */  lw         $v0, 0x4($v1)
    /* F74 00100F74 FF014230 */  andi       $v0, $v0, 0x1FF
    /* F78 00100F78 40300200 */  sll        $a2, $v0, 1
    /* F7C 00100F7C 01004224 */  addiu      $v0, $v0, 0x1
    /* F80 00100F80 21286600 */  addu       $a1, $v1, $a2
    /* F84 00100F84 040062AC */  sw         $v0, 0x4($v1)
    /* F88 00100F88 2D18A000 */  daddu      $v1, $a1, $zero
    /* F8C 00100F8C 0800A0A0 */  sb         $zero, 0x8($a1)
    /* F90 00100F90 5401040C */  jal        func_00100550
    /* F94 00100F94 090070A0 */   sb        $s0, 0x9($v1)
    /* F98 00100F98 2D100002 */  daddu      $v0, $s0, $zero
.align 2
  .L00100F9C:
    /* F9C 00100F9C 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L00100FA0:
    /* FA0 00100FA0 0000B0DF */  ld         $s0, 0x0($sp)
    /* FA4 00100FA4 0800E003 */  jr         $ra
    /* FA8 00100FA8 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00100F18
