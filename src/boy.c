#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/boy", dispClothes);
INCLUDE_ASM("asm/nonmatchings/src/boy", execClothes);
INCLUDE_ASM("asm/nonmatchings/src/boy", InitLightLineGeo);
INCLUDE_ASM("asm/nonmatchings/src/boy", LightLineDL);
INCLUDE_ASM("asm/nonmatchings/src/boy", InitBoyGeo);
INCLUDE_ASM("asm/nonmatchings/src/boy", synchronizeMotionOutputOriginForGirl);
INCLUDE_ASM("asm/nonmatchings/src/boy", actionOfWater);
INCLUDE_ASM("asm/nonmatchings/src/boy", BoyGeo);
INCLUDE_ASM("asm/nonmatchings/src/boy", dispSubParts);
INCLUDE_ASM("asm/nonmatchings/src/boy", dispCrown);
INCLUDE_ASM("asm/nonmatchings/src/boy", BoyDL);
void SelectBoyCrown(char *a0, int a1) {
    *(int *)(*(char **)(*(char **)(a0 + 0x15C) + 0x830) + 0x0) = a1;
}
INCLUDE_ASM("asm/nonmatchings/src/boy", LightLineGeo);
INCLUDE_ASM("asm/nonmatchings/src/boy", SetBoyStonizedVisual);
