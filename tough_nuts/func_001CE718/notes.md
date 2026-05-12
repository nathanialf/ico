
---

## Attempt at 2026-05-08

**Reason parked:** float clamp 0..1: ee-gcc emits 16 insns; original 17 (uses v1=v0 copy + b/swc1 for first clamp)

Seed: `tough_nuts/func_001CE718/0CE718.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001CE718; check asm/matchings/cod/0CE718/)
```

---

## Attempt at 2026-05-12

**Reason parked:** float clamp: target uses daddu v1,v0,0 to split p across two halves, builds use single v0; also missing FPU hazard nop before bc1tl

Seed: `tough_nuts/func_001CE718/0CE718.c.new`

Disassembly excerpt:

```
glabel func_001CE718
    /* CE718 001CE718 5C01828C */  lw         $v0, 0x15C($a0)
    /* CE71C 001CE71C 00008044 */  mtc1       $zero, $f0
    /* CE720 001CE720 4008428C */  lw         $v0, 0x840($v0)
    /* CE724 001CE724 34600046 */  c.lt.s     $f12, $f0
    /* CE728 001CE728 2D184000 */  daddu      $v1, $v0, $zero
    /* CE72C 001CE72C 02000045 */  bc1f       .L001CE738
    /* CE730 001CE730 30004CE4 */   swc1      $f12, 0x30($v0)
    /* CE734 001CE734 300040E4 */  swc1       $f0, 0x30($v0)
.align 2
  .L001CE738:
    /* CE738 001CE738 300060C4 */  lwc1       $f0, 0x30($v1)
    /* CE73C 001CE73C 803F013C */  lui        $at, (0x3F800000 >> 16)
    /* CE740 001CE740 00088144 */  mtc1       $at, $f1
    /* CE744 001CE744 34080046 */  c.lt.s     $f1, $f0
    /* CE748 001CE748 00000000 */  nop
    /* CE74C 001CE74C 01000345 */  bc1tl      .L001CE754
    /* CE750 001CE750 300061E4 */   swc1      $f1, 0x30($v1)
.align 2
  .L001CE754:
    /* CE754 001CE754 0800E003 */  jr         $ra
    /* CE758 001CE758 00000000 */   nop
endlabel func_001CE718
```
