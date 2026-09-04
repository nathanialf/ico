# func_001CEC88 — parked

VRAM: 0x001CEC88 (file_off 0x0CEC88)
Asm source: asm/nonmatchings/src/enemyParts/func_001CEC88.s

## Attempt at 2026-05-31

**Reason parked:** rc11 STRUCTURE-PERFECT near-miss; sole residual is a v0/v1 birth-order swap (ROM: arithmetic-chain 60->num->quotient in v0, D-base+store-base in v1; built reversed). FP/*0.0f/divzero-guard/2 calls/offsets all match. 6 forms tried (inline/pointer-base/sixty-first/named-locals all identical rc11; num-before-calls rc29 frame-iosCdvdBackGroundMgrInit; int-return rc13 over-extends q). func_001886D0-class v0/v1 allocator tie-break; ideal regalloc-swap permuter target for auto_permute.

**TU:** `src/enemyParts.c`

**Seed:** `tough_nuts/func_001CEC88/func_001CEC88.c`

Disassembly:

```
.align 3
nonmatching func_001CEC88, 0xA0

glabel func_001CEC88
    /* CEC88 001CEC88 D0FFBD27 */  addiu      $29, $29, -0x30
    /* CEC8C 001CEC8C 1000B1FF */  sd         $17, 0x10($29)
    /* CEC90 001CEC90 2000BFFF */  sd         $31, 0x20($29)
    /* CEC94 001CEC94 2D888000 */  daddu      $17, $4, $0
    /* CEC98 001CEC98 0000B0FF */  sd         $16, 0x0($29)
    /* CEC9C 001CEC9C 5C01228E */  lw         $2, 0x15C($17)
    /* CECA0 001CECA0 0008508C */  lw         $16, 0x800($2)
    /* CECA4 001CECA4 883E070C */  jal        func_001CFA20
    /* CECA8 001CECA8 1800048E */   lw        $4, 0x18($16)
    /* CECAC 001CECAC 883E070C */  jal        func_001CFA20
    /* CECB0 001CECB0 2000048E */   lw        $4, 0x20($16)
    /* CECB4 001CECB4 2700033C */  lui        $3, %hi(D_00274EC0)
    /* CECB8 001CECB8 0A000624 */  addiu      $6, $0, 0xA
    /* CECBC 001CECBC C04E658C */  lw         $5, %lo(D_00274EC0)($3)
    /* CECC0 001CECC0 3C000224 */  addiu      $2, $0, 0x3C
    /* CECC4 001CECC4 C04E6324 */  addiu      $3, $3, %lo(D_00274EC0)
    /* CECC8 001CECC8 7042013C */  lui        $1, (0x42700000 >> 16)
    /* CECCC 001CECCC 00088144 */  mtc1       $1, $f1
    /* CECD0 001CECD0 1828A600 */  mult       $5, $5, $6
    /* CECD4 001CECD4 0400648C */  lw         $4, 0x4($3)
    /* CECD8 001CECD8 00108044 */  mtc1       $0, $f2
    /* CECDC 001CECDC 01008050 */  beql       $4, $0, .L001CECE4
    /* CECE0 001CECE0 CD010000 */   break     0, 7
.align 2
  .L001CECE4:
    /* CECE4 001CECE4 5C01238E */  lw         $3, 0x15C($17)
    /* CECE8 001CECE8 23104500 */  subu       $2, $2, $5
    /* CECEC 001CECEC 2000BFDF */  ld         $31, 0x20($29)
    /* CECF0 001CECF0 1A004400 */  div        $0, $2, $4
    /* CECF4 001CECF4 1000B1DF */  ld         $17, 0x10($29)
    /* CECF8 001CECF8 0000B0DF */  ld         $16, 0x0($29)
    /* CECFC 001CECFC 12100000 */  mflo       $2
    /* CED00 001CED00 00008244 */  mtc1       $2, $f0
    /* CED04 001CED04 20008046 */  cvt.s.w    $f0, $f0
    /* CED08 001CED08 00000000 */  nop
    /* CED0C 001CED0C 00000000 */  nop
    /* CED10 001CED10 03000146 */  div.s      $f0, $f0, $f1
    /* CED14 001CED14 02000246 */  mul.s      $f0, $f0, $f2
    /* CED18 001CED18 64000046 */  .word      0x46000064                    # cvt.w.s    $f1, $f0 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* CED1C 001CED1C 140561E4 */  swc1       $f1, 0x514($3)
    /* CED20 001CED20 0800E003 */  jr         $31
    /* CED24 001CED24 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001CEC88
```
