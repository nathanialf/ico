#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEneChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bFloorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnemy3);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnemy4);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnemy5);

extern void _ACTWait(int a0);
extern int D_00629DE8;
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);

void actSt01bEnemy6(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x27);
}

void actSt01bFloor(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bWay);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bEnd);

void actSt01bSekizoEvent(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bFloorEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", actSt01bWayOnChk);

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt01bWayOffChk(void) {
    if (func_00178DB0(0x42) == 0) {
        AddWayPointTop(0x2, 0);
        stage_KillPlayBgAnimation(0xA1, 0, 0);
        stage_KillPlayBgAnimation(0x9E, 0, 0);
    } else {
        AddWayPointTop(0x2, 1);
        stage_KillPlayBgAnimation(0xA1, 0, -1);
        stage_KillPlayBgAnimation(0x9E, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", func_0020E210);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st01b", func_0020E340);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
void func_0020E510(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1);
    func_00179710(a0, 0x3D, 0x9C, 0, 0x12, 1000.0f, 528.0f, -150.0f, 1000.0f, 528.0f, -100.0f);
}
