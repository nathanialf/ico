#include "common.h"

/* box__1BA660 0x7F0 view (local) */
typedef struct { int f_0; char _4[0x1C]; int f_20; char _pad24[0x34]; int f_58; char _pad5C[0xB4]; int f_110; int f_114; char _pad118[0x20]; int f_138; } BoxGeo2;

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", initLanding);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", execFallDown);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", inertiaMove);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxExtGeoRestore);


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
