/* Symbols accessed via $gp register */
.extern D_00631AE8, 1
.extern D_0063330C, 1
.extern D_00633310, 1
.extern D_00633314, 1
.extern D_00633318, 1
.extern D_0063331C, 1

.align 3
nonmatching func_001CBD88, 0x98

glabel func_001CBD88
    /* CBD88 001CBD88 D0FFBD27 */  addiu      $29, $29, -0x30
    /* CBD8C 001CBD8C F891828F */  lw         $2, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* CBD90 001CBD90 0000B0FF */  sd         $16, 0x0($29)
    /* CBD94 001CBD94 2000B4E7 */  swc1       $f20, 0x20($29)
    /* CBD98 001CBD98 2D808000 */  daddu      $16, $4, $0
    /* CBD9C 001CBD9C 1000BFFF */  sd         $31, 0x10($29)
    /* CBDA0 001CBDA0 10004010 */  beqz       $2, .L001CBDE4
    /* CBDA4 001CBDA4 06650046 */   mov.s     $f20, $f12
    /* CBDA8 001CBDA8 2D204000 */  daddu      $4, $2, $0
    /* CBDAC 001CBDAC AA44070C */  jal        func_001D12A8
    /* CBDB0 001CBDB0 75000524 */   addiu     $5, $0, 0x75
    /* CBDB4 001CBDB4 F891848F */  lw         $4, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* CBDB8 001CBDB8 AA44070C */  jal        func_001D12A8
    /* CBDBC 001CBDBC 76000524 */   addiu     $5, $0, 0x76
    /* CBDC0 001CBDC0 F891848F */  lw         $4, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* CBDC4 001CBDC4 AA44070C */  jal        func_001D12A8
    /* CBDC8 001CBDC8 77000524 */   addiu     $5, $0, 0x77
    /* CBDCC 001CBDCC F891848F */  lw         $4, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* CBDD0 001CBDD0 AA44070C */  jal        func_001D12A8
    /* CBDD4 001CBDD4 78000524 */   addiu     $5, $0, 0x78
    /* CBDD8 001CBDD8 F891848F */  lw         $4, (D_00631AE8) /* gp_rel: (D_00631AE8) */
    /* CBDDC 001CBDDC AA44070C */  jal        func_001D12A8
    /* CBDE0 001CBDE0 79000524 */   addiu     $5, $0, 0x79
.align 2
  .L001CBDE4:
    /* CBDE4 001CBDE4 01000224 */  addiu      $2, $0, 0x1
    /* CBDE8 001CBDE8 4C00043C */  lui        $4, %hi(D_004C09A0)
    /* CBDEC 001CBDEC 2D280002 */  daddu      $5, $16, $0
    /* CBDF0 001CBDF0 24AA82AF */  sw         $2, (D_00633314) /* gp_rel: (D_00633314) */
    /* CBDF4 001CBDF4 A0098424 */  addiu      $4, $4, %lo(D_004C09A0)
    /* CBDF8 001CBDF8 1CAA82AF */  sw         $2, (D_0063330C) /* gp_rel: (D_0063330C) */
    /* CBDFC 001CBDFC 20AA80AF */  sw         $0, (D_00633310) /* gp_rel: (D_00633310) */
    /* CBE00 001CBE00 C017040C */  jal        func_00105F00
    /* CBE04 001CBE04 28AA80AF */   sw        $0, (D_00633318) /* gp_rel: (D_00633318) */
    /* CBE08 001CBE08 2CAA94E7 */  swc1       $f20, (D_0063331C) /* gp_rel: (D_0063331C) */
    /* CBE0C 001CBE0C 1000BFDF */  ld         $31, 0x10($29)
    /* CBE10 001CBE10 0000B0DF */  ld         $16, 0x0($29)
    /* CBE14 001CBE14 2000B4C7 */  lwc1       $f20, 0x20($29)
    /* CBE18 001CBE18 0800E003 */  jr         $31
    /* CBE1C 001CBE1C 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001CBD88
