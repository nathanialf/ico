#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/girl", func_001DD128);
INCLUDE_ASM("asm/nonmatchings/src/girl", func_001DD340);
INCLUDE_ASM("asm/nonmatchings/src/girl", func_001DD440);
INCLUDE_ASM("asm/nonmatchings/src/girl", InitGirlGeo);
INCLUDE_ASM("asm/nonmatchings/src/girl", GirlGeo);
INCLUDE_ASM("asm/nonmatchings/src/girl", GirlAI);
INCLUDE_ASM("asm/nonmatchings/src/girl", debugWireStringGirl);
extern int debugWireStringGirl(int a0);
extern void func_001DD440(int a0);
extern void p2o_DispVU1(int a0);
extern void p2o_SetDefaultEnviroment(int a0);

void GirlDL(int a0)
{
    p2o_SetDefaultEnviroment(a0);
    p2o_DispVU1(a0);
    func_001DD440(a0);
    return debugWireStringGirl(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/girl", SetGirlClothDispSwitch);
void SetGirlHairDispSwitch(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x28) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/girl", setGirlClothSetting);
