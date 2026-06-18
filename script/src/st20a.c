#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEnd);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaDown);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaUp);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFence);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceDownChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceUpChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceDownChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aFenceUpChk2);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridge);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondola);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aExit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aElv);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aEne);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void Generator_Mask(int a0);
extern int func_00178DB0(int a0);
extern int actSt25aQueenDeadChk(int a0);
extern void Generator_Call(int a0);
extern void scpDispOnAllWithKind(void);
extern void func_00178E08(int a0);
extern int D_0062C2C8;

void actSt20aEnemy1(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    D_0062C2C8 = a0;
    Generator_Mask(a0);
    while (func_00178DB0(0x16) == 0) {
        _ACTWait(1);
    }
    Generator_Call(actSt25aQueenDeadChk(0x86));
    _ACTWait(0xB4);
    Generator_Call(a0);
    scpDispOnAllWithKind();
    func_00178E08(0x16);
}


extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);

void actSt20aEnemy2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_00178DB0(0x18) == 0) {
        _ACTWait(1);
    }
    Generator_MaskOff(a0);
}

#include "common.h"
extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int a0, int a1, int a2, int a3, int a4, float f0, float f1, float f2, float f3, float f4, float f5);
extern int func_00178DB0(int a0);
extern void AddWayPointTop(int a0, int a1);
void actSt20aEnemy3(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x1D, 0x40, 0, 0x11, -300.0f, -100.0f, 100.0f, -300.0f, -100.0f, 0.0f);
    if (func_00178DB0(0x1D) == 0) {
        AddWayPointTop(2, 0);
    } else {
        AddWayPointTop(2, 1);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aBridgeSwitch);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaMain);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st20a", actSt20aGondolaSwitch);
