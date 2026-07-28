#include "common.h"


extern void backStageProcessMain(void);
extern void _ACTWait();
extern void func_0017B258(int bit_idx);
INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022ED40);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022ED98);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EE68);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EE98);

void func_0022EEF0(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EF00);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EF78);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F130);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F218);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F360);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F560);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F600);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F698);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F710);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F7B8);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F7E8);

void func_0022F850(int a0)
{
    volatile int local = a0;
    _ACTWait(1);
    backStageProcessMain();
    func_0017B258(0x12A);
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F880);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F930);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F9E0);

