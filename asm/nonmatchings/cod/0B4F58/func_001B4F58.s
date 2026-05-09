/* Symbols accessed via $gp register */
.extern D_00631A00, 1
.extern D_00633E9C, 1
.extern D_0063305C, 1

.align 3
nonmatching func_001B4F58, 0x64

glabel func_001B4F58
    /* B4F58 001B4F58 E0FFBD27 */  addiu      $29, $29, -0x20
    /* B4F5C 001B4F5C 1000BFFF */  sd         $31, 0x10($29)
    /* B4F60 001B4F60 11008010 */  beqz       $4, .L001B4FA8
    /* B4F64 001B4F64 0000B0FF */   sd        $16, 0x0($29)
    /* B4F68 001B4F68 2D200000 */  daddu      $4, $0, $0
    /* B4F6C 001B4F6C 0480060C */  jal        func_001A0010
    /* B4F70 001B4F70 01001024 */   addiu     $16, $0, 0x1
    /* B4F74 001B4F74 1091828F */  lw         $2, (D_00631A00) /* gp_rel: (D_00631A00) */
    /* B4F78 001B4F78 2700033C */  lui        $3, %hi(D_00274ED4)
    /* B4F7C 001B4F7C D44E70AC */  sw         $16, %lo(D_00274ED4)($3)
    /* B4F80 001B4F80 16EE040C */  jal        func_0013B858
    /* B4F84 001B4F84 ACB582AF */   sw        $2, (D_00633E9C) /* gp_rel: (D_00633E9C) */
    /* B4F88 001B4F88 2D280000 */  daddu      $5, $0, $0
    /* B4F8C 001B4F8C 50FB040C */  jal        func_0013ED40
    /* B4F90 001B4F90 2D200000 */   daddu     $4, $0, $0
    /* B4F94 001B4F94 A2EC050C */  jal        func_0017B288
    /* B4F98 001B4F98 61010424 */   addiu     $4, $0, 0x161
    /* B4F9C 001B4F9C 6CA7828F */  lw         $2, (D_0063305C) /* gp_rel: (D_0063305C) */
    /* B4FA0 001B4FA0 01004050 */  beql       $2, $0, .L001B4FA8
    /* B4FA4 001B4FA4 6CA790AF */   sw        $16, (D_0063305C) /* gp_rel: (D_0063305C) */
.align 2
  .L001B4FA8:
    /* B4FA8 001B4FA8 1000BFDF */  ld         $31, 0x10($29)
    /* B4FAC 001B4FAC FFFF0224 */  addiu      $2, $0, -0x1
    /* B4FB0 001B4FB0 0000B0DF */  ld         $16, 0x0($29)
    /* B4FB4 001B4FB4 0800E003 */  jr         $31
    /* B4FB8 001B4FB8 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001B4F58
    /* B4FBC 001B4FBC 00000000 */  nop
