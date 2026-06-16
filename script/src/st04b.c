#include "common.h"

#include "common.h"
extern void _ACTWait(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void lt_fade_status(int a0);
extern void func_0017A040(int a0);
extern void func_00178DD8(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void func_0017A008(int a0);
extern void *D_00629DE8;
extern int D_00629DE4;
extern int D_0062A894;
void actSt04bEnd(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepEnemyOne(a0, D_00629DE4, 100.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_0017A040(0xD57);
    func_00178DD8(0x5D);
    func_00178DD8(0x5E);
    stage_KillPlayBgAnimation(0x44, 1, 0);
    while (func_0012A958(0x44) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_0062A894 = 0;
    func_0017A008(0xD57);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEne1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bCrest01XL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bDoorXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bMonyoDoorXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEne1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEnemy1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bEnemy2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bBallXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSolarXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", actSt04bSekizoEvent);

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void func_00178DD8(int a0);
extern void lt_fade_status(int a0);
extern void func_001790A8(void *a0);
extern void scpTrans(void *a0, int a1);
extern void AdpcmClose(int a0);
extern void actCreateSubThread(void *fn, int a1);
extern void actSt04cWaterXL(volatile int a0);
extern void func_00213960(volatile int a0);
extern void actSt04cDoorDownEvent(volatile int a0);
extern void *D_00629DE8;
extern int D_00629DE4;
extern int D_0062A894;
extern void *D_0062BC8C;
extern char *D_0062BC90;

void actSt04bGirlWay(volatile int a0) {
    if (D_00629DE8 == 0) {
        _ACTWait(0);
    }
    while (func_00178DB0(0x7F) == 0 || scpSleepEnemyOne(a0, D_00629DE4, 450.0f) == 0) {
        _ACTWait(1);
    }
    func_00178DD8(0x80);
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_001790A8((void *)D_00629DE4);
    func_001790A8(D_00629DE8);
    if (D_0062BC8C != 0) {
        scpTrans(D_0062BC8C, 0x50);
    }
    while (D_0062BC90 == 0) {
        _ACTWait(1);
    }
    AdpcmClose(*(int *)(D_0062BC90 + 0x2C));
    actCreateSubThread(actSt04cWaterXL, 0x15);
    actCreateSubThread(func_00213960, 0x15);
    actCreateSubThread(actSt04cDoorDownEvent, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00213960);

#include "common.h"
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void lt_fade_status(int a0);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, int a1, int a2, int a3, int a4);
extern void actConte11Jimaku(float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012A958(int a0);
extern void actSt25aQueenDead(int a0, int a1, int a2, float f0, float f1);
extern int D_0062BC94;
extern int D_00629DE4;
extern void *D_00629DE8;
extern int D_0062A894;
void func_00214368(volatile int a0) {
    while (func_00178DB0(0x9B) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_0062A894 = 1;
    func_00178DD8(0x7C);
    scpPlayStart(0x1C, (int)&D_0062BC94, 1, 1, 1);
    while (D_0062BC94 == 0) { _ACTWait(1); }
    actConte11Jimaku(6.0f);
    stage_KillPlayBgAnimation(0x103, 1, 0);
    while (func_0012A958(0x103) == 0) { _ACTWait(1); }
    _ACTWait(1);
    actSt25aQueenDead(4, D_00629DE4, (int)D_00629DE8, 1.0f, 8.0f);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00214468);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00214640);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00214950);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00214B20);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04b", func_00214CF0);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00614810;  /* stride 0x4 */

/* end struct shapes */
