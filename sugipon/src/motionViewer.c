#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", setRootUpdateMode);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", setMotionSpeed);

extern void ClearMotionBlendlessNode(void *a0, int a1);
extern void *D_0062B820;
extern int D_0062B828;

void dispProgressBar(void) {
    ClearMotionBlendlessNode(D_0062B820, D_0062B828);
}

extern void *D_0062B820;
extern void GetHeightOfCliffFromGObj(void *a0);

void dispMotFrameProgress(void) {
    GetHeightOfCliffFromGObj(D_0062B820);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", objMenuProc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", motKindMenuProc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", motOriMenuProc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", modeMessage);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", lookAtTest);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", MotionViewer);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", func_001E2D78);
