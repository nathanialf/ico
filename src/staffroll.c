#include "common.h"



extern int D_0063318C;
extern char D_00633188;
extern int D_00633EC8;
extern int D_00633EC4;
extern int D_00633ECC;
void staffRollStart(int unused, int a, int b, int c) {
    D_00633EC4 = a;
    D_00633EC8 = b;
    D_00633ECC = c;
}

extern int D_006319B0;

int staffRollScroll(int a0, int a1, int a2, int *p, int *q, int *r) {
    int ret = 1;
    if (D_006319B0 == 0) {
        *r = 1;
        *q = 1;
        *p = 1;
    } else {
        *p = D_00633EC4;
        *q = D_00633EC8;
        *r = D_00633ECC;
        if (*q == 0) ret = 0;
        if (*p == 0) *p = 1;
        if (*q == 0) *q = 1;
        if (*r == 0) *r = 1;
    }
    *q = 0x32;
    return ret;
}

void staffRollNameOut(void) {
    D_00633188 = 0;
    D_0063318C = -1;
}

extern int D_004BD980[];
extern int D_00633198;
extern float D_0063319C;
extern float D_006331A0;
extern int D_006331B4;
extern float D_00633ED0;
extern float D_00633ED4;
extern int D_00633ED8;
extern int D_00633EDC;
extern int D_00633EE8;
extern int D_00633EEC;
extern unsigned char D_00706F70[];
extern void func_002641D8(void *a0, int a1, int a2);

void staffRollMain(int a0, float arg) {
    int z = 0;
    D_00633ED4 = 0.0f;
    D_006331B4 = a0;
    D_00633198 = 1;
    D_004BD980[0] = 0x500;
    D_00633ED0 = arg + arg;
    D_00633ED8 = 0;
    D_00633EEC = 0;
    D_00633EDC = z;
    D_00633EE8 = z;
    D_006331A0 = D_00633ED4;
    D_0063319C = D_00633ED4;
    func_002641D8(D_00706F70, z, 0x12C0);
}

INCLUDE_ASM("asm/nonmatchings/src/staffroll", staffRollWide);

INCLUDE_ASM("asm/nonmatchings/src/staffroll", func_001B8388);

INCLUDE_ASM("asm/nonmatchings/src/staffroll", func_001B84C8);

