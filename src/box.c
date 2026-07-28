#include "common.h"



extern void LocalizeDirectionOrient();
extern void func_002438B8();
#include "ico/types.h"
INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD408);

INCLUDE_ASM("asm/nonmatchings/src/box", func_001BD668);

INCLUDE_ASM("asm/nonmatchings/src/box", onPath);

INCLUDE_ASM("asm/nonmatchings/src/box", playAnimationCore);

INCLUDE_ASM("asm/nonmatchings/src/box", MoveFloatingBox);

INCLUDE_ASM("asm/nonmatchings/src/box", avoidCharGObj);

INCLUDE_ASM("asm/nonmatchings/src/box", execFloating);

INCLUDE_ASM("asm/nonmatchings/src/box", initFloating);

INCLUDE_ASM("asm/nonmatchings/src/box", _checkItemBreak);

INCLUDE_ASM("asm/nonmatchings/src/box", initLanding);

INCLUDE_ASM("asm/nonmatchings/src/box", execFallDown);

INCLUDE_ASM("asm/nonmatchings/src/box", inertiaMove);

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

INCLUDE_ASM("asm/nonmatchings/src/box", ExecBoxMoveEndReaction);

INCLUDE_ASM("asm/nonmatchings/src/box", BoxGeoRestore);

INCLUDE_ASM("asm/nonmatchings/src/box", BoxExtGeoRestore);

