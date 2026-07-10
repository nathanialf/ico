#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aInit);


extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void func_00178E08(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt09aBrgSwitch(volatile int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern int func_0012A958(int a0);
extern void func_00178DD8(int a0);
extern int D_00629DE4;
extern int D_0062A894;
struct Q { long long a, b; };
extern struct Q D_00614930;

void actSt09aElvDown(volatile int a0) {
    struct Q buf;
    while (scpSleepEnemyOne(a0, D_00629DE4, 200.0f) == 0) {
        _ACTWait(1);
    }
    D_0062A894 = 1;
    _ACTWait(0x1E);
    func_00178E08(0x164);
    actCreateSubThread(actSt09aBrgSwitch, 0x15);
    stage_KillPlayBgAnimation(0x139, 1, 0);
    buf = D_00614930;
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012A958(0x139) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_00178DD8(0x94);
    D_0062A894 = 0;
}

extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void *actSt25aQueenDeadChk(int a0);
extern int fallDownStartSE(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void soundSeDefPitchSet(int a0);
extern void scpActivateAllWithKind(void);

void actSt09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xE6) == 0) {
        int r = fallDownStartSE((int)actSt25aQueenDeadChk(0x4FC));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x12C, 1, 0);
            while (func_0012A958(0x12C) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            ((int *)actSt25aQueenDeadChk(0x4FC))[0x16C / 4] = 0;
            lt_fade_status(0x33);
            D_0062A894 = 1;
            scpDispOnAllWithKind();
            func_00178DD8(0xE6);
            stage_KillPlayBgAnimation(0x12A, 1, 0);
            {
                int snd = soundSeDefPlayWithVolumeRate(0x51A, 0, 0, 1);
                _ACTWait(0x5A);
                soundSeDefPitchSet(snd);
            }
            soundSeDefPlayWithVolumeRate(0x51B, 0, 0, 1);
            scpActivateAllWithKind();
            D_0062A894 = 0;
            lt_fade_status(0x32);
            break;
        }
    }
}


void actSt09aBrgDown(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_00178DB0(0xE7) == 0) {
        int r = fallDownStartSE((int)actSt25aQueenDeadChk(0x4FD));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x12D, 1, 0);
            while (func_0012A958(0x12D) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            ((int *)actSt25aQueenDeadChk(0x4FD))[0x16C / 4] = 0;
            lt_fade_status(0x33);
            D_0062A894 = 1;
            scpDispOnAllWithKind();
            func_00178DD8(0xE7);
            stage_KillPlayBgAnimation(0x12B, 1, 0);
            {
                int snd = soundSeDefPlayWithVolumeRate(0x51A, 0, 0, 1);
                _ACTWait(0x5A);
                soundSeDefPitchSet(snd);
            }
            soundSeDefPlayWithVolumeRate(0x51B, 0, 0, 1);
            scpActivateAllWithKind();
            D_0062A894 = 0;
            lt_fade_status(0x32);
            break;
        }
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void *actSt25aQueenDeadChk(int a0);

void actSt09aElv(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x7D) == 0) {
        stage_KillPlayBgAnimation(0x10E, -1, -2);
    }
}

void actSt09aIntro(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xCE) != 0) {
        ((int *)actSt25aQueenDeadChk(0x4F8))[0x16C / 4] = 0;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CD040[];
extern void actSt09aSekizo(volatile int a0);

void actSt09aBrg(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE6) == 0) {
        stage_KillPlayBgAnimation(0x12A, 0, 0);
        D_004CD040[1] = (int)actSt09aSekizo;
        gobj->unkB4 = D_004CD040;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x12A, 0, -1);
        ((int *)actSt25aQueenDeadChk(0x4FC))[0x16C / 4] = 0;
    }
}


extern int D_004CD060[];
extern void actSt09aBrgDown(volatile int a0);

void actSt09aElvMain(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xE7) == 0) {
        stage_KillPlayBgAnimation(0x12B, 0, 0);
        D_004CD060[1] = (int)actSt09aBrgDown;
        gobj->unkB4 = D_004CD060;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x12B, 0, -1);
        ((int *)actSt25aQueenDeadChk(0x4FD))[0x16C / 4] = 0;
    }
}


extern int D_004CD000[];

void actSt09aElvSwitch(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    if (func_00178DB0(0x94) == 0) {
        D_004CD000[1] = (int)actSt09aElvDown;
        gobj->unkB4 = D_004CD000;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CD020[];
extern void func_00222038(volatile int a0);

void actSt09aElvUp(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x96) == 0) {
        D_004CD020[1] = (int)func_00222038;
        gobj->unkB4 = D_004CD020;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


void actSt09aSekizoEvent(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x97)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt09aIntroChk(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x97)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void actSt09aBrgMain(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aBrgSwitch);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
void func_00222038(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (D_00629DE8 == 0 || func_00178DB0(0xE6) == 0) { _ACTWait(1); }
    _ACTWait(0x258);
    func_00178DD8(0x96);
    func_00178DD8(0x97);
}

extern int D_004CD080[];
extern int D_004CD0A0[];
extern void func_00222310(volatile int a0);
extern void func_002221B0(volatile int a0);

void func_002220A8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00629DE4, 400.0f) != 0 ||
        (D_00629DE8 != 0 && scpSleepEnemyOne(a0, D_00629DE8, 400.0f) != 0)) {
        stage_KillPlayBgAnimation(0x13B, 0, 0);
        _ACTWait(0x3C);
        D_004CD080[1] = (int)func_00222310;
        gobj->unkB4 = D_004CD080;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x13A, 0, 0);
        D_004CD0A0[1] = (int)func_002221B0;
        gobj->unkB4 = D_004CD0A0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", func_002221B0);


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", func_00222310);


extern int D_004CD100[];
extern void actSt10lFloorRight(volatile int a0);

void func_00222470(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x99) == 0) {
        D_004CD100[1] = (int)actSt10lFloorRight;
        gobj->unkB4 = D_004CD100;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


void func_002224E8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x9A)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void func_00222580(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_00178DB0(0x9A)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void func_00222610(int a0) {
    int buf[4];
    buf[0] = a0;
}
