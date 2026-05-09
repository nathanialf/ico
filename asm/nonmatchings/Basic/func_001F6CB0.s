/* Symbols accessed via $gp register */
.extern D_00633780, 1
.extern D_00633784, 1
.extern D_00632014, 1
.extern D_00632024, 1

.align 3
nonmatching func_001F6CB0, 0xE0

glabel func_001F6CB0
    /* F6CB0 001F6CB0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* F6CB4 001F6CB4 90AE838F */  lw         $3, %gp_rel(D_00633780)($gp) /* gp_rel: (D_00633780) */
    /* F6CB8 001F6CB8 2000B2FF */  sd         $18, 0x20($29)
    /* F6CBC 001F6CBC FFFF0224 */  addiu      $2, $0, -0x1
    /* F6CC0 001F6CC0 1000B1FF */  sd         $17, 0x10($29)
    /* F6CC4 001F6CC4 2D900000 */  daddu      $18, $0, $0
    /* F6CC8 001F6CC8 3000BFFF */  sd         $31, 0x30($29)
    /* F6CCC 001F6CCC 2D888000 */  daddu      $17, $4, $0
    /* F6CD0 001F6CD0 0F006214 */  bne        $3, $2, .L001F6D10
    /* F6CD4 001F6CD4 0000B0FF */   sd        $16, 0x0($29)
    /* F6CD8 001F6CD8 6200043C */  lui        $4, %hi(D_0061A890)
    /* F6CDC 001F6CDC 8A9B060C */  jal        func_001A6E28
    /* F6CE0 001F6CE0 90A88424 */   addiu     $4, $4, %lo(D_0061A890)
    /* F6CE4 001F6CE4 6200103C */  lui        $16, %hi(D_0061A8A8)
    /* F6CE8 001F6CE8 74010524 */  addiu      $5, $0, 0x174
    /* F6CEC 001F6CEC A8A81026 */  addiu      $16, $16, %lo(D_0061A8A8)
    /* F6CF0 001F6CF0 DAB5060C */  jal        func_001AD768
    /* F6CF4 001F6CF4 2D200002 */   daddu     $4, $16, $0
    /* F6CF8 001F6CF8 6300063C */  lui        $6, %hi(D_00633788)
    /* F6CFC 001F6CFC 2D200002 */  daddu      $4, $16, $0
    /* F6D00 001F6D00 8837C624 */  addiu      $6, $6, %lo(D_00633788)
    /* F6D04 001F6D04 FC8F090C */  jal        func_00263FF0
    /* F6D08 001F6D08 74010524 */   addiu     $5, $0, 0x174
    /* F6D0C 001F6D0C 90AE838F */  lw         $3, %gp_rel(D_00633780)($gp) /* gp_rel: (D_00633780) */
.align 2
  .L001F6D10:
    /* F6D10 001F6D10 05006010 */  beqz       $3, .L001F6D28
    /* F6D14 001F6D14 01000224 */   addiu     $2, $0, 0x1
    /* F6D18 001F6D18 0F006210 */  beq        $3, $2, .L001F6D58
    /* F6D1C 001F6D1C 2D104002 */   daddu     $2, $18, $0
    /* F6D20 001F6D20 16000010 */  b          .L001F6D7C
    /* F6D24 001F6D24 3000BFDF */   ld        $31, 0x30($29)
.align 2
  .L001F6D28:
    /* F6D28 001F6D28 94AE828F */  lw         $2, %gp_rel(D_00633784)($gp) /* gp_rel: (D_00633784) */
    /* F6D2C 001F6D2C 6200063C */  lui        $6, %hi(D_0061A8A8)
    /* F6D30 001F6D30 2497848F */  lw         $4, %gp_rel(D_00632014)($gp) /* gp_rel: (D_00632014) */
    /* F6D34 001F6D34 2D282002 */  daddu      $5, $17, $0
    /* F6D38 001F6D38 30004224 */  addiu      $2, $2, 0x30
    /* F6D3C 001F6D3C A8A8C624 */  addiu      $6, $6, %lo(D_0061A8A8)
    /* F6D40 001F6D40 21105100 */  addu       $2, $2, $17
    /* F6D44 001F6D44 7B010724 */  addiu      $7, $0, 0x17B
    /* F6D48 001F6D48 3EE8040C */  jal        func_0013A0F8
    /* F6D4C 001F6D4C 94AE82AF */   sw        $2, %gp_rel(D_00633784)($gp) /* gp_rel: (D_00633784) */
    /* F6D50 001F6D50 08000010 */  b          .L001F6D74
    /* F6D54 001F6D54 2D904000 */   daddu     $18, $2, $0
.align 2
  .L001F6D58:
    /* F6D58 001F6D58 6200063C */  lui        $6, %hi(D_0061A8A8)
    /* F6D5C 001F6D5C 3497848F */  lw         $4, %gp_rel(D_00632024)($gp) /* gp_rel: (D_00632024) */
    /* F6D60 001F6D60 2D282002 */  daddu      $5, $17, $0
    /* F6D64 001F6D64 A8A8C624 */  addiu      $6, $6, %lo(D_0061A8A8)
    /* F6D68 001F6D68 3EE8040C */  jal        func_0013A0F8
    /* F6D6C 001F6D6C 7E010724 */   addiu     $7, $0, 0x17E
    /* F6D70 001F6D70 2D904000 */  daddu      $18, $2, $0
.align 2
  .L001F6D74:
    /* F6D74 001F6D74 2D104002 */  daddu      $2, $18, $0
    /* F6D78 001F6D78 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L001F6D7C:
    /* F6D7C 001F6D7C 2000B2DF */  ld         $18, 0x20($29)
    /* F6D80 001F6D80 1000B1DF */  ld         $17, 0x10($29)
    /* F6D84 001F6D84 0000B0DF */  ld         $16, 0x0($29)
    /* F6D88 001F6D88 0800E003 */  jr         $31
    /* F6D8C 001F6D8C 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001F6CB0
