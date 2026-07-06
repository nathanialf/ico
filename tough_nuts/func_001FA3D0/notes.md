[NOTE: earlier driver lever-log truncated to satisfy the 256KiB check_no_rom size gate.
 Full 478KB raw log backed up out-of-repo; CURATED findings are in the auto-memory
 project_func_001FA3D0_resume.md. Below = most-recent lever history.]

  .L001FC824:
    /* FC824 001FC824 3C004228 */  slti       $2, $2, 0x3C
    /* FC828 001FC828 04004010 */  beqz       $2, .L001FC83C
    /* FC82C 001FC82C 0200033C */   lui       $3, (0x20000 >> 16)
    /* FC830 001FC830 0800828E */  lw         $2, 0x8($20)
    /* FC834 001FC834 25104300 */  or         $2, $2, $3
    /* FC838 001FC838 080082AE */  sw         $2, 0x8($20)
.align 2
  .L001FC83C:
    /* FC83C 001FC83C 3000A28F */  lw         $2, 0x30($29)
    /* FC840 001FC840 C000B226 */  addiu      $18, $21, 0xC0
    /* FC844 001FC844 03001124 */  addiu      $17, $0, 0x3
    /* FC848 001FC848 5C01438C */  lw         $3, 0x15C($2)
    /* FC84C 001FC84C 6000A0AF */  sw         $0, 0x60($29)
    /* FC850 001FC850 8801628C */  lw         $2, 0x188($3)
    /* FC854 001FC854 6400A0AF */  sw         $0, 0x64($29)
    /* FC858 001FC858 6800A0AF */  sw         $0, 0x68($29)
    /* FC85C 001FC85C 2D804000 */  daddu      $16, $2, $0
    /* FC860 001FC860 6000A427 */  addiu      $4, $29, 0x60
    /* FC864 001FC864 00000000 */  nop
.align 2
  .L001FC868:
    /* FC868 001FC868 2D300002 */  daddu      $6, $16, $0
    /* FC86C 001FC86C 2D288000 */  daddu      $5, $4, $0
    /* FC870 001FC870 FCFF080C */  jal        func_0023FFF0
    /* FC874 001FC874 10001026 */   addiu     $16, $16, 0x10
    /* FC878 001FC878 FFFF3126 */  addiu      $17, $17, -0x1
    /* FC87C 001FC87C FAFF2106 */  bgez       $17, .L001FC868
    /* FC880 001FC880 6000A427 */   addiu     $4, $29, 0x60
    /* FC884 001FC884 803E013C */  lui        $1, (0x3E800000 >> 16)
    /* FC888 001FC888 00608144 */  mtc1       $1, $f12
    /* FC88C 001FC88C 2D204002 */  daddu      $4, $18, $0
    /* FC890 001FC890 0E00090C */  jal        func_00240038
    /* FC894 001FC894 6000A527 */   addiu     $5, $29, 0x60
    /* FC898 001FC898 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FC89C 001FC89C 00008144 */  mtc1       $1, $f0
    /* FC8A0 001FC8A0 CC00A0E6 */  swc1       $f0, 0xCC($21)
    /* FC8A4 001FC8A4 3000A48F */  lw         $4, 0x30($29)
.align 2
  .L001FC8A8:
    /* FC8A8 001FC8A8 2228040C */  jal        DisableMotionOrientUpdate
    /* FC8AC 001FC8AC 00C00534 */   ori       $5, $0, 0xC000
    /* FC8B0 001FC8B0 04004010 */  beqz       $2, .L001FC8C4
    /* FC8B4 001FC8B4 00000000 */   nop
    /* FC8B8 001FC8B8 0800828E */  lw         $2, 0x8($20)
    /* FC8BC 001FC8BC 00084234 */  ori        $2, $2, 0x800
    /* FC8C0 001FC8C0 080082AE */  sw         $2, 0x8($20)
.align 2
  .L001FC8C4:
    /* FC8C4 001FC8C4 C841013C */  lui        $1, (0x41C80000 >> 16)
    /* FC8C8 001FC8C8 00008144 */  mtc1       $1, $f0
    /* FC8CC 001FC8CC 34A80046 */  c.lt.s     $f21, $f0
    /* FC8D0 001FC8D0 00000000 */  nop
    /* FC8D4 001FC8D4 1C000045 */  bc1f       .L001FC948
    /* FC8D8 001FC8D8 BC01A98F */   lw        $9, 0x1BC($29)
    /* FC8DC 001FC8DC 1B002011 */  beqz       $9, .L001FC94C
    /* FC8E0 001FC8E0 3000A38F */   lw        $3, 0x30($29)
    /* FC8E4 001FC8E4 5C42013C */  lui        $1, (0x425C0000 >> 16)
    /* FC8E8 001FC8E8 00008144 */  mtc1       $1, $f0
    /* FC8EC 001FC8EC 34C00046 */  c.lt.s     $f24, $f0
    /* FC8F0 001FC8F0 00000000 */  nop
    /* FC8F4 001FC8F4 03000045 */  bc1f       .L001FC904
    /* FC8F8 001FC8F8 0200033C */   lui       $3, (0x20000 >> 16)
    /* FC8FC 001FC8FC 10000010 */  b          .L001FC940
    /* FC900 001FC900 700462DE */   ld        $2, 0x470($19)
.align 2
  .L001FC904:
    /* FC904 001FC904 D242013C */  lui        $1, (0x42D20000 >> 16)
    /* FC908 001FC908 00008144 */  mtc1       $1, $f0
    /* FC90C 001FC90C 34C00046 */  c.lt.s     $f24, $f0
    /* FC910 001FC910 00000000 */  nop
    /* FC914 001FC914 03000045 */  bc1f       .L001FC924
    /* FC918 001FC918 0400033C */   lui       $3, (0x40000 >> 16)
    /* FC91C 001FC91C 08000010 */  b          .L001FC940
    /* FC920 001FC920 700462DE */   ld        $2, 0x470($19)
.align 2
  .L001FC924:
    /* FC924 001FC924 4D43013C */  lui        $1, (0x434D0000 >> 16)
    /* FC928 001FC928 00008144 */  mtc1       $1, $f0
    /* FC92C 001FC92C 34C00046 */  c.lt.s     $f24, $f0
    /* FC930 001FC930 00000000 */  nop
    /* FC934 001FC934 04000045 */  bc1f       .L001FC948
    /* FC938 001FC938 0800033C */   lui       $3, (0x80000 >> 16)
    /* FC93C 001FC93C 700462DE */  ld         $2, 0x470($19)
.align 2
  .L001FC940:
    /* FC940 001FC940 25104300 */  or         $2, $2, $3
    /* FC944 001FC944 700462FE */  sd         $2, 0x470($19)
.align 2
  .L001FC948:
    /* FC948 001FC948 3000A38F */  lw         $3, 0x30($29)
.align 2
  .L001FC94C:
    /* FC94C 001FC94C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* FC950 001FC950 C2016214 */  bne        $3, $2, .L001FD05C
    /* FC954 001FC954 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FC958 001FC958 E902A050 */  beql       $5, $0, .L001FD500
    /* FC95C 001FC95C 0800828E */   lw        $2, 0x8($20)
    /* FC960 001FC960 6401A28C */  lw         $2, 0x164($5)
    /* FC964 001FC964 26000424 */  addiu      $4, $0, 0x26
    /* FC968 001FC968 3000438C */  lw         $3, 0x30($2)
    /* FC96C 001FC96C BB016410 */  beq        $3, $4, .L001FD05C
    /* FC970 001FC970 00000000 */   nop
    /* FC974 001FC974 4843013C */  lui        $1, (0x43480000 >> 16)
    /* FC978 001FC978 00008144 */  mtc1       $1, $f0
    /* FC97C 001FC97C 34A80046 */  c.lt.s     $f21, $f0
    /* FC980 001FC980 B6010045 */  bc1f       .L001FD05C
    /* FC984 001FC984 00000000 */   nop
    /* FC988 001FC988 A222050C */  jal        ACTEnvGetTest
    /* FC98C 001FC98C 00000000 */   nop
    /* FC990 001FC990 B2014014 */  bnez       $2, .L001FD05C
    /* FC994 001FC994 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FC998 001FC998 3000A48F */  lw         $4, 0x30($29)
    /* FC99C 001FC99C 2228040C */  jal        DisableMotionOrientUpdate
    /* FC9A0 001FC9A0 00700524 */   addiu     $5, $0, 0x7000
    /* FC9A4 001FC9A4 AD014014 */  bnez       $2, .L001FD05C
    /* FC9A8 001FC9A8 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FC9AC 001FC9AC 3000A48F */  lw         $4, 0x30($29)
    /* FC9B0 001FC9B0 2228040C */  jal        DisableMotionOrientUpdate
    /* FC9B4 001FC9B4 00040524 */   addiu     $5, $0, 0x400
    /* FC9B8 001FC9B8 A8014014 */  bnez       $2, .L001FD05C
    /* FC9BC 001FC9BC F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FC9C0 001FC9C0 01000224 */  addiu      $2, $0, 0x1
    /* FC9C4 001FC9C4 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FC9C8 001FC9C8 6629040C */  jal        EnableChangeRootUpdateMode
    /* FC9CC 001FC9CC CC01A2AF */   sw        $2, 0x1CC($29)
    /* FC9D0 001FC9D0 C7050046 */  neg.s      $f23, $f0
    /* FC9D4 001FC9D4 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FC9D8 001FC9D8 00008144 */  mtc1       $1, $f0
    /* FC9DC 001FC9DC 34A80046 */  c.lt.s     $f21, $f0
    /* FC9E0 001FC9E0 00000000 */  nop
    /* FC9E4 001FC9E4 01000245 */  bc1fl      .L001FC9EC
    /* FC9E8 001FC9E8 CC01A0AF */   sw        $0, 0x1CC($29)
.align 2
  .L001FC9EC:
    /* FC9EC 001FC9EC 6000A327 */  addiu      $3, $29, 0x60
    /* FC9F0 001FC9F0 6300063C */  lui        $6, %hi(D_0062D9D8)
    /* FC9F4 001FC9F4 F491858F */  lw         $5, %gp_rel(D_00629DE4)($28)
    /* FC9F8 001FC9F8 2D206000 */  daddu      $4, $3, $0
    /* FC9FC 001FC9FC D401A3AF */  sw         $3, 0x1D4($29)
    /* FCA00 001FCA00 2DB80000 */  daddu      $23, $0, $0
    /* FCA04 001FCA04 C210040C */  jal        GetRootMatrixByDObj
    /* FCA08 001FCA08 D8D9D6C4 */   lwc1      $f22, %lo(D_0062D9D8)($6)
    /* FCA0C 001FCA0C 01000724 */  addiu      $7, $0, 0x1
    /* FCA10 001FCA10 7000B227 */  addiu      $18, $29, 0x70
    /* FCA14 001FCA14 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FCA18 001FCA18 2D204002 */  daddu      $4, $18, $0
    /* FCA1C 001FCA1C C210040C */  jal        GetRootMatrixByDObj
    /* FCA20 001FCA20 D001A7AF */   sw        $7, 0x1D0($29)
    /* FCA24 001FCA24 5C42013C */  lui        $1, (0x425C0000 >> 16)
    /* FCA28 001FCA28 00008144 */  mtc1       $1, $f0
    /* FCA2C 001FCA2C 34C00046 */  c.lt.s     $f24, $f0
    /* FCA30 001FCA30 00000000 */  nop
    /* FCA34 001FCA34 1C000145 */  bc1t       .L001FCAA8
    /* FCA38 001FCA38 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FCA3C 001FCA3C 1B43013C */  lui        $1, (0x431B0000 >> 16)
    /* FCA40 001FCA40 00008144 */  mtc1       $1, $f0
    /* FCA44 001FCA44 34C00046 */  c.lt.s     $f24, $f0
    /* FCA48 001FCA48 05000045 */  bc1f       .L001FCA60
    /* FCA4C 001FCA4C 00000000 */   nop
    /* FCA50 001FCA50 A042013C */  lui        $1, (0x42A00000 >> 16)
    /* FCA54 001FCA54 00B08144 */  mtc1       $1, $f22
    /* FCA58 001FCA58 13000010 */  b          .L001FCAA8
    /* FCA5C 001FCA5C 64001724 */   addiu     $23, $0, 0x64
.align 2
  .L001FCA60:
    /* FCA60 001FCA60 7F43013C */  lui        $1, (0x437F0000 >> 16)
    /* FCA64 001FCA64 00008144 */  mtc1       $1, $f0
    /* FCA68 001FCA68 34C00046 */  c.lt.s     $f24, $f0
    /* FCA6C 001FCA6C 05000045 */  bc1f       .L001FCA84
    /* FCA70 001FCA70 00000000 */   nop
    /* FCA74 001FCA74 2043013C */  lui        $1, (0x43200000 >> 16)
    /* FCA78 001FCA78 00B08144 */  mtc1       $1, $f22
    /* FCA7C 001FCA7C 09000010 */  b          .L001FCAA4
    /* FCA80 001FCA80 C8001724 */   addiu     $23, $0, 0xC8
.align 2
  .L001FCA84:
    /* FCA84 001FCA84 448B80C7 */  lwc1       $f0, %gp_rel(D_00629734)($28)
    /* FCA88 001FCA88 34C00046 */  c.lt.s     $f24, $f0
    /* FCA8C 001FCA8C 00000000 */  nop
    /* FCA90 001FCA90 05000045 */  bc1f       .L001FCAA8
    /* FCA94 001FCA94 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FCA98 001FCA98 2043013C */  lui        $1, (0x43200000 >> 16)
    /* FCA9C 001FCA9C 00B08144 */  mtc1       $1, $f22
    /* FCAA0 001FCAA0 2C011724 */  addiu      $23, $0, 0x12C
.align 2
  .L001FCAA4:
    /* FCAA4 001FCAA4 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FCAA8:
    /* FCAA8 001FCAA8 1100A010 */  beqz       $5, .L001FCAF0
    /* FCAAC 001FCAAC F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* FCAB0 001FCAB0 10004010 */  beqz       $2, .L001FCAF4
    /* FCAB4 001FCAB4 A090838F */   lw        $3, %gp_rel(D_00629C90)($28)
    /* FCAB8 001FCAB8 3E74050C */  jal        ContinueCorrectPosition
    /* FCABC 001FCABC 2D20A000 */   daddu     $4, $5, $0
    /* FCAC0 001FCAC0 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FCAC4 001FCAC4 3E74050C */  jal        ContinueCorrectPosition
    /* FCAC8 001FCAC8 2D804000 */   daddu     $16, $2, $0
    /* FCACC 001FCACC 040040C4 */  lwc1       $f0, 0x4($2)
    /* FCAD0 001FCAD0 4844013C */  lui        $1, (0x44480000 >> 16)
    /* FCAD4 001FCAD4 00088144 */  mtc1       $1, $f1
    /* FCAD8 001FCAD8 040002C6 */  lwc1       $f2, 0x4($16)
    /* FCADC 001FCADC 00000146 */  add.s      $f0, $f0, $f1
    /* FCAE0 001FCAE0 34000246 */  c.lt.s     $f0, $f2
    /* FCAE4 001FCAE4 00000000 */  nop
    /* FCAE8 001FCAE8 01000345 */  bc1tl      .L001FCAF0
    /* FCAEC 001FCAEC D001A0AF */   sw        $0, 0x1D0($29)
.align 2
  .L001FCAF0:
    /* FCAF0 001FCAF0 A090838F */  lw         $3, %gp_rel(D_00629C90)($28)
.align 2
  .L001FCAF4:
    /* FCAF4 001FCAF4 07000224 */  addiu      $2, $0, 0x7
    /* FCAF8 001FCAF8 19006214 */  bne        $3, $2, .L001FCB60
    /* FCAFC 001FCAFC F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* FCB00 001FCB00 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FCB04 001FCB04 E229040C */  jal        GetHeightOfWallFromGObj
    /* FCB08 001FCB08 8000A427 */   addiu     $4, $29, 0x80
    /* FCB0C 001FCB0C C8000224 */  addiu      $2, $0, 0xC8
    /* FCB10 001FCB10 1300E256 */  bnel       $23, $2, .L001FCB60
    /* FCB14 001FCB14 F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* FCB18 001FCB18 8400A0C7 */  lwc1       $f0, 0x84($29)
    /* FCB1C 001FCB1C 0400A1C7 */  lwc1       $f1, 0x4($29)
    /* FCB20 001FCB20 3443013C */  lui        $1, (0x43340000 >> 16)
    /* FCB24 001FCB24 00108144 */  mtc1       $1, $f2
    /* FCB28 001FCB28 01000146 */  sub.s      $f0, $f0, $f1
    /* FCB2C 001FCB2C 34100046 */  c.lt.s     $f2, $f0
    /* FCB30 001FCB30 00000000 */  nop
    /* FCB34 001FCB34 01000245 */  bc1fl      .L001FCB3C
    /* FCB38 001FCB38 D001A0AF */   sw        $0, 0x1D0($29)
.align 2
  .L001FCB3C:
    /* FCB3C 001FCB3C 0000A0C7 */  lwc1       $f0, 0x0($29)
    /* FCB40 001FCB40 8000A1C7 */  lwc1       $f1, 0x80($29)
    /* FCB44 001FCB44 00108044 */  mtc1       $0, $f2
    /* FCB48 001FCB48 02000146 */  mul.s      $f0, $f0, $f1
    /* FCB4C 001FCB4C 34000246 */  c.lt.s     $f0, $f2
    /* FCB50 001FCB50 00000000 */  nop
    /* FCB54 001FCB54 01000345 */  bc1tl      .L001FCB5C
    /* FCB58 001FCB58 D001A0AF */   sw        $0, 0x1D0($29)
.align 2
  .L001FCB5C:
    /* FCB5C 001FCB5C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
.align 2
  .L001FCB60:
    /* FCB60 001FCB60 6401448C */  lw         $4, 0x164($2)
    /* FCB64 001FCB64 200083DC */  ld         $3, 0x20($4)
    /* FCB68 001FCB68 781B0300 */  dsll       $3, $3, 13
    /* FCB6C 001FCB6C 3F180300 */  dsra32     $3, $3, 0
    /* FCB70 001FCB70 01006330 */  andi       $3, $3, 0x1
    /* FCB74 001FCB74 08006010 */  beqz       $3, .L001FCB98
    /* FCB78 001FCB78 1400A1C7 */   lwc1      $f1, 0x14($29)
    /* FCB7C 001FCB7C C844013C */  lui        $1, (0x44C80000 >> 16)
    /* FCB80 001FCB80 00008144 */  mtc1       $1, $f0
    /* FCB84 001FCB84 34000146 */  c.lt.s     $f0, $f1
    /* FCB88 001FCB88 00000000 */  nop
    /* FCB8C 001FCB8C 02000045 */  bc1f       .L001FCB98
    /* FCB90 001FCB90 C800E22A */   slti      $2, $23, 0xC8
    /* FCB94 001FCB94 0AB80200 */  movz       $23, $0, $2
.align 2
  .L001FCB98:
    /* FCB98 001FCB98 C800E82A */  slti       $8, $23, 0xC8
    /* FCB9C 001FCB9C 66000015 */  bnez       $8, .L001FCD38
    /* FCBA0 001FCBA0 D801A8AF */   sw        $8, 0x1D8($29)
    /* FCBA4 001FCBA4 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FCBA8 001FCBA8 00608144 */  mtc1       $1, $f12
    /* FCBAC 001FCBAC 9000B127 */  addiu      $17, $29, 0x90
    /* FCBB0 001FCBB0 0000A2C7 */  lwc1       $f2, 0x0($29)
    /* FCBB4 001FCBB4 2D202002 */  daddu      $4, $17, $0
    /* FCBB8 001FCBB8 0400A0C7 */  lwc1       $f0, 0x4($29)
    /* FCBBC 001FCBBC 00AB0C46 */  add.s      $f12, $f21, $f12
    /* FCBC0 001FCBC0 0800A1C7 */  lwc1       $f1, 0x8($29)
    /* FCBC4 001FCBC4 C801A58F */  lw         $5, 0x1C8($29)
    /* FCBC8 001FCBC8 A000A2E7 */  swc1       $f2, 0xA0($29)
    /* FCBCC 001FCBCC A400A0E7 */  swc1       $f0, 0xA4($29)
    /* FCBD0 001FCBD0 0E00090C */  jal        func_00240038
    /* FCBD4 001FCBD4 A800A1E7 */   swc1      $f1, 0xA8($29)
    /* FCBD8 001FCBD8 B000BE27 */  addiu      $30, $29, 0xB0
    /* FCBDC 001FCBDC 2D302002 */  daddu      $6, $17, $0
    /* FCBE0 001FCBE0 2D20C003 */  daddu      $4, $30, $0
    /* FCBE4 001FCBE4 FCFF080C */  jal        func_0023FFF0
    /* FCBE8 001FCBE8 A000A527 */   addiu     $5, $29, 0xA0
    /* FCBEC 001FCBEC B400A0C7 */  lwc1       $f0, 0xB4($29)
    /* FCBF0 001FCBF0 C000B627 */  addiu      $22, $29, 0xC0
    /* FCBF4 001FCBF4 C801A58F */  lw         $5, 0x1C8($29)
    /* FCBF8 001FCBF8 2D20C002 */  daddu      $4, $22, $0
    /* FCBFC 001FCBFC 00001846 */  add.s      $f0, $f0, $f24
    /* FCC00 001FCC00 2C46060C */  jal        _OrientGV
    /* FCC04 001FCC04 B400A0E7 */   swc1      $f0, 0xB4($29)
    /* FCC08 001FCC08 8EF9040C */  jal        isysGObjSearchFromObjLayoutID
    /* FCC0C 001FCC0C 11000424 */   addiu     $4, $0, 0x11
    /* FCC10 001FCC10 2D804000 */  daddu      $16, $2, $0
    /* FCC14 001FCC14 48000012 */  beqz       $16, .L001FCD38
    /* FCC18 001FCC18 00000000 */   nop
    /* FCC1C 001FCC1C C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FCC20 001FCC20 00A08144 */  mtc1       $1, $f20
    /* FCC24 001FCC24 1001B227 */  addiu      $18, $29, 0x110
    /* FCC28 001FCC28 6C01028E */  lw         $2, 0x16C($16)
    /* FCC2C 001FCC2C 00000000 */  nop
.align 2
  .L001FCC30:
    /* FCC30 001FCC30 3C004010 */  beqz       $2, .L001FCD24
    /* FCC34 001FCC34 00000000 */   nop
    /* FCC38 001FCC38 86F6060C */  jal        ExecBoxMoveEndReaction
    /* FCC3C 001FCC3C 2D200002 */   daddu     $4, $16, $0
    /* FCC40 001FCC40 07000324 */  addiu      $3, $0, 0x7
    /* FCC44 001FCC44 37004310 */  beq        $2, $3, .L001FCD24
    /* FCC48 001FCC48 00000000 */   nop
    /* FCC4C 001FCC4C 3E74050C */  jal        ContinueCorrectPosition
    /* FCC50 001FCC50 2D200002 */   daddu     $4, $16, $0
    /* FCC54 001FCC54 000040C4 */  lwc1       $f0, 0x0($2)
    /* FCC58 001FCC58 2D200002 */  daddu      $4, $16, $0
    /* FCC5C 001FCC5C 3E74050C */  jal        ContinueCorrectPosition
    /* FCC60 001FCC60 0001A0E7 */   swc1      $f0, 0x100($29)
    /* FCC64 001FCC64 040040C4 */  lwc1       $f0, 0x4($2)
    /* FCC68 001FCC68 2D200002 */  daddu      $4, $16, $0
    /* FCC6C 001FCC6C 3E74050C */  jal        ContinueCorrectPosition
    /* FCC70 001FCC70 0401A0E7 */   swc1      $f0, 0x104($29)
    /* FCC74 001FCC74 080040C4 */  lwc1       $f0, 0x8($2)
    /* FCC78 001FCC78 0001B127 */  addiu      $17, $29, 0x100
    /* FCC7C 001FCC7C 2D20C003 */  daddu      $4, $30, $0
    /* FCC80 001FCC80 2D282002 */  daddu      $5, $17, $0
    /* FCC84 001FCC84 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FCC88 001FCC88 0801A0E7 */   swc1      $f0, 0x108($29)
    /* FCC8C 001FCC8C 488B81C7 */  lwc1       $f1, %gp_rel(D_00629738)($28)
    /* FCC90 001FCC90 34000146 */  c.lt.s     $f0, $f1
    /* FCC94 001FCC94 00000000 */  nop
    /* FCC98 001FCC98 22000045 */  bc1f       .L001FCD24
    /* FCC9C 001FCC9C B400A0C7 */   lwc1      $f0, 0xB4($29)
    /* FCCA0 001FCCA0 0401A1C7 */  lwc1       $f1, 0x104($29)
    /* FCCA4 001FCCA4 00108044 */  mtc1       $0, $f2
    /* FCCA8 001FCCA8 01000146 */  sub.s      $f0, $f0, $f1
    /* FCCAC 001FCCAC 34000246 */  c.lt.s     $f0, $f2
    /* FCCB0 001FCCB0 00000000 */  nop
    /* FCCB4 001FCCB4 01000345 */  bc1tl      .L001FCCBC
    /* FCCB8 001FCCB8 07000046 */   neg.s     $f0, $f0
.align 2
  .L001FCCBC:
    /* FCCBC 001FCCBC 34A00046 */  c.lt.s     $f20, $f0
    /* FCCC0 001FCCC0 00000000 */  nop
    /* FCCC4 001FCCC4 17000145 */  bc1t       .L001FCD24
    /* FCCC8 001FCCC8 C401A58F */   lw        $5, 0x1C4($29)
    /* FCCCC 001FCCCC 2D302002 */  daddu      $6, $17, $0
    /* FCCD0 001FCCD0 0200090C */  jal        func_00240008
    /* FCCD4 001FCCD4 2D204002 */   daddu     $4, $18, $0
    /* FCCD8 001FCCD8 1C01A0AF */  sw         $0, 0x11C($29)
    /* FCCDC 001FCCDC 2001A427 */  addiu      $4, $29, 0x120
    /* FCCE0 001FCCE0 2D28C002 */  daddu      $5, $22, $0
    /* FCCE4 001FCCE4 76FF080C */  jal        func_0023FDD8
    /* FCCE8 001FCCE8 2D304002 */   daddu     $6, $18, $0
    /* FCCEC 001FCCEC 2001A1C7 */  lwc1       $f1, 0x120($29)
    /* FCCF0 001FCCF0 F0C1013C */  lui        $1, (0xC1F00000 >> 16)
    /* FCCF4 001FCCF4 00008144 */  mtc1       $1, $f0
    /* FCCF8 001FCCF8 34080046 */  c.lt.s     $f1, $f0
    /* FCCFC 001FCCFC 00000000 */  nop
    /* FCD00 001FCD00 0D000345 */  bc1tl      .L001FCD38
    /* FCD04 001FCD04 D001A0AF */   sw        $0, 0x1D0($29)
    /* FCD08 001FCD08 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FCD0C 001FCD0C 00008144 */  mtc1       $1, $f0
    /* FCD10 001FCD10 34000146 */  c.lt.s     $f0, $f1
    /* FCD14 001FCD14 03000045 */  bc1f       .L001FCD24
    /* FCD18 001FCD18 00000000 */   nop
    /* FCD1C 001FCD1C 06000010 */  b          .L001FCD38
    /* FCD20 001FCD20 D001A0AF */   sw        $0, 0x1D0($29)
.align 2
  .L001FCD24:
    /* FCD24 001FCD24 B2F9040C */  jal        isysGObjSearchFromObjKindID_begin
    /* FCD28 001FCD28 2D200002 */   daddu     $4, $16, $0
    /* FCD2C 001FCD2C 2D804000 */  daddu      $16, $2, $0
    /* FCD30 001FCD30 BFFF0056 */  bnel       $16, $0, .L001FCC30
    /* FCD34 001FCD34 6C01028E */   lw        $2, 0x16C($16)
.align 2
  .L001FCD38:
    /* FCD38 001FCD38 C800E012 */  beqz       $23, .L001FD05C
    /* FCD3C 001FCD3C F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FCD40 001FCD40 34B01746 */  c.lt.s     $f22, $f23
    /* FCD44 001FCD44 00000000 */  nop
    /* FCD48 001FCD48 C4000045 */  bc1f       .L001FD05C
    /* FCD4C 001FCD4C D401A48F */   lw        $4, 0x1D4($29)
    /* FCD50 001FCD50 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FCD54 001FCD54 7000A527 */   addiu     $5, $29, 0x70
    /* FCD58 001FCD58 4C8B81C7 */  lwc1       $f1, %gp_rel(D_0062973C)($28)
    /* FCD5C 001FCD5C 34000146 */  c.lt.s     $f0, $f1
    /* FCD60 001FCD60 00000000 */  nop
    /* FCD64 001FCD64 BC000045 */  bc1f       .L001FD058
    /* FCD68 001FCD68 D001A98F */   lw        $9, 0x1D0($29)
    /* FCD6C 001FCD6C BA002011 */  beqz       $9, .L001FD058
    /* FCD70 001FCD70 4001B127 */   addiu     $17, $29, 0x140
    /* FCD74 001FCD74 3000A58F */  lw         $5, 0x30($29)
    /* FCD78 001FCD78 2D202002 */  daddu      $4, $17, $0
    /* FCD7C 001FCD7C C210040C */  jal        GetRootMatrixByDObj
    /* FCD80 001FCD80 5000B226 */   addiu     $18, $21, 0x50
    /* FCD84 001FCD84 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FCD88 001FCD88 00A08144 */  mtc1       $1, $f20
    /* FCD8C 001FCD8C 3001B027 */  addiu      $16, $29, 0x130
    /* FCD90 001FCD90 C801A58F */  lw         $5, 0x1C8($29)
    /* FCD94 001FCD94 2D200002 */  daddu      $4, $16, $0
    /* FCD98 001FCD98 0E00090C */  jal        func_00240038
    /* FCD9C 001FCD9C 06AB0046 */   mov.s     $f12, $f21
    /* FCDA0 001FCDA0 2D282002 */  daddu      $5, $17, $0
    /* FCDA4 001FCDA4 2D300002 */  daddu      $6, $16, $0
    /* FCDA8 001FCDA8 FCFF080C */  jal        func_0023FFF0
    /* FCDAC 001FCDAC 2D204002 */   daddu     $4, $18, $0
    /* FCDB0 001FCDB0 6001B127 */  addiu      $17, $29, 0x160
    /* FCDB4 001FCDB4 3000A58F */  lw         $5, 0x30($29)
    /* FCDB8 001FCDB8 C210040C */  jal        GetRootMatrixByDObj
    /* FCDBC 001FCDBC 2D202002 */   daddu     $4, $17, $0
    /* FCDC0 001FCDC0 01AB1446 */  sub.s      $f12, $f21, $f20
    /* FCDC4 001FCDC4 5001B027 */  addiu      $16, $29, 0x150
    /* FCDC8 001FCDC8 C801A58F */  lw         $5, 0x1C8($29)
    /* FCDCC 001FCDCC 0E00090C */  jal        func_00240038
    /* FCDD0 001FCDD0 2D200002 */   daddu     $4, $16, $0
    /* FCDD4 001FCDD4 3000A38F */  lw         $3, 0x30($29)
    /* FCDD8 001FCDD8 2D282002 */  daddu      $5, $17, $0
    /* FCDDC 001FCDDC 2D300002 */  daddu      $6, $16, $0
    /* FCDE0 001FCDE0 6401628C */  lw         $2, 0x164($3)
    /* FCDE4 001FCDE4 7806448C */  lw         $4, 0x678($2)
    /* FCDE8 001FCDE8 FCFF080C */  jal        func_0023FFF0
    /* FCDEC 001FCDEC 20078424 */   addiu     $4, $4, 0x720
    /* FCDF0 001FCDF0 3000A48F */  lw         $4, 0x30($29)
    /* FCDF4 001FCDF4 14000524 */  addiu      $5, $0, 0x14
    /* FCDF8 001FCDF8 1000A0C6 */  lwc1       $f0, 0x10($21)
    /* FCDFC 001FCDFC 00800634 */  ori        $6, $0, 0x8000
    /* FCE00 001FCE00 BC330600 */  dsll32     $6, $6, 14
    /* FCE04 001FCE04 6401828C */  lw         $2, 0x164($4)
    /* FCE08 001FCE08 7806438C */  lw         $3, 0x678($2)
    /* FCE0C 001FCE0C 300760E4 */  swc1       $f0, 0x730($3)
    /* FCE10 001FCE10 440765AC */  sw         $5, 0x744($3)
    /* FCE14 001FCE14 1400A0C6 */  lwc1       $f0, 0x14($21)
    /* FCE18 001FCE18 6401828C */  lw         $2, 0x164($4)
    /* FCE1C 001FCE1C 340760E4 */  swc1       $f0, 0x734($3)
    /* FCE20 001FCE20 7806448C */  lw         $4, 0x678($2)
    /* FCE24 001FCE24 1800A0C6 */  lwc1       $f0, 0x18($21)
    /* FCE28 001FCE28 400774E4 */  swc1       $f20, 0x740($3)
    /* FCE2C 001FCE2C 380760E4 */  swc1       $f0, 0x738($3)
    /* FCE30 001FCE30 480780AC */  sw         $0, 0x748($4)
    /* FCE34 001FCE34 680462DE */  ld         $2, 0x468($19)
    /* FCE38 001FCE38 25104600 */  or         $2, $2, $6
    /* FCE3C 001FCE3C 680462FE */  sd         $2, 0x468($19)
    /* FCE40 001FCE40 CC01A28F */  lw         $2, 0x1CC($29)
    /* FCE44 001FCE44 84004010 */  beqz       $2, .L001FD058
    /* FCE48 001FCE48 A090838F */   lw        $3, %gp_rel(D_00629C90)($28)
    /* FCE4C 001FCE4C 62000224 */  addiu      $2, $0, 0x62
    /* FCE50 001FCE50 5C006254 */  bnel       $3, $2, .L001FCFC4
    /* FCE54 001FCE54 3401B7AE */   sw        $23, 0x134($21)
    /* FCE58 001FCE58 8EF9040C */  jal        isysGObjSearchFromObjLayoutID
    /* FCE5C 001FCE5C 11000424 */   addiu     $4, $0, 0x11
    /* FCE60 001FCE60 2D884000 */  daddu      $17, $2, $0
    /* FCE64 001FCE64 57002052 */  beql       $17, $0, .L001FCFC4
    /* FCE68 001FCE68 3401B7AE */   sw        $23, 0x134($21)
    /* FCE6C 001FCE6C 3E74050C */  jal        ContinueCorrectPosition
    /* FCE70 001FCE70 2D202002 */   daddu     $4, $17, $0
    /* FCE74 001FCE74 3000A48F */  lw         $4, 0x30($29)
    /* FCE78 001FCE78 3E74050C */  jal        ContinueCorrectPosition
    /* FCE7C 001FCE7C 2D804000 */   daddu     $16, $2, $0
    /* FCE80 001FCE80 2D200002 */  daddu      $4, $16, $0
    /* FCE84 001FCE84 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FCE88 001FCE88 2D284000 */   daddu     $5, $2, $0
    /* FCE8C 001FCE8C 508B81C7 */  lwc1       $f1, %gp_rel(D_00629740)($28)
    /* FCE90 001FCE90 34000146 */  c.lt.s     $f0, $f1
    /* FCE94 001FCE94 00000000 */  nop
    /* FCE98 001FCE98 49000045 */  bc1f       .L001FCFC0
    /* FCE9C 001FCE9C D801A38F */   lw        $3, 0x1D8($29)
    /* FCEA0 001FCEA0 48006054 */  bnel       $3, $0, .L001FCFC4
    /* FCEA4 001FCEA4 3401B7AE */   sw        $23, 0x134($21)
    /* FCEA8 001FCEA8 2D01E22A */  slti       $2, $23, 0x12D
    /* FCEAC 001FCEAC 45004050 */  beql       $2, $0, .L001FCFC4
    /* FCEB0 001FCEB0 3401B7AE */   sw        $23, 0x134($21)
    /* FCEB4 001FCEB4 3E74050C */  jal        ContinueCorrectPosition
    /* FCEB8 001FCEB8 2D202002 */   daddu     $4, $17, $0
    /* FCEBC 001FCEBC 3000A48F */  lw         $4, 0x30($29)
    /* FCEC0 001FCEC0 3E74050C */  jal        ContinueCorrectPosition
    /* FCEC4 001FCEC4 2D804000 */   daddu     $16, $2, $0
    /* FCEC8 001FCEC8 040001C6 */  lwc1       $f1, 0x4($16)
    /* FCECC 001FCECC 040040C4 */  lwc1       $f0, 0x4($2)
    /* FCED0 001FCED0 34000146 */  c.lt.s     $f0, $f1
    /* FCED4 001FCED4 00000000 */  nop
    /* FCED8 001FCED8 3A000245 */  bc1fl      .L001FCFC4
    /* FCEDC 001FCEDC 3401B7AE */   sw        $23, 0x134($21)
    /* FCEE0 001FCEE0 3E74050C */  jal        ContinueCorrectPosition
    /* FCEE4 001FCEE4 2D202002 */   daddu     $4, $17, $0
    /* FCEE8 001FCEE8 3000A48F */  lw         $4, 0x30($29)
    /* FCEEC 001FCEEC 3E74050C */  jal        ContinueCorrectPosition
    /* FCEF0 001FCEF0 2D804000 */   daddu     $16, $2, $0
    /* FCEF4 001FCEF4 040000C6 */  lwc1       $f0, 0x4($16)
    /* FCEF8 001FCEF8 040041C4 */  lwc1       $f1, 0x4($2)
    /* FCEFC 001FCEFC 00108044 */  mtc1       $0, $f2
    /* FCF00 001FCF00 01000146 */  sub.s      $f0, $f0, $f1
    /* FCF04 001FCF04 34000246 */  c.lt.s     $f0, $f2
    /* FCF08 001FCF08 12000045 */  bc1f       .L001FCF54
    /* FCF0C 001FCF0C 00000000 */   nop
    /* FCF10 001FCF10 3E74050C */  jal        ContinueCorrectPosition
    /* FCF14 001FCF14 2D202002 */   daddu     $4, $17, $0
    /* FCF18 001FCF18 3000A48F */  lw         $4, 0x30($29)
    /* FCF1C 001FCF1C 3E74050C */  jal        ContinueCorrectPosition
    /* FCF20 001FCF20 2D804000 */   daddu     $16, $2, $0
    /* FCF24 001FCF24 040000C6 */  lwc1       $f0, 0x4($16)
    /* FCF28 001FCF28 040041C4 */  lwc1       $f1, 0x4($2)
    /* FCF2C 001FCF2C C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FCF30 001FCF30 00108144 */  mtc1       $1, $f2
    /* FCF34 001FCF34 01000146 */  sub.s      $f0, $f0, $f1
    /* FCF38 001FCF38 07000046 */  neg.s      $f0, $f0
    /* FCF3C 001FCF3C 34100046 */  c.lt.s     $f2, $f0
    /* FCF40 001FCF40 00000000 */  nop
    /* FCF44 001FCF44 12000145 */  bc1t       .L001FCF90
    /* FCF48 001FCF48 7001B027 */   addiu     $16, $29, 0x170
    /* FCF4C 001FCF4C 1D000010 */  b          .L001FCFC4
    /* FCF50 001FCF50 3401B7AE */   sw        $23, 0x134($21)
.align 2
  .L001FCF54:
    /* FCF54 001FCF54 3E74050C */  jal        ContinueCorrectPosition
    /* FCF58 001FCF58 2D202002 */   daddu     $4, $17, $0
    /* FCF5C 001FCF5C 3000A48F */  lw         $4, 0x30($29)
    /* FCF60 001FCF60 3E74050C */  jal        ContinueCorrectPosition
    /* FCF64 001FCF64 2D804000 */   daddu     $16, $2, $0
    /* FCF68 001FCF68 040000C6 */  lwc1       $f0, 0x4($16)
    /* FCF6C 001FCF6C 040041C4 */  lwc1       $f1, 0x4($2)
    /* FCF70 001FCF70 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FCF74 001FCF74 00108144 */  mtc1       $1, $f2
    /* FCF78 001FCF78 01000146 */  sub.s      $f0, $f0, $f1
    /* FCF7C 001FCF7C 34100046 */  c.lt.s     $f2, $f0
    /* FCF80 001FCF80 00000000 */  nop
    /* FCF84 001FCF84 0F000245 */  bc1fl      .L001FCFC4
    /* FCF88 001FCF88 3401B7AE */   sw        $23, 0x134($21)
    /* FCF8C 001FCF8C 7001B027 */  addiu      $16, $29, 0x170
.align 2
  .L001FCF90:
    /* FCF90 001FCF90 48C2013C */  lui        $1, (0xC2480000 >> 16)
    /* FCF94 001FCF94 00608144 */  mtc1       $1, $f12
    /* FCF98 001FCF98 C801A58F */  lw         $5, 0x1C8($29)
    /* FCF9C 001FCF9C 2D200002 */  daddu      $4, $16, $0
    /* FCFA0 001FCFA0 0E00090C */  jal        func_00240038
    /* FCFA4 001FCFA4 C8001724 */   addiu     $23, $0, 0xC8
    /* FCFA8 001FCFA8 3E74050C */  jal        ContinueCorrectPosition
    /* FCFAC 001FCFAC 2D202002 */   daddu     $4, $17, $0
    /* FCFB0 001FCFB0 2D204002 */  daddu      $4, $18, $0
    /* FCFB4 001FCFB4 2D284000 */  daddu      $5, $2, $0
    /* FCFB8 001FCFB8 FCFF080C */  jal        func_0023FFF0
    /* FCFBC 001FCFBC 2D300002 */   daddu     $6, $16, $0
.align 2
  .L001FCFC0:
    /* FCFC0 001FCFC0 3401B7AE */  sw         $23, 0x134($21)
.align 2
  .L001FCFC4:
    /* FCFC4 001FCFC4 C8000224 */  addiu      $2, $0, 0xC8
    /* FCFC8 001FCFC8 1200E212 */  beq        $23, $2, .L001FD014
    /* FCFCC 001FCFCC C900E22A */   slti      $2, $23, 0xC9
    /* FCFD0 001FCFD0 05004010 */  beqz       $2, .L001FCFE8
    /* FCFD4 001FCFD4 64000224 */   addiu     $2, $0, 0x64
    /* FCFD8 001FCFD8 0800E212 */  beq        $23, $2, .L001FCFFC
    /* FCFDC 001FCFDC 6100103C */   lui       $16, %hi(D_006139D0)
    /* FCFE0 001FCFE0 15000010 */  b          .L001FD038
    /* FCFE4 001FCFE4 17090524 */   addiu     $5, $0, 0x917
.align 2
  .L001FCFE8:
    /* FCFE8 001FCFE8 2C010224 */  addiu      $2, $0, 0x12C
    /* FCFEC 001FCFEC 0D00E212 */  beq        $23, $2, .L001FD024
    /* FCFF0 001FCFF0 6100103C */   lui       $16, %hi(D_006139D0)
    /* FCFF4 001FCFF4 10000010 */  b          .L001FD038
    /* FCFF8 001FCFF8 17090524 */   addiu     $5, $0, 0x917
.align 2
  .L001FCFFC:
    /* FCFFC 001FCFFC 700462DE */  ld         $2, 0x470($19)
    /* FD000 001FD000 00800334 */  ori        $3, $0, 0x8000
    /* FD004 001FD004 FC1B0300 */  dsll32     $3, $3, 15
.align 2
  .L001FD008:
    /* FD008 001FD008 25104300 */  or         $2, $2, $3
    /* FD00C 001FD00C 12000010 */  b          .L001FD058
    /* FD010 001FD010 700462FE */   sd        $2, 0x470($19)
.align 2
  .L001FD014:
    /* FD014 001FD014 00800334 */  ori        $3, $0, 0x8000
    /* FD018 001FD018 3C1C0300 */  dsll32     $3, $3, 16
    /* FD01C 001FD01C FAFF0010 */  b          .L001FD008
    /* FD020 001FD020 700462DE */   ld        $2, 0x470($19)
.align 2
  .L001FD024:
    /* FD024 001FD024 780462DE */  ld         $2, 0x478($19)
    /* FD028 001FD028 01000324 */  addiu      $3, $0, 0x1
    /* FD02C 001FD02C 25104300 */  or         $2, $2, $3
    /* FD030 001FD030 09000010 */  b          .L001FD058
    /* FD034 001FD034 780462FE */   sd        $2, 0x478($19)
.align 2
  .L001FD038:
    /* FD038 001FD038 D0391026 */  addiu      $16, $16, %lo(D_006139D0)
    /* FD03C 001FD03C 40AB060C */  jal        func_001AAD00
    /* FD040 001FD040 2D200002 */   daddu     $4, $16, $0
    /* FD044 001FD044 6300063C */  lui        $6, %hi(D_0062D9C8)
    /* FD048 001FD048 2D200002 */  daddu      $4, $16, $0
    /* FD04C 001FD04C C8D9C624 */  addiu      $6, $6, %lo(D_0062D9C8)
    /* FD050 001FD050 E080090C */  jal        func_00260380
    /* FD054 001FD054 17090524 */   addiu     $5, $0, 0x917
.align 2
  .L001FD058:
    /* FD058 001FD058 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FD05C:
    /* FD05C 001FD05C 2701A010 */  beqz       $5, .L001FD4FC
    /* FD060 001FD060 F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* FD064 001FD064 3000A38F */  lw         $3, 0x30($29)
    /* FD068 001FD068 25016254 */  bnel       $3, $2, .L001FD500
    /* FD06C 001FD06C 0800828E */   lw        $2, 0x8($20)
    /* FD070 001FD070 4843013C */  lui        $1, (0x43480000 >> 16)
    /* FD074 001FD074 00008144 */  mtc1       $1, $f0
    /* FD078 001FD078 34A80046 */  c.lt.s     $f21, $f0
    /* FD07C 001FD07C 00000000 */  nop
    /* FD080 001FD080 1F010245 */  bc1fl      .L001FD500
    /* FD084 001FD084 0800828E */   lw        $2, 0x8($20)
    /* FD088 001FD088 AF43013C */  lui        $1, (0x43AF0000 >> 16)
    /* FD08C 001FD08C 00008144 */  mtc1       $1, $f0
    /* FD090 001FD090 34001846 */  c.lt.s     $f0, $f24
    /* FD094 001FD094 00000000 */  nop
    /* FD098 001FD098 19010245 */  bc1fl      .L001FD500
    /* FD09C 001FD09C 0800828E */   lw        $2, 0x8($20)
    /* FD0A0 001FD0A0 A222050C */  jal        ACTEnvGetTest
    /* FD0A4 001FD0A4 00000000 */   nop
    /* FD0A8 001FD0A8 15014054 */  bnel       $2, $0, .L001FD500
    /* FD0AC 001FD0AC 0800828E */   lw        $2, 0x8($20)
    /* FD0B0 001FD0B0 3E74050C */  jal        ContinueCorrectPosition
    /* FD0B4 001FD0B4 F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FD0B8 001FD0B8 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* FD0BC 001FD0BC 3E74050C */  jal        ContinueCorrectPosition
    /* FD0C0 001FD0C0 2D804000 */   daddu     $16, $2, $0
    /* FD0C4 001FD0C4 2D200002 */  daddu      $4, $16, $0
    /* FD0C8 001FD0C8 E646060C */  jal        HandyCamera_TargetMoveType
    /* FD0CC 001FD0CC 2D284000 */   daddu     $5, $2, $0
    /* FD0D0 001FD0D0 548B81C7 */  lwc1       $f1, %gp_rel(D_00629744)($28)
    /* FD0D4 001FD0D4 34000146 */  c.lt.s     $f0, $f1
    /* FD0D8 001FD0D8 00000000 */  nop
    /* FD0DC 001FD0DC 08010345 */  bc1tl      .L001FD500
    /* FD0E0 001FD0E0 0800828E */   lw        $2, 0x8($20)
    /* FD0E4 001FD0E4 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FD0E8 001FD0E8 1200A010 */  beqz       $5, .L001FD134
    /* FD0EC 001FD0EC F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* FD0F0 001FD0F0 11004050 */  beql       $2, $0, .L001FD138
    /* FD0F4 001FD0F4 6401A28C */   lw        $2, 0x164($5)
    /* FD0F8 001FD0F8 3E74050C */  jal        ContinueCorrectPosition
    /* FD0FC 001FD0FC 2D20A000 */   daddu     $4, $5, $0
    /* FD100 001FD100 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FD104 001FD104 3E74050C */  jal        ContinueCorrectPosition
    /* FD108 001FD108 2D804000 */   daddu     $16, $2, $0
    /* FD10C 001FD10C 040040C4 */  lwc1       $f0, 0x4($2)
    /* FD110 001FD110 4844013C */  lui        $1, (0x44480000 >> 16)
    /* FD114 001FD114 00088144 */  mtc1       $1, $f1
    /* FD118 001FD118 040002C6 */  lwc1       $f2, 0x4($16)
    /* FD11C 001FD11C 00000146 */  add.s      $f0, $f0, $f1
    /* FD120 001FD120 34000246 */  c.lt.s     $f0, $f2
    /* FD124 001FD124 00000000 */  nop
    /* FD128 001FD128 F5000345 */  bc1tl      .L001FD500
    /* FD12C 001FD12C 0800828E */   lw        $2, 0x8($20)
    /* FD130 001FD130 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FD134:
    /* FD134 001FD134 6401A28C */  lw         $2, 0x164($5)
.align 2
  .L001FD138:
    /* FD138 001FD138 04000424 */  addiu      $4, $0, 0x4
    /* FD13C 001FD13C 3000438C */  lw         $3, 0x30($2)
    /* FD140 001FD140 11006410 */  beq        $3, $4, .L001FD188
    /* FD144 001FD144 00000000 */   nop
    /* FD148 001FD148 3E74050C */  jal        ContinueCorrectPosition
    /* FD14C 001FD14C F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FD150 001FD150 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* FD154 001FD154 3E74050C */  jal        ContinueCorrectPosition
    /* FD158 001FD158 2D804000 */   daddu     $16, $2, $0
    /* FD15C 001FD15C 2D200002 */  daddu      $4, $16, $0
    /* FD160 001FD160 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FD164 001FD164 2D284000 */   daddu     $5, $2, $0
    /* FD168 001FD168 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FD16C 001FD16C 00088144 */  mtc1       $1, $f1
    /* FD170 001FD170 40A80146 */  add.s      $f1, $f21, $f1
    /* FD174 001FD174 42080146 */  mul.s      $f1, $f1, $f1
    /* FD178 001FD178 34000146 */  c.lt.s     $f0, $f1
    /* FD17C 001FD17C 00000000 */  nop
    /* FD180 001FD180 DF000345 */  bc1tl      .L001FD500
    /* FD184 001FD184 0800828E */   lw        $2, 0x8($20)
.align 2
  .L001FD188:
    /* FD188 001FD188 3E74050C */  jal        ContinueCorrectPosition
    /* FD18C 001FD18C F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FD190 001FD190 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* FD194 001FD194 3E74050C */  jal        ContinueCorrectPosition
    /* FD198 001FD198 2D804000 */   daddu     $16, $2, $0
    /* FD19C 001FD19C 2D200002 */  daddu      $4, $16, $0
    /* FD1A0 001FD1A0 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FD1A4 001FD1A4 2D284000 */   daddu     $5, $2, $0
    /* FD1A8 001FD1A8 588B81C7 */  lwc1       $f1, %gp_rel(D_00629748)($28)
    /* FD1AC 001FD1AC 34000146 */  c.lt.s     $f0, $f1
    /* FD1B0 001FD1B0 00000000 */  nop
    /* FD1B4 001FD1B4 0A000045 */  bc1f       .L001FD1E0
    /* FD1B8 001FD1B8 F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* FD1BC 001FD1BC 6629040C */  jal        EnableChangeRootUpdateMode
    /* FD1C0 001FD1C0 F491858F */   lw        $5, %gp_rel(D_00629DE4)($28)
    /* FD1C4 001FD1C4 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FD1C8 001FD1C8 00088144 */  mtc1       $1, $f1
    /* FD1CC 001FD1CC 34080046 */  c.lt.s     $f1, $f0
    /* FD1D0 001FD1D0 00000000 */  nop
    /* FD1D4 001FD1D4 CA000345 */  bc1tl      .L001FD500
    /* FD1D8 001FD1D8 0800828E */   lw        $2, 0x8($20)
    /* FD1DC 001FD1DC F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FD1E0:
    /* FD1E0 001FD1E0 3E74050C */  jal        ContinueCorrectPosition
    /* FD1E4 001FD1E4 8000B127 */   addiu     $17, $29, 0x80
    /* FD1E8 001FD1E8 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FD1EC 001FD1EC 3E74050C */  jal        ContinueCorrectPosition
    /* FD1F0 001FD1F0 2D804000 */   daddu     $16, $2, $0
    /* FD1F4 001FD1F4 2D280002 */  daddu      $5, $16, $0
    /* FD1F8 001FD1F8 2D304000 */  daddu      $6, $2, $0
    /* FD1FC 001FD1FC F447060C */  jal        func_00191FD0
    /* FD200 001FD200 2D202002 */   daddu     $4, $17, $0
    /* FD204 001FD204 C801A58F */  lw         $5, 0x1C8($29)
    /* FD208 001FD208 6447060C */  jal        func_00191D90
    /* FD20C 001FD20C 2D202002 */   daddu     $4, $17, $0
    /* FD210 001FD210 50004228 */  slti       $2, $2, 0x50
    /* FD214 001FD214 B9004010 */  beqz       $2, .L001FD4FC
    /* FD218 001FD218 4C00023C */   lui       $2, %hi(D_004C6EC0)
    /* FD21C 001FD21C F491858F */  lw         $5, %gp_rel(D_00629DE4)($28)
    /* FD220 001FD220 C06E4224 */  addiu      $2, $2, %lo(D_004C6EC0)
    /* FD224 001FD224 9001B127 */  addiu      $17, $29, 0x190
    /* FD228 001FD228 9001A2AF */  sw         $2, 0x190($29)
    /* FD22C 001FD22C 9401B627 */  addiu      $22, $29, 0x194
    /* FD230 001FD230 9801B227 */  addiu      $18, $29, 0x198
    /* FD234 001FD234 9401A0AF */  sw         $0, 0x194($29)
    /* FD238 001FD238 1500A010 */  beqz       $5, .L001FD290
    /* FD23C 001FD23C 9801A0AF */   sw        $0, 0x198($29)
    /* FD240 001FD240 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* FD244 001FD244 12008010 */  beqz       $4, .L001FD290
    /* FD248 001FD248 A090838F */   lw        $3, %gp_rel(D_00629C90)($28)
    /* FD24C 001FD24C 08000224 */  addiu      $2, $0, 0x8
    /* FD250 001FD250 10006254 */  bnel       $3, $2, .L001FD294
    /* FD254 001FD254 2D800000 */   daddu     $16, $0, $0
    /* FD258 001FD258 5C01A28C */  lw         $2, 0x15C($5)
    /* FD25C 001FD25C 5C01838C */  lw         $3, 0x15C($4)
    /* FD260 001FD260 0000428C */  lw         $2, 0x0($2)
    /* FD264 001FD264 05004010 */  beqz       $2, .L001FD27C
    /* FD268 001FD268 0000648C */   lw        $4, 0x0($3)
    /* FD26C 001FD26C 0C00438C */  lw         $3, 0xC($2)
    /* FD270 001FD270 2B000224 */  addiu      $2, $0, 0x2B
    /* FD274 001FD274 07006210 */  beq        $3, $2, .L001FD294
    /* FD278 001FD278 01001024 */   addiu     $16, $0, 0x1
.align 2
  .L001FD27C:
    /* FD27C 001FD27C 04008010 */  beqz       $4, .L001FD290
    /* FD280 001FD280 2B000224 */   addiu     $2, $0, 0x2B
    /* FD284 001FD284 0C00838C */  lw         $3, 0xC($4)
    /* FD288 001FD288 02006210 */  beq        $3, $2, .L001FD294
    /* FD28C 001FD28C 02001024 */   addiu     $16, $0, 0x2
.align 2
  .L001FD290:
    /* FD290 001FD290 2D800000 */  daddu      $16, $0, $0
.align 2
  .L001FD294:
    /* FD294 001FD294 44000012 */  beqz       $16, .L001FD3A8
    /* FD298 001FD298 9001A48F */   lw        $4, 0x190($29)
    /* FD29C 001FD29C 3E74050C */  jal        ContinueCorrectPosition
    /* FD2A0 001FD2A0 F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FD2A4 001FD2A4 040041C4 */  lwc1       $f1, 0x4($2)
    /* FD2A8 001FD2A8 5C8B80C7 */  lwc1       $f0, %gp_rel(D_0062974C)($28)
    /* FD2AC 001FD2AC 34000146 */  c.lt.s     $f0, $f1
    /* FD2B0 001FD2B0 00000000 */  nop
    /* FD2B4 001FD2B4 04000045 */  bc1f       .L001FD2C8
    /* FD2B8 001FD2B8 4C00023C */   lui       $2, %hi(D_004C6ED0)
    /* FD2BC 001FD2BC D06E4224 */  addiu      $2, $2, %lo(D_004C6ED0)
    /* FD2C0 001FD2C0 38000010 */  b          .L001FD3A4
    /* FD2C4 001FD2C4 000022AE */   sw        $2, 0x0($17)
.align 2
  .L001FD2C8:
    /* FD2C8 001FD2C8 01000224 */  addiu      $2, $0, 0x1
    /* FD2CC 001FD2CC 25000216 */  bne        $16, $2, .L001FD364
    /* FD2D0 001FD2D0 4C00033C */   lui       $3, %hi(D_004C6F30)
    /* FD2D4 001FD2D4 4C00033C */  lui        $3, %hi(D_004C6F00)
    /* FD2D8 001FD2D8 4C00023C */  lui        $2, %hi(D_004C6EE0)
    /* FD2DC 001FD2DC 006F6624 */  addiu      $6, $3, %lo(D_004C6F00)
    /* FD2E0 001FD2E0 006F60C4 */  lwc1       $f0, %lo(D_004C6F00)($3)
    /* FD2E4 001FD2E4 0400C1C4 */  lwc1       $f1, 0x4($6)
    /* FD2E8 001FD2E8 E06E4224 */  addiu      $2, $2, %lo(D_004C6EE0)
    /* FD2EC 001FD2EC 0800C2C4 */  lwc1       $f2, 0x8($6)
    /* FD2F0 001FD2F0 4C00053C */  lui        $5, %hi(D_004C6F10)
    /* FD2F4 001FD2F4 000022AE */  sw         $2, 0x0($17)
    /* FD2F8 001FD2F8 106FA524 */  addiu      $5, $5, %lo(D_004C6F10)
    /* FD2FC 001FD2FC B000A0E7 */  swc1       $f0, 0xB0($29)
    /* FD300 001FD300 C000A427 */  addiu      $4, $29, 0xC0
    /* FD304 001FD304 B400A1E7 */  swc1       $f1, 0xB4($29)
    /* FD308 001FD308 F447060C */  jal        func_00191FD0
    /* FD30C 001FD30C B800A2E7 */   swc1      $f2, 0xB8($29)
    /* FD310 001FD310 22000010 */  b          .L001FD39C
    /* FD314 001FD314 000050AE */   sw        $16, 0x0($18)
.align 2
  .L001FD318:
    /* FD318 001FD318 9801A293 */  lbu        $2, 0x198($29)
    /* FD31C 001FD31C 08000324 */  addiu      $3, $0, 0x8
    /* FD320 001FD320 200562A2 */  sb         $2, 0x520($19)
    /* FD324 001FD324 9000A0C7 */  lwc1       $f0, 0x90($29)
    /* FD328 001FD328 9400A1C7 */  lwc1       $f1, 0x94($29)
    /* FD32C 001FD32C 9800A2C7 */  lwc1       $f2, 0x98($29)
    /* FD330 001FD330 A000A3C7 */  lwc1       $f3, 0xA0($29)
    /* FD334 001FD334 A400A4C7 */  lwc1       $f4, 0xA4($29)
    /* FD338 001FD338 A800A5C7 */  lwc1       $f5, 0xA8($29)
    /* FD33C 001FD33C 6000A0E6 */  swc1       $f0, 0x60($21)
    /* FD340 001FD340 6400A1E6 */  swc1       $f1, 0x64($21)
    /* FD344 001FD344 6800A2E6 */  swc1       $f2, 0x68($21)
    /* FD348 001FD348 7000A3E6 */  swc1       $f3, 0x70($21)
    /* FD34C 001FD34C 7400A4E6 */  swc1       $f4, 0x74($21)
    /* FD350 001FD350 7800A5E6 */  swc1       $f5, 0x78($21)
    /* FD354 001FD354 780462DE */  ld         $2, 0x478($19)
    /* FD358 001FD358 25104300 */  or         $2, $2, $3
    /* FD35C 001FD35C 67000010 */  b          .L001FD4FC
    /* FD360 001FD360 780462FE */   sd        $2, 0x478($19)
.align 2
  .L001FD364:
    /* FD364 001FD364 4C00023C */  lui        $2, %hi(D_004C6EF0)
    /* FD368 001FD368 306F6624 */  addiu      $6, $3, %lo(D_004C6F30)
    /* FD36C 001FD36C 306F60C4 */  lwc1       $f0, %lo(D_004C6F30)($3)
    /* FD370 001FD370 0400C1C4 */  lwc1       $f1, 0x4($6)
    /* FD374 001FD374 F06E4224 */  addiu      $2, $2, %lo(D_004C6EF0)
    /* FD378 001FD378 0800C2C4 */  lwc1       $f2, 0x8($6)
    /* FD37C 001FD37C 4C00053C */  lui        $5, %hi(D_004C6F20)
    /* FD380 001FD380 000022AE */  sw         $2, 0x0($17)
    /* FD384 001FD384 206FA524 */  addiu      $5, $5, %lo(D_004C6F20)
    /* FD388 001FD388 B000A0E7 */  swc1       $f0, 0xB0($29)
    /* FD38C 001FD38C C000A427 */  addiu      $4, $29, 0xC0
    /* FD390 001FD390 B400A1E7 */  swc1       $f1, 0xB4($29)
    /* FD394 001FD394 F447060C */  jal        func_00191FD0
    /* FD398 001FD398 B800A2E7 */   swc1      $f2, 0xB8($29)
.align 2
  .L001FD39C:
    /* FD39C 001FD39C 01000224 */  addiu      $2, $0, 0x1
    /* FD3A0 001FD3A0 0000C2AE */  sw         $2, 0x0($22)
.align 2
  .L001FD3A4:
    /* FD3A4 001FD3A4 9001A48F */  lw         $4, 0x190($29)
.align 2
  .L001FD3A8:
    /* FD3A8 001FD3A8 00088044 */  mtc1       $0, $f1
    /* FD3AC 001FD3AC 000080C4 */  lwc1       $f0, 0x0($4)
    /* FD3B0 001FD3B0 36080046 */  c.le.s     $f1, $f0
    /* FD3B4 001FD3B4 00000000 */  nop
    /* FD3B8 001FD3B8 50000045 */  bc1f       .L001FD4FC
    /* FD3BC 001FD3BC 2D800000 */   daddu     $16, $0, $0
    /* FD3C0 001FD3C0 9000B127 */  addiu      $17, $29, 0x90
    /* FD3C4 001FD3C4 2D180000 */  daddu      $3, $0, $0
    /* FD3C8 001FD3C8 21106400 */  addu       $2, $3, $4
    /* FD3CC 001FD3CC C401A58F */  lw         $5, 0x1C4($29)
.align 2
  .L001FD3D0:
    /* FD3D0 001FD3D0 00004DC4 */  lwc1       $f13, 0x0($2)
    /* FD3D4 001FD3D4 2D202002 */  daddu      $4, $17, $0
    /* FD3D8 001FD3D8 C801A68F */  lw         $6, 0x1C8($29)
    /* FD3DC 001FD3DC 1EE8070C */  jal        func_001FA078
    /* FD3E0 001FD3E0 06AB0046 */   mov.s     $f12, $f21
    /* FD3E4 001FD3E4 3B004010 */  beqz       $2, .L001FD4D4
    /* FD3E8 001FD3E8 A000A427 */   addiu     $4, $29, 0xA0
    /* FD3EC 001FD3EC 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FD3F0 001FD3F0 00608144 */  mtc1       $1, $f12
    /* FD3F4 001FD3F4 0E00090C */  jal        func_00240038
    /* FD3F8 001FD3F8 DC01A58F */   lw        $5, 0x1DC($29)
    /* FD3FC 001FD3FC 9401A28F */  lw         $2, 0x194($29)
    /* FD400 001FD400 0C004010 */  beqz       $2, .L001FD434
    /* FD404 001FD404 B000A0C7 */   lwc1      $f0, 0xB0($29)
    /* FD408 001FD408 B400A1C7 */  lwc1       $f1, 0xB4($29)
    /* FD40C 001FD40C B800A2C7 */  lwc1       $f2, 0xB8($29)
    /* FD410 001FD410 C000A3C7 */  lwc1       $f3, 0xC0($29)
    /* FD414 001FD414 C400A4C7 */  lwc1       $f4, 0xC4($29)
    /* FD418 001FD418 C800A5C7 */  lwc1       $f5, 0xC8($29)
    /* FD41C 001FD41C 9000A0E7 */  swc1       $f0, 0x90($29)
    /* FD420 001FD420 9400A1E7 */  swc1       $f1, 0x94($29)
    /* FD424 001FD424 9800A2E7 */  swc1       $f2, 0x98($29)
    /* FD428 001FD428 A000A3E7 */  swc1       $f3, 0xA0($29)
    /* FD42C 001FD42C A400A4E7 */  swc1       $f4, 0xA4($29)
    /* FD430 001FD430 A800A5E7 */  swc1       $f5, 0xA8($29)
.align 2
  .L001FD434:
    /* FD434 001FD434 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FD438 001FD438 00008144 */  mtc1       $1, $f0
    /* FD43C 001FD43C 34A80046 */  c.lt.s     $f21, $f0
    /* FD440 001FD440 00000000 */  nop
    /* FD444 001FD444 B4FF0145 */  bc1t       .L001FD318
    /* FD448 001FD448 D000B027 */   addiu     $16, $29, 0xD0
    /* FD44C 001FD44C F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FD450 001FD450 00A08144 */  mtc1       $1, $f20
    /* FD454 001FD454 DC01A58F */  lw         $5, 0x1DC($29)
    /* FD458 001FD458 2D200002 */  daddu      $4, $16, $0
    /* FD45C 001FD45C 0E00090C */  jal        func_00240038
    /* FD460 001FD460 01AB1446 */   sub.s     $f12, $f21, $f20
    /* FD464 001FD464 3000A38F */  lw         $3, 0x30($29)
    /* FD468 001FD468 2D300002 */  daddu      $6, $16, $0
    /* FD46C 001FD46C 1000A527 */  addiu      $5, $29, 0x10
    /* FD470 001FD470 6401628C */  lw         $2, 0x164($3)
    /* FD474 001FD474 7806448C */  lw         $4, 0x678($2)
    /* FD478 001FD478 FCFF080C */  jal        func_0023FFF0
    /* FD47C 001FD47C 80078424 */   addiu     $4, $4, 0x780
    /* FD480 001FD480 3000A48F */  lw         $4, 0x30($29)
    /* FD484 001FD484 14000524 */  addiu      $5, $0, 0x14
    /* FD488 001FD488 1000A0C6 */  lwc1       $f0, 0x10($21)
    /* FD48C 001FD48C 00800634 */  ori        $6, $0, 0x8000
    /* FD490 001FD490 3C340600 */  dsll32     $6, $6, 16
    /* FD494 001FD494 6401828C */  lw         $2, 0x164($4)
    /* FD498 001FD498 7806438C */  lw         $3, 0x678($2)
    /* FD49C 001FD49C 900760E4 */  swc1       $f0, 0x790($3)
    /* FD4A0 001FD4A0 A40765AC */  sw         $5, 0x7A4($3)
    /* FD4A4 001FD4A4 1400A0C6 */  lwc1       $f0, 0x14($21)
    /* FD4A8 001FD4A8 6401828C */  lw         $2, 0x164($4)
    /* FD4AC 001FD4AC 940760E4 */  swc1       $f0, 0x794($3)
    /* FD4B0 001FD4B0 7806448C */  lw         $4, 0x678($2)
    /* FD4B4 001FD4B4 1800A0C6 */  lwc1       $f0, 0x18($21)
    /* FD4B8 001FD4B8 A00774E4 */  swc1       $f20, 0x7A0($3)
    /* FD4BC 001FD4BC 980760E4 */  swc1       $f0, 0x798($3)
    /* FD4C0 001FD4C0 A80780AC */  sw         $0, 0x7A8($4)
    /* FD4C4 001FD4C4 680462DE */  ld         $2, 0x468($19)
    /* FD4C8 001FD4C8 25104600 */  or         $2, $2, $6
    /* FD4CC 001FD4CC 0B000010 */  b          .L001FD4FC
    /* FD4D0 001FD4D0 680462FE */   sd        $2, 0x468($19)
.align 2
  .L001FD4D4:
    /* FD4D4 001FD4D4 01001026 */  addiu      $16, $16, 0x1
    /* FD4D8 001FD4D8 9001A48F */  lw         $4, 0x190($29)
    /* FD4DC 001FD4DC 80181000 */  sll        $3, $16, 2
    /* FD4E0 001FD4E0 00088044 */  mtc1       $0, $f1
    /* FD4E4 001FD4E4 21106400 */  addu       $2, $3, $4
    /* FD4E8 001FD4E8 000040C4 */  lwc1       $f0, 0x0($2)
    /* FD4EC 001FD4EC 36080046 */  c.le.s     $f1, $f0
    /* FD4F0 001FD4F0 00000000 */  nop
    /* FD4F4 001FD4F4 B6FF0145 */  bc1t       .L001FD3D0
    /* FD4F8 001FD4F8 C401A58F */   lw        $5, 0x1C4($29)
.align 2
  .L001FD4FC:
    /* FD4FC 001FD4FC 0800828E */  lw         $2, 0x8($20)
.align 2
  .L001FD500:
    /* FD500 001FD500 82150200 */  srl        $2, $2, 22
    /* FD504 001FD504 01004230 */  andi       $2, $2, 0x1
    /* FD508 001FD508 09004010 */  beqz       $2, .L001FD530
    /* FD50C 001FD50C 00000000 */   nop
    /* FD510 001FD510 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FD514 001FD514 00008144 */  mtc1       $1, $f0
    /* FD518 001FD518 34A80046 */  c.lt.s     $f21, $f0
    /* FD51C 001FD51C 00000000 */  nop
    /* FD520 001FD520 0A000345 */  bc1tl      .L001FD54C
    /* FD524 001FD524 1000A2C6 */   lwc1      $f2, 0x10($21)
    /* FD528 001FD528 8E000010 */  b          .L001FD764
    /* FD52C 001FD52C 3000A48F */   lw        $4, 0x30($29)
.align 2
  .L001FD530:
    /* FD530 001FD530 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FD534 001FD534 00008144 */  mtc1       $1, $f0
    /* FD538 001FD538 34A80046 */  c.lt.s     $f21, $f0
    /* FD53C 001FD53C 00000000 */  nop
    /* FD540 001FD540 88000245 */  bc1fl      .L001FD764
    /* FD544 001FD544 3000A48F */   lw        $4, 0x30($29)
    /* FD548 001FD548 1000A2C6 */  lwc1       $f2, 0x10($21)
.align 2
  .L001FD54C:
    /* FD54C 001FD54C 9000B727 */  addiu      $23, $29, 0x90
    /* FD550 001FD550 1400A1C6 */  lwc1       $f1, 0x14($21)
    /* FD554 001FD554 2D20E002 */  daddu      $4, $23, $0
    /* FD558 001FD558 1800A0C6 */  lwc1       $f0, 0x18($21)
    /* FD55C 001FD55C 2DB00000 */  daddu      $22, $0, $0
    /* FD560 001FD560 608B8CC7 */  lwc1       $f12, %gp_rel(D_00629750)($28)
    /* FD564 001FD564 9000A2E7 */  swc1       $f2, 0x90($29)
    /* FD568 001FD568 9400A1E7 */  swc1       $f1, 0x94($29)
    /* FD56C 001FD56C 6E47060C */  jal        func_00191DB8
    /* FD570 001FD570 9800A0E7 */   swc1      $f0, 0x98($29)
    /* FD574 001FD574 8EF9040C */  jal        isysGObjSearchFromObjLayoutID
    /* FD578 001FD578 15000424 */   addiu     $4, $0, 0x15
    /* FD57C 001FD57C 2D804000 */  daddu      $16, $2, $0
    /* FD580 001FD580 41000012 */  beqz       $16, .L001FD688
    /* FD584 001FD584 C001A58F */   lw        $5, 0x1C0($29)
    /* FD588 001FD588 648B98C7 */  lwc1       $f24, %gp_rel(D_00629754)($28)
    /* FD58C 001FD58C B000B127 */  addiu      $17, $29, 0xB0
    /* FD590 001FD590 00B88044 */  mtc1       $0, $f23
    /* FD594 001FD594 A000B227 */  addiu      $18, $29, 0xA0
    /* FD598 001FD598 8C42013C */  lui        $1, (0x428C0000 >> 16)
    /* FD59C 001FD59C 00B08144 */  mtc1       $1, $f22
    /* FD5A0 001FD5A0 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FD5A4 001FD5A4 00A88144 */  mtc1       $1, $f21
    /* FD5A8 001FD5A8 6C01028E */  lw         $2, 0x16C($16)
    /* FD5AC 001FD5AC 00000000 */  nop
.align 2
  .L001FD5B0:
    /* FD5B0 001FD5B0 2F004010 */  beqz       $2, .L001FD670
    /* FD5B4 001FD5B4 2D202002 */   daddu     $4, $17, $0
    /* FD5B8 001FD5B8 C210040C */  jal        GetRootMatrixByDObj
    /* FD5BC 001FD5BC 2D280002 */   daddu     $5, $16, $0
    /* FD5C0 001FD5C0 2D204002 */  daddu      $4, $18, $0
    /* FD5C4 001FD5C4 2D282002 */  daddu      $5, $17, $0
    /* FD5C8 001FD5C8 0200090C */  jal        func_00240008
    /* FD5CC 001FD5CC 2D30A003 */   daddu     $6, $29, $0
    /* FD5D0 001FD5D0 2D204002 */  daddu      $4, $18, $0
    /* FD5D4 001FD5D4 9CFF080C */  jal        func_0023FE70
    /* FD5D8 001FD5D8 2D28E002 */   daddu     $5, $23, $0
    /* FD5DC 001FD5DC 06050046 */  mov.s      $f20, $f0
    /* FD5E0 001FD5E0 2D20A003 */  daddu      $4, $29, $0
    /* FD5E4 001FD5E4 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FD5E8 001FD5E8 2D282002 */   daddu     $5, $17, $0
    /* FD5EC 001FD5EC 34001846 */  c.lt.s     $f0, $f24
    /* FD5F0 001FD5F0 00000000 */  nop
    /* FD5F4 001FD5F4 1E000045 */  bc1f       .L001FD670
    /* FD5F8 001FD5F8 0400A1C7 */   lwc1      $f1, 0x4($29)
    /* FD5FC 001FD5FC B400A0C7 */  lwc1       $f0, 0xB4($29)
    /* FD600 001FD600 01080046 */  sub.s      $f0, $f1, $f0
    /* FD604 001FD604 34001746 */  c.lt.s     $f0, $f23
    /* FD608 001FD608 07000045 */  bc1f       .L001FD628
    /* FD60C 001FD60C 00000000 */   nop
    /* FD610 001FD610 07000046 */  neg.s      $f0, $f0
    /* FD614 001FD614 34001646 */  c.lt.s     $f0, $f22
    /* FD618 001FD618 06000145 */  bc1t       .L001FD634
    /* FD61C 001FD61C 00000000 */   nop
    /* FD620 001FD620 13000010 */  b          .L001FD670
    /* FD624 001FD624 00000000 */   nop
.align 2
  .L001FD628:
    /* FD628 001FD628 34001646 */  c.lt.s     $f0, $f22
    /* FD62C 001FD62C 10000045 */  bc1f       .L001FD670
    /* FD630 001FD630 00000000 */   nop
.align 2
  .L001FD634:
    /* FD634 001FD634 34A01746 */  c.lt.s     $f20, $f23
    /* FD638 001FD638 08000045 */  bc1f       .L001FD65C
    /* FD63C 001FD63C 00000000 */   nop
    /* FD640 001FD640 07A00046 */  neg.s      $f0, $f20
    /* FD644 001FD644 34001546 */  c.lt.s     $f0, $f21
    /* FD648 001FD648 00000000 */  nop
    /* FD64C 001FD64C 0D000345 */  bc1tl      .L001FD684
    /* FD650 001FD650 2DB00002 */   daddu     $22, $16, $0
    /* FD654 001FD654 06000010 */  b          .L001FD670
    /* FD658 001FD658 00000000 */   nop
.align 2
  .L001FD65C:
    /* FD65C 001FD65C 34A01546 */  c.lt.s     $f20, $f21
    /* FD660 001FD660 03000045 */  bc1f       .L001FD670
    /* FD664 001FD664 00000000 */   nop
    /* FD668 001FD668 06000010 */  b          .L001FD684
    /* FD66C 001FD66C 2DB00002 */   daddu     $22, $16, $0
.align 2
  .L001FD670:
    /* FD670 001FD670 B2F9040C */  jal        isysGObjSearchFromObjKindID_begin
    /* FD674 001FD674 2D200002 */   daddu     $4, $16, $0
    /* FD678 001FD678 2D804000 */  daddu      $16, $2, $0
    /* FD67C 001FD67C CCFF0056 */  bnel       $16, $0, .L001FD5B0
    /* FD680 001FD680 6C01028E */   lw        $2, 0x16C($16)
.align 2
  .L001FD684:
    /* FD684 001FD684 C001A58F */  lw         $5, 0x1C0($29)
.align 2
  .L001FD688:
    /* FD688 001FD688 1000A010 */  beqz       $5, .L001FD6CC
    /* FD68C 001FD68C C000B027 */   addiu     $16, $29, 0xC0
    /* FD690 001FD690 3E74050C */  jal        ContinueCorrectPosition
    /* FD694 001FD694 2D20A000 */   daddu     $4, $5, $0
    /* FD698 001FD698 C401A68F */  lw         $6, 0x1C4($29)
    /* FD69C 001FD69C 2D284000 */  daddu      $5, $2, $0
    /* FD6A0 001FD6A0 0200090C */  jal        func_00240008
    /* FD6A4 001FD6A4 2D200002 */   daddu     $4, $16, $0
    /* FD6A8 001FD6A8 C801A58F */  lw         $5, 0x1C8($29)
    /* FD6AC 001FD6AC 2D200002 */  daddu      $4, $16, $0
    /* FD6B0 001FD6B0 9CFF080C */  jal        func_0023FE70
    /* FD6B4 001FD6B4 C400A0AF */   sw        $0, 0xC4($29)
    /* FD6B8 001FD6B8 00088044 */  mtc1       $0, $f1
    /* FD6BC 001FD6BC 34080046 */  c.lt.s     $f1, $f0
    /* FD6C0 001FD6C0 00000000 */  nop
    /* FD6C4 001FD6C4 01000345 */  bc1tl      .L001FD6CC
    /* FD6C8 001FD6C8 C001B68F */   lw        $22, 0x1C0($29)
.align 2
  .L001FD6CC:
    /* FD6CC 001FD6CC 2400C012 */  beqz       $22, .L001FD760
    /* FD6D0 001FD6D0 2D20C002 */   daddu     $4, $22, $0
    /* FD6D4 001FD6D4 700462DE */  ld         $2, 0x470($19)
    /* FD6D8 001FD6D8 00800334 */  ori        $3, $0, 0x8000
    /* FD6DC 001FD6DC BC190300 */  dsll32     $3, $3, 6
    /* FD6E0 001FD6E0 25104300 */  or         $2, $2, $3
    /* FD6E4 001FD6E4 700462FE */  sd         $2, 0x470($19)
    /* FD6E8 001FD6E8 3E74050C */  jal        ContinueCorrectPosition
    /* FD6EC 001FD6EC 5C01B6AE */   sw        $22, 0x15C($21)
    /* FD6F0 001FD6F0 000040C4 */  lwc1       $f0, 0x0($2)
    /* FD6F4 001FD6F4 2D20C002 */  daddu      $4, $22, $0
    /* FD6F8 001FD6F8 3E74050C */  jal        ContinueCorrectPosition
    /* FD6FC 001FD6FC E000A0E7 */   swc1      $f0, 0xE0($29)
    /* FD700 001FD700 040040C4 */  lwc1       $f0, 0x4($2)
    /* FD704 001FD704 2D20C002 */  daddu      $4, $22, $0
    /* FD708 001FD708 3E74050C */  jal        ContinueCorrectPosition
    /* FD70C 001FD70C E400A0E7 */   swc1      $f0, 0xE4($29)
    /* FD710 001FD710 080040C4 */  lwc1       $f0, 0x8($2)
    /* FD714 001FD714 D000B027 */  addiu      $16, $29, 0xD0
    /* FD718 001FD718 A0C1013C */  lui        $1, (0xC1A00000 >> 16)
    /* FD71C 001FD71C 00608144 */  mtc1       $1, $f12
    /* FD720 001FD720 2D200002 */  daddu      $4, $16, $0
    /* FD724 001FD724 C801A58F */  lw         $5, 0x1C8($29)
    /* FD728 001FD728 0E00090C */  jal        func_00240038
    /* FD72C 001FD72C E800A0E7 */   swc1      $f0, 0xE8($29)
    /* FD730 001FD730 3000A38F */  lw         $3, 0x30($29)
    /* FD734 001FD734 2D300002 */  daddu      $6, $16, $0
    /* FD738 001FD738 E000A527 */  addiu      $5, $29, 0xE0
    /* FD73C 001FD73C 6401628C */  lw         $2, 0x164($3)
    /* FD740 001FD740 7006448C */  lw         $4, 0x670($2)
    /* FD744 001FD744 FCFF080C */  jal        func_0023FFF0
    /* FD748 001FD748 C0018424 */   addiu     $4, $4, 0x1C0
    /* FD74C 001FD74C 3000A48F */  lw         $4, 0x30($29)
    /* FD750 001FD750 1400A0C7 */  lwc1       $f0, 0x14($29)
    /* FD754 001FD754 6401828C */  lw         $2, 0x164($4)
    /* FD758 001FD758 7006438C */  lw         $3, 0x670($2)
    /* FD75C 001FD75C C40160E4 */  swc1       $f0, 0x1C4($3)
.align 2
  .L001FD760:
    /* FD760 001FD760 3000A48F */  lw         $4, 0x30($29)
.align 2
  .L001FD764:
    /* FD764 001FD764 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FD768 001FD768 00020524 */   addiu     $5, $0, 0x200
    /* FD76C 001FD76C 3000A78F */  lw         $7, 0x30($29)
    /* FD770 001FD770 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FD774 001FD774 3600E514 */  bne        $7, $5, .L001FD850
    /* FD778 001FD778 3000668E */   lw        $6, 0x30($19)
    /* FD77C 001FD77C 45000224 */  addiu      $2, $0, 0x45
    /* FD780 001FD780 3300C214 */  bne        $6, $2, .L001FD850
    /* FD784 001FD784 F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FD788 001FD788 6629040C */  jal        EnableChangeRootUpdateMode
    /* FD78C 001FD78C 2D28E000 */   daddu     $5, $7, $0
    /* FD790 001FD790 700466DE */  ld         $6, 0x470($19)
    /* FD794 001FD794 78150600 */  dsll       $2, $6, 21
    /* FD798 001FD798 3F100200 */  dsra32     $2, $2, 0
    /* FD79C 001FD79C 01004230 */  andi       $2, $2, 0x1
    /* FD7A0 001FD7A0 0F004010 */  beqz       $2, .L001FD7E0
    /* FD7A4 001FD7A4 47000046 */   neg.s     $f1, $f0
    /* FD7A8 001FD7A8 A040013C */  lui        $1, (0x40A00000 >> 16)
    /* FD7AC 001FD7AC 00008144 */  mtc1       $1, $f0
    /* FD7B0 001FD7B0 34000146 */  c.lt.s     $f0, $f1
    /* FD7B4 001FD7B4 00000000 */  nop
    /* FD7B8 001FD7B8 09000045 */  bc1f       .L001FD7E0
    /* FD7BC 001FD7BC 02000424 */   addiu     $4, $0, 0x2
    /* FD7C0 001FD7C0 780462DE */  ld         $2, 0x478($19)
    /* FD7C4 001FD7C4 00800334 */  ori        $3, $0, 0x8000
    /* FD7C8 001FD7C8 BC1B0300 */  dsll32     $3, $3, 14
    /* FD7CC 001FD7CC 2518C300 */  or         $3, $6, $3
    /* FD7D0 001FD7D0 25104400 */  or         $2, $2, $4
    /* FD7D4 001FD7D4 700463FE */  sd         $3, 0x470($19)
    /* FD7D8 001FD7D8 780462FE */  sd         $2, 0x478($19)
    /* FD7DC 001FD7DC 2D306000 */  daddu      $6, $3, $0
.align 2
  .L001FD7E0:
    /* FD7E0 001FD7E0 38150600 */  dsll       $2, $6, 20
    /* FD7E4 001FD7E4 3F100200 */  dsra32     $2, $2, 0
    /* FD7E8 001FD7E8 01004230 */  andi       $2, $2, 0x1
    /* FD7EC 001FD7EC 0F004010 */  beqz       $2, .L001FD82C
    /* FD7F0 001FD7F0 00000000 */   nop
    /* FD7F4 001FD7F4 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FD7F8 001FD7F8 00008144 */  mtc1       $1, $f0
    /* FD7FC 001FD7FC 34000146 */  c.lt.s     $f0, $f1
    /* FD800 001FD800 00000000 */  nop
    /* FD804 001FD804 09000045 */  bc1f       .L001FD82C
    /* FD808 001FD808 F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FD80C 001FD80C 37000524 */  addiu      $5, $0, 0x37
    /* FD810 001FD810 6401828C */  lw         $2, 0x164($4)
    /* FD814 001FD814 3000438C */  lw         $3, 0x30($2)
    /* FD818 001FD818 04006514 */  bne        $3, $5, .L001FD82C
    /* FD81C 001FD81C 04000324 */   addiu     $3, $0, 0x4
    /* FD820 001FD820 780462DE */  ld         $2, 0x478($19)
    /* FD824 001FD824 25104300 */  or         $2, $2, $3
    /* FD828 001FD828 780462FE */  sd         $2, 0x478($19)
.align 2
  .L001FD82C:
    /* FD82C 001FD82C F8140600 */  dsll       $2, $6, 19
    /* FD830 001FD830 3F100200 */  dsra32     $2, $2, 0
    /* FD834 001FD834 01004230 */  andi       $2, $2, 0x1
    /* FD838 001FD838 04004010 */  beqz       $2, .L001FD84C
    /* FD83C 001FD83C F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FD840 001FD840 4343013C */  lui        $1, (0x43430000 >> 16)
    /* FD844 001FD844 00008144 */  mtc1       $1, $f0
    /* FD848 001FD848 34000146 */  c.lt.s     $f0, $f1
.align 2
  .L001FD84C:
    /* FD84C 001FD84C 3000668E */  lw         $6, 0x30($19)
.align 2
  .L001FD850:
    /* FD850 001FD850 0700A050 */  beql       $5, $0, .L001FD870
    /* FD854 001FD854 6001628E */   lw        $2, 0x160($19)
    /* FD858 001FD858 680462DE */  ld         $2, 0x468($19)
    /* FD85C 001FD85C 00800334 */  ori        $3, $0, 0x8000
    /* FD860 001FD860 B81F0300 */  dsll       $3, $3, 30
    /* FD864 001FD864 25104300 */  or         $2, $2, $3
    /* FD868 001FD868 680462FE */  sd         $2, 0x468($19)
    /* FD86C 001FD86C 6001628E */  lw         $2, 0x160($19)
.align 2
  .L001FD870:
    /* FD870 001FD870 07004010 */  beqz       $2, .L001FD890
    /* FD874 001FD874 3000A38F */   lw        $3, 0x30($29)
    /* FD878 001FD878 700462DE */  ld         $2, 0x470($19)
    /* FD87C 001FD87C 00800334 */  ori        $3, $0, 0x8000
    /* FD880 001FD880 B81D0300 */  dsll       $3, $3, 22
    /* FD884 001FD884 25104300 */  or         $2, $2, $3
    /* FD888 001FD888 700462FE */  sd         $2, 0x470($19)
    /* FD88C 001FD88C 3000A38F */  lw         $3, 0x30($29)
.align 2
  .L001FD890:
    /* FD890 001FD890 F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* FD894 001FD894 52006214 */  bne        $3, $2, .L001FD9E0
    /* FD898 001FD898 3B00C22C */   sltiu     $2, $6, 0x3B
    /* FD89C 001FD89C 0E000224 */  addiu      $2, $0, 0xE
    /* FD8A0 001FD8A0 4F00C210 */  beq        $6, $2, .L001FD9E0
    /* FD8A4 001FD8A4 3B00C22C */   sltiu     $2, $6, 0x3B
    /* FD8A8 001FD8A8 3001648E */  lw         $4, 0x130($19)
    /* FD8AC 001FD8AC 07008010 */  beqz       $4, .L001FD8CC
    /* FD8B0 001FD8B0 00000000 */   nop
    /* FD8B4 001FD8B4 1643013C */  lui        $1, (0x43160000 >> 16)
    /* FD8B8 001FD8B8 00608144 */  mtc1       $1, $f12
    /* FD8BC 001FD8BC E8C3070C */  jal        WeaponHitEffect
    /* FD8C0 001FD8C0 00000000 */   nop
    /* FD8C4 001FD8C4 06000010 */  b          .L001FD8E0
    /* FD8C8 001FD8C8 2D804000 */   daddu     $16, $2, $0
.align 2
  .L001FD8CC:
    /* FD8CC 001FD8CC 1643013C */  lui        $1, (0x43160000 >> 16)
    /* FD8D0 001FD8D0 00608144 */  mtc1       $1, $f12
    /* FD8D4 001FD8D4 E8C3070C */  jal        WeaponHitEffect
    /* FD8D8 001FD8D8 2D206000 */   daddu     $4, $3, $0
    /* FD8DC 001FD8DC 2D804000 */  daddu      $16, $2, $0
.align 2
  .L001FD8E0:
    /* FD8E0 001FD8E0 3D000012 */  beqz       $16, .L001FD9D8
    /* FD8E4 001FD8E4 2D200002 */   daddu     $4, $16, $0
    /* FD8E8 001FD8E8 5801B0AE */  sw         $16, 0x158($21)
    /* FD8EC 001FD8EC 00800334 */  ori        $3, $0, 0x8000
    /* FD8F0 001FD8F0 7C190300 */  dsll32     $3, $3, 5
    /* FD8F4 001FD8F4 680462DE */  ld         $2, 0x468($19)
    /* FD8F8 001FD8F8 25104300 */  or         $2, $2, $3
    /* FD8FC 001FD8FC 3E74050C */  jal        ContinueCorrectPosition
    /* FD900 001FD900 680462FE */   sd        $2, 0x468($19)
    /* FD904 001FD904 000040C4 */  lwc1       $f0, 0x0($2)
    /* FD908 001FD908 2D200002 */  daddu      $4, $16, $0
    /* FD90C 001FD90C 3E74050C */  jal        ContinueCorrectPosition
    /* FD910 001FD910 6000A0E7 */   swc1      $f0, 0x60($29)
    /* FD914 001FD914 040040C4 */  lwc1       $f0, 0x4($2)
    /* FD918 001FD918 2D200002 */  daddu      $4, $16, $0
    /* FD91C 001FD91C 3E74050C */  jal        ContinueCorrectPosition
    /* FD920 001FD920 6400A0E7 */   swc1      $f0, 0x64($29)
    /* FD924 001FD924 080040C4 */  lwc1       $f0, 0x8($2)
    /* FD928 001FD928 7000B127 */  addiu      $17, $29, 0x70
    /* FD92C 001FD92C 6000B227 */  addiu      $18, $29, 0x60
    /* FD930 001FD930 C401A68F */  lw         $6, 0x1C4($29)
    /* FD934 001FD934 2D202002 */  daddu      $4, $17, $0
    /* FD938 001FD938 2D284002 */  daddu      $5, $18, $0
    /* FD93C 001FD93C F447060C */  jal        func_00191FD0
    /* FD940 001FD940 6800A0E7 */   swc1      $f0, 0x68($29)
    /* FD944 001FD944 A801A58F */  lw         $5, 0x1A8($29)
    /* FD948 001FD948 6447060C */  jal        func_00191D90
    /* FD94C 001FD94C 2D202002 */   daddu     $4, $17, $0
    /* FD950 001FD950 2D004228 */  slti       $2, $2, 0x2D
    /* FD954 001FD954 09004010 */  beqz       $2, .L001FD97C
    /* FD958 001FD958 2D204002 */   daddu     $4, $18, $0
    /* FD95C 001FD95C D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FD960 001FD960 1000A527 */   addiu     $5, $29, 0x10
    /* FD964 001FD964 C845013C */  lui        $1, (0x45C80000 >> 16)
    /* FD968 001FD968 00088144 */  mtc1       $1, $f1
    /* FD96C 001FD96C 34000146 */  c.lt.s     $f0, $f1
    /* FD970 001FD970 00000000 */  nop
    /* FD974 001FD974 11000345 */  bc1tl      .L001FD9BC
    /* FD978 001FD978 680462DE */   ld        $2, 0x468($19)
.align 2
  .L001FD97C:
    /* FD97C 001FD97C A801A58F */  lw         $5, 0x1A8($29)
    /* FD980 001FD980 6447060C */  jal        func_00191D90
    /* FD984 001FD984 2D202002 */   daddu     $4, $17, $0
    /* FD988 001FD988 2D004228 */  slti       $2, $2, 0x2D
    /* FD98C 001FD98C 13004054 */  bnel       $2, $0, .L001FD9DC
    /* FD990 001FD990 3000668E */   lw        $6, 0x30($19)
    /* FD994 001FD994 2D204002 */  daddu      $4, $18, $0
    /* FD998 001FD998 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FD99C 001FD99C 1000A527 */   addiu     $5, $29, 0x10
    /* FD9A0 001FD9A0 6144013C */  lui        $1, (0x44610000 >> 16)
    /* FD9A4 001FD9A4 00088144 */  mtc1       $1, $f1
    /* FD9A8 001FD9A8 34000146 */  c.lt.s     $f0, $f1
    /* FD9AC 001FD9AC 00000000 */  nop
    /* FD9B0 001FD9B0 0A000245 */  bc1fl      .L001FD9DC
    /* FD9B4 001FD9B4 3000668E */   lw        $6, 0x30($19)
    /* FD9B8 001FD9B8 680462DE */  ld         $2, 0x468($19)
.align 2
  .L001FD9BC:
    /* FD9BC 001FD9BC 00800334 */  ori        $3, $0, 0x8000
    /* FD9C0 001FD9C0 3C190300 */  dsll32     $3, $3, 4
    /* FD9C4 001FD9C4 3000668E */  lw         $6, 0x30($19)
    /* FD9C8 001FD9C8 25104300 */  or         $2, $2, $3
    /* FD9CC 001FD9CC 680462FE */  sd         $2, 0x468($19)
    /* FD9D0 001FD9D0 02000010 */  b          .L001FD9DC
    /* FD9D4 001FD9D4 5801B0AE */   sw        $16, 0x158($21)
.align 2
  .L001FD9D8:
    /* FD9D8 001FD9D8 3000668E */  lw         $6, 0x30($19)
.align 2
  .L001FD9DC:
    /* FD9DC 001FD9DC 3B00C22C */  sltiu      $2, $6, 0x3B
.align 2
  .L001FD9E0:
    /* FD9E0 001FD9E0 16004010 */  beqz       $2, .L001FDA3C
    /* FD9E4 001FD9E4 3900C22C */   sltiu     $2, $6, 0x39
    /* FD9E8 001FD9E8 15004014 */  bnez       $2, .L001FDA40
    /* FD9EC 001FD9EC 3000A38F */   lw        $3, 0x30($29)
    /* FD9F0 001FD9F0 8001648E */  lw         $4, 0x180($19)
    /* FD9F4 001FD9F4 9C01A527 */  addiu      $5, $29, 0x19C
    /* FD9F8 001FD9F8 A001A627 */  addiu      $6, $29, 0x1A0
    /* FD9FC 001FD9FC F636060C */  jal        isStopChain
    /* FDA00 001FDA00 A401A727 */   addiu     $7, $29, 0x1A4
    /* FDA04 001FDA04 9C01A1C7 */  lwc1       $f1, 0x19C($29)
    /* FDA08 001FDA08 00008044 */  mtc1       $0, $f0
    /* FDA0C 001FDA0C 34000146 */  c.lt.s     $f0, $f1
    /* FDA10 001FDA10 00000000 */  nop
    /* FDA14 001FDA14 05000045 */  bc1f       .L001FDA2C
    /* FDA18 001FDA18 700462DE */   ld        $2, 0x470($19)
    /* FDA1C 001FDA1C 00800334 */  ori        $3, $0, 0x8000
    /* FDA20 001FDA20 3C190300 */  dsll32     $3, $3, 4
    /* FDA24 001FDA24 04000010 */  b          .L001FDA38
    /* FDA28 001FDA28 25104300 */   or        $2, $2, $3
.align 2
  .L001FDA2C:
    /* FDA2C 001FDA2C 00800334 */  ori        $3, $0, 0x8000
    /* FDA30 001FDA30 7C190300 */  dsll32     $3, $3, 5
    /* FDA34 001FDA34 25104300 */  or         $2, $2, $3
.align 2
  .L001FDA38:
    /* FDA38 001FDA38 700462FE */  sd         $2, 0x470($19)
.align 2
  .L001FDA3C:
    /* FDA3C 001FDA3C 3000A38F */  lw         $3, 0x30($29)
.align 2
  .L001FDA40:
    /* FDA40 001FDA40 F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* FDA44 001FDA44 32006214 */  bne        $3, $2, .L001FDB10
    /* FDA48 001FDA48 3000A48F */   lw        $4, 0x30($29)
    /* FDA4C 001FDA4C F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
    /* FDA50 001FDA50 2F004010 */  beqz       $2, .L001FDB10
    /* FDA54 001FDA54 6B000324 */   addiu     $3, $0, 0x6B
    /* FDA58 001FDA58 6401448C */  lw         $4, 0x164($2)
    /* FDA5C 001FDA5C 3000828C */  lw         $2, 0x30($4)
    /* FDA60 001FDA60 2B004354 */  bnel       $2, $3, .L001FDB10
    /* FDA64 001FDA64 3000A48F */   lw        $4, 0x30($29)
    /* FDA68 001FDA68 2401858C */  lw         $5, 0x124($4)
    /* FDA6C 001FDA6C 64000224 */  addiu      $2, $0, 0x64
    /* FDA70 001FDA70 6401A38C */  lw         $3, 0x164($5)
    /* FDA74 001FDA74 3000648C */  lw         $4, 0x30($3)
    /* FDA78 001FDA78 25008214 */  bne        $4, $2, .L001FDB10
    /* FDA7C 001FDA7C 3000A48F */   lw        $4, 0x30($29)
    /* FDA80 001FDA80 5E29040C */  jal        GetDifferenceFromWallUpperPlane
    /* FDA84 001FDA84 2D20A000 */   daddu     $4, $5, $0
    /* FDA88 001FDA88 20004010 */  beqz       $2, .L001FDB0C
    /* FDA8C 001FDA8C 3000A48F */   lw        $4, 0x30($29)
    /* FDA90 001FDA90 78000624 */  addiu      $6, $0, 0x78
    /* FDA94 001FDA94 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FDA98 001FDA98 4843013C */  lui        $1, (0x43480000 >> 16)
    /* FDA9C 001FDA9C 00608144 */  mtc1       $1, $f12
    /* FDAA0 001FDAA0 C843013C */  lui        $1, (0x43C80000 >> 16)
    /* FDAA4 001FDAA4 00688144 */  mtc1       $1, $f13
    /* FDAA8 001FDAA8 780F050C */  jal        func_00143DE0
    /* FDAAC 001FDAAC 6000A727 */   addiu     $7, $29, 0x60
    /* FDAB0 001FDAB0 16004010 */  beqz       $2, .L001FDB0C
    /* FDAB4 001FDAB4 C401A48F */   lw        $4, 0x1C4($29)
    /* FDAB8 001FDAB8 9A26050C */  jal        PAIR_GetPosition_BOY
    /* FDABC 001FDABC 21000524 */   addiu     $5, $0, 0x21
    /* FDAC0 001FDAC0 2D804000 */  daddu      $16, $2, $0
    /* FDAC4 001FDAC4 3E74050C */  jal        ContinueCorrectPosition
    /* FDAC8 001FDAC8 2D200002 */   daddu     $4, $16, $0
    /* FDACC 001FDACC C401A48F */  lw         $4, 0x1C4($29)
    /* FDAD0 001FDAD0 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FDAD4 001FDAD4 2D284000 */   daddu     $5, $2, $0
    /* FDAD8 001FDAD8 688B81C7 */  lwc1       $f1, %gp_rel(D_00629758)($28)
    /* FDADC 001FDADC 34000146 */  c.lt.s     $f0, $f1
    /* FDAE0 001FDAE0 00000000 */  nop
    /* FDAE4 001FDAE4 09000045 */  bc1f       .L001FDB0C
    /* FDAE8 001FDAE8 3000A48F */   lw        $4, 0x30($29)
    /* FDAEC 001FDAEC 680462DE */  ld         $2, 0x468($19)
    /* FDAF0 001FDAF0 00800334 */  ori        $3, $0, 0x8000
    /* FDAF4 001FDAF4 BC190300 */  dsll32     $3, $3, 6
    /* FDAF8 001FDAF8 25104300 */  or         $2, $2, $3
    /* FDAFC 001FDAFC 680462FE */  sd         $2, 0x468($19)
    /* FDB00 001FDB00 6401838C */  lw         $3, 0x164($4)
    /* FDB04 001FDB04 7006628C */  lw         $2, 0x670($3)
    /* FDB08 001FDB08 E00250AC */  sw         $16, 0x2E0($2)
.align 2
  .L001FDB0C:
    /* FDB0C 001FDB0C 3000A48F */  lw         $4, 0x30($29)
.align 2
  .L001FDB10:
    /* FDB10 001FDB10 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FDB14 001FDB14 00080524 */   addiu     $5, $0, 0x800
    /* FDB18 001FDB18 07004054 */  bnel       $2, $0, .L001FDB38
    /* FDB1C 001FDB1C 700462DE */   ld        $2, 0x470($19)
    /* FDB20 001FDB20 3000A48F */  lw         $4, 0x30($29)
    /* FDB24 001FDB24 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FDB28 001FDB28 00090524 */   addiu     $5, $0, 0x900
    /* FDB2C 001FDB2C 06004010 */  beqz       $2, .L001FDB48
    /* FDB30 001FDB30 3000A48F */   lw        $4, 0x30($29)
    /* FDB34 001FDB34 700462DE */  ld         $2, 0x470($19)
.align 2
  .L001FDB38:
    /* FDB38 001FDB38 00010324 */  addiu      $3, $0, 0x100
    /* FDB3C 001FDB3C 25104300 */  or         $2, $2, $3
    /* FDB40 001FDB40 700462FE */  sd         $2, 0x470($19)
    /* FDB44 001FDB44 3000A48F */  lw         $4, 0x30($29)
.align 2
  .L001FDB48:
    /* FDB48 001FDB48 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FDB4C 001FDB4C 8000053C */   lui       $5, (0x800000 >> 16)
    /* FDB50 001FDB50 29004010 */  beqz       $2, .L001FDBF8
    /* FDB54 001FDB54 3000A28F */   lw        $2, 0x30($29)
    /* FDB58 001FDB58 6000B027 */  addiu      $16, $29, 0x60
    /* FDB5C 001FDB5C 2D200002 */  daddu      $4, $16, $0
    /* FDB60 001FDB60 5C01458C */  lw         $5, 0x15C($2)
    /* FDB64 001FDB64 A6FF080C */  jal        func_0023FE98
    /* FDB68 001FDB68 C001A524 */   addiu     $5, $5, 0x1C0
    /* FDB6C 001FDB6C 3000A48F */  lw         $4, 0x30($29)
    /* FDB70 001FDB70 6000A1C7 */  lwc1       $f1, 0x60($29)
    /* FDB74 001FDB74 6401838C */  lw         $3, 0x164($4)
    /* FDB78 001FDB78 7006628C */  lw         $2, 0x670($3)
    /* FDB7C 001FDB7C 700241E4 */  swc1       $f1, 0x270($2)
    /* FDB80 001FDB80 6400A0C7 */  lwc1       $f0, 0x64($29)
    /* FDB84 001FDB84 740240E4 */  swc1       $f0, 0x274($2)
    /* FDB88 001FDB88 6800A1C7 */  lwc1       $f1, 0x68($29)
    /* FDB8C 001FDB8C 2274050C */  jal        subCommonIdle
    /* FDB90 001FDB90 780241E4 */   swc1      $f1, 0x278($2)
    /* FDB94 001FDB94 2D204000 */  daddu      $4, $2, $0
    /* FDB98 001FDB98 9CFF080C */  jal        func_0023FE70
    /* FDB9C 001FDB9C 2D280002 */   daddu     $5, $16, $0
    /* FDBA0 001FDBA0 00088044 */  mtc1       $0, $f1
    /* FDBA4 001FDBA4 34080046 */  c.lt.s     $f1, $f0
    /* FDBA8 001FDBA8 00000000 */  nop
    /* FDBAC 001FDBAC 09000045 */  bc1f       .L001FDBD4
    /* FDBB0 001FDBB0 00020324 */   addiu     $3, $0, 0x200
    /* FDBB4 001FDBB4 700462DE */  ld         $2, 0x470($19)
    /* FDBB8 001FDBB8 3000A48F */  lw         $4, 0x30($29)
    /* FDBBC 001FDBBC 25104300 */  or         $2, $2, $3
    /* FDBC0 001FDBC0 700462FE */  sd         $2, 0x470($19)
    /* FDBC4 001FDBC4 6401838C */  lw         $3, 0x164($4)
    /* FDBC8 001FDBC8 7006628C */  lw         $2, 0x670($3)
    /* FDBCC 001FDBCC 0A000010 */  b          .L001FDBF8
    /* FDBD0 001FDBD0 800240A0 */   sb        $0, 0x280($2)
.align 2
  .L001FDBD4:
    /* FDBD4 001FDBD4 700463DE */  ld         $3, 0x470($19)
    /* FDBD8 001FDBD8 00040224 */  addiu      $2, $0, 0x400
    /* FDBDC 001FDBDC 3000A48F */  lw         $4, 0x30($29)
    /* FDBE0 001FDBE0 01000524 */  addiu      $5, $0, 0x1
    /* FDBE4 001FDBE4 25186200 */  or         $3, $3, $2
    /* FDBE8 001FDBE8 700463FE */  sd         $3, 0x470($19)
    /* FDBEC 001FDBEC 6401828C */  lw         $2, 0x164($4)
    /* FDBF0 001FDBF0 7006438C */  lw         $3, 0x670($2)
    /* FDBF4 001FDBF4 800265A0 */  sb         $5, 0x280($3)
.align 2
  .L001FDBF8:
    /* FDBF8 001FDBF8 3000A48F */  lw         $4, 0x30($29)
    /* FDBFC 001FDBFC 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FDC00 001FDC00 40000524 */   addiu     $5, $0, 0x40
    /* FDC04 001FDC04 07004010 */  beqz       $2, .L001FDC24
    /* FDC08 001FDC08 10000324 */   addiu     $3, $0, 0x10
    /* FDC0C 001FDC0C 700462DE */  ld         $2, 0x470($19)
    /* FDC10 001FDC10 6300043C */  lui        $4, %hi(D_0062D9D0)
    /* FDC14 001FDC14 25104300 */  or         $2, $2, $3
    /* FDC18 001FDC18 D0D98424 */  addiu      $4, $4, %lo(D_0062D9D0)
    /* FDC1C 001FDC1C F290060C */  jal        debug_assertMessage
    /* FDC20 001FDC20 700462FE */   sd        $2, 0x470($19)
.align 2
  .L001FDC24:
    /* FDC24 001FDC24 3000A48F */  lw         $4, 0x30($29)
    /* FDC28 001FDC28 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FDC2C 001FDC2C 50000524 */   addiu     $5, $0, 0x50
    /* FDC30 001FDC30 37004010 */  beqz       $2, .L001FDD10
    /* FDC34 001FDC34 20000324 */   addiu     $3, $0, 0x20
    /* FDC38 001FDC38 700462DE */  ld         $2, 0x470($19)
    /* FDC3C 001FDC3C 3000A78F */  lw         $7, 0x30($29)
    /* FDC40 001FDC40 25104300 */  or         $2, $2, $3
    /* FDC44 001FDC44 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FDC48 001FDC48 700462FE */  sd         $2, 0x470($19)
    /* FDC4C 001FDC4C 5C01E38C */  lw         $3, 0x15C($7)
    /* FDC50 001FDC50 0900E414 */  bne        $7, $4, .L001FDC78
    /* FDC54 001FDC54 340661C4 */   lwc1      $f1, 0x634($3)
    /* FDC58 001FDC58 DC42013C */  lui        $1, (0x42DC0000 >> 16)
    /* FDC5C 001FDC5C 00008144 */  mtc1       $1, $f0
    /* FDC60 001FDC60 34000146 */  c.lt.s     $f0, $f1
    /* FDC64 001FDC64 00000000 */  nop
    /* FDC68 001FDC68 0A000345 */  bc1tl      .L001FDC94
    /* FDC6C 001FDC6C 700462DE */   ld        $2, 0x470($19)
    /* FDC70 001FDC70 11000010 */  b          .L001FDCB8
    /* FDC74 001FDC74 5C01E28C */   lw        $2, 0x15C($7)
.align 2
  .L001FDC78:
    /* FDC78 001FDC78 0743013C */  lui        $1, (0x43070000 >> 16)
    /* FDC7C 001FDC7C 00008144 */  mtc1       $1, $f0
    /* FDC80 001FDC80 34000146 */  c.lt.s     $f0, $f1
    /* FDC84 001FDC84 00000000 */  nop
    /* FDC88 001FDC88 0B000245 */  bc1fl      .L001FDCB8
    /* FDC8C 001FDC8C 5C01E28C */   lw        $2, 0x15C($7)
    /* FDC90 001FDC90 700462DE */  ld         $2, 0x470($19)
.align 2
  .L001FDC94:
    /* FDC94 001FDC94 40000324 */  addiu      $3, $0, 0x40
    /* FDC98 001FDC98 6100043C */  lui        $4, %hi(D_006139E0)
    /* FDC9C 001FDC9C 25104300 */  or         $2, $2, $3
    /* FDCA0 001FDCA0 E0398424 */  addiu      $4, $4, %lo(D_006139E0)
    /* FDCA4 001FDCA4 F290060C */  jal        debug_assertMessage
    /* FDCA8 001FDCA8 700462FE */   sd        $2, 0x470($19)
    /* FDCAC 001FDCAC 3000A78F */  lw         $7, 0x30($29)
    /* FDCB0 001FDCB0 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FDCB4 001FDCB4 5C01E28C */  lw         $2, 0x15C($7)
.align 2
  .L001FDCB8:
    /* FDCB8 001FDCB8 0900E414 */  bne        $7, $4, .L001FDCE0
    /* FDCBC 001FDCBC 340641C4 */   lwc1      $f1, 0x634($2)
    /* FDCC0 001FDCC0 D242013C */  lui        $1, (0x42D20000 >> 16)
    /* FDCC4 001FDCC4 00008144 */  mtc1       $1, $f0
    /* FDCC8 001FDCC8 34080046 */  c.lt.s     $f1, $f0
    /* FDCCC 001FDCCC 00000000 */  nop
    /* FDCD0 001FDCD0 09000345 */  bc1tl      .L001FDCF8
    /* FDCD4 001FDCD4 700462DE */   ld        $2, 0x470($19)
    /* FDCD8 001FDCD8 0F000010 */  b          .L001FDD18
    /* FDCDC 001FDCDC 00000000 */   nop
.align 2
  .L001FDCE0:
    /* FDCE0 001FDCE0 0243013C */  lui        $1, (0x43020000 >> 16)
    /* FDCE4 001FDCE4 00008144 */  mtc1       $1, $f0
    /* FDCE8 001FDCE8 34080046 */  c.lt.s     $f1, $f0
    /* FDCEC 001FDCEC 0A000045 */  bc1f       .L001FDD18
    /* FDCF0 001FDCF0 00000000 */   nop
    /* FDCF4 001FDCF4 700462DE */  ld         $2, 0x470($19)
.align 2
  .L001FDCF8:
    /* FDCF8 001FDCF8 80000324 */  addiu      $3, $0, 0x80
    /* FDCFC 001FDCFC 6100043C */  lui        $4, %hi(D_006139F0)
    /* FDD00 001FDD00 25104300 */  or         $2, $2, $3
    /* FDD04 001FDD04 F0398424 */  addiu      $4, $4, %lo(D_006139F0)
    /* FDD08 001FDD08 F290060C */  jal        debug_assertMessage
    /* FDD0C 001FDD0C 700462FE */   sd        $2, 0x470($19)
.align 2
  .L001FDD10:
    /* FDD10 001FDD10 3000A78F */  lw         $7, 0x30($29)
    /* FDD14 001FDD14 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
.align 2
  .L001FDD18:
    /* FDD18 001FDD18 C600E454 */  bnel       $7, $4, .L001FE034
    /* FDD1C 001FDD1C 0400828E */   lw        $2, 0x4($20)
    /* FDD20 001FDD20 5C01E28C */  lw         $2, 0x15C($7)
    /* FDD24 001FDD24 90010524 */  addiu      $5, $0, 0x190
    /* FDD28 001FDD28 5600043C */  lui        $4, %hi(D_0055DA10)
    /* FDD2C 001FDD2C 2DF00000 */  daddu      $30, $0, $0
    /* FDD30 001FDD30 9004438C */  lw         $3, 0x490($2)
    /* FDD34 001FDD34 10DA8424 */  addiu      $4, $4, %lo(D_0055DA10)
    /* FDD38 001FDD38 2DB00000 */  daddu      $22, $0, $0
    /* FDD3C 001FDD3C 18186500 */  mult       $3, $3, $5
    /* FDD40 001FDD40 B442013C */  lui        $1, (0x42B40000 >> 16)
    /* FDD44 001FDD44 00A08144 */  mtc1       $1, $f20
    /* FDD48 001FDD48 21186400 */  addu       $3, $3, $4
    /* FDD4C 001FDD4C 86016294 */  lhu        $2, 0x186($3)
    /* FDD50 001FDD50 07004230 */  andi       $2, $2, 0x7
    /* FDD54 001FDD54 03004010 */  beqz       $2, .L001FDD64
    /* FDD58 001FDD58 2DB80000 */   daddu     $23, $0, $0
    /* FDD5C 001FDD5C C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FDD60 001FDD60 00A08144 */  mtc1       $1, $f20
.align 2
  .L001FDD64:
    /* FDD64 001FDD64 4843013C */  lui        $1, (0x43480000 >> 16)
    /* FDD68 001FDD68 00A88144 */  mtc1       $1, $f21
    /* FDD6C 001FDD6C 2D20E000 */  daddu      $4, $7, $0
    /* FDD70 001FDD70 52BC070C */  jal        InitTorchGeo
    /* FDD74 001FDD74 06AB0046 */   mov.s     $f12, $f21
    /* FDD78 001FDD78 2D804000 */  daddu      $16, $2, $0
    /* FDD7C 001FDD7C 32000012 */  beqz       $16, .L001FDE48
    /* FDD80 001FDD80 7000B227 */   addiu     $18, $29, 0x70
    /* FDD84 001FDD84 2D280002 */  daddu      $5, $16, $0
    /* FDD88 001FDD88 2D204002 */  daddu      $4, $18, $0
    /* FDD8C 001FDD8C C210040C */  jal        GetRootMatrixByDObj
    /* FDD90 001FDD90 2D884002 */   daddu     $17, $18, $0
    /* FDD94 001FDD94 2D20A003 */  daddu      $4, $29, $0
    /* FDD98 001FDD98 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FDD9C 001FDD9C 2D284002 */   daddu     $5, $18, $0
    /* FDDA0 001FDDA0 42A01446 */  mul.s      $f1, $f20, $f20
    /* FDDA4 001FDDA4 34000146 */  c.lt.s     $f0, $f1
    /* FDDA8 001FDDA8 00000000 */  nop
    /* FDDAC 001FDDAC 26000045 */  bc1f       .L001FDE48
    /* FDDB0 001FDDB0 7400A1C7 */   lwc1      $f1, 0x74($29)
    /* FDDB4 001FDDB4 0400A0C7 */  lwc1       $f0, 0x4($29)
    /* FDDB8 001FDDB8 34080046 */  c.lt.s     $f1, $f0
    /* FDDBC 001FDDBC 22000045 */  bc1f       .L001FDE48
    /* FDDC0 001FDDC0 00000000 */   nop
    /* FDDC4 001FDDC4 2274050C */  jal        subCommonIdle
    /* FDDC8 001FDDC8 3000A48F */   lw        $4, 0x30($29)
    /* FDDCC 001FDDCC 2D204002 */  daddu      $4, $18, $0
    /* FDDD0 001FDDD0 2D304000 */  daddu      $6, $2, $0
    /* FDDD4 001FDDD4 2D28A003 */  daddu      $5, $29, $0
    /* FDDD8 001FDDD8 1048060C */  jal        func_00192040
    /* FDDDC 001FDDDC 2D000724 */   addiu     $7, $0, 0x2D
    /* FDDE0 001FDDE0 19004010 */  beqz       $2, .L001FDE48
    /* FDDE4 001FDDE4 7400A3C7 */   lwc1      $f3, 0x74($29)
    /* FDDE8 001FDDE8 0400A2C7 */  lwc1       $f2, 0x4($29)
    /* FDDEC 001FDDEC 00008044 */  mtc1       $0, $f0
    /* FDDF0 001FDDF0 41180246 */  sub.s      $f1, $f3, $f2
    /* FDDF4 001FDDF4 34080046 */  c.lt.s     $f1, $f0
    /* FDDF8 001FDDF8 07000045 */  bc1f       .L001FDE18
    /* FDDFC 001FDDFC 00000000 */   nop
    /* FDE00 001FDE00 07080046 */  neg.s      $f0, $f1
    /* FDE04 001FDE04 34001546 */  c.lt.s     $f0, $f21
    /* FDE08 001FDE08 06000145 */  bc1t       .L001FDE24
    /* FDE0C 001FDE0C 00000000 */   nop
    /* FDE10 001FDE10 0D000010 */  b          .L001FDE48
    /* FDE14 001FDE14 00000000 */   nop
.align 2
  .L001FDE18:
    /* FDE18 001FDE18 34081546 */  c.lt.s     $f1, $f21
    /* FDE1C 001FDE1C 0A000045 */  bc1f       .L001FDE48
    /* FDE20 001FDE20 00000000 */   nop
.align 2
  .L001FDE24:
    /* FDE24 001FDE24 34180246 */  c.lt.s     $f3, $f2
    /* FDE28 001FDE28 00000000 */  nop
    /* FDE2C 001FDE2C 06000045 */  bc1f       .L001FDE48
    /* FDE30 001FDE30 2D282002 */   daddu     $5, $17, $0
    /* FDE34 001FDE34 2DB80002 */  daddu      $23, $16, $0
    /* FDE38 001FDE38 2000A426 */  addiu      $4, $21, 0x20
    /* FDE3C 001FDE3C F447060C */  jal        func_00191FD0
    /* FDE40 001FDE40 2D30A003 */   daddu     $6, $29, $0
    /* FDE44 001FDE44 2DF0E002 */  daddu      $30, $23, $0
.align 2
  .L001FDE48:
    /* FDE48 001FDE48 4843013C */  lui        $1, (0x43480000 >> 16)
    /* FDE4C 001FDE4C 00A08144 */  mtc1       $1, $f20
    /* FDE50 001FDE50 3000A48F */  lw         $4, 0x30($29)
    /* FDE54 001FDE54 2EBB070C */  jal        LightTorchOn
    /* FDE58 001FDE58 06A30046 */   mov.s     $f12, $f20
    /* FDE5C 001FDE5C 2D804000 */  daddu      $16, $2, $0
    /* FDE60 001FDE60 3A000012 */  beqz       $16, .L001FDF4C
    /* FDE64 001FDE64 00000000 */   nop
    /* FDE68 001FDE68 5C01028E */  lw         $2, 0x15C($16)
    /* FDE6C 001FDE6C 0000428C */  lw         $2, 0x0($2)
    /* FDE70 001FDE70 04004010 */  beqz       $2, .L001FDE84
    /* FDE74 001FDE74 2D900000 */   daddu     $18, $0, $0
    /* FDE78 001FDE78 0C00428C */  lw         $2, 0xC($2)
    /* FDE7C 001FDE7C 13004238 */  xori       $2, $2, 0x13
    /* FDE80 001FDE80 0100522C */  sltiu      $18, $2, 0x1
.align 2
  .L001FDE84:
    /* FDE84 001FDE84 7000B127 */  addiu      $17, $29, 0x70
    /* FDE88 001FDE88 2D280002 */  daddu      $5, $16, $0
    /* FDE8C 001FDE8C C210040C */  jal        GetRootMatrixByDObj
    /* FDE90 001FDE90 2D202002 */   daddu     $4, $17, $0
    /* FDE94 001FDE94 2D004016 */  bnez       $18, .L001FDF4C
    /* FDE98 001FDE98 2D20A003 */   daddu     $4, $29, $0
    /* FDE9C 001FDE9C D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FDEA0 001FDEA0 2D282002 */   daddu     $5, $17, $0
    /* FDEA4 001FDEA4 6C8B81C7 */  lwc1       $f1, %gp_rel(D_0062975C)($28)
    /* FDEA8 001FDEA8 34000146 */  c.lt.s     $f0, $f1
    /* FDEAC 001FDEAC 00000000 */  nop
    /* FDEB0 001FDEB0 26000045 */  bc1f       .L001FDF4C
    /* FDEB4 001FDEB4 7400A1C7 */   lwc1      $f1, 0x74($29)
    /* FDEB8 001FDEB8 0400A0C7 */  lwc1       $f0, 0x4($29)
    /* FDEBC 001FDEBC 34080046 */  c.lt.s     $f1, $f0
    /* FDEC0 001FDEC0 22000045 */  bc1f       .L001FDF4C
    /* FDEC4 001FDEC4 00000000 */   nop
    /* FDEC8 001FDEC8 2274050C */  jal        subCommonIdle
    /* FDECC 001FDECC 3000A48F */   lw        $4, 0x30($29)
    /* FDED0 001FDED0 2D304000 */  daddu      $6, $2, $0
    /* FDED4 001FDED4 2D202002 */  daddu      $4, $17, $0
    /* FDED8 001FDED8 2D28A003 */  daddu      $5, $29, $0
    /* FDEDC 001FDEDC 1048060C */  jal        func_00192040
    /* FDEE0 001FDEE0 2D000724 */   addiu     $7, $0, 0x2D
    /* FDEE4 001FDEE4 19004010 */  beqz       $2, .L001FDF4C
    /* FDEE8 001FDEE8 7400A3C7 */   lwc1      $f3, 0x74($29)
    /* FDEEC 001FDEEC 0400A2C7 */  lwc1       $f2, 0x4($29)
    /* FDEF0 001FDEF0 00008044 */  mtc1       $0, $f0
    /* FDEF4 001FDEF4 41180246 */  sub.s      $f1, $f3, $f2
    /* FDEF8 001FDEF8 34080046 */  c.lt.s     $f1, $f0
    /* FDEFC 001FDEFC 07000045 */  bc1f       .L001FDF1C
    /* FDF00 001FDF00 00000000 */   nop
    /* FDF04 001FDF04 07080046 */  neg.s      $f0, $f1
    /* FDF08 001FDF08 34001446 */  c.lt.s     $f0, $f20
    /* FDF0C 001FDF0C 06000145 */  bc1t       .L001FDF28
    /* FDF10 001FDF10 00000000 */   nop
    /* FDF14 001FDF14 0D000010 */  b          .L001FDF4C
    /* FDF18 001FDF18 00000000 */   nop
.align 2
  .L001FDF1C:
    /* FDF1C 001FDF1C 34081446 */  c.lt.s     $f1, $f20
    /* FDF20 001FDF20 0A000045 */  bc1f       .L001FDF4C
    /* FDF24 001FDF24 00000000 */   nop
.align 2
  .L001FDF28:
    /* FDF28 001FDF28 34180246 */  c.lt.s     $f3, $f2
    /* FDF2C 001FDF2C 00000000 */  nop
    /* FDF30 001FDF30 06000045 */  bc1f       .L001FDF4C
    /* FDF34 001FDF34 2D282002 */   daddu     $5, $17, $0
    /* FDF38 001FDF38 3000A426 */  addiu      $4, $21, 0x30
    /* FDF3C 001FDF3C 2D30A003 */  daddu      $6, $29, $0
    /* FDF40 001FDF40 F447060C */  jal        func_00191FD0
    /* FDF44 001FDF44 2DB00002 */   daddu     $22, $16, $0
    /* FDF48 001FDF48 6801B6AE */  sw         $22, 0x168($21)
.align 2
  .L001FDF4C:
    /* FDF4C 001FDF4C 7E26050C */  jal        ACTGame_ConnectHand
    /* FDF50 001FDF50 3000A48F */   lw        $4, 0x30($29)
    /* FDF54 001FDF54 13004054 */  bnel       $2, $0, .L001FDFA4
    /* FDF58 001FDF58 6001648E */   lw        $4, 0x160($19)
    /* FDF5C 001FDF5C 2C24050C */  jal        ACTGameCollisionOff
    /* FDF60 001FDF60 3001648E */   lw        $4, 0x130($19)
    /* FDF64 001FDF64 0F004050 */  beql       $2, $0, .L001FDFA4
    /* FDF68 001FDF68 6001648E */   lw        $4, 0x160($19)
    /* FDF6C 001FDF6C 4EBC070C */  jal        TorchGeo
    /* FDF70 001FDF70 2D204000 */   daddu     $4, $2, $0
    /* FDF74 001FDF74 05004014 */  bnez       $2, .L001FDF8C
    /* FDF78 001FDF78 00000000 */   nop
    /* FDF7C 001FDF7C 0800C013 */  beqz       $30, .L001FDFA0
    /* FDF80 001FDF80 0004033C */   lui       $3, (0x4000000 >> 16)
    /* FDF84 001FDF84 04000010 */  b          .L001FDF98
    /* FDF88 001FDF88 700462DE */   ld        $2, 0x470($19)
.align 2
  .L001FDF8C:
    /* FDF8C 001FDF8C 0400C012 */  beqz       $22, .L001FDFA0
    /* FDF90 001FDF90 0010033C */   lui       $3, (0x10000000 >> 16)
    /* FDF94 001FDF94 700462DE */  ld         $2, 0x470($19)
.align 2
  .L001FDF98:
    /* FDF98 001FDF98 25104300 */  or         $2, $2, $3
    /* FDF9C 001FDF9C 700462FE */  sd         $2, 0x470($19)
.align 2
  .L001FDFA0:
    /* FDFA0 001FDFA0 6001648E */  lw         $4, 0x160($19)
.align 2
  .L001FDFA4:
    /* FDFA4 001FDFA4 11008010 */  beqz       $4, .L001FDFEC
    /* FDFA8 001FDFA8 3000A38F */   lw        $3, 0x30($29)
    /* FDFAC 001FDFAC 5244070C */  jal        _getLine
    /* FDFB0 001FDFB0 00000000 */   nop
    /* FDFB4 001FDFB4 0C00E012 */  beqz       $23, .L001FDFE8
    /* FDFB8 001FDFB8 2D804000 */   daddu     $16, $2, $0
    /* FDFBC 001FDFBC 0B000012 */  beqz       $16, .L001FDFEC
    /* FDFC0 001FDFC0 3000A38F */   lw        $3, 0x30($29)
    /* FDFC4 001FDFC4 4EBC070C */  jal        TorchGeo
    /* FDFC8 001FDFC8 2D200002 */   daddu     $4, $16, $0
    /* FDFCC 001FDFCC 07004014 */  bnez       $2, .L001FDFEC
    /* FDFD0 001FDFD0 3000A38F */   lw        $3, 0x30($29)
    /* FDFD4 001FDFD4 6401B0AE */  sw         $16, 0x164($21)
    /* FDFD8 001FDFD8 0008033C */  lui        $3, (0x8000000 >> 16)
    /* FDFDC 001FDFDC 700462DE */  ld         $2, 0x470($19)
    /* FDFE0 001FDFE0 25104300 */  or         $2, $2, $3
    /* FDFE4 001FDFE4 700462FE */  sd         $2, 0x470($19)
.align 2
  .L001FDFE8:
    /* FDFE8 001FDFE8 3000A38F */  lw         $3, 0x30($29)
.align 2
  .L001FDFEC:
    /* FDFEC 001FDFEC 5C01638C */  lw         $3, 0x15C($3)
    /* FDFF0 001FDFF0 6805628C */  lw         $2, 0x568($3)
    /* FDFF4 001FDFF4 08004010 */  beqz       $2, .L001FE018
    /* FDFF8 001FDFF8 2D200000 */   daddu     $4, $0, $0
    /* FDFFC 001FDFFC D00561C4 */  lwc1       $f1, 0x5D0($3)
    /* FE000 001FE000 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FE004 001FE004 00008144 */  mtc1       $1, $f0
    /* FE008 001FE008 34080046 */  c.lt.s     $f1, $f0
    /* FE00C 001FE00C 00000000 */  nop
    /* FE010 001FE010 01000345 */  bc1tl      .L001FE018
    /* FE014 001FE014 01000424 */   addiu     $4, $0, 0x1
.align 2
  .L001FE018:
    /* FE018 001FE018 06008054 */  bnel       $4, $0, .L001FE034
    /* FE01C 001FE01C 0400828E */   lw        $2, 0x4($20)
    /* FE020 001FE020 700462DE */  ld         $2, 0x470($19)
    /* FE024 001FE024 08000324 */  addiu      $3, $0, 0x8
    /* FE028 001FE028 25104300 */  or         $2, $2, $3
    /* FE02C 001FE02C 700462FE */  sd         $2, 0x470($19)
    /* FE030 001FE030 0400828E */  lw         $2, 0x4($20)
.align 2
  .L001FE034:
    /* FE034 001FE034 82170200 */  srl        $2, $2, 30
    /* FE038 001FE038 01004230 */  andi       $2, $2, 0x1
    /* FE03C 001FE03C 07004010 */  beqz       $2, .L001FE05C
    /* FE040 001FE040 3000A68F */   lw        $6, 0x30($29)
    /* FE044 001FE044 AC01A58F */  lw         $5, 0x1AC($29)
    /* FE048 001FE048 6401C38C */  lw         $3, 0x164($6)
    /* FE04C 001FE04C 7006628C */  lw         $2, 0x670($3)
    /* FE050 001FE050 D0024424 */  addiu      $4, $2, 0x2D0
    /* FE054 001FE054 F4F1060C */  jal        moveBoxAutoMatic
    /* FE058 001FE058 C40245AC */   sw        $5, 0x2C4($2)
.align 2
  .L001FE05C:
    /* FE05C 001FE05C 7002BFDF */  ld         $31, 0x270($29)
    /* FE060 001FE060 6002BEDF */  ld         $30, 0x260($29)
    /* FE064 001FE064 5002B7DF */  ld         $23, 0x250($29)
    /* FE068 001FE068 4002B6DF */  ld         $22, 0x240($29)
    /* FE06C 001FE06C 3002B5DF */  ld         $21, 0x230($29)
    /* FE070 001FE070 2002B4DF */  ld         $20, 0x220($29)
    /* FE074 001FE074 1002B3DF */  ld         $19, 0x210($29)
    /* FE078 001FE078 0002B2DF */  ld         $18, 0x200($29)
    /* FE07C 001FE07C F001B1DF */  ld         $17, 0x1F0($29)
    /* FE080 001FE080 E001B0DF */  ld         $16, 0x1E0($29)
    /* FE084 001FE084 A802B9C7 */  lwc1       $f25, 0x2A8($29)
    /* FE088 001FE088 A002B8C7 */  lwc1       $f24, 0x2A0($29)
    /* FE08C 001FE08C 9802B7C7 */  lwc1       $f23, 0x298($29)
    /* FE090 001FE090 9002B6C7 */  lwc1       $f22, 0x290($29)
    /* FE094 001FE094 8802B5C7 */  lwc1       $f21, 0x288($29)
    /* FE098 001FE098 8002B4C7 */  lwc1       $f20, 0x280($29)
    /* FE09C 001FE09C 0800E003 */  jr         $31
    /* FE0A0 001FE0A0 B002BD27 */   addiu     $29, $29, 0x2B0
endlabel func_001FA3D0
    /* FE0A4 001FE0A4 00000000 */  nop
```
