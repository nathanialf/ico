#include "common.h"


extern int EnableMotionOrientUpdate();
extern int ForMotionViewer_GetCurrentMotion();
extern int D_00631990;
INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC6C8);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FC780);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_001FCA20);

INCLUDE_ASM("asm/nonmatchings/src/act-env", func_00200848);

extern void func_00243AD0(float *a0, float *a1, float *a2);
extern void func_00243B18(float *a0, float *a1, float f12);
extern char D_0061AD10[];
extern int D_00631AE4;
extern void func_002438B8(void *a0, void *a1, void *a2);
union ENVLL { long long ll; };
union ENVIF { int i; float f; };
void func_00200970(void *a0, void *a1)
{
    float W[4] __attribute__((aligned(16)));
    char *m6;
    char *w70 = (char *)W;
    ((union ENVLL *)w70)->ll = *(long long *)&D_0061AD10[0];
    ((union ENVLL *)(w70 + 8))->ll = *(long long *)&D_0061AD10[8];
    m6 = *(char **)((char *)a0 + 0x164);
    {
        float t0 = *(float *)(m6 + 0x4A0);
        float t1 = *(float *)(m6 + 0x4A4);
        float t2 = *(float *)(m6 + 0x4A8);
        *(float *)(m6 + 0x550) = t0;
        *(float *)(m6 + 0x554) = t1;
        *(float *)(m6 + 0x558) = t2;
    }
    if ((char *)a0 == (char *)D_00631AE4) *(float *)w70 = -*(float *)w70;
    {
        char *bx = *(char **)((char *)a1 + 0x15C);
        void *hp = (void *)*(int *)(bx + 0xC);
        ((union ENVIF *)(w70 + 0xC))->f = 1.0f;
        func_002438B8(m6 + 0x5A0, hp, w70);
    }
}

void func_002009F0(void *a0, void *a1, void *a2)
{
    float acc[4] __attribute__((aligned(16)));
    char *w;
    int i;
    acc[0] = 0;
    acc[1] = 0;
    acc[2] = 0;
    i = 3;
    w = (char *)a2;
    do {
        func_00243AD0(acc, acc, (float *)w);
        w += 0x10;
        i--;
    } while (i >= 0);
    func_00243B18((float *)a0, acc, 0.25f);
    if (a1 != 0) {
        ((union ENVIF *)((char *)a0 + 0xC))->f = 1.0f;
        func_002438B8(a0, (void *)*(int *)(*(char **)((char *)a1 + 0x15C) + 0xC), a0);
    }
}

int func_00200A98(int a0)
{
    unsigned char v0;
    if (D_00631990 == 4) {
        v0 = EnableMotionOrientUpdate(a0, 0x1000);
    } else {
        v0 = ForMotionViewer_GetCurrentMotion(a0, 0x1000);
    }
    return v0 & 0xFF;
}

