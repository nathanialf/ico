
---

## Attempt at 2026-05-12

**Reason parked:** NaN check via union: structure matches but regalloc differs (mfc1 a0 vs v1, daddu missing)

Seed: `tough_nuts/func_002609E8/1609E8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_002609E8; check asm/matchings/cod/1609E8/)
```

---

## Attempt at 2026-05-12

**Reason parked:** isnan-bits: same instruction sequence but reg alloc differs (mfc1 a0 vs v1); ee-gcc 2.9 allocator stubborn

Seed: `tough_nuts/func_002609E8/1609E8.c.new`

Disassembly excerpt:

```
glabel func_002609E8
    /* 1609E8 002609E8 00600344 */  mfc1       $v1, $f12
    /* 1609EC 002609EC 2D106000 */  daddu      $v0, $v1, $zero
    /* 1609F0 002609F0 FF7F043C */  lui        $a0, (0x7FFFFFFF >> 16)
    /* 1609F4 002609F4 FFFF8434 */  ori        $a0, $a0, (0x7FFFFFFF & 0xFFFF)
    /* 1609F8 002609F8 807F033C */  lui        $v1, (0x7F800000 >> 16)
    /* 1609FC 002609FC 24104400 */  and        $v0, $v0, $a0
    /* 160A00 00260A00 23106200 */  subu       $v0, $v1, $v0
    /* 160A04 00260A04 0800E003 */  jr         $ra
    /* 160A08 00260A08 C2170200 */   srl       $v0, $v0, 31
endlabel func_002609E8
```
