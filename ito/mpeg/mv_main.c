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

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", movie_init);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", movie_end);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", movie_proc);
