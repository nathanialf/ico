# _SgContDump — parked

VRAM: 0x00257C10 (file_off 0x157C10)
Asm source: asm/aug6/nonmatchings/common/src/PObj/_SgContDump.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=17). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_SgContDump/_SgContDump.c`

Disassembly:

```
.align 3
nonmatching _SgContDump, 0x118

glabel _SgContDump
    /* 157C10 00257C10 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 157C14 00257C14 1000B1FF */  sd         $17, 0x10($29)
    /* 157C18 00257C18 2D888000 */  daddu      $17, $4, $0
    /* 157C1C 00257C1C 2000B2FF */  sd         $18, 0x20($29)
    /* 157C20 00257C20 0000B0FF */  sd         $16, 0x0($29)
    /* 157C24 00257C24 3000BFFF */  sd         $31, 0x30($29)
    /* 157C28 00257C28 F253090C */  jal        _SgGetSlotContext
    /* 157C2C 00257C2C 2D200000 */   daddu     $4, $0, $0
    /* 157C30 00257C30 FE53090C */  jal        func_00254FF8
    /* 157C34 00257C34 2D804000 */   daddu     $16, $2, $0
    /* 157C38 00257C38 1854090C */  jal        func_00255060
    /* 157C3C 00257C3C 2D904000 */   daddu     $18, $2, $0
    /* 157C40 00257C40 2D304000 */  daddu      $6, $2, $0
    /* 157C44 00257C44 4E002396 */  lhu        $3, 0x4E($17)
    /* 157C48 00257C48 1000C58C */  lw         $5, 0x10($6)
    /* 157C4C 00257C4C 0800C28C */  lw         $2, 0x8($6)
    /* 157C50 00257C50 00190300 */  sll        $3, $3, 4
    /* 157C54 00257C54 0100A490 */  lbu        $4, 0x1($5)
    /* 157C58 00257C58 21104300 */  addu       $2, $2, $3
    /* 157C5C 00257C5C 1B0044A0 */  sb         $4, 0x1B($2)
    /* 157C60 00257C60 1000C38C */  lw         $3, 0x10($6)
    /* 157C64 00257C64 01006290 */  lbu        $2, 0x1($3)
    /* 157C68 00257C68 27004054 */  bnel       $2, $0, .L00257D08
    /* 157C6C 00257C6C 0400228E */   lw        $2, 0x4($17)
    /* 157C70 00257C70 4E002796 */  lhu        $7, 0x4E($17)
    /* 157C74 00257C74 2D280000 */  daddu      $5, $0, $0
    /* 157C78 00257C78 01000824 */  addiu      $8, $0, 0x1
    /* 157C7C 00257C7C 00000000 */  nop
.align 2
  .L00257C80:
    /* 157C80 00257C80 4F000292 */  lbu        $2, 0x4F($16)
    /* 157C84 00257C84 1C004754 */  bnel       $2, $7, .L00257CF8
    /* 157C88 00257C88 0100A524 */   addiu     $5, $5, 0x1
    /* 157C8C 00257C8C 54000392 */  lbu        $3, 0x54($16)
    /* 157C90 00257C90 18002296 */  lhu        $2, 0x18($17)
    /* 157C94 00257C94 18006254 */  bnel       $3, $2, .L00257CF8
    /* 157C98 00257C98 0100A524 */   addiu     $5, $5, 0x1
    /* 157C9C 00257C9C 50000392 */  lbu        $3, 0x50($16)
    /* 157CA0 00257CA0 4C002296 */  lhu        $2, 0x4C($17)
    /* 157CA4 00257CA4 14006254 */  bnel       $3, $2, .L00257CF8
    /* 157CA8 00257CA8 0100A524 */   addiu     $5, $5, 0x1
    /* 157CAC 00257CAC 0000028E */  lw         $2, 0x0($16)
    /* 157CB0 00257CB0 04004230 */  andi       $2, $2, 0x4
    /* 157CB4 00257CB4 10004050 */  beql       $2, $0, .L00257CF8
    /* 157CB8 00257CB8 0100A524 */   addiu     $5, $5, 0x1
    /* 157CBC 00257CBC 4E002296 */  lhu        $2, 0x4E($17)
    /* 157CC0 00257CC0 0800C38C */  lw         $3, 0x8($6)
    /* 157CC4 00257CC4 00110200 */  sll        $2, $2, 4
    /* 157CC8 00257CC8 21186200 */  addu       $3, $3, $2
    /* 157CCC 00257CCC 1B006490 */  lbu        $4, 0x1B($3)
    /* 157CD0 00257CD0 05008014 */  bnez       $4, .L00257CE8
    /* 157CD4 00257CD4 1418A800 */   dsllv     $3, $8, $5
    /* 157CD8 00257CD8 280042DE */  ld         $2, 0x28($18)
    /* 157CDC 00257CDC 25104300 */  or         $2, $2, $3
    /* 157CE0 00257CE0 04000010 */  b          .L00257CF4
    /* 157CE4 00257CE4 280042FE */   sd        $2, 0x28($18)
.align 2
  .L00257CE8:
    /* 157CE8 00257CE8 0000028E */  lw         $2, 0x0($16)
    /* 157CEC 00257CEC 08004234 */  ori        $2, $2, 0x8
    /* 157CF0 00257CF0 000002AE */  sw         $2, 0x0($16)
.align 2
  .L00257CF4:
    /* 157CF4 00257CF4 0100A524 */  addiu      $5, $5, 0x1
.align 2
  .L00257CF8:
    /* 157CF8 00257CF8 3000A228 */  slti       $2, $5, 0x30
    /* 157CFC 00257CFC E0FF4014 */  bnez       $2, .L00257C80
    /* 157D00 00257D00 58001026 */   addiu     $16, $16, 0x58
    /* 157D04 00257D04 0400228E */  lw         $2, 0x4($17)
.align 2
  .L00257D08:
    /* 157D08 00257D08 3000BFDF */  ld         $31, 0x30($29)
    /* 157D0C 00257D0C 03004224 */  addiu      $2, $2, 0x3
    /* 157D10 00257D10 2000B2DF */  ld         $18, 0x20($29)
    /* 157D14 00257D14 040022AE */  sw         $2, 0x4($17)
    /* 157D18 00257D18 1000B1DF */  ld         $17, 0x10($29)
    /* 157D1C 00257D1C 0000B0DF */  ld         $16, 0x0($29)
    /* 157D20 00257D20 0800E003 */  jr         $31
    /* 157D24 00257D24 4000BD27 */   addiu     $29, $29, 0x40
endlabel _SgContDump
```
