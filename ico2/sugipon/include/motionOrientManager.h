/*
 * ico2/sugipon/include/motionOrientManager.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what motionOrientManager.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef MOTIONORIENTMANAGER_H
#define MOTIONORIENTMANAGER_H

/* motion-orient: one orientation row, 0x18 bytes, keyed on the current
   motion and the requested kind.  Readers: motionOrientManager.c,
   motionViewer.c, ico2/fumi/src/commonact.c. */
typedef struct {   /* field names derived */
    int id;        /* 0x00 */
    int kind;      /* 0x04 */
    int nextId;    /* 0x08, the motion this row chains to */
    int shiftFrom; /* 0x0C, the frame the shift may start from, -1 for none */
    int shiftMode; /* 0x10, handed to shiftMotionOrientBeginFunc */
    int word14;    /* 0x14 */
} MotionOrientEntry;

/* parallel-motion-orient: one parallel orientation row, 0x14 bytes, the
   first five words of a MotionOrientEntry. Reader: findParallelMotion. */
typedef struct {   /* field names derived */
    int id;        /* 0x00 */
    int kind;      /* 0x04 */
    int nextId;    /* 0x08 */
    int shiftFrom; /* 0x0C */
    int shiftMode; /* 0x10 */
} MotOriParallelEnt;

/* mirror-motion-def: one alternative motion, 8 bytes; six {request,
   substitute} pairs. */
typedef struct { /* field names derived */
    int req;     /* 0x00 */
    int alt;     /* 0x04, -1 for none */
} MotOriAlt;

/* motion-orient-def, moviefile: one 0x20-byte name.  The ROM copies a row
   with ldl/ldr, so the record is 4-aligned and not 8-aligned.  Readers:
   motionOrientManager.c, motionViewer.c, ico2/common/src/main.c
   (movie_init's file). */
typedef struct { /* field names derived */
    char s[32];  /* 0x00 */
} MotOriName;

/* blend-motion-def: one node-blend motion, 0x10 bytes, indexed by the
   motion record's blendKind; the list runs to motion 1147. */
typedef struct { /* field names derived */
    int motion;  /* 0x00, the motion blended from */
    int node;    /* 0x04, the focus node it is blended on */
    float rate;  /* 0x08, its play rate */
    int frames;  /* 0x0C, the frame count, -1 for the motion's own */
} MotOriSub;

/* a limit triple of motion-limit-def, in degrees */
typedef struct { /* field names derived */
    float x, y, z;
} MotOriLimit3;

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
} MotOriLimit;

extern const MotOriParallelEnt parallelMotionOrient[];
extern MotOriAlt mirrorMotionTable[];
extern const MotOriSub blendMotionKind[];
extern const MotOriLimit motionLimitDef[];

/* Reconstruction: the 32-byte orient record an actor hands to
 * SetMotionRequest by value (the EE ABI passes it by reference and the callee
 * copies it into its frame, which is what the ROM's prologue does). The same
 * record is reconstructed in ico2/fumi/src/act.c as IntrOrient, whose matched
 * uses fix the member spelling. */
typedef struct {  /* field names derived */
    int word[8]; /* copied whole, no member read: its eight words */
} MotOriReq;

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order motionOrientManager.c's inline tail has. */
MotionOrientEntry *GetMotionOrient(int i, int n, int id, int kind);
MotionOrientEntry *getMotionOrient(int i, int n, int id, int kind);
void CopyBlendMotionDataSource(void *self, short ang);
void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2);
void SetParallelMotionTable(void *self, int a1, int a2, int a3, int a4);
void InitMotionOrient(void *self, int a1, int a2, int a3, int a4, int a5);

struct GObj;

unsigned int GetCurrentMotionDirectionAdjustFlag(struct GObj *a0);
int ExecuteSlipProc(struct GObj *a0);
int ExecutePauseSlipProc(struct GObj *a0);
void ExecMotionOrient(void *self);
float GetMotionPlaySpeedRatio(int id);
int GetNbMotionFrames(int id);
char *SetMotionRequest(void *self, int mot, MotOriReq req);
void SetNodeRotationLimitDataTable(void *self, int a1, int a2);
void getMotionGeometry(void *self);
void getShapeGeometry(void *self);
void getStreamBlendShapeGeometry(void *self, void *m0, void *m1, float t);
void getStreamShapeGeometry(void *self, void *sm);
int normalMotionShift(void *self, int a1);
void orientDebug(void *self, int mode, int col);
int parallelMotionShift(void *self);
void shiftMotionData(int a0, int a1, int a2, int a3);
/* the rope interpolation rate the chain sets (motionOrientManager.c) */
extern float ropeInterRate;

#endif /* MOTIONORIENTMANAGER_H */
