# AttackCheckBoundaryBeforeFunc — fresh, rc9 beql-reorg + gp-rel addressing

VRAM 0x001B8D48. `p=a0->[0x164]; if(p && p->[0x30]<6) return D_004BA260[idx]; return &D_0062D388;`
Residual rc9, TWO permuter-class issues:
1. ROM `beql v0,zero` (branch-likely, annul-fills the `lui` of &D_0062D388) on the
   p==0 test; gcc emits plain `beq`+nop. Also the idx<6 branch is `bne` (ROM) vs
   `beq` (built) — inverted direction. Reorg-pass / branch-likely tail.
2. ROM addresses &D_0062D388 via `lui/addiu` (%hi/%lo); gcc uses `addiu v0,gp`
   (gp-relative). big-array decl, __asm__ alias, [N] sizing all FAILED to force
   %hi/%lo (~25 forms all rc9). gp-rel vs %hi/%lo cross-TU addressing.
Permuter target (reorg-tail, cf. permuter_cracks_reorg_tail memory).
## Fire 10: fresh; rc9 beql-reorg + gp-rel addressing; ~28 forms (early-return/goto/big-array/asm-alias/cmp/array-type) all rc9; 90s permuter no rc0 (best output drops null-check, rc9). (b)
