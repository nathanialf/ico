#include "common.h"

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;



extern void func_00122C48(int val);
extern void actConte14_7();
extern void UpdateStormPackage(int x);
extern void actEndDemo01();
extern void actCreateSubThread();
extern void func_0017B288(int bit_idx);
extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0D70[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actStaff1Demo(void);
extern int func_0017B230(int a0);

void actTitleCamera2(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x143) == 0) {
        D_004D0D70[1] = (int)actStaff1Demo;
        gobj->unkB4 = D_004D0D70;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D0D90[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void actSt00aStairChk(void);

void actOpDemo01(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    D_004D0D90[1] = (int)actSt00aStairChk;
    gobj->unkB4 = D_004D0D90;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

extern int D_00633904;
extern void actConte11Jimaku(float f);
extern void actCreateSubThread__p4(void *fn, int a1) __asm__("actCreateSubThread");
extern void actE3GateJimaku();
extern void func_0017B258(int a0);
extern void func_0017C9B0(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actTitleShortCut(volatile int a0) {
    scpPlayStart(0x2A, (int)&D_00633904, 0, 1, 1);
    while (D_00633904 == 0) {
        _ACTWait(1);
    }
    func_0017C9B0(2);
    actConte11Jimaku(6.0f);
    func_0017B258(2);
    func_0017B258(3);
    func_0017B258(4);
    func_0017B258(0x134);
    actCreateSubThread__p4(actE3GateJimaku, 0x15);
}

extern int D_00633908;
extern void actConte11Jimaku(float f);
extern void actCreateSubThread__p4(void *fn, int a1) __asm__("actCreateSubThread");
extern void actE3Warning();
extern void func_0017B258(int a0);
extern void func_0017C9B0(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actTitleReadTimeDemo0(volatile int a0) {
    scpPlayStart(0x2B, (int)&D_00633908, 0, 1, 1);
    while (D_00633908 == 0) {
        _ACTWait(1);
    }
    func_0017C9B0(3);
    actConte11Jimaku(6.0f);
    func_0017B258(0x135);
    actCreateSubThread__p4(actE3Warning, 0x15);
}

extern int D_0063390C;
extern void actOpDemo01_2Chk__p4() __asm__("actOpDemo01_2Chk");

void actOpDemo01_2(volatile int a0) {
    scpPlayStart(0x2C, (int)&D_0063390C, 0, 1, 1);
    while (D_0063390C == 0) {
        _ACTWait(1);
    }
    func_0017C9B0(2);
    actConte11Jimaku(6.0f);
    func_0017B258(0x136);
    actCreateSubThread__p4(actOpDemo01_2Chk__p4, 0x15);
}

extern int D_00631AE4;
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
extern int func_0012AA80(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actOpDemo01_2Chk(volatile int a0) {
    stage_KillPlayBgAnimation(0x2F7, 1, 0);
    while (func_0012AA80(0x2F7) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(2, D_00631AE4, 0, 1.0f, 8.0f);
}

extern int D_00633910;
extern void actSt24aConte01_2__p4() __asm__("actSt24aConte01_2");

void actOpDemo02(volatile int a0) {
    scpPlayStart(0x2D, (int)&D_00633910, 0, 1, 1);
    while (D_00633910 == 0) {
        _ACTWait(1);
    }
    func_0017C9B0(5);
    actConte11Jimaku(6.0f);
    func_0017B258(0x137);
    actCreateSubThread__p4(actSt24aConte01_2__p4, 0x15);
}

extern int D_00631AE8;

void actSt24aConte01_2(volatile int a0) {
    stage_KillPlayBgAnimation(0x2F8, 1, 0);
    while (func_0012AA80(0x2F8) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(5, D_00631AE4, D_00631AE8, 1.0f, 8.0f);
}

extern void actCreateSubThread__p4(void *fn, int a1) __asm__("actCreateSubThread");
extern void actSt13aConte01_3();
extern void func_0017B258(int a0);

void actOpDemo03Chk(volatile int a0) {
    func_0017B258(0x138);
    actCreateSubThread__p4(actSt13aConte01_3, 0x15);
}

extern void func_0017C9B0(int a0);

void actSt13aConte01_3(volatile int a0){
 func_0017C9B0(6); stage_KillPlayBgAnimation(0x2F9,1,0);
 while(func_0012AA80(0x2F9)==0) _ACTWait(1); _ACTWait(1);
 actSt25aQueenDead(6, D_00631AE4, D_00631AE8, 1.0f, 8.0f); }

void actOpDemo03(int a0)
{
    volatile int local = a0;
    func_0017B288(0x134);
    func_0017B288(0x138);
    actCreateSubThread((void *)actEndDemo01, 0x15);
}

extern int D_00633914;
extern void actConte11Jimaku(float f);
extern void actEndDemo02();
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);

void actSubMpegReturnPreload(volatile int a0) {
    scpPlayStart(0x2E, (int)&D_00633914, 0, 1, 1);
    while (D_00633914 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    func_0017B258(0x13A);
    actCreateSubThread__p4(actEndDemo02, 0x15);
}

extern int D_00633918;
extern void actEndDemo06();
extern void actOpDemo02Chk();

void actSt26aConte01_1_newgame(volatile int a0) {
    scpPlayStart(0x2F, (int)&D_00633918, 0, 1, 1);
    while (D_00633918 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    func_0017B258(0x13D);
    actCreateSubThread__p4(actEndDemo06, 0x15);
    actCreateSubThread__p4(actOpDemo02Chk, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/src/op", actOpDemo02Chk);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D5A8);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D5D8);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D660);

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D690);

extern void actConte14_6(void);
extern void actCreateSubThread__p4(void *entry, int a1) __asm__("actCreateSubThread");
extern void func_0017B258(int a0);

void actSt00aEneChk(volatile int a0) {
    func_0017B258(0x140);
    actCreateSubThread__p4(actConte14_6, 0x15);
}

INCLUDE_ASM("asm/nonmatchings/src/op", func_0020D748);

void func_0020D770(int a0)
{
    volatile int local = a0;
    func_00122C48(1);
    UpdateStormPackage(0);
    actCreateSubThread((void *)actConte14_7, 0x15);
}

