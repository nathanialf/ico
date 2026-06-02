#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", _FUNC_GetWay_begin);

extern void func_00174650(int a0);
extern int D_00271268[];

void avoid_obstacle2(int a0) {
    D_00271268[0] = 0;
    func_00174650(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", create_box_bridge);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", GetWay_next);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", GetNearNigePointN);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", GetWay_begin);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", BridgeBox);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/way_sys", DeleteGuideWay);
