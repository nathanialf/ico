# dispPool — parked

VRAM: 0x0010B0C0 (file_off 0x00B0C0)
Asm source: asm/aug6/nonmatchings/sugipon/src/pool/dispPool.s

## Attempt at 2026-07-03

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=7). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `sugipon/src/pool.c`

**Seed:** `tough_nuts/dispPool/dispPool.c`

Disassembly:

```
.align 3
nonmatching dispPool, 0x178

glabel dispPool
    /* B0C0 0010B0C0 C0FFBD27 */  addiu      $29, $29, -0x40
    /* B0C4 0010B0C4 3000BFFF */  sd         $31, 0x30($29)
    /* B0C8 0010B0C8 8CBF040C */  jal        func_0012FE30
    /* B0CC 0010B0CC 00000000 */   nop
    /* B0D0 0010B0D0 2D200000 */  daddu      $4, $0, $0
    /* B0D4 0010B0D4 6AAB040C */  jal        tex_transVramClutTex
    /* B0D8 0010B0D8 00040524 */   addiu     $5, $0, 0x400
    /* B0DC 0010B0DC 6C93848F */  lw         $4, %gp_rel(D_00629F5C)($28)
    /* B0E0 0010B0E0 FFFF0324 */  addiu      $3, $0, -0x1
    /* B0E4 0010B0E4 06000624 */  addiu      $6, $0, 0x6
    /* B0E8 0010B0E8 38340600 */  dsll       $6, $6, 16
    /* B0EC 0010B0EC 0064C634 */  ori        $6, $6, 0x6400
    /* B0F0 0010B0F0 38340600 */  dsll       $6, $6, 16
    /* B0F4 0010B0F4 0008C634 */  ori        $6, $6, 0x800
    /* B0F8 0010B0F8 709282AF */  sw         $2, %gp_rel(D_00629E60)($28)
    /* B0FC 0010B0FC 2A186400 */  slt        $3, $3, $4
    /* B100 0010B100 3F008524 */  addiu      $5, $4, 0x3F
    /* B104 0010B104 0B288300 */  movn       $5, $4, $3
    /* B108 0010B108 83290500 */  sra        $5, $5, 6
    /* B10C 0010B10C 06000424 */  addiu      $4, $0, 0x6
    /* B110 0010B110 B82B0500 */  dsll       $5, $5, 14
    /* B114 0010B114 2E47040C */  jal        gif_SpriteOrg
    /* B118 0010B118 2528A600 */   or        $5, $5, $6
    /* B11C 0010B11C 7092848F */  lw         $4, %gp_rel(D_00629E60)($28)
    /* B120 0010B120 2D480000 */  daddu      $9, $0, $0
    /* B124 0010B124 2D280000 */  daddu      $5, $0, $0
    /* B128 0010B128 00010624 */  addiu      $6, $0, 0x100
    /* B12C 0010B12C 00010724 */  addiu      $7, $0, 0x100
    /* B130 0010B130 F643040C */  jal        gif_MakeSprite
    /* B134 0010B134 2D400000 */   daddu     $8, $0, $0
    /* B138 0010B138 3A49040C */  jal        gsb_Reduction
    /* B13C 0010B13C 2D200000 */   daddu     $4, $0, $0
    /* B140 0010B140 4A49040C */  jal        gsb_KeepFrameBuffer
    /* B144 0010B144 2D200000 */   daddu     $4, $0, $0
    /* B148 0010B148 2D200000 */  daddu      $4, $0, $0
    /* B14C 0010B14C 04000524 */  addiu      $5, $0, 0x4
    /* B150 0010B150 D248040C */  jal        gsb_SetFrame
    /* B154 0010B154 2D300000 */   daddu     $6, $0, $0
    /* B158 0010B158 47000424 */  addiu      $4, $0, 0x47
    /* B15C 0010B15C 2E47040C */  jal        gif_SpriteOrg
    /* B160 0010B160 0300053C */   lui       $5, (0x30000 >> 16)
    /* B164 0010B164 14000424 */  addiu      $4, $0, 0x14
    /* B168 0010B168 2E47040C */  jal        gif_SpriteOrg
    /* B16C 0010B16C 60000524 */   addiu     $5, $0, 0x60
    /* B170 0010B170 6C93828F */  lw         $2, %gp_rel(D_00629F5C)($28)
    /* B174 0010B174 5500043C */  lui        $4, %hi(D_0054E100)
    /* B178 0010B178 7093838F */  lw         $3, %gp_rel(D_00629F60)($28)
    /* B17C 0010B17C 08000624 */  addiu      $6, $0, 0x8
    /* B180 0010B180 00E18924 */  addiu      $9, $4, %lo(D_0054E100)
    /* B184 0010B184 07002569 */  ldl        $5, 0x7($9)
    /* B188 0010B188 0000256D */  ldr        $5, 0x0($9)
    /* B18C 0010B18C 0F002769 */  ldl        $7, 0xF($9)
    /* B190 0010B190 0800276D */  ldr        $7, 0x8($9)
    /* B194 0010B194 0700A5B3 */  sdl        $5, 0x7($29)
    /* B198 0010B198 0000A5B7 */  sdr        $5, 0x0($29)
    /* B19C 0010B19C 0F00A7B3 */  sdl        $7, 0xF($29)
    /* B1A0 0010B1A0 0800A7B7 */  sdr        $7, 0x8($29)
    /* B1A4 0010B1A4 00110200 */  sll        $2, $2, 4
    /* B1A8 0010B1A8 00190300 */  sll        $3, $3, 4
    /* B1AC 0010B1AC 2400A6AF */  sw         $6, 0x24($29)
    /* B1B0 0010B1B0 2000A6AF */  sw         $6, 0x20($29)
    /* B1B4 0010B1B4 6300093C */  lui        $9, %hi(D_0062BCE8)
    /* B1B8 0010B1B8 2800A2AF */  sw         $2, 0x28($29)
    /* B1BC 0010B1BC 2D20A003 */  daddu      $4, $29, $0
    /* B1C0 0010B1C0 2C00A3AF */  sw         $3, 0x2C($29)
    /* B1C4 0010B1C4 2D280000 */  daddu      $5, $0, $0
    /* B1C8 0010B1C8 2700AA6B */  ldl        $10, 0x27($29)
    /* B1CC 0010B1CC 2000AA6F */  ldr        $10, 0x20($29)
    /* B1D0 0010B1D0 2F00AB6B */  ldl        $11, 0x2F($29)
    /* B1D4 0010B1D4 2800AB6F */  ldr        $11, 0x28($29)
    /* B1D8 0010B1D8 1700AAB3 */  sdl        $10, 0x17($29)
    /* B1DC 0010B1DC 1000AAB7 */  sdr        $10, 0x10($29)
    /* B1E0 0010B1E0 1F00ABB3 */  sdl        $11, 0x1F($29)
    /* B1E4 0010B1E4 1800ABB7 */  sdr        $11, 0x18($29)
    /* B1E8 0010B1E8 1000A627 */  addiu      $6, $29, 0x10
    /* B1EC 0010B1EC 2000A727 */  addiu      $7, $29, 0x20
    /* B1F0 0010B1F0 E8BC2325 */  addiu      $3, $9, %lo(D_0062BCE8)
    /* B1F4 0010B1F4 03006A88 */  lwl        $10, 0x3($3)
    /* B1F8 0010B1F8 00006A98 */  lwr        $10, 0x0($3)
    /* B1FC 0010B1FC 2300AAAB */  swl        $10, 0x23($29)
    /* B200 0010B200 2000AABB */  swr        $10, 0x20($29)
    /* B204 0010B204 A443040C */  jal        gif_MakeLine2DOffset
    /* B208 0010B208 2D400000 */   daddu     $8, $0, $0
    /* B20C 0010B20C 4A49040C */  jal        gsb_KeepFrameBuffer
    /* B210 0010B210 01000424 */   addiu     $4, $0, 0x1
    /* B214 0010B214 3A49040C */  jal        gsb_Reduction
    /* B218 0010B218 01000424 */   addiu     $4, $0, 0x1
    /* B21C 0010B21C 0500053C */  lui        $5, (0x5000D >> 16)
    /* B220 0010B220 0D00A534 */  ori        $5, $5, (0x5000D & 0xFFFF)
    /* B224 0010B224 2E47040C */  jal        gif_SpriteOrg
    /* B228 0010B228 47000424 */   addiu     $4, $0, 0x47
    /* B22C 0010B22C 3000BFDF */  ld         $31, 0x30($29)
    /* B230 0010B230 0800E003 */  jr         $31
    /* B234 0010B234 4000BD27 */   addiu     $29, $29, 0x40
endlabel dispPool
```
