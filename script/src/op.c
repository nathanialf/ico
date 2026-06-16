#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actTitleCamera2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo01);

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern void actConte11Jimaku(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actE3GateJimaku();
extern int D_0062BC0C;
void actTitleShortCut(volatile int a0) {
    scpPlayStart(0x2A, (int)&D_0062BC0C, 0, 1, 1);
    while (D_0062BC0C == 0) {
        _ACTWait(1);
    }
    func_0017A0F8(2);
    actConte11Jimaku(6.0f);
    func_00178DD8(2);
    func_00178DD8(3);
    func_00178DD8(4);
    func_00178DD8(0x133);
    actCreateSubThread(actE3GateJimaku, 0x15);
}

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern void actConte11Jimaku(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actE3Warning();
extern int D_0062BC10;
void actTitleReadTimeDemo0(volatile int a0) {
    scpPlayStart(0x2B, (int)&D_0062BC10, 0, 1, 1);
    while (D_0062BC10 == 0) {
        _ACTWait(1);
    }
    func_0017A0F8(3);
    actConte11Jimaku(6.0f);
    func_00178DD8(0x134);
    actCreateSubThread(actE3Warning, 0x15);
}

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern void actConte11Jimaku(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actOpDemo01_2Chk();
extern int D_0062BC14;
void actOpDemo01_2(volatile int a0) {
    scpPlayStart(0x2C, (int)&D_0062BC14, 0, 1, 1);
    while (D_0062BC14 == 0) {
        _ACTWait(1);
    }
    func_0017A0F8(2);
    actConte11Jimaku(6.0f);
    func_00178DD8(0x135);
    actCreateSubThread(actOpDemo01_2Chk, 0x15);
}

extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern int D_00629DE4;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
void actOpDemo01_2Chk(volatile int a0) {
    stage_KillPlayBgAnimation(0x2F6, 1, 0);
    while (func_0012A958(0x2F6) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(2, D_00629DE4, 0, 1.0f, 8.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo02);

extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern int D_00629DE4;
extern int D_00629DE8;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f12, float f13);
void actSt24aConte01_2(volatile int a0) {
    stage_KillPlayBgAnimation(0x2F7, 1, 0);
    while (func_0012A958(0x2F7) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(5, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
}

extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *entry, int a1);
extern void actSt13aConte01_3();

void actOpDemo03Chk(volatile int a0) {
    func_00178DD8(0x137);
    actCreateSubThread(actSt13aConte01_3, 0x15);
}

void actSt13aConte01_3(volatile int a0){
 func_0017A0F8(6); stage_KillPlayBgAnimation(0x2F8,1,0);
 while(func_0012A958(0x2F8)==0) _ACTWait(1); _ACTWait(1);
 actSt25aQueenDead(6, D_00629DE4, D_00629DE8, 1.0f, 8.0f); }

extern void func_00178E08(int a0);
extern void actEndDemo01(void);

void actOpDemo03(volatile int a0) {
    func_00178E08(0x133);
    func_00178E08(0x137);
    actCreateSubThread(actEndDemo01, 0x15);
}

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void actConte11Jimaku(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actEndDemo02();
extern int D_0062BC1C;
void actSubMpegReturnPreload(volatile int a0) {
    scpPlayStart(0x2E, (int)&D_0062BC1C, 0, 1, 1);
    while (D_0062BC1C == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    func_00178DD8(0x139);
    actCreateSubThread(actEndDemo02, 0x15);
}

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void actConte11Jimaku(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actEndDemo06();
extern void actOpDemo02Chk();
extern int D_0062BC20;
void actSt26aConte01_1_newgame(volatile int a0) {
    scpPlayStart(0x2F, (int)&D_0062BC20, 0, 1, 1);
    while (D_0062BC20 == 0) {
        _ACTWait(1);
    }
    actConte11Jimaku(6.0f);
    func_00178DD8(0x13C);
    actCreateSubThread(actEndDemo06, 0x15);
    actCreateSubThread(actOpDemo02Chk, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actOpDemo02Chk);

extern void func_0020AA00();

void actSt24aConte01_2_Jimaku(volatile int a0) {
    func_00178DD8(0x13D);
    actCreateSubThread(func_0020AA00, 0x15);
}

extern void func_0017A0F8(int a0);
extern void func_001790A8(int a0);
void func_0020AA00(volatile int a0){
 func_0017A0F8(2); func_001790A8(D_00629DE4); stage_KillPlayBgAnimation(0x309,1,0);
 while(func_0012A958(0x309)==0) _ACTWait(1); _ACTWait(1);
 actSt25aQueenDead(2, D_00629DE4, D_00629DE8, 1.0f, 8.0f); }

extern void func_0020AAB8(volatile int a0);

void func_0020AA88(volatile int a0) {
    func_00178DD8(0x13E);
    actCreateSubThread(func_0020AAB8, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", func_0020AAB8);

extern void actConte14_6(void);

void func_0020AB40(volatile int a0) {
    func_00178DD8(0x13F);
    actCreateSubThread(actConte14_6, 0x15);
}

extern void actCreateSubThread(void *entry, int a1);
extern void actEndDemo07(void);

void func_0020AB70(volatile int a0) {
    actCreateSubThread(actEndDemo07, 0x15);
}

extern void shadow_Tool(int a0);
extern void UpdateStormPackage(int a0);
extern void actConte14_7(void);

void func_0020AB98(volatile int a0) {
    shadow_Tool(1);
    UpdateStormPackage(0);
    actCreateSubThread(actConte14_7, 0x15);
}
