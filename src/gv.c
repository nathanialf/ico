#include "common.h"

typedef union { unsigned long ll; unsigned int i; } GVBits;
typedef struct { char _0[0x42]; short f42; unsigned short f44; unsigned int f48; } GVGeo2;




extern char D_002E4D64[];
extern char D_002A4C48[];
extern void debug_assertMessage(char *fmt, ...);
extern char D_0055AEE8[];
int _InterGV(float *dst, float *src) {
    dst[0] = src[4];
    dst[1] = src[5];
    dst[2] = src[6];
    return 1;
}

INCLUDE_ASM("asm/nonmatchings/src/gv", GetMatrixDirectionToZ);

INCLUDE_ASM("asm/nonmatchings/src/gv", _InterRotGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _DistxzSqGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _DistSqGV);

void _DistGV(int *self)
{
    int *p;
    p = (int *)self[0x164 / 4];
    debug_assertMessage(D_0055AEE8, self[0x8 / 4]);
    *(long long *)((char *)p + 0x18) = *(long long *)((char *)p + 0x18) | 0x400000000LL;
}

extern GVGeo2 D_002A4C48__p4[] __asm__("D_002A4C48");
extern char D_0055AEF8[];
extern void debug_assertMessage__p4(char *a0, int a1) __asm__("debug_assertMessage");

void _DistxzGV(void *a0) {
    void *p = *(void **)((char *)a0 + 0x164);
    GVGeo2 *g = &D_002A4C48__p4[*(int *)((char *)a0 + 0x8)];
    debug_assertMessage__p4(D_0055AEF8, *(int *)((char *)a0 + 0x8));
    ((GVBits *)((char *)p + 0x18))->ll &= ~((unsigned long)0x8000 << 19);
    g->f48 = (g->f48 | 0x200000) & 0xFFFBFFFF;
}

INCLUDE_ASM("asm/nonmatchings/src/gv", _MoveGV);

void _RotyGV(int a0) {
    GVGeo2 *g = &D_002A4C48__p4[a0];
    unsigned int x = g->f48 & 0xFFDFFFFF;
    unsigned int y = x & 0xFFFBFFFF;
    y |= ((x >> 19) & 1) << 18;
    g->f48 = y;
    if ((y >> 19) & 1) {
        unsigned int z = y | 0x40000;
        g->f48 = z;
        if ((int)((z >> 5) & 0x1F) != -1) {
            g->f42++;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/gv", func_00193EC8);

INCLUDE_ASM("asm/nonmatchings/src/gv", func_00193EE0);

void func_00193F48(int a0)
{
    int idx = *(int *)(a0 + 0x8);
    char *base = &D_002A4C48[idx * 0x4C];
    *(short *)(base + 0x42) = 0;
}

void _GetDirection(short *a0) {
    a0[0] = 1;
    a0[1] = 1;
}

void _RotGV(void)
{
  int new_var;
  new_var = 0x42;
  *((short *) (D_002E4D64 + new_var)) = 0;
  *((int *) (D_002E4D64 + 0x48)) = ((*((int *) (D_002E4D64 + 0x48))) | 0x200000) & (~0x40000);
}

int _RotGVF(void *a0) {
    GVGeo2 *g = &D_002A4C48__p4[*(int *)((char *)a0 + 0x8)];
    void *p = *(void **)((char *)a0 + 0x164);
    if (g->f44 != 0) {
        return 0;
    }
    if ((unsigned int)(*(unsigned long long *)((char *)p + 0x18) >> 34) & 1) {
        return 0;
    }
    if (((g->f48 >> 21) & 1) == 0 && (g->f42 == -1 || g->f42 > 0)) {
        return 1;
    }
    return 0;
}

extern char D_006327A8[];
extern void assertMsg1(char *a0) __asm__("debug_assertMessage");
extern void func_00243AA8(void *a0, void *a1, void *a2, float a3);

void _OrientXZGV(void *a0, void *a1, void *a2, float a3, float a4) {
    if (a0 == 0 || a1 == 0 || a2 == 0) {
        assertMsg1(D_006327A8);
    }
    func_00243AA8(a0, a1, a2, a4 / (a3 + a4));
}

INCLUDE_ASM("asm/nonmatchings/src/gv", _OrientGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _FrontGV);

