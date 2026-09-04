# func_0016B028 — parked

VRAM: 0x0016B028 (file_off 0x06B028)
Asm source: asm/aug6/nonmatchings/fumi/src/girl_act/func_0016B028.s

## Attempt at 2026-06-30

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=3). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/girl_act.c`

**Seed:** `tough_nuts/func_0016B028/func_0016B028.c`

Disassembly:

```
.align 3
nonmatching func_0016B028, 0x154

glabel func_0016B028
    /* 6B028 0016B028 70FFBD27 */  addiu      $29, $29, -0x90
    /* 6B02C 0016B02C 2D10A000 */  daddu      $2, $5, $0
    /* 6B030 0016B030 7000B4FF */  sd         $20, 0x70($29)
    /* 6B034 0016B034 2C000624 */  addiu      $6, $0, 0x2C
    /* 6B038 0016B038 6000B3FF */  sd         $19, 0x60($29)
    /* 6B03C 0016B03C 2DA08000 */  daddu      $20, $4, $0
    /* 6B040 0016B040 5000B2FF */  sd         $18, 0x50($29)
    /* 6B044 0016B044 2D20A003 */  daddu      $4, $29, $0
    /* 6B048 0016B048 4000B1FF */  sd         $17, 0x40($29)
    /* 6B04C 0016B04C 2D288002 */  daddu      $5, $20, $0
    /* 6B050 0016B050 3000B0FF */  sd         $16, 0x30($29)
    /* 6B054 0016B054 8000BFFF */  sd         $31, 0x80($29)
    /* 6B058 0016B058 2D800000 */  daddu      $16, $0, $0
    /* 6B05C 0016B05C 080042C4 */  lwc1       $f2, 0x8($2)
    /* 6B060 0016B060 000040C4 */  lwc1       $f0, 0x0($2)
    /* 6B064 0016B064 040041C4 */  lwc1       $f1, 0x4($2)
    /* 6B068 0016B068 1000A0E7 */  swc1       $f0, 0x10($29)
    /* 6B06C 0016B06C 1400A1E7 */  swc1       $f1, 0x14($29)
    /* 6B070 0016B070 EE10050C */  jal        func_001443B8
    /* 6B074 0016B074 1800A2E7 */   swc1      $f2, 0x18($29)
    /* 6B078 0016B078 1000B327 */  addiu      $19, $29, 0x10
    /* 6B07C 0016B07C 2D20A003 */  daddu      $4, $29, $0
    /* 6B080 0016B080 4247060C */  jal        _RotyGV
    /* 6B084 0016B084 2D286002 */   daddu     $5, $19, $0
    /* 6B088 0016B088 2D884000 */  daddu      $17, $2, $0
    /* 6B08C 0016B08C 02002106 */  bgez       $17, .L0016B098
    /* 6B090 0016B090 2D902002 */   daddu     $18, $17, $0
    /* 6B094 0016B094 23901200 */  negu       $18, $18
.align 2
  .L0016B098:
    /* 6B098 0016B098 1500422A */  slti       $2, $18, 0x15
    /* 6B09C 0016B09C 2F004014 */  bnez       $2, .L0016B15C
    /* 6B0A0 0016B0A0 2D100002 */   daddu     $2, $16, $0
    /* 6B0A4 0016B0A4 2000B027 */  addiu      $16, $29, 0x20
    /* 6B0A8 0016B0A8 2D288002 */  daddu      $5, $20, $0
    /* 6B0AC 0016B0AC 2D200002 */  daddu      $4, $16, $0
    /* 6B0B0 0016B0B0 EE10050C */  jal        func_001443B8
    /* 6B0B4 0016B0B4 23000624 */   addiu     $6, $0, 0x23
    /* 6B0B8 0016B0B8 2D200002 */  daddu      $4, $16, $0
    /* 6B0BC 0016B0BC 4247060C */  jal        _RotyGV
    /* 6B0C0 0016B0C0 2D286002 */   daddu     $5, $19, $0
    /* 6B0C4 0016B0C4 2D184000 */  daddu      $3, $2, $0
    /* 6B0C8 0016B0C8 5A00422A */  slti       $2, $18, 0x5A
    /* 6B0CC 0016B0CC 03004010 */  beqz       $2, .L0016B0DC
    /* 6B0D0 0016B0D0 18102302 */   mult      $2, $17, $3
    /* 6B0D4 0016B0D4 02004004 */  bltz       $2, .L0016B0E0
    /* 6B0D8 0016B0D8 2D102002 */   daddu     $2, $17, $0
.align 2
  .L0016B0DC:
    /* 6B0DC 0016B0DC 2D106000 */  daddu      $2, $3, $0
.align 2
  .L0016B0E0:
    /* 6B0E0 0016B0E0 0E004018 */  blez       $2, .L0016B11C
    /* 6B0E4 0016B0E4 6A00043C */   lui       $4, %hi(D_006A58A0)
    /* 6B0E8 0016B0E8 02000524 */  addiu      $5, $0, 0x2
    /* 6B0EC 0016B0EC A058828C */  lw         $2, %lo(D_006A58A0)($4)
    /* 6B0F0 0016B0F0 2A10A200 */  slt        $2, $5, $2
    /* 6B0F4 0016B0F4 17004014 */  bnez       $2, .L0016B154
    /* 6B0F8 0016B0F8 A0588324 */   addiu     $3, $4, %lo(D_006A58A0)
    /* 6B0FC 0016B0FC 1000A0C7 */  lwc1       $f0, 0x10($29)
    /* 6B100 0016B100 1400A2C7 */  lwc1       $f2, 0x14($29)
    /* 6B104 0016B104 1800A1C7 */  lwc1       $f1, 0x18($29)
    /* 6B108 0016B108 A05885AC */  sw         $5, %lo(D_006A58A0)($4)
    /* 6B10C 0016B10C 180061E4 */  swc1       $f1, 0x18($3)
    /* 6B110 0016B110 040065AC */  sw         $5, 0x4($3)
    /* 6B114 0016B114 0E000010 */  b          .L0016B150
    /* 6B118 0016B118 100060E4 */   swc1      $f0, 0x10($3)
.align 2
  .L0016B11C:
    /* 6B11C 0016B11C 02000524 */  addiu      $5, $0, 0x2
    /* 6B120 0016B120 A058828C */  lw         $2, %lo(D_006A58A0)($4)
    /* 6B124 0016B124 2A10A200 */  slt        $2, $5, $2
    /* 6B128 0016B128 0A004014 */  bnez       $2, .L0016B154
    /* 6B12C 0016B12C A0588324 */   addiu     $3, $4, %lo(D_006A58A0)
    /* 6B130 0016B130 1000A1C7 */  lwc1       $f1, 0x10($29)
    /* 6B134 0016B134 01000224 */  addiu      $2, $0, 0x1
    /* 6B138 0016B138 1400A2C7 */  lwc1       $f2, 0x14($29)
    /* 6B13C 0016B13C 1800A0C7 */  lwc1       $f0, 0x18($29)
    /* 6B140 0016B140 A05885AC */  sw         $5, %lo(D_006A58A0)($4)
    /* 6B144 0016B144 180060E4 */  swc1       $f0, 0x18($3)
    /* 6B148 0016B148 040062AC */  sw         $2, 0x4($3)
    /* 6B14C 0016B14C 100061E4 */  swc1       $f1, 0x10($3)
.align 2
  .L0016B150:
    /* 6B150 0016B150 140062E4 */  swc1       $f2, 0x14($3)
.align 2
  .L0016B154:
    /* 6B154 0016B154 01001024 */  addiu      $16, $0, 0x1
    /* 6B158 0016B158 2D100002 */  daddu      $2, $16, $0
.align 2
  .L0016B15C:
    /* 6B15C 0016B15C 8000BFDF */  ld         $31, 0x80($29)
    /* 6B160 0016B160 7000B4DF */  ld         $20, 0x70($29)
    /* 6B164 0016B164 6000B3DF */  ld         $19, 0x60($29)
    /* 6B168 0016B168 5000B2DF */  ld         $18, 0x50($29)
    /* 6B16C 0016B16C 4000B1DF */  ld         $17, 0x40($29)
    /* 6B170 0016B170 3000B0DF */  ld         $16, 0x30($29)
    /* 6B174 0016B174 0800E003 */  jr         $31
    /* 6B178 0016B178 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_0016B028
    /* 6B17C 0016B17C 00000000 */  nop
```

---

## Attempt at 2026-07-07

**Reason parked:** rc3 permuter-domain store-schedule floor: body byte-perfect; block B (mode=1) stores z,x,mode,y but ROM wants z,mode,x,y (int mode-store vs float x-store schedule tie). Aligning source to block A order MERGES the two duplicated CamRec-write blocks (rc6); 5 distinct block-B orderings all >=rc3. Anti-merge (scramble/do-while0) required, so aligned-correct order unreachable by source. Permuter-seeded.

**TU:** `fumi/src/girl_act.c`

**Seed:** `tough_nuts/func_0016B028/func_0016B028.1.c`

Disassembly:

```
.align 3
nonmatching func_0016B028, 0x154

glabel func_0016B028
    /* 6B028 0016B028 70FFBD27 */  addiu      $29, $29, -0x90
    /* 6B02C 0016B02C 2D10A000 */  daddu      $2, $5, $0
    /* 6B030 0016B030 7000B4FF */  sd         $20, 0x70($29)
    /* 6B034 0016B034 2C000624 */  addiu      $6, $0, 0x2C
    /* 6B038 0016B038 6000B3FF */  sd         $19, 0x60($29)
    /* 6B03C 0016B03C 2DA08000 */  daddu      $20, $4, $0
    /* 6B040 0016B040 5000B2FF */  sd         $18, 0x50($29)
    /* 6B044 0016B044 2D20A003 */  daddu      $4, $29, $0
    /* 6B048 0016B048 4000B1FF */  sd         $17, 0x40($29)
    /* 6B04C 0016B04C 2D288002 */  daddu      $5, $20, $0
    /* 6B050 0016B050 3000B0FF */  sd         $16, 0x30($29)
    /* 6B054 0016B054 8000BFFF */  sd         $31, 0x80($29)
    /* 6B058 0016B058 2D800000 */  daddu      $16, $0, $0
    /* 6B05C 0016B05C 080042C4 */  lwc1       $f2, 0x8($2)
    /* 6B060 0016B060 000040C4 */  lwc1       $f0, 0x0($2)
    /* 6B064 0016B064 040041C4 */  lwc1       $f1, 0x4($2)
    /* 6B068 0016B068 1000A0E7 */  swc1       $f0, 0x10($29)
    /* 6B06C 0016B06C 1400A1E7 */  swc1       $f1, 0x14($29)
    /* 6B070 0016B070 EE10050C */  jal        func_001443B8
    /* 6B074 0016B074 1800A2E7 */   swc1      $f2, 0x18($29)
    /* 6B078 0016B078 1000B327 */  addiu      $19, $29, 0x10
    /* 6B07C 0016B07C 2D20A003 */  daddu      $4, $29, $0
    /* 6B080 0016B080 4247060C */  jal        _RotyGV
    /* 6B084 0016B084 2D286002 */   daddu     $5, $19, $0
    /* 6B088 0016B088 2D884000 */  daddu      $17, $2, $0
    /* 6B08C 0016B08C 02002106 */  bgez       $17, .L0016B098
    /* 6B090 0016B090 2D902002 */   daddu     $18, $17, $0
    /* 6B094 0016B094 23901200 */  negu       $18, $18
.align 2
  .L0016B098:
    /* 6B098 0016B098 1500422A */  slti       $2, $18, 0x15
    /* 6B09C 0016B09C 2F004014 */  bnez       $2, .L0016B15C
    /* 6B0A0 0016B0A0 2D100002 */   daddu     $2, $16, $0
    /* 6B0A4 0016B0A4 2000B027 */  addiu      $16, $29, 0x20
    /* 6B0A8 0016B0A8 2D288002 */  daddu      $5, $20, $0
    /* 6B0AC 0016B0AC 2D200002 */  daddu      $4, $16, $0
    /* 6B0B0 0016B0B0 EE10050C */  jal        func_001443B8
    /* 6B0B4 0016B0B4 23000624 */   addiu     $6, $0, 0x23
    /* 6B0B8 0016B0B8 2D200002 */  daddu      $4, $16, $0
    /* 6B0BC 0016B0BC 4247060C */  jal        _RotyGV
    /* 6B0C0 0016B0C0 2D286002 */   daddu     $5, $19, $0
    /* 6B0C4 0016B0C4 2D184000 */  daddu      $3, $2, $0
    /* 6B0C8 0016B0C8 5A00422A */  slti       $2, $18, 0x5A
    /* 6B0CC 0016B0CC 03004010 */  beqz       $2, .L0016B0DC
    /* 6B0D0 0016B0D0 18102302 */   mult      $2, $17, $3
    /* 6B0D4 0016B0D4 02004004 */  bltz       $2, .L0016B0E0
    /* 6B0D8 0016B0D8 2D102002 */   daddu     $2, $17, $0
.align 2
  .L0016B0DC:
    /* 6B0DC 0016B0DC 2D106000 */  daddu      $2, $3, $0
.align 2
  .L0016B0E0:
    /* 6B0E0 0016B0E0 0E004018 */  blez       $2, .L0016B11C
    /* 6B0E4 0016B0E4 6A00043C */   lui       $4, %hi(D_006A58A0)
    /* 6B0E8 0016B0E8 02000524 */  addiu      $5, $0, 0x2
    /* 6B0EC 0016B0EC A058828C */  lw         $2, %lo(D_006A58A0)($4)
    /* 6B0F0 0016B0F0 2A10A200 */  slt        $2, $5, $2
    /* 6B0F4 0016B0F4 17004014 */  bnez       $2, .L0016B154
    /* 6B0F8 0016B0F8 A0588324 */   addiu     $3, $4, %lo(D_006A58A0)
    /* 6B0FC 0016B0FC 1000A0C7 */  lwc1       $f0, 0x10($29)
    /* 6B100 0016B100 1400A2C7 */  lwc1       $f2, 0x14($29)
    /* 6B104 0016B104 1800A1C7 */  lwc1       $f1, 0x18($29)
    /* 6B108 0016B108 A05885AC */  sw         $5, %lo(D_006A58A0)($4)
    /* 6B10C 0016B10C 180061E4 */  swc1       $f1, 0x18($3)
    /* 6B110 0016B110 040065AC */  sw         $5, 0x4($3)
    /* 6B114 0016B114 0E000010 */  b          .L0016B150
    /* 6B118 0016B118 100060E4 */   swc1      $f0, 0x10($3)
.align 2
  .L0016B11C:
    /* 6B11C 0016B11C 02000524 */  addiu      $5, $0, 0x2
    /* 6B120 0016B120 A058828C */  lw         $2, %lo(D_006A58A0)($4)
    /* 6B124 0016B124 2A10A200 */  slt        $2, $5, $2
    /* 6B128 0016B128 0A004014 */  bnez       $2, .L0016B154
    /* 6B12C 0016B12C A0588324 */   addiu     $3, $4, %lo(D_006A58A0)
    /* 6B130 0016B130 1000A1C7 */  lwc1       $f1, 0x10($29)
    /* 6B134 0016B134 01000224 */  addiu      $2, $0, 0x1
    /* 6B138 0016B138 1400A2C7 */  lwc1       $f2, 0x14($29)
    /* 6B13C 0016B13C 1800A0C7 */  lwc1       $f0, 0x18($29)
    /* 6B140 0016B140 A05885AC */  sw         $5, %lo(D_006A58A0)($4)
    /* 6B144 0016B144 180060E4 */  swc1       $f0, 0x18($3)
    /* 6B148 0016B148 040062AC */  sw         $2, 0x4($3)
    /* 6B14C 0016B14C 100061E4 */  swc1       $f1, 0x10($3)
.align 2
  .L0016B150:
    /* 6B150 0016B150 140062E4 */  swc1       $f2, 0x14($3)
.align 2
  .L0016B154:
    /* 6B154 0016B154 01001024 */  addiu      $16, $0, 0x1
    /* 6B158 0016B158 2D100002 */  daddu      $2, $16, $0
.align 2
  .L0016B15C:
    /* 6B15C 0016B15C 8000BFDF */  ld         $31, 0x80($29)
    /* 6B160 0016B160 7000B4DF */  ld         $20, 0x70($29)
    /* 6B164 0016B164 6000B3DF */  ld         $19, 0x60($29)
    /* 6B168 0016B168 5000B2DF */  ld         $18, 0x50($29)
    /* 6B16C 0016B16C 4000B1DF */  ld         $17, 0x40($29)
    /* 6B170 0016B170 3000B0DF */  ld         $16, 0x30($29)
    /* 6B174 0016B174 0800E003 */  jr         $31
    /* 6B178 0016B178 9000BD27 */   addiu     $29, $29, 0x90
endlabel func_0016B028
    /* 6B17C 0016B17C 00000000 */  nop
```
