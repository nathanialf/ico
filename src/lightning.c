#include "common.h"


#include "vu0.h"

typedef struct {
    float v[4];
} LVec;

typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} StructB;
void set_vertex(void *p0, void *p1, void *p2, void *p3)
{
    VU0_LSV(lqc2, 8, 0x0, a2);
    VU0_LSV(lqc2, 4, 0x0, a1);
    VU0_LSV(lqc2, 5, 0x10, a1);
    VU0_LSV(lqc2, 6, 0x20, a1);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_BC(vmaddz.xyzw, 12, 6, 8, z);
    VU0_LSV(sqc2, 12, 0x0, a0);
    VU0_NOP();
}

extern void func_00198B70(int n, void *a, void *b, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, int c);
extern void func_00243B60(void *a0, void *a1);

void DrawLightning2(void *p0, void *p1, void *a2, float f0, float f1, float f2,
                    float f3, float f4, float f5, float f6, float f7, float f8,
                    float f9, int a3) {
    StructB buf[2];
    func_00243B60(&buf[0], p0);
    func_00243B60(&buf[1], p1);
    func_00198B70(2, &buf[0], a2, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, a3);
}

INCLUDE_ASM("asm/nonmatchings/src/lightning", DrawLightningN);

int apply_m34(int *self, int *other) {
    return *(int *)((char *)self + 0x10) - *(int *)((char *)other + 0x10);
}

extern void func_00243B18(void *a0, void *a1, float a2);
extern void func_00243B70(void *a0, void *a1);

void DrawLightning(LVec *a0, void *a1, float f) {
    func_00243B70(a0, a1);
    func_00243B18(a0, a0, f);
    func_00243B18(a0 + 1, a0 + 1, f);
    return func_00243B18(a0 + 2, a0 + 2, f);
}

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199A08);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199A60);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199C30);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_00199F80);

INCLUDE_ASM("asm/nonmatchings/src/lightning", func_0019A6E8);

