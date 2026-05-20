
---

## Attempt at 2026-05-12

**Reason parked:** low-32 widen wrapper: gcc optimizes (int)(unsigned)a1 to single sign-ext; expected has 4-insn zero-ext+sign-ext dance

Seed: `tough_nuts/func_0023F5D0/13F5D0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023F5D0; check asm/matchings/cod/13F5D0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** missing dsll+dsrl canonicalization at entry; ee-gcc 2.9 folds when (int)cast is direct use

Seed: `tough_nuts/func_0023F5D0/13F5D0.c.new`

Disassembly excerpt:

```
glabel func_0023F5D0
    /* 13F5D0 0023F5D0 3C280500 */  dsll32     $a1, $a1, 0
    /* 13F5D4 0023F5D4 1A000224 */  addiu      $v0, $zero, 0x1A
    /* 13F5D8 0023F5D8 3E280500 */  dsrl32     $a1, $a1, 0
    /* 13F5DC 0023F5DC 080082AC */  sw         $v0, 0x8($a0)
    /* 13F5E0 0023F5E0 3C280500 */  dsll32     $a1, $a1, 0
    /* 13F5E4 0023F5E4 3F280500 */  dsra32     $a1, $a1, 0
    /* 13F5E8 0023F5E8 10008224 */  addiu      $v0, $a0, 0x10
    /* 13F5EC 0023F5EC 000085AC */  sw         $a1, 0x0($a0)
    /* 13F5F0 0023F5F0 040080AC */  sw         $zero, 0x4($a0)
    /* 13F5F4 0023F5F4 0800E003 */  jr         $ra
    /* 13F5F8 0023F5F8 0C0080AC */   sw        $zero, 0xC($a0)
endlabel func_0023F5D0
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: redundant zero-extend then sign-extend pattern hard to drive from C

Seed: `tough_nuts/func_0023F5D0/13F5D0.c.new`

Disassembly excerpt:

```
glabel func_0023F5D0
    /* 13F5D0 0023F5D0 3C280500 */  dsll32     $a1, $a1, 0
    /* 13F5D4 0023F5D4 1A000224 */  addiu      $v0, $zero, 0x1A
    /* 13F5D8 0023F5D8 3E280500 */  dsrl32     $a1, $a1, 0
    /* 13F5DC 0023F5DC 080082AC */  sw         $v0, 0x8($a0)
    /* 13F5E0 0023F5E0 3C280500 */  dsll32     $a1, $a1, 0
    /* 13F5E4 0023F5E4 3F280500 */  dsra32     $a1, $a1, 0
    /* 13F5E8 0023F5E8 10008224 */  addiu      $v0, $a0, 0x10
    /* 13F5EC 0023F5EC 000085AC */  sw         $a1, 0x0($a0)
    /* 13F5F0 0023F5F0 040080AC */  sw         $zero, 0x4($a0)
    /* 13F5F4 0023F5F4 0800E003 */  jr         $ra
    /* 13F5F8 0023F5F8 0C0080AC */   sw        $zero, 0xC($a0)
endlabel func_0023F5D0
```
