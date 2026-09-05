#include "common.h"

#include "ico/types.h"
union ENVIF { int i; float f; };
/* .data — carved VMA 0x4F1D60..0x4F1E10: the per-stage ditch-distance
   tables getDitchDistTbl selects between (the first six are ranges
   terminated by -1.0f, the rest position/orientation vectors).  Values are
   the shortest decimals that round-trip through binary32; every byte
   verified against baserom/pal/baseelf.rom. */
float D_004F1D60[4] = { 150.0f, 215.0f, 315.0f, -1.0f };
float D_004F1D70[4] = { 150.0f, 235.0f, 315.0f, -1.0f };
float D_004F1D80[4] = { 315.0f, 330.0f, 350.0f, -1.0f };
float D_004F1D90[4] = { 150.0f, 215.0f, 315.0f, -1.0f };
float D_004F1DA0[4] = { 150.0f, 215.0f, 315.0f, -1.0f };
float D_004F1DB0[4] = { -1.0f, 0.0f, 0.0f, 0.0f };
float D_004F1DC0[4] = { 226.0f, -2328.0f, 343.0f, 1.0f };
float D_004F1DD0[4] = { 0.642799f, 0.0f, -0.765893f, 0.0f };
float D_004F1DE0[4] = { 602.0f, -3775.0f, 2480.0f, 1.0f };
float D_004F1DF0[4] = { 749.0f, -3775.0f, 2650.0f, 1.0f };
float D_004F1E00[4] = { 559.0f, -3775.0f, 2503.0f, 1.0f };
extern int ACTGame_FLAG_TETSUNAGI(void);
typedef struct { float x, y, z, w; } Vec4 __attribute__((aligned(16)));
/* {30, 0, -50, 0}: the sofa seat offset in the room's local space.  Lives in
   act-env's own .rodata run at 0x621A00 (only this TU's code references
   0x621A00..0x621A3F); extern until that run is carved. */
extern Vec4 D_00621A00;
extern char *D_00639EA4;
extern void sceVu0ApplyMatrix(void *a0, void *a1, void *a2);
extern void sceVu0AddVector(float *a0, float *a1, float *a2);
extern void sceVu0ScaleVector(float *a0, float *a1, float a2);
extern int CheckPureWallAttribute();
extern int CheckWallAttribute();
extern int stage_no;
extern int CheckPureWallAttribute__pn(int a0, int a1) __asm__("CheckPureWallAttribute");
extern int CheckWallAttribute__pn(int a0, int a1) __asm__("CheckWallAttribute");
/* prototypes: their order is the inline tail's emission order */
void ACTSetEnvAllmighty(char *a0);
void GetSofaPosition(char *a0, char *a1);
void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2);
int CheckWallAttributeEdegWall(int a0);
inline void GetSofaPosition(char *a0, char *a1) {
    char *w = *(char **)(a0 + 0x164);
    Vec4 v = D_00621A00;
    *(float *)(w + 0x560) = *(float *)(w + 0x4B0);
    *(float *)(w + 0x564) = *(float *)(w + 0x4B4);
    *(float *)(w + 0x568) = *(float *)(w + 0x4B8);
    if (a0 == D_00639EA4) {
        v.x = -v.x;
    }
    v.w = 1.0f;
    sceVu0ApplyMatrix(w + 0x5B0, *(void **)(*(char **)(a1 + 0x15C) + 0xC), &v);
}
INCLUDE_ASM("asm/nonmatchings/src/act-env", getDitchDistTbl);
INCLUDE_ASM("asm/nonmatchings/src/act-env", GetDitchPosition);
inline void GetCollisCenterPositionSimple(void *a0, void *a1, void *a2)
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
INCLUDE_ASM("asm/nonmatchings/src/act-env", DebugActOrientFlag);
inline void ACTSetEnvAllmighty(char *a0) {
    char *s = *(char **)(a0 + 0x164);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 38);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 39);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 40);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 41);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 44);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 45);
    if (ACTGame_FLAG_TETSUNAGI()) {
        *(unsigned long long *)(s + 0x18) &= ~(1ULL << 43);
        *(int *)(s + 0x28) = 0;
    } else {
        if ((int)(*(unsigned long long *)(s + 0x18) >> 43) & 1)
            *(unsigned long long *)(s + 0x478) |= (1ULL << 46);
        *(int *)(s + 0x28) += 1;
    }
    *(unsigned long long *)(s + 0x478) |= (1ULL << 50);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 51);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 52);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 53);
    *(unsigned long long *)(s + 0x478) |= (1ULL << 49);
    *(unsigned long long *)(s + 0x480) |= (1ULL << 43);
}
inline int CheckWallAttributeEdegWall(int a0) {
    if (stage_no == 4) {
        return (unsigned char)CheckPureWallAttribute__pn(a0, 0x1000);
    }
    return (unsigned char)CheckWallAttribute__pn(a0, 0x1000);
}
INCLUDE_ASM("asm/nonmatchings/src/act-env", ACTGetEnvironment);
