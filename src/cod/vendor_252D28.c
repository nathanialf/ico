#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00252D28);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00252E90);

extern int D_0062ED78[];
extern void func_00252590(void *a0);

void func_00252F30(void) {
    func_00252590(D_0062ED78);
}

extern int D_0062EDA8[];

void func_00252F40(void) {
    func_00252590(D_0062EDA8);
}

extern int D_0062EDC0[];

void func_00252F50(void) {
    func_00252590(D_0062EDC0);
}

extern int D_0062EDF8[];

void func_00252F60(void) {
    func_00252590(D_0062EDF8);
}

extern void func_002586F8(void *a0);

void func_00252F70(int **a0) {
    func_002586F8((char *)a0[0x10] + 0x4C);
}

extern void func_002587E0(void *a0);

void func_00252F80(int **a0) {
    func_002587E0((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00252F90);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002532C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00253978);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00253D98);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00253F28);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00253FA0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254038);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002540F0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002541C0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254270);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254328);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254420);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254520);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002545C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254678);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254760);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254848);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254928);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002549F8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254B20);

extern int D_00254CE0;

void func_00254C38(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $12, $0, 0x18\n"
        "lui $10, %%hi(D_00254CE0)\n"
        "addiu $10, $10, %%lo(D_00254CE0)\n"
        "lq $11, 0x0($10)\n"
        "1:\n"
        "lq $8, 0x0($5)\n"
        "addi $12, $12, -0x1\n"
        "lq $13, 0x0($6)\n"
        "addiu $4, $4, 0x10\n"
        "lq $9, 0x10($5)\n"
        "paddh $8, $8, $13\n"
        "lq $2, 0x10($6)\n"
        "pminh $8, $8, $11\n"
        "paddh $9, $9, $2\n"
        "pmaxh $8, $8, $0\n"
        "pminh $9, $9, $11\n"
        "addiu $5, $5, 0x20\n"
        "pmaxh $9, $9, $0\n"
        "addiu $6, $6, 0x20\n"
        "ppacb $10, $9, $8\n"
        "bnez $12, 1b\n"
        "sq $10, -0x10($4)\n"
        ".set reorder\n"
        ::: "$2","$8","$9","$10","$11","$12","$13","memory");
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254C98);

void func_00254CF8(int a0) {
    volatile int *reg = (volatile int *)0x10002010;
    *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254D20);

extern int func_002560D8(int a0);

int func_00254F08(void) {
    return func_002560D8(3);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00254F28);

extern int D_005525C8[];
extern int D_00552D70[];
extern int D_0062EEF0[];
extern void func_00252560(int a0, int a1);
extern int func_00256290(int a0);
extern void func_002563C8(int a0);

int func_002550B0(void) {
    int cont;
    int sum;
    unsigned int v;

    sum = 0;
    do {
        v = func_002560D8(0);
        switch (v) {
        case 0x22:
            cont = 1;
            break;
        case 0x23:
            cont = 1;
            sum += 0x21;
            break;
        case 0:
            {
                int r = func_00256290(0xB);
                if ((D_00552D70[0] != 0) && (r == 0xF)) {
                    func_002563C8(0xB);
                    cont = 1;
                } else {
                    func_00252560((int) D_0062EEF0, v);
                    D_005525C8[0] = 1;
                    return 1;
                }
            }
            break;
        default:
            sum += v;
            cont = 0;
            break;
        }
    } while (cont);
    return sum;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002551C0);

extern int D_005525E8[];
extern int D_005526FC[];
extern int D_0062EF48[];
extern int D_0062EF70[];
extern void func_00256648(void);
extern int func_002566B0(void);

int func_002552E8(int a0, int *a1, int *a2, int *a3) {
    int id;
    int m;
    int n;

    D_005525C8[0] = 0;
    func_00256648();
    id = func_00256290(0x20);
    if ((unsigned int) (id - 0x101) >= 0xAF) {
        func_00252560((int) D_0062EF48, id);
        return 2;
    }
    func_002563C8(0x20);
    m = func_002566B0();
    n = func_002550B0();
    *a2 = n;
    if (D_005525C8[0] != 0) {
        func_00252590(D_0062EF70);
        return 1;
    }
    *a1 = ((((m << 7) + (id & 0xFF)) - 1) * D_005525E8[0] + n) - 1;
    *a2 = 1;
    D_005526FC[0] = 1;
    a3[5] = 0;
    a3[4] = 0;
    a3[1] = 0;
    a3[0] = 0;
    a3[7] = 0;
    a3[6] = 0;
    a3[3] = 0;
    a3[2] = 0;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00255410);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00255610);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002556E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00255C08);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00255C90);

extern void func_00255C08();
extern int func_002564E0(int a0);

void func_00255E10(char *a0, char *a1, void *a2, void *a3, int a4, int a5, int a6) {
    void *r;
    int r2;

    r = (void *)func_002560D8(2);
    if (a2 == 0) goto c1z;
    if (r == 0) { r2 = 0; goto c1c; }
    r2 = func_002564E0(a2);
    goto c1c;
c1z:
    r2 = 0;
c1c:
    func_00255C08(a0, a2, r, r2, a6);
    if (a4 != 0) {
        *(int *)a1 = func_00254F08();
    }
    r = (void *)func_002560D8(2);
    if (a3 == 0) goto c2z;
    if (r == 0) { r2 = 0; goto c2c; }
    r2 = func_002564E0(a3);
    goto c2c;
c2z:
    r2 = 0;
c2c:
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) >> 1;
    }
    func_00255C08(a0 + 4, a3, r, r2, a6);
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) * 2;
    }
    if (a4 != 0) {
        *(int *)(a1 + 4) = func_00254F08();
    }
}

extern int D_005524E4[];
extern int D_00552DC8[];

void func_00255F50(unsigned int a0) {
    *(volatile unsigned int *)0x10002000 = a0;
    D_005524E4[0] = D_00552DC8[a0 >> 28];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00255F80);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256028);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002560D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256290);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002563C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002564E0);

extern void func_00255F80(void);

void func_00256648(void) {
    int v;
    func_00255F80();
    v = (-(*(volatile int *)0x10002020 & 7)) & 7;
    if (v) func_002563C8(v);
    while (func_00256290(0x18) != 1) {
        func_002563C8(8);
    }
}

extern int D_00552700[];
extern int D_00552D80[];
extern void func_00256BF8(void);

int func_002566B0(void) {
    int *p = D_00552700;
    *p = func_002564E0(5);
    if (func_002564E0(1)) {
        int *q = D_00552D80;
        *q = func_002564E0(1);
        func_002563C8(7);
        func_00256BF8();
    } else {
        D_00552D80[0] = 0;
    }
    return 0;
}

extern void *D_005524A4[];
extern int D_0055263C[];
extern long long D_00552D48[];
extern long long D_00552D50[];
extern void *func_00251CF8(void *a0, void *a1);
extern void func_002526E0(void);
extern void func_00256848(void);
extern void func_00256D10(void);

int func_00256720(void) {
    struct { int f0; long long f8; long long f10; } local;

    while (1) {
        func_00256648();
        switch ((unsigned int) func_002564E0(0x20)) {
        case 0x1B3:
            func_002526E0();
            break;
        case 0x1B8:
            func_00256D10();
            break;
        case 0x100:
            func_00256848();
            local.f0 = 5;
            local.f8 = -1;
            local.f10 = -1;
            func_00251CF8(D_005524A4[0], &local);
            D_00552D48[0] = local.f8;
            D_00552D50[0] = local.f10;
            return D_0055263C[0];
        case 0x1B7:
            return 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256848);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256918);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002569C8);

void func_00256BF8(void) {
    while (func_002564E0(1)) {
        func_002563C8(8);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256C30);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256D10);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256DF8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256EA8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00256F98);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257048);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257128);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002571E0);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257660);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257888);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257A20);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257B38);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257DE0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00257F28);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002581C0);

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

int func_00258450(void *a0, int a1) {
    unsigned long long v = *(unsigned long long *)a0;
    return v >> (64 - a1);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00258470);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_002587E0);

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

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_252D28", func_00258A00);

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
