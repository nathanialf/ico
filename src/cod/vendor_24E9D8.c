#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { int unk0, unk4, unk8, unkC; } P24D418;

struct S12 { char b[12]; };
typedef struct { int f0; int *f4; int f8; int fC; int f10; char pad14[0x8]; } PObjA8B8Ent;

extern PObjA8B8Ent D_00717C50[][4];
extern int func_0024E4C8(int a0, int a1);

int func_0024E9D8(int a0, int a1, int a2, int a3) {
    int q;
    int t72;
    int v;

    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    q = func_0024E4C8(a0, a1);
    t72 = *(unsigned char *)(q + 0x72);
    if (t72 == 1 && *(unsigned char *)(q + 0x71) != 2) {
    if (a2 == 2) {
        goto case2;
    }
    if (a2 >= 3) {
        goto ge3;
    }
    if (a2 == t72) {
        goto case1;
    }
    return 0;
ge3:
    if (a2 == 3) {
        goto case3;
    }
    if (a2 == 4) {
        goto case4;
    }
    return 0;
case1:
    v = *(unsigned char *)(q + 0x65);
    if (v == 0xF3) {
        return 0;
    }
    return v >> 4;
case2:
    if (*(unsigned char *)(q + 0x64) == t72) {
        return 0;
    }
    return *(unsigned short *)(q + (*(unsigned char *)(q + 0x69) << 1) + 0x50);
case3:
    if (*(unsigned char *)(q + 0x64) == t72) {
        return 0;
    }
    return *(unsigned char *)(q + 0x69);
case4:
    if (*(unsigned char *)(q + 0x64) == t72) {
        return 0;
    }
    if (a3 == -1) {
        return *(unsigned char *)(q + 0x68);
    }
    if (a3 >= (int)*(unsigned char *)(q + 0x68)) {
        return 0;
    }
    return *(unsigned short *)(q + (a3 << 1) + 0x50);
    }
    return 0;
}

extern int D_00717C00[];
extern int D_00717F40[];
extern int func_00246458();
extern int func_0024E6A8(int a0, int a1, int a2);

int func_0024EB10(int a0, int a1, int a2, int a3) {
    int *s0 = D_00717F40;
    int local = 0;
    int ret;
    int s;
    D_00717F40[0] = 6;
    s0[1] = a0;
    s0[2] = a1;
    s0[3] = a2;
    s0[4] = a3;
    ret = func_00246458((int)D_00717C00, 1, 0, (int)s0, 0x80, (int)s0, 0x80, 0, local);
    if (ret < 0) {
        return 0;
    }
    s = s0[5];
    if (s == 1) {
        func_0024E6A8(a0, a1, 2);
        s = s0[5];
    }
    return s;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024EBC8);

int func_0024EC80(int a0, int a1, char *a2)
{
    int *s0 = D_00717F40;
    int i;
    int val;
    int *new_var;
    int ret;
    char *dst;
    D_00717F40[0] = 8;
    new_var = D_00717F40;
    s0[1] = a0;
    s0[2] = a1;
    dst = (char *)s0 + 0xC;
    for (i = 0; i < 6; i++) {
        dst[i] = a2[i];
    }
    ret = func_00246458(D_00717C00, 1, 0, new_var, 0x80, new_var, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        func_0024E6A8(a0, a1, 2);
        val = s0[5];
    }
    return val;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024ED58);

int func_0024EE10(int a0, int a1, int a2) {
    int ret;
    D_00717F40[3] = a2;
    D_00717F40[0] = 0xA;
    D_00717F40[1] = a0;
    D_00717F40[2] = a1;
    if (func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0) < 0) {
        return 0;
    }
    ret = D_00717F40[4];
    if (ret == 1) {
        func_0024E6A8(a0, a1, 2);
        ret = D_00717F40[4];
    }
    return ret;
}

extern int func_0024ED58(int a0, int a1);

int func_0024EEC0(int a0, int a1) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    return func_0024ED58(a0, a1) == 0x3FFFF;
}

int func_0024EF20(int a0, int a1) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    return func_0024EE10(a0, a1, 0xFFF);
}

int func_0024EF78(int a0, int a1) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    return func_0024EE10(a0, a1, 0);
}

int func_0024EFD0(int a0, int a1, void *a2) {
    int r;
    D_00717F40[1] = a0;
    D_00717F40[0] = 0xB;
    D_00717F40[2] = a1;
    *(struct S12 *)((char *)D_00717F40 + 0xC) = *(struct S12 *)a2;
    r = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    if (D_00717F40[7] == 1) {
        func_0024E6A8(a0, a1, 2);
    }
    return D_00717F40[7];
}

int func_0024F0A0(void) {
    int ret;
    D_00717F40[0] = 0xC;
    ret = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_00717F40[3];
}

int func_0024F108(int a0) {
    int ret;
    D_00717F40[0] = 0xD;
    D_00717F40[1] = a0;
    ret = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_00717F40[3];
}

int func_0024F170(void) {
    int ret;
    D_00717F40[0] = 0x12;
    ret = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_00717F40[3];
}

int func_0024F1D8(int a0) {
    int ret;
    D_00717F40[0] = 0x14;
    D_00717F40[1] = a0;
    ret = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_00717F40[2];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F240);

extern char D_005523D0[];
extern int D_005523D4[];
extern char D_00717FC0[];
extern char D_00719580[];

void *func_0024F3F8(int *a0, int *a1) {
    a0[0] = (int)D_00719580;
    a1[0] = (int)D_005523D0;
    *(int *)(D_00719580 + 0x3C) = D_005523D4[0];
    return D_00717FC0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F428);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F4E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F5A0);

extern int func_0024F5A0(int a0, int a1, int a2, int a3);

int func_0024F6D8(int a0, int a1, int a2) {
    int ret = func_0024F5A0(a0, a1, a2, 0x40);
    if (ret == 0) {
        *(int *)D_005523D0 = 0xB;
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F710);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F7C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F8A0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F930);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024FA50);

extern void func_00100F18(int a0);

void func_0024FBD0(int a0, int a1, int a2) {
    func_00100F18(a2);
    SYNC();
    EI();
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024FBF8);

extern void func_00100540(int a0);
extern int func_00246648(char *a0);
extern void func_0024FBF8(int a0);

int func_0024FC40(int a0, int *a1, int *a2) {
    int r;
    if (*(int *)D_005523D0 == 0) {
        return 0xFFFFFFFF;
    }
    r = func_00246648(D_00717FC0);
    if (a0 != 0) goto L050;
    if (r == 0) goto L050;
    while (func_00246648(D_00717FC0) != 0) {
        func_0024FBF8(0x3C);
    }
    r = 0;
L050:
    r = (r == 0);
    if (a1 != 0) {
        *a1 = *(int *)D_005523D0;
    }
    if (r != 0) {
        *(int *)D_005523D0 = 0;
        if (a2 != 0) {
            *a2 = *(int *)D_00719580;
        }
        func_00100540(D_005523D4[0]);
    }
    return r;
}

extern int *D_00717FE8[];
extern int *D_00717FEC[];
extern int *D_00717FF0[];

void func_0024FD20(int a0) {
    a0 |= 0x20000000;
    if (D_00717FE8[0]) *D_00717FE8[0] = *(int *)a0;
    if (D_00717FEC[0]) *D_00717FEC[0] = *(int *)(a0 + 4);
    if (D_00717FF0[0]) *D_00717FF0[0] = *(int *)(a0 + 0x90);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024FD78);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024FF00);

extern char D_00718580[];
extern int func_00264128(char *a0, char *a1, int a2);
extern int func_0026527C(char *a0);

void func_00250058(char *a0) {
    int n;
    if (a0 != 0) {
        if ((unsigned int)func_0026527C((char *)((int)D_00718580 | 0x20000000)) < 0x400) {
            n = func_0026527C((char *)((int)D_00718580 | 0x20000000));
        } else {
            n = 0x3FF;
        }
        func_00264128(a0, (char *)((int)D_00718580 | 0x20000000), n);
        a0[n] = 0;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002500E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00250230);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002502F8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00250420);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002504D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002506B0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00250818);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002508E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002509F8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00250A80);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00250C80);

extern void func_00250C80(void *a0, int a1, int a2, int a3, int a4);

void func_00250F70(void *a0, int a1, int a2) {
    do {
        func_00250C80(a0, a1, a2, 0, -1);
    } while (0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00250F90);

extern int func_002511D8();
extern int func_00258450(void *a0, int a1);
extern int func_00258508(int *bs, int nbits);
extern int func_00258558(int *bs);

int func_00251088(int *bs, P24D418 *pkt) {
    unsigned int i = 0;
    unsigned int a, b, c, n;
    int last;

    func_00258508(bs, 0x22);
    a = func_00258508(bs, 0x3);
    func_00258558(bs);
    b = func_00258508(bs, 0xF);
    func_00258558(bs);
    c = func_00258508(bs, 0xF);
    func_00258558(bs);
    pkt->unk0 = func_00258508(bs, 0x9);
    func_00258508(bs, 0x1E);
    n = func_00258508(bs, 0x3);
    pkt->unk8 = (a >> 2) & 1;
    pkt->unk4 = (a << 30) | (b << 15) | c;
    for (i = 0; i < n; i++) {
        func_00258508(bs, 0x8);
    }
    last = func_00258450(bs, 0x20);
    if (last != 0x1BB) goto unset;
    pkt->unkC = 1;
    func_002511D8(bs, pkt);
    goto end;
unset:
    pkt->unkC = 0;
end:
    return 1;
}

int func_002511D8(int *a0) {
    func_00258508(a0, 0x38);
    func_00258508(a0, 0x28);
    while (func_00258450(a0, 1) == 1) {
        func_00258508(a0, 0x18);
    }
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00251248);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002517D0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00251870);

int func_00251AB0(void) {
    return 1;
}

extern int D_005524A8[];
extern int D_005525C0[];
extern void func_002525E8(int a0, int a1);

void func_00251AB8(int a0, int a1, int a2) {
    int rounded = (a2 + 0x13) / 16 * 16;
    D_005524A8[0] = a1;
    D_005525C0[0] = rounded;
    func_002525E8(a1, rounded);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00251AF0);

extern void func_00251ED0(int self);

void func_00251B38(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int new_var;
  p[0xE4 / 4] = a2;
  new_var = 0xD8;
  p[new_var / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  p[0xDC / 4] = 0;
 do { } while (0);
  p[0xB0 / 4] = 0;
  p[0xE0 / 4] = 0;
  func_00251ED0((int) self);
  asm __volatile__("" : : : "memory");
}

void func_00251B80(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int prod;
  p[0xE0 / 4] = a3 << 4;
  p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  prod = a2 * a3;
  p[0xE4 / 4] = prod;
  p[0xDC / 4] = a2 << 4;
  p[0xB0 / 4] = 0;
  func_00251ED0((int) self);
  asm __volatile__("" : : : "memory");
}

void func_00251BD0(void *a0, int a1, int a2, int a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x25] = a1;
    p[0x26] = a2;
    p[0x27] = a3;
}

void func_00251BE8(void *a0, int *a1, int *a2, int *a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    *a1 = *(int *)((char *)p + 0x94);
    *a2 = *(int *)((char *)p + 0x98);
    *a3 = *(int *)((char *)p + 0x9C);
}

int func_00251C08(int **a0) {
    return a0[0x10][0];
}

int func_00251C18(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    return *(int *)((char *)p + 0x4) == 0;
}

extern int D_0054C884_b[] __asm__("D_005525C4");
extern void func_002523A0(void);
extern void func_00252488(void);

void func_00251C28(int *a0) {
    int *p = (int *)a0[0x10];
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    a0[2] = 0;
    p[0x20] = -1;
    p[0x2B] = 0;
    func_00252488();
    D_0054C884_b[0] = 0;
    func_002523A0();
}

extern int D_005524C0[];
extern int D_005524C4[];
extern int D_005524CC[];
extern int D_005524D0[];
extern int D_005524D8[];
extern int D_005524DC[];

int func_00251C68(void) {
    if (D_005524C0[0] != 0) *(int *)(D_005524C0[0] + 0x28) = 0;
    if (D_005524CC[0] != 0) *(int *)(D_005524CC[0] + 0x28) = 0;
    if (D_005524D8[0] != 0) *(int *)(D_005524D8[0] + 0x28) = 0;
    if (D_005524C4[0] != 0) *(int *)(D_005524C4[0] + 0x28) = 0;
    if (D_005524D0[0] != 0) *(int *)(D_005524D0[0] + 0x28) = 0;
    if (D_005524DC[0] != 0) *(int *)(D_005524DC[0] + 0x28) = 0;
    return 1;
}

int func_00251CD0(void *a0, int a1, int a2, int a3) {
    char *p = *(char **)((char *)a0 + 0x40);
    char *q0 = p + 0xC;
    int *q = (int *)(q0 + a1 * 8);
    int old;
    p += a1 * 8;
    ((int *)p)[4] = a3;
    old = *q;
    *q = a2;
    return old;
}

void *func_00251CF8(void *a0, void *a1) {
    void *rv = 0;
    if (a0 != 0) {
        char *p = *(char **)((char *)a0 + 0x40);
        if (p != 0) {
            char *q0 = p + 0xC;
            int off = *(int *)a1 * 8;
            void *(*fn)(void *, void *, int) = *(void *(**)(void *, void *, int))(q0 + off);
            if (fn != 0) {
                char *e2 = p + off;
                rv = fn(a0, a1, *(int *)(e2 + 0x10));
            }
        }
    }
    return rv;
}

void func_00251D48(void *a0) {
    int buf[8];
    buf[0] = 1;
    func_00251CF8(a0, buf);
}

void func_00251D70(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x1C] = 1;
    *(long long *)((char *)p + 0x78) = a1;
}

void func_00251D88(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    *(int *)((char *)p + 0x70) = 0;
    *(long long *)((char *)p + 0x78) = 0;
}

extern void *D_005524A4[];

void func_00251D98(int a0) {
    int *q = *(int **)((char *)D_005524A4[0] + 0x40);
    q[0x36] = a0;
}

int func_00251DB0(int **a0) {
    return a0[0x10][0x33];
}

int func_00251DC0(int **a0) {
    return a0[0x10][0x34];
}

void *func_00251DD0(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

void *func_00251DE0(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

int func_00251DF0(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x40);
    int old = *(int *)((char *)p + 0xE8);
    *(int *)((char *)p + 0xE8) = a1;
    return old;
}

void func_00251E00(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    *(long long *)((char *)p + 0xF0) = a1;
    p[0x3E] = 1;
}

void func_00251E18(int *a0, int a1, int a2) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a1;
    a0[3] = a1;
}

void func_00251E30(int *a0) {
    a0[3] = a0[2];
}

void func_00251E40(int *a0) {
    a0[2] = a0[3];
}

extern int D_0062EC68[];
extern void func_00252590(void *a0);

int func_00251E50(unsigned int *a0, int a1, unsigned int a2) {
    unsigned int rounded;
    unsigned int total;
    rounded = ((a0[2] + a2 - 1) / a2) * a2;
    total = rounded + a1;
    if (a0[0] + a0[1] >= total) {
        a0[2] = total;
        return rounded;
    }
    func_00252590(D_0062EC68);
    return 0;
}

int func_00251EB8(int *a0) {
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00251ED0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00252058);

extern int D_0055266C[];
extern int func_00252058(int a0, int a1, int a2);
extern int func_002521C0(int a0, int a1, int a2);

int func_00252180(int a0, int a1, int a2) {
    if (D_0055266C[0] != 3) {
        return func_002521C0(a0, a1, a2);
    }
    return func_00252058(a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002521C0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00252330);

extern int D_0054D030_alias[] __asm__("D_00552D70");
extern void func_00254CF8(int a0);

void func_002523A0(void) {
    D_0054D030_alias[0] = 0;
    func_00254CF8(1);
}

extern int D_005525DC[];
extern char D_0062ECE8[];
extern void func_00257A20();
extern void func_00257B38();

void func_002523B0(int a0) {
    int t;
    int d;
    int c;
    if (D_005525DC[0]) {
        func_00252590(D_0062ECE8);
        D_005525DC[0] = 0;
        return;
    }
    t = D_0055266C[0];
    if (t == 3) {
        func_00257A20(D_005524C4[0], a0 - 1);
    } else {
        func_00257B38(D_005524D0[0], D_005524DC[0], a0 - 1);
    }
    D_005525DC[0] = 0;
}

extern int D_00552498[];
extern int D_00552AB8[];

void func_00252438(void) {
    int v;
    func_00254CF8(1);
    v = D_00552498[0];
    D_00552AB8[0] = v;
    D_00552AB8[1] = v + 0x1800;
    *(void **)&D_00552AB8[0x50] = (void *)(v + 0x1B00);
    *(void **)&D_00552AB8[0x51] = (void *)(v + 0x3300);
    *(float *)((char *)D_00552AB8 + 0x280) = 0.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00252488);

extern int D_00628EC8_alias[] __asm__("D_0062ED08");
extern void func_002642D8(void *a0, ...);

void func_00252550(int a0) {
    func_002642D8(D_00628EC8_alias, a0);
}

extern void func_00264DF8(void *a0, int a1, ...);

void func_00252560(int a0, int a1) {
    char buf[0x100];
    func_00264DF8(buf, a0, a1);
    func_00252590(buf);
}

void func_00252590(void *a0)
{
    char *p = D_005524A4[0];
    if (p != 0) {
        register int q = *(int *)(p + 0x40);
        if (q != 0) {
            register int r = *(int *)(q + 0xC);
            if (r != 0) {
                int local[2];
                local[0] = 0;
                local[1] = (int)a0;
                func_00251CF8((int)p, local);
                return;
            }
        }
    }
    func_00252550(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002525E8);

int func_002526C0(int *a0, int a1, int a2) {
    a0[0x4 / 4] = a1;
    a0[0x8 / 4] = a2;
    a0[0xC / 4] = a1 >> 4;
    a0[0x10 / 4] = a2 >> 4;
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_002526E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00252838);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00252B80);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_00252C68);
