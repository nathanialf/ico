# func_001FBFC8 — parked

VRAM: 0x001FBFC8 (file_off 0x0FBFC8)
Asm source: asm/nonmatchings/src/EnemyInit/func_001FBFC8.s

## Attempt at 2026-05-31

**Reason parked:** rc18 doubly-linked-list REMOVE + null-assert. K&R def (callers pass both 1 and 4 args -> must be K&R, matching extern void func_001FBFC8()). Structure: if(a0==0){func_001A6E28(D_0061AC80);return;} next=a0->0x38; prev=a0->0x34; if(next)next->0x34=prev; if(a0->0x34)(a0->0x34)->0x38=a0->0x38; if((uint)a0==D_006321D4(head,uint))D_006321D4=a0->0x34; if(a0==D_006321D8(tail,int*))D_006321D8=a0->0x38. MULTI-WALL: (1) bnel branch-likely for the a0!=0 assert AND the next!=0 check (delay holds the annulled body load) — gcc emits beq/bne, see [[branch_likely_emission]]; (2) gp_rel access to in-TU D_006321D4 shows raw -16384(gp) vs ROM's %gp_rel (in-TU sdata gp_rel mismatch); (3) v0/v1 reg alloc. Sibling func_001FC220 has the same assert (matched). Needs branch-likely + gp_rel levers / permuter. NOT a floor, stall 1.

**TU:** `src/EnemyInit.c`

**Seed:** `tough_nuts/func_001FBFC8/func_001FBFC8.c`

Disassembly:

```
/* Symbols accessed via $gp register */
.extern D_006321D8, 1
.extern D_006321D4, 1

.align 3
nonmatching func_001FBFC8, 0x78

glabel func_001FBFC8
    /* FBFC8 001FBFC8 04008054 */  bnel       $4, $0, .L001FBFDC
    /* FBFCC 001FBFCC 3800838C */   lw        $3, 0x38($4)
    /* FBFD0 001FBFD0 6200043C */  lui        $4, %hi(D_0061AC80)
    /* FBFD4 001FBFD4 8A9B0608 */  j          func_001A6E28
    /* FBFD8 001FBFD8 80AC8424 */   addiu     $4, $4, %lo(D_0061AC80)
.align 2
  .L001FBFDC:
    /* FBFDC 001FBFDC 06006054 */  bnel       $3, $0, .L001FBFF8
    /* FBFE0 001FBFE0 3400828C */   lw        $2, 0x34($4)
    /* FBFE4 001FBFE4 3400838C */  lw         $3, 0x34($4)
    /* FBFE8 001FBFE8 0A006010 */  beqz       $3, .L001FC014
    /* FBFEC 001FBFEC E498828F */   lw        $2, (D_006321D4) /* gp_rel: (D_006321D4) */
    /* FBFF0 001FBFF0 03000010 */  b          .L001FC000
    /* FBFF4 001FBFF4 00000000 */   nop
.align 2
  .L001FBFF8:
    /* FBFF8 001FBFF8 340062AC */  sw         $2, 0x34($3)
    /* FBFFC 001FBFFC 3400838C */  lw         $3, 0x34($4)
.align 2
  .L001FC000:
    /* FC000 001FC000 04006010 */  beqz       $3, .L001FC014
    /* FC004 001FC004 E498828F */   lw        $2, (D_006321D4) /* gp_rel: (D_006321D4) */
    /* FC008 001FC008 3800828C */  lw         $2, 0x38($4)
    /* FC00C 001FC00C 380062AC */  sw         $2, 0x38($3)
    /* FC010 001FC010 E498828F */  lw         $2, (D_006321D4) /* gp_rel: (D_006321D4) */
.align 2
  .L001FC014:
    /* FC014 001FC014 04008214 */  bne        $4, $2, .L001FC028
    /* FC018 001FC018 E898828F */   lw        $2, (D_006321D8) /* gp_rel: (D_006321D8) */
    /* FC01C 001FC01C 3400828C */  lw         $2, 0x34($4)
    /* FC020 001FC020 E49882AF */  sw         $2, (D_006321D4) /* gp_rel: (D_006321D4) */
    /* FC024 001FC024 E898828F */  lw         $2, (D_006321D8) /* gp_rel: (D_006321D8) */
.align 2
  .L001FC028:
    /* FC028 001FC028 03008214 */  bne        $4, $2, .L001FC038
    /* FC02C 001FC02C 00000000 */   nop
    /* FC030 001FC030 3800828C */  lw         $2, 0x38($4)
    /* FC034 001FC034 E89882AF */  sw         $2, (D_006321D8) /* gp_rel: (D_006321D8) */
.align 2
  .L001FC038:
    /* FC038 001FC038 0800E003 */  jr         $31
    /* FC03C 001FC03C 00000000 */   nop
endlabel func_001FBFC8
```
