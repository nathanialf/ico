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

extern char D_00718040[];
extern int func_00100570(int sema);
extern void func_00100540(int sema);
extern int func_00246458();

/* Take the device lock, refuse if the device is not open, publish the
 * argument into the shared request block and submit it.  On success the
 * lock is HELD (the completion path releases it) and the request tag is
 * recorded; on failure it is released here. */
int func_0024F428(int arg) {
    char *dev;
    char *blk;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    blk = D_00718040;
    *(int *)(blk + 0x14) = arg;
    r = func_00246458(dev, 0x14, 1, blk, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0x14;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* Query variant of the device-request template: on success the reply word
 * is read back out of the shared reply block rather than a tag recorded. */
int func_0024F4E0(int arg) {
    char *dev;
    char *blk;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    blk = D_00718040;
    *(int *)(blk + 4) = arg;
    r = func_00246458(dev, 0x15, 0, blk, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        func_00100540(D_005523D4[0]);
        return r;
    }
    func_00100540(D_005523D4[0]);
    return *(int *)D_00719580;
}

extern char *func_00265570(char *dst, const char *src, int n);

/* The name-carrying request block: a 0x14-byte header followed by a
 * 0x400-byte name, submitted whole (0x414). */
typedef struct {
    int f0;
    int f4;
    int f8;
    int fC;
    int f10;
    char name[0x400];
} NameReq;

extern NameReq D_00718070;

/* String sub-template, copy-first form, with a third header word. */
int func_0024F5A0(int a0, int a1, int a2, int a3) {
    char *name = (char *)a2;
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.f0 = a0;
    D_00718070.f8 = a3;
    D_00718070.f4 = a1;
    D_00718070.name[0x3FF] = 0;
    r = func_00246458(dev, 2, 1, &D_00718070, 0x414, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 2;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

extern int func_0024F5A0(int a0, int a1, int a2, int a3);

int func_0024F6D8(int a0, int a1, int a2) {
    int ret = func_0024F5A0(a0, a1, a2, 0x40);
    if (ret == 0) {
        *(int *)D_005523D0 = 0xB;
    }
    return ret;
}

/* Take the device lock, refuse if the device is not open, publish the
 * argument into the shared request block and submit it.  On success the
 * lock is HELD (the completion path releases it) and the request tag is
 * recorded; on failure it is released here. */
int func_0024F710(int arg) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    *(int *)D_00718040 = arg;
    r = func_00246458(dev, 0x3, 1, D_00718040, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0x3;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* Three-argument variant of the device-request template. */
int func_0024F7C8(int a0, int a1, int a2) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    *(int *)D_00718040 = a0;
    *(int *)(D_00718040 + 0x10) = a1;
    *(int *)(D_00718040 + 0x14) = a2;
    r = func_00246458(dev, 4, 1, D_00718040, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 4;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024F8A0);

extern char D_007184C0[];
extern int func_0024F8A0();

/* Plain (0x30) sub-template with a caller buffer AND a completion
 * callback: both the caller's buffer and the fixed 0xC0 reply area are
 * flushed out of cache before submission -- the peer touches both by DMA
 * -- and the reply area doubles as the callback's cookie. */
int func_0024F930(int a0, void *buf, int len) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    *(int *)D_00718040 = a0;
    *(int *)(D_00718040 + 0x1C) = (int)D_007184C0;
    *(int *)(D_00718040 + 0x18) = (int)buf;
    *(int *)(D_00718040 + 0xC) = len;
    func_0024BEF8(buf, len);
    func_0024BEF8(D_007184C0, 0xC0);
    r = func_00246458(dev, 5, 1, D_00718040, 0x30, D_00719580, 4,
                      func_0024F8A0, D_007184C0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 5;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_24E9D8", func_0024FA50);

extern void func_00100F18(int a0);

void func_0024FBD0(int a0, int a1, int a2) {
    func_00100F18(a2);
    SYNC();
    EI();
}

extern int func_001002A0(int a0, void *a1, int a2);
extern int func_00100410(void);
extern void func_00100440(void);
extern void func_0024FBD0();

void func_0024FBF8(int a0) {
    func_001002A0(a0 & 0xFFFF, func_0024FBD0, func_00100410());
    func_00100440();
}

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

extern void func_0024BEF8(void *addr, int len);

/* String sub-template, header-first form, with a data buffer: when the
 * caller supplies a non-negative block count the buffer is flushed out of
 * the cache before the request is submitted, because the peer reads it by
 * DMA.  The count is in 64-byte blocks (`sll $5,$17,6`). */
int func_0024FF00(int a0, int a1, char *name, int a3, int nblk, void *buf) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    D_00718070.f0 = a0;
    D_00718070.f4 = a1;
    D_00718070.f8 = a3;
    D_00718070.fC = nblk;
    D_00718070.f10 = (int)buf;
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.name[0x3FF] = 0;
    if (nblk >= 0) {
        func_0024BEF8(buf, nblk * 64);
    }
    r = func_00246458(dev, 0xD, 1, &D_00718070, 0x414, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0xD;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

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

extern char D_00718580[];

/* String sub-template with a fixed 0x400 reply buffer and a COMPLETION
 * CALLBACK: the request names func_00250058 as its 8th argument and passes
 * the caller's cookie as the 9th (the stack word every other member of the
 * family leaves zero).  The buffer is flushed out of the cache first --
 * the peer fills it by DMA. */
int func_002500E0(int a0, int a1, char *name, int cookie) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    D_00718070.f0 = a0;
    D_00718070.f10 = (int)D_00718580;
    D_00718070.f4 = a1;
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.name[0x3FF] = 0;
    func_0024BEF8(D_00718580, 0x400);
    r = func_00246458(dev, 0xC, 1, &D_00718070, 0x414, D_00719580, 4,
                      func_00250058, cookie);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0xC;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* Two-argument variant of the device-request template. */
int func_00250230(int a0, int a1) {
    char *dev;
    char *blk;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    blk = D_00718040;
    *(int *)(blk + 4) = a0;
    *(int *)(blk + 8) = a1;
    r = func_00246458(dev, 0x10, 1, blk, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0x10;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}


/* String variant of the device-request template: refuses an absent or
 * empty name with its own error, copies the name into the request block,
 * then submits it. */
int func_002502F8(int a0, int a1, char *name) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.f0 = a0;
    D_00718070.f4 = a1;
    D_00718070.name[0x3FF] = 0;
    D_00718070.f8 = 0;
    r = func_00246458(dev, 0xF, 1, &D_00718070, 0x414, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0xF;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* Take the device lock, refuse if the device is not open, publish the
 * argument into the shared request block and submit it.  On success the
 * lock is HELD (the completion path releases it) and the request tag is
 * recorded; on failure it is released here. */
int func_00250420(int arg) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    *(int *)D_00718040 = arg;
    r = func_00246458(dev, 0xA, 1, D_00718040, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0xA;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* The auxiliary block the two-name members point the main request at: a
 * 0x20-byte header followed by a 0x20-byte name. */
typedef struct {
    char f0[0x20];
    char name[0x20];
} AuxReq;

extern AuxReq D_00718000;
extern void func_001007A0(int a0);

/* String sub-template carrying a whole 0x40-byte auxiliary block copied in
 * from the caller.  AuxReq is all-char, so its alignment is 1 and the
 * struct assignment compiles to the unaligned ldl/ldr + sdl/sdr sequence
 * the ROM has (COOKBOOK §6.1). */
int func_002504D8(int a0, int a1, char *name, void *src, int flags) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    flags &= 7;
    D_00718070.f0 = a0;
    D_00718070.f4 = a1;
    D_00718070.f8 = flags;
    D_00718000 = *(AuxReq *)src;
    D_00718070.f10 = (int)&D_00718000;
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.name[0x3FF] = 0;
    func_001007A0(0);
    r = func_00246458(dev, 0xE, 1, &D_00718070, 0x414, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0xE;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}


/* String sub-template carrying a SECOND name in its own block. */
int func_002506B0(int a0, int a1, char *name, char *name2) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name == 0) {
        goto badname;
    }
    if (name2 != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    D_00718070.f0 = a0;
    D_00718070.f4 = a1;
    D_00718070.f8 = 0x10;
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.name[0x3FF] = 0;
    func_00265570(D_00718000.name, name2, 0x20);
    D_00718000.name[0x1F] = 0;
    D_00718070.f10 = (int)&D_00718000;
    func_001007A0(0);
    r = func_00246458(dev, 0xE, 1, &D_00718070, 0x414, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0x13;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* Two-argument variant of the device-request template. */
int func_00250818(int a0, int a1) {
    char *dev;
    char *blk;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    blk = D_00718040;
    *(int *)(blk + 4) = a0;
    *(int *)(blk + 8) = a1;
    r = func_00246458(dev, 0x11, 1, blk, 0x30, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0x11;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

/* Sibling of func_002502F8: same string variant, but the header words are
 * written BEFORE the name copy and there is no third word to clear. */
int func_002508E0(int a0, int a1, char *name) {
    char *dev;
    int r;
    if (func_00100570(D_005523D4[0]) < 0) {
        return -0xC8;
    }
    dev = D_00717FC0;
    if (*(int *)(dev + 0x24) == 0) {
        func_00100540(D_005523D4[0]);
        return -0x64;
    }
    if (name == 0) {
        goto badname;
    }
    if (*name != 0) {
        goto ok;
    }
badname:
    func_00100540(D_005523D4[0]);
    return -0xD2;
ok:
    D_00718070.f0 = a0;
    D_00718070.f4 = a1;
    func_00265570(D_00718070.name, name, 0x3FF);
    D_00718070.name[0x3FF] = 0;
    r = func_00246458(dev, 0x12, 1, &D_00718070, 0x414, D_00719580, 4, 0, 0);
    if (r != 0) {
        goto unlock;
    }
    *(int *)D_005523D0 = 0x12;
    goto done;
unlock:
    func_00100540(D_005523D4[0]);
done:
    return r;
}

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
