# GetWgAll — parked

VRAM: 0x00176FC0 (file_off 0x076FC0)
Asm source: asm/aug6/nonmatchings/fumi/src/way_util/GetWgAll.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=10). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/src/way_util.c`

**Seed:** `tough_nuts/GetWgAll/GetWgAll.c`

Disassembly:

```
.align 3
nonmatching GetWgAll, 0x118

glabel GetWgAll
    /* 76FC0 00176FC0 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 76FC4 00176FC4 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 76FC8 00176FC8 0000B0FF */  sd         $16, 0x0($29)
    /* 76FCC 00176FCC 1C000524 */  addiu      $5, $0, 0x1C
    /* 76FD0 00176FD0 5500103C */  lui        $16, %hi(D_00554080)
    /* 76FD4 00176FD4 1000B1FF */  sd         $17, 0x10($29)
    /* 76FD8 00176FD8 80401026 */  addiu      $16, $16, %lo(D_00554080)
    /* 76FDC 00176FDC 2000BFFF */  sd         $31, 0x20($29)
    /* 76FE0 00176FE0 2D300002 */  daddu      $6, $16, $0
    /* 76FE4 00176FE4 CEE2040C */  jal        iosFree
    /* 76FE8 00176FE8 59030724 */   addiu     $7, $0, 0x359
    /* 76FEC 00176FEC 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 76FF0 00176FF0 2D884000 */  daddu      $17, $2, $0
    /* 76FF4 00176FF4 41000524 */  addiu      $5, $0, 0x41
    /* 76FF8 00176FF8 2D300002 */  daddu      $6, $16, $0
    /* 76FFC 00176FFC CEE2040C */  jal        iosFree
    /* 77000 00177000 5B030724 */   addiu     $7, $0, 0x35B
    /* 77004 00177004 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 77008 00177008 00400524 */  addiu      $5, $0, 0x4000
    /* 7700C 0017700C 000022AE */  sw         $2, 0x0($17)
    /* 77010 00177010 2D300002 */  daddu      $6, $16, $0
    /* 77014 00177014 CEE2040C */  jal        iosFree
    /* 77018 00177018 5C030724 */   addiu     $7, $0, 0x35C
    /* 7701C 0017701C 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 77020 00177020 04010524 */  addiu      $5, $0, 0x104
    /* 77024 00177024 040022AE */  sw         $2, 0x4($17)
    /* 77028 00177028 2D300002 */  daddu      $6, $16, $0
    /* 7702C 0017702C CEE2040C */  jal        iosFree
    /* 77030 00177030 5D030724 */   addiu     $7, $0, 0x35D
    /* 77034 00177034 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 77038 00177038 04010524 */  addiu      $5, $0, 0x104
    /* 7703C 0017703C 0C0022AE */  sw         $2, 0xC($17)
    /* 77040 00177040 2D300002 */  daddu      $6, $16, $0
    /* 77044 00177044 CEE2040C */  jal        iosFree
    /* 77048 00177048 5E030724 */   addiu     $7, $0, 0x35E
    /* 7704C 0017704C 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 77050 00177050 04010524 */  addiu      $5, $0, 0x104
    /* 77054 00177054 100022AE */  sw         $2, 0x10($17)
    /* 77058 00177058 2D300002 */  daddu      $6, $16, $0
    /* 7705C 0017705C CEE2040C */  jal        iosFree
    /* 77060 00177060 5F030724 */   addiu     $7, $0, 0x35F
    /* 77064 00177064 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 77068 00177068 04010524 */  addiu      $5, $0, 0x104
    /* 7706C 0017706C 140022AE */  sw         $2, 0x14($17)
    /* 77070 00177070 2D300002 */  daddu      $6, $16, $0
    /* 77074 00177074 CEE2040C */  jal        iosFree
    /* 77078 00177078 60030724 */   addiu     $7, $0, 0x360
    /* 7707C 0017707C 2097848F */  lw         $4, %gp_rel(D_0062A310)($28)
    /* 77080 00177080 2D300002 */  daddu      $6, $16, $0
    /* 77084 00177084 180022AE */  sw         $2, 0x18($17)
    /* 77088 00177088 00010524 */  addiu      $5, $0, 0x100
    /* 7708C 0017708C CEE2040C */  jal        iosFree
    /* 77090 00177090 62030724 */   addiu     $7, $0, 0x362
    /* 77094 00177094 080022AE */  sw         $2, 0x8($17)
    /* 77098 00177098 2D300000 */  daddu      $6, $0, $0
    /* 7709C 0017709C 2D284000 */  daddu      $5, $2, $0
.align 2
  .L001770A0:
    /* 770A0 001770A0 0400228E */  lw         $2, 0x4($17)
    /* 770A4 001770A4 001A0600 */  sll        $3, $6, 8
    /* 770A8 001770A8 0100C624 */  addiu      $6, $6, 0x1
    /* 770AC 001770AC 21104300 */  addu       $2, $2, $3
    /* 770B0 001770B0 4000C428 */  slti       $4, $6, 0x40
    /* 770B4 001770B4 0000A2AC */  sw         $2, 0x0($5)
    /* 770B8 001770B8 F9FF8014 */  bnez       $4, .L001770A0
    /* 770BC 001770BC 0400A524 */   addiu     $5, $5, 0x4
    /* 770C0 001770C0 2D102002 */  daddu      $2, $17, $0
    /* 770C4 001770C4 2000BFDF */  ld         $31, 0x20($29)
    /* 770C8 001770C8 1000B1DF */  ld         $17, 0x10($29)
    /* 770CC 001770CC 0000B0DF */  ld         $16, 0x0($29)
    /* 770D0 001770D0 0800E003 */  jr         $31
    /* 770D4 001770D4 3000BD27 */   addiu     $29, $29, 0x30
endlabel GetWgAll
```
