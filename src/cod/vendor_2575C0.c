/* Vendor TU: libsndn2.a(sound.o), head - 0x2575C0..0x258CC0; the member
 * continues into vendor_258CC0. */
#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

extern void func_00252590(void *a0);
extern void func_00255F50(unsigned int a0);
extern void *D_005524A4[];
extern void *func_00251CF8(void *a0, void *a1);

extern char D_0062F098[];
extern void func_00264DF8();

int func_002575C0(char *p) {
    char *c = *(char **)((char *)D_005524A4[0] + 0x40);
    int e0 = *(int *)(c + 0xE0);
    int flag;
    if (e0 != 0) {
        flag = *(int *)(c + 0xDC) >= *(int *)(p + 0x4) && e0 >= *(int *)(p + 0x8);
    } else {
        flag = *(int *)(c + 0xE4) >= *(int *)(p + 0xC) * *(int *)(p + 0x10);
    }
    if (flag == 0) {
        char buf[0x100];
        func_00264DF8(buf, (int)D_0062F098, *(int *)(p + 0x4), *(int *)(p + 0x8));
        func_00252590(buf);
    }
    return flag;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00257660);

extern int D_005525C4[];
extern int D_00552D40[];

int func_00257850(void) {
    int *q = *(int **)((char *)D_005524A4[0] + 0x40);
    if (q[2] != 2) {
        int v = D_005525C4[0];
        q[2] = 2;
        q[0x2B] = v;
    }
    D_00552D40[0] = 1;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00257888);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00257A20);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00257B38);

void func_00257CF8(int a0, int a1) {
    int local[8];
    while (*(volatile int *)0x10002010 < 0) {
    }
    *(volatile int *)0x1000B010 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000B020 = a1 << 6;
    *(volatile int *)0x1000B000 = 0x100;
    func_00255F50(a1 | 0x70000000);
    local[0] = 4;
    func_00251CF8(D_005524A4[0], local);
    while ((*(volatile unsigned int *)0x1000B000 >> 8) & 1) {
    }
    while (*(volatile int *)0x10002010 < 0) {
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00257DE0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00257F28);

extern int D_00719FDC[];
extern int D_00719FE0[];
extern int D_00719FE4[];

int func_002580E8(void) {
    int rem;
    *(volatile int *)0x1000E010 = 0x10;
    rem = D_00719FE0[0];
    D_00719FDC[0] = D_00719FDC[0] + 1;
    if (rem == 0) {
        return 1;
    }
    if ((unsigned int)rem > 0xFFFF) {
        int addr = D_00719FE4[0];
        *(volatile int *)0x1000B410 = addr;
        *(volatile int *)0x1000B420 = 0xFFFF;
        *(volatile int *)0x1000B400 = 0x101;
        D_00719FE4[0] = (addr + 0xFFFF0) & 0x0FFFFFFF;
        D_00719FE0[0] = rem - 0xFFFF;
    } else {
        *(volatile int *)0x1000B410 = D_00719FE4[0];
        *(volatile int *)0x1000B420 = rem;
        *(volatile int *)0x1000B400 = 0x101;
        D_00719FE0[0] = 0;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_002581C0);

extern void func_00258470(int *a0, int a1);

void func_00258418(int *a0, int a1, int a2, int a3) {
    a0[2] = a1;
    a0[3] = a1;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = 0;
    a0[8] = a2;
    a0[9] = a2 + a3;
    a0[0xA] = a3;
    func_00258470(a0, 0);
}

/* func_00258450 — PARKED 2026-08-06, ONE divergent instruction. The recovered C
 * and the full mechanism are in tough_nuts/func_00258450/ — read notes.md there
 * before spending a round on this; three separate confident accounts of why it
 * resists were each measured wrong, and the corrections are recorded.
 * Short version: the C is `long long f(unsigned long long *p, int n) {
 * return (int)(*p >> (64 - n)); }` (the `long long` return is measured-safe —
 * both callers stay byte-identical). It emits all 7 ROM instructions in ROM's
 * registers and order; only the `jr` delay slot differs. The assembler question
 * is settled and closed. Sibling with the identical residual: func_001011E8. */
extern int func_00258450(unsigned long long *p, int n);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00258450);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00258470);

int func_00258508(int *self, int a1)
{
    int ret = func_00258450(self, a1);
    func_00258470(self, a1);
    return ret;
}

int func_00258558(int *self)
{
    int ret = func_00258450(self, 1);
    func_00258470(self, 1);
    return ret;
}

void func_002585A0(int *a0, int a1) {
    long long x = *(long long *)(a0 + 6) + (a1 << 3);
    int v;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = x;
    v = a0[2] + (int)(x >> 3);
    a0[3] = v;
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        a0[3] = v - a0[10];
    }
    func_00258470(a0, 0);
}

int func_002585F8(int *a0, int a1) {
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

extern void func_00101A40(int *self);
extern void func_00101A88(void);

void func_00258628(int *a0) {
    func_00101A40(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B000 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    func_00101A88();
}

void func_00258690(int *a0) {
    func_00101A40(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    func_00101A88();
}

void func_002586F8(void *a0) {
    func_00258690((int *)1);
    ((int *)a0)[0] = *(volatile int *)0x1000B410;
    ((int *)a0)[1] = *(volatile int *)0x1000B430;
    ((int *)a0)[2] = *(volatile int *)0x1000B420;
    ((int *)a0)[3] = *(volatile int *)0x1000B400;
    while (*(volatile int *)0x10002010 & 0xF0) {
    }
    func_00258628((int *)0);
    ((int *)a0)[4] = *(volatile int *)0x1000B010;
    ((int *)a0)[5] = *(volatile int *)0x1000B020;
    ((int *)a0)[6] = *(volatile int *)0x1000B000;
    ((int *)a0)[7] = *(volatile int *)0x10002020;
    ((int *)a0)[8] = *(volatile int *)0x10002010;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_002587E0);

int func_00258930(int a0) {
    int r = 0;
    switch (a0) {
    case 0:
        while (*(volatile int *)0x10002010 < 0) {
        }
        r = 0;
        break;
    case 1:
        r = (unsigned)*(volatile int *)0x10002010 >> 31;
        break;
    }
    return r;
}

void func_00258998(int *a0) {
    func_00101A40(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    func_00101A88();
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2575C0", func_00258A00);

extern unsigned char D_0071A600[];

void *func_00258C38(int a0) {
    return &D_0071A600[a0 * 0x58];
}

extern unsigned char D_0071B680[];

void *func_00258C50(int a0) {
    return &D_0071B680[a0 * 0x54];
}

extern int D_0071C640[];

void *func_00258C68(void) {
    return D_0071C640;
}

extern unsigned char D_0071A000[];

void *func_00258C78(int a0) {
    return &D_0071A000[a0 * 0xC];
}

extern int D_0071E900[];

void func_00258C90(int a0, int a1) {
    D_0071E900[a0] = a1;
}

int func_00258CA8(int a0) {
    return D_0071E900[a0];
}

