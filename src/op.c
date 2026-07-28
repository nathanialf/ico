#include "common.h"



extern void func_00122C48(int val);
extern void actConte14_7();
extern void UpdateStormPackage(int x);
extern void actEndDemo01();
extern void actCreateSubThread();
extern void func_0017B288(int bit_idx);
INCLUDE_ASM("asm/nonmatchings/src/op", actTitleCamera2);

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01);

INCLUDE_ASM("asm/nonmatchings/src/op", actTitleShortCut);

INCLUDE_ASM("asm/nonmatchings/src/op", actTitleReadTimeDemo0);

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01_2);

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo01_2Chk);

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo02);

INCLUDE_ASM("asm/nonmatchings/src/op", actSt24aConte01_2);

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo03Chk);

INCLUDE_ASM("asm/nonmatchings/src/op", actSt13aConte01_3);

void actOpDemo03(int a0)
{
    volatile int local = a0;
    func_0017B288(0x134);
    func_0017B288(0x138);
    actCreateSubThread((void *)actEndDemo01, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/src/op", actSubMpegReturnPreload);

INCLUDE_ASM("asm/nonmatchings/src/op", actSt26aConte01_1_newgame);

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo02Chk);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D5A8);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D5D8);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D660);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D690);

INCLUDE_ASM("asm/nonmatchings/src/op", actSt00aEneChk);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D748);

void func_0020D770(int a0)
{
    volatile int local = a0;
    func_00122C48(1);
    UpdateStormPackage(0);
    actCreateSubThread((void *)actConte14_7, 0x15);
}

