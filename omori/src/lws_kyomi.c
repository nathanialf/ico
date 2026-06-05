#include "common.h"

void LwsKyomiGeo(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", CreateKyomiGObj);

void SetParamKyomiGObj(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00236ED0(int a0) {
    int buf[4];
    buf[0] = a0;
}

void func_00236EE0(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00236EF0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00236FE0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_002370D8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237128);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237178);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237268);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237360);

void func_002373B0(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_002373C0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237480);

extern void *actSt25aQueenDeadChk(int a0);

void func_002374F8(int a0) {
    volatile int home = a0;
    *(int *)((char *)actSt25aQueenDeadChk(0x1B4) + 0x16C) = 1;
    *(int *)((char *)actSt25aQueenDeadChk(0x1B5) + 0x16C) = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237530);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_002375A0);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237608);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237670);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_002376D8);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/lws_kyomi", func_00237740);
