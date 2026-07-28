#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3WarningChk);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Title);

extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actE3TitleChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3TitleFrameChk);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Inst1Chk);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Capsule);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CapsuleDemoCancel);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CapsuleDemo);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St13cInit);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFall);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallChk);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallDemo);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallEffect);

extern int D_00631AE4;
extern int D_006338F4;
extern void scpPlayStart(int a0, int *a1, int a2, int a3, int a4);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actE3St09aSekizo(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_006338F4 = 0;
    _ACTWait(1);
    while (scpSleepSpiderGroupOne(D_00631AE4, 0x2000000) == 0) { _ACTWait(1); }
    scpPlayStart(3, &D_006338F4, 1, 1, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aSekizoChk);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateChk);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateDemo);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateJimaku);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St01bInit);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Warning);

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Inst1);

