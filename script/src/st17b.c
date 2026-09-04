#include "common.h"

typedef struct ActB4Obj {
    char pad[0xB4];
    int *unkB4;
} ActB4Obj;
extern void BoxBarSoundOn(int a0, int a1);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void gflagLoad(int a0, float f);
extern float D_0062993C;
extern int D_004CDC10[];
extern void actSt17aDoorUpEffect(volatile int a0);

void actSt17bTest(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    gflagLoad(0x5EB, D_0062993C);
    if (func_00178DB0(0x112) == 0) {
        D_004CDC10[1] = (int)actSt17aDoorUpEffect;
        gobj->unkB4 = D_004CDC10;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int D_004CDC30[];
extern void actSt17aDoorDownEffect(volatile int a0);

void actSt17bCheck(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x113) == 0) {
        D_004CDC30[1] = (int)actSt17aDoorDownEffect;
        gobj->unkB4 = D_004CDC30;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int D_004CDC50[];
void func_0022B408(volatile int a0);

void actSt17bIntro(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004CDC50[1] = (int)func_0022B408;
    gobj->unkB4 = D_004CDC50;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", actSt17bCheckChk);


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_00629940;
extern float D_00629944;

void actSt17bIntroChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x115, 0x161, 0, 0x12, 0.0f, D_00629940, D_00629944, -75.0f, D_00629940, D_00629944);
}

extern int D_004CDCD0[];
void func_0022B578(volatile int a0);

void func_0022B150(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x116) == 0) {
        D_004CDCD0[1] = (int)func_0022B578;
        gobj->unkB4 = D_004CDCD0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void Generator_Call(int a0);
void func_0022B1C8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x117)==0){ _ACTWait(1); }
 _ACTWait(1); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); Generator_MaskOff(a0); }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void func_0022B270(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x117) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

extern void func_00178E08(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
void func_0022B2E0(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
if(func_00178DB0(0x121)){ *(int*)(actSt25aQueenDeadChk(0x5F1) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x5F2) + 0x16C) = 0; func_00178E08(0x121); } else { *(int*)(actSt25aQueenDeadChk(0x5EF) + 0x16C) = 0; *(int*)(actSt25aQueenDeadChk(0x5F0) + 0x16C) = 0; } }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);

void func_0022B360(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xDA) == 0) {
        *(int *)(actSt25aQueenDeadChk(0x5CF) + 0x16C) = 0;
    } else {
        *(int *)(actSt25aQueenDeadChk(0x5CE) + 0x16C) = 0;
    }
}

extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern void _ACTWait(int x);
extern int D_00629DE8;
extern long long D_00614BD0[];

void func_0022B3B0(volatile unsigned int a0)
{
    volatile int local;
    long long buf[2];
    buf[0] = D_00614BD0[0];
    buf[1] = D_00614BD0[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

extern int scpTriggerBall(int a0, int a1, float a2);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void OnGirlEscortFlag(void);
extern void RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern void func_00178DD8(int a0);
extern int D_00629DE4;

void func_0022B408(volatile int a0) {
    while (scpTriggerBall(a0, D_00629DE4, 400.0f) == 0 ||
           scpSleepSpiderGroupOne(D_00629DE4, 0x2000000) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x119);
    func_00178E08(0x121);
    if (D_00629DE8 != 0) {
        if (scpSleepSpiderGroupOne(D_00629DE8, 0x2000000) != 0) {
            OnGirlEscortFlag();
            RequestStageChange(1, D_00629DE4, D_00629DE8, 2.0f, 8.0f);
        }
    }
    RequestStageChange(1, D_00629DE4, 0, 2.0f, 8.0f);
}

extern int D_0062A894;
extern int D_004CDC70[];

void func_0022B4D8(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CDC70;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct { char pad[0xB0]; void *f_B0; void *unkB4; } BoxObj_st17b;
extern int *D_004CDCB0[];
extern void actSt17aIntroChk(volatile int a0);
void func_0022B510(volatile int a0) {
    BoxObj_st17b *obj = *(BoxObj_st17b **)(a0 + 0x164);
    D_0062A894 = 1;
    D_004CDCB0[1] = (int *)actSt17aIntroChk;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004CDCB0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

void func_0022B568(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
extern int D_00629DE4;
void func_0022B578(volatile int a0){
 if(D_00629DE8 == 0) _ACTWait(0);
 while(scpSleepSpiderGroupOne(D_00629DE8, 0x1000000)==0 || scpSleepSpiderGroupOne(D_00629DE4, 0x3000000)==0) _ACTWait(1);
 _ACTWait(1); func_00178DD8(0x116); func_00178DD8(0x117); }

extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int iosPadDevRead(int a0, int a1);
extern void iosPadActVolumeSet(int a0, int a1);
extern int func_0012AA28(int a0, int a1, int a2);
extern void Vibration_ShotDecode(int a0);
extern void func_00178DD8(int a0);
extern void RequestStageChange(int a0, int a1, int a2, float a3, float a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_0062BD90;
extern int D_0062BD9C;
extern unsigned char D_0062BDA0;
extern int D_00629DEC;
extern int D_00629DE4;

void func_0022B5F0(volatile int a0) {
    _ACTWait(0x3C);
    scpPlayStart(0x4B, &D_0062BD90, 0, 1, 1);
    while (D_0062BD90 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x97, 1, 0);
    stage_KillPlayBgAnimation(0x98, 1, 0);
    while (func_0012AA28(0x97, 0x56, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x97, 0x8C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    {
        int r = iosPadDevRead(D_00629DEC, 0x9);
        D_0062BDA0 = 0x80;
        D_0062BD9C = r;
        iosPadActVolumeSet(r, 0x80);
    }
    while (func_0012AA28(0x97, 0xC8, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0062BDA0 = 0x40;
    while (func_0012AA28(0x97, 0x17C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BD9C);
    func_00178DD8(0x127);
    RequestStageChange(0xF, D_00629DE4, 0, 16.0f, 16.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st17b", func_0022B790);


extern int scpTriggerBall(int a0, int a1, float a2);
extern int actItouQueenAttackChk(void);
extern int func_0017BE60(int a0);
extern void lt_fade_status(int a0);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void iosPadActVolumeSet(int a0, int a1);
extern void func_001790A8(int a0);
extern void scpPlayPosSet(void *a0, float f12, float f13, float f14);
extern void gflagOff(void *a0, int a1);
extern void *ContinueCorrectPosition(void *a0);
extern void sceVu0SubVector(void *a0, void *a1, void *a2);
extern void gflagChk(int a0, void *a1);
extern void func_00179F88(void);
extern void actSt25aQueenBefore(void *a0);
extern void func_001790E8(void *a0);
extern void func_00178DD8(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern void Vibration_ShotDecode(int a0);
extern int func_0012A958(int a0);
extern int D_0062A894;
extern int D_0062BD98;
extern int D_0062BDA4;
extern unsigned char D_0062BDA8;
extern int D_00629DEC;
extern int D_00629DE4;
extern float D_00629950, D_00629954, D_00629958;

void func_0022B8E8(volatile int a0) {
    float buf[4];
    void *r16;
    while (scpTriggerBall(a0, D_00629DE4, 200.0f) == 0 ||
           actItouQueenAttackChk() != 5 ||
           func_0017BE60(D_00629DE4) != 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpPlayStart(0x12, &D_0062BD98, 1, 1, 1);
    while (D_0062BD98 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x9A, 1, 0);
    {
        int r = iosPadDevRead(D_00629DEC, 0x9);
        D_0062BDA8 = 0x80;
        D_0062BDA4 = r;
        iosPadActVolumeSet(r, 0x80);
    }
    func_001790A8(D_00629DE4);
    {
        float t13 = *(volatile float *)&D_00629950;
        float t14 = *(volatile float *)&D_00629954;
        float t12 = *(volatile float *)&D_00629958;
        scpPlayPosSet((void *)D_00629DE4, t12, t13, t14);
    }
    gflagOff((void *)D_00629DE4, 0);
    _ACTWait(1);
    r16 = ContinueCorrectPosition((void *)a0);
    sceVu0SubVector(buf, r16, ContinueCorrectPosition((void *)D_00629DE4));
    gflagChk(D_00629DE4, buf);
    func_00179F88();
    gflagOff((void *)D_00629DE4, 0xF6);
    actSt25aQueenBefore((void *)D_00629DE4);
    gflagOff((void *)D_00629DE4, 0);
    func_001790E8((void *)D_00629DE4);
    func_00178DD8(0x128);
    while (func_0012AA28(0x9A, 0x97, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Vibration_ShotDecode(D_0062BDA4);
    while (func_0012A958(0x9A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}


extern void warpGirlInStage(float f0, float f1, float f2);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern float D_0062995C, D_00629960, D_00629964;
extern int D_004CDDD0[];
extern void actSt18aSwitchRChk(volatile int a0);

void func_0022BAE8(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    warpGirlInStage(*(volatile float *)&D_0062995C, *(volatile float *)&D_00629960, *(volatile float *)&D_00629964);
    if (func_00178DB0(0x127) == 0) {
        stage_KillPlayBgAnimation(0x97, 0, 0);
        D_004CDDD0[1] = (int)actSt18aSwitchRChk;
        gobj->unkB4 = D_004CDDD0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void scpFadeOut(int a0, int a1, int a2, float f0);
extern void lt_fade_status(int a0);
extern void func_001790A8(int a0);
extern int D_0062A894;
extern int D_00629DE4;
extern int D_004CDE10[];
void func_0022B790(volatile int a0);

void func_0022BB88(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0xF) != 0) {
        scpFadeOut(0, 0, 0, 255.0f);
        stage_KillPlayBgAnimation(0x97, 0, 0);
        lt_fade_status(0x33);
        D_0062A894 = 1;
        func_001790A8(D_00629DE4);
        _ACTWait(0xA);
        stage_KillPlayBgAnimation(0x97, 0, 0x1C3);
        D_004CDE10[1] = (int)func_0022B790;
        gobj->unkB4 = D_004CDE10;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CDE30[];
void func_0022B8E8(volatile int a0);

void func_0022BC58(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x128) == 0) {
        stage_KillPlayBgAnimation(0x9A, 0, 0);
        D_004CDE30[1] = (int)func_0022B8E8;
        gobj->unkB4 = D_004CDE30;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x9A, 0, -1);
    }
}

