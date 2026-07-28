#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;



extern int D_00633A00;
extern int func_0017B230(int a0);
extern int soundSeVolSet();
extern int actSt25aQueenDeadChk();
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void lt_fade_status(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05dDoor2(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepEnemyOne(a0, D_00631AE8, 200.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    func_0017B258(0xAA);
    _ACTWait(0xA);
    stage_KillPlayBgAnimation(0xCA, 1, 0);
    while (func_0012AA80(0xCA) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern int D_004D1BB0[];
extern int D_00631AE4;
extern void actSt04lRope2Chk(void);

INCLUDE_ASM("asm/nonmatchings/src/st05d", actSt05dDoor2UpChk);

void actSt05dDoor2DownChk(int x) {
    volatile int local = x;
}

void actSt05dEne(int x) {
    volatile int local = x;
}

void actSt05dEnemy1(int x) {
    volatile int local = x;
}

void actSt05dEnemy2(int x) {
    volatile int local = x;
}

void actSt05dDoor2Event(int x) {
    volatile int local = x;
}

void actSt05dDoor2UpEffect(int x) {
    volatile int local = x;
}

void actSt05dDoor2DownEffect(int x) {
    volatile int local = x;
}

void actSt05dEneChk(int x) {
    volatile int local = x;
}

void func_0021F578(int x) {
    volatile int local = x;
}

void func_0021F588(int x) {
    volatile int local = x;
    char *p = actSt25aQueenDeadChk(0x40A);
    *(int *)(p + 0x16C) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F5B0);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F5F8);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F640);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F688);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F6D0);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F718);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F760);

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F7A8);

void func_0021F7F0(void)
{
    if (D_00633A00 == 0) {
        return;
    }
    if (func_0017B230(0xD1) != 0) {
        return;
    }
    return soundSeVolSet(D_00633A00);
}

INCLUDE_ASM("asm/nonmatchings/src/st05d", func_0021F828);

