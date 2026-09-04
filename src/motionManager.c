#include "common.h"

#include "ico/types.h"

typedef struct { char b[0x20]; } ShiftBlk;

extern char D_004EC990[];
extern char D_004EC9A0[];
extern char D_004EC9B0[];
extern char D_004EC9C0[];
extern char D_004EC9D0[];
extern void DrawLineG(void *a0, void *a1, void *a2, void *a3, int a4);

void dispSquare2(void) {
    DrawLineG(D_004EC9A0, D_004EC990, D_004EC9C0, D_004EC990, -1);
    DrawLineG(D_004EC9C0, D_004EC990, D_004EC9B0, D_004EC990, -1);
    DrawLineG(D_004EC9B0, D_004EC990, D_004EC9D0, D_004EC990, -1);
    DrawLineG(D_004EC9D0, D_004EC990, D_004EC9A0, D_004EC990, -1);
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", limitHPAngleAndSetB);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", avoidReverseInterpOnCurrentMatrix);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", avoidReverseInterpOnCurrentMatrixWithLimit);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", _getFinalMatrix);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", EditRotEmphasys);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", getFinalMatrix);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", getFinalMatrixWithNaturalGeometry);
extern float D_0063B900;
extern char *D_0063B938;
extern char *D_0063C4A4;
extern char D_007201A0[];
extern char D_007201E0[];
extern void GetMatrixFromQuaternion(void *a0, void *a1);
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void *MatrixDrive_GetLastMatrix(void);
extern void *MatrixDrive_GetMatrix__pn(void) __asm__("MatrixDrive_GetMatrix");
extern void _MulMatrix(void *a0, void *a1, void *a2);
extern void _ScaleVectorXYZ(void *buf, void *p1, float f);

void _calcNaturalGeometry(int a0) {
    char *elemA = D_0063B938 + a0 * 0x40;
    char *elemB = D_0063C4A4 + a0 * 0x20;
    void *x;
    if (*(int *)(elemA + 0x38) != -1) {
        _ScaleVectorXYZ(D_007201E0, elemA + 0x10, D_0063B900);
        GetMatrixFromQuaternionPos(D_007201A0, elemB + 0x10, D_007201E0);
    } else {
        GetMatrixFromQuaternion(D_007201A0, elemB + 0x10);
    }
    x = MatrixDrive_GetMatrix__pn();
    _MulMatrix(x, MatrixDrive_GetLastMatrix(), D_007201A0);
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", findActPoint);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkActPointWithHeight);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", clearCollisionStatus);
extern void ClipWall(void *a0);
extern void CopyVector(void *dst, void *src);
extern char D_004ECA10[];
extern char D_004ECA20[];
extern int D_0063C494;
extern float GetPointDistance(void *a0, void *a1);
extern int MatrixDrive_GetMatrix(void);
extern void MatrixDrive_PopMatrix(void);
extern int MatrixDrive_PushMatrix(void);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void memset(void *a0, int a1, int a2);
extern void sceVu0ApplyMatrix(int *a0, int a1, char *a2);

void checkUpperWallState(void) {
    char buf[0xC0];
    memset(buf, 0, 0xC0);
    MatrixDrive_PushMatrix();
    MatrixDrive_TransMatrixV(D_004ECA10);
    CopyVector((void *)buf, (void *)(MatrixDrive_GetMatrix() + 0x30));
    sceVu0ApplyMatrix((int *)(buf + 0x10), MatrixDrive_GetMatrix(), D_004ECA20);
    MatrixDrive_PopMatrix();
    ClipWall(buf);
    if (*(int *)(buf + 0x88) != 0) {
        float a;
        int *D;
        a = GetPointDistance(buf + 0x20, buf);
        D = (int *)D_0063C494;
        *(float *)((char *)D + 0x170) = a;
        *(int *)((char *)D + 0x108) = 1;
        *(int *)((char *)D + 0x14) = *(int *)((char *)D + 0x14) | 0x1000;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkWallSideState);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkWallState);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkCliffState);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", _checkCliffAndWall);
extern int D_0063C490;
extern float GetYProjectionOfPlane(int a0, int a1);
extern void MatrixDrive_TransMatrix(float, float, float);
extern void MultiMatrixByQuaternion(char *p);
extern void _UnitMatrix(int a0);
extern void _checkCliffAndWall(void);
extern void checkWallSideState(void);

void checkCliffAndWallStateOfLastPlane(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = (float *)D_0063C490;
        float r = GetYProjectionOfPlane(D_0063C490 + 0x130, D_0063C490);
        MatrixDrive_TransMatrix(p[0], r, *(float *)(D_0063C490 + 8));
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    MatrixDrive_PushMatrix();
    _checkCliffAndWall();
    MatrixDrive_PopMatrix();
    if (*(int *)(D_0063C494 + 0xE4) != 0) {
        MatrixDrive_PushMatrix();
        checkWallSideState();
        MatrixDrive_PopMatrix();
    }
}
void checkCliffAndWallStateAtJump(void)
{
    _UnitMatrix(MatrixDrive_GetMatrix());
    {
        register float *p = (float *)D_0063C490;
        MatrixDrive_TransMatrix(p[0], p[1] + p[116] + 10.0f, p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    _checkCliffAndWall();
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispActNode);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", dispLastNode);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", _wallHitReaction);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", _wallCollisionPreProcess);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", getFieldCollision);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", setIKAndAdjustRootHeight);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", landingFieldAction);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", floorFitting);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateXZ);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateXZ_MotPos);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", adjustSideWall);
extern void ClipWallFuchiHangWalkStop(void *a0);
extern char D_004ECA80[];
extern int GetWallAttribute(void *a0);
extern void _AddVectorXYZ(int a0, int a1, void *a2);
extern void _ApplyMatrix(void *a0, int a1, char *a2);
extern int adjustSideWall(int a0, int a1, int a2);

int checkSideWall(int a0, int a1, int p, int a3, int a4) {
    char buf[0x10];
    int flag;
    int mag;
    int mask;

    *(int *)(p + 0x70) = 0;
    CopyVector((void *)p, (void *)a3);
    sceVu0ApplyMatrix((int *)(p + 0x10), a1, (char *)a0);
    ClipWall((void *)p);

    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    if (*(int *)(D_0063C490 + 0x324) != 0) {
        ClipWallFuchiHangWalkStop((void *)p);
        if (*(int *)(p + 0x88) != 0) {
            flag = 0;
            mag = GetWallAttribute((void *)p);
            switch (*(int *)(D_0063C490 + 0x324)) {
            default:
            case 1:
                mask = 0x20000000;
                break;
            case 2:
                mask = 0x10000000;
                break;
            }
            if (mag & mask) {
                flag = 1;
                if (mag & 0x0FFFFFFF) {
                    return -1;
                }
            }
            if (flag != 0) {
                return adjustSideWall(p, 0, a4);
            }
            goto block12;
        }
    }
block12:
    _ApplyMatrix(buf, a1, D_004ECA80);
    CopyVector((void *)p, (void *)(p + 0x10));
    _AddVectorXYZ(p + 0x10, p, buf);
    ClipWall((void *)p);
    if (*(int *)(p + 0x88) != 0) {
        goto disp_one;
    }
    CopyVector((void *)p, (void *)(p + 0x10));
    CopyVector((void *)(p + 0x10), (void *)(a3 + 0x10));
    ClipWall((void *)p);
    if (*(int *)(p + 0x88) != 0) {
disp_one:
        return adjustSideWall(p, 1, a4);
    }
    return 0;
}
extern int D_0063B93C;
extern int iosOmSendMail(char *self_arg, int val5, int val6);

void forceFallDown(void)
{
    iosOmSendMail(D_0063B93C, 0x18, D_0063B93C);
    CopyVector(D_0063C490 + 0x150, D_0063C490);
}
void forceReset(void) {
    iosOmSendMail(D_0063B93C, 0x103, D_0063B93C);
    CopyVector((char *)D_0063C490 + 0x150, (char *)D_0063C490);
}
extern float D_007201F4[];
extern void sceVu0UnitMatrix(int);

void checkWallUpperWall(void)
{
    int v;
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix(v);
    {
        register float *p = (float *)D_0063C490;
        MatrixDrive_TransMatrix(p[0], p[1] - D_007201F4[0], p[2]);
    }
    MultiMatrixByQuaternion((char *)D_0063C490 + 0x30);
    checkUpperWallState();
    MatrixDrive_PopMatrix();
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", calcWallFittingGeometry);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateHang);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateSwim);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", avoidSideAdjustWall);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateStepSolution);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateTrueMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateDirectPlayForStream);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateDirectPlay);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", keepVerticalZWithQ);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateNodeFix);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateY);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateY_Rope);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateFly);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", rootUpdateEnemyFly);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", _getGeometryOfMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", execPositionReserver);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetGeometryOfMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetMatrixOfMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001ECE40);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001ED110);
extern void func_001ECE40();
extern void gif_EndPacket();
extern void gif_SetAlpha();
extern void gif_StartPacketPri();
extern int sceVu0UnitMatrix__pn(int) __asm__("sceVu0UnitMatrix");

void dispSkelton(void) {
    int v;
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 5, 0x80);
    MatrixDrive_PushMatrix();
    v = MatrixDrive_GetMatrix();
    sceVu0UnitMatrix__pn(v);
    func_001ECE40(0);
    MatrixDrive_PopMatrix();
    gif_EndPacket();
}
extern int D_0063B148;
extern int D_0063B938__pn __asm__("D_0063B938");
extern void func_001DDAB8_a(char *) __asm__("dispSkelton");
extern void p2o_DispVU1();

void SkelTest(char *a0) {
    int sub = *(int *)(a0 + 0x15C);
    int v;
    D_0063B93C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0063B938__pn = v;
    if (v != 0) {
        p2o_DispVU1();
        if (D_0063B148 != 0) {
            func_001DDAB8_a(a0);
        }
    }
}
extern void MatrixDrive_RotMatrixX(int a0);
extern void func_001ED110(int a0, int a1);
extern void func_0025D440(int a0, int a1, int a2);

void SkelTestGeo(char *a0) {
    int sub = *(int *)(a0 + 0x15C);
    int v;
    int i;
    D_0063B93C = (int)a0;
    v = *(int *)(sub + 0x8C);
    D_0063B938__pn = v;
    if (v != 0) {
        int s2;
        sceVu0UnitMatrix__pn(MatrixDrive_GetMatrix());
        MatrixDrive_RotMatrixX(-0x8000);
        func_001ED110(*(int *)(a0 + 0x15C), 0);
        s2 = *(int *)(a0 + 0x15C);
        for (i = 0; i < *(int *)(s2 + 0x88); i++) {
            int e = *(int *)(s2 + 0xC) + i * 0x40;
            func_0025D440(e, s2 + 0x20, e);
            s2 = *(int *)(a0 + 0x15C);
        }
        if (D_0063B148 != 0) {
            func_001DDAB8_a(a0);
        }
    }
}
extern int D_0063B8F8;
extern int D_0063B8FC;

void SetHitCollisionDisplay(int a, int b) {
    D_0063B8F8 = a;
    D_0063B8FC = b;
}
extern char D_002907E0[];
int ResetMotionProgramInterpInfo(char *a0, int a1) {
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = *(char **)(*(char **)(a0 + 0x15C) + 0x80C) + (n << 6);
    if (n < 0) return 0;
    *(int *)e = 0;
    CopyQuaternion(e + 0x20, D_002907E0);
    CopyQuaternion(e + 0x30, D_002907E0);
    return 1;
}
extern char D_002907E0[];
int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f) {
    int n = GetSkeltonFocusNode(a0, a1);
    char *e = *(char **)(*(char **)(a0 + 0x15C) + 0x80C) + (n << 6);
    if (n < 0) return 0;
    *(float *)e = f;
    CopyQuaternion(e + 0x20, D_002907E0);
    CopyQuaternion(e + 0x30, D_002907E0);
    return 1;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", getFinalMatrixCore);
extern char *D_0063B938;
extern char *D_0063C4A0;
extern void *MatrixDrive_GetMatrix__pn(void) __asm__("MatrixDrive_GetMatrix");
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void _calcNaturalGeometry(int id);

void pursueNaturalGeometry(int id) {
    char *e = D_0063B938 + id * 0x40;
    int child = *(int *)(e + 0x30);
    int next = *(int *)(e + 0x34);
    char *o;
    void *m;
    MatrixDrive_PushMatrixWithNoCopy();
    _calcNaturalGeometry(id);
    o = D_0063C4A0 + id * 0x10;
    m = MatrixDrive_GetMatrix__pn();
    CopyVector((void *)o, (char *)m + 0x30);
    if (child != -1) {
        pursueNaturalGeometry(child);
    }
    MatrixDrive_PopMatrix();
    if (next != -1) {
        pursueNaturalGeometry(next);
    }
}
void GetWallVector(int a0, int a1)
{
    CopyVector(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}
extern void ClipFloor();

int upperFieldCheck(char *a0, float f) {
    char buf[0xC0] __attribute__((aligned(16)));
    CopyVector((void *)buf, a0);
    CopyVector((void *)(buf + 0x10), a0);
    *(float *)(buf + 0x14) = *(float *)(buf + 0x14) + f;
    ClipFloor(buf);
    return *(int *)(buf + 0x94);
}
extern char *D_0063B93C__pn __asm__("D_0063B93C");
extern void _getGeometryOfMotion(int a, int b);

void getGeometryOfMotion(void) {
    ShiftBlk buf;
    int x, y;
    char *p;
    buf = *(ShiftBlk *)(*(char **)(D_0063B93C__pn + 0x15C) + 0x180);
    _getGeometryOfMotion(x, y);
    p = *(char **)(D_0063B93C__pn + 0x15C);
    if (*(int *)(p + 0x634) != 0) {
        *(ShiftBlk *)(p + 0x180) = buf;
    }
}
