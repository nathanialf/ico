#include "common.h"


extern void iosMallocCheckLeak2();
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", switchThread);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", proceedAudio);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", readMpeg);

void initAll(int a0)
{
    iosMallocCheckLeak2(a0 & 0x0FFFFFFF);
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", termAll);

int movie_init(int *a0, int *a1)
{
    int new_var;
    int diff = a0[1] - a0[3];
    if (diff != 0) {
        new_var = a0[2];
        a1[0] = a0[0] + new_var;
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

int movie_proc(int *a0, int *out)
{
    int a2 = a0[3];
    if (a2 != 0) {
        int v1 = a0[2] - a2;
        int divisor = a0[1];
        v1 = v1 + divisor;
        *out = a0[0] + (v1 % divisor);
    }
    return a2;
}

