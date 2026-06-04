#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", switchThread);

extern void initAll(void *a0);

void proceedAudio(void **a0) {
    initAll(*a0);
}

void readMpeg(void **a0) {
    proceedAudio(a0);
}

extern int iosMallocCheckLeak2(int a0);

void initAll(void *a0) {
    iosMallocCheckLeak2((int)a0 & 0xFFFFFFF);
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", termAll);

int movie_init(volatile int *a0, int *a1) {
    int diff = a0[1] - a0[3];
    if (diff != 0) {
        a1[0] = a0[0] + a0[2];
    }
    return diff;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", movie_end);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", movie_proc);
