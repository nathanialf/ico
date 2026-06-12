# func_002409C8 — parked

VRAM: 0x002409C8 (file_off 0x1409C8)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_002409C8.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_002409C8/func_002409C8.c`

Disassembly:

```
.align 3
nonmatching func_002409C8, 0x60

glabel func_002409C8
    /* 1409C8 002409C8 2C01E04B */  vsub.xyzw  $vf4, $vf0, $vf0
    /* 1409CC 002409CC 8045023C */  lui        $2, (0x45800000 >> 16)
    /* 1409D0 002409D0 38140200 */  dsll       $2, $2, 16
    /* 1409D4 002409D4 80454234 */  ori        $2, $2, 0x4580
    /* 1409D8 002409D8 38140200 */  dsll       $2, $2, 16
    /* 1409DC 002409DC 000086D8 */  lqc2       $vf6, 0x0($4)
    /* 1409E0 002409E0 0000A8D8 */  lqc2       $vf8, 0x0($5)
    /* 1409E4 002409E4 0000C9D8 */  lqc2       $vf9, 0x0($6)
    /* 1409E8 002409E8 0038A248 */  qmtc2.ni   $2, $vf7
    /* 1409EC 002409EC 0080C048 */  ctc2.ni    $0, $vi16
    /* 1409F0 002409F0 6C31A44B */  vsub.xyw   $vf5, $vf6, $vf4
    /* 1409F4 002409F4 6C39864B */  vsub.xy    $vf5, $vf7, $vf6
    /* 1409F8 002409F8 6C41A44B */  vsub.xyw   $vf5, $vf8, $vf4
    /* 1409FC 002409FC 6C39884B */  vsub.xy    $vf5, $vf7, $vf8
    /* 140A00 00240A00 6C49A44B */  vsub.xyw   $vf5, $vf9, $vf4
    /* 140A04 00240A04 6C39894B */  vsub.xy    $vf5, $vf7, $vf9
    /* 140A08 00240A08 FF02004A */  vnop
    /* 140A0C 00240A0C FF02004A */  vnop
    /* 140A10 00240A10 FF02004A */  vnop
    /* 140A14 00240A14 FF02004A */  vnop
    /* 140A18 00240A18 FF02004A */  vnop
    /* 140A1C 00240A1C 00804248 */  cfc2.ni    $2, $vi16
    /* 140A20 00240A20 0800E003 */  jr         $31
    /* 140A24 00240A24 C0004230 */   andi      $2, $2, 0xC0
endlabel func_002409C8
```
