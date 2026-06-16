#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aInit);

extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void func_00178E08(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt09aBrgSwitch(volatile int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aBrgDown);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aBrg);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aElvMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aElvSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", actSt09aElvUp);

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

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", func_002220A8);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", func_002221B0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", func_00222310);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st09a", func_00222470);

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
