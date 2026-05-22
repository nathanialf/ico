# func_001BF2C8 — parked

VRAM: 0x001BF2C8 (file_off 0x0BF2C8)
Asm source: asm/nonmatchings/src/box/func_001BF2C8.s

## Attempt at 2026-05-22

**Reason parked:** iter 30: 39 byte diffs remaining. Most function body matches. Key blockers: (1) jtbl_00618720 placement — box.o now has 2 gcc-emitted jtbls (006186E0 + 00618720) sharing .rodata section, but D_00618708 string needs to split them; current slinky.ld puts both jtbls back-to-back at 0x6186E0 then D_00618708 at 0x618730 (wrong VMA). Needs gen_slinky.py multi-jtbl-per-TU support. (2) Case 1 null check for q->_11C: target uses beql + 'daddu a0,sp,0' in annulled delay slot, build uses regular beq. Tried KEEP_LIVE(local), reg pins, restructure with skip_body label — couldn't force beql. (3) Build has extra 'lw a0,0x15C(s0); daddu a2,sp,0' lines around case 5 boundary.

**TU:** `src/box.c`

**Seed:** `tough_nuts/func_001BF2C8/func_001BF2C8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_0063118C, 1

.align 3
nonmatching func_001BF2C8, 0x198

glabel func_001BF2C8
    /* BF2C8 001BF2C8 C0FFBD27 */  addiu      $29, $29, -0x40
    /* BF2CC 001BF2CC 1000B0FF */  sd         $16, 0x10($29)
    /* BF2D0 001BF2D0 3000BFFF */  sd         $31, 0x30($29)
    /* BF2D4 001BF2D4 2D808000 */  daddu      $16, $4, $0
    /* BF2D8 001BF2D8 2000B1FF */  sd         $17, 0x20($29)
    /* BF2DC 001BF2DC 5C01028E */  lw         $2, 0x15C($16)
    /* BF2E0 001BF2E0 0008518C */  lw         $17, 0x800($2)
    /* BF2E4 001BF2E4 2000258E */  lw         $5, 0x20($17)
    /* BF2E8 001BF2E8 0100A324 */  addiu      $3, $5, 0x1
    /* BF2EC 001BF2EC 0800622C */  sltiu      $2, $3, 0x8
    /* BF2F0 001BF2F0 4B004010 */  beqz       $2, .L001BF420
    /* BF2F4 001BF2F4 6200023C */   lui       $2, %hi(jtbl_00618720)
    /* BF2F8 001BF2F8 80180300 */  sll        $3, $3, 2
    /* BF2FC 001BF2FC 20874224 */  addiu      $2, $2, %lo(jtbl_00618720)
    /* BF300 001BF300 21186200 */  addu       $3, $3, $2
    /* BF304 001BF304 0000648C */  lw         $4, 0x0($3)
    /* BF308 001BF308 08008000 */  jr         $4
    /* BF30C 001BF30C 00000000 */   nop
.align 2
  jlabel .L001BF310
    /* BF310 001BF310 5800228E */  lw         $2, 0x58($17)
    /* BF314 001BF314 47004010 */  beqz       $2, .L001BF434
    /* BF318 001BF318 06000224 */   addiu     $2, $0, 0x6
    /* BF31C 001BF31C 52FC060C */  jal        func_001BF148
    /* BF320 001BF320 2D200002 */   daddu     $4, $16, $0
    /* BF324 001BF324 5C01028E */  lw         $2, 0x15C($16)
    /* BF328 001BF328 0008448C */  lw         $4, 0x800($2)
    /* BF32C 001BF32C 1C01838C */  lw         $3, 0x11C($4)
    /* BF330 001BF330 10006050 */  beql       $3, $0, .L001BF374
    /* BF334 001BF334 2D20A003 */   daddu     $4, $29, $0
    /* BF338 001BF338 9C8880C7 */  lwc1       $f0, (D_0063118C) /* gp_rel: (D_0063118C) */
    /* BF33C 001BF33C 480081C4 */  lwc1       $f1, 0x48($4)
    /* BF340 001BF340 240182C4 */  lwc1       $f2, 0x124($4)
    /* BF344 001BF344 42080046 */  mul.s      $f1, $f1, $f0
    /* BF348 001BF348 20018284 */  lh         $2, 0x120($4)
    /* BF34C 001BF34C 00008244 */  mtc1       $2, $f0
    /* BF350 001BF350 20008046 */  cvt.s.w    $f0, $f0
    /* BF354 001BF354 00000000 */  nop
    /* BF358 001BF358 00000000 */  nop
    /* BF35C 001BF35C 43080246 */  div.s      $f1, $f1, $f2
    /* BF360 001BF360 01000146 */  sub.s      $f0, $f0, $f1
    /* BF364 001BF364 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* BF368 001BF368 00080244 */  mfc1       $2, $f1
    /* BF36C 001BF36C 200182A4 */  sh         $2, 0x120($4)
    /* BF370 001BF370 2D20A003 */  daddu      $4, $29, $0
.align 2
  .L001BF374:
    /* BF374 001BF374 2D280000 */  daddu      $5, $0, $0
    /* BF378 001BF378 7690090C */  jal        func_002641D8
    /* BF37C 001BF37C 10000624 */   addiu     $6, $0, 0x10
    /* BF380 001BF380 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* BF384 001BF384 00008144 */  mtc1       $1, $f0
    /* BF388 001BF388 2D30A003 */  daddu      $6, $29, $0
    /* BF38C 001BF38C 5C01028E */  lw         $2, 0x15C($16)
    /* BF390 001BF390 0800A0E7 */  swc1       $f0, 0x8($29)
    /* BF394 001BF394 20054424 */  addiu      $4, $2, 0x520
    /* BF398 001BF398 9261040C */  jal        func_00118648
    /* BF39C 001BF39C 0C00458C */   lw        $5, 0xC($2)
    /* BF3A0 001BF3A0 23000010 */  b          .L001BF430
    /* BF3A4 001BF3A4 2000258E */   lw        $5, 0x20($17)
.align 2
  jlabel .L001BF3A8
    /* BF3A8 001BF3A8 4EF4060C */  jal        func_001BD138
    /* BF3AC 001BF3AC 2D200002 */   daddu     $4, $16, $0
    /* BF3B0 001BF3B0 1F000010 */  b          .L001BF430
    /* BF3B4 001BF3B4 2000258E */   lw        $5, 0x20($17)
.align 2
  jlabel .L001BF3B8
    /* BF3B8 001BF3B8 D6FB060C */  jal        func_001BEF58
    /* BF3BC 001BF3BC 2D200002 */   daddu     $4, $16, $0
    /* BF3C0 001BF3C0 1B000010 */  b          .L001BF430
    /* BF3C4 001BF3C4 2000258E */   lw        $5, 0x20($17)
.align 2
  jlabel .L001BF3C8
    /* BF3C8 001BF3C8 48F8060C */  jal        func_001BE120
    /* BF3CC 001BF3CC 2D200002 */   daddu     $4, $16, $0
    /* BF3D0 001BF3D0 17004050 */  beql       $2, $0, .L001BF430
    /* BF3D4 001BF3D4 2000258E */   lw        $5, 0x20($17)
    /* BF3D8 001BF3D8 5C01038E */  lw         $3, 0x15C($16)
    /* BF3DC 001BF3DC 2D20A003 */  daddu      $4, $29, $0
    /* BF3E0 001BF3E0 0008628C */  lw         $2, 0x800($3)
    /* BF3E4 001BF3E4 200040AC */  sw         $0, 0x20($2)
    /* BF3E8 001BF3E8 5C01058E */  lw         $5, 0x15C($16)
    /* BF3EC 001BF3EC 0E36040C */  jal        func_0010D838
    /* BF3F0 001BF3F0 6000A524 */   addiu     $5, $5, 0x60
    /* BF3F4 001BF3F4 2D200002 */  daddu      $4, $16, $0
    /* BF3F8 001BF3F8 1C0A040C */  jal        func_00102870
    /* BF3FC 001BF3FC 2D28A003 */   daddu     $5, $29, $0
    /* BF400 001BF400 5C01038E */  lw         $3, 0x15C($16)
    /* BF404 001BF404 01000224 */  addiu      $2, $0, 0x1
    /* BF408 001BF408 08000010 */  b          .L001BF42C
    /* BF40C 001BF40C 780062AC */   sw        $2, 0x78($3)
.align 2
  jlabel .L001BF410
    /* BF410 001BF410 AAF9060C */  jal        func_001BE6A8
    /* BF414 001BF414 2D200002 */   daddu     $4, $16, $0
    /* BF418 001BF418 05000010 */  b          .L001BF430
    /* BF41C 001BF41C 2000258E */   lw        $5, 0x20($17)
.align 2
  jlabel .L001BF420
    /* BF420 001BF420 6200043C */  lui        $4, %hi(D_00618708)
    /* BF424 001BF424 8A9B060C */  jal        func_001A6E28
    /* BF428 001BF428 08878424 */   addiu     $4, $4, %lo(D_00618708)
.align 2
  .L001BF42C:
    /* BF42C 001BF42C 2000258E */  lw         $5, 0x20($17)
.align 2
  .L001BF430:
    /* BF430 001BF430 06000224 */  addiu      $2, $0, 0x6
.align 2
  .L001BF434:
    /* BF434 001BF434 0600A210 */  beq        $5, $2, .L001BF450
    /* BF438 001BF438 3000BFDF */   ld        $31, 0x30($29)
    /* BF43C 001BF43C 8001238E */  lw         $3, 0x180($17)
    /* BF440 001BF440 6C01628C */  lw         $2, 0x16C($3)
    /* BF444 001BF444 02004054 */  bnel       $2, $0, .L001BF450
    /* BF448 001BF448 6C0160AC */   sw        $0, 0x16C($3)
    /* BF44C 001BF44C 3000BFDF */  ld         $31, 0x30($29)
.align 2
  .L001BF450:
    /* BF450 001BF450 2000B1DF */  ld         $17, 0x20($29)
    /* BF454 001BF454 1000B0DF */  ld         $16, 0x10($29)
    /* BF458 001BF458 0800E003 */  jr         $31
    /* BF45C 001BF45C 4000BD27 */   addiu     $29, $29, 0x40
endlabel func_001BF2C8
```
