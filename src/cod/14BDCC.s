.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

nonmatching func_0024BDCC, 0x4

glabel func_0024BDCC
    /* 14BDCC 0024BDCC 00000000 */  nop
endlabel func_0024BDCC

/* Handwritten function */
nonmatching func_0024BDD0, 0x128

glabel func_0024BDD0
    /* 14BDD0 0024BDD0 70FFBD27 */  addiu      $sp, $sp, -0x90
    /* 14BDD4 0024BDD4 7000B0FF */  sd         $s0, 0x70($sp)
    /* 14BDD8 0024BDD8 8000BFFF */  sd         $ra, 0x80($sp)
    /* 14BDDC 0024BDDC A206040C */  jal        func_00101A88
    /* 14BDE0 0024BDE0 00000000 */   nop
    /* 14BDE4 0024BDE4 7100033C */  lui        $v1, %hi(D_00717758)
    /* 14BDE8 0024BDE8 5877678C */  lw         $a3, %lo(D_00717758)($v1)
    /* 14BDEC 0024BDEC 58777024 */  addiu      $s0, $v1, %lo(D_00717758)
    /* 14BDF0 0024BDF0 0000E290 */  lbu        $v0, 0x0($a3)
    /* 14BDF4 0024BDF4 FF004530 */  andi       $a1, $v0, 0xFF
    /* 14BDF8 0024BDF8 3B00A010 */  beqz       $a1, .L0024BEE8
    /* 14BDFC 0024BDFC 2D100000 */   daddu     $v0, $zero, $zero
    /* 14BE00 0024BE00 0F00A224 */  addiu      $v0, $a1, 0xF
    /* 14BE04 0024BE04 FFFF0324 */  addiu      $v1, $zero, -0x1
    /* 14BE08 0024BE08 1E00A424 */  addiu      $a0, $a1, 0x1E
    /* 14BE0C 0024BE0C 2A186200 */  slt        $v1, $v1, $v0
    /* 14BE10 0024BE10 0B204300 */  movn       $a0, $v0, $v1
    /* 14BE14 0024BE14 2D30E000 */  daddu      $a2, $a3, $zero
    /* 14BE18 0024BE18 03290400 */  sra        $a1, $a0, 4
    /* 14BE1C 0024BE1C 0000E0A0 */  sb         $zero, 0x0($a3)
    /* 14BE20 0024BE20 0A00A018 */  blez       $a1, .L0024BE4C
    /* 14BE24 0024BE24 2D20A000 */   daddu     $a0, $a1, $zero
    /* 14BE28 0024BE28 2D18A003 */  daddu      $v1, $sp, $zero
    /* 14BE2C 0024BE2C 00000000 */  nop
.align 2
  .L0024BE30:
    /* 14BE30 0024BE30 0000C278 */  lq         $v0, 0x0($a2)
    /* 14BE34 0024BE34 FFFF8424 */  addiu      $a0, $a0, -0x1
    /* 14BE38 0024BE38 1000C624 */  addiu      $a2, $a2, 0x10
    /* 14BE3C 0024BE3C 0000627C */  sq         $v0, 0x0($v1)
    /* 14BE40 0024BE40 10006324 */  addiu      $v1, $v1, 0x10
    /* 14BE44 0024BE44 FAFF8014 */  bnez       $a0, .L0024BE30
    /* 14BE48 0024BE48 00000000 */   nop
.align 2
  .L0024BE4C:
    /* 14BE4C 0024BE4C 4402040C */  jal        func_00100910
    /* 14BE50 0024BE50 00000000 */   nop
    /* 14BE54 0024BE54 0800A38F */  lw         $v1, 0x8($sp)
    /* 14BE58 0024BE58 13006104 */  bgez       $v1, .L0024BEA8
    /* 14BE5C 0024BE5C 00000000 */   nop
    /* 14BE60 0024BE60 0800A28F */  lw         $v0, 0x8($sp)
    /* 14BE64 0024BE64 FF7F033C */  lui        $v1, (0x7FFFFFFF >> 16)
    /* 14BE68 0024BE68 FFFF6334 */  ori        $v1, $v1, (0x7FFFFFFF & 0xFFFF)
    /* 14BE6C 0024BE6C 1000048E */  lw         $a0, 0x10($s0)
    /* 14BE70 0024BE70 24284300 */  and        $a1, $v0, $v1
    /* 14BE74 0024BE74 2A20A400 */  slt        $a0, $a1, $a0
    /* 14BE78 0024BE78 18008010 */  beqz       $a0, .L0024BEDC
    /* 14BE7C 0024BE7C C0100500 */   sll       $v0, $a1, 3
    /* 14BE80 0024BE80 0C00038E */  lw         $v1, 0xC($s0)
    /* 14BE84 0024BE84 21104300 */  addu       $v0, $v0, $v1
    /* 14BE88 0024BE88 0000468C */  lw         $a2, 0x0($v0)
    /* 14BE8C 0024BE8C 1300C010 */  beqz       $a2, .L0024BEDC
    /* 14BE90 0024BE90 00000000 */   nop
    /* 14BE94 0024BE94 0400458C */  lw         $a1, 0x4($v0)
    /* 14BE98 0024BE98 09F8C000 */  jalr       $a2
    /* 14BE9C 0024BE9C 2D20A003 */   daddu     $a0, $sp, $zero
    /* 14BEA0 0024BEA0 0E000010 */  b          .L0024BEDC
    /* 14BEA4 0024BEA4 00000000 */   nop
.align 2
  .L0024BEA8:
    /* 14BEA8 0024BEA8 0800A58F */  lw         $a1, 0x8($sp)
    /* 14BEAC 0024BEAC 1800028E */  lw         $v0, 0x18($s0)
    /* 14BEB0 0024BEB0 2A10A200 */  slt        $v0, $a1, $v0
    /* 14BEB4 0024BEB4 09004010 */  beqz       $v0, .L0024BEDC
    /* 14BEB8 0024BEB8 C0100500 */   sll       $v0, $a1, 3
    /* 14BEBC 0024BEBC 1400038E */  lw         $v1, 0x14($s0)
    /* 14BEC0 0024BEC0 21104300 */  addu       $v0, $v0, $v1
    /* 14BEC4 0024BEC4 0000468C */  lw         $a2, 0x0($v0)
    /* 14BEC8 0024BEC8 0400C010 */  beqz       $a2, .L0024BEDC
    /* 14BECC 0024BECC 00000000 */   nop
    /* 14BED0 0024BED0 0400458C */  lw         $a1, 0x4($v0)
    /* 14BED4 0024BED4 09F8C000 */  jalr       $a2
    /* 14BED8 0024BED8 2D20A003 */   daddu     $a0, $sp, $zero
.align 2
  .L0024BEDC:
    /* 14BEDC 0024BEDC 0F000000 */  sync
    /* 14BEE0 0024BEE0 38000042 */  ei /* handwritten instruction */
    /* 14BEE4 0024BEE4 2D100000 */  daddu      $v0, $zero, $zero
.align 2
  .L0024BEE8:
    /* 14BEE8 0024BEE8 8000BFDF */  ld         $ra, 0x80($sp)
    /* 14BEEC 0024BEEC 7000B0DF */  ld         $s0, 0x70($sp)
    /* 14BEF0 0024BEF0 0800E003 */  jr         $ra
    /* 14BEF4 0024BEF4 9000BD27 */   addiu     $sp, $sp, 0x90
endlabel func_0024BDD0
