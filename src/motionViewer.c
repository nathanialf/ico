#include "common.h"

extern int D_0063BA08;
extern int D_0063BA10;
extern void SetRootUpdateMode(char *self, int val);

void setRootUpdateMode(void)
{
    SetRootUpdateMode(D_0063BA08, D_0063BA10);
}
extern int D_0063BA08;
extern void SetMotionPlaySpeedRatio();

void setMotionSpeed(void)
{
    SetMotionPlaySpeedRatio(D_0063BA08);
}
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", dispProgressBar);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", dispMotFrameProgress);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", objMenuProc);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motKindMenuProc);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motOriMenuProc);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", modeMessage);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", lookAtTest);
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", MotionViewer);
