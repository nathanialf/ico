# func_00150608 — parked

VRAM: 0x00150608 (file_off 0x050608)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/func_00150608.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=13). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/func_00150608/func_00150608.c`

Disassembly:

```
.align 3
nonmatching func_00150608, 0x10C

glabel func_00150608
    /* 50608 00150608 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 5060C 0015060C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* 50610 00150610 1000B0FF */  sd         $16, 0x10($29)
    /* 50614 00150614 3000BFFF */  sd         $31, 0x30($29)
    /* 50618 00150618 2000B1FF */  sd         $17, 0x20($29)
    /* 5061C 0015061C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 50620 00150620 3E74050C */  jal        ContinueCorrectPosition
    /* 50624 00150624 6401518C */   lw        $17, 0x164($2)
    /* 50628 00150628 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 5062C 0015062C 3E74050C */  jal        ContinueCorrectPosition
    /* 50630 00150630 2D804000 */   daddu     $16, $2, $0
    /* 50634 00150634 2D304000 */  daddu      $6, $2, $0
    /* 50638 00150638 2D280002 */  daddu      $5, $16, $0
    /* 5063C 0015063C 0200090C */  jal        sceVu0SubVector
    /* 50640 00150640 2D20A003 */   daddu     $4, $29, $0
    /* 50644 00150644 2D20A003 */  daddu      $4, $29, $0
    /* 50648 00150648 9CFF080C */  jal        sceVu0InnerProduct
    /* 5064C 0015064C B0042526 */   addiu     $5, $17, 0x4B0
    /* 50650 00150650 00088044 */  mtc1       $0, $f1
    /* 50654 00150654 34080046 */  c.lt.s     $f1, $f0
    /* 50658 00150658 00000000 */  nop
    /* 5065C 0015065C 27000045 */  bc1f       .L001506FC
    /* 50660 00150660 F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* 50664 00150664 3E74050C */  jal        ContinueCorrectPosition
    /* 50668 00150668 F0043026 */   addiu     $16, $17, 0x4F0
    /* 5066C 0015066C 2D200002 */  daddu      $4, $16, $0
    /* 50670 00150670 0047060C */  jal        _DistxzGV
    /* 50674 00150674 2D284000 */   daddu     $5, $2, $0
    /* 50678 00150678 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* 5067C 0015067C 00088144 */  mtc1       $1, $f1
    /* 50680 00150680 34000146 */  c.lt.s     $f0, $f1
    /* 50684 00150684 00000000 */  nop
    /* 50688 00150688 1C000045 */  bc1f       .L001506FC
    /* 5068C 0015068C F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* 50690 00150690 6401838C */  lw         $3, 0x164($4)
    /* 50694 00150694 1E006294 */  lhu        $2, 0x1E($3)
    /* 50698 00150698 3C100200 */  dsll32     $2, $2, 0
    /* 5069C 0015069C 3F100200 */  dsra32     $2, $2, 0
    /* 506A0 001506A0 01004230 */  andi       $2, $2, 0x1
    /* 506A4 001506A4 16004010 */  beqz       $2, .L00150700
    /* 506A8 001506A8 2D100000 */   daddu     $2, $0, $0
    /* 506AC 001506AC 11008010 */  beqz       $4, .L001506F4
    /* 506B0 001506B0 F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* 506B4 001506B4 12004010 */  beqz       $2, .L00150700
    /* 506B8 001506B8 01000224 */   addiu     $2, $0, 0x1
    /* 506BC 001506BC 3E74050C */  jal        ContinueCorrectPosition
    /* 506C0 001506C0 00000000 */   nop
    /* 506C4 001506C4 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 506C8 001506C8 3E74050C */  jal        ContinueCorrectPosition
    /* 506CC 001506CC 2D804000 */   daddu     $16, $2, $0
    /* 506D0 001506D0 040040C4 */  lwc1       $f0, 0x4($2)
    /* 506D4 001506D4 E143013C */  lui        $1, (0x43E10000 >> 16)
    /* 506D8 001506D8 00088144 */  mtc1       $1, $f1
    /* 506DC 001506DC 040002C6 */  lwc1       $f2, 0x4($16)
    /* 506E0 001506E0 00000146 */  add.s      $f0, $f0, $f1
    /* 506E4 001506E4 34000246 */  c.lt.s     $f0, $f2
    /* 506E8 001506E8 00000000 */  nop
    /* 506EC 001506EC 04000145 */  bc1t       .L00150700
    /* 506F0 001506F0 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001506F4:
    /* 506F4 001506F4 02000010 */  b          .L00150700
    /* 506F8 001506F8 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001506FC:
    /* 506FC 001506FC 2D100000 */  daddu      $2, $0, $0
.align 2
  .L00150700:
    /* 50700 00150700 3000BFDF */  ld         $31, 0x30($29)
    /* 50704 00150704 2000B1DF */  ld         $17, 0x20($29)
    /* 50708 00150708 1000B0DF */  ld         $16, 0x10($29)
    /* 5070C 0015070C 0800E003 */  jr         $31
    /* 50710 00150710 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_00150608
    /* 50714 00150714 00000000 */  nop
```

---

## Attempt at 2026-07-07

**Reason parked:** rc7 twin of subBoyCollision (structure recovered); residuals: §5.11 dsll32/dsra32 sign-ext on lhu bitfield (gcc drops as value non-negative) + shared beql-vs-beq + fp-reg f1/f2 swap; all fold; permuter-class

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/func_00150608/func_00150608.1.c`

Disassembly:

```
.align 3
nonmatching func_00150608, 0x10C

glabel func_00150608
    /* 50608 00150608 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 5060C 0015060C F491828F */  lw         $2, %gp_rel(D_00629DE4)($28)
    /* 50610 00150610 1000B0FF */  sd         $16, 0x10($29)
    /* 50614 00150614 3000BFFF */  sd         $31, 0x30($29)
    /* 50618 00150618 2000B1FF */  sd         $17, 0x20($29)
    /* 5061C 0015061C F891848F */  lw         $4, %gp_rel(D_00629DE8)($28)
    /* 50620 00150620 3E74050C */  jal        ContinueCorrectPosition
    /* 50624 00150624 6401518C */   lw        $17, 0x164($2)
    /* 50628 00150628 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 5062C 0015062C 3E74050C */  jal        ContinueCorrectPosition
    /* 50630 00150630 2D804000 */   daddu     $16, $2, $0
    /* 50634 00150634 2D304000 */  daddu      $6, $2, $0
    /* 50638 00150638 2D280002 */  daddu      $5, $16, $0
    /* 5063C 0015063C 0200090C */  jal        sceVu0SubVector
    /* 50640 00150640 2D20A003 */   daddu     $4, $29, $0
    /* 50644 00150644 2D20A003 */  daddu      $4, $29, $0
    /* 50648 00150648 9CFF080C */  jal        sceVu0InnerProduct
    /* 5064C 0015064C B0042526 */   addiu     $5, $17, 0x4B0
    /* 50650 00150650 00088044 */  mtc1       $0, $f1
    /* 50654 00150654 34080046 */  c.lt.s     $f1, $f0
    /* 50658 00150658 00000000 */  nop
    /* 5065C 0015065C 27000045 */  bc1f       .L001506FC
    /* 50660 00150660 F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* 50664 00150664 3E74050C */  jal        ContinueCorrectPosition
    /* 50668 00150668 F0043026 */   addiu     $16, $17, 0x4F0
    /* 5066C 0015066C 2D200002 */  daddu      $4, $16, $0
    /* 50670 00150670 0047060C */  jal        _DistxzGV
    /* 50674 00150674 2D284000 */   daddu     $5, $2, $0
    /* 50678 00150678 C842013C */  lui        $1, (0x42C80000 >> 16)
    /* 5067C 0015067C 00088144 */  mtc1       $1, $f1
    /* 50680 00150680 34000146 */  c.lt.s     $f0, $f1
    /* 50684 00150684 00000000 */  nop
    /* 50688 00150688 1C000045 */  bc1f       .L001506FC
    /* 5068C 0015068C F891848F */   lw        $4, %gp_rel(D_00629DE8)($28)
    /* 50690 00150690 6401838C */  lw         $3, 0x164($4)
    /* 50694 00150694 1E006294 */  lhu        $2, 0x1E($3)
    /* 50698 00150698 3C100200 */  dsll32     $2, $2, 0
    /* 5069C 0015069C 3F100200 */  dsra32     $2, $2, 0
    /* 506A0 001506A0 01004230 */  andi       $2, $2, 0x1
    /* 506A4 001506A4 16004010 */  beqz       $2, .L00150700
    /* 506A8 001506A8 2D100000 */   daddu     $2, $0, $0
    /* 506AC 001506AC 11008010 */  beqz       $4, .L001506F4
    /* 506B0 001506B0 F491828F */   lw        $2, %gp_rel(D_00629DE4)($28)
    /* 506B4 001506B4 12004010 */  beqz       $2, .L00150700
    /* 506B8 001506B8 01000224 */   addiu     $2, $0, 0x1
    /* 506BC 001506BC 3E74050C */  jal        ContinueCorrectPosition
    /* 506C0 001506C0 00000000 */   nop
    /* 506C4 001506C4 F491848F */  lw         $4, %gp_rel(D_00629DE4)($28)
    /* 506C8 001506C8 3E74050C */  jal        ContinueCorrectPosition
    /* 506CC 001506CC 2D804000 */   daddu     $16, $2, $0
    /* 506D0 001506D0 040040C4 */  lwc1       $f0, 0x4($2)
    /* 506D4 001506D4 E143013C */  lui        $1, (0x43E10000 >> 16)
    /* 506D8 001506D8 00088144 */  mtc1       $1, $f1
    /* 506DC 001506DC 040002C6 */  lwc1       $f2, 0x4($16)
    /* 506E0 001506E0 00000146 */  add.s      $f0, $f0, $f1
    /* 506E4 001506E4 34000246 */  c.lt.s     $f0, $f2
    /* 506E8 001506E8 00000000 */  nop
    /* 506EC 001506EC 04000145 */  bc1t       .L00150700
    /* 506F0 001506F0 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001506F4:
    /* 506F4 001506F4 02000010 */  b          .L00150700
    /* 506F8 001506F8 01000224 */   addiu     $2, $0, 0x1
.align 2
  .L001506FC:
    /* 506FC 001506FC 2D100000 */  daddu      $2, $0, $0
.align 2
  .L00150700:
    /* 50700 00150700 3000BFDF */  ld         $31, 0x30($29)
    /* 50704 00150704 2000B1DF */  ld         $17, 0x20($29)
    /* 50708 00150708 1000B0DF */  ld         $16, 0x10($29)
    /* 5070C 0015070C 0800E003 */  jr         $31
    /* 50710 00150710 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_00150608
    /* 50714 00150714 00000000 */  nop
```
