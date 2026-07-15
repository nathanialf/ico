#include "common.h"

void LwsKyomiGeo(int a0) {
    int buf[4];
    buf[0] = a0;
}

void CreateKyomiGObj(volatile unsigned int x) {
    typedef struct { long long lo; long long hi; } V16k;
    extern V16k D_00614E60;
    extern int D_00629DE8;
    extern int D_0062A894;
    extern void actSt25aQueenTalkChk(int, int, V16k *, int, float);
    extern void func_00260568(void *, int, int);
    extern void actSwordEffXL(int, int, void *, int);
    extern void lt_fade_status(int);
    extern void saveEditedDataBinary(void);
    V16k buf;
    char buf2[16];
    buf = D_00614E60;
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf, 0, 100.0f);
    func_00260568(buf2, 0, 0x10);
    actSwordEffXL(D_00629DE8, 0xB, buf2, 0xB4);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    saveEditedDataBinary();
}

void SetParamKyomiGObj(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00236ED0(int a0) {
    int buf[4];
    buf[0] = a0;
}

typedef struct { long long lo; long long hi; } V16;

void func_00236EE0(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00236EF0);

typedef struct KSub {
    char pad[0xB0];
    int unkB0;
    int *unkB4;
} KSub;

extern void lt_fade_status(int);
extern void scpDispOnAllWithKind(void);
extern int func_00178DB0(int);
extern void BoxBarSoundOn(int, int);
extern int _ACTWait(int);
extern int D_0062A894;
extern int D_004CEA40[];
extern int D_004CEA60[];
extern void func_002361C0(int);
extern void func_00236FE0(int);

void func_00236F38(volatile int a0) {
    KSub *s = *(KSub **)(a0 + 0x164);
    s->unkB0 = 0;
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    if (func_00178DB0(0x2C) != 0) {
        D_004CEA40[1] = (int)func_002361C0;
        s->unkB4 = D_004CEA40;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
    D_004CEA60[1] = (int)func_00236FE0;
    s->unkB4 = D_004CEA60;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00236FE0);

extern V16 D_00614E70;
extern int D_00629DE8;
extern void actSt25aQueenTalkChk(int, int, V16 *, int, float);

void func_002370D8(volatile unsigned int x)
{
    volatile int local;
    V16 buf;
    buf = D_00614E70;
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf, 0, 100.0f);
}

extern V16 D_00614E80;

void func_00237128(volatile unsigned int x)
{
    volatile int local;
    V16 buf;
    buf = D_00614E80;
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf, 0, 100.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237178);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_002371C0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237268);

extern V16 D_00614E90;

void func_00237360(volatile unsigned int x)
{
    volatile int local;
    V16 buf;
    buf = D_00614E90;
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf, 0, 100.0f);
}

void func_002373B0(int a0) {
    int buf[4];
    buf[0] = a0;
}

extern int scpSubAdpcmPlay(int);
extern int scpSleepEnemyOne(int, int, float);
extern void lt_fade_status(int);
extern void scpDispOnAllWithKind(void);
extern void stage_KillPlayBgAnimation(int, int, int);
extern void func_00178DD8(int);
extern int func_0012A958(int);
extern void scpActivateAllWithKind(void);
extern int _ACTWait(int);
extern int D_0062A894;

void func_002373C0(int a0) {
    volatile int buf[4];
    int r;
    buf[0] = a0;
    for (;;) {
        r = scpSubAdpcmPlay(0x13);
        if (r != 0 && scpSleepEnemyOne(buf[0], r, 350.0f) != 0) {
            break;
        }
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    scpDispOnAllWithKind();
    stage_KillPlayBgAnimation(0x95, 1, 0);
    func_00178DD8(0x2F);
    while (func_0012A958(0x95) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}

extern int _ACTWait(int);
extern int func_00178DB0(int);
extern void func_00178DD8(int);

void func_00237480(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    *(int *)((char *)actSt25aQueenDeadChk(0x1B5) + 0x16C) = 0;
    while (func_00178DB0(0x9B) == 0 || func_00178DB0(0xD1) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x30);
    *(int *)((char *)actSt25aQueenDeadChk(0x1B4) + 0x16C) = 0;
    *(int *)((char *)actSt25aQueenDeadChk(0x1B5) + 0x16C) = 1;
}

extern void *actSt25aQueenDeadChk(int a0);

void func_002374F8(int a0) {
    volatile int home = a0;
    *(int *)((char *)actSt25aQueenDeadChk(0x1B4) + 0x16C) = 1;
    *(int *)((char *)actSt25aQueenDeadChk(0x1B5) + 0x16C) = 0;
}

extern int _ACTWait(int);
extern int scpSleepSpiderGroupOne(int, int);
extern void func_00178E08(int);
extern void func_00178DD8(int);

void func_00237530(int a0) {
    volatile int buf[4];
    buf[0] = a0;
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    func_00178E08(0x165);
    _ACTWait(1);
    func_00178DD8(0x31);
    func_00178DD8(0x32);
}

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern int actInitialize(int a0);
extern int _ACTWait(int);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004CEC20[];
extern void ObjAction_MailCenter(int a0);

void func_002375A0(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CEC20[1] = (int)ObjAction_MailCenter;
    gobj->unkB4 = D_004CEC20;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CEC40[];
extern void ObjAction_Init(int a0);

void func_00237608(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CEC40[1] = (int)ObjAction_Init;
    gobj->unkB4 = D_004CEC40;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

extern int D_004CEC60[];
extern void func_00237A20(int a0);

void func_00237670(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CEC60[1] = (int)func_00237A20;
    gobj->unkB4 = D_004CEC60;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

extern int D_004CEC80[];
extern void func_00237AD0(int a0);

void func_002376D8(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CEC80[1] = (int)func_00237AD0;
    gobj->unkB4 = D_004CEC80;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

extern void func_0012AAB8(int a0, int a1);
extern int D_004CECC0[];
extern void func_00237C30(int a0);

void func_00237740(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    func_0012AAB8(0x8A, 1);
    stage_KillPlayBgAnimation(0x8A, 1, 0);
    D_004CECC0[1] = (int)func_00237C30;
    gobj->unkB4 = D_004CECC0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

