# func_001EA030 — parked

VRAM: 0x001EA030 (file_off 0x0EA030)
Asm source: asm/nonmatchings/src/rotObject/func_001EA030.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE)

**TU:** `src/rotObject.c`

**Seed:** `tough_nuts/func_001EA030/func_001EA030.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006313C8, 1

.align 3
nonmatching func_001EA030, 0xD4

glabel func_001EA030
    /* EA030 001EA030 B0FFBD27 */  addiu      $29, $29, -0x50
    /* EA034 001EA034 2000B1FF */  sd         $17, 0x20($29)
    /* EA038 001EA038 4000BFFF */  sd         $31, 0x40($29)
    /* EA03C 001EA03C 2D888000 */  daddu      $17, $4, $0
    /* EA040 001EA040 3000B2FF */  sd         $18, 0x30($29)
    /* EA044 001EA044 1000B0FF */  sd         $16, 0x10($29)
    /* EA048 001EA048 5C01228E */  lw         $2, 0x15C($17)
    /* EA04C 001EA04C 0008508C */  lw         $16, 0x800($2)
    /* EA050 001EA050 9E14040C */  jal        func_00105278
    /* EA054 001EA054 0C00528C */   lw        $18, 0xC($2)
    /* EA058 001EA058 2D282002 */  daddu      $5, $17, $0
    /* EA05C 001EA05C 5010040C */  jal        func_00104140
    /* EA060 001EA060 2D204000 */   daddu     $4, $2, $0
    /* EA064 001EA064 F013040C */  jal        func_00104FC0
    /* EA068 001EA068 20000486 */   lh        $4, 0x20($16)
    /* EA06C 001EA06C 9E14040C */  jal        func_00105278
    /* EA070 001EA070 00000000 */   nop
    /* EA074 001EA074 2700063C */  lui        $6, %hi(D_00275890)
    /* EA078 001EA078 2D284000 */  daddu      $5, $2, $0
    /* EA07C 001EA07C 9058C624 */  addiu      $6, $6, %lo(D_00275890)
    /* EA080 001EA080 9261040C */  jal        func_00118648
    /* EA084 001EA084 2D20A003 */   daddu     $4, $29, $0
    /* EA088 001EA088 0400A0AF */  sw         $0, 0x4($29)
    /* EA08C 001EA08C 2D20A003 */  daddu      $4, $29, $0
    /* EA090 001EA090 BC60040C */  jal        func_001182F0
    /* EA094 001EA094 2D28A003 */   daddu     $5, $29, $0
    /* EA098 001EA098 9E14040C */  jal        func_00105278
    /* EA09C 001EA09C 00000000 */   nop
    /* EA0A0 001EA0A0 EA17040C */  jal        func_00105FA8
    /* EA0A4 001EA0A4 2D204000 */   daddu     $4, $2, $0
    /* EA0A8 001EA0A8 0000ACC7 */  lwc1       $f12, 0x0($29)
    /* EA0AC 001EA0AC 7679090C */  jal        func_0025E5D8
    /* EA0B0 001EA0B0 0800ADC7 */   lwc1      $f13, 0x8($29)
    /* EA0B4 001EA0B4 D88A81C7 */  lwc1       $f1, (D_006313C8) /* gp_rel: (D_006313C8) */
    /* EA0B8 001EA0B8 02000146 */  mul.s      $f0, $f0, $f1
    /* EA0BC 001EA0BC 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* EA0C0 001EA0C0 00080444 */  mfc1       $4, $f1
    /* EA0C4 001EA0C4 00240400 */  sll        $4, $4, 16
    /* EA0C8 001EA0C8 F013040C */  jal        func_00104FC0
    /* EA0CC 001EA0CC 03240400 */   sra       $4, $4, 16
    /* EA0D0 001EA0D0 9E14040C */  jal        func_00105278
    /* EA0D4 001EA0D4 00000000 */   nop
    /* EA0D8 001EA0D8 2D204002 */  daddu      $4, $18, $0
    /* EA0DC 001EA0DC C817040C */  jal        func_00105F20
    /* EA0E0 001EA0E0 2D284000 */   daddu     $5, $2, $0
    /* EA0E4 001EA0E4 2E3B040C */  jal        func_0010ECB8
    /* EA0E8 001EA0E8 2D202002 */   daddu     $4, $17, $0
    /* EA0EC 001EA0EC 4000BFDF */  ld         $31, 0x40($29)
    /* EA0F0 001EA0F0 3000B2DF */  ld         $18, 0x30($29)
    /* EA0F4 001EA0F4 2000B1DF */  ld         $17, 0x20($29)
    /* EA0F8 001EA0F8 1000B0DF */  ld         $16, 0x10($29)
    /* EA0FC 001EA0FC 0800E003 */  jr         $31
    /* EA100 001EA100 5000BD27 */   addiu     $29, $29, 0x50
endlabel func_001EA030
    /* EA104 001EA104 00000000 */  nop
```
