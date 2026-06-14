#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eSolarChk);

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05eWater(void) {
    if (func_00178DB0(0xCE) == 0) {
        AddWayPointTop(5, 0);
    } else {
        AddWayPointTop(5, 1);
    }
    if (func_00178DB0(0xEA) == 0) {
        stage_KillPlayBgAnimation(0x126, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x126, 0, -1);
    }
    if (func_00178DB0(0xEB) == 0) {
        stage_KillPlayBgAnimation(0x127, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x127, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eSolar);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterStop);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", actSt05eWaterFlagOn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D370);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D668);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D850);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021D9C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021DAF8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021DDC8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E080);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E1C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E300);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E430);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E570);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E6B0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E7E0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05e", func_0021E8D8);
