#include "common.h"

typedef struct GObj {
    char pad[0xB4];
    int *unkB4;
} GObj;

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern int func_00178DB0(int a0);

extern int D_004CB980[];
extern void actStaff1Demo(void);

void actTitleCamera2(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x142) == 0) {
        D_004CB980[1] = (int)actStaff1Demo;
        gobj->unkB4 = D_004CB980;
        BoxBarSoundOn(a0, 0x189);
        _ACTWait(0);
    }
}


extern int D_004CB9A0[];
extern void actSt00aStairChk(void);

void actOpDemo01(volatile int a0) {
    int x = a0;
    GObj *gobj = (GObj *)actInitialize(a0);
    _ACTWait(1);
    D_004CB9A0[1] = (int)actSt00aStairChk;
    gobj->unkB4 = D_004CB9A0;
    BoxBarSoundOn(a0, 0x189);
    _ACTWait(0);
}


#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern void scpFadeIn(float f);
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
    scpFadeIn(6.0f);
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
extern void scpFadeIn(float f);
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
    scpFadeIn(6.0f);
    func_00178DD8(0x134);
    actCreateSubThread(actE3Warning, 0x15);
}

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern void scpFadeIn(float f);
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
    scpFadeIn(6.0f);
    func_00178DD8(0x135);
    actCreateSubThread(actOpDemo01_2Chk, 0x15);
}

extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern int D_00629DE4;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void RequestStageChange(int a0, int a1, int a2, float f12, float f13);
void actOpDemo01_2Chk(volatile int a0) {
    stage_KillPlayBgAnimation(0x2F6, 1, 0);
    while (func_0012A958(0x2F6) == 0) { _ACTWait(1); }
    _ACTWait(1);
    RequestStageChange(2, D_00629DE4, 0, 1.0f, 8.0f);
}

extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void func_0017A0F8(int a0);
extern void scpFadeIn(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt24aConte01_2();
extern int D_0062BC18;

void actOpDemo02(volatile int a0) {
    scpPlayStart(0x2D, (int)&D_0062BC18, 0, 1, 1);
    while (D_0062BC18 == 0) {
        _ACTWait(1);
    }
    func_0017A0F8(5);
    scpFadeIn(6.0f);
    func_00178DD8(0x136);
    actCreateSubThread(actSt24aConte01_2, 0x15);
}


extern void _ACTWait(int a0);
extern int func_0012A958(int a0);
extern int D_00629DE4;
extern int D_00629DE8;
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void RequestStageChange(int a0, int a1, int a2, float f12, float f13);
void actSt24aConte01_2(volatile int a0) {
    stage_KillPlayBgAnimation(0x2F7, 1, 0);
    while (func_0012A958(0x2F7) == 0) { _ACTWait(1); }
    _ACTWait(1);
    RequestStageChange(5, D_00629DE4, D_00629DE8, 1.0f, 8.0f);
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
 RequestStageChange(6, D_00629DE4, D_00629DE8, 1.0f, 8.0f); }

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
extern void scpFadeIn(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actEndDemo02();
extern int D_0062BC1C;
void actSubMpegReturnPreload(volatile int a0) {
    scpPlayStart(0x2E, (int)&D_0062BC1C, 0, 1, 1);
    while (D_0062BC1C == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
    func_00178DD8(0x139);
    actCreateSubThread(actEndDemo02, 0x15);
}

#include "common.h"
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void _ACTWait(int a0);
extern void scpFadeIn(float f);
extern void func_00178DD8(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actEndDemo06();
extern void actConte14_10_Jimaku();
extern int D_0062BC20;
void actSt26aConte01_1_newgame(volatile int a0) {
    scpPlayStart(0x2F, (int)&D_0062BC20, 0, 1, 1);
    while (D_0062BC20 == 0) {
        _ACTWait(1);
    }
    scpFadeIn(6.0f);
    func_00178DD8(0x13C);
    actCreateSubThread(actEndDemo06, 0x15);
    actCreateSubThread(actConte14_10_Jimaku, 0x15);
}

/* actConte14_10_Jimaku: C is FULLY RECOVERED and verified byte-identical when assembled
 * with the 2.96/modern assembler. It does NOT byte-match under the default period
 * assembler (ee-as 2.9-991111): gcc emits `.p2align 3` for the loop top, which 2.9
 * over-pads by one slot (2 nops where ROM has 1, shifting everything after). A C
 * source shape that avoids the over-pad is still TBD; an inline-asm nop is not
 * usable (any asm statement reshuffles gcc's prologue schedule away from ROM).
 * Kept as INCLUDE_ASM until the proper shape lands. Recovered C:
 *
 *   typedef struct { char pad0[0x38]; int unk38; char pad1[8]; int unk44; } OpObj;
 *   extern void func_00174698(OpObj *p);
 *   extern void _FUNC_GetWay_begin(OpObj *p);   // takes the base (a0=&D_00286840)
 *   extern int D_00271240[]; extern OpObj D_00286840; extern int D_0062A7F8;
 *
 *   void actConte14_10_Jimaku(volatile int a0) {
 *       float t = 0.0f;
 *       do {
 *           switch ((int)t) {
 *           case 1:    func_00174698(&D_00286840); break;
 *           case 1500: D_00286840.unk38 = 112; D_00286840.unk44 = -1;
 *                      D_0062A7F8 = 1; _FUNC_GetWay_begin(&D_00286840); break;
 *           }
 *           {
 *               int it = (int)t;
 *               int q  = (60 - D_00271240[0] * 10) / D_00271240[1];
 *               float nt = t + (float)q / 60.0f;
 *               if (it != (int)nt) { _ACTWait(1); t = nt; }
 *               else               { t = nt + 1.0f; }
 *           }
 *       } while (t < 1800.0f);
 *   }
 */
INCLUDE_ASM("asm/aug6/nonmatchings/script/src/op", actConte14_10_Jimaku);


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
 RequestStageChange(2, D_00629DE4, D_00629DE8, 1.0f, 8.0f); }

extern void func_0020AAB8(volatile int a0);

void func_0020AA88(volatile int a0) {
    func_00178DD8(0x13E);
    actCreateSubThread(func_0020AAB8, 0x15);
}

extern void _ACTWait(int a0);
extern void func_0017A0F8(int a0);
extern int func_0012A958(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern void actItouQueenAttack(int a0, int a1, int a2, int a3, float a6, float a7, int a4, int a5);
extern int D_00629DE4;
extern int D_00629DE8;

void func_0020AAB8(volatile int a0) {
    stage_KillPlayBgAnimation(0x30A, 1, 0);
    func_0017A0F8(4);
    while (func_0012A958(0x30A) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    actItouQueenAttack(4, D_00629DE4, D_00629DE8, 0xFF, 16.0f, 16.0f, 0xFF, 0xFF);
}


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
extern void SetStaticBlur(int a0);
extern void actConte14_7(void);

void actStaff2Chk(volatile int a0) {
    shadow_Tool(1);
    SetStaticBlur(0);
    actCreateSubThread(actConte14_7, 0x15);
}
