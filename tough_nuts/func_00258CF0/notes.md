# func_00258CF0 — parked

VRAM: 0x00258CF0 (file offset 0x158CF0)
Asm source: asm/cod/158CEC.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** mult/shift order vs ee-gcc 2.9 emit

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_00258CF0
    /* 158CF0 00258CF0 7200033C */  lui        $v1, %hi(D_0071C6C0)
    /* 158CF4 00258CF4 00110500 */  sll        $v0, $a1, 4
    /* 158CF8 00258CF8 C0C66324 */  addiu      $v1, $v1, %lo(D_0071C6C0)
    /* 158CFC 00258CFC 00230400 */  sll        $a0, $a0, 12
    /* 158D00 00258D00 21104300 */  addu       $v0, $v0, $v1
    /* 158D04 00258D04 0800E003 */  jr         $ra
    /* 158D08 00258D08 21108200 */   addu      $v0, $a0, $v0
endlabel func_00258CF0
```
