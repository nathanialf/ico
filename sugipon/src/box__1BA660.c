#include "common.h"

/* box__1BA660 0x7F0 view (local) */
typedef struct { char _0[0x20]; int f_20; char _pad24[0x34]; int f_58; } BoxGeo2;

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", AlignBox);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", IsThisBoxTruck);

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

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxGeoRestore);

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
