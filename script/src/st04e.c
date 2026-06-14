#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWater);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterStop);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", actSt04eWaterFlagOn);

void func_00217198(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_002171A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217288);

void func_00217368(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217378);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217458);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217538);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_002175E0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217668);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217730);

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void func_002177A8(void) {
    if (func_00178DB0(0xC0) == 0) stage_KillPlayBgAnimation(0xCD, 0, 0); else stage_KillPlayBgAnimation(0xCD, 0, -1);
    if (func_00178DB0(0xC1) == 0) stage_KillPlayBgAnimation(0xCE, 0, 0); else stage_KillPlayBgAnimation(0xCE, 0, -1);
    if (func_00178DB0(0xC2) == 0) stage_KillPlayBgAnimation(0xCF, 0, 0); else stage_KillPlayBgAnimation(0xCF, 0, -1);
    if (func_00178DB0(0xC3) == 0) stage_KillPlayBgAnimation(0xD0, 0, 0); else stage_KillPlayBgAnimation(0xD0, 0, -1);
    if (func_00178DB0(0xC4) == 0) stage_KillPlayBgAnimation(0xD1, 0, 0); else stage_KillPlayBgAnimation(0xD1, 0, -1);
    if (func_00178DB0(0xC5) == 0) stage_KillPlayBgAnimation(0xD2, 0, 0); else stage_KillPlayBgAnimation(0xD2, 0, -1);
    if (func_00178DB0(0xC6) == 0) stage_KillPlayBgAnimation(0xD3, 0, 0); else stage_KillPlayBgAnimation(0xD3, 0, -1);
    if (func_00178DB0(0xA9) == 0) AddWayPointTop(1, 0); else AddWayPointTop(1, 1);
    if (func_00178DB0(0xA3) == 0) stage_KillPlayBgAnimation(0xC3, 0, 0); else stage_KillPlayBgAnimation(0xC3, 0, -1);
    if (func_00178DB0(0xA4) == 0) stage_KillPlayBgAnimation(0xC4, 0, 0); else stage_KillPlayBgAnimation(0xC4, 0, -1);
}

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void func_00217990(void) {
    if (func_00178DB0(0xA1) == 0) {
        stage_KillPlayBgAnimation(0xC6, 0, 0);
        stage_KillPlayBgAnimation(0xE5, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC6, 0, -1);
        stage_KillPlayBgAnimation(0xE5, 0, -1);
    }
    if (func_00178DB0(0xA3) == 0) {
        stage_KillPlayBgAnimation(0xC3, 0, 0);
        AddWayPointTop(3, 0);
    } else {
        stage_KillPlayBgAnimation(0xC3, 0, -1);
        AddWayPointTop(3, 1);
    }
    if (func_00178DB0(0xA4) == 0) {
        stage_KillPlayBgAnimation(0xC4, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0xC4, 0, -1);
        AddWayPointTop(4, 1);
    }
    if (func_00178DB0(0xC0) == 0) stage_KillPlayBgAnimation(0xCD, 0, 0); else stage_KillPlayBgAnimation(0xCD, 0, -1);
    if (func_00178DB0(0xC1) == 0) stage_KillPlayBgAnimation(0xCE, 0, 0); else stage_KillPlayBgAnimation(0xCE, 0, -1);
    if (func_00178DB0(0xC2) == 0) stage_KillPlayBgAnimation(0xCF, 0, 0); else stage_KillPlayBgAnimation(0xCF, 0, -1);
    if (func_00178DB0(0xC3) == 0) stage_KillPlayBgAnimation(0xD0, 0, 0); else stage_KillPlayBgAnimation(0xD0, 0, -1);
    if (func_00178DB0(0xC4) == 0) stage_KillPlayBgAnimation(0xD1, 0, 0); else stage_KillPlayBgAnimation(0xD1, 0, -1);
    if (func_00178DB0(0xC5) == 0) stage_KillPlayBgAnimation(0xD2, 0, 0); else stage_KillPlayBgAnimation(0xD2, 0, -1);
    if (func_00178DB0(0xC6) == 0) stage_KillPlayBgAnimation(0xD3, 0, 0); else stage_KillPlayBgAnimation(0xD3, 0, -1);
    if (func_00178DB0(0x91) != 0 && func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xE0, 0, -1);
    }
    if (func_00178DB0(0x91) == 0 || func_00178DB0(0x9B) != 0) {
        stage_KillPlayBgAnimation(0xE0, 0, 0);
    }
    if (func_00178DB0(0xAB) != 0) {
        stage_KillPlayBgAnimation(0xC7, 0, 0xC8);
    } else {
        stage_KillPlayBgAnimation(0xC7, 0, 0);
    }
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00217C58(void) {
    if (func_00178DB0(0xCD) == 0) {
        AddWayPointTop(5, 0);
    } else {
        AddWayPointTop(5, 1);
    }
    if (func_00178DB0(0xA3) == 0) {
        stage_KillPlayBgAnimation(0xC3, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC3, 0, -1);
    }
    if (func_00178DB0(0xA4) == 0) {
        stage_KillPlayBgAnimation(0xC4, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xC4, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217CF0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217E18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04e", func_00217F40);
