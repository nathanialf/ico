/*
 * ico2/sugipon/include/motionOrientManager.h
 *
 * The declarations of what motionOrientManager.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef MOTIONORIENTMANAGER_H
#define MOTIONORIENTMANAGER_H

#include "typedef.h" /* MotOriReq */

/* motion-orient: one orientation row, 0x18 bytes, keyed on the current
   motion and the requested kind.  Readers: motionOrientManager.c,
   motionViewer.c, ico2/fumi/src/commonact.c. */
typedef struct {     /* field names derived */
    int id;          /* 0x00 */
    int kind;        /* 0x04 */
    int nextId;      /* 0x08, the motion this row chains to */
    int shiftFrom;   /* 0x0C, the frame the shift may start from, -1 for none */
    int shiftMode;   /* 0x10, handed to shiftMotionOrientBeginFunc */
    int word14;      /* 0x14 */
} MotionOrientEntry; /* derived name */

/* parallel-motion-orient: one parallel orientation row, 0x14 bytes, the
   first five words of a MotionOrientEntry. Reader: findParallelMotion. */
typedef struct {     /* field names derived */
    int id;          /* 0x00 */
    int kind;        /* 0x04 */
    int nextId;      /* 0x08 */
    int shiftFrom;   /* 0x0C */
    int shiftMode;   /* 0x10 */
} MotOriParallelEnt; /* derived name */

/* mirror-motion-def: one alternative motion, 8 bytes; six {request,
   substitute} pairs. */
typedef struct { /* field names derived */
    int req;     /* 0x00 */
    int alt;     /* 0x04, -1 for none */
} MotOriAlt;     /* derived name */

/* motion-orient-def, moviefile: one 0x20-byte name, 4-aligned.  Readers:
   motionOrientManager.c, motionViewer.c, ico2/common/src/main.c
   (movie_init's file). */
typedef struct { /* field names derived */
    char s[32];  /* 0x00 */
} MotOriName;    /* derived name */

/* blend-motion-def: one node-blend motion, 0x10 bytes, indexed by the
   motion record's blendKind; the list runs to motion 1147. */
typedef struct { /* field names derived */
    int motion;  /* 0x00, the motion blended from */
    int node;    /* 0x04, the focus node it is blended on */
    float rate;  /* 0x08, its play rate */
    int frames;  /* 0x0C, the frame count, -1 for the motion's own */
} MotOriSub;     /* derived name */

/* a limit triple of motion-limit-def, in degrees */
typedef struct { /* field names derived */
    float x, y, z;
} MotOriLimit3; /* derived name */

/* motion-limit-def: one node's rotation limits, 0x30 bytes: the lower, the
   middle and the upper limit, the focus node, and two words nothing reads.
   SetNodeRotationLimitDataTable swaps rows and triples in place. */
typedef struct {      /* field names derived */
    MotOriLimit3 lo;  /* 0x00 */
    MotOriLimit3 mid; /* 0x0C */
    MotOriLimit3 hi;  /* 0x18 */
    int node;         /* 0x24 */
    float float28;    /* 0x28 */
    int word2C;       /* 0x2C */
} MotOriLimit;        /* derived name */

/* motion-def: one frame-timed trigger of a motion, a frame and a number */
typedef struct { /* field names derived */
    float t;     /* 0x00, the frame */
    int no;      /* 0x04 */
} FDSSlot;       /* derived name */

/* motion-def's three flag words, read whole or by bit */
typedef union { /* field names derived */
    unsigned int word;

    struct {
        unsigned int : 22;
        unsigned int fuchiMode : 2; /* MotCtrl fuchiMode */
        unsigned int : 2;
        unsigned int handIK : 2;    /* MotCtrl handIK */
        unsigned int dirAdjust : 2; /* GetCurrentMotionDirectionAdjustFlag */
        unsigned int : 2;
    } bits;
} MotionModeBits; /* derived name */

typedef union { /* field names derived */
    unsigned int word;

    struct {
        unsigned int : 5;
        unsigned int dropNode4Turn : 1; /* MotCtrl flag330 */
        unsigned int : 4;
        unsigned int carried
            : 1; /* a carried pose: the girl's carry ends on it (commonact.c's becarry check) */
        unsigned int : 3;
        unsigned int parallel : 1; /* played as a parallel motion */
        unsigned int : 1;
        unsigned int shiftInside : 1; /* the shift range is the frames the shift may happen in */
        unsigned int stairStep : 1;   /* MotCtrl stairStep */
        unsigned int intr10Live : 1;  /* actIntrList row 10 stays live (ACTRunIntrCorrect) */
        unsigned int : 1;
        unsigned int avgWallPlane : 1; /* MotCtrl avgWallPlane */
        unsigned int : 2;
        unsigned int adjustRoot : 1; /* the root is turned by adjustAngle */
        unsigned int loop : 1;       /* the motion loops */
        unsigned int clothPlane : 1; /* cloth is pushed out of the object's floor plane */
        unsigned int : 6;
    } bits;
} MotionFlags; /* derived name */

typedef union { /* field names derived */
    unsigned int word;

    struct {
        unsigned int : 1;
        unsigned int weaponSwing
            : 1; /* the held weapon's blade is drawn, its hand left to the motion */
        unsigned int : 30;
    } bits;
} MotionFlags2; /* derived name */

/* motion-def: one motion kind, 0x190 bytes, indexed by the motion id the
   motion work carries (Sub15C+0x4A0): the sound, effect and vibration
   triggers frameDependSequence.c fires, the motion file, the name, the
   switches SetMotionRequest copies into the motion work (MotCtrl), the root
   update mode, the direction frames ico2/fumi's actors read, the shift and
   trigger ranges, the play mode and the speed ratio ExecMotionOrient plays it
   by, the slope rates, the input frames, and three flag words, read whole or
   by bit (modeBits' two nibbles at bits 8 and 12 pick handManager.c's
   motionIKEffKind rows).  The generated motion-def member compiles against
   this record. */
typedef struct {    /* field names derived */
    FDSSlot se[12]; /* 0x000, sound effects */
    FDSSlot eff[5]; /* 0x060, particle effects */
    char path[64];  /* 0x088, derived name: the motion file, no C reader */
    char name[48];  /* 0x0C8 */
    FDSSlot vib[1]; /* 0x0F8, pad vibrations */
    int word100;    /* 0x100 */
    int cylinder; /* 0x104, the motion pushes by cylinder collision, 0 for the standing ones (MotRoot 0x328) */
    int adjustAngle;    /* 0x108, degrees the root is turned by, 0 or 1 for none */
    int slopeIK;        /* 0x10C, MotCtrl slopeIK */
    int gravity;        /* 0x110, MotCtrl gravity */
    int noStepSearch;   /* 0x114, MotCtrl noStepSearch */
    int rootUpdateMode; /* 0x118 */
    int stepNode;       /* 0x11C, the focus node the step solution walks on */
    float
        landFrame; /* 0x120, a flying motion follows the floor before this frame, -1 for no floor */
    float
        rootOffset[3]; /* 0x124, the root's offset the direct-play update takes off the position */
    int wallFeedback;  /* 0x130, the wall work is fed back to the brain */
    int area;          /* 0x134, the motion memory area: 0 static, 4 dynamic, else swap */
    int dirFrames;     /* 0x138 */
    float weaponFrame; /* 0x13C */
    int shiftStart;    /* 0x140 */
    int shiftLength;   /* 0x144 */
    int blendKind;     /* 0x148, index into blendMotionKind, 228 for none */
    float playSpeedRatio; /* 0x14C */
    float rate1;          /* 0x150 */
    float rate0;          /* 0x154 */
    float
        faceRotRatio; /* 0x158, the face turn's weight (the motion viewer's debug_face_rot_w_ratio) */
    int playMode;     /* 0x15C, 1 loops */
    int handTurnIK;   /* 0x160, MotCtrl handTurnIK */
    int triggerStart;        /* 0x164 */
    int lookIK;              /* 0x168, MotCtrl lookIK */
    int triggerEnd;          /* 0x16C */
    int fieldWall;           /* 0x170, MotCtrl fieldWall */
    int trigger2Start;       /* 0x174 */
    int trigger2End;         /* 0x178 */
    float clipRadius;        /* 0x17C, the clip radius a shift eases to, 5 at least */
    short priInputEnd;       /* 0x180 */
    short priInputBegin;     /* 0x182 */
    MotionModeBits modeBits; /* 0x184 */
    MotionFlags flags;       /* 0x188 */
    MotionFlags2 flags2;     /* 0x18C */
} MotionDef;                 /* derived name */

extern const MotOriParallelEnt parallelMotionOrient[];
extern MotOriAlt mirrorMotionTable[];
extern const MotOriSub blendMotionKind[];
extern const MotOriLimit motionLimitDef[];

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionOrientManager.c's inline tail has. */
MotionOrientEntry *GetMotionOrient(int i, int n, int id, int kind);
MotionOrientEntry *getMotionOrient(int i, int n, int id, int kind);
void CopyBlendMotionDataSource(void *self, short ang);
void SetParallelMotionTableWithNoRequest(void *self, int *next, int *req);
void SetParallelMotionTable(void *self, int *next, int *req, int from, int mode);
void InitMotionOrient(void *self, int oriFrom, int oriTo, int limitFrom, int limitTo, int motion);

struct GObj;

unsigned int GetCurrentMotionDirectionAdjustFlag(struct GObj *self);
int ExecuteSlipProc(struct GObj *self);
int ExecutePauseSlipProc(struct GObj *self);
void ExecMotionOrient(void *self);
float GetMotionPlaySpeedRatio(int id);
int GetNbMotionFrames(int id);
int UpdateFrameCounter(void *self);
char *SetMotionRequest(void *self, int mot, MotOriReq req);
void SetNodeRotationLimitDataTable(void *self, int from, int to);
/* the rope interpolation rate the chain sets (motionOrientManager.c) */
extern float ropeInterRate;
void ForTest_ForceShiftMotion(int obj, int motion);

#endif /* MOTIONORIENTMANAGER_H */
