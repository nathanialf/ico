#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", orientDebug);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetNbMotionFrames);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionPlaySpeedRatio);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", execFrameTrigger);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", UpdateFrameCounter);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", sendStateMail);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionData);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientEndFunc);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", shiftMotionOrientBeginFunc);
extern void shiftMotionData(int a0, int a1, int a2, int a3);

void ForTest_ForceShiftMotion(int a0, int a1) {
    shiftMotionData(a0, a1, a1, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", normalMotionShift);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", parallelMotionShift);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetMotionRequest);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getNodeBlendedFloatingMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getShapeGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamMotionGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamBlendMotionGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamBlendShapeGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamShapeGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getStreamMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ExecMotionOrient);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetNodeRotationLimitDataTable);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetMotionOrient);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", getMotionOrient);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", CopyBlendMotionDataSource);
void SetParallelMotionTableWithNoRequest(void *self, int a1, int a2)
{
    char *m = *(char **)((char *)self + 0x15C) + 0x470;

    if (*(int *)(m + 0x18) == 0) {
        *(int *)(m + 0x1C) = a2;
        *(int *)(m + 0x20) = a1;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", SetParallelMotionTable);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", InitMotionOrient);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", GetCurrentMotionDirectionAdjustFlag);
INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ExecuteSlipProc);
extern int D_0028F4D4[];
extern void StopSEPackageWithGroupVariation(void *a0, int a1);

INCLUDE_ASM("asm/nonmatchings/src/motionOrientManager", ExecutePauseSlipProc);
