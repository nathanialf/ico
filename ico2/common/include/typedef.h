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
 *   (a) the line-74 helper, fixed by the listing: the float absolute value
 *       avoid_obstacle2 inlines twice; see section (a) below.
 *
 *   (b) the cross-programmer engine object shapes (GObj, PObjGObj, Sub15C,
 *       Act) and the GOBJ_SUB and GOBJ_ACT accessors.  PLACEMENT BY INCLUDE
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
 * (a) the line-74 helper, a float absolute value.
 *
 * Both of its expansions in the ROM, avoid_obstacle2's |dx| and |dz|
 * tests (the listing's rows inside way_sys.c 633 and 634), are
 * `mtc1 $zero,$fN; c.lt.s $f1,$fN; bc1tl <skip>; neg.s $f1,$f1`, i.e.
 * `x < 0.0f ? -x : x`, and SRCFILE.TXT attributes their three rows to
 * this file's line 74 alone.  A macro expansion would carry the caller's
 * line, so the helper is a function whose whole body is on that line.
 * It is never emitted out of line, so it has no symbol in
 * baserom/pal/MAIN.MAP and no disc name: `absf` is ours.  Unreferenced,
 * a static inline function emits nothing, so every other includer's
 * object is unchanged (each compared by whole object when it landed,
 * chain 1 pass 130).
 *
 * One host uses it (twice); the listing, not a second host, is what
 * places it here.
 *
 * The helper below is line 74.  DO NOT REFLOW ANYTHING ABOVE IT, and
 * keep it on one line: the listing puts every instruction of both
 * expansions on that line.
 * ------------------------------------------------------------------ */
static inline float absf(float x)
{
    return x < 0.0f ? -x : x;
}

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
 * a verbatim copy. Every field is named from what its readers and writers do
 * with it; a word whose readers do not fix its meaning is named by its type
 * and offset (word13C), and a word nothing in the tree reads is padding.
 * Padding is explicit so every field sits at its exact recovered offset; a
 * wrong offset is caught by the byte gate.
 *
 * Structs grow as TUs are typed; only add a field with a verified access.
 */

/* The 0x15C sub-object slot is an INT handle the engine casts to a pointer at
 * use, not a clean Sub15C*. Reading it int-typed reproduces the developer's
 * TBAA: it may-alias adjacent int writes, so the load reloads (not hoisted),
 * matching byte-for-byte WITHOUT the per-function int-typed-reload hacks
 * (COOKBOOK section 8.22). Pointer-chain users still match (no aliasing trigger).
 * Use this accessor for 0x15C; keep dobj in the struct for layout only. */
#define GOBJ_SUB(o) ((Sub15C *)*(int *)&((GObj *)(o))->dobj)
/* The 0x164 actor slot, the companion of GOBJ_SUB: the action-state object the
 * per-object functions run their state machines out of. */
#define GOBJ_ACT(o) ((Act *)((GObj *)(o))->act)

typedef struct GObj GObj;

typedef struct Sub15C Sub15C; /* *(GObj + 0x15C), the object's display object (DObj.c) */

/* The 80-byte record Sub15C + 0x870 points at, one per display node; the
 * buffer is reallocated with the 0xC matrices and 0x10 vectors for the node
 * count.  The display (RegistPacket.c) draws a node with alpha
 * 1 - (1 - fade) * alpha, fading when bit 0 of the flag word is set, turns it
 * by the Z angle at 0x3A and places it at pos. */
struct DObjNode {   /* field names derived */
    int rot[4];     /* 0x00, the angles, read back as shorts */
    int word10[4];  /* 0x10 */
    float scale[4]; /* 0x20 */
    float fade;     /* 0x30 */
    float alpha;    /* 0x34 */

    union {
        int i;
        long long ll; /* bit 0 fade, bits 1 and 2 */
    } flags;          /* 0x38; its 0x3A half is also stored as a short, the Z angle */

    float pos[4]; /* 0x40, reset to 0 0 0 1 */
};

/* GObj and PObjGObj below are two views of ONE record: the game object.  GObj
 * types the run-list links, the display object pointer and the run function;
 * PObjGObj carries them as words.  The names are this repository's. */
struct GObj {   /* field names derived */
    GObj *self; /* 0x0, the object itself while its table entry is
                               in use, 0 when free (gobj.c) */
    int labelType; /* 0x4, the label type the object was created under, 1 for a stage layout object, -1 for none */
    int labelId; /* 0x8, the layout or label number within that type (objLayout's row for a layout object) */
    int kind;             /* 0xC, the object-kind id, -1 when the object has
                                 none; it indexes the ObjKindEnt table */
    GObj *next;           /* 0x10, next object on its run list */
    GObj *prev;           /* 0x14, previous object on its run list */
    unsigned char linkId; /* 0x18, which of the eight run lists */
    char pad19[3];
    unsigned int key;       /* 0x1C, the run list's sort key */
    char pad20[8];          /* 0x20 .. 0x27 */
    void (*fn)(GObj *);     /* 0x28, the object's per-frame function */
    struct GProc *procHead; /* 0x2C, head of the object's process list */
    struct GProc *procTail; /* 0x30, tail of the same list */
    char pad34[8];          /* 0x34 .. 0x3B */
    GObj *kindNext;         /* 0x3C, next object of the same kind */
    int dlLinkId;           /* 0x40, the display list the object is linked into (gobj_dl.c) */
    char pad44[4];
    int dl; /* 0x48, the object's display function */
    char pad4C[4];
    int drawMask; /* 0x50, ANDed with a camera's mask to pick the cameras that draw it; all ones while shown */
    int mailQueue; /* 0x54, the mail box (obj_manager.c's IosMailBox), this word unread */
    int mailNum;   /* 0x58, the count of mails queued from 0x5C */
    int mailType;  /* 0x5C, the first queued mail's type; 31 more type and argument pairs follow */
    int mailArg;   /* 0x60, the first queued mail's argument */
    char pad64[248]; /* 0x64 .. 0x15B */
    Sub15C *dobj;    /* 0x15C, the display object (CSVSYSTEM_InitDObj) */
    char pad160[4];
    int act; /* 0x164, the actor/action-state object, held as a word like
                0x15C: the actor and script translation units read it as Act
                through GOBJ_ACT below, other translation units hang their own
                record there */
    char pad168[4];
    int active;      /* 0x16C, nonzero while the object is active: the object
                  manager runs only active objects' functions and processes */
    int pauseExempt; /* 0x170, nonzero when the object keeps running while the
                  game is paused (systemStatus[5]) */
};

struct Sub15C { /* field names derived */
    char pad0[4];
    int parentNode; /* 0x4, the parent object's node this one hangs from; the parent object is the word at 0 */
    int nodeNum;  /* 0x8, the count of node matrices and quaternions at 0xC and 0x10 */
    int nodeMtx;  /* 0xC, one 64-byte matrix a node */
    int nodeQuat; /* 0x10, one quaternion a node */
    char pad14[12];
    int matrix; /* 0x20, the object's own matrix starts here (initMatrixDObj) */
    char pad24[48];
    float matrixTy; /* 0x54, the translation height in that matrix */
    char pad58[24];
    int colData;   /* 0x70, the collision data; its wall list hangs at 0x10 */
    int disp;      /* 0x74, nonzero while the stage animation draws the object */
    int colRotate; /* 0x78, nonzero when the collision follows the node's rotation */
    int cylinderOn; /* 0x7C, nonzero, with the word at 0x3C8, when the object takes part in cylinder collision */
    int colPerNode;  /* 0x80, nonzero when the collision has one entry a node */
    int modelId;     /* 0x84, the model id the enemy setup loads (GetPObjAddress) */
    int skelNodeNum; /* 0x88, the count of skeleton nodes */
    int skel;        /* 0x8C, the skeleton node records, 64 bytes each; +0x14 is the root height */
    char *
        clusterMtx; /* 0x90, one matrix a node, applied before the node's own for a cluster shadow */
    char pad94[16];
    float rootPosY; /* 0xA4, the root position's height (MotRoot at 0xA0) */
    char padA8[76];
    float handBlend; /* 0xF4, the hand IK blend HandManager eases toward its target */
    char padF8[56];
    float moveX; /* 0x130, the root movement, x */
    float moveY; /* 0x134, the root movement, y */
    float moveZ; /* 0x138, the root movement, z */
    int word13C; /* 0x13C */
    char pad140[32];
    float height; /* 0x160, the root height above the position, added back on unlinking */
    char pad164[28];
    int wallObj; /* 0x180, the object of the wall the root touches */
    char pad184[4];
    int wallPlane; /* 0x188, the wall's plane record, 0 when no wall */
    char pad18C[68];
    float planeX; /* 0x1D0, the contact plane, x (dispPlane) */
    float planeY; /* 0x1D4, the contact plane, y */
    float planeZ; /* 0x1D8, the contact plane, z */
    char pad1DC[4];
    int lastField; /* 0x1E0, the field GetCollisionOfLastActiveField returns */
    int word1E4;   /* 0x1E4 */
    char pad1E8[8];
    float lastPos[4]; /* 0x1F0, the root's last position */
    char pad200[84];
    float groundY; /* 0x254, the ground height the root measures from */
    char pad258[24];
    float projHeight; /* 0x270, the height GetRootProjectionPosOfGObj adds to the root position */
    char pad274[60];
    int hand1Mode; /* 0x2B0, hand record 1 (RequestChangeHandMode mode 1): the mode flag */
    int hand1Obj;  /* 0x2B4, the object the hand reaches for */
    int hand1Node; /* 0x2B8, the node the hand reaches for */
    char pad2BC[4];
    float hand1PosX; /* 0x2C0, the hand target, x */
    float hand1PosY; /* 0x2C4, the hand target, y */
    float hand1PosZ; /* 0x2C8, the hand target, z */
    char pad2CC[68];
    int hand0Mode; /* 0x310, hand record 0 (RequestChangeHandMode mode 0): the mode flag */
    int hand0Obj;  /* 0x314, the object the hand reaches for */
    int hand0Node; /* 0x318, the node the hand reaches for */
    char pad31C[4];
    float hand0PosX; /* 0x320, the hand target, x */
    float hand0PosY; /* 0x324, the hand target, y */
    float hand0PosZ; /* 0x328, the hand target, z */
    char pad32C[84];
    int lookMode; /* 0x380, the look-target mode ACTLookTarget_Exec sets */
    char pad384[12];
    float lookPosX; /* 0x390, the look-target position, x */
    float lookPosY; /* 0x394, the look-target position, y */
    float lookPosZ; /* 0x398, the look-target position, z */
    char pad39C[28];
    int word3B8; /* 0x3B8 */
    int word3BC; /* 0x3BC */
    int word3C0; /* 0x3C0 */
    char pad3C4[20];
    float radius; /* 0x3D8, the collision cylinder's radius */
    char pad3DC[36];
    int handIK; /* 0x400, nonzero when HandManager runs the hand IK */
    char pad404[12];
    float ropeBaseX; /* 0x410, the hold point on the chain, x */
    float ropeBaseY; /* 0x414, the hold point on the chain, y */
    float ropeBaseZ; /* 0x418, the hold point on the chain, z */
    char pad41C[4];
    int ropeState; /* 0x420, 0, or -1 and 1 by the hold height on the chain */
    int fixObj;    /* 0x424, the object SetMotionNodeFixModeParameter fixes the node to */
    int fixNode;   /* 0x428, the focus node on that object */
    char pad42C[36];
    float fixWeight; /* 0x450, the fix weight */
    int fixMode;     /* 0x454, the fix mode */
    char pad458[4];
    float ikRate0;  /* 0x45C */
    float handRate; /* 0x460, the default hand rate ResetHandTarget copies */
    float ikRate1;  /* 0x464 */
    float ikRate2;  /* 0x468 */
    char pad46C[20];
    int motFlagsLo; /* 0x480, the motion control flags, low word (MotCtrl at 0x470) */
    int motFlags;   /* 0x484, the motion control flags */
    char pad488[24];
    int motion; /* 0x4A0, the current motion; it indexes motionKind */
    char pad4A4[8];
    float animFrame; /* 0x4AC, the current animation frame */
    char pad4B0[8];
    float speedRatio; /* 0x4B8, the motion play speed ratio */
    char pad4BC[8];
    int word4C4; /* 0x4C4 */
    char pad4C8[4];
    int word4CC; /* 0x4CC */
    char pad4D0[8];
    int rootUpdateMode; /* 0x4D8, the root update mode SetRootUpdateMode sets */
    char pad4DC[8];
    int orientUpdateOff; /* 0x4E4, 1 while the motion orient update is disabled */
    int word4E8;         /* 0x4E8 */
    int posReserve; /* 0x4EC, 1 while a position reservation is pending (execPositionReserver) */
    int word4F0;    /* 0x4F0 */
    char pad4F4[4];
    int word4F8; /* 0x4F8 */
    char pad4FC[24];
    int word514; /* 0x514 */
    char pad518[20];
    int word52C; /* 0x52C */
    char pad530[20];
    int word544;  /* 0x544 */
    int word548;  /* 0x548 */
    int word54C;  /* 0x54C */
    int catchBoy; /* 0x550, 1 while the enemy holds the boy (MoveChestForCatchBoy) */
    char pad554[4];
    int word558;        /* 0x558 */
    float fallHeight;   /* 0x55C, the fall height the death checks compare */
    float groundHeight; /* 0x560, the root's height above the ground */
    int wallHit;        /* 0x564, nonzero when the root hit a wall this frame */
    int word568;        /* 0x568 */
    int word56C;        /* 0x56C */
    char pad570[8];
    int word578; /* 0x578 */
    int word57C; /* 0x57C */
    char pad580[96];
    float float5E0;    /* 0x5E0 */
    float float5E4;    /* 0x5E4 */
    float cliffDepth;  /* 0x5E8, the cliff's depth below the edge */
    int pureWallAttr;  /* 0x5EC */
    int pureCliffAttr; /* 0x5F0 */
    int wallAttr;      /* 0x5F4, the attribute of the wall the root touches */
    int floorAttr;     /* 0x5F8, the attribute of the floor the root stands on */
    char pad5FC[4];
    int frameFlag1; /* 0x600, the motion frame flag GetMotionFrameFlag1 returns */
    int frameFlag2; /* 0x604, the motion frame flag GetMotionFrameFlag2 returns */
    char pad608[28];
    int slipFlags;     /* 0x624, the slip bits of this frame */
    int lastSlipFlags; /* 0x628, the slip bits of the last frame */
    int word62C;       /* 0x62C */
    int pickedWeapon;  /* 0x630, the weapon PickupWeapon picked up */
    int keepWall;      /* 0x634, nonzero to keep the wall contact over getGeometryOfMotion */
    int word638;       /* 0x638 */
    char pad63C[4];
    float waterY;     /* 0x640, the water surface height */
    float waterDepth; /* 0x644, the depth under the pool surface (poolRideFunc) */
    int pool;         /* 0x648, the pool the object stands in */
    int contactFlags; /* 0x64C, the field contact bits CheckFieldContact sets */
    char pad650[4];
    int word654; /* 0x654 */
    char pad658[8];
    int streamScale; /* 0x660, nonzero to scale the stream motion by the node scale */
    char pad664[12];
    float streamOfs[3]; /* 0x670, the stream motion offset */
    char pad67C[312];
    void *motionBuf; /* 0x7B4, the current motion's rotation elements, 32 bytes a skeleton node */
    char pad7B8[8];
    float motionPos[4]; /* 0x7C0, the position GetMatrixOfMotion places the root at */
    void *blendBuf;     /* 0x7D0, the blend source's rotation elements */
    char pad7D4[12];
    float localPos[4]; /* 0x7E0, the position relative to the object at 0x800 */
    char pad7F0[16];
    void *localObj;    /* 0x800, the object the position at 0x7E0 is relative to, 0 for none */
    int localNode;     /* 0x804, the node of that object */
    float localHeight; /* 0x808, the height added to the local position */
    char *nodeRotElem; /* 0x80C, one 64-byte rotation element a skeleton node */
    int nodeLimit;     /* 0x810, one rotation limit record pointer a skeleton node */
    int nodeVec;       /* 0x814, one vector a skeleton node */
    char pad818[4];
    int rideFunc; /* 0x81C, the function an object riding this one calls (CageRideFunc, poolRideFunc) */
    char *blendless;  /* 0x820, one byte a node, set where the motion blend leaves the node alone */
    float scaleRatio; /* 0x824, the geometry scale ratio initGeometryScaleRatio sets */
    char pad828[8];
    void *work;   /* 0x830, the actor's own work record; each actor TU casts it to its own shape */
    int morphNum; /* 0x834, the count of morph weights at 0x838 */
    float *morphWeight; /* 0x838, one weight a morph target of the model's parts */
    int lightId;        /* 0x83C, the light the object carries (0 for none), Light.c */
    char *
        focusNodes; /* 0x840, the skeleton node for each focus point GetSkeltonFocusNode looks up */
    int accessary;  /* 0x844, the object's row in the accessary table */
    char pad848[4];
    unsigned short
        dispType; /* 0x84C, 2 when the object draws its node list, 1 for a cluster model */
    char pad84E[2];
    char *lineHdr;            /* 0x850, read by RegistPacket.c's point and line display */
    struct PObjModel *model;  /* 0x854, DisplayP2O.h */
    struct PObjModel *shadow; /* 0x858 */
    char pad85C[4];
    float shadowDir[4];           /* 0x860, the direction the shadow is cast in */
    struct DObjNode *nodes;       /* 0x870, the node records, nodeNum of them */
    struct LightMatrix *lightMtx; /* 0x874, the object's light matrices (Light.h) */
};

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN.  The 16-byte aligned float
 * quadword the VU0 entry points take and return.  Three TUs (ito/src/stage_orient,
 * sugipon/src/clothAnimation, sugipon/src/waterDot) carried character-for-character
 * the same local definition, which is what makes it one type rather than three;
 * the alignment is the ROM's, whose copies of these values are lq/sq quadword
 * moves.  The name is this repository's: no disc artefact names a type.
 */
typedef struct { /* field names derived */
    float x, y, z, w;
} __attribute__((aligned(16))) VECTOR;

/* RECONSTRUCTION, PUBLIC SDK NAMING RUNG.  The 16-byte aligned integer
 * quadword; the name is the one the public PS2 SDK documentation gives
 * libvu0's integer vector.  It is declared here rather than in
 * sce/libvu0/libvu0.h because StageSetting below uses it and 64 of the TUs
 * that include this header do not include libvu0.h.
 */
typedef int sceVu0IVECTOR[4] __attribute__((aligned(16)));

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
/* Quadword copy, one 128-bit lq/sq pair through a scratch GPR (the nop in
 * the return slot after it is the toolchain's own).  The scratch register
 * differs per call site ($8 in seki/src/Matrix, $6 in
 * sugipon/src/matrixDrive), so it is a macro argument.  dst/src are
 * implicit in $4/$5: the macro is the BODY of a two-pointer wrapper. */
#define QCOPY16(scratch)                                                                           \
    __asm__ __volatile__("lq " scratch ", 0($5)" : : : "memory");                                  \
    __asm__ __volatile__("sq " scratch ", 0($4)" : : : "memory")

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
 *  (e.g. `13` for `$vf13`, `8` for `$8`, `f12` for `$f12`).
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
typedef struct StageSetting { /* field names derived */
    float flatLightDir[3][4]; /* 0x000 */
    float flatLightCol[3][4]; /* 0x030 */
    float ambientCol[4];      /* 0x060 */
    char pad070[16];          /* 0x070 */
    /* the fog words, as ico2/seki/src/ZFog.c reads and edits them */
    int fogOn;       /* 0x080 */
    char pad084[12]; /* 0x084 */
    int fogColR;     /* 0x090 */
    int fogColG;     /* 0x094 */
    int fogColB;     /* 0x098 */
    int fogColA;     /* 0x09C */
    int fogOffsetA;  /* 0x0A0 */
    int fogNear;     /* 0x0A4 */
    int fogFar;      /* 0x0A8 */
    /* the shadow words, as ico2/seki/src/Shadow.c's tool labels them */
    int shadowDepth; /* 0x0AC */                                        /* derived name */
    int shadowBlend[4]; /* 0x0B0, the 1/1, 1/4, 1/16 and 1/64 blends */ /* derived name */
    int shadowColR; /* 0x0C0 */                                         /* derived name */
    int shadowColG; /* 0x0C4 */                                         /* derived name */
    int shadowColB; /* 0x0C8 */                                         /* derived name */
    char pad0CC[4];                                                     /* 0x0CC */
    /* RECONSTRUCTION: the reduction tint used while no sub target is current,
       and the per sub target row whose fourth word is the film grain tint
       ico2/seki/src/GsBase.c reads at 0x13C. */
    int reductionCol[3]; /* 0x0D0 */
    char pad0DC[4];      /* 0x0DC */
    /* RECONSTRUCTION: the stage's view scale, a percentage that
       ico2/seki/src/GsBase.c's gsb_SetVSMatrix divides by 100 into the zoom
       and again into the mip map level. */
    int viewScale; /* 0x0E0 */
    /* 0x0E4 to 0x110: named after the labels ico2/seki/src/GsBase.c's stage
       setting menu prints for them */
    int texSampleMode; /* 0x0E4, "Def Tex Sample Mode" */         /* derived name */
    int postEffect; /* 0x0E8, "Post Effect" */                    /* derived name */
    int depthFieldStart; /* 0x0EC, "DepthField Start" */          /* derived name */
    int depthFieldWidth; /* 0x0F0, "DepthField Width" */          /* derived name */
    int motionBlur;                                               /* 0x0F4, "Motion Blur" */
    int depthFieldLevel; /* 0x0F8, "DepthField Level" */          /* derived name */
    int antiLevel0; /* 0x0FC, "AntiLevel0" */                     /* derived name */
    int antiLevel1; /* 0x100, "AntiLevel1" */                     /* derived name */
    int feedbackEffect; /* 0x104, "Feedback Effect" */            /* derived name */
    char pad108[8];                                               /* 0x108 */
    int feedbackCol[4]; /* 0x110, "Feedback Effect R, G, B, A" */ /* derived name */
    int fogStrength;                                              /* 0x120 */
    char pad124[12];                                              /* 0x124 */

    /* RECONSTRUCTION: each target row is a 16 byte aligned quadword (red,
       green, blue, then the film grain tint), the ROM's own proof being
       gsb_Reduction's tint reads in ico2/seki/src/GsBase.c.  expr.c folds
       a member's constant offset onto the record's base before adding the
       variable index only while the reference's alignment is exactly the
       field's; with the row aligned to 16 it adds base and index first, cse
       puts the index first, and the 0x130 stays the load's displacement,
       which is the ROM's `addu index, index, base` / `lw 0x130`.  The row
       is the typed quadword; it replaced a bare aligned(16) on an r, g, b, a
       struct (re-audit, completeness pass 57), with every user's object
       byte-identical. */
    sceVu0IVECTOR targetCol[4]; /* 0x130 */

    /* RECONSTRUCTION: the film grain's UV step, which
       ico2/seki/src/GsBase.c's gsb_filmNoise passes as raw bits. */
    float grainScale; /* 0x170 */
    char pad174[12];  /* 0x174 */
    /* the camera limits ico2/omori/src/camera-root.c loads per stage, named
       after GsBase.c's menu labels */
    int handCameraLimitP; /* 0x180, "HandCamera Limit P" */ /* derived name */
    int handCameraLimitV; /* 0x184, "HandCamera Limit V" */ /* derived name */
    char pad188[8];                                         /* 0x188 */
    int zoomMaxInDemo; /* 0x190, "ZOOM MAX IN DEMO" */      /* derived name */
    char pad194[8];                                         /* 0x194 */

    struct {
        int a;
        int b;
    } antiLevel[4]; /* 0x19C */

    int subMotionBlur[5]; /* 0x1BC */
} StageSetting;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 3 TUs that carried 3 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union { /* field names derived */
    int c[4];
    long long ll[2];
} __attribute__((aligned(16))) Col4;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct { /* field names derived */
    int gobj;
    float level;
    float levelCap; /* 0x08, the most the level climbs to */
    float capStep;  /* 0x0C, what brainClsTargetLevel takes off the cap */
    float rate;     /* 0x10, the level's rise and decay rate */
    int timer;
    unsigned char byte18;     /* 0x18, nonzero holds the target type at 1 */
    unsigned char alwaysSeen; /* 0x19, nonzero skips the view check */
    unsigned char detail;     /* 0x1A, bit 0 set by brainAddLevelGirlDetail */
    char pad1B[1];
} BrainTarget;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 3 TUs. */
typedef struct { /* field names derived */
    int cur;
    int *buf[2];
    char *dma;
    unsigned long long *ptr;
    char *tail;
    char *gif;
    char *end;
} GifDpk;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 3 TUs. */
typedef union { /* field names derived */
    long long d;
    int w[2];
} GifPkWord;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct { /* field names derived */
    char pad0[32];
    int kind; /* 0x20, debug.c's SE test reads it as the SE kind */
    char pad24[24];
} GsysObjInfo;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 3 TUs. */
typedef union { /* field names derived */
    int i;
    float f;
} IntFloat;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct { /* field names derived */
    char pad0[16];
    int size; /* 0x10 */
    char pad14[12];
    char name[32]; /* 0x20 */
} McDirEnt;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef union { /* field names derived */
    float f[4];
    int i[4];
} Vec4u;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 12 TUs that carried 3 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct PadState {                                           /* field names derived */
    int now; /* 0x00, the buttons held this frame */                /* derived name */
    int flags;                                                      /* 0x04, the trigger bits */
    int rel;                                                        /* 0x08 */
    int rep; /* 0x0C, the auto-repeat bits */                       /* derived name */
    int old; /* 0x10, last frame's buttons (keyInput.c fills it) */ /* derived name */
    unsigned int hist[16]; /* 0x14, per-button held-frame counts */ /* derived name */
    unsigned char ana[4]; /* 0x54, the two analog sticks */         /* derived name */
} PadState;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 8 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union Vec16 { /* field names derived */
    float f[4];
    long long ll[2];
} __attribute__((aligned(16))) Vec16;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the 70-entry object-kind table at
 * objKindData, one 0x64-byte row per kind, indexed by the kind id a GObj carries
 * at +0xC.  The row's leading 0x24 bytes are the kind's name ("BOY", "GIRL",
 * "GIRLDEMOCTRL", ...), which debug.c and debug_menu.c hand straight to the
 * menu as a string.  Five translation units read this row through five
 * different local views (brain, gamesys, sceneManager, debug, debug_menu) and
 * this record is the merge of what all of them know; the offsets that hold a
 * text address in every row are spelled as function pointers.  Field names are
 * this repository's. */
typedef struct {        /* field names derived */
    char name[36];      /* 0x00 */
    float targetTime;   /* 0x24, brain's target timer, -1.0 = none */
    float brainCapStep; /* 0x28, the girl brain's cap step for the kind (BrainTarget) */
    float brainRate;    /* 0x2C, the girl brain's rate for the kind */
    int brainLevel;     /* 0x30, the brain level the kind starts with, 0 for none */
    void (*infoLoad)(); /* 0x34, applies the saved object info to the new GObj */
    void (*infoInit)(); /* 0x38, builds the create arguments from the saved object info */
    void (*uniqDataSet)(int *, int); /* 0x3C, gamesys' per-kind unique-data writer */
    void (*start)();                 /* 0x40, the actor's start process (actBoyStart) */
    int layouted;           /* 0x44, nonzero when the kind is created from the stage layout */
    void (*dl)();           /* 0x48, the display function (BoyDL) */
    int afterGeo;           /* 0x4C, the process CreateGObjByFuncSet adds after the geometry one */
    void (*geo)();          /* 0x50, the geometry process (BoyGeo) */
    void (*hotInit)(int *); /* 0x54, sceneManager's hot-init hook */
    int (*create)(char *, int); /* 0x58, the kind's GObj constructor */
    void (*ai)();               /* 0x5C, the brain process (GirlAI, EnemyAI) */
    void (*before)();           /* 0x60, the object's per-frame function (BeforeFunc); nonzero means
                           the kind takes mail 47 */
} ObjKindEnt;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: the 0x194-byte per-stage preset
 * record at stageData.  Every offset any translation unit reads is named here:
 * the views that stayed local (sceneManager, deja, st25a, script, way_tool,
 * s_init, camera-editor, ebrain, layout_texture, commonact) each say in a
 * comment why their bytes need their own spelling, and this record is the
 * merge of what all of them know.  Field names are this repository's; no disc
 * artefact names a field of this table. */
typedef struct { /* field names derived */
    unsigned char pad0[32];
    char name[64];     /* 0x20, the stage name icoMisc prints */
    float fog[8];      /* 0x60, the fog switch, colour, offset, near and far
                                sceneManager casts into the stage setting record */
    char dataFile[32]; /* 0x80, the data file name access.c builds a path from */
    short ent[24];     /* 0xA0, the stage-manager table entries */
    unsigned char padD0[8];
    float bgCol[3];        /* 0xD8 */
    float ambientCol[3];   /* 0xE4 */
    float flatLightCol[3]; /* 0xF0 */
    float flatLightDir[3]; /* 0xFC */
    int seSegFirst;        /* 0x108, sound data segment range */
    int seSegLast;         /* 0x10C */
    int seEnvFirst;        /* 0x110, sound SE environment range */
    int seEnvLast;         /* 0x114 */
    int camSetId;          /* 0x118, the camera set the stage opens with */
    unsigned char pad11C[12];
    int labelTop;    /* 0x128, generator label range */
    int labelEnd;    /* 0x12C */
    int layoutFirst; /* 0x130, layout range */
    int layoutLast;  /* 0x134 */
    int mdl[4];      /* 0x138, the four stage model ids GetRealModelId picks from */
    unsigned char pad148[4];
    int mot;                /* 0x14C, the motion-set id */
    void (*endproc)(void);  /* 0x150 */
    void (*initproc)(void); /* 0x154, the per-stage init hook */
    unsigned char pad158[12];
    int wayGroupEnd; /* 0x164 */
    unsigned char pad168[8];
    int wayGroupStart; /* 0x170 */
    unsigned char pad174[12];
    float ledgeRange; /* 0x180, how near the girl must be across a ledge (act-env.c squares it) */
    float handCameraRate; /* 0x184 */
    short shadowDepth;    /* 0x188, copied into the stage setting's shadow depth */
    unsigned char pad18A[2];
    /* 0x18C, flag word whose low half is the reverb depth (soundManager reads
     * that half at this offset).  RECONSTRUCTION: bits 25-30 are a bitfield,
     * the stage's movie number StageManager copies into mpegPlay, because the
     * ROM reads it as one: a whole-word field makes expand_expr fold the 0x18C
     * into a constant table base (expr.c 6464-6482), where StageManager's three
     * reads keep the table base, add the index product and load at 0x18C,
     * with the const table's unchanging flag on the load. */
    unsigned int attrLow : 25;
    unsigned int mpegNo : 6;
    unsigned int attrTop : 1;
    /* 0x190, a word of one-bit stage switches.  They are bitfields because the
     * ROM reads them as bitfields: a read off the record itself keeps the
     * const table's unchanging flag on the load and emits the index product
     * as the first operand of the address add (actCommonFall, actCommonEdgeHang). */
    unsigned int flag0 : 1; /* no C reader */
    unsigned int flag1 : 1; /* GeneratorGeo: the stage keeps the boy out; initSceneGObj tests it */
    unsigned int flag2 : 1; /* actCommonEdgeHang: re-clip the hang to the floor */
    unsigned int flag3 : 1; /* actCommonFall: print and keep the low nibble of 0x5F8 */
} StgPre;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 12 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union { /* field names derived */
    float f[4];
    long long ll[2];
} Vec4;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 5 TUs that carried 4 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {  /* field names derived */
    float a[4];   /* 0x00 start point   */
    float b[4];   /* 0x10 end point     */
    float pos[4]; /* 0x20 clipped point */
    char pad30[64];
    float radius;              /* 0x70 clip radius */
    int skipSrc[2];            /* 0x74 the pair _Clip passes with an element, for the element
                        the search must skip */
    int skipElem;              /* 0x7C */
    int wallSrc[2];            /* 0x80 the same pair for the wall the search hit */
    struct FcWallEnt *wallHit; /* 0x88, fieldCollision.h's wall record */
    int floorSrc[2];           /* 0x8C the same pair for the floor the search hit */
    int floorHit;              /* 0x94 */
    char pad98[8];
    float normal[4]; /* 0xA0 */
    int slideCount;  /* 0xB0, times clip_wall_1 ran the ray along a wall's end */
    char padB4[12];
} ClipWork;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct { /* field names derived */
    int girl;
    BrainTarget *cur;
    int lock;           /* 0x08, brainLockGirl: every level held at 0 */
    int spMode;         /* 0x0C, brainSetSpMode's one-frame request */
    int spCount;        /* 0x10, frames the special mode was asked for, clamped */
    float threshold;    /* 0x14, the level a target must pass, decaying to 0x18 */
    float minThreshold; /* 0x18 */
    short targetType;   /* 0x1C, 1 to 3 by the chosen target's level */
    char pad1E[2];
    float targetLevel; /* 0x20, the chosen target's level over the threshold, 0 to 1 */
    short idx;
    char pad26[2];
    BrainTarget tgt[40];
} Brain;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 5 TUs. */
typedef union ActStatus { /* field names derived */
    unsigned long long ll;
    int i[2];
} ActStatus;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record, previously repeated character for character in 2 TUs. */
typedef struct ViTs { /* field names derived */
    long long pts;    /* 0x00 -1 when the pack carried none */
    long long dts;    /* 0x08 */
    int pos;          /* 0x10 byte position in the data ring */
    int len;          /* 0x14 bytes the pair covers, 0 when the slot is free */
} ViTs;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 10 TUs that carried 4 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct Pad {      /* field names derived */
    int now;              /* 0x00, the buttons held */
    int trg;              /* 0x04 */
    char pad08[76];       /* 0x08 */
    unsigned char ana[4]; /* 0x54 */
} Pad;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 4 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct { /* field names derived */
    float pos[3];
    float rot[3];
    int firstWalk0; /* 0x18, the three words test_nextstage_firstwalk_set takes */
    int firstWalk1;
    int firstWalk2;
    int nextStage; /* 0x24, the stage the exit leads to */
} ExitData;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 38 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct ActMail {        /* field names derived */
    int mail;                   /* 0x00 */
    void (*func)(volatile int); /* 0x04 */
    char pad8[8];
} ActMail;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 17 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef union { /* field names derived */
    float f[4];
    long long d[2];
} __attribute__((aligned(16))) ConstVec;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 30 TUs that carried 8 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct PObjGObj { /* field names derived */
    int self;             /* 0x000, the object itself while in use */
    int labelType;        /* 0x004, 1 for a stage layout object */
    int labelId;          /* 0x008, the layout row */
    int kind;             /* 0x00C, the object-kind id, -1 when the object has none */
    int next;             /* 0x010 */
    int prev;             /* 0x014 */
    unsigned char linkId; /* 0x018 */
    char pad19[3];
    unsigned int key; /* 0x01C */
    char pad20[8];
    int fn;                 /* 0x028 */
    struct GProc *procHead; /* 0x02C, head of the object's process list */
    struct GProc *procTail; /* 0x030, tail of the same list */
    char pad34[8];
    int kindNext; /* 0x03C */
    int dlLinkId; /* 0x040, the display list the object is linked into */
    char pad44[4];
    int dl;        /* 0x048, the display function */
    int word4C;    /* 0x04C, read only by GobjProc.c's CreateGObj, through an ObjKindEnt row */
    int drawMask;  /* 0x050, ANDed with a camera's mask */
    int mailQueue; /* 0x054, the mail box (GObj's view) */
    int mailNum;   /* 0x058 */
    int mailType;  /* 0x05C */
    int mailArg;   /* 0x060 */
    char pad64[248];
    int sub; /* 0x15C, the sub-object GObj's own view types as Sub15C * */
    char pad160[4];
    int act; /* 0x164, the actor/action-state object */
    char pad168[4];
    int active;      /* 0x16C */
    int pauseExempt; /* 0x170 */
} PObjGObj;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 38 TUs that carried 6 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
/* Act + 0x438: the way-state word, one 64-bit flag word whose low two bytes
   are also the way walker's two status bytes; bit 16 asks for the detailed
   way search (act-way.c, girl_act.c's attract state) */
typedef union { /* field names derived */
    long long flags;
    unsigned char st[2];

    struct {
        unsigned long long : 16;
        unsigned long long wayDetail : 1;
    } bits;
} WayState;

/* one of the actor's 64-bit wish words (Act + 0x478 .. 0x49F): act-wish.c sets
   and tests their bits, other readers take the low or high word */
typedef union { /* field names derived */
    unsigned long long ll;
    unsigned int w[2];
} ActWishWord;

#include "motionOrientManager.h" /* MotOriReq, which Act carries at 0x620 */

/* The pad configuration record iosPadConnect hands a pad (pad.c's
   iosPadConfDefault and iosPadConfCustom, and the copy each actor keeps), 60
   words: two byte tables and a pair table for the pressure and repeat
   handling (no reader in this build) and, at 0xB0, the sixteen button bits
   iosPadRead ORs. */
typedef struct PadConf { /* field names derived */
    unsigned char press[12][2];
    unsigned char pressRate[24];
    int repeat[16][2];
    int bit[16];
} PadConf;

typedef struct Act { /* field names derived */
    char pad0[4];
    void *actProc; /* 0x4, the actor's action process (actInitialize, actChangeActMain) */
    int motProc;   /* 0x8, the motion thread an interrupt's first function runs in */
    int motProc2;  /* 0xC, the motion thread of its second function */
    int frame;     /* 0x10, the actor's frame count */
    void *after;   /* 0x14, the actor's after function (enemy_act.c's name) */

    union {
        unsigned long long ll;
        void (*afterProc)(char *);
    } flags18; /* 0x18, a 64-bit word: the after-proc in the low word
                  (commonact.c stores actAfterForceRope, afterCommonRopeCliff,
                  actAfterDown and actAfterRopeJump there), the state flags
                  in the high word, which every reader tests as bits 32-63
                  of the doubleword */

    ActStatus flags20;    /* 0x20 */
    int handFreeFrame;    /* 0x28, frames since the boy and girl let go of each other's hands */
    GObj *intrArg;        /* 0x2C, the argument of the mail that interrupted this frame */
    int intrData;         /* 0x30, the mail additional data of that mail */
    int actMode;          /* 0x34, the current action mode; it indexes actModeTbl */
    unsigned int pushDir; /* 0x38, 1 while a box or bar is pushed, -1 while pulled, 0 otherwise */
    int intrMot;          /* 0x3C, the motion the interrupting mail chose */
    int curMot;           /* 0x40, the motion number copied from the display object each frame */
    int orientMot;        /* 0x44, the motion the pull-up mails orient to */
    int actKind;          /* 0x48, the actor's column in actModeTbl */
    int modeFrame;        /* 0x4C, frames since the action mode changed */
    int msgBlockTimer;    /* 0x50, while nonzero, mail 205 is turned away */
    int restartMot;       /* 0x54, the motion the enemy restarts with */
    char pad58[16];
    float statusWait8; /* 0x68, the value char status bit 8 carries (a wait) */
    float statusWait5; /* 0x6C, the value char status bit 5 carries (a wait) */
    float statusVal17; /* 0x70, the value char status bit 17 carries */
    int statusVal18;   /* 0x74, the value char status bit 18 carries */
    int statusTarget;  /* 0x78, the target char status bit 10 carries */
    int statusOther;   /* 0x7C, the object char status bit 2 carries (the nearest active enemy) */
    GObj *gobj80;      /* 0x80 */
    GObj *gobj84;      /* 0x84 */
    int statusObj;     /* 0x88, the object char status bit 11 carries (bomb, gondola, box) */
    char pad8C[4];
    long long paraStatus;              /* 0x90, the parallel status bits ACTParaStatus sets */
    unsigned long long lastParaStatus; /* 0x98, the parallel status bits as last seen */
    long long flags;                   /* 0xA0 */
    int lookTarget; /* 0xA8, the object the actor looks at, 0 for the position at 0xC0 */
    int lookPri;    /* 0xAC, the priority of the current look request */
    int lookMode;   /* 0xB0, the look mode passed to the display object */
    char padB4[12];
    float lookPosX; /* 0xC0, the look position, x */
    float lookPosY; /* 0xC4, the look position, y */
    float lookPosZ; /* 0xC8, the look position, z */
    char padCC[4];
    ActMail *mainMail; /* 0xD0 */
    ActMail *mail;     /* 0xD4 */
    int intrKind;      /* 0xD8, the kind of the mail that last interrupted */
    char padDC[4];
    int readyFlags; /* 0xE0, the hand-in-hand handshake bits: 1 ready begin, 2 ready end, 8 exec end, 0x10 error */
    char padE4[44];
    float camRootX; /* 0x110, the root position the camera follows, x */
    float camRootY; /* 0x114, the root position the camera follows, y */
    float camRootZ; /* 0x118, the root position the camera follows, z */
    char pad11C[4];
    float dir[4]; /* 0x120, the facing direction: enemy_act.c's views
                     name it dir, every actor TU writes the three
                     components */
    void *motReq; /* 0x130: the motion record SetMotionRequest returns */
    int soundMot; /* 0x134, the motion a sound mail asks for (ACTGame_SendSoundMail) */
    char pad138[2];
    short soundWait;  /* 0x13A, frames before the next sound mail is taken */
    int reserved;     /* 0x13C, the actor that reserved this one as a target (ACTReserveTarget) */
    int reservedMail; /* 0x140, the mail the reservation waits for */
    int carrier;      /* 0x144, the enemy carrying the girl */
    struct GObj *carried; /* 0x148, the object the actor holds (the carried girl) */
    char *brainTarget;    /* 0x14C, the enemy brain's target */
    GObj *weapon;         /* 0x150, the weapon the actor holds */
    char *curItem;        /* 0x154, the held item as last published (SetBoyInfo, stage change) */
    void *box;            /* 0x158, the box/truck GObj the actor is holding: commonact.c
                  stores it here in actCommonBox and reads it back through
                  `*(void **)(s + 0x158)` in the boxbar helpers */
    char pad15C[4];
    char *sofa; /* 0x160, the sofa the actor sits on */
    char pad164[12];
    float restartPosX; /* 0x170, the enemy restart position, x */
    float restartPosY; /* 0x174, the enemy restart position, y */
    float restartPosZ; /* 0x178, the enemy restart position, z */
    char pad17C[4];

    /* 0x180 the held item, 0x184 the item about to be taken (act-game.c's
       ItemHold): the item object, which HoldItem, ThrowItem and GetItemKind
       take as an int and the release and compare paths read as a pointer */
    union {
        int i;
        char *p;
    } heldItem;

    union {
        int i;
        char *p;
    } nextItem;

    int attackTurn; /* 0x188, nonzero while the attack turns toward the target */
    char pad18C[4];
    GObj *chain;     /* 0x190, the chain the actor hangs on */
    char *lastChain; /* 0x194, the chain the actor last hung on */
    char pad198[8];
    float ropeSwingX; /* 0x1A0, the rope swing direction, x */
    float ropeSwingY; /* 0x1A4, the rope swing direction, y */
    float ropeSwingZ; /* 0x1A8, the rope swing direction, z */
    char pad1AC[4];
    GObj *attacker; /* 0x1B0, the object whose attack hit the actor */
    char pad1B4[12];
    float attackDirX; /* 0x1C0, the attack direction, x */
    float attackDirY; /* 0x1C4, the attack direction, y */
    float attackDirZ; /* 0x1C8, the attack direction, z */
    char pad1CC[4];
    int damage;       /* 0x1D0, the damage of the attack that hit the actor */
    int hitGroup;     /* 0x1D4, the attack group that hit the actor */
    char downHit;     /* 0x1D8, nonzero when the hit knocks the actor down */
    char stoneHit;    /* 0x1D9, nonzero when the hit turns the actor to stone */
    char hit;         /* 0x1DA, set when the actor goes down, cleared each frame */
    char unguardable; /* 0x1DB, nonzero when the hit cannot be guarded */
    char pad1DC[4];
    float life;      /* 0x1E0, the actor's life */
    float maxLife;   /* 0x1E4, the life the enemy restarts with */
    PadConf padConf; /* 0x1E8, the pad configuration the actor's pad record
                        at 0x2D8 is connected to (actInitialize copies
                        iosPadConfDefault into it) */
    char *padDev;    /* 0x2D8, the pad handle (pad.c's IosPadCtx) starts here: the device record */
    char pad2DC[4];
    int padNow; /* 0x2E0, the buttons held */
    int padTrg; /* 0x2E4, the buttons pressed this frame */
    int padRel; /* 0x2E8, the buttons released this frame */
    char pad2EC[76];
    int stickX;     /* 0x338, the stick record (pad.c's IosPadStick) starts here: the raw x */
    int stickY;     /* 0x33C, the raw y */
    int stickAngle; /* 0x340, the stick's angle to the facing direction */
    char pad344[4];
    float stickDz;  /* 0x348, the stick's normalised z */
    float stickMag; /* 0x34C, the stick's magnitude */
    int wayMode;    /* 0x350, the way follow state: 0 none, 1 search, 2 follow */
    char pad354[44];
    char *wayPoint; /* 0x380, the way point being walked to (the guide-way block at 0x360) */
    char *wayStart; /* 0x384, the start of the walk */
    int wayCross;   /* 0x388, the far end of a crossing */
    char pad38C[24];
    int wayStep; /* 0x3A4, the walk's step */
    char pad3A8[28];
    int wayAvoid; /* 0x3C4, the first point of the guide way round an obstacle, -1 when none */
    char pad3C8[24];
    float wayNodeX; /* 0x3E0, the next way node, x */
    float wayNodeY; /* 0x3E4, the next way node, y */
    float wayNodeZ; /* 0x3E8, the next way node, z */
    char pad3EC[4];
    long long wayFlags;  /* 0x3F0, the way walk flags */
    float wayGoalDist;   /* 0x3F8, the distance to the goal across the floor */
    float wayGoalHeight; /* 0x3FC, the goal's height over the actor */
    char pad400[32];
    float wayDetailX; /* 0x420, the detailed way point, x */
    float wayDetailY; /* 0x424, the detailed way point, y */
    float wayDetailZ; /* 0x428, the detailed way point, z */
    char pad42C[12];
    WayState wayState; /* 0x438 */
    int brainAim;      /* 0x440, the enemy brain's aim: 1 the girl, 2 the boy */
    int infoPos;       /* 0x444, the object info position the enemy is saved at */
    int brainStatus;   /* 0x448, the brain status the actor starts with */
    char pad44C[4];
    int attackGroup; /* 0x450, the actor's attack group */
    int doorFlag;    /* 0x454, the game flag of the door script */
    float doorDist;  /* 0x458, the door's travel */
    float doorStep;  /* 0x45C, the door's step */
    int doorMail;    /* 0x460, the door's main mail list */
    int doorCamWait; /* 0x464, frames to wait after the camera move */
    int doorEndWait; /* 0x468, frames to wait after the move */
    int doorCamera;  /* 0x46C, the camera target of the door move, 0 for none */
    char pad470[8];
    ActWishWord wish0; /* 0x478 */
    ActWishWord wish1; /* 0x480 */
    ActWishWord wish2; /* 0x488 */
    ActWishWord wish3; /* 0x490 */
    ActWishWord wish4; /* 0x498 */
    char pad4A0[16];
    float
        wallOrientX; /* 0x4B0, the environment record (act-env.h's ActEnv) starts here: the wall orientation, x */
    float wallOrientY; /* 0x4B4, the wall orientation, y */
    float wallOrientZ; /* 0x4B8, the wall orientation, z */
    char pad4BC[4];
    float cliffOrientX; /* 0x4C0, the cliff orientation, x */
    float cliffOrientY; /* 0x4C4, the cliff orientation, y */
    float cliffOrientZ; /* 0x4C8, the cliff orientation, z */
    char pad4CC[68];
    float ditchPosX; /* 0x510, the ditch position, x */
    float ditchPosY; /* 0x514, the ditch position, y */
    float ditchPosZ; /* 0x518, the ditch position, z */
    char pad51C[20];
    unsigned char byte530; /* 0x530 */
    char pad531[63];
    float edgePosX; /* 0x570, the edge position, x */
    char pad574[4];
    float edgePosZ; /* 0x578, the edge position, z */
    float edgePosW; /* 0x57C, the edge position's fourth word */
    char pad580[32];
    float pullPosX; /* 0x5A0, the pull position, x */
    float pullPosY; /* 0x5A4, the pull position, y */
    float pullPosZ; /* 0x5A8, the pull position, z */
    char pad5AC[4];
    float sofaPosX; /* 0x5B0, the sofa position, x */
    float sofaPosY; /* 0x5B4, the sofa position, y */
    float sofaPosZ; /* 0x5B8, the sofa position, z */
    char pad5BC[4];
    float turnDirX; /* 0x5C0, the direction the enemy turns from, x */
    float turnDirY; /* 0x5C4, the direction the enemy turns from, y */
    float turnDirZ; /* 0x5C8, the direction the enemy turns from, z */
    char pad5CC[20];
    int wallWord;      /* 0x5E0, the wall's attribute word */
    int cliffSel;      /* 0x5E4, the cliff selection */
    float cliffHeight; /* 0x5E8, the cliff height */
    char pad5EC[8];
    char *holdBoxObj; /* 0x5F4, the box the actor can hold */
    int barObj;       /* 0x5F8, the bar or turning object */
    int pullObj;      /* 0x5FC, the pull lever */
    void *pullKind;   /* 0x600, the pull lever's kind */
    char pad604[4];
    char *swapWeapon; /* 0x608, the weapon the actor can swap to */
    char pad60C[4];
    int cageObj;         /* 0x610, the cage */
    void *bombObj;       /* 0x614, the bomb */
    void *torchRevObj;   /* 0x618, the torch */
    int sofaObj;         /* 0x61C, the sofa */
    MotOriReq motOriReq; /* 0x620, the motion orient request SetMotionRequest
                            takes, filled from the sub-object's at 0x180 */
    char pad640[64];
    struct EnemyBattleWork *enemy;          /* 0x680, the enemy work (enemy_act.c) */
    struct MailAdditionalData *mailAddData; /* 0x684, the mail additional data table */
    int work; /* 0x688, the actor's extended work block (act-game.h's ActWork) */
} Act;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {            /* field names derived */
    float scale[3];         /* 0x00 */
    float rot[3];           /* 0x0C */
    float pos[3];           /* 0x18 */
    int proc;               /* 0x24, a process the generator adds, 0 for the kind's own */
    int *outGObj;           /* 0x28, where the created GObj is stored, 0 for nowhere */
    int mdl;                /* 0x2C */
    int accessary;          /* 0x30, the accessary table row */
    char pad34[4];          /* 0x34 */
    int initArg;            /* 0x38, the last word of the create arguments */
    char pad3C[4];          /* 0x3C */
    unsigned short procPri; /* 0x40, the process priority, shifted by 10 */
    char pad42[2];
    unsigned short parent; /* 0x44 */
    unsigned char kind;    /* 0x46 */
    unsigned char light;   /* 0x47, low five bits the light id */
    unsigned int flags;    /* 0x48, display list in bits 14-16, the generator display bit 21 */
} GenGeo;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct { /* field names derived */
    char pad0[52];
    int action; /* 0x34, the object's row in the action table, 0 for none */
    char pad38[20];
} OaRecA;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct {  /* field names derived */
    int baseMode; /* 0x00, the mode the record returns to, also its BG animation */
    char pad4[8];
    int mode;  /* 0x0C, 972 while held */
    int flags; /* 0x10, bit 0 holds the mode at 972 */
} OaRecB;

/* RECONSTRUCTION, PLACED BY INCLUDE PATTERN: one record for 2 TUs that carried 2 divergent local copies; this body is the one the ROM's bytes accept in the most of them. */
typedef struct { /* field names derived */
    float m[16];
} Mtx44 __attribute__((aligned(16)));

#endif /* TYPEDEF_H */
