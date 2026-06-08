#include "common.h"

/* box__1BA660 0x7F0 view (local) */
typedef struct { int f_0; char _4[0x1C]; int f_20; char _pad24[0x34]; int f_58; char _pad5C[0xB4]; int f_110; int f_114; char _pad118[0x20]; int f_138; char _pad13C[0x4]; int f_140; } BoxGeo2;

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", dispWheels);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", getNearestPosition);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", onPathInitialize);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", onPath);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", playAnimationCore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", MoveFloatingBox);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", avoidCharGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", execFloating);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", initFloating);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", _checkItemBreak);

extern void GetInverseQuaternion(void *a0, void *a1);
extern void func_00102840(void *self, void *src);
extern int func_002610F0(void);
extern void MatrixDrive_TurnObjectMatrix(void *a0, void *a1);
extern void GetRootMatrixByDObj(void *a0, void *a1);
extern void _checkItemBreak(void *a0);
extern int D_002724B0[];
extern int D_00271BD0[];
extern int D_004BAAC0[];

void initLanding(void *self) {
    char *d = (char *)*(int *)((char *)self + 0x15C);
    char *box = (char *)*(int *)(d + 0x7F0);
    *(int *)(d + 0x70) = *(int *)((char *)*(int *)(box + 0x160) + 0x70);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x78) = 1;
    GetInverseQuaternion((char *)*(int *)((char *)self + 0x15C) + 0xC0, D_002724B0);
    func_00102840(self, D_002724B0);
    MatrixDrive_TurnObjectMatrix(box + 0xE0, D_00271BD0);
    MatrixDrive_TurnObjectMatrix(box + 0xC0, D_00271BD0);
    MatrixDrive_TurnObjectMatrix(box + 0xD0, D_00271BD0);
    GetRootMatrixByDObj(box + 0x100, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x510, D_004BAAC0);
    *(short *)(box + 0x118) = (short)func_002610F0();
    _checkItemBreak(self);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", execFallDown);

extern void GetPureVerticalPlaneOfCurrentPosition(int a0, void *a1, int a2, void *a3, int a4);
extern float func_001669D0(void *a0, void *a1);
extern void func_00240968(void *a0, void *a1, float a2);
extern void MatrixDrive_TurnZObjectMatrixXY(void *a0, void *a1, void *a2);
extern void func_0010E250(void *a0, void *a1, void *a2);
extern void execFallDown(void *a0);

struct vec4_iner { float x, y, z, w; } __attribute__((aligned(8)));

void inertiaMove(void *self) {
    struct vec4_iner m;
    struct vec4_iner v1;
    struct vec4_iner v2;
    char *box = (char *)*(int *)((char *)*(int *)((char *)self + 0x15C) + 0x7F0);
    int cond;
    GetRootMatrixByDObj(&m, self);
    MatrixDrive_TurnObjectMatrix((char *)*(int *)((char *)self + 0x15C) + 0x120, D_00271BD0);
    cond = *(int *)(box + 0x68);
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x49C) = 0;
    *(int *)((char *)*(int *)((char *)self + 0x15C) + 0x490) = 0x43D;
    if (cond != 0) {
        float t;
        GetPureVerticalPlaneOfCurrentPosition(0, &v1, 0, box + 0x60, 1);
        t = func_001669D0(&v1, &m);
        *(int *)((char *)&v1 + 0xC) = 0;
        func_00240968(&v2, &v1, -(t - 50.0f));
        MatrixDrive_TurnZObjectMatrixXY(&m, &m, &v2);
    }
    execFallDown(&m);
    func_0010E250(box + 0x70, (char *)*(int *)((char *)self + 0x15C) + 0xC0, &m);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", action);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", GetBoxHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", _checkItemCollision);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", moveBoxAutoMatic);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", MoveBoxWithHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", ReInitBoxGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", func_001BCC88);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", GetBoxMode);

extern void _checkItemCollision(void *a0);
extern void func_00102828(void *a0);
extern void func_001AB9F8(void *a0);

void AlignBox(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    _checkItemCollision(a0);
    func_00102828(a0);
    if (q->f_0++ >= 0x1F) {
        q->f_0 = 0;
        func_001AB9F8(a0);
    }
}

int CanHoldBox(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    return q->f_20;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxDL);

int GetBoxGlobalHoldPoint(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    return q->f_20 == 0;
}

extern void func_0010F068(void *a0);
extern void func_0010F048(void *a0);
extern void onPathInitialize(void *a0);
extern void execEff(void *a0, int a1);
extern int D_00271254[];

void IsThisBoxTruck(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    func_0010F068(a0);
    func_0010F048(a0);
    if (q->f_58 != 0)
        onPathInitialize(a0);
    if (D_00271254[0] != 0) {
        BoxGeo2 *q2;
        execEff(a0, 1);
        q2 = *(BoxGeo2 **)((char *)(*(int **)((char *)a0 + 0x15C)) + 0x7F0);
        q2->f_138 = 0;
    }
}

extern void LocalizeDirectionOrient(int *buf);
extern void func_0023FDD8(int a, int *buf, int c);

void ExecBoxMoveStartReaction(int a0, int a1, int a2)
{
    int buf[16];
    LocalizeDirectionOrient(buf);
    func_0023FDD8(a0, buf, a2);
}

int ExecBoxMoveEndReaction(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    return q->f_58;
}

extern void InitBoxGeo(void *a0);
extern void execAutoMove(void *a0);

void BoxGeoRestore(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    if (q->f_58 != 0) {
        if (q->f_110 != 0) {
            goto end;
        }
    }
    if (a1 >= 0) {
        InitBoxGeo(a0);
        q->f_114 = 0;
    } else {
        execAutoMove(a0);
        q->f_114 = 0;
    }
end:
    q->f_110 = 1;
}

extern void ExecFrameDependSequence(void *a0);
extern void playSEConditionID(void *a0, int a1);
extern void initWheels(void *a0);

void BoxExtGeoRestore(void *self) {
    int *p = *(int **)((char *)self + 0x15C);
    BoxGeo2 *q = *(BoxGeo2 **)((char *)p + 0x7F0);
    if (q->f_58 == 0 || q->f_110 != 0) {
        ExecFrameDependSequence(self);
        execEff(self, 1);
        playSEConditionID(self, 0x16);
        if (q->f_140 != 0) {
            initWheels(self);
            q->f_140 = 0;
        }
    }
    q->f_110 = 0;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_8;  /* 0x08 */
} S_00288C88;  /* stride 0x28 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_004BA770;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00610FF0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00611030;  /* stride 0x4 */

/* end struct shapes */
