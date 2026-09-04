#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/op", actTitleReadTimeDemo0);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01_2);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01_2Chk);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo02);
INCLUDE_ASM("asm/nonmatchings/src/op", actSt24aConte01_2);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo03Chk);
INCLUDE_ASM("asm/nonmatchings/src/op", actSt13aConte01_3);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo03);
extern int D_0028F4C0[];
extern void _ACTWait(int a0);
extern void stgmgrNextStagePreLoadForceNoCancel(int a0);
extern void stgmgrNextStagePreLoadForceStageSet(int a0);

void actSubMpegReturnPreload(volatile int a0) {
    _ACTWait((int)((float)((0x3C - D_0028F4C0[0] * 0xA) / D_0028F4C0[1]) * 5.0f));
    stgmgrNextStagePreLoadForceStageSet(1);
    stgmgrNextStagePreLoadForceNoCancel(1);
}
INCLUDE_ASM("asm/nonmatchings/src/op", actSt26aConte01_1_newgame);
INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo02Chk);
INCLUDE_ASM("asm/nonmatchings/src/op", actSt24aConte01_2_Jimaku);
