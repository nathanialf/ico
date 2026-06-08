#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSwordChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSword);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231C58);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231CC0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231D28);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231DF0);

void func_00231E68(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231E78);

void func_00231ED0(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231EE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231FC0);

void func_002320A0(int a0) {
    int buf[4];
    buf[0] = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_002320B0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00232170);

extern void actInitialize(int a0);
extern void _ACTWait(int a0);

void func_002321C0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_002321F0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00232298);

extern void backStageProcessMain(void);
extern void func_00178DD8(int a0);

void func_00232310(volatile int a0) {
    _ACTWait(1);
    backStageProcessMain();
    func_00178DD8(0x20);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00232340);

extern int D_00629DE8;
extern int func_00178DB0(int a0);

void func_002323E0(void) {
    if (D_00629DE8 != 0) {
        if (func_00178DB0(0x39) == 0) {
            func_00178DD8(0x165);
        }
    }
}
