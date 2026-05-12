
---

## Attempt at 2026-05-12

**Reason parked:** flag-set: result allocated to a3 (expected) vs v1 (built); also 'result=0' in delay slot vs separate

Seed: `tough_nuts/func_001D40A0/0D40A0.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001D40A0; check asm/matchings/cod/0D40A0/)
```

---

## Attempt at 2026-05-12

**Reason parked:** boolean check: built uses bnel+movz folding; target uses sequential branches; condmove vs branches

Seed: `tough_nuts/func_001D40A0/0D40A0.c.new`

Disassembly excerpt:

```
glabel func_001D40A0
    /* D40A0 001D40A0 2D308000 */  daddu      $a2, $a0, $zero
    /* D40A4 001D40A4 5C01C48C */  lw         $a0, 0x15C($a2)
    /* D40A8 001D40A8 01000524 */  addiu      $a1, $zero, 0x1
    /* D40AC 001D40AC 0008828C */  lw         $v0, 0x800($a0)
    /* D40B0 001D40B0 0000438C */  lw         $v1, 0x0($v0)
    /* D40B4 001D40B4 04006510 */  beq        $v1, $a1, .L001D40C8
    /* D40B8 001D40B8 2D380000 */   daddu     $a3, $zero, $zero
    /* D40BC 001D40BC 6C01C28C */  lw         $v0, 0x16C($a2)
    /* D40C0 001D40C0 02004014 */  bnez       $v0, .L001D40CC
    /* D40C4 001D40C4 00000000 */   nop
.align 2
  .L001D40C8:
    /* D40C8 001D40C8 01000724 */  addiu      $a3, $zero, 0x1
.align 2
  .L001D40CC:
    /* D40CC 001D40CC 0800E003 */  jr         $ra
    /* D40D0 001D40D0 2D10E000 */   daddu     $v0, $a3, $zero
endlabel func_001D40A0
```
