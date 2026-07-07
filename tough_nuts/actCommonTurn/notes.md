# actCommonTurn — parked

VRAM: 0x0015D190 (file_off 0x05D190)
Asm source: asm/aug6/nonmatchings/fumi/src/commonact/actCommonTurn.s

## Attempt at 2026-06-26

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=40). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/actCommonTurn/actCommonTurn.c`

Disassembly:

```
.align 3
nonmatching actCommonTurn, 0x150

glabel actCommonTurn
    /* 5D190 0015D190 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 5D194 0015D194 1000B1FF */  sd         $17, 0x10($29)
    /* 5D198 0015D198 2D888000 */  daddu      $17, $4, $0
    /* 5D19C 0015D19C 3000B3FF */  sd         $19, 0x30($29)
    /* 5D1A0 0015D1A0 2000B2FF */  sd         $18, 0x20($29)
    /* 5D1A4 0015D1A4 2D98E000 */  daddu      $19, $7, $0
    /* 5D1A8 0015D1A8 0000B0FF */  sd         $16, 0x0($29)
    /* 5D1AC 0015D1AC 2D90C000 */  daddu      $18, $6, $0
    /* 5D1B0 0015D1B0 5000B4E7 */  swc1       $f20, 0x50($29)
    /* 5D1B4 0015D1B4 2D80A000 */  daddu      $16, $5, $0
    /* 5D1B8 0015D1B8 4000BFFF */  sd         $31, 0x40($29)
    /* 5D1BC 0015D1BC 3E74050C */  jal        ContinueCorrectPosition
    /* 5D1C0 0015D1C0 06650046 */   mov.s     $f20, $f12
    /* 5D1C4 0015D1C4 6401238E */  lw         $3, 0x164($17)
    /* 5D1C8 0015D1C8 2D202002 */  daddu      $4, $17, $0
    /* 5D1CC 0015D1CC 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5D1D0 0015D1D0 7006628C */  lw         $2, 0x670($3)
    /* 5D1D4 0015D1D4 3E74050C */  jal        ContinueCorrectPosition
    /* 5D1D8 0015D1D8 700040E4 */   swc1      $f0, 0x70($2)
    /* 5D1DC 0015D1DC 6401238E */  lw         $3, 0x164($17)
    /* 5D1E0 0015D1E0 2D202002 */  daddu      $4, $17, $0
    /* 5D1E4 0015D1E4 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5D1E8 0015D1E8 7006628C */  lw         $2, 0x670($3)
    /* 5D1EC 0015D1EC 3E74050C */  jal        ContinueCorrectPosition
    /* 5D1F0 0015D1F0 740040E4 */   swc1      $f0, 0x74($2)
    /* 5D1F4 0015D1F4 6401238E */  lw         $3, 0x164($17)
    /* 5D1F8 0015D1F8 2D202002 */  daddu      $4, $17, $0
    /* 5D1FC 0015D1FC 080040C4 */  lwc1       $f0, 0x8($2)
    /* 5D200 0015D200 7006628C */  lw         $2, 0x670($3)
    /* 5D204 0015D204 2274050C */  jal        subCommonIdle
    /* 5D208 0015D208 780040E4 */   swc1      $f0, 0x78($2)
    /* 5D20C 0015D20C 6401238E */  lw         $3, 0x164($17)
    /* 5D210 0015D210 2D202002 */  daddu      $4, $17, $0
    /* 5D214 0015D214 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5D218 0015D218 7006628C */  lw         $2, 0x670($3)
    /* 5D21C 0015D21C 2274050C */  jal        subCommonIdle
    /* 5D220 0015D220 800040E4 */   swc1      $f0, 0x80($2)
    /* 5D224 0015D224 6401238E */  lw         $3, 0x164($17)
    /* 5D228 0015D228 2D202002 */  daddu      $4, $17, $0
    /* 5D22C 0015D22C 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5D230 0015D230 7006628C */  lw         $2, 0x670($3)
    /* 5D234 0015D234 2274050C */  jal        subCommonIdle
    /* 5D238 0015D238 840040E4 */   swc1      $f0, 0x84($2)
    /* 5D23C 0015D23C 6401238E */  lw         $3, 0x164($17)
    /* 5D240 0015D240 080041C4 */  lwc1       $f1, 0x8($2)
    /* 5D244 0015D244 7006628C */  lw         $2, 0x670($3)
    /* 5D248 0015D248 880041E4 */  swc1       $f1, 0x88($2)
    /* 5D24C 0015D24C 000000C6 */  lwc1       $f0, 0x0($16)
    /* 5D250 0015D250 900040E4 */  swc1       $f0, 0x90($2)
    /* 5D254 0015D254 040001C6 */  lwc1       $f1, 0x4($16)
    /* 5D258 0015D258 940041E4 */  swc1       $f1, 0x94($2)
    /* 5D25C 0015D25C 080000C6 */  lwc1       $f0, 0x8($16)
    /* 5D260 0015D260 07004012 */  beqz       $18, .L0015D280
    /* 5D264 0015D264 980040E4 */   swc1      $f0, 0x98($2)
    /* 5D268 0015D268 000040C6 */  lwc1       $f0, 0x0($18)
    /* 5D26C 0015D26C A00040E4 */  swc1       $f0, 0xA0($2)
    /* 5D270 0015D270 040041C6 */  lwc1       $f1, 0x4($18)
    /* 5D274 0015D274 A40041E4 */  swc1       $f1, 0xA4($2)
    /* 5D278 0015D278 080040C6 */  lwc1       $f0, 0x8($18)
    /* 5D27C 0015D27C A80040E4 */  swc1       $f0, 0xA8($2)
.align 2
  .L0015D280:
    /* 5D280 0015D280 7006638C */  lw         $3, 0x670($3)
    /* 5D284 0015D284 00800534 */  ori        $5, $0, 0x8000
    /* 5D288 0015D288 782C0500 */  dsll       $5, $5, 17
    /* 5D28C 0015D28C 4000BFDF */  ld         $31, 0x40($29)
    /* 5D290 0015D290 24A00046 */  .word      0x4600A024                    # cvt.w.s    $f0, $f20 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 5D294 0015D294 B00060E4 */  swc1       $f0, 0xB0($3)
    /* 5D298 0015D298 2000B2DF */  ld         $18, 0x20($29)
    /* 5D29C 0015D29C 0000B0DF */  ld         $16, 0x0($29)
    /* 5D2A0 0015D2A0 5000B4C7 */  lwc1       $f20, 0x50($29)
    /* 5D2A4 0015D2A4 6401228E */  lw         $2, 0x164($17)
    /* 5D2A8 0015D2A8 7006438C */  lw         $3, 0x670($2)
    /* 5D2AC 0015D2AC B40060AC */  sw         $0, 0xB4($3)
    /* 5D2B0 0015D2B0 6401228E */  lw         $2, 0x164($17)
    /* 5D2B4 0015D2B4 7006438C */  lw         $3, 0x670($2)
    /* 5D2B8 0015D2B8 B80073AC */  sw         $19, 0xB8($3)
    /* 5D2BC 0015D2BC 3000B3DF */  ld         $19, 0x30($29)
    /* 5D2C0 0015D2C0 6401248E */  lw         $4, 0x164($17)
    /* 5D2C4 0015D2C4 1000B1DF */  ld         $17, 0x10($29)
    /* 5D2C8 0015D2C8 7006838C */  lw         $3, 0x670($4)
    /* 5D2CC 0015D2CC B80062DC */  ld         $2, 0xB8($3)
    /* 5D2D0 0015D2D0 25104500 */  or         $2, $2, $5
    /* 5D2D4 0015D2D4 B80062FC */  sd         $2, 0xB8($3)
    /* 5D2D8 0015D2D8 0800E003 */  jr         $31
    /* 5D2DC 0015D2DC 6000BD27 */   addiu     $29, $29, 0x60
endlabel actCommonTurn
```

---

## Attempt at 2026-07-07

**Reason parked:** rc40 body byte-correct (all Continue/subCommonIdle call-reloaded stores + a1/a2 vec + cvt.w.s tail match). residual = a0/a1 s1<->s0 callee-saved swap (cascades ~half) + epilogue rematerializes o=self->164->670 for B0/B4/B8 (aug6 lacks -fno-strict-aliasing so build CSEs o). permuter territory.

**TU:** `fumi/src/commonact.c`

**Seed:** `tough_nuts/actCommonTurn/actCommonTurn.1.c`

Disassembly:

```
.align 3
nonmatching actCommonTurn, 0x150

glabel actCommonTurn
    /* 5D190 0015D190 A0FFBD27 */  addiu      $29, $29, -0x60
    /* 5D194 0015D194 1000B1FF */  sd         $17, 0x10($29)
    /* 5D198 0015D198 2D888000 */  daddu      $17, $4, $0
    /* 5D19C 0015D19C 3000B3FF */  sd         $19, 0x30($29)
    /* 5D1A0 0015D1A0 2000B2FF */  sd         $18, 0x20($29)
    /* 5D1A4 0015D1A4 2D98E000 */  daddu      $19, $7, $0
    /* 5D1A8 0015D1A8 0000B0FF */  sd         $16, 0x0($29)
    /* 5D1AC 0015D1AC 2D90C000 */  daddu      $18, $6, $0
    /* 5D1B0 0015D1B0 5000B4E7 */  swc1       $f20, 0x50($29)
    /* 5D1B4 0015D1B4 2D80A000 */  daddu      $16, $5, $0
    /* 5D1B8 0015D1B8 4000BFFF */  sd         $31, 0x40($29)
    /* 5D1BC 0015D1BC 3E74050C */  jal        ContinueCorrectPosition
    /* 5D1C0 0015D1C0 06650046 */   mov.s     $f20, $f12
    /* 5D1C4 0015D1C4 6401238E */  lw         $3, 0x164($17)
    /* 5D1C8 0015D1C8 2D202002 */  daddu      $4, $17, $0
    /* 5D1CC 0015D1CC 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5D1D0 0015D1D0 7006628C */  lw         $2, 0x670($3)
    /* 5D1D4 0015D1D4 3E74050C */  jal        ContinueCorrectPosition
    /* 5D1D8 0015D1D8 700040E4 */   swc1      $f0, 0x70($2)
    /* 5D1DC 0015D1DC 6401238E */  lw         $3, 0x164($17)
    /* 5D1E0 0015D1E0 2D202002 */  daddu      $4, $17, $0
    /* 5D1E4 0015D1E4 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5D1E8 0015D1E8 7006628C */  lw         $2, 0x670($3)
    /* 5D1EC 0015D1EC 3E74050C */  jal        ContinueCorrectPosition
    /* 5D1F0 0015D1F0 740040E4 */   swc1      $f0, 0x74($2)
    /* 5D1F4 0015D1F4 6401238E */  lw         $3, 0x164($17)
    /* 5D1F8 0015D1F8 2D202002 */  daddu      $4, $17, $0
    /* 5D1FC 0015D1FC 080040C4 */  lwc1       $f0, 0x8($2)
    /* 5D200 0015D200 7006628C */  lw         $2, 0x670($3)
    /* 5D204 0015D204 2274050C */  jal        subCommonIdle
    /* 5D208 0015D208 780040E4 */   swc1      $f0, 0x78($2)
    /* 5D20C 0015D20C 6401238E */  lw         $3, 0x164($17)
    /* 5D210 0015D210 2D202002 */  daddu      $4, $17, $0
    /* 5D214 0015D214 000040C4 */  lwc1       $f0, 0x0($2)
    /* 5D218 0015D218 7006628C */  lw         $2, 0x670($3)
    /* 5D21C 0015D21C 2274050C */  jal        subCommonIdle
    /* 5D220 0015D220 800040E4 */   swc1      $f0, 0x80($2)
    /* 5D224 0015D224 6401238E */  lw         $3, 0x164($17)
    /* 5D228 0015D228 2D202002 */  daddu      $4, $17, $0
    /* 5D22C 0015D22C 040040C4 */  lwc1       $f0, 0x4($2)
    /* 5D230 0015D230 7006628C */  lw         $2, 0x670($3)
    /* 5D234 0015D234 2274050C */  jal        subCommonIdle
    /* 5D238 0015D238 840040E4 */   swc1      $f0, 0x84($2)
    /* 5D23C 0015D23C 6401238E */  lw         $3, 0x164($17)
    /* 5D240 0015D240 080041C4 */  lwc1       $f1, 0x8($2)
    /* 5D244 0015D244 7006628C */  lw         $2, 0x670($3)
    /* 5D248 0015D248 880041E4 */  swc1       $f1, 0x88($2)
    /* 5D24C 0015D24C 000000C6 */  lwc1       $f0, 0x0($16)
    /* 5D250 0015D250 900040E4 */  swc1       $f0, 0x90($2)
    /* 5D254 0015D254 040001C6 */  lwc1       $f1, 0x4($16)
    /* 5D258 0015D258 940041E4 */  swc1       $f1, 0x94($2)
    /* 5D25C 0015D25C 080000C6 */  lwc1       $f0, 0x8($16)
    /* 5D260 0015D260 07004012 */  beqz       $18, .L0015D280
    /* 5D264 0015D264 980040E4 */   swc1      $f0, 0x98($2)
    /* 5D268 0015D268 000040C6 */  lwc1       $f0, 0x0($18)
    /* 5D26C 0015D26C A00040E4 */  swc1       $f0, 0xA0($2)
    /* 5D270 0015D270 040041C6 */  lwc1       $f1, 0x4($18)
    /* 5D274 0015D274 A40041E4 */  swc1       $f1, 0xA4($2)
    /* 5D278 0015D278 080040C6 */  lwc1       $f0, 0x8($18)
    /* 5D27C 0015D27C A80040E4 */  swc1       $f0, 0xA8($2)
.align 2
  .L0015D280:
    /* 5D280 0015D280 7006638C */  lw         $3, 0x670($3)
    /* 5D284 0015D284 00800534 */  ori        $5, $0, 0x8000
    /* 5D288 0015D288 782C0500 */  dsll       $5, $5, 17
    /* 5D28C 0015D28C 4000BFDF */  ld         $31, 0x40($29)
    /* 5D290 0015D290 24A00046 */  .word      0x4600A024                    # cvt.w.s    $f0, $f20 # 00000000 <InstrIdType: CPU_COP1_FPUS>
    /* 5D294 0015D294 B00060E4 */  swc1       $f0, 0xB0($3)
    /* 5D298 0015D298 2000B2DF */  ld         $18, 0x20($29)
    /* 5D29C 0015D29C 0000B0DF */  ld         $16, 0x0($29)
    /* 5D2A0 0015D2A0 5000B4C7 */  lwc1       $f20, 0x50($29)
    /* 5D2A4 0015D2A4 6401228E */  lw         $2, 0x164($17)
    /* 5D2A8 0015D2A8 7006438C */  lw         $3, 0x670($2)
    /* 5D2AC 0015D2AC B40060AC */  sw         $0, 0xB4($3)
    /* 5D2B0 0015D2B0 6401228E */  lw         $2, 0x164($17)
    /* 5D2B4 0015D2B4 7006438C */  lw         $3, 0x670($2)
    /* 5D2B8 0015D2B8 B80073AC */  sw         $19, 0xB8($3)
    /* 5D2BC 0015D2BC 3000B3DF */  ld         $19, 0x30($29)
    /* 5D2C0 0015D2C0 6401248E */  lw         $4, 0x164($17)
    /* 5D2C4 0015D2C4 1000B1DF */  ld         $17, 0x10($29)
    /* 5D2C8 0015D2C8 7006838C */  lw         $3, 0x670($4)
    /* 5D2CC 0015D2CC B80062DC */  ld         $2, 0xB8($3)
    /* 5D2D0 0015D2D0 25104500 */  or         $2, $2, $5
    /* 5D2D4 0015D2D4 B80062FC */  sd         $2, 0xB8($3)
    /* 5D2D8 0015D2D8 0800E003 */  jr         $31
    /* 5D2DC 0015D2DC 6000BD27 */   addiu     $29, $29, 0x60
endlabel actCommonTurn
```
