
---

## Attempt at 2026-05-12

**Reason parked:** gcc emits beql (likely-eq) instead of bne; functionally equiv but different encoding

Seed: `tough_nuts/func_00144208/044208.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00144208; check asm/matchings/cod/044208/)
```

---

## Attempt at 2026-05-12

**Reason parked:** gcc emits beql for both branch-on-eq and branch-on-ne forms; bne not selected

Seed: `tough_nuts/func_00144208/044208.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00144208; check asm/matchings/cod/044208/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: gcc emits beql + a1 store, expected bne + v0=a2+v1 recomputed

Seed: `tough_nuts/func_00144208/044208.c.new`

Disassembly excerpt:

```
glabel func_00144208
    /* 44208 00144208 6B00023C */  lui        $v0, %hi(D_006A98B0)
    /* 4420C 0014420C FF008330 */  andi       $v1, $a0, 0xFF
    /* 44210 00144210 B0984624 */  addiu      $a2, $v0, %lo(D_006A98B0)
    /* 44214 00144214 80190300 */  sll        $v1, $v1, 6
    /* 44218 00144218 21286600 */  addu       $a1, $v1, $a2
    /* 4421C 0014421C 1000A284 */  lh         $v0, 0x10($a1)
    /* 44220 00144220 05004004 */  bltz       $v0, .L00144238
    /* 44224 00144224 03220400 */   sra       $a0, $a0, 8
    /* 44228 00144228 0000A294 */  lhu        $v0, 0x0($a1)
    /* 4422C 0014422C 02008214 */  bne        $a0, $v0, .L00144238
    /* 44230 00144230 2110C300 */   addu      $v0, $a2, $v1
    /* 44234 00144234 18004CE4 */  swc1       $f12, 0x18($v0)
.align 2
  .L00144238:
    /* 44238 00144238 0800E003 */  jr         $ra
    /* 4423C 0014423C 00000000 */   nop
endlabel func_00144208
```
