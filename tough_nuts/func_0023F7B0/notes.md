
---

## Attempt at 2026-05-12

**Reason parked:** gcc emits 2-shift sign-extend instead of 4-shift cast chain

Seed: `tough_nuts/func_0023F7B0/13F7B0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0023F7B0; check asm/matchings/cod/13F7B0/)
```

---

## Attempt at 2026-05-13

**Reason parked:** gcc folds (int)(unsigned int) into single dsll32+dsra32; expected has dsll32/dsrl32 then dsll32/dsra32

Seed: `tough_nuts/func_0023F7B0/13F7B0.c.new`

Disassembly excerpt:

```
glabel func_0023F7B0
    /* 13F7B0 0023F7B0 3C280500 */  dsll32     $a1, $a1, 0
    /* 13F7B4 0023F7B4 53000224 */  addiu      $v0, $zero, 0x53
    /* 13F7B8 0023F7B8 3E280500 */  dsrl32     $a1, $a1, 0
    /* 13F7BC 0023F7BC 080082AC */  sw         $v0, 0x8($a0)
    /* 13F7C0 0023F7C0 3C280500 */  dsll32     $a1, $a1, 0
    /* 13F7C4 0023F7C4 3F280500 */  dsra32     $a1, $a1, 0
    /* 13F7C8 0023F7C8 10008224 */  addiu      $v0, $a0, 0x10
    /* 13F7CC 0023F7CC 000085AC */  sw         $a1, 0x0($a0)
    /* 13F7D0 0023F7D0 040080AC */  sw         $zero, 0x4($a0)
    /* 13F7D4 0023F7D4 0800E003 */  jr         $ra
    /* 13F7D8 0023F7D8 0C0080AC */   sw        $zero, 0xC($a0)
endlabel func_0023F7B0
```
