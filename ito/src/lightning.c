#include "common.h"

void set_vertex(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf8, 0x0($6)\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x10($5)\n"
        "lqc2 $vf6, 0x20($5)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddz.xyzw $vf12, $vf6, $vf8z\n"
        "sqc2 $vf12, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

typedef union {
    float f[16];
    unsigned long long w[8];
} StructA;
typedef union {
    unsigned int c[4];
    unsigned long long w[2];
} StructB;
/* lightning effect data (.rodata, VMA 0x556390..0x5563E0) */
const StructB D_00556390 = {{ 0x80, 0xFF, 0xFF, 0x80 }};  /* RGBA channels */
const StructA D_005563A0 = {{
    0.0f, 750.0f,    0.0f, 1.0f,  /* vert0 */
    0.0f, 500.0f, -200.0f, 1.0f,  /* vert1 */
    0.0f, 250.0f,  200.0f, 1.0f,  /* vert2 */
    0.0f,   0.0f,    0.0f, 1.0f,  /* vert3 */
}};

extern void func_001962C0(int n, void *a, void *b, float f0, float f1,
                          float f2, float f3, float f4, float f5, float f6,
                          float f7, float f8, float f9, int c);
extern void func_00240080(void *a0, void *a1);

void DrawLightning2(void *p0, void *p1, void *a2, float f0, float f1, float f2,
                    float f3, float f4, float f5, float f6, float f7, float f8,
                    float f9, int a3) {
    StructB buf[2];
    func_00240080(&buf[0], p0);
    func_00240080(&buf[1], p1);
    func_001962C0(2, &buf[0], a2, f0, f1, f2, f3, f4, f5, f6, f7, f8, f9, a3);
}

void DrawLightningN(void) {
    StructB b = D_00556390;
    StructA a = D_005563A0;
    func_001962C0(4, &a, &b, 5.0f, 25.0f, 5.0f, 25.0f, 5.0f, 10.0f, 70.0f, 8.0f,
                  20.0f, 0.0f, 0);
}

int apply_m34(int *a0, int *a1) {
    return a0[4] - a1[4];
}

extern void func_00240090(void *a0, void *a1);
extern void func_00240038(void *a0, void *a1, float a2);

typedef struct {
    float v[4];
} LVec;

void DrawLightning(LVec *a0, void *a1, float f) {
    func_00240090(a0, a1);
    func_00240038(a0, a0, f);
    func_00240038(a0 + 1, a0 + 1, f);
    return func_00240038(a0 + 2, a0 + 2, f);
}


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_005563A0;

/* end struct shapes */
