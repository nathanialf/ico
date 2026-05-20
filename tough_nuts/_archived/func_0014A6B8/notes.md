
---

## Attempt at 2026-05-12

**Reason parked:** bit-check: srl fixed via unsigned cast; branch direction at end inverts (built bne v0,zero,+40 vs target beq); functional equiv

Seed: `tough_nuts/func_0014A6B8/04A6B8.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_0014A6B8; check asm/matchings/cod/04A6B8/)
```

---

## Attempt at 2026-05-13

**Reason parked:** beql vs bne branch-likely; reg alloc a0 vs v1 for table index

Seed: `tough_nuts/func_0014A6B8/04A6B8.c.new`

Disassembly excerpt:

```
glabel func_0014A6B8
    /* 4A6B8 0014A6B8 F491828F */  lw         $v0, %gp_rel(D_00631AE4)($gp)
    /* 4A6BC 0014A6BC 0E008214 */  bne        $a0, $v0, .L0014A6F8
    /* 4A6C0 0014A6C0 6401858C */   lw        $a1, 0x164($a0)
    /* 4A6C4 0014A6C4 3000A48C */  lw         $a0, 0x30($a1)
    /* 4A6C8 0014A6C8 50000224 */  addiu      $v0, $zero, 0x50
    /* 4A6CC 0014A6CC 5600033C */  lui        $v1, %hi(D_0055CFD8)
    /* 4A6D0 0014A6D0 18208200 */  mult       $a0, $a0, $v0
    /* 4A6D4 0014A6D4 D8CF6324 */  addiu      $v1, $v1, %lo(D_0055CFD8)
    /* 4A6D8 0014A6D8 21208300 */  addu       $a0, $a0, $v1
    /* 4A6DC 0014A6DC 4C00828C */  lw         $v0, 0x4C($a0)
    /* 4A6E0 0014A6E0 42120200 */  srl        $v0, $v0, 9
    /* 4A6E4 0014A6E4 01004230 */  andi       $v0, $v0, 0x1
    /* 4A6E8 0014A6E8 03004010 */  beqz       $v0, .L0014A6F8
    /* 4A6EC 0014A6EC 00000000 */   nop
    /* 4A6F0 0014A6F0 0800E003 */  jr         $ra
    /* 4A6F4 0014A6F4 8001A28C */   lw        $v0, 0x180($a1)
.align 2
  .L0014A6F8:
    /* 4A6F8 0014A6F8 0800E003 */  jr         $ra
    /* 4A6FC 0014A6FC 2D100000 */   daddu     $v0, $zero, $zero
endlabel func_0014A6B8
```
