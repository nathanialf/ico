#include "common.h"

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkB4;
} ActB4Obj;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D1CF0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt05eEnd(void);
extern int func_0017B230(int a0);

void actSt05bCrest01XL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xB6) == 0) {
        D_004D1CF0[1] = (int)actSt05eEnd;
        gobj->unkB4 = D_004D1CF0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1D30[];
extern void func_0021F588(void);

void actSt05bSekizoChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x9C) == 0) {
        D_004D1D30[1] = (int)func_0021F588;
        gobj->unkB4 = D_004D1D30;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1B50[];
extern int D_004D1B70[];
extern void actSt04lRope2Chk(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05bDoorXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xAB) != 0) {
        stage_KillPlayBgAnimation(0xC8, 0, 0xC8);
        D_004D1B50[1] = (int)actSt04lRope2Chk;
        gobj->unkB4 = D_004D1B50;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xC8, 0, 0);
        D_004D1B70[1] = (int)actSt04lRope2Chk;
        gobj->unkB4 = D_004D1B70;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

extern int D_004D1BD0[];
extern void actSt04lBrg1Chk(void);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt05bMonyoDoorXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC0) == 0) {
        stage_KillPlayBgAnimation(0xCE, 0, 0);
        D_004D1BD0[1] = (int)actSt04lBrg1Chk;
        gobj->unkB4 = D_004D1BD0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xCE, 0, -1);
    }
}

extern int D_004D1BF0[];
extern void actSt04lRope3Chk(void);

void actSt05bSekizo(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC1) == 0) {
        stage_KillPlayBgAnimation(0xCF, 0, 0);
        D_004D1BF0[1] = (int)actSt04lRope3Chk;
        gobj->unkB4 = D_004D1BF0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xCF, 0, -1);
    }
}

extern int D_004D1C10[];
extern void actSt04lRope4Chk(void);

void actSt05bBallXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC2) == 0) {
        stage_KillPlayBgAnimation(0xD0, 0, 0);
        D_004D1C10[1] = (int)actSt04lRope4Chk;
        gobj->unkB4 = D_004D1C10;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD0, 0, -1);
    }
}

extern int D_004D1C30[];
extern void actSt04lBrg2Chk(void);

void actSt05bSolarXL(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC3) == 0) {
        stage_KillPlayBgAnimation(0xD1, 0, 0);
        D_004D1C30[1] = (int)actSt04lBrg2Chk;
        gobj->unkB4 = D_004D1C30;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD1, 0, -1);
    }
}

extern int D_004D1C50[];
extern void actSt04lSekizoChk(void);

void actSt05bSekizoEvent(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC4) == 0) {
        stage_KillPlayBgAnimation(0xD2, 0, 0);
        D_004D1C50[1] = (int)actSt04lSekizoChk;
        gobj->unkB4 = D_004D1C50;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD2, 0, -1);
    }
}

extern int D_004D1C70[];
extern void actSt04lGondolaChk(void);

void actSt05bGirlWay(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xC5) == 0) {
        stage_KillPlayBgAnimation(0xD3, 0, 0);
        D_004D1C70[1] = (int)actSt04lGondolaChk;
        gobj->unkB4 = D_004D1C70;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0xD3, 0, -1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E580);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E618);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E678);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E6D8);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E738);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E7B8);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E830);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E8B8);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E940);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021E9D8);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021EA70);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021EAF8);

INCLUDE_ASM("asm/nonmatchings/src/st05b", func_0021EB80);

