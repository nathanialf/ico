# PrintGObjID — parked

VRAM: 0x0023BCD0 (file_off 0x13BCD0)
Asm source: asm/aug6/nonmatchings/common/src/GobjProc/PrintGObjID.s

## Attempt at 2026-06-04

**Reason parked:** rc3 §5.11 canon floor. Stores 'S'(0x53)@+8, sign_ext(zero_ext(low32(a1)))@+0, 0@+4/+0xC, ret a0+0x10. ROM keeps a REDUNDANT zero-ext(dsll32/dsrl32)+sign-ext(dsll32/dsra32) on a1; gcc FOLDS it in ALL value-equivalent C (~30 forms: literal double-shift, two-temp, casts, masks, struct-by-value, store-orders) to a single sign-ext. Seed: ull a1; ull t=(uint)a1; *(int*)=(int)t. Permuter-class (non-equivalent rewrite). next-verdict park 30/30 for offline auto_permute.

**TU:** `common/src/GobjProc.c`

**Seed:** `tough_nuts/PrintGObjID/PrintGObjID.c`

Disassembly:

```
.align 3
nonmatching PrintGObjID, 0x2C

glabel PrintGObjID
    /* 13BCD0 0023BCD0 3C280500 */  dsll32     $5, $5, 0
    /* 13BCD4 0023BCD4 53000224 */  addiu      $2, $0, 0x53
    /* 13BCD8 0023BCD8 3E280500 */  dsrl32     $5, $5, 0
    /* 13BCDC 0023BCDC 080082AC */  sw         $2, 0x8($4)
    /* 13BCE0 0023BCE0 3C280500 */  dsll32     $5, $5, 0
    /* 13BCE4 0023BCE4 3F280500 */  dsra32     $5, $5, 0
    /* 13BCE8 0023BCE8 10008224 */  addiu      $2, $4, 0x10
    /* 13BCEC 0023BCEC 000085AC */  sw         $5, 0x0($4)
    /* 13BCF0 0023BCF0 040080AC */  sw         $0, 0x4($4)
    /* 13BCF4 0023BCF4 0800E003 */  jr         $31
    /* 13BCF8 0023BCF8 0C0080AC */   sw        $0, 0xC($4)
endlabel PrintGObjID
    /* 13BCFC 0023BCFC 00000000 */  nop
```
