#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3WarningChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Title);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void actE3TitleChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3TitleFrameChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Inst1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Capsule);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CapsuleDemoCancel);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CapsuleDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St13cInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFall);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3CageFallEffect);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St09aSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St09aSekizoChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateDemo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3GateJimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3St01bInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Warning);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/e3", actE3Inst1);
