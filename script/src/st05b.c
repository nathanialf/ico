#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bCrest01XL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bDoorXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bMonyoDoorXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bBallXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bSekizoEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", actSt05bGirlWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021B580);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0021B618(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9B) == 0) {
        stage_KillPlayBgAnimation(0xB5, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xB5, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0021B678(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9C) == 0) {
        stage_KillPlayBgAnimation(0xB6, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xB6, 0, -1);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_0021B6D8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x9D) == 0) {
        stage_KillPlayBgAnimation(0xB7, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0xB7, 0, -1);
    }
}

extern void func_00178E08(int a0);
void func_0021B738(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0x9F)==0){ *(int*)(actSt25aQueenDeadChk(0x403) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x404) + 0x16C) = 0; stage_KillPlayBgAnimation(0xB9,0,0); } else { stage_KillPlayBgAnimation(0xB9,0,-1); } }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
void func_0021B7B8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xA0) == 0) {
        stage_KillPlayBgAnimation(0xBA, 0, 0);
        *(int *)(actSt25aQueenDeadChk(0x49F) + 0x16C) = 0;
        *(int *)(actSt25aQueenDeadChk(0x4A0) + 0x16C) = 0;
    } else {
        stage_KillPlayBgAnimation(0xBA, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021B830);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021B8B8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021B940);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021B9D8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021BA70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021BAF8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05b", func_0021BB80);
