#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaAfter);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actDejaAfterChk);

extern void _ACTWait(int a0);
extern void iosSemaWait(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f);
extern int actSt25aQueenDeadEvent(void);
extern void soundSeVolSet(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void actConte11Jimaku(float f);
extern void actCreateSubThread(void *fn, int a1);
extern void actE3CageFall(volatile int a0);
extern int D_0062C294;
extern int D_0062C290;
extern int D_0062BBF8;
extern int D_002715D0[];

void actDeja(volatile int a0) {
    while (D_0062C294 == 0 || (D_002715D0[1] & 0x800) == 0) {
        _ACTWait(1);
    }
    iosSemaWait(D_0062C290 + 0x24, 0x22);
    actSt25aQueenBeforeChk(0, 0, 0, 8.0f);
    while (actSt25aQueenDeadEvent() != 0) {
        _ACTWait(1);
    }
    soundSeVolSet(D_0062BBF8);
    stage_KillPlayBgAnimation(0x1F, 0, -1);
    stage_KillPlayBgAnimation(0x19, 0, -1);
    stage_KillPlayBgAnimation(0x20A, -1, -2);
    stage_KillPlayBgAnimation(0x20F, -1, -2);
    stage_KillPlayBgAnimation(0x211, -1, -2);
    stage_KillPlayBgAnimation(0x212, -1, -2);
    stage_KillPlayBgAnimation(0x213, -1, -2);
    stage_KillPlayBgAnimation(0x214, -1, -2);
    stage_KillPlayBgAnimation(0x215, -1, -2);
    stage_KillPlayBgAnimation(0x216, -1, -2);
    stage_KillPlayBgAnimation(0x228, 1, 0);
    actConte11Jimaku(6.0f);
    actCreateSubThread(actE3CageFall, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", actEnemySleep);

extern void AddWayPointTop(int a0, int a1);
extern int func_00178DB0(int a0);

void func_00205BA8(void) {
    AddWayPointTop(7, 0);
    if (func_00178DB0(0x147) != 0) {
        AddWayPointTop(9, 0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205BE8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205CE8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00205E18);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206128);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002064E8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002065F8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002068A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206A20);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206D70);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00206F18(void) {
    stage_KillPlayBgAnimation(0xA1, 0, -1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206F28);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00206FE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00207098);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_00207130);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/deja", func_002071A8);
