
---

## Attempt at 2026-05-12

**Reason parked:** operation order around tail-call differs; sd in delay slot vs not

Seed: `tough_nuts/func_001325D8/0325D8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001325D8; check asm/matchings/cod/0325D8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: instruction scheduling — sd in middle vs jr delay slot

Seed: `tough_nuts/func_001325D8/0325D8.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001325D8; check asm/matchings/cod/0325D8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** retry: REG pin v1 + fno-sched still gives wrong reg alloc

Seed: `tough_nuts/func_001325D8/0325D8.c.new`

Disassembly excerpt:

```
glabel func_001325D8
    /* 325D8 001325D8 2D188000 */  daddu      $v1, $a0, $zero
    /* 325DC 001325DC 01000224 */  addiu      $v0, $zero, 0x1
    /* 325E0 001325E0 040062AC */  sw         $v0, 0x4($v1)
    /* 325E4 001325E4 FEFF0724 */  addiu      $a3, $zero, -0x2
    /* 325E8 001325E8 0100A830 */  andi       $t0, $a1, 0x1
    /* 325EC 001325EC 2800043C */  lui        $a0, %hi(D_0027E4C0)
    /* 325F0 001325F0 000062DC */  ld         $v0, 0x0($v1)
    /* 325F4 001325F4 C0E48424 */  addiu      $a0, $a0, %lo(D_0027E4C0)
    /* 325F8 001325F8 2D286000 */  daddu      $a1, $v1, $zero
    /* 325FC 001325FC 2D300000 */  daddu      $a2, $zero, $zero
    /* 32600 00132600 24104700 */  and        $v0, $v0, $a3
    /* 32604 00132604 25104800 */  or         $v0, $v0, $t0
    /* 32608 00132608 6EE90408 */  j          func_0013A5B8
    /* 3260C 0013260C 000062FC */   sd        $v0, 0x0($v1)
endlabel func_001325D8
```
