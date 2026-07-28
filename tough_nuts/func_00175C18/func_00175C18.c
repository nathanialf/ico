/* func_00175C18 - parked seed (CORRECTED TOPOLOGY, 2026-06-01).
 *
 * IMPORTANT: the previous rc9 seed (r=v chain) was SEMANTICALLY WRONG — on the
 * v!=0x45 path it returned v (raw sub->0x30) instead of 0 (the real fn's
 * `daddu v0,zero,zero`). It was a false floor that structurally could not reach
 * rc0. This seed is the semantically-correct && topology (rc11): bne + beq +
 * single shared jr, exactly matching the expected branch structure.
 *
 * Sole remaining defect (pure 3-cycle regalloc rotation, tag_diff §regalloc-swap;
 * instruction stream is byte-identical): the speculative delay-slot load
 * *(int*)(sub+0x30) coalesces into the dying $v1 (sub) base (`lw v1,48(v1)`)
 * instead of landing in $a0 (`lw a0,48(v1)`). That cascades: const 0x45 -> $v0
 * (should be $v1), result r -> $a0 + trailing `daddu v0,a0,zero` copy (should be
 * $v0, no copy).
 *
 * Hand levers exhausted on the CORRECT topology (~10 distinct, all rc11-13):
 * decl order, r-decl-pre-branch, ternary, nested-if, multi-return(17),
 * assignment-in-condition, goto-body(13), scratch-var reuse, lazy/eager cfg ptr.
 * Empirical finding: the load leaves $v1 ONLY under register pressure AT the load
 * (explicit cfg=D ptr held live -> load->$v0, rc12) but that hoists the Dptr
 * early (reorders, wrong). A lazy cfg loses the pressure and the coalesce
 * returns. To land the load in $a0 specifically, $v0 must also be busy at the
 * load (so it's steered to $a0, reserving $v0 for the return) — which needs the
 * flag value held live across the bnel, impossible without a semantic-changing
 * use or extra instruction. The historical match used REG("$4")(load)+REG("$2")(r)
 * scoped pins — both RETIRED. This is a graph-perturbation coloring tie =
 * permuter territory; the prior permuter shot ran on the WRONG seed, so the
 * permuter has never seen this correct topology. Seed it WITH --stop-on-zero. */

extern int D_00631AE8;
extern unsigned char D_002883D0[];

int func_00175C18(void)
{
    char *sub = *(char **)((char *)D_00631AE8 + 0x164);
    if (((*(unsigned long long *)(sub + 0x18) >> 36) & 1) == 0) {
        return 1;
    }
    {
        int v = *(int *)(sub + 0x30);
        int r = 0;
        if (v == 0x45 && (r = D_002883D0[0x5D]) != (r = 0)) {
            r = D_002883D0[0x58] == 0;
        }
        return r;
    }
}
