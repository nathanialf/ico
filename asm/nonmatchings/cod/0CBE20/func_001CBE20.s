/* Symbols accessed via $gp register */
.extern D_0063330C, 1
.extern D_00633310, 1
.extern D_00633314, 1
.extern D_00633318, 1
.extern D_0063331C, 1

.align 3
nonmatching func_001CBE20, 0x58

glabel func_001CBE20
    /* CBE20 001CBE20 D0FFBD27 */  addiu      $29, $29, -0x30
    /* CBE24 001CBE24 2D288000 */  daddu      $5, $4, $0
    /* CBE28 001CBE28 0000B0FF */  sd         $16, 0x0($29)
    /* CBE2C 001CBE2C 4C00043C */  lui        $4, %hi(D_004C09A0)
    /* CBE30 001CBE30 01001024 */  addiu      $16, $0, 0x1
    /* CBE34 001CBE34 2000B4E7 */  swc1       $f20, 0x20($29)
    /* CBE38 001CBE38 06650046 */  mov.s      $f20, $f12
    /* CBE3C 001CBE3C 1CAA90AF */  sw         $16, (D_0063330C) /* gp_rel: (D_0063330C) */
    /* CBE40 001CBE40 24AA90AF */  sw         $16, (D_00633314) /* gp_rel: (D_00633314) */
    /* CBE44 001CBE44 A0098424 */  addiu      $4, $4, %lo(D_004C09A0)
    /* CBE48 001CBE48 1000BFFF */  sd         $31, 0x10($29)
    /* CBE4C 001CBE4C 20AA80AF */  sw         $0, (D_00633310) /* gp_rel: (D_00633310) */
    /* CBE50 001CBE50 C017040C */  jal        func_00105F00
    /* CBE54 001CBE54 28AA80AF */   sw        $0, (D_00633318) /* gp_rel: (D_00633318) */
    /* CBE58 001CBE58 2CAA94E7 */  swc1       $f20, (D_0063331C) /* gp_rel: (D_0063331C) */
    /* CBE5C 001CBE5C 28AA90AF */  sw         $16, (D_00633318) /* gp_rel: (D_00633318) */
    /* CBE60 001CBE60 1000BFDF */  ld         $31, 0x10($29)
    /* CBE64 001CBE64 0000B0DF */  ld         $16, 0x0($29)
    /* CBE68 001CBE68 2000B4C7 */  lwc1       $f20, 0x20($29)
    /* CBE6C 001CBE6C 24AA80AF */  sw         $0, (D_00633314) /* gp_rel: (D_00633314) */
    /* CBE70 001CBE70 0800E003 */  jr         $31
    /* CBE74 001CBE74 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001CBE20
