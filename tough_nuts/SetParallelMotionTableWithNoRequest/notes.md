# SetParallelMotionTableWithNoRequest — parked

VRAM: 0x001E10A0 (file_off 0x0E10A0)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionOrientManager/SetParallelMotionTableWithNoRequest.s

## Attempt at 2026-07-07

**Reason parked:** rc30 STRUCTURE BYTE-IDENTICAL (alloca(n<<5>>3) float buf + CheckFloorAttribute + deadzone clamp |v*g684|>g688?v:0 via nested if-else branch-likely + else-zero loop; walking src ptr; hoisted g684/g688/0.0 invariants; dst=*(int**)(geom+0x7F8)+i deref). Residual is PURE caller-saved register PERMUTATION (11 sites, ALL identical instructions): expected i=a2/p=a1/dst=a0/geom=v1/g684=f4/0.0=f3 vs built i=a1/p=a0/dst=v0/geom=a2/g684=f3/0.0=f4. regalloc-swap+fp-licm = permuter-class per tools/tag_diff.py; resisted decl-order/inline/hoist steering. Strong seed for permuter.

**TU:** `sugipon/src/motionOrientManager.c`

**Seed:** `tough_nuts/SetParallelMotionTableWithNoRequest/SetParallelMotionTableWithNoRequest.c`

Disassembly:

```
.align 3
nonmatching SetParallelMotionTableWithNoRequest, 0x11C

glabel SetParallelMotionTableWithNoRequest
    /* E10A0 001E10A0 A0FFBD27 */  addiu      $29, $29, -0x60
    /* E10A4 001E10A4 4000BEFF */  sd         $30, 0x40($29)
    /* E10A8 001E10A8 3000B1FF */  sd         $17, 0x30($29)
    /* E10AC 001E10AC 5000BFFF */  sd         $31, 0x50($29)
    /* E10B0 001E10B0 2D888000 */  daddu      $17, $4, $0
    /* E10B4 001E10B4 2000B0FF */  sd         $16, 0x20($29)
    /* E10B8 001E10B8 5C01228E */  lw         $2, 0x15C($17)
    /* E10BC 001E10BC F407508C */  lw         $16, 0x7F4($2)
    /* E10C0 001E10C0 37000012 */  beqz       $16, .L001E11A0
    /* E10C4 001E10C4 2DF0A003 */   daddu     $30, $29, $0
    /* E10C8 001E10C8 40111000 */  sll        $2, $16, 5
    /* E10CC 001E10CC C2100200 */  srl        $2, $2, 3
    /* E10D0 001E10D0 0F004224 */  addiu      $2, $2, 0xF
    /* E10D4 001E10D4 02110200 */  srl        $2, $2, 4
    /* E10D8 001E10D8 00110200 */  sll        $2, $2, 4
    /* E10DC 001E10DC 23E8A203 */  subu       $29, $29, $2
    /* E10E0 001E10E0 2A28040C */  jal        CheckFloorAttribute
    /* E10E4 001E10E4 2D20A003 */   daddu     $4, $29, $0
    /* E10E8 001E10E8 22004010 */  beqz       $2, .L001E1174
    /* E10EC 001E10EC 00000000 */   nop
    /* E10F0 001E10F0 2B00001A */  blez       $16, .L001E11A0
    /* E10F4 001E10F4 2D300000 */   daddu     $6, $0, $0
    /* E10F8 001E10F8 948A84C7 */  lwc1       $f4, %gp_rel(D_00629684)($28)
    /* E10FC 001E10FC 2D28A003 */  daddu      $5, $29, $0
    /* E1100 001E1100 00188044 */  mtc1       $0, $f3
    /* E1104 001E1104 988A82C7 */  lwc1       $f2, %gp_rel(D_00629688)($28)
.align 2
  .L001E1108:
    /* E1108 001E1108 0000A0C4 */  lwc1       $f0, 0x0($5)
    /* E110C 001E110C 80200600 */  sll        $4, $6, 2
    /* E1110 001E1110 5C01238E */  lw         $3, 0x15C($17)
    /* E1114 001E1114 42000446 */  mul.s      $f1, $f0, $f4
    /* E1118 001E1118 F807628C */  lw         $2, 0x7F8($3)
    /* E111C 001E111C 34080346 */  c.lt.s     $f1, $f3
    /* E1120 001E1120 00000000 */  nop
    /* E1124 001E1124 08000045 */  bc1f       .L001E1148
    /* E1128 001E1128 21208200 */   addu      $4, $4, $2
    /* E112C 001E112C 07080046 */  neg.s      $f0, $f1
    /* E1130 001E1130 34100046 */  c.lt.s     $f2, $f0
    /* E1134 001E1134 00000000 */  nop
    /* E1138 001E1138 08000345 */  bc1tl      .L001E115C
    /* E113C 001E113C 000081E4 */   swc1      $f1, 0x0($4)
    /* E1140 001E1140 06000010 */  b          .L001E115C
    /* E1144 001E1144 000080AC */   sw        $0, 0x0($4)
.align 2
  .L001E1148:
    /* E1148 001E1148 34100146 */  c.lt.s     $f2, $f1
    /* E114C 001E114C 00000000 */  nop
    /* E1150 001E1150 02000245 */  bc1fl      .L001E115C
    /* E1154 001E1154 000080AC */   sw        $0, 0x0($4)
    /* E1158 001E1158 000081E4 */  swc1       $f1, 0x0($4)
.align 2
  .L001E115C:
    /* E115C 001E115C 0100C624 */  addiu      $6, $6, 0x1
    /* E1160 001E1160 2A10D000 */  slt        $2, $6, $16
    /* E1164 001E1164 E8FF4014 */  bnez       $2, .L001E1108
    /* E1168 001E1168 0400A524 */   addiu     $5, $5, 0x4
    /* E116C 001E116C 0C000010 */  b          .L001E11A0
    /* E1170 001E1170 00000000 */   nop
.align 2
  .L001E1174:
    /* E1174 001E1174 0A00001A */  blez       $16, .L001E11A0
    /* E1178 001E1178 2D300000 */   daddu     $6, $0, $0
    /* E117C 001E117C 00000000 */  nop
.align 2
  .L001E1180:
    /* E1180 001E1180 5C01248E */  lw         $4, 0x15C($17)
    /* E1184 001E1184 80100600 */  sll        $2, $6, 2
    /* E1188 001E1188 0100C624 */  addiu      $6, $6, 0x1
    /* E118C 001E118C F807838C */  lw         $3, 0x7F8($4)
    /* E1190 001E1190 2A28D000 */  slt        $5, $6, $16
    /* E1194 001E1194 21104300 */  addu       $2, $2, $3
    /* E1198 001E1198 F9FFA014 */  bnez       $5, .L001E1180
    /* E119C 001E119C 000040AC */   sw        $0, 0x0($2)
.align 2
  .L001E11A0:
    /* E11A0 001E11A0 2DE8C003 */  daddu      $29, $30, $0
    /* E11A4 001E11A4 5000BFDF */  ld         $31, 0x50($29)
    /* E11A8 001E11A8 4000BEDF */  ld         $30, 0x40($29)
    /* E11AC 001E11AC 3000B1DF */  ld         $17, 0x30($29)
    /* E11B0 001E11B0 2000B0DF */  ld         $16, 0x20($29)
    /* E11B4 001E11B4 0800E003 */  jr         $31
    /* E11B8 001E11B8 6000BD27 */   addiu     $29, $29, 0x60
endlabel SetParallelMotionTableWithNoRequest
    /* E11BC 001E11BC 00000000 */  nop
```
