#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct { int f0; int *f4; int f8; int fC; int f10; char pad14[0x8]; } PObjA8B8Ent;

extern int func_0024A9C0(void *a0, int a1, int a2, int a3);

int func_0024AAC8(void *a0, int a1, int a2) {
    return func_0024A9C0(a0, a1, a2, 1);
}

extern char D_0062E668[];

int func_0024AAE8(void *a0, int a1) {
    return func_0024A9C0(a0, (int)D_0062E668, a1, 1);
}

extern char D_00716180[];
extern char D_00716380[];
extern int func_00246458();
extern int func_0024A348(void);

int func_0024AB10(int a0, void *a1, int a2) {
    int r;
    if (func_0024A348() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_00716180 + 0) = a0;
    *(int *)(D_00716180 + 4) = a2;
    r = func_00246458(D_00716380, 3, 0, D_00716180, 0x20, D_00716180, 0x20, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (a2 == 0) {
        *(unsigned char *)a1 = *(unsigned char *)D_00716180;
    } else if (a2 == 1) {
        *(unsigned short *)a1 = *(unsigned short *)D_00716180;
    } else if (a2 == 2) {
        *(int *)a1 = *(int *)D_00716180;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024AC00);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024ACE0);

extern int func_00100930(int a0);

int func_0024AE10(void) {
    int t = func_00100930(4) & 0x10000;
    return t != 0;
}

extern void func_00100920(int a0, int a1);
extern void func_002453C0();

int func_0024AE38(void) {
    if (func_00100930(4) & 0x40000) {
        func_00100920(4, 0x40000);
        ((void (*)(void))func_002453C0)();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024AE80);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024AF90);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B028);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B0E8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B130);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B180);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B1D0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B300);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B360);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B3E8);

extern int D_005508C8[];
extern void func_0024B3E8(int x, int y);

void func_0024B3F8(void)
{
  int *p = D_005508C8;
  unsigned int i = 0;
  do
  {
    i++;
    func_0024B3E8(p[0], p[1]);
    p += 2;
  }
  while (i < 6);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B448);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B458);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B468);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B478);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B488);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B498);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B4A8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B4B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B4C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B500);

void func_0024B880(int *a0, int *a1) {
    a1[2] = a0[4];
}

extern int D_00717880[];

int func_0024B890(int a0) {
    return D_00717880[a0];
}

int func_0024B8A8(int a0, int a1) {
    D_00717880[a0] = a1;
    return a1;
}

extern int D_00717758[];

void *func_0024B8C8(void) {
    return D_00717758;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024B8D8);

extern int D_005508F8[];
extern int D_00717754[];
extern int func_00100250(int a0, int a1);
extern int func_00100AD8(int a0);

void func_0024BB58(void) {
    func_00100AD8(5);
    func_00100250(5, D_00717754[0]);
    D_005508F8[0] = 0;
}

int func_0024BB90(int a0, int a1) {
    int old = D_00717758[5];
    D_00717758[5] = a0;
    D_00717758[6] = a1;
    return old;
}

int func_0024BBA8(int a0, int a1) {
    int old = D_00717758[3];
    D_00717758[3] = a0;
    D_00717758[4] = a1;
    return old;
}

extern int D_00717764[];
extern int D_0071776C[];

int func_0024BBC0(int a0, int a1, int a2) {
    int off = a0 * 8;
    int *p;
    if (a0 >= 0) goto pos;
    a0 = D_00717764[0];
    goto done;
pos:
    a0 = D_0071776C[0];
done:
    off += a0;
    p = (int *)off;
    p[0] = a1;
    p[1] = a2;
}

void func_0024BBF0(int a0) {
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_00717764[0];
    } else {
        a0 = D_0071776C[0];
    }
    off += a0;
    *(int *)off = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BC18);

extern int func_0024BC18(int a0, int a1, int a2, int a3, int t0, int t1, int t2);

int func_0024BD50(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = func_0024BC18(a0, 0, a1, a2, a3, t0, t1);
  return v;
  asm __volatile__("" : : : "memory");
}

int func_0024BD90(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = func_0024BC18(a0, 1, a1, a2, a3, t0, t1);
  int new_var;
  new_var = v;
  return new_var;
  asm __volatile__("" : : : "memory");
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BDD0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BEF8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BFA4);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BFAC);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024BFD0);

extern int D_00717900[];
extern void func_00101A40(int *self);
extern void func_00101A88(void);
extern int func_0024CBC0(int a0);

int func_0024C038(int a0) {
    int ret;
    if (func_0024CBC0(1) != 0) {
        return 0;
    }
    (*(int (*)(void))func_00101A40)();
    ret = D_00717900[0];
    D_00717900[0] = a0;
    func_00101A88();
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C090);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C130);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C2C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C368);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C400);

extern int D_0055093C[];
extern void (*D_00717904[])(int);
extern int D_00717908[];
extern void func_0024C530();

int func_0024C480(int a0, int a1) {
    int ret;
    if (D_0055093C[0] < 0) {
        func_0024C530();
    }
    (*(int (*)(void))func_00101A40)();
    ret = (int)D_00717904[0];
    D_00717908[0] = a1;
    D_00717904[0] = (void (*)(int))a0;
    func_00101A88();
    return ret;
}

extern int D_00550924[];

void func_0024C4F0(void) {
    if (D_00717904[0] != 0 && D_00550924[0] == 0) {
        D_00717904[0](D_00717908[0]);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C530);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C6B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024C9B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CB28);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CBC0);

extern int D_00550910[];
extern char D_00552348[];
extern char D_0062E818[];
extern void func_001019E0();
extern int func_00246648(char *a0);
extern void func_0024BFD0(unsigned short a0);

int func_0024CC60(int a0) {
    if (!a0) {
        if (D_00550910[0] > 0) func_001019E0(D_0062E818);
        while (func_00246648(D_00552348)) {
            func_0024BFD0(0x3C);
        }
        return 0;
    }
    return func_00246648(D_00552348);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CCD0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024CE40);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D120);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D318);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D3E0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D5C0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D718);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D7B0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D848);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024D900);

extern int D_00552370[];
extern int D_00717BD8[];
extern int func_0024DD30(int a0, int a1, int a2, int a3, void *a4);

int func_0024D9B8(int a0, int a1, int a2) {
    D_00552370[0] = 0;
    return func_0024DD30(a0, a1, a2, 5, D_00717BD8);
}

int func_0024D9E8(int a0, void *a1) {
    D_00552370[0] = 1;
    return func_0024DD30(a0, 0, 0, 1, a1);
}

int func_0024DA20(int a0) {
    return func_0024DD30(a0, 0, 0, 9, D_00717BD8);
}

int func_0024DA50(int a0) {
    return func_0024DD30(a0, 0, 0, 4, D_00717BD8);
}

int func_0024DA80(void) {
    D_00552370[0] = 0;
    return func_0024DD30(0, 0, 0, 3, D_00717BD8);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024DAB8);

extern char D_0062E9C0[];

int func_0024DC40(void) {
    D_00552370[0] = 0;
    if (D_00550910[0] > 0) {
        func_001019E0(D_0062E9C0);
    }
    return func_0024DD30(0, 0, 0, 7, D_00717BD8);
}

extern char D_0062E9D8[];

int func_0024DC90(void) {
    D_00552370[0] = 1;
    if (D_00550910[0] > 0) {
        func_001019E0(D_0062E9D8);
    }
    return func_0024DD30(0, 0, 0, 8, D_00717BD8);
}

extern int D_0062E9F0[];

int func_0024DCE8(void) {
    if (D_00550910[0] > 0) {
        func_001019E0(D_0062E9F0);
    }
    return func_0024DD30(0, 0, 0, 6, D_00717BD8);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024DD30);

extern int D_0055238C[];
extern char D_0062EA48[];
extern PObjA8B8Ent D_00717C50[][4];
extern int func_001008C0(int a0);
extern int func_001008E0(void *a0, int a1);
extern void func_002642D8();
extern void func_0026F3A0(void *a0, void *a1);

void func_0024DE98(int a0, int a1) {
    struct { int *f0; int f4; int f8; int fC; char rest[0xF0]; } buf;
    int *p17 = D_00717C50[a0][a1].f4;
    int ret = func_001008C0(D_00717C50[a0][a1].fC);

    if (ret >= 0) {
        if (D_0055238C[0] != 0) {
            func_002642D8(D_0062EA48);
        }
    } else {
        int n = *p17 + 1;
        int v = D_00717C50[a0][a1].f8 + ((n & 1) << 5);
        int r;
        *p17 = n;
        func_0026F3A0(p17, (char *) p17 + 0x20);
        buf.f0 = p17;
        buf.f4 = v;
        buf.f8 = 0x20;
        buf.fC = 0;
        r = func_001008E0(&buf, 1);
        if (r == 0) {
            if (D_0055238C[0] != 0) {
                func_002642D8(D_0062EA48);
            }
        }
        D_00717C50[a0][a1].fC = r;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024DFC8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E108);

extern int D_00552388[];
extern int D_00717C00[];
extern int D_00717F40[];

int func_0024E1A8(void) {
    int ret;
    int val;
    D_00717F40[0] = 0xF;
    ret = func_00246458(D_00717C00, 1, 0, D_00717F40, 0x80, D_00717F40, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_00717F40[3];
    if (val == 1) {
        D_00552388[0] = 0;
    }
    return val;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E228);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E410);

int func_0024E4C8(int a0, int a1) {
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_00717C50 + a1 * 0x1C + a0 * 0x70);
    func_0026F3A0((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}

int func_0024E528(int a0, int a1) {
    int ret = 0;
    if (D_00717C50[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(func_0024E4C8(a0, a1) + 0x58);
}

extern int func_00264128(char *a0, char *a1, int a2);

int func_0024E578(int a0, int a1, int a2) {
    int s0;
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    s0 = func_0024E4C8(a0, a1);
    func_00264128(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}

int func_0024E5F8(int a0, int a1) {
    unsigned char *p;
    if (D_00717C50[a0][a1].f10 == 0) return 0x63;
    p = (unsigned char *)func_0024E4C8(a0, a1);
    if (p[0x70] != 6) return p[0x70];
    if (p[0x71] == 2) return 5;
    return p[0x70];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E670);

int func_0024E6A8(int a0, int a1, int a2) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    ((unsigned char *)func_0024E4C8(a0, a1))[0x71] = a2;
    return 1;
}

int func_0024E710(int a0, int a1) {
    if (D_00717C50[a0][a1].f10 == 0) {
        return 0;
    }
    return ((unsigned char *)func_0024E4C8(a0, a1))[0x71];
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E760);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E798);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24AAC8", func_0024E8B8);
