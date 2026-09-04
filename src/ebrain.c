#include "common.h"



extern int D_00633DB8;
extern int D_00633DB4;
extern int D_00633DBC;
extern int D_00632774;
extern int D_00633DB0;
extern int D_00632778;
extern int D_006D0710[];
extern int D_00633DAC;
INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainProcess);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", eBrainGetTargetGeneratorFromLabel);

/* eBrain 0x800 view (local) */
typedef struct { char _0[0x74]; int f_74; char _pad78[0x50]; float f_C8; char f_CC; unsigned char f_CD; } EGeo;

void eBrainGetTarget(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    q->f_CC = 1;
}

void eBrainInit(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    q->f_CC = 0;
}

float eBrainStatusSet(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    return q->f_C8;
}

float eBrainSendMes(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    return (float)(q->f_74 - 1) * 50.0f;
}

void GetStageFromLabel(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    q->f_CD = 1;
}

void eBrainGetTargetGeneratorFromLabelStage(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    q->f_CD = 0;
}

unsigned char func_001906A8(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    EGeo *q = *(EGeo **)((char *)p + 0x800);
    return q->f_CD;
}

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001906B8);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", chain_sub_simulate);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", chain_sub_pendulum);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190A48);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190B30);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190D70);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00190F30);

void func_001918A8(void)
{
    int *p = D_006D0710;
    int i;
    D_00632778 = 0;
    D_00632774 = 0;
    D_00633DAC = 0;
    p = (int *)((char *)p + 0x37C);
    D_00633DB0 = 0;
    i = 0x1F;
    do {
        *p = 0;
        p = (int *)((char *)p - 0x1C);
        i--;
    } while (i >= 0);
}

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001918F0);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_001919A0);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00191AA0);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00191B70);

INCLUDE_ASM("asm/nonmatchings/src/ebrain", func_00191C80);

int func_00191D08(void)
{
    D_00633DB4 = 0;
    D_00633DB8 = -1;
    D_00633DBC = 0;
    return 0;
}

