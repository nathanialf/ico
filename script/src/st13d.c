#include "common.h"

extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern int iosPadDevRead(int a0, int a1);
extern void func_00178DD8(int a0);
extern void scpTrans(int a0, int a1);
extern int scpTriggerBallTargetMan(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt17aDoorDownChk(void);
extern int D_0062BD74;
extern int D_00629DEC;
extern int D_004CDA90[];

void actSt13dExit(volatile int a0) {
    struct { char pad[0xB4]; int *unkB4; } *gobj = *(void **)(a0 + 0x164);
    scpPlayStart(0x56, (int)&D_0062BD74, 1, 1, 1);
    while (D_0062BD74 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x158, 1, 0);
    while (func_0012AA28(0x158, 0xA9, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x10);
    while (func_0012AA28(0x158, 0xB3, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x109);
    if (D_0062BD74 != 0) {
        scpTrans(D_0062BD74, 0x100);
    }
    while (scpTriggerBallTargetMan(D_0062BD74) != 0) { _ACTWait(1); }
    D_004CDA90[1] = (int)actSt17aDoorDownChk;
    gobj->unkB4 = D_004CDA90;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern void jimakuMgrJump(int a0);
extern void jimakuMgrEnd(void);
extern void func_00178E08(int a0);
extern int D_00629DE4;
extern int D_0062BD78;
extern int D_004CDAB0[];

void actSt13dExitR(volatile int a0) {
    struct { char pad[0xB4]; int *unkB4; } *gobj = *(void **)(a0 + 0x164);
    jimakuMgrJump(D_00629DE4);
    scpPlayStart(0x57, (int)&D_0062BD78, 1, 1, 1);
    while (D_0062BD78 == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x158, 1, 0xB4);
    while (func_0012AA28(0x158, 0x154, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0x11);
    while (func_0012AA28(0x158, 0x168, 1) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178E08(0x109);
    if (D_0062BD78 != 0) {
        scpTrans(D_0062BD78, 0x100);
    }
    while (scpTriggerBallTargetMan(D_0062BD78) != 0) { _ACTWait(1); }
    jimakuMgrEnd();
    D_004CDAB0[1] = (int)actSt17aDoorDownChk;
    gobj->unkB4 = D_004CDAB0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void func_00178DD8(int a0);
extern void func_00178E08(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int actSt25aQueenTalkChk(int a0, int a1, void *a2, int a3, float f);
extern int func_0012A958(int a0);
extern void lt_fade_status(int a0);
extern void scpActivateAllWithKind(void);
extern int D_00629DE8;
extern int D_0062A894;
extern int D_00271240[];
struct Q { long long a, b; };
extern struct Q D_00614BC0;

void actSt13dExitL(volatile int a0) {
    struct Q buf;
    while (func_00178DB0(0x10E) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x10D);
    stage_KillPlayBgAnimation(0x15A, 1, 0);
    buf = D_00614BC0;
    actSt25aQueenTalkChk(D_00629DE8, 0, &buf, 0, 100.0f);
    while (func_0012A958(0x15A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_00178E08(0x10D);
    _ACTWait(((0x3C - D_00271240[0] * 0xA) / D_00271240[1]) * 3);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    scpActivateAllWithKind();
}

#include "common.h"
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178DD8(int a0);
extern void _ACTWait(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void func_0018A380(void);
extern int func_0012AA28(int a0, int a1, int a2);
extern int actSt25aQueenDeadChk(int a0);
extern void scpActivateAllWithKind(void);
extern int D_0062BD7C;
extern int D_0062A894;
void actSt13dInit(volatile int a0) {
    lt_fade_status(0x33);
    scpDispOnAllWithKind();
    func_00178DD8(0x105);
    _ACTWait(0x1E);
    scpPlayStart(0x5F, (int)&D_0062BD7C, 1, 1, 1);
    while (D_0062BD7C == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x15C, 1, 0);
    func_0018A380();
    while (func_0012AA28(0x15C, 0xF0, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    *(int *)(actSt25aQueenDeadChk(0x382) + 0x16C) = 1;
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_002292F0);


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt17aDoorUpChk(void);
extern int D_004CD970[];
void func_00229398(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    D_004CD970[1] = (int)actSt17aDoorUpChk;
    gobj->unkB4 = D_004CD970;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern int func_00178DB0(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt17aDoorDownChk(void);
extern int D_004CDA30[];
void func_00229400(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x109) != 0) {
        stage_KillPlayBgAnimation(0x158, 0, 0);
        _ACTWait(0xA);
        stage_KillPlayBgAnimation(0x158, 0, 0xB3);
    } else {
        stage_KillPlayBgAnimation(0x158, 0, 0);
    }
    D_004CDA30[1] = (int)actSt17aDoorDownChk;
    gobj->unkB4 = D_004CDA30;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_00629938;

void func_002294B0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x106, 0x15B, 0, 0x12, 0.0f, -72.0f, D_00629938, 76.0f, -72.0f, D_00629938);
}

extern int D_004CDAF0[];
extern void actSt17aHasiEffect(void);

void func_00229518(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    D_004CDAF0[1] = (int)actSt17aHasiEffect;
    gobj->unkB4 = D_004CDAF0;
    BoxBarSoundOn((int)a0, 0x189);
    _ACTWait(0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229580(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10B) == 0) { _ACTWait(1); }
    _ACTWait(0x74);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229600(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10B) == 0) { _ACTWait(1); }
    _ACTWait(0x64);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229680(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10C) == 0) { _ACTWait(1); }
    _ACTWait(0x74);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229700(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10C) == 0) { _ACTWait(1); }
    _ACTWait(0x64);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229780(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10C) == 0) { _ACTWait(1); }
    _ACTWait(0x82);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229800(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10D) == 0) { _ACTWait(1); }
    _ACTWait(0x1);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229880(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10D) == 0) { _ACTWait(1); }
    _ACTWait(0x140);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int func_00178DB0(int a0);
extern void actSt17aHasiChk(void);
extern int D_004CDAD0[];
void func_00229900(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x10B) == 0) {
        D_004CDAD0[1] = (int)actSt17aHasiChk;
        gobj->unkB4 = D_004CDAD0;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void actLinkTest(void);
extern int D_004CDB10[];
void func_00229978(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x10C) == 0) {
        D_004CDB10[1] = (int)actLinkTest;
        gobj->unkB4 = D_004CDB10;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern void actSt13dExitL(volatile int a0);
extern int D_004CDB30[];
void func_002299F0(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x10E) == 0) {
        D_004CDB30[1] = (int)actSt13dExitL;
        gobj->unkB4 = D_004CDB30;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    }
}


extern int actSt25aQueenDeadChk(int a0);
extern void actSt17aHasi(void);
extern int D_004CDB50[];
void func_00229A68(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x10F) == 0) {
        D_004CDB50[1] = (int)actSt17aHasi;
        gobj->unkB4 = D_004CDB50;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x37A) + 0x16C) = 0;
    }
}


extern void actSt17aIntro(void);
extern int D_004CDB70[];
void func_00229AF0(volatile int a0) {
    int x = a0;
    struct { char pad[0xB4]; int *unkB4; } *gobj = (void *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x110) == 0) {
        D_004CDB70[1] = (int)actSt17aIntro;
        gobj->unkB4 = D_004CDB70;
        BoxBarSoundOn((int)a0, 0x189);
        _ACTWait(0);
    } else {
        *(int *)(actSt25aQueenDeadChk(0x37B) + 0x16C) = 0;
    }
}

