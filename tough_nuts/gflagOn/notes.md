# gflagOn — parked

VRAM: 0x00178F18 (file_off 0x078F18)
Asm source: asm/aug6/nonmatchings/script/src/gflag/gflagOn.s

## Attempt at 2026-07-05

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=6). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `script/src/gflag.c`

**Seed:** `tough_nuts/gflagOn/gflagOn.c`

Disassembly:

```
.align 3
nonmatching gflagOn, 0x60

glabel gflagOn
    /* 78F18 00178F18 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 78F1C 00178F1C 1000B1FF */  sd         $17, 0x10($29)
    /* 78F20 00178F20 0000B0FF */  sd         $16, 0x0($29)
    /* 78F24 00178F24 2D888000 */  daddu      $17, $4, $0
    /* 78F28 00178F28 2D80A000 */  daddu      $16, $5, $0
    /* 78F2C 00178F2C 2000BFFF */  sd         $31, 0x20($29)
    /* 78F30 00178F30 A6FF080C */  jal        sceVu0Normalize
    /* 78F34 00178F34 2D200002 */   daddu     $4, $16, $0
    /* 78F38 00178F38 5C01258E */  lw         $5, 0x15C($17)
    /* 78F3C 00178F3C 90010624 */  addiu      $6, $0, 0x190
    /* 78F40 00178F40 5600033C */  lui        $3, %hi(D_0055DA10)
    /* 78F44 00178F44 2D202002 */  daddu      $4, $17, $0
    /* 78F48 00178F48 9004A28C */  lw         $2, 0x490($5)
    /* 78F4C 00178F4C 10DA6324 */  addiu      $3, $3, %lo(D_0055DA10)
    /* 78F50 00178F50 2D280002 */  daddu      $5, $16, $0
    /* 78F54 00178F54 2000BFDF */  ld         $31, 0x20($29)
    /* 78F58 00178F58 18104600 */  mult       $2, $2, $6
    /* 78F5C 00178F5C 1000B1DF */  ld         $17, 0x10($29)
    /* 78F60 00178F60 0000B0DF */  ld         $16, 0x0($29)
    /* 78F64 00178F64 21186200 */  addu       $3, $3, $2
    /* 78F68 00178F68 38016CC4 */  lwc1       $f12, 0x138($3)
    /* 78F6C 00178F6C 20638046 */  cvt.s.w    $f12, $f12
    /* 78F70 00178F70 AC660508 */  j          actCommonStoneDead
    /* 78F74 00178F74 3000BD27 */   addiu     $29, $29, 0x30
endlabel gflagOn
```
