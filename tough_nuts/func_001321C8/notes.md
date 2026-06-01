# func_001321C8 — near-miss rc51 (iosCdvdMgrReadDir)

VRAM 0x001321C8  TU ios/cdvd.c (111 insns, frame 0x1d0). Seed = full TU at rc51.
ALGORITHM + FRAME correct. Drove rc54->51 following the regimen.

## Progress this pass
- **count cluster CRACKED**: `if (count-- <= 0) return 1;` (post-decrement in the
  test) gives the ROM's "copy count, count-1, blez original, store count-1".
  This cleared blk1 (rc54->51).
- `name = self+0x34` AFTER the count check (clears block 0).

## Remaining: ONE cluster (blk2) — loop-invariant hoist register assignment
ROM hoists (in loop-preheader): name=$19, %hi(D_00556A10)=$30, namebuf(sp+0x20)
=$21, %hi(D_00631F70)=$23, %hi(D_0027E528)=$22, sizebuf(sp+0x124)=$20.
rc51 (D_tbl_0027E520 form): self CORRECT($18) but does NOT hoist %hi(A10)
(computes it inline) and DOES hoist an extra %hi(D_0027E520)=$22, shifting
E528->$23, F70->$30, and swapping namebuf/sizebuf into $20/$21. 6 diffs.

## The fork (both are ~6-diff local optima)
- D_tbl_0027E520[n].f0/.f1 (rc51): self right, extra E520 hi-reg -> buffer swap.
- single base D_0027E528[n*0x30]-8 / -4 with SEPARATE store/read addr (no shared
  `e`): removes E520 (rc65) BUT shifts self $18->$19. `e`-shared was worse (rc77).

## Next levers (fresh eyes)
- The real ROM uses the SINGLE D_0027E528 base (id/size at -8/-4 = D_0027E520[n]);
  D_tbl form can't reach rc0. Need single-base + get %hi(A10) hoisted + keep self
  in $18. The A10-not-hoisted + self-shift are the two coupled blockers.
- Try forcing %hi(D_00556A10) into a callee-saved reg; investigate why F70 hoists
  but A10 (first func_00264DF8) doesn't (entry sp+0 3rd-arg interaction?).
- NOT a floor. Pure LICM/regalloc hoist. Regimen verified: count cluster cracked.
