#include "common.h"

#include "ico/types.h"
union ENVIF { int i; float f; };

INCLUDE_ASM("asm/nonmatchings/src/act-env", getDitchDistTbl);
INCLUDE_ASM("asm/nonmatchings/src/act-env", GetDitchPosition);
INCLUDE_ASM("asm/nonmatchings/src/act-env", DebugActOrientFlag);
INCLUDE_ASM("asm/nonmatchings/src/act-env", ACTGetEnvironment);
INCLUDE_ASM("asm/nonmatchings/src/act-env", ACTSetEnvAllmighty);
INCLUDE_ASM("asm/nonmatchings/src/act-env", GetSofaPosition);
extern void sceVu0AddVector(float *a0, float *a1, float *a2);
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0ScaleVector(float *a0, float *a1, float a2);

void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2)
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
        sceVu0AddVector(acc, acc, (float *)w);
        w += 0x10;
        i--;
    } while (i >= 0);
    sceVu0ScaleVector((float *)a0, acc, 0.25f);
    if (a1 != 0) {
        ((union ENVIF *)((char *)a0 + 0xC))->f = 1.0f;
        sceVu0ApplyMatrix(a0, (void *)*(int *)(*(char **)((char *)a1 + 0x15C) + 0xC), a0);
    }
}
extern int CheckPureWallAttribute();
extern int CheckWallAttribute();
extern int stage_no;

extern int CheckPureWallAttribute__pn(int a0, int a1) __asm__("CheckPureWallAttribute");
extern int CheckWallAttribute__pn(int a0, int a1) __asm__("CheckWallAttribute");

int CheckWallAttributeEdegWall(int a0) {
    if (stage_no == 4) {
        return (unsigned char)CheckPureWallAttribute__pn(a0, 0x1000);
    }
    return (unsigned char)CheckWallAttribute__pn(a0, 0x1000);
}
