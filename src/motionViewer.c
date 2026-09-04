#include "common.h"



extern void SetMotionPlaySpeedRatio();
extern int D_00633540;
extern void ClearMotionBlendlessNode(char *self, int val);
extern int D_00633548;
extern void StopSEPackageWithGroupVariation(void *a0, int a1);
extern void ExecuteSEPackageWithGroupVariation(void *a0, int a1, int a2);

int setRootUpdateMode(void *a0) {
    char *sub = *(char **)((char *)a0 + 0x15C);
    if (*(int *)(sub + 0x628) != *(int *)(sub + 0x624)) {
        StopSEPackageWithGroupVariation(a0, 1);
        if (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x624) & 0x100000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x6D, 1);
        }
        if (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x624) & 0x200000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x6F, 1);
        }
        if (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x624) & 0x400000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x71, 1);
        }
        if (*(int *)(*(char **)((char *)a0 + 0x15C) + 0x624) & 0x800000) {
            ExecuteSEPackageWithGroupVariation(a0, 0x73, 1);
        }
    }
    return 1;
}

extern int D_00274ED4[];
extern void StopSEPackageWithGroupVariation(void *a0, int a1);

int setMotionSpeed(char *a0) {
    if (D_00274ED4[0] != 0) {
        *(int *)(*(char **)(a0 + 0x15C) + 0x628) = 0;
        StopSEPackageWithGroupVariation(a0, 1);
    }
    return 1;
}

void dispProgressBar(void)
{
    ClearMotionBlendlessNode(D_00633540, D_00633548);
}

void dispMotFrameProgress(void)
{
    SetMotionPlaySpeedRatio(D_00633540);
}

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", objMenuProc);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motKindMenuProc);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", motOriMenuProc);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", modeMessage);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", lookAtTest);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", MotionViewer);

INCLUDE_ASM("asm/nonmatchings/src/motionViewer", func_001E5AF8);

