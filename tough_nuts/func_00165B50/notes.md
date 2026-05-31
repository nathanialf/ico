# func_00165B50 (enemy_act) — near-miss, STRUCTURE PERFECT, 1-reg rotation

void func_00165B50(char *self, int a1, int *a2) — conditional setter.
WORKING C (structure 100% match, only regalloc rotation remains):
  *(int*)(*(int*)(*(int*)(self+0x164)+0x670)+0x200) = a1;   // unconditional (beq delay)
  if (a2 != 0) { v = a2[0];  <dup final store> }
  else         { v = D_00632390; <dup final store> }
  // final store DUPLICATED into each branch -> gcc gives the per-branch self->0x164 reloads + `b` merge
Final store: *(int*)(*(int*)(*(int*)(self+0x164)+0x670)+0x20C) = v;
REMAINING DIFF (rc~5): value `v` lands in a2 (built, `lw a2,0(a2)` reuse-base) vs a0 (expected,
`lw a0,0(a2)` reuse-dead-self-arg); reload self->0x164 v1 vs v0. Pure regalloc tie-break.
Same "reuse the dead arg reg" wall as func_0014B2F0/func_0014A0A8 (return-reg-swap). Needs REG pin or
a clean lever not yet found. Permuter/offline candidate.
