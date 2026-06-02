#include "common.h"

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
    int *q = *(int **)((char *)p + 0x7F0);
    return q[8];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", GetBoxGlobalHoldPoint);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", IsThisBoxTruck);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", ExecBoxMoveStartReaction);

int ExecBoxMoveEndReaction(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    int *q = *(int **)((char *)p + 0x7F0);
    return q[0x16];
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxGeoRestore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/box__1BA660", BoxExtGeoRestore);
