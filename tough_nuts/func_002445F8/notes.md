
---

## Attempt at 2026-05-12

**Reason parked:** gcc reuses a1 as loop counter; expected uses v0 separate. just register names differ

Seed: `tough_nuts/func_002445F8/1445F8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_002445F8; check asm/matchings/cod/1445F8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** loop body has 2 internal nops + trailing align nop; gcc scheduler doesn't insert; needs branch alignment flag

Seed: `tough_nuts/func_002445F8/1445F8.c.new`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_002445F8; check asm/matchings/cod/1445F8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** very close: body matches with inline nops; trailing alignment nop placed wrong

Seed: `tough_nuts/func_002445F8/1445F8.c.new`

Disassembly excerpt:

```
glabel func_002445F8
    /* 1445F8 002445F8 0A00A010 */  beqz       $a1, .L00244624
    /* 1445FC 002445FC FFFFA224 */   addiu     $v0, $a1, -0x1
    /* 144600 00244600 FFFF0324 */  addiu      $v1, $zero, -0x1
    /* 144604 00244604 00000000 */  nop
.align 2
  .L00244608:
    /* 144608 00244608 000080A0 */  sb         $zero, 0x0($a0)
    /* 14460C 0024460C FFFF4224 */  addiu      $v0, $v0, -0x1
    /* 144610 00244610 01008424 */  addiu      $a0, $a0, 0x1
    /* 144614 00244614 00000000 */  nop
    /* 144618 00244618 00000000 */  nop
    /* 14461C 0024461C FAFF4314 */  bne        $v0, $v1, .L00244608
    /* 144620 00244620 00000000 */   nop
.align 2
  .L00244624:
    /* 144624 00244624 0800E003 */  jr         $ra
    /* 144628 00244628 00000000 */   nop
endlabel func_002445F8
```
