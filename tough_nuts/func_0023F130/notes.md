
---

## Attempt at 2026-05-12

**Reason parked:** v0 vs v1 reg alloc for mask; sw zero,12 scheduling differs

Seed: `tough_nuts/func_0023F130/13F130.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023F130; check asm/matchings/cod/13F130/)
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: gcc uses v1 vs expected v0 for low-32 extract; same shape

Seed: `tough_nuts/func_0023F130/13F130.c.new`

Disassembly excerpt:

```
glabel func_0023F130
    /* 13F130 0023F130 FFFF023C */  lui        $v0, (0xFFFF0000 >> 16)
    /* 13F134 0023F134 3E100200 */  dsrl32     $v0, $v0, 0
    /* 13F138 0023F138 080085AC */  sw         $a1, 0x8($a0)
    /* 13F13C 0023F13C 2410C200 */  and        $v0, $a2, $v0
    /* 13F140 0023F140 0C0080AC */  sw         $zero, 0xC($a0)
    /* 13F144 0023F144 3C100200 */  dsll32     $v0, $v0, 0
    /* 13F148 0023F148 3F100200 */  dsra32     $v0, $v0, 0
    /* 13F14C 0023F14C 3F300600 */  dsra32     $a2, $a2, 0
    /* 13F150 0023F150 000082AC */  sw         $v0, 0x0($a0)
    /* 13F154 0023F154 10008224 */  addiu      $v0, $a0, 0x10
    /* 13F158 0023F158 0800E003 */  jr         $ra
    /* 13F15C 0023F15C 040086AC */   sw        $a2, 0x4($a0)
endlabel func_0023F130
```
