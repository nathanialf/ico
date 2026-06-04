# func_0023BAF0 — parked

VRAM: 0x0023BAF0 (file_off 0x13BAF0)
Asm source: asm/aug6/nonmatchings/ito/mpeg/mv_vibuf/func_0023BAF0.s

## Attempt at 2026-06-04

**Reason parked:** best rc3 (clean) / rc12 both-halves seed saved. ROM = zero-ext(dsll32;dsrl32) THEN sign-ext(dsll32;dsra32) of single-use a1.low32, store low+0x1A+0+0, return a0+0x10. §5.11 redundant-canon: combine folds zext+sext in EVERY value-equiv single-use C (rc3-6); opaque DImode AND survives via inliner but emits and-mask not ROM shift (rc5); DImode shift always folds even in inline helper (rc4); multi-use both-halves keeps the exact zext+sext shifts (rc12) but gcc over-schedules 2 extra extension chains. Permuter-class like PrintGObjID/GetRealModelId. Seed = both-halves rc12 (right shift structure, needs reorder to drop extras).

**TU:** `ito/mpeg/mv_vibuf.c`

**Seed:** `tough_nuts/func_0023BAF0/func_0023BAF0.c`

Disassembly:

```
.align 3
nonmatching func_0023BAF0, 0x2C

glabel func_0023BAF0
    /* 13BAF0 0023BAF0 3C280500 */  dsll32     $5, $5, 0
    /* 13BAF4 0023BAF4 1A000224 */  addiu      $2, $0, 0x1A
    /* 13BAF8 0023BAF8 3E280500 */  dsrl32     $5, $5, 0
    /* 13BAFC 0023BAFC 080082AC */  sw         $2, 0x8($4)
    /* 13BB00 0023BB00 3C280500 */  dsll32     $5, $5, 0
    /* 13BB04 0023BB04 3F280500 */  dsra32     $5, $5, 0
    /* 13BB08 0023BB08 10008224 */  addiu      $2, $4, 0x10
    /* 13BB0C 0023BB0C 000085AC */  sw         $5, 0x0($4)
    /* 13BB10 0023BB10 040080AC */  sw         $0, 0x4($4)
    /* 13BB14 0023BB14 0800E003 */  jr         $31
    /* 13BB18 0023BB18 0C0080AC */   sw        $0, 0xC($4)
endlabel func_0023BAF0
    /* 13BB1C 0023BB1C 00000000 */  nop
```
