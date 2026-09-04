#include "common.h"


extern int D_0055C720[];
extern int D_00633DE0;
extern void debug_StdPrintfDummy();
INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A7E8);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A8F0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019A9A0);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AA20);

extern void MakeRefractTexture(float f);

void func_0019AE50(void *a0)
{
    char *q = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);

    if (*(char *)(q + 0x12) != 0) {
        MakeRefractTexture(1.0f - (float)*(int *)(q + 0x18) / 5.0f);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019AE98);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B660);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B7F8);

extern void *isysGObjSearchFromObjLayoutID(int id);
extern void *isysGObjSearchFromObjKindID_next(void *g);

void func_0019B888(void)
{
    void *g;

    g = isysGObjSearchFromObjLayoutID(0x2E);
    *(char *)(*(char **)(*(char **)((char *)g + 0x15C) + 0x800) + 1) = 1;

    g = isysGObjSearchFromObjLayoutID(0x35);
    while (g != 0) {
        *(char *)(*(char **)(*(char **)((char *)g + 0x15C) + 0x800) + 0x12) = 1;
        g = isysGObjSearchFromObjKindID_next(g);
    }
}


char func_0019B8E8(void)
{
    char *p = *(char **)(*(char **)((char *)isysGObjSearchFromObjLayoutID(0x2E) + 0x15C) + 0x800);

    return p[3];
}

int func_0019B910(void)
{
    char *p = *(char **)(*(char **)((char *)isysGObjSearchFromObjLayoutID(0x2E) + 0x15C) + 0x800);

    return *(int *)(p + 4);
}

float func_0019B938(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    char *q = *(char **)((char *)p + 0x800);
    return *(float *)(q + 0x14);
}

int func_0019B948(void)
{
    void *g;
    char *q;
    int rv = 0;

    g = isysGObjSearchFromObjLayoutID(0x2E);
    q = *(char **)(*(char **)((char *)g + 0x15C) + 0x800);
    if (*(int *)(q + 4) > 0 || *(int *)(q + 8) > 0) {
        rv = 1;
    }
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019B998);

int func_0019BA60(void)
{
    void *g;
    int rv = 0;

    g = isysGObjSearchFromObjLayoutID(0x35);
    if (g != 0) {
        char *q = *(char **)(*(char **)((char *)g + 0x15C) + 0x800);
        rv = *(int *)(q + 0x18) < 5;
    }
    return rv;
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BAA8);

float func_0019BB40(void *a0) {
    int *p = *(int **)((char *)a0 + 0x15C);
    char *q = *(char **)((char *)p + 0x800);
    return *(float *)(q + 0x14) * 100.0f;
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BB60);

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BC58);

extern void _ACTWait(int a0);
extern void func_0019A6E8(void *a0);

void func_0019BCE0(void *volatile a0)
{
    char *q = *(char **)(*(char **)((char *)a0 + 0x15C) + 0x800);

    _ACTWait(1);
    while (1) {
        if (*q == 0) {
            func_0019A6E8(a0);
        }
        _ACTWait(1);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/queen", func_0019BD30);

void queenBallBeforeFunc(void)
{
    D_00633DE0 = 0x3C;
    debug_StdPrintfDummy(D_0055C720);
}

INCLUDE_ASM("asm/nonmatchings/src/queen", InitQueenBallGeo);

