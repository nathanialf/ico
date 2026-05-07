# func_001AA580 — parked

VRAM: 0x001AA580 (file offset 0x0AA580)
Asm source: asm/cod/0AA57C.s

## Attempt at 2026-05-07 — re-park (no .c seed preserved)

**Reason parked:** v0=0 placement vs ee-gcc 2.9 emit

**Note:** previous near-miss .c attempt was reverted+deleted before this
session's policy update; the original seed is not recoverable. Permuter
must start from scratch on this one. Reason recorded above is from
operator memory of the failure mode.

Disassembly excerpt:

```
glabel func_001AA580
    /* AA580 001AA580 E0FFBD27 */  addiu      $sp, $sp, -0x20
    /* AA584 001AA584 90A3848F */  lw         $a0, %gp_rel(D_00632C80)($gp)
    /* AA588 001AA588 0000B0FF */  sd         $s0, 0x0($sp)
    /* AA58C 001AA58C 2D100000 */  daddu      $v0, $zero, $zero
    /* AA590 001AA590 FFFF1024 */  addiu      $s0, $zero, -0x1
    /* AA594 001AA594 04009010 */  beq        $a0, $s0, .L001AA5A8
    /* AA598 001AA598 1000BFFF */   sd        $ra, 0x10($sp)
    /* AA59C 001AA59C 821D090C */  jal        func_00247608
    /* AA5A0 001AA5A0 90A390AF */   sw        $s0, %gp_rel(D_00632C80)($gp)
    /* AA5A4 001AA5A4 90A390AF */  sw         $s0, %gp_rel(D_00632C80)($gp)
.align 2
  .L001AA5A8:
    /* AA5A8 001AA5A8 1000BFDF */  ld         $ra, 0x10($sp)
    /* AA5AC 001AA5AC 0000B0DF */  ld         $s0, 0x0($sp)
    /* AA5B0 001AA5B0 0800E003 */  jr         $ra
    /* AA5B4 001AA5B4 2000BD27 */   addiu     $sp, $sp, 0x20
endlabel func_001AA580
```

---

## Attempt at 2026-05-07

**Reason parked:** v0=0 (return val) emitted late vs expected early; tried explicit 'int rv=0' lift but compiler still re-orders the materialize-zero past the call

Seed: `tough_nuts/func_001AA580/0AA580.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001AA580; check asm/matchings/cod/0AA580/)
```
