#include "common.h"

extern int D_00631AE8;
extern int D_006325B4;
extern void _ACTWait(int a0);
extern void actConte11(int a0);
extern int func_0012AA80(int a0);
extern void func_0017B258(int a0);
extern void func_0017B288(int a0);
extern void func_0017C8C0(int a0);
extern void func_0017C8F8(int a0);
extern void func_0017C990(int a0);
extern void lt_fade_status(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

extern int D_00632110;
void actSt13b2Generator(volatile int a0) {
    int save;
    if (D_00631AE8 == 0) { _ACTWait(0); }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x5000000) == 0) { _ACTWait(1); }
    lt_fade_status(0x33);
    D_006325B4 = 1;
    func_0017C8F8(0xD7D);
    func_0017B288(0x166);
    func_0017B258(0x45);
    func_0017B258(0x47);
    _ACTWait(0x3C);
    save = D_00632110;
    D_00632110 = 0;
    actConte11(0x130);
    actConte11(0x131);
    actConte11(0x132);
    func_0017C990(0x133);
    stage_KillPlayBgAnimation(0x5A, 1, 0);
    while (func_0012AA80(0x5A) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_00632110 = save;
    lt_fade_status(0x32);
    D_006325B4 = 0;
    func_0017C8C0(0xD7D);
}

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A2C8);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A398);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A440);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A4B8);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A530);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A5D8);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A680);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A720);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A7C0);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A838);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A8B0);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A940);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022A9E8);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022AD90);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022AEA8);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022AFA8);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022B0B0);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022B228);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022B3A0);

INCLUDE_ASM("asm/nonmatchings/src/st13b2", func_0022B408);

