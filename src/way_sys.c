#include "common.h"


extern int D_00274EE8[];
extern void func_00176AA0();
INCLUDE_ASM("asm/nonmatchings/src/way_sys", _FUNC_GetWay_begin);

void avoid_obstacle2(void)
{
    D_00274EE8[0] = 0;
    func_00176AA0();
}

INCLUDE_ASM("asm/nonmatchings/src/way_sys", create_box_bridge);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetWay_next);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", func_00176DD0);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetNearNigePointN);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", GetWay_begin);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", BridgeBox);

INCLUDE_ASM("asm/nonmatchings/src/way_sys", DeleteGuideWay);

