#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cDoorDownChk);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoorChk);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt04rDoor2Chk);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cSolarXL);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cWaterXL);

extern void Generator_Call(int a0);
extern void Generator_Mask(int a0);
extern void Generator_MaskOff(int a0);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern int func_0017B230(int a0);

void actSt04rDoor(volatile int a0){
 int x=a0;
 actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
 while(func_0017B230(0xC8)==0){ _ACTWait(1); }
 Generator_MaskOff(a0); Generator_Call(a0); _ACTWait(0x3C); Generator_Call(a0);
}

void actSt04rDoor2(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    Generator_Mask(a0);
    while (func_0017B230(0xC8) == 0) {
        _ACTWait(1);
    }
    Generator_Call(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cDoorDown);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEne);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEnemy1);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cEnemy2);

INCLUDE_ASM("asm/nonmatchings/src/st05c", actSt05cDoorDownEvent);

void actSt05cDoorDownEffect(int x) {
    volatile int local = x;
}

void actSt05cEneChk(int x) {
    volatile int local = x;
}

void func_0021F2C8(int x) {
    volatile int local = x;
}

void func_0021F2D8(int x) {
    volatile int local = x;
}

void func_0021F2E8(int x) {
    volatile int local = x;
}

void func_0021F2F8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st05c", func_0021F308);

INCLUDE_ASM("asm/nonmatchings/src/st05c", func_0021F350);

void func_0021F3A8(int x) {
    volatile int local = x;
}

