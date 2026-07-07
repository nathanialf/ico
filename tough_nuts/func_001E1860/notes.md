# func_001E1860 — parked

VRAM: 0x001E1860 (file_off 0x0E1860)
Asm source: asm/aug6/nonmatchings/sugipon/src/motionOrientManager/func_001E1860.s

## Attempt at 2026-07-07

**Reason parked:** rc45 STRUCTURE CORRECT (linked-list walk: GetRootProjectionPosOfGObj + 2x MatrixDrive + float copy 0x150->0x7C8 + Blk8 unaligned copy + do-while node walk idx/off via geom->0x8C nodes). Residual is PERMUTER-CLASS per tools/tag_diff.py fp-licm: gcc hoists the 0.0f GetTableArcSin arg into callee-saved f20 (ROM re-materializes mtc1 in-loop) -> frame 0x90 vs 0x70 + s5 vs callee-saved renumber (a0:s0 vs s1, off:s0). 5 distinct shapes (var-reduction, scope, decl-order, buf-type) all fold to same f20-hoist sig. Seed for permuter.

**TU:** `sugipon/src/motionOrientManager.c`

**Seed:** `tough_nuts/func_001E1860/func_001E1860.c`

Disassembly:

```
.align 3
nonmatching func_001E1860, 0x11C

glabel func_001E1860
    /* E1860 001E1860 90FFBD27 */  addiu      $29, $29, -0x70
    /* E1864 001E1864 002C0500 */  sll        $5, $5, 16
    /* E1868 001E1868 5000B4FF */  sd         $20, 0x50($29)
    /* E186C 001E186C 3000B2FF */  sd         $18, 0x30($29)
    /* E1870 001E1870 03A40500 */  sra        $20, $5, 16
    /* E1874 001E1874 2000B1FF */  sd         $17, 0x20($29)
    /* E1878 001E1878 2D900000 */  daddu      $18, $0, $0
    /* E187C 001E187C 6000BFFF */  sd         $31, 0x60($29)
    /* E1880 001E1880 2D888000 */  daddu      $17, $4, $0
    /* E1884 001E1884 4000B3FF */  sd         $19, 0x40($29)
    /* E1888 001E1888 1000B0FF */  sd         $16, 0x10($29)
    /* E188C 001E188C 5C01228E */  lw         $2, 0x15C($17)
    /* E1890 001E1890 9007538C */  lw         $19, 0x790($2)
    /* E1894 001E1894 8800468C */  lw         $6, 0x88($2)
    /* E1898 001E1898 7C07458C */  lw         $5, 0x77C($2)
    /* E189C 001E189C 122A040C */  jal        GetRootProjectionPosOfGObj
    /* E18A0 001E18A0 2D206002 */   daddu     $4, $19, $0
    /* E18A4 001E18A4 5C01248E */  lw         $4, 0x15C($17)
    /* E18A8 001E18A8 80078524 */  addiu      $5, $4, 0x780
    /* E18AC 001E18AC 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* E18B0 001E18B0 A0078424 */   addiu     $4, $4, 0x7A0
    /* E18B4 001E18B4 5C01248E */  lw         $4, 0x15C($17)
    /* E18B8 001E18B8 20018524 */  addiu      $5, $4, 0x120
    /* E18BC 001E18BC 4017040C */  jal        MatrixDrive_TurnObjectMatrix
    /* E18C0 001E18C0 B0078424 */   addiu     $4, $4, 0x7B0
    /* E18C4 001E18C4 5C01238E */  lw         $3, 0x15C($17)
    /* E18C8 001E18C8 FFFF0524 */  addiu      $5, $0, -0x1
    /* E18CC 001E18CC 500160C4 */  lwc1       $f0, 0x150($3)
    /* E18D0 001E18D0 C80760E4 */  swc1       $f0, 0x7C8($3)
    /* E18D4 001E18D4 5C01228E */  lw         $2, 0x15C($17)
    /* E18D8 001E18D8 07004368 */  ldl        $3, 0x7($2)
    /* E18DC 001E18DC 0000436C */  ldr        $3, 0x0($2)
    /* E18E0 001E18E0 C70743B0 */  sdl        $3, 0x7C7($2)
    /* E18E4 001E18E4 C00743B4 */  sdr        $3, 0x7C0($2)
    /* E18E8 001E18E8 5C01238E */  lw         $3, 0x15C($17)
    /* E18EC 001E18EC 8C00628C */  lw         $2, 0x8C($3)
    /* E18F0 001E18F0 3800448C */  lw         $4, 0x38($2)
    /* E18F4 001E18F4 1A008514 */  bne        $4, $5, .L001E1960
    /* E18F8 001E18F8 6000BFDF */   ld        $31, 0x60($29)
    /* E18FC 001E18FC 2D800000 */  daddu      $16, $0, $0
.align 2
  .L001E1900:
    /* E1900 001E1900 00608044 */  mtc1       $0, $f12
    /* E1904 001E1904 2D20A003 */  daddu      $4, $29, $0
    /* E1908 001E1908 803F013C */  lui        $1, (0x3F800000 >> 16)
    /* E190C 001E190C 00688144 */  mtc1       $1, $f13
    /* E1910 001E1910 2D288002 */  daddu      $5, $20, $0
    /* E1914 001E1914 BC37040C */  jal        GetTableArcSin
    /* E1918 001E1918 86630046 */   mov.s     $f14, $f12
    /* E191C 001E191C 40211200 */  sll        $4, $18, 5
    /* E1920 001E1920 2D28A003 */  daddu      $5, $29, $0
    /* E1924 001E1924 21206402 */  addu       $4, $19, $4
    /* E1928 001E1928 10008424 */  addiu      $4, $4, 0x10
    /* E192C 001E192C 5238040C */  jal        func_0010E148
    /* E1930 001E1930 2D308000 */   daddu     $6, $4, $0
    /* E1934 001E1934 5C01238E */  lw         $3, 0x15C($17)
    /* E1938 001E1938 FFFF0524 */  addiu      $5, $0, -0x1
    /* E193C 001E193C 8C00648C */  lw         $4, 0x8C($3)
    /* E1940 001E1940 21100402 */  addu       $2, $16, $4
    /* E1944 001E1944 3400528C */  lw         $18, 0x34($2)
    /* E1948 001E1948 80191200 */  sll        $3, $18, 6
    /* E194C 001E194C 2D806000 */  daddu      $16, $3, $0
    /* E1950 001E1950 21200402 */  addu       $4, $16, $4
    /* E1954 001E1954 3800828C */  lw         $2, 0x38($4)
    /* E1958 001E1958 E9FF4510 */  beq        $2, $5, .L001E1900
    /* E195C 001E195C 6000BFDF */   ld        $31, 0x60($29)
.align 2
  .L001E1960:
    /* E1960 001E1960 5000B4DF */  ld         $20, 0x50($29)
    /* E1964 001E1964 4000B3DF */  ld         $19, 0x40($29)
    /* E1968 001E1968 3000B2DF */  ld         $18, 0x30($29)
    /* E196C 001E196C 2000B1DF */  ld         $17, 0x20($29)
    /* E1970 001E1970 1000B0DF */  ld         $16, 0x10($29)
    /* E1974 001E1974 0800E003 */  jr         $31
    /* E1978 001E1978 7000BD27 */   addiu     $29, $29, 0x70
endlabel func_001E1860
    /* E197C 001E197C 00000000 */  nop
```
