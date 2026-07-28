#include "common.h"




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

INCLUDE_ASM("asm/nonmatchings/src/gv", _DistxzGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _MoveGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _RotyGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", func_00193EC8);

INCLUDE_ASM("asm/nonmatchings/src/gv", func_00193EE0);

void func_00193F48(int a0)
{
    int idx = *(int *)(a0 + 0x8);
    char *base = &D_002A4C48[idx * 0x4C];
    *(short *)(base + 0x42) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/gv", _GetDirection);

void _RotGV(void)
{
  int new_var;
  new_var = 0x42;
  *((short *) (D_002E4D64 + new_var)) = 0;
  *((int *) (D_002E4D64 + 0x48)) = ((*((int *) (D_002E4D64 + 0x48))) | 0x200000) & (~0x40000);
}

INCLUDE_ASM("asm/nonmatchings/src/gv", _RotGVF);

INCLUDE_ASM("asm/nonmatchings/src/gv", _OrientXZGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _OrientGV);

INCLUDE_ASM("asm/nonmatchings/src/gv", _FrontGV);

