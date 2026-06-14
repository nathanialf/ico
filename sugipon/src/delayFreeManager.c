#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00101C80);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102310);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_001023E8);

extern int D_00629C14;
extern int D_00629C00;
extern int D_002715D4[];
extern void func_00104A80(void);

int func_00102488(void) {
    int ret = 0;
    if (D_00629C14 != D_00629C00) {
        unsigned int x;
        D_00629C14 = D_00629C00;
        func_00104A80();
        x = D_002715D4[0] & 0x800;
        ret = x != 0;
    }
    return ret;
}

extern void func_0025D038();
extern void debug_assertMessage();
extern int func_00100410();
extern int func_001003B0();
extern void func_00102310();
extern char D_0062BAB0[];
extern int D_0062BF08;

int func_001024C8(void) {
    func_0025D038();
    debug_assertMessage(D_0062BAB0);
    debug_assertMessage(D_0062BAB0);
    func_001003B0(func_00100410(), 0xE);
    D_0062BF08 = func_00100410();
    func_00102310();
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102528);

extern int D_00629E20;
extern int D_00629E24;
extern int D_00658EC0[];

void func_001025B8(void) {
    int i;
    for (i = 0x7F; i >= 0; i--) D_00658EC0[i] = 0;
    for (i = 0x7F; i >= 0; i--) D_00658EC0[0x80 + i] = 0;
    for (i = 0x7F; i >= 0; i--) D_00658EC0[0x100 + i] = 0;
    D_00629E24 = 0;
    D_00629E20 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/delayFreeManager", func_00102650);

extern void func_0010E148(void *a0, void *a1, void *a2);
extern void GetInverseQuaternion(void *a0, void *a1);

void func_00102760(void *a0, void *a1) {
    char *p = *(char **)a1;
    if (p != 0) {
        char *q = *(char **)(p + 0x15C);
        int idx = *(int *)((char *)a1 + 0x4);
        char *base = *(char **)(q + 0x10);
        func_0010E148(a0, base + idx * 16, (char *)a1 + 0xD0);
    } else {
        GetInverseQuaternion(a0, (char *)a1 + 0xD0);
    }
}

extern void func_0010E250();
extern void func_0023FE08();

void func_00102798(void *a0) {
    char *p = (char *)a0 + 0xA0;
    char *fobj = *(char **)((char *)a0 + 0xC);
    func_0010E250(fobj, (char *)a0 + 0xD0, p);
    {
        char *q = *(char **)a0;
        if (q != 0) {
            func_0023FE08(fobj, *(int *)(*(char **)(q + 0x15C) + 0xC) + (*(int *)((char *)a0 + 0x4) << 6), fobj);
        }
    }
    *(float *)(fobj + 0x34) = *(float *)(fobj + 0x34) + *(float *)(p + 0xB0);
    func_00102760(*(void **)((char *)a0 + 0x10), a0);
}

extern void func_00102760(void *a0, void *a1);
extern void func_00102798(void *a0);

void func_00102820(void *a0, int a1) {
    func_00102760(a0, *(void **)(a1 + 0x15C));
}

void func_00102828(int a0) {
    func_00102798(*(void **)(a0 + 0x15C));
}

extern void GetInverseQuaternion(void *a0, void *a1);

void func_00102830(int **a0, void *a1) {
    GetInverseQuaternion((char *)a0[0x57] + 0xC0, a1);
}

extern void func_0010E188(void *a0, void *a1, int a2);

void func_00102840(char *a0, void *a1) {
    char *q = *(char **)(a0 + 0x15C) + 0xD0;
    char *p;
    GetInverseQuaternion(q, a1);
    p = *(char **)(a0 + 0x15C);
    if (*(int *)p != 0) {
        char *m = *(char **)(*(int *)p + 0x15C);
        func_0010E188(q, a1, *(int *)(m + 0x10) + (*(int *)(p + 4) << 4));
    }
}
