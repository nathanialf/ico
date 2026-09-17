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

typedef struct {
    int id;
    int kind;
    int nextId; /* 0x08, the motion this row chains to */
    int pad[3];
} MotionOrientEntry;

/* Reconstruction: the 32-byte orient record an actor hands to
 * SetMotionRequest by value (the EE ABI passes it by reference and the callee
 * copies it into its frame, which is what the ROM's prologue does). The same
 * record is reconstructed in ico2/fumi/src/act.c as IntrOrient, whose matched
 * uses fix the member spelling. */
typedef struct {
    int w[8];
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
unsigned int GetCurrentMotionDirectionAdjustFlag(char *a0);
int ExecuteSlipProc(char *a0);
int ExecutePauseSlipProc(char *a0);

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

#endif /* MOTIONORIENTMANAGER_H */
