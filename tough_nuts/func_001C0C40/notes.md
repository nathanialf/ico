# func_001C0C40 — parked

VRAM: 0x001C0C40 (file_off 0x0C0C40)
Asm source: asm/matchings/src/switch/func_001C0C40.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE,REG)

**TU:** `src/switch.c`

**Seed:** `tough_nuts/func_001C0C40/func_001C0C40.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001C0C40, 0x110

glabel func_001C0C40
    /* C0C40 001C0C40 A0FFBD27 */  addiu      $29, $29, -0x60
    /* C0C44 001C0C44 6200063C */  lui        $6, %hi(D_00618630)
    /* C0C48 001C0C48 4000B4FF */  sd         $20, 0x40($29)
    /* C0C4C 001C0C4C 3086C624 */  addiu      $6, $6, %lo(D_00618630)
    /* C0C50 001C0C50 3000B3FF */  sd         $19, 0x30($29)
    /* C0C54 001C0C54 2DA08000 */  daddu      $20, $4, $0
    /* C0C58 001C0C58 2D98A000 */  daddu      $19, $5, $0
    /* C0C5C 001C0C5C 2097848F */  lw         $4, (D_00632010) /* gp_rel: (D_00632010) */
    /* C0C60 001C0C60 2000B2FF */  sd         $18, 0x20($29)
    /* C0C64 001C0C64 20000524 */  addiu      $5, $0, 0x20
    /* C0C68 001C0C68 5000BFFF */  sd         $31, 0x50($29)
    /* C0C6C 001C0C6C 2C010724 */  addiu      $7, $0, 0x12C
    /* C0C70 001C0C70 1000B1FF */  sd         $17, 0x10($29)
    /* C0C74 001C0C74 3EE8040C */  jal        func_0013A0F8
    /* C0C78 001C0C78 0000B0FF */   sd        $16, 0x0($29)
    /* C0C7C 001C0C7C 2D904000 */  daddu      $18, $2, $0
    /* C0C80 001C0C80 4C00023C */  lui        $2, %hi(D_004BEFD0)
    /* C0C84 001C0C84 D0EF4624 */  addiu      $6, $2, %lo(D_004BEFD0)
    /* C0C88 001C0C88 0700C368 */  ldl        $3, 0x7($6)
    /* C0C8C 001C0C8C 0000C36C */  ldr        $3, 0x0($6)
    /* C0C90 001C0C90 0F00C468 */  ldl        $4, 0xF($6)
    /* C0C94 001C0C94 0800C46C */  ldr        $4, 0x8($6)
    /* C0C98 001C0C98 1700C568 */  ldl        $5, 0x17($6)
    /* C0C9C 001C0C9C 1000C56C */  ldr        $5, 0x10($6)
    /* C0CA0 001C0CA0 070043B2 */  sdl        $3, 0x7($18)
    /* C0CA4 001C0CA4 000043B6 */  sdr        $3, 0x0($18)
    /* C0CA8 001C0CA8 0F0044B2 */  sdl        $4, 0xF($18)
    /* C0CAC 001C0CAC 080044B6 */  sdr        $4, 0x8($18)
    /* C0CB0 001C0CB0 170045B2 */  sdl        $5, 0x17($18)
    /* C0CB4 001C0CB4 100045B6 */  sdr        $5, 0x10($18)
    /* C0CB8 001C0CB8 1F00C368 */  ldl        $3, 0x1F($6)
    /* C0CBC 001C0CBC 1800C36C */  ldr        $3, 0x18($6)
    /* C0CC0 001C0CC0 1F0043B2 */  sdl        $3, 0x1F($18)
    /* C0CC4 001C0CC4 180043B6 */  sdr        $3, 0x18($18)
    /* C0CC8 001C0CC8 3000638E */  lw         $3, 0x30($19)
    /* C0CCC 001C0CCC 03006010 */  beqz       $3, .L001C0CDC
    /* C0CD0 001C0CD0 01000224 */   addiu     $2, $0, 0x1
    /* C0CD4 001C0CD4 02000010 */  b          .L001C0CE0
    /* C0CD8 001C0CD8 140042AE */   sw        $2, 0x14($18)
.align 2
  .L001C0CDC:
    /* C0CDC 001C0CDC 140040AE */  sw         $0, 0x14($18)
.align 2
  .L001C0CE0:
    /* C0CE0 001C0CE0 5C01838E */  lw         $3, 0x15C($20)
    /* C0CE4 001C0CE4 28001124 */  addiu      $17, $0, 0x28
    /* C0CE8 001C0CE8 2900103C */  lui        $16, %hi(D_0028CA88)
    /* C0CEC 001C0CEC 2D286002 */  daddu      $5, $19, $0
    /* C0CF0 001C0CF0 1408628C */  lw         $2, 0x814($3)
    /* C0CF4 001C0CF4 88CA1026 */  addiu      $16, $16, %lo(D_0028CA88)
    /* C0CF8 001C0CF8 18105100 */  mult       $2, $2, $17
    /* C0CFC 001C0CFC 21105000 */  addu       $2, $2, $16
    /* C0D00 001C0D00 C47C060C */  jal        func_0019F310
    /* C0D04 001C0D04 0000448C */   lw        $4, 0x0($2)
    /* C0D08 001C0D08 0C0042AE */  sw         $2, 0xC($18)
    /* C0D0C 001C0D0C 2D286002 */  daddu      $5, $19, $0
    /* C0D10 001C0D10 5C01838E */  lw         $3, 0x15C($20)
    /* C0D14 001C0D14 1408628C */  lw         $2, 0x814($3)
    /* C0D18 001C0D18 18185100 */  mult       $3, $2, $17
    /* C0D1C 001C0D1C 21107000 */  addu       $2, $3, $16
    /* C0D20 001C0D20 C47C060C */  jal        func_0019F310
    /* C0D24 001C0D24 0400448C */   lw        $4, 0x4($2)
    /* C0D28 001C0D28 100042AE */  sw         $2, 0x10($18)
    /* C0D2C 001C0D2C 2D104002 */  daddu      $2, $18, $0
    /* C0D30 001C0D30 5000BFDF */  ld         $31, 0x50($29)
    /* C0D34 001C0D34 4000B4DF */  ld         $20, 0x40($29)
    /* C0D38 001C0D38 3000B3DF */  ld         $19, 0x30($29)
    /* C0D3C 001C0D3C 2000B2DF */  ld         $18, 0x20($29)
    /* C0D40 001C0D40 1000B1DF */  ld         $17, 0x10($29)
    /* C0D44 001C0D44 0000B0DF */  ld         $16, 0x0($29)
    /* C0D48 001C0D48 0800E003 */  jr         $31
    /* C0D4C 001C0D4C 6000BD27 */   addiu     $29, $29, 0x60
endlabel func_001C0C40
```
