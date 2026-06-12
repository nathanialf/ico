#include "common.h"
#include "r5900.h"
#include "vu0.h"
#include "math_private.h"

extern int D_0062BEA0;

void MakeBoundingBox(void) {
    D_0062BEA0 = 0;
}

int MakePacket(void) {
    return D_0062BEA0;
}

extern int D_0070C340[];

int AllocPObj(int a0) {
    return D_0070C340[a0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", InitPObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", FreePObj);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D3C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D4E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D7F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D910);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023DDC0);

extern void *D_006281F8[];
extern void debug_assertMessage(void *a0);
void func_0023DF20(void) {
    do {
        debug_assertMessage(D_006281F8);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023DF40);

extern void *func_00105078(void);
extern void func_001050A8(int a0);

void func_0023E008(int a0, void *a1) {
    func_002400F8(func_00105078());
    *(float *)((char *)a1 + 0xC) = 1.0f;
    func_001050A8((int)a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E048);

extern int D_0054A960[];

void *func_0023E158(void) {
    return D_0054A960;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E168);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E500);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E6E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E7D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EA68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EAC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EB60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EE78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EF88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EFE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023F1D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023F310);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023F490);

extern int func_00100840(void);
extern void func_00100860(void *a0);

int func_0023FB20(void *a0) {
    int r = func_00100840();
    func_00100860(a0);
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FB60);

void func_0023FBE8(void) {
    do {
        func_00100840();
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FC08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FCD0);

void func_0023FDD8(void *a0, void *a1, void *a2) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FE08);

void func_0023FE50(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP_ACC(vopmula.xyz, 4, 5);
    VU0_V3OP(vopmsub.xyz, 6, 5, 4);
    VU0_V3OP(vsub.w, 6, 6, 6);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

float func_0023FE70(void *a0, void *a1) {
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

void func_0023FE98(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_REG("vmul.xyz $vf5, $vf4, $vf4");
    VU0_REG("vaddy.x $vf5, $vf5, $vf5y");
    VU0_REG("vaddz.x $vf5, $vf5, $vf5z");
    VU0_REG(".word 0x4A0503BD");
    VU0_WAIT();
    VU0_REG("vaddq.x $vf5, $vf0, $Q");
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_REG("vsub.xyzw $vf6, $vf0, $vf0");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf6, $vf4, $Q");
    VU0_LSV(sqc2, 6, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FED0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023FF18);

void func_0023FF88(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyzw $vf4, $vf4, $Q");
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void func_0023FFA8(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 5);
    VU0_NOREORDER_END();
    VU0_REG("vdiv $Q, $vf0w, $vf5x");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf4, $vf4, $Q");
    VU0_LSV(sqc2, 4, 0x0, 4);
}

void func_0023FFC8(void *a0, void *a1, void *a2, float t) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_NOREORDER_BEGIN();
    VU0_MFC1(8, 12);
    VU0_QMTC2_NI(8, 6);
    VU0_NOREORDER_END();
    VU0_REG("vaddw.x $vf7, $vf0, $vf0w");
    VU0_REG("vsub.x $vf8, $vf7, $vf6");
    VU0_REG("vmulax.xyzw $ACC, $vf4, $vf6x");
    VU0_REG("vmaddx.xyzw $vf9, $vf5, $vf8x");
    VU0_LSV(sqc2, 9, 0x0, 4);
}

void func_0023FFF0(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00240008(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00240020(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vmul.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00240038(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyzw, 6, 4, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void func_00240050(void *a0, void *a1, void *a2) {
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

void func_00240080(void *a0, void *a1) {
    QCOPY16_NO_NOP("$a2");
}

void func_00240090(void *a0, void *a1) {
    QCOPY64_PARALLEL_NO_NOP("$a2", "$a3", "$t0", "$t1");
}

void func_002400B8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400C8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400D8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400E8(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void func_002400F8(void *a0) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240198);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240240);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002402E8);

extern void func_00240198(int a, int b, float f);
extern void func_002402E8(int a, int b, float f);
extern void func_00240240(int a, int b, float f);

void func_00240390(int a0, int a1, float *fa)
{
    func_00240198(a0, a1, fa[2]);
    func_002402E8(a0, a0, fa[1]);
    func_00240240(a0, a0, fa[0]);
}

void func_002403E0(void *a0, void *a1, float a2, float a3) {
    VU0_MFC1(8, 12);
    VU0_MFC1(9, 13);
    VU0_LSV(lqc2, 6, 0x0, 5);
    VU0_QMTC2_NI(8, 4);
    VU0_QMTC2_NI(9, 5);
    VU0_V3OP_BC(vmaxx.xyzw, 6, 6, 4, x);
    VU0_V3OP_BC(vminix.xyzw, 6, 6, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240408);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002404B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240578);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002405E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002406E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240878);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002408D0);

void func_00240918(void *a0, void *a1) {
    ((float *)a0)[0] = ((float *)a1)[0];
    ((float *)a0)[1] = ((float *)a1)[1];
    ((float *)a0)[2] = ((float *)a1)[2];
}

void func_00240938(void *a0, void *a1, void *a2, float a3) {
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

void func_00240968(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240980);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002409C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240A28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240AB8);

void func_00240B18(unsigned char *a0, int a1) {
    int i;
    for (i = a1 - 1; i != -1; i--) {
        *a0++ = 0;
    }
}

extern int D_0054A9D0[];

int func_00240B50(unsigned int a0) {
    if (a0 < 0xA) {
        return D_0054A9D0[a0];
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240B78);

extern int D_0054A9F8_alias[] __asm__("D_0054A9F8");

int func_00240C58(int a0) {
    int old = D_0054A9F8_alias[0];
    D_0054A9F8_alias[0] = a0;
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240C68);

struct __attribute__((packed)) S_240E40 {
    long long a;
    long long b;
    int c __attribute__((aligned(4)));
};
extern struct S_240E40 D_0054AA68;

void *func_00240E40(void *a0) {
    *(struct S_240E40 *)a0 = D_0054AA68;
    return a0;
}

int func_00240E78(unsigned int a0) {
    int old = *(volatile int *)0x1000E060;
    if (a0 != 0xFFFFFFFF) {
        *(volatile int *)0x1000E060 = a0;
    }
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240EA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00240F78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241060);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241148);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241210);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241300);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002413F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002414B8);

int func_00241588(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

int func_002415A8(void *a0) {
    int v = *(int *)a0;
    *(int *)a0 = v & ~0x100;
    return ((unsigned int)v >> 8) & 1;
}

void func_002415C8(int *a0, int a1) {
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

int func_002415D8(int *a0) {
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002415E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241640);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241698);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002416F0);

typedef struct { int *end; int pad[2]; int *cur; } Pool241748;

int func_00241748(Pool241748 *a0) {
    int n = (int)a0->end - 4;
    int *p = a0->cur;
    a0->cur = 0;
    n -= (int)p;
    n = (unsigned)(n >> 2) >> 2;
    *p = *p + n;
    return n;
}

typedef unsigned int u128_241778 __attribute__((mode(TI)));

void func_00241778(void *a0, u128_241778 a1) {
    void **pp = (void **)a0;
    void *p = *pp;
    *(u128_241778 *)p = a1;
    *(void **)((char *)a0 + 0x14) = p;
    *pp = (char *)p + 0x10;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241790);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241838);

void func_002418B8(int **a0, long long a1) {
    int *p = *a0;
    *p++ = (int)a1;
    *a0 = p + 1;
    *p = (int)(a1 >> 32);
}

extern int D_0054AA90[];
extern void func_00242078(int a0);

void func_002418E0(int a0) {
    D_0054AA90[0] = 0;
    func_00242078(a0);
}

void func_002418F0(void) {
    volatile int *p = (volatile int *)0x1000F000;
    *p = 4;
    while ((*p & 4) == 0) {
    }
    *p = 4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241930);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241990);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241A10);

extern int func_002603E0(void);

int func_00241A88(void) {
    *(int *)func_002603E0() = 5;
    return -1;
}

int func_00241AB0(int a1) {
    return -1;
}

int func_00241AB8(void) {
    return -1;
}

int func_00241AC0(int a1, int a2, int a3) {
    return -1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241AC8);

int func_00241B78(void) {
    return 1;
}

int func_00241B80(void *a0, void *a1) {
    *(long long *)((char *)a1 + 0x48) = 0;
    *(int *)((char *)a1 + 0x4) = 0x2000;
    return 0;
}

int func_00241B98(void) {
    return 1;
}

extern void func_00100140(void *a0);

int func_00241BA0(int a0, void *a1) {
    if (a0 == 1) {
        func_00100140(a1);
    }
    return 0;
}

int func_00241BC8(void) {
    *(int *)func_002603E0() = 5;
    return -1;
}

int func_00241BF0(void) {
    *(int *)func_002603E0() = 5;
    return -1;
}

extern volatile int D_0070C680[];

void *func_00241C18(int a0) {
    D_0070C680[0] = a0;
    D_0070C680[2] = (int)&D_0070C680[4];
    D_0070C680[1] = 0;
    D_0070C680[3] = (int)&D_0070C680[4];
    return (void *)D_0070C680;
}

void func_00241C40(int *q)
{
    int count = q[1] + 1;
    char *wp = (char *)q[3] + 1;
    int cap = q[0];
    q[1] = count;
    cap += 0x10;
    {
        char *end = (char *)q + cap;
        q[3] = (int)wp;
        if (wp == end) {
            q[3] = (int)q + 0x10;
        }
    }
}

typedef struct { int f0; int f4; char *f8; } RingBuf_241C80;

void func_00241C80(RingBuf_241C80 *a0) {
    a0->f4--;
    a0->f8++;
    if (a0->f8 == (char *)a0 + (a0->f0 + 0x10)) {
        a0->f8 = (char *)a0 + 0x10;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241CC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241E58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242078);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242138);

extern void func_00248058(void);
extern int D_0054AA98[];

void func_002422D8(void) {
    func_00248058();
    D_0054AA98[0] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242300);

void func_002423A8(void *a0) {
    int *p = (int *)a0;
    p[6] = 0;
    p[4] &= 0xFFFFFFFE;
}

int func_002423C8(int *a0) {
    int rem = a0[9] % a0[6];
    int ret = a0[5] + rem * 64;
    a0[9] = rem + 1;
    return ret;
}

int func_002423F8(int *a0, int a1) {
    if (a1 < 0) {
        goto err;
    }
    if (a1 < a0[8]) {
        goto elem;
    }
err:
    return func_002423C8(a0);
elem:
    return a0[7] + a1 * 64;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242438);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002424F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002426A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002426F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002427A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002428E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242978);

int func_00242B68(char *a0) {
    char *p = *(char **)a0;
    if (p == 0) goto ret0;
    if (*(int *)(a0 + 4) != *(int *)(p + 0x18)) goto ret0;
    if (*(int *)(p + 0x10) & 1) goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242C40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242D10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242DA8);

extern void func_00101A40(int *self);
extern void func_00101A88(void);

int *func_00242E38(int *self)
{
    int *p;
    int v;
    func_00101A40(self);
    p = (int *)self[0xC/4];
    if (p == 0) {
        self[0x4/4] = 0;
        goto after;
    }
    v = p[0x3C/4];
    self[0x4/4] = 1;
    self[0xC/4] = v;
after:
    func_00101A88();
    return p;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00242E90);

extern void func_00242E90(int);
extern void func_00100440(void);

void func_00243058(int a0)
{
    for (;;) {
        int v;
        while ((v = func_00242E38(a0)) != 0) {
            func_00242E90(v);
        }
        func_00100440();
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243098);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002430F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243180);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002431F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002435A8);

extern void func_002435A8(void);
extern void func_00100560(int a0);
extern int D_0054AB24[];

int func_002435F8(void) {
    func_002435A8();
    func_00100560(D_0054AB24[0]);
    return 0;
}

extern int D_0054AB24[];
extern void func_00100540(int a0);

void func_00243628(void) {
    func_00100540(D_0054AB24[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243638);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002437D8);

extern int D_0054AB20[];
extern char D_0070F5A8[];
extern void func_00260568(void *a0, int a1, int a2);

int func_00243868(void) {
    D_0054AB20[0] = 0;
    func_00260568(D_0070F5A8, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002438A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243B28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243EE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244150);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244760);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244938);

extern int func_00244938(void *a0, int a1);

int func_00244AE0(void *a0) {
    return func_00244938(a0, 6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244B00);

int func_00244CB0(void *a0) {
    return func_00244938(a0, 8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244CD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244F40);

int func_00245060(void *a0) {
    return func_00244938(a0, 0x10);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245080);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245288);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002453E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245580);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002457C0);

int func_002459B0(void *a0) {
    return func_00244938(a0, 0x12);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002459D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245B68);

int func_00245DD8(void *a0) {
    return func_00244938(a0, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246608);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246690);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246700);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246778);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246968);

extern int D_0054AB38[];
extern char D_0070FA28[];

int func_002469F8(void) {
    D_0054AB38[0] = -1;
    func_00260568(D_0070FA28, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246A30);

extern int func_00246A30(void *a0, int a1, int a2, void *a3);

void func_00246C38(void *a0, int a1, int a2) {
    int local[4];
    func_00246A30(a0, a1, a2, &local);
}

int func_00246C58(void *a0, int a1, int a2, void *a3) {
    return func_00246A30(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246C78);

extern void func_00246C78(void *a0, int a1, int a2, int a3, int a4);

void func_00246EA0(void *a0, int a1, int a2) {
    int local;
    func_00246C78(a0, a1, a2, (int)&local, 0);
}

void func_00246EC0(void *a0, int a1, int a2, int a3) {
    do {
        func_00246C78(a0, a1, a2, a3, 0);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246EE0);

extern int func_00246EE0(void *a0, int a1, int a2, int a3);

int func_00246FE8(void *a0, int a1, int a2) {
    return func_00246EE0(a0, a1, a2, 1);
}

extern char D_00628838[];

int func_00247008(void *a0, int a1) {
    return func_00246EE0(a0, (int)D_00628838, a1, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247200);

extern int func_00100930(int a0);

int func_00247330(void) {
    int t = func_00100930(4) & 0x10000;
    return t != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247358);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002473A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002474B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247548);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247608);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247650);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002476A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002476F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247820);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247880);

/* func_00247908 — hand-written PS2 EE syscall stub: syscall number in $v1,
 * then `syscall 0`. .set noreorder keeps the bare nop in the jr delay slot. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247908\n"
    "    addiu      $3, $0, 0x74\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247908\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_0054AB88[];
extern void func_00247908(int x, int y);

void func_00247918(void)
{
  int *p = D_0054AB88;
  unsigned int i = 0;
  do
  {
    i++;
    func_00247908(p[0], p[1]);
    p += 2;
  }
  while (i < 6);
}

/* func_00247968 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247968\n"
    "    addiu      $3, $0, 0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247968\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247978 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247978\n"
    "    addiu      $3, $0, -0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247978\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247988 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247988\n"
    "    addiu      $3, $0, 0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247988\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247998 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_00247998\n"
    "    addiu      $3, $0, -0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_00247998\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479A8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479A8\n"
    "    addiu      $3, $0, 0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479A8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479B8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479B8\n"
    "    addiu      $3, $0, -0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479B8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479C8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479C8\n"
    "    addiu      $3, $0, 0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479C8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479D8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479D8\n"
    "    addiu      $3, $0, -0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479D8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002479E8 — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002479E8\n"
    "    addiu      $3, $0, 0x59\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel func_002479E8\n"
    /* 8 bytes of trailing nop padding before the next (16-aligned) func */
    "    nop\n"
    "    nop\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247A00);

void func_00247D80(int *a0, int *a1) {
    a1[2] = a0[4];
}

extern int D_00710F00[];

int func_00247D90(int a0) {
    return D_00710F00[a0];
}

int func_00247DA8(int a0, int a1) {
    D_00710F00[a0] = a1;
    return a1;
}

extern int D_00710DD8[];

void *func_00247DC8(void) {
    return D_00710DD8;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247DD8);

extern int func_00100AD8(int a0);
extern int func_00100250(int a0, int a1);
extern int D_00710DD4[];
extern int D_0054ABB8[];

void func_00248058(void) {
    func_00100AD8(5);
    func_00100250(5, D_00710DD4[0]);
    D_0054ABB8[0] = 0;
}

extern int D_00710DD8[];

int func_00248090(int a0, int a1) {
    int old = D_00710DD8[5];
    D_00710DD8[5] = a0;
    D_00710DD8[6] = a1;
    return old;
}

int func_002480A8(int a0, int a1) {
    int old = D_00710DD8[3];
    D_00710DD8[3] = a0;
    D_00710DD8[4] = a1;
    return old;
}

extern int D_00710DE4[];
extern int D_00710DEC[];

int func_002480C0(int a0, int a1, int a2) {
    int off = a0 * 8;
    int *p;
    if (a0 >= 0) goto pos;
    a0 = D_00710DE4[0];
    goto done;
pos:
    a0 = D_00710DEC[0];
done:
    off += a0;
    p = (int *)off;
    p[0] = a1;
    p[1] = a2;
}

void func_002480F0(int a0) {
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_00710DE4[0];
    } else {
        a0 = D_00710DEC[0];
    }
    off += a0;
    *(int *)off = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248118);

int func_00248250(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = func_00248118(a0, 0, a1, a2, a3, t0, t1);
  return v;
  asm __volatile__("" : : : "memory");
}

extern int func_00248118(int a0, int a1, int a2, int a3, int t0, int t1, int t2);

int func_00248290(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = func_00248118(a0, 1, a1, a2, a3, t0, t1);
  int new_var;
  new_var = v;
  return new_var;
  asm __volatile__("" : : : "memory");
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002482D0);

/* Hand-written EE assembly (NOT a C-match target) — a cache / INTC
 * critical-section module:
 *   func_002483F8  DCache hit-writeback-invalidate loop (cache 0x18 / sync).
 *   func_002484A4  + func_002484AC are ONE routine splat over-split: the ISR.
 *                  Its real entry is func_002484A4 + 0x4 (the addiu $sp,-0x10),
 *                  which func_002484D0 installs via %hi/%lo(func_002484A4 + 0x4);
 *                  the body ends with `ei` (enable interrupts, COP0).
 *   func_002484D0  installs that ISR and toggles INTC enable.
 * `ei`, `cache`, and the address-of-instruction callback cannot be emitted by
 * ee-gcc. func_002484A4 is short enough to author inline below; the rest stay
 * as assembled .s (byte-identical via INCLUDE_ASM). */
INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002483F8);

/* func_002484A4 — hand-written: bare-return entry whose delay slot doubles as
 * the prologue (addiu $sp,-0x10) of the ISR installed at func_002484A4+0x4.
 * .set noreorder keeps the addiu in the jr delay slot as written. */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel func_002484A4\n"
    "    jr         $31\n"
    "    addiu      $29, $29, -0x10\n"
    "endlabel func_002484A4\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002484AC: handwritten ISR thunk (ei/sync, asymmetric hand-frame).
 * C-inexpressible: an honest 33-hypothesis stall floored at rc3 (the entry
 * frame adjust, sync, and ei cannot be emitted by ee-gcc 2.9). Written as
 * in-file handwritten asm per maintainer exception (one-off). */
__asm__(
    ".section .text
"
    "    .set at
"
    "    .set noreorder
"
    "    .global func_002484AC
"
    "    .type func_002484AC, @function
"
    "func_002484AC:
"
    "    sd    $31, 0x0($29)
"
    "    jal   func_00100550
"
    "    daddu $4, $6, $0
"
    "    sync
"
    "    ei
"
    "    ld    $31, 0x0($29)
"
    "    jr    $31
"
    "    addiu $29, $29, 0x10
"
    "    .size func_002484AC, . - func_002484AC
"
    "    .set reorder
"
    "    .set at
"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002484D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248538);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248590);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248630);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002487C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248900);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248980);

extern void (*D_00710F84[])(int);
extern int D_0054ABE4[];
extern int D_00710F88[];

void func_002489F0(void) {
    if (D_00710F84[0] != 0 && D_0054ABE4[0] == 0) {
        D_00710F84[0](D_00710F88[0]);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248A30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248BB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002490C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249160);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002491D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249340);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249620);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249818);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002498E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249AC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249C18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249CB0);

extern int D_0054C630[];
extern int D_00711258[];
extern int func_0024A0C0(int a0, int a1, int a2, int a3, void *a4);

int func_00249D48(int a0, int a1, int a2) {
    D_0054C630[0] = 0;
    return func_0024A0C0(a0, a1, a2, 5, D_00711258);
}

int func_00249D78(int a0, void *a1) {
    D_0054C630[0] = 1;
    return func_0024A0C0(a0, 0, 0, 1, a1);
}

int func_00249DB0(int a0) {
    return func_0024A0C0(a0, 0, 0, 9, D_00711258);
}

int func_00249DE0(int a0) {
    return func_0024A0C0(a0, 0, 0, 4, D_00711258);
}

int func_00249E10(void) {
    D_0054C630[0] = 0;
    return func_0024A0C0(0, 0, 0, 3, D_00711258);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249E48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249FD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A020);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A078);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A0C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A228);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A358);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A498);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A538);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A5B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A7A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A858);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A8B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A908);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A988);

extern int D_0054C650[];
extern unsigned char D_00628D28[];
extern void func_002614F8(char *a0, int a1);

void func_0024AA00(int a0, char *a1) {
    if ((unsigned int)a0 < 8) {
        func_002614F8(a1, D_0054C650[a0]);
    } else {
        *a1 = D_00628D28[0];
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AA38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AAA0);

extern int D_0054C670[];

void func_0024AAF0(int a0, char *a1) {
    if ((unsigned int)a0 < 4) {
        func_002614F8(a1, D_0054C670[a0]);
    } else {
        *a1 = D_00628D28[0];
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AB28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AC48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AD68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AEA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AF58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B010);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B0E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B1A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B250);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B2B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B308);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B360);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B430);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B498);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B500);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B5D0);

extern char D_00712C00[];
extern char D_0054C690[];
extern int D_0054C694[];
extern char D_00711640[];

void *func_0024B788(int *a0, int *a1) {
    a0[0] = (int)D_00712C00;
    a1[0] = (int)D_0054C690;
    *(int *)(D_00712C00 + 0x3C) = D_0054C694[0];
    return D_00711640;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B7B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B930);

extern int func_0024B930(int a0, int a1, int a2, int a3);

int func_0024BA68(int a0, int a1, int a2) {
    int ret = func_0024B930(a0, a1, a2, 0x40);
    if (ret == 0) {
        *(int *)D_0054C690 = 0xB;
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BAA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BB58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BC30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BCC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BDE0);

extern void func_00100F18(int a0);

void func_0024BF60(int a0, int a1, int a2) {
    func_00100F18(a2);
    SYNC();
    EI();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BF88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BFD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C0B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C108);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C3E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C470);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C5C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C7B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CA40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CBA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CC70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CD88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CE10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D010);

extern void func_0024D010(void *a0, int a1, int a2, int a3, int a4);
void func_0024D300(void *a0, int a1, int a2) {
    do {
        func_0024D010(a0, a1, a2, 0, -1);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D320);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D418);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024D5D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DB60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DC00);

int func_0024DE40(void) {
    return 1;
}

extern int D_0054C768[];
extern int D_0054C880[];
extern void func_0024E978(int a0, int a1);

void func_0024DE48(int a0, int a1, int a2) {
    int rounded = (a2 + 0x13) / 16 * 16;
    D_0054C768[0] = a1;
    D_0054C880[0] = rounded;
    func_0024E978(a1, rounded);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DE80);

void func_0024DEC8(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int new_var;
  p[0xE4 / 4] = a2;
  new_var = 0xD8;
  p[new_var / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  p[0xDC / 4] = 0;
 do { } while (0);
  p[0xB0 / 4] = 0;
  p[0xE0 / 4] = 0;
  func_0024E260((int) self);
  asm __volatile__("" : : : "memory");
}

extern void func_0024E260(int self);

void func_0024DF10(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int prod;
  p[0xE0 / 4] = a3 << 4;
  p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  prod = a2 * a3;
  p[0xE4 / 4] = prod;
  p[0xDC / 4] = a2 << 4;
  p[0xB0 / 4] = 0;
  func_0024E260((int) self);
  asm __volatile__("" : : : "memory");
}

void func_0024DF60(void *a0, int a1, int a2, int a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x25] = a1;
    p[0x26] = a2;
    p[0x27] = a3;
}

void func_0024DF78(void *a0, int *a1, int *a2, int *a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    *a1 = *(int *)((char *)p + 0x94);
    *a2 = *(int *)((char *)p + 0x98);
    *a3 = *(int *)((char *)p + 0x9C);
}

int func_0024DF98(int **a0) {
    return a0[0x10][0];
}

int func_0024DFA8(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    return *(int *)((char *)p + 0x4) == 0;
}

extern void func_0024E818(void);
extern void func_0024E730(void);
extern int D_0054C884_b[] __asm__("D_0054C884");

void func_0024DFB8(int *a0) {
    int *p = (int *)a0[0x10];
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    a0[2] = 0;
    p[0x20] = -1;
    p[0x2B] = 0;
    func_0024E818();
    D_0054C884_b[0] = 0;
    func_0024E730();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024DFF8);

int func_0024E060(void *a0, int a1, int a2, int a3) {
    char *p = *(char **)((char *)a0 + 0x40);
    char *q0 = p + 0xC;
    int *q = (int *)(q0 + a1 * 8);
    int old;
    p += a1 * 8;
    ((int *)p)[4] = a3;
    old = *q;
    *q = a2;
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E088);

extern void func_0024E088(void *a0, void *a1);

void func_0024E0D8(void *a0) {
    int buf[8];
    buf[0] = 1;
    func_0024E088(a0, buf);
}

void func_0024E100(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x1C] = 1;
    *(long long *)((char *)p + 0x78) = a1;
}

void func_0024E118(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    *(int *)((char *)p + 0x70) = 0;
    *(long long *)((char *)p + 0x78) = 0;
}

extern void *D_0054C764[];

void func_0024E128(int a0) {
    int *q = *(int **)((char *)D_0054C764[0] + 0x40);
    q[0x36] = a0;
}

int func_0024E140(int **a0) {
    return a0[0x10][0x33];
}

int func_0024E150(int **a0) {
    return a0[0x10][0x34];
}

void *func_0024E160(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

void *func_0024E170(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

int func_0024E180(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x40);
    int old = *(int *)((char *)p + 0xE8);
    *(int *)((char *)p + 0xE8) = a1;
    return old;
}

void func_0024E190(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    *(long long *)((char *)p + 0xF0) = a1;
    p[0x3E] = 1;
}

void func_0024E1A8(int *a0, int a1, int a2) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a1;
    a0[3] = a1;
}

void func_0024E1C0(int *a0) {
    a0[3] = a0[2];
}

void func_0024E1D0(int *a0) {
    a0[2] = a0[3];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E1E0);

int func_0024E248(int *a0) {
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E3E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E510);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E6C0);

extern int D_0054D030_alias[] __asm__("D_0054D030");
extern void func_00251088(int a0);

void func_0024E730(void) {
    D_0054D030_alias[0] = 0;
    func_00251088(1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E740);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E7C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E818);

extern int D_00628EC8_alias[] __asm__("D_00628EC8");
extern void func_00260668(void *a0, int a1);

void func_0024E8E0(int a0) {
    func_00260668(D_00628EC8_alias, a0);
}

extern void func_00261188(void *a0, int a1, int a2);
extern void func_0024E920(void *a0);

void func_0024E8F0(int a0, int a1) {
    char buf[0x100];
    func_00261188(buf, a0, a1);
    func_0024E920(buf);
}

void func_0024E920(void *a0)
{
    char *p = D_0054C764[0];
    if (p != 0) {
        register int q = *(int *)(p + 0x40);
        if (q != 0) {
            register int r = *(int *)(q + 0xC);
            if (r != 0) {
                int local[2];
                local[0] = 0;
                local[1] = (int)a0;
                func_0024E088((int)p, local);
                return;
            }
        }
    }
    func_0024E8E0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E978);

int func_0024EA50(int *a0, int a1, int a2) {
    a0[0x4 / 4] = a1;
    a0[0x8 / 4] = a2;
    a0[0xC / 4] = a1 >> 4;
    a0[0x10 / 4] = a2 >> 4;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EA70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EBC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EF10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EFF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F0B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F220);

extern void func_0024E920(void *a0);
extern int D_00628F38[];

void func_0024F2C0(void) {
    func_0024E920(D_00628F38);
}

extern int D_00628F68[];
extern int D_00628F80[];
extern int D_00628FB8[];

void func_0024F2D0(void) {
    func_0024E920(D_00628F68);
}

void func_0024F2E0(void) {
    func_0024E920(D_00628F80);
}

void func_0024F2F0(void) {
    func_0024E920(D_00628FB8);
}

extern void func_00254A88(void *a0);
extern void func_00254B70(void *a0);

void func_0024F300(int **a0) {
    func_00254A88((char *)a0[0x10] + 0x4C);
}

void func_0024F310(int **a0) {
    func_00254B70((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F320);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F658);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024FD08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250128);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002502B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250330);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002503C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250480);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250600);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002506B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002507B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002508B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250958);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250A08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250AF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250BD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250CB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250D88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250EB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00250FC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251028);

void func_00251088(int a0) {
    volatile int *reg = (volatile int *)0x10002010;
    *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002510B0);

extern int func_00252468(int a0);

int func_00251298(void) {
    return func_00252468(3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002512B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251550);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251678);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002517A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002519A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251A70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251F98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252020);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002521A0);

extern int D_0054D088[];
extern int D_0054C7A4[];

void func_002522E0(unsigned int a0) {
    *(volatile unsigned int *)0x10002000 = a0;
    D_0054C7A4[0] = D_0054D088[a0 >> 28];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252310);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002523B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252468);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252620);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252758);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252870);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002529D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252A40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252AB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252BD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252D58);

extern void func_00252758(int a0);
extern int func_00252870(int a0);

void func_00252F88(void) {
    while (func_00252870(1)) {
        func_00252758(8);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002530A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253188);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253238);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253328);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002533D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002534B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253570);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253950);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002539F0);

extern int D_0054C884[];
extern int D_0054D000[];

int func_00253BE0(void) {
    int *q = *(int **)((char *)D_0054C764[0] + 0x40);
    if (q[2] != 2) {
        int v = D_0054C884[0];
        q[2] = 2;
        q[0x2B] = v;
    }
    D_0054D000[0] = 1;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253C18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253DB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00253EC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254088);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002542B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254478);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254550);

extern void func_00254800(int *a0, int a1);

void func_002547A8(int *a0, int a1, int a2, int a3) {
    a0[2] = a1;
    a0[3] = a1;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = 0;
    a0[8] = a2;
    a0[9] = a2 + a3;
    a0[0xA] = a3;
    func_00254800(a0, 0);
}

int func_002547E0(void *a0, int a1) {
    unsigned long long v = *(unsigned long long *)a0;
    return v >> (64 - a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254800);

int func_00254898(int *self, int a1)
{
    int ret = func_002547E0(self, a1);
    func_00254800(self, a1);
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002548E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254930);

int func_00254988(int *a0, int a1) {
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002549B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254A20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254A88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254B70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254CC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254D28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254D90);

extern unsigned char D_00713C80[];

void *func_00254FC8(int a0) {
    return &D_00713C80[a0 * 0x58];
}

extern unsigned char D_00714D00[];

void *func_00254FE0(int a0) {
    return &D_00714D00[a0 * 0x54];
}

extern int D_00715CC0[];

void *func_00254FF8(void) {
    return D_00715CC0;
}

extern unsigned char D_00713680[];

void *func_00255008(int a0) {
    return &D_00713680[a0 * 0xC];
}

extern int D_00717F80[];

void func_00255020(int a0, int a1) {
    D_00717F80[a0] = a1;
}

int func_00255038(int a0) {
    return D_00717F80[a0];
}

extern int D_00717F80[];
extern int D_00718180[];
extern int D_00717F40[];

void *func_00255050(void) {
    return D_00717F80;
}

void *func_00255060(void) {
    return D_00718180;
}

int func_00255070(void) {
    return D_00717F40[0];
}

extern unsigned char D_00715D40[];

void *func_00255080(int a0, int a1) {
    unsigned char *p = &D_00715D40[a1 * 0x10];
    return (void *)(a0 * 0x1000 + (int)p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002550A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255580);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255618);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255A38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00255ED8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002565E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002567C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256960);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256A98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256CD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256E18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256F20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256FA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256FF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257190);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257220);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002572F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257380);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257570);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002576E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257838);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002579F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257C10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257D28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257DE8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258168);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002581F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258328);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258438);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258490);

int func_00258650(int a0, int a1, int a2, int a3) {
    return ((a0 & 0xFF) + ((a1 & 0xFF) - (a0 & 0xFF)) * (a3 & 0xFF) / (a2 & 0xFF)) & 0xFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258820);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258870);

extern int func_00242B68(char *p);
extern char D_007181C0[];

int func_00258900(void)
{
    int ret = 0;
    int *p = func_00254FF8();
    if (p[0x44 / 4] != 0) {
        ret = func_00242B68(D_007181C0);
    }
    return ret;
}

extern void func_00258688(int a0);

void func_00258948(void) {
    func_00258688(0);
}

void func_00258950(void) {
    func_00258688(1);
}

void func_00258958(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        func_00255580(0xB, i, 0xFFFFFF, 0);
        func_00255580(0x28, i, 0, 0);
    }
    func_00255580(0x1F, 0, 0, 0);
}

extern void func_002550A0(void);

void func_002589C8(void) {
    void *r = func_00254FF8();
    if (*(int *)((char *)r + 0x44)) {
        func_002550A0();
    }
}

extern void func_00255580(int a0, int a1, int a2, int a3);

void func_002589F8(int a0) {
    func_00255580(0x32, 0xA, a0, 0);
}

extern void func_00258A68(int a0, int a1, void *a2, void *a3);

int func_00258A10(int a0, void *a1, void *a2) {
    func_00258A68(0x20, a0, a1, a2);
    return 0;
}

extern void func_00258A68(int a0, int a1, void *a2, void *a3);

int func_00258A40(void *a0, int a1, void *a2) {
    func_00258A68(0x21, a1, a0, a2);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258A68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258AF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258B88);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258BF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258CF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258E50);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258FB8);

void func_00259040(int a0, int a1) {
    func_00255580(0x14, a0, a1, 0);
}

void func_00259058(int a0, int a1) {
    func_00255580(0x15, a0, a1, 0);
}

void func_00259070(int a0, int a1, int a2) {
    func_00255580(0x16, a0, a1, a2);
}

void func_00259088(int a0, int a1) {
    func_00255580(0x17, a0, a1, 0);
}

void func_002590A0(int a0, int a1) {
    func_00255580(0x18, a0, a1, 0);
}

void func_002590B8(int a0) {
    void *r = func_00254FF8();
    *(short *)((char *)r + 0x38) = a0;
}

void func_002590E0(int a0) {
    void *r = func_00254FF8();
    *(short *)((char *)r + 0x3A) = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259108);

void func_00259208(int a0, int a1, int a2) {
    func_00255580(0x28, a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259220);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002592C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259350);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002593F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259668);

int func_00259710(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        void *r = func_00254FE0(a0);
        ret = *(unsigned short *)((char *)r + 0x1E);
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259740);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002597C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259878);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259958);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259B80);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259CB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259D58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259E68);

int func_0025A040(unsigned int a0) {
    if (a0 < 0x30) {
        unsigned char *p = (unsigned char *)func_00254FC8(a0);
        if (p[0x51] == 3) {
            p[0x51] = 0;
        }
    }
    return -1;
}

void func_0025A080(void) {
    func_00255580(0x3C, 0, 0, 0);
}

void func_0025A098(void) {
    func_00255580(0x3D, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A0B0);

int func_0025A140(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        func_00255580(0x3F, a0, 0, 0);
        ret = 0;
    }
    return ret;
}

int func_0025A180(unsigned long long a0, unsigned int a1, int a2)
{
    int ret = -1;
    if (a1 < 0x4000 && a2 >= 0 && a2 < 0x4000 && (a0 & 0xFF000000) == 0) {
        func_00255580(0x40, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), (a1 << 16) | a2);
        ret = 0;
    }
    return ret;
}

int func_0025A208(unsigned long long a0, int a1)
{
    int ret = -1;
    if (((a0 & 0xFF000000) == 0) && (a1 >= 0) && (a1 <= 0x2EE00)) {
        func_00255580(0x41, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), a1);
        ret = 0;
    }
    return ret;
}

int func_0025A280(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        func_00255580(0x42, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}

int func_0025A2E0(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        func_00255580(0x43, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A340);

void func_0025A3B0(void) {
    func_00255580(0x46, 0, 0, 0);
}

void func_0025A3C8(void) {
    func_00255580(0x47, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A3E0);

int func_0025A450(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x10) {
        func_00255580(0x49, a0, 0, 0);
        ret = 0;
    }
    return ret;
}

void func_0025A490(int a0) {
    func_00255580(0x4E, a0, 0, 0);
}

int func_0025A4A8(unsigned long long a0) {
    if ((a0 & 0xFF000000) == 0) {
        func_00255580(0x4B, (int)a0, 0, 0);
    }
    return 0;
}

int func_0025A4E8(unsigned long long a0) {
    if ((a0 & 0xFF000000) == 0) {
        func_00255580(0x4C, (int)a0, 0, 0);
    }
    return 0;
}

int func_0025A528(unsigned int a0, unsigned int a1)
{
    int ret = -1;
    if (a0 < 0x10) {
        if (a1 <= 0x1FFFFF) {
            func_00255580(0x4D, (int)a0, (int)a1, 0);
            ret = 0;
        }
    }
    return ret;
}

void func_0025A578(unsigned long long a0, unsigned int a1, int a2)
{
    if (a1 <= 0x7FFF && a2 >= 0 && a2 <= 0x7FFF && (a0 & 0xFF000000) == 0) {
        func_00255580(0x4A, (int)a0, a1, a2);
    }
}

int func_0025A5C8(unsigned int a0)
{
    int ret = 0;
    if (a0 < 0x10) {
        int *p = func_00255070();
        ret = *(int *)((char *)p + (a0 << 2) + 0x180);
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A610);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A678);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A768);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025AA90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025ABD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B3A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B8D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025BCB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025BDF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025BF48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025C898);

extern void func_0025F4A0(long a0, long a1);

int func_0025C9A0(void *a0) {
    long p = *(long *)((char *)a0 + 8);
    func_0025F4A0(p, p);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025C9C8);

/* fabsf(x) via the standard IEEE-754 bit twiddle: clear the sign bit. */
float func_0025CC70(float a0) {
    unsigned int ix;
    GET_FLOAT_WORD(ix, a0);
    SET_FLOAT_WORD(a0, ix & 0x7fffffff);
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CC90);

/* isnanf(x) via the standard IEEE-754 bit test: NaN iff |x| bits > 0x7F800000 (+inf). */
int func_0025CD78(float x) {
    int hx;
    GET_FLOAT_WORD(hx, x);
    hx &= 0x7fffffff;
    hx = 0x7f800000 - hx;
    return (unsigned)hx >> 31;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CDA0);

/* copysignf(x, y): magnitude of x with the sign of y, via IEEE-754 bit twiddle. */
float func_0025CF00(float a0, float a1) {
    unsigned int ix, iy;
    GET_FLOAT_WORD(ix, a0);
    GET_FLOAT_WORD(iy, a1);
    SET_FLOAT_WORD(a0, (ix & 0x7fffffff) | (iy & 0x80000000));
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF88);

/* D_007181E8 is a .bss global splat left as a raw lui/lw (no name); declared in
 * symbol_addrs + defined for the linker in undefined_funcs_extra.aug6.txt so the
 * %hi/%lo base reuses one reg like the ROM. Byte-identical in the link
 * (ninja verify_elf OK); match_diff shows a residual only because the reference
 * .s keeps the raw value rather than %hi(D_007181E8). */
extern int D_007181E8[];
extern void func_0025CF88(void);
void func_0025D038(void) {
    if (D_007181E8[0] == 0) {
        D_007181E8[0] = 1;
        func_0025CF88();
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D058);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D838);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025D8D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025DF38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025DF98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025E568);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EAA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EBD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EC78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EEB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EF10);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EF78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F220);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F388);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F4A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F4F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F5A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F640);

extern void func_0025EBD8(void *in, void *out);
extern void func_0025EAA8(void *s);

void func_0025F6E0(long long a0) {
    struct { int a, b, c, pad; long long d; } s;
    long long t = a0;
    func_0025EBD8(&t, &s);
    s.b = (s.b == 0);
    func_0025EAA8(&s);
}

extern void func_0025EAA8(void *s);

int func_0025F718(int a0, int a1, int a2, long long a3) {
    struct { int a, b, c, pad; long long d; } s;
    s.a = a0;
    s.b = a1;
    s.c = a2;
    s.d = a3;
    func_0025EAA8(&s);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F7A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F8B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F940);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FB78);

int func_0025FBD0(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    func_0025F8B0(buf + 0x30, buf);
    func_0025F8B0(buf + 0x34, buf + 0x10);
    *(int *)(buf + 0x14) ^= 1;
    ret = func_0025F940(buf, buf + 0x10, buf + 0x20);
    return func_0025F7A0(ret);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FC38);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FE30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025FF90);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002600A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002600F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002601B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260240);

extern void func_0025F8B0(void *a0, void *a1);
extern int func_0025F7A0(void *s);

int func_002602D8(float f12)
{
    int o[4];
    float in[4];
    in[0] = f12;
    func_0025F8B0(in, o);
    o[1] = (o[1] == 0);
    return func_0025F7A0(o);
}

void func_00260310(int a0, int a1, int a2, int a3) {
    int buf[4];
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = a3;
    func_0025F7A0(buf);
}

int func_00260340(float f12)
{
    int local0[4];
    float local1[4];
    long long a3_val;
    local1[0] = f12;
    func_0025F8B0(local1, local0);
    a3_val = (long long)(unsigned int)local0[3] << 32;
    return func_0025F718(local0[0], local0[1], local0[2],
                         (long long)((unsigned long long)a3_val >> 2));
}

extern int D_0054D504[];
extern char D_00629E08[];
extern void func_002603F0(int a0, int a1, ...);
extern void func_00265298(void);

void func_00260380(int a0, int a1, int a2) {
    func_002603F0(*(int *)(D_0054D504[0] + 0xC), (int)D_00629E08, a2, a0, a1);
    func_00265298();
}

extern long long func_00261E80(void *a0, int a1, int a2);

int func_002603B8(void *a0) {
    return (int)func_00261E80(a0, 0, 0xA);
}

extern int D_0054D504[];

int func_002603E0(void) {
    return D_0054D504[0];
}

extern void func_00261FB8(int a0, int a1, void *args);

/* printf-style forwarder: va_start points at the homed vararg GP regs
 * (the 6 slots, 6*8 = 48 bytes, just below __builtin_next_arg). */
void func_002603F0(int a0, int a1, ...) {
    char *ap = (char *)__builtin_next_arg(a1) - 48;
    func_00261FB8(a0, a1, ap);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260424);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002604B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260568);

extern int func_00262D78(int *self, int subj, int b, void *args);

int func_00260628(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return func_00262D78(self, self[2], b, args);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00260668);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002606B8);

extern void *D_0054D504_alias[] __asm__("D_0054D504");

void func_002610E0(int a0) {
    char *p = (char *)D_0054D504_alias[0];
    *(int *)(p + 0x58) = a0;
}

int func_002610F0(void) {
    char *p = (char *)D_0054D504_alias[0];
    int s = *(int *)(p + 0x58) * 0x41C64E6D + 0x3039;
    *(int *)(p + 0x58) = s;
    return s & 0x7fffffff;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261120);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261188);

int func_002611F8(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261200);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261288);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002613B4);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002614F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026160C);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261900);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261AC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261B10);

extern int D_0054D504[];
extern int func_00261BA8(int a0, int a1, int a2);

int func_00261B80(int a0, int a1) {
    return func_00261BA8(a0, a1, D_0054D504[0] + 0x5C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261BA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261C48);

extern long long func_00261C48(void *a0, void *a1, int a2, int a3);

long long func_00261E80(void *a0, int a1, int a2) {
    return func_00261C48((void *)D_0054D504[0], a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261EB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261F00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261FB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262030);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264520);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265028);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265130);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265188);

extern int func_002697C0(int a0);
extern void InitDelayFree(int a0);
void func_00265298(void) {
    for (;;) {
        func_002697C0(6);
        InitDelayFree(1);
    }
}

extern int func_0026A958();

int func_002652B8(void *a0) {
    return func_0026A958(a0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002652D8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002654F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002666C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002667C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266820);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266890);

extern int func_002666C0(void);
extern void func_002673A8(int a0, void *a1);

void func_00266970(int a0) {
    func_002673A8(a0, func_002666C0);
}

void func_00266980(void) {
    func_00266970(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266990);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266A20);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266B40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266E60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266FD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002673A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267440);

extern int D_0062A818[];

void *func_002674C8(int a0) {
    return D_0062A818;
}

extern int func_00267440(void *a0, int a1, int a2);

int func_002674D8(int a0, int a1) {
    return func_00267440(D_0054D504_alias[0], a0, a1);
}

void *func_00267508(void) {
    return func_002674C8(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267530);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00267680);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002678D8);

int func_00268050(int a0, int *a1, unsigned char *a2, int a3) {
    int local;
    int *p = &local;
    if (a1 != 0) p = a1;
    if (a2 == 0) goto zero;
    if (a3 != 0) goto store;
    return -1;
zero:
    return 0;
store:
    *p = *a2;
    return *a2 != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026808C);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026816C);

void func_00268270(void) {
}

void func_00268278(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268280);

void func_00268328(char *a0, int *a1) {
    if (a1) {
        int off = a1[1] * 4;
        int *slot;
        a0 = *(char **)(a0 + 0x4C);
        off += (int)a0;
        slot = (int *)off;
        a1[0] = slot[0];
        slot[0] = (int)a1;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268358);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268470);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002685B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268640);

extern int *func_00268280(void *a0, int a1);

void *func_00268700(void *a0, int a1) {
    int *r = func_00268280(a0, 1);
    r[5] = a1;
    r[4] = 1;
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268738);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268968);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268A68);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268BE0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268E70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00268FF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269230);

int func_002692A0(void) {
    return func_002666C0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002692C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269438);

int func_00269480(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    do { return ((unsigned int)hx) >> 31; } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002694B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269518);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269588);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269618);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269708);

extern int func_00269618(int a0, int a1);

int func_002697C0(int a0) {
    return func_00269618(D_0054D504[0], a0);
}

extern int func_00269588(void *a0, int a1, int a2);

int func_002697E8(int a0, int a1) {
    return func_00269588(D_0054D504_alias[0], a0, a1);
}

extern void *func_00269518(int a0);

void *func_00269818(void) {
    return func_00269518(D_0054D504[0]);
}

extern int func_00269708(int a0, int a1);

int func_00269840(int a0) {
    return func_00269708(D_0054D504[0], a0);
}

extern int D_0062E170[];

int func_00269868(int *self, int a1, int a2)
{
    int ret;
    D_0062E170[0] = 0;
    ret = func_00241BA0(a1, a2);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

int func_002698C8(void) {
    return func_00241B98();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002698E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269950);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002699D0);

extern int func_0026AFA0(int *self, int a1);
int func_00269A38(void *a0) {
    return func_0026AFA0((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE));
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269A58);

extern int func_00269A58(void *a0, int a1, int a2);

int func_0026A958(a0, a1)
int a0, a1;
{
    return func_00269A58(D_0054D504_alias[0], a0, a1);
}

extern int func_0025F748(int a0);

int func_0026A988(void) {
    return func_0025F748(func_0026A958());
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026A9B0);

extern long long func_0026A9B0(void *a0, void *a1, int a2, int a3);

long long func_0026ABD0(void *a0, int a1, int a2) {
    return func_0026A9B0((void *)D_0054D504[0], a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AC08);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026ACF8);

extern int func_00241990(int a1, int a2, int a3);

int func_0026AE80(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0062E170[0] = 0;
    ret = func_00241990(a1, a2, a3);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026AEE0);

int func_0026AFA0(int *self, int a1)
{
    int ret;
    D_0062E170[0] = 0;
    ret = func_00241AB0(a1);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

int func_0026AFF8(int *self, int a1, int a2)
{
    int ret;
    D_0062E170[0] = 0;
    ret = func_00241B80(a1, a2);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

int func_0026B058(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0062E170[0] = 0;
    ret = func_00241AC0(a1, a2, a3);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

extern int func_00241A10(int a1, int a2, int a3);
extern int D_0062E170[];

int func_0026B0B8(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0062E170[0] = 0;
    ret = func_00241A10(a1, a2, a3);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B118);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B730);

extern void func_0026B688(int a0, int a1);

void func_0026B7B0(int a0, int a1) {
    func_0026B688(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B7C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B870);

extern void func_0026B7C8(int a0, int a1);

void func_0026B8F0(int a0, int a1) {
    func_0026B7C8(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026B908);


/* recovered struct shapes */
typedef struct {
    /* width 16 */ unsigned char f_10;  /* 0x10 */
    /* width 16 */ unsigned char f_20;  /* 0x20 */
    /* width 16 */ unsigned char f_30;  /* 0x30 */
    /* width 16 */ unsigned char f_40;  /* 0x40 */
    /* width 16 */ unsigned char f_50;  /* 0x50 */
    /* width 16 */ unsigned char f_60;  /* 0x60 */
    /* width 16 */ unsigned char f_70;  /* 0x70 */
    /* width 16 */ unsigned char f_80;  /* 0x80 */
    /* width 16 */ unsigned char f_90;  /* 0x90 */
    /* width 16 */ unsigned char f_A0;  /* 0xA0 */
    /* width 16 */ unsigned char f_B0;  /* 0xB0 */
    /* width 16 */ unsigned char f_C0;  /* 0xC0 */
    /* width 16 */ unsigned char f_D0;  /* 0xD0 */
    /* width 16 */ unsigned char f_E0;  /* 0xE0 */
    /* width 16 */ unsigned char f_F0;  /* 0xF0 */
    /* width 16 */ unsigned char f_100;  /* 0x100 */
    /* width 16 */ unsigned char f_110;  /* 0x110 */
    /* width 16 */ unsigned char f_120;  /* 0x120 */
    /* width 16 */ unsigned char f_130;  /* 0x130 */
    /* width 16 */ unsigned char f_140;  /* 0x140 */
    /* width 16 */ unsigned char f_150;  /* 0x150 */
    /* width 16 */ unsigned char f_160;  /* 0x160 */
    /* width 16 */ unsigned char f_170;  /* 0x170 */
    /* width 16 */ unsigned char f_180;  /* 0x180 */
    /* width 16 */ unsigned char f_190;  /* 0x190 */
    /* width 16 */ unsigned char f_1C0;  /* 0x1C0 */
    /* width 16 */ unsigned char f_1D0;  /* 0x1D0 */
    /* width 16 */ unsigned char f_1E0;  /* 0x1E0 */
    /* width 16 */ unsigned char f_1F0;  /* 0x1F0 */
} S_00710AC0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_1C;  /* 0x1C */
} S_007115C0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
} S_00710DD8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_007112D0;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
    unsigned int       f_14;  /* 0x14 */
    unsigned int       f_18;  /* 0x18 */
    unsigned int       f_1C;  /* 0x1C */
    unsigned int       f_20;  /* 0x20 */
    unsigned int       f_24;  /* 0x24 */
    unsigned int       f_28;  /* 0x28 */
} S_0070E240;

typedef struct {
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0054D520;  /* stride 0x8 */

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
    /* width 16 */ unsigned char f_20;  /* 0x20 */
    /* width 16 */ unsigned char f_30;  /* 0x30 */
    /* width 16 */ unsigned char f_40;  /* 0x40 */
} S_0054D160;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0054C918;

typedef struct {
    unsigned long long f_0;  /* 0x00 */
} S_0062A870;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0070C340;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00710F00;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_00710FC8;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00717F80;  /* stride 0x4 */

typedef struct {
    unsigned int       f_108;  /* 0x108 */
} S_004CED88;  /* stride 0x10C */

typedef struct {
    unsigned long long f_8;  /* 0x08 */
} S_0054C698;  /* stride 0x10 */

typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_0054D1D0;  /* stride 0x2 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_0070C680;

typedef struct {
    unsigned int       f_C;  /* 0x0C */
    unsigned int       f_10;  /* 0x10 */
} S_0070C790;

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
} S_0054A970;

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
} S_0054A9B0;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054AB48;  /* stride 0x4 */

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_0054C968;

typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
} S_0054C978;

typedef struct {
    /* width 16 */ unsigned char f_0;  /* 0x00 */
    /* width 16 */ unsigned char f_10;  /* 0x10 */
} S_0054D1B0;

typedef struct {
    short              f_0;  /* 0x00 */
} S_0062A350;  /* stride 0x2 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
} S_0062E160;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054A940;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054A9D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054C650;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054C670;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D048;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D068;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D088;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054D0F8;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00629860;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_00629930;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0062A860;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_007113C0;  /* stride 0x100 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00628430;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00628640;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006287C0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00628E90;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006292A0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00629430;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A1E0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A380;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A570;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A800;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0062A990;  /* stride 0x4 */

/* end struct shapes */
