# cut_gobj_dl_link — parked

VRAM: 0x0013E738 (file_off 0x03E738)
Asm source: asm/aug6/nonmatchings/fumi/isys/gobj_dl/cut_gobj_dl_link.s

## Attempt at 2026-06-10

**Reason parked:** best rc14 mult-at-top structure: INSTRUCTION-IDENTICAL to target (full-pin diagnostic count=$8/i=$6/base=$7/stride=$2/unk0=$3 -> byte-exact). Residual is PURE conflict-graph regalloc: clean source packs stride+elem into one reg (5 regs); target separates elem->a1 (6 regs, count spills to t0). 30+ clean shapes all land at rc14 (loop-carried 'stride=0x174' bottom-reassign defeats strength-reduction = cookbook 3.10 lever A; i=0 in beq-delay = lever C done clean). Lever B (unk0 reuse mult-reg forcing elem->a1) is the unsolved domino - needs stride in v0 via global-alloc, which packing prevents. Permuter-class: find the source perturbation that makes stride conflict with elem.

**TU:** `fumi/isys/gobj_dl.c`

**Seed:** `tough_nuts/cut_gobj_dl_link/cut_gobj_dl_link.c`

Disassembly:

```
.align 3
nonmatching cut_gobj_dl_link, 0x54

glabel cut_gobj_dl_link
    /* 3E738 0013E738 BCB3888F */  lw         $8, %gp_rel(D_0062BFAC)($28)
    /* 3E73C 0013E73C 11000011 */  beqz       $8, .L0013E784
    /* 3E740 0013E740 2D300000 */   daddu     $6, $0, $0
    /* 3E744 0013E744 B8B3878F */  lw         $7, %gp_rel(D_0062BFA8)($28)
    /* 3E748 0013E748 74010224 */  addiu      $2, $0, 0x174
    /* 3E74C 0013E74C 00000000 */  nop
.align 2
  .L0013E750:
    /* 3E750 0013E750 1818C200 */  mult       $3, $6, $2
    /* 3E754 0013E754 21286700 */  addu       $5, $3, $7
    /* 3E758 0013E758 0000A38C */  lw         $3, 0x0($5)
    /* 3E75C 0013E75C 06006010 */  beqz       $3, .L0013E778
    /* 3E760 0013E760 0100C624 */   addiu     $6, $6, 0x1
    /* 3E764 0013E764 0400A28C */  lw         $2, 0x4($5)
    /* 3E768 0013E768 04004414 */  bne        $2, $4, .L0013E77C
    /* 3E76C 0013E76C 2B10C800 */   sltu      $2, $6, $8
    /* 3E770 0013E770 0800E003 */  jr         $31
    /* 3E774 0013E774 2D10A000 */   daddu     $2, $5, $0
.align 2
  .L0013E778:
    /* 3E778 0013E778 2B10C800 */  sltu       $2, $6, $8
.align 2
  .L0013E77C:
    /* 3E77C 0013E77C F4FF4014 */  bnez       $2, .L0013E750
    /* 3E780 0013E780 74010224 */   addiu     $2, $0, 0x174
.align 2
  .L0013E784:
    /* 3E784 0013E784 0800E003 */  jr         $31
    /* 3E788 0013E788 2D100000 */   daddu     $2, $0, $0
endlabel cut_gobj_dl_link
    /* 3E78C 0013E78C 00000000 */  nop
```
