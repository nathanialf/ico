#include "common.h"



extern int D_0061C0D0[];
extern void debug_assertMessage();
extern void func_0017B258(int bit_idx);
extern void AddWayPointTop();
extern int func_0017B230(int a0);
INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aOriDown);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aHaguruma);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aHagurumaChk);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aPipeChk);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChainDown);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChainUp);

void actSt19aOri(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aOriXL);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231690);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChain);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231818);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_002318D0);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231958);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChainMain);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChainSwitch);

void actSt19bIntroChk(void)
{
    if (func_0017B230(0x14) != 0) {
        AddWayPointTop(9, 0);
    }
}

void func_00231AF8(void)
{
    if (func_0017B230(0x1D) != 0) {
        return;
    }
    debug_assertMessage(D_0061C0D0);
    func_0017B258(0x165);
}

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231B38);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231C58);

