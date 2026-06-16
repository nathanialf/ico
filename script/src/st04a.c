#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGate);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aConte06);

extern void _ACTWait(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void func_0017C1B0(void);

void actSt04aConte06Jimaku(volatile int a0) {
    while (actSt25aQueenDeadChk(0x659) == 0) {
        _ACTWait(1);
    }
    _ACTWait(0x3C);
    func_0017C1B0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpenChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actConte09);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actConte09Jimaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpen2Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actConte09_2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpen3Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actConte09_3);

extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);

void actSt04aGateLChk(void) {
    if (!func_00178DB0(0x52)) {
        AddWayPointTop(7, 0);
    }
    if (func_00178DB0(0x53)) {
        AddWayPointTop(5, 1);
    } else {
        AddWayPointTop(5, 0);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateRChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aTorch1);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aTorch1Chk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aTorchAllFlagfChk);

extern int actInitialize(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void Generator_Call(int a0);
void actSt04aGateL(volatile int a0){ int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0); Generator_Mask(actSt25aQueenDeadChk(0x331));
 while(func_00178DB0(0x5E)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x14); Generator_Call(a0); Generator_Call(actSt25aQueenDeadChk(0x331)); }

void actSt04aGateR(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aTorchXL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st04a", actSt04aGateOpen2);

void actSt04aGateOpen3(int a0) {
    int buf[4];
    buf[0] = a0;
}
