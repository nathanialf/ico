#include "common.h"



extern void GetHeightOfCliffFromGObj();
extern int D_00633540;
extern void ClearMotionBlendlessNode(char *self, int val);
extern int D_00633548;
INCLUDE_ASM("asm/nonmatchings/src/motionViewer", setRootUpdateMode);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", setMotionSpeed);

void dispProgressBar(void)
{
    ClearMotionBlendlessNode(D_00633540, D_00633548);
}

void dispMotFrameProgress(void)
{
    GetHeightOfCliffFromGObj(D_00633540);
}

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", objMenuProc);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motKindMenuProc);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motOriMenuProc);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", modeMessage);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", lookAtTest);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", MotionViewer);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E5AF8);

