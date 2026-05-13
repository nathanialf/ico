
---

## Attempt at 2026-05-12

**Reason parked:** store order around tail-call differs; gcc puts sw a1,0(a0) in delay slot, expected has it first

Seed: `tough_nuts/func_0013C488/03C488.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013C488; check asm/matchings/cod/03C488/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: scheduler hoists all loads first; expected has sw a1,0 first

Seed: `tough_nuts/func_0013C488/03C488.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0013C488; check asm/matchings/cod/03C488/)
```

---

## Attempt at 2026-05-13

**Reason parked:** reg alloc swap: h[5] in v1 vs expected v0; multiple register swaps

Seed: `tough_nuts/func_0013C488/03C488.c.new`

Disassembly excerpt:

```
glabel func_0013C488
    /* 3C488 0013C488 000085AC */  sw         $a1, 0x0($a0)
    /* 3C48C 0013C48C 0A00A294 */  lhu        $v0, 0xA($a1)
    /* 3C490 0013C490 0200A694 */  lhu        $a2, 0x2($a1)
    /* 3C494 0013C494 0600A394 */  lhu        $v1, 0x6($a1)
    /* 3C498 0013C498 80100200 */  sll        $v0, $v0, 2
    /* 3C49C 0013C49C 80300600 */  sll        $a2, $a2, 2
    /* 3C4A0 0013C4A0 2110A200 */  addu       $v0, $a1, $v0
    /* 3C4A4 0013C4A4 2130A600 */  addu       $a2, $a1, $a2
    /* 3C4A8 0013C4A8 80180300 */  sll        $v1, $v1, 2
    /* 3C4AC 0013C4AC 2128A300 */  addu       $a1, $a1, $v1
    /* 3C4B0 0013C4B0 0C0082AC */  sw         $v0, 0xC($a0)
    /* 3C4B4 0013C4B4 080085AC */  sw         $a1, 0x8($a0)
    /* 3C4B8 0013C4B8 0800E003 */  jr         $ra
    /* 3C4BC 0013C4BC 040086AC */   sw        $a2, 0x4($a0)
endlabel func_0013C488
```
