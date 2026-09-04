#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

struct S12 { char b[12]; };

typedef struct { int f0; int *f4; int f8; int fC; int f10; char pad14[0x8]; } PObjA8B8Ent;

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadInit);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadInit2);
extern int D_0054BFC8[];
extern int D_0072F200[];
extern int D_0072F540[];
extern int sceSifCallRpc();

int scePadEnd(void) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadPortOpen);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadPortClose);
extern PObjA8B8Ent D_0072F250[][4];
extern void SyncDCache(void *a0, void *a1);

int scePadGetDmaStr(int a0, int a1) {
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_0072F250 + a1 * 0x1C + a0 * 0x70);
    SyncDCache((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}
int scePadGetFrameCount(int a0, int a1) {
    int ret = 0;
    if (D_0072F250[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(scePadGetDmaStr(a0, a1) + 0x58);
}
extern int memcpy(char *a0, char *a1, int a2);

int scePadRead(int a0, int a1, int a2) {
    int s0;
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    s0 = scePadGetDmaStr(a0, a1);
    memcpy(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}
int scePadGetState(int a0, int a1) {
    unsigned char *p;
    if (D_0072F250[a0][a1].f10 == 0) return 0x63;
    p = (unsigned char *)scePadGetDmaStr(a0, a1);
    if (p[0x70] != 6) return p[0x70];
    if (p[0x71] == 2) return 5;
    return p[0x70];
}
extern char *D_0054BFD0[];
extern char D_00636C58[];
void scePadStateIntToStr(unsigned int a0, char *a1) {
    if (a0 < 8) {
        strcpy(a1, D_0054BFD0[a0]);
    } else {
        *a1 = D_00636C58[0];
    }
}
int scePadSetReqState(int a0, int a1, int a2) {
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71] = a2;
    return 1;
}
int scePadGetReqState(int a0, int a1) {
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71];
}
extern char *D_0054BFF0[];
extern char D_00636C58[];
void scePadReqIntToStr(unsigned int a0, char *a1) {
    if (a0 < 4) {
        strcpy(a1, D_0054BFF0[a0]);
    } else {
        *a1 = D_00636C58[0];
    }
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadInfoAct);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadInfoComb);
int scePadInfoMode(int a0, int a1, int a2, int a3) {
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
int scePadSetMainMode(int a0, int a1, int a2, int a3) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadSetActDirect);
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_267C00", scePadGetButtonMask);
int scePadSetButtonInfo(int a0, int a1, int a2) {
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
extern int scePadGetButtonMask(int a0, int a1);

int scePadInfoPressMode(int a0, int a1) {
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadGetButtonMask(a0, a1) == 0x3FFFF;
}
int scePadEnterPressMode(int a0, int a1) {
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0xFFF);
}
int scePadExitPressMode(int a0, int a1) {
    if (D_0072F250[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0);
}
int scePadSetVrefParam(int a0, int a1, void *a2) {
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
int scePadGetPortMax(void) {
    int ret;
    D_0072F540[0] = 0xC;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}
int scePadGetSlotMax(int a0) {
    int ret;
    D_0072F540[0] = 0xD;
    D_0072F540[1] = a0;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}
int scePadGetModVersion(void) {
    int ret;
    D_0072F540[0] = 0x12;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[3];
}
int scePadSetWarningLevel(int a0) {
    int ret;
    D_0072F540[0] = 0x14;
    D_0072F540[1] = a0;
    ret = sceSifCallRpc(D_0072F200, 1, 0, D_0072F540, 0x80, D_0072F540, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_0072F540[2];
}
