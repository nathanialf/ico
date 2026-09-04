#include "common.h"

#include "ico/types.h"

typedef struct { char b[0x20]; } ShiftBlk;
extern char D_004EC990[];
extern char D_004EC9A0[];
extern char D_004EC9B0[];
extern char D_004EC9C0[];
extern char D_004EC9D0[];
extern void DrawLineG(void *a0, void *a1, void *a2, void *a3, int a4);
extern char *D_0063B938;
extern char *D_0063C480;
extern int D_0063B93C;
extern int MatrixDrive_GetMatrix(void);
extern void CopyMatrix(void *dst, void *src);
extern void MatrixDrive_PopMatrix(void);
extern void *GetCurrentQuaternion(void);
extern void MatrixDrive_PushMatrixWithNoCopy(void);
extern void PushQuaternionWithNoCopy(void);
extern void _getFinalMatrix(int id);
extern char D_0028FF30[];
extern char D_004EC9E0[];
extern char D_004EC9F0[];
extern char D_004ECA00[];
extern int D_0063C490;
extern int MatrixDrive_PushMatrix(void);
extern void SetQuaternionByAxisRotateV(void *dst, short ang, void *v);
extern void _ApplyMatrix(void *a0, int a1, char *a2);
extern float D_0063B900;
extern char *D_0063C4A4;
extern char D_007201A0[];
extern char D_007201E0[];
extern void GetMatrixFromQuaternion(void *a0, void *a1);
extern void GetMatrixFromQuaternionPos(void *a0, void *a1, void *a2);
extern void *MatrixDrive_GetLastMatrix(void);
extern void _MulMatrix(void *a0, void *a1, void *a2);
extern void _ScaleVectorXYZ(void *buf, void *p1, float f);
extern void ClipWall(void *a0);
extern void CopyVector(void *dst, void *src);
extern char D_004ECA10[];
extern char D_004ECA20[];
extern int D_0063C494;
extern float GetPointDistance(void *a0, void *a1);
extern void MatrixDrive_TransMatrixV(void *a0);
extern void memset(void *a0, int a1, int a2);
extern void sceVu0ApplyMatrix(int *a0, int a1, char *a2);
extern float GetYProjectionOfPlane(int a0, int a1);
extern void MatrixDrive_TransMatrix(float, float, float);
extern void MultiMatrixByQuaternion(char *p);
extern void _UnitMatrix(int a0);
extern void _checkCliffAndWall(void);
extern void checkWallSideState(void);
extern void ClipWallFuchiHangWalkStop(void *a0);
extern char D_004ECA80[];
extern int GetWallAttribute(void *a0);
extern void _AddVectorXYZ(int a0, int a1, void *a2);
extern int adjustSideWall(int a0, int a1, int a2);
extern int iosOmSendMail(char *self_arg, int val5, int val6);
extern float D_007201F4[];
extern void sceVu0UnitMatrix(int);
extern char *D_0063C4A0;
typedef struct {
    int a;
    int b;
} MotShift;
extern char D_004ECB10[];
extern char D_004ECB28[];
extern char D_0061FDC0[];
extern char D_0061FFD8[];
extern char D_0063B920[];
extern char *D_0063C478;
extern char *D_0063C47C;
extern char *D_0063C484;
extern char *D_0063C488;
extern int D_0063C48C;
extern char *D_0063C4A8;
extern void PushQuaternion(void);
extern void SetIdentityQuaternion(void *q);
extern void RotQuaternionY(void *q, short ang);
extern void SetCurrentQuaternion(void *q);
extern void MatrixDrive_SetTransposeMatrix(void *a0, int a1);
extern void sceVu0Normalize(void *dst, void *src);
extern float atan2f(float y, float x);
extern void clearCollisionStatus(void);
extern void *findActPoint(void *a0);
extern void *checkActPointWithHeight(int a0, float h);
extern int sprintf(char *buf, char *fmt, ...);
extern void debug_assertMessage(char *file, int line, char *msg);
extern void __assert(char *file, int line, char *expr);
extern MotShift rootUpdateDirectPlayForStream(void);
extern MotShift rootUpdateXZ(int a0, void *a1);
extern MotShift rootUpdateXZ_MotPos(int a0, void *a1);
extern MotShift rootUpdateStepSolution(int a0);
extern MotShift rootUpdateHang(int a0, void *a1, void *a2);
extern MotShift rootUpdateSwim(void);
extern MotShift rootUpdateNodeFix(void);
extern void rootUpdateY_Rope(void *a0);
extern MotShift rootUpdateY(void);
extern MotShift rootUpdateTrueMotion(int a0);
extern MotShift rootUpdateDirectPlay(int a0);
extern MotShift rootUpdateFly(void);
extern MotShift rootUpdateEnemyFly(void);
extern void func_001ECE40();
extern void gif_EndPacket();
extern void gif_SetAlpha();
extern void gif_StartPacketPri();
extern int sceVu0UnitMatrix__pn(int) __asm__("sceVu0UnitMatrix");
extern int D_0063B148;
extern int D_0063B938__pn __asm__("D_0063B938");
extern void func_001DDAB8_a(char *) __asm__("dispSkelton");
extern void p2o_DispVU1();
extern void MatrixDrive_RotMatrixX(int a0);
extern void func_001ED110(int a0, int a1);
extern void func_0025D440(int a0, int a1, int a2);
extern int D_0063B8F8;
extern int D_0063B8FC;
extern char D_002907E0[];
extern void ClipFloor();
extern char *D_0063B93C__pn __asm__("D_0063B93C");
/* motionManager.h prototypes: their order is the inline tail's emission order */
void SetHitCollisionDisplay(int a, int b);
int ResetMotionProgramInterpInfo(char *a0, int a1);
int SetDirectMotionProgramInterpInfo(char *a0, int a1, float f);
void dispSquare2(void) {
    DrawLineG(D_004EC9A0, D_004EC990, D_004EC9C0, D_004EC990, -1);
    DrawLineG(D_004EC9C0, D_004EC990, D_004EC9B0, D_004EC990, -1);
    DrawLineG(D_004EC9B0, D_004EC990, D_004EC9D0, D_004EC990, -1);
    DrawLineG(D_004EC9D0, D_004EC990, D_004EC9A0, D_004EC990, -1);
}
#include "motMan_getFinalMatrix.c.inc"
inline void SetHitCollisionDisplay(int a, int b) {
    D_0063B8F8 = a;
    D_0063B8FC = b;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", findActPoint);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkActPointWithHeight);
inline void GetWallVector(int a0, int a1)
{
    CopyVector(a0, a1 + 0xA0);
    *(int *)(a0 + 0xC) = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", clearCollisionStatus);
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
ASM_LIT4_SLOT(D_006395B0, 1e+04f);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", checkCliffState);
ASM_LIT4_SLOT(D_006395B4, 1e+04f);
ASM_LIT4_SLOT(D_006395B8, 1e+04f);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", _checkCliffAndWall);
ASM_LIT4_SLOT(D_006395BC, 0.01f);
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
#include "motMan_rootUpdate.c.inc"
static inline void calcMaxNodeHeight(int n) {
    int i;
    *(float *)(D_0063C490 + 0x1D0) = 0.0f;
    for (i = 0; i < n; i++) {
        if (*(float *)(D_0063C490 + 0x1D0) < *(float *)(D_0063C488 + i * 0x10 + 4)) {
            *(float *)(D_0063C490 + 0x1D0) = *(float *)(D_0063C488 + i * 0x10 + 4);
        }
    }
}
void _getGeometryOfMotion(MotShift *out, int second) {
    float v[4];
    char q[0x10];
    int save180 = *(int *)(D_0063C490 + 0x180);

    MatrixDrive_PushMatrix();
    PushQuaternion();
    CopyVector((void *)v, (void *)(D_0063C494 + 0xB0));
    SetIdentityQuaternion(q);
    sceVu0Normalize((void *)v, (void *)v);
    RotQuaternionY(q, atan2f(v[0], v[2]) * 10430.378f);
    CopyQuaternion((char *)D_0063C490 + 0x30, q);
    GetMatrixFromQuaternion((void *)MatrixDrive_GetMatrix(),
                            (char *)D_0063C490 + 0x30);
    SetCurrentQuaternion((char *)D_0063C490 + 0x30);

    D_0063C4A4 = D_0063C478;
    D_0063C4A0 = D_0063C484;
    pursueNaturalGeometry(0);

    if (second) {
        D_0063C4A4 = D_0063C47C;
        D_0063C4A0 = D_0063C488;
        pursueNaturalGeometry(0);
    } else {
        int i;
        for (i = 0; i < D_0063C48C; i++) {
            CopyVector((void *)(D_0063C488 + i * 0x10),
                       (void *)(D_0063C484 + i * 0x10));
        }
    }
    calcMaxNodeHeight(D_0063C48C);

    clearCollisionStatus();
    {
        char *fp = (char *)D_0063C490;
        *(int *)(fp + 0x204) = 0;
        *(int *)(fp + 0x208) = 0;
        *(int *)(fp + 0x20C) = 0;
        CopyVector(fp + 0x60, fp);
    }

    if (*(int *)D_0063C494 != -1) {
        *out = rootUpdateDirectPlayForStream();
    } else {
        char *pm;
        MatrixDrive_PushMatrix();
        pm = (char *)D_0063C494;
        switch (*(int *)(pm + 0x68)) {
        default: {
            char buf[0x400];
            sprintf(buf, D_0061FFD8, D_0063C4A8 + 0xC0, *(int *)(pm + 0x30),
                    *(int *)(pm + 0x68));
            debug_assertMessage(D_0061FDC0, 997, buf);
            __assert(D_0061FDC0, 997, D_0063B920);
        } break;
        case 1:
        case 20:
            *out = rootUpdateXZ(*(int *)(pm + 0x68), findActPoint(D_004ECB10));
            break;
        case 2:
        case 17:
            *out = rootUpdateXZ_MotPos(*(int *)(pm + 0x68),
                                       findActPoint(D_004ECB10));
            break;
        case 7:
        case 8:
        case 9:
        case 13:
        case 16:
            *out = rootUpdateStepSolution(*(int *)(pm + 0x68));
            break;
        case 10:
        case 15:
            *out = rootUpdateHang(*(int *)(pm + 0x68),
                                  checkActPointWithHeight(6, 10.0f),
                                  checkActPointWithHeight(0x16, 10.0f));
            break;
        case 11:
            *out = rootUpdateSwim();
            break;
        case 5:
            *out = rootUpdateNodeFix();
            break;
        case 4:
            rootUpdateY_Rope(findActPoint(D_004ECB28));
            break;
        case 3:
            *out = rootUpdateY();
            break;
        case 0:
        case 19:
            *out = rootUpdateTrueMotion(*(int *)(pm + 0x68));
            break;
        case 6:
        case 14:
            *out = rootUpdateDirectPlay(*(int *)(pm + 0x68));
            break;
        case 12:
            *out = rootUpdateFly();
            break;
        case 18:
            *out = rootUpdateEnemyFly();
            break;
        }
        MatrixDrive_PopMatrix();
    }

    *(float *)(D_0063C494 + 0xF0) = *(float *)(D_0063C490 + 4) +
                                    *(float *)(D_0063B938 + 0x14) -
                                    *(float *)(D_0063C490 + 0x1B4);

    MatrixDrive_PushMatrix();
    MatrixDrive_SetTransposeMatrix((void *)MatrixDrive_GetMatrix(),
                                   MatrixDrive_GetMatrix());
    sceVu0ApplyMatrix((int *)(D_0063C490 + 0x170), MatrixDrive_GetMatrix(),
                      (char *)D_0063C490 + 0x90);
    MatrixDrive_PopMatrix();

    MatrixDrive_PopMatrix();
    PopQuaternion();

    if (*(int *)(D_0063C490 + 0x180) != -1 && save180 == -1) {
        *(int *)(D_0063C494 + 0x1CC) = 1;
    }
}
inline void getGeometryOfMotion(void) {
    ShiftBlk buf;
    int x, y;
    char *p;
    buf = *(ShiftBlk *)(*(char **)(D_0063B93C__pn + 0x15C) + 0x180);
    _getGeometryOfMotion((MotShift *)x, y);
    p = *(char **)(D_0063B93C__pn + 0x15C);
    if (*(int *)(p + 0x634) != 0) {
        *(ShiftBlk *)(p + 0x180) = buf;
    }
}
INCLUDE_ASM("asm/nonmatchings/src/motionManager", execPositionReserver);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetGeometryOfMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", GetMatrixOfMotion);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001ECE40);
INCLUDE_ASM("asm/nonmatchings/src/motionManager", func_001ED110);
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
