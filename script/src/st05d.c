#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", actSt05dDoor2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", actSt05dDoor2UpChk);

void actSt05dDoor2DownChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEne(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEnemy1(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEnemy2(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dDoor2Event(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dDoor2UpEffect(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dDoor2DownEffect(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt05dEneChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_0021C570(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void *actSt25aQueenDeadChk(int a0);

void func_0021C580(volatile int a0) {
    void *p = actSt25aQueenDeadChk(0x407);
    *(int *)((char *)p + 0x16C) = 0;
}

extern void _ACTWait(int a0);
extern int scpDoorTypeUpUp(int a0);
extern void func_00178DD8(int a0);

void func_0021C5A8(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x3FF) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xB8);
}

void func_0021C5F0(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x400) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xB9);
}

void func_0021C638(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    while (scpDoorTypeUpUp(0x451) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0xBA);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", func_0021C680);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", func_0021C6C8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", func_0021C710);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", func_0021C758);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", func_0021C7A0);

extern int D_0062BD08;
extern int func_00178DB0(int a0);
extern void soundSeVolSet(int a0);

void func_0021C7E8(void) {
    if (D_0062BD08 != 0) {
        if (func_00178DB0(0xD1) == 0) {
            soundSeVolSet(D_0062BD08);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st05d", func_0021C820);
