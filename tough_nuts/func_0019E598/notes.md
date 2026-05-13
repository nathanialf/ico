
---

## Attempt at 2026-05-12

**Reason parked:** early-exit + multiply: beq emits correctly now but v0/v1 swapped for mult operands

Seed: `tough_nuts/func_0019E598/09E598.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0019E598; check asm/matchings/cod/09E598/)
```

---

## Attempt at 2026-05-12

**Reason parked:** scheduler fills beq delay with lui v1 (target has nop); reg alloc v0/v1 swapped

Seed: `tough_nuts/func_0019E598/09E598.c.new`

Disassembly excerpt:

```
glabel func_0019E598
    /* 9E598 0019E598 0C00838C */  lw         $v1, 0xC($a0)
    /* 9E59C 0019E59C 1000828C */  lw         $v0, 0x10($a0)
    /* 9E5A0 0019E5A0 08006210 */  beq        $v1, $v0, .L0019E5C4
    /* 9E5A4 0019E5A4 00000000 */   nop
    /* 9E5A8 0019E5A8 0800838C */  lw         $v1, 0x8($a0)
    /* 9E5AC 0019E5AC 1500023C */  lui        $v0, (0x151800 >> 16)
    /* 9E5B0 0019E5B0 00184234 */  ori        $v0, $v0, (0x151800 & 0xFFFF)
    /* 9E5B4 0019E5B4 0000848C */  lw         $a0, 0x0($a0)
    /* 9E5B8 0019E5B8 18186200 */  mult       $v1, $v1, $v0
    /* 9E5BC 0019E5BC 0800E003 */  jr         $ra
    /* 9E5C0 0019E5C0 21108300 */   addu      $v0, $a0, $v1
.align 2
  .L0019E5C4:
    /* 9E5C4 0019E5C4 0800E003 */  jr         $ra
    /* 9E5C8 0019E5C8 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0019E598
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss: branch likely structure matches but reg alloc v0/v1 swap + delay slot fill

Seed: `tough_nuts/func_0019E598/09E598.c.new`

Disassembly excerpt:

```
glabel func_0019E598
    /* 9E598 0019E598 0C00838C */  lw         $v1, 0xC($a0)
    /* 9E59C 0019E59C 1000828C */  lw         $v0, 0x10($a0)
    /* 9E5A0 0019E5A0 08006210 */  beq        $v1, $v0, .L0019E5C4
    /* 9E5A4 0019E5A4 00000000 */   nop
    /* 9E5A8 0019E5A8 0800838C */  lw         $v1, 0x8($a0)
    /* 9E5AC 0019E5AC 1500023C */  lui        $v0, (0x151800 >> 16)
    /* 9E5B0 0019E5B0 00184234 */  ori        $v0, $v0, (0x151800 & 0xFFFF)
    /* 9E5B4 0019E5B4 0000848C */  lw         $a0, 0x0($a0)
    /* 9E5B8 0019E5B8 18186200 */  mult       $v1, $v1, $v0
    /* 9E5BC 0019E5BC 0800E003 */  jr         $ra
    /* 9E5C0 0019E5C0 21108300 */   addu      $v0, $a0, $v1
.align 2
  .L0019E5C4:
    /* 9E5C4 0019E5C4 0800E003 */  jr         $ra
    /* 9E5C8 0019E5C8 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0019E598
```

---

## Attempt at 2026-05-13

**Reason parked:** near-miss retry: gcc fills beq delay with lui, expected has nop

Seed: `tough_nuts/func_0019E598/09E598.c.new`

Disassembly excerpt:

```
glabel func_0019E598
    /* 9E598 0019E598 0C00838C */  lw         $v1, 0xC($a0)
    /* 9E59C 0019E59C 1000828C */  lw         $v0, 0x10($a0)
    /* 9E5A0 0019E5A0 08006210 */  beq        $v1, $v0, .L0019E5C4
    /* 9E5A4 0019E5A4 00000000 */   nop
    /* 9E5A8 0019E5A8 0800838C */  lw         $v1, 0x8($a0)
    /* 9E5AC 0019E5AC 1500023C */  lui        $v0, (0x151800 >> 16)
    /* 9E5B0 0019E5B0 00184234 */  ori        $v0, $v0, (0x151800 & 0xFFFF)
    /* 9E5B4 0019E5B4 0000848C */  lw         $a0, 0x0($a0)
    /* 9E5B8 0019E5B8 18186200 */  mult       $v1, $v1, $v0
    /* 9E5BC 0019E5BC 0800E003 */  jr         $ra
    /* 9E5C0 0019E5C0 21108300 */   addu      $v0, $a0, $v1
.align 2
  .L0019E5C4:
    /* 9E5C4 0019E5C4 0800E003 */  jr         $ra
    /* 9E5C8 0019E5C8 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0019E598
```
