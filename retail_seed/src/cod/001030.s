.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — syscall(-0x2F) lookup variant */
nonmatching func_00101030, 0x98

glabel func_00101030
    /* 1030 00101030 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* 1034 00101034 1000BFFF */  sd         $ra, 0x10($sp)
    /* 1038 00101038 0000B0FF */  sd         $s0, 0x0($sp)
    /* 103C 0010103C D1FF0324 */  addiu      $v1, $zero, -0x2F
    /* 1040 00101040 0C000000 */  syscall    0 /* handwritten instruction */
    /* 1044 00101044 2D804000 */  daddu      $s0, $v0, $zero
    /* 1048 00101048 05000412 */  beq        $s0, $a0, .L00101060
    /* 104C 0010104C 0001022E */   sltiu     $v0, $s0, 0x100
    /* 1050 00101050 2801040C */  jal        func_001004A0
    /* 1054 00101054 00000000 */   nop
    /* 1058 00101058 18000010 */  b          .L001010BC
    /* 105C 0010105C 1000BFDF */   ld        $ra, 0x10($sp)
.align 2
  .L00101060:
    /* 1060 00101060 04004010 */  beqz       $v0, .L00101074
    /* 1064 00101064 2700023C */   lui       $v0, %hi(D_00274EB0)
    /* 1068 00101068 B04E438C */  lw         $v1, %lo(D_00274EB0)($v0)
    /* 106C 0010106C 03006014 */  bnez       $v1, .L0010107C
    /* 1070 00101070 6300033C */   lui       $v1, %hi(D_00634558)
.align 2
  .L00101074:
    /* 1074 00101074 10000010 */  b          .L001010B8
    /* 1078 00101078 FFFF0224 */   addiu     $v0, $zero, -0x1
.align 2
  .L0010107C:
    /* 107C 0010107C 6300053C */  lui        $a1, %hi(D_00634550)
    /* 1080 00101080 58456324 */  addiu      $v1, $v1, %lo(D_00634558)
    /* 1084 00101084 5045A48C */  lw         $a0, %lo(D_00634550)($a1)
    /* 1088 00101088 0400628C */  lw         $v0, 0x4($v1)
    /* 108C 0010108C 02000724 */  addiu      $a3, $zero, 0x2
    /* 1090 00101090 FF014230 */  andi       $v0, $v0, 0x1FF
    /* 1094 00101094 40300200 */  sll        $a2, $v0, 1
    /* 1098 00101098 01004224 */  addiu      $v0, $v0, 0x1
    /* 109C 0010109C 21286600 */  addu       $a1, $v1, $a2
    /* 10A0 001010A0 040062AC */  sw         $v0, 0x4($v1)
    /* 10A4 001010A4 0800A7A0 */  sb         $a3, 0x8($a1)
    /* 10A8 001010A8 2D18A000 */  daddu      $v1, $a1, $zero
    /* 10AC 001010AC 5401040C */  jal        func_00100550
    /* 10B0 001010B0 090070A0 */   sb        $s0, 0x9($v1)
    /* 10B4 001010B4 2D100002 */  daddu      $v0, $s0, $zero
.align 2
  .L001010B8:
    /* 10B8 001010B8 1000BFDF */  ld         $ra, 0x10($sp)
.align 2
  .L001010BC:
    /* 10BC 001010BC 0000B0DF */  ld         $s0, 0x0($sp)
    /* 10C0 001010C0 0800E003 */  jr         $ra
    /* 10C4 001010C4 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_00101030
