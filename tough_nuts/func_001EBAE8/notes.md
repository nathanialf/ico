
---

## Attempt at 2026-05-11

**Reason parked:** near-miss: schedule of sw a0/sw a2 in jr-ra delay slot differs from gcc default

Seed: `tough_nuts/func_001EBAE8/0EBAE8.c`

Disassembly excerpt:

```
glabel func_001EBAE8
    /* EBAE8 001EBAE8 14AD868F */  lw         $a2, %gp_rel(D_00633604)($gp)
    /* EBAEC 001EBAEC 7100033C */  lui        $v1, %hi(D_0070C9C8)
    /* EBAF0 001EBAF0 C8C96324 */  addiu      $v1, $v1, %lo(D_0070C9C8)
    /* EBAF4 001EBAF4 1CAD85AF */  sw         $a1, %gp_rel(D_0063360C)($gp)
    /* EBAF8 001EBAF8 80100600 */  sll        $v0, $a2, 2
    /* EBAFC 001EBAFC 21104300 */  addu       $v0, $v0, $v1
    /* EBB00 001EBB00 0100C624 */  addiu      $a2, $a2, 0x1
    /* EBB04 001EBB04 000044AC */  sw         $a0, 0x0($v0)
    /* EBB08 001EBB08 0800E003 */  jr         $ra
    /* EBB0C 001EBB0C 14AD86AF */   sw        $a2, %gp_rel(D_00633604)($gp)
endlabel func_001EBAE8
```
