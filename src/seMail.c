#include "common.h"

extern char D_00621D40[];
extern void debug_StdPrintfDummy();

extern void debug_StdPrintfDummy__pn(void *a0) __asm__("debug_StdPrintfDummy");
void setMailTarget(int a0, int *a1, int *a2)
{
    int v = *a2;
    if (v >= 0x10) {
        debug_StdPrintfDummy(D_00621D40);
        return;
    }
    *a2 = v + 1;
    a1[v] = a0;
}
INCLUDE_ASM("asm/nonmatchings/src/seMail", seMail);
extern void GetRootPosition(void *out, void *obj);
extern float sceVu0InnerProduct(void *a, void *b);
extern void sceVu0SubVector(void *out, void *a, void *b);

int seMailTargetDistCheck(void *a0, void *a1, void *a2) {
    float buf0[4];
    float buf1[4];
    float buf2[4];
    float threshold;
    threshold = (float)(*(int *)((char *)a2 + 0x30) * *(int *)((char *)a2 + 0x30));
    if (a0 == 0 || a1 == 0) {
        return 0;
    }
    GetRootPosition(buf0, a0);
    GetRootPosition(buf1, a1);
    sceVu0SubVector(buf2, buf0, buf1);
    if (sceVu0InnerProduct(buf2, buf2) < threshold) {
        return 1;
    }
    return 0;
}
