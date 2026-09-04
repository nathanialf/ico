# SetStatusBoy_OtherStageGirlPinch — parked

VRAM: 0x00152960 (file_off 0x052960)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/SetStatusBoy_OtherStageGirlPinch.s

## Attempt at 2026-07-07

**Reason parked:** rc13 structure correct (64-bit bit34/33 clear+guarded-set on D_006A45A0[1]); consistent regalloc swap o=a1-vs-a0 / mask=v1-vs-a1 + beqz delay-nop; folds under reshaping; permuter-class coloring

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/SetStatusBoy_OtherStageGirlPinch/SetStatusBoy_OtherStageGirlPinch.c`

Disassembly:

```
.align 3
nonmatching SetStatusBoy_OtherStageGirlPinch, 0xD4

glabel SetStatusBoy_OtherStageGirlPinch
    /* 52960 00152960 D0FFBD27 */  addiu      $29, $29, -0x30
    /* 52964 00152964 F491858F */  lw         $5, %gp_rel(D_00629DE4)($28)
    /* 52968 00152968 1000B1FF */  sd         $17, 0x10($29)
    /* 5296C 0015296C FBFF0324 */  addiu      $3, $0, -0x5
    /* 52970 00152970 381C0300 */  dsll       $3, $3, 16
    /* 52974 00152974 FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 52978 00152978 381C0300 */  dsll       $3, $3, 16
    /* 5297C 0015297C FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 52980 00152980 0000B0FF */  sd         $16, 0x0($29)
    /* 52984 00152984 6A00113C */  lui        $17, %hi(D_006A45A0)
    /* 52988 00152988 2000BFFF */  sd         $31, 0x20($29)
    /* 5298C 0015298C A0453026 */  addiu      $16, $17, %lo(D_006A45A0)
    /* 52990 00152990 080002DE */  ld         $2, 0x8($16)
    /* 52994 00152994 6401A48C */  lw         $4, 0x164($5)
    /* 52998 00152998 24104300 */  and        $2, $2, $3
    /* 5299C 0015299C 080002FE */  sd         $2, 0x8($16)
    /* 529A0 001529A0 3001848C */  lw         $4, 0x130($4)
    /* 529A4 001529A4 0F008010 */  beqz       $4, .L001529E4
    /* 529A8 001529A8 00000000 */   nop
    /* 529AC 001529AC 2C24050C */  jal        ACTGame_isWeaponEnableCatchfire
    /* 529B0 001529B0 00000000 */   nop
    /* 529B4 001529B4 0B004010 */  beqz       $2, .L001529E4
    /* 529B8 001529B8 00000000 */   nop
    /* 529BC 001529BC 4EBC070C */  jal        TorchGeo
    /* 529C0 001529C0 2D204000 */   daddu     $4, $2, $0
    /* 529C4 001529C4 07004050 */  beql       $2, $0, .L001529E4
    /* 529C8 001529C8 A0453026 */   addiu     $16, $17, %lo(D_006A45A0)
    /* 529CC 001529CC 080002DE */  ld         $2, 0x8($16)
    /* 529D0 001529D0 00800334 */  ori        $3, $0, 0x8000
    /* 529D4 001529D4 F81C0300 */  dsll       $3, $3, 19
    /* 529D8 001529D8 25104300 */  or         $2, $2, $3
    /* 529DC 001529DC 080002FE */  sd         $2, 0x8($16)
    /* 529E0 001529E0 A0453026 */  addiu      $16, $17, %lo(D_006A45A0)
.align 2
  .L001529E4:
    /* 529E4 001529E4 FDFF0324 */  addiu      $3, $0, -0x3
    /* 529E8 001529E8 381C0300 */  dsll       $3, $3, 16
    /* 529EC 001529EC FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 529F0 001529F0 381C0300 */  dsll       $3, $3, 16
    /* 529F4 001529F4 FFFF6334 */  ori        $3, $3, 0xFFFF
    /* 529F8 001529F8 080002DE */  ld         $2, 0x8($16)
    /* 529FC 001529FC 24104300 */  and        $2, $2, $3
    /* 52A00 00152A00 A222050C */  jal        ACTEnvGetTest
    /* 52A04 00152A04 080002FE */   sd        $2, 0x8($16)
    /* 52A08 00152A08 06004010 */  beqz       $2, .L00152A24
    /* 52A0C 00152A0C 2000BFDF */   ld        $31, 0x20($29)
    /* 52A10 00152A10 080002DE */  ld         $2, 0x8($16)
    /* 52A14 00152A14 00800334 */  ori        $3, $0, 0x8000
    /* 52A18 00152A18 B81C0300 */  dsll       $3, $3, 18
    /* 52A1C 00152A1C 25104300 */  or         $2, $2, $3
    /* 52A20 00152A20 080002FE */  sd         $2, 0x8($16)
.align 2
  .L00152A24:
    /* 52A24 00152A24 1000B1DF */  ld         $17, 0x10($29)
    /* 52A28 00152A28 0000B0DF */  ld         $16, 0x0($29)
    /* 52A2C 00152A2C 0800E003 */  jr         $31
    /* 52A30 00152A30 3000BD27 */   addiu     $29, $29, 0x30
endlabel SetStatusBoy_OtherStageGirlPinch
    /* 52A34 00152A34 00000000 */  nop
```
