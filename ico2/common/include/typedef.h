/*
 * common/include/typedef.h, the `common` programmer's shared header.
 *
 * PROVENANCE.  Dev path `common/include/typedef.h`, reached from `fumi/` as
 * `../common/include/typedef.h`.  `baserom/pal/SRCFILE.TXT` attributes
 * instructions to exactly one of its lines (census:
 * docs/pal_source_tree.md, section `fumi/../common/include/typedef.h`):
 *
 *   line 74, avoid_obstacle2 (src/way_sys, 0x0017DA50), 3 rows / 2 expansions
 *
 * so the header holds at least one `static` helper besides whatever typedefs
 * its name implies.  Instructions from a MACRO expansion would be attributed
 * to the caller's line, not to line 74, so line 74 is a function.
 *
 * WHAT IS IN HERE AND ON WHAT EVIDENCE.  Three classes, marked individually:
 *
 *   (a) the line-74 helper slot, fixed by the listing.  Reserved below and
 *       still empty; see the TODO there.
 *
 *   (b) the cross-programmer engine object shapes (GObj, Sub15C, Obj7F0,
 *       GeoNode, GeoSub) and the GOBJ_SUB accessor.  PLACEMENT BY INCLUDE
 *       PATTERN, NOT BY LISTING ROWS: a struct declaration emits no
 *       instructions, so no listing row can name its home.  They are used by
 *       37 TUs spanning common, fumi, ito, seki, sugipon and fumi/sound, and
 *       this is the only header the disc attests that every one of those
 *       trees reaches (`-I../common/include` is in every ico2 TU's search
 *       order).  The shapes themselves are mechanical, recovered from load
 *       offsets by tools/dump_all_struct_shapes.py; only add a field with a
 *       verified access.
 *
 *   (c) the R5900 and VU0 macro-mode opcode wrappers.  PLACEMENT BY INCLUDE
 *       PATTERN, NOT BY LISTING ROWS: every one of their expansions is
 *       attributed by SRCFILE.TXT to the .c line that invokes it, which is
 *       what a macro expansion looks like and is therefore consistent with
 *       any header home, including one the listing cannot see.  They are
 *       used across seki (Matrix, BgAnimation, GifPacket), sugipon
 *       (clothAnimation, matrixDrive, quaternion, motionManager2, stormTest,
 *       sugiCommon.h) and ito (itou_sub, lightning, mpeg/mv_disp,
 *       mpeg/mv_vobuf), so no single programmer's header can own them and
 *       this one can.  The macro NAMES are ours; none is a disc fact.
 *       Wrappers used by exactly one TU are NOT here, they live in that TU:
 *       QCOPY64_PARALLEL in seki/src/Matrix.c, and QCOPY64_SERIAL /
 *       LQ16_FROM / SQ16_TO / MAP_A0_TO_SPR in sugipon/src/matrixDrive.c.
 *       The sce/ archives get their own per-member definitions: their uses
 *       stand for Sony-internal headers this tree cannot name.
 *
 * Nothing here is a typedef lifted out of a leaked or SDK header.
 */
#ifndef TYPEDEF_H
#define TYPEDEF_H

/* ------------------------------------------------------------------ *
 * (a) line-74 helper slot.
 *
 * TODO(line 74), a float absolute value.  Both expansions in the ROM are
 * `mtc1 $zero,$fN; c.lt.s $f1,$fN; bc1tl <skip>; neg.s $f1,$f1`, i.e.
 * `x < 0.0f ? -x : x`.  It is NOT written: the rule for defining a
 * census-only helper is >= 2 HOSTS with the same sequence, and this has one
 * host (twice).  Its host is still INCLUDE_ASM; write the helper when
 * avoid_obstacle2 is matched, and name it then, the helper is never emitted
 * out of line, so it has no symbol in baserom/pal/MAIN.MAP and no name.
 *
 * The line below is line 74 and is kept free for that body.  DO NOT REFLOW
 * ANYTHING ABOVE IT.
 * ------------------------------------------------------------------ */









/*
 * RECONSTRUCTION.  Every shape below was read back out of the binary's own
 * memory accesses (offsets and widths from the load and store mnemonics, via
 * tools/dump_all_struct_shapes.py); no disc artefact declares any of them.
 * The names are this repository's, not the developers': the disc's maps name
 * functions and objects, never a struct, a field or a typedef.  And this file
 * is where they sit BY INCLUDE PATTERN, NOT BY LISTING ROWS: a declaration
 * emits no instructions, so no row of SRCFILE.TXT can name its home, and
 * ico2/common/include/typedef.h is the only attested header every one of the
 * 37 TUs that use these shapes reaches.
 *
 * `GObj` = the game object passed as `self` to per-object functions. The
 * name is the engine's own term, re-derived from the public PAL ICO-decomp's
 * Char/GObj list API (GetCharGObjList / MakeCharGObjList), a reference, not
 * a verbatim copy. Sub-object struct and field names are MECHANICAL
 * (offset-derived); a field gets a meaningful name only when the binary gives
 * evidence (e.g. a debug string). Padding is explicit so every field sits at
 * its exact recovered offset, a wrong offset is caught by the SHA-1 gate.
 *
 * Structs grow as TUs are typed; only add a field with a verified access.
 */

/* The 0x15C sub-object slot is an INT handle the engine casts to a pointer at
 * use, not a clean Sub15C*. Reading it int-typed reproduces the developer's
 * TBAA: it may-alias adjacent int writes, so the load reloads (not hoisted),
 * matching byte-for-byte WITHOUT the per-function int-typed-reload hacks
 * (COOKBOOK section 8.22). Pointer-chain users still match (no aliasing trigger).
 * Use this accessor for 0x15C; keep p_15C in the struct for layout only. */
#define GOBJ_SUB(o)  ((Sub15C *)*(int *)&((GObj *)(o))->p_15C)

typedef struct GObj    GObj;
typedef struct Sub15C  Sub15C;   /* *(GObj   + 0x15C), per-object sub state */
typedef struct Obj7F0  Obj7F0;   /* *(Sub15C + 0x7F0), shared geometry/model obj (~25 TUs) */
typedef struct GeoNode GeoNode;  /* *(Obj7F0  + 0x20) */
typedef struct GeoSub  GeoSub;   /* *(GeoNode + 0x8)  */

struct GObj {
    char    _pad0[0x8];
    int     f_8;              /* 0x8   */
    char    _pad_c[0x150];    /* 0xC .. 0x15B */
    Sub15C *p_15C;            /* 0x15C, sub-object pointer */
    char    _pad160[0x4];
    void   *p_164;           /* 0x164, actor/action-state object (engine-wide,
                                polymorphic target; type each TU's view locally) */
    char    _pad168[0x4];
    int     f_16C;            /* 0x16C */
};

struct Sub15C {
    char    _pad0[0x4];
    int     f_4; /* 0x4 */
    int     f_8; /* 0x8 */
    int     f_C; /* 0xC */
    char    _pad10[0x8];
    int     f_18; /* 0x18 */
    int     f_1C; /* 0x1C */
    int     f_20; /* 0x20 */
    int     f_24; /* 0x24 */
    int     f_28; /* 0x28 */
    char    _pad2C[0x4];
    int     f_30; /* 0x30 */
    char    _pad34[0x8];
    int     f_3C; /* 0x3C */
    char    _pad40[0x4];
    int     f_44; /* 0x44 */
    char    _pad48[0x8];
    int     f_50; /* 0x50 */
    int     f_54; /* 0x54 */
    int     f_58; /* 0x58 */
    char    _pad5C[0x10];
    char    f_6C; /* 0x6C */
    char    _pad6D[0x3];
    int     f_70; /* 0x70 */
    int     f_74; /* 0x74 */
    char    _pad78[0x4];
    int     f_7C; /* 0x7C */
    char    _pad80[0x4];
    int     f_84; /* 0x84 */
    int     f_88; /* 0x88 */
    char    _pad8C[0x44];
    int     f_D0; /* 0xD0 */
    char    _padD4[0xAC];
    int     f_180; /* 0x180 */
    char    _pad184[0x10];
    int     f_194; /* 0x194 */
    int     f_198; /* 0x198 */
    int     f_19C; /* 0x19C */
    char    _pad1A0[0x24];
    int     f_1C4; /* 0x1C4 */
    int     f_1C8; /* 0x1C8 */
    char    _pad1CC[0x14];
    int     f_1E0; /* 0x1E0 */
    char    _pad1E4[0x8C];
    int     f_270; /* 0x270 */
    int     f_274; /* 0x274 */
    int     f_278; /* 0x278 */
    char    _pad27C[0xF4];
    int     f_370; /* 0x370 */
    char    _pad374[0x64];
    int     f_3D8; /* 0x3D8 */
    char    _pad3DC[0xB4];
    int     f_490; /* 0x490, char-status index */
    char    _pad494[0xC];
    int     f_4A0; /* 0x4A0 index */
    char    _pad4A4[0x8];
    int     f_4AC; /* 0x4AC */
    char    _pad4B0[0x8];
    int     f_4B8; /* 0x4B8 */
    char    _pad4BC[0x1C];
    int     f_4D8; /* 0x4D8 */
    char    _pad4DC[0x8];
    int     f_4E4; /* 0x4E4 */
    char    _pad4E8[0x44];
    int     f_52C; /* 0x52C */
    char    _pad530[0x4];
    int     f_534; /* 0x534 */
    int     f_538; /* 0x538 */
    int     f_53C; /* 0x53C */
    int     f_540; /* 0x540 */
    char    _pad544[0xC4];
    float   f_608; /* 0x608 */
    char    _pad60C[0x1E4];
    Obj7F0 *p_7F0; /* 0x7F0, cage-fix geometry */
    char    _pad7F4[0xC];
    void   *p_800; /* 0x800, untyped (no consumers yet) */
    char    _pad804[0x10];
    int     f_814; /* 0x814 */
};

/* Geometry/model object hanging off Sub15C + 0x7F0. The p_7F0 field is read
 * in ~25 TUs (weapon, torch, boy, rope, enemy, box, spider, chain, ...), so
 * this is shared-core; only cageFix.c walks the +0x20 matrix chain so far.
 * Fields grow as TUs are typed; names are offset-derived (no string evidence). */
struct GeoSub {
    void   *p_0;          /* 0x0, object matrix passed to TurnObjectMatrix */
};

struct GeoNode {
    char    _pad0[0x8];
    GeoSub *p_8;          /* 0x8 */
};

struct Obj7F0 {
    void    *p_0;         /* 0x00, model / geometry node pointer */
    int      f_4;         /* 0x04 */
    int      f_8;         /* 0x08 */
    int      f_C;         /* 0x0C */
    int      f_10;        /* 0x10 */
    char     _pad14[0x4];
    int      f_18;        /* 0x18 */
    char     _pad1C[0x4];
    GeoNode *p_20;        /* 0x20 */
    char     _pad24[0x18];
    float    f_3C;        /* 0x3C */
    int      f_40;        /* 0x40 */
};

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN.  The 16-byte aligned float
 * quadword the VU0 entry points take and return.  Three TUs (ito/src/stage_orient,
 * sugipon/src/clothAnimation, sugipon/src/waterDot) carried character-for-character
 * the same local definition, which is what makes it one type rather than three;
 * the alignment is the ROM's, whose copies of these values are lq/sq quadword
 * moves.  The name is this repository's: no disc artefact names a type.
 */
typedef struct {
    float x, y, z, w;
} __attribute__((aligned(16))) VECTOR;

/* ------------------------------------------------------------------ *
 * (c) R5900 opcodes with no C spelling.
 *
 * Each emits exactly one instruction inside a volatile inline-asm block.
 * ------------------------------------------------------------------ */

/* Memory sync barrier, stalls the CPU until pending stores commit.
 * Used as a fence between a write and an external observer (GS, IPU,
 * VU0/1, DMAC).  ico2 sites: ito/mpeg/mv_disp, ito/mpeg/mv_vobuf. */
#define SYNC()      __asm__ __volatile__("sync"   : : : "memory")

/* Disable / enable interrupts (COP0 DI, EI).  Encodings 0x42000039 and
 * 0x42000038; the period ee-as has no mnemonic for either.  ico2 sites:
 * seki/src/Matrix (the VU0 register push/pop pair), ito/mpeg/mv_disp,
 * ito/mpeg/mv_vobuf. */
#define DI()        __asm__ __volatile__(".word 0x42000039" : : : "memory")
#define EI()        __asm__ __volatile__(".word 0x42000038" : : : "memory")

/* Quadword copy, one 128-bit lq/sq pair through a scratch GPR, with the
 * trailing nop the ROM's lq+sq+nop shape carries.  The scratch register
 * differs per call site ($t0 in seki/src/Matrix, $a2 in
 * sugipon/src/matrixDrive), so it is a macro argument.  dst/src are
 * implicit in $a0/$a1: the macro is the BODY of a two-pointer wrapper. */
#define QCOPY16(scratch)                                                       \
    __asm__ __volatile__("lq " scratch ", 0($a1)" : : : "memory");             \
    __asm__ __volatile__("sq " scratch ", 0($a0)" : : : "memory");             \
    __asm__ __volatile__("nop")

/* ------------------------------------------------------------------ *
 * (c) VU0 / COP2 macro-mode opcodes.
 *
 * The R5900's VU0 macro mode exposes ~120 distinct instruction variants
 * (broadcast + dest-mask combinations).  A unique macro per variant would
 * multiply the surface without buying any analysis power, since the
 * assembler already parses the asm text embedded in each one.  Instead
 * there is ONE macro per side-effect class.  Each emits exactly one
 * instruction inside its own __asm__ block, with a "memory" clobber only
 * on the loads and stores that observe caller-visible state.
 * ------------------------------------------------------------------ */

/* ===========================================================
 *  TYPED MACROS, preferred form.  Pass operands as tokens; the
 *  macro builds the asm string via stringify-and-paste.
 * ===========================================================
 *
 *  Naming: VU0_<SHAPE>(<mnem-with-mask>, <operands...>)
 *
 *  The mnemonic (including mask, e.g. `vmul.xyzw`, and any
 *  broadcast prefix in the mnemonic, e.g. `vaddz`) is passed as
 *  a SINGLE token; operands are unprefixed register numbers
 *  (e.g. `13` for `$vf13`, `t0` for `$t0`, `f12` for `$f12`).
 *
 *  Memory loads/stores
 *  -------------------
 *    VU0_LSV(mnem, vf, off, base)   -> "<mnem> $vf<vf>, <off>($<base>)"
 *      Use for: lqc2, sqc2, vlqd, vsqi.
 *    VU0_LSGP(mnem, gp, off, base)  -> "<mnem> $<gp>, <off>($<base>)"
 *      Use for: lq, sq, ld, sd.
 *
 *  VU compute (register-only)
 *  --------------------------
 *    VU0_V2OP(mnem, d, a)         -> "<mnem> $vfd, $vfa"
 *      Use for: vmove, vmr32, vftoi0/4/12/15, vsqrt-style 2-arg.
 *    VU0_V3OP(mnem, d, a, b)      -> "<mnem> $vfd, $vfa, $vfb"
 *      Use for: vmul.MASK / vsub.MASK / vadd.MASK with no broadcast.
 *    VU0_V3OP_BC(mnem, d, a, b, bc)
 *                                 -> "<mnem> $vfd, $vfa, $vfb<bc>"
 *      Use for: vmulx.MASK / vaddy.MASK / vmaddw.MASK style ops where
 *      the broadcast letter is part of the mnemonic AND appears as a
 *      register suffix on the b operand.
 *    VU0_V3OP_ACC(mnem, a, b)     -> "<mnem> ACC, $vfa, $vfb"
 *      Use for: vopmula.MASK, vopmsub.MASK destination=ACC.
 *    VU0_V3OP_ACC_BC(mnem, a, b, bc)
 *                                 -> "<mnem> ACC, $vfa, $vfb<bc>"
 *      Use for: vmulax/vmadday/vmaddaz.MASK style.
 *
 *  EE<->VU transfer
 *  ----------------
 *    VU0_MFC1(gp, fp)        -> "mfc1 $<gp>, $f<fp>"
 *    VU0_MTC1(gp, fp)        -> "mtc1 $<gp>, $f<fp>"
 *    VU0_QMFC2_NI(gp, vf)    -> "qmfc2.ni $<gp>, $vf<vf>"
 *    VU0_QMTC2_NI(gp, vf)    -> "qmtc2.ni $<gp>, $vf<vf>"
 *    VU0_CFC2_NI(gp, vi)     -> "cfc2.ni $<gp>, $vi<vi>"
 *
 *  Escape hatches (pass full asm string)
 *  -------------------------------------
 *    VU0_MEM(insn), caller-visible load/store; "memory" clobber.
 *    VU0_REG(insn), register-only; no clobber.
 *
 *  Use the escape hatches only when no typed macro fits, e.g. for
 *  `vrnext`, `vrxor`, `vrsqrt`, `vdiv`, `viaddi`, `vmulq`, or any
 *  rare opcode without a typed shape above.  When the same shape
 *  shows up in 3+ functions, lift it into a new typed macro here.
 */

/* Escape-hatch macros (raw asm string).  Use sparingly.
 *
 * RECONSTRUCTION, like the whole R5900 and VU0 wrapper set below and above it:
 * the opcodes are what the ROM's instructions decode to, the wrapper around
 * them is this repository's reconstruction of how the source reached them, and
 * every macro name here is ours rather than the developers', a macro leaves
 * no symbol and the disc's maps name none of them.  They sit in this header BY
 * INCLUDE PATTERN, NOT BY LISTING ROWS: SRCFILE.TXT attributes each expansion
 * to the .c line that invokes it, which is consistent with any header home, so
 * what places them here is that seki, sugipon and ito all use them and this is
 * the one attested header all three trees reach.
 *
 * Both bodies assemble with reordering off.  The game tree's VU0 opcodes are
 * hand-scheduled against the COP2 pipeline, so the assembler must leave them
 * where they are written; the visible consequence is the return of a VU0 leaf,
 * where ee-as would otherwise swap the closing `sqc2` into the `jr $31` delay
 * slot and the ROM has a `nop` there instead (69 sites in six objects).  The
 * SDK's own copy of these macros in sce/libvu0/libvu0.c is deliberately not
 * spelled this way: the ROM carries `sqc2` in 26 of that archive's return
 * slots, so the two trees were built from differently spelled templates. */
#define VU0_MEM(insn)   __asm__ __volatile__(".set noreorder\n\t" insn "\n\t.set reorder" : : : "memory")
#define VU0_REG(insn)   __asm__ __volatile__(".set noreorder\n\t" insn "\n\t.set reorder")

/* Memory load/store: typed forms. */
#define VU0_LSV(mnem, vf, off, base)        VU0_MEM(#mnem " $vf" #vf ", " #off "($" #base ")")
#define VU0_LSGP(mnem, gp, off, base)       VU0_MEM(#mnem " $" #gp ", " #off "($" #base ")")

/* Like VU0_LSV but the base address is a C expression bound via an "r"
 * constraint, so gcc sees the data dependency on `base`. Use when the
 * base is a function argument/local that must stay in a callee-saved reg
 * across calls: the explicit dependency makes the scheduler emit the
 * base-setup move just before the load (filling the prologue's ra-save
 * gap) instead of greedily up front. */
#define VU0_LSV_R(mnem, vf, off, base)      __asm__ __volatile__(#mnem " $vf" #vf ", " #off "(%0)" : : "r"(base) : "memory")

/* VU compute: 2-operand register-to-register (vmove, vmr32, vftoi*). */
#define VU0_V2OP(mnem, d, a)                VU0_REG(#mnem " $vf" #d ", $vf" #a)

/* VU compute: 3-operand register-to-register. */
#define VU0_V3OP(mnem, d, a, b)             VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b)

/* Same with broadcast on b operand (mnemonic has broadcast letter,
 * b operand has matching register suffix). */
#define VU0_V3OP_BC(mnem, d, a, b, bc)      VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b #bc)

/* VU compute to ACC. */
#define VU0_V3OP_ACC(mnem, a, b)            VU0_REG(#mnem " ACC, $vf" #a ", $vf" #b)
#define VU0_V3OP_ACC_BC(mnem, a, b, bc)     VU0_REG(#mnem " ACC, $vf" #a ", $vf" #b #bc)

/* EE<->VU transfer ops. */
#define VU0_MFC1(gp, fp)                    VU0_REG("mfc1 $" #gp ", $f" #fp)
#define VU0_MTC1(gp, fp)                    VU0_REG("mtc1 $" #gp ", $f" #fp)
#define VU0_QMFC2_NI(gp, vf)                VU0_REG("qmfc2.ni $" #gp ", $vf" #vf)
#define VU0_QMTC2_NI(gp, vf)                VU0_REG("qmtc2.ni $" #gp ", $vf" #vf)
#define VU0_CFC2_NI(gp, vi)                 VU0_REG("cfc2.ni $" #gp ", $vi" #vi)

/* VU0_NOP() (an explicit `nop` before a VU0 leaf's return) was retired 2026-09-05:
   the return-slot nop after an inline-asm block is the assembler's, and
   tools/compile_c.sh reproduces it (docs/NOTES.md "Return-slot padding"). */

/* Wait-for-Q-pipeline barrier (vwaitq).  No memory effect but
 * sequences subsequent VU0 ops with prior compute. */
#define VU0_WAIT()      __asm__ __volatile__("vwaitq")

/* Raw 32-bit word emission for COP2 ops without a gas mnemonic
 * (e.g., `vsqrt Q, $vfNx` -> .word 0x4A0X03BD). */
#define VU0_WORD(w)     __asm__ __volatile__(".word " #w)

/* Hazard-pair scheduler barriers.
 *
 * Several R5900 COP2 transfer pairs have intrinsic load-delay or
 * Q-pipeline interlocks that gas's default `.set reorder` mode
 * "fixes" by inserting a `nop` between them.  The original ICO
 * codegen does NOT have those nops -- the bytes are tight.  Wrap
 * the affected pair in VU0_NOREORDER_BEGIN/END to suppress gas's
 * auto-fill.
 *
 * Example: `mfc1 $tN, $fM` followed by `qmtc2.ni $tN, $vfK` has a
 * 1-cycle GPR load-delay.  In `.set reorder` gas inserts a nop
 * between them; in `.set noreorder` gas leaves the bytes untouched
 * (the EE pipeline is forwarding-correct already).
 */
#define VU0_NOREORDER_BEGIN()  __asm__ __volatile__(".set noreorder")
#define VU0_NOREORDER_END()    __asm__ __volatile__(".set reorder")




/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 3 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct StageSetting {
    float flatLightDir[3][4]; /* 0x000 */
    float flatLightCol[3][4]; /* 0x030 */
    float ambientCol[4];      /* 0x060 */
    char pad070[0x84];        /* 0x070 */
    int motionBlur;           /* 0x0F4 */
    char pad0F8[0xC4];        /* 0x0F8 */
    int subMotionBlur[5];     /* 0x1BC */
} StageSetting;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 3 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union {
    int c[4];
    long long ll[2];
} Col4;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    int gobj;
    float level;
    float f8;
    float fC;
    float f10;
    int timer;
    unsigned char b18;
    unsigned char b19;
    unsigned char b1A;
    unsigned char b1B;
} BrainTarget;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 3 TUs. */
typedef struct {
    int cur;
    int *buf[2];
    char *dma;
    unsigned long long *ptr;
    char *tail;
    char *gif;
    char *end;
} GifDpk;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 3 TUs. */
typedef union {
    long long d;
    int w[2];
} GifPkWord;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    char _0[0x20];
    int f_20;
    char _24[0x18];
} GsysObjInfo;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 3 TUs. */
typedef union {
    int i;
    float f;
} IntFloat;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    char _0[0x10];
    int size; /* 0x10 */
    char _14[0xC];
    char name[0x20]; /* 0x20 */
} McDirEnt;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef union {
    float f[4];
    int i[4];
} Vec4u;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 12 TUs that carried 3 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct PadState {
    int unk00;        /* 0x00 */
    int flags;        /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} PadState;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 8 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union Vec16 {
    float f[4];
    long long ll[2];
} Vec16;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 6 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    unsigned char _0[0x20];
    char name[0x80];         /* 0x20, the stage name icoMisc prints */
    short ent[0x18];         /* 0xA0 */
    unsigned char _d0[0x7C];
    int mot;                 /* 0x14C, the motion-set id */
    void (*endproc)(void);   /* 0x150 */
    void (*initproc)(void);  /* 0x154, the per-stage init hook */
    unsigned char _158[0x34];
    unsigned int attr;       /* 0x18C */
    unsigned char _190[0x4];
} StgPre;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 12 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union {
    float f[4];
    long long ll[2];
} Vec4;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 5 TUs that carried 4 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    float a[4];   /* 0x00 start point   */
    float b[4];   /* 0x10 end point     */
    float pos[4]; /* 0x20 clipped point */
    char _30[0x40];
    float f_70;
    char _74[0x14];
    int f_88;
    char _8c[0x08];
    int f_94;
    char _98[0x28];
} ClipWork;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    int girl;
    BrainTarget *cur;
    int w8;
    int wC;
    int w10;
    float f14;
    float f18;
    short h1C;
    short _1E;
    float f20;
    short idx;
    short _26;
    BrainTarget tgt[0x28];
} Brain;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 5 TUs. */
typedef union ActStatus {
    unsigned long long ll;
    int i[2];
} ActStatus;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct ViTs {
    long long pts; /* 0x00 -1 when the pack carried none */
    long long dts; /* 0x08 */
    int pos;       /* 0x10 byte position in the data ring */
    int len;       /* 0x14 bytes the pair covers, 0 when the slot is free */
} ViTs;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct {
    int w[13];
} WayRec;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 10 TUs that carried 4 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct Pad {
    int unk00;        /* 0x00 */
    int trg;          /* 0x04 */
    char unk08[0x50]; /* 0x08 */
} Pad;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 4 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    float pos[3];
    float rot[3];
    int f_18;
    int f_1C;
    int f_20;
    int f_24;
} ExitData;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 38 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct ActMail {
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    int unk08;                  /* 0x08 */
    int unk0C;                  /* 0x0C */
} ActMail;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 17 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union {
    float f[4];
    long long d[2];
} ConstVec;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 30 TUs that carried 8 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct PObjGObj {
    char pad00[0x4]; /* 0x000 */
    int f04;         /* 0x004 */
    int f08;         /* 0x008 */
    int f0C;         /* 0x00C */
    char pad10[0x30];
    int f40; /* 0x040 */
    char pad44[0x4];
    int f48; /* 0x048 */
    int f4C; /* 0x04C */
    int f50; /* 0x050 */
    char pad54[0x8];
    int f5C; /* 0x05C */
    int f60; /* 0x060 */
    char pad64[0x100];
    int act; /* 0x164, the actor/action-state object */
    char pad168[0x4];
    int f16C; /* 0x16C */
} PObjGObj;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 38 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct Act {
    char unk00[0x20];  /* 0x00 */
    ActStatus flags20; /* 0x20 */
    char unk28[0xC];   /* 0x28 */
    int unk34;         /* 0x34 */
    char unk38[0x68];  /* 0x38 */
    long long flags;   /* 0xA0 */
    char unkA8[0x28];  /* 0xA8 */
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
    char unkD8[0x20C]; /* 0xD8 */
    int unk2E4;        /* 0x2E4 */
} Act;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    float scale[3];        /* 0x00 */
    float rot[3];          /* 0x0C */
    float pos[3];          /* 0x18 */
    int f24;               /* 0x24 */
    int *f28;              /* 0x28 */
    int mdl;               /* 0x2C */
    int f30;               /* 0x30 */
    char _34[4];           /* 0x34 */
    int f38;               /* 0x38 */
    char _3C[4];           /* 0x3C */
    unsigned short f40;    /* 0x40 */
    unsigned short f44;    /* 0x42 */
    unsigned short parent; /* 0x44 */
    unsigned char kind;    /* 0x46 */
    unsigned char f47;     /* 0x47 */
    unsigned int f48;      /* 0x48 */
} GenGeo;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    char pad[0x34];
    int x34;
    char pad2[0x4C - 0x38];
} OaRecA;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    int x0;
    int x4;
    int x8;
    int xC;
    int x10;
} OaRecB;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    float m[16];
} Mtx44 __attribute__((aligned(16)));

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {
    int _0;
    int trg; /* 0x4 */
    int _8;
    int rep; /* 0xC */
} GsbPad;

#endif /* TYPEDEF_H */
