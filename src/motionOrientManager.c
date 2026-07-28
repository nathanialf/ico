#include "common.h"

#include "ico/types.h"




extern unsigned short D_00565060[];
extern int D_00292540[];
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", orientDebug);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetNbMotionFrames);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionPlaySpeedRatio);

extern char *D_00633478;
extern char *D_00633F4C;
extern void MatrixDrive_TurnObjectMatrix__p4(int a0, void *a1) __asm__("MatrixDrive_TurnObjectMatrix");
extern void func_00105258(void);
extern void func_00105268(void);
extern void *func_00105278(void);
extern void func_001D88B8(int id);

void execFrameTrigger(int id) {
    char *e = D_00633478 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    void *m;
    func_00105258();
    func_001D88B8(id);
    o = D_00633F4C + id * 0x10;
    m = func_00105278();
    MatrixDrive_TurnObjectMatrix__p4((int)o, (char *)m + 0x30);
    if (child != -1) {
        execFrameTrigger(child);
    }
    func_00105268();
    if (next != -1) {
        execFrameTrigger(next);
    }
}

void UpdateFrameCounter(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

extern void ChangeFieldCollisionDebugMode();

int sendStateMail(char *a0, float f) {
    char buf[0xC0] __attribute__((aligned(16)));
    MatrixDrive_TurnObjectMatrix__p4((int)buf, a0);
    MatrixDrive_TurnObjectMatrix__p4((int)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ChangeFieldCollisionDebugMode(buf);
    return *(int *)(buf + 0x94);
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionData);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientEndFunc);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientBeginFunc);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ForTest_ForceShiftMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", normalMotionShift);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", parallelMotionShift);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetMotionRequest);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getNodeBlendedFloatingMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionGeometry);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getShapeGeometry);

extern void getNodeBlendedFloatingMotion(int a0, int a1, int a2, int a3);

void getStreamMotionGeometry(int a0, int a1) {
    getNodeBlendedFloatingMotion(a0, a1, a1, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamShapeGeometry);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ExecMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetNodeRotationLimitDataTable);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", CopyBlendMotionDataSource);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetParallelMotionTableWithNoRequest);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetParallelMotionTable);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", InitMotionOrient);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetCurrentMotionDirectionAdjustFlag);

int *ExecuteSlipProc(int start, int end, int a2, int a3) {
    int best = -1;
    if (start < end) {
        do {
            int *p = (int *)(((char *)D_00292540) - (-(start * 0x18)));
            if (p[1] == a3) {
                int *q = (int *)(((char *)D_00292540) + (start * 0x18));
                if (q[0] == a2) {
                    return q;
                }
                if (q[0] == 0x43D) {
                    best = start;
                }
            }
            start++;
        } while (start < end);
    }
    if (best != -1) {
        return (int *)(((char *)D_00292540) + (best * 0x18));
    }
    return (int *)0;
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ExecutePauseSlipProc);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E45E0);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E4700);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E4728);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", func_001E4798);

int func_001E4838(void *a0)
{
  void *p = *((void **) (((char *) a0) + 0x15C));
  int idx = *((int *) (((char *) p) + 0x4A0));
  int new_var;
  new_var = 0x184;
  return (((unsigned int) (*((int *) (((char *)D_00565060 + (idx * 0x190)) + new_var)))) >> 28) & 3;
}

