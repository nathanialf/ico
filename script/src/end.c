#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern void func_0017A0F8(int a0);
extern void func_001790A8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern int stage_DispBgAnimation(int a0, int a1);
extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int D_00629DE4;
extern int D_00629DE8;
void actEndDemo01(volatile int a0) {
    func_0017A0F8(3);
    func_001790A8(D_00629DE4);
    stage_KillPlayBgAnimation(0x2FB, 1, 0);
    stage_KillPlayBgAnimation(0x2FD, 1, 0);
    stage_KillPlayBgAnimation(0x2FE, 1, 0);
    gflagOff(D_00629DE4, 0x1B8);
    gflagOff(actSt25aQueenDeadChk(0x8E7), 0x309);
    *(int *)(actSt25aQueenDeadChk(0x8E7) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x2FB, 0x2FC) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1B9);
    gflagOff(actSt25aQueenDeadChk(0x8E7), 0x30A);
    while (func_0012A958(0x2FC) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(3, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
}


extern int actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void LightLineGeo(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern void scpPlayMotDir(int a0, int a1, int a2, int a3);
extern void func_0012AAB8(int a0, int a1);
extern int func_00178DB0(int a0);
extern int D_0062A894;
extern int D_004CB860[];
extern void actSubMpegReturnPreload(volatile int a0);
void actConte14_1(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayMotDir(3, 0, 0x1E2, 0);
    stage_KillPlayBgAnimation(0x97, 0, 0);
    func_0012AAB8(0x1E2, 1);
    stage_KillPlayBgAnimation(0x1E2, 1, 0);
    if (func_00178DB0(0x139) == 0) {
        LightLineGeo(D_00629DE4, 2);
        D_004CB860[1] = (int)actSubMpegReturnPreload;
        gobj->unkB4 = D_004CB860;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo02);

extern int actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void LightLineGeo(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern void scpPlayMotDir(int a0, int a1, int a2, int a3);
extern void func_0012AAB8(int a0, int a1);
extern int D_0062A894;
extern int D_004CB880[];
extern void actSt26aConte01_1_newgame(volatile int a0);
void actConte14_2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayMotDir(3, 0, 0x1E2, 0);
    func_0012AAB8(0x1E2, 1);
    stage_KillPlayBgAnimation(0x1E2, 1, 0);
    LightLineGeo(D_00629DE4, 2);
    stage_KillPlayBgAnimation(0x307, 0, 0);
    D_004CB880[1] = (int)actSt26aConte01_1_newgame;
    gobj->unkB4 = D_004CB880;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void func_0017A0F8(int a0);
void actEndDemo06(volatile int a0) {
    func_0017A0F8(3);
    func_001790A8(D_00629DE4);
    stage_KillPlayBgAnimation(0x300, 1, 0);
    gflagOff(D_00629DE4, 0x1BB);
    gflagOff(actSt25aQueenDeadChk(0x77C), 0x30C);
    *(int *)(actSt25aQueenDeadChk(0x77C) + 0x16C) = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2A, 1, 0);
    stage_KillPlayBgAnimation(0x301, 1, 0);
    while (stage_DispBgAnimation(0x300, 0x302) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1BC);
    gflagOff(actSt25aQueenDeadChk(0x77C), 0x30D);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2B, 1, 0);
    while (stage_DispBgAnimation(0x302, 0x303) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1BD);
    gflagOff(actSt25aQueenDeadChk(0x77C), 0x30E);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2C, 1, 0);
    while (stage_DispBgAnimation(0x303, 0x304) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1BE);
    gflagOff(actSt25aQueenDeadChk(0x77C), 0x30F);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2D, 1, 0);
    while (stage_DispBgAnimation(0x304, 0x305) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1BF);
    gflagOff(actSt25aQueenDeadChk(0x77C), 0x310);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2E, 1, 0);
    while (stage_DispBgAnimation(0x305, 0x306) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1C0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2F, 1, 0);
    stage_KillPlayBgAnimation(0x35, 1, 0);
    stage_KillPlayBgAnimation(0x307, 1, 0);
    while (stage_DispBgAnimation(0x306, 0x308) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1C1);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x30, 1, 0);
    stage_KillPlayBgAnimation(0x36, 1, 0);
    while (func_0012A958(0x308) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(3, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
}


#include "common.h"
extern void func_001790A8(int a0);
extern void actConte11Jimaku(float f);
extern void func_0017A0F8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(int a0, int a1);
extern int stage_DispBgAnimation(int a0, int a1);
extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern void func_001790E8(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int D_00629DE4;
extern int D_00629DE8;
void actConte14_6(volatile int a0) {
    func_001790A8(D_00629DE4);
    actConte11Jimaku(3.0f);
    func_0017A0F8(6);
    stage_KillPlayBgAnimation(0x30B, 1, 0);
    gflagOff(D_00629DE4, 0x1C2);
    while (stage_DispBgAnimation(0x30B, 0x30C) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x32, 1, 0);
    stage_KillPlayBgAnimation(0x191, 1, 0);
    gflagOff(D_00629DE4, 0x1C2);
    while (func_0012A958(0x30C) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_001790E8(D_00629DE4);
    actSt25aQueenDead(6, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
}

extern void staffRollMain(int a0, float a1);
extern int func_0012AA28(int a0, int a1, int a2);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern int actSt25aQueenDeadEvent(void);
void actEndDemo07(volatile int a0) {
    func_0017A0F8(1);
    staffRollMain(0xFF, 1.0f);
    stage_KillPlayBgAnimation(0x20A, 1, 0);
    while (stage_DispBgAnimation(0x20A, 0x20B) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x19, 1, 0);
    gflagOff(D_00629DE4, 0x11A);
    while (stage_DispBgAnimation(0x20B, 0x20D) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x20D, 0x20E) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x11B);
    _ACTWait(0x82);
    stage_KillPlayBgAnimation(0x1F, 1, 0);
    while (stage_DispBgAnimation(0x20E, 0x20F) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x20F, 0x210) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x11C);
    while (stage_DispBgAnimation(0x210, 0x211) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x211, 0x212) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x11E);
    while (stage_DispBgAnimation(0x212, 0x213) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x11F);
    while (stage_DispBgAnimation(0x213, 0x214) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x120);
    while (stage_DispBgAnimation(0x214, 0x215) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x121);
    while (stage_DispBgAnimation(0x215, 0x216) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x122);
    while (stage_DispBgAnimation(0x216, 0x217) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x123);
    while (func_0012AA28(0x217, 0x64, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenBeforeChk(0, 0, 0, 8.0f);
    while (actSt25aQueenDeadEvent() != 0) { _ACTWait(1); }
    actSt25aQueenDead(1, D_00629DE4, D_00629DE8, 0.0f, 8.0f);
}


extern int func_0012AA28(int a0, int a1, int a2);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern int actSt25aQueenDeadEvent(void);
extern void shadow_Tool(int a0);
extern void UpdateStormPackage(int a0);
void actConte14_7(volatile int a0) {
    func_0017A0F8(1);
    stage_KillPlayBgAnimation(0x240, 1, 0);
    stage_KillPlayBgAnimation(0xED, 1, 0);
    gflagOff(D_00629DE4, 0x141);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2B6);
    *(int *)(actSt25aQueenDeadChk(0x9FC) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x240, 0x241) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x142);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2B7);
    while (stage_DispBgAnimation(0x241, 0x242) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x143);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2B8);
    while (stage_DispBgAnimation(0x242, 0x243) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x243, 0x244) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x144);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2B9);
    while (stage_DispBgAnimation(0x244, 0x245) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x145);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2BA);
    while (stage_DispBgAnimation(0x245, 0x246) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x146);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2BB);
    while (stage_DispBgAnimation(0x246, 0x247) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x147);
    while (stage_DispBgAnimation(0x247, 0x256) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x14F);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2C1);
    while (stage_DispBgAnimation(0x256, 0x257) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x150);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2C2);
    while (stage_DispBgAnimation(0x257, 0x258) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x151);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2C3);
    while (stage_DispBgAnimation(0x258, 0x259) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x152);
    gflagOff(actSt25aQueenDeadChk(0x9FC), 0x2C4);
    while (func_0012AA28(0x259, 0xC8, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    shadow_Tool(0);
    UpdateStormPackage(1);
    actSt25aQueenBeforeChk(0, 0, 0, 8.0f);
    while (actSt25aQueenDeadEvent() != 0) { _ACTWait(1); }
    actSt25aQueenDead(1, D_00629DE4, D_00629DE8, 0.0f, 8.0f);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actEndDemo10);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_10);


extern void actConte11Jimaku(float f);
extern void lt_fade_status(int a0);
extern void func_001790E8(int a0);
extern void func_00178E08(int a0);
extern void *ContinueCorrectPosition(int a0);
extern void func_00240008(void *a0, void *a1, void *a2);
extern void gflagChk(int a0, void *a1);
extern int D_0062A894;
typedef struct { long long _0; long long _8; } WpData16;
extern WpData16 D_006144B0;
void actConte14_13(volatile int a0) {
    WpData16 local10, local20;
    func_001790A8(D_00629DE4);
    actConte11Jimaku(6.0f);
    stage_KillPlayBgAnimation(0x311, 1, 0);
    gflagOff(D_00629DE4, 0x1C7);
    while (stage_DispBgAnimation(0x311, 0x312) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1C8);
    while (stage_DispBgAnimation(0x312, 0x313) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1C9);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x33, 1, 0);
    while (stage_DispBgAnimation(0x313, 0x314) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1CA);
    while (stage_DispBgAnimation(0x314, 0x315) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1CB);
    while (stage_DispBgAnimation(0x315, 0x316) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1CC);
    gflagOff(actSt25aQueenDeadChk(0x7FA), 0x312);
    *(int *)(actSt25aQueenDeadChk(0x7FA) + 0x16C) = 1;
    while (func_0012A958(0x316) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait(0xB4);
    gflagOff(D_00629DE4, 0);
    local10 = D_006144B0;
    func_00240008(&local20, &local10, ContinueCorrectPosition(D_00629DE4));
    gflagChk(D_00629DE4, &local20);
    func_001790E8(D_00629DE4);
    D_0062A894 = 0;
    lt_fade_status(0x32);
    func_00178E08(0x132);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actStaff1Demo);


extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void gflagOff(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);
extern int stage_DispBgAnimation(int a0, int a1);
extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int D_00629DE4;
extern int D_00629DE8;
void actStaff2Demo(volatile int a0) {
    stage_KillPlayBgAnimation(0x317, 1, 0);
    gflagOff(D_00629DE4, 0x1CD);
    gflagOff(actSt25aQueenDeadChk(0x7FA), 0x313);
    *(int *)(actSt25aQueenDeadChk(0x7FA) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x317, 0x318) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1CE);
    gflagOff(actSt25aQueenDeadChk(0x7FA), 0x314);
    while (stage_DispBgAnimation(0x318, 0x319) == 0) { _ACTWait(1); }
    gflagOff(D_00629DE4, 0x1CF);
    gflagOff(actSt25aQueenDeadChk(0x7FA), 0x315);
    while (func_0012A958(0x319) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(1, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
}


extern int actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern int D_0062A894;
extern int D_004CB7E0[];
extern void actOpDemo01_2(volatile int a0);
void actStaff3Demo(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE4 != 0) { gflagOff(D_00629DE4, 0); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    D_004CB7E0[1] = (int)actOpDemo01_2;
    gobj->unkB4 = D_004CB7E0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern int D_0062A894;
extern int D_004CB800[];
extern void actOpDemo02(volatile int a0);
void actEndDemo14(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (D_00629DE4 != 0) { gflagOff(D_00629DE4, 0); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    D_004CB800[1] = (int)actOpDemo02;
    gobj->unkB4 = D_004CB800;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/script/src/end", actConte14_14);


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void lt_fade_status(int a0);
extern void LightLineGeo(int a0, int a1);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_0062A894;
extern int D_00629DE4;
extern int D_004CB8A0[];
extern void actSt24aConte01_2_Jimaku(volatile int a0);
void actSt27aEndChk(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    LightLineGeo(D_00629DE4, 2);
    D_004CB8A0[1] = (int)actSt24aConte01_2_Jimaku;
    gobj->unkB4 = D_004CB8A0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CB8C0[];
extern void func_0020AA88(volatile int a0);
void actSt27aEndDemo(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    stage_KillPlayBgAnimation(0x43, 0, -1);
    D_004CB8C0[1] = (int)func_0020AA88;
    gobj->unkB4 = D_004CB8C0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern int D_004CB8E0[];
extern void func_0020AB40(volatile int a0);
void actEndDemo03(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    actSt25aQueenBeforeChk(0xFF, 0xFF, 0xFF, 255.0f);
    LightLineGeo(D_00629DE4, 2);
    D_004CB8E0[1] = (int)func_0020AB40;
    gobj->unkB4 = D_004CB8E0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int actInitialize(int a0);
extern void lt_fade_status(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_0062A894;
extern int D_004CB900[];
extern void func_0020AB70(volatile int a0);
void actEndDemo04(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    stage_KillPlayBgAnimation(0x1D, 0, 0);
    stage_KillPlayBgAnimation(0x19, 0, 0);
    stage_KillPlayBgAnimation(0x20, 0, 0);
    stage_KillPlayBgAnimation(0x21, 0, 0);
    stage_KillPlayBgAnimation(0x23, 0, 0);
    stage_KillPlayBgAnimation(0x25, 0, 0);
    D_004CB900[1] = (int)func_0020AB70;
    gobj->unkB4 = D_004CB900;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CB920[];
extern void func_0020AB98(volatile int a0);
void actEndDemo05(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    stage_KillPlayBgAnimation(0xED, 0, 0);
    stage_KillPlayBgAnimation(0x101, 0, 0);
    D_004CB920[1] = (int)func_0020AB98;
    gobj->unkB4 = D_004CB920;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


extern int D_004CB940[];
extern void actSt00aInit(volatile int a0);
void actEndDemo11(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    stage_KillPlayBgAnimation(0x3B, 0, 0);
    stage_KillPlayBgAnimation(0x40, 0, 0);
    D_004CB940[1] = (int)actSt00aInit;
    gobj->unkB4 = D_004CB940;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}

