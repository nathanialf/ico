#include "common.h"



extern int D_00633438;
extern int D_0063343C;
extern int D_0063347C;
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern int D_00633F3C;
INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispSquare2);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", findActPoint);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkActPointWithHeight);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", clearCollisionStatus);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkUpperWallState);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkWallSideState);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkWallState);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkCliffState);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", _checkCliffAndWall);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkCliffAndWallStateOfLastPlane);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkCliffAndWallStateAtJump);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispActNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispLastNode);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", _getGeometryOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", execPositionReserver);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetGeometryOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetMatrixOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DB000);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", getInitialMatrix);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispSkelton);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", SkelTest);

void SkelTestGeo(void)
{
    iosOmBeforeFuncStandard(D_0063347C, 0x18, D_0063347C);
    MatrixDrive_TurnObjectMatrix(D_00633F3C + 0x150, D_00633F3C);
}

void SetHitCollisionDisplay(void)
{
    iosOmBeforeFuncStandard(D_0063347C, 0xF3, D_0063347C);
    MatrixDrive_TurnObjectMatrix(D_00633F3C + 0x150, D_00633F3C);
}

INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetWallVector);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", getGeometryOfMotion);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DCAC8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD1F0);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD668);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DD7A8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE250);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE338);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE428);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE588);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE6B8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DE8D0);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DED10);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DEF20);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF150);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF368);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DF8C0);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001DFBC8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E00F8);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0438);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0708);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0808);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E0860);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001E08B8);

void func_001E0978(int a, int b) {
    D_00633438 = a;
    D_0063343C = b;
}

