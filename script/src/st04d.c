#include "common.h"

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04dDoor1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7C) == 0) {
        stage_KillPlayBgAnimation(0x109, -1, -2);
    } else {
        stage_KillPlayBgAnimation(0x107, -1, -2);
    }
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04dDoor1UpChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7C) == 0) {
        stage_KillPlayBgAnimation(0x10B, -1, -2);
        stage_KillPlayBgAnimation(0x10F, -1, -2);
    }
}

void actSt04dDoor1DownChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor2);

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSt04dDoor2UpChk(void) {
    if (D_00629DE8 == 0) return;
    if (func_00178DB0(0x92) != 0) return;
    func_00178DD8(0x165);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor2DownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor1Event);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void *actSt25aQueenDeadChk(int a0);

void actSt04dDoor1UpEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7C) == 0) {
        stage_KillPlayBgAnimation(0x10C, -1, -2);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor1DownEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor2Event);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor2UpEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", actSt04dDoor2DownEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", func_00216648);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", func_002166D8);

void func_00216768(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xCD) != 0) {
        ((int *)actSt25aQueenDeadChk(0x3EB))[0x16C / 4] = 0;
    }
}

void func_002167B8(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", func_002167C8);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
void func_002168E0(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0xB000000) == 0) { _ACTWait(1); }
    func_00178E08(0x165);
    _ACTWait(1);
    func_00178DD8(0x92);
    func_00178DD8(0x93);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", func_00216950);

void func_00216A18(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04d", func_00216A28);
