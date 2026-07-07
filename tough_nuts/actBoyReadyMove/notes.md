# actBoyReadyMove — parked

VRAM: 0x00152DF0 (file_off 0x052DF0)
Asm source: asm/aug6/nonmatchings/fumi/src/boyact/actBoyReadyMove.s

## Attempt at 2026-07-07

**Reason parked:** rc48 leaf 64-bit bitfield-pack D_006A4600->D_006A45A0 (bits 32/33/34 from src flags); ops correct but ROM materializes 3 masks upfront in t0/t1/t2 + holds v in v0, gcc schedules lazily+churns regs; regalloc-swap, permuter-class

**TU:** `fumi/src/boyact.c`

**Seed:** `tough_nuts/actBoyReadyMove/actBoyReadyMove.c`

Disassembly:

```
.align 3
nonmatching actBoyReadyMove, 0xC4

glabel actBoyReadyMove
    /* 52DF0 00152DF0 6A000C3C */  lui        $12, %hi(D_006A4600)
    /* 52DF4 00152DF4 6A000B3C */  lui        $11, %hi(D_006A45A0)
    /* 52DF8 00152DF8 00468625 */  addiu      $6, $12, %lo(D_006A4600)
    /* 52DFC 00152DFC A0456725 */  addiu      $7, $11, %lo(D_006A45A0)
    /* 52E00 00152E00 1000C28C */  lw         $2, 0x10($6)
    /* 52E04 00152E04 FEFF0824 */  addiu      $8, $0, -0x2
    /* 52E08 00152E08 38440800 */  dsll       $8, $8, 16
    /* 52E0C 00152E0C FFFF0835 */  ori        $8, $8, 0xFFFF
    /* 52E10 00152E10 38440800 */  dsll       $8, $8, 16
    /* 52E14 00152E14 FFFF0835 */  ori        $8, $8, 0xFFFF
    /* 52E18 00152E18 1400C590 */  lbu        $5, 0x14($6)
    /* 52E1C 00152E1C FDFF0924 */  addiu      $9, $0, -0x3
    /* 52E20 00152E20 384C0900 */  dsll       $9, $9, 16
    /* 52E24 00152E24 FFFF2935 */  ori        $9, $9, 0xFFFF
    /* 52E28 00152E28 384C0900 */  dsll       $9, $9, 16
    /* 52E2C 00152E2C FFFF2935 */  ori        $9, $9, 0xFFFF
    /* 52E30 00152E30 0800E2AC */  sw         $2, 0x8($7)
    /* 52E34 00152E34 FBFF0A24 */  addiu      $10, $0, -0x5
    /* 52E38 00152E38 38540A00 */  dsll       $10, $10, 16
    /* 52E3C 00152E3C FFFF4A35 */  ori        $10, $10, 0xFFFF
    /* 52E40 00152E40 38540A00 */  dsll       $10, $10, 16
    /* 52E44 00152E44 FFFF4A35 */  ori        $10, $10, 0xFFFF
    /* 52E48 00152E48 0100A530 */  andi       $5, $5, 0x1
    /* 52E4C 00152E4C 0800E2DC */  ld         $2, 0x8($7)
    /* 52E50 00152E50 3C280500 */  dsll32     $5, $5, 0
    /* 52E54 00152E54 1500C390 */  lbu        $3, 0x15($6)
    /* 52E58 00152E58 24104800 */  and        $2, $2, $8
    /* 52E5C 00152E5C 1600C494 */  lhu        $4, 0x16($6)
    /* 52E60 00152E60 25104500 */  or         $2, $2, $5
    /* 52E64 00152E64 01006330 */  andi       $3, $3, 0x1
    /* 52E68 00152E68 7C180300 */  dsll32     $3, $3, 1
    /* 52E6C 00152E6C 24104900 */  and        $2, $2, $9
    /* 52E70 00152E70 0800C58C */  lw         $5, 0x8($6)
    /* 52E74 00152E74 25104300 */  or         $2, $2, $3
    /* 52E78 00152E78 01008430 */  andi       $4, $4, 0x1
    /* 52E7C 00152E7C 0C00C38C */  lw         $3, 0xC($6)
    /* 52E80 00152E80 BC200400 */  dsll32     $4, $4, 2
    /* 52E84 00152E84 24104A00 */  and        $2, $2, $10
    /* 52E88 00152E88 A04565AD */  sw         $5, %lo(D_006A45A0)($11)
    /* 52E8C 00152E8C 25104400 */  or         $2, $2, $4
    /* 52E90 00152E90 0400E3AC */  sw         $3, 0x4($7)
    /* 52E94 00152E94 0800E2FC */  sd         $2, 0x8($7)
    /* 52E98 00152E98 00468525 */  addiu      $5, $12, %lo(D_006A4600)
    /* 52E9C 00152E9C 0700A268 */  ldl        $2, 0x7($5)
    /* 52EA0 00152EA0 0000A26C */  ldr        $2, 0x0($5)
    /* 52EA4 00152EA4 5700E2B0 */  sdl        $2, 0x57($7)
    /* 52EA8 00152EA8 5000E2B4 */  sdr        $2, 0x50($7)
    /* 52EAC 00152EAC 0800E003 */  jr         $31
    /* 52EB0 00152EB0 00000000 */   nop
endlabel actBoyReadyMove
    /* 52EB4 00152EB4 00000000 */  nop
```
