/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001E8EB8, 0x6C

glabel func_001E8EB8
    /* E8EB8 001E8EB8 C0FFBD27 */  addiu      $29, $29, -0x40
    /* E8EBC 001E8EBC 6200063C */  lui        $6, %hi(D_00619EC0)
    /* E8EC0 001E8EC0 2000B2FF */  sd         $18, 0x20($29)
    /* E8EC4 001E8EC4 C09EC624 */  addiu      $6, $6, %lo(D_00619EC0)
    /* E8EC8 001E8EC8 2D908000 */  daddu      $18, $4, $0
    /* E8ECC 001E8ECC 1000B1FF */  sd         $17, 0x10($29)
    /* E8ED0 001E8ED0 2D88A000 */  daddu      $17, $5, $0
    /* E8ED4 001E8ED4 2097848F */  lw         $4, (D_00632010) /* gp_rel: (D_00632010) */
    /* E8ED8 001E8ED8 0000B0FF */  sd         $16, 0x0($29)
    /* E8EDC 001E8EDC 04000524 */  addiu      $5, $0, 0x4
    /* E8EE0 001E8EE0 3000BFFF */  sd         $31, 0x30($29)
    /* E8EE4 001E8EE4 3EE8040C */  jal        func_0013A0F8
    /* E8EE8 001E8EE8 0C000724 */   addiu     $7, $0, 0xC
    /* E8EEC 001E8EEC 5C01468E */  lw         $6, 0x15C($18)
    /* E8EF0 001E8EF0 2D804000 */  daddu      $16, $2, $0
    /* E8EF4 001E8EF4 3000248E */  lw         $4, 0x30($17)
    /* E8EF8 001E8EF8 2D282002 */  daddu      $5, $17, $0
    /* E8EFC 001E8EFC D2A2070C */  jal        func_001E8B48
    /* E8F00 001E8F00 6000C624 */   addiu     $6, $6, 0x60
    /* E8F04 001E8F04 000002AE */  sw         $2, 0x0($16)
    /* E8F08 001E8F08 2D100002 */  daddu      $2, $16, $0
    /* E8F0C 001E8F0C 3000BFDF */  ld         $31, 0x30($29)
    /* E8F10 001E8F10 2000B2DF */  ld         $18, 0x20($29)
    /* E8F14 001E8F14 1000B1DF */  ld         $17, 0x10($29)
    /* E8F18 001E8F18 0000B0DF */  ld         $16, 0x0($29)
    /* E8F1C 001E8F1C 0800E003 */  jr         $31
    /* E8F20 001E8F20 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001E8EB8
    /* E8F24 001E8F24 00000000 */  nop
