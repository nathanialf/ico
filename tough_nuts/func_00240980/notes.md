# func_00240980 — parked

VRAM: 0x00240980 (file_off 0x140980)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_00240980.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_00240980/func_00240980.c`

Disassembly:

```
.align 3
nonmatching func_00240980, 0x48

glabel func_00240980
    /* 140980 00240980 2C01E04B */  vsub.xyzw  $vf4, $vf0, $vf0
    /* 140984 00240984 8045023C */  lui        $2, (0x45800000 >> 16)
    /* 140988 00240988 38140200 */  dsll       $2, $2, 16
    /* 14098C 0024098C 80454234 */  ori        $2, $2, 0x4580
    /* 140990 00240990 38140200 */  dsll       $2, $2, 16
    /* 140994 00240994 000087D8 */  lqc2       $vf7, 0x0($4)
    /* 140998 00240998 0030A248 */  qmtc2.ni   $2, $vf6
    /* 14099C 0024099C 0080C048 */  ctc2.ni    $0, $vi16
    /* 1409A0 002409A0 6C39A44B */  vsub.xyw   $vf5, $vf7, $vf4
    /* 1409A4 002409A4 6C31874B */  vsub.xy    $vf5, $vf6, $vf7
    /* 1409A8 002409A8 FF02004A */  vnop
    /* 1409AC 002409AC FF02004A */  vnop
    /* 1409B0 002409B0 FF02004A */  vnop
    /* 1409B4 002409B4 FF02004A */  vnop
    /* 1409B8 002409B8 FF02004A */  vnop
    /* 1409BC 002409BC 00804248 */  cfc2.ni    $2, $vi16
    /* 1409C0 002409C0 0800E003 */  jr         $31
    /* 1409C4 002409C4 C0004230 */   andi      $2, $2, 0xC0
endlabel func_00240980
```
