#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CE2A0[];
extern void func_00230F80(volatile int a0);

void actSt22aLightningVolime(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CE2A0[1] = (int)func_00230F80;
    gobj->unkB4 = D_004CE2A0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


void actSt22aIntro(int a0) {
    int buf[4];
    buf[0] = a0;
}

void actSt22aIntroChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void *D_00629DE8;
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void func_001790A8(void *a0);
extern void *ContinueCorrectPosition(int a0);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void gflagChk(int a0, void *a1);
extern void BoySekikaTexScroll(int a0, int a1);
typedef struct { long long _0; long long _8; } WpData16;
extern WpData16 D_00614C10;

void actSt22aIntroSub(volatile int a0) {
    WpData16 local10, local20;
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepEnemyOne(a0, (int)D_00629DE8, 200.0f) == 0) {
        _ACTWait(1);
    }
    func_001790A8(D_00629DE8);
    _ACTWait(1);
    local10 = D_00614C10;
    func_00240008(&local20, &local10, ContinueCorrectPosition((int)D_00629DE8));
    gflagChk((int)D_00629DE8, &local20);
    BoySekikaTexScroll((int)D_00629DE8, 0xFB);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230A78);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230AB0);

extern void *D_00629DE4;
extern int D_0062C2C4;
extern void func_001790A8(void *a0);
extern void gflagOff(void *a0, int a1);
extern void actSt25aQueenBefore(void *a0);
extern void _ACTWait(int a0);

void func_00230B20(int a0) {
    int buf[4];
    buf[0] = a0;
    func_001790A8(D_00629DE4);
    gflagOff(D_00629DE4, 0x133);
    actSt25aQueenBefore(D_00629DE4);
    _ACTWait(0xF0);
    D_0062C2C4 = 1;
    _ACTWait(0);
}

#include "common.h"
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepSpiderGroupOne(void *a0, int a1);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void *D_00629DE4;
extern int D_0062BDE8;
void func_00230B70(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0 || func_00178DB0(0x13) == 0) {
        _ACTWait(1);
    }
    scpPlayStart(0xF, (int)&D_0062BDE8, 1, 1, 0);
}

void func_00230BF0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00230C00(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void func_00230C70(int a0);

void func_00230C10(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0x1D) == 0) {
        _ACTWait(1);
    }
    actCreateSubThread(func_00230C70, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230C70);

extern int D_004CE240[];
extern void actSt20aFenceUpChk2(int a0);
extern void func_00178E08(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void *D_00629DE8;

void func_00230E00(volatile int a0) {
    GObj *obj = *(GObj **)(a0 + 0x164);
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (*(int *)((char *)*(void **)((char *)D_00629DE8 + 0x164) + 0x30) != 0x6B) {
        _ACTWait(1);
    }
    func_00178E08(0x19);
    D_004CE240[1] = (int)actSt20aFenceUpChk2;
    obj->unkB4 = D_004CE240;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
    _ACTWait(1);
}


extern void *D_00629DE8;
extern int D_0062A894;
extern void func_00178DD8(int a0);

void func_00230EC8(int a0) {
    volatile int x;
    x = a0;
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (*(int *)((char *)*(void **)((char *)D_00629DE8 + 0x164) + 0x30) != 0x6A) {
        _ACTWait(1);
    }
    func_00178DD8(0x1B);
    D_0062A894 = 1;
    _ACTWait(0xC8);
    func_001790A8(D_00629DE8);
    gflagOff(D_00629DE8, 0x229);
    _ACTWait(0x78);
    func_00178DD8(0x1C);
}

void func_00230F70(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern void *D_00629DE4;
extern int GetSkeltonFocusNode(void *a0);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void func_00230F80(int a0) {
    volatile int x;
    x = a0;
    while (GetSkeltonFocusNode(D_00629DE4) != 0xE3) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x3F, -1, -2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00230FD8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_002310B8);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00231188);

void func_00231258(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st22a", func_00231260);


extern int scpKillSpiderGroup(int a0, int a1);
extern void func_0017BF50(float a0, float a1, float a2, float a3);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern void soundSeDefPitchSet(int a0);
extern int func_0012A958(int a0);
extern void func_0012AAB8(int a0, int a1);
extern void func_00231EE0(volatile int a0);
extern void actSt24aSwordChk(int a0);
extern int D_004CE340[];
extern WpData16 D_00614D30;
extern volatile float D_00629994, D_00629998, D_0062999C;

void func_002313B0(volatile int a0) {
    WpData16 buf;
    int sndid;
    GObj *obj = *(GObj **)(a0 + 0x164);
    while (scpKillSpiderGroup(a0, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    actCreateSubThread(func_00231EE0, 0x15);
    func_0017BF50(D_00629994, D_00629998, D_0062999C, 100.0f);
    stage_KillPlayBgAnimation(0x6C, 1, 0);
    buf = D_00614D30;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, (int)&buf, 1);
    _ACTWait(0x1E);
    sndid = soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)&buf, 1);
    _ACTWait(0x3C);
    soundSeDefPitchSet(sndid);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)&buf, 1);
    while (func_0012A958(0x6C) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0012AAB8(0x6E, 1);
    stage_KillPlayBgAnimation(0x6E, 1, 0);
    D_004CE340[1] = (int)actSt24aSwordChk;
    obj->unkB4 = D_004CE340;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

