#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", new_mblock_node);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", reuse_mblock1);

extern void *D_0062A348;
extern int iosMallocCheckLeak2(int a0);

void init_mblock(int *a0) {
    if ((unsigned int)a0[1] < 0x2001) {
        void *old = D_0062A348;
        D_0062A348 = a0;
        *(void **)(a0 + 3) = old;
    } else {
        iosMallocCheckLeak2(a0[0]);
    }
}

void new_segment(int *a0) {
    a0[0] = 0;
    a0[1] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", reuse_mblock);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", func_00135EA0);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/ios/mblock", func_00135F88);
