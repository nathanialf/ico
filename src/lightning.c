#include "common.h"

#include "vu0.h"

typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} StructB;

typedef union {
    float f[4];
    unsigned long long w[2];
} LightningVtx;

typedef struct {
    LightningVtx v[4];
} StructC;

/* prototypes: their order is the inline tail's emission order */
void apply_m34(void *p0, void *p1, void *p2, void *p3);
void DrawLightning(void *p0, void *p1, void *a2, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, int a3);
void lightning_test(void);
int cmpr(int *self, int *other);
INCLUDE_ASM("asm/nonmatchings/src/lightning", set_vertex);
INCLUDE_ASM("asm/nonmatchings/src/lightning", DrawLightning2);
INCLUDE_ASM("asm/nonmatchings/src/lightning", DrawLightningN);
inline void apply_m34(void *p0, void *p1, void *p2, void *p3)
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
extern void DrawLightning2(int n, void *a, void *b, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, int c);
extern void sceVu0CopyVector(void *a0, void *a1);

inline int cmpr(int *self, int *other) {
    return *(int *)((char *)self + 0x10) - *(int *)((char *)other + 0x10);
}
inline void DrawLightning(void *p0, void *p1, void *a2, float f0, float f1, float f2,
                    float f3, float f4, float f5, float f6, float f7, float f8,
                    float f9, int a3) {
    StructB buf[2];
    sceVu0CopyVector(&buf[0], p0);
    sceVu0CopyVector(&buf[1], p1);
    DrawLightning2(2, &buf[0], a2, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, a3);
}
inline void lightning_test(void) {
    StructB col = { { 0x80, 0xFF, 0xFF, 0x80 } };
    StructC vtx = { {
        { { 0.0f, 750.0f,    0.0f, 1.0f } },
        { { 0.0f, 500.0f, -200.0f, 1.0f } },
        { { 0.0f, 250.0f,  200.0f, 1.0f } },
        { { 0.0f,   0.0f,    0.0f, 1.0f } },
    } };
    DrawLightning2(4, &vtx, &col, 5.0f, 25.0f, 5.0f, 25.0f, 5.0f, 10.0f, 70.0f,
                   8.0f, 20.0f, 0.0f, 0);
}
