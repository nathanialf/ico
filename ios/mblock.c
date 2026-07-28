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

void new_segment(int *a0) {
    a0[0] = 0;
    a0[1] = 0;
}

INCLUDE_ASM("asm/nonmatchings/ios/mblock", reuse_mblock);

void strdup_mblock(int *a0) {
    int *node = (int *)a0[0];
    if (node != 0) {
        do {
            int *next = (int *)node[3];
            init_mblock(node);
            node = next;
        } while (node != 0);
        a0[0] = 0;
        a0[1] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/ios/mblock", func_00136198);

INCLUDE_ASM("asm/nonmatchings/ios/mblock", func_00136280);

