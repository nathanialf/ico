#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cDoorDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt04rDoorChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt04rDoor2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cWaterXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt04rDoor);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt04rDoor2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cDoorDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cEne);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", actSt05cDoorDownEvent);

void actSt05cDoorDownEffect(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05cEneChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2C0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2D0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2E0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C2F0(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void func_0021C300(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (func_00178DB0(0xA3) == 0) {
        _ACTWait(1);
    }
    AddWayPointTop(3, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05c", func_0021C348);

void func_0021C3A0(int a0) {
    int buf[4];
    buf[0] = a0;
}
