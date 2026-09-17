/* Vendor SCE library run.  The archive attribution (libpad.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"
#include <sifrpc.h>
#include <libpad.h>
#include <stdio.h>
#include <eekernel.h>
#include <string.h>

struct S12 {
    char b[12];
};

typedef struct {
    int f0;
    int *f4;
    int f8;
    int fC;
    int f10;
    int f14;
    int f18;
} PObjA8B8Ent;

extern int D_0054BFC8[];
extern int D_0054BFCC[];
extern int D_0072F200[];
extern char D_00636B80[];
extern char D_00636BA8[];

int scePadInit(int a0)
{
    int ver;
    int major;
    int i;

    D_0054BFC8[0] = 1;
    while (1) {
        sceSifBindRpc(D_0072F200, 0x80000100, 0);
        if (D_0072F200[9] != 0) {
            break;
        }
        for (i = 0x10000; i != -1; i--) {}
    }
    while (1) {
        sceSifBindRpc(&D_0072F200[10], 0x80000101, 0);
        if (D_0072F200[19] != 0) {
            break;
        }
        for (i = 0x10000; i != -1; i--) {}
    }
    ver = scePadGetModVersion();
    major = ver >> 8;
    if (major != 4) {
        if (D_0054BFCC[0] != 0) {
            printf(D_00636B80);
            printf(D_00636BA8, 4, 0, major, ver & 0xFF);
        }
        return 0;
    }
    return scePadInit2(a0);
}

extern PObjA8B8Ent D_0072F250[][4];
extern int D_0072F200[];
extern int D_0072F540[];

int scePadInit2(int a0)
{
    int ret;
    int i;

    for (i = 0; i < 4; i++) {
        D_0072F250[0][i].f10 = 0;
        D_0072F250[0][i].f18 = 0;
        D_0072F250[0][i].f14 = 0;
        D_0072F250[1][i].f10 = 0;
        D_0072F250[1][i].f18 = 0;
        D_0072F250[1][i].f14 = 0;
    }
    D_0072F540[0] = 0x10;
    D_0072F540[4] = 0;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}

extern int D_0054BFC8[];
extern int D_0072F200[];
extern int D_0072F540[];

int scePadEnd(void)
{
    int ret;
    int val;
    D_0072F540[0] = 0xF;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_0072F540[3];
    if (val == 1) {
        D_0054BFC8[0] = 0;
    }
    return val;
}

INCLUDE_ASM("asm/nonmatchings/sce/libpad/libpad", scePadPortOpen);

int scePadPortClose(int a0, int a1)
{
    int ret;

    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    D_0072F540[0] = 0xE;
    D_0072F540[1] = a0;
    D_0072F540[2] = a1;
    D_0072F540[4] = 1;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    D_0072F250[a0][a1].f10 = 0;
    return D_0072F540[3];
}

extern PObjA8B8Ent D_0072F250[][4];

int scePadGetDmaStr(int a0, int a1)
{
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_0072F250 + a1 * 0x1C + a0 * 0x70);
    SyncDCache((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}

int scePadGetFrameCount(int a0, int a1)
{
    int ret = 0;
    if (D_0072F250[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(scePadGetDmaStr(a0, a1) + 0x58);
}

int scePadRead(int a0, int a1, int a2)
{
    int s0;
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    s0 = scePadGetDmaStr(a0, a1);
    memcpy(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}

int scePadGetState(int a0, int a1)
{
    unsigned char *p;
    if (D_0072F250[a0][a1].f10 == 0)
        return 0x63;
    p = (unsigned char *)scePadGetDmaStr(a0, a1);
    if (p[0x70] != 6)
        return p[0x70];
    if (p[0x71] == 2)
        return 5;
    return p[0x70];
}

extern char *D_0054BFD0[];
extern char D_00636C58[];

void scePadStateIntToStr(unsigned int a0, char *a1)
{
    if (a0 < 8) {
        strcpy(a1, D_0054BFD0[a0]);
    } else {
        *a1 = D_00636C58[0];
    }
}

int scePadSetReqState(int a0, int a1, int a2)
{
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71] = a2;
    return 1;
}

int scePadGetReqState(int a0, int a1)
{
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71];
}

extern char *D_0054BFF0[];
extern char D_00636C58[];

void scePadReqIntToStr(unsigned int a0, char *a1)
{
    if (a0 < 4) {
        strcpy(a1, D_0054BFF0[a0]);
    } else {
        *a1 = D_00636C58[0];
    }
}

INCLUDE_ASM("asm/nonmatchings/sce/libpad/libpad", scePadInfoAct);
INCLUDE_ASM("asm/nonmatchings/sce/libpad/libpad", scePadInfoComb);

int scePadInfoMode(int a0, int a1, int a2, int a3)
{
    int q;
    int t72;
    int v;

    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    q = scePadGetDmaStr(a0, a1);
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

int scePadSetMainMode(int a0, int a1, int a2, int a3)
{
    int *s0 = D_0072F540;
    int local = 0;
    int ret;
    int s;
    D_0072F540[0] = 6;
    s0[1] = a0;
    s0[2] = a1;
    s0[3] = a2;
    s0[4] = a3;
    ret = sceSifCallRpc((int)D_0072F200, 1, 0, (int)s0, 0x80, (int)s0, 0x80, 0, local);
    if (ret < 0) {
        return 0;
    }
    s = s0[5];
    if (s == 1) {
        scePadSetReqState(a0, a1, 2);
        s = s0[5];
    }
    return s;
}

extern void _send_to_iop(int a0, int a1);

int scePadSetActDirect(int a0, int a1, unsigned char *a2)
{
    int *p;
    unsigned char *q;
    int i;

    if (((unsigned char *)scePadGetDmaStr(a0, a1))[0x72] != 1) {
        return 0;
    }
    p = D_0072F250[a0][a1].f4;
    q = (unsigned char *)p + 0xC;
    for (i = 0; i < 6; i++) {
        q[i] = a2[i];
    }
    p[2] = 6;
    p[1] = 1;
    _send_to_iop(a0, a1);
    return 1;
}

int scePadSetActAlign(int a0, int a1, char *a2)
{
    int *s0 = D_0072F540;
    int i;
    int val;
    int *new_var;
    int ret;
    char *dst;
    D_0072F540[0] = 8;
    new_var = D_0072F540;
    s0[1] = a0;
    s0[2] = a1;
    dst = (char *)s0 + 0xC;
    for (i = 0; i < 6; i++) {
        dst[i] = a2[i];
    }
    ret = sceSifCallRpc(D_0072F200, 1, 0, new_var, 0x80, new_var, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        scePadSetReqState(a0, a1, 2);
        val = s0[5];
    }
    return val;
}

int scePadGetButtonMask(int a0, int a1)
{
    unsigned char *p;

    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    p = (unsigned char *)scePadGetDmaStr(a0, a1);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x64] < 2) {
        return 0;
    }
    if (p[0x66] < 2) {
        return 0;
    }
    return (long long)p[0x79] + ((long long)p[0x7A] << 8) + ((long long)p[0x7B] << 16) +
           ((long long)p[0x7C] << 24);
}

int scePadSetButtonInfo(int a0, int a1, int a2)
{
    int ret;
    D_0072F540[3] = a2;
    D_0072F540[0] = 0xA;
    D_0072F540[1] = a0;
    D_0072F540[2] = a1;
    if (sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0) < 0) {
        return 0;
    }
    ret = D_0072F540[4];
    if (ret == 1) {
        scePadSetReqState(a0, a1, 2);
        ret = D_0072F540[4];
    }
    return ret;
}

int scePadInfoPressMode(int a0, int a1)
{
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadGetButtonMask(a0, a1) == 0x3FFFF;
}

int scePadEnterPressMode(int a0, int a1)
{
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0xFFF);
}

int scePadExitPressMode(int a0, int a1)
{
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0);
}

int scePadSetVrefParam(int a0, int a1, void *a2)
{
    int r;
    D_0072F540[1] = a0;
    D_0072F540[0] = 0xB;
    D_0072F540[2] = a1;
    *(struct S12 *)((char *)D_0072F540 + 0xC) = *(struct S12 *)a2;
    r = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    if (D_0072F540[7] == 1) {
        scePadSetReqState(a0, a1, 2);
    }
    return D_0072F540[7];
}

int scePadGetPortMax(void)
{
    int ret;
    D_0072F540[0] = 0xC;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}

int scePadGetSlotMax(int a0)
{
    int ret;
    D_0072F540[0] = 0xD;
    D_0072F540[1] = a0;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}

int scePadGetModVersion(void)
{
    int ret;
    D_0072F540[0] = 0x12;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}

int scePadSetWarningLevel(int a0)
{
    int ret;
    D_0072F540[0] = 0x14;
    D_0072F540[1] = a0;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[2];
}
