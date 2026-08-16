#include "common.h"

struct Q { long long a, b; };

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;



extern void _ACTWait();
extern int actInitialize();
extern int actSt25aQueenDeadChk();
extern int func_0017B230(int a0);
extern void *D_00631AE8;
extern void func_0017B258(int bit_idx);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04dDoor1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x7C) == 0) {
        stage_KillPlayBgAnimation(0x10A, -1, -2);
    } else {
        stage_KillPlayBgAnimation(0x108, -1, -2);
    }
}

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04dDoor1UpChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x7C) == 0) {
        stage_KillPlayBgAnimation(0x10C, -1, -2);
        stage_KillPlayBgAnimation(0x110, -1, -2);
    }
}

void actSt04dDoor1DownChk(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor2);

void actSt04dDoor2UpChk(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x92) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

extern struct Q D_0061BD20;
extern int D_00631AE4;
extern void actCreateSubThread(void *fn, int a1);
extern int func_0012AA80(int a0);
extern void func_002194D8(void);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);

void actSt04dDoor2DownChk(volatile int a0) {
    struct Q buf;
    while (scpSleepEnemyOne(a0, D_00631AE4, 200.0f) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x1E);
    actCreateSubThread(func_002194D8, 0x15);
    stage_KillPlayBgAnimation(0xE1, 1, 0);
    buf = D_0061BD20;
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0xE1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0017B258(0x91);
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", actSt04dDoor1Event);

extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04dDoor1UpEffect(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x7C) == 0) {
        stage_KillPlayBgAnimation(0x10D, -1, -2);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D16D0[];
extern void actSt04dDoor1Event(volatile int a0);

void actSt04dDoor1DownEffect(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xB3) == 0) {
        stage_KillPlayBgAnimation(0xCB, 0, 0);
        D_004D16D0[1] = (int)actSt04dDoor1Event;
        gobj->unkB4 = D_004D16D0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xCB, 0, -1);
        ((int *)actSt25aQueenDeadChk(0x3F2))[0x16C / 4] = 0;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D16B0[];
extern void func_00219660(volatile int a0);

void actSt04dDoor2Event(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x90) == 0) {
        D_004D16B0[1] = (int)func_00219660;
        gobj->unkB4 = D_004D16B0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1670[];
extern void actSt04dDoor2DownChk(volatile int a0);

void actSt04dDoor2UpEffect(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    if (func_0017B230(0x91) == 0) {
        D_004D1670[1] = (int)actSt04dDoor2DownChk;
        gobj->unkB4 = D_004D1670;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1690[];
extern void func_002195F0(volatile int a0);

void actSt04dDoor2DownEffect(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x92) == 0) {
        D_004D1690[1] = (int)func_002195F0;
        gobj->unkB4 = D_004D1690;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_00219358);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_002193E8);

void func_00219478(volatile unsigned int a0)
{
  unsigned int self = a0;
  actInitialize(a0);
  _ACTWait(1);
  if (func_0017B230(0xCD) != 0)
  {
    *((int *) (((char *) actSt25aQueenDeadChk(0x3EE)) + 0x16C)) = 0;
  }
}

void func_002194C8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_002194D8);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_002195F0);

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_00219660);

void func_00219728(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st04d", func_00219738);

