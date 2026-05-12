
---

## Attempt at 2026-05-12

**Reason parked:** 2-way dispatch: gcc emits stack frame + jal+j mixed; expected has no frame + 2 j

Seed: `tough_nuts/func_001E8598/0E8598.c`

Disassembly excerpt:

```
(no asm/cod/*.s found for func_001E8598; check asm/matchings/cod/0E8598/)
```

---

## Attempt at 2026-05-12

**Reason parked:** table lookup + dispatch: target recomputes entry addr in delay slot; reg alloc differs

Seed: `tough_nuts/func_001E8598/0E8598.c.new`

Disassembly excerpt:

```
glabel func_001E8598
    /* E8598 001E8598 0D008004 */  bltz       $a0, .L001E85D0
    /* E859C 001E859C 18000224 */   addiu     $v0, $zero, 0x18
    /* E85A0 001E85A0 7100033C */  lui        $v1, %hi(D_007097F0)
    /* E85A4 001E85A4 18208200 */  mult       $a0, $a0, $v0
    /* E85A8 001E85A8 F0976724 */  addiu      $a3, $v1, %lo(D_007097F0)
    /* E85AC 001E85AC 21108700 */  addu       $v0, $a0, $a3
    /* E85B0 001E85B0 0000438C */  lw         $v1, 0x0($v0)
    /* E85B4 001E85B4 04006014 */  bnez       $v1, .L001E85C8
    /* E85B8 001E85B8 2110E400 */   addu      $v0, $a3, $a0
    /* E85BC 001E85BC 6200043C */  lui        $a0, %hi(D_00619E40)
    /* E85C0 001E85C0 8A9B0608 */  j          func_001A6E28
    /* E85C4 001E85C4 409E8424 */   addiu     $a0, $a0, %lo(D_00619E40)
.align 2
  .L001E85C8:
    /* E85C8 001E85C8 5A9B0708 */  j          func_001E6D68
    /* E85CC 001E85CC 1400448C */   lw        $a0, 0x14($v0)
.align 2
  .L001E85D0:
    /* E85D0 001E85D0 0800E003 */  jr         $ra
    /* E85D4 001E85D4 00000000 */   nop
endlabel func_001E8598
```
