# func_0013D718 — parked

VRAM: 0x0013D718 (file_off 0x03D718)
Asm source: asm/aug6/nonmatchings/fumi/ios/thread/func_0013D718.s

## Attempt at 2026-07-01

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=11). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/ios/thread.c`

**Seed:** `tough_nuts/func_0013D718/func_0013D718.c`

Disassembly:

```
.align 3
nonmatching func_0013D718, 0xEC

glabel func_0013D718
    /* 3D718 0013D718 80FFBD27 */  addiu      $29, $29, -0x80
    /* 3D71C 0013D71C 5500043C */  lui        $4, %hi(D_00551CF8)
    /* 3D720 0013D720 6000B5FF */  sd         $21, 0x60($29)
    /* 3D724 0013D724 F81C8424 */  addiu      $4, $4, %lo(D_00551CF8)
    /* 3D728 0013D728 5000B4FF */  sd         $20, 0x50($29)
    /* 3D72C 0013D72C 4000B3FF */  sd         $19, 0x40($29)
    /* 3D730 0013D730 5500153C */  lui        $21, %hi(D_00551D18)
    /* 3D734 0013D734 3000B2FF */  sd         $18, 0x30($29)
    /* 3D738 0013D738 6A00133C */  lui        $19, %hi(D_006A0EB0)
    /* 3D73C 0013D73C 7000BFFF */  sd         $31, 0x70($29)
    /* 3D740 0013D740 01001424 */  addiu      $20, $0, 0x1
    /* 3D744 0013D744 2000B1FF */  sd         $17, 0x20($29)
    /* 3D748 0013D748 F290060C */  jal        debug_assertMessage
    /* 3D74C 0013D74C 1000B0FF */   sd        $16, 0x10($29)
    /* 3D750 0013D750 B00E6426 */  addiu      $4, $19, %lo(D_006A0EB0)
    /* 3D754 0013D754 B0B38527 */  addiu      $5, $28, %gp_rel(D_0062BFA0)
    /* 3D758 0013D758 4EE7040C */  jal        iosMsgQueueDestroy
    /* 3D75C 0013D75C 02000624 */   addiu     $6, $0, 0x2
    /* 3D760 0013D760 6A00023C */  lui        $2, %hi(D_006A0AB0)
    /* 3D764 0013D764 B00A5224 */  addiu      $18, $2, %lo(D_006A0AB0)
.align 2
  .L0013D768:
    /* 3D768 0013D768 B00E6426 */  addiu      $4, $19, %lo(D_006A0EB0)
    /* 3D76C 0013D76C 2D28A003 */  daddu      $5, $29, $0
    /* 3D770 0013D770 6AE8040C */  jal        iosMsgRecv
    /* 3D774 0013D774 01000624 */   addiu     $6, $0, 0x1
    /* 3D778 0013D778 C098838F */  lw         $3, %gp_rel(D_0062A4B0)($28)
    /* 3D77C 0013D77C 181DA426 */  addiu      $4, $21, %lo(D_00551D18)
    /* 3D780 0013D780 0000A28F */  lw         $2, 0x0($29)
    /* 3D784 0013D784 FFFF6324 */  addiu      $3, $3, -0x1
    /* 3D788 0013D788 3000508C */  lw         $16, 0x30($2)
    /* 3D78C 0013D78C 2D286000 */  daddu      $5, $3, $0
    /* 3D790 0013D790 F290060C */  jal        debug_assertMessage
    /* 3D794 0013D794 C09883AF */   sw        $3, %gp_rel(D_0062A4B0)($28)
    /* 3D798 0013D798 80881000 */  sll        $17, $16, 2
    /* 3D79C 0013D79C DC00040C */  jal        func_00100370
    /* 3D7A0 0013D7A0 2D200002 */   daddu     $4, $16, $0
    /* 3D7A4 0013D7A4 CC00040C */  jal        func_00100330
    /* 3D7A8 0013D7A8 2D200002 */   daddu     $4, $16, $0
    /* 3D7AC 0013D7AC 0000A38F */  lw         $3, 0x0($29)
    /* 3D7B0 0013D7B0 3C00628C */  lw         $2, 0x3C($3)
    /* 3D7B4 0013D7B4 01004230 */  andi       $2, $2, 0x1
    /* 3D7B8 0013D7B8 06005414 */  bne        $2, $20, .L0013D7D4
    /* 3D7BC 0013D7BC 21203202 */   addu      $4, $17, $18
    /* 3D7C0 0013D7C0 0000828C */  lw         $2, 0x0($4)
    /* 3D7C4 0013D7C4 3CE4040C */  jal        iosMallocCheckLeak2
    /* 3D7C8 0013D7C8 0800448C */   lw        $4, 0x8($2)
    /* 3D7CC 0013D7CC 02000010 */  b          .L0013D7D8
    /* 3D7D0 0013D7D0 0000A38F */   lw        $3, 0x0($29)
.align 2
  .L0013D7D4:
    /* 3D7D4 0013D7D4 80881000 */  sll        $17, $16, 2
.align 2
  .L0013D7D8:
    /* 3D7D8 0013D7D8 4800628C */  lw         $2, 0x48($3)
    /* 3D7DC 0013D7DC 07004010 */  beqz       $2, .L0013D7FC
    /* 3D7E0 0013D7E0 21103202 */   addu      $2, $17, $18
    /* 3D7E4 0013D7E4 78E7040C */  jal        send_signal_message
    /* 3D7E8 0013D7E8 4C00648C */   lw        $4, 0x4C($3)
    /* 3D7EC 0013D7EC 0000A28F */  lw         $2, 0x0($29)
    /* 3D7F0 0013D7F0 3CE4040C */  jal        iosMallocCheckLeak2
    /* 3D7F4 0013D7F4 4C00448C */   lw        $4, 0x4C($2)
    /* 3D7F8 0013D7F8 21103202 */  addu       $2, $17, $18
.align 2
  .L0013D7FC:
    /* 3D7FC 0013D7FC DAFF0010 */  b          .L0013D768
    /* 3D800 0013D800 000040AC */   sw        $0, 0x0($2)
endlabel func_0013D718
    /* 3D804 0013D804 00000000 */  nop
```

---

## Attempt at 2026-07-01

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=8). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/ios/thread.c`

**Seed:** `tough_nuts/func_0013D718/func_0013D718.1.c`

Disassembly:

```
.align 3
nonmatching func_0013D718, 0xEC

glabel func_0013D718
    /* 3D718 0013D718 80FFBD27 */  addiu      $29, $29, -0x80
    /* 3D71C 0013D71C 5500043C */  lui        $4, %hi(D_00551CF8)
    /* 3D720 0013D720 6000B5FF */  sd         $21, 0x60($29)
    /* 3D724 0013D724 F81C8424 */  addiu      $4, $4, %lo(D_00551CF8)
    /* 3D728 0013D728 5000B4FF */  sd         $20, 0x50($29)
    /* 3D72C 0013D72C 4000B3FF */  sd         $19, 0x40($29)
    /* 3D730 0013D730 5500153C */  lui        $21, %hi(D_00551D18)
    /* 3D734 0013D734 3000B2FF */  sd         $18, 0x30($29)
    /* 3D738 0013D738 6A00133C */  lui        $19, %hi(D_006A0EB0)
    /* 3D73C 0013D73C 7000BFFF */  sd         $31, 0x70($29)
    /* 3D740 0013D740 01001424 */  addiu      $20, $0, 0x1
    /* 3D744 0013D744 2000B1FF */  sd         $17, 0x20($29)
    /* 3D748 0013D748 F290060C */  jal        debug_assertMessage
    /* 3D74C 0013D74C 1000B0FF */   sd        $16, 0x10($29)
    /* 3D750 0013D750 B00E6426 */  addiu      $4, $19, %lo(D_006A0EB0)
    /* 3D754 0013D754 B0B38527 */  addiu      $5, $28, %gp_rel(D_0062BFA0)
    /* 3D758 0013D758 4EE7040C */  jal        iosMsgQueueDestroy
    /* 3D75C 0013D75C 02000624 */   addiu     $6, $0, 0x2
    /* 3D760 0013D760 6A00023C */  lui        $2, %hi(D_006A0AB0)
    /* 3D764 0013D764 B00A5224 */  addiu      $18, $2, %lo(D_006A0AB0)
.align 2
  .L0013D768:
    /* 3D768 0013D768 B00E6426 */  addiu      $4, $19, %lo(D_006A0EB0)
    /* 3D76C 0013D76C 2D28A003 */  daddu      $5, $29, $0
    /* 3D770 0013D770 6AE8040C */  jal        iosMsgRecv
    /* 3D774 0013D774 01000624 */   addiu     $6, $0, 0x1
    /* 3D778 0013D778 C098838F */  lw         $3, %gp_rel(D_0062A4B0)($28)
    /* 3D77C 0013D77C 181DA426 */  addiu      $4, $21, %lo(D_00551D18)
    /* 3D780 0013D780 0000A28F */  lw         $2, 0x0($29)
    /* 3D784 0013D784 FFFF6324 */  addiu      $3, $3, -0x1
    /* 3D788 0013D788 3000508C */  lw         $16, 0x30($2)
    /* 3D78C 0013D78C 2D286000 */  daddu      $5, $3, $0
    /* 3D790 0013D790 F290060C */  jal        debug_assertMessage
    /* 3D794 0013D794 C09883AF */   sw        $3, %gp_rel(D_0062A4B0)($28)
    /* 3D798 0013D798 80881000 */  sll        $17, $16, 2
    /* 3D79C 0013D79C DC00040C */  jal        func_00100370
    /* 3D7A0 0013D7A0 2D200002 */   daddu     $4, $16, $0
    /* 3D7A4 0013D7A4 CC00040C */  jal        func_00100330
    /* 3D7A8 0013D7A8 2D200002 */   daddu     $4, $16, $0
    /* 3D7AC 0013D7AC 0000A38F */  lw         $3, 0x0($29)
    /* 3D7B0 0013D7B0 3C00628C */  lw         $2, 0x3C($3)
    /* 3D7B4 0013D7B4 01004230 */  andi       $2, $2, 0x1
    /* 3D7B8 0013D7B8 06005414 */  bne        $2, $20, .L0013D7D4
    /* 3D7BC 0013D7BC 21203202 */   addu      $4, $17, $18
    /* 3D7C0 0013D7C0 0000828C */  lw         $2, 0x0($4)
    /* 3D7C4 0013D7C4 3CE4040C */  jal        iosMallocCheckLeak2
    /* 3D7C8 0013D7C8 0800448C */   lw        $4, 0x8($2)
    /* 3D7CC 0013D7CC 02000010 */  b          .L0013D7D8
    /* 3D7D0 0013D7D0 0000A38F */   lw        $3, 0x0($29)
.align 2
  .L0013D7D4:
    /* 3D7D4 0013D7D4 80881000 */  sll        $17, $16, 2
.align 2
  .L0013D7D8:
    /* 3D7D8 0013D7D8 4800628C */  lw         $2, 0x48($3)
    /* 3D7DC 0013D7DC 07004010 */  beqz       $2, .L0013D7FC
    /* 3D7E0 0013D7E0 21103202 */   addu      $2, $17, $18
    /* 3D7E4 0013D7E4 78E7040C */  jal        send_signal_message
    /* 3D7E8 0013D7E8 4C00648C */   lw        $4, 0x4C($3)
    /* 3D7EC 0013D7EC 0000A28F */  lw         $2, 0x0($29)
    /* 3D7F0 0013D7F0 3CE4040C */  jal        iosMallocCheckLeak2
    /* 3D7F4 0013D7F4 4C00448C */   lw        $4, 0x4C($2)
    /* 3D7F8 0013D7F8 21103202 */  addu       $2, $17, $18
.align 2
  .L0013D7FC:
    /* 3D7FC 0013D7FC DAFF0010 */  b          .L0013D768
    /* 3D800 0013D800 000040AC */   sw        $0, 0x0($2)
endlabel func_0013D718
    /* 3D804 0013D804 00000000 */  nop
```
