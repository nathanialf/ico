
---

## Attempt at 2026-05-12

**Reason parked:** copysign: mfc1 reg differs; gcc allocates a1/v1 for input regs differently

Seed: `tough_nuts/func_00260B70/160B70.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00260B70; check asm/matchings/cod/160B70/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: copysign — gcc reg alloc swaps; needs inline asm

Seed: `tough_nuts/func_00260B70/160B70.c.new`

Disassembly excerpt:

```
glabel func_00260B70
    /* 160B70 00260B70 00600544 */  mfc1       $a1, $f12
    /* 160B74 00260B74 00680444 */  mfc1       $a0, $f13
    /* 160B78 00260B78 2D188000 */  daddu      $v1, $a0, $zero
    /* 160B7C 00260B7C FF7F023C */  lui        $v0, (0x7FFFFFFF >> 16)
    /* 160B80 00260B80 FFFF4234 */  ori        $v0, $v0, (0x7FFFFFFF & 0xFFFF)
    /* 160B84 00260B84 0080043C */  lui        $a0, (0x80000000 >> 16)
    /* 160B88 00260B88 2428A200 */  and        $a1, $a1, $v0
    /* 160B8C 00260B8C 24186400 */  and        $v1, $v1, $a0
    /* 160B90 00260B90 2528A300 */  or         $a1, $a1, $v1
    /* 160B94 00260B94 00008544 */  mtc1       $a1, $f0
    /* 160B98 00260B98 0800E003 */  jr         $ra
    /* 160B9C 00260B9C 00000000 */   nop
endlabel func_00260B70
```
