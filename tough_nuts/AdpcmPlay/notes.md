# AdpcmPlay — parked

VRAM: 0x001F9188 (file_off 0x0F9188)
Asm source: asm/aug6/nonmatchings/fumi/sound/adpcm_init/AdpcmPlay.s

## Attempt at 2026-06-20

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=5). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `fumi/sound/adpcm_init.c`

**Seed:** `tough_nuts/AdpcmPlay/AdpcmPlay.c`

Disassembly:

```
.align 3
nonmatching AdpcmPlay, 0x114

glabel AdpcmPlay
    /* F9188 001F9188 D0FFBD27 */  addiu      $29, $29, -0x30
    /* F918C 001F918C 7100023C */  lui        $2, %hi(D_0070A970)
    /* F9190 001F9190 1000B1FF */  sd         $17, 0x10($29)
    /* F9194 001F9194 0000B0FF */  sd         $16, 0x0($29)
    /* F9198 001F9198 70A95124 */  addiu      $17, $2, %lo(D_0070A970)
    /* F919C 001F919C 2000BFFF */  sd         $31, 0x20($29)
    /* F91A0 001F91A0 03001024 */  addiu      $16, $0, 0x3
    /* F91A4 001F91A4 00000000 */  nop
.align 2
  .L001F91A8:
    /* F91A8 001F91A8 01000424 */  addiu      $4, $0, 0x1
    /* F91AC 001F91AC 9A67090C */  jal        SgGetSpuSlotMalloc
    /* F91B0 001F91B0 FFFF1026 */   addiu     $16, $16, -0x1
    /* F91B4 001F91B4 000022AE */  sw         $2, 0x0($17)
    /* F91B8 001F91B8 FBFF0106 */  bgez       $16, .L001F91A8
    /* F91BC 001F91BC 04003126 */   addiu     $17, $17, 0x4
    /* F91C0 001F91C0 0B00043C */  lui        $4, (0xB8800 >> 16)
    /* F91C4 001F91C4 6100053C */  lui        $5, %hi(D_00613820)
    /* F91C8 001F91C8 2038A524 */  addiu      $5, $5, %lo(D_00613820)
    /* F91CC 001F91CC 00888434 */  ori        $4, $4, (0xB8800 & 0xFFFF)
    /* F91D0 001F91D0 F0D6040C */  jal        new_mblock_node
    /* F91D4 001F91D4 4D000624 */   addiu     $6, $0, 0x4D
    /* F91D8 001F91D8 2D204000 */  daddu      $4, $2, $0
    /* F91DC 001F91DC FF078230 */  andi       $2, $4, 0x7FF
    /* F91E0 001F91E0 09004010 */  beqz       $2, .L001F9208
    /* F91E4 001F91E4 FFFF0324 */   addiu     $3, $0, -0x1
    /* F91E8 001F91E8 FF078224 */  addiu      $2, $4, 0x7FF
    /* F91EC 001F91EC 2A186400 */  slt        $3, $3, $4
    /* F91F0 001F91F0 0B108300 */  movn       $2, $4, $3
    /* F91F4 001F91F4 C3120200 */  sra        $2, $2, 11
    /* F91F8 001F91F8 01004224 */  addiu      $2, $2, 0x1
    /* F91FC 001F91FC C0120200 */  sll        $2, $2, 11
    /* F9200 001F9200 02000010 */  b          .L001F920C
    /* F9204 001F9204 78B682AF */   sw        $2, %gp_rel(D_0062C268)($28)
.align 2
  .L001F9208:
    /* F9208 001F9208 78B684AF */  sw         $4, %gp_rel(D_0062C268)($28)
.align 2
  .L001F920C:
    /* F920C 001F920C 78B6858F */  lw         $5, %gp_rel(D_0062C268)($28)
    /* F9210 001F9210 0B00063C */  lui        $6, (0xB8000 >> 16)
    /* F9214 001F9214 6100043C */  lui        $4, %hi(D_00613838)
    /* F9218 001F9218 0080C634 */  ori        $6, $6, (0xB8000 & 0xFFFF)
    /* F921C 001F921C 38388424 */  addiu      $4, $4, %lo(D_00613838)
    /* F9220 001F9220 F290060C */  jal        debug_StdPrintfDummy
    /* F9224 001F9224 01001024 */   addiu     $16, $0, 0x1
    /* F9228 001F9228 2068090C */  jal        SgStAdpcmInit
    /* F922C 001F922C 00000000 */   nop
    /* F9230 001F9230 7100023C */  lui        $2, %hi(D_0070A8C0)
    /* F9234 001F9234 C0A84224 */  addiu      $2, $2, %lo(D_0070A8C0)
    /* F9238 001F9238 58004224 */  addiu      $2, $2, 0x58
    /* F923C 001F923C 00000000 */  nop
.align 2
  .L001F9240:
    /* F9240 001F9240 000040AC */  sw         $0, 0x0($2)
    /* F9244 001F9244 FFFF1026 */  addiu      $16, $16, -0x1
    /* F9248 001F9248 A8FF4224 */  addiu      $2, $2, -0x58
    /* F924C 001F924C 00000000 */  nop
    /* F9250 001F9250 00000000 */  nop
    /* F9254 001F9254 FAFF0106 */  bgez       $16, .L001F9240
    /* F9258 001F9258 00000000 */   nop
    /* F925C 001F925C 01001024 */  addiu      $16, $0, 0x1
    /* F9260 001F9260 84B68227 */  addiu      $2, $28, %gp_rel(D_0062C274)
    /* F9264 001F9264 00000000 */  nop
.align 2
  .L001F9268:
    /* F9268 001F9268 000040AC */  sw         $0, 0x0($2)
    /* F926C 001F926C FFFF1026 */  addiu      $16, $16, -0x1
    /* F9270 001F9270 FCFF4224 */  addiu      $2, $2, -0x4
    /* F9274 001F9274 00000000 */  nop
    /* F9278 001F9278 00000000 */  nop
    /* F927C 001F927C FAFF0106 */  bgez       $16, .L001F9268
    /* F9280 001F9280 00000000 */   nop
    /* F9284 001F9284 2000BFDF */  ld         $31, 0x20($29)
    /* F9288 001F9288 1000B1DF */  ld         $17, 0x10($29)
    /* F928C 001F928C 0000B0DF */  ld         $16, 0x0($29)
    /* F9290 001F9290 88B680AF */  sw         $0, %gp_rel(D_0062C278)($28)
    /* F9294 001F9294 0800E003 */  jr         $31
    /* F9298 001F9298 3000BD27 */   addiu     $29, $29, 0x30
endlabel AdpcmPlay
    /* F929C 001F929C 00000000 */  nop
```
