#include "common.h"
extern int D_004D1450[];

typedef struct ActB4Obj { char pad[0xC4]; int *unkC4; } ActB4Obj;
struct SndBuf { long long a, b; };

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1730[];
extern struct SndBuf D_0061BD60;
extern void _ACTWait(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt04eWaterMain(int a0);
extern int func_0012AA80(int a0);
extern void func_00219EB8(int a0);
extern int scpKillSpiderGroup(int a0, int a1);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04eWater(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    struct SndBuf buf;
    while (scpKillSpiderGroup(a0, 0x1000000) == 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread(func_00219EB8, 0x15);
    stage_KillPlayBgAnimation(0xE2, 1, 0);
    buf = D_0061BD60;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0xE2) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_004D1730[1] = (int)actSt04eWaterMain;
    obj->unkC4 = D_004D1730;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04e", actSt04eWaterMain);

extern int D_004D1770[];
extern int D_004D1790[];
extern int D_00631AE4;
extern int D_00631AE8;
extern int actInitialize(int a0);
extern void actSt04eWaterFlagOn(int a0);
extern void actSt04eWaterStop(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);

void actSt04eWaterSwitch(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00631AE4, 400.0f) != 0) goto flagon;
    if (D_00631AE8 == 0) goto stop;
    if (scpSleepEnemyOne(a0, D_00631AE8, 400.0f) == 0) goto stop;
flagon:
    stage_KillPlayBgAnimation(0xE5, 0, 0);
    _ACTWait(0x3C);
    D_004D1770[1] = (int)actSt04eWaterFlagOn;
    gobj->unkC4 = D_004D1770;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
    return;
stop:
    stage_KillPlayBgAnimation(0xE4, 0, 0);
    D_004D1790[1] = (int)actSt04eWaterStop;
    gobj->unkC4 = D_004D1790;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st04e", actSt04eWaterStop);

extern int D_004D17D0[];
extern struct SndBuf D_0061BD90;
extern void actSt04eWaterStop(int a0);
extern void func_0021A168(int a0);

void actSt04eWaterFlagOn(volatile int a0) {
    ActB4Obj *obj = *(ActB4Obj **)(a0 + 0x164);
    struct SndBuf buf;
    while (scpKillSpiderGroup(a0, 0x2000000) != 0) { _ACTWait(1); }
    _ACTWait(0xF);
    actCreateSubThread(func_0021A168, 0x15);
    stage_KillPlayBgAnimation(0xE5, 1, 0);
    buf = D_0061BD90;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0xE5) == 0) { _ACTWait(1); }
    _ACTWait(1);
    {
        int *p = D_004D1450 + 224;
        p[1] = (int)actSt04eWaterStop;
        obj->unkC4 = p;
    }
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

void func_00219EA8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_00219EB8);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_00219F98);

void func_0021A078(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A088);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A168);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A248);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A308);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A390);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A458);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A4D0);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A6B8);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021A980);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021AA18);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021AB40);

INCLUDE_ASM("asm/nonmatchings/src/st04e", func_0021AC68);

