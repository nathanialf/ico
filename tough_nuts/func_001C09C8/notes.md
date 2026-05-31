# func_001C09C8 — parked

VRAM: 0x001C09C8 (file_off 0x0C09C8)
Asm source: asm/matchings/src/switch/func_001C09C8.s

## Attempt at 2026-05-31

**Reason parked:** crutch-removal: deleting bucket A/B matching macros (KEEP_LIVE,REG)

**TU:** `src/switch.c`

**Seed:** `tough_nuts/func_001C09C8/func_001C09C8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00632010, 1

.align 3
nonmatching func_001C09C8, 0x110

glabel func_001C09C8
    /* C09C8 001C09C8 A0FFBD27 */  addiu      $29, $29, -0x60
    /* C09CC 001C09CC 6200063C */  lui        $6, %hi(D_00618630)
    /* C09D0 001C09D0 4000B4FF */  sd         $20, 0x40($29)
    /* C09D4 001C09D4 3086C624 */  addiu      $6, $6, %lo(D_00618630)
    /* C09D8 001C09D8 3000B3FF */  sd         $19, 0x30($29)
    /* C09DC 001C09DC 2DA08000 */  daddu      $20, $4, $0
    /* C09E0 001C09E0 2D98A000 */  daddu      $19, $5, $0
    /* C09E4 001C09E4 2097848F */  lw         $4, (D_00632010) /* gp_rel: (D_00632010) */
    /* C09E8 001C09E8 2000B2FF */  sd         $18, 0x20($29)
    /* C09EC 001C09EC 20000524 */  addiu      $5, $0, 0x20
    /* C09F0 001C09F0 5000BFFF */  sd         $31, 0x50($29)
    /* C09F4 001C09F4 8D000724 */  addiu      $7, $0, 0x8D
    /* C09F8 001C09F8 1000B1FF */  sd         $17, 0x10($29)
    /* C09FC 001C09FC 3EE8040C */  jal        func_0013A0F8
    /* C0A00 001C0A00 0000B0FF */   sd        $16, 0x0($29)
    /* C0A04 001C0A04 2D904000 */  daddu      $18, $2, $0
    /* C0A08 001C0A08 4C00023C */  lui        $2, %hi(D_004BEFD0)
    /* C0A0C 001C0A0C D0EF4624 */  addiu      $6, $2, %lo(D_004BEFD0)
    /* C0A10 001C0A10 0700C368 */  ldl        $3, 0x7($6)
    /* C0A14 001C0A14 0000C36C */  ldr        $3, 0x0($6)
    /* C0A18 001C0A18 0F00C468 */  ldl        $4, 0xF($6)
    /* C0A1C 001C0A1C 0800C46C */  ldr        $4, 0x8($6)
    /* C0A20 001C0A20 1700C568 */  ldl        $5, 0x17($6)
    /* C0A24 001C0A24 1000C56C */  ldr        $5, 0x10($6)
    /* C0A28 001C0A28 070043B2 */  sdl        $3, 0x7($18)
    /* C0A2C 001C0A2C 000043B6 */  sdr        $3, 0x0($18)
    /* C0A30 001C0A30 0F0044B2 */  sdl        $4, 0xF($18)
    /* C0A34 001C0A34 080044B6 */  sdr        $4, 0x8($18)
    /* C0A38 001C0A38 170045B2 */  sdl        $5, 0x17($18)
    /* C0A3C 001C0A3C 100045B6 */  sdr        $5, 0x10($18)
    /* C0A40 001C0A40 1F00C368 */  ldl        $3, 0x1F($6)
    /* C0A44 001C0A44 1800C36C */  ldr        $3, 0x18($6)
    /* C0A48 001C0A48 1F0043B2 */  sdl        $3, 0x1F($18)
    /* C0A4C 001C0A4C 180043B6 */  sdr        $3, 0x18($18)
    /* C0A50 001C0A50 3000638E */  lw         $3, 0x30($19)
    /* C0A54 001C0A54 03006010 */  beqz       $3, .L001C0A64
    /* C0A58 001C0A58 01000224 */   addiu     $2, $0, 0x1
    /* C0A5C 001C0A5C 02000010 */  b          .L001C0A68
    /* C0A60 001C0A60 140042AE */   sw        $2, 0x14($18)
.align 2
  .L001C0A64:
    /* C0A64 001C0A64 140040AE */  sw         $0, 0x14($18)
.align 2
  .L001C0A68:
    /* C0A68 001C0A68 5C01838E */  lw         $3, 0x15C($20)
    /* C0A6C 001C0A6C 28001124 */  addiu      $17, $0, 0x28
    /* C0A70 001C0A70 2900103C */  lui        $16, %hi(D_0028CA88)
    /* C0A74 001C0A74 2D286002 */  daddu      $5, $19, $0
    /* C0A78 001C0A78 1408628C */  lw         $2, 0x814($3)
    /* C0A7C 001C0A7C 88CA1026 */  addiu      $16, $16, %lo(D_0028CA88)
    /* C0A80 001C0A80 18105100 */  mult       $2, $2, $17
    /* C0A84 001C0A84 21105000 */  addu       $2, $2, $16
    /* C0A88 001C0A88 C47C060C */  jal        func_0019F310
    /* C0A8C 001C0A8C 0000448C */   lw        $4, 0x0($2)
    /* C0A90 001C0A90 0C0042AE */  sw         $2, 0xC($18)
    /* C0A94 001C0A94 2D286002 */  daddu      $5, $19, $0
    /* C0A98 001C0A98 5C01838E */  lw         $3, 0x15C($20)
    /* C0A9C 001C0A9C 1408628C */  lw         $2, 0x814($3)
    /* C0AA0 001C0AA0 18185100 */  mult       $3, $2, $17
    /* C0AA4 001C0AA4 21107000 */  addu       $2, $3, $16
    /* C0AA8 001C0AA8 C47C060C */  jal        func_0019F310
    /* C0AAC 001C0AAC 0400448C */   lw        $4, 0x4($2)
    /* C0AB0 001C0AB0 100042AE */  sw         $2, 0x10($18)
    /* C0AB4 001C0AB4 2D104002 */  daddu      $2, $18, $0
    /* C0AB8 001C0AB8 5000BFDF */  ld         $31, 0x50($29)
    /* C0ABC 001C0ABC 4000B4DF */  ld         $20, 0x40($29)
    /* C0AC0 001C0AC0 3000B3DF */  ld         $19, 0x30($29)
    /* C0AC4 001C0AC4 2000B2DF */  ld         $18, 0x20($29)
    /* C0AC8 001C0AC8 1000B1DF */  ld         $17, 0x10($29)
    /* C0ACC 001C0ACC 0000B0DF */  ld         $16, 0x0($29)
    /* C0AD0 001C0AD0 0800E003 */  jr         $31
    /* C0AD4 001C0AD4 6000BD27 */   addiu     $29, $29, 0x60
endlabel func_001C09C8
```
