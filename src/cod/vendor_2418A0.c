#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

typedef unsigned int u128_241778 __attribute__((mode(TI)));

typedef struct { int *end; int pad[2]; int *cur; } Pool241748;

typedef unsigned int u128 __attribute__((mode(TI)));
typedef struct {
    char pad0[0xF0];
    float fF0;
    float fF4;
    float fF8;
    float fFC;
    float f100;
    char pad104[4];
    union { unsigned char b; unsigned int w; } f108;
} CEntry;

extern CEntry D_004D4230[];
extern void _ApplyCurrentMatrix(void *a0, void *a1, void *a2);
extern void func_002412D8(void *a0, int a1);
extern void *func_002413F0(void *a0, void *a1, int a2);

void *func_002418A0(void *a0, void *a1, int a2) {
    void *obj = func_002413F0(a0, a1, a2);
    float vec[4];
    int i;
    int k;
    signed char count;

    vec[3] = 0.0f;
    vec[0] = D_004D4230[a2].fF0;
    vec[1] = D_004D4230[a2].fF4;
    vec[2] = D_004D4230[a2].fF8;
    count = *(signed char *)((char *)obj + 0x2E);
    for (i = 0; i < count; i++) {
        char *sub = *(char **)((char *)obj + 0x40) + i * 0x180;
        int n = *(int *)(sub + 0x94);
        for (k = 0; k < n; k++) {
            char *m = *(char **)(sub + 0x90) + k * 0x10;
            _ApplyCurrentMatrix(m, m, vec);
        }
        for (k = 0; k < 8; k++) {
            char *m = *(char **)((char *)obj + 0x44) + i * 0x80 + k * 0x10;
            _ApplyCurrentMatrix(m, m, vec);
        }
    }
    func_002412D8(obj, a2);
    return obj;
}

extern const char D_0062E020[];
extern void debug_assertMessage();

void func_00241A00(void) {
    do {
        debug_assertMessage(D_0062E020);
    } while (0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00241A20);

extern void *func_00105278(void);
extern void func_001052A8(int a0);
extern void func_00243BD8(void *a0);

void func_00241AE8(int a0, void *a1) {
    func_00243BD8(func_00105278());
    *(float *)((char *)a1 + 0xC) = 1.0f;
    func_001052A8((int)a1);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00241B28);

extern int D_005506A0[];

void *func_00241C38(void) {
    return D_005506A0;
}

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00241C48\n"
    "    .type func_00241C48, @function\n"
    "    .align 3\n"
    "func_00241C48:\n"
    "    lui   $2, 0x1000\n"
    "    addiu $7, $0, 0x1\n"
    "    ori   $2, $2, 0x3C10\n"
    "    lui   $3, 0x1000\n"
    "    sw    $7, 0x0($2)\n"
    "    ori   $3, $3, 0x3C20\n"
    "    addiu $2, $0, 0x2\n"
    "    daddu $4, $0, $0\n"
    "    sw    $2, 0x0($3)\n"
    "    sync\n"
    "    cfc2.ni $4, $vi28\n"
    "    ori   $4, $4, 0x200\n"
    "    ctc2.ni $4, $vi28\n"
    "    sync.p\n"
    "    lui   $5, %hi(D_005506B0)\n"
    "    lui   $6, 0x1000\n"
    "    addiu $5, $5, %lo(D_005506B0)\n"
    "    ori   $6, $6, 0x5000\n"
    "    lq    $4, 0x0($5)\n"
    "    lui   $3, 0x1000\n"
    "    ori   $3, $3, 0x3000\n"
    "    sq    $4, 0x0($6)\n"
    "    lq    $2, 0x10($5)\n"
    "    sq    $2, 0x0($6)\n"
    "    jr    $31\n"
    "    sw    $7, 0x0($3)\n"
    "    .size func_00241C48, . - func_00241C48\n"
    "    .set reorder\n"
    "    .set at\n"
);

const char D_0062E020[0x10] = "free object\n";

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00241CB0);

void func_00241F20(void *a0) {
    long *s = (long *)a0;
    if (*(short *)((char *)func_00241C38() + 6) == 1) {
        *(volatile long *)0x12000000 = s[0];
        *(volatile long *)0x12000070 = s[2];
        *(volatile long *)0x12000080 = s[3];
        *(volatile long *)0x120000C0 = s[4];
    } else {
        *(volatile long *)0x12000000 = s[0];
        *(volatile long *)0x12000020 = s[1];
        *(volatile long *)0x12000090 = s[2];
        *(volatile long *)0x120000A0 = s[3];
        *(volatile long *)0x120000E0 = s[4];
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00241FE0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002421C8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002422B0);

int func_00242548(void *a0, int a1) {
    int s0 = a1 & 1;
    int ret;
    func_00241F20((char *)a0 + s0 * 0x28);
    if (!s0) goto zero_path;
    ret = func_002421C8((char *)a0 + 0x140);
    goto done;
zero_path:
    ret = func_002421C8((char *)a0 + 0x50);
done:
    return ret;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002425A8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00242640);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00242958);

int func_00242A68(long long *a0, int a1) {
    short t = a1;
    a0[1] = 0x42;
    a0[0] = 0x44;
    a0[3] = 0x49;
    a0[2] = t;
    a0[5] = 0x3B;
    a0[4] = 0x000000810000807FLL;
    a0[7] = 0x4A;
    a0[6] = 0;
    SYNC();
    return 4;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00242AC8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00242CB0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00242DF0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00242F70);

const char D_0062E560[0x18] = "libdma: sync timeout\n";

extern int func_00100840(void);
extern void func_00100860(void *a0);

int func_00243600(void *a0) {
    int r = func_00100840();
    func_00100860(a0);
    return r;
}

void func_00243640(void *a0, short a1, short a2, short a3) {
    unsigned long long v = *(unsigned long long *)((char *)a0 + 0x30);
    long long a, b, ta, t, hi;
    b = (short)a2;
    b -= (unsigned long long)((int)((v >> 48) & 0x7FF) + 1) >> 1;
    t = b << 4;
    a = (short)a1;
    a -= (unsigned long long)((int)((v >> 16) & 0x7FF) + 1) >> 1;
    ta = a << 4;
    if (a3 != 0) hi = (t + 8) << 32; else hi = b << 36;
    *(long long *)((char *)a0 + 0x20) = ta | hi;
}

void func_002436C8(void) {
    do {
        func_00100840();
    } while (0);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002436E8);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002437B0);

void func_002438B8(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x10, 5);
    VU0_LSV(lqc2, 6, 0x20, 5);
    VU0_LSV(lqc2, 7, 0x30, 5);
    VU0_LSV(lqc2, 8, 0x0, 6);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 7, 8, w);
    VU0_LSV(sqc2, 9, 0x0, 4);
}

void func_002438E8(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x10($5)\n"
        "lqc2 $vf6, 0x20($5)\n"
        "lqc2 $vf7, 0x30($5)\n"
        "addiu $7, $0, 0x4\n"
        "1:\n"
        "lqc2 $vf8, 0x0($6)\n"
        "vmulax.xyzw ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf9, $vf7, $vf8w\n"
        "sqc2 $vf9, 0x0($4)\n"
        "addi $7, $7, -0x1\n"
        "addi $6, $6, 0x10\n"
        "bne $0, $7, 1b\n"
        "addi $4, $4, 0x10\n"
        ".set reorder\n"
        ::: "$7", "memory");
}

void func_00243930(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP_ACC(vopmula.xyz, 4, 5);
    VU0_V3OP(vopmsub.xyz, 6, 5, 4);
    VU0_V3OP(vsub.w, 6, 6, 6);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

float func_00243950(void *a0, void *a1) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "lqc2 $vf5, 0x0($5)\n"
        "vmul.xyz $vf5, $vf4, $vf5\n"
        "vaddy.x $vf5, $vf5, $vf5y\n"
        "vaddz.x $vf5, $vf5, $vf5z\n"
        "qmfc2.ni $2, $vf5\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

void func_00243978(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_REG("vmul.xyz $vf5, $vf4, $vf4");
    VU0_REG("vaddy.x $vf5, $vf5, $vf5y");
    VU0_REG("vaddz.x $vf5, $vf5, $vf5z");
    VU0_REG(".word 0x4A0503BD");
    VU0_WAIT();
    VU0_REG("vaddq.x $vf5, $vf0, Q");
    VU0_REG("vdiv Q, $vf0w, $vf5x");
    VU0_REG("vsub.xyzw $vf6, $vf0, $vf0");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf6, $vf4, Q");
    VU0_LSV(sqc2, 6, 0x0, 4);
}

/* 4x4 matrix transpose via the MMI pack/unpack ops — hand-written assembly
 * in the original, same class and same whole-function `__asm__` form as
 * func_002439F8 below: the $t0..$t7 register budget is the author's, and the
 * trailing `sq` in the `jr` delay slot has to be written explicitly (gcc's
 * reorg cannot schedule an inline-asm insn into a delay slot, and
 * ee-as 2.9-991111 fills no slots). */
void func_002439B0(void *a0, void *a1);
__asm__(
    ".section .text\n"
    "    .align 3\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_002439B0\n"
    "    .type func_002439B0, @function\n"
    "func_002439B0:\n"
    "    lq    $8, 0x0($5)\n"
    "    lq    $9, 0x10($5)\n"
    "    lq    $10, 0x20($5)\n"
    "    lq    $11, 0x30($5)\n"
    "    pextlw $12, $9, $8\n"
    "    pextuw $13, $9, $8\n"
    "    pextlw $14, $11, $10\n"
    "    pextuw $15, $11, $10\n"
    "    pcpyld $8, $14, $12\n"
    "    pcpyud $9, $12, $14\n"
    "    pcpyld $10, $15, $13\n"
    "    pcpyud $11, $13, $15\n"
    "    sq    $8, 0x0($4)\n"
    "    sq    $9, 0x10($4)\n"
    "    sq    $10, 0x20($4)\n"
    "    jr    $31\n"
    "    sq    $11, 0x30($4)\n"
    "    .size func_002439B0, . - func_002439B0\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .align 3\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_002439F8\n"
    "    .type func_002439F8, @function\n"
    "func_002439F8:\n"
    "    lq    $8, 0x0($5)\n"
    "    lq    $9, 0x10($5)\n"
    "    lq    $10, 0x20($5)\n"
    "    lqc2  $vf4, 0x30($5)\n"
    "    vmove.xyzw $vf5, $vf4\n"
    "    vsub.xyz $vf4, $vf4, $vf4\n"
    "    vmove.xyzw $vf9, $vf4\n"
    "    qmfc2.ni $11, $vf4\n"
    "    pextlw $12, $9, $8\n"
    "    pextuw $13, $9, $8\n"
    "    pextlw $14, $11, $10\n"
    "    pextuw $15, $11, $10\n"
    "    pcpyld $8, $14, $12\n"
    "    pcpyud $9, $12, $14\n"
    "    pcpyld $10, $15, $13\n"
    "    qmtc2.ni $8, $vf6\n"
    "    qmtc2.ni $9, $vf7\n"
    "    qmtc2.ni $10, $vf8\n"
    "    vmulax.xyz ACC, $vf6, $vf5x\n"
    "    vmadday.xyz ACC, $vf7, $vf5y\n"
    "    vmaddz.xyz $vf4, $vf8, $vf5z\n"
    "    vsub.xyz $vf4, $vf9, $vf4\n"
    "    sq    $8, 0x0($4)\n"
    "    sq    $9, 0x10($4)\n"
    "    sq    $10, 0x20($4)\n"
    "    jr    $31\n"
    "    sqc2  $vf4, 0x30($4)\n"
    "    .size func_002439F8, . - func_002439F8\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

void func_00243A68(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyzw $vf4, $vf4, Q");
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void func_00243A88(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf4, $vf4, Q");
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void func_00243AA8(void *a0, void *a1, void *a2, float t) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 6);
    VU0_NOREORDER_END();
    VU0_REG("vaddw.x $vf7, $vf0, $vf0w");
    VU0_REG("vsub.x $vf8, $vf7, $vf6");
    VU0_REG("vmulax.xyzw ACC, $vf4, $vf6x");
    VU0_REG("vmaddx.xyzw $vf9, $vf5, $vf8x");
    VU0_LSV(sqc2, 9, 0x0, 4);
}

void func_00243AD0(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00243AE8(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00243B00(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vmul.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00243B18(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyzw, 6, 4, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00243B30(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 6);
    VU0_LSV(lqc2, 5, 0x30, 5);
    VU0_LSGP(lq, 7, 0x0, 5);
    VU0_LSGP(lq, 8, 0x10, 5);
    VU0_LSGP(lq, 9, 0x20, 5);
    VU0_V3OP(vadd.xyz, 5, 5, 4);
    VU0_LSGP(sq, 7, 0x0, 4);
    VU0_LSGP(sq, 8, 0x10, 4);
    VU0_LSGP(sq, 9, 0x20, 4);
    VU0_LSV(sqc2, 5, 0x30, 4);
}

/* Quadword copy leaves, hand-written assembly in the original.
 *
 * These cannot be C: ee-gcc's own allocator always picks $2/$3 for the
 * quadword temporaries (verified: a `mode(TI)` `*d = *s` compiles to
 * `lq $2,0($5) / jr $31 / sq $2,0($4)`), and it emits a 64-byte copy as
 * interleaved lq/sq pairs, never as four loads followed by four stores.
 * The ROM's hand-picked $a2..$t1 and its load-all-then-store-all shape are
 * an author's register budget, not an allocator's. gcc also never hoists an
 * inline-asm insn into the `jr` delay slot (reorg cannot schedule asm), so
 * the trailing `sq` sitting in the slot has to be written there explicitly —
 * ee-as 2.9-991111 does no delay-slot filling of its own. Same whole-function
 * `__asm__` form as func_002439F8 above. */
void func_00243B60(void *a0, void *a1);
__asm__(
    ".section .text\n"
    "    .align 3\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00243B60\n"
    "    .type func_00243B60, @function\n"
    "func_00243B60:\n"
    "    lq    $6, 0x0($5)\n"
    "    jr    $31\n"
    "    sq    $6, 0x0($4)\n"
    "    .size func_00243B60, . - func_00243B60\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .align 3\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00243B70\n"
    "    .type func_00243B70, @function\n"
    "func_00243B70:\n"
    "    lq    $6, 0x0($5)\n"
    "    lq    $7, 0x10($5)\n"
    "    lq    $8, 0x20($5)\n"
    "    lq    $9, 0x30($5)\n"
    "    sq    $6, 0x0($4)\n"
    "    sq    $7, 0x10($4)\n"
    "    sq    $8, 0x20($4)\n"
    "    jr    $31\n"
    "    sq    $9, 0x30($4)\n"
    "    .size func_00243B70, . - func_00243B70\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

void func_00243B98(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_00243BA8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_00243BB8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_00243BC8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_00243BD8(void *a0) {
    __asm__ __volatile__(
        "vsub.xyzw $vf4, $vf0, $vf0\n"
        "vadd.w $vf4, $vf4, $vf0\n"
        "vmr32.xyzw $vf5, $vf4\n"
        "vmr32.xyzw $vf6, $vf5\n"
        "vmr32.xyzw $vf7, $vf6\n"
        "sqc2 $vf4, 0x30($4)\n"
        "sqc2 $vf5, 0x20($4)\n"
        "sqc2 $vf6, 0x10($4)\n"
        "sqc2 $vf7, 0x0($4)\n" : : : "memory");
}

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00243C00\n"
    "    .type func_00243C00, @function\n"
    "    .align 3\n"
    "func_00243C00:\n"
    "    lui   $8, %hi(D_005506E0)\n"
    "    addiu $8, $8, %lo(D_005506E0)\n"
    "    lqc2  $vf5, 0x0($8)\n"
    "    vmr32.w $vf6, $vf6\n"
    "    vaddx.x $vf4, $vf0, $vf6x\n"
    "    vmul.x $vf6, $vf6, $vf6\n"
    "    vmulx.yzw $vf4, $vf4, $vf0x\n"
    "    vmulw.xyzw $vf8, $vf5, $vf6w\n"
    "    vsub.xyzw $vf5, $vf0, $vf0\n"
    "    vmulx.xyzw $vf8, $vf8, $vf6x\n"
    "    vmulx.xyz $vf8, $vf8, $vf6x\n"
    "    vaddw.x $vf4, $vf4, $vf8w\n"
    "    vmulx.xy $vf8, $vf8, $vf6x\n"
    "    vaddz.x $vf4, $vf4, $vf8z\n"
    "    vmulx.x $vf8, $vf8, $vf6x\n"
    "    vaddy.x $vf4, $vf4, $vf8y\n"
    "    vaddx.x $vf4, $vf4, $vf8x\n"
    "    vaddx.xy $vf4, $vf5, $vf4x\n"
    "    vmul.x $vf7, $vf4, $vf4\n"
    "    vsubx.w $vf7, $vf0, $vf7x\n"
    "    .word 0x4B8703BD\n"
    "    vwaitq\n"
    "    bnez  $7, 1f\n"
    "    vaddq.x $vf7, $vf0, Q\n"
    "    b     2f\n"
    "    vaddx.x $vf4, $vf5, $vf7x\n"
    "1:\n"
    "    vsubx.x $vf4, $vf5, $vf7x\n"
    "2:\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00243C00, . - func_00243C00\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00243C78\n"
    "    .type func_00243C78, @function\n"
    "    .align 3\n"
    "func_00243C78:\n"
    "    mtc1  $0, $f0\n"
    "    c.lt.s $f12, $f0\n"
    "    lui   $1, 0x3FC9\n"
    "    ori   $1, $1, 0x0FDB\n"
    "    mtc1  $1, $f0\n"
    "    bc1f  1f\n"
    "    nop\n"
    "    add.s $f12, $f0, $f12\n"
    "    j     func_00243CA8\n"
    "    addiu $7, $0, 0x1\n"
    "1:\n"
    "    sub.s $f12, $f0, $f12\n"
    "    daddu $7, $0, $0\n"
    "    .align 3\n"
    "func_00243CA8:\n"
    "    mfc1  $8, $f12\n"
    "    qmtc2.ni $8, $vf6\n"
    "    daddu $6, $31, $0\n"
    "    jal   func_00243C00\n"
    "    nop\n"
    "    daddu $31, $6, $0\n"
    "    vmove.xyzw $vf6, $vf5\n"
    "    vmove.xyzw $vf7, $vf5\n"
    "    vmove.xyzw $vf9, $vf0\n"
    "    vsub.xyz $vf9, $vf9, $vf9\n"
    "    vmr32.xyzw $vf8, $vf9\n"
    "    vsub.zw $vf4, $vf4, $vf4\n"
    "    vaddx.y $vf6, $vf5, $vf4x\n"
    "    vaddy.x $vf6, $vf5, $vf4y\n"
    "    vsubx.x $vf7, $vf5, $vf4x\n"
    "    vaddy.y $vf7, $vf5, $vf4y\n"
    "    addiu $7, $0, 0x4\n"
    "2:\n"
    "    lqc2  $vf4, 0x0($5)\n"
    "    vmulax.xyzw ACC, $vf6, $vf4x\n"
    "    vmadday.xyzw ACC, $vf7, $vf4y\n"
    "    vmaddaz.xyzw ACC, $vf8, $vf4z\n"
    "    vmaddw.xyzw $vf5, $vf9, $vf4w\n"
    "    sqc2  $vf5, 0x0($4)\n"
    "    addi  $7, $7, -0x1\n"
    "    addi  $5, $5, 0x10\n"
    "    bne   $0, $7, 2b\n"
    "    addi  $4, $4, 0x10\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00243C78, . - func_00243C78\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00243D20\n"
    "    .type func_00243D20, @function\n"
    "    .align 3\n"
    "func_00243D20:\n"
    "    mtc1  $0, $f0\n"
    "    c.lt.s $f12, $f0\n"
    "    lui   $1, 0x3FC9\n"
    "    ori   $1, $1, 0x0FDB\n"
    "    mtc1  $1, $f0\n"
    "    bc1f  1f\n"
    "    nop\n"
    "    add.s $f12, $f0, $f12\n"
    "    j     func_00243D50\n"
    "    addiu $7, $0, 0x1\n"
    "1:\n"
    "    sub.s $f12, $f0, $f12\n"
    "    daddu $7, $0, $0\n"
    "    .align 3\n"
    "func_00243D50:\n"
    "    mfc1  $8, $f12\n"
    "    qmtc2.ni $8, $vf6\n"
    "    daddu $6, $31, $0\n"
    "    jal   func_00243C00\n"
    "    nop\n"
    "    daddu $31, $6, $0\n"
    "    vmove.xyzw $vf6, $vf5\n"
    "    vmove.xyzw $vf7, $vf5\n"
    "    vmove.xyzw $vf8, $vf5\n"
    "    vmove.xyzw $vf9, $vf5\n"
    "    vaddw.x $vf6, $vf5, $vf0w\n"
    "    vaddw.w $vf9, $vf5, $vf0w\n"
    "    vsub.zw $vf4, $vf4, $vf4\n"
    "    vaddx.z $vf7, $vf5, $vf4x\n"
    "    vaddy.y $vf7, $vf5, $vf4y\n"
    "    vsubx.y $vf8, $vf5, $vf4x\n"
    "    vaddy.z $vf8, $vf5, $vf4y\n"
    "    addiu $7, $0, 0x4\n"
    "2:\n"
    "    lqc2  $vf4, 0x0($5)\n"
    "    vmulax.xyzw ACC, $vf6, $vf4x\n"
    "    vmadday.xyzw ACC, $vf7, $vf4y\n"
    "    vmaddaz.xyzw ACC, $vf8, $vf4z\n"
    "    vmaddw.xyzw $vf5, $vf9, $vf4w\n"
    "    sqc2  $vf5, 0x0($4)\n"
    "    addi  $7, $7, -0x1\n"
    "    addi  $5, $5, 0x10\n"
    "    bne   $0, $7, 2b\n"
    "    addi  $4, $4, 0x10\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00243D20, . - func_00243D20\n"
    "    .set reorder\n"
    "    .set at\n"
);

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00243DC8\n"
    "    .type func_00243DC8, @function\n"
    "    .align 3\n"
    "func_00243DC8:\n"
    "    mtc1  $0, $f0\n"
    "    c.lt.s $f12, $f0\n"
    "    lui   $1, 0x3FC9\n"
    "    ori   $1, $1, 0x0FDB\n"
    "    mtc1  $1, $f0\n"
    "    bc1f  1f\n"
    "    nop\n"
    "    add.s $f12, $f0, $f12\n"
    "    j     func_00243DF8\n"
    "    addiu $7, $0, 0x1\n"
    "1:\n"
    "    sub.s $f12, $f0, $f12\n"
    "    daddu $7, $0, $0\n"
    "    .align 3\n"
    "func_00243DF8:\n"
    "    mfc1  $8, $f12\n"
    "    qmtc2.ni $8, $vf6\n"
    "    daddu $6, $31, $0\n"
    "    jal   func_00243C00\n"
    "    nop\n"
    "    daddu $31, $6, $0\n"
    "    vmove.xyzw $vf6, $vf5\n"
    "    vmove.xyzw $vf7, $vf5\n"
    "    vmove.xyzw $vf8, $vf5\n"
    "    vmove.xyzw $vf9, $vf5\n"
    "    vaddw.y $vf7, $vf5, $vf0w\n"
    "    vaddw.w $vf9, $vf5, $vf0w\n"
    "    vsub.zw $vf4, $vf4, $vf4\n"
    "    vsubx.z $vf6, $vf5, $vf4x\n"
    "    vaddy.x $vf6, $vf5, $vf4y\n"
    "    vaddx.x $vf8, $vf5, $vf4x\n"
    "    vaddy.z $vf8, $vf5, $vf4y\n"
    "    addiu $7, $0, 0x4\n"
    "2:\n"
    "    lqc2  $vf4, 0x0($5)\n"
    "    vmulax.xyzw ACC, $vf6, $vf4x\n"
    "    vmadday.xyzw ACC, $vf7, $vf4y\n"
    "    vmaddaz.xyzw ACC, $vf8, $vf4z\n"
    "    vmaddw.xyzw $vf5, $vf9, $vf4w\n"
    "    sqc2  $vf5, 0x0($4)\n"
    "    addi  $7, $7, -0x1\n"
    "    addi  $5, $5, 0x10\n"
    "    bne   $0, $7, 2b\n"
    "    addi  $4, $4, 0x10\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00243DC8, . - func_00243DC8\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern void func_00243C78(int a, int b, float f);
extern void func_00243D20(int a, int b, float f);
extern void func_00243DC8(int a, int b, float f);

void func_00243E70(int a0, int a1, float *fa)
{
    func_00243C78(a0, a1, fa[2]);
    func_00243DC8(a0, a0, fa[1]);
    func_00243D20(a0, a0, fa[0]);
}

void func_00243EC0(void *a0, void *a1, float a2, float a3) {
    VU0_MFC1(8, 12);
    VU0_MFC1(9, 13);
    VU0_LSV(lqc2, 6, 0x0, 5);
    VU0_QMTC2_NI(8, 4);
    VU0_QMTC2_NI(9, 5);
    VU0_V3OP_BC(vmaxx.xyzw, 6, 6, 4, x);
    VU0_V3OP_BC(vminix.xyzw, 6, 6, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

extern void func_002439F8(void *a0, void *a1);

void func_00243EE8(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x50];
    func_00243BD8(buf);
    func_00243930(buf + 0x40, a3, a2);
    func_00243978(buf, buf + 0x40);
    func_00243978(buf + 0x20, a2);
    func_00243930(buf + 0x10, buf + 0x20, buf);
    func_00243B30(buf, buf, a1);
    func_002439F8(a0, buf);
}


void func_00243F98(void *a0, void *a1, void *a2, void *a3) {
    float buf[4];
    func_00243B18(buf, a1, -1.0f);
    func_00243978(a0, buf);
    func_00243B18(buf, a2, -1.0f);
    func_00243978((char *)a0 + 0x10, buf);
    func_00243B18(buf, a3, -1.0f);
    func_00243978((char *)a0 + 0x20, buf);
    {
        float fzero = 0.0f;
        *(float *)((char *)a0 + 0x38) = fzero;
        *(float *)((char *)a0 + 0x3C) = 1.0f;
        *(float *)((char *)a0 + 0x34) = fzero;
        *(float *)((char *)a0 + 0x30) = fzero;
    }
    func_002439B0(a0, a0);
}


void func_00244058(void *a0, void *a1, void *a2, void *a3, void *a4) {
    func_00243B60((void *)a0, a1);
    func_00243B60((char *)a0 + 0x10, a2);
    func_00243B60((char *)a0 + 0x20, a3);
    func_00243B60((char *)a0 + 0x30, a4);
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002440C0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_002441C8);

void func_00244358(void *a0, void *a1, void *a2, int a3, int a4) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x10($5)\n"
        "lqc2 $vf6, 0x20($5)\n"
        "lqc2 $vf7, 0x30($5)\n"
        "1:\n"
        "lqc2 $vf8, 0x0($6)\n"
        "vmulax.xyzw ACC, $vf4, $vf8x\n"
        "vmadday.xyzw ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf9, $vf7, $vf8w\n"
        "vdiv Q, $vf0w, $vf9w\n"
        "vwaitq\n"
        "vmulq.xyz $vf9, $vf9, Q\n"
        "beqz $8, 2f\n"
        "vftoi4.xyzw $vf10, $vf9\n"
        "vftoi0.zw $vf10, $vf9\n"
        "2:\n"
        "sqc2 $vf10, 0x0($4)\n"
        "addi $7, $7, -0x1\n"
        "addi $6, $6, 0x10\n"
        "bne $0, $7, 1b\n"
        "addi $4, $4, 0x10\n"
        ".set reorder\n"
        ::: "$7", "memory");
}

void func_002443B0(void *a0, void *a1, void *a2, int a3) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x10, 5);
    VU0_LSV(lqc2, 6, 0x20, 5);
    VU0_LSV(lqc2, 7, 0x30, 5);
    VU0_LSV(lqc2, 8, 0x0, 6);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 7, 8, w);
    VU0_REG("vdiv Q, $vf0w, $vf9w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf9, $vf9, Q");
    VU0_REG("vftoi4.xyzw $vf10, $vf9");
    if (a3) {
        VU0_REG("vftoi0.zw $vf10, $vf9");
    }
    VU0_LSV(sqc2, 10, 0x0, 4);
}

void func_002443F8(void *a0, void *a1) {
    ((float *)a0)[0] = ((float *)a1)[0];
    ((float *)a0)[1] = ((float *)a1)[1];
    ((float *)a0)[2] = ((float *)a1)[2];
}

void func_00244418(void *a0, void *a1, void *a2, float a3) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 6);
    VU0_NOREORDER_END();
    VU0_V2OP(vmove.w, 9, 4);
    VU0_V3OP_BC(vaddw.x, 7, 0, 0, w);
    VU0_V3OP(vsub.x, 8, 7, 6);
    VU0_V3OP_ACC_BC(vmulax.xyz, 4, 6, x);
    VU0_V3OP_BC(vmaddx.xyz, 9, 5, 8, x);
    VU0_LSV(sqc2, 9, 0x0, 4);
}

void func_00244448(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

int func_00244460(void *a0) {
    register int r __asm__("$2");
    __asm__ __volatile__(
        ".set noreorder\n"
        "vsub.xyzw $vf4, $vf0, $vf0\n"
        "lui $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "ori $2, $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "lqc2 $vf7, 0x0($4)\n"
        "qmtc2.ni $2, $vf6\n"
        "ctc2.ni $0, $vi16\n"
        "vsub.xyw $vf5, $vf7, $vf4\n"
        "vsub.xy $vf5, $vf6, $vf7\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2.ni $2, $vi16\n"
        ".set reorder\n"
        : "=r"(r));
    return r & 0xC0;
}

int func_002444A8(void *a0, void *a1, void *a2) {
    register int ret __asm__("$2");
    __asm__ __volatile__(
        ".set noreorder\n"
        "vsub.xyzw $vf4, $vf0, $vf0\n"
        "lui $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "ori $2, $2, 0x4580\n"
        "dsll $2, $2, 16\n"
        "lqc2 $vf6, 0x0($4)\n"
        "lqc2 $vf8, 0x0($5)\n"
        "lqc2 $vf9, 0x0($6)\n"
        "qmtc2.ni $2, $vf7\n"
        "ctc2.ni $0, $vi16\n"
        "vsub.xyw $vf5, $vf6, $vf4\n"
        "vsub.xy $vf5, $vf7, $vf6\n"
        "vsub.xyw $vf5, $vf8, $vf4\n"
        "vsub.xy $vf5, $vf7, $vf8\n"
        "vsub.xyw $vf5, $vf9, $vf4\n"
        "vsub.xy $vf5, $vf7, $vf9\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "vnop\n"
        "cfc2.ni $2, $vi16\n"
        ".set reorder\n"
        : "=r"(ret));
    return ret & 0xC0;
}

__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00244508\n"
    "    .type func_00244508, @function\n"
    "    .align 3\n"
    "func_00244508:\n"
    "    lqc2 $vf8, 0x0($7)\n"
    "    lqc2 $vf4, 0x0($6)\n"
    "    lqc2 $vf5, 0x10($6)\n"
    "    lqc2 $vf6, 0x20($6)\n"
    "    lqc2 $vf7, 0x30($6)\n"
    "    lqc2 $vf9, 0x0($4)\n"
    "    lqc2 $vf10, 0x0($5)\n"
    "    lqc2 $vf11, 0x0($4)\n"
    "    lqc2 $vf12, 0x0($5)\n"
    "1:\n"
    "    vmulax.xyzw ACC, $vf4, $vf8x\n"
    "    vmadday.xyzw ACC, $vf5, $vf8y\n"
    "    vmaddaz.xyzw ACC, $vf6, $vf8z\n"
    "    vmaddw.xyzw $vf8, $vf7, $vf8w\n"
    "    vmulw.xyz $vf11, $vf9, $vf8w\n"
    "    vmulw.xyz $vf12, $vf10, $vf8w\n"
    "    vnop\n"
    "    vnop\n"
    "    ctc2.ni $0, $vi16\n"
    "    vsub.xyw $vf11, $vf8, $vf11\n"
    "    vsub.xyw $vf12, $vf12, $vf8\n"
    "    vmove.w $vf11, $vf9\n"
    "    vmove.w $vf12, $vf10\n"
    "    vnop\n"
    "    addi $7, $7, 0x10\n"
    "    lqc2 $vf8, 0x0($7)\n"
    "    addi $8, $8, -0x1\n"
    "    cfc2.ni $2, $vi16\n"
    "    andi $2, $2, 0xC0\n"
    "    beqz $2, 2f\n"
    "    nop\n"
    "    bne $0, $8, 1b\n"
    "    nop\n"
    "    addi $2, $0, 0x1\n"
    "2:\n"
    "    jr $31\n"
    "    nop\n"
    "    .size func_00244508, . - func_00244508\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_005506F0[];

void func_00244598(void) {
    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;

    __asm__ __volatile__(
        ".set noreorder\n"
        "cfc2.ni $8, $vi28\n"
        "ori $8, $8, 0x2\n"
        "ctc2.ni $8, $vi28\n"
        "sync.p\n"
        ".set reorder\n"
        : : : "memory");

    {
        u128 *fifo = (u128 *)0x10004000;
        u128 *pkt = (u128 *)D_005506F0;

        *(volatile u128 *)fifo = pkt[0];
        *fifo = pkt[1];
    }
}

void func_002445F8(unsigned char *a0, int a1) {
    int i;
    for (i = a1 - 1; i != -1; i--) {
        *a0++ = 0;
    }
}

extern int D_00550710[];

int func_00244630(unsigned int a0) {
    if (a0 < 0xA) {
        return D_00550710[a0];
    }
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244658);

extern int D_00550738[];

int func_00244738(int a0) {
    int old = D_00550738[0];
    D_00550738[0] = a0;
    return old;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244748);

struct __attribute__((packed)) S_244920 {
    long long a;
    long long b;
    int c __attribute__((aligned(4)));
};
extern struct S_244920 D_005507A8;

void *func_00244920(void *a0) {
    *(struct S_244920 *)a0 = D_005507A8;
    return a0;
}

/* Delay-slot dependant (see tough_nuts/delayslot_unfilled/HANDOFF_vendor_2418A0.md):
 * the ROM's `beq` carries the D_STADR read in its delay slot. Every C spelling of
 * that read is either volatile — which registerises the address exactly as the ROM
 * does but makes the insn ineligible for gcc's delay-slot pass — or non-volatile,
 * which folds the address back into a 2-insn `lw $r,<const>` macro that is
 * ineligible for a different reason. */
/* func_00244958 — parked. Its recovered C is stashed verbatim at
 * tough_nuts/delayslot_unfilled/vendor_2418A0_func_00244958.c and matches ONLY
 * under a delay-slot-filling assembler; under the one period assembler
 * (ee-as 2.9-991111, which fills nothing) the ROM's `lw v0,0(v0)` in the
 * `beq a0,v1` slot is left in front. Assembler swapping was tried 2026-08-05
 * and reverted — the remaining work is a source shape that makes gcc's OWN
 * reorg fill the slot. See tough_nuts/delayslot_unfilled/QUEUE.md row 3. */
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244958);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244980);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244A58);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244B40);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244C28);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244CF0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244DE0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244ED0);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00244F98);

int func_00245068(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

int func_00245088(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

void func_002450A8(int *a0, int a1) {
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

int func_002450B8(int *a0) {
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}

int *func_002450C8(int **a0) {
    int *p = a0[0];
    int *q = (int *)a0[2];
    while ((int)p & 0xC) {
        *p = 0;
        p++;
    }
    if (q) {
        int n = (((char *)p - (char *)q) >> 4) - 1;
        *q += n;
    }
    a0[0] = p;
    a0[2] = 0;
    return p;
}

void func_00245120(int *a1, unsigned int a2) {
    int *a0;
    int s0;
    int v0;
    v0 = func_002450C8(a1);
    a0 = (int *)a1[0];
    do { s0 = a2 | 0x10000000; } while (0);
    a1[2] = v0;
    a0[0] = s0;
    a0++;
    a1[3] = 0;
    a1[0] = (int)(a0 + 1);
    a0[0] = 0;
}

void func_00245178(int *a1, unsigned int a2) {
    int *a0;
    int s0;
    int v0;
    v0 = func_002450C8(a1);
    a0 = (int *)a1[0];
    do { s0 = a2 | 0x70000000; } while (0);
    a1[2] = v0;
    a0[0] = s0;
    a0++;
    a1[3] = 0;
    a1[0] = (int)(a0 + 1);
    a0[0] = 0;
}

extern void func_00245318(void *a0, int a1, int a2);

void func_002451D0(void *a0, int a1) {
    int *v;
    int w;
    func_00245318(a0, 2, 3);
    v = *(int **)a0;
    w = a1 ? 0xD0000000 : 0x50000000;
    *v = w;
    *(int **)((char *)a0 + 0xC) = v;
    *(int **)a0 = v + 1;
}

int func_00245228(Pool241748 *a0) {
    int n = (int)a0->end - 4;
    int *p = a0->cur;
    a0->cur = 0;
    n -= (int)p;
    n = (unsigned)(n >> 2) >> 2;
    *p = *p + n;
    return n;
}

void func_00245258(void *a0, u128_241778 a1) {
    void **pp = (void **)a0;
    void *p = *pp;
    *(u128_241778 *)p = a1;
    *(void **)((char *)a0 + 0x14) = p;
    *pp = (char *)p + 0x10;
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00245270);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2418A0", func_00245318);

void func_00245398(int **a0, long long a1) {
    int *p = *a0;
    *p++ = (int)a1;
    *a0 = p + 1;
    *p = (int)(a1 >> 32);
}
