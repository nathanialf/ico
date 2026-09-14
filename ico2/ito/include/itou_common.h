/*
 * include/itou_common.h — the `ito` programmer's shared header.
 *
 * PROVENANCE.  `baserom/pal/SRCFILE.TXT` attributes instructions inside five
 * functions to `ito/include/itou_common.h` (census: decomp/pal_source_tree.md,
 * section "ito/../ito/include/itou_common.h"):
 *   line 26 — subBirdBrainMain (src/act_bird), QueenBarrierGeo (src/queen),
 *             GatherEffect_Proc (src/gather_effect), DrawLightning2
 *             (src/lightning)                                  29 rows total
 *   line 31 — vector_angle_degree (src/act_bird), subBirdBrainMain
 *                                                              3 rows total
 * Two distinct line ranges = two `static` helpers.  Neither is ever emitted
 * out of line, so neither has a MAIN.MAP symbol: BOTH NAMES BELOW ARE OURS,
 * chosen to describe what the instructions do.
 *
 * The header's dev path is `ito/include/itou_common.h`; this repo has no
 * per-programmer source dirs, so it lives in `include/`.  Unlike
 * `ito/include/mv_defs.h` nothing here bakes a `__FILE__` literal, so the
 * include spelling is not load-bearing.
 */
#ifndef ITOU_COMMON_H
#define ITOU_COMMON_H

/* --- header lines ~24-27 ------------------------------------------------
 * Degrees to radians.  Census line 26: `lwc1 <2pi lit4>; mul.s; mtc1 360.0;
 * div.s` — the multiply by the .lit4 2*pi comes first, then the divide by
 * the immediate 360.0 (0x43B40000).  RECONSTRUCTION: every host is still
 * INCLUDE_ASM, so this body is derived from the ROM's instruction sequence
 * (4 hosts, same sequence) and is not yet proven byte-identical. */
static __inline__ float degrees_to_radians(float deg)
{
    return deg * 6.2831855f / 360.0f;
}

/* --- header lines ~29-32 ------------------------------------------------
 * Radians to degrees — the inverse, with the operands swapped: census line
 * 31 is `mtc1 360.0; mul.s; lwc1 <2pi lit4>; div.s`.
 * PROVEN in one host: src/act_bird's `vector_angle_degree` is matched and
 * its tail is exactly this helper (census row itou_common.h:31), so it now
 * calls this function and re-gates byte-identical. */
static __inline__ float radians_to_degrees(float rad)
{
    return rad * 360.0f / 6.2831855f;
}

#endif /* ITOU_COMMON_H */
