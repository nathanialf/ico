#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", controler_stable_check);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevReadFunc);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadNormalizeStick);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadGetStick);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadActRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadDevRead);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadGetPort);

extern unsigned char D_0027D540[];

int iosPadGetSlot(int a0, int a1) {
    return *(int *)&D_0027D540[a1 * 0x200];
}

int iosPadGetDevice(int a0, int a1) {
    int *base = (int *)&D_0027D540[a1 * 0x200];
    return base[1];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadConnect);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadStickCameraCoord);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadEnable);

extern int D_0062BF98;

void iosPadDisable(void) {
    D_0062BF98 = 1;
}

extern int D_0062BF98;

void iosPadEnableGet(void) {
    D_0062BF98 = 0;
}

int iosPadActInit(void) {
    return D_0062BF98;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/pad", iosPadActStop);
