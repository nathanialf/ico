#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04cInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04dInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04eInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lC1BallTurn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lC2BallTurn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lC3BallTurn);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lCrest02);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lCrestMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lCrest2Main);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lCrest3Main);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lStairChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lRope1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lRope2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lBrg1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lRope3Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lRope4Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lBrg2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lGondolaChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lMonyou01Chk);

extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern int actItouQueenAttackChk(void);
extern int scpSleepEnemyOne(int a0, int a1, float f);
extern void scpDispOnAllWithKind(void);
extern void lt_fade_status(int a0);
extern void gflagOff(int a0, int a1);
extern void iosOmBeforeFuncStandard(int a0, int a1, int a2);
extern void func_00178DD8(int a0);
extern void scpPlayStart(int a0, void *a1, int a2, int a3, int a4);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int func_0012AA28(int a0, int a1, int a2);
extern void iosPadDevRead(int a0, int a1);
extern int func_0012A958(int a0);
extern void scpActivateAllWithKind(void);
extern int D_00629DE4;
extern int D_00629DE8;
extern int D_00629DEC;
extern int D_0062A894;
extern int D_0062BCF0;

void actSt04lMonyou02Chk(volatile int a0) {
    while (func_00178DB0(0x9C) == 0 || actItouQueenAttackChk() != 4 || scpSleepEnemyOne(a0, D_00629DE4, 1000.0f) == 0) {
        _ACTWait(1);
    }
    scpDispOnAllWithKind();
    lt_fade_status(0x33);
    D_0062A894 = 1;
    gflagOff(D_00629DE4, 0);
    if (D_00629DE8 != 0) {
        iosOmBeforeFuncStandard(D_00629DE8, 0x3A, D_00629DE4);
    }
    func_00178DD8(0xB4);
    _ACTWait(0x3C);
    scpPlayStart(0x3C, &D_0062BCF0, 1, 1, 1);
    while (D_0062BCF0 == 0) {
        _ACTWait(1);
    }
    stage_KillPlayBgAnimation(0xD6, 1, 0);
    stage_KillPlayBgAnimation(0xD8, 1, 0);
    stage_KillPlayBgAnimation(0xD7, 1, 0);
    while (func_0012AA28(0xD6, 0x5A, 0) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    iosPadDevRead(D_00629DEC, 0xF);
    while (func_0012A958(0xD6) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    scpActivateAllWithKind();
    D_0062A894 = 0;
    lt_fade_status(0x32);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04l", actSt04lMonyou03Chk);
