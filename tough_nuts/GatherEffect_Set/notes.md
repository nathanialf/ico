# GatherEffect_Set (ito/src/gather_effect) — rc12, strength-reduce class

Purpose: "is the gather effect finished?" query. p = InitParticleLayoutGeo(a0)
(= D_007030C0[a0].w[5], a runtime ptr to the particle-data block); OR every
entry's field-0 (entries=p->0x24, count=p->0x30, stride 0x70); return acc==0.
Special: a0<0 -> 1; p==0 -> 1 (direct).

## Best clean shape = rc12 (this seed)
goto-CFG, base-read-before-count (sinks base past the guard -> PLAIN `blez`,
not annulled `blezl`), stride-reassign keeps the per-iter MULT (non-loop-
invariant stride defeats the GIV). This is an improvement over the prior rc13
park (the blezl is fixed at rc12).

## Sole residual root: stride REGISTER cascade (pin-class)
ROM: count=a3, base=a2, stride=v0 (re-materialised each iter, REUSING the dead
`p`=v0 after count/base are read). Mine: count=a2, base=t0, stride=a3 (the
mult-keeping hoisted stride is long-lived -> a3, with a doubled addiu; never
reuses v0). To get stride into v0 the cookbook §3.10 recipe uses ANCHOR(i)+REG
pins (BANNED here).

## Dev-folder evidence (why this is hard, not a quick miss)
- particleLayout.c func_001E6070 (`for(i){p=&D_007030C0[i]; p->w[..]}`) is
  MATCHED and STRENGTH-REDUCES to a walking ptr (`addiu $16,$16,0x18`). So this
  dev's runtime/multi-use loops DO strength-reduce.
- itou_boss.c:674 `D_006CCE60[i*0x40+4]` keeps the mult — but that base is a
  GLOBAL (constant addr, cookbook clean direct-index). GatherEffect's base is a
  RUNTIME ptr (p->0x24), so the clean global-index trick does NOT apply.
- 7+ funcs parked for this same root (func_001C6398, correctJumpOrientByChain,
  scpPlayStart, GatherEffect_Proc, tex_makeTexturePacket, FlagDL). Repo-wide
  unsolved "gcc strength-reduces vs ROM keeps per-iter mult, NON-GLOBAL base".

## Tried (all fold to strength-reduced or stride-reassign-a3)
plain i*0x70, int*[i*28], 2D-array, struct PLEnt, reuse-p (count=a3 but adds
v0->a2 copy), reuse-p-as-stride, base-inline, stride top-of-body, count-inline,
int* p[9]/p[12], mult operand order. NOT a cflag (-fno-strength-reduce is a
crutch; cookbook says it's the wrong tool).

## Next: a clean shape exists (user-asserted). Likely a register-pressure /
operand-lifetime reshape that lands the in-loop stride constant in v0 (reusing
dead p) without the hoisted long-lived stride. Permuter only after a genuine
stall>=30 (do NOT force the gate).
