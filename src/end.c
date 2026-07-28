#include "common.h"

typedef struct { long long _0; long long _8; } WpData16;

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkC4;
} GObj__p4;

extern int D_00631AE4;
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int actSt25aQueenDeadChk(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B528(int a0);
extern void func_0017C9B0(int a0);
extern void gflagOff(int a0, int a1);
extern int stage_DispBgAnimation(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actEndDemo01(volatile int a0) {
    func_0017C9B0(3);
    func_0017B528(D_00631AE4);
    stage_KillPlayBgAnimation(0x2FC, 1, 0);
    stage_KillPlayBgAnimation(0x2FE, 1, 0);
    stage_KillPlayBgAnimation(0x2FF, 1, 0);
    gflagOff(D_00631AE4, 0x1B8);
    gflagOff(actSt25aQueenDeadChk(0x904), 0x307);
    *(int *)(actSt25aQueenDeadChk(0x904) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x2FC, 0x2FD) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1B9);
    gflagOff(actSt25aQueenDeadChk(0x904), 0x308);
    while (func_0012AA80(0x2FD) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(3, D_00631AE4, D_00631AE8, 1.0f, 8.0f);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0C50[];
extern int D_00631AE4;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern void actSubMpegReturnPreload(volatile int a0);
extern void func_0012ABE0(int a0, int a1);
extern int func_0017B230(int a0);
extern void func_001C2098(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpPlayMotDir(int a0, int a1, int a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actConte14_1(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayMotDir(3, 0, 0x1E3, 0);
    stage_KillPlayBgAnimation(0x98, 0, 0);
    func_0012ABE0(0x1E3, 1);
    stage_KillPlayBgAnimation(0x1E3, 1, 0);
    if (func_0017B230(0x13A) == 0) {
        func_001C2098(D_00631AE4, 2);
        D_004D0C50[1] = (int)actSubMpegReturnPreload;
        gobj->unkC4 = D_004D0C50;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/end", actEndDemo02);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0C70[];
extern int D_00631AE4;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern void actSt26aConte01_1_newgame(volatile int a0);
extern void func_0012ABE0(int a0, int a1);
extern void func_001C2098(int a0, int a1);
extern void lt_fade_status(int a0);
extern void scpPlayMotDir(int a0, int a1, int a2, int a3);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actConte14_2(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    scpPlayMotDir(3, 0, 0x1E3, 0);
    func_0012ABE0(0x1E3, 1);
    stage_KillPlayBgAnimation(0x1E3, 1, 0);
    func_001C2098(D_00631AE4, 2);
    stage_KillPlayBgAnimation(0x308, 0, 0);
    D_004D0C70[1] = (int)actSt26aConte01_1_newgame;
    gobj->unkC4 = D_004D0C70;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

void actEndDemo06(volatile int a0) {
    func_0017C9B0(3);
    func_0017B528(D_00631AE4);
    stage_KillPlayBgAnimation(0x301, 1, 0);
    gflagOff(D_00631AE4, 0x1BB);
    gflagOff(actSt25aQueenDeadChk(0x794), 0x30A);
    *(int *)(actSt25aQueenDeadChk(0x794) + 0x16C) = 1;
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2A, 1, 0);
    stage_KillPlayBgAnimation(0x302, 1, 0);
    while (stage_DispBgAnimation(0x301, 0x303) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1BC);
    gflagOff(actSt25aQueenDeadChk(0x794), 0x30B);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2B, 1, 0);
    while (stage_DispBgAnimation(0x303, 0x304) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1BD);
    gflagOff(actSt25aQueenDeadChk(0x794), 0x30C);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2C, 1, 0);
    while (stage_DispBgAnimation(0x304, 0x305) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1BE);
    gflagOff(actSt25aQueenDeadChk(0x794), 0x30D);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2D, 1, 0);
    while (stage_DispBgAnimation(0x305, 0x306) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1BF);
    gflagOff(actSt25aQueenDeadChk(0x794), 0x30E);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2E, 1, 0);
    while (stage_DispBgAnimation(0x306, 0x307) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1C0);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x2F, 1, 0);
    stage_KillPlayBgAnimation(0x35, 1, 0);
    stage_KillPlayBgAnimation(0x308, 1, 0);
    while (stage_DispBgAnimation(0x307, 0x309) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1C1);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x30, 1, 0);
    stage_KillPlayBgAnimation(0x36, 1, 0);
    while (func_0012AA80(0x309) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(3, D_00631AE4, D_00631AE8, 1.0f, 8.0f);
}

extern int D_00631AE8;
extern void actConte11Jimaku(float f);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int func_0012AA80(int a0);
extern void func_0017B528(int a0);
extern void func_0017B568(int a0);
extern void func_0017C9B0(int a0);
extern void gflagOff(int a0, int a1);
extern int stage_DispBgAnimation(int a0, int a1);

void actConte14_6(volatile int a0) {
    func_0017B528(D_00631AE4);
    actConte11Jimaku(3.0f);
    func_0017C9B0(6);
    stage_KillPlayBgAnimation(0x30C, 1, 0);
    gflagOff(D_00631AE4, 0x1C2);
    while (stage_DispBgAnimation(0x30C, 0x30D) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x32, 1, 0);
    stage_KillPlayBgAnimation(0x192, 1, 0);
    gflagOff(D_00631AE4, 0x1C2);
    while (func_0012AA80(0x30D) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_0017B568(D_00631AE4);
    actSt25aQueenDead(6, D_00631AE4, D_00631AE8, 1.0f, 8.0f);
}

extern int actSt25aQueenDeadEvent(void);
extern int func_0012AB50(int a0, int a1, int a2);
extern void staffRollMain(int a0, float a1);

void actEndDemo07(volatile int a0) {
    func_0017C9B0(1);
    staffRollMain(0xFF, 1.0f);
    stage_KillPlayBgAnimation(0x20B, 1, 0);
    while (stage_DispBgAnimation(0x20B, 0x20C) == 0) { _ACTWait(1); }
    stage_KillPlayBgAnimation(0x19, 1, 0);
    gflagOff(D_00631AE4, 0x11A);
    while (stage_DispBgAnimation(0x20C, 0x20E) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x20E, 0x20F) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x11B);
    _ACTWait(0x82);
    stage_KillPlayBgAnimation(0x1F, 1, 0);
    while (stage_DispBgAnimation(0x20F, 0x210) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x210, 0x211) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x11C);
    while (stage_DispBgAnimation(0x211, 0x212) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x212, 0x213) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x11E);
    while (stage_DispBgAnimation(0x213, 0x214) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x11F);
    while (stage_DispBgAnimation(0x214, 0x215) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x120);
    while (stage_DispBgAnimation(0x215, 0x216) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x121);
    while (stage_DispBgAnimation(0x216, 0x217) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x122);
    while (stage_DispBgAnimation(0x217, 0x218) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x123);
    while (func_0012AB50(0x218, 0x64, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenBeforeChk(0, 0, 0, 8.0f);
    while (actSt25aQueenDeadEvent() != 0) { _ACTWait(1); }
    actSt25aQueenDead(1, D_00631AE4, D_00631AE8, 0.0f, 8.0f);
}

extern void UpdateStormPackage(int a0);
extern void func_00122C48(int a0);

void actConte14_7(volatile int a0) {
    func_0017C9B0(1);
    stage_KillPlayBgAnimation(0x241, 1, 0);
    stage_KillPlayBgAnimation(0xEE, 1, 0);
    gflagOff(D_00631AE4, 0x141);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2B4);
    *(int *)(actSt25aQueenDeadChk(0xA19) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x241, 0x242) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x142);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2B5);
    while (stage_DispBgAnimation(0x242, 0x243) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x143);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2B6);
    while (stage_DispBgAnimation(0x243, 0x244) == 0) { _ACTWait(1); }
    while (stage_DispBgAnimation(0x244, 0x245) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x144);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2B7);
    while (stage_DispBgAnimation(0x245, 0x246) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x145);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2B8);
    while (stage_DispBgAnimation(0x246, 0x247) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x146);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2B9);
    while (stage_DispBgAnimation(0x247, 0x248) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x147);
    while (stage_DispBgAnimation(0x248, 0x257) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x14F);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2BF);
    while (stage_DispBgAnimation(0x257, 0x258) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x150);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2C0);
    while (stage_DispBgAnimation(0x258, 0x259) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x151);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2C1);
    while (stage_DispBgAnimation(0x259, 0x25A) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x152);
    gflagOff(actSt25aQueenDeadChk(0xA19), 0x2C2);
    while (func_0012AB50(0x25A, 0xC8, 0) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00122C48(0);
    UpdateStormPackage(1);
    actSt25aQueenBeforeChk(0, 0, 0, 8.0f);
    while (actSt25aQueenDeadEvent() != 0) { _ACTWait(1); }
    actSt25aQueenDead(1, D_00631AE4, D_00631AE8, 0.0f, 8.0f);
}

INCLUDE_ASM("asm/nonmatchings/src/end", actEndDemo10);

INCLUDE_ASM("asm/nonmatchings/src/end", actConte14_10);

extern void *ContinueCorrectPosition(int a0);
extern WpData16 D_0061B920;
extern void func_0017B288(int a0);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void gflagChk(int a0, void *a1);

void actConte14_13(volatile int a0) {
    WpData16 local10, local20;
    func_0017B528(D_00631AE4);
    actConte11Jimaku(6.0f);
    stage_KillPlayBgAnimation(0x312, 1, 0);
    gflagOff(D_00631AE4, 0x1C7);
    while (stage_DispBgAnimation(0x312, 0x313) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1C8);
    while (stage_DispBgAnimation(0x313, 0x314) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1C9);
    _ACTWait(1);
    stage_KillPlayBgAnimation(0x33, 1, 0);
    while (stage_DispBgAnimation(0x314, 0x315) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1CA);
    while (stage_DispBgAnimation(0x315, 0x316) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1CB);
    while (stage_DispBgAnimation(0x316, 0x317) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1CC);
    gflagOff(actSt25aQueenDeadChk(0x813), 0x310);
    *(int *)(actSt25aQueenDeadChk(0x813) + 0x16C) = 1;
    while (func_0012AA80(0x317) == 0) { _ACTWait(1); }
    _ACTWait(1);
    _ACTWait(0xB4);
    gflagOff(D_00631AE4, 0);
    local10 = D_0061B920;
    func_00243AE8(&local20, &local10, ContinueCorrectPosition(D_00631AE4));
    gflagChk(D_00631AE4, &local20);
    func_0017B568(D_00631AE4);
    D_006325B4 = 0;
    lt_fade_status(0x32);
    func_0017B288(0x133);
}

INCLUDE_ASM("asm/nonmatchings/src/end", actStaff1Demo);

void actStaff2Demo(volatile int a0) {
    stage_KillPlayBgAnimation(0x318, 1, 0);
    gflagOff(D_00631AE4, 0x1CD);
    gflagOff(actSt25aQueenDeadChk(0x813), 0x311);
    *(int *)(actSt25aQueenDeadChk(0x813) + 0x16C) = 1;
    while (stage_DispBgAnimation(0x318, 0x319) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1CE);
    gflagOff(actSt25aQueenDeadChk(0x813), 0x312);
    while (stage_DispBgAnimation(0x319, 0x31A) == 0) { _ACTWait(1); }
    gflagOff(D_00631AE4, 0x1CF);
    gflagOff(actSt25aQueenDeadChk(0x813), 0x313);
    while (func_0012AA80(0x31A) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(1, D_00631AE4, D_00631AE8, 1.0f, 8.0f);
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0BD0[];
extern int D_00631AE4;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actOpDemo01_2(volatile int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);
extern void gflagOff(int a0, int a1);
extern void lt_fade_status(int a0);

void actStaff3Demo(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (D_00631AE4 != 0) { gflagOff(D_00631AE4, 0); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    D_004D0BD0[1] = (int)actOpDemo01_2;
    gobj->unkC4 = D_004D0BD0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D0BF0[];
extern void actOpDemo02(volatile int a0);

void actEndDemo14(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (D_00631AE4 != 0) { gflagOff(D_00631AE4, 0); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actSt25aQueenBeforeChk(0, 0, 0, 255.0f);
    D_004D0BF0[1] = (int)actOpDemo02;
    gobj->unkC4 = D_004D0BF0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/end", actConte14_14);

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0C90[];
extern int D_00631AE4;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void func_001C2098(int a0, int a1);
extern void func_0020D5A8(volatile int a0);
extern void lt_fade_status(int a0);

void actSt27aEndChk(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_001C2098(D_00631AE4, 2);
    D_004D0C90[1] = (int)func_0020D5A8;
    gobj->unkC4 = D_004D0C90;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D0CB0[];
extern void func_0020D660(volatile int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt27aEndDemo(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    stage_KillPlayBgAnimation(0x43, 0, -1);
    D_004D0CB0[1] = (int)func_0020D660;
    gobj->unkC4 = D_004D0CB0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D0CD0[];
extern void actSt00aEneChk(volatile int a0);
extern void actSt25aQueenBeforeChk(int a0, int a1, int a2, float f12);

void actEndDemo03(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actSt25aQueenBeforeChk(0xFF, 0xFF, 0xFF, 255.0f);
    func_001C2098(D_00631AE4, 2);
    D_004D0CD0[1] = (int)actSt00aEneChk;
    gobj->unkC4 = D_004D0CD0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D0CF0[];
extern void func_0020D748(volatile int a0);

void actEndDemo04(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    stage_KillPlayBgAnimation(0x1D, 0, 0);
    stage_KillPlayBgAnimation(0x19, 0, 0);
    stage_KillPlayBgAnimation(0x20, 0, 0);
    stage_KillPlayBgAnimation(0x21, 0, 0);
    stage_KillPlayBgAnimation(0x23, 0, 0);
    stage_KillPlayBgAnimation(0x25, 0, 0);
    D_004D0CF0[1] = (int)func_0020D748;
    gobj->unkC4 = D_004D0CF0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/end", actEndDemo05);

extern int D_004D0D30[];
extern void actBoyRescueReady(void);
extern void actSt00aInit(volatile int a0);

void actEndDemo11(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    lt_fade_status(0x33);
    D_006325B4 = 1;
    actBoyRescueReady();
    stage_KillPlayBgAnimation(0x3B, 0, 0);
    stage_KillPlayBgAnimation(0x40, 0, 0);
    D_004D0D30[1] = (int)actSt00aInit;
    gobj->unkC4 = D_004D0D30;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

