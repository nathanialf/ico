#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleCamera2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleShortCut);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleReadTimeDemo0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01_2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo02);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt24aConte01_2);

extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void actSt13aConte01_3(void);

void actOpDemo03Chk(volatile int a0) {
    func_00178DD8(0x137);
    actCreateSubThread(actSt13aConte01_3, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt13aConte01_3);

extern void func_00178E08(int a0);
extern void actEndDemo01(void);

void actOpDemo03(volatile int a0) {
    func_00178E08(0x133);
    func_00178E08(0x137);
    actCreateSubThread(actEndDemo01, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSubMpegReturnPreload);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt26aConte01_1_newgame);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo02Chk);

extern void func_0020AA00(void);

void actSt24aConte01_2_Jimaku(volatile int a0) {
    func_00178DD8(0x13D);
    actCreateSubThread(func_0020AA00, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AA00);

extern void func_0020AAB8(void);

void func_0020AA88(volatile int a0) {
    func_00178DD8(0x13E);
    actCreateSubThread(func_0020AAB8, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AAB8);

extern void actConte14_6(void);

void func_0020AB40(volatile int a0) {
    func_00178DD8(0x13F);
    actCreateSubThread(actConte14_6, 0x15);
}

extern void actCreateSubThread(void *entry, int a1);
extern void actEndDemo07(void);

void func_0020AB70(volatile int a0) {
    actCreateSubThread(actEndDemo07, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AB98);
