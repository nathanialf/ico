# _clearOnce — parked

VRAM: 0x0024E7C8 (file_off 0x14E7C8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/_clearOnce.s

## Attempt at 2026-06-13

**Reason parked:** rc5 stall=30/30. PURE sched2 tie: all regs correct, only ld-ra hoisted into lw-v0 load-delay (ROM) vs gcc filling slot with sw-zero. Exhausted: store-order sweep(120, floor5), temps+order(720, floor7), do-while placements, ptr-deref C758/CD78, scalar/struct/char*/volatile/union, inline-helper. Data model: D_0054CD78=array-of-struct stride0x140; [0].f0=base,[0].f4=base+0x1800,[1].f0=base+0x1B00,[1].f4=base+0x3300,[2].f0=0; base=D_0054C758[0]; calls _ipuSetMPEG1(1) first. Permuter-class (func_001FB768 precedent).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_clearOnce/_clearOnce.c`

Disassembly:

```
.align 3
nonmatching _clearOnce, 0x4C

glabel _clearOnce
    /* 14E7C8 0024E7C8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E7CC 0024E7CC 0000BFFF */  sd         $31, 0x0($29)
    /* 14E7D0 0024E7D0 2244090C */  jal        _ipuSetMPEG1
    /* 14E7D4 0024E7D4 01000424 */   addiu     $4, $0, 0x1
    /* 14E7D8 0024E7D8 5500043C */  lui        $4, %hi(D_0054C758)
    /* 14E7DC 0024E7DC 5500063C */  lui        $6, %hi(D_0054CD78)
    /* 14E7E0 0024E7E0 58C7828C */  lw         $2, %lo(D_0054C758)($4)
    /* 14E7E4 0024E7E4 78CDC324 */  addiu      $3, $6, %lo(D_0054CD78)
    /* 14E7E8 0024E7E8 0000BFDF */  ld         $31, 0x0($29)
    /* 14E7EC 0024E7EC 00334724 */  addiu      $7, $2, 0x3300
    /* 14E7F0 0024E7F0 00184424 */  addiu      $4, $2, 0x1800
    /* 14E7F4 0024E7F4 001B4524 */  addiu      $5, $2, 0x1B00
    /* 14E7F8 0024E7F8 78CDC2AC */  sw         $2, %lo(D_0054CD78)($6)
    /* 14E7FC 0024E7FC 800260AC */  sw         $0, 0x280($3)
    /* 14E800 0024E800 040064AC */  sw         $4, 0x4($3)
    /* 14E804 0024E804 400165AC */  sw         $5, 0x140($3)
    /* 14E808 0024E808 440167AC */  sw         $7, 0x144($3)
    /* 14E80C 0024E80C 0800E003 */  jr         $31
    /* 14E810 0024E810 1000BD27 */   addiu     $29, $29, 0x10
endlabel _clearOnce
    /* 14E814 0024E814 00000000 */  nop
```

## Permuter run (2026-06-13) — resolution (b) permuter-exhausted
- Seed replaced with CLEAN MINIMAL standalone (the whole-TU seed broke the
  permuter: a sibling's raw `__asm__` block (func_002484AC) survived
  strip_other_fns and corrupted base.c → "no permutation matched" with zero
  real iterations). Re-ran on the minimal seed: ~300 iterations, 54 outputs.
- Harvest by TRUE real_count (score is anti-correlated): best output score=200
  → rc6; score=130 → rc12. NOTHING beat the parked best (rc5). Permuter
  mutations were semantically invalid (it only chases the asm score), so no
  byte-match (no output-0-*).
- Residual is a pure sched2 instruction-priority tie: all registers match;
  ROM hoists the epilogue `ld ra` into the `lw v0` (base) load-delay slot,
  gcc fills that slot with the independent `sw zero` ([2].f0=0) and defers
  `ld ra` to the tail. Order/temp/do-while/ptr/struct/volatile all floor rc5.
- RESUME idea: needs a shape that makes `sw zero` un-ready during the load
  delay (genuine dep on base) OR raises `ld ra` priority — neither found by
  hand or permuter. Re-attack with a fresh hypothesis, NOT a re-run.

---

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=2). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_clearOnce/_clearOnce.1.c`

Disassembly:

```
.align 3
nonmatching _clearOnce, 0x4C

glabel _clearOnce
    /* 14E7C8 0024E7C8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E7CC 0024E7CC 0000BFFF */  sd         $31, 0x0($29)
    /* 14E7D0 0024E7D0 2244090C */  jal        _ipuSetMPEG1
    /* 14E7D4 0024E7D4 01000424 */   addiu     $4, $0, 0x1
    /* 14E7D8 0024E7D8 5500043C */  lui        $4, %hi(D_0054C758)
    /* 14E7DC 0024E7DC 5500063C */  lui        $6, %hi(D_0054CD78)
    /* 14E7E0 0024E7E0 58C7828C */  lw         $2, %lo(D_0054C758)($4)
    /* 14E7E4 0024E7E4 78CDC324 */  addiu      $3, $6, %lo(D_0054CD78)
    /* 14E7E8 0024E7E8 0000BFDF */  ld         $31, 0x0($29)
    /* 14E7EC 0024E7EC 00334724 */  addiu      $7, $2, 0x3300
    /* 14E7F0 0024E7F0 00184424 */  addiu      $4, $2, 0x1800
    /* 14E7F4 0024E7F4 001B4524 */  addiu      $5, $2, 0x1B00
    /* 14E7F8 0024E7F8 78CDC2AC */  sw         $2, %lo(D_0054CD78)($6)
    /* 14E7FC 0024E7FC 800260AC */  sw         $0, 0x280($3)
    /* 14E800 0024E800 040064AC */  sw         $4, 0x4($3)
    /* 14E804 0024E804 400165AC */  sw         $5, 0x140($3)
    /* 14E808 0024E808 440167AC */  sw         $7, 0x144($3)
    /* 14E80C 0024E80C 0800E003 */  jr         $31
    /* 14E810 0024E810 1000BD27 */   addiu     $29, $29, 0x10
endlabel _clearOnce
    /* 14E814 0024E814 00000000 */  nop
```

---

## Attempt at 2026-06-21

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/_clearOnce/_clearOnce.2.c`

Disassembly:

```
.align 3
nonmatching _clearOnce, 0x4C

glabel _clearOnce
    /* 14E7C8 0024E7C8 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14E7CC 0024E7CC 0000BFFF */  sd         $31, 0x0($29)
    /* 14E7D0 0024E7D0 2244090C */  jal        _ipuSetMPEG1
    /* 14E7D4 0024E7D4 01000424 */   addiu     $4, $0, 0x1
    /* 14E7D8 0024E7D8 5500043C */  lui        $4, %hi(D_0054C758)
    /* 14E7DC 0024E7DC 5500063C */  lui        $6, %hi(D_0054CD78)
    /* 14E7E0 0024E7E0 58C7828C */  lw         $2, %lo(D_0054C758)($4)
    /* 14E7E4 0024E7E4 78CDC324 */  addiu      $3, $6, %lo(D_0054CD78)
    /* 14E7E8 0024E7E8 0000BFDF */  ld         $31, 0x0($29)
    /* 14E7EC 0024E7EC 00334724 */  addiu      $7, $2, 0x3300
    /* 14E7F0 0024E7F0 00184424 */  addiu      $4, $2, 0x1800
    /* 14E7F4 0024E7F4 001B4524 */  addiu      $5, $2, 0x1B00
    /* 14E7F8 0024E7F8 78CDC2AC */  sw         $2, %lo(D_0054CD78)($6)
    /* 14E7FC 0024E7FC 800260AC */  sw         $0, 0x280($3)
    /* 14E800 0024E800 040064AC */  sw         $4, 0x4($3)
    /* 14E804 0024E804 400165AC */  sw         $5, 0x140($3)
    /* 14E808 0024E808 440167AC */  sw         $7, 0x144($3)
    /* 14E80C 0024E80C 0800E003 */  jr         $31
    /* 14E810 0024E810 1000BD27 */   addiu     $29, $29, 0x10
endlabel _clearOnce
    /* 14E814 0024E814 00000000 */  nop
```
