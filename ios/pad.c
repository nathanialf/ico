#include "common.h"


extern int D_00633C90;
INCLUDE_ASM("asm/nonmatchings/ios/pad", controler_stable_check);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevInit);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevReadFunc);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadRead);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadNormalizeStick);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadGetStick);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadActRequest);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadDevRead);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadGetPort);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadGetSlot);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadGetDevice);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadConnect);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadStickCameraCoord);

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadEnable);

void iosPadDisable(void)
{
    D_00633C90 = 1;
}

void iosPadEnableGet(void) {
    D_00633C90 = 0;
}

int iosPadActInit(void) {
    return D_00633C90;
}

INCLUDE_ASM("asm/nonmatchings/ios/pad", iosPadActStop);

