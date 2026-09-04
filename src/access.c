#include "common.h"

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D3E50[];
extern int D_004D3F10[];
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);


extern int actSt25aQueenDeadChk();
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern int actInitialize(int a0);

void func_0023A978(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x32) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
}

void func_0023A9E0(int x) {
    volatile int local = x;
}

extern long long D_0061C350[];
extern int D_00631AE8;
extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern void memset(void *a0, int a1, int a2);
extern void RequestStageChangeDirect(int a0, int a1, int *a2, int a3);
extern void scpActivateAllWithKind(void);
extern void brainUnlockGirl(void);

void func_0023A9F0(volatile int a0)
{
    long long buf[2];
    int pos[4];
    buf[0] = D_0061C350[0];
    buf[1] = D_0061C350[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
    memset(pos, 0, 0x10);
    RequestStageChangeDirect(D_00631AE8, 0xB, pos, 0xB4);
    scpActivateAllWithKind();
    lt_fade_status(0x32);
    D_006325B4 = 0;
    brainUnlockGirl();
}

void func_0023AA88(int x) {
    volatile int local = x;
}

void func_0023AA98(int x) {
    volatile int local = x;
}

void func_0023AAA8(int x) {
    volatile int local = x;
}

typedef struct KSub_aab8 { char pad[0xC0]; int unkC0; } KSub_aab8;


void func_0023AAB8(volatile int a0) {
    KSub_aab8 *s = *(KSub_aab8 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3E50;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_aae8 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_aae8;

extern int D_004D3E90[];
extern int D_004D3EB0[];
extern void func_00239C58(volatile int a0);
extern void func_00239B50(volatile int a0);

void func_0023AAE8(volatile int a0) {
    KSub_aae8 *s = *(KSub_aae8 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x2C) != 0) {
        D_004D3E90[1] = (int)func_00239C58;
        s->unkC4 = D_004D3E90;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D3EB0[1] = (int)func_00239B50;
    s->unkC4 = D_004D3EB0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern long long D_0061C360[];

void func_0023AB90(volatile int a0)
{
    long long buf[2];
    buf[0] = D_0061C360[0];
    buf[1] = D_0061C360[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
}

extern long long D_0061C370[];

void func_0023ABE0(volatile int a0)
{
    long long buf[2];
    buf[0] = D_0061C370[0];
    buf[1] = D_0061C370[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
}

typedef struct KSub_ac30 { char pad[0xC0]; int unkC0; } KSub_ac30;


void func_0023AC30(volatile int a0) {
    KSub_ac30 *s = *(KSub_ac30 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3F10;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_ac60 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_ac60;

extern int D_004D3F50[];
extern int D_004D3F70[];
extern void func_00239EB0(volatile int a0);
extern void func_00239DA8(volatile int a0);

void func_0023AC60(volatile int a0) {
    KSub_ac60 *s = *(KSub_ac60 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x2D) != 0) {
        D_004D3F50[1] = (int)func_00239EB0;
        s->unkC4 = D_004D3F50;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D3F70[1] = (int)func_00239DA8;
    s->unkC4 = D_004D3F70;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern long long D_0061C380[];

void func_0023AD08(volatile int a0)
{
    long long buf[2];
    buf[0] = D_0061C380[0];
    buf[1] = D_0061C380[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
}

void func_0023AD58(int x) {
    volatile int local = x;
}

extern int scpIsBombExplode(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern void func_0017B258(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA80(int a0);

void func_0023AD68(volatile int a0)
{
    int v0;
    while ((v0 = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, v0, 350.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    stage_KillPlayBgAnimation(0x96, 1, 0);
    func_0017B258(0x2F);
    while (func_0012AA80(0x96) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_006325B4 = 0;
    lt_fade_status(0x32);
    scpActivateAllWithKind();
}


void func_0023AE28(int a0)
{
    volatile int local = a0;
    int v0;
    v0 = actSt25aQueenDeadChk(0x1B6);
    *(int *)(v0 + 0x16C) = 0;
    while (func_0017B230(0x9B) == 0 || func_0017B230(0xD1) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x30);
    v0 = actSt25aQueenDeadChk(0x1B5);
    *(int *)(v0 + 0x16C) = 0;
    v0 = actSt25aQueenDeadChk(0x1B6);
    *(int *)(v0 + 0x16C) = 1;
}

void func_0023AEA0(int a0)
{
    volatile int local = a0;
    int v0;
    v0 = actSt25aQueenDeadChk(0x1B5);
    *(int *)(v0 + 0x16C) = 1;
    v0 = actSt25aQueenDeadChk(0x1B6);
    *(int *)(v0 + 0x16C) = 0;
}

extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_0017B288(int a0);

void func_0023AED8(int a0)
{
    volatile int local = a0;
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) == 0) {
        _ACTWait(1);
    }
    func_0017B288(0x166);
    _ACTWait(1);
    func_0017B258(0x31);
    func_0017B258(0x32);
}


typedef struct KSub_af48 {
    char pad[0xC4];
    int *unkC4;
} KSub_af48;

extern int D_004D4070[];
extern void func_0023B2E0(volatile int a0);

void func_0023AF48(volatile int a0) {
    int x = a0;
    KSub_af48 *s = (KSub_af48 *)actInitialize(a0);
    _ACTWait(1);
    D_004D4070[1] = (int)func_0023B2E0;
    s->unkC4 = D_004D4070;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_afb0 {
    char pad[0xC4];
    int *unkC4;
} KSub_afb0;

extern int D_004D4090[];
extern void func_0023B390(volatile int a0);

void func_0023AFB0(volatile int a0) {
    int x = a0;
    KSub_afb0 *s = (KSub_afb0 *)actInitialize(a0);
    _ACTWait(1);
    D_004D4090[1] = (int)func_0023B390;
    s->unkC4 = D_004D4090;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_b018 {
    char pad[0xC4];
    int *unkC4;
} KSub_b018;

extern int D_004D40B0[];
extern void func_0023B440(volatile int a0);

void func_0023B018(volatile int a0) {
    int x = a0;
    KSub_b018 *s = (KSub_b018 *)actInitialize(a0);
    _ACTWait(1);
    D_004D40B0[1] = (int)func_0023B440;
    s->unkC4 = D_004D40B0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_b080 {
    char pad[0xC4];
    int *unkC4;
} KSub_b080;

extern int D_004D40D0[];
extern void func_0023B4F0(volatile int a0);

void func_0023B080(volatile int a0) {
    int x = a0;
    KSub_b080 *s = (KSub_b080 *)actInitialize(a0);
    _ACTWait(1);
    D_004D40D0[1] = (int)func_0023B4F0;
    s->unkC4 = D_004D40D0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_b0e8 {
    char pad[0xC4];
    int *unkC4;
} KSub_b0e8;

extern int D_004D4110[];
extern void func_0023B650(volatile int a0);
extern void func_0012ABE0(int a0, int a1);

void func_0023B0E8(volatile int a0) {
    int x = a0;
    KSub_b0e8 *s = (KSub_b0e8 *)actInitialize(a0);
    _ACTWait(1);
    func_0012ABE0(0x8B, 1);
    stage_KillPlayBgAnimation(0x8B, 1, 0);
    D_004D4110[1] = (int)func_0023B650;
    s->unkC4 = D_004D4110;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern void scpSetCageVelocityFriction(int a0, int a1, int a2, int a3);

void func_0023B170(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpSetCageVelocityFriction(0xCAA, 0, 0x1E3, 0);
}

void func_0023B1B8(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpSetCageVelocityFriction(0xCA9, 0, 0x1E4, 0);
}

typedef struct KSub_b200 {
    char pad[0xC4];
    int *unkC4;
} KSub_b200;

extern int D_004D4130[];
extern void func_0023B6B8(volatile int a0);

void func_0023B200(volatile int a0) {
    int x = a0;
    KSub_b200 *s = (KSub_b200 *)actInitialize(a0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x70, 0, 0);
    D_004D4130[1] = (int)func_0023B6B8;
    s->unkC4 = D_004D4130;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_b278 {
    char pad[0xC4];
    int *unkC4;
} KSub_b278;

extern int D_004D40F0[];
extern void func_0023B5A0(volatile int a0);

void func_0023B278(volatile int a0) {
    int x = a0;
    KSub_b278 *s = (KSub_b278 *)actInitialize(a0);
    _ACTWait(1);
    D_004D40F0[1] = (int)func_0023B5A0;
    s->unkC4 = D_004D40F0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern void scpGetWallCollision(float a0, float a1, float a2, float a3, float a4, float a5);
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);

void func_0023B2E0(volatile int a0)
{
    int v0;
    v0 = actSt25aQueenDeadChk(0xAE7);
    *(int *)(*(int *)(v0 + 0x15C) + 0x4E8) = 1;
    v0 = actSt25aQueenDeadChk(0xAE7);
    *(int *)(*(int *)(v0 + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x1B8, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xAE7, 0x1B8);
    while (func_0012AA80(0x1B8) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void func_0023B390(volatile int a0)
{
    int v0;
    v0 = actSt25aQueenDeadChk(0xAE8);
    *(int *)(*(int *)(v0 + 0x15C) + 0x4E8) = 1;
    v0 = actSt25aQueenDeadChk(0xAE8);
    *(int *)(*(int *)(v0 + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x1AC, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xAE8, 0x1AC);
    while (func_0012AA80(0x1AC) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

void func_0023B440(volatile int a0)
{
    int v0;
    v0 = actSt25aQueenDeadChk(0xAE9);
    *(int *)(*(int *)(v0 + 0x15C) + 0x4E8) = 1;
    v0 = actSt25aQueenDeadChk(0xAE9);
    *(int *)(*(int *)(v0 + 0x15C) + 0x4E8) = 0;
    scpGetWallCollision(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 100.0f);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x1AD, 1, 0);
    scpLinkBGAtoLayoutedTarget(0xAE9, 0x1AD);
    while (func_0012AA80(0x1AD) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
}

