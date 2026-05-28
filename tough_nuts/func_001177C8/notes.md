# func_001177C8 — parked

VRAM: 0x001177C8 (file_off 0x0177C8)
Asm source: asm/nonmatchings/src/Light/func_001177C8.s

## Attempt at 2026-05-28

**Reason parked:** rc 7 PURE branch-likely near-miss. List walk: head=D_00633C34 (int holding ptr), next at 0x98, field at 0x90. Calls func_00115068(node) for each node where 0<=node->f90<3. SOLVED structure: nested-if (if(v<3) if(v>=0)) gives the signed slti+bltz the original uses -- a plain 'v<3 && v>=0' COLLAPSES to a single sltiu(v,3) (unsigned range check, drops the bltz). RESIDUAL: the inner v>=0 check is bltzl (branch-likely, advance annulled) but the original is plain bltz (call-arg daddu a0,s0 fills the bltz delay; advance duplicated per exit path + a 'beq zero,zero' skip). 4 distinct structures (for-loop / nested-if / do-while / explicit per-path-advance goto) ALL emit bltzl -- it is ee-gcc 2.9's branch-likely heuristic for a conditional-call loop, not a source-shape issue (conditional call can't hoist the arg to the loop top per cookbook 3.4, so reorg annuls the advance). beql (v>=3) and bnel (loop) already match; only the bltz differs + its cascade. Permuter food / known gcc floor per [[branch_likely_emission]].

**TU:** `src/Light.c`

**Seed:** `tough_nuts/func_001177C8/func_001177C8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_00633C34, 1

.align 3
nonmatching func_001177C8, 0x58

glabel func_001177C8
    /* 177C8 001177C8 E0FFBD27 */  addiu      $29, $29, -0x20
    /* 177CC 001177CC 0000B0FF */  sd         $16, 0x0($29)
    /* 177D0 001177D0 44B3908F */  lw         $16, (D_00633C34) /* gp_rel: (D_00633C34) */
    /* 177D4 001177D4 0E000012 */  beqz       $16, .L00117810
    /* 177D8 001177D8 1000BFFF */   sd        $31, 0x10($29)
    /* 177DC 001177DC 9000038E */  lw         $3, 0x90($16)
.align 2
  .L001177E0:
    /* 177E0 001177E0 03006228 */  slti       $2, $3, 0x3
    /* 177E4 001177E4 08004050 */  beql       $2, $0, .L00117808
    /* 177E8 001177E8 9800108E */   lw        $16, 0x98($16)
    /* 177EC 001177EC 05006004 */  bltz       $3, .L00117804
    /* 177F0 001177F0 2D200002 */   daddu     $4, $16, $0
    /* 177F4 001177F4 1A54040C */  jal        func_00115068
    /* 177F8 001177F8 9800108E */   lw        $16, 0x98($16)
    /* 177FC 001177FC 02000010 */  b          .L00117808
    /* 17800 00117800 00000000 */   nop
.align 2
  .L00117804:
    /* 17804 00117804 9800108E */  lw         $16, 0x98($16)
.align 2
  .L00117808:
    /* 17808 00117808 F5FF0056 */  bnel       $16, $0, .L001177E0
    /* 1780C 0011780C 9000038E */   lw        $3, 0x90($16)
.align 2
  .L00117810:
    /* 17810 00117810 1000BFDF */  ld         $31, 0x10($29)
    /* 17814 00117814 0000B0DF */  ld         $16, 0x0($29)
    /* 17818 00117818 0800E003 */  jr         $31
    /* 1781C 0011781C 2000BD27 */   addiu     $29, $29, 0x20
endlabel func_001177C8
```
