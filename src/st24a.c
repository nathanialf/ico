#include "common.h"

extern int actInitialize(int a0);



extern void *D_00631AE8;
extern int func_0017B230(int a0);
extern void func_0017B258(int bit_idx);
extern void backStageProcessMain(void);
extern void _ACTWait();
INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSwordChk);

INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSword);

INCLUDE_ASM("asm/nonmatchings/src/st24a", actSt24aSaku);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_002354B0);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235518);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235580);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235648);

void func_002356C0(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_002356D0);

void func_00235728(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235738);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235818);

void func_002358F8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235908);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_002359C8);


void func_00235A18(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
}

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235A48);

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235AF0);

void func_00235B68(int a0)
{
    volatile int local = a0;
    _ACTWait(1);
    backStageProcessMain();
    func_0017B258(0x20);
}

INCLUDE_ASM("asm/nonmatchings/src/st24a", func_00235B98);

void func_00235C38(void)
{
    if (D_00631AE8 == 0) {
        return;
    }
    if (func_0017B230(0x39) != 0) {
        return;
    }
    return func_0017B258(0x166);
}

