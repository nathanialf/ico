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

/* motion-def's two flag words, read whole or by bit (bit positions as this
   build's readers take them: shiftMotionData, GetCurrentMotionDirectionAdjustFlag,
   shiftMotionOrientBeginFunc, checkMotionShiftRange, ACTRunIntrCorrect) */
typedef union { /* field names derived */
    unsigned int word;

    struct {
        unsigned int : 23;
        unsigned int fuchiMode : 2; /* MotCtrl fuchiMode */
        unsigned int dirAdjust : 2; /* GetCurrentMotionDirectionAdjustFlag */
        unsigned int : 2;
        unsigned int handIK : 2; /* MotCtrl handIK */
        unsigned int : 1;
    } bits;
} MotionModeBits; /* derived name */

typedef union { /* field names derived */
    unsigned int word;

    struct {
        unsigned int : 1;
        unsigned int weaponSwing
            : 1; /* the held weapon's blade is drawn, its hand left to the motion (_getFinalMatrix) */
        unsigned int shiftInside : 1; /* the shift range is the frames the shift may happen in */
        unsigned int chainIkRate : 1; /* findChainInJump sets the IK rates to 0.8 by a chain */
        unsigned int : 1;
        unsigned int parallel : 1; /* played as a parallel motion */
        unsigned int : 1;
        unsigned int carried
            : 1; /* a carried pose: the girl's carry ends on it (commonact.c's becarry check) */
        unsigned int : 2;
        unsigned int dropNode4Turn : 1; /* MotCtrl flag330 */
        unsigned int chainHang
            : 1; /* the boy hangs on a chain: chain.c widens its hang range to 70 */
        unsigned int : 4;
        unsigned int jumpHit : 1;      /* actCommonJump's jump has hit and stops on a mode 1 motion */
        unsigned int avgWallPlane : 1; /* MotCtrl avgWallPlane */
        unsigned int stairStep : 1;    /* MotCtrl stairStep */
        unsigned int intr10Live : 1;   /* actIntrList row 10 stays live (ACTRunIntrCorrect) */
        unsigned int : 1;
        unsigned int adjustRoot : 1; /* the root is turned by adjustAngle */
        unsigned int : 3;
        unsigned int loop : 1; /* the motion loops */
        unsigned int : 6;
    } bits;
} MotionFlags; /* derived name */

/* motion-def: one motion kind, 0x184 bytes, indexed by the motion id the
   motion work carries (Sub15C+0x4A0). The demo's record is PAL's in an
   earlier order: five effect and five sound slots where PAL has twelve
   of each, a Japanese comment, the motion file's path and the name, one
   vibration slot, the switches SetMotionRequest copies into the motion work,
   the memory area, the root update mode, the blend kind and play speed, the
   slope rates, the play mode, the shift and trigger ranges, the input
   frames and two flag words. Each named field is at the offset the demo's
   readers use for the PAL field of that name (ReadMotionFile, orientDebug,
   shiftMotionData, shiftMotionOrientBeginFunc, shiftMotionOrientEndFunc,
   GetMotionPlaySpeedRatio, getMotionGeometry, SlopeIKControl,
   UpdateFrameCounter, execFrameTrigger, ACTParaStatus_Exec,
   ACTGame_CheckPriInputFrame, ACTGetEnvironment); a wordNNN no reader
   names. The generated motion-def member compiles against this record. */
typedef struct {             /* field names derived */
    FDSSlot eff[5];          /* 0x000, effect triggers (frameDependSequence.c) */
    FDSSlot se[5];           /* 0x028, sound triggers (frameDependSequence.c) */
    char comment[48];        /* 0x050, the motion's name in Japanese, EUC-JP; no C reader */
    char path[64];           /* 0x080, the motion file */
    char name[48];           /* 0x0C0 */
    FDSSlot vib[1];          /* 0x0F0, pad vibration */
    float weaponFrame;       /* 0x0F8, the frame the weapon's torch goes out (frameDependSequence.c) */
    int word0FC;             /* 0x0FC */
    int cylinder;            /* 0x100 */
    int adjustAngle;         /* 0x104 */
    int slopeIK;             /* 0x108 */
    int gravity;             /* 0x10C */
    int noStepSearch;        /* 0x110 */
    int dirFrames;           /* 0x114, an int in this build (90, 360, small counts, -1), read by the turn and smoothing helpers (_ACTDebugPrint's maxry) */
    int area;                /* 0x118, the motion memory area: 0 static, 4 dynamic, else swap */
    int wallFeedback;        /* 0x11C */
    float rootOffsetZ;       /* 0x120, the root's offsets the direct-play update takes off the position */
    int rootUpdateMode;      /* 0x124 */
    float rootOffsetY;       /* 0x128 */
    int stepNode;            /* 0x12C */
    float rootOffsetX;       /* 0x130 */
    float landFrame;         /* 0x134, a flying motion follows the floor before this frame, -1 for no floor */
    int blendKind;           /* 0x138, index into blendMotionKind */
    float playSpeedRatio;    /* 0x13C */
    float rate1;             /* 0x140, the slope's play-rate weight (SlopeIKControl) */
    float rate0;             /* 0x144, the slope's foot IK weight (SlopeIKControl) */
    float faceRotRatio;      /* 0x148, the face turn's weight (_getFinalMatrix's blends) */
    int playMode;            /* 0x14C, 1 loops */
    int shiftLength;         /* 0x150 */
    int triggerStart;        /* 0x154 */
    int triggerEnd;          /* 0x158 */
    int trigger2Start;       /* 0x15C */
    int trigger2End;         /* 0x160 */
    float clipRadius;        /* 0x164 */
    int shiftStart;          /* 0x168 */
    int fieldWall;           /* 0x16C */
    int lookIK;              /* 0x170 */
    int handTurnIK;          /* 0x174 */
    short priInputBegin;     /* 0x178 */
    short priInputEnd;       /* 0x17A */
    MotionModeBits modeBits; /* 0x17C */
    MotionFlags flags;       /* 0x180 */
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
void ForTest_ForceShiftMotion(int obj, int motion);

#endif /* MOTIONORIENTMANAGER_H */
