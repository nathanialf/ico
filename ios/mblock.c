#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ios/mblock", new_mblock_node);
extern int D_0063A470;
extern void iosFree();

void reuse_mblock1(int *a0)
{
    if ((unsigned int)a0[1] < 0x2001) {
        int tmp = D_0063A470;
        D_0063A470 = (int)a0;
        a0[3] = tmp;
        return;
    }
    return iosFree(*a0);
}
void init_mblock(int *a0) {
    a0[0] = 0;
    a0[1] = 0;
}
INCLUDE_ASM("asm/nonmatchings/ios/mblock", new_segment);
void reuse_mblock(int *a0) {
    int *node = (int *)a0[0];
    if (node != 0) {
        do {
            int *next = (int *)node[3];
            reuse_mblock1(node);
            node = next;
        } while (node != 0);
        a0[0] = 0;
        a0[1] = 0;
    }
}
INCLUDE_ASM("asm/nonmatchings/ios/mblock", strdup_mblock);
