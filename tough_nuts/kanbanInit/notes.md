# kanbanInit — parked

VRAM: 0x001AD128 (file_off 0x0AD128)
Asm source: asm/aug6/nonmatchings/common/src/kanban/kanbanInit.s

## Attempt at 2026-06-22

**Reason parked:** plateau: 30 distinct hand hypotheses, no real_count progress (best=42). PARK the seed, then fire ONE bounded permuter shot on it (REFERENCE Step 4); harvest by true real_count and adopt any improvement (resolution b only if nothing beats best).

**TU:** `common/src/kanban.c`

**Seed:** `tough_nuts/kanbanInit/kanbanInit.c`

Disassembly:

```
.align 3
nonmatching kanbanInit, 0x12C

glabel kanbanInit
    /* AD128 001AD128 38000324 */  addiu      $3, $0, 0x38
    /* AD12C 001AD12C F0FFBD27 */  addiu      $29, $29, -0x10
    /* AD130 001AD130 18208300 */  mult       $4, $4, $3
    /* AD134 001AD134 5300023C */  lui        $2, %hi(D_00536530)
    /* AD138 001AD138 7000033C */  lui        $3, %hi(D_006FF910)
    /* AD13C 001AD13C 30654224 */  addiu      $2, $2, %lo(D_00536530)
    /* AD140 001AD140 10F96624 */  addiu      $6, $3, %lo(D_006FF910)
    /* AD144 001AD144 0000BFFF */  sd         $31, 0x0($29)
    /* AD148 001AD148 2D180000 */  daddu      $3, $0, $0
    /* AD14C 001AD14C 21208200 */  addu       $4, $4, $2
.align 2
  .L001AD150:
    /* AD150 001AD150 0000C28C */  lw         $2, 0x0($6)
    /* AD154 001AD154 09004010 */  beqz       $2, .L001AD17C
    /* AD158 001AD158 01006324 */   addiu     $3, $3, 0x1
    /* AD15C 001AD15C 1E006228 */  slti       $2, $3, 0x1E
    /* AD160 001AD160 FBFF4014 */  bnez       $2, .L001AD150
    /* AD164 001AD164 2000C624 */   addiu     $6, $6, 0x20
    /* AD168 001AD168 6100043C */  lui        $4, %hi(D_0060F658)
    /* AD16C 001AD16C F290060C */  jal        debug_StdPrintfDummy
    /* AD170 001AD170 58F68424 */   addiu     $4, $4, %lo(D_0060F658)
    /* AD174 001AD174 34000010 */  b          .L001AD248
    /* AD178 001AD178 2D100000 */   daddu     $2, $0, $0
.align 2
  .L001AD17C:
    /* AD17C 001AD17C 0C00C28C */  lw         $2, 0xC($6)
    /* AD180 001AD180 FEFF0324 */  addiu      $3, $0, -0x2
    /* AD184 001AD184 0800C0AC */  sw         $0, 0x8($6)
    /* AD188 001AD188 24104300 */  and        $2, $2, $3
    /* AD18C 001AD18C 0000C4AC */  sw         $4, 0x0($6)
    /* AD190 001AD190 0C00C2AC */  sw         $2, 0xC($6)
    /* AD194 001AD194 1000C0AC */  sw         $0, 0x10($6)
    /* AD198 001AD198 2800878C */  lw         $7, 0x28($4)
    /* AD19C 001AD19C 6CB5838F */  lw         $3, %gp_rel(D_0062C15C)($28)
    /* AD1A0 001AD1A0 D0A68A27 */  addiu      $10, $28, %gp_rel(D_0062B2C0)
    /* AD1A4 001AD1A4 03004289 */  lwl        $2, 0x3($10)
    /* AD1A8 001AD1A8 00004299 */  lwr        $2, 0x0($10)
    /* AD1AC 001AD1AC 1700C2A8 */  swl        $2, 0x17($6)
    /* AD1B0 001AD1B0 1400C2B8 */  swr        $2, 0x14($6)
    /* AD1B4 001AD1B4 2C0087AC */  sw         $7, 0x2C($4)
    /* AD1B8 001AD1B8 1C006010 */  beqz       $3, .L001AD22C
    /* AD1BC 001AD1BC 0400C5AC */   sw        $5, 0x4($6)
    /* AD1C0 001AD1C0 0400628C */  lw         $2, 0x4($3)
    /* AD1C4 001AD1C4 2A10A200 */  slt        $2, $5, $2
    /* AD1C8 001AD1C8 06004050 */  beql       $2, $0, .L001AD1E4
    /* AD1CC 001AD1CC 1800648C */   lw        $4, 0x18($3)
    /* AD1D0 001AD1D0 1C0066AC */  sw         $6, 0x1C($3)
    /* AD1D4 001AD1D4 1800C3AC */  sw         $3, 0x18($6)
    /* AD1D8 001AD1D8 1C00C0AC */  sw         $0, 0x1C($6)
    /* AD1DC 001AD1DC 16000010 */  b          .L001AD238
    /* AD1E0 001AD1E0 6CB586AF */   sw        $6, %gp_rel(D_0062C15C)($28)
.align 2
  .L001AD1E4:
    /* AD1E4 001AD1E4 0F008050 */  beql       $4, $0, .L001AD224
    /* AD1E8 001AD1E8 180066AC */   sw        $6, 0x18($3)
    /* AD1EC 001AD1EC 2D188000 */  daddu      $3, $4, $0
.align 2
  .L001AD1F0:
    /* AD1F0 001AD1F0 1800628C */  lw         $2, 0x18($3)
    /* AD1F4 001AD1F4 0A004010 */  beqz       $2, .L001AD220
    /* AD1F8 001AD1F8 2D204000 */   daddu     $4, $2, $0
    /* AD1FC 001AD1FC 0400628C */  lw         $2, 0x4($3)
    /* AD200 001AD200 2A10A200 */  slt        $2, $5, $2
    /* AD204 001AD204 FAFF4050 */  beql       $2, $0, .L001AD1F0
    /* AD208 001AD208 2D188000 */   daddu     $3, $4, $0
    /* AD20C 001AD20C 1C00628C */  lw         $2, 0x1C($3)
    /* AD210 001AD210 1C00C2AC */  sw         $2, 0x1C($6)
    /* AD214 001AD214 1C0066AC */  sw         $6, 0x1C($3)
    /* AD218 001AD218 07000010 */  b          .L001AD238
    /* AD21C 001AD21C 1800C3AC */   sw        $3, 0x18($6)
.align 2
  .L001AD220:
    /* AD220 001AD220 180066AC */  sw         $6, 0x18($3)
.align 2
  .L001AD224:
    /* AD224 001AD224 03000010 */  b          .L001AD234
    /* AD228 001AD228 1C00C3AC */   sw        $3, 0x1C($6)
.align 2
  .L001AD22C:
    /* AD22C 001AD22C 6CB586AF */  sw         $6, %gp_rel(D_0062C15C)($28)
    /* AD230 001AD230 1C00C0AC */  sw         $0, 0x1C($6)
.align 2
  .L001AD234:
    /* AD234 001AD234 1800C0AC */  sw         $0, 0x18($6)
.align 2
  .L001AD238:
    /* AD238 001AD238 FFFF0224 */  addiu      $2, $0, -0x1
    /* AD23C 001AD23C 0100E254 */  bnel       $7, $2, .L001AD244
    /* AD240 001AD240 70B586AF */   sw        $6, %gp_rel(D_0062C160)($28)
.align 2
  .L001AD244:
    /* AD244 001AD244 2D10C000 */  daddu      $2, $6, $0
.align 2
  .L001AD248:
    /* AD248 001AD248 0000BFDF */  ld         $31, 0x0($29)
    /* AD24C 001AD24C 0800E003 */  jr         $31
    /* AD250 001AD250 1000BD27 */   addiu     $29, $29, 0x10
endlabel kanbanInit
    /* AD254 001AD254 00000000 */  nop
```
