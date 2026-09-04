#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Title);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3TitleChk);
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
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aSekizo);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aSekizoChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateDemo);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3GateJimaku);
void actE3St01bInit(void) {
    stage_SetAnimation(0xB7, 0, -1);
}
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aBrgDown);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Warning);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Inst1);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Door);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CageFallReady);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St13cIntro);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St13cGene1);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St13cGene2);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);

void actE3Floor(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St01bEne);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St01bGene1);
void actE3St01bGene2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16A) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
void actE3St01bGene3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (gflagChk(0x16A) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    _ACTWait(0x3C);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aBrg);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3Gate);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CapsuleChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3CapsuleDemoEnd);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3DoorMain);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3DoorUp);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St13cIntroChk);
extern int D_00639EA4;
extern int D_0063BDFC;
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void scpAdpcmPlayRequestFunc(int a0, int *a1, int a2, int a3, int a4);
extern int scpTriggerFloorAttr(int a0, int a1);

void actE3CageFallReadyChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    D_0063BDFC = 0;
    _ACTWait(1);
    while (scpTriggerFloorAttr(D_00639EA4, 0x2000000) == 0) { _ACTWait(1); }
    scpAdpcmPlayRequestFunc(3, &D_0063BDFC, 1, 1, 0);
}
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St01bEneChk);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aGirlWay);
INCLUDE_ASM("asm/nonmatchings/src/e3", actE3St09aBrgMain);
