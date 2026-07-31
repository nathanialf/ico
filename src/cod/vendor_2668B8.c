#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size;  /* 0x4 */
} PObjBlk;
struct D520 {
    char pad0[8];
    PObjBlk *blk;       /* 0x8 */
};

typedef struct {
    char *pos;   /* 0x0 */
    int len;     /* 0x4 */
} StreamBuf;

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_002668B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00266970);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_002669E8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00267F00);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_002680B0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00268190);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00268C98);

extern int D_00553244[];
extern int func_00266970();

int func_00268DA0(void *out, void *a1, void *a2) {
    char s[0x60];
    int n;
    *(void **)(s + 0x0) = out;
    *(int *)(s + 0x8) = 0x7FFFFFFF;
    *(short *)(s + 0xC) = 0x208;
    *(void **)(s + 0x10) = out;
    *(int *)(s + 0x14) = 0x7FFFFFFF;
    *(int *)(s + 0x54) = D_00553244[0];
    n = func_00266970(s, a1, a2);
    *(char *)(*(void **)(s + 0x0)) = 0;
    return n;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00268DF8);

/* Both callees are declared elsewhere in this TU with signatures that
 * contradict the ones this loop needs; bind correctly-typed names to the
 * same symbols. */
extern void func_0026D430_1(int a0) __asm__("func_0026D430");
extern void func_001000B8_1(int a0) __asm__("func_001000B8");

void func_00268F08(void) {
    for (;;) {
        func_0026D430_1(6);
        func_001000B8_1(1);
    }
}

/* The sibling below declares this callee with one argument; the kernel
 * entry takes two, so bind a correctly-typed name to the same symbol. */
extern int func_0026E5C8_2(int a0, int a1) __asm__("func_0026E5C8");

int func_00268F28(int a0) {
    return func_0026E5C8_2(a0, 0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00268F48);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_00269160);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026A330);

extern int func_0026D558();
extern long func_0026D5C0(void *a0, int a1, int a2);
extern long func_0026D640(void *a0, int a1, int a2);
extern int func_0026D6A8(void *a0);

void func_0026A438(char *a0, short a1, short a2, int a3) {
    *(int *)(a0 + 0x54) = a3;
    *(short *)(a0 + 0xC) = a1;
    *(short *)(a0 + 0xE) = a2;
    *(void **)(a0 + 0x20) = (void *)func_0026D558;
    *(void **)(a0 + 0x24) = (void *)func_0026D5C0;
    *(void **)(a0 + 0x28) = (void *)func_0026D640;
    *(void **)(a0 + 0x2C) = (void *)func_0026D6A8;
    *(int *)(a0 + 0x4) = 0;
    *(int *)(a0 + 0x8) = 0;
    *(int *)(a0 + 0x10) = 0;
    *(int *)(a0 + 0x18) = 0;
    *(char **)(a0 + 0x1C) = a0;
    *(int *)(a0 + 0x0) = 0;
}

extern void func_002641D8(void *a0, int a1, int a2);
extern void *func_0026B548(void *a0, int a1);

void *func_0026A490(void *a0, int a1) {
    int sz;
    char *p;
    char *body;
    sz = a1 * 0x58;
    p = (char *)func_0026B548(a0, sz + 0xC);
    if (p == 0) {
        return 0;
    }
    body = p + 0xC;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x8) = (int)body;
    func_002641D8(body, 0, sz);
    return p;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026A500);

extern int func_0026A330(void);
extern void func_0026B018(int a0, void *a1);

void func_0026A5E0(int a0) {
    func_0026B018(a0, func_0026A330);
}

extern int D_00553244[];
extern void func_0026A5E0(int a0);

void func_0026A5F0(void) {
    func_0026A5E0(D_00553244[0]);
}

void func_0026A600(char *a0) {
    char *p = a0 + 0x1E4;
    *(void **)(a0 + 0x3C) = (void *)func_0026A5E0;
    *(int *)(a0 + 0x38) = 1;
    func_0026A438(p, 4, 0, (int)a0);
    func_0026A438(a0 + 0x23C, 9, 1, (int)a0);
    func_0026A438(a0 + 0x294, 0xA, 2, (int)a0);
    *(char **)(a0 + 0x1E0) = p;
    *(int *)(a0 + 0x1DC) = 3;
    *(int *)(a0 + 0x1D8) = 0;
}

extern int func_00264128(char *a0, char *a1, int a2);
extern int func_0026CF30(StreamBuf *s);

int func_0026A690(char *dst, int size, int count, StreamBuf *s) {
    unsigned int total = count * size;
    int len;
    unsigned int avail;
    unsigned int total_orig;
    char *p;

    if (total == 0) {
        return 0;
    }
    len = s->len;
    if (len < 0) {
        s->len = 0;
        len = 0;
    }
    avail = len;
    total_orig = total;
    p = dst;
    if (avail < total) {
        do {
            func_00264128(p, s->pos, avail);
            total -= avail;
            p += avail;
            s->pos += avail;
            if (func_0026CF30(s) != 0) {
                return (total_orig - total) / size;
            }
            avail = s->len;
        } while (avail < total);
    }
    func_00264128(p, s->pos, total);
    s->len -= total;
    s->pos += total;
    return count;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026A7B0);

extern int D_0054D938_a[] __asm__("D_00553678");
extern int D_0054D950_a[] __asm__("D_00553690");
extern struct D520 D_00553260;
extern long long func_00261BA8(long long a0, long long a1);
extern long long func_00261C08(long long a0, long long a1);
extern void func_0026BEE0(void);
extern void func_0026BEE8__p4(void *self) __asm__("func_0026BEE8");
extern int func_0026D128(int *self, int a1);

int func_0026AAD0(int *self, unsigned int a1) {
    long long A;
    long long need;
    long long newlen;
    int r4;

    func_0026BEE0();
    A = D_00553260.blk->size & 0xFFFFFFFC;
    need = func_00261C08((A - a1) + 0xFEF, 0x1000);
    newlen = func_00261BA8(need - 1, 0x1000);
    if (newlen < 0x1000) {
        goto fail;
    }
    if (func_0026D128(self, 0) != (int)D_00553260.blk + (int)A) {
        goto fail;
    }
    if (func_0026D128(self, -(int)newlen) != 0xFFFFFFFFU) {
        goto adjust;
    }
    r4 = func_0026D128(self, 0);
    A = r4 - (int)D_00553260.blk;
    if (A >= 0x10) {
        D_0054D950_a[0] = r4 - D_0054D938_a[0];
        D_00553260.blk->size = A | 1;
    }
fail:
    func_0026BEE8__p4(self);
    return 0;
adjust:
    D_00553260.blk->size = (A - newlen) | 1;
    D_0054D950_a[0] -= (int)newlen;
    func_0026BEE8__p4(self);
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026AC40);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026B018);

extern int D_00630688[];
extern int D_00630698[];
extern int func_00265024(int *p, int *buf);

int func_0026B0B0(void *a0, int a1, int a2) {
    if (a2 == 0) goto no_check;
    if (func_00265024(a2, D_00630698) == 0) goto found;
    if (func_00265024(a2, D_00630688) != 0) return 0;
found:
    *(int *)((char *)a0 + 0x30) = a1;
    *(int *)((char *)a0 + 0x34) = a2;
no_check:
    return (int)D_00630698;
}

extern int D_00630658[];

void *func_0026B138(int a0) {
    return D_00630658;
}

extern void *D_0054D504_alias[] __asm__("D_00553244");

int func_0026B148(int a0, int a1) {
    return func_0026B0B0(D_0054D504_alias[0], a0, a1);
}

void *func_0026B178(void) {
    return func_0026B138(D_00553244[0]);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026B1A0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026B2F0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026B548);

int func_0026BCC0(int a0, int *a1, unsigned char *a2, int a3) {
    int local;
    int *p = &local;
    if (a1 != 0) p = a1;
    if (a2 == 0) goto zero;
    if (a3 != 0) goto store;
    return -1;
zero:
    return 0;
store:
    *p = *a2;
    return *a2 != 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026BCFC);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026BDDC);

void func_0026BEE0(void) {
}

void func_0026BEE8(void) {
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026BEF0);

void func_0026BF98(char *a0, int *a1) {
    if (a1) {
        int off = a1[1] * 4;
        int *slot;
        a0 = *(char **)(a0 + 0x4C);
        off += (int)a0;
        slot = (int *)off;
        a1[0] = slot[0];
        slot[0] = (int)a1;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026BFC8);

extern int *func_0026BEF0(void *a0, int a1);
extern int *func_0026BFC8(void *a0, int *a1, int a2, int a3);

int func_0026C0E0(void *a0, char *a1, int a2, int a3, int a4)
{
    int n3 = (a3 + 8) / 9;
    int p = 1;
    int five = 0;
    int i18;
    int *r5;
    int i17;

    if (p < n3) {
        do {
            p <<= 1;
            five++;
        } while (p < n3);
    }
    i18 = a2 < 10;
    r5 = func_0026BEF0(a0, five);
    i17 = 9;
    r5[5] = a4;
    r5[4] = 1;
    if (i18 == 0) {
        a1 += 9;
        do {
            i17++;
            r5 = func_0026BFC8(a0, r5, 10, a1[0] - 0x30);
            a1++;
        } while (i17 < a2);
        a1++;
    } else {
        a1 += 10;
    }
    if (i17 < a3) {
        i17 = a3 - i17;
        do {
            r5 = func_0026BFC8(a0, r5, 10, a1[0] - 0x30);
            a1++;
            i17--;
        } while (i17 != 0);
    }
    return (int)r5;
}

int func_0026C228(unsigned int a0) {
    int n = 0;
    if ((a0 & 0xFFFF0000) == 0) { n = 16; a0 <<= 16; }
    if ((a0 & 0xFF000000) == 0) { n += 8; a0 <<= 8; }
    if ((a0 & 0xF0000000) == 0) { n += 4; a0 <<= 4; }
    if ((a0 & 0xC0000000) == 0) { n += 2; a0 <<= 2; }
    if ((int)a0 >= 0) {
        n += 1;
        if ((a0 & 0x40000000) == 0) {
            return 0x20;
        }
    }
    return n;
}

int func_0026C2B0(int *p) {
    unsigned int v = *p;
    int n;
    if (v & 7) {
        if (v & 1) {
            return 0;
        }
        if (v & 2) {
            *p = v >> 1;
            return 1;
        }
        *p = v >> 2;
        return 2;
    }
    n = 0;
    if ((v & 0xFFFF) == 0) {
        n = 0x10;
        v >>= 16;
    }
    if ((v & 0xFF) == 0) {
        n += 8;
        v >>= 8;
    }
    if ((v & 0xF) == 0) {
        n += 4;
        v >>= 4;
    }
    if ((v & 3) == 0) {
        n += 2;
        v >>= 2;
    }
    if (v & 1) {
        *p = v;
    } else {
        v >>= 1;
        n += 1;
        if (v == 0) {
            return 0x20;
        }
        *p = v;
    }
    return n;
}

void *func_0026C370(void *a0, int a1) {
    int *r = func_0026BEF0(a0, 1);
    r[5] = a1;
    r[4] = 1;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026C3A8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026C5D8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026C6D8);

int func_0026C850(unsigned int *a, unsigned int *b) {
 int n = a[4] - b[4]; unsigned int *pa, *pb, *pae, *pbe;
 if (n != 0) return n;
 n = b[4]; pa = a + 5; pb = b + 5; pae = pa + n; pbe = pb + n;
 do { --pae; --pbe; if (*pae != *pbe) return (*pae < *pbe) ? -1 : 1; } while (pa < pae);
 return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026C8B8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026CA48);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026CAE0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026CC60);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026CDE0);

extern long D_006306B0[];
extern long func_00262BE8(long a, long b);

long func_0026CEA0(int n) {
    long acc = (long)0xFFC0 << 46;
    if (n < 0x18) {
        return D_006306B0[n];
    }
    while (n > 0) {
        acc = func_00262BE8(acc, (long)0x8048 << 47);
        n--;
    }
    return acc;
}

extern int func_0026A330(void);

int func_0026CF10(void) {
    return func_0026A330();
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026CF30);

int func_0026D0A8(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int)(((unsigned int)(hx | (-hx))) >> 31);
}

int func_0026D0F0(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    do { return ((unsigned int)hx) >> 31; } while (0);
}

extern int D_00633FF0[];
extern unsigned int func_002455A8(int a0);

int func_0026D128(int *self, int a1)
{
    unsigned int ret;
    D_00633FF0[0] = 0;
    ret = func_002455A8(a1);
    if (ret == 0xFFFFFFFF) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026D188);

extern int func_0026D188(int a0);

unsigned int func_0026D1F8(void *a0, int a1, int a2) {
    unsigned int *base;
    unsigned int old;
    if ((unsigned int)a1 >= 0x20) {
        *(int *)a0 = 0x16;
        return 0xFFFFFFFFU;
    }
    if (*(int *)((char *)a0 + 0x1D4) == 0) {
        if (func_0026D188((int)a0) != 0) {
            return 0xFFFFFFFFU;
        }
    }
    base = *(unsigned int **)((char *)a0 + 0x1D4);
    old = base[a1];
    base[a1] = a2;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026D288);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026D378);

extern int func_0026D288(int a0, int a1);

int func_0026D430(int a0) {
    return func_0026D288(D_00553244[0], a0);
}

int func_0026D458(int a0, int a1) {
    return func_0026D1F8(D_0054D504_alias[0], a0, a1);
}

void *func_0026D488(void) {
    return func_0026D188(D_00553244[0]);
}

extern int func_0026D378(int a0, int a1);

int func_0026D4B0(int a0) {
    return func_0026D378(D_00553244[0], a0);
}

extern int func_00245680(int a0, void *a1);

int func_0026D4D8(int *self, int a1, int a2)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_00245680(a1, a2);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

extern int func_00245678(void);

int func_0026D538(void) {
    return func_00245678();
}

extern int func_0026ED28(int *self, int a1, int a2, int a3);

int func_0026D558(void *a0, int a1, int a2) {
    long v = func_0026ED28((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
    if ((int)v >= 0) {
        *(int *)((char *)a0 + 0x50) = *(int *)((char *)a0 + 0x50) + (int)v;
    } else {
        *(unsigned short *)((char *)a0 + 0xC) = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    }
    return (int)v;
}

extern int func_0026EAF0(int *self, int a1, int a2, int a3);
extern int func_0026ECC8(int *self, int a1, int a2, int a3);

long func_0026D5C0(void *a0, int a1, int a2) {
    unsigned short flag = *(unsigned short *)((char *)a0 + 0xC);
    if (flag & 0x100) {
        func_0026ECC8((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), 0, 2);
    }
    flag = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    *(unsigned short *)((char *)a0 + 0xC) = flag;
    {
        unsigned long r = (unsigned long)func_0026EAF0((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
        return (int)r;
    }
}

long func_0026D640(void *a0, int a1, int a2) {
    unsigned long r = (unsigned long)func_0026ECC8((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
    if (r == -1) {
        *(unsigned short *)((char *)a0 + 0xC) &= 0xEFFF;
    } else {
        *(int *)((char *)a0 + 0x50) = (int)r;
        *(unsigned short *)((char *)a0 + 0xC) |= 0x1000;
    }
    return r;
}

extern int func_0026EC10(int *self, int a1);

int func_0026D6A8(void *a0) {
    return func_0026EC10((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE));
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026D6C8);

extern unsigned int func_0026D6C8(void *a0, int a1, int a2);

int func_0026E5C8(a0, a1)
int a0;
int a1;
{
    return func_0026D6C8(D_0054D504_alias[0], a0, a1);
}

extern int func_002633B8(long a0);
extern int func_0026E5C8();

int func_0026E5F8(void) {
    return func_002633B8(func_0026E5C8());
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026E620);

extern long long func_0026E620(void *a0, void *a1, int a2, int a3);

long long func_0026E840(void *a0, int a1, int a2) {
    return func_0026E620((void *)D_00553244[0], a0, a1, a2);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026E878);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026E968);

extern int func_00245470(int a1, int a2, int a3);

int func_0026EAF0(int *self, int a1, int a2, int a3)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_00245470(a1, a2, a3);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026EB50);

extern int func_00245590(int a1);

int func_0026EC10(int *self, int a1)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_00245590(a1);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

extern int func_00245660(void *a0, void *a1);

int func_0026EC68(int *self, int a1, int a2)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_00245660(a1, a2);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

extern int func_002455A0(int a1, int a2, int a3);

int func_0026ECC8(int *self, int a1, int a2, int a3)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_002455A0(a1, a2, a3);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

extern int func_002454F0(int a1, int a2, int a3);

int func_0026ED28(int *self, int a1, int a2, int a3)
{
    int ret;
    D_00633FF0[0] = 0;
    ret = func_002454F0(a1, a2, a3);
    if (ret == -1) {
        if (D_00633FF0[0] != 0) {
            self[0] = D_00633FF0[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2668B8", func_0026ED88);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0026F2F8\n"
    ".type func_0026F2F8, @function\n"
    "    .align 3\n"
    "func_0026F2F8:\n"
    "    lui $7, (0xFFFFF000 >> 16)\n"
    "    daddu $6, $0, $0\n"
    "    ori $7, $7, (0xFFFFF000 & 0xFFFF)\n"
    "    nop\n"
    ".L0026B698:\n"
    "    sync\n"
    "    cache 0x10, 0x0($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B6D4\n"
    "    nop\n"
    "    bnez $3, .L0026B6D4\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x14, 0x0($6)\n"
    "    sync\n"
    ".L0026B6D4:\n"
    "    sync\n"
    "    cache 0x10, 0x1($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B710\n"
    "    nop\n"
    "    bnez $3, .L0026B710\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x14, 0x1($6)\n"
    "    sync\n"
    ".L0026B710:\n"
    "    sync\n"
    "    addiu $6, $6, 0x40\n"
    "    slti $2, $6, 0x1000\n"
    "    bnez $2, .L0026B698\n"
    "    nop\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_0026F2F8, . - func_0026F2F8\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0026F3A0\n"
    "    .type func_0026F3A0, @function\n"
    "    .align 3\n"
    "func_0026F3A0:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd    $18, 0x20($29)\n"
    "    sd    $17, 0x10($29)\n"
    "    daddu $18, $4, $0\n"
    "    sd    $31, 0x30($29)\n"
    "    daddu $17, $5, $0\n"
    "    sd    $16, 0x0($29)\n"
    "    mfc0  $16, $12\n"
    "    lui   $2, 0x1\n"
    "    and   $16, $16, $2\n"
    "    beqz  $16, 1f\n"
    "    nop\n"
    "    jal   func_00101A40\n"
    "    nop\n"
    "1:\n"
    "    lui   $4, 0xFFFF\n"
    "    ori   $4, $4, 0xFFC0\n"
    "    and   $5, $17, $4\n"
    "    jal   func_0026F2F8\n"
    "    and   $4, $18, $4\n"
    "    beqz  $16, 2f\n"
    "    ld    $31, 0x30($29)\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    j     func_00101A88\n"
    "    addiu $29, $29, 0x40\n"
    "2:\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    jr    $31\n"
    "    addiu $29, $29, 0x40\n"
    "    .size func_0026F3A0, . - func_0026F3A0\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern void func_0026F2F8(int a0, int a1);

void func_0026F420(int a0, int a1) {
    func_0026F2F8(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0026F438\n"
    ".type func_0026F438, @function\n"
    "    .align 3\n"
    "func_0026F438:\n"
    "    lui $7, (0xFFFFF000 >> 16)\n"
    "    daddu $6, $0, $0\n"
    "    ori $7, $7, (0xFFFFF000 & 0xFFFF)\n"
    "    nop\n"
    ".L0026B7D8:\n"
    "    sync\n"
    "    cache 0x10, 0x0($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B814\n"
    "    nop\n"
    "    bnez $3, .L0026B814\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x16, 0x0($6)\n"
    "    sync\n"
    ".L0026B814:\n"
    "    sync\n"
    "    cache 0x10, 0x1($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B850\n"
    "    nop\n"
    "    bnez $3, .L0026B850\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x16, 0x1($6)\n"
    "    sync\n"
    ".L0026B850:\n"
    "    sync\n"
    "    addiu $6, $6, 0x40\n"
    "    slti $2, $6, 0x1000\n"
    "    bnez $2, .L0026B7D8\n"
    "    nop\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_0026F438, . - func_0026F438\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0026F4E0\n"
    "    .type func_0026F4E0, @function\n"
    "    .align 3\n"
    "func_0026F4E0:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd    $18, 0x20($29)\n"
    "    sd    $17, 0x10($29)\n"
    "    daddu $18, $4, $0\n"
    "    sd    $31, 0x30($29)\n"
    "    daddu $17, $5, $0\n"
    "    sd    $16, 0x0($29)\n"
    "    mfc0  $16, $12\n"
    "    lui   $2, 0x1\n"
    "    and   $16, $16, $2\n"
    "    beqz  $16, 1f\n"
    "    nop\n"
    "    jal   func_00101A40\n"
    "    nop\n"
    "1:\n"
    "    lui   $4, 0xFFFF\n"
    "    ori   $4, $4, 0xFFC0\n"
    "    and   $5, $17, $4\n"
    "    jal   func_0026F438\n"
    "    and   $4, $18, $4\n"
    "    beqz  $16, 2f\n"
    "    ld    $31, 0x30($29)\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    j     func_00101A88\n"
    "    addiu $29, $29, 0x40\n"
    "2:\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    jr    $31\n"
    "    addiu $29, $29, 0x40\n"
    "    .size func_0026F4E0, . - func_0026F4E0\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern void func_0026F438(int a0, int a1);

void func_0026F560(int a0, int a1) {
    func_0026F438(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}
