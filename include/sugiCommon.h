/*
 * include/sugiCommon.h — the `sugipon` programmer's shared header.
 *
 * PROVENANCE.  The 2002-01-16 PAL listing (`baserom/pal/SRCFILE.TXT`, an
 * `objdump -dl` of the disc's `main.elf`; see decomp/pal_source_tree.md)
 * records 84 expansions of `sugipon/include/sugiCommon.h` across six
 * programmer directories.  Its dev path was
 * `sugipon/include/sugiCommon.h`, reached from other programmers' dirs as
 * `../sugipon/include/sugiCommon.h`; this repo has no per-programmer source
 * dirs, so it lives in `include/`.
 *
 * Instructions attributed to a `.h` are a header body expanded into the
 * caller, so every distinct `first_line..last_line` range below is a
 * separate `static` helper.  NAMES: none of these helpers is ever emitted
 * out of line, so none has a symbol in `baserom/pal/MAIN.MAP` — every name
 * here is OUR descriptive choice, not the developer's.  (`checkOverThePlane`
 * is NOT one of them: the census lists it under this header because its
 * first instruction row is the inlined line-71 helper, but its own body
 * rows are in `sugipon/src/clothAnimation.c:1086`, so it is a
 * clothAnimation.c static that *calls* the helper.)
 *
 * Bodies were re-derived from the disassembly of the ROM we build against.
 * Only `plane_distance` is proven byte-identical (it is factored out of four
 * matched hosts and re-gated); the rest are reconstructions whose hosts are
 * all still INCLUDE_ASM, kept here so the matcher knows the helper exists
 * and does not re-invent it per TU.  See decomp/HEADERS.md.
 */
#ifndef SUGICOMMON_H
#define SUGICOMMON_H

#include "vu0.h"

/* --- header lines 45-48 -------------------------------------------------
 * A one-call wrapper around the engine RNG.  Census: the `jal _GetRandom`
 * of 39 hosts is attributed to line 47 (ACTParaStatus_Exec, actCommonCling,
 * EnemyCtrlBeforeFunc, GetFlyPosition, InitBirdGeo, LightLineGeo, ...).
 * RECONSTRUCTION — no matched host yet. */
extern float _GetRandom(void);

static __inline__ float random_unit(void)
{
    return _GetRandom();
}

/* --- header lines 53-56 -------------------------------------------------
 * `random_unit()` mapped to -1..+1.  Census line 55 (`add.s f,f,f` then
 * `sub.s f,f,1.0`) always co-occurs with a line-47 `jal _GetRandom` in the
 * same host (13 hosts): SetLayoutedPoolReflactionMesh, SetLimitedPoolReflactionMesh,
 * _setParticleEffect, InitStormPackage, UpdateStormPackage, InitWormGeo,
 * GetWormRoute, InitLightLineGeo, InitBoxGeo, MotionViewer, calcBlur,
 * FloorLeverGeo, WallLeverGeo.  RECONSTRUCTION — no matched host yet. */
static __inline__ float random_signed(void)
{
    return random_unit() * 2.0f - 1.0f;
}

/* --- header lines 58-61 -------------------------------------------------
 * The libc-RNG variant.  Census line 60 (playSERandomID, execEff,
 * setWaterDot): `jal rand; sra v0,v0,4; andi v0,0xFFFF; cvt.s.w; mul.s` by
 * a .lit4 float.  That float is 0x37800080 in the ROM we build against
 * (retail PAL D_006394E4, read out of baserom/pal/baseelf.elf) = 1/65535.
 * RECONSTRUCTION — no matched host yet. */
extern int rand(void);

static __inline__ float crt_random_unit(void)
{
    return (float)((rand() >> 4) & 0xFFFF) * (1.0f / 65535.0f);
}

/* --- header lines 63-66 -------------------------------------------------
 * A SECOND -1..+1 helper, textually distinct from the line-53 one but with
 * the identical body: census line 65 emits the same `add.s`/`sub.s 1.0`
 * pair and likewise co-occurs with a line-47 `jal _GetRandom` (never with
 * line 60).  Hosts: EntryWaterDot, scpBornSpider, InitSpiderLayoutGeo,
 * WeaponGeo, ExecWindManager.  We do not know how the developer's two
 * spellings differed; the two line ranges are the only evidence that there
 * are two.  RECONSTRUCTION — no matched host yet. */
static __inline__ float random_signed_b(void)
{
    return random_unit() * 2.0f - 1.0f;
}

/* --- header lines 69-72 -------------------------------------------------
 * Signed distance from a point to a plane: dot(plane.xyz, pos.xyz) + plane.w,
 * evaluated on VU0 in macro mode.  vf1 <- pos (first argument), vf2 <- plane.
 *
 * PROVEN.  28 line-71 expansions in the census, 8 instructions each, always
 * this sequence.  Factored out of four MATCHED hosts and re-gated
 * byte-identical: GetProjectionPosOfPlane / GetProjectionOfPlane /
 * GetProjectionOfPlaneWithKeepAway (src/geometryManager) and
 * checkOverThePlane (src/clothAnimation).  A fifth matched host,
 * GetOutOutsideOfWall (src/motionManager2), keeps the body hand-expanded —
 * see decomp/HEADERS.md for the inliner mechanism that costs it one
 * instruction.  Line 69 is the helper's declaration line: hosts that show a
 * bare line-69 row (getParallelWindVector, clipCylinderCollision) have the
 * argument-address arithmetic attributed there. */
static __inline__ float plane_distance(const void *pos, const void *plane)
{
    float d;
    int t;
    VU0_LSV_R(lqc2, 1, 0x0, pos);
    VU0_LSV_R(lqc2, 2, 0x0, plane);
    VU0_V3OP(vmul.xyz, 3, 1, 2);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    VU0_V3OP_BC(vaddw.x, 3, 3, 2, w);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(d) : "r"(t));
    return d;
}

/* --- header lines 85-88 -------------------------------------------------
 * Squared distance between two points (xyz).  Census line 87, 8 instructions:
 * `vsub.wxyz vf3,vf1,vf2; vmul.xyz vf3,vf3,vf3; vaddy.x; vaddz.x; qmfc2;
 * mtc1`.  Hosts (22): EnemyCheckHit, CheckEnemyHit, checkWallState,
 * emergencyCheck.495, execPositionReserver, fitToCol, subAP1BrainMain,
 * DispGameOverEffect, onPathInitialize, GetChainCollision, GirlForceFieldDL,
 * ReviveCarryableItemsWithBoundary, checkCliffState, GetNearestOfLayoutSpiders,
 * CheckSpidersInsideOfReviveRange, CheckTorchChainReaction(+Reverse),
 * procChainReaction, CheckSwapableWeapon, flyCoreLoop.  Line 85 carries the
 * argument-address arithmetic.  RECONSTRUCTION — no matched host yet. */
static __inline__ float distance_squared(const void *a, const void *b)
{
    float d;
    int t;
    VU0_LSV_R(lqc2, 1, 0x0, a);
    VU0_LSV_R(lqc2, 2, 0x0, b);
    VU0_V3OP(vsub.wxyz, 3, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(d) : "r"(t));
    return d;
}

/* --- header lines 95-98 -------------------------------------------------
 * A SECOND squared-distance helper: census line 97 emits the identical
 * 8-instruction sequence.  Its one host, GetBoxHoldPoint (src/box), shows
 * rows at BOTH 87 and 97, so the two are distinct definitions rather than
 * one range.  RECONSTRUCTION — no matched host yet. */
static __inline__ float distance_squared_b(const void *a, const void *b)
{
    float d;
    int t;
    VU0_LSV_R(lqc2, 1, 0x0, a);
    VU0_LSV_R(lqc2, 2, 0x0, b);
    VU0_V3OP(vsub.wxyz, 3, 1, 2);
    VU0_V3OP(vmul.xyz, 3, 3, 3);
    VU0_V3OP_BC(vaddy.x, 3, 3, 3, y);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(d) : "r"(t));
    return d;
}

/* --- header lines 100-103 ----------------------------------------------
 * Squared distance in the XZ plane: `vmul.xz` + a single `vaddz.x`, 7
 * instructions.  ONE census host (clip_wall_1, src/fieldCollision, line 102)
 * — kept because the sequence is unambiguous, but it is a one-host
 * RECONSTRUCTION and no matched host exists. */
static __inline__ float distance_squared_xz(const void *a, const void *b)
{
    float d;
    int t;
    VU0_LSV_R(lqc2, 1, 0x0, a);
    VU0_LSV_R(lqc2, 2, 0x0, b);
    VU0_V3OP(vsub.wxyz, 3, 1, 2);
    VU0_V3OP(vmul.xz, 3, 3, 3);
    VU0_V3OP_BC(vaddz.x, 3, 3, 3, z);
    __asm__ __volatile__("qmfc2.ni %0, $vf3" : "=r"(t));
    __asm__ __volatile__("mtc1 %1, %0" : "=f"(d) : "r"(t));
    return d;
}

/* --- header lines 115-120 ----------------------------------------------
 * Byte-sum checksum over a buffer.  Census: line 115 = argument setup,
 * line 118 = the guard/counter (`blez`, `addiu -1`, `bnez`) and the
 * accumulator's zero-init, line 119 = `lbu` / pointer bump / `addu`.
 * Hosts: ReadSkeltonFile and CSVSYSTEM_ReadCharFiles (src/charFileManager).
 * RECONSTRUCTION — no matched host yet. */
static __inline__ int byte_checksum(const unsigned char *p, int n)
{
    int sum;
    for (sum = 0; n > 0; n--) {
        sum += *p++;
    }
    return sum;
}

#endif /* SUGICOMMON_H */
