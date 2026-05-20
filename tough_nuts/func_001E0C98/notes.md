# func_001E0C98 — parked

VRAM: 0x001E0C98 (file_off 0x0E0C98)
Asm source: asm/nonmatchings/src/motionOrientManager/func_001E0C98.s

## Attempt at 2026-05-20

**Reason parked:** alignment proof: gcc emits sd/ld for stack buf instead of sdl/sdr; load-store interleave because gcc serializes through v1

**TU:** `src/motionOrientManager.c`

**Seed:** `tough_nuts/func_001E0C98/func_001E0C98.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_0063347C, 1

.align 3
nonmatching func_001E0C98, 0xB4

glabel func_001E0C98
    /* E0C98 001E0C98 D0FFBD27 */  addiu      $29, $29, -0x30
    /* E0C9C 001E0C9C 8CAB838F */  lw         $3, (D_0063347C) /* gp_rel: (D_0063347C) */
    /* E0CA0 001E0CA0 2000BFFF */  sd         $31, 0x20($29)
    /* E0CA4 001E0CA4 5C01628C */  lw         $2, 0x15C($3)
    /* E0CA8 001E0CA8 87014368 */  ldl        $3, 0x187($2)
    /* E0CAC 001E0CAC 8001436C */  ldr        $3, 0x180($2)
    /* E0CB0 001E0CB0 8F014668 */  ldl        $6, 0x18F($2)
    /* E0CB4 001E0CB4 8801466C */  ldr        $6, 0x188($2)
    /* E0CB8 001E0CB8 97014768 */  ldl        $7, 0x197($2)
    /* E0CBC 001E0CBC 9001476C */  ldr        $7, 0x190($2)
    /* E0CC0 001E0CC0 9F014868 */  ldl        $8, 0x19F($2)
    /* E0CC4 001E0CC4 9801486C */  ldr        $8, 0x198($2)
    /* E0CC8 001E0CC8 0700A3B3 */  sdl        $3, 0x7($29)
    /* E0CCC 001E0CCC 0000A3B7 */  sdr        $3, 0x0($29)
    /* E0CD0 001E0CD0 0F00A6B3 */  sdl        $6, 0xF($29)
    /* E0CD4 001E0CD4 0800A6B7 */  sdr        $6, 0x8($29)
    /* E0CD8 001E0CD8 1700A7B3 */  sdl        $7, 0x17($29)
    /* E0CDC 001E0CDC 1000A7B7 */  sdr        $7, 0x10($29)
    /* E0CE0 001E0CE0 1F00A8B3 */  sdl        $8, 0x1F($29)
    /* E0CE4 001E0CE4 1800A8B7 */  sdr        $8, 0x18($29)
    /* E0CE8 001E0CE8 DA7C070C */  jal        func_001DF368
    /* E0CEC 001E0CEC 00000000 */   nop
    /* E0CF0 001E0CF0 8CAB828F */  lw         $2, (D_0063347C) /* gp_rel: (D_0063347C) */
    /* E0CF4 001E0CF4 5C01428C */  lw         $2, 0x15C($2)
    /* E0CF8 001E0CF8 3406438C */  lw         $3, 0x634($2)
    /* E0CFC 001E0CFC 11006010 */  beqz       $3, .L001E0D44
    /* E0D00 001E0D00 2000BFDF */   ld        $31, 0x20($29)
    /* E0D04 001E0D04 0700A36B */  ldl        $3, 0x7($29)
    /* E0D08 001E0D08 0000A36F */  ldr        $3, 0x0($29)
    /* E0D0C 001E0D0C 0F00A46B */  ldl        $4, 0xF($29)
    /* E0D10 001E0D10 0800A46F */  ldr        $4, 0x8($29)
    /* E0D14 001E0D14 1700A56B */  ldl        $5, 0x17($29)
    /* E0D18 001E0D18 1000A56F */  ldr        $5, 0x10($29)
    /* E0D1C 001E0D1C 1F00A66B */  ldl        $6, 0x1F($29)
    /* E0D20 001E0D20 1800A66F */  ldr        $6, 0x18($29)
    /* E0D24 001E0D24 870143B0 */  sdl        $3, 0x187($2)
    /* E0D28 001E0D28 800143B4 */  sdr        $3, 0x180($2)
    /* E0D2C 001E0D2C 8F0144B0 */  sdl        $4, 0x18F($2)
    /* E0D30 001E0D30 880144B4 */  sdr        $4, 0x188($2)
    /* E0D34 001E0D34 970145B0 */  sdl        $5, 0x197($2)
    /* E0D38 001E0D38 900145B4 */  sdr        $5, 0x190($2)
    /* E0D3C 001E0D3C 9F0146B0 */  sdl        $6, 0x19F($2)
    /* E0D40 001E0D40 980146B4 */  sdr        $6, 0x198($2)
.align 2
  .L001E0D44:
    /* E0D44 001E0D44 0800E003 */  jr         $31
    /* E0D48 001E0D48 3000BD27 */   addiu     $29, $29, 0x30
endlabel func_001E0C98
    /* E0D4C 001E0D4C 00000000 */  nop
```
