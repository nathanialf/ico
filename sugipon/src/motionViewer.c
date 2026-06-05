#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/motionViewer", setRootUpdateMode);

extern int D_00271254[];
extern void execEff(void *a0, int a1);

int setMotionSpeed(char *a0) {
    if (D_00271254[0] != 0) {
        *(int *)(*(char **)(a0 + 0x15C) + 0x618) = 0;
        execEff(a0, 1);
    }
    return 1;
}

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


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_004C1E30;  /* stride 0x18 */

/* end struct shapes */
