#include "common.h"

extern int D_004D3000[];

typedef struct { char pad[0xC0]; void *f_B0; void *unkB4; } BoxObj_st17a;

extern int D_00631AE4;
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void func_0017B258(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void *actSt25aQueenDeadChk(int a0);
extern int actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0017B288(int a0);
extern int *D_00633A80;
extern int D_00633FB4;
extern void func_0022E398(volatile int a0);
extern void func_0022E508(volatile int a0);
extern void func_0022E680(volatile int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void scpActivateAllWithKind(void);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern void soundSeDefPitchSet(int a0);
extern int iosPadDevRead(int a0, int a1);
extern int D_00633A84;
extern int D_00631AEC;
extern int func_0012AA80(int a0);

void actSt17aHasiChk(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (1) {
        if (scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) != 0 && func_0017B230(0x10A) != 0) {
            break;
        }
        if (scpSleepSpiderGroupOne(D_00631AE4, 0x2000000) != 0 && scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) != 0) {
            break;
        }
        _ACTWait(1);
    }
    func_0017B258(0x10B);
}

void func_0022D650(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne((int)actSt25aQueenDeadChk(0x386), 0x1000000) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x10A);
}

void actSt17aSekizo(int x) {
    volatile int local = x;
}

extern int scpTriggerBall(int a0, int a1, float f);
extern int soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void func_0022D6C0(volatile int a0) {
    while (scpTriggerBall(a0, (int)actSt25aQueenDeadChk(0x37B), 100.0f) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x110);
    ((int *)actSt25aQueenDeadChk(0x37B))[0x16C / 4] = 0;
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4DE, 0, 0, 1);
}

void func_0022D740(volatile int a0) {
    while (scpTriggerBall(a0, (int)actSt25aQueenDeadChk(0x37C), 100.0f) == 0) {
        _ACTWait(1);
    }
    func_0017B258(0x111);
    ((int *)actSt25aQueenDeadChk(0x37C))[0x16C / 4] = 0;
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4DF, 0, 0, 1);
}

typedef struct KSub_d7c0 { char pad[0xC0]; int unkC0; } KSub_d7c0;


void func_0022D7C0(volatile int a0) {
    KSub_d7c0 *s = *(KSub_d7c0 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3000;
    for (;;) {
        _ACTWait(1);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int *D_004D3040[];
extern int D_006325B4;
extern void func_0022C9F0(volatile int a0);

void func_0022D7F0(volatile int a0) {
    BoxObj_st17a *obj = *(BoxObj_st17a **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D3040[1] = (int *)func_0022C9F0;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D3040;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_00632110;
extern int D_00633060;
extern void scpKillEnemyOne(int a0);
extern void func_0017C990(int a0);

void func_0022D848(volatile int a0) {
    int save;
    while (scpTriggerBall(a0, D_00631AE4, 500.0f) == 0) {
        _ACTWait(1);
    }
    D_00633060 = 0;
    _ACTWait(1);
    save = D_00632110;
    D_00632110 = 0;
    _ACTWait(0x1E);
    func_0017B258(0x10F);
    scpKillEnemyOne(0x388);
    scpKillEnemyOne(0x391);
    scpKillEnemyOne(0x392);
    func_0017C990(0x393);
    _ACTWait(0x1E);
    D_00632110 = save;
    _ACTWait(1);
    D_00633060 = 1;
}

extern void SetWayGroupActive(int a0, int a1);

void func_0022D8F8(void) {
    if (func_0017B230(0x112) != 0) {
        stage_KillPlayBgAnimation(0x15E, 0, -1);
        SetWayGroupActive(0xF, 1);
    } else {
        stage_KillPlayBgAnimation(0x15E, 0, 0);
    }
    if (func_0017B230(0x114) == 0) {
        SetWayGroupActive(0x17, 0);
        stage_KillPlayBgAnimation(0x161, 0, 0);
    } else {
        SetWayGroupActive(0x17, 1);
        stage_KillPlayBgAnimation(0x161, 0, -1);
    }
    if (func_0017B230(0x113) == 0) {
        stage_KillPlayBgAnimation(0x160, 0, 0);
    } else {
        stage_KillPlayBgAnimation(0x160, 0, -1);
    }
}

extern int D_00633A78;

void func_0022D9C0(volatile int a0) {
    while (scpTriggerBall(a0, D_00631AE4, 50.0f) == 0) {
        _ACTWait(1);
    }
    iosPadDevRead(D_00631AEC, 0x10);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0x112);
    scpPlayStart(0x5A, &D_00633A78, 1, 1, 1);
    while (D_00633A78 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x15E, 1, 0);
    while (func_0012AA80(0x15E) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    SetWayGroupActive(0xF, 1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern float scpSekizou(int a0);
extern int D_00633A7C;

void func_0022DAC8(volatile int a0) {
    while (!(scpSekizou(0x5DB) < -2.0f)) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0x113);
    _ACTWait(0x1E);
    scpPlayStart(0x47, &D_00633A7C, 1, 1, 1);
    while (D_00633A7C == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x160, 1, 0);
    while (func_0012AA80(0x160) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int scpIsBombExplode(int a0);
extern int actCreateSubThread(void *fn, int a1);
extern int scpPlayEnd(void);
extern void scpTrans(int a0, int a1);
extern void scpFadeOut(int a0, int a1, int a2, float f);
extern int scpFadeChk(void);
extern void iosPadActStopAll(void);
extern void iosThreadSetPri(int a0, int a1);
extern void func_0018CEE0(void);
extern void gflagOff(int a0, int a1);
extern void scpFadeIn(float f);
extern void func_00122C48(int a0);
extern void func_0022ED40(volatile unsigned int a0);
extern void func_0022DDD8(volatile int a0);
extern int D_00275254[];

void func_0022DBC8(volatile int a0) {
    int v0;
    int sub;
    int st;

    while ((v0 = scpIsBombExplode(0x13)) == 0 || scpTriggerBall(a0, v0, 350.0f) == 0) {
        _ACTWait(1);
    }
    if (D_00631AE8 != 0 && scpSleepSpiderGroupOne(D_00631AE8, 0x4000000) != 0) {
        actCreateSubThread(func_0022ED40, 0x15);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    func_0017B258(0x114);
    func_00122C48(1);
    scpPlayStart(0x46, (int *)&D_00633A80, 1, 1, 0);
    _ACTWait(0x3C);
    while (D_00633A80 == 0) {
        _ACTWait(1);
    }
    sub = actCreateSubThread(func_0022DDD8, 0x15);
    D_00633FB4 = 0;
    while (D_00633FB4 == 0 && ((D_00275254[0] & 0x800) == 0 || scpPlayEnd() != 0)) {
        _ACTWait(1);
    }
    st = D_00633FB4 ^ 1;
    if (st != 0) {
        scpTrans((int)D_00633A80, 0xC0);
        scpFadeOut(0, 0, 0, 16.0f);
        while (scpFadeChk() != 0) {
            _ACTWait(1);
        }
    }
    iosPadActStopAll();
    iosThreadSetPri(sub + 0x24, 0x22);
    if (st) {
        stage_KillPlayBgAnimation(0x161, 1, -1);
        func_0018CEE0();
        gflagOff(D_00631AE4, 0);
        scpFadeIn(3.0f);
    }
    ((int *)actSt25aQueenDeadChk(0x5D1))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x5D2))[0x16C / 4] = 1;
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
    func_00122C48(0);
    SetWayGroupActive(0x17, 1);
}

extern void AdpcmPlay(int a0);

void func_0022DDD8(volatile int a0) {
    stage_KillPlayBgAnimation(0x161, 1, 0);
    AdpcmPlay(D_00633A80[0x2C / 4]);
    ((int *)actSt25aQueenDeadChk(0x5D1))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x5D2))[0x16C / 4] = 0;
    while (func_0012AB50(0x161, 0xD7, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0xF);
    while (func_0012AB50(0x161, 0x10E, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    while (func_0012AB50(0x161, 0x118, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0xF);
    while (func_0012AB50(0x161, 0x12C, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    while (func_0012AA80(0x161) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_00633FB4 = 1;
    _ACTWait(0);
}

void func_0022DF60(volatile int a0) {
    int se;
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_0017B258(0x115);
    ((int *)actSt25aQueenDeadChk(0x5EC))[0x16C / 4] = 1;
    _ACTWait(0x1E);
    scpPlayStart(0x5B, &D_00633A84, 1, 1, 1);
    while (D_00633A84 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0x15F, 1, 0);
    se = soundSeDefPlayWithVolumeRate(0x4EF, 0, 0, 1);
    _ACTWait(0xB4);
    soundSeDefPitchSet(se);
    soundSeDefPlayWithVolumeRate(0x4F0, 0, 0, 1);
    iosPadDevRead(D_00631AEC, 0x11);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

typedef struct KSub_e058 {
    char pad[0xC4];
    int *unkC4;
} KSub_e058;

extern int D_004D3180[];
extern int D_004D31A0[];
extern void scpLinkBGAtoLayoutedTarget(int a0, int a1);

void func_0022E058(volatile int a0) {
    int x = a0;
    KSub_e058 *s = (KSub_e058 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x122) == 0) {
        ((int *)actSt25aQueenDeadChk(0x5F5))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5F6))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5F9))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FA))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FB))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FC))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FD))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FE))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FF))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x600))[0x16C / 4] = 0;
        scpLinkBGAtoLayoutedTarget(0x5F7, 0x81);
        stage_KillPlayBgAnimation(0x81, 0, 0x1E);
        SetWayGroupActive(0x25, 1);
        SetWayGroupActive(0x26, 1);
        D_004D3180[1] = (int)func_0022E398;
        s->unkC4 = D_004D3180;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        ((int *)actSt25aQueenDeadChk(0x5F7))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5F8))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FD))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FE))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5FF))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x600))[0x16C / 4] = 0;
        func_0017B288(0x122);
        scpLinkBGAtoLayoutedTarget(0x5F5, 0x81);
        stage_KillPlayBgAnimation(0x81, 0, 0);
        D_004D31A0[1] = (int)func_0022E508;
        s->unkC4 = D_004D31A0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

typedef struct KSub_e220 {
    char pad[0xC4];
    int *unkC4;
} KSub_e220;

extern int D_004D31C0[];

void func_0022E220(volatile int a0) {
    KSub_e220 *s = *(KSub_e220 **)(a0 + 0x164);
    while (scpTriggerBall(a0, (int)actSt25aQueenDeadChk(0x5F7), 5.0f) == 0) {
        _ACTWait(1);
    }
    ((int *)actSt25aQueenDeadChk(0x5FD))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x5FE))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x5FF))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x600))[0x16C / 4] = 0;
    stage_KillPlayBgAnimation(0x81, 1, 0);
    while (func_0012AB50(0x81, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012AB50(0x81, 0x1E, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(0x25, 1);
    SetWayGroupActive(0x26, 1);
    func_0017B288(0x119);
    D_004D31C0[1] = (int)func_0022E398;
    s->unkC4 = D_004D31C0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_e398 {
    char pad[0xC4];
    int *unkC4;
} KSub_e398;

extern int D_004D31E0[];
extern int func_0012AB50(int a0, int a1, int a2);

void func_0022E398(volatile int a0) {
    KSub_e398 *s = *(KSub_e398 **)(a0 + 0x164);
    while (scpTriggerBall(a0, (int)actSt25aQueenDeadChk(0x5F7), 5.0f) != 0) {
        _ACTWait(1);
    }
    ((int *)actSt25aQueenDeadChk(0x5FD))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x5FE))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x5FF))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x600))[0x16C / 4] = 1;
    stage_KillPlayBgAnimation(0x81, 1, 0x1F);
    while (func_0012AB50(0x81, 0x28, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012AA80(0x81) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(0x25, 0);
    SetWayGroupActive(0x26, 0);
    func_0017B258(0x119);
    D_004D31E0[1] = (int)func_0022E220;
    s->unkC4 = D_004D31E0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_e508 {
    char pad[0xC4];
    int *unkC4;
} KSub_e508;

extern int D_004D3200[];

void func_0022E508(volatile int a0) {
    int *tbl;
    KSub_e508 *s = *(KSub_e508 **)(a0 + 0x164);
    while (scpTriggerBall(a0, (int)actSt25aQueenDeadChk(0x5F5), 5.0f) == 0) {
        _ACTWait(1);
    }
    ((int *)actSt25aQueenDeadChk(0x5F9))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x5FA))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x5FB))[0x16C / 4] = 0;
    ((int *)actSt25aQueenDeadChk(0x5FC))[0x16C / 4] = 0;
    stage_KillPlayBgAnimation(0x81, 1, 0);
    while (func_0012AB50(0x81, 0xA, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012AB50(0x81, 0x1E, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(0x25, 1);
    SetWayGroupActive(0x26, 1);
    func_0017B288(0x119);
    /* D_004D31E0 + 0x20 == D_004D3200: same contiguous table run */
    tbl = &D_004D31E0[8];
    tbl[1] = (int)func_0022E680;
    s->unkC4 = tbl;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_e680 {
    char pad[0xC4];
    int *unkC4;
} KSub_e680;

void func_0022E680(volatile int a0) {
    int *tbl;
    KSub_e680 *s = *(KSub_e680 **)(a0 + 0x164);
    while (scpTriggerBall(a0, (int)actSt25aQueenDeadChk(0x5F5), 5.0f) != 0) {
        _ACTWait(1);
    }
    ((int *)actSt25aQueenDeadChk(0x5F9))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x5FA))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x5FB))[0x16C / 4] = 1;
    ((int *)actSt25aQueenDeadChk(0x5FC))[0x16C / 4] = 1;
    stage_KillPlayBgAnimation(0x81, 1, 0x1F);
    while (func_0012AB50(0x81, 0x28, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    soundSeDefPlayWithVolumeRate(0x522, 0, 0, 1);
    while (func_0012AA80(0x81) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    SetWayGroupActive(0x25, 0);
    SetWayGroupActive(0x26, 0);
    func_0017B258(0x119);
    /* D_004D31E0 + 0x40 == D_004D3220: same contiguous table run */
    tbl = &D_004D31E0[16];
    tbl[1] = (int)func_0022E508;
    s->unkC4 = tbl;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_e7f0 {
    char pad[0xC4];
    int *unkC4;
} KSub_e7f0;

extern int D_004D3080[];
extern void func_0022D9C0(volatile int a0);

void func_0022E7F0(volatile int a0) {
    int x = a0;
    KSub_e7f0 *s = (KSub_e7f0 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x112) == 0) {
        D_004D3080[1] = (int)func_0022D9C0;
        s->unkC4 = D_004D3080;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

typedef struct KSub_e868 {
    char pad[0xC4];
    int *unkC4;
} KSub_e868;

extern int D_004D30A0[];
extern void func_0022DAC8(volatile int a0);
extern float D_00631650;
extern void gflagLoad(int a0, float f);

void func_0022E868(volatile int a0) {
    int x = a0;
    KSub_e868 *s = (KSub_e868 *)actInitialize(a0);
    _ACTWait(1);
    gflagLoad(0x5F1, D_00631650);
    if (func_0017B230(0x113) == 0) {
        D_004D30A0[1] = (int)func_0022DAC8;
        s->unkC4 = D_004D30A0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

typedef struct KSub_e8f0 {
    char pad[0xC4];
    int *unkC4;
} KSub_e8f0;

extern int D_004D30C0[];
extern void func_0022DBC8(volatile int a0);

void func_0022E8F0(volatile int a0) {
    int x = a0;
    KSub_e8f0 *s = (KSub_e8f0 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x114) == 0) {
        D_004D30C0[1] = (int)func_0022DBC8;
        s->unkC4 = D_004D30C0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

typedef struct KSub_e968 {
    char pad[0xC4];
    int *unkC4;
} KSub_e968;

extern int D_004D30E0[];
extern void func_0022ED98(volatile int a0);

void func_0022E968(volatile int a0) {
    int x = a0;
    KSub_e968 *s = (KSub_e968 *)actInitialize(a0);
    _ACTWait(1);
    D_004D30E0[1] = (int)func_0022ED98;
    s->unkC4 = D_004D30E0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_e9d0 {
    char pad[0xC4];
    void *unkC4;
    char pad2[0xA4];
    int unk16C;
} KSub_e9d0;

extern int *D_004D3120[];
extern void func_0022EE68(volatile int a0);

void func_0022E9D0(volatile int a0) {
    int x = a0;
    KSub_e9d0 *s = (KSub_e9d0 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x115) == 0) {
        stage_KillPlayBgAnimation(0x15F, 0, 0);
        ((KSub_e9d0 *)actSt25aQueenDeadChk(0x5EC))->unk16C = 0;
        D_004D3120[1] = (int *)func_0022EE68;
        s->unkC4 = (void *)D_004D3120;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x15F, 0, -1);
    }
}

extern float D_00631654, D_00631658;
extern void func_0017BF78(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);

void func_0022EA78(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_0017BF78(a0, 0x116, 0x162, 0, 0x12, 0.0f, D_00631654, D_00631658, -75.0f, D_00631654, D_00631658);
}

typedef struct KSub_eae0 {
    char pad[0xC4];
    int *unkC4;
} KSub_eae0;

extern int D_004D3160[];
extern void func_0022EF00(volatile int a0);

void func_0022EAE0(volatile int a0) {
    int x = a0;
    KSub_eae0 *s = (KSub_eae0 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x117) == 0) {
        D_004D3160[1] = (int)func_0022EF00;
        s->unkC4 = D_004D3160;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

void func_0022EB58(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x118) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

void func_0022EC00(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x118) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    Generator_MaskOff(a0);
}

void func_0022EC70(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x122) != 0) {
        ((int *)actSt25aQueenDeadChk(0x5F7))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5F8))[0x16C / 4] = 0;
        func_0017B288(0x122);
    } else {
        ((int *)actSt25aQueenDeadChk(0x5F5))[0x16C / 4] = 0;
        ((int *)actSt25aQueenDeadChk(0x5F6))[0x16C / 4] = 0;
    }
}

void func_0022ECF0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xDA) == 0) {
        ((int *)actSt25aQueenDeadChk(0x5D5))[0x16C / 4] = 0;
    } else {
        ((int *)actSt25aQueenDeadChk(0x5D4))[0x16C / 4] = 0;
    }
}

