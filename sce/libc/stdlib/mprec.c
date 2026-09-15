/* libc.a member mprec.o.  MAIN.MAP member spans tile this run exactly and
 * this member starts at an 8-aligned function start of the shipped ELF. */
#include "common.h"

typedef struct PObjBlk {
    char pad0[4];
    unsigned int size; /* 0x4 */
} PObjBlk;

struct D520 {
    char pad0[8];
    PObjBlk *blk; /* 0x8 */
};

typedef struct {
    char *pos; /* 0x0 */
    int len;   /* 0x4 */
} StreamBuf;

extern int D_0054CEAC[];
extern char D_00637E38[];
extern void fiprintf();
extern void abort(void);
extern long long strtol(void *a0, int a1, int a2);
extern int _vfprintf_r(int *self, int subj, int b, void *args);
extern int strtok_r(int a0, int a1, int a2);
extern int __sread(void *a0, int a1, int a2);
extern long __swrite(void *a0, int a1, int a2);
extern long __sseek(void *a0, int a1, int a2);
extern void *_malloc_r(void *a0, int a1);
extern void memset(void *a0, int a1, int a2);
extern void _fwalk(int a0, void *a1);
extern int memcpy(char *a0, char *a1, int a2);
extern long long __muldi3(long long a0, long long a1);
extern long long __udivdi3(long long a0, long long a1);
extern int strcmp(int *p, int *buf);

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _Balloc);

void _Bfree(char *a0, int *a1)
{
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

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _multadd);

extern int *_Balloc(void *a0, int a1);
extern int *_multadd(void *a0, int *a1, int a2, int a3);

int _s2b(void *a0, char *a1, int a2, int a3, int a4)
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
    r5 = _Balloc(a0, five);
    i17 = 9;
    r5[5] = a4;
    r5[4] = 1;
    if (i18 == 0) {
        a1 += 9;
        do {
            i17++;
            r5 = _multadd(a0, r5, 10, a1[0] - 0x30);
            a1++;
        } while (i17 < a2);
        a1++;
    } else {
        a1 += 10;
    }
    if (i17 < a3) {
        i17 = a3 - i17;
        do {
            r5 = _multadd(a0, r5, 10, a1[0] - 0x30);
            a1++;
            i17--;
        } while (i17 != 0);
    }
    return (int)r5;
}

int _hi0bits(unsigned int a0)
{
    int n = 0;
    if ((a0 & 0xFFFF0000) == 0) {
        n = 16;
        a0 <<= 16;
    }
    if ((a0 & 0xFF000000) == 0) {
        n += 8;
        a0 <<= 8;
    }
    if ((a0 & 0xF0000000) == 0) {
        n += 4;
        a0 <<= 4;
    }
    if ((a0 & 0xC0000000) == 0) {
        n += 2;
        a0 <<= 2;
    }
    if ((int)a0 >= 0) {
        n += 1;
        if ((a0 & 0x40000000) == 0) {
            return 0x20;
        }
    }
    return n;
}

int _lo0bits(int *p)
{
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

void *_i2b(void *a0, int a1)
{
    int *r = _Balloc(a0, 1);
    r[5] = a1;
    r[4] = 1;
    return r;
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _multiply);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _pow5mult);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _lshift);

int __mcmp(unsigned int *a, unsigned int *b)
{
    int n = a[4] - b[4];
    unsigned int *pa, *pb, *pae, *pbe;
    if (n != 0)
        return n;
    n = b[4];
    pa = a + 5;
    pb = b + 5;
    pae = pa + n;
    pbe = pb + n;
    do {
        --pae;
        --pbe;
        if (*pae != *pbe)
            return (*pae < *pbe) ? -1 : 1;
    } while (pa < pae);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", __mdiff);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _ulp);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _b2d);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _d2b);
INCLUDE_ASM("asm/nonmatchings/sce/libc/stdlib/mprec", _ratio);

extern const long D_006388A0[];
extern long dpmul(long a, long b);

long _mprec_log10(int n)
{
    long acc = (long)0xFFC0 << 46;
    if (n < 0x18) {
        return D_006388A0[n];
    }
    while (n > 0) {
        acc = dpmul(acc, (long)0x8048 << 47);
        n--;
    }
    return acc;
}

extern int _raise_r(int a0, int a1);
extern int __sigtramp_r(int a0, int a1);
extern int kill(int a0, void *a1);
extern int _read_r(int *self, int a1, int a2, int a3);
extern int _lseek_r(int *self, int a1, int a2, int a3);
extern int _write_r(int *self, int a1, int a2, int a3);
extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);
extern int write(int a1, int a2, int a3);
extern int fstat(void *a0, void *a1);
extern int lseek(int a1, int a2, int a3);
extern int read(int a1, int a2, int a3);
