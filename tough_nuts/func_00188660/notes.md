# func_00188660 — parked

VRAM: 0x00188660 (file_off 0x088660)
Asm source: asm/aug6/nonmatchings/omori/src/camera-ico2/func_00188660.s

## Attempt at 2026-07-07

**Reason parked:** rc27 structure recovered (point-in-box search, outer mult+separate c/h in target); gcc IV-coalesce merges c/h(-12) and strength-reduces outer; 7 distinct source shapes fold/regress. Permuter-class.

**TU:** `omori/src/camera-ico2.c`

**Seed:** `tough_nuts/func_00188660/func_00188660.c`

Disassembly:

```
.align 3
nonmatching func_00188660, 0xC8

glabel func_00188660
    /* 88660 00188660 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 88664 00188664 2D288000 */  daddu      $5, $4, $0
    /* 88668 00188668 80BF013C */  lui        $1, (0xBF800000 >> 16)
    /* 8866C 0018866C 00608144 */  mtc1       $1, $f12
    /* 88670 00188670 1000BFFF */  sd         $31, 0x10($29)
    /* 88674 00188674 0E00090C */  jal        func_00240038
    /* 88678 00188678 2D20A003 */   daddu     $4, $29, $0
    /* 8867C 0018867C 60B4898F */  lw         $9, %gp_rel(D_0062C050)($28)
    /* 88680 00188680 2D58A003 */  daddu      $11, $29, $0
    /* 88684 00188684 FFFF0A24 */  addiu      $10, $0, -0x1
    /* 88688 00188688 23002019 */  blez       $9, .L00188718
    /* 8868C 0018868C 2D300000 */   daddu     $6, $0, $0
    /* 88690 00188690 58B4888F */  lw         $8, %gp_rel(D_0062C048)($28)
    /* 88694 00188694 4C000224 */  addiu      $2, $0, 0x4C
.align 2
  .L00188698:
    /* 88698 00188698 2D380000 */  daddu      $7, $0, $0
    /* 8869C 0018869C 1818C200 */  mult       $3, $6, $2
    /* 886A0 001886A0 2D286001 */  daddu      $5, $11, $0
    /* 886A4 001886A4 21106800 */  addu       $2, $3, $8
    /* 886A8 001886A8 20004424 */  addiu      $4, $2, 0x20
    /* 886AC 001886AC 2C004324 */  addiu      $3, $2, 0x2C
.align 2
  .L001886B0:
    /* 886B0 001886B0 000083C4 */  lwc1       $f3, 0x0($4)
    /* 886B4 001886B4 000061C4 */  lwc1       $f1, 0x0($3)
    /* 886B8 001886B8 0000A2C4 */  lwc1       $f2, 0x0($5)
    /* 886BC 001886BC 01180146 */  sub.s      $f0, $f3, $f1
    /* 886C0 001886C0 34100046 */  c.lt.s     $f2, $f0
    /* 886C4 001886C4 00000000 */  nop
    /* 886C8 001886C8 0C000145 */  bc1t       .L001886FC
    /* 886CC 001886CC 03000224 */   addiu     $2, $0, 0x3
    /* 886D0 001886D0 00180146 */  add.s      $f0, $f3, $f1
    /* 886D4 001886D4 34000246 */  c.lt.s     $f0, $f2
    /* 886D8 001886D8 08000145 */  bc1t       .L001886FC
    /* 886DC 001886DC 00000000 */   nop
    /* 886E0 001886E0 0100E724 */  addiu      $7, $7, 0x1
    /* 886E4 001886E4 0400A524 */  addiu      $5, $5, 0x4
    /* 886E8 001886E8 04006324 */  addiu      $3, $3, 0x4
    /* 886EC 001886EC 0300E228 */  slti       $2, $7, 0x3
    /* 886F0 001886F0 EFFF4014 */  bnez       $2, .L001886B0
    /* 886F4 001886F4 04008424 */   addiu     $4, $4, 0x4
    /* 886F8 001886F8 03000224 */  addiu      $2, $0, 0x3
.align 2
  .L001886FC:
    /* 886FC 001886FC 0300E254 */  bnel       $7, $2, .L0018870C
    /* 88700 00188700 0100C624 */   addiu     $6, $6, 0x1
    /* 88704 00188704 04000010 */  b          .L00188718
    /* 88708 00188708 2D50C000 */   daddu     $10, $6, $0
.align 2
  .L0018870C:
    /* 8870C 0018870C 2A10C900 */  slt        $2, $6, $9
    /* 88710 00188710 E1FF4014 */  bnez       $2, .L00188698
    /* 88714 00188714 4C000224 */   addiu     $2, $0, 0x4C
.align 2
  .L00188718:
    /* 88718 00188718 1000BFDF */  ld         $31, 0x10($29)
    /* 8871C 0018871C 2D104001 */  daddu      $2, $10, $0
    /* 88720 00188720 0800E003 */  jr         $31
    /* 88724 00188724 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_00188660
```
