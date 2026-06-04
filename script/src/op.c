#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleCamera2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleShortCut);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleReadTimeDemo0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01_2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo02);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt24aConte01_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo03Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt13aConte01_3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo03);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSubMpegReturnPreload);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt26aConte01_1_newgame);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo02Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actSt24aConte01_2_Jimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AA00);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AA88);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AAB8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AB40);

extern void actCreateSubThread(void *entry, int a1);
extern void actEndDemo07(void);

void func_0020AB70(volatile int a0) {
    actCreateSubThread(actEndDemo07, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AB98);
