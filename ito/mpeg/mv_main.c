#include "common.h"

extern void debug_assertMessage(char *fmt, int n);
extern int OtherStagePositionGet(void *a, void *b, void *c, void *d);
extern int func_0019AE20(void);
extern int D_0062AADC;
extern char D_0062C960[];
extern char D_006D5ED0[];
extern char D_006D5EC0[];
extern char D_006CDD00[];

int switchThread(void *a0) {
    int rv;
    debug_assertMessage(D_0062C960, D_0062AADC++);
    rv = OtherStagePositionGet(D_006D5ED0, D_006D5EC0, D_006CDD00, a0);
    func_0019AE20();
    return rv;
}

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

int movie_proc(int *a0, int *a1) {
    int cum = a0[3];
    if (cum != 0) {
        a1[0] = a0[0] + ((a0[2] - cum + a0[1]) % a0[1]);
    }
    return cum;
}
