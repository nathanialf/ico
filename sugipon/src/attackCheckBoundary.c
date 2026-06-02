#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryBeforeFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", InitAttackCheckBoundaryManagerGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryManagerGeo);

void AttackCheckBoundaryManagerDL(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", InitAttackCheckBoundaryGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", AttackCheckBoundaryDL);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", actAttackCheckBoundaryStart);

void GetAttackCheckBoundaryRadius(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", CreateAttackCheckBoundary);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/attackCheckBoundary", GetAttackCheckBoundaryManagerStatus);
