#include "common.h"

extern int D_00623418[];
extern void debug_StdPrintfDummy(char *fmt, ...);

void ErrMessage(int a0)
{
    debug_StdPrintfDummy(D_00623418, a0);
}
extern void memcpy(void *dst, void *src, int count);

int copy2area(char *a0, int a1, char *a2, int a3, char *a4, int a5, char *a6, int a7) {
    int b = a5 + a7;
    if (a1 + a3 < b) {
        return 0;
    }
    if (a5 >= a1) {
        memcpy(a0, a4, a1);
        memcpy(a2, a4 + a1, a5 - a1);
        memcpy(a2 + a5 - a1, a6, a7);
    } else if (a7 >= a1 - a5) {
        memcpy(a0, a4, a5);
        memcpy(a0 + a5, a6, a1 - a5);
        memcpy(a2, a6 + a1 - a5, a7 - (a1 - a5));
    } else {
        memcpy(a0, a4, a5);
        memcpy(a0 + a5, a6, a7);
    }
    return b;
}
