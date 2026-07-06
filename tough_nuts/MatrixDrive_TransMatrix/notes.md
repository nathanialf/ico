# MatrixDrive_TransMatrix — parked

VRAM: 0x00105C70 (file_off 0x005C70)
Asm source: asm/aug6/nonmatchings/sugipon/src/matrixDrive/MatrixDrive_TransMatrix.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=4). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `sugipon/src/matrixDrive.c`

**Seed:** `tough_nuts/MatrixDrive_TransMatrix/MatrixDrive_TransMatrix.c`

Disassembly:

```
.align 3
nonmatching MatrixDrive_TransMatrix, 0x8C

glabel MatrixDrive_TransMatrix
    /* 5C70 00105C70 C0FFBD27 */  addiu      $29, $29, -0x40
    /* 5C74 00105C74 2D10A000 */  daddu      $2, $5, $0
    /* 5C78 00105C78 2000B0FF */  sd         $16, 0x20($29)
    /* 5C7C 00105C7C 3000BFFF */  sd         $31, 0x30($29)
    /* 5C80 00105C80 2D808000 */  daddu      $16, $4, $0
    /* 5C84 00105C84 300042C4 */  lwc1       $f2, 0x30($2)
    /* 5C88 00105C88 340041C4 */  lwc1       $f1, 0x34($2)
    /* 5C8C 00105C8C 380040C4 */  lwc1       $f0, 0x38($2)
    /* 5C90 00105C90 87100046 */  neg.s      $f2, $f2
    /* 5C94 00105C94 47080046 */  neg.s      $f1, $f1
    /* 5C98 00105C98 1C00A0AF */  sw         $0, 0x1C($29)
    /* 5C9C 00105C9C 07000046 */  neg.s      $f0, $f0
    /* 5CA0 00105CA0 1000A2E7 */  swc1       $f2, 0x10($29)
    /* 5CA4 00105CA4 1400A1E7 */  swc1       $f1, 0x14($29)
    /* 5CA8 00105CA8 1800A0E7 */  swc1       $f0, 0x18($29)
    /* 5CAC 00105CAC 1000A2DF */  ld         $2, 0x10($29)
    /* 5CB0 00105CB0 1800A3DF */  ld         $3, 0x18($29)
    /* 5CB4 00105CB4 0000A2FF */  sd         $2, 0x0($29)
    /* 5CB8 00105CB8 B4FF080C */  jal        func_0023FED0
    /* 5CBC 00105CBC 0800A3FF */   sd        $3, 0x8($29)
    /* 5CC0 00105CC0 00008044 */  mtc1       $0, $f0
    /* 5CC4 00105CC4 30000426 */  addiu      $4, $16, 0x30
    /* 5CC8 00105CC8 2D280002 */  daddu      $5, $16, $0
    /* 5CCC 00105CCC 2D30A003 */  daddu      $6, $29, $0
    /* 5CD0 00105CD0 0C0000E6 */  swc1       $f0, 0xC($16)
    /* 5CD4 00105CD4 2C0000E6 */  swc1       $f0, 0x2C($16)
    /* 5CD8 00105CD8 76FF080C */  jal        func_0023FDD8
    /* 5CDC 00105CDC 1C0000E6 */   swc1      $f0, 0x1C($16)
    /* 5CE0 00105CE0 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* 5CE4 00105CE4 00008144 */  mtc1       $1, $f0
    /* 5CE8 00105CE8 3000BFDF */  ld         $31, 0x30($29)
    /* 5CEC 00105CEC 3C0000E6 */  swc1       $f0, 0x3C($16)
    /* 5CF0 00105CF0 2000B0DF */  ld         $16, 0x20($29)
    /* 5CF4 00105CF4 0800E003 */  jr         $31
    /* 5CF8 00105CF8 4000BD27 */   addiu     $29, $29, 0x40
endlabel MatrixDrive_TransMatrix
    /* 5CFC 00105CFC 00000000 */  nop
```
