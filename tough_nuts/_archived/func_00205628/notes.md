
---

## Attempt at 2026-05-12

**Reason parked:** linked-list insert: regalloc + setup reordering

Seed: `tough_nuts/func_00205628/105628.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_00205628; check asm/matchings/cod/105628/)
```

---

## Attempt at 2026-05-12

**Reason parked:** linked-list insert: int return adds daddu v0,zero but scheduling order differs

Seed: `tough_nuts/func_00205628/105628.c.new`

Disassembly excerpt:

```
glabel func_00205628
    /* 105628 00205628 34000224 */  addiu      $v0, $zero, 0x34
    /* 10562C 0020562C 4D00063C */  lui        $a2, %hi(D_004CAEC0)
    /* 105630 00205630 18208200 */  mult       $a0, $a0, $v0
    /* 105634 00205634 4D00033C */  lui        $v1, %hi(D_004CC1E0)
    /* 105638 00205638 C0AEC624 */  addiu      $a2, $a2, %lo(D_004CAEC0)
    /* 10563C 0020563C E0C16324 */  addiu      $v1, $v1, %lo(D_004CC1E0)
    /* 105640 00205640 80290500 */  sll        $a1, $a1, 6
    /* 105644 00205644 2D100000 */  daddu      $v0, $zero, $zero
    /* 105648 00205648 2128A300 */  addu       $a1, $a1, $v1
    /* 10564C 0020564C 21208600 */  addu       $a0, $a0, $a2
    /* 105650 00205650 0800A0AC */  sw         $zero, 0x8($a1)
    /* 105654 00205654 0800868C */  lw         $a2, 0x8($a0)
    /* 105658 00205658 080085AC */  sw         $a1, 0x8($a0)
    /* 10565C 0020565C 0800C38C */  lw         $v1, 0x8($a2)
    /* 105660 00205660 0C00A3AC */  sw         $v1, 0xC($a1)
    /* 105664 00205664 0800E003 */  jr         $ra
    /* 105668 00205668 0800C5AC */   sw        $a1, 0x8($a2)
endlabel func_00205628
```
