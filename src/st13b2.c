#include "common.h"

typedef struct { char pad[0xC0]; void *f_B0; void *unkB4; } BoxObj_st13b2;

extern int D_00631AE8;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern void actConte11(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void func_0017B288(int a0);
extern void func_0017C8C0(int a0);
extern void func_0017C8F8(int a0);
extern void func_0017C990(int a0);
extern void lt_fade_status(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

extern int D_00632110;
void actSt13b2Generator(volatile int a0) {
    int save;
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x5000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017C8F8(0xD7D);
    func_0017B288(0x166);
    func_0017B258(0x45);
    func_0017B258(0x47);
    _ACTWait(0x3C);
    save = D_00632110;
    D_00632110 = 0;
    actConte11(0x130);
    actConte11(0x131);
    actConte11(0x132);
    func_0017C990(0x133);
    stage_KillPlayBgAnimation(0x5A, 1, 0);
    while (func_0012AA80(0x5A) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_00632110 = save;
    lt_fade_status(0x32);
    D_006325B4 = 0;
    func_0017C8C0(0xD7D);
}

extern void AddWayPointTop();
extern void scpDispOnAllWithKind(void);
extern void scpActivateAllWithKind(void);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, void *a2, int a3);
extern int D_004D2B50[];

void func_0022A2C8(volatile int a0)
{
    lt_fade_status(0x33);
    func_0017B258(0x43);
    scpDispOnAllWithKind();
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x5B, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, D_004D2B50, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, D_004D2B50, 1);
    while (func_0012AA80(0x5B) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    AddWayPointTop(0xB, 1);
    scpActivateAllWithKind();
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern int actInitialize(int a0);
extern int func_0017B230(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2B10[];
extern void func_0022A8B0(volatile int a0);

void func_0022A398(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x43) == 0) {
        stage_KillPlayBgAnimation(0x5B, 0, 0);
        D_004D2B10[1] = (int)func_0022A8B0;
        gobj->unkB4 = D_004D2B10;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        AddWayPointTop(0xB, 1);
        stage_KillPlayBgAnimation(0x5B, 0, -1);
    }
}

extern int D_004D2AB0[];
extern void actSt13bMeetAgainChk(volatile int a0);

void func_0022A440(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x44) == 0) {
        D_004D2AB0[1] = (int)actSt13bMeetAgainChk;
        gobj->unkB4 = D_004D2AB0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D2AD0[];

void func_0022A4B8(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x45) == 0) {
        D_004D2AD0[1] = (int)actSt13b2Generator;
        gobj->unkB4 = D_004D2AD0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void func_0022A530(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x46) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x74);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void func_0022A5D8(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x46) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x64);
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void func_0022A680(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x47) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

void func_0022A720(volatile int a0)
{
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0x47) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
}

extern int D_004D2B60[];
extern void func_0022A940(volatile int a0);

void func_0022A7C0(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x48) == 0) {
        D_004D2B60[1] = (int)func_0022A940;
        gobj->unkB4 = D_004D2B60;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern void gflagLoad(int a0, float f);
extern int actSt25aQueenDeadChk(int a0);

void func_0022A838(void)
{
    float f = 0.95f;
    gflagLoad(0x150, f);
    gflagLoad(0x14F, f);
    if (func_0017B230(0x49) != 0) {
        stage_KillPlayBgAnimation(0x14F, 0, 0x1FE);
        *(int *)(actSt25aQueenDeadChk(0x150) + 0x16C) = 0;
    } else {
        stage_KillPlayBgAnimation(0x14F, 0, 0);
        *(int *)(actSt25aQueenDeadChk(0x14F) + 0x16C) = 0;
    }
}

extern int D_004D2AF0[];

void func_0022A8B0(volatile int a0)
{
    int s = *(int *)(a0 + 0x164);
    D_006325B4 = 0;
    *(int *)(s + 0xC0) = (int)D_004D2AF0;
    for (;;) {
        _ACTWait(1);
    }
}

extern int *D_004D2B30[];

void func_0022A8E8(volatile int a0) {
    BoxObj_st13b2 *obj = *(BoxObj_st13b2 **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D2B30[1] = (int *)func_0022A2C8;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D2B30;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int *D_00631AE4;
extern int scpSleepEnemyOne(int a0, int *a1, float f);

void func_0022A940(volatile int a0)
{
    while (scpSleepEnemyOne(a0, D_00631AE4, 100.0f) == 0) {
        _ACTWait(1);
    }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017B258(0x48);
    stage_KillPlayBgAnimation(0x73, 1, 0);
    while (func_0012AA80(0x73) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
}

extern int D_00631AEC;
extern int D_00633FB0;
extern void func_001D4170(int a0);
extern int func_0012AB50(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);

union Vec_st13b2 { long long q[2]; float f[4]; };

extern union Vec_st13b2 D_0061C040, D_0061C050;
extern int D_00275254[];
extern int D_004D2BC0[];
extern void actSt13cBmg1(volatile int a0);
extern void func_0022B5E8(volatile int a0);
extern void func_0022AEA8(volatile int a0);
extern void func_0022AD90(volatile int a0);
extern int actCreateSubThread(void *fn, int a1);
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int scpPlayEnd(void);
extern void scpTrans(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f);
extern int actSt25aQueenDeadEvent(void);
extern void iosSemaWait(int a0, int a1);
extern void gflagOff(int a0, int a1);
extern void actConte11Jimaku(float f);
extern void CageDL(int a0);
extern void GetCylinderCollisionWithExceptOwnCollision(int a0, void *a1);

void func_0022A9E8(volatile int a0)
{
    union Vec_st13b2 b1;
    union Vec_st13b2 b2;
    int st;
    int sub = 0;
    int th;
    int frames;
    BoxObj_st13b2 *gobj = *(BoxObj_st13b2 **)(a0 + 0x164);

    D_006325B4 = 1;
    gobj->f_B0 = 0;
    if (D_00631AE8 != 0 && scpSleepSpiderGroupOne(D_00631AE8, 0x3000000) != 0) {
        sub = actCreateSubThread(func_0022B5E8, 0x15);
    }
    lt_fade_status(0x33);
    if (func_0017B230(0x49) != 0) {
        scpPlayStart(0x38, &st, 1, 1, 1);
        while (st == 0) {
            _ACTWait(1);
        }
        th = actCreateSubThread(func_0022AEA8, 0x15);
        frames = 0x3FC;
    } else {
        scpPlayStart(0x37, &st, 1, 1, 1);
        while (st == 0) {
            _ACTWait(1);
        }
        th = actCreateSubThread(func_0022AD90, 0x15);
        frames = 0x1FE;
    }
    _ACTWait(3);
    D_00633FB0 = 0;
    while (D_00633FB0 == 0 && ((D_00275254[0] & 0x800) == 0 || scpPlayEnd() != 0)) {
        _ACTWait(1);
    }
    iosSemaWait(th + 0x24, 0x22);
    if (sub != 0) {
        iosSemaWait(sub + 0x24, 0x22);
    }
    if (D_00633FB0 == 0) {
        scpTrans(st, 0x80);
        actSt25aQueenBeforeChk(0, 0, 0, 16.0f);
        while (actSt25aQueenDeadEvent() != 0) {
            _ACTWait(1);
        }
        stage_KillPlayBgAnimation(0x14F, 1, frames - 0x3C);
        _ACTWait(1);
        CageDL(actSt25aQueenDeadChk(0x150));
        CageDL(actSt25aQueenDeadChk(0x14F));
        _ACTWait(1);
        if (sub != 0) {
            gflagOff(D_00631AE8, 0x202);
            if (func_0017B230(0x49) != 0) {
                b1 = D_0061C040;
                GetCylinderCollisionWithExceptOwnCollision(D_00631AE8, &b1);
            } else {
                b2 = D_0061C050;
                b2.f[1] += *(float *)(*(int *)(*(int *)(D_00631AE8 + 0x15C) + 0x8C) + 0x14);
                GetCylinderCollisionWithExceptOwnCollision(D_00631AE8, &b2);
            }
        }
        actConte11Jimaku(3.0f);
    }
    while (func_0012AB50(0x14F, frames, 1) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    lt_fade_status(0x32);
    if (func_0017B230(0x49) != 0) {
        *(int *)(actSt25aQueenDeadChk(0x150) + 0x16C) = 1;
        *(int *)(actSt25aQueenDeadChk(0x14F) + 0x16C) = 0;
        _ACTWait(1);
        func_0017B288(0x49);
    } else {
        func_0017B258(0x49);
    }
    D_004D2BC0[1] = (int)actSt13cBmg1;
    gobj->unkB4 = D_004D2BC0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

void func_0022AD90(volatile int a0)
{
    func_001D4170(0x12C);
    stage_KillPlayBgAnimation(0x14F, 1, 0);
    *(int *)(actSt25aQueenDeadChk(0x150) + 0x16C) = 0;
    *(int *)(actSt25aQueenDeadChk(0x14F) + 0x16C) = 1;
    while (func_0012AB50(0x14F, 5, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x10);
    while (func_0012AB50(0x14F, 0xD7, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    while (func_0012AB50(0x14F, 0x1D1, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    D_00633FB0 = 1;
    _ACTWait(0);
}

void func_0022AEA8(volatile int a0)
{
    func_001D4170(0x12C);
    stage_KillPlayBgAnimation(0x14F, 1, 0x1FF);
    while (func_0012AB50(0x14F, 0x2DC, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    while (func_0012AB50(0x14F, 0x336, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    while (func_0012AB50(0x14F, 0x3E3, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00631AEC, 0x11);
    D_00633FB0 = 1;
    _ACTWait(0);
}

extern int D_004D2BE0[];
extern int D_004D2C00[];
extern void func_0022B228(volatile int a0);
extern void func_0022B0B0(volatile int a0);

void func_0022AFA8(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    if (scpSleepEnemyOne(a0, D_00631AE4, 200.0f) != 0 ||
        (D_00631AE8 != 0 && scpSleepEnemyOne(a0, (int *)D_00631AE8, 400.0f) != 0)) {
        stage_KillPlayBgAnimation(0x151, 0, 0);
        _ACTWait(0x3C);
        D_004D2BE0[1] = (int)func_0022B228;
        gobj->unkB4 = D_004D2BE0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x150, 0, 0);
        D_004D2C00[1] = (int)func_0022B0B0;
        gobj->unkB4 = D_004D2C00;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

struct QBuf_st13b2 { long long a, b; };

extern struct QBuf_st13b2 D_0061C060;
extern int D_004D2C20[];
extern void actSt13cConte04(volatile int a0);
extern int scpKillSpiderGroup(int a0, int a1);
extern void func_0017E870(float a0, float a1, float a2, float a3);

void func_0022B0B0(volatile int a0)
{
    struct QBuf_st13b2 buf;
    BoxObj_st13b2 *gobj = *(BoxObj_st13b2 **)(a0 + 0x164);
    while (scpKillSpiderGroup(a0, 0x4000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0xF);
    actCreateSubThread(actSt13cConte04, 0x15);
    func_0017E870(-1189.0f, -2326.0f, -408.0f, 100.0f);
    stage_KillPlayBgAnimation(0x150, 1, 0);
    buf = D_0061C060;
    soundSeDefPlayWithVolumeRate(0x4AC, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, &buf, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, &buf, 1);
    while (func_0012AA80(0x150) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    D_004D2C20[1] = (int)func_0022B228;
    gobj->unkB4 = D_004D2C20;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022B228);
ASM_LIT4_SLOT(D_00631634, -1189.0f);
ASM_LIT4_SLOT(D_00631638, -2326.0f);

extern int D_004D2BA0[];

void func_0022B3A0(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    D_004D2BA0[1] = (int)actSt13cBmg1;
    gobj->unkB4 = D_004D2BA0;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D2C60[];
extern void actSt13cCage1stDownDemoCancel(volatile int a0);

void func_0022B408(volatile int a0)
{
    int x = a0;
    BoxObj_st13b2 *gobj = (BoxObj_st13b2 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x4A) == 0) {
        D_004D2C60[1] = (int)actSt13cCage1stDownDemoCancel;
        gobj->unkB4 = D_004D2C60;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

