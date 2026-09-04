#include "common.h"

struct Q { long long a, b; };

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkC4;
} GObj__p4;

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aInit);

extern struct Q D_0061BE00;
extern int D_00631AE4;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt09aBrgSwitch(volatile int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void func_0017B288(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt09aElvDown(volatile int a0) {
    struct Q buf;
    while (scpTriggerBall(a0, D_00631AE4, 200.0f) == 0) {
        _ACTWait(1);
    }
    D_006325B4 = 1;
    _ACTWait(0x1E);
    func_0017B288(0x165);
    actCreateSubThread(actSt09aBrgSwitch, 0x15);
    stage_KillPlayBgAnimation(0x13A, 1, 0);
    buf = D_0061BE00;
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0x13A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0017B258(0x94);
    D_006325B4 = 0;
}

extern int actInitialize(int a0);
extern void *actSt25aQueenDeadChk(int a0);
extern int func_0017B230(int a0);
extern int func_001BC088(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern void scpDispOnAllWithKind(void);
extern void soundSeDefPitchSet(int a0);

void actSt09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_0017B230(0xE6) == 0) {
        int r = func_001BC088((int)actSt25aQueenDeadChk(0x500));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x12D, 1, 0);
            while (func_0012AA80(0x12D) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            ((int *)actSt25aQueenDeadChk(0x500))[0x16C / 4] = 0;
            lt_fade_status(0x33);
            D_006325B4 = 1;
            scpDispOnAllWithKind();
            func_0017B258(0xE6);
            stage_KillPlayBgAnimation(0x12B, 1, 0);
            {
                int snd = soundSeDefPlayWithVolumeRate(0x51A, 0, 0, 1);
                _ACTWait(0x5A);
                soundSeDefPitchSet(snd);
            }
            soundSeDefPlayWithVolumeRate(0x51B, 0, 0, 1);
            scpActivateAllWithKind();
            D_006325B4 = 0;
            lt_fade_status(0x32);
            break;
        }
    }
}

void actSt09aBrgDown(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    while (func_0017B230(0xE7) == 0) {
        int r = func_001BC088((int)actSt25aQueenDeadChk(0x501));
        switch (r) {
        case 0:
            _ACTWait(1);
            break;
        case 1:
            stage_KillPlayBgAnimation(0x12E, 1, 0);
            while (func_0012AA80(0x12E) == 0) {
                _ACTWait(1);
            }
            _ACTWait(1);
            break;
        case 2:
            ((int *)actSt25aQueenDeadChk(0x501))[0x16C / 4] = 0;
            lt_fade_status(0x33);
            D_006325B4 = 1;
            scpDispOnAllWithKind();
            func_0017B258(0xE7);
            stage_KillPlayBgAnimation(0x12C, 1, 0);
            {
                int snd = soundSeDefPlayWithVolumeRate(0x51A, 0, 0, 1);
                _ACTWait(0x5A);
                soundSeDefPitchSet(snd);
            }
            soundSeDefPlayWithVolumeRate(0x51B, 0, 0, 1);
            scpActivateAllWithKind();
            D_006325B4 = 0;
            lt_fade_status(0x32);
            break;
        }
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt09aElv(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x7D) == 0) {
        stage_KillPlayBgAnimation(0x10F, -1, -2);
    }
}

extern void *actSt25aQueenDeadChk(int a0);

void actSt09aIntro(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xCE) != 0) {
        ((int *)actSt25aQueenDeadChk(0x4FC))[0x16C / 4] = 0;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2430[];
extern void actSt09aSekizo(volatile int a0);

void actSt09aBrg(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE6) == 0) {
        stage_KillPlayBgAnimation(0x12B, 0, 0);
        D_004D2430[1] = (int)actSt09aSekizo;
        gobj->unkC4 = D_004D2430;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x12B, 0, -1);
        ((int *)actSt25aQueenDeadChk(0x500))[0x16C / 4] = 0;
    }
}

extern int D_004D2450[];
extern void actSt09aBrgDown(volatile int a0);

void actSt09aElvMain(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE7) == 0) {
        stage_KillPlayBgAnimation(0x12C, 0, 0);
        D_004D2450[1] = (int)actSt09aBrgDown;
        gobj->unkC4 = D_004D2450;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x12C, 0, -1);
        ((int *)actSt25aQueenDeadChk(0x501))[0x16C / 4] = 0;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D23F0[];
extern void actSt09aElvDown();

void actSt09aElvSwitch(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    if (func_0017B230(0x94) == 0) {
        D_004D23F0[1] = (int)actSt09aElvDown;
        gobj->unkC4 = D_004D23F0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2410[];
extern void func_00225308(volatile int a0);

void actSt09aElvUp(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x96) == 0) {
        D_004D2410[1] = (int)func_00225308;
        gobj->unkC4 = D_004D2410;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt09aSekizoEvent(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0x97)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_MaskOff(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void actSt09aIntroChk(volatile int a0){
 int x=a0;
 actInitialize(a0);
 _ACTWait(1);
 Generator_Mask(a0);
 while(func_0017B230(0x97)==0){ _ACTWait(1); }
 _ACTWait(1);
 Generator_MaskOff(a0);
 Generator_Call(a0);
 _ACTWait(0x3C);
 Generator_Call(a0);
}

void actSt09aBrgMain(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st09a", actSt09aBrgSwitch);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225308);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225378);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225480);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_002255E0);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225740);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_002257B8);

INCLUDE_ASM("asm/nonmatchings/src/st09a", func_00225850);

void func_002258E0(int x) {
    volatile int local = x;
}

