#include "common.h"

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0012AAB8(int a0, int a1);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern int func_0012A958(int a0);
extern int D_0062A894;
extern int D_0062BE00;
struct Q { long long a, b; };
extern struct Q D_00614E30;

void actExplode(volatile int a0) {
    struct Q buf;
    while (scpSleepEnemyOne(a0, actSt25aQueenDeadChk(0x6F2), 220.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x11B);
    scpPlayStart(0x4A, &D_0062BE00, 1, 1, 1);
    while (D_0062BE00 == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x78, 1, 0);
    _ACTWait(0x5A);
    stage_KillPlayBgAnimation(0x76, 1, 0);
    stage_KillPlayBgAnimation(0x77, 1, 0);
    *(int *)(actSt25aQueenDeadChk(0x6F2) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x6F1) + 0x16C) = 1;
    func_0012AAB8(0x76, 1);
    func_0012AAB8(0x77, 1);
    buf = D_00614E30;
    soundSeDefPlayWithVolumeRate(0x52B, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x52C, 0, &buf, 1);
    soundSeDefPlayWithVolumeRate(0x52D, 0, &buf, 1);
    while (func_0012A958(0x78) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWave);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSpider);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
typedef struct { long a, b; } S16;
extern S16 D_00614E20;
void actDevilLightning(volatile int a0) {
    S16 buf;
    int x = a0;
    actInitialize(a0); _ACTWait(1);
    buf = D_00614E20;
    soundSeDefPlayWithVolumeRate(0x52A, 0, &buf, 1);
    stage_KillPlayBgAnimation(0x79, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actQueenLightning);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt27aWave(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x11C) == 0) {
        stage_KillPlayBgAnimation(0x7A, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x7A, 0, -1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actExplodeChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSplash2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWaveChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actWave1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", actSt27aWaveChk);

extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void AddWayPointTop(int a0, int a1);

void actSt27aWave1(void) {
    if (func_00178DB0(0x11F) == 0) {
        stage_KillPlayBgAnimation(0x7F, 0, 0);
        AddWayPointTop(4, 0);
    } else {
        stage_KillPlayBgAnimation(0x7F, 0, -1);
        AddWayPointTop(4, 1);
    }
}

extern int D_00629DE8;
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);

void actSpiderChk(void) {
    if (D_00629DE8) {
        if (func_00178DB0(0x11F)) {
            if (!func_00178DB0(0x122)) {
                func_00178DD8(0x165);
            }
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002343C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002344C0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_00234640);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002347A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st99a", func_002348D8);
