#include "common.h"

extern int D_00631AE4;
extern void *D_00631AE8;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void scpWakeupEnemyOne(int a0);
extern void scpSleepEnemyOne(int a0);
extern void lt_fade_status(int a0);
extern int scpTriggerBall(int a0, int a1, float f);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt04bEnd(volatile int a0) {
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpTriggerBall(a0, D_00631AE4, 100.0f) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpSleepEnemyOne(0xD7D);
    func_0017B258(0x5D);
    func_0017B258(0x5E);
    stage_KillPlayBgAnimation(0x44, 1, 0);
    while (func_0012AA80(0x44) == 0) { _ACTWait(1); }
    _ACTWait(1);
    lt_fade_status(0x32);
    D_006325B4 = 0;
    scpWakeupEnemyOne(0xD7D);
}

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bSekizoChk);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bEne1Chk);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bCrest01XL);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bDoorXL);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bMonyoDoorXL);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bSekizo);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bEne1);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bEnemy2);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bBallXL);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bSolarXL);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bSekizoEvent);

INCLUDE_ASM("asm/nonmatchings/src/st04b", actSt04bGirlWay);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_002166C0);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_002170C8);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_002171D0);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_00217348);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_00217658);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_00217828);

INCLUDE_ASM("asm/nonmatchings/src/st04b", func_002179F8);

/* .data — carved VMA 0x4D1490..0x4D1510 (4 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004D1490[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D14B0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D14D0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};
unsigned int D_004D14F0[8] = {
    0x0000018D, 0x00000000, 0x00000000, 0x00000000,
    0x0000018C, 0x00000000, 0x00000000, 0x00000000,
};

