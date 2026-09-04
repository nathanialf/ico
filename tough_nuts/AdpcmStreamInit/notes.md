# AdpcmStreamInit — parked

VRAM: 0x00140BE0 (file_off 0x040BE0)
Asm source: asm/nonmatchings/sound/adpcm_init/func_00140BE0.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: bucket A/B macros (MEM_BARRIER)

**TU:** `sound/adpcm_init.c`

**Seed:** `tough_nuts/AdpcmStreamInit/func_00140BE0.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CB0, 1
.extern D_00633CBC, 1
.extern D_00633CC4, 1
.extern D_00633CC0, 1

.align 3
nonmatching AdpcmStreamInit, 0xFC

glabel AdpcmStreamInit
    /* 40BE0 00140BE0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 40BE4 00140BE4 6B00023C */  lui        $2, %hi(D_006A9590)
    /* 40BE8 00140BE8 1000B1FF */  sd         $17, 0x10($29)
    /* 40BEC 00140BEC 0000B0FF */  sd         $16, 0x0($29)
    /* 40BF0 00140BF0 90955124 */  addiu      $17, $2, %lo(D_006A9590)
    /* 40BF4 00140BF4 2000BFFF */  sd         $31, 0x20($29)
    /* 40BF8 00140BF8 03001024 */  addiu      $16, $0, 0x3
    /* 40BFC 00140BFC 00000000 */  nop
.align 2
  .L00140C00:
    /* 40C00 00140C00 01000424 */  addiu      $4, $0, 0x1
    /* 40C04 00140C04 B676090C */  jal        SgGetSpuSlotMalloc
    /* 40C08 00140C08 FFFF1026 */   addiu     $16, $16, -0x1
    /* 40C0C 00140C0C 000022AE */  sw         $2, 0x0($17)
    /* 40C10 00140C10 FBFF0106 */  bgez       $16, .L00140C00
    /* 40C14 00140C14 04003126 */   addiu     $17, $17, 0x4
    /* 40C18 00140C18 0B00043C */  lui        $4, (0xB8800 >> 16)
    /* 40C1C 00140C1C 5500053C */  lui        $5, %hi(D_00557B78)
    /* 40C20 00140C20 787BA524 */  addiu      $5, $5, %lo(D_00557B78)
    /* 40C24 00140C24 00888434 */  ori        $4, $4, (0xB8800 & 0xFFFF)
    /* 40C28 00140C28 AED7040C */  jal        func_00135EB8
    /* 40C2C 00140C2C 44000624 */   addiu     $6, $0, 0x44
    /* 40C30 00140C30 2D204000 */  daddu      $4, $2, $0
    /* 40C34 00140C34 FF078230 */  andi       $2, $4, 0x7FF
    /* 40C38 00140C38 0A004010 */  beqz       $2, .L00140C64
    /* 40C3C 00140C3C D4B384AF */   sw        $4, (D_00633CC4) /* gp_rel: (D_00633CC4) */
    /* 40C40 00140C40 FFFF0324 */  addiu      $3, $0, -0x1
    /* 40C44 00140C44 FF078224 */  addiu      $2, $4, 0x7FF
    /* 40C48 00140C48 2A186400 */  slt        $3, $3, $4
    /* 40C4C 00140C4C 0B108300 */  movn       $2, $4, $3
    /* 40C50 00140C50 C3120200 */  sra        $2, $2, 11
    /* 40C54 00140C54 01004224 */  addiu      $2, $2, 0x1
    /* 40C58 00140C58 C0120200 */  sll        $2, $2, 11
    /* 40C5C 00140C5C 02000010 */  b          .L00140C68
    /* 40C60 00140C60 C0B382AF */   sw        $2, (D_00633CB0) /* gp_rel: (D_00633CB0) */
.align 2
  .L00140C64:
    /* 40C64 00140C64 C0B384AF */  sw         $4, (D_00633CB0) /* gp_rel: (D_00633CB0) */
.align 2
  .L00140C68:
    /* 40C68 00140C68 3C77090C */  jal        SgStAdpcmInit
    /* 40C6C 00140C6C 01001024 */   addiu     $16, $0, 0x1
    /* 40C70 00140C70 6B00023C */  lui        $2, %hi(D_006A94E0)
    /* 40C74 00140C74 E0944224 */  addiu      $2, $2, %lo(D_006A94E0)
    /* 40C78 00140C78 58004224 */  addiu      $2, $2, 0x58
    /* 40C7C 00140C7C 00000000 */  nop
.align 2
  .L00140C80:
    /* 40C80 00140C80 000040AC */  sw         $0, 0x0($2)
    /* 40C84 00140C84 FFFF1026 */  addiu      $16, $16, -0x1
    /* 40C88 00140C88 A8FF4224 */  addiu      $2, $2, -0x58
    /* 40C8C 00140C8C 00000000 */  nop
    /* 40C90 00140C90 00000000 */  nop
    /* 40C94 00140C94 FAFF0106 */  bgez       $16, .L00140C80
    /* 40C98 00140C98 00000000 */   nop
    /* 40C9C 00140C9C 01001024 */  addiu      $16, $0, 0x1
    /* 40CA0 00140CA0 CCB38227 */  .4byte 0x2782B3CC  /* la $2, (D_00633CBC) */ /* gp_rel: (D_00633CBC) */
    /* 40CA4 00140CA4 00000000 */  nop
.align 2
  .L00140CA8:
    /* 40CA8 00140CA8 000040AC */  sw         $0, 0x0($2)
    /* 40CAC 00140CAC FFFF1026 */  addiu      $16, $16, -0x1
    /* 40CB0 00140CB0 FCFF4224 */  addiu      $2, $2, -0x4
    /* 40CB4 00140CB4 00000000 */  nop
    /* 40CB8 00140CB8 00000000 */  nop
    /* 40CBC 00140CBC FAFF0106 */  bgez       $16, .L00140CA8
    /* 40CC0 00140CC0 00000000 */   nop
    /* 40CC4 00140CC4 2000BFDF */  ld         $31, 0x20($29)
    /* 40CC8 00140CC8 1000B1DF */  ld         $17, 0x10($29)
    /* 40CCC 00140CCC 0000B0DF */  ld         $16, 0x0($29)
    /* 40CD0 00140CD0 D0B380AF */  sw         $0, (D_00633CC0) /* gp_rel: (D_00633CC0) */
    /* 40CD4 00140CD4 0800E003 */  jr         $31
    /* 40CD8 00140CD8 3000BD27 */   addiu     $29, $29, 0x30
endlabel AdpcmStreamInit
    /* 40CDC 00140CDC 00000000 */  nop
```
