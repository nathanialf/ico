#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSwordChk);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSword);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", actSt24aSaku);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/st24a", func_00231C58);

extern void func_00179710(int, int, int, int, int, float, float, float, float, float, float);
extern float D_006299BC;
extern float D_006299C0;
extern float D_006299C4;

void func_00231CC0(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    func_00179710(a0, 0x1E, 0x45, 0x6D, 0x12, D_006299BC, D_006299C0, 1000.0f, D_006299BC, D_006299C0, D_006299C4);
}

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

extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);
extern int D_00629DE8;
extern long long D_00614E10[];

void func_00232170(volatile unsigned int a0) {
    volatile int local;
    long long buf[2];
    buf[0] = D_00614E10[0];
    buf[1] = D_00614E10[1];
    actSt25aQueenTalkChk(D_00629DE8, 0, (int *)buf, 2, 100.0f);
}

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
