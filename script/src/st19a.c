#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aHaguruma);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aHagurumaChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aPipeChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChainDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChainUp);

void actSt19aOri(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aPipe);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aPipeXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19bIntro);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aOriUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", actSt19aChainMain);

extern void Generator_Mask(int a0);
extern void Generator_ResetCount(int a0);

void actSt19aChainSwitch(volatile int a0) {
    Generator_Mask(a0);
    Generator_ResetCount(a0);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt19bIntroChk(void) {
    if (func_00178DB0(0x14)) {
        AddWayPointTop(9, 0);
    }
}

extern void func_00178DD8(int a0);
extern void func_00178E08(int a0);

void func_0022E2E8(void) {
    if (func_00178DB0(0x1D) == 0) {
        func_00178DD8(0x164);
    } else {
        func_00178E08(0x164);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", func_0022E318);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st19a", func_0022E438);
