#include "common.h"



extern int D_00633438;
extern int D_0063343C;
extern int D_0063347C;
extern int iosOmBeforeFuncStandard(char *self_arg, int val5, int val6);
extern void MatrixDrive_TurnObjectMatrix(void *dst, void *src);
extern int D_00633F3C;
INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispSquare2);

INCLUDE_ASM("asm/nonmatchings/src/motionManager", findActPoint);

extern void ClipWallBoxStop(void *a0);
extern char D_004C5B60[];
extern char D_004C5B70[];
extern int D_00633F40;
extern float MatrixDrive_GetTurnZAngleYX(void *a0, void *a1);
extern void MatrixDrive_TurnObjectMatrix__p4(int a0, int a1) __asm__("MatrixDrive_TurnObjectMatrix");
extern int func_00104F20(void);
extern void func_00105268(void);
extern int func_00105278(void);
extern void func_001052A8(void *a0);
extern void func_002438B8(int *a0, int a1, char *a2);
extern void func_002641D8(void *a0, int a1, int a2);

void checkActPointWithHeight(void) {
    char buf[0xC0];
    func_002641D8(buf, 0, 0xC0);
    func_00104F20();
    func_001052A8(D_004C5B60);
    MatrixDrive_TurnObjectMatrix__p4((int)buf, func_00105278() + 0x30);
    func_002438B8((int *)(buf + 0x10), func_00105278(), D_004C5B70);
    func_00105268();
    ClipWallBoxStop(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = MatrixDrive_GetTurnZAngleYX(buf + 0x20, buf);
        D = (int *)D_00633F40;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}

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

extern float D_007097C4[];
extern void func_00105308(float, float, float);
extern void func_0010DF70(char *p);
extern int func_00243BD8(int);

void GetWallVector(void)
{
    int v;
    func_00104F20();
    v = func_00105278();
    func_00243BD8(v);
    {
        register float *p = (float *)D_00633F3C;
        func_00105308(p[0], p[1] - D_007097C4[0], p[2]);
    }
    func_0010DF70((char *)D_00633F3C + 0x30);
    checkActPointWithHeight();
    func_00105268();
}

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

