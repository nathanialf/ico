#include "common.h"



extern void LocalizeDirectionOrient();
extern void func_002438B8();
#include "ico/types.h"

typedef struct { int f_0; char _4[0x1C]; int f_20; char _pad24[0x34]; int f_58; char _pad5C[0xB4]; int f_110; int f_114; char _pad118[0x20]; int f_138; char _pad13C[0x4]; int f_140; } BoxGeo2;
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD408);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD668);

INCLUDE_ASM("asm/nonmatchings/src/box", onPath);

INCLUDE_ASM("asm/nonmatchings/src/box", playAnimationCore);

INCLUDE_ASM("asm/nonmatchings/src/box", MoveFloatingBox);

INCLUDE_ASM("asm/nonmatchings/src/box", avoidCharGObj);

INCLUDE_ASM("asm/nonmatchings/src/box", execFloating);

INCLUDE_ASM("asm/nonmatchings/src/box", initFloating);

INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemBreak);

extern int D_00275850[];
extern int D_00276140[];
extern int D_004BF7C0[];
extern void GetInverseQuaternion(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void _checkItemBreak(void *a0);
extern void func_00102870(void *self, void *src);
extern int func_00264D60(void);

void initLanding(void *self) {
    char *d = (char *)*(int *)((char *)self + 0x15C);
    char *box = (char *)*(int *)(d + 0x800);
    *(int *)(d + 0x70) = *(int *)((char *)*(int *)(box + 0x160) + 0x70);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x78) = 1;
    GetInverseQuaternion((char *)*(int *)((char *)self + 0x15C) + 0xC0, D_00276140);
    func_00102870(self, D_00276140);
    MatrixDrive_TurnObjectMatrix(box + 0xE0, D_00275850);
    MatrixDrive_TurnObjectMatrix(box + 0xC0, D_00275850);
    MatrixDrive_TurnObjectMatrix(box + 0xD0, D_00275850);
    GetRootMatrixByDObj(box + 0x100, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x520, D_004BF7C0);
    *(short *)(box + 0x118) = (short)func_00264D60();
    _checkItemBreak(self);
}

INCLUDE_ASM("asm/nonmatchings/src/box", execFallDown);

extern void GetPureVerticalPlaneOfCurrentPosition(int a0, void *a1, int a2, void *a3, int a4);
extern void MatrixDrive_TurnZObjectMatrixXY(void *a0, void *a1, void *a2);
extern void execFallDown(void *a0);
extern void func_0010DEC0(void *a0, void *a1, void *a2);
extern float func_00168BA0(void *a0, void *a1);
extern void func_00244448(void *a0, void *a1, float a2);

struct vec4_iner { float x, y, z, w; } __attribute__((aligned(8)));

void inertiaMove(void *self) {
    struct vec4_iner m;
    struct vec4_iner v1;
    struct vec4_iner v2;
    char *box = (char *)*(int *)((char *)*(int *)((char *)self + 0x15C) + 0x800);
    int cond;
    GetRootMatrixByDObj(&m, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x130, D_00275850);
    cond = *(int *)(box + 0x68);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x4AC) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x4A0) = 0x43B;
    if (cond != 0) {
        float t;
        GetPureVerticalPlaneOfCurrentPosition(0, &v1, 0, box + 0x60, 1);
        t = func_00168BA0(&v1, &m);
        *(int *)((char *)&v1 + 0xC) = 0;
        func_00244448(&v2, &v1, -(t - 50.0f));
        MatrixDrive_TurnZObjectMatrixXY(&m, &m, &v2);
    }
    execFallDown(&m);
    func_0010DEC0(box + 0x70, (char *)*(int *)((char *)self + 0x15C) + 0xC0, &m);
}

INCLUDE_ASM("asm/nonmatchings/src/box", action);

INCLUDE_ASM("asm/nonmatchings/src/box", GetBoxHoldPoint);

INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemCollision);

INCLUDE_ASM("asm/nonmatchings/src/box", moveBoxAutoMatic);

INCLUDE_ASM("asm/nonmatchings/src/box", MoveBoxWithHoldPoint);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF7F8);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BF918);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BFFE8);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001C00C0);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001C0538);

int func_001C05A8(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x20);
}

int func_001C05B8(char *self) {
    char *sub = ((GObj *)(self))->p_15C;
    char *p = ((Sub15C *)(sub))->p_800;
    return *(int *)(p + 0x20) == 0;
}

INCLUDE_ASM("asm/nonmatchings/src/box", func_001C05D0);

void ExecBoxMoveStartReaction(int a0, int a1, int a2)
{
    int buf[16];
    LocalizeDirectionOrient(buf);
    func_002438B8(a0, buf, a2);
}

int ExecBoxMoveEndReaction(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x800);
    return q->f_58;
}

extern void func_001BC9B0(int a0);
extern void func_001BC9B8(int a0);

void BoxGeoRestore(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x800);
    if (q->f_58 != 0) {
        if (q->f_110 != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        func_001BC9B0(a0);
        q->f_114 = 0;
    } else {
        func_001BC9B8(a0);
        q->f_114 = 0;
    }
end:
    q->f_110 = 1;
}

extern void ExecFrameDependSequence(void *a0);
extern void execEff(void *a0, int a1);
extern void func_001BC9C0(int a0);
extern void playSEConditionID(int a0, int a1);

void BoxExtGeoRestore(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x800);
    if (q->f_58 == 0 || q->f_110 != 0) {
        ExecFrameDependSequence(self);
        execEff(self, 1);
        playSEConditionID(self, 0x16);
        if (q->f_140 != 0) {
            func_001BC9C0(self);
            q->f_140 = 0;
        }
    }
    q->f_110 = 0;
}

