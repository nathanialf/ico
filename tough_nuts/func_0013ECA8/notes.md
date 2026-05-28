# func_0013ECA8 — parked

VRAM: 0x0013ECA8 (file_off 0x03ECA8)
Asm source: asm/nonmatchings/isys/gobj/func_0013ECA8.s

## Attempt at 2026-05-28

**Reason parked:** rc 7 near-miss. Structure FULLY correct: single-IV pointer search (stride 0x174, base=D_00633CA0 ptr, count=D_00633CA4), plain bne BOTH branches, correct shifted bound (base+(count-1)*stride via byte-offset count*0x174-0x174), count==0 guard. Cracked the bnel->bne (CFG-mirror p=base-1/end/guard forces increment-first rotation, NOT natural for-loop which pipelines the load=bnel) and the end-offset computation order (explicit byte-offset). RESIDUAL (7): end lands in a1 vs a0 -- gcc keeps base in a0 for p=base 'daddu a0' which forces end->a1, whereas original frees a0 (p=base via 'addiu v1,v1,372' from base-stride) reusing a0 for end. Cascades to beq/bne v1,a1 vs v1,a0. Plus bnez delay nop vs 'daddu v0,v1' (return-copy). RULED OUT (20+ iters): pin end=$4 / pin r=$2 both rescramble the count/base load order; ANCHOR forces a BB split (unconditional branch); decl-swap and increment-first while scramble regalloc; volatile field kills delay-fill; int-index gives blez+slt+counter; lag-temp gives a spurious 2nd advancing IV (dual not single). Pure regalloc/sched tail -> permuter.

**TU:** `isys/gobj.c`

**Seed:** `tough_nuts/func_0013ECA8/func_0013ECA8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633CA0, 1
.extern D_00633CA4, 1

.align 3
nonmatching func_0013ECA8, 0x4C

glabel func_0013ECA8
    /* 3ECA8 0013ECA8 B4B3828F */  lw         $2, (D_00633CA4) /* gp_rel: (D_00633CA4) */
    /* 3ECAC 0013ECAC 74010324 */  addiu      $3, $0, 0x174
    /* 3ECB0 0013ECB0 B0B3848F */  lw         $4, (D_00633CA0) /* gp_rel: (D_00633CA0) */
    /* 3ECB4 0013ECB4 18104300 */  mult       $2, $2, $3
    /* 3ECB8 0013ECB8 8CFE8324 */  addiu      $3, $4, -0x174
    /* 3ECBC 0013ECBC 8CFE4224 */  addiu      $2, $2, -0x174
    /* 3ECC0 0013ECC0 21208200 */  addu       $4, $4, $2
    /* 3ECC4 0013ECC4 07006410 */  beq        $3, $4, .L0013ECE4
    /* 3ECC8 0013ECC8 74016324 */   addiu     $3, $3, 0x174
    /* 3ECCC 0013ECCC 00000000 */  nop
.align 2
  .L0013ECD0:
    /* 3ECD0 0013ECD0 0000628C */  lw         $2, 0x0($3)
    /* 3ECD4 0013ECD4 05004014 */  bnez       $2, .L0013ECEC
    /* 3ECD8 0013ECD8 2D106000 */   daddu     $2, $3, $0
    /* 3ECDC 0013ECDC FCFF6414 */  bne        $3, $4, .L0013ECD0
    /* 3ECE0 0013ECE0 74016324 */   addiu     $3, $3, 0x174
.align 2
  .L0013ECE4:
    /* 3ECE4 0013ECE4 0800E003 */  jr         $31
    /* 3ECE8 0013ECE8 2D100000 */   daddu     $2, $0, $0
.align 2
  .L0013ECEC:
    /* 3ECEC 0013ECEC 0800E003 */  jr         $31
    /* 3ECF0 0013ECF0 00000000 */   nop
endlabel func_0013ECA8
    /* 3ECF4 0013ECF4 00000000 */  nop
```
