#include "common.h"


extern int D_00632048;
extern void iosMallocCheckLeak2();
INCLUDE_ASM("asm/nonmatchings/ios/mblock", new_mblock_node);

INCLUDE_ASM("asm/nonmatchings/ios/mblock", reuse_mblock1);

void init_mblock(int *a0)
{
    if ((unsigned int)a0[1] < 0x2001) {
        int tmp = D_00632048;
        D_00632048 = (int)a0;
        a0[3] = tmp;
        return;
    }
    return iosMallocCheckLeak2(*a0);
}

INCLUDE_ASM("asm/nonmatchings/ios/mblock", new_segment);

INCLUDE_ASM("asm/nonmatchings/ios/mblock", reuse_mblock);

INCLUDE_ASM("asm/nonmatchings/ios/mblock", strdup_mblock);

INCLUDE_ASM("asm/nonmatchings/ios/mblock", func_00136198);

INCLUDE_ASM("asm/nonmatchings/ios/mblock", func_00136280);

