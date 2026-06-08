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

extern int deq_mes_th(int a0, int a1, int a2, void *a3, int a4);
extern void func_001AAD00(void *a0, int a1);
extern void func_00260380(void *a0, int a1, void *a2);
extern void func_00260568(int a0, int a1, int a2);
extern int D_0062A340;
extern char D_00557060[];
extern char D_00557080[];

int termAll(int *a0) {
    int rv = deq_mes_th(D_0062A340, 0x50000, 0x40, D_00557060, 0x2A);
    if (rv == 0) {
        func_001AAD00(D_00557060, 0x2B);
        func_00260380(D_00557060, 0x2B, D_00557080);
    }
    func_00260568(rv, 0, 0x50000);
    a0[0] = rv;
    if (rv == 0) {
        return -1;
    }
    a0[3] = 0;
    a0[1] = 0x50000;
    a0[2] = 0;
    return 0;
}

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
