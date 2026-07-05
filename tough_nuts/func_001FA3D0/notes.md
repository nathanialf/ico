# func_001FA3D0 — parked

VRAM: 0x001FA3D0 (file_off 0x0FA3D0)
Asm source: asm/aug6/nonmatchings/fumi/src/act-env/func_001FA3D0.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=1077). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/act-env.c`

**Seed:** `tough_nuts/func_001FA3D0/func_001FA3D0.c`

Disassembly:

```
.align 3
nonmatching func_001FA3D0, 0x3CD4

glabel func_001FA3D0
    /* FA3D0 001FA3D0 50FDBD27 */  addiu      $29, $29, -0x2B0
    /* FA3D4 001FA3D4 2D108000 */  daddu      $2, $4, $0
    /* FA3D8 001FA3D8 6002BEFF */  sd         $30, 0x260($29)
    /* FA3DC 001FA3DC 01000924 */  addiu      $9, $0, 0x1
    /* FA3E0 001FA3E0 3002B5FF */  sd         $21, 0x230($29)
    /* FA3E4 001FA3E4 2DF0A000 */  daddu      $30, $5, $0
    /* FA3E8 001FA3E8 2002B4FF */  sd         $20, 0x220($29)
    /* FA3EC 001FA3EC 2DA80001 */  daddu      $21, $8, $0
    /* FA3F0 001FA3F0 9802B7E7 */  swc1       $f23, 0x298($29)
    /* FA3F4 001FA3F4 2DA0E000 */  daddu      $20, $7, $0
    /* FA3F8 001FA3F8 7002BFFF */  sd         $31, 0x270($29)
    /* FA3FC 001FA3FC 01000724 */  addiu      $7, $0, 0x1
    /* FA400 001FA400 5002B7FF */  sd         $23, 0x250($29)
    /* FA404 001FA404 4002B6FF */  sd         $22, 0x240($29)
    /* FA408 001FA408 0002B2FF */  sd         $18, 0x200($29)
    /* FA40C 001FA40C F001B1FF */  sd         $17, 0x1F0($29)
    /* FA410 001FA410 E001B0FF */  sd         $16, 0x1E0($29)
    /* FA414 001FA414 A802B9E7 */  swc1       $f25, 0x2A8($29)
    /* FA418 001FA418 A002B8E7 */  swc1       $f24, 0x2A0($29)
    /* FA41C 001FA41C 9002B6E7 */  swc1       $f22, 0x290($29)
    /* FA420 001FA420 8802B5E7 */  swc1       $f21, 0x288($29)
    /* FA424 001FA424 8002B4E7 */  swc1       $f20, 0x280($29)
    /* FA428 001FA428 1002B3FF */  sd         $19, 0x210($29)
    /* FA42C 001FA42C 6401538C */  lw         $19, 0x164($2)
    /* FA430 001FA430 A801A6AF */  sw         $6, 0x1A8($29)
    /* FA434 001FA434 10000624 */  addiu      $6, $0, 0x10
    /* FA438 001FA438 5C01438C */  lw         $3, 0x15C($2)
    /* FA43C 001FA43C 1001628E */  lw         $2, 0x110($19)
    /* FA440 001FA440 7001658C */  lw         $5, 0x170($3)
    /* FA444 001FA444 AC01A5AF */  sw         $5, 0x1AC($29)
    /* FA448 001FA448 2D280000 */  daddu      $5, $0, $0
    /* FA44C 001FA44C 300140C4 */  lwc1       $f0, 0x130($2)
    /* FA450 001FA450 100158C4 */  lwc1       $f24, 0x110($2)
    /* FA454 001FA454 B401A7AF */  sw         $7, 0x1B4($29)
    /* FA458 001FA458 07000046 */  neg.s      $f0, $f0
    /* FA45C 001FA45C 0000688C */  lw         $8, 0x0($3)
    /* FA460 001FA460 B801A9AF */  sw         $9, 0x1B8($29)
    /* FA464 001FA464 B001A8AF */  sw         $8, 0x1B0($29)
    /* FA468 001FA468 940561C4 */  lwc1       $f1, 0x594($3)
    /* FA46C 001FA46C 3000A4AF */  sw         $4, 0x30($29)
    /* FA470 001FA470 C001A0AF */  sw         $0, 0x1C0($29)
    /* FA474 001FA474 C70D0046 */  neg.s      $f23, $f1
    /* FA478 001FA478 2D20A003 */  daddu      $4, $29, $0
    /* FA47C 001FA47C 380156C4 */  lwc1       $f22, 0x138($2)
    /* FA480 001FA480 3400A0E7 */  swc1       $f0, 0x34($29)
    /* FA484 001FA484 6405778C */  lw         $23, 0x564($3)
    /* FA488 001FA488 140155C4 */  lwc1       $f21, 0x114($2)
    /* FA48C 001FA48C 5A81090C */  jal        func_00260568
    /* FA490 001FA490 5405768C */   lw        $22, 0x554($3)
    /* FA494 001FA494 3000A78F */  lw         $7, 0x30($29)
    /* FA498 001FA498 2D20E000 */  daddu      $4, $7, $0
    /* FA49C 001FA49C 5C01828C */  lw         $2, 0x15C($4)
    /* FA4A0 001FA4A0 7801438C */  lw         $3, 0x178($2)
    /* FA4A4 001FA4A4 03006014 */  bnez       $3, .L001FA4B4
    /* FA4A8 001FA4A8 00000000 */   nop
    /* FA4AC 001FA4AC 2DB80000 */  daddu      $23, $0, $0
    /* FA4B0 001FA4B0 2DB00000 */  daddu      $22, $0, $0
.align 2
  .L001FA4B4:
    /* FA4B4 001FA4B4 0500E016 */  bnez       $23, .L001FA4CC
    /* FA4B8 001FA4B8 5C01908C */   lw        $16, 0x15C($4)
    /* FA4BC 001FA4BC 0300C016 */  bnez       $22, .L001FA4CC
    /* FA4C0 001FA4C0 00000000 */   nop
    /* FA4C4 001FA4C4 6300023C */  lui        $2, %hi(D_0062D9D8)
    /* FA4C8 001FA4C8 D8D956C4 */  lwc1       $f22, %lo(D_0062D9D8)($2)
.align 2
  .L001FA4CC:
    /* FA4CC 001FA4CC 5805028E */  lw         $2, 0x558($16)
    /* FA4D0 001FA4D0 03004014 */  bnez       $2, .L001FA4E0
    /* FA4D4 001FA4D4 180062DE */   ld        $2, 0x18($19)
    /* FA4D8 001FA4D8 6300033C */  lui        $3, %hi(D_0062D9D8)
    /* FA4DC 001FA4DC D8D975C4 */  lwc1       $f21, %lo(D_0062D9D8)($3)
.align 2
  .L001FA4E0:
    /* FA4E0 001FA4E0 02000424 */  addiu      $4, $0, 0x2
    /* FA4E4 001FA4E4 B401A58F */  lw         $5, 0x1B4($29)
    /* FA4E8 001FA4E8 FE130200 */  dsrl32     $2, $2, 15
    /* FA4EC 001FA4EC 01004230 */  andi       $2, $2, 0x1
    /* FA4F0 001FA4F0 0B280200 */  movn       $5, $0, $2
    /* FA4F4 001FA4F4 4027050C */  jal        func_00149D00
    /* FA4F8 001FA4F8 B401A5AF */   sw        $5, 0x1B4($29)
    /* FA4FC 001FA4FC 500501C6 */  lwc1       $f1, 0x550($16)
    /* FA500 001FA500 34000146 */  c.lt.s     $f0, $f1
    /* FA504 001FA504 00000000 */  nop
    /* FA508 001FA508 04000045 */  bc1f       .L001FA51C
    /* FA50C 001FA50C 3000A58F */   lw        $5, 0x30($29)
    /* FA510 001FA510 B401A0AF */  sw         $0, 0x1B4($29)
    /* FA514 001FA514 B801A0AF */  sw         $0, 0x1B8($29)
    /* FA518 001FA518 3000A58F */  lw         $5, 0x30($29)
.align 2
  .L001FA51C:
    /* FA51C 001FA51C E229040C */  jal        GetHeightOfWallFromGObj
    /* FA520 001FA520 2D20A003 */   daddu     $4, $29, $0
    /* FA524 001FA524 1000A627 */  addiu      $6, $29, 0x10
    /* FA528 001FA528 3000A58F */  lw         $5, 0x30($29)
    /* FA52C 001FA52C C401A6AF */  sw         $6, 0x1C4($29)
    /* FA530 001FA530 C210040C */  jal        GetRootMatrixByDObj
    /* FA534 001FA534 2D20C000 */   daddu     $4, $6, $0
    /* FA538 001FA538 3000A58F */  lw         $5, 0x30($29)
    /* FA53C 001FA53C 2000A427 */  addiu      $4, $29, 0x20
    /* FA540 001FA540 EE10050C */  jal        func_001443B8
    /* FA544 001FA544 2C000624 */   addiu     $6, $0, 0x2C
    /* FA548 001FA548 3000A28F */  lw         $2, 0x30($29)
    /* FA54C 001FA54C 7FFF0424 */  addiu      $4, $0, -0x81
    /* FA550 001FA550 38240400 */  dsll       $4, $4, 16
    /* FA554 001FA554 FFFF8434 */  ori        $4, $4, 0xFFFF
    /* FA558 001FA558 38240400 */  dsll       $4, $4, 16
    /* FA55C 001FA55C FFFF8434 */  ori        $4, $4, 0xFFFF
    /* FA560 001FA560 FFFE0524 */  addiu      $5, $0, -0x101
    /* FA564 001FA564 382C0500 */  dsll       $5, $5, 16
    /* FA568 001FA568 FFFFA534 */  ori        $5, $5, 0xFFFF
    /* FA56C 001FA56C 382C0500 */  dsll       $5, $5, 16
    /* FA570 001FA570 FFFFA534 */  ori        $5, $5, 0xFFFF
    /* FA574 001FA574 FFDF063C */  lui        $6, (0xDFFFFFFF >> 16)
    /* FA578 001FA578 FFFFC634 */  ori        $6, $6, (0xDFFFFFFF & 0xFFFF)
    /* FA57C 001FA57C 38340600 */  dsll       $6, $6, 16
    /* FA580 001FA580 FFFFC634 */  ori        $6, $6, 0xFFFF
    /* FA584 001FA584 38340600 */  dsll       $6, $6, 16
    /* FA588 001FA588 FFFFC634 */  ori        $6, $6, 0xFFFF
    /* FA58C 001FA58C 5C01438C */  lw         $3, 0x15C($2)
    /* FA590 001FA590 77016768 */  ldl        $7, 0x177($3)
    /* FA594 001FA594 7001676C */  ldr        $7, 0x170($3)
    /* FA598 001FA598 7F016868 */  ldl        $8, 0x17F($3)
    /* FA59C 001FA59C 7801686C */  ldr        $8, 0x178($3)
    /* FA5A0 001FA5A0 87016968 */  ldl        $9, 0x187($3)
    /* FA5A4 001FA5A4 8001696C */  ldr        $9, 0x180($3)
    /* FA5A8 001FA5A8 8F016268 */  ldl        $2, 0x18F($3)
    /* FA5AC 001FA5AC 8801626C */  ldr        $2, 0x188($3)
    /* FA5B0 001FA5B0 7701A7B2 */  sdl        $7, 0x177($21)
    /* FA5B4 001FA5B4 7001A7B6 */  sdr        $7, 0x170($21)
    /* FA5B8 001FA5B8 7F01A8B2 */  sdl        $8, 0x17F($21)
    /* FA5BC 001FA5BC 7801A8B6 */  sdr        $8, 0x178($21)
    /* FA5C0 001FA5C0 8701A9B2 */  sdl        $9, 0x187($21)
    /* FA5C4 001FA5C4 8001A9B6 */  sdr        $9, 0x180($21)
    /* FA5C8 001FA5C8 8F01A2B2 */  sdl        $2, 0x18F($21)
    /* FA5CC 001FA5CC 8801A2B6 */  sdr        $2, 0x188($21)
    /* FA5D0 001FA5D0 180062DE */  ld         $2, 0x18($19)
    /* FA5D4 001FA5D4 200063DE */  ld         $3, 0x20($19)
    /* FA5D8 001FA5D8 24104400 */  and        $2, $2, $4
    /* FA5DC 001FA5DC 24104500 */  and        $2, $2, $5
    /* FA5E0 001FA5E0 B81F0300 */  dsll       $3, $3, 30
    /* FA5E4 001FA5E4 3F180300 */  dsra32     $3, $3, 0
    /* FA5E8 001FA5E8 24104600 */  and        $2, $2, $6
    /* FA5EC 001FA5EC 01006330 */  andi       $3, $3, 0x1
    /* FA5F0 001FA5F0 05006010 */  beqz       $3, .L001FA608
    /* FA5F4 001FA5F4 180062FE */   sd        $2, 0x18($19)
    /* FA5F8 001FA5F8 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FA5FC 001FA5FC 00C88144 */  mtc1       $1, $f25
    /* FA600 001FA600 05000010 */  b          .L001FA618
    /* FA604 001FA604 BC01A0AF */   sw        $0, 0x1BC($29)
.align 2
  .L001FA608:
    /* FA608 001FA608 01000324 */  addiu      $3, $0, 0x1
    /* FA60C 001FA60C 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FA610 001FA610 00C88144 */  mtc1       $1, $f25
    /* FA614 001FA614 BC01A3AF */  sw         $3, 0x1BC($29)
.align 2
  .L001FA618:
    /* FA618 001FA618 3000A28F */  lw         $2, 0x30($29)
    /* FA61C 001FA61C 2B000424 */  addiu      $4, $0, 0x2B
    /* FA620 001FA620 F891838F */  lw         $3, %gp_rel(D_00629DE8)($28)
    /* FA624 001FA624 BC01A58F */  lw         $5, 0x1BC($29)
    /* FA628 001FA628 26104300 */  xor        $2, $2, $3
    /* FA62C 001FA62C 408B94C7 */  lwc1       $f20, %gp_rel(D_00629730)($28)
    /* FA630 001FA630 0A280200 */  movz       $5, $0, $2
    /* FA634 001FA634 8EF9040C */  jal        isysGObjSearchFromObjLayoutID
    /* FA638 001FA638 BC01A5AF */   sw        $5, 0x1BC($29)
    /* FA63C 001FA63C 04000010 */  b          .L001FA650
    /* FA640 001FA640 4000B127 */   addiu     $17, $29, 0x40
    /* FA644 001FA644 00000000 */  nop
.align 2
  .L001FA648:
    /* FA648 001FA648 B2F9040C */  jal        isysGObjSearchFromObjKindID_begin
    /* FA64C 001FA64C 2D200002 */   daddu     $4, $16, $0
.align 2
  .L001FA650:
    /* FA650 001FA650 2D804000 */  daddu      $16, $2, $0
    /* FA654 001FA654 17000012 */  beqz       $16, .L001FA6B4
    /* FA658 001FA658 C001A68F */   lw        $6, 0x1C0($29)
    /* FA65C 001FA65C 6C01028E */  lw         $2, 0x16C($16)
    /* FA660 001FA660 F9FF4010 */  beqz       $2, .L001FA648
    /* FA664 001FA664 2D202002 */   daddu     $4, $17, $0
    /* FA668 001FA668 5000A527 */  addiu      $5, $29, 0x50
    /* FA66C 001FA66C 2600070C */  jal        CageFixDL
    /* FA670 001FA670 2D300002 */   daddu     $6, $16, $0
    /* FA674 001FA674 3E74050C */  jal        ContinueCorrectPosition
    /* FA678 001FA678 3000A48F */   lw        $4, 0x30($29)
    /* FA67C 001FA67C 2D204000 */  daddu      $4, $2, $0
    /* FA680 001FA680 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FA684 001FA684 2D282002 */   daddu     $5, $17, $0
    /* FA688 001FA688 34001446 */  c.lt.s     $f0, $f20
    /* FA68C 001FA68C 00000000 */  nop
    /* FA690 001FA690 EDFF0045 */  bc1f       .L001FA648
    /* FA694 001FA694 5400A1C7 */   lwc1      $f1, 0x54($29)
    /* FA698 001FA698 1400A0C7 */  lwc1       $f0, 0x14($29)
    /* FA69C 001FA69C 34000146 */  c.lt.s     $f0, $f1
    /* FA6A0 001FA6A0 E9FF0045 */  bc1f       .L001FA648
    /* FA6A4 001FA6A4 00000000 */   nop
    /* FA6A8 001FA6A8 C001B0AF */  sw         $16, 0x1C0($29)
    /* FA6AC 001FA6AC 6001B0AE */  sw         $16, 0x160($21)
    /* FA6B0 001FA6B0 C001A68F */  lw         $6, 0x1C0($29)
.align 2
  .L001FA6B4:
    /* FA6B4 001FA6B4 3B00C010 */  beqz       $6, .L001FA7A4
    /* FA6B8 001FA6B8 3000A48F */   lw        $4, 0x30($29)
    /* FA6BC 001FA6BC 5E37060C */  jal        eBrainProcess
    /* FA6C0 001FA6C0 6000A527 */   addiu     $5, $29, 0x60
    /* FA6C4 001FA6C4 7000B227 */  addiu      $18, $29, 0x70
    /* FA6C8 001FA6C8 8000B027 */  addiu      $16, $29, 0x80
    /* FA6CC 001FA6CC 2D884002 */  daddu      $17, $18, $0
    /* FA6D0 001FA6D0 C001A68F */  lw         $6, 0x1C0($29)
    /* FA6D4 001FA6D4 2D280002 */  daddu      $5, $16, $0
    /* FA6D8 001FA6D8 2600070C */  jal        CageFixDL
    /* FA6DC 001FA6DC 2D202002 */   daddu     $4, $17, $0
    /* FA6E0 001FA6E0 7400A2C7 */  lwc1       $f2, 0x74($29)
    /* FA6E4 001FA6E4 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FA6E8 001FA6E8 00008144 */  mtc1       $1, $f0
    /* FA6EC 001FA6EC 6400A1C7 */  lwc1       $f1, 0x64($29)
    /* FA6F0 001FA6F0 00100046 */  add.s      $f0, $f2, $f0
    /* FA6F4 001FA6F4 34000146 */  c.lt.s     $f0, $f1
    /* FA6F8 001FA6F8 00000000 */  nop
    /* FA6FC 001FA6FC 04000045 */  bc1f       .L001FA710
    /* FA700 001FA700 8000033C */   lui       $3, (0x800000 >> 16)
    /* FA704 001FA704 0000828E */  lw         $2, 0x0($20)
    /* FA708 001FA708 25104300 */  or         $2, $2, $3
    /* FA70C 001FA70C 000082AE */  sw         $2, 0x0($20)
.align 2
  .L001FA710:
    /* FA710 001FA710 41080246 */  sub.s      $f1, $f1, $f2
    /* FA714 001FA714 00008044 */  mtc1       $0, $f0
    /* FA718 001FA718 34080046 */  c.lt.s     $f1, $f0
    /* FA71C 001FA71C 0A000045 */  bc1f       .L001FA748
    /* FA720 001FA720 00000000 */   nop
    /* FA724 001FA724 47080046 */  neg.s      $f1, $f1
    /* FA728 001FA728 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FA72C 001FA72C 00008144 */  mtc1       $1, $f0
    /* FA730 001FA730 34080046 */  c.lt.s     $f1, $f0
    /* FA734 001FA734 00000000 */  nop
    /* FA738 001FA738 09000345 */  bc1tl      .L001FA760
    /* FA73C 001FA73C 0000828E */   lw        $2, 0x0($20)
    /* FA740 001FA740 0A000010 */  b          .L001FA76C
    /* FA744 001FA744 00000000 */   nop
.align 2
  .L001FA748:
    /* FA748 001FA748 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FA74C 001FA74C 00008144 */  mtc1       $1, $f0
    /* FA750 001FA750 34080046 */  c.lt.s     $f1, $f0
    /* FA754 001FA754 05000045 */  bc1f       .L001FA76C
    /* FA758 001FA758 00000000 */   nop
    /* FA75C 001FA75C 0000828E */  lw         $2, 0x0($20)
.align 2
  .L001FA760:
    /* FA760 001FA760 0001033C */  lui        $3, (0x1000000 >> 16)
    /* FA764 001FA764 25104300 */  or         $2, $2, $3
    /* FA768 001FA768 000082AE */  sw         $2, 0x0($20)
.align 2
  .L001FA76C:
    /* FA76C 001FA76C C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FA770 001FA770 00A08144 */  mtc1       $1, $f20
    /* FA774 001FA774 2D200002 */  daddu      $4, $16, $0
    /* FA778 001FA778 2D280000 */  daddu      $5, $0, $0
    /* FA77C 001FA77C FF000624 */  addiu      $6, $0, 0xFF
    /* FA780 001FA780 2D380000 */  daddu      $7, $0, $0
    /* FA784 001FA784 1012060C */  jal        debug_Marker
    /* FA788 001FA788 06A30046 */   mov.s     $f12, $f20
    /* FA78C 001FA78C 2D202002 */  daddu      $4, $17, $0
    /* FA790 001FA790 06A30046 */  mov.s      $f12, $f20
    /* FA794 001FA794 2D280000 */  daddu      $5, $0, $0
    /* FA798 001FA798 2D300000 */  daddu      $6, $0, $0
    /* FA79C 001FA79C 1012060C */  jal        debug_Marker
    /* FA7A0 001FA7A0 FF000724 */   addiu     $7, $0, 0xFF
.align 2
  .L001FA7A4:
    /* FA7A4 001FA7A4 1100C012 */  beqz       $22, .L001FA7EC
    /* FA7A8 001FA7A8 3000A48F */   lw        $4, 0x30($29)
    /* FA7AC 001FA7AC 1A28040C */  jal        EnableMotionOrientUpdate
    /* FA7B0 001FA7B0 00030524 */   addiu     $5, $0, 0x300
    /* FA7B4 001FA7B4 0B004014 */  bnez       $2, .L001FA7E4
    /* FA7B8 001FA7B8 6300073C */   lui       $7, %hi(D_0062D9D8)
    /* FA7BC 001FA7BC 3000A48F */  lw         $4, 0x30($29)
    /* FA7C0 001FA7C0 1A28040C */  jal        EnableMotionOrientUpdate
    /* FA7C4 001FA7C4 00050524 */   addiu     $5, $0, 0x500
    /* FA7C8 001FA7C8 06004014 */  bnez       $2, .L001FA7E4
    /* FA7CC 001FA7CC 6300073C */   lui       $7, %hi(D_0062D9D8)
    /* FA7D0 001FA7D0 3000A48F */  lw         $4, 0x30($29)
    /* FA7D4 001FA7D4 1A28040C */  jal        EnableMotionOrientUpdate
    /* FA7D8 001FA7D8 00060524 */   addiu     $5, $0, 0x600
    /* FA7DC 001FA7DC 03004010 */  beqz       $2, .L001FA7EC
    /* FA7E0 001FA7E0 6300073C */   lui       $7, %hi(D_0062D9D8)
.align 2
  .L001FA7E4:
    /* FA7E4 001FA7E4 D8D9F7C4 */  lwc1       $f23, %lo(D_0062D9D8)($7)
    /* FA7E8 001FA7E8 3400B7E7 */  swc1       $f23, 0x34($29)
.align 2
  .L001FA7EC:
    /* FA7EC 001FA7EC 3000A78F */  lw         $7, 0x30($29)
    /* FA7F0 001FA7F0 5C01E28C */  lw         $2, 0x15C($7)
    /* FA7F4 001FA7F4 5805438C */  lw         $3, 0x558($2)
    /* FA7F8 001FA7F8 13006010 */  beqz       $3, .L001FA848
    /* FA7FC 001FA7FC 2D20E000 */   daddu     $4, $7, $0
    /* FA800 001FA800 2228040C */  jal        DisableMotionOrientUpdate
    /* FA804 001FA804 00030524 */   addiu     $5, $0, 0x300
    /* FA808 001FA808 0B004014 */  bnez       $2, .L001FA838
    /* FA80C 001FA80C 6300083C */   lui       $8, %hi(D_0062D9D8)
    /* FA810 001FA810 3000A48F */  lw         $4, 0x30($29)
    /* FA814 001FA814 2228040C */  jal        DisableMotionOrientUpdate
    /* FA818 001FA818 00050524 */   addiu     $5, $0, 0x500
    /* FA81C 001FA81C 06004014 */  bnez       $2, .L001FA838
    /* FA820 001FA820 6300083C */   lui       $8, %hi(D_0062D9D8)
    /* FA824 001FA824 3000A48F */  lw         $4, 0x30($29)
    /* FA828 001FA828 2228040C */  jal        DisableMotionOrientUpdate
    /* FA82C 001FA82C 00060524 */   addiu     $5, $0, 0x600
    /* FA830 001FA830 04004010 */  beqz       $2, .L001FA844
    /* FA834 001FA834 6300083C */   lui       $8, %hi(D_0062D9D8)
.align 2
  .L001FA838:
    /* FA838 001FA838 3000A78F */  lw         $7, 0x30($29)
    /* FA83C 001FA83C 02000010 */  b          .L001FA848
    /* FA840 001FA840 D8D915C5 */   lwc1      $f21, %lo(D_0062D9D8)($8)
.align 2
  .L001FA844:
    /* FA844 001FA844 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FA848:
    /* FA848 001FA848 0400E056 */  bnel       $23, $0, .L001FA85C
    /* FA84C 001FA84C 5C01E28C */   lw        $2, 0x15C($7)
    /* FA850 001FA850 5700C052 */  beql       $22, $0, .L001FA9B0
    /* FA854 001FA854 5C01E48C */   lw        $4, 0x15C($7)
    /* FA858 001FA858 5C01E28C */  lw         $2, 0x15C($7)
.align 2
  .L001FA85C:
    /* FA85C 001FA85C 7801458C */  lw         $5, 0x178($2)
    /* FA860 001FA860 4F00A010 */  beqz       $5, .L001FA9A0
    /* FA864 001FA864 70014624 */   addiu     $6, $2, 0x170
    /* FA868 001FA868 C499050C */  jal        fzMagnitudefv
    /* FA86C 001FA86C 2D20A002 */   daddu     $4, $21, $0
    /* FA870 001FA870 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FA874 001FA874 00008144 */  mtc1       $1, $f0
    /* FA878 001FA878 2900C012 */  beqz       $22, .L001FA920
    /* FA87C 001FA87C 0C00A0E6 */   swc1      $f0, 0xC($21)
    /* FA880 001FA880 01001124 */  addiu      $17, $0, 0x1
    /* FA884 001FA884 A222050C */  jal        ACTEnvGetTest
    /* FA888 001FA888 01001224 */   addiu     $18, $0, 0x1
    /* FA88C 001FA88C 08004010 */  beqz       $2, .L001FA8B0
    /* FA890 001FA890 3000A28F */   lw        $2, 0x30($29)
    /* FA894 001FA894 2D900000 */  daddu      $18, $0, $0
    /* FA898 001FA898 F491838F */  lw         $3, %gp_rel(D_00629DE4)($28)
    /* FA89C 001FA89C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* FA8A0 001FA8A0 26184300 */  xor        $3, $2, $3
    /* FA8A4 001FA8A4 26104400 */  xor        $2, $2, $4
    /* FA8A8 001FA8A8 0B902302 */  movn       $18, $17, $3
    /* FA8AC 001FA8AC 0A880200 */  movz       $17, $0, $2
.align 2
  .L001FA8B0:
    /* FA8B0 001FA8B0 6000B027 */  addiu      $16, $29, 0x60
    /* FA8B4 001FA8B4 3000A58F */  lw         $5, 0x30($29)
    /* FA8B8 001FA8B8 2D200002 */  daddu      $4, $16, $0
    /* FA8BC 001FA8BC EE10050C */  jal        func_001443B8
    /* FA8C0 001FA8C0 2C000624 */   addiu     $6, $0, 0x2C
    /* FA8C4 001FA8C4 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FA8C8 001FA8C8 00608144 */  mtc1       $1, $f12
    /* FA8CC 001FA8CC 7000A427 */  addiu      $4, $29, 0x70
    /* FA8D0 001FA8D0 0E00090C */  jal        func_00240038
    /* FA8D4 001FA8D4 2D28A002 */   daddu     $5, $21, $0
    /* FA8D8 001FA8D8 2D200002 */  daddu      $4, $16, $0
    /* FA8DC 001FA8DC 4247060C */  jal        HandCameraCorrect
    /* FA8E0 001FA8E0 7000A527 */   addiu     $5, $29, 0x70
    /* FA8E4 001FA8E4 07004012 */  beqz       $18, .L001FA904
    /* FA8E8 001FA8E8 2D184000 */   daddu     $3, $2, $0
    /* FA8EC 001FA8EC 1F006228 */  slti       $2, $3, 0x1F
    /* FA8F0 001FA8F0 04004014 */  bnez       $2, .L001FA904
    /* FA8F4 001FA8F4 00000000 */   nop
    /* FA8F8 001FA8F8 0000828E */  lw         $2, 0x0($20)
    /* FA8FC 001FA8FC 10004234 */  ori        $2, $2, 0x10
    /* FA900 001FA900 000082AE */  sw         $2, 0x0($20)
.align 2
  .L001FA904:
    /* FA904 001FA904 06002012 */  beqz       $17, .L001FA920
    /* FA908 001FA908 E2FF6228 */   slti      $2, $3, -0x1E
    /* FA90C 001FA90C 04004010 */  beqz       $2, .L001FA920
    /* FA910 001FA910 00000000 */   nop
    /* FA914 001FA914 0000828E */  lw         $2, 0x0($20)
    /* FA918 001FA918 08004234 */  ori        $2, $2, 0x8
    /* FA91C 001FA91C 000082AE */  sw         $2, 0x0($20)
.align 2
  .L001FA920:
    /* FA920 001FA920 1F00E012 */  beqz       $23, .L001FA9A0
    /* FA924 001FA924 00000000 */   nop
    /* FA928 001FA928 34B01946 */  c.lt.s     $f22, $f25
    /* FA92C 001FA92C 00000000 */  nop
    /* FA930 001FA930 1B000045 */  bc1f       .L001FA9A0
    /* FA934 001FA934 7000A427 */   addiu     $4, $29, 0x70
    /* FA938 001FA938 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FA93C 001FA93C 00608144 */  mtc1       $1, $f12
    /* FA940 001FA940 0E00090C */  jal        func_00240038
    /* FA944 001FA944 2D28A002 */   daddu     $5, $21, $0
    /* FA948 001FA948 2D20C003 */  daddu      $4, $30, $0
    /* FA94C 001FA94C 4247060C */  jal        HandCameraCorrect
    /* FA950 001FA950 7000A527 */   addiu     $5, $29, 0x70
    /* FA954 001FA954 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FA958 001FA958 00008144 */  mtc1       $1, $f0
    /* FA95C 001FA95C 02004104 */  bgez       $2, .L001FA968
    /* FA960 001FA960 2D204000 */   daddu     $4, $2, $0
    /* FA964 001FA964 23200400 */  negu       $4, $4
.align 2
  .L001FA968:
    /* FA968 001FA968 180063DE */  ld         $3, 0x18($19)
    /* FA96C 001FA96C 00800234 */  ori        $2, $0, 0x8000
    /* FA970 001FA970 FC100200 */  dsll32     $2, $2, 3
    /* FA974 001FA974 34B00046 */  c.lt.s     $f22, $f0
    /* FA978 001FA978 25186200 */  or         $3, $3, $2
    /* FA97C 001FA97C 08000045 */  bc1f       .L001FA9A0
    /* FA980 001FA980 180063FE */   sd        $3, 0x18($19)
    /* FA984 001FA984 1E008228 */  slti       $2, $4, 0x1E
    /* FA988 001FA988 05004010 */  beqz       $2, .L001FA9A0
    /* FA98C 001FA98C 00000000 */   nop
    /* FA990 001FA990 00800234 */  ori        $2, $0, 0x8000
    /* FA994 001FA994 BC100200 */  dsll32     $2, $2, 2
    /* FA998 001FA998 25106200 */  or         $2, $3, $2
    /* FA99C 001FA99C 180062FE */  sd         $2, 0x18($19)
.align 2
  .L001FA9A0:
    /* FA9A0 001FA9A0 2200C016 */  bnez       $22, .L001FAA2C
    /* FA9A4 001FA9A4 6300093C */   lui       $9, %hi(D_0062D9D8)
    /* FA9A8 001FA9A8 3000A78F */  lw         $7, 0x30($29)
    /* FA9AC 001FA9AC 5C01E48C */  lw         $4, 0x15C($7)
.align 2
  .L001FA9B0:
    /* FA9B0 001FA9B0 6C05828C */  lw         $2, 0x56C($4)
    /* FA9B4 001FA9B4 1D004010 */  beqz       $2, .L001FAA2C
    /* FA9B8 001FA9B8 6300093C */   lui       $9, %hi(D_0062D9D8)
    /* FA9BC 001FA9BC D40581C4 */  lwc1       $f1, 0x5D4($4)
    /* FA9C0 001FA9C0 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FA9C4 001FA9C4 00008144 */  mtc1       $1, $f0
    /* FA9C8 001FA9C8 34080046 */  c.lt.s     $f1, $f0
    /* FA9CC 001FA9CC 00000000 */  nop
    /* FA9D0 001FA9D0 17000045 */  bc1f       .L001FAA30
    /* FA9D4 001FA9D4 D8D920C5 */   lwc1      $f0, %lo(D_0062D9D8)($9)
    /* FA9D8 001FA9D8 C0058524 */  addiu      $5, $4, 0x5C0
    /* FA9DC 001FA9DC 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FA9E0 001FA9E0 00608144 */  mtc1       $1, $f12
    /* FA9E4 001FA9E4 0E00090C */  jal        func_00240038
    /* FA9E8 001FA9E8 6000A427 */   addiu     $4, $29, 0x60
    /* FA9EC 001FA9EC 2D20C003 */  daddu      $4, $30, $0
    /* FA9F0 001FA9F0 4247060C */  jal        HandCameraCorrect
    /* FA9F4 001FA9F4 6000A527 */   addiu     $5, $29, 0x60
    /* FA9F8 001FA9F8 01004204 */  bltzl      $2, .L001FAA00
    /* FA9FC 001FA9FC 23100200 */   negu      $2, $2
.align 2
  .L001FAA00:
    /* FAA00 001FAA00 28004228 */  slti       $2, $2, 0x28
    /* FAA04 001FAA04 09004010 */  beqz       $2, .L001FAA2C
    /* FAA08 001FAA08 6300093C */   lui       $9, %hi(D_0062D9D8)
    /* FAA0C 001FAA0C 180062DE */  ld         $2, 0x18($19)
    /* FAA10 001FAA10 00800334 */  ori        $3, $0, 0x8000
    /* FAA14 001FAA14 381E0300 */  dsll       $3, $3, 24
    /* FAA18 001FAA18 00800434 */  ori        $4, $0, 0x8000
    /* FAA1C 001FAA1C 78260400 */  dsll       $4, $4, 25
    /* FAA20 001FAA20 25104300 */  or         $2, $2, $3
    /* FAA24 001FAA24 25104400 */  or         $2, $2, $4
    /* FAA28 001FAA28 180062FE */  sd         $2, 0x18($19)
.align 2
  .L001FAA2C:
    /* FAA2C 001FAA2C D8D920C5 */  lwc1       $f0, %lo(D_0062D9D8)($9)
.align 2
  .L001FAA30:
    /* FAA30 001FAA30 32B00046 */  c.eq.s     $f22, $f0
    /* FAA34 001FAA34 00000000 */  nop
    /* FAA38 001FAA38 BA050145 */  bc1t       .L001FC124
    /* FAA3C 001FAA3C 6300083C */   lui       $8, %hi(D_0062D9D8)
    /* FAA40 001FAA40 B805C012 */  beqz       $22, .L001FC124
    /* FAA44 001FAA44 B401A28F */   lw        $2, 0x1B4($29)
    /* FAA48 001FAA48 B7054010 */  beqz       $2, .L001FC128
    /* FAA4C 001FAA4C D8D900C5 */   lwc1      $f0, %lo(D_0062D9D8)($8)
    /* FAA50 001FAA50 2274050C */  jal        subCommonIdle
    /* FAA54 001FAA54 3000A48F */   lw        $4, 0x30($29)
    /* FAA58 001FAA58 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FAA5C 001FAA5C 00608144 */  mtc1       $1, $f12
    /* FAA60 001FAA60 2D804000 */  daddu      $16, $2, $0
    /* FAA64 001FAA64 6000A427 */  addiu      $4, $29, 0x60
    /* FAA68 001FAA68 0E00090C */  jal        func_00240038
    /* FAA6C 001FAA6C 2D28A002 */   daddu     $5, $21, $0
    /* FAA70 001FAA70 2D200002 */  daddu      $4, $16, $0
    /* FAA74 001FAA74 4247060C */  jal        HandCameraCorrect
    /* FAA78 001FAA78 6000A527 */   addiu     $5, $29, 0x60
    /* FAA7C 001FAA7C 7801A38E */  lw         $3, 0x178($21)
    /* FAA80 001FAA80 02004104 */  bgez       $2, .L001FAA8C
    /* FAA84 001FAA84 2DB84000 */   daddu     $23, $2, $0
    /* FAA88 001FAA88 23B81700 */  negu       $23, $23
.align 2
  .L001FAA8C:
    /* FAA8C 001FAA8C 3000A48F */  lw         $4, 0x30($29)
    /* FAA90 001FAA90 00100524 */  addiu      $5, $0, 0x1000
    /* FAA94 001FAA94 4800628C */  lw         $2, 0x48($3)
    /* FAA98 001FAA98 1A28040C */  jal        EnableMotionOrientUpdate
    /* FAA9C 001FAA9C 3001A2AE */   sw        $2, 0x130($21)
    /* FAAA0 001FAAA0 AC01A38F */  lw         $3, 0x1AC($29)
    /* FAAA4 001FAAA4 FF005630 */  andi       $22, $2, 0xFF
    /* FAAA8 001FAAA8 3400A1C7 */  lwc1       $f1, 0x34($29)
    /* FAAAC 001FAAAC 3C01A3AE */  sw         $3, 0x13C($21)
    /* FAAB0 001FAAB0 34081746 */  c.lt.s     $f1, $f23
    /* FAAB4 001FAAB4 0000828E */  lw         $2, 0x0($20)
    /* FAAB8 001FAAB8 01004234 */  ori        $2, $2, 0x1
    /* FAABC 001FAABC 07000045 */  bc1f       .L001FAADC
    /* FAAC0 001FAAC0 000082AE */   sw        $2, 0x0($20)
    /* FAAC4 001FAAC4 6300023C */  lui        $2, %hi(D_0062D9DC)
    /* FAAC8 001FAAC8 DCD940C4 */  lwc1       $f0, %lo(D_0062D9DC)($2)
    /* FAACC 001FAACC 32080046 */  c.eq.s     $f1, $f0
    /* FAAD0 001FAAD0 00000000 */  nop
    /* FAAD4 001FAAD4 01000245 */  bc1fl      .L001FAADC
    /* FAAD8 001FAAD8 3400B7E7 */   swc1      $f23, 0x34($29)
.align 2
  .L001FAADC:
    /* FAADC 001FAADC 34B01946 */  c.lt.s     $f22, $f25
    /* FAAE0 001FAAE0 00000000 */  nop
    /* FAAE4 001FAAE4 11000045 */  bc1f       .L001FAB2C
    /* FAAE8 001FAAE8 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FAAEC 001FAAEC 00008044 */  mtc1       $0, $f0
    /* FAAF0 001FAAF0 34080046 */  c.lt.s     $f1, $f0
    /* FAAF4 001FAAF4 00000000 */  nop
    /* FAAF8 001FAAF8 02000045 */  bc1f       .L001FAB04
    /* FAAFC 001FAAFC 6300053C */   lui       $5, %hi(D_0062D9D8)
    /* FAB00 001FAB00 D8D9A1C4 */  lwc1       $f1, %lo(D_0062D9D8)($5)
.align 2
  .L001FAB04:
    /* FAB04 001FAB04 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FAB08 001FAB08 00008144 */  mtc1       $1, $f0
    /* FAB0C 001FAB0C 36000146 */  c.le.s     $f0, $f1
    /* FAB10 001FAB10 06000045 */  bc1f       .L001FAB2C
    /* FAB14 001FAB14 00000000 */   nop
    /* FAB18 001FAB18 180062DE */  ld         $2, 0x18($19)
    /* FAB1C 001FAB1C 00800334 */  ori        $3, $0, 0x8000
    /* FAB20 001FAB20 FC180300 */  dsll32     $3, $3, 3
    /* FAB24 001FAB24 25104300 */  or         $2, $2, $3
    /* FAB28 001FAB28 180062FE */  sd         $2, 0x18($19)
.align 2
  .L001FAB2C:
    /* FAB2C 001FAB2C 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FAB30 001FAB30 00008144 */  mtc1       $1, $f0
    /* FAB34 001FAB34 34B00046 */  c.lt.s     $f22, $f0
    /* FAB38 001FAB38 00000000 */  nop
    /* FAB3C 001FAB3C 10000045 */  bc1f       .L001FAB80
    /* FAB40 001FAB40 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FAB44 001FAB44 00008044 */  mtc1       $0, $f0
    /* FAB48 001FAB48 34080046 */  c.lt.s     $f1, $f0
    /* FAB4C 001FAB4C 00000000 */  nop
    /* FAB50 001FAB50 02000045 */  bc1f       .L001FAB5C
    /* FAB54 001FAB54 6300063C */   lui       $6, %hi(D_0062D9D8)
    /* FAB58 001FAB58 D8D9C1C4 */  lwc1       $f1, %lo(D_0062D9D8)($6)
.align 2
  .L001FAB5C:
    /* FAB5C 001FAB5C 7A43013C */  lui        $1, (0x437A0000 >> 16)
    /* FAB60 001FAB60 00008144 */  mtc1       $1, $f0
    /* FAB64 001FAB64 36080046 */  c.le.s     $f1, $f0
    /* FAB68 001FAB68 00000000 */  nop
    /* FAB6C 001FAB6C 05000045 */  bc1f       .L001FAB84
    /* FAB70 001FAB70 3000A78F */   lw        $7, 0x30($29)
    /* FAB74 001FAB74 0000828E */  lw         $2, 0x0($20)
    /* FAB78 001FAB78 02004234 */  ori        $2, $2, 0x2
    /* FAB7C 001FAB7C 000082AE */  sw         $2, 0x0($20)
.align 2
  .L001FAB80:
    /* FAB80 001FAB80 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FAB84:
    /* FAB84 001FAB84 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FAB88 001FAB88 3800E514 */  bne        $7, $5, .L001FAC6C
    /* FAB8C 001FAB8C 2D20E000 */   daddu     $4, $7, $0
    /* FAB90 001FAB90 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FAB94 001FAB94 00008144 */  mtc1       $1, $f0
    /* FAB98 001FAB98 34B00046 */  c.lt.s     $f22, $f0
    /* FAB9C 001FAB9C 00000000 */  nop
    /* FABA0 001FABA0 2E000045 */  bc1f       .L001FAC5C
    /* FABA4 001FABA4 AC01A88F */   lw        $8, 0x1AC($29)
    /* FABA8 001FABA8 11000224 */  addiu      $2, $0, 0x11
    /* FABAC 001FABAC 0C00038D */  lw         $3, 0xC($8)
    /* FABB0 001FABB0 2A006214 */  bne        $3, $2, .L001FAC5C
    /* FABB4 001FABB4 00000000 */   nop
    /* FABB8 001FABB8 86F6060C */  jal        ExecBoxMoveEndReaction
    /* FABBC 001FABBC 2D200001 */   daddu     $4, $8, $0
    /* FABC0 001FABC0 07000324 */  addiu      $3, $0, 0x7
    /* FABC4 001FABC4 24004314 */  bne        $2, $3, .L001FAC58
    /* FABC8 001FABC8 3000A78F */   lw        $7, 0x30($29)
    /* FABCC 001FABCC 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FABD0 001FABD0 00608144 */  mtc1       $1, $f12
    /* FABD4 001FABD4 6000A427 */  addiu      $4, $29, 0x60
    /* FABD8 001FABD8 0E00090C */  jal        func_00240038
    /* FABDC 001FABDC 2D28A002 */   daddu     $5, $21, $0
    /* FABE0 001FABE0 2D20C003 */  daddu      $4, $30, $0
    /* FABE4 001FABE4 4247060C */  jal        HandCameraCorrect
    /* FABE8 001FABE8 6000A527 */   addiu     $5, $29, 0x60
    /* FABEC 001FABEC 01004204 */  bltzl      $2, .L001FABF4
    /* FABF0 001FABF0 23100200 */   negu      $2, $2
.align 2
  .L001FABF4:
    /* FABF4 001FABF4 2D004228 */  slti       $2, $2, 0x2D
    /* FABF8 001FABF8 17004010 */  beqz       $2, .L001FAC58
    /* FABFC 001FABFC 3000A78F */   lw        $7, 0x30($29)
    /* FAC00 001FAC00 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FAC04 001FAC04 00608144 */  mtc1       $1, $f12
    /* FAC08 001FAC08 6000A427 */  addiu      $4, $29, 0x60
    /* FAC0C 001FAC0C 0E00090C */  jal        func_00240038
    /* FAC10 001FAC10 2D28A002 */   daddu     $5, $21, $0
    /* FAC14 001FAC14 A801A48F */  lw         $4, 0x1A8($29)
    /* FAC18 001FAC18 4247060C */  jal        HandCameraCorrect
    /* FAC1C 001FAC1C 6000A527 */   addiu     $5, $29, 0x60
    /* FAC20 001FAC20 01004204 */  bltzl      $2, .L001FAC28
    /* FAC24 001FAC24 23100200 */   negu      $2, $2
.align 2
  .L001FAC28:
    /* FAC28 001FAC28 2D004228 */  slti       $2, $2, 0x2D
    /* FAC2C 001FAC2C 09004010 */  beqz       $2, .L001FAC54
    /* FAC30 001FAC30 A801A58F */   lw        $5, 0x1A8($29)
    /* FAC34 001FAC34 6447060C */  jal        func_00191D90
    /* FAC38 001FAC38 2D20C003 */   daddu     $4, $30, $0
    /* FAC3C 001FAC3C 2D004228 */  slti       $2, $2, 0x2D
    /* FAC40 001FAC40 04004010 */  beqz       $2, .L001FAC54
    /* FAC44 001FAC44 00800334 */   ori       $3, $0, 0x8000
    /* FAC48 001FAC48 200062DE */  ld         $2, 0x20($19)
    /* FAC4C 001FAC4C 25104300 */  or         $2, $2, $3
    /* FAC50 001FAC50 200062FE */  sd         $2, 0x20($19)
.align 2
  .L001FAC54:
    /* FAC54 001FAC54 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FAC58:
    /* FAC58 001FAC58 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FAC5C:
    /* FAC5C 001FAC5C 0300E514 */  bne        $7, $5, .L001FAC6C
    /* FAC60 001FAC60 2D20E000 */   daddu     $4, $7, $0
    /* FAC64 001FAC64 05000010 */  b          .L001FAC7C
    /* FAC68 001FAC68 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001FAC6C:
    /* FAC6C 001FAC6C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FAC70 001FAC70 00B00534 */   ori       $5, $0, 0xB000
    /* FAC74 001FAC74 3000A78F */  lw         $7, 0x30($29)
    /* FAC78 001FAC78 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FAC7C:
    /* FAC7C 001FAC7C 2F004054 */  bnel       $2, $0, .L001FAD3C
    /* FAC80 001FAC80 3400B7E7 */   swc1      $f23, 0x34($29)
    /* FAC84 001FAC84 0300E514 */  bne        $7, $5, .L001FAC94
    /* FAC88 001FAC88 2D20E000 */   daddu     $4, $7, $0
    /* FAC8C 001FAC8C 04000010 */  b          .L001FACA0
    /* FAC90 001FAC90 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001FAC94:
    /* FAC94 001FAC94 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FAC98 001FAC98 00E00534 */   ori       $5, $0, 0xE000
    /* FAC9C 001FAC9C 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FACA0:
    /* FACA0 001FACA0 23004014 */  bnez       $2, .L001FAD30
    /* FACA4 001FACA4 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FACA8 001FACA8 2D20E000 */  daddu      $4, $7, $0
    /* FACAC 001FACAC 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FACB0 001FACB0 00C00534 */   ori       $5, $0, 0xC000
    /* FACB4 001FACB4 1D004014 */  bnez       $2, .L001FAD2C
    /* FACB8 001FACB8 3000A78F */   lw        $7, 0x30($29)
    /* FACBC 001FACBC F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
    /* FACC0 001FACC0 0300E514 */  bne        $7, $5, .L001FACD0
    /* FACC4 001FACC4 2D20E000 */   daddu     $4, $7, $0
    /* FACC8 001FACC8 04000010 */  b          .L001FACDC
    /* FACCC 001FACCC 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001FACD0:
    /* FACD0 001FACD0 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FACD4 001FACD4 00D00534 */   ori       $5, $0, 0xD000
    /* FACD8 001FACD8 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FACDC:
    /* FACDC 001FACDC 14004014 */  bnez       $2, .L001FAD30
    /* FACE0 001FACE0 F891858F */   lw        $5, %gp_rel(D_00629DE8)($28)
    /* FACE4 001FACE4 A090838F */  lw         $3, %gp_rel(D_00629C90)($28)
    /* FACE8 001FACE8 04000224 */  addiu      $2, $0, 0x4
    /* FACEC 001FACEC 05006214 */  bne        $3, $2, .L001FAD04
    /* FACF0 001FACF0 2D20E000 */   daddu     $4, $7, $0
    /* FACF4 001FACF4 1A28040C */  jal        EnableMotionOrientUpdate
    /* FACF8 001FACF8 00100524 */   addiu     $5, $0, 0x1000
    /* FACFC 001FACFC 04000010 */  b          .L001FAD10
    /* FAD00 001FAD00 FF004230 */   andi      $2, $2, 0xFF
.align 2
  .L001FAD04:
    /* FAD04 001FAD04 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FAD08 001FAD08 00100524 */   addiu     $5, $0, 0x1000
    /* FAD0C 001FAD0C FF004230 */  andi       $2, $2, 0xFF
.align 2
  .L001FAD10:
    /* FAD10 001FAD10 06004014 */  bnez       $2, .L001FAD2C
    /* FAD14 001FAD14 3000A78F */   lw        $7, 0x30($29)
    /* FAD18 001FAD18 3000A48F */  lw         $4, 0x30($29)
    /* FAD1C 001FAD1C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FAD20 001FAD20 00300524 */   addiu     $5, $0, 0x3000
    /* FAD24 001FAD24 04004010 */  beqz       $2, .L001FAD38
    /* FAD28 001FAD28 3000A78F */   lw        $7, 0x30($29)
.align 2
  .L001FAD2C:
    /* FAD2C 001FAD2C F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FAD30:
    /* FAD30 001FAD30 02000010 */  b          .L001FAD3C
    /* FAD34 001FAD34 3400B7E7 */   swc1      $f23, 0x34($29)
.align 2
  .L001FAD38:
    /* FAD38 001FAD38 F891858F */  lw         $5, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FAD3C:
    /* FAD3C 001FAD3C 3B00E514 */  bne        $7, $5, .L001FAE2C
    /* FAD40 001FAD40 3400A0C7 */   lwc1      $f0, 0x34($29)
    /* FAD44 001FAD44 2D20E000 */  daddu      $4, $7, $0
    /* FAD48 001FAD48 1A28040C */  jal        EnableMotionOrientUpdate
    /* FAD4C 001FAD4C 00700524 */   addiu     $5, $0, 0x7000
    /* FAD50 001FAD50 34004010 */  beqz       $2, .L001FAE24
    /* FAD54 001FAD54 6300093C */   lui       $9, %hi(D_0062D9D8)
    /* FAD58 001FAD58 D8D937C5 */  lwc1       $f23, %lo(D_0062D9D8)($9)
    /* FAD5C 001FAD5C A222050C */  jal        ACTEnvGetTest
    /* FAD60 001FAD60 3400B7E7 */   swc1      $f23, 0x34($29)
    /* FAD64 001FAD64 30004010 */  beqz       $2, .L001FAE28
    /* FAD68 001FAD68 3000A78F */   lw        $7, 0x30($29)
    /* FAD6C 001FAD6C 3E74050C */  jal        ContinueCorrectPosition
    /* FAD70 001FAD70 F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* FAD74 001FAD74 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FAD78 001FAD78 3E74050C */  jal        ContinueCorrectPosition
    /* FAD7C 001FAD7C 2D804000 */   daddu     $16, $2, $0
    /* FAD80 001FAD80 040040C4 */  lwc1       $f0, 0x4($2)
    /* FAD84 001FAD84 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FAD88 001FAD88 00088144 */  mtc1       $1, $f1
    /* FAD8C 001FAD8C 040002C6 */  lwc1       $f2, 0x4($16)
    /* FAD90 001FAD90 00000146 */  add.s      $f0, $f0, $f1
    /* FAD94 001FAD94 34000246 */  c.lt.s     $f0, $f2
    /* FAD98 001FAD98 00000000 */  nop
    /* FAD9C 001FAD9C 21000045 */  bc1f       .L001FAE24
    /* FADA0 001FADA0 6000B027 */   addiu     $16, $29, 0x60
    /* FADA4 001FADA4 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FADA8 001FADA8 00608144 */  mtc1       $1, $f12
    /* FADAC 001FADAC 2D200002 */  daddu      $4, $16, $0
    /* FADB0 001FADB0 0E00090C */  jal        func_00240038
    /* FADB4 001FADB4 2D28A002 */   daddu     $5, $21, $0
    /* FADB8 001FADB8 9000B127 */  addiu      $17, $29, 0x90
    /* FADBC 001FADBC 2D280002 */  daddu      $5, $16, $0
    /* FADC0 001FADC0 2C46060C */  jal        _OrientGV
    /* FADC4 001FADC4 2D202002 */   daddu     $4, $17, $0
    /* FADC8 001FADC8 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FADCC 001FADCC 3E74050C */  jal        ContinueCorrectPosition
    /* FADD0 001FADD0 7000B227 */   addiu     $18, $29, 0x70
    /* FADD4 001FADD4 F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* FADD8 001FADD8 3E74050C */  jal        ContinueCorrectPosition
    /* FADDC 001FADDC 2D804000 */   daddu     $16, $2, $0
    /* FADE0 001FADE0 2D280002 */  daddu      $5, $16, $0
    /* FADE4 001FADE4 2D304000 */  daddu      $6, $2, $0
    /* FADE8 001FADE8 0200090C */  jal        func_00240008
    /* FADEC 001FADEC 2D204002 */   daddu     $4, $18, $0
    /* FADF0 001FADF0 2D282002 */  daddu      $5, $17, $0
    /* FADF4 001FADF4 2D304002 */  daddu      $6, $18, $0
    /* FADF8 001FADF8 7C00A0AF */  sw         $0, 0x7C($29)
    /* FADFC 001FADFC 76FF080C */  jal        func_0023FDD8
    /* FAE00 001FAE00 8000A427 */   addiu     $4, $29, 0x80
    /* FAE04 001FAE04 8800A0C7 */  lwc1       $f0, 0x88($29)
    /* FAE08 001FAE08 34B00046 */  c.lt.s     $f22, $f0
    /* FAE0C 001FAE0C 00000000 */  nop
    /* FAE10 001FAE10 04000045 */  bc1f       .L001FAE24
    /* FAE14 001FAE14 20000324 */   addiu     $3, $0, 0x20
    /* FAE18 001FAE18 200062DE */  ld         $2, 0x20($19)
    /* FAE1C 001FAE1C 25104300 */  or         $2, $2, $3
    /* FAE20 001FAE20 200062FE */  sd         $2, 0x20($19)
.align 2
  .L001FAE24:
    /* FAE24 001FAE24 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FAE28:
    /* FAE28 001FAE28 3400A0C7 */  lwc1       $f0, 0x34($29)
.align 2
  .L001FAE2C:
    /* FAE2C 001FAE2C 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FAE30 001FAE30 00088144 */  mtc1       $1, $f1
    /* FAE34 001FAE34 700160E6 */  swc1       $f0, 0x170($19)
    /* FAE38 001FAE38 34B00146 */  c.lt.s     $f22, $f1
    /* FAE3C 001FAE3C 5C01E28C */  lw         $2, 0x15C($7)
    /* FAE40 001FAE40 E405438C */  lw         $3, 0x5E4($2)
    /* FAE44 001FAE44 14000045 */  bc1f       .L001FAE98
    /* FAE48 001FAE48 740163AE */   sw        $3, 0x174($19)
    /* FAE4C 001FAE4C 180062DE */  ld         $2, 0x18($19)
    /* FAE50 001FAE50 00800334 */  ori        $3, $0, 0x8000
    /* FAE54 001FAE54 381E0300 */  dsll       $3, $3, 24
    /* FAE58 001FAE58 2D20E000 */  daddu      $4, $7, $0
    /* FAE5C 001FAE5C 25104300 */  or         $2, $2, $3
    /* FAE60 001FAE60 2274050C */  jal        subCommonIdle
    /* FAE64 001FAE64 180062FE */   sd        $2, 0x18($19)
    /* FAE68 001FAE68 2D204000 */  daddu      $4, $2, $0
    /* FAE6C 001FAE6C 6447060C */  jal        func_00191D90
    /* FAE70 001FAE70 2D28A002 */   daddu     $5, $21, $0
    /* FAE74 001FAE74 88004228 */  slti       $2, $2, 0x88
    /* FAE78 001FAE78 07004014 */  bnez       $2, .L001FAE98
    /* FAE7C 001FAE7C 3000A78F */   lw        $7, 0x30($29)
    /* FAE80 001FAE80 180062DE */  ld         $2, 0x18($19)
    /* FAE84 001FAE84 00800334 */  ori        $3, $0, 0x8000
    /* FAE88 001FAE88 781E0300 */  dsll       $3, $3, 25
    /* FAE8C 001FAE8C 25104300 */  or         $2, $2, $3
    /* FAE90 001FAE90 180062FE */  sd         $2, 0x18($19)
    /* FAE94 001FAE94 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FAE98:
    /* FAE98 001FAE98 3400A1C7 */  lwc1       $f1, 0x34($29)
    /* FAE9C 001FAE9C 2D300000 */  daddu      $6, $0, $0
    /* FAEA0 001FAEA0 B442013C */  lui        $1, (0x42B40000 >> 16)
    /* FAEA4 001FAEA4 00008144 */  mtc1       $1, $f0
    /* FAEA8 001FAEA8 34000146 */  c.lt.s     $f0, $f1
    /* FAEAC 001FAEAC 00000000 */  nop
    /* FAEB0 001FAEB0 07000045 */  bc1f       .L001FAED0
    /* FAEB4 001FAEB4 86080046 */   mov.s     $f2, $f1
    /* FAEB8 001FAEB8 DC42013C */  lui        $1, (0x42DC0000 >> 16)
    /* FAEBC 001FAEBC 00008144 */  mtc1       $1, $f0
    /* FAEC0 001FAEC0 34080046 */  c.lt.s     $f1, $f0
    /* FAEC4 001FAEC4 00000000 */  nop
    /* FAEC8 001FAEC8 01000345 */  bc1tl      .L001FAED0
    /* FAECC 001FAECC 0100C62E */   sltiu     $6, $22, 0x1
.align 2
  .L001FAED0:
    /* FAED0 001FAED0 3E43013C */  lui        $1, (0x433E0000 >> 16)
    /* FAED4 001FAED4 00008144 */  mtc1       $1, $f0
    /* FAED8 001FAED8 34000246 */  c.lt.s     $f0, $f2
    /* FAEDC 001FAEDC 00000000 */  nop
    /* FAEE0 001FAEE0 04000045 */  bc1f       .L001FAEF4
    /* FAEE4 001FAEE4 5C01E28C */   lw        $2, 0x15C($7)
    /* FAEE8 001FAEE8 5243013C */  lui        $1, (0x43520000 >> 16)
    /* FAEEC 001FAEEC 00008144 */  mtc1       $1, $f0
    /* FAEF0 001FAEF0 34080046 */  c.lt.s     $f1, $f0
.align 2
  .L001FAEF4:
    /* FAEF4 001FAEF4 90010524 */  addiu      $5, $0, 0x190
    /* FAEF8 001FAEF8 56001E3C */  lui        $30, %hi(D_0055DA10)
    /* FAEFC 001FAEFC 9004438C */  lw         $3, 0x490($2)
    /* FAF00 001FAF00 10DAC427 */  addiu      $4, $30, %lo(D_0055DA10)
    /* FAF04 001FAF04 18186500 */  mult       $3, $3, $5
    /* FAF08 001FAF08 21186400 */  addu       $3, $3, $4
    /* FAF0C 001FAF0C 86016294 */  lhu        $2, 0x186($3)
    /* FAF10 001FAF10 07004230 */  andi       $2, $2, 0x7
    /* FAF14 001FAF14 05004010 */  beqz       $2, .L001FAF2C
    /* FAF18 001FAF18 01001224 */   addiu     $18, $0, 0x1
    /* FAF1C 001FAF1C 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FAF20 001FAF20 00A08144 */  mtc1       $1, $f20
    /* FAF24 001FAF24 0A000010 */  b          .L001FAF50
    /* FAF28 001FAF28 00000000 */   nop
.align 2
  .L001FAF2C:
    /* FAF2C 001FAF2C 8801628C */  lw         $2, 0x188($3)
    /* FAF30 001FAF30 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FAF34 001FAF34 00A08144 */  mtc1       $1, $f20
    /* FAF38 001FAF38 82160200 */  srl        $2, $2, 26
    /* FAF3C 001FAF3C 01004230 */  andi       $2, $2, 0x1
    /* FAF40 001FAF40 03004010 */  beqz       $2, .L001FAF50
    /* FAF44 001FAF44 00000000 */   nop
    /* FAF48 001FAF48 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FAF4C 001FAF4C 00A08144 */  mtc1       $1, $f20
.align 2
  .L001FAF50:
    /* FAF50 001FAF50 F042013C */  lui        $1, (0x42F00000 >> 16)
    /* FAF54 001FAF54 00008144 */  mtc1       $1, $f0
    /* FAF58 001FAF58 34B00046 */  c.lt.s     $f22, $f0
    /* FAF5C 001FAF5C 00000000 */  nop
    /* FAF60 001FAF60 27000045 */  bc1f       .L001FB000
    /* FAF64 001FAF64 F891828F */   lw        $2, %gp_rel(D_00629DE8)($28)
    /* FAF68 001FAF68 2500C010 */  beqz       $6, .L001FB000
    /* FAF6C 001FAF6C 6000B027 */   addiu     $16, $29, 0x60
    /* FAF70 001FAF70 2D28A002 */  daddu      $5, $21, $0
    /* FAF74 001FAF74 2D200002 */  daddu      $4, $16, $0
    /* FAF78 001FAF78 0E00090C */  jal        func_00240038
    /* FAF7C 001FAF7C 06B30046 */   mov.s     $f12, $f22
    /* FAF80 001FAF80 3000A38F */  lw         $3, 0x30($29)
    /* FAF84 001FAF84 2D300002 */  daddu      $6, $16, $0
    /* FAF88 001FAF88 C401A58F */  lw         $5, 0x1C4($29)
    /* FAF8C 001FAF8C 6401628C */  lw         $2, 0x164($3)
    /* FAF90 001FAF90 7806448C */  lw         $4, 0x678($2)
    /* FAF94 001FAF94 FCFF080C */  jal        func_0023FFF0
    /* FAF98 001FAF98 50078424 */   addiu     $4, $4, 0x750
    /* FAF9C 001FAF9C 3000A38F */  lw         $3, 0x30($29)
    /* FAFA0 001FAFA0 2D28A002 */  daddu      $5, $21, $0
    /* FAFA4 001FAFA4 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FAFA8 001FAFA8 00608144 */  mtc1       $1, $f12
    /* FAFAC 001FAFAC 6401628C */  lw         $2, 0x164($3)
    /* FAFB0 001FAFB0 7806448C */  lw         $4, 0x678($2)
    /* FAFB4 001FAFB4 0E00090C */  jal        func_00240038
    /* FAFB8 001FAFB8 60078424 */   addiu     $4, $4, 0x760
    /* FAFBC 001FAFBC 3000A78F */  lw         $7, 0x30($29)
    /* FAFC0 001FAFC0 14000424 */  addiu      $4, $0, 0x14
    /* FAFC4 001FAFC4 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FAFC8 001FAFC8 00008144 */  mtc1       $1, $f0
    /* FAFCC 001FAFCC 01000524 */  addiu      $5, $0, 0x1
    /* FAFD0 001FAFD0 6401E28C */  lw         $2, 0x164($7)
    /* FAFD4 001FAFD4 0040063C */  lui        $6, (0x40000000 >> 16)
    /* FAFD8 001FAFD8 7806438C */  lw         $3, 0x678($2)
    /* FAFDC 001FAFDC 740764AC */  sw         $4, 0x774($3)
    /* FAFE0 001FAFE0 700760E4 */  swc1       $f0, 0x770($3)
    /* FAFE4 001FAFE4 6401E28C */  lw         $2, 0x164($7)
    /* FAFE8 001FAFE8 7806438C */  lw         $3, 0x678($2)
    /* FAFEC 001FAFEC 780765AC */  sw         $5, 0x778($3)
    /* FAFF0 001FAFF0 0000828E */  lw         $2, 0x0($20)
    /* FAFF4 001FAFF4 25104600 */  or         $2, $2, $6
    /* FAFF8 001FAFF8 000082AE */  sw         $2, 0x0($20)
    /* FAFFC 001FAFFC F891828F */  lw         $2, %gp_rel(D_00629DE8)($28)
.align 2
  .L001FB000:
    /* FB000 001FB000 2D00E214 */  bne        $7, $2, .L001FB0B8
    /* FB004 001FB004 F491848F */   lw        $4, %gp_rel(D_00629DE4)($28)
    /* FB008 001FB008 2D20E000 */  daddu      $4, $7, $0
    /* FB00C 001FB00C 2827050C */  jal        func_00149CA0
    /* FB010 001FB010 1A000524 */   addiu     $5, $0, 0x1A
    /* FB014 001FB014 26004010 */  beqz       $2, .L001FB0B0
    /* FB018 001FB018 F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* FB01C 001FB01C 3E74050C */  jal        ContinueCorrectPosition
    /* FB020 001FB020 6000B127 */   addiu     $17, $29, 0x60
    /* FB024 001FB024 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FB028 001FB028 3E74050C */  jal        ContinueCorrectPosition
    /* FB02C 001FB02C 2D804000 */   daddu     $16, $2, $0
    /* FB030 001FB030 2D280002 */  daddu      $5, $16, $0
    /* FB034 001FB034 2D304000 */  daddu      $6, $2, $0
    /* FB038 001FB038 0200090C */  jal        func_00240008
    /* FB03C 001FB03C 2D202002 */   daddu     $4, $17, $0
    /* FB040 001FB040 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FB044 001FB044 2274050C */  jal        subCommonIdle
    /* FB048 001FB048 6400A0AF */   sw        $0, 0x64($29)
    /* FB04C 001FB04C 2D202002 */  daddu      $4, $17, $0
    /* FB050 001FB050 9CFF080C */  jal        func_0023FE70
    /* FB054 001FB054 2D284000 */   daddu     $5, $2, $0
    /* FB058 001FB058 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FB05C 001FB05C 00088144 */  mtc1       $1, $f1
    /* FB060 001FB060 34000146 */  c.lt.s     $f0, $f1
    /* FB064 001FB064 00000000 */  nop
    /* FB068 001FB068 11000045 */  bc1f       .L001FB0B0
    /* FB06C 001FB06C AC01A28F */   lw        $2, 0x1AC($29)
    /* FB070 001FB070 0C00438C */  lw         $3, 0xC($2)
    /* FB074 001FB074 11000224 */  addiu      $2, $0, 0x11
    /* FB078 001FB078 09006214 */  bne        $3, $2, .L001FB0A0
    /* FB07C 001FB07C 2D280000 */   daddu     $5, $0, $0
    /* FB080 001FB080 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* FB084 001FB084 5C01828C */  lw         $2, 0x15C($4)
    /* FB088 001FB088 0000428C */  lw         $2, 0x0($2)
    /* FB08C 001FB08C 05004010 */  beqz       $2, .L001FB0A4
    /* FB090 001FB090 AC01A38F */   lw        $3, 0x1AC($29)
    /* FB094 001FB094 26106200 */  xor        $2, $3, $2
    /* FB098 001FB098 02000010 */  b          .L001FB0A4
    /* FB09C 001FB09C 2B280200 */   sltu      $5, $0, $2
.align 2
  .L001FB0A0:
    /* FB0A0 001FB0A0 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
.align 2
  .L001FB0A4:
    /* FB0A4 001FB0A4 0A900500 */  movz       $18, $0, $5
    /* FB0A8 001FB0A8 03000010 */  b          .L001FB0B8
    /* FB0AC 001FB0AC 3000A78F */   lw        $7, 0x30($29)
.align 2
  .L001FB0B0:
    /* FB0B0 001FB0B0 3000A78F */  lw         $7, 0x30($29)
    /* FB0B4 001FB0B4 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
.align 2
  .L001FB0B8:
    /* FB0B8 001FB0B8 3400A1C7 */  lwc1       $f1, 0x34($29)
    /* FB0BC 001FB0BC 2D280000 */  daddu      $5, $0, $0
    /* FB0C0 001FB0C0 2041013C */  lui        $1, (0x41200000 >> 16)
    /* FB0C4 001FB0C4 00008144 */  mtc1       $1, $f0
    /* FB0C8 001FB0C8 34000146 */  c.lt.s     $f0, $f1
    /* FB0CC 001FB0CC 00000000 */  nop
    /* FB0D0 001FB0D0 07000045 */  bc1f       .L001FB0F0
    /* FB0D4 001FB0D4 86080046 */   mov.s     $f2, $f1
    /* FB0D8 001FB0D8 9642013C */  lui        $1, (0x42960000 >> 16)
    /* FB0DC 001FB0DC 00008144 */  mtc1       $1, $f0
    /* FB0E0 001FB0E0 34080046 */  c.lt.s     $f1, $f0
    /* FB0E4 001FB0E4 00000000 */  nop
    /* FB0E8 001FB0E8 03000345 */  bc1tl      .L001FB0F8
    /* FB0EC 001FB0EC 0100C52E */   sltiu     $5, $22, 0x1
.align 2
  .L001FB0F0:
    /* FB0F0 001FB0F0 9642013C */  lui        $1, (0x42960000 >> 16)
    /* FB0F4 001FB0F4 00008144 */  mtc1       $1, $f0
.align 2
  .L001FB0F8:
    /* FB0F8 001FB0F8 34000246 */  c.lt.s     $f0, $f2
    /* FB0FC 001FB0FC 00000000 */  nop
    /* FB100 001FB100 07000045 */  bc1f       .L001FB120
    /* FB104 001FB104 2D880000 */   daddu     $17, $0, $0
    /* FB108 001FB108 1643013C */  lui        $1, (0x43160000 >> 16)
    /* FB10C 001FB10C 00008144 */  mtc1       $1, $f0
    /* FB110 001FB110 34080046 */  c.lt.s     $f1, $f0
    /* FB114 001FB114 00000000 */  nop
    /* FB118 001FB118 03000345 */  bc1tl      .L001FB128
    /* FB11C 001FB11C 0100D12E */   sltiu     $17, $22, 0x1
.align 2
  .L001FB120:
    /* FB120 001FB120 1643013C */  lui        $1, (0x43160000 >> 16)
    /* FB124 001FB124 00008144 */  mtc1       $1, $f0
.align 2
  .L001FB128:
    /* FB128 001FB128 34000246 */  c.lt.s     $f0, $f2
    /* FB12C 001FB12C 00000000 */  nop
    /* FB130 001FB130 07000045 */  bc1f       .L001FB150
    /* FB134 001FB134 2D100000 */   daddu     $2, $0, $0
    /* FB138 001FB138 7A43013C */  lui        $1, (0x437A0000 >> 16)
    /* FB13C 001FB13C 00008144 */  mtc1       $1, $f0
    /* FB140 001FB140 34080046 */  c.lt.s     $f1, $f0
    /* FB144 001FB144 00000000 */  nop
    /* FB148 001FB148 01000345 */  bc1tl      .L001FB150
    /* FB14C 001FB14C 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001FB150:
    /* FB150 001FB150 2D804000 */  daddu      $16, $2, $0
    /* FB154 001FB154 2D180000 */  daddu      $3, $0, $0
    /* FB158 001FB158 34B01446 */  c.lt.s     $f22, $f20
    /* FB15C 001FB15C 0A181602 */  movz       $3, $16, $22
    /* FB160 001FB160 2610E400 */  xor        $2, $7, $4
    /* FB164 001FB164 6B000045 */  bc1f       .L001FB314
    /* FB168 001FB168 0B806200 */   movn      $16, $3, $2
    /* FB16C 001FB16C 69004012 */  beqz       $18, .L001FB314
    /* FB170 001FB170 00000000 */   nop
    /* FB174 001FB174 0900A010 */  beqz       $5, .L001FB19C
    /* FB178 001FB178 2D20E000 */   daddu     $4, $7, $0
    /* FB17C 001FB17C 1A28040C */  jal        EnableMotionOrientUpdate
    /* FB180 001FB180 000A0524 */   addiu     $5, $0, 0xA00
    /* FB184 001FB184 03004010 */  beqz       $2, .L001FB194
    /* FB188 001FB188 0400828E */   lw        $2, 0x4($20)
    /* FB18C 001FB18C 02000010 */  b          .L001FB198
    /* FB190 001FB190 00104234 */   ori       $2, $2, 0x1000
.align 2
  .L001FB194:
    /* FB194 001FB194 00084234 */  ori        $2, $2, 0x800
.align 2
  .L001FB198:
    /* FB198 001FB198 040082AE */  sw         $2, 0x4($20)
.align 2
  .L001FB19C:
    /* FB19C 001FB19C 04002012 */  beqz       $17, .L001FB1B0
    /* FB1A0 001FB1A0 00000000 */   nop
    /* FB1A4 001FB1A4 0400828E */  lw         $2, 0x4($20)
    /* FB1A8 001FB1A8 00104234 */  ori        $2, $2, 0x1000
    /* FB1AC 001FB1AC 040082AE */  sw         $2, 0x4($20)
.align 2
  .L001FB1B0:
    /* FB1B0 001FB1B0 05000052 */  beql       $16, $0, .L001FB1C8
    /* FB1B4 001FB1B4 700463DE */   ld        $3, 0x470($19)
    /* FB1B8 001FB1B8 0400828E */  lw         $2, 0x4($20)
    /* FB1BC 001FB1BC 00204234 */  ori        $2, $2, 0x2000
    /* FB1C0 001FB1C0 040082AE */  sw         $2, 0x4($20)
    /* FB1C4 001FB1C4 700463DE */  ld         $3, 0x470($19)
.align 2
  .L001FB1C8:
    /* FB1C8 001FB1C8 00786230 */  andi       $2, $3, 0x7800
    /* FB1CC 001FB1CC 2A004010 */  beqz       $2, .L001FB278
    /* FB1D0 001FB1D0 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FB1D4 001FB1D4 F8140300 */  dsll       $2, $3, 19
    /* FB1D8 001FB1D8 3F100200 */  dsra32     $2, $2, 0
    /* FB1DC 001FB1DC 01004230 */  andi       $2, $2, 0x1
    /* FB1E0 001FB1E0 15004010 */  beqz       $2, .L001FB238
    /* FB1E4 001FB1E4 3000A78F */   lw        $7, 0x30($29)
    /* FB1E8 001FB1E8 04000324 */  addiu      $3, $0, 0x4
    /* FB1EC 001FB1EC 0C00E28C */  lw         $2, 0xC($7)
    /* FB1F0 001FB1F0 12004314 */  bne        $2, $3, .L001FB23C
    /* FB1F4 001FB1F4 2D28E000 */   daddu     $5, $7, $0
    /* FB1F8 001FB1F8 A0C1013C */  lui        $1, (0xC1A00000 >> 16)
    /* FB1FC 001FB1FC 00A08144 */  mtc1       $1, $f20
    /* FB200 001FB200 7000A427 */  addiu      $4, $29, 0x70
    /* FB204 001FB204 C210040C */  jal        GetRootMatrixByDObj
    /* FB208 001FB208 80057026 */   addiu     $16, $19, 0x580
    /* FB20C 001FB20C 01B51446 */  sub.s      $f20, $f22, $f20
    /* FB210 001FB210 8000A427 */  addiu      $4, $29, 0x80
    /* FB214 001FB214 2D28A002 */  daddu      $5, $21, $0
    /* FB218 001FB218 0E00090C */  jal        func_00240038
    /* FB21C 001FB21C 07A30046 */   neg.s     $f12, $f20
    /* FB220 001FB220 2D200002 */  daddu      $4, $16, $0
    /* FB224 001FB224 7000A527 */  addiu      $5, $29, 0x70
    /* FB228 001FB228 FCFF080C */  jal        func_0023FFF0
    /* FB22C 001FB22C 8000A627 */   addiu     $6, $29, 0x80
    /* FB230 001FB230 11000010 */  b          .L001FB278
    /* FB234 001FB234 3400A1C7 */   lwc1      $f1, 0x34($29)
.align 2
  .L001FB238:
    /* FB238 001FB238 2D28E000 */  daddu      $5, $7, $0
.align 2
  .L001FB23C:
    /* FB23C 001FB23C A040013C */  lui        $1, (0x40A00000 >> 16)
    /* FB240 001FB240 00A08144 */  mtc1       $1, $f20
    /* FB244 001FB244 7000A427 */  addiu      $4, $29, 0x70
    /* FB248 001FB248 C210040C */  jal        GetRootMatrixByDObj
    /* FB24C 001FB24C 80057026 */   addiu     $16, $19, 0x580
    /* FB250 001FB250 01B51446 */  sub.s      $f20, $f22, $f20
    /* FB254 001FB254 8000A427 */  addiu      $4, $29, 0x80
    /* FB258 001FB258 2D28A002 */  daddu      $5, $21, $0
    /* FB25C 001FB25C 0E00090C */  jal        func_00240038
    /* FB260 001FB260 07A30046 */   neg.s     $f12, $f20
    /* FB264 001FB264 2D200002 */  daddu      $4, $16, $0
    /* FB268 001FB268 7000A527 */  addiu      $5, $29, 0x70
    /* FB26C 001FB26C FCFF080C */  jal        func_0023FFF0
    /* FB270 001FB270 8000A627 */   addiu     $6, $29, 0x80
    /* FB274 001FB274 3400A1C7 */  lwc1       $f1, 0x34($29)
.align 2
  .L001FB278:
    /* FB278 001FB278 A042013C */  lui        $1, (0x42A00000 >> 16)
    /* FB27C 001FB27C 00008144 */  mtc1       $1, $f0
    /* FB280 001FB280 34000146 */  c.lt.s     $f0, $f1
    /* FB284 001FB284 00000000 */  nop
    /* FB288 001FB288 11000045 */  bc1f       .L001FB2D0
    /* FB28C 001FB28C 3000A48F */   lw        $4, 0x30($29)
    /* FB290 001FB290 3443013C */  lui        $1, (0x43340000 >> 16)
    /* FB294 001FB294 00008144 */  mtc1       $1, $f0
    /* FB298 001FB298 34080046 */  c.lt.s     $f1, $f0
    /* FB29C 001FB29C 00000000 */  nop
    /* FB2A0 001FB2A0 0B000045 */  bc1f       .L001FB2D0
    /* FB2A4 001FB2A4 AC01A58F */   lw        $5, 0x1AC($29)
    /* FB2A8 001FB2A8 11000224 */  addiu      $2, $0, 0x11
    /* FB2AC 001FB2AC 0C00A38C */  lw         $3, 0xC($5)
    /* FB2B0 001FB2B0 04006214 */  bne        $3, $2, .L001FB2C4
    /* FB2B4 001FB2B4 0400828E */   lw        $2, 0x4($20)
    /* FB2B8 001FB2B8 0100033C */  lui        $3, (0x10000 >> 16)
    /* FB2BC 001FB2BC 02000010 */  b          .L001FB2C8
    /* FB2C0 001FB2C0 25104300 */   or        $2, $2, $3
.align 2
  .L001FB2C4:
    /* FB2C4 001FB2C4 00804234 */  ori        $2, $2, 0x8000
.align 2
  .L001FB2C8:
    /* FB2C8 001FB2C8 040082AE */  sw         $2, 0x4($20)
    /* FB2CC 001FB2CC 3000A48F */  lw         $4, 0x30($29)
.align 2
  .L001FB2D0:
    /* FB2D0 001FB2D0 1A28040C */  jal        EnableMotionOrientUpdate
    /* FB2D4 001FB2D4 00200524 */   addiu     $5, $0, 0x2000
    /* FB2D8 001FB2D8 0E004010 */  beqz       $2, .L001FB314
    /* FB2DC 001FB2DC 00000000 */   nop
    /* FB2E0 001FB2E0 A042013C */  lui        $1, (0x42A00000 >> 16)
    /* FB2E4 001FB2E4 00008144 */  mtc1       $1, $f0
    /* FB2E8 001FB2E8 34001746 */  c.lt.s     $f0, $f23
    /* FB2EC 001FB2EC 09000045 */  bc1f       .L001FB314
    /* FB2F0 001FB2F0 00000000 */   nop
    /* FB2F4 001FB2F4 3443013C */  lui        $1, (0x43340000 >> 16)
    /* FB2F8 001FB2F8 00008144 */  mtc1       $1, $f0
    /* FB2FC 001FB2FC 34B80046 */  c.lt.s     $f23, $f0
    /* FB300 001FB300 04000045 */  bc1f       .L001FB314
    /* FB304 001FB304 00000000 */   nop
    /* FB308 001FB308 0400828E */  lw         $2, 0x4($20)
    /* FB30C 001FB30C 02004234 */  ori        $2, $2, 0x2
    /* FB310 001FB310 040082AE */  sw         $2, 0x4($20)
.align 2
  .L001FB314:
    /* FB314 001FB314 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FB318 001FB318 00008144 */  mtc1       $1, $f0
    /* FB31C 001FB31C 34B00046 */  c.lt.s     $f22, $f0
    /* FB320 001FB320 00000000 */  nop
    /* FB324 001FB324 75010045 */  bc1f       .L001FB8FC
    /* FB328 001FB328 AC01A68F */   lw        $6, 0x1AC($29)
    /* FB32C 001FB32C 10000224 */  addiu      $2, $0, 0x10
    /* FB330 001FB330 0C00C38C */  lw         $3, 0xC($6)
    /* FB334 001FB334 3C006214 */  bne        $3, $2, .L001FB428
    /* FB338 001FB338 11000224 */   addiu     $2, $0, 0x11
    /* FB33C 001FB33C 3000A78F */  lw         $7, 0x30($29)
    /* FB340 001FB340 F491888F */  lw         $8, %gp_rel(D_00629DE4)($28)
    /* FB344 001FB344 2041013C */  lui        $1, (0x41200000 >> 16)
    /* FB348 001FB348 00A08144 */  mtc1       $1, $f20
    /* FB34C 001FB34C 0300E814 */  bne        $7, $8, .L001FB35C
    /* FB350 001FB350 6100023C */   lui       $2, %hi(D_006138D0)
    /* FB354 001FB354 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FB358 001FB358 00A08144 */  mtc1       $1, $f20
.align 2
  .L001FB35C:
    /* FB35C 001FB35C 6401E68C */  lw         $6, 0x164($7)
    /* FB360 001FB360 D0384324 */  addiu      $3, $2, %lo(D_006138D0)
    /* FB364 001FB364 D03844DC */  ld         $4, %lo(D_006138D0)($2)
    /* FB368 001FB368 080065DC */  ld         $5, 0x8($3)
    /* FB36C 001FB36C 7000B227 */  addiu      $18, $29, 0x70
    /* FB370 001FB370 7000A4FF */  sd         $4, 0x70($29)
    /* FB374 001FB374 7800A5FF */  sd         $5, 0x78($29)
    /* FB378 001FB378 A004C0C4 */  lwc1       $f0, 0x4A0($6)
    /* FB37C 001FB37C A404C1C4 */  lwc1       $f1, 0x4A4($6)
    /* FB380 001FB380 A804C2C4 */  lwc1       $f2, 0x4A8($6)
    /* FB384 001FB384 5005C0E4 */  swc1       $f0, 0x550($6)
    /* FB388 001FB388 5405C1E4 */  swc1       $f1, 0x554($6)
    /* FB38C 001FB38C 0400E814 */  bne        $7, $8, .L001FB3A0
    /* FB390 001FB390 5805C2E4 */   swc1      $f2, 0x558($6)
    /* FB394 001FB394 7000A0C7 */  lwc1       $f0, 0x70($29)
    /* FB398 001FB398 07000046 */  neg.s      $f0, $f0
    /* FB39C 001FB39C 7000A0E7 */  swc1       $f0, 0x70($29)
.align 2
  .L001FB3A0:
    /* FB3A0 001FB3A0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FB3A4 001FB3A4 00008144 */  mtc1       $1, $f0
    /* FB3A8 001FB3A8 A005C424 */  addiu      $4, $6, 0x5A0
    /* FB3AC 001FB3AC 2D304002 */  daddu      $6, $18, $0
    /* FB3B0 001FB3B0 A0057026 */  addiu      $16, $19, 0x5A0
    /* FB3B4 001FB3B4 0C0040E6 */  swc1       $f0, 0xC($18)
    /* FB3B8 001FB3B8 AC01A78F */  lw         $7, 0x1AC($29)
    /* FB3BC 001FB3BC 5C01E28C */  lw         $2, 0x15C($7)
    /* FB3C0 001FB3C0 76FF080C */  jal        func_0023FDD8
    /* FB3C4 001FB3C4 0C00458C */   lw        $5, 0xC($2)
    /* FB3C8 001FB3C8 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FB3CC 001FB3CC 00608144 */  mtc1       $1, $f12
    /* FB3D0 001FB3D0 2D200002 */  daddu      $4, $16, $0
    /* FB3D4 001FB3D4 2D280000 */  daddu      $5, $0, $0
    /* FB3D8 001FB3D8 FF000624 */  addiu      $6, $0, 0xFF
    /* FB3DC 001FB3DC 1012060C */  jal        debug_Marker
    /* FB3E0 001FB3E0 2D380000 */   daddu     $7, $0, $0
    /* FB3E4 001FB3E4 2D280002 */  daddu      $5, $16, $0
    /* FB3E8 001FB3E8 D846060C */  jal        RotateAccordingToStick_PatternThree
    /* FB3EC 001FB3EC 2D20A003 */   daddu     $4, $29, $0
    /* FB3F0 001FB3F0 42A01446 */  mul.s      $f1, $f20, $f20
    /* FB3F4 001FB3F4 34000146 */  c.lt.s     $f0, $f1
    /* FB3F8 001FB3F8 00000000 */  nop
    /* FB3FC 001FB3FC 08000045 */  bc1f       .L001FB420
    /* FB400 001FB400 AC01A98F */   lw        $9, 0x1AC($29)
    /* FB404 001FB404 0400828E */  lw         $2, 0x4($20)
    /* FB408 001FB408 01004234 */  ori        $2, $2, 0x1
    /* FB40C 001FB40C 040082AE */  sw         $2, 0x4($20)
    /* FB410 001FB410 AC01A88F */  lw         $8, 0x1AC($29)
    /* FB414 001FB414 6C01A8AE */  sw         $8, 0x16C($21)
    /* FB418 001FB418 02000010 */  b          .L001FB424
    /* FB41C 001FB41C 0C00038D */   lw        $3, 0xC($8)
.align 2
  .L001FB420:
    /* FB420 001FB420 0C00238D */  lw         $3, 0xC($9)
.align 2
  .L001FB424:
    /* FB424 001FB424 11000224 */  addiu      $2, $0, 0x11
.align 2
  .L001FB428:
    /* FB428 001FB428 25006214 */  bne        $3, $2, .L001FB4C0
    /* FB42C 001FB42C 12000224 */   addiu     $2, $0, 0x12
    /* FB430 001FB430 3000A48F */  lw         $4, 0x30($29)
    /* FB434 001FB434 1A28040C */  jal        EnableMotionOrientUpdate
    /* FB438 001FB438 000B0524 */   addiu     $5, $0, 0xB00
    /* FB43C 001FB43C 18004014 */  bnez       $2, .L001FB4A0
    /* FB440 001FB440 AC01A68F */   lw        $6, 0x1AC($29)
    /* FB444 001FB444 0400828E */  lw         $2, 0x4($20)
    /* FB448 001FB448 0040033C */  lui        $3, (0x40000000 >> 16)
    /* FB44C 001FB44C AC01A48F */  lw         $4, 0x1AC($29)
    /* FB450 001FB450 25104300 */  or         $2, $2, $3
    /* FB454 001FB454 040082AE */  sw         $2, 0x4($20)
    /* FB458 001FB458 AC01A28F */  lw         $2, 0x1AC($29)
    /* FB45C 001FB45C 50F6060C */  jal        GetBoxGlobalHoldPoint
    /* FB460 001FB460 4001A2AE */   sw        $2, 0x140($21)
    /* FB464 001FB464 10004010 */  beqz       $2, .L001FB4A8
    /* FB468 001FB468 3000A68F */   lw        $6, 0x30($29)
    /* FB46C 001FB46C 7000A427 */  addiu      $4, $29, 0x70
    /* FB470 001FB470 F4F1060C */  jal        moveBoxAutoMatic
    /* FB474 001FB474 AC01A58F */   lw        $5, 0x1AC($29)
    /* FB478 001FB478 0E004010 */  beqz       $2, .L001FB4B4
    /* FB47C 001FB47C 0020033C */   lui       $3, (0x20000000 >> 16)
    /* FB480 001FB480 0400828E */  lw         $2, 0x4($20)
    /* FB484 001FB484 25104300 */  or         $2, $2, $3
    /* FB488 001FB488 040082AE */  sw         $2, 0x4($20)
    /* FB48C 001FB48C AC01A38F */  lw         $3, 0x1AC($29)
    /* FB490 001FB490 4401A3AE */  sw         $3, 0x144($21)
    /* FB494 001FB494 AC01A58F */  lw         $5, 0x1AC($29)
    /* FB498 001FB498 08000010 */  b          .L001FB4BC
    /* FB49C 001FB49C 0C00A38C */   lw        $3, 0xC($5)
.align 2
  .L001FB4A0:
    /* FB4A0 001FB4A0 06000010 */  b          .L001FB4BC
    /* FB4A4 001FB4A4 0C00C38C */   lw        $3, 0xC($6)
.align 2
  .L001FB4A8:
    /* FB4A8 001FB4A8 AC01A78F */  lw         $7, 0x1AC($29)
    /* FB4AC 001FB4AC 03000010 */  b          .L001FB4BC
    /* FB4B0 001FB4B0 0C00E38C */   lw        $3, 0xC($7)
.align 2
  .L001FB4B4:
    /* FB4B4 001FB4B4 AC01A88F */  lw         $8, 0x1AC($29)
    /* FB4B8 001FB4B8 0C00038D */  lw         $3, 0xC($8)
.align 2
  .L001FB4BC:
    /* FB4BC 001FB4BC 12000224 */  addiu      $2, $0, 0x12
.align 2
  .L001FB4C0:
    /* FB4C0 001FB4C0 10006214 */  bne        $3, $2, .L001FB504
    /* FB4C4 001FB4C4 17000224 */   addiu     $2, $0, 0x17
    /* FB4C8 001FB4C8 3000A48F */  lw         $4, 0x30($29)
    /* FB4CC 001FB4CC 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FB4D0 001FB4D0 00070524 */   addiu     $5, $0, 0x700
    /* FB4D4 001FB4D4 09004010 */  beqz       $2, .L001FB4FC
    /* FB4D8 001FB4D8 AC01A28F */   lw        $2, 0x1AC($29)
    /* FB4DC 001FB4DC 0400828E */  lw         $2, 0x4($20)
    /* FB4E0 001FB4E0 0080033C */  lui        $3, (0x80000000 >> 16)
    /* FB4E4 001FB4E4 25104300 */  or         $2, $2, $3
    /* FB4E8 001FB4E8 040082AE */  sw         $2, 0x4($20)
    /* FB4EC 001FB4EC AC01A98F */  lw         $9, 0x1AC($29)
    /* FB4F0 001FB4F0 4801A9AE */  sw         $9, 0x148($21)
    /* FB4F4 001FB4F4 02000010 */  b          .L001FB500
    /* FB4F8 001FB4F8 0C00238D */   lw        $3, 0xC($9)
.align 2
  .L001FB4FC:
    /* FB4FC 001FB4FC 0C00438C */  lw         $3, 0xC($2)
.align 2
  .L001FB500:
    /* FB500 001FB500 17000224 */  addiu      $2, $0, 0x17
.align 2
  .L001FB504:
    /* FB504 001FB504 3E006214 */  bne        $3, $2, .L001FB600
    /* FB508 001FB508 16000224 */   addiu     $2, $0, 0x16
    /* FB50C 001FB50C 3000A48F */  lw         $4, 0x30($29)
    /* FB510 001FB510 1A28040C */  jal        EnableMotionOrientUpdate
    /* FB514 001FB514 00050524 */   addiu     $5, $0, 0x500
    /* FB518 001FB518 36004010 */  beqz       $2, .L001FB5F4
    /* FB51C 001FB51C F000B226 */   addiu     $18, $21, 0xF0
    /* FB520 001FB520 0800828E */  lw         $2, 0x8($20)
    /* FB524 001FB524 3000A48F */  lw         $4, 0x30($29)
    /* FB528 001FB528 03001124 */  addiu      $17, $0, 0x3
    /* FB52C 001FB52C 01004234 */  ori        $2, $2, 0x1
    /* FB530 001FB530 080082AE */  sw         $2, 0x8($20)
    /* FB534 001FB534 B001A38F */  lw         $3, 0x1B0($29)
    /* FB538 001FB538 6401828C */  lw         $2, 0x164($4)
    /* FB53C 001FB53C 5001A3AE */  sw         $3, 0x150($21)
    /* FB540 001FB540 A0045624 */  addiu      $22, $2, 0x4A0
    /* FB544 001FB544 AC01A58F */  lw         $5, 0x1AC($29)
    /* FB548 001FB548 4C01A5AE */  sw         $5, 0x14C($21)
    /* FB54C 001FB54C 5C01838C */  lw         $3, 0x15C($4)
    /* FB550 001FB550 8000A0AF */  sw         $0, 0x80($29)
    /* FB554 001FB554 7801628C */  lw         $2, 0x178($3)
    /* FB558 001FB558 8400A0AF */  sw         $0, 0x84($29)
    /* FB55C 001FB55C 8800A0AF */  sw         $0, 0x88($29)
    /* FB560 001FB560 2D804000 */  daddu      $16, $2, $0
    /* FB564 001FB564 8000A427 */  addiu      $4, $29, 0x80
.align 2
  .L001FB568:
    /* FB568 001FB568 2D300002 */  daddu      $6, $16, $0
    /* FB56C 001FB56C 2D288000 */  daddu      $5, $4, $0
    /* FB570 001FB570 FCFF080C */  jal        func_0023FFF0
    /* FB574 001FB574 10001026 */   addiu     $16, $16, 0x10
    /* FB578 001FB578 FFFF3126 */  addiu      $17, $17, -0x1
    /* FB57C 001FB57C FAFF2106 */  bgez       $17, .L001FB568
    /* FB580 001FB580 8000A427 */   addiu     $4, $29, 0x80
    /* FB584 001FB584 803E013C */  lui        $1, (0x3E800000 >> 16)
    /* FB588 001FB588 00608144 */  mtc1       $1, $f12
    /* FB58C 001FB58C 2D204002 */  daddu      $4, $18, $0
    /* FB590 001FB590 0E00090C */  jal        func_00240038
    /* FB594 001FB594 8000A527 */   addiu     $5, $29, 0x80
    /* FB598 001FB598 AC01A68F */  lw         $6, 0x1AC($29)
    /* FB59C 001FB59C 0900C010 */  beqz       $6, .L001FB5C4
    /* FB5A0 001FB5A0 2D204002 */   daddu     $4, $18, $0
    /* FB5A4 001FB5A4 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FB5A8 001FB5A8 00008144 */  mtc1       $1, $f0
    /* FB5AC 001FB5AC 2D304002 */  daddu      $6, $18, $0
    /* FB5B0 001FB5B0 0C0040E6 */  swc1       $f0, 0xC($18)
    /* FB5B4 001FB5B4 AC01A78F */  lw         $7, 0x1AC($29)
    /* FB5B8 001FB5B8 5C01E28C */  lw         $2, 0x15C($7)
    /* FB5BC 001FB5BC 76FF080C */  jal        func_0023FDD8
    /* FB5C0 001FB5C0 0C00458C */   lw        $5, 0xC($2)
.align 2
  .L001FB5C4:
    /* FB5C4 001FB5C4 A040013C */  lui        $1, (0x40A00000 >> 16)
    /* FB5C8 001FB5C8 00608144 */  mtc1       $1, $f12
    /* FB5CC 001FB5CC 2D28C002 */  daddu      $5, $22, $0
    /* FB5D0 001FB5D0 0E00090C */  jal        func_00240038
    /* FB5D4 001FB5D4 7000A427 */   addiu     $4, $29, 0x70
    /* FB5D8 001FB5D8 2D204002 */  daddu      $4, $18, $0
    /* FB5DC 001FB5DC 7000A627 */  addiu      $6, $29, 0x70
    /* FB5E0 001FB5E0 FCFF080C */  jal        func_0023FFF0
    /* FB5E4 001FB5E4 2D288000 */   daddu     $5, $4, $0
    /* FB5E8 001FB5E8 AC01A88F */  lw         $8, 0x1AC($29)
    /* FB5EC 001FB5EC 03000010 */  b          .L001FB5FC
    /* FB5F0 001FB5F0 0C00038D */   lw        $3, 0xC($8)
.align 2
  .L001FB5F4:
    /* FB5F4 001FB5F4 AC01A98F */  lw         $9, 0x1AC($29)
    /* FB5F8 001FB5F8 0C00238D */  lw         $3, 0xC($9)
.align 2
  .L001FB5FC:
    /* FB5FC 001FB5FC 16000224 */  addiu      $2, $0, 0x16
.align 2
  .L001FB600:
    /* FB600 001FB600 42006214 */  bne        $3, $2, .L001FB70C
    /* FB604 001FB604 18000224 */   addiu     $2, $0, 0x18
    /* FB608 001FB608 3000A48F */  lw         $4, 0x30($29)
    /* FB60C 001FB60C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FB610 001FB610 00050524 */   addiu     $5, $0, 0x500
    /* FB614 001FB614 38004010 */  beqz       $2, .L001FB6F8
    /* FB618 001FB618 AC01A68F */   lw        $6, 0x1AC($29)
    /* FB61C 001FB61C 4EF7060C */  jal        InitWallLeverGeo
    /* FB620 001FB620 AC01A48F */   lw        $4, 0x1AC($29)
    /* FB624 001FB624 36004010 */  beqz       $2, .L001FB700
    /* FB628 001FB628 F000B226 */   addiu     $18, $21, 0xF0
    /* FB62C 001FB62C 0800828E */  lw         $2, 0x8($20)
    /* FB630 001FB630 3000A48F */  lw         $4, 0x30($29)
    /* FB634 001FB634 03001124 */  addiu      $17, $0, 0x3
    /* FB638 001FB638 02004234 */  ori        $2, $2, 0x2
    /* FB63C 001FB63C 080082AE */  sw         $2, 0x8($20)
    /* FB640 001FB640 AC01A28F */  lw         $2, 0x1AC($29)
    /* FB644 001FB644 4C01A2AE */  sw         $2, 0x14C($21)
    /* FB648 001FB648 6401828C */  lw         $2, 0x164($4)
    /* FB64C 001FB64C 5C01838C */  lw         $3, 0x15C($4)
    /* FB650 001FB650 8000A0AF */  sw         $0, 0x80($29)
    /* FB654 001FB654 A0045624 */  addiu      $22, $2, 0x4A0
    /* FB658 001FB658 7801628C */  lw         $2, 0x178($3)
    /* FB65C 001FB65C 8400A0AF */  sw         $0, 0x84($29)
    /* FB660 001FB660 8800A0AF */  sw         $0, 0x88($29)
    /* FB664 001FB664 2D804000 */  daddu      $16, $2, $0
    /* FB668 001FB668 8000A427 */  addiu      $4, $29, 0x80
    /* FB66C 001FB66C 00000000 */  nop
.align 2
  .L001FB670:
    /* FB670 001FB670 2D300002 */  daddu      $6, $16, $0
    /* FB674 001FB674 2D288000 */  daddu      $5, $4, $0
    /* FB678 001FB678 FCFF080C */  jal        func_0023FFF0
    /* FB67C 001FB67C 10001026 */   addiu     $16, $16, 0x10
    /* FB680 001FB680 FFFF3126 */  addiu      $17, $17, -0x1
    /* FB684 001FB684 FAFF2106 */  bgez       $17, .L001FB670
    /* FB688 001FB688 8000A427 */   addiu     $4, $29, 0x80
    /* FB68C 001FB68C 803E013C */  lui        $1, (0x3E800000 >> 16)
    /* FB690 001FB690 00608144 */  mtc1       $1, $f12
    /* FB694 001FB694 2D204002 */  daddu      $4, $18, $0
    /* FB698 001FB698 0E00090C */  jal        func_00240038
    /* FB69C 001FB69C 8000A527 */   addiu     $5, $29, 0x80
    /* FB6A0 001FB6A0 AC01A38F */  lw         $3, 0x1AC($29)
    /* FB6A4 001FB6A4 08006010 */  beqz       $3, .L001FB6C8
    /* FB6A8 001FB6A8 2D204002 */   daddu     $4, $18, $0
    /* FB6AC 001FB6AC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FB6B0 001FB6B0 00008144 */  mtc1       $1, $f0
    /* FB6B4 001FB6B4 2D304002 */  daddu      $6, $18, $0
    /* FB6B8 001FB6B8 0C0040E6 */  swc1       $f0, 0xC($18)
    /* FB6BC 001FB6BC 5C01628C */  lw         $2, 0x15C($3)
    /* FB6C0 001FB6C0 76FF080C */  jal        func_0023FDD8
    /* FB6C4 001FB6C4 0C00458C */   lw        $5, 0xC($2)
.align 2
  .L001FB6C8:
    /* FB6C8 001FB6C8 A040013C */  lui        $1, (0x40A00000 >> 16)
    /* FB6CC 001FB6CC 00608144 */  mtc1       $1, $f12
    /* FB6D0 001FB6D0 2D28C002 */  daddu      $5, $22, $0
    /* FB6D4 001FB6D4 0E00090C */  jal        func_00240038
    /* FB6D8 001FB6D8 7000A427 */   addiu     $4, $29, 0x70
    /* FB6DC 001FB6DC 2D204002 */  daddu      $4, $18, $0
    /* FB6E0 001FB6E0 7000A627 */  addiu      $6, $29, 0x70
    /* FB6E4 001FB6E4 FCFF080C */  jal        func_0023FFF0
    /* FB6E8 001FB6E8 2D288000 */   daddu     $5, $4, $0
    /* FB6EC 001FB6EC AC01A58F */  lw         $5, 0x1AC($29)
    /* FB6F0 001FB6F0 05000010 */  b          .L001FB708
    /* FB6F4 001FB6F4 0C00A38C */   lw        $3, 0xC($5)
.align 2
  .L001FB6F8:
    /* FB6F8 001FB6F8 03000010 */  b          .L001FB708
    /* FB6FC 001FB6FC 0C00C38C */   lw        $3, 0xC($6)
.align 2
  .L001FB700:
    /* FB700 001FB700 AC01A78F */  lw         $7, 0x1AC($29)
    /* FB704 001FB704 0C00E38C */  lw         $3, 0xC($7)
.align 2
  .L001FB708:
    /* FB708 001FB708 18000224 */  addiu      $2, $0, 0x18
.align 2
  .L001FB70C:
    /* FB70C 001FB70C 41006214 */  bne        $3, $2, .L001FB814
    /* FB710 001FB710 19000224 */   addiu     $2, $0, 0x19
    /* FB714 001FB714 3000A48F */  lw         $4, 0x30($29)
    /* FB718 001FB718 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FB71C 001FB71C 00060524 */   addiu     $5, $0, 0x600
    /* FB720 001FB720 37004010 */  beqz       $2, .L001FB800
    /* FB724 001FB724 AC01A58F */   lw        $5, 0x1AC($29)
    /* FB728 001FB728 DAF7060C */  jal        func_001BDF68
    /* FB72C 001FB72C AC01A48F */   lw        $4, 0x1AC($29)
    /* FB730 001FB730 35004010 */  beqz       $2, .L001FB808
    /* FB734 001FB734 F000B226 */   addiu     $18, $21, 0xF0
    /* FB738 001FB738 0800828E */  lw         $2, 0x8($20)
    /* FB73C 001FB73C 3000A48F */  lw         $4, 0x30($29)
    /* FB740 001FB740 03001124 */  addiu      $17, $0, 0x3
    /* FB744 001FB744 04004234 */  ori        $2, $2, 0x4
    /* FB748 001FB748 080082AE */  sw         $2, 0x8($20)
    /* FB74C 001FB74C AC01A88F */  lw         $8, 0x1AC($29)
    /* FB750 001FB750 6401828C */  lw         $2, 0x164($4)
    /* FB754 001FB754 4C01A8AE */  sw         $8, 0x14C($21)
    /* FB758 001FB758 A0045624 */  addiu      $22, $2, 0x4A0
    /* FB75C 001FB75C 5C01838C */  lw         $3, 0x15C($4)
    /* FB760 001FB760 8000A0AF */  sw         $0, 0x80($29)
    /* FB764 001FB764 7801628C */  lw         $2, 0x178($3)
    /* FB768 001FB768 8400A0AF */  sw         $0, 0x84($29)
    /* FB76C 001FB76C 8800A0AF */  sw         $0, 0x88($29)
    /* FB770 001FB770 2D804000 */  daddu      $16, $2, $0
    /* FB774 001FB774 8000A427 */  addiu      $4, $29, 0x80
.align 2
  .L001FB778:
    /* FB778 001FB778 2D300002 */  daddu      $6, $16, $0
    /* FB77C 001FB77C 2D288000 */  daddu      $5, $4, $0
    /* FB780 001FB780 FCFF080C */  jal        func_0023FFF0
    /* FB784 001FB784 10001026 */   addiu     $16, $16, 0x10
    /* FB788 001FB788 FFFF3126 */  addiu      $17, $17, -0x1
    /* FB78C 001FB78C FAFF2106 */  bgez       $17, .L001FB778
    /* FB790 001FB790 8000A427 */   addiu     $4, $29, 0x80
    /* FB794 001FB794 803E013C */  lui        $1, (0x3E800000 >> 16)
    /* FB798 001FB798 00608144 */  mtc1       $1, $f12
    /* FB79C 001FB79C 2D204002 */  daddu      $4, $18, $0
    /* FB7A0 001FB7A0 0E00090C */  jal        func_00240038
    /* FB7A4 001FB7A4 8000A527 */   addiu     $5, $29, 0x80
    /* FB7A8 001FB7A8 AC01A98F */  lw         $9, 0x1AC($29)
    /* FB7AC 001FB7AC 08002011 */  beqz       $9, .L001FB7D0
    /* FB7B0 001FB7B0 2D204002 */   daddu     $4, $18, $0
    /* FB7B4 001FB7B4 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FB7B8 001FB7B8 00008144 */  mtc1       $1, $f0
    /* FB7BC 001FB7BC 2D304002 */  daddu      $6, $18, $0
    /* FB7C0 001FB7C0 0C0040E6 */  swc1       $f0, 0xC($18)
    /* FB7C4 001FB7C4 5C01228D */  lw         $2, 0x15C($9)
    /* FB7C8 001FB7C8 76FF080C */  jal        func_0023FDD8
    /* FB7CC 001FB7CC 0C00458C */   lw        $5, 0xC($2)
.align 2
  .L001FB7D0:
    /* FB7D0 001FB7D0 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FB7D4 001FB7D4 00608144 */  mtc1       $1, $f12
    /* FB7D8 001FB7D8 2D28C002 */  daddu      $5, $22, $0
    /* FB7DC 001FB7DC 0E00090C */  jal        func_00240038
    /* FB7E0 001FB7E0 7000A427 */   addiu     $4, $29, 0x70
    /* FB7E4 001FB7E4 2D204002 */  daddu      $4, $18, $0
    /* FB7E8 001FB7E8 7000A627 */  addiu      $6, $29, 0x70
    /* FB7EC 001FB7EC FCFF080C */  jal        func_0023FFF0
    /* FB7F0 001FB7F0 2D288000 */   daddu     $5, $4, $0
    /* FB7F4 001FB7F4 AC01A28F */  lw         $2, 0x1AC($29)
    /* FB7F8 001FB7F8 05000010 */  b          .L001FB810
    /* FB7FC 001FB7FC 0C00438C */   lw        $3, 0xC($2)
.align 2
  .L001FB800:
    /* FB800 001FB800 03000010 */  b          .L001FB810
    /* FB804 001FB804 0C00A38C */   lw        $3, 0xC($5)
.align 2
  .L001FB808:
    /* FB808 001FB808 AC01A68F */  lw         $6, 0x1AC($29)
    /* FB80C 001FB80C 0C00C38C */  lw         $3, 0xC($6)
.align 2
  .L001FB810:
    /* FB810 001FB810 19000224 */  addiu      $2, $0, 0x19
.align 2
  .L001FB814:
    /* FB814 001FB814 39006214 */  bne        $3, $2, .L001FB8FC
    /* FB818 001FB818 3000A48F */   lw        $4, 0x30($29)
    /* FB81C 001FB81C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FB820 001FB820 00060524 */   addiu     $5, $0, 0x600
    /* FB824 001FB824 35004010 */  beqz       $2, .L001FB8FC
    /* FB828 001FB828 00000000 */   nop
    /* FB82C 001FB82C DAF7060C */  jal        func_001BDF68
    /* FB830 001FB830 AC01A48F */   lw        $4, 0x1AC($29)
    /* FB834 001FB834 31004010 */  beqz       $2, .L001FB8FC
    /* FB838 001FB838 F000B226 */   addiu     $18, $21, 0xF0
    /* FB83C 001FB83C 0800828E */  lw         $2, 0x8($20)
    /* FB840 001FB840 3000A48F */  lw         $4, 0x30($29)
    /* FB844 001FB844 03001124 */  addiu      $17, $0, 0x3
    /* FB848 001FB848 08004234 */  ori        $2, $2, 0x8
    /* FB84C 001FB84C 080082AE */  sw         $2, 0x8($20)
    /* FB850 001FB850 AC01A78F */  lw         $7, 0x1AC($29)
    /* FB854 001FB854 6401828C */  lw         $2, 0x164($4)
    /* FB858 001FB858 4C01A7AE */  sw         $7, 0x14C($21)
    /* FB85C 001FB85C A0045624 */  addiu      $22, $2, 0x4A0
    /* FB860 001FB860 5C01838C */  lw         $3, 0x15C($4)
    /* FB864 001FB864 8000A0AF */  sw         $0, 0x80($29)
    /* FB868 001FB868 7801628C */  lw         $2, 0x178($3)
    /* FB86C 001FB86C 8400A0AF */  sw         $0, 0x84($29)
    /* FB870 001FB870 8800A0AF */  sw         $0, 0x88($29)
    /* FB874 001FB874 2D804000 */  daddu      $16, $2, $0
    /* FB878 001FB878 8000A427 */  addiu      $4, $29, 0x80
    /* FB87C 001FB87C 00000000 */  nop
.align 2
  .L001FB880:
    /* FB880 001FB880 2D300002 */  daddu      $6, $16, $0
    /* FB884 001FB884 2D288000 */  daddu      $5, $4, $0
    /* FB888 001FB888 FCFF080C */  jal        func_0023FFF0
    /* FB88C 001FB88C 10001026 */   addiu     $16, $16, 0x10
    /* FB890 001FB890 FFFF3126 */  addiu      $17, $17, -0x1
    /* FB894 001FB894 FAFF2106 */  bgez       $17, .L001FB880
    /* FB898 001FB898 8000A427 */   addiu     $4, $29, 0x80
    /* FB89C 001FB89C 803E013C */  lui        $1, (0x3E800000 >> 16)
    /* FB8A0 001FB8A0 00608144 */  mtc1       $1, $f12
    /* FB8A4 001FB8A4 2D204002 */  daddu      $4, $18, $0
    /* FB8A8 001FB8A8 0E00090C */  jal        func_00240038
    /* FB8AC 001FB8AC 8000A527 */   addiu     $5, $29, 0x80
    /* FB8B0 001FB8B0 AC01A88F */  lw         $8, 0x1AC($29)
    /* FB8B4 001FB8B4 08000011 */  beqz       $8, .L001FB8D8
    /* FB8B8 001FB8B8 2D204002 */   daddu     $4, $18, $0
    /* FB8BC 001FB8BC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FB8C0 001FB8C0 00008144 */  mtc1       $1, $f0
    /* FB8C4 001FB8C4 2D304002 */  daddu      $6, $18, $0
    /* FB8C8 001FB8C8 0C0040E6 */  swc1       $f0, 0xC($18)
    /* FB8CC 001FB8CC 5C01028D */  lw         $2, 0x15C($8)
    /* FB8D0 001FB8D0 76FF080C */  jal        func_0023FDD8
    /* FB8D4 001FB8D4 0C00458C */   lw        $5, 0xC($2)
.align 2
  .L001FB8D8:
    /* FB8D8 001FB8D8 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FB8DC 001FB8DC 00608144 */  mtc1       $1, $f12
    /* FB8E0 001FB8E0 2D28C002 */  daddu      $5, $22, $0
    /* FB8E4 001FB8E4 0E00090C */  jal        func_00240038
    /* FB8E8 001FB8E8 7000A427 */   addiu     $4, $29, 0x70
    /* FB8EC 001FB8EC 2D204002 */  daddu      $4, $18, $0
    /* FB8F0 001FB8F0 7000A627 */  addiu      $6, $29, 0x70
    /* FB8F4 001FB8F4 FCFF080C */  jal        func_0023FFF0
    /* FB8F8 001FB8F8 2D288000 */   daddu     $5, $4, $0
.align 2
  .L001FB8FC:
    /* FB8FC 001FB8FC 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FB900 001FB900 00008144 */  mtc1       $1, $f0
    /* FB904 001FB904 34B00046 */  c.lt.s     $f22, $f0
    /* FB908 001FB908 00000000 */  nop
    /* FB90C 001FB90C 38000045 */  bc1f       .L001FB9F0
    /* FB910 001FB910 3000A48F */   lw        $4, 0x30($29)
    /* FB914 001FB914 1A28040C */  jal        EnableMotionOrientUpdate
    /* FB918 001FB918 00040524 */   addiu     $5, $0, 0x400
    /* FB91C 001FB91C 2C004010 */  beqz       $2, .L001FB9D0
    /* FB920 001FB920 C000B626 */   addiu     $22, $21, 0xC0
    /* FB924 001FB924 0800828E */  lw         $2, 0x8($20)
    /* FB928 001FB928 3000A38F */  lw         $3, 0x30($29)
    /* FB92C 001FB92C 7000B227 */  addiu      $18, $29, 0x70
    /* FB930 001FB930 00804234 */  ori        $2, $2, 0x8000
    /* FB934 001FB934 03001124 */  addiu      $17, $0, 0x3
    /* FB938 001FB938 080082AE */  sw         $2, 0x8($20)
    /* FB93C 001FB93C 0000A0C6 */  lwc1       $f0, 0x0($21)
    /* FB940 001FB940 0400A1C6 */  lwc1       $f1, 0x4($21)
    /* FB944 001FB944 0800A2C6 */  lwc1       $f2, 0x8($21)
    /* FB948 001FB948 A000A0E6 */  swc1       $f0, 0xA0($21)
    /* FB94C 001FB94C A400A1E6 */  swc1       $f1, 0xA4($21)
    /* FB950 001FB950 A800A2E6 */  swc1       $f2, 0xA8($21)
    /* FB954 001FB954 5C01628C */  lw         $2, 0x15C($3)
    /* FB958 001FB958 7000A0AF */  sw         $0, 0x70($29)
    /* FB95C 001FB95C 7801438C */  lw         $3, 0x178($2)
    /* FB960 001FB960 7400A0AF */  sw         $0, 0x74($29)
    /* FB964 001FB964 7800A0AF */  sw         $0, 0x78($29)
    /* FB968 001FB968 2D806000 */  daddu      $16, $3, $0
    /* FB96C 001FB96C 7000A427 */  addiu      $4, $29, 0x70
.align 2
  .L001FB970:
    /* FB970 001FB970 2D300002 */  daddu      $6, $16, $0
    /* FB974 001FB974 2D288000 */  daddu      $5, $4, $0
    /* FB978 001FB978 FCFF080C */  jal        func_0023FFF0
    /* FB97C 001FB97C 10001026 */   addiu     $16, $16, 0x10
    /* FB980 001FB980 FFFF3126 */  addiu      $17, $17, -0x1
    /* FB984 001FB984 FAFF2106 */  bgez       $17, .L001FB970
    /* FB988 001FB988 7000A427 */   addiu     $4, $29, 0x70
    /* FB98C 001FB98C 803E013C */  lui        $1, (0x3E800000 >> 16)
    /* FB990 001FB990 00608144 */  mtc1       $1, $f12
    /* FB994 001FB994 2D20C002 */  daddu      $4, $22, $0
    /* FB998 001FB998 0E00090C */  jal        func_00240038
    /* FB99C 001FB99C 7000A527 */   addiu     $5, $29, 0x70
    /* FB9A0 001FB9A0 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FB9A4 001FB9A4 00608144 */  mtc1       $1, $f12
    /* FB9A8 001FB9A8 2D204002 */  daddu      $4, $18, $0
    /* FB9AC 001FB9AC 0E00090C */  jal        func_00240038
    /* FB9B0 001FB9B0 2D28A002 */   daddu     $5, $21, $0
    /* FB9B4 001FB9B4 2D20C002 */  daddu      $4, $22, $0
    /* FB9B8 001FB9B8 2D304002 */  daddu      $6, $18, $0
    /* FB9BC 001FB9BC FCFF080C */  jal        func_0023FFF0
    /* FB9C0 001FB9C0 2D288000 */   daddu     $5, $4, $0
    /* FB9C4 001FB9C4 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FB9C8 001FB9C8 00008144 */  mtc1       $1, $f0
    /* FB9CC 001FB9CC CC00A0E6 */  swc1       $f0, 0xCC($21)
.align 2
  .L001FB9D0:
    /* FB9D0 001FB9D0 3000A48F */  lw         $4, 0x30($29)
    /* FB9D4 001FB9D4 1A28040C */  jal        EnableMotionOrientUpdate
    /* FB9D8 001FB9D8 00C00534 */   ori       $5, $0, 0xC000
    /* FB9DC 001FB9DC 05004010 */  beqz       $2, .L001FB9F4
    /* FB9E0 001FB9E0 3000A78F */   lw        $7, 0x30($29)
    /* FB9E4 001FB9E4 0800828E */  lw         $2, 0x8($20)
    /* FB9E8 001FB9E8 00044234 */  ori        $2, $2, 0x400
    /* FB9EC 001FB9EC 080082AE */  sw         $2, 0x8($20)
.align 2
  .L001FB9F0:
    /* FB9F0 001FB9F0 3000A78F */  lw         $7, 0x30($29)
.align 2
  .L001FB9F4:
    /* FB9F4 001FB9F4 90010424 */  addiu      $4, $0, 0x190
    /* FB9F8 001FB9F8 10DAC527 */  addiu      $5, $30, %lo(D_0055DA10)
    /* FB9FC 001FB9FC FFFF0624 */  addiu      $6, $0, -0x1
    /* FBA00 001FBA00 5C01E38C */  lw         $3, 0x15C($7)
    /* FBA04 001FBA04 9004628C */  lw         $2, 0x490($3)
    /* FBA08 001FBA08 18104400 */  mult       $2, $2, $4
    /* FBA0C 001FBA0C 21104500 */  addu       $2, $2, $5
    /* FBA10 001FBA10 8401438C */  lw         $3, 0x184($2)
    /* FBA14 001FBA14 80190300 */  sll        $3, $3, 6
    /* FBA18 001FBA18 831F0300 */  sra        $3, $3, 30
    /* FBA1C 001FBA1C 07006610 */  beq        $3, $6, .L001FBA3C
    /* FBA20 001FBA20 01000224 */   addiu     $2, $0, 0x1
    /* FBA24 001FBA24 30006210 */  beq        $3, $2, .L001FBAE8
    /* FBA28 001FBA28 00000000 */   nop
    /* FBA2C 001FBA2C 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FBA30 001FBA30 00008144 */  mtc1       $1, $f0
    /* FBA34 001FBA34 2E000010 */  b          .L001FBAF0
    /* FBA38 001FBA38 00000000 */   nop
.align 2
  .L001FBA3C:
    /* FBA3C 001FBA3C A090838F */  lw         $3, %gp_rel(D_00629C90)($28)
    /* FBA40 001FBA40 04000224 */  addiu      $2, $0, 0x4
    /* FBA44 001FBA44 05006214 */  bne        $3, $2, .L001FBA5C
    /* FBA48 001FBA48 2D20E000 */   daddu     $4, $7, $0
    /* FBA4C 001FBA4C 1A28040C */  jal        EnableMotionOrientUpdate
    /* FBA50 001FBA50 00100524 */   addiu     $5, $0, 0x1000
    /* FBA54 001FBA54 04000010 */  b          .L001FBA68
    /* FBA58 001FBA58 FF004230 */   andi      $2, $2, 0xFF
.align 2
  .L001FBA5C:
    /* FBA5C 001FBA5C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBA60 001FBA60 00100524 */   addiu     $5, $0, 0x1000
    /* FBA64 001FBA64 FF004230 */  andi       $2, $2, 0xFF
.align 2
  .L001FBA68:
    /* FBA68 001FBA68 05004010 */  beqz       $2, .L001FBA80
    /* FBA6C 001FBA6C 3000A28F */   lw        $2, 0x30($29)
    /* FBA70 001FBA70 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FBA74 001FBA74 00008144 */  mtc1       $1, $f0
    /* FBA78 001FBA78 0D000010 */  b          .L001FBAB0
    /* FBA7C 001FBA7C 00000000 */   nop
.align 2
  .L001FBA80:
    /* FBA80 001FBA80 90010624 */  addiu      $6, $0, 0x190
    /* FBA84 001FBA84 10DAC327 */  addiu      $3, $30, %lo(D_0055DA10)
    /* FBA88 001FBA88 0040013C */  lui        $1, (0x40000000 >> 16)
    /* FBA8C 001FBA8C 00008144 */  mtc1       $1, $f0
    /* FBA90 001FBA90 5C01458C */  lw         $5, 0x15C($2)
    /* FBA94 001FBA94 2D20E002 */  daddu      $4, $23, $0
    /* FBA98 001FBA98 9004A28C */  lw         $2, 0x490($5)
    /* FBA9C 001FBA9C 18104600 */  mult       $2, $2, $6
    /* FBAA0 001FBAA0 21186200 */  addu       $3, $3, $2
    /* FBAA4 001FBAA4 7C016CC4 */  lwc1       $f12, 0x17C($3)
    /* FBAA8 001FBAA8 3C48060C */  jal        func_001920F0
    /* FBAAC 001FBAAC 00630046 */   add.s     $f12, $f12, $f0
.align 2
  .L001FBAB0:
    /* FBAB0 001FBAB0 00088044 */  mtc1       $0, $f1
    /* FBAB4 001FBAB4 34000146 */  c.lt.s     $f0, $f1
    /* FBAB8 001FBAB8 00000000 */  nop
    /* FBABC 001FBABC 0C000345 */  bc1tl      .L001FBAF0
    /* FBAC0 001FBAC0 06080046 */   mov.s     $f0, $f1
    /* FBAC4 001FBAC4 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FBAC8 001FBAC8 00108144 */  mtc1       $1, $f2
    /* FBACC 001FBACC 34100046 */  c.lt.s     $f2, $f0
    /* FBAD0 001FBAD0 00000000 */  nop
    /* FBAD4 001FBAD4 02000045 */  bc1f       .L001FBAE0
    /* FBAD8 001FBAD8 46000046 */   mov.s     $f1, $f0
    /* FBADC 001FBADC 46100046 */  mov.s      $f1, $f2
.align 2
  .L001FBAE0:
    /* FBAE0 001FBAE0 03000010 */  b          .L001FBAF0
    /* FBAE4 001FBAE4 06080046 */   mov.s     $f0, $f1
.align 2
  .L001FBAE8:
    /* FBAE8 001FBAE8 1643013C */  lui        $1, (0x43160000 >> 16)
    /* FBAEC 001FBAEC 00008144 */  mtc1       $1, $f0
.align 2
  .L001FBAF0:
    /* FBAF0 001FBAF0 34B00046 */  c.lt.s     $f22, $f0
    /* FBAF4 001FBAF4 00000000 */  nop
    /* FBAF8 001FBAF8 BF000045 */  bc1f       .L001FBDF8
    /* FBAFC 001FBAFC 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FBB00 001FBB00 2DB00000 */  daddu      $22, $0, $0
    /* FBB04 001FBB04 0243013C */  lui        $1, (0x43020000 >> 16)
    /* FBB08 001FBB08 00008144 */  mtc1       $1, $f0
    /* FBB0C 001FBB0C 36000146 */  c.le.s     $f0, $f1
    /* FBB10 001FBB10 00000000 */  nop
    /* FBB14 001FBB14 07000045 */  bc1f       .L001FBB34
    /* FBB18 001FBB18 86080046 */   mov.s     $f2, $f1
    /* FBB1C 001FBB1C 2A43013C */  lui        $1, (0x432A0000 >> 16)
    /* FBB20 001FBB20 00008144 */  mtc1       $1, $f0
    /* FBB24 001FBB24 34080046 */  c.lt.s     $f1, $f0
    /* FBB28 001FBB28 00000000 */  nop
    /* FBB2C 001FBB2C 01000345 */  bc1tl      .L001FBB34
    /* FBB30 001FBB30 01001624 */   addiu     $22, $0, 0x1
.align 2
  .L001FBB34:
    /* FBB34 001FBB34 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FBB38 001FBB38 00008144 */  mtc1       $1, $f0
    /* FBB3C 001FBB3C 34000246 */  c.lt.s     $f0, $f2
    /* FBB40 001FBB40 00000000 */  nop
    /* FBB44 001FBB44 0B000045 */  bc1f       .L001FBB74
    /* FBB48 001FBB48 2D900000 */   daddu     $18, $0, $0
    /* FBB4C 001FBB4C C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FBB50 001FBB50 00008144 */  mtc1       $1, $f0
    /* FBB54 001FBB54 34080046 */  c.lt.s     $f1, $f0
    /* FBB58 001FBB58 00000000 */  nop
    /* FBB5C 001FBB5C 01000345 */  bc1tl      .L001FBB64
    /* FBB60 001FBB60 01001224 */   addiu     $18, $0, 0x1
.align 2
  .L001FBB64:
    /* FBB64 001FBB64 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FBB68 001FBB68 00008144 */  mtc1       $1, $f0
    /* FBB6C 001FBB6C 34000246 */  c.lt.s     $f0, $f2
    /* FBB70 001FBB70 00000000 */  nop
.align 2
  .L001FBB74:
    /* FBB74 001FBB74 07000045 */  bc1f       .L001FBB94
    /* FBB78 001FBB78 2D800000 */   daddu     $16, $0, $0
    /* FBB7C 001FBB7C 1643013C */  lui        $1, (0x43160000 >> 16)
    /* FBB80 001FBB80 00008144 */  mtc1       $1, $f0
    /* FBB84 001FBB84 34080046 */  c.lt.s     $f1, $f0
    /* FBB88 001FBB88 00000000 */  nop
    /* FBB8C 001FBB8C 01000345 */  bc1tl      .L001FBB94
    /* FBB90 001FBB90 01001024 */   addiu     $16, $0, 0x1
.align 2
  .L001FBB94:
    /* FBB94 001FBB94 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FBB98 001FBB98 00008144 */  mtc1       $1, $f0
    /* FBB9C 001FBB9C 34000246 */  c.lt.s     $f0, $f2
    /* FBBA0 001FBBA0 00000000 */  nop
    /* FBBA4 001FBBA4 07000045 */  bc1f       .L001FBBC4
    /* FBBA8 001FBBA8 2D880000 */   daddu     $17, $0, $0
    /* FBBAC 001FBBAC 6643013C */  lui        $1, (0x43660000 >> 16)
    /* FBBB0 001FBBB0 00008144 */  mtc1       $1, $f0
    /* FBBB4 001FBBB4 34080046 */  c.lt.s     $f1, $f0
    /* FBBB8 001FBBB8 00000000 */  nop
    /* FBBBC 001FBBBC 01000345 */  bc1tl      .L001FBBC4
    /* FBBC0 001FBBC0 01001124 */   addiu     $17, $0, 0x1
.align 2
  .L001FBBC4:
    /* FBBC4 001FBBC4 3000A48F */  lw         $4, 0x30($29)
    /* FBBC8 001FBBC8 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBBCC 001FBBCC 00B00534 */   ori       $5, $0, 0xB000
    /* FBBD0 001FBBD0 06004010 */  beqz       $2, .L001FBBEC
    /* FBBD4 001FBBD4 FFFE0324 */   addiu     $3, $0, -0x101
    /* FBBD8 001FBBD8 0800828E */  lw         $2, 0x8($20)
    /* FBBDC 001FBBDC 00221000 */  sll        $4, $16, 8
    /* FBBE0 001FBBE0 24104300 */  and        $2, $2, $3
    /* FBBE4 001FBBE4 83000010 */  b          .L001FBDF4
    /* FBBE8 001FBBE8 25104400 */   or        $2, $2, $4
.align 2
  .L001FBBEC:
    /* FBBEC 001FBBEC 3000A48F */  lw         $4, 0x30($29)
    /* FBBF0 001FBBF0 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBBF4 001FBBF4 00E00534 */   ori       $5, $0, 0xE000
    /* FBBF8 001FBBF8 06004010 */  beqz       $2, .L001FBC14
    /* FBBFC 001FBBFC FFFD0324 */   addiu     $3, $0, -0x201
    /* FBC00 001FBC00 0800828E */  lw         $2, 0x8($20)
    /* FBC04 001FBC04 40221000 */  sll        $4, $16, 9
    /* FBC08 001FBC08 24104300 */  and        $2, $2, $3
    /* FBC0C 001FBC0C 79000010 */  b          .L001FBDF4
    /* FBC10 001FBC10 25104400 */   or        $2, $2, $4
.align 2
  .L001FBC14:
    /* FBC14 001FBC14 3000A48F */  lw         $4, 0x30($29)
    /* FBC18 001FBC18 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBC1C 001FBC1C 00D00534 */   ori       $5, $0, 0xD000
    /* FBC20 001FBC20 06004010 */  beqz       $2, .L001FBC3C
    /* FBC24 001FBC24 FFEF0324 */   addiu     $3, $0, -0x1001
    /* FBC28 001FBC28 0800828E */  lw         $2, 0x8($20)
    /* FBC2C 001FBC2C 00231000 */  sll        $4, $16, 12
    /* FBC30 001FBC30 24104300 */  and        $2, $2, $3
    /* FBC34 001FBC34 6F000010 */  b          .L001FBDF4
    /* FBC38 001FBC38 25104400 */   or        $2, $2, $4
.align 2
  .L001FBC3C:
    /* FBC3C 001FBC3C A090838F */  lw         $3, %gp_rel(D_00629C90)($28)
    /* FBC40 001FBC40 04000224 */  addiu      $2, $0, 0x4
    /* FBC44 001FBC44 05006214 */  bne        $3, $2, .L001FBC5C
    /* FBC48 001FBC48 3000A48F */   lw        $4, 0x30($29)
    /* FBC4C 001FBC4C 1A28040C */  jal        EnableMotionOrientUpdate
    /* FBC50 001FBC50 00100524 */   addiu     $5, $0, 0x1000
    /* FBC54 001FBC54 04000010 */  b          .L001FBC68
    /* FBC58 001FBC58 FF004230 */   andi      $2, $2, 0xFF
.align 2
  .L001FBC5C:
    /* FBC5C 001FBC5C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBC60 001FBC60 00100524 */   addiu     $5, $0, 0x1000
    /* FBC64 001FBC64 FF004230 */  andi       $2, $2, 0xFF
.align 2
  .L001FBC68:
    /* FBC68 001FBC68 43004010 */  beqz       $2, .L001FBD78
    /* FBC6C 001FBC6C FFDF0224 */   addiu     $2, $0, -0x2001
    /* FBC70 001FBC70 0800838E */  lw         $3, 0x8($20)
    /* FBC74 001FBC74 40231000 */  sll        $4, $16, 13
    /* FBC78 001FBC78 24186200 */  and        $3, $3, $2
    /* FBC7C 001FBC7C 25186400 */  or         $3, $3, $4
    /* FBC80 001FBC80 42130300 */  srl        $2, $3, 13
    /* FBC84 001FBC84 01004230 */  andi       $2, $2, 0x1
    /* FBC88 001FBC88 5B004010 */  beqz       $2, .L001FBDF8
    /* FBC8C 001FBC8C 080083AE */   sw        $3, 0x8($20)
    /* FBC90 001FBC90 3000B08F */  lw         $16, 0x30($29)
    /* FBC94 001FBC94 F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* FBC98 001FBC98 6401058E */  lw         $5, 0x164($16)
    /* FBC9C 001FBC9C 2F000216 */  bne        $16, $2, .L001FBD5C
    /* FBCA0 001FBCA0 3400B4C7 */   lwc1      $f20, 0x34($29)
    /* FBCA4 001FBCA4 A090848F */  lw         $4, %gp_rel(D_00629C90)($28)
    /* FBCA8 001FBCA8 90010224 */  addiu      $2, $0, 0x190
    /* FBCAC 001FBCAC 5F00033C */  lui        $3, %hi(D_005EBC48)
    /* FBCB0 001FBCB0 18208200 */  mult       $4, $4, $2
    /* FBCB4 001FBCB4 48BC6324 */  addiu      $3, $3, %lo(D_005EBC48)
    /* FBCB8 001FBCB8 21208300 */  addu       $4, $4, $3
    /* FBCBC 001FBCBC 8C01828C */  lw         $2, 0x18C($4)
    /* FBCC0 001FBCC0 82100200 */  srl        $2, $2, 2
    /* FBCC4 001FBCC4 01004230 */  andi       $2, $2, 0x1
    /* FBCC8 001FBCC8 25004010 */  beqz       $2, .L001FBD60
    /* FBCCC 001FBCCC 01000224 */   addiu     $2, $0, 0x1
    /* FBCD0 001FBCD0 3000A28C */  lw         $2, 0x30($5)
    /* FBCD4 001FBCD4 FCFF4224 */  addiu      $2, $2, -0x4
    /* FBCD8 001FBCD8 0200422C */  sltiu      $2, $2, 0x2
    /* FBCDC 001FBCDC 1F004010 */  beqz       $2, .L001FBD5C
    /* FBCE0 001FBCE0 D000A427 */   addiu     $4, $29, 0xD0
    /* FBCE4 001FBCE4 2D280000 */  daddu      $5, $0, $0
    /* FBCE8 001FBCE8 5A81090C */  jal        func_00260568
    /* FBCEC 001FBCEC C0000624 */   addiu     $6, $0, 0xC0
    /* FBCF0 001FBCF0 2D280002 */  daddu      $5, $16, $0
    /* FBCF4 001FBCF4 D000A427 */  addiu      $4, $29, 0xD0
    /* FBCF8 001FBCF8 AC22050C */  jal        ActOrientTest
    /* FBCFC 001FBCFC 2C000624 */   addiu     $6, $0, 0x2C
    /* FBD00 001FBD00 D400A0C7 */  lwc1       $f0, 0xD4($29)
    /* FBD04 001FBD04 D000A427 */  addiu      $4, $29, 0xD0
    /* FBD08 001FBD08 4843013C */  lui        $1, (0x43480000 >> 16)
    /* FBD0C 001FBD0C 00088144 */  mtc1       $1, $f1
    /* FBD10 001FBD10 D000A3C7 */  lwc1       $f3, 0xD0($29)
    /* FBD14 001FBD14 00000146 */  add.s      $f0, $f0, $f1
    /* FBD18 001FBD18 D800A2C7 */  lwc1       $f2, 0xD8($29)
    /* FBD1C 001FBD1C E000A3E7 */  swc1       $f3, 0xE0($29)
    /* FBD20 001FBD20 E800A2E7 */  swc1       $f2, 0xE8($29)
    /* FBD24 001FBD24 DA98050C */  jal        ChangeFieldCollisionDebugMode
    /* FBD28 001FBD28 E400A0E7 */   swc1      $f0, 0xE4($29)
    /* FBD2C 001FBD2C 6401A28F */  lw         $2, 0x164($29)
    /* FBD30 001FBD30 0A004010 */  beqz       $2, .L001FBD5C
    /* FBD34 001FBD34 F400A0C7 */   lwc1      $f0, 0xF4($29)
    /* FBD38 001FBD38 D400A1C7 */  lwc1       $f1, 0xD4($29)
    /* FBD3C 001FBD3C 7A43013C */  lui        $1, (0x437A0000 >> 16)
    /* FBD40 001FBD40 00108144 */  mtc1       $1, $f2
    /* FBD44 001FBD44 01000146 */  sub.s      $f0, $f0, $f1
    /* FBD48 001FBD48 00A00046 */  add.s      $f0, $f20, $f0
    /* FBD4C 001FBD4C 34000246 */  c.lt.s     $f0, $f2
    /* FBD50 001FBD50 00000000 */  nop
    /* FBD54 001FBD54 02000145 */  bc1t       .L001FBD60
    /* FBD58 001FBD58 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001FBD5C:
    /* FBD5C 001FBD5C 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L001FBD60:
    /* FBD60 001FBD60 FF004230 */  andi       $2, $2, 0xFF
    /* FBD64 001FBD64 24004014 */  bnez       $2, .L001FBDF8
    /* FBD68 001FBD68 FFDF0324 */   addiu     $3, $0, -0x2001
    /* FBD6C 001FBD6C 0800828E */  lw         $2, 0x8($20)
    /* FBD70 001FBD70 20000010 */  b          .L001FBDF4
    /* FBD74 001FBD74 24104300 */   and       $2, $2, $3
.align 2
  .L001FBD78:
    /* FBD78 001FBD78 3000A48F */  lw         $4, 0x30($29)
    /* FBD7C 001FBD7C 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBD80 001FBD80 00300524 */   addiu     $5, $0, 0x3000
    /* FBD84 001FBD84 06004010 */  beqz       $2, .L001FBDA0
    /* FBD88 001FBD88 FFBF0324 */   addiu     $3, $0, -0x4001
    /* FBD8C 001FBD8C 0800828E */  lw         $2, 0x8($20)
    /* FBD90 001FBD90 80231000 */  sll        $4, $16, 14
    /* FBD94 001FBD94 24104300 */  and        $2, $2, $3
    /* FBD98 001FBD98 16000010 */  b          .L001FBDF4
    /* FBD9C 001FBD9C 25104400 */   or        $2, $2, $4
.align 2
  .L001FBDA0:
    /* FBDA0 001FBDA0 3000A28F */  lw         $2, 0x30($29)
    /* FBDA4 001FBDA4 5C01438C */  lw         $3, 0x15C($2)
    /* FBDA8 001FBDA8 D401648C */  lw         $4, 0x1D4($3)
    /* FBDAC 001FBDAC 12008010 */  beqz       $4, .L001FBDF8
    /* FBDB0 001FBDB0 7FFF0324 */   addiu     $3, $0, -0x81
    /* FBDB4 001FBDB4 0800828E */  lw         $2, 0x8($20)
    /* FBDB8 001FBDB8 C0211200 */  sll        $4, $18, 7
    /* FBDBC 001FBDBC BFFF0624 */  addiu      $6, $0, -0x41
    /* FBDC0 001FBDC0 24104300 */  and        $2, $2, $3
    /* FBDC4 001FBDC4 80291600 */  sll        $5, $22, 6
    /* FBDC8 001FBDC8 25104400 */  or         $2, $2, $4
    /* FBDCC 001FBDCC 2B000324 */  addiu      $3, $0, 0x2B
    /* FBDD0 001FBDD0 24204600 */  and        $4, $2, $6
    /* FBDD4 001FBDD4 25208500 */  or         $4, $4, $5
    /* FBDD8 001FBDD8 080084AE */  sw         $4, 0x8($20)
    /* FBDDC 001FBDDC AC01A98F */  lw         $9, 0x1AC($29)
    /* FBDE0 001FBDE0 0C00228D */  lw         $2, 0xC($9)
    /* FBDE4 001FBDE4 04004314 */  bne        $2, $3, .L001FBDF8
    /* FBDE8 001FBDE8 24108600 */   and       $2, $4, $6
    /* FBDEC 001FBDEC 80191100 */  sll        $3, $17, 6
    /* FBDF0 001FBDF0 25104300 */  or         $2, $2, $3
.align 2
  .L001FBDF4:
    /* FBDF4 001FBDF4 080082AE */  sw         $2, 0x8($20)
.align 2
  .L001FBDF8:
    /* FBDF8 001FBDF8 4842013C */  lui        $1, (0x42480000 >> 16)
    /* FBDFC 001FBDFC 00008144 */  mtc1       $1, $f0
    /* FBE00 001FBE00 34B00046 */  c.lt.s     $f22, $f0
    /* FBE04 001FBE04 00000000 */  nop
    /* FBE08 001FBE08 1F000045 */  bc1f       .L001FBE88
    /* FBE0C 001FBE0C 7000A427 */   addiu     $4, $29, 0x70
    /* FBE10 001FBE10 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* FBE14 001FBE14 00608144 */  mtc1       $1, $f12
    /* FBE18 001FBE18 0E00090C */  jal        func_00240038
    /* FBE1C 001FBE1C 2D28A002 */   daddu     $5, $21, $0
    /* FBE20 001FBE20 A801A48F */  lw         $4, 0x1A8($29)
    /* FBE24 001FBE24 4247060C */  jal        HandCameraCorrect
    /* FBE28 001FBE28 7000A527 */   addiu     $5, $29, 0x70
    /* FBE2C 001FBE2C 01004204 */  bltzl      $2, .L001FBE34
    /* FBE30 001FBE30 23100200 */   negu      $2, $2
.align 2
  .L001FBE34:
    /* FBE34 001FBE34 28004228 */  slti       $2, $2, 0x28
    /* FBE38 001FBE38 13004010 */  beqz       $2, .L001FBE88
    /* FBE3C 001FBE3C 3000A38F */   lw        $3, 0x30($29)
    /* FBE40 001FBE40 F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* FBE44 001FBE44 0B006210 */  beq        $3, $2, .L001FBE74
    /* FBE48 001FBE48 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FBE4C 001FBE4C 0243013C */  lui        $1, (0x43020000 >> 16)
    /* FBE50 001FBE50 00008144 */  mtc1       $1, $f0
    /* FBE54 001FBE54 34000146 */  c.lt.s     $f0, $f1
    /* FBE58 001FBE58 00000000 */  nop
    /* FBE5C 001FBE5C 0A000045 */  bc1f       .L001FBE88
    /* FBE60 001FBE60 AC01A28F */   lw        $2, 0x1AC($29)
    /* FBE64 001FBE64 0C00438C */  lw         $3, 0xC($2)
    /* FBE68 001FBE68 10000224 */  addiu      $2, $0, 0x10
    /* FBE6C 001FBE6C 07006250 */  beql       $3, $2, .L001FBE8C
    /* FBE70 001FBE70 700462DE */   ld        $2, 0x470($19)
.align 2
  .L001FBE74:
    /* FBE74 001FBE74 700462DE */  ld         $2, 0x470($19)
    /* FBE78 001FBE78 00800334 */  ori        $3, $0, 0x8000
    /* FBE7C 001FBE7C FC1A0300 */  dsll32     $3, $3, 11
    /* FBE80 001FBE80 25104300 */  or         $2, $2, $3
    /* FBE84 001FBE84 700462FE */  sd         $2, 0x470($19)
.align 2
  .L001FBE88:
    /* FBE88 001FBE88 700462DE */  ld         $2, 0x470($19)
.align 2
  .L001FBE8C:
    /* FBE8C 001FBE8C BE160200 */  dsrl32     $2, $2, 26
    /* FBE90 001FBE90 01004230 */  andi       $2, $2, 0x1
    /* FBE94 001FBE94 18004010 */  beqz       $2, .L001FBEF8
    /* FBE98 001FBE98 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FBE9C 001FBE9C 00008044 */  mtc1       $0, $f0
    /* FBEA0 001FBEA0 34080046 */  c.lt.s     $f1, $f0
    /* FBEA4 001FBEA4 00000000 */  nop
    /* FBEA8 001FBEA8 02000045 */  bc1f       .L001FBEB4
    /* FBEAC 001FBEAC 6300033C */   lui       $3, %hi(D_0062D9D8)
    /* FBEB0 001FBEB0 D8D961C4 */  lwc1       $f1, %lo(D_0062D9D8)($3)
.align 2
  .L001FBEB4:
    /* FBEB4 001FBEB4 8242013C */  lui        $1, (0x42820000 >> 16)
    /* FBEB8 001FBEB8 00008144 */  mtc1       $1, $f0
    /* FBEBC 001FBEBC 34000146 */  c.lt.s     $f0, $f1
    /* FBEC0 001FBEC0 0D000045 */  bc1f       .L001FBEF8
    /* FBEC4 001FBEC4 00000000 */   nop
    /* FBEC8 001FBEC8 00089744 */  mtc1       $23, $f1
    /* FBECC 001FBECC 60088046 */  cvt.s.w    $f1, $f1
    /* FBED0 001FBED0 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FBED4 001FBED4 00008144 */  mtc1       $1, $f0
    /* FBED8 001FBED8 34080046 */  c.lt.s     $f1, $f0
    /* FBEDC 001FBEDC 06000045 */  bc1f       .L001FBEF8
    /* FBEE0 001FBEE0 00000000 */   nop
    /* FBEE4 001FBEE4 680462DE */  ld         $2, 0x468($19)
    /* FBEE8 001FBEE8 00800334 */  ori        $3, $0, 0x8000
    /* FBEEC 001FBEEC B81E0300 */  dsll       $3, $3, 26
    /* FBEF0 001FBEF0 25104300 */  or         $2, $2, $3
    /* FBEF4 001FBEF4 680462FE */  sd         $2, 0x468($19)
.align 2
  .L001FBEF8:
    /* FBEF8 001FBEF8 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FBEFC 001FBEFC 00008144 */  mtc1       $1, $f0
    /* FBF00 001FBF00 34B00046 */  c.lt.s     $f22, $f0
    /* FBF04 001FBF04 00000000 */  nop
    /* FBF08 001FBF08 47000045 */  bc1f       .L001FC028
    /* FBF0C 001FBF0C 3000A68F */   lw        $6, 0x30($29)
    /* FBF10 001FBF10 00089744 */  mtc1       $23, $f1
    /* FBF14 001FBF14 60088046 */  cvt.s.w    $f1, $f1
    /* FBF18 001FBF18 F041013C */  lui        $1, (0x41F00000 >> 16)
    /* FBF1C 001FBF1C 00008144 */  mtc1       $1, $f0
    /* FBF20 001FBF20 34080046 */  c.lt.s     $f1, $f0
    /* FBF24 001FBF24 00000000 */  nop
    /* FBF28 001FBF28 02000145 */  bc1t       .L001FBF34
    /* FBF2C 001FBF2C 01001024 */   addiu     $16, $0, 0x1
    /* FBF30 001FBF30 2D800000 */  daddu      $16, $0, $0
.align 2
  .L001FBF34:
    /* FBF34 001FBF34 AC01A58F */  lw         $5, 0x1AC($29)
    /* FBF38 001FBF38 35000224 */  addiu      $2, $0, 0x35
    /* FBF3C 001FBF3C 0C00A38C */  lw         $3, 0xC($5)
    /* FBF40 001FBF40 09006254 */  bnel       $3, $2, .L001FBF68
    /* FBF44 001FBF44 680462DE */   ld        $2, 0x468($19)
    /* FBF48 001FBF48 0464060C */  jal        QueenInqDead
    /* FBF4C 001FBF4C 00000000 */   nop
    /* FBF50 001FBF50 0A004014 */  bnez       $2, .L001FBF7C
    /* FBF54 001FBF54 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FBF58 001FBF58 00800334 */  ori        $3, $0, 0x8000
    /* FBF5C 001FBF5C FC1A0300 */  dsll32     $3, $3, 11
    /* FBF60 001FBF60 03000010 */  b          .L001FBF70
    /* FBF64 001FBF64 680462DE */   ld        $2, 0x468($19)
.align 2
  .L001FBF68:
    /* FBF68 001FBF68 00800334 */  ori        $3, $0, 0x8000
    /* FBF6C 001FBF6C BC1A0300 */  dsll32     $3, $3, 10
.align 2
  .L001FBF70:
    /* FBF70 001FBF70 25104300 */  or         $2, $2, $3
    /* FBF74 001FBF74 680462FE */  sd         $2, 0x468($19)
    /* FBF78 001FBF78 3400A1C7 */  lwc1       $f1, 0x34($29)
.align 2
  .L001FBF7C:
    /* FBF7C 001FBF7C 00008044 */  mtc1       $0, $f0
    /* FBF80 001FBF80 34080046 */  c.lt.s     $f1, $f0
    /* FBF84 001FBF84 00000000 */  nop
    /* FBF88 001FBF88 02000045 */  bc1f       .L001FBF94
    /* FBF8C 001FBF8C 6300063C */   lui       $6, %hi(D_0062D9D8)
    /* FBF90 001FBF90 D8D9C1C4 */  lwc1       $f1, %lo(D_0062D9D8)($6)
.align 2
  .L001FBF94:
    /* FBF94 001FBF94 6643013C */  lui        $1, (0x43660000 >> 16)
    /* FBF98 001FBF98 00008144 */  mtc1       $1, $f0
    /* FBF9C 001FBF9C 34000146 */  c.lt.s     $f0, $f1
    /* FBFA0 001FBFA0 00000000 */  nop
    /* FBFA4 001FBFA4 1F000045 */  bc1f       .L001FC024
    /* FBFA8 001FBFA8 3000A48F */   lw        $4, 0x30($29)
    /* FBFAC 001FBFAC 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBFB0 001FBFB0 00040524 */   addiu     $5, $0, 0x400
    /* FBFB4 001FBFB4 1C004014 */  bnez       $2, .L001FC028
    /* FBFB8 001FBFB8 3000A68F */   lw        $6, 0x30($29)
    /* FBFBC 001FBFBC 3000A48F */  lw         $4, 0x30($29)
    /* FBFC0 001FBFC0 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBFC4 001FBFC4 00800534 */   ori       $5, $0, 0x8000
    /* FBFC8 001FBFC8 17004014 */  bnez       $2, .L001FC028
    /* FBFCC 001FBFCC 3000A68F */   lw        $6, 0x30($29)
    /* FBFD0 001FBFD0 AC01A78F */  lw         $7, 0x1AC($29)
    /* FBFD4 001FBFD4 2B000224 */  addiu      $2, $0, 0x2B
    /* FBFD8 001FBFD8 0C00E38C */  lw         $3, 0xC($7)
    /* FBFDC 001FBFDC 12006210 */  beq        $3, $2, .L001FC028
    /* FBFE0 001FBFE0 35000224 */   addiu     $2, $0, 0x35
    /* FBFE4 001FBFE4 11006210 */  beq        $3, $2, .L001FC02C
    /* FBFE8 001FBFE8 04000324 */   addiu     $3, $0, 0x4
    /* FBFEC 001FBFEC 0F000012 */  beqz       $16, .L001FC02C
    /* FBFF0 001FBFF0 3000A48F */   lw        $4, 0x30($29)
    /* FBFF4 001FBFF4 1228040C */  jal        ForMotionViewer_GetCurrentMotion
    /* FBFF8 001FBFF8 00E00534 */   ori       $5, $0, 0xE000
    /* FBFFC 001FBFFC 05004010 */  beqz       $2, .L001FC014
    /* FC000 001FC000 680462DE */   ld        $2, 0x468($19)
    /* FC004 001FC004 00800334 */  ori        $3, $0, 0x8000
    /* FC008 001FC008 3C1B0300 */  dsll32     $3, $3, 12
    /* FC00C 001FC00C 04000010 */  b          .L001FC020
    /* FC010 001FC010 25104300 */   or        $2, $2, $3
.align 2
  .L001FC014:
    /* FC014 001FC014 00800334 */  ori        $3, $0, 0x8000
    /* FC018 001FC018 7C1B0300 */  dsll32     $3, $3, 13
    /* FC01C 001FC01C 25104300 */  or         $2, $2, $3
.align 2
  .L001FC020:
    /* FC020 001FC020 680462FE */  sd         $2, 0x468($19)
.align 2
  .L001FC024:
    /* FC024 001FC024 3000A68F */  lw         $6, 0x30($29)
.align 2
  .L001FC028:
    /* FC028 001FC028 04000324 */  addiu      $3, $0, 0x4
.align 2
  .L001FC02C:
    /* FC02C 001FC02C 0C00C28C */  lw         $2, 0xC($6)
    /* FC030 001FC030 3C004314 */  bne        $2, $3, .L001FC124
    /* FC034 001FC034 6300083C */   lui       $8, %hi(D_0062D9D8)
    /* FC038 001FC038 6401C48C */  lw         $4, 0x164($6)
    /* FC03C 001FC03C 03000524 */  addiu      $5, $0, 0x3
    /* FC040 001FC040 7006828C */  lw         $2, 0x670($4)
    /* FC044 001FC044 DC01438C */  lw         $3, 0x1DC($2)
    /* FC048 001FC048 37006514 */  bne        $3, $5, .L001FC128
    /* FC04C 001FC04C D8D900C5 */   lwc1      $f0, %lo(D_0062D9D8)($8)
    /* FC050 001FC050 3443013C */  lui        $1, (0x43340000 >> 16)
    /* FC054 001FC054 00008144 */  mtc1       $1, $f0
    /* FC058 001FC058 34B00046 */  c.lt.s     $f22, $f0
    /* FC05C 001FC05C 00000000 */  nop
    /* FC060 001FC060 31000045 */  bc1f       .L001FC128
    /* FC064 001FC064 D8D900C5 */   lwc1      $f0, %lo(D_0062D9D8)($8)
    /* FC068 001FC068 5C01C28C */  lw         $2, 0x15C($6)
    /* FC06C 001FC06C D401438C */  lw         $3, 0x1D4($2)
    /* FC070 001FC070 2D006010 */  beqz       $3, .L001FC128
    /* FC074 001FC074 3400A1C7 */   lwc1      $f1, 0x34($29)
    /* FC078 001FC078 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FC07C 001FC07C 00008144 */  mtc1       $1, $f0
    /* FC080 001FC080 36000146 */  c.le.s     $f0, $f1
    /* FC084 001FC084 00000000 */  nop
    /* FC088 001FC088 09000045 */  bc1f       .L001FC0B0
    /* FC08C 001FC08C 86080046 */   mov.s     $f2, $f1
    /* FC090 001FC090 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FC094 001FC094 00008144 */  mtc1       $1, $f0
    /* FC098 001FC098 34080046 */  c.lt.s     $f1, $f0
    /* FC09C 001FC09C 00000000 */  nop
    /* FC0A0 001FC0A0 05000045 */  bc1f       .L001FC0B8
    /* FC0A4 001FC0A4 1000033C */   lui       $3, (0x100000 >> 16)
    /* FC0A8 001FC0A8 1B000010 */  b          .L001FC118
    /* FC0AC 001FC0AC 0400828E */   lw        $2, 0x4($20)
.align 2
  .L001FC0B0:
    /* FC0B0 001FC0B0 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FC0B4 001FC0B4 00008144 */  mtc1       $1, $f0
.align 2
  .L001FC0B8:
    /* FC0B8 001FC0B8 36000246 */  c.le.s     $f0, $f2
    /* FC0BC 001FC0BC 09000045 */  bc1f       .L001FC0E4
    /* FC0C0 001FC0C0 00000000 */   nop
    /* FC0C4 001FC0C4 FA43013C */  lui        $1, (0x43FA0000 >> 16)
    /* FC0C8 001FC0C8 00008144 */  mtc1       $1, $f0
    /* FC0CC 001FC0CC 34080046 */  c.lt.s     $f1, $f0
    /* FC0D0 001FC0D0 00000000 */  nop
    /* FC0D4 001FC0D4 05000045 */  bc1f       .L001FC0EC
    /* FC0D8 001FC0D8 2000033C */   lui       $3, (0x200000 >> 16)
    /* FC0DC 001FC0DC 0E000010 */  b          .L001FC118
    /* FC0E0 001FC0E0 0400828E */   lw        $2, 0x4($20)
.align 2
  .L001FC0E4:
    /* FC0E4 001FC0E4 FA43013C */  lui        $1, (0x43FA0000 >> 16)
    /* FC0E8 001FC0E8 00008144 */  mtc1       $1, $f0
.align 2
  .L001FC0EC:
    /* FC0EC 001FC0EC 36000246 */  c.le.s     $f0, $f2
    /* FC0F0 001FC0F0 00000000 */  nop
    /* FC0F4 001FC0F4 0B000045 */  bc1f       .L001FC124
    /* FC0F8 001FC0F8 6300083C */   lui       $8, %hi(D_0062D9D8)
    /* FC0FC 001FC0FC 2F44013C */  lui        $1, (0x442F0000 >> 16)
    /* FC100 001FC100 00008144 */  mtc1       $1, $f0
    /* FC104 001FC104 34080046 */  c.lt.s     $f1, $f0
    /* FC108 001FC108 00000000 */  nop
    /* FC10C 001FC10C 05000045 */  bc1f       .L001FC124
    /* FC110 001FC110 4000033C */   lui       $3, (0x400000 >> 16)
    /* FC114 001FC114 0400828E */  lw         $2, 0x4($20)
.align 2
  .L001FC118:
    /* FC118 001FC118 25104300 */  or         $2, $2, $3
    /* FC11C 001FC11C 040082AE */  sw         $2, 0x4($20)
    /* FC120 001FC120 6300083C */  lui        $8, %hi(D_0062D9D8)
.align 2
  .L001FC124:
    /* FC124 001FC124 D8D900C5 */  lwc1       $f0, %lo(D_0062D9D8)($8)
.align 2
  .L001FC128:
    /* FC128 001FC128 32A80046 */  c.eq.s     $f21, $f0
    /* FC12C 001FC12C 00000000 */  nop
    /* FC130 001FC130 8C050145 */  bc1t       .L001FD764
    /* FC134 001FC134 3000A48F */   lw        $4, 0x30($29)
    /* FC138 001FC138 3000A58F */  lw         $5, 0x30($29)
    /* FC13C 001FC13C 5C01A28C */  lw         $2, 0x15C($5)
    /* FC140 001FC140 5805438C */  lw         $3, 0x558($2)
    /* FC144 001FC144 87056010 */  beqz       $3, .L001FD764
    /* FC148 001FC148 B801A98F */   lw        $9, 0x1B8($29)
    /* FC14C 001FC14C 85052011 */  beqz       $9, .L001FD764
    /* FC150 001FC150 1000A226 */   addiu     $2, $21, 0x10
    /* FC154 001FC154 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FC158 001FC158 00A08144 */  mtc1       $1, $f20
    /* FC15C 001FC15C C801A2AF */  sw         $2, 0x1C8($29)
    /* FC160 001FC160 2D204000 */  daddu      $4, $2, $0
    /* FC164 001FC164 2A1A040C */  jal        CheckFieldContact
    /* FC168 001FC168 DC01A2AF */   sw        $2, 0x1DC($29)
    /* FC16C 001FC16C 1C00B4E6 */  swc1       $f20, 0x1C($21)
    /* FC170 001FC170 2274050C */  jal        subCommonIdle
    /* FC174 001FC174 3000A48F */   lw        $4, 0x30($29)
    /* FC178 001FC178 C801A58F */  lw         $5, 0x1C8($29)
    /* FC17C 001FC17C 2D804000 */  daddu      $16, $2, $0
    /* FC180 001FC180 06A30046 */  mov.s      $f12, $f20
    /* FC184 001FC184 0E00090C */  jal        func_00240038
    /* FC188 001FC188 6000A427 */   addiu     $4, $29, 0x60
    /* FC18C 001FC18C 2D200002 */  daddu      $4, $16, $0
    /* FC190 001FC190 4247060C */  jal        HandCameraCorrect
    /* FC194 001FC194 6000A527 */   addiu     $5, $29, 0x60
    /* FC198 001FC198 A041013C */  lui        $1, (0x41A00000 >> 16)
    /* FC19C 001FC19C 00008144 */  mtc1       $1, $f0
    /* FC1A0 001FC1A0 02004104 */  bgez       $2, .L001FC1AC
    /* FC1A4 001FC1A4 2D904000 */   daddu     $18, $2, $0
    /* FC1A8 001FC1A8 23901200 */  negu       $18, $18
.align 2
  .L001FC1AC:
    /* FC1AC 001FC1AC 34A80046 */  c.lt.s     $f21, $f0
    /* FC1B0 001FC1B0 00000000 */  nop
    /* FC1B4 001FC1B4 10000045 */  bc1f       .L001FC1F8
    /* FC1B8 001FC1B8 2E00422A */   slti      $2, $18, 0x2E
    /* FC1BC 001FC1BC 0F004054 */  bnel       $2, $0, .L001FC1FC
    /* FC1C0 001FC1C0 3000638E */   lw        $3, 0x30($19)
    /* FC1C4 001FC1C4 200062DE */  ld         $2, 0x20($19)
    /* FC1C8 001FC1C8 B8130200 */  dsll       $2, $2, 14
    /* FC1CC 001FC1CC 3F100200 */  dsra32     $2, $2, 0
    /* FC1D0 001FC1D0 01004230 */  andi       $2, $2, 0x1
    /* FC1D4 001FC1D4 08004010 */  beqz       $2, .L001FC1F8
    /* FC1D8 001FC1D8 3000A48F */   lw        $4, 0x30($29)
    /* FC1DC 001FC1DC 2E1A040C */  jal        dispPlane
    /* FC1E0 001FC1E0 C801A58F */   lw        $5, 0x1C8($29)
    /* FC1E4 001FC1E4 200062DE */  ld         $2, 0x20($19)
    /* FC1E8 001FC1E8 FBFF033C */  lui        $3, (0xFFFBFFFF >> 16)
    /* FC1EC 001FC1EC FFFF6334 */  ori        $3, $3, (0xFFFBFFFF & 0xFFFF)
    /* FC1F0 001FC1F0 24104300 */  and        $2, $2, $3
    /* FC1F4 001FC1F4 200062FE */  sd         $2, 0x20($19)
.align 2
  .L001FC1F8:
    /* FC1F8 001FC1F8 3000638E */  lw         $3, 0x30($19)
.align 2
  .L001FC1FC:
    /* FC1FC 001FC1FC 29000224 */  addiu      $2, $0, 0x29
    /* FC200 001FC200 04006214 */  bne        $3, $2, .L001FC214
    /* FC204 001FC204 00000000 */   nop
    /* FC208 001FC208 0400828E */  lw         $2, 0x4($20)
    /* FC20C 001FC20C 04004234 */  ori        $2, $2, 0x4
    /* FC210 001FC210 040082AE */  sw         $2, 0x4($20)
.align 2
  .L001FC214:
    /* FC214 001FC214 34A81946 */  c.lt.s     $f21, $f25
    /* FC218 001FC218 0B000045 */  bc1f       .L001FC248
    /* FC21C 001FC21C 00000000 */   nop
    /* FC220 001FC220 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FC224 001FC224 00008144 */  mtc1       $1, $f0
    /* FC228 001FC228 36001846 */  c.le.s     $f0, $f24
    /* FC22C 001FC22C 06000045 */  bc1f       .L001FC248
    /* FC230 001FC230 00000000 */   nop
    /* FC234 001FC234 180062DE */  ld         $2, 0x18($19)
    /* FC238 001FC238 00800334 */  ori        $3, $0, 0x8000
    /* FC23C 001FC23C 3C190300 */  dsll32     $3, $3, 4
    /* FC240 001FC240 25104300 */  or         $2, $2, $3
    /* FC244 001FC244 180062FE */  sd         $2, 0x18($19)
.align 2
  .L001FC248:
    /* FC248 001FC248 9643013C */  lui        $1, (0x43960000 >> 16)
    /* FC24C 001FC24C 00008144 */  mtc1       $1, $f0
    /* FC250 001FC250 34A80046 */  c.lt.s     $f21, $f0
    /* FC254 001FC254 00000000 */  nop
    /* FC258 001FC258 0C000245 */  bc1fl      .L001FC28C
    /* FC25C 001FC25C 3000638E */   lw        $3, 0x30($19)
    /* FC260 001FC260 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* FC264 001FC264 00008144 */  mtc1       $1, $f0
    /* FC268 001FC268 36001846 */  c.le.s     $f0, $f24
    /* FC26C 001FC26C 00000000 */  nop
    /* FC270 001FC270 06000245 */  bc1fl      .L001FC28C
    /* FC274 001FC274 3000638E */   lw        $3, 0x30($19)
    /* FC278 001FC278 0000828E */  lw         $2, 0x0($20)
    /* FC27C 001FC27C 04004234 */  ori        $2, $2, 0x4
    /* FC280 001FC280 000082AE */  sw         $2, 0x0($20)
    /* FC284 001FC284 3801B5E6 */  swc1       $f21, 0x138($21)
    /* FC288 001FC288 3000638E */  lw         $3, 0x30($19)
.align 2
  .L001FC28C:
    /* FC28C 001FC28C 03000224 */  addiu      $2, $0, 0x3
    /* FC290 001FC290 AE006210 */  beq        $3, $2, .L001FC54C
    /* FC294 001FC294 0400622C */   sltiu     $2, $3, 0x4
    /* FC298 001FC298 07004010 */  beqz       $2, .L001FC2B8
    /* FC29C 001FC29C 01000224 */   addiu     $2, $0, 0x1
    /* FC2A0 001FC2A0 9C006210 */  beq        $3, $2, .L001FC514
    /* FC2A4 001FC2A4 02000224 */   addiu     $2, $0, 0x2
    /* FC2A8 001FC2A8 11006210 */  beq        $3, $2, .L001FC2F0
    /* FC2AC 001FC2AC 00000000 */   nop
    /* FC2B0 001FC2B0 10010010 */  b          .L001FC6F4
    /* FC2B4 001FC2B4 00000000 */   nop
.align 2
  .L001FC2B8:
    /* FC2B8 001FC2B8 2A000224 */  addiu      $2, $0, 0x2A
    /* FC2BC 001FC2BC 95006210 */  beq        $3, $2, .L001FC514
    /* FC2C0 001FC2C0 2B00622C */   sltiu     $2, $3, 0x2B
    /* FC2C4 001FC2C4 05004010 */  beqz       $2, .L001FC2DC
    /* FC2C8 001FC2C8 0F000224 */   addiu     $2, $0, 0xF
    /* FC2CC 001FC2CC 91006210 */  beq        $3, $2, .L001FC514
    /* FC2D0 001FC2D0 00000000 */   nop
    /* FC2D4 001FC2D4 07010010 */  b          .L001FC6F4
    /* FC2D8 001FC2D8 00000000 */   nop
.align 2
  .L001FC2DC:
    /* FC2DC 001FC2DC 70000224 */  addiu      $2, $0, 0x70
    /* FC2E0 001FC2E0 7E006210 */  beq        $3, $2, .L001FC4DC
    /* FC2E4 001FC2E4 00000000 */   nop
    /* FC2E8 001FC2E8 02010010 */  b          .L001FC6F4
    /* FC2EC 001FC2EC 00000000 */   nop
.align 2
  .L001FC2F0:
    /* FC2F0 001FC2F0 A041013C */  lui        $1, (0x41A00000 >> 16)
    /* FC2F4 001FC2F4 00008144 */  mtc1       $1, $f0
    /* FC2F8 001FC2F8 34A80046 */  c.lt.s     $f21, $f0
    /* FC2FC 001FC2FC FD000045 */  bc1f       .L001FC6F4
    /* FC300 001FC300 00000000 */   nop
    /* FC304 001FC304 3443013C */  lui        $1, (0x43340000 >> 16)
    /* FC308 001FC308 00008144 */  mtc1       $1, $f0
    /* FC30C 001FC30C 34001846 */  c.lt.s     $f0, $f24
    /* FC310 001FC310 00000000 */  nop
    /* FC314 001FC314 F7000045 */  bc1f       .L001FC6F4
    /* FC318 001FC318 3000A38F */   lw        $3, 0x30($29)
    /* FC31C 001FC31C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* FC320 001FC320 14006214 */  bne        $3, $2, .L001FC374
    /* FC324 001FC324 BC01A78F */   lw        $7, 0x1BC($29)
    /* FC328 001FC328 6144013C */  lui        $1, (0x44610000 >> 16)
    /* FC32C 001FC32C 00008144 */  mtc1       $1, $f0
    /* FC330 001FC330 34001846 */  c.lt.s     $f0, $f24
    /* FC334 001FC334 00000000 */  nop
    /* FC338 001FC338 06000045 */  bc1f       .L001FC354
    /* FC33C 001FC33C BC01A58F */   lw        $5, 0x1BC($29)
    /* FC340 001FC340 FFFE033C */  lui        $3, (0xFEFFFFFF >> 16)
    /* FC344 001FC344 0800828E */  lw         $2, 0x8($20)
    /* FC348 001FC348 FFFF6334 */  ori        $3, $3, (0xFEFFFFFF & 0xFFFF)
    /* FC34C 001FC34C 0D000010 */  b          .L001FC384
    /* FC350 001FC350 0100A430 */   andi      $4, $5, 0x1
.align 2
  .L001FC354:
    /* FC354 001FC354 BC01A68F */  lw         $6, 0x1BC($29)
    /* FC358 001FC358 FFFD033C */  lui        $3, (0xFDFFFFFF >> 16)
    /* FC35C 001FC35C 0800828E */  lw         $2, 0x8($20)
    /* FC360 001FC360 FFFF6334 */  ori        $3, $3, (0xFDFFFFFF & 0xFFFF)
    /* FC364 001FC364 0100C430 */  andi       $4, $6, 0x1
    /* FC368 001FC368 24104300 */  and        $2, $2, $3
    /* FC36C 001FC36C 07000010 */  b          .L001FC38C
    /* FC370 001FC370 40260400 */   sll       $4, $4, 25
.align 2
  .L001FC374:
    /* FC374 001FC374 FFFE033C */  lui        $3, (0xFEFFFFFF >> 16)
    /* FC378 001FC378 0800828E */  lw         $2, 0x8($20)
    /* FC37C 001FC37C FFFF6334 */  ori        $3, $3, (0xFEFFFFFF & 0xFFFF)
    /* FC380 001FC380 0100E430 */  andi       $4, $7, 0x1
.align 2
  .L001FC384:
    /* FC384 001FC384 24104300 */  and        $2, $2, $3
    /* FC388 001FC388 00260400 */  sll        $4, $4, 24
.align 2
  .L001FC38C:
    /* FC38C 001FC38C 25104400 */  or         $2, $2, $4
    /* FC390 001FC390 7A44013C */  lui        $1, (0x447A0000 >> 16)
    /* FC394 001FC394 00008144 */  mtc1       $1, $f0
    /* FC398 001FC398 34001846 */  c.lt.s     $f0, $f24
    /* FC39C 001FC39C 00000000 */  nop
    /* FC3A0 001FC3A0 05000045 */  bc1f       .L001FC3B8
    /* FC3A4 001FC3A4 080082AE */   sw        $2, 0x8($20)
    /* FC3A8 001FC3A8 0800828E */  lw         $2, 0x8($20)
    /* FC3AC 001FC3AC 8000033C */  lui        $3, (0x800000 >> 16)
    /* FC3B0 001FC3B0 25104300 */  or         $2, $2, $3
    /* FC3B4 001FC3B4 080082AE */  sw         $2, 0x8($20)
.align 2
  .L001FC3B8:
    /* FC3B8 001FC3B8 A801A88F */  lw         $8, 0x1A8($29)
    /* FC3BC 001FC3BC 6000B127 */  addiu      $17, $29, 0x60
    /* FC3C0 001FC3C0 2D202002 */  daddu      $4, $17, $0
    /* FC3C4 001FC3C4 2D282002 */  daddu      $5, $17, $0
    /* FC3C8 001FC3C8 000001C5 */  lwc1       $f1, 0x0($8)
    /* FC3CC 001FC3CC 06AB0046 */  mov.s      $f12, $f21
    /* FC3D0 001FC3D0 040002C5 */  lwc1       $f2, 0x4($8)
    /* FC3D4 001FC3D4 080000C5 */  lwc1       $f0, 0x8($8)
    /* FC3D8 001FC3D8 6000A1E7 */  swc1       $f1, 0x60($29)
    /* FC3DC 001FC3DC 6400A2E7 */  swc1       $f2, 0x64($29)
    /* FC3E0 001FC3E0 0E00090C */  jal        func_00240038
    /* FC3E4 001FC3E4 6800A0E7 */   swc1      $f0, 0x68($29)
    /* FC3E8 001FC3E8 A040013C */  lui        $1, (0x40A00000 >> 16)
    /* FC3EC 001FC3EC 00A08144 */  mtc1       $1, $f20
    /* FC3F0 001FC3F0 7000B027 */  addiu      $16, $29, 0x70
    /* FC3F4 001FC3F4 3000A58F */  lw         $5, 0x30($29)
    /* FC3F8 001FC3F8 C210040C */  jal        GetRootMatrixByDObj
    /* FC3FC 001FC3FC 2D200002 */   daddu     $4, $16, $0
    /* FC400 001FC400 2D280002 */  daddu      $5, $16, $0
    /* FC404 001FC404 2D302002 */  daddu      $6, $17, $0
    /* FC408 001FC408 FCFF080C */  jal        func_0023FFF0
    /* FC40C 001FC40C 4000A426 */   addiu     $4, $21, 0x40
    /* FC410 001FC410 34A01546 */  c.lt.s     $f20, $f21
    /* FC414 001FC414 00000000 */  nop
    /* FC418 001FC418 B6000045 */  bc1f       .L001FC6F4
    /* FC41C 001FC41C 3000A48F */   lw        $4, 0x30($29)
    /* FC420 001FC420 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FC424 001FC424 00F00534 */   ori       $5, $0, 0xF000
    /* FC428 001FC428 B2004010 */  beqz       $2, .L001FC6F4
    /* FC42C 001FC42C 00000000 */   nop
    /* FC430 001FC430 00089244 */  mtc1       $18, $f1
    /* FC434 001FC434 60088046 */  cvt.s.w    $f1, $f1
    /* FC438 001FC438 A041013C */  lui        $1, (0x41A00000 >> 16)
    /* FC43C 001FC43C 00008144 */  mtc1       $1, $f0
    /* FC440 001FC440 34000146 */  c.lt.s     $f0, $f1
    /* FC444 001FC444 AB000045 */  bc1f       .L001FC6F4
    /* FC448 001FC448 00000000 */   nop
    /* FC44C 001FC44C 7041013C */  lui        $1, (0x41700000 >> 16)
    /* FC450 001FC450 00088144 */  mtc1       $1, $f1
    /* FC454 001FC454 00608044 */  mtc1       $0, $f12
    /* FC458 001FC458 01081546 */  sub.s      $f0, $f1, $f21
    /* FC45C 001FC45C 02001446 */  mul.s      $f0, $f0, $f20
    /* FC460 001FC460 00000000 */  nop
    /* FC464 001FC464 00000000 */  nop
    /* FC468 001FC468 03000146 */  div.s      $f0, $f0, $f1
    /* FC46C 001FC46C 34000C46 */  c.lt.s     $f0, $f12
    /* FC470 001FC470 03000045 */  bc1f       .L001FC480
    /* FC474 001FC474 00000000 */   nop
    /* FC478 001FC478 05000010 */  b          .L001FC490
    /* FC47C 001FC47C 06600046 */   mov.s     $f0, $f12
.align 2
  .L001FC480:
    /* FC480 001FC480 34A00046 */  c.lt.s     $f20, $f0
    /* FC484 001FC484 00000000 */  nop
    /* FC488 001FC488 01000345 */  bc1tl      .L001FC490
    /* FC48C 001FC48C 06A00046 */   mov.s     $f0, $f20
.align 2
  .L001FC490:
    /* FC490 001FC490 07030046 */  neg.s      $f12, $f0
    /* FC494 001FC494 9000B127 */  addiu      $17, $29, 0x90
    /* FC498 001FC498 C801A58F */  lw         $5, 0x1C8($29)
    /* FC49C 001FC49C 0E00090C */  jal        func_00240038
    /* FC4A0 001FC4A0 2D202002 */   daddu     $4, $17, $0
    /* FC4A4 001FC4A4 3000A48F */  lw         $4, 0x30($29)
    /* FC4A8 001FC4A8 3E74050C */  jal        ContinueCorrectPosition
    /* FC4AC 001FC4AC 8000B027 */   addiu     $16, $29, 0x80
    /* FC4B0 001FC4B0 2D200002 */  daddu      $4, $16, $0
    /* FC4B4 001FC4B4 2D284000 */  daddu      $5, $2, $0
    /* FC4B8 001FC4B8 FCFF080C */  jal        func_0023FFF0
    /* FC4BC 001FC4BC 2D302002 */   daddu     $6, $17, $0
    /* FC4C0 001FC4C0 8000A1C7 */  lwc1       $f1, 0x80($29)
    /* FC4C4 001FC4C4 FFFE053C */  lui        $5, (0xFEFFFFFF >> 16)
    /* FC4C8 001FC4C8 8400A2C7 */  lwc1       $f2, 0x84($29)
    /* FC4CC 001FC4CC FFFFA534 */  ori        $5, $5, (0xFEFFFFFF & 0xFFFF)
    /* FC4D0 001FC4D0 FFFD043C */  lui        $4, (0xFDFFFFFF >> 16)
    /* FC4D4 001FC4D4 7C000010 */  b          .L001FC6C8
    /* FC4D8 001FC4D8 8800A0C7 */   lwc1      $f0, 0x88($29)
.align 2
  .L001FC4DC:
    /* FC4DC 001FC4DC A041013C */  lui        $1, (0x41A00000 >> 16)
    /* FC4E0 001FC4E0 00008144 */  mtc1       $1, $f0
    /* FC4E4 001FC4E4 34A80046 */  c.lt.s     $f21, $f0
    /* FC4E8 001FC4E8 82000045 */  bc1f       .L001FC6F4
    /* FC4EC 001FC4EC 00000000 */   nop
    /* FC4F0 001FC4F0 7A44013C */  lui        $1, (0x447A0000 >> 16)
    /* FC4F4 001FC4F4 00008144 */  mtc1       $1, $f0
    /* FC4F8 001FC4F8 34001846 */  c.lt.s     $f0, $f24
    /* FC4FC 001FC4FC 00000000 */  nop
    /* FC500 001FC500 7C000045 */  bc1f       .L001FC6F4
    /* FC504 001FC504 4000033C */   lui       $3, (0x400000 >> 16)
    /* FC508 001FC508 0800828E */  lw         $2, 0x8($20)
    /* FC50C 001FC50C 78000010 */  b          .L001FC6F0
    /* FC510 001FC510 25104300 */   or        $2, $2, $3
.align 2
  .L001FC514:
    /* FC514 001FC514 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FC518 001FC518 00008144 */  mtc1       $1, $f0
    /* FC51C 001FC51C 34A80046 */  c.lt.s     $f21, $f0
    /* FC520 001FC520 74000045 */  bc1f       .L001FC6F4
    /* FC524 001FC524 00000000 */   nop
    /* FC528 001FC528 7A44013C */  lui        $1, (0x447A0000 >> 16)
    /* FC52C 001FC52C 00008144 */  mtc1       $1, $f0
    /* FC530 001FC530 34001846 */  c.lt.s     $f0, $f24
    /* FC534 001FC534 00000000 */  nop
    /* FC538 001FC538 6E000045 */  bc1f       .L001FC6F4
    /* FC53C 001FC53C 4000033C */   lui       $3, (0x400000 >> 16)
    /* FC540 001FC540 0800828E */  lw         $2, 0x8($20)
    /* FC544 001FC544 6A000010 */  b          .L001FC6F0
    /* FC548 001FC548 25104300 */   or        $2, $2, $3
.align 2
  .L001FC54C:
    /* FC54C 001FC54C 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FC550 001FC550 00008144 */  mtc1       $1, $f0
    /* FC554 001FC554 34A80046 */  c.lt.s     $f21, $f0
    /* FC558 001FC558 66000045 */  bc1f       .L001FC6F4
    /* FC55C 001FC55C 00000000 */   nop
    /* FC560 001FC560 7A44013C */  lui        $1, (0x447A0000 >> 16)
    /* FC564 001FC564 00008144 */  mtc1       $1, $f0
    /* FC568 001FC568 34001846 */  c.lt.s     $f0, $f24
    /* FC56C 001FC56C 00000000 */  nop
    /* FC570 001FC570 60000045 */  bc1f       .L001FC6F4
    /* FC574 001FC574 BC01A98F */   lw        $9, 0x1BC($29)
    /* FC578 001FC578 FFFE023C */  lui        $2, (0xFEFFFFFF >> 16)
    /* FC57C 001FC57C 0800848E */  lw         $4, 0x8($20)
    /* FC580 001FC580 FFFF4234 */  ori        $2, $2, (0xFEFFFFFF & 0xFFFF)
    /* FC584 001FC584 01002331 */  andi       $3, $9, 0x1
    /* FC588 001FC588 2041013C */  lui        $1, (0x41200000 >> 16)
    /* FC58C 001FC58C 00608144 */  mtc1       $1, $f12
    /* FC590 001FC590 24208200 */  and        $4, $4, $2
    /* FC594 001FC594 001E0300 */  sll        $3, $3, 24
    /* FC598 001FC598 25208300 */  or         $4, $4, $3
    /* FC59C 001FC59C 4000023C */  lui        $2, (0x400000 >> 16)
    /* FC5A0 001FC5A0 25208200 */  or         $4, $4, $2
    /* FC5A4 001FC5A4 00AB0C46 */  add.s      $f12, $f21, $f12
    /* FC5A8 001FC5A8 080084AE */  sw         $4, 0x8($20)
    /* FC5AC 001FC5AC 6000B127 */  addiu      $17, $29, 0x60
    /* FC5B0 001FC5B0 2D202002 */  daddu      $4, $17, $0
    /* FC5B4 001FC5B4 2D282002 */  daddu      $5, $17, $0
    /* FC5B8 001FC5B8 A801A28F */  lw         $2, 0x1A8($29)
    /* FC5BC 001FC5BC A040013C */  lui        $1, (0x40A00000 >> 16)
    /* FC5C0 001FC5C0 00A08144 */  mtc1       $1, $f20
    /* FC5C4 001FC5C4 000042C4 */  lwc1       $f2, 0x0($2)
    /* FC5C8 001FC5C8 040040C4 */  lwc1       $f0, 0x4($2)
    /* FC5CC 001FC5CC 080041C4 */  lwc1       $f1, 0x8($2)
    /* FC5D0 001FC5D0 6000A2E7 */  swc1       $f2, 0x60($29)
    /* FC5D4 001FC5D4 6400A0E7 */  swc1       $f0, 0x64($29)
    /* FC5D8 001FC5D8 0E00090C */  jal        func_00240038
    /* FC5DC 001FC5DC 6800A1E7 */   swc1      $f1, 0x68($29)
    /* FC5E0 001FC5E0 7000B027 */  addiu      $16, $29, 0x70
    /* FC5E4 001FC5E4 3000A58F */  lw         $5, 0x30($29)
    /* FC5E8 001FC5E8 C210040C */  jal        GetRootMatrixByDObj
    /* FC5EC 001FC5EC 2D200002 */   daddu     $4, $16, $0
    /* FC5F0 001FC5F0 2D280002 */  daddu      $5, $16, $0
    /* FC5F4 001FC5F4 2D302002 */  daddu      $6, $17, $0
    /* FC5F8 001FC5F8 FCFF080C */  jal        func_0023FFF0
    /* FC5FC 001FC5FC 4000A426 */   addiu     $4, $21, 0x40
    /* FC600 001FC600 34A01546 */  c.lt.s     $f20, $f21
    /* FC604 001FC604 00000000 */  nop
    /* FC608 001FC608 3A000045 */  bc1f       .L001FC6F4
    /* FC60C 001FC60C 3000A48F */   lw        $4, 0x30($29)
    /* FC610 001FC610 0A28040C */  jal        ForMotionViewer_GetCurrentAnimationFrame
    /* FC614 001FC614 00F00534 */   ori       $5, $0, 0xF000
    /* FC618 001FC618 36004010 */  beqz       $2, .L001FC6F4
    /* FC61C 001FC61C 00000000 */   nop
    /* FC620 001FC620 00089244 */  mtc1       $18, $f1
    /* FC624 001FC624 60088046 */  cvt.s.w    $f1, $f1
    /* FC628 001FC628 A041013C */  lui        $1, (0x41A00000 >> 16)
    /* FC62C 001FC62C 00008144 */  mtc1       $1, $f0
    /* FC630 001FC630 34000146 */  c.lt.s     $f0, $f1
    /* FC634 001FC634 2F000045 */  bc1f       .L001FC6F4
    /* FC638 001FC638 00000000 */   nop
    /* FC63C 001FC63C C841013C */  lui        $1, (0x41C80000 >> 16)
    /* FC640 001FC640 00088144 */  mtc1       $1, $f1
    /* FC644 001FC644 00608044 */  mtc1       $0, $f12
    /* FC648 001FC648 01081546 */  sub.s      $f0, $f1, $f21
    /* FC64C 001FC64C 02001446 */  mul.s      $f0, $f0, $f20
    /* FC650 001FC650 00000000 */  nop
    /* FC654 001FC654 00000000 */  nop
    /* FC658 001FC658 03000146 */  div.s      $f0, $f0, $f1
    /* FC65C 001FC65C 34000C46 */  c.lt.s     $f0, $f12
    /* FC660 001FC660 03000045 */  bc1f       .L001FC670
    /* FC664 001FC664 00000000 */   nop
    /* FC668 001FC668 05000010 */  b          .L001FC680
    /* FC66C 001FC66C 06600046 */   mov.s     $f0, $f12
.align 2
  .L001FC670:
    /* FC670 001FC670 34A00046 */  c.lt.s     $f20, $f0
    /* FC674 001FC674 00000000 */  nop
    /* FC678 001FC678 01000345 */  bc1tl      .L001FC680
    /* FC67C 001FC67C 06A00046 */   mov.s     $f0, $f20
.align 2
  .L001FC680:
    /* FC680 001FC680 07030046 */  neg.s      $f12, $f0
    /* FC684 001FC684 9000B127 */  addiu      $17, $29, 0x90
    /* FC688 001FC688 C801A58F */  lw         $5, 0x1C8($29)
    /* FC68C 001FC68C 0E00090C */  jal        func_00240038
    /* FC690 001FC690 2D202002 */   daddu     $4, $17, $0
    /* FC694 001FC694 3000A48F */  lw         $4, 0x30($29)
    /* FC698 001FC698 3E74050C */  jal        ContinueCorrectPosition
    /* FC69C 001FC69C 8000B027 */   addiu     $16, $29, 0x80
    /* FC6A0 001FC6A0 2D200002 */  daddu      $4, $16, $0
    /* FC6A4 001FC6A4 2D284000 */  daddu      $5, $2, $0
    /* FC6A8 001FC6A8 FCFF080C */  jal        func_0023FFF0
    /* FC6AC 001FC6AC 2D302002 */   daddu     $6, $17, $0
    /* FC6B0 001FC6B0 8000A1C7 */  lwc1       $f1, 0x80($29)
    /* FC6B4 001FC6B4 FFFE053C */  lui        $5, (0xFEFFFFFF >> 16)
    /* FC6B8 001FC6B8 8400A2C7 */  lwc1       $f2, 0x84($29)
    /* FC6BC 001FC6BC FFFFA534 */  ori        $5, $5, (0xFEFFFFFF & 0xFFFF)
    /* FC6C0 001FC6C0 8800A0C7 */  lwc1       $f0, 0x88($29)
    /* FC6C4 001FC6C4 BFFF043C */  lui        $4, (0xFFBFFFFF >> 16)
.align 2
  .L001FC6C8:
    /* FC6C8 001FC6C8 9000A1E6 */  swc1       $f1, 0x90($21)
    /* FC6CC 001FC6CC FFFF8434 */  ori        $4, $4, (0xFFBFFFFF & 0xFFFF)
    /* FC6D0 001FC6D0 9400A2E6 */  swc1       $f2, 0x94($21)
    /* FC6D4 001FC6D4 9800A0E6 */  swc1       $f0, 0x98($21)
    /* FC6D8 001FC6D8 0800828E */  lw         $2, 0x8($20)
    /* FC6DC 001FC6DC 0C00838E */  lw         $3, 0xC($20)
    /* FC6E0 001FC6E0 24104500 */  and        $2, $2, $5
    /* FC6E4 001FC6E4 24104400 */  and        $2, $2, $4
    /* FC6E8 001FC6E8 10006334 */  ori        $3, $3, 0x10
    /* FC6EC 001FC6EC 0C0083AE */  sw         $3, 0xC($20)
.align 2
  .L001FC6F0:
    /* FC6F0 001FC6F0 080082AE */  sw         $2, 0x8($20)
.align 2
  .L001FC6F4:
    /* FC6F4 001FC6F4 A222050C */  jal        ACTEnvGetTest
    /* FC6F8 001FC6F8 00000000 */   nop
    /* FC6FC 001FC6FC 22004010 */  beqz       $2, .L001FC788
    /* FC700 001FC700 00000000 */   nop
    /* FC704 001FC704 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FC708 001FC708 00008144 */  mtc1       $1, $f0
    /* FC70C 001FC70C 34A80046 */  c.lt.s     $f21, $f0
    /* FC710 001FC710 00000000 */  nop
    /* FC714 001FC714 6B000045 */  bc1f       .L001FC8C4
    /* FC718 001FC718 3000A48F */   lw        $4, 0x30($29)
    /* FC71C 001FC71C 7A44013C */  lui        $1, (0x447A0000 >> 16)
    /* FC720 001FC720 00008144 */  mtc1       $1, $f0
    /* FC724 001FC724 34001846 */  c.lt.s     $f0, $f24
    /* FC728 001FC728 00000000 */  nop
    /* FC72C 001FC72C 16000045 */  bc1f       .L001FC788
    /* FC730 001FC730 3000A28F */   lw        $2, 0x30($29)
    /* FC734 001FC734 4000043C */  lui        $4, (0x400000 >> 16)
    /* FC738 001FC738 5C01438C */  lw         $3, 0x15C($2)
    /* FC73C 001FC73C 77016568 */  ldl        $5, 0x177($3)
    /* FC740 001FC740 7001656C */  ldr        $5, 0x170($3)
    /* FC744 001FC744 7F016668 */  ldl        $6, 0x17F($3)
    /* FC748 001FC748 7801666C */  ldr        $6, 0x178($3)
    /* FC74C 001FC74C 87016768 */  ldl        $7, 0x187($3)
    /* FC750 001FC750 8001676C */  ldr        $7, 0x180($3)
    /* FC754 001FC754 8F016868 */  ldl        $8, 0x18F($3)
    /* FC758 001FC758 8801686C */  ldr        $8, 0x188($3)
    /* FC75C 001FC75C 9701A5B2 */  sdl        $5, 0x197($21)
    /* FC760 001FC760 9001A5B6 */  sdr        $5, 0x190($21)
    /* FC764 001FC764 9F01A6B2 */  sdl        $6, 0x19F($21)
    /* FC768 001FC768 9801A6B6 */  sdr        $6, 0x198($21)
    /* FC76C 001FC76C A701A7B2 */  sdl        $7, 0x1A7($21)
    /* FC770 001FC770 A001A7B6 */  sdr        $7, 0x1A0($21)
    /* FC774 001FC774 AF01A8B2 */  sdl        $8, 0x1AF($21)
    /* FC778 001FC778 A801A8B6 */  sdr        $8, 0x1A8($21)
    /* FC77C 001FC77C 0000828E */  lw         $2, 0x0($20)
    /* FC780 001FC780 25104400 */  or         $2, $2, $4
    /* FC784 001FC784 000082AE */  sw         $2, 0x0($20)
.align 2
  .L001FC788:
    /* FC788 001FC788 2042013C */  lui        $1, (0x42200000 >> 16)
    /* FC78C 001FC78C 00008144 */  mtc1       $1, $f0
    /* FC790 001FC790 34A80046 */  c.lt.s     $f21, $f0
    /* FC794 001FC794 00000000 */  nop
    /* FC798 001FC798 4A000045 */  bc1f       .L001FC8C4
    /* FC79C 001FC79C 3000A48F */   lw        $4, 0x30($29)
    /* FC7A0 001FC7A0 2228040C */  jal        DisableMotionOrientUpdate
    /* FC7A4 001FC7A4 00040524 */   addiu     $5, $0, 0x400
    /* FC7A8 001FC7A8 3F004010 */  beqz       $2, .L001FC8A8
    /* FC7AC 001FC7AC 3000A48F */   lw        $4, 0x30($29)
    /* FC7B0 001FC7B0 7042013C */  lui        $1, (0x42700000 >> 16)
    /* FC7B4 001FC7B4 00008144 */  mtc1       $1, $f0
    /* FC7B8 001FC7B8 34001846 */  c.lt.s     $f0, $f24
    /* FC7BC 001FC7BC 00000000 */  nop
    /* FC7C0 001FC7C0 39000045 */  bc1f       .L001FC8A8
    /* FC7C4 001FC7C4 0100033C */   lui       $3, (0x10000 >> 16)
    /* FC7C8 001FC7C8 1400A0C6 */  lwc1       $f0, 0x14($21)
    /* FC7CC 001FC7CC 1000A2C6 */  lwc1       $f2, 0x10($21)
    /* FC7D0 001FC7D0 1800A1C6 */  lwc1       $f1, 0x18($21)
    /* FC7D4 001FC7D4 A400A0E6 */  swc1       $f0, 0xA4($21)
    /* FC7D8 001FC7D8 A000A2E6 */  swc1       $f2, 0xA0($21)
    /* FC7DC 001FC7DC A800A1E6 */  swc1       $f1, 0xA8($21)
    /* FC7E0 001FC7E0 2041013C */  lui        $1, (0x41200000 >> 16)
    /* FC7E4 001FC7E4 00008144 */  mtc1       $1, $f0
    /* FC7E8 001FC7E8 0800828E */  lw         $2, 0x8($20)
    /* FC7EC 001FC7EC 34A80046 */  c.lt.s     $f21, $f0
    /* FC7F0 001FC7F0 25104300 */  or         $2, $2, $3
    /* FC7F4 001FC7F4 11000045 */  bc1f       .L001FC83C
    /* FC7F8 001FC7F8 080082AE */   sw        $2, 0x8($20)
    /* FC7FC 001FC7FC 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* FC800 001FC800 00608144 */  mtc1       $1, $f12
    /* FC804 001FC804 6000A427 */  addiu      $4, $29, 0x60
    /* FC808 001FC808 0E00090C */  jal        func_00240038
    /* FC80C 001FC80C C801A58F */   lw        $5, 0x1C8($29)
    /* FC810 001FC810 2000A427 */  addiu      $4, $29, 0x20
    /* FC814 001FC814 4247060C */  jal        HandCameraCorrect
    /* FC818 001FC818 6000A527 */   addiu     $5, $29, 0x60
    /* FC81C 001FC81C 01004204 */  bltzl      $2, .L001FC824
    /* FC820 001FC820 23100200 */   negu      $2, $2
.align 2
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
