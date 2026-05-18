.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"

/* Handwritten function — data cache flush (cache opcode 0x18 = DInvalidateAll
 * over the 0x40-aligned range covering [a0, a0+a1)). Unrolled 8x in the
 * main loop. ee-gcc 2.9 doesn't emit `cache` so Pattern A is required. */
nonmatching func_0024BEF8, 0xAC

glabel func_0024BEF8
    /* 14BEF8 0024BEF8 FFFF193C */  lui        $t9, (0xFFFFFFC0 >> 16)
    /* 14BEFC 0024BEFC C0FF3937 */  ori        $t9, $t9, (0xFFFFFFC0 & 0xFFFF)
    /* 14BF00 0024BF00 2600A018 */  blez       $a1, .L0024BF9C
    /* 14BF04 0024BF04 21508500 */   addu      $t2, $a0, $a1
    /* 14BF08 0024BF08 24409900 */  and        $t0, $a0, $t9
    /* 14BF0C 0024BF0C FFFF4A25 */  addiu      $t2, $t2, -0x1
    /* 14BF10 0024BF10 24485901 */  and        $t1, $t2, $t9
    /* 14BF14 0024BF14 23502801 */  subu       $t2, $t1, $t0
    /* 14BF18 0024BF18 82590A00 */  srl        $t3, $t2, 6
    /* 14BF1C 0024BF1C 01006B25 */  addiu      $t3, $t3, 0x1
    /* 14BF20 0024BF20 07006931 */  andi       $t1, $t3, 0x7
    /* 14BF24 0024BF24 08002011 */  beqz       $t1, .L0024BF48
    /* 14BF28 0024BF28 C2500B00 */   srl       $t2, $t3, 3
.align 2
  .L0024BF2C:
    /* 14BF2C 0024BF2C 0F000000 */  sync
    /* 14BF30 0024BF30 000018BD */  cache      0x18, 0x0($t0) /* handwritten instruction */
    /* 14BF34 0024BF34 0F000000 */  sync
    /* 14BF38 0024BF38 FFFF2925 */  addiu      $t1, $t1, -0x1
    /* 14BF3C 0024BF3C 00000000 */  nop
    /* 14BF40 0024BF40 FAFF201D */  bgtz       $t1, .L0024BF2C
    /* 14BF44 0024BF44 40000825 */   addiu     $t0, $t0, 0x40
.align 2
  .L0024BF48:
    /* 14BF48 0024BF48 14004011 */  beqz       $t2, .L0024BF9C
.align 2
  .L0024BF4C:
    /* 14BF4C 0024BF4C FFFF4A25 */   addiu     $t2, $t2, -0x1
    /* 14BF50 0024BF50 0F000000 */  sync
    /* 14BF54 0024BF54 000018BD */  cache      0x18, 0x0($t0) /* handwritten instruction */
    /* 14BF58 0024BF58 0F000000 */  sync
    /* 14BF5C 0024BF5C 400018BD */  cache      0x18, 0x40($t0) /* handwritten instruction */
    /* 14BF60 0024BF60 0F000000 */  sync
    /* 14BF64 0024BF64 800018BD */  cache      0x18, 0x80($t0) /* handwritten instruction */
    /* 14BF68 0024BF68 0F000000 */  sync
    /* 14BF6C 0024BF6C C00018BD */  cache      0x18, 0xC0($t0) /* handwritten instruction */
    /* 14BF70 0024BF70 0F000000 */  sync
    /* 14BF74 0024BF74 000118BD */  cache      0x18, 0x100($t0) /* handwritten instruction */
    /* 14BF78 0024BF78 0F000000 */  sync
    /* 14BF7C 0024BF7C 400118BD */  cache      0x18, 0x140($t0) /* handwritten instruction */
    /* 14BF80 0024BF80 0F000000 */  sync
    /* 14BF84 0024BF84 800118BD */  cache      0x18, 0x180($t0) /* handwritten instruction */
    /* 14BF88 0024BF88 0F000000 */  sync
    /* 14BF8C 0024BF8C C00118BD */  cache      0x18, 0x1C0($t0) /* handwritten instruction */
    /* 14BF90 0024BF90 0F000000 */  sync
    /* 14BF94 0024BF94 EDFF401D */  bgtz       $t2, .L0024BF4C
    /* 14BF98 0024BF98 00020825 */   addiu     $t0, $t0, 0x200
.align 2
  .L0024BF9C:
    /* 14BF9C 0024BF9C 0800E003 */  jr         $ra
    /* 14BFA0 0024BFA0 00000000 */   nop
endlabel func_0024BEF8
