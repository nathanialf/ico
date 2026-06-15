#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", actSt13dExit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", actSt13dExitR);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", actSt13dExitL);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", actSt13dInit);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_002292F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229398);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229400);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_00629938;

void func_002294B0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x106, 0x15B, 0, 0x12, 0.0f, -72.0f, D_00629938, 76.0f, -72.0f, D_00629938);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229518);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229580(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10B) == 0) { _ACTWait(1); }
    _ACTWait(0x74);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229600(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10B) == 0) { _ACTWait(1); }
    _ACTWait(0x64);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229680(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10C) == 0) { _ACTWait(1); }
    _ACTWait(0x74);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229700(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10C) == 0) { _ACTWait(1); }
    _ACTWait(0x64);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229780(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10C) == 0) { _ACTWait(1); }
    _ACTWait(0x82);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229800(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10D) == 0) { _ACTWait(1); }
    _ACTWait(0x1);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern int func_00178DB0(int a0);
extern void Generator_Mask(int a0);
extern void Generator_Call(int a0);
extern void Generator_MaskOff(int a0);
void func_00229880(volatile int a0) {
    int x = a0;
    actInitialize(a0); _ACTWait(1); Generator_Mask(a0);
    while (func_00178DB0(0x10D) == 0) { _ACTWait(1); }
    _ACTWait(0x140);
    Generator_Call(a0);
    Generator_MaskOff(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229900);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229978);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_002299F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229A68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st13d", func_00229AF0);
