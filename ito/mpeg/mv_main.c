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

void movie_end(int *a0, int a1)
{
  int size;
  int pos;
  int cum;
  int remaining;
  int step;
  size = a0[1];
  cum = a0[3];
  pos = a0[2];
  remaining = size - cum;
  step = (a1 < remaining) ? (a1) : (remaining);
  pos += step;
  cum = cum + step;
  a0[2] = pos % size;
  a0[3] = cum;
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/mpeg/mv_main", movie_proc);
