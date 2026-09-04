#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef struct PObjGObj {
    /*0x00*/ char pad00[0x4];
    /*0x04*/ int f04;
    /*0x08*/ int f08;
    /*0x0C*/ int f0C;
    /*0x10*/ char pad10[0x30];
    /*0x40*/ int f40;
    /*0x44*/ char pad44[0x4];
    /*0x48*/ int f48;
    /*0x4C*/ int f4C;
    /*0x50*/ int f50;
    /*0x54*/ char pad54[0x8];
    /*0x5C*/ int f5C;
    /*0x60*/ int f60;
    /*0x64*/ char pad64[0x100];
    /*0x164*/ int f164;
    /*0x168*/ char pad168[0x4];
    /*0x16C*/ int f16C;
} PObjGObj;

extern int D_0063C0C8;

void ResetGObjProc(void) {
    D_0063C0C8 = 0;
}
int GetMaxGObj(void) {
    return D_0063C0C8;
}
extern int D_0072A2C0[];

int GetGObjP(int idx)
{
    return D_0072A2C0[idx];
}
extern int D_0063C0C8;
extern int D_0072A2C0[];

int GetGObjId(int a0) {
    int i;
    for (i = 0; i < D_0063C0C8; i++) {
        if (a0 == D_0072A2C0[i]) {
            return i;
        }
    }
    return -1;
}
extern char D_0063C0D0[];
extern void debug_StdPrintfDummy();

void PrintGObjID(int a0) {
    int i;
    for (i = 0; i < D_0063C0C8; i++) {
        if (a0 == D_0072A2C0[i]) {
            debug_StdPrintfDummy(D_0063C0D0, i);
        }
    }
}
INCLUDE_ASM("asm/nonmatchings/src/GobjProc", InitCameraGObjs);
extern PObjGObj *D_0070C340_p[] __asm__("D_0072A2C0");
extern PObjGObj *isysGObjAdd(int a0, int a1, int a2);
extern void isysGObjKindTableAdd(void *a0, int a1);
extern void isysGObjLinkObjDL(void *a0, int a1, int a2, int a3, unsigned int a4);
extern int isysGObjProcAdd(void *a0, int a1, int a2, int a3);
extern void isysGObjProcAddS(void *a0, int a1, int a2, int a3, int a4);

PObjGObj *CreateGObj(PObjGObj *p, int a1, int a2, int a3, int a4) {
    PObjGObj *g;
    int one;
    int r21 = 0;
    int c5C, c50, c4C, c48;

    if (a4 != 0) {
        r21 = p->f40;
    }
    c5C = p->f5C;
    c50 = p->f50;
    c4C = p->f4C;
    c48 = p->f48;
    g = isysGObjAdd(p->f60, 0, 0);
    one = 1;
    g->f164 = 0;
    g->f04 = one;
    g->f16C = one;
    g->f08 = -1;
    g->f0C = -1;
    D_0070C340_p[D_0063C0C8++] = g;
    isysGObjProcAdd(g, c5C, one, 0x16);
    isysGObjProcAdd(g, c50, one, 0x17);
    isysGObjProcAdd(g, c4C, one, 0x18);
    isysGObjLinkObjDL(g, c48, 0, a3, 0xFFFFFFFF);
    if (r21 != 0) {
        isysGObjProcAddS(g, r21, 0, 0x13, 0x1800);
    }
    g->f08 = a2;
    isysGObjKindTableAdd(g, a1);
    return g;
}
INCLUDE_ASM("asm/nonmatchings/src/GobjProc", CreateGObjByFuncSet);
