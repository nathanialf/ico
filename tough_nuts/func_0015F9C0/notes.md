# func_0015F9C0 — parked

VRAM: 0x0015F9C0 (file_off 0x05F9C0)
Asm source: asm/aug6/nonmatchings/fumi/src/enemy_act/func_0015F9C0.s

## Attempt at 2026-07-04

**Reason parked:** user-directed park at session wrap-up; rc5 near-match (2 diffs: x-block jump-thread v0-materialization + -2-path shared-store vs direct). Full structure recovered; seed banked for trivial resume.

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/func_0015F9C0/func_0015F9C0.c`

Disassembly:

```
.align 3
nonmatching func_0015F9C0, 0x16C

glabel func_0015F9C0
    /* 5F9C0 0015F9C0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5F9C4 0015F9C4 2D388000 */  daddu      $7, $4, $0
    /* 5F9C8 0015F9C8 1000B1FF */  sd         $17, 0x10($29)
    /* 5F9CC 0015F9CC 0000B0FF */  sd         $16, 0x0($29)
    /* 5F9D0 0015F9D0 2D88C000 */  daddu      $17, $6, $0
    /* 5F9D4 0015F9D4 2000BFFF */  sd         $31, 0x20($29)
    /* 5F9D8 0015F9D8 000020AE */  sw         $0, 0x0($17)
    /* 5F9DC 0015F9DC 6401E68C */  lw         $6, 0x164($7)
    /* 5F9E0 0015F9E0 2801C28C */  lw         $2, 0x128($6)
    /* 5F9E4 0015F9E4 0B004010 */  beqz       $2, .L0015FA14
    /* 5F9E8 0015F9E8 2D80A000 */   daddu     $16, $5, $0
    /* 5F9EC 0015F9EC 5C01E48C */  lw         $4, 0x15C($7)
    /* 5F9F0 0015F9F0 90010524 */  addiu      $5, $0, 0x190
    /* 5F9F4 0015F9F4 5600033C */  lui        $3, %hi(D_0055DA10)
    /* 5F9F8 0015F9F8 9004828C */  lw         $2, 0x490($4)
    /* 5F9FC 0015F9FC 10DA6324 */  addiu      $3, $3, %lo(D_0055DA10)
    /* 5FA00 0015FA00 18104500 */  mult       $2, $2, $5
    /* 5FA04 0015FA04 21186200 */  addu       $3, $3, $2
    /* 5FA08 0015FA08 0001648C */  lw         $4, 0x100($3)
    /* 5FA0C 0015FA0C 28008010 */  beqz       $4, .L0015FAB0
    /* 5FA10 0015FA10 FFFF0224 */   addiu     $2, $0, -0x1
.align 2
  .L0015FA14:
    /* 5FA14 0015FA14 1800C2DC */  ld         $2, 0x18($6)
    /* 5FA18 0015FA18 3E130200 */  dsrl32     $2, $2, 12
    /* 5FA1C 0015FA1C 01004230 */  andi       $2, $2, 0x1
    /* 5FA20 0015FA20 22004010 */  beqz       $2, .L0015FAAC
    /* 5FA24 0015FA24 4C000424 */   addiu     $4, $0, 0x4C
    /* 5FA28 0015FA28 0800E38C */  lw         $3, 0x8($7)
    /* 5FA2C 0015FA2C 2A00023C */  lui        $2, %hi(D_002A0A90)
    /* 5FA30 0015FA30 18186400 */  mult       $3, $3, $4
    /* 5FA34 0015FA34 900A4224 */  addiu      $2, $2, %lo(D_002A0A90)
    /* 5FA38 0015FA38 21186200 */  addu       $3, $3, $2
    /* 5FA3C 0015FA3C 4800638C */  lw         $3, 0x48($3)
    /* 5FA40 0015FA40 82140300 */  srl        $2, $3, 18
    /* 5FA44 0015FA44 01004230 */  andi       $2, $2, 0x1
    /* 5FA48 0015FA48 07004014 */  bnez       $2, .L0015FA68
    /* 5FA4C 0015FA4C 2D100000 */   daddu     $2, $0, $0
    /* 5FA50 0015FA50 42150300 */  srl        $2, $3, 21
    /* 5FA54 0015FA54 01004230 */  andi       $2, $2, 0x1
    /* 5FA58 0015FA58 01004238 */  xori       $2, $2, 0x1
    /* 5FA5C 0015FA5C 02004014 */  bnez       $2, .L0015FA68
    /* 5FA60 0015FA60 2D100000 */   daddu     $2, $0, $0
    /* 5FA64 0015FA64 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0015FA68:
    /* 5FA68 0015FA68 11004010 */  beqz       $2, .L0015FAB0
    /* 5FA6C 0015FA6C FFFF0224 */   addiu     $2, $0, -0x1
    /* 5FA70 0015FA70 3000C38C */  lw         $3, 0x30($6)
    /* 5FA74 0015FA74 1700622C */  sltiu      $2, $3, 0x17
    /* 5FA78 0015FA78 07004010 */  beqz       $2, .L0015FA98
    /* 5FA7C 0015FA7C 1300622C */   sltiu     $2, $3, 0x13
    /* 5FA80 0015FA80 0A004010 */  beqz       $2, .L0015FAAC
    /* 5FA84 0015FA84 07000224 */   addiu     $2, $0, 0x7
    /* 5FA88 0015FA88 09006210 */  beq        $3, $2, .L0015FAB0
    /* 5FA8C 0015FA8C FFFF0224 */   addiu     $2, $0, -0x1
    /* 5FA90 0015FA90 0A000010 */  b          .L0015FABC
    /* 5FA94 0015FA94 4001C4DC */   ld        $4, 0x140($6)
.align 2
  .L0015FA98:
    /* 5FA98 0015FA98 7000622C */  sltiu      $2, $3, 0x70
    /* 5FA9C 0015FA9C 06004010 */  beqz       $2, .L0015FAB8
    /* 5FAA0 0015FAA0 6E00622C */   sltiu     $2, $3, 0x6E
    /* 5FAA4 0015FAA4 05004054 */  bnel       $2, $0, .L0015FABC
    /* 5FAA8 0015FAA8 4001C4DC */   ld        $4, 0x140($6)
.align 2
  .L0015FAAC:
    /* 5FAAC 0015FAAC FFFF0224 */  addiu      $2, $0, -0x1
.align 2
  .L0015FAB0:
    /* 5FAB0 0015FAB0 19000010 */  b          .L0015FB18
    /* 5FAB4 0015FAB4 000002AE */   sw        $2, 0x0($16)
.align 2
  .L0015FAB8:
    /* 5FAB8 0015FAB8 4001C4DC */  ld         $4, 0x140($6)
.align 2
  .L0015FABC:
    /* 5FABC 0015FABC 3F100400 */  dsra32     $2, $4, 0
    /* 5FAC0 0015FAC0 01004230 */  andi       $2, $2, 0x1
    /* 5FAC4 0015FAC4 09004010 */  beqz       $2, .L0015FAEC
    /* 5FAC8 0015FAC8 FEFF0324 */   addiu     $3, $0, -0x2
    /* 5FACC 0015FACC FEFF0224 */  addiu      $2, $0, -0x2
    /* 5FAD0 0015FAD0 38140200 */  dsll       $2, $2, 16
    /* 5FAD4 0015FAD4 FFFF4234 */  ori        $2, $2, 0xFFFF
    /* 5FAD8 0015FAD8 38140200 */  dsll       $2, $2, 16
    /* 5FADC 0015FADC FFFF4234 */  ori        $2, $2, 0xFFFF
    /* 5FAE0 0015FAE0 24108200 */  and        $2, $4, $2
    /* 5FAE4 0015FAE4 0B000010 */  b          .L0015FB14
    /* 5FAE8 0015FAE8 4001C2FC */   sd        $2, 0x140($6)
.align 2
  .L0015FAEC:
    /* 5FAEC 0015FAEC 0C3A060C */  jal        func_0018E830
    /* 5FAF0 0015FAF0 2D20E000 */   daddu     $4, $7, $0
    /* 5FAF4 0015FAF4 2D184000 */  daddu      $3, $2, $0
    /* 5FAF8 0015FAF8 04006054 */  bnel       $3, $0, .L0015FB0C
    /* 5FAFC 0015FAFC 0400628C */   lw        $2, 0x4($3)
    /* 5FB00 0015FB00 000020AE */  sw         $0, 0x0($17)
    /* 5FB04 0015FB04 03000010 */  b          .L0015FB14
    /* 5FB08 0015FB08 2D180000 */   daddu     $3, $0, $0
.align 2
  .L0015FB0C:
    /* 5FB0C 0015FB0C 00006394 */  lhu        $3, 0x0($3)
    /* 5FB10 0015FB10 000022AE */  sw         $2, 0x0($17)
.align 2
  .L0015FB14:
    /* 5FB14 0015FB14 000003AE */  sw         $3, 0x0($16)
.align 2
  .L0015FB18:
    /* 5FB18 0015FB18 2000BFDF */  ld         $31, 0x20($29)
    /* 5FB1C 0015FB1C 1000B1DF */  ld         $17, 0x10($29)
    /* 5FB20 0015FB20 0000B0DF */  ld         $16, 0x0($29)
    /* 5FB24 0015FB24 0800E003 */  jr         $31
    /* 5FB28 0015FB28 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0015F9C0
    /* 5FB2C 0015FB2C 00000000 */  nop
```

---

## Attempt at 2026-07-07

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/enemy_act.c`

**Seed:** `tough_nuts/func_0015F9C0/func_0015F9C0.1.c`

Disassembly:

```
.align 3
nonmatching func_0015F9C0, 0x16C

glabel func_0015F9C0
    /* 5F9C0 0015F9C0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 5F9C4 0015F9C4 2D388000 */  daddu      $7, $4, $0
    /* 5F9C8 0015F9C8 1000B1FF */  sd         $17, 0x10($29)
    /* 5F9CC 0015F9CC 0000B0FF */  sd         $16, 0x0($29)
    /* 5F9D0 0015F9D0 2D88C000 */  daddu      $17, $6, $0
    /* 5F9D4 0015F9D4 2000BFFF */  sd         $31, 0x20($29)
    /* 5F9D8 0015F9D8 000020AE */  sw         $0, 0x0($17)
    /* 5F9DC 0015F9DC 6401E68C */  lw         $6, 0x164($7)
    /* 5F9E0 0015F9E0 2801C28C */  lw         $2, 0x128($6)
    /* 5F9E4 0015F9E4 0B004010 */  beqz       $2, .L0015FA14
    /* 5F9E8 0015F9E8 2D80A000 */   daddu     $16, $5, $0
    /* 5F9EC 0015F9EC 5C01E48C */  lw         $4, 0x15C($7)
    /* 5F9F0 0015F9F0 90010524 */  addiu      $5, $0, 0x190
    /* 5F9F4 0015F9F4 5600033C */  lui        $3, %hi(D_0055DA10)
    /* 5F9F8 0015F9F8 9004828C */  lw         $2, 0x490($4)
    /* 5F9FC 0015F9FC 10DA6324 */  addiu      $3, $3, %lo(D_0055DA10)
    /* 5FA00 0015FA00 18104500 */  mult       $2, $2, $5
    /* 5FA04 0015FA04 21186200 */  addu       $3, $3, $2
    /* 5FA08 0015FA08 0001648C */  lw         $4, 0x100($3)
    /* 5FA0C 0015FA0C 28008010 */  beqz       $4, .L0015FAB0
    /* 5FA10 0015FA10 FFFF0224 */   addiu     $2, $0, -0x1
.align 2
  .L0015FA14:
    /* 5FA14 0015FA14 1800C2DC */  ld         $2, 0x18($6)
    /* 5FA18 0015FA18 3E130200 */  dsrl32     $2, $2, 12
    /* 5FA1C 0015FA1C 01004230 */  andi       $2, $2, 0x1
    /* 5FA20 0015FA20 22004010 */  beqz       $2, .L0015FAAC
    /* 5FA24 0015FA24 4C000424 */   addiu     $4, $0, 0x4C
    /* 5FA28 0015FA28 0800E38C */  lw         $3, 0x8($7)
    /* 5FA2C 0015FA2C 2A00023C */  lui        $2, %hi(D_002A0A90)
    /* 5FA30 0015FA30 18186400 */  mult       $3, $3, $4
    /* 5FA34 0015FA34 900A4224 */  addiu      $2, $2, %lo(D_002A0A90)
    /* 5FA38 0015FA38 21186200 */  addu       $3, $3, $2
    /* 5FA3C 0015FA3C 4800638C */  lw         $3, 0x48($3)
    /* 5FA40 0015FA40 82140300 */  srl        $2, $3, 18
    /* 5FA44 0015FA44 01004230 */  andi       $2, $2, 0x1
    /* 5FA48 0015FA48 07004014 */  bnez       $2, .L0015FA68
    /* 5FA4C 0015FA4C 2D100000 */   daddu     $2, $0, $0
    /* 5FA50 0015FA50 42150300 */  srl        $2, $3, 21
    /* 5FA54 0015FA54 01004230 */  andi       $2, $2, 0x1
    /* 5FA58 0015FA58 01004238 */  xori       $2, $2, 0x1
    /* 5FA5C 0015FA5C 02004014 */  bnez       $2, .L0015FA68
    /* 5FA60 0015FA60 2D100000 */   daddu     $2, $0, $0
    /* 5FA64 0015FA64 01000224 */  addiu      $2, $0, 0x1
.align 2
  .L0015FA68:
    /* 5FA68 0015FA68 11004010 */  beqz       $2, .L0015FAB0
    /* 5FA6C 0015FA6C FFFF0224 */   addiu     $2, $0, -0x1
    /* 5FA70 0015FA70 3000C38C */  lw         $3, 0x30($6)
    /* 5FA74 0015FA74 1700622C */  sltiu      $2, $3, 0x17
    /* 5FA78 0015FA78 07004010 */  beqz       $2, .L0015FA98
    /* 5FA7C 0015FA7C 1300622C */   sltiu     $2, $3, 0x13
    /* 5FA80 0015FA80 0A004010 */  beqz       $2, .L0015FAAC
    /* 5FA84 0015FA84 07000224 */   addiu     $2, $0, 0x7
    /* 5FA88 0015FA88 09006210 */  beq        $3, $2, .L0015FAB0
    /* 5FA8C 0015FA8C FFFF0224 */   addiu     $2, $0, -0x1
    /* 5FA90 0015FA90 0A000010 */  b          .L0015FABC
    /* 5FA94 0015FA94 4001C4DC */   ld        $4, 0x140($6)
.align 2
  .L0015FA98:
    /* 5FA98 0015FA98 7000622C */  sltiu      $2, $3, 0x70
    /* 5FA9C 0015FA9C 06004010 */  beqz       $2, .L0015FAB8
    /* 5FAA0 0015FAA0 6E00622C */   sltiu     $2, $3, 0x6E
    /* 5FAA4 0015FAA4 05004054 */  bnel       $2, $0, .L0015FABC
    /* 5FAA8 0015FAA8 4001C4DC */   ld        $4, 0x140($6)
.align 2
  .L0015FAAC:
    /* 5FAAC 0015FAAC FFFF0224 */  addiu      $2, $0, -0x1
.align 2
  .L0015FAB0:
    /* 5FAB0 0015FAB0 19000010 */  b          .L0015FB18
    /* 5FAB4 0015FAB4 000002AE */   sw        $2, 0x0($16)
.align 2
  .L0015FAB8:
    /* 5FAB8 0015FAB8 4001C4DC */  ld         $4, 0x140($6)
.align 2
  .L0015FABC:
    /* 5FABC 0015FABC 3F100400 */  dsra32     $2, $4, 0
    /* 5FAC0 0015FAC0 01004230 */  andi       $2, $2, 0x1
    /* 5FAC4 0015FAC4 09004010 */  beqz       $2, .L0015FAEC
    /* 5FAC8 0015FAC8 FEFF0324 */   addiu     $3, $0, -0x2
    /* 5FACC 0015FACC FEFF0224 */  addiu      $2, $0, -0x2
    /* 5FAD0 0015FAD0 38140200 */  dsll       $2, $2, 16
    /* 5FAD4 0015FAD4 FFFF4234 */  ori        $2, $2, 0xFFFF
    /* 5FAD8 0015FAD8 38140200 */  dsll       $2, $2, 16
    /* 5FADC 0015FADC FFFF4234 */  ori        $2, $2, 0xFFFF
    /* 5FAE0 0015FAE0 24108200 */  and        $2, $4, $2
    /* 5FAE4 0015FAE4 0B000010 */  b          .L0015FB14
    /* 5FAE8 0015FAE8 4001C2FC */   sd        $2, 0x140($6)
.align 2
  .L0015FAEC:
    /* 5FAEC 0015FAEC 0C3A060C */  jal        func_0018E830
    /* 5FAF0 0015FAF0 2D20E000 */   daddu     $4, $7, $0
    /* 5FAF4 0015FAF4 2D184000 */  daddu      $3, $2, $0
    /* 5FAF8 0015FAF8 04006054 */  bnel       $3, $0, .L0015FB0C
    /* 5FAFC 0015FAFC 0400628C */   lw        $2, 0x4($3)
    /* 5FB00 0015FB00 000020AE */  sw         $0, 0x0($17)
    /* 5FB04 0015FB04 03000010 */  b          .L0015FB14
    /* 5FB08 0015FB08 2D180000 */   daddu     $3, $0, $0
.align 2
  .L0015FB0C:
    /* 5FB0C 0015FB0C 00006394 */  lhu        $3, 0x0($3)
    /* 5FB10 0015FB10 000022AE */  sw         $2, 0x0($17)
.align 2
  .L0015FB14:
    /* 5FB14 0015FB14 000003AE */  sw         $3, 0x0($16)
.align 2
  .L0015FB18:
    /* 5FB18 0015FB18 2000BFDF */  ld         $31, 0x20($29)
    /* 5FB1C 0015FB1C 1000B1DF */  ld         $17, 0x10($29)
    /* 5FB20 0015FB20 0000B0DF */  ld         $16, 0x0($29)
    /* 5FB24 0015FB24 0800E003 */  jr         $31
    /* 5FB28 0015FB28 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_0015F9C0
    /* 5FB2C 0015FB2C 00000000 */  nop
```
