/* Symbols accessed via $gp register */
.extern D_006317E0, 1

.align 3
nonmatching func_0023C090, 0x58

glabel func_0023C090
    /* 13C090 0023C090 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 13C094 0023C094 F08E82C7 */  lwc1       $f2, (D_006317E0) /* gp_rel: (D_006317E0) */
    /* 13C098 0023C098 0000B0FF */  sd         $16, 0x0($29)
    /* 13C09C 0023C09C 1000BFFF */  sd         $31, 0x10($29)
    /* 13C0A0 0023C0A0 2D808000 */  daddu      $16, $4, $0
    /* 13C0A4 0023C0A4 F143013C */  lui        $1, (0x43F10000 >> 16)
    /* 13C0A8 0023C0A8 00008144 */  mtc1       $1, $f0
    /* 13C0AC 0023C0AC 5F000424 */  addiu      $4, $0, 0x5F
    /* 13C0B0 0023C0B0 3400028E */  lw         $2, 0x34($16)
    /* 13C0B4 0023C0B4 003F013C */  lui        $1, (0x3F000000 >> 16)
    /* 13C0B8 0023C0B8 00088144 */  mtc1       $1, $f1
    /* 13C0BC 0023C0BC 080040E4 */  swc1       $f0, 0x8($2)
    /* 13C0C0 0023C0C0 000042E4 */  swc1       $f2, 0x0($2)
    /* 13C0C4 0023C0C4 8CEC050C */  jal        func_0017B230
    /* 13C0C8 0023C0C8 1C0001E6 */   swc1      $f1, 0x1C($16)
    /* 13C0CC 0023C0CC 01004054 */  bnel       $2, $0, .L0023C0D4
    /* 13C0D0 0023C0D0 180000AE */   sw        $0, 0x18($16)
.align 2
  .L0023C0D4:
    /* 13C0D4 0023C0D4 1000BFDF */  ld         $31, 0x10($29)
    /* 13C0D8 0023C0D8 01000224 */  addiu      $2, $0, 0x1
    /* 13C0DC 0023C0DC 0000B0DF */  ld         $16, 0x0($29)
    /* 13C0E0 0023C0E0 0800E003 */  jr         $31
    /* 13C0E4 0023C0E4 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_0023C090
