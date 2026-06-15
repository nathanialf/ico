#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchLChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchLUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchR);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void *actSt25aQueenDeadChk(int a0);

void actSt03tSwitchRChk(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (func_00178DB0(0x63) == 0) {
        ((int *)actSt25aQueenDeadChk(0x62A))[0x16C / 4] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSwitchRUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tBoxA);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tBoxB);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_006297E8;
extern float D_006297EC;

void actSt03tInit(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x6E, 0x57, 0, 0x12, 900.0f, D_006297E8, D_006297EC, 800.0f, D_006297E8, D_006297EC);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGirlCam);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSekizo);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tWay);

void actSt03tEne(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGene);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGirlCamEvent);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGirlCamStartChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tGirlCamEndChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tSekizoEvent);

extern int D_00629DE8;
extern void _ACTWait(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void func_00178DD8(int a0);
void actSt03tEneChk(volatile int a0) {
    if (D_00629DE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00629DE8, 0x3000000) == 0) { _ACTWait(1); }
    _ACTWait(1);
    func_00178DD8(0x6C);
    func_00178DD8(0x6D);
}

void actSt03tWayOnChk(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st03t", actSt03tWayOffChk);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_00614610;

/* end struct shapes */
