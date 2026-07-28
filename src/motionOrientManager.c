#include "common.h"




extern unsigned short D_00565060[];
extern int D_00292540[];
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", orientDebug);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetNbMotionFrames);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionPlaySpeedRatio);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", execFrameTrigger);

void UpdateFrameCounter(int a0, int a1)
{
    MatrixDrive_TurnObjectMatrix(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", sendStateMail);

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

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamMotionGeometry);

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

