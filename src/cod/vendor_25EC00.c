#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct { int *end; int pad[2]; int *cur; } Pool241748;

void sceVif1PkInit(int *a0, int a1) {
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}
int sceVif1PkReset(int *a0) {
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}
int *sceVif1PkTerminate(int **a0) {
    int *p = a0[0];
    int *q = (int *)a0[2];
    while ((int)p & 0xC) {
        *p = 0;
        p++;
    }
    if (q) {
        int n = (((char *)p - (char *)q) >> 4) - 1;
        *q += n;
    }
    a0[0] = p;
    a0[2] = 0;
    return p;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EC00", sceVif1PkCnt);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EC00", sceVif1PkEnd);
extern void sceVif1PkAlign(void *a0, int a1, int a2);

void sceVif1PkOpenDirectCode(void *a0, int a1) {
    int *v;
    int w;
    sceVif1PkAlign(a0, 2, 3);
    v = *(int **)a0;
    w = a1 ? 0xD0000000 : 0x50000000;
    *v = w;
    *(int **)((char *)a0 + 0xC) = v;
    *(int **)a0 = v + 1;
}
int sceVif1PkCloseDirectCode(Pool241748 *a0) {
    int n = (int)a0->end - 4;
    int *p = a0->cur;
    a0->cur = 0;
    n -= (int)p;
    n = (unsigned)(n >> 2) >> 2;
    *p = *p + n;
    return n;
}
void sceVif1PkOpenGifTag(void *a0, u128_241778 a1) {
    void **pp = (void **)a0;
    void *p = *pp;
    *(u128_241778 *)p = a1;
    *(void **)((char *)a0 + 0x14) = p;
    *pp = (char *)p + 0x10;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EC00", sceVif1PkCloseGifTag);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25EC00", sceVif1PkAlign);
void sceVif1PkAddGsData(int **a0, long long a1) {
    int *p = *a0;
    *p++ = (int)a1;
    *a0 = p + 1;
    *p = (int)(a1 >> 32);
}
