/*
 * ico2/sugipon/include/motionManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONMANAGER_H
#define MOTIONMANAGER_H

struct GObj;

#include "typedef.h"

/* An object and one of its nodes: the motion work opens with the parent
   it is linked to, the rootUpdates return the one they stand on, and the
   wall-hit record at ClipBuf+0x80 is one followed by the hit count.  GetPureVerticalPlane reads it as its `int *cfg` argument (see
   getVerticalElementOfWallNormal in src/motionManager2) and the character
   record keeps a copy at +0xE0.  The object/node pair is its own member: the
   ROM copies it as an eight-byte block and the count as a separate word. */
typedef struct {
    char *obj; /* the object (a GObj) */
    int node;  /* the node index in its geometry */
} ObjNode;     /* derived name */

typedef struct {
    ObjNode o;
    void *n;
} WallCfg;

/* RECONSTRUCTION: the 0xC0-byte field/wall clip request block.  The sweep
   radius at +0x70 is _wallHitReaction's initialiser's single non-zero
   element; +0x74 is the element filter _wallCollisionPreProcess copies in
   from the root block, +0x80 and +0x8C the wall and floor the search hit, each
   an object node and the element, as fieldCollision.h's ClipWork has them.
   The block is quadword aligned: the ROM's constant initialiser of one
   (checkWallSideState's, at 0x61FD00 in .rodata) sits on a 16-byte boundary
   after EditRotEmphasys's 8-aligned strings, the alignment of the points the
   block opens with. */
typedef struct {
    float pt[3][4]; /* 0x00 the start, end and clipped points */
    char _30[0x40];
    float rad;      /* 0x70 sweep radius */
    WallCfg filter; /* 0x74 the element the search skips */
    WallCfg wall;   /* 0x80 the wall the search hit */
    WallCfg floor;  /* 0x8C the floor the search hit */
    int attr;       /* 0x98 */
    char _9C[0x4];
    Vec16 normal; /* 0xA0 the hit plane */
    char _B0[0x10];
} __attribute__((aligned(16))) ClipBuf;

/* RECONSTRUCTION, names ours: a node's 0x40-byte IK state: the blend rate
   _getFinalMatrix eases toward its target, the heading, pitch and pitch step
   of the look turn, and the node's three quaternions. */
typedef struct {
    float rate; /* 0x00 */
    short h;    /* 0x04 */
    short _6;
    short p; /* 0x08 */
    short _A[2];
    short dp;     /* 0x0E */
    float q[4];   /* 0x10 */
    float q20[4]; /* 0x20 */
    float q30[4]; /* 0x30 */
} MotIk;          /* derived name */

/* RECONSTRUCTION, names ours: one entry of a node's interp limit table, in
   degrees: the heading, pitch and bank limits _getFinalMatrix's turns are
   clamped to, read at 12-byte steps (the table's +0x30 and +0x48 headings are
   entries 4 and 6). */
typedef struct {
    float h;
    float p;
    float b;
} MotLimAng; /* derived name */

/* RECONSTRUCTION, names ours: the motion work's root block (the motion work
   + 0xA0, up to its motion-control block at + 0x470), the record skelRoot
   points at.  The position, translation, rotation and the last position are
   what every rootUpdate reads and writes; the wall records are the ones the
   hit tests keep; the lift pair and the turn at + 0x300 are _getFinalMatrix's.
   Fields from the access widths and offsets in this file; names offset-derived
   where nothing names them. */
struct MotRoot {
    float pos[4];   /* 0x0 */
    float trans[4]; /* 0x10 */
    char _pad20[0x10];
    float quat[4]; /* 0x30 */
    char _pad40[0x10];
    short twist; /* 0x50 */
    char _pad52[0x2];
    float twistRate; /* 0x54 */
    char _pad58[0x8];
    float up[4];      /* 0x60 */
    float savePos[4]; /* 0x70 */
    ObjNode hitObj;   /* 0x80 */
    char _pad88[0x8];
    float move[4]; /* 0x90 */
    char _padA0[0x20];
    float height; /* 0xC0 */
    char _padC4[0xC];
    float delta[4];     /* 0xD0 */
    WallCfg wall;       /* 0xE0 */
    int wallCount;      /* 0xEC */
    WallCfg cliffWall;  /* 0xF0, the wall found under the cliff edge (checkCliffState) */
    int cliffWallCount; /* 0xFC, its hit count, -1 once copied */
    WallCfg aheadWall;  /* 0x100, the wall clipWallAhead hit */
    char _pad10C[0x14];
    WallCfg filter; /* 0x120 */
    char _pad12C[0x4];
    Vec16 plane; /* 0x130 */
    char _pad140[0x4];
    void *cliffFloor; /* 0x144, the floor under the cliff edge, 0 for none */
    char _pad148[0x8];
    float last[4];     /* 0x150 */
    float clipFrom[4]; /* 0x160, where the root's wall clip starts */
    float stepMove
        [4]; /* 0x170, the step the motion moves the root by, rotated by the root quaternion */
    int standNode; /* 0x180, the skeleton node the root stands on, -1 for none */
    char _pad184[0xC];
    float focusPos[4];   /* 0x190, the focus node's position */
    float focusLocal[4]; /* 0x1A0, the focus node's position in the root's frame */
    float footPos[4];    /* 0x1B0, the foot position fitted to the floor */
    float reservePos[4]; /* 0x1C0, the reserved position, in world space */
    float
        projHeight; /* 0x1D0, the height above the floor the root keeps (GetRootProjectionPosOfGObj adds it) */
    char _pad1D4[0x2C];
    int word200;   /* 0x200, set by the jump setup, read by the root update */
    int word204;   /* 0x204, set while the root update runs the jump */
    float lift[2]; /* 0x208 */
    char _pad210[0x20];
    int hand1IKMode; /* 0x230, hand 1's turn IK mode, 0 for off */
    int hand1IKLock; /* 0x234 */
    char _pad238[0x8];
    float hand1IKDir[4];  /* 0x240, hand 1's turn target */
    float hand1IKQuat[4]; /* 0x250 */
    char _pad260[0x30];
    int hand0IKMode; /* 0x290, hand 0's turn IK mode, 0 for off */
    int hand0IKLock; /* 0x294 */
    char _pad298[0x8];
    float hand0IKDir[4];  /* 0x2A0, hand 0's turn target */
    float hand0IKQuat[4]; /* 0x2B0 */
    float hand0IKRate;    /* 0x2C0, the slerp rate toward the target */
    int hand0IKReached;   /* 0x2C4, 1 once the target is reached */
    int hand0IKFlag;      /* 0x2C8 */
    char _pad2CC[0x4];
    float armTwist[4]; /* 0x2D0, the arm turn eased toward the hand targets */
    int lookMode;      /* 0x2E0, the look-target mode, 2 to turn the head fully */
    char _pad2E4[0xC];
    float lookPos[4]; /* 0x2F0, the look target */
    short h;          /* 0x300 */
    short p;          /* 0x302 */
    short b;          /* 0x304 */
    char _pad306[0x2];
    int noStepSearch; /* 0x308, the motion forbids the stand-node search */
    int gravity;      /* 0x30C, the motion falls under gravity */
    int slopeIK;      /* 0x310, the motion runs the slope foot IK */
    int stairStep;    /* 0x314, the motion steps the root by 50-unit stairs */
    int lookIK;       /* 0x318, the motion turns the head to lookPos */
    int handTurnIK;   /* 0x31C, the motion turns toward the hand targets (1) */
    int fieldWall;    /* 0x320, the motion clips against field walls */
    int fuchiMode;    /* 0x324, the edge reaction mode */
    char _pad328[0x4];
    int avgWallPlane; /* 0x32C, the motion averages four wall planes */
    int flag330;      /* 0x330, the motion drops node 4's own turn */
    int flag334;      /* 0x334, the motion drops node 6's own turn */
    float radius;     /* 0x338, the clip radius */
    char _pad33C[0x14];
    float cliffPlane[4]; /* 0x350, the plane at the cliff floor's height */
    int handIK;          /* 0x360, nonzero while HandManager runs the hand IK */
    int stepNode;        /* 0x364, the focus node the step solution walks on */
    char _pad368[0x8];
    float holdPoint[4]; /* 0x370, the point the hang hold is measured from */
    int ropeState;      /* 0x380, 0, or -1 and 1 by the hold height on the chain */
    char *fixObj;       /* 0x384, the object SetMotionNodeFixModeParameter fixes the node to */
    int fixNode;        /* 0x388, the focus node on that object */
    char _pad38C[0x4];
    float fixQuat[4];     /* 0x390, the fixed node's turn */
    float fixPos[4];      /* 0x3A0, the fixed node's offset */
    float fixWeight;      /* 0x3B0 */
    unsigned int fixMode; /* 0x3B4 */
    float footIKRate;     /* 0x3B8, the slope IK's blend */
    float ikRate0;        /* 0x3BC, the look IK's blend rate */
    float handRate;       /* 0x3C0, the hand IK's blend rate */
    float ikRate1;        /* 0x3C4 */
    float ikRate2;        /* 0x3C8 */
    char _pad3CC[0x4];
};

/* the 0x08C counter (cleared by shiftMotionData, stepped by
   UpdateFrameCounter) is not an int to the scheduler: in shiftMotionData its
   store does not precede the inlined int table read the other int stores do,
   so its lvalue has an alias set of its own, which a 32-bit enumerated type
   gives (motionOrientManager.c). */
enum MotOriStep { MOTORI_STEP_0 };

/* RECONSTRUCTION, names ours: the motion work's motion-control block (the
   motion work + 0x470), the record skelMotCtrl points at: the stream, the
   status flags, the motion number and the root-update mode the assert in
   _getGeometryOfMotion prints ("ID", "rootUpdateMode"), the wall and cliff
   distances and normals the hit tests leave.  Names offset-derived where
   nothing names them. */
struct MotCtrl {
    int stream;            /* 0x0 */
    int oriFrom;           /* 0x4, the first motionOrient row the request searches */
    int oriTo;             /* 0x8, one past the last */
    int shifted;           /* 0xC, 1 after a motion shift */
    int ctrlFlags;         /* 0x10 */
    unsigned int flags;    /* 0x14 */
    int word18;            /* 0x18 */
    int *shiftReq;         /* 0x1C, the request table searchMotionShift walks, -1 terminated */
    int *shiftNext;        /* 0x20, the motion each request shifts to */
    int shiftFrom;         /* 0x24 */
    int shiftMode;         /* 0x28 */
    int request;           /* 0x2C, the requested motion */
    int motion;            /* 0x30 */
    int noAlt;             /* 0x34, 1 when the mirror table had no alternative */
    int shiftReady;        /* 0x38, the frame lies in the motion's shift range */
    float animFrame;       /* 0x3C, the current animation frame */
    float lastFrame;       /* 0x40 */
    float playTime;        /* 0x44 */
    float speedRatio;      /* 0x48 */
    float playRate;        /* 0x4C */
    float frameRatio;      /* 0x50, the frame, 0 to 1, of a mode 4 motion */
    int waterDrag;         /* 0x54, the play slows in water */
    int justShifted;       /* 0x58, 1 for the frame of a shift */
    int frameEnd;          /* 0x5C, the motion reached its end (its loop kind) */
    int keepUpdateMode;    /* 0x60, the shift keeps rootUpdateMode */
    int updateModeChanged; /* 0x64 */
    int rootUpdateMode;    /* 0x68 */
    int parallelEnded;     /* 0x6C */
    int parallel;          /* 0x70, the motion is a parallel one */
    int orientUpdateOff;   /* 0x74, 1 while the motion orient update is disabled */
    char _pad78[0x4];
    int posReserve;       /* 0x7C, 1 while a position reservation is pending */
    int loopFlag;         /* 0x80 */
    int reserveBlend;     /* 0x84, frames left of the reservation blend */
    int reserveMoved;     /* 0x88 */
    enum MotOriStep step; /* 0x8C, frames since the shift */
    int orientReq;        /* 0x90 */
    int lastMotion;       /* 0x94 */
    int lastNoAlt;        /* 0x98 */
    int shiftFrame;       /* 0x9C, the frame the last motion was left at */
    int blendCount;       /* 0xA0 */
    int blendFrames;      /* 0xA4 */
    char _padA8[0x8];
    float dir[4];       /* 0xB0, the motion direction */
    float lastDir[4];   /* 0xC0 */
    int orientKind;     /* 0xD0 */
    int wordD4;         /* 0xD4 */
    int wordD8;         /* 0xD8 */
    int wordDC;         /* 0xDC */
    int catchBoy;       /* 0xE0, 1 while the enemy holds the boy */
    int wordE4;         /* 0xE4 */
    int wordE8;         /* 0xE8 */
    float fallHeight;   /* 0xEC, the fall height the death checks compare */
    float groundHeight; /* 0xF0, the root's height above the ground */
    int wallHit;        /* 0xF4, a wall was hit this frame */
    int cliffEdge;      /* 0xF8, a cliff edge was found (flag 0x10) */
    int cliffWallHit;   /* 0xFC, a wall under the edge was found */
    int cliffBack;      /* 0x100, the wall behind the edge was found */
    int fieldWallHit;   /* 0x104, a field wall was hit */
    int upperWall;      /* 0x108, a wall above was found (flag 0x1000) */
    int sideWall;       /* 0x10C, a side wall was found */
    float cliffHeight;  /* 0x110, the floor above the edge */
    float cliffDist;    /* 0x114, the distance to the edge */
    char _pad118[0x8];
    float cliffNormal[4];  /* 0x120 */
    float wallFloorHeight; /* 0x130, the floor beyond the wall */
    float wallTopHeight;   /* 0x134 */
    float wallDist;        /* 0x138 */
    char _pad13C[0x4];
    float wallDir[4];        /* 0x140 */
    float wallNormal[4];     /* 0x150 */
    float sideWallNormal[4]; /* 0x160 */
    float upperWallDist;     /* 0x170 */
    float sideWallDist;      /* 0x174 */
    float cliffDepth;        /* 0x178, the cliff's depth below the edge */
    int pureWallAttr;        /* 0x17C */
    int pureCliffAttr;       /* 0x180 */
    int wallAttr;            /* 0x184, the attribute of the wall the root touches */
    int floorAttr;           /* 0x188, the attribute of the floor the root stands on */
    char _pad18C[0x4];
    int frameFlag1;   /* 0x190 */
    int frameFlag2;   /* 0x194 */
    int trigger1;     /* 0x198, the first frame trigger fired this frame */
    int trigger1Done; /* 0x19C */
    int trigger2;     /* 0x1A0, the second frame trigger fired this frame */
    int trigger2Done; /* 0x1A4 */
    char _pad1A8[0x4];
    int word1AC; /* 0x1AC */
    char _pad1B0[0x4];
    int slipFlags;     /* 0x1B4 */
    int lastSlipFlags; /* 0x1B8 */
    int slipOn;        /* 0x1BC, the floor slip attribute bits take effect */
    int pickedWeapon;  /* 0x1C0, the weapon PickupWeapon picked up */
    char _pad1C4[0x8];
    int word1CC;      /* 0x1CC */
    float waterY;     /* 0x1D0, the water surface height */
    float waterDepth; /* 0x1D4, the depth under the pool surface */
    char *obj;        /* 0x1D8 */
    int contactFlags; /* 0x1DC, the field contact bits CheckFieldContact sets */
    int word1E0;      /* 0x1E0 */
    char _pad1E4[0xC];
};

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionManager.c's inline tail has. */
void SetHitCollisionDisplay(int a, int b);
int ResetMotionProgramInterpInfo(struct GObj *a0, int a1);
int SetDirectMotionProgramInterpInfo(struct GObj *a0, int a1, float f);
void GetGeometryOfMotion(void *self, void *m0, void *m1, float *v, float r, char *tbl, int k);
void _checkCliffAndWall(void);
void _getFinalMatrix(int id);
int adjustSideWall(ClipBuf *w, int a1, int a2);
int checkActPointWithHeight(int kind, float h);
void checkCliffState(int a0);
void checkWallSideState(void);
void checkWallState(int flag);
void clearCollisionStatus(void);
int findActPoint(int *list);
void getFinalMatrixWithNaturalGeometry(int id);
void _wallHitReaction(ClipBuf *w, void *pos, void *last, int noSlide);

#endif /* MOTIONMANAGER_H */
