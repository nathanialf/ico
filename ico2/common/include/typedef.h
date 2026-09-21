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
#define GOBJ_SUB(o) ((Sub15C *)*(int *)&((GObj *)(o))->p_15C)
/* The 0x164 actor slot, the companion of GOBJ_SUB: the action-state object the
 * per-object functions run their state machines out of. */
#define GOBJ_ACT(o) ((Act *)((GObj *)(o))->p_164)

typedef struct GObj GObj;

typedef struct Sub15C Sub15C; /* *(GObj   + 0x15C), per-object sub state */

typedef struct Obj7F0 Obj7F0; /* *(Sub15C + 0x7F0), shared geometry/model obj (~25 TUs) */

typedef struct Obj874 Obj874; /* *(Sub15C + 0x874), per-object light record */

typedef struct GeoNode GeoNode; /* *(Obj7F0  + 0x20) */

typedef struct GeoSub GeoSub; /* *(GeoNode + 0x8)  */

/* GObj and PObjGObj below are two views of ONE record: the game object.  Every
 * offset either view knows is named in both, under the same name, so no offset
 * a translation unit has identified is left inside a pad; the two names survive
 * only because their field types differ where the bytes let them (this view
 * carries the typed sub-object and actor pointers, the other carries them as
 * words).  Rungs: ROM bytes for every offset, the reading translation units for
 * the roles; names are this repository's. */
struct GObj {
    char _pad0[0x4];
    int f04;                /* 0x4   */
    int f_8;                /* 0x8   */
    int kind;               /* 0xC, the object-kind id, -1 when the object has
                                 none; it indexes the ObjKindEnt table */
    char _pad10[0x1C];      /* 0x10 .. 0x2B */
    struct GProc *procHead; /* 0x2C, head of the object's process list */
    struct GProc *procTail; /* 0x30, tail of the same list */
    char _pad34[0xC];       /* 0x34 .. 0x3F */
    int f40;                /* 0x40  */
    char _pad44[0x4];
    int f48; /* 0x48  */
    int f4C; /* 0x4C  */
    int f50; /* 0x50  */
    char _pad54[0x8];
    int f5C;           /* 0x5C  */
    int f60;           /* 0x60  */
    char _pad64[0xF8]; /* 0x64 .. 0x15B */
    Sub15C *p_15C;     /* 0x15C, sub-object pointer */
    char _pad160[0x4];
    void *p_164; /* 0x164, actor/action-state object.  The actor and
                                script translation units read it as Act, through
                                GOBJ_ACT below; it stays void * because other
                                translation units hang their own record there */
    char _pad168[0x4];
    int f_16C; /* 0x16C */
};

struct Sub15C {
    char _pad0[0x4];
    int f_4;  /* 0x4 */
    int f_8;  /* 0x8 */
    int f_C;  /* 0xC */
    int f_10; /* 0x10 */
    char _pad14[0x4];
    int f_18; /* 0x18 */
    int f_1C; /* 0x1C */
    int f_20; /* 0x20 */
    int f_24; /* 0x24 */
    int f_28; /* 0x28 */
    char _pad2C[0x4];
    int f_30; /* 0x30 */
    char _pad34[0x8];
    int f_3C; /* 0x3C */
    char _pad40[0x4];
    int f_44; /* 0x44 */
    char _pad48[0x8];
    int f_50;   /* 0x50 */
    float f_54; /* 0x54 */
    int f_58;   /* 0x58 */
    char _pad5C[0x10];
    char f_6C; /* 0x6C */
    char _pad6D[0x3];
    int f_70; /* 0x70 */
    int f_74; /* 0x74 */
    int f_78; /* 0x78 */
    int f_7C; /* 0x7C */
    int f_80; /* 0x80 */
    int f_84; /* 0x84 */
    int f_88; /* 0x88 */
    char _pad8C[0x18];
    float f_A4; /* 0xA4 */
    char _padA8[0x28];
    int f_D0; /* 0xD0 */
    char _padD4[0x5C];
    float f_130; /* 0x130 */
    float f_134; /* 0x134 */
    float f_138; /* 0x138 */
    char _pad13C[0x44];
    int f_180; /* 0x180 */
    char _pad184[0x4];
    int f_188; /* 0x188 */
    char _pad18C[0x8];
    int f_194; /* 0x194 */
    int f_198; /* 0x198 */
    int f_19C; /* 0x19C */
    char _pad1A0[0x24];
    int f_1C4; /* 0x1C4 */
    int f_1C8; /* 0x1C8 */
    char _pad1CC[0x14];
    int f_1E0; /* 0x1E0 */
    char _pad1E4[0x8C];
    float f_270; /* 0x270 */
    int f_274;   /* 0x274 */
    int f_278;   /* 0x278 */
    char _pad27C[0x34];
    int f_2B0; /* 0x2B0 */
    int f_2B4; /* 0x2B4 */
    int f_2B8; /* 0x2B8 */
    char _pad2BC[0x4];
    float f_2C0; /* 0x2C0 */
    float f_2C4; /* 0x2C4 */
    float f_2C8; /* 0x2C8 */
    char _pad2CC[0x44];
    int f_310; /* 0x310 */
    int f_314; /* 0x314 */
    int f_318; /* 0x318 */
    char _pad31C[0x4];
    float f_320; /* 0x320 */
    float f_324; /* 0x324 */
    float f_328; /* 0x328 */
    char _pad32C[0x44];
    int f_370; /* 0x370 */
    char _pad374[0xC];
    int f_380; /* 0x380 */
    char _pad384[0xC];
    float f_390; /* 0x390 */
    float f_394; /* 0x394 */
    float f_398; /* 0x398 */
    char _pad39C[0x1C];
    int f_3B8; /* 0x3B8 */
    int f_3BC; /* 0x3BC */
    char _pad3C0[0x18];
    int f_3D8; /* 0x3D8 */
    char _pad3DC[0x44];
    int f_420; /* 0x420 */
    char _pad424[0x38];
    float f_45C; /* 0x45C */
    char _pad460[0x4];
    float f_464; /* 0x464 */
    float f_468; /* 0x468 */
    char _pad46C[0x24];
    int f_490; /* 0x490, char-status index */
    char _pad494[0xC];
    int f_4A0; /* 0x4A0 index */
    char _pad4A4[0x8];
    float f_4AC; /* 0x4AC */
    char _pad4B0[0x8];
    float f_4B8; /* 0x4B8 */
    char _pad4BC[0x1C];
    int f_4D8; /* 0x4D8 */
    char _pad4DC[0x8];
    int f_4E4; /* 0x4E4 */
    char _pad4E8[0x4];
    int f_4EC; /* 0x4EC */
    char _pad4F0[0x8];
    int f_4F8; /* 0x4F8 */
    char _pad4FC[0x18];
    int f_514; /* 0x514 */
    char _pad518[0x14];
    int f_52C; /* 0x52C */
    char _pad530[0x4];
    int f_534; /* 0x534 */
    int f_538; /* 0x538 */
    int f_53C; /* 0x53C */
    int f_540; /* 0x540 */
    char _pad544[0x10];
    int f_554; /* 0x554 */
    char _pad558[0x14];
    int f_56C; /* 0x56C */
    char _pad570[0x78];
    float f_5E8; /* 0x5E8 */
    char _pad5EC[0x8];
    int f_5F4; /* 0x5F4 */
    int f_5F8; /* 0x5F8 */
    char _pad5FC[0x4];
    int f_600;   /* 0x600 */
    int f_604;   /* 0x604 */
    float f_608; /* 0x608 */
    char _pad60C[0x18];
    int f_624; /* 0x624 */
    int f_628; /* 0x628 */
    char _pad62C[0x4];
    int f_630; /* 0x630 */
    int f_634; /* 0x634 */
    char _pad638[0x8];
    float f_640; /* 0x640 */
    float f_644; /* 0x644 */
    int f_648;   /* 0x648 */
    char _pad64C[0x1A4];
    Obj7F0 *p_7F0; /* 0x7F0, cage-fix geometry */
    char _pad7F4[0xC];
    void *p_800; /* 0x800, untyped (no consumers yet) */
    char _pad804[0x10];
    int f_814; /* 0x814 */
    char _pad818[0x4];
    int f_81C; /* 0x81C */
    char _pad820[0x10];
    int f_830; /* 0x830, the actor's own work record; each actor TU casts it to its own shape */
    int f_834; /* 0x834 */
    int f_838; /* 0x838 */
    char _pad83C[0x8];
    int f_844; /* 0x844 */
    char _pad848[0x28];
    void *p_870; /* 0x870 */
    void *p_874; /* 0x874 */
};

/* Per-object light record, *(Sub15C + 0x874).  Light.c fills the three light
 * colour vectors at 0xB0, 0xC0 and 0xD0, the ambient at 0xE0 and the scale at
 * 0xEC, and f_F0 selects the light mode: Light.c tests it against 0, DObj.c
 * copies it and tests it against 4, Packet.c hands it to pac_makePacket and
 * RegistPacket.c gates the light packet on it.  Rung: ROM bytes for every
 * offset, the reading translation units for the roles; names are offset
 * derived (no string evidence).  p_874 above stays void * because most
 * readers reach the record through a char * cast. */
struct Obj874 {
    char _pad0[0xB0];
    float f_B0[4]; /* 0xB0 */
    float f_C0[4]; /* 0xC0 */
    float f_D0[4]; /* 0xD0 */
    float f_E0[3]; /* 0xE0 */
    float f_EC;    /* 0xEC */
    int f_F0;      /* 0xF0, light mode */
};

/* Geometry/model object hanging off Sub15C + 0x7F0. The p_7F0 field is read
 * in ~25 TUs (weapon, torch, boy, rope, enemy, box, spider, chain, ...), so
 * this is shared-core; only cageFix.c walks the +0x20 matrix chain so far.
 * Fields grow as TUs are typed; names are offset-derived (no string evidence). */
struct GeoSub {
    void *p_0; /* 0x0, object matrix passed to TurnObjectMatrix */
};

struct GeoNode {
    char _pad0[0x8];
    GeoSub *p_8; /* 0x8 */
};

struct Obj7F0 {
    void *p_0; /* 0x00, model / geometry node pointer */
    int f_4;   /* 0x04 */
    int f_8;   /* 0x08 */
    int f_C;   /* 0x0C */
    int f_10;  /* 0x10 */
    char _pad14[0x4];
    int f_18; /* 0x18 */
    char _pad1C[0x4];
    GeoNode *p_20; /* 0x20 */
    char _pad24[0x18];
    float f_3C; /* 0x3C */
    int f_40;   /* 0x40 */
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
#define SYNC() __asm__ __volatile__("sync" : : : "memory")
/* Disable / enable interrupts (COP0 DI, EI).  Encodings 0x42000039 and
 * 0x42000038; the period ee-as has no mnemonic for either.  ico2 sites:
 * seki/src/Matrix (the VU0 register push/pop pair), ito/mpeg/mv_disp,
 * ito/mpeg/mv_vobuf. */
#define DI() __asm__ __volatile__(".word 0x42000039" : : : "memory")
#define EI() __asm__ __volatile__(".word 0x42000038" : : : "memory")
/* Quadword copy, one 128-bit lq/sq pair through a scratch GPR, with the
 * trailing nop the ROM's lq+sq+nop shape carries.  The scratch register
 * differs per call site ($t0 in seki/src/Matrix, $a2 in
 * sugipon/src/matrixDrive), so it is a macro argument.  dst/src are
 * implicit in $a0/$a1: the macro is the BODY of a two-pointer wrapper. */
#define QCOPY16(scratch)                                                                           \
    __asm__ __volatile__("lq " scratch ", 0($a1)" : : : "memory");                                 \
    __asm__ __volatile__("sq " scratch ", 0($a0)" : : : "memory");                                 \
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
#define VU0_MEM(insn)                                                                              \
    __asm__ __volatile__(".set noreorder\n\t" insn "\n\t.set reorder" : : : "memory")
#define VU0_REG(insn) __asm__ __volatile__(".set noreorder\n\t" insn "\n\t.set reorder")
/* Memory load/store: typed forms. */
#define VU0_LSV(mnem, vf, off, base) VU0_MEM(#mnem " $vf" #vf ", " #off "($" #base ")")
#define VU0_LSGP(mnem, gp, off, base) VU0_MEM(#mnem " $" #gp ", " #off "($" #base ")")
/* Like VU0_LSV but the base address is a C expression bound via an "r"
 * constraint, so gcc sees the data dependency on `base`. Use when the
 * base is a function argument/local that must stay in a callee-saved reg
 * across calls: the explicit dependency makes the scheduler emit the
 * base-setup move just before the load (filling the prologue's ra-save
 * gap) instead of greedily up front. */
#define VU0_LSV_R(mnem, vf, off, base)                                                             \
    __asm__ __volatile__(#mnem " $vf" #vf ", " #off "(%0)" : : "r"(base) : "memory")
/* VU compute: 2-operand register-to-register (vmove, vmr32, vftoi*). */
#define VU0_V2OP(mnem, d, a) VU0_REG(#mnem " $vf" #d ", $vf" #a)
/* VU compute: 3-operand register-to-register. */
#define VU0_V3OP(mnem, d, a, b) VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b)
/* Same with broadcast on b operand (mnemonic has broadcast letter,
 * b operand has matching register suffix). */
#define VU0_V3OP_BC(mnem, d, a, b, bc) VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b #bc)
/* VU compute to ACC. */
#define VU0_V3OP_ACC(mnem, a, b) VU0_REG(#mnem " ACC, $vf" #a ", $vf" #b)
#define VU0_V3OP_ACC_BC(mnem, a, b, bc) VU0_REG(#mnem " ACC, $vf" #a ", $vf" #b #bc)
/* EE<->VU transfer ops. */
#define VU0_MFC1(gp, fp) VU0_REG("mfc1 $" #gp ", $f" #fp)
#define VU0_MTC1(gp, fp) VU0_REG("mtc1 $" #gp ", $f" #fp)
#define VU0_QMFC2_NI(gp, vf) VU0_REG("qmfc2.ni $" #gp ", $vf" #vf)
#define VU0_QMTC2_NI(gp, vf) VU0_REG("qmtc2.ni $" #gp ", $vf" #vf)
#define VU0_CFC2_NI(gp, vi) VU0_REG("cfc2.ni $" #gp ", $vi" #vi)

/* VU0_NOP() (an explicit `nop` before a VU0 leaf's return) was retired 2026-09-05:
   the return-slot nop after an inline-asm block is the assembler's, and
   tools/compile_c.sh reproduces it (docs/NOTES.md "Return-slot padding"). */

/* Wait-for-Q-pipeline barrier (vwaitq).  No memory effect but
 * sequences subsequent VU0 ops with prior compute. */
#define VU0_WAIT() __asm__ __volatile__("vwaitq")
/* Raw 32-bit word emission for COP2 ops without a gas mnemonic
 * (e.g., `vsqrt Q, $vfNx` -> .word 0x4A0X03BD). */
#define VU0_WORD(w) __asm__ __volatile__(".word " #w)
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
#define VU0_NOREORDER_BEGIN() __asm__ __volatile__(".set noreorder")
#define VU0_NOREORDER_END() __asm__ __volatile__(".set reorder")

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 3 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct StageSetting {
    float flatLightDir[3][4]; /* 0x000 */
    float flatLightCol[3][4]; /* 0x030 */
    float ambientCol[4];      /* 0x060 */
    char pad070[0x60];        /* 0x070 */
    /* RECONSTRUCTION: the reduction tint used while no sub target is current,
       and the per sub target row whose fourth word is the film grain tint
       ico2/seki/src/GsBase.c reads at 0x13C. */
    int reductionCol[3]; /* 0x0D0 */
    char pad0DC[0x4];    /* 0x0DC */
    /* RECONSTRUCTION: the stage's view scale, a percentage that
       ico2/seki/src/GsBase.c's gsb_SetVSMatrix divides by 100 into the zoom
       and again into the mip map level. */
    int viewScale;     /* 0x0E0 */
    char pad0E4[0x10]; /* 0x0E4 */
    int motionBlur;    /* 0x0F4 */
    char pad0F8[0x4];  /* 0x0F8 */
    int f0FC;          /* 0x0FC */
    int f100;          /* 0x100 */
    char pad104[0x2C]; /* 0x104 */

    struct {
        int r;
        int g;
        int b;
        int a;
    } targetCol[4]; /* 0x130 */

    char pad170[0x2C]; /* 0x170 */

    struct {
        int a;
        int b;
    } f19C[4]; /* 0x19C */

    int subMotionBlur[5]; /* 0x1BC */
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

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the 70-entry object-kind table at
 * D_002C1270, one 0x64-byte row per kind, indexed by the kind id a GObj carries
 * at +0xC.  The row's leading 0x24 bytes are the kind's name ("BOY", "GIRL",
 * "GIRLDEMOCTRL", ...), which debug.c and debug_menu.c hand straight to the
 * menu as a string.  Five translation units read this row through five
 * different local views (brain, gamesys, sceneManager, debug, debug_menu) and
 * this record is the merge of what all of them know; the offsets that hold a
 * text address in every row are spelled as function pointers.  Field names are
 * this repository's. */
typedef struct {
    char name[0x24];                 /* 0x00 */
    float targetTime;                /* 0x24, brain's target timer, -1.0 = none */
    float f28;                       /* 0x28 */
    float f2C;                       /* 0x2C */
    int f30;                         /* 0x30 */
    void (*f34)();                   /* 0x34 */
    void (*f38)();                   /* 0x38 */
    void (*uniqDataSet)(int *, int); /* 0x3C, gamesys' per-kind unique-data writer */
    void (*f40)();                   /* 0x40 */
    int f44;                         /* 0x44 */
    void (*f48)();                   /* 0x48 */
    int f4C;                         /* 0x4C */
    void (*f50)();                   /* 0x50 */
    void (*hotInit)(int *);          /* 0x54, sceneManager's hot-init hook */
    int (*create)(char *, int);      /* 0x58, the kind's GObj constructor */
    void (*f5C)();                   /* 0x5C */
    void (*f60)();                   /* 0x60, nonzero means the kind takes mail 47 */
} ObjKindEnt;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the 0x194-byte per-stage preset
 * record at D_005F5D50.  Every offset any translation unit reads is named here:
 * the views that stayed local (sceneManager, deja, st25a, script, way_tool,
 * s_init, camera-editor, ebrain, layout_texture, commonact) each say in a
 * comment why their bytes need their own spelling, and this record is the
 * merge of what all of them know.  Field names are this repository's; no disc
 * artefact names a field of this table. */
typedef struct {
    unsigned char _0[0x20];
    char name[0x40];     /* 0x20, the stage name icoMisc prints */
    float f60[8];        /* 0x60, the eight scene values sceneManager casts
                                into the stage setting record */
    char dataFile[0x20]; /* 0x80, the data file name access.c builds a path from */
    short ent[0x18];     /* 0xA0, the stage-manager table entries */
    unsigned char _d0[0x8];
    float bgCol[3];        /* 0xD8 */
    float ambientCol[3];   /* 0xE4 */
    float flatLightCol[3]; /* 0xF0 */
    float flatLightDir[3]; /* 0xFC */
    int seSegFirst;        /* 0x108, sound data segment range */
    int seSegLast;         /* 0x10C */
    int seEnvFirst;        /* 0x110, sound SE environment range */
    int seEnvLast;         /* 0x114 */
    int camSetId;          /* 0x118, the camera set the stage opens with */
    unsigned char _11c[0xC];
    int labelTop;    /* 0x128, generator label range */
    int labelEnd;    /* 0x12C */
    int layoutFirst; /* 0x130, layout range */
    int layoutLast;  /* 0x134 */
    int mdl[4];      /* 0x138, the four stage model ids GetRealModelId picks from */
    unsigned char _148[0x4];
    int mot;                /* 0x14C, the motion-set id */
    void (*endproc)(void);  /* 0x150 */
    void (*initproc)(void); /* 0x154, the per-stage init hook */
    unsigned char _158[0xC];
    int wayGroupEnd; /* 0x164 */
    unsigned char _168[0x8];
    int wayGroupStart; /* 0x170 */
    unsigned char _174[0x10];
    float handCameraRate; /* 0x184 */
    short f188;           /* 0x188 */
    unsigned char _18a[0x2];
    unsigned int attr;  /* 0x18C, flag word whose low half is the reverb depth */
    unsigned int flags; /* 0x190 */
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
    float radius;    /* 0x70 clip radius */
    int skipSrc[2];  /* 0x74 the pair _Clip passes with an element, for the element
                        the search must skip */
    int skipElem;    /* 0x7C */
    int wallSrc[2];  /* 0x80 the same pair for the wall the search hit */
    int wallHit;     /* 0x88 */
    int floorSrc[2]; /* 0x8C the same pair for the floor the search hit */
    int floorHit;    /* 0x94 */
    char _98[0x8];
    float normal[4]; /* 0xA0 */
    int f_B0;        /* 0xB0 */
    char _b4[0xC];
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
    int kind;        /* 0x00C, the object-kind id, -1 when the object has none */
    char pad10[0x1C];
    struct GProc *procHead; /* 0x02C, head of the object's process list */
    struct GProc *procTail; /* 0x030, tail of the same list */
    char pad34[0xC];
    int f40; /* 0x040 */
    char pad44[0x4];
    int f48; /* 0x048 */
    int f4C; /* 0x04C */
    int f50; /* 0x050 */
    char pad54[0x8];
    int f5C; /* 0x05C */
    int f60; /* 0x060 */
    char pad64[0xF8];
    int sub; /* 0x15C, the sub-object GObj's own view types as Sub15C * */
    char pad160[0x4];
    int act; /* 0x164, the actor/action-state object */
    char pad168[0x4];
    int f16C; /* 0x16C */
} PObjGObj;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 38 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct Act {
    char _pad0[0x10];
    int f_10; /* 0x10 */
    int f_14; /* 0x14 */
    char _pad18[0x8];
    ActStatus flags20; /* 0x20 */
    char _pad28[0x8];
    int f_30;          /* 0x30 */
    int unk34;         /* 0x34 */
    unsigned int f_38; /* 0x38 */
    char _pad3C[0x8];
    int f_44; /* 0x44 */
    char _pad48[0x48];
    long long f_90; /* 0x90 */
    char _pad98[0x8];
    long long flags; /* 0xA0 */
    int f_A8;        /* 0xA8 */
    int f_AC;        /* 0xAC */
    char _padB0[0x20];
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
    char _padD8[0x8];
    int f_E0; /* 0xE0 */
    char _padE4[0x3C];
    float f_120; /* 0x120 */
    float f_124; /* 0x124 */
    float f_128; /* 0x128 */
    char _pad12C[0x4];
    void *f_130; /* 0x130: the motion record SetMotionRequest returns */
    int f_134;   /* 0x134 */
    char _pad138[0x2];
    short f_13A; /* 0x13A */
    char _pad13C[0x8];
    int f_144; /* 0x144 */
    int f_148; /* 0x148 */
    char _pad14C[0x4];
    int f_150; /* 0x150 */
    char _pad154[0x3C];
    int f_190; /* 0x190 */
    char _pad194[0x2C];
    float f_1C0; /* 0x1C0 */
    float f_1C4; /* 0x1C4 */
    float f_1C8; /* 0x1C8 */
    char _pad1CC[0x4];
    int f_1D0;  /* 0x1D0 */
    int f_1D4;  /* 0x1D4 */
    char f_1D8; /* 0x1D8 */
    char f_1D9; /* 0x1D9 */
    char f_1DA; /* 0x1DA */
    char f_1DB; /* 0x1DB */
    char _pad1DC[0x4];
    float f_1E0; /* 0x1E0 */
    char _pad1E4[0x100];
    int unk2E4; /* 0x2E4 */
    char _pad2E8[0x64];
    int f_34C; /* 0x34C */
    int f_350; /* 0x350 */
    char _pad354[0xEC];
    int f_440; /* 0x440 */
    int f_444; /* 0x444 */
    char _pad448[0x1B4];
    int f_5FC; /* 0x5FC */
    char _pad600[0x80];
    int f_680; /* 0x680 */
    int f_684; /* 0x684 */
    int f_688; /* 0x688 */
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
