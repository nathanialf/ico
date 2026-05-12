
---

## Attempt at 2026-05-12

**Reason parked:** zero-loop matches; trailing sw zero,0(gp) emitted TWICE (before jr + delay slot fill) — gcc duplicates the store

Seed: `tough_nuts/func_001B0538/0B0538.c`

Disassembly excerpt:

```
glabel func_001B0538
    /* B0538 001B0538 7000023C */  lui        $v0, %hi(D_00706110)
    /* B053C 001B053C 1D000324 */  addiu      $v1, $zero, 0x1D
    /* B0540 001B0540 10614224 */  addiu      $v0, $v0, %lo(D_00706110)
    /* B0544 001B0544 A0034224 */  addiu      $v0, $v0, 0x3A0
.align 2
  .L001B0548:
    /* B0548 001B0548 000040AC */  sw         $zero, 0x0($v0)
    /* B054C 001B054C FFFF6324 */  addiu      $v1, $v1, -0x1
    /* B0550 001B0550 E0FF4224 */  addiu      $v0, $v0, -0x20
    /* B0554 001B0554 00000000 */  nop
    /* B0558 001B0558 00000000 */  nop
    /* B055C 001B055C FAFF6104 */  bgez       $v1, .L001B0548
    /* B0560 001B0560 00000000 */   nop
    /* B0564 001B0564 7CB580AF */  sw         $zero, %gp_rel(D_00633E6C)($gp)
    /* B0568 001B0568 0800E003 */  jr         $ra
    /* B056C 001B056C 80B580AF */   sw        $zero, %gp_rel(D_00633E70)($gp)
endlabel func_001B0538
```

---

## Attempt at 2026-05-12

**Reason parked:** clear loop: missing 2 nop pipeline-fillers in loop body + addiu split for address

Seed: `tough_nuts/func_001B0538/0B0538.c.new`

Disassembly excerpt:

```
glabel func_001B0538
    /* B0538 001B0538 7000023C */  lui        $v0, %hi(D_00706110)
    /* B053C 001B053C 1D000324 */  addiu      $v1, $zero, 0x1D
    /* B0540 001B0540 10614224 */  addiu      $v0, $v0, %lo(D_00706110)
    /* B0544 001B0544 A0034224 */  addiu      $v0, $v0, 0x3A0
.align 2
  .L001B0548:
    /* B0548 001B0548 000040AC */  sw         $zero, 0x0($v0)
    /* B054C 001B054C FFFF6324 */  addiu      $v1, $v1, -0x1
    /* B0550 001B0550 E0FF4224 */  addiu      $v0, $v0, -0x20
    /* B0554 001B0554 00000000 */  nop
    /* B0558 001B0558 00000000 */  nop
    /* B055C 001B055C FAFF6104 */  bgez       $v1, .L001B0548
    /* B0560 001B0560 00000000 */   nop
    /* B0564 001B0564 7CB580AF */  sw         $zero, %gp_rel(D_00633E6C)($gp)
    /* B0568 001B0568 0800E003 */  jr         $ra
    /* B056C 001B056C 80B580AF */   sw        $zero, %gp_rel(D_00633E70)($gp)
endlabel func_001B0538
```
