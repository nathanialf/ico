#include "common.h"

typedef struct GObj { char pad[0xB4]; int *unkB4; } GObj;
extern int actInitialize(int a0);
extern void BoxBarSoundOn(int a0, int a1);

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void lt_fade_status(int a0);
extern void func_0017A040(int a0);
extern void func_00178E08(int a0);
extern void func_00178DD8(int a0);
extern void actConte11(int a0);
extern void func_0017A0D8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_0017A008(int a0);
extern int D_00629DE8;
extern int D_0062A894;
void actSt13b2Generator(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x5000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_0017A040(0xD57);
    func_00178E08(0x165);
    func_00178DD8(0x45);
    func_00178DD8(0x47);
    _ACTWait(0x3C);
    actConte11(0x12F);
    actConte11(0x130);
    actConte11(0x131);
    func_0017A0D8(0x132);
    stage_KillPlayBgAnimation(0x59, 1, 0);
    while (func_0012A958(0x59) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    func_0017A008(0xD57);
}

#include "common.h"
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpDispOnAllWithKind(void);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);
extern int func_0012A958(int a0);
extern void AddWayPointTop(int a0, int a1);
extern void scpActivateAllWithKind(void);
extern int D_004CD6E0[];
extern int D_0062A894;
void func_00226C80(volatile int a0) {
    lt_fade_status(0x33);
    func_00178DD8(0x43);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x5A, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004CD6E0, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004CD6E0, 1);
    while (func_0012A958(0x5A) == 0) { _ACTWait(1); }
    _ACTWait(1);
    AddWayPointTop(0xB, 1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
extern int D_004CD6A0[];
extern void func_00227268(volatile int a0);
void func_00226D50(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x43) == 0) {
        stage_KillPlayBgAnimation(0x5A, 0, 0);
        D_004CD6A0[1] = (int)func_00227268;
        gobj->unkB4 = D_004CD6A0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        AddWayPointTop(0xB, 1);
        stage_KillPlayBgAnimation(0x5A, 0, -1);
    }
}


extern int func_00178DB0(int a0);
extern int D_004CD640[];
extern void actSt13bMeetAgainChk(void);
void func_00226DF8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x44) == 0) {
        D_004CD640[1] = (int)actSt13bMeetAgainChk;
        gobj->unkB4 = D_004CD640;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int func_00178DB0(int a0);
extern int D_004CD660[];
void func_00226E70(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x45) == 0) {
        D_004CD660[1] = (int)actSt13b2Generator;
        gobj->unkB4 = D_004CD660;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


void func_00226EE8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x46)==0){ _ACTWait(1); }
 _ACTWait(0x74); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void func_00226F90(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x46)==0){ _ACTWait(1); }
 _ACTWait(0x64); Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void func_00227038(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x47)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

void func_002270D8(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_00178DB0(0x47)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0); }

extern int func_00178DB0(int a0);
extern int D_004CD6F0[];
extern void func_002272F8(volatile int a0);
void func_00227178(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x48) == 0) {
        D_004CD6F0[1] = (int)func_002272F8;
        gobj->unkB4 = D_004CD6F0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern void gflagLoad(int a0, float a1);
extern float D_00629914;
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
void func_002271F0(void) {
    float f = D_00629914;
    gflagLoad(0x14F, f);
    gflagLoad(0x14E, f);
    if (func_00178DB0(0x49) != 0) {
        stage_KillPlayBgAnimation(0x14E, 0, 0x1FE);
        *(int *)(actSt25aQueenDeadChk(0x14F) + 0x16C) = 0;
    } else {
        stage_KillPlayBgAnimation(0x14E, 0, 0);
        *(int *)(actSt25aQueenDeadChk(0x14E) + 0x16C) = 0;
    }
}


extern int D_004CD680[];

void func_00227268(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    D_0062A894 = 0;
    *(int *)(gobj + 0xB0) = (int)D_004CD680;
    for (;;) {
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002272A0);

extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern int D_00629DE4;

void func_002272F8(volatile int a0) {
    while (scpSleepEnemyOne(a0, D_00629DE4, 100.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x48);
    stage_KillPlayBgAnimation(0x72, 1, 0);
    while (func_0012A958(0x72) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_002273A0);

extern void func_001D1508(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int D_00629DEC;
extern int D_0062C2B0;
void func_00227748(volatile int a0) {
    func_001D1508(0x12C);
    stage_KillPlayBgAnimation(0x14E, 1, 0);
    *(int *)(actSt25aQueenDeadChk(0x14F) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x14E) + 0x16C) = 1;
    while (func_0012AA28(0x14E, 0x5, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012AA28(0x14E, 0xD7, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x14E, 0x1D1, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    D_0062C2B0 = 1;
    _ACTWait(0);
}


extern void func_001D1508(int a0);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern int D_00629DEC;
extern int D_0062C2B0;
void func_00227860(volatile int a0) {
    func_001D1508(0x12C);
    stage_KillPlayBgAnimation(0x14E, 1, 0x1FF);
    while (func_0012AA28(0x14E, 0x2DC, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x14E, 0x336, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x14E, 0x3E3, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    D_0062C2B0 = 1;
    _ACTWait(0);
}


extern int scpSleepEnemyOne(int a0, int a1, float a2);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_004CD770[];
extern int D_004CD790[];
extern void func_00227BE0(volatile int a0);
extern void func_00227A68(volatile int a0);
void func_00227960(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00629DE4, 200.0f) != 0 ||
        (D_00629DE8 != 0 && scpSleepEnemyOne(a0, D_00629DE8, 400.0f) != 0)) {
        stage_KillPlayBgAnimation(0x150, 0, 0);
        _ACTWait(0x3C);
        D_004CD770[1] = (int)func_00227BE0;
        gobj->unkB4 = D_004CD770;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x14F, 0, 0);
        D_004CD790[1] = (int)func_00227A68;
        gobj->unkB4 = D_004CD790;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227A68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13b2", func_00227BE0);

extern int D_004CD730[];
extern void actSt13cBmg1(void);
void func_00227D58(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CD730[1] = (int)actSt13cBmg1;
    gobj->unkB4 = D_004CD730;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int func_00178DB0(int a0);
extern int D_004CD7F0[];
extern void actSt13cCage1stDownDemoCancel(void);
void func_00227DC0(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x4A) == 0) {
        D_004CD7F0[1] = (int)actSt13cCage1stDownDemoCancel;
        gobj->unkB4 = D_004CD7F0;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}

