# func_0024DE80 — parked

VRAM: 0x0024DE80 (file_off 0x14DE80)
Asm source: asm/aug6/nonmatchings/common/src/PObj/func_0024DE80.s

## Attempt at 2026-06-12

**Reason parked:** recovered from cancelled bulk campaign (matched, unverified-in-TU); re-verify before integrating

**TU:** `common/src/PObj.c`

**Seed:** `tough_nuts/func_0024DE80/func_0024DE80.c`

Disassembly:

```
.align 3
nonmatching func_0024DE80, 0x48

glabel func_0024DE80
    /* 14DE80 0024DE80 F0FFBD27 */  addiu      $29, $29, -0x10
    /* 14DE84 0024DE84 FF0F023C */  lui        $2, (0xFFFFFFF >> 16)
    /* 14DE88 0024DE88 0000BFFF */  sd         $31, 0x0($29)
    /* 14DE8C 0024DE8C FFFF4234 */  ori        $2, $2, (0xFFFFFFF & 0xFFFF)
    /* 14DE90 0024DE90 2428A200 */  and        $5, $5, $2
    /* 14DE94 0024DE94 0020033C */  lui        $3, (0x20000000 >> 16)
    /* 14DE98 0024DE98 4000878C */  lw         $7, 0x40($4)
    /* 14DE9C 0024DE9C 2528A300 */  or         $5, $5, $3
    /* 14DEA0 0024DEA0 01000224 */  addiu      $2, $0, 0x1
    /* 14DEA4 0024DEA4 B000E2AC */  sw         $2, 0xB0($7)
    /* 14DEA8 0024DEA8 D800E5AC */  sw         $5, 0xD8($7)
    /* 14DEAC 0024DEAC E400E6AC */  sw         $6, 0xE4($7)
    /* 14DEB0 0024DEB0 DC00E0AC */  sw         $0, 0xDC($7)
    /* 14DEB4 0024DEB4 9838090C */  jal        func_0024E260
    /* 14DEB8 0024DEB8 E000E0AC */   sw        $0, 0xE0($7)
    /* 14DEBC 0024DEBC 0000BFDF */  ld         $31, 0x0($29)
    /* 14DEC0 0024DEC0 0800E003 */  jr         $31
    /* 14DEC4 0024DEC4 1000BD27 */   addiu     $29, $29, 0x10
endlabel func_0024DE80
```
