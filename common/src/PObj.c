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

int InitPObj(int a0) {
    int i;
    for (i = 0; i < D_0062BEA0; i++) {
        if (a0 == D_0070C340[i]) {
            return i;
        }
    }
    return -1;
}

extern int D_0062BEA0;
extern int D_0070C340[];
extern void debug_assertMessage();
extern char D_0062DD28[];

void FreePObj(int a0) {
    int i;
    for (i = 0; i < D_0062BEA0; i++) {
        if (a0 == D_0070C340[i]) {
            debug_assertMessage(D_0062DD28, i);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D170);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D260);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D3C0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023D4E8);

typedef struct {
    char pad0[0xFC];
    float fFC;
    float f100;
    char pad104[4];
    union { unsigned char b; unsigned int w; } f108;
} CEntry;
extern CEntry D_004CED88[];
extern void *freeseki(int a0);
extern void func_0010EFE0(void *a0);
extern char D_006280E0[];

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

/* func_0023E168: handwritten VIF/VU0 init — MMIO register pokes, a cfc2/ctc2
 * read-modify-write of VU0 control reg $vi28, sync barriers, and two qword
 * FIFO copies from D_0054A970. In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0023E168\n"
    "    .type func_0023E168, @function\n"
    "    .align 3\n"
    "func_0023E168:\n"
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
    "    lui   $5, %hi(D_0054A970)\n"
    "    lui   $6, 0x1000\n"
    "    addiu $5, $5, %lo(D_0054A970)\n"
    "    ori   $6, $6, 0x5000\n"
    "    lq    $4, 0x0($5)\n"
    "    lui   $3, 0x1000\n"
    "    ori   $3, $3, 0x3000\n"
    "    sq    $4, 0x0($6)\n"
    "    lq    $2, 0x10($5)\n"
    "    sq    $2, 0x0($6)\n"
    "    jr    $31\n"
    "    sw    $7, 0x0($3)\n"
    "    .size func_0023E168, . - func_0023E168\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E1D0);

extern void *func_0023E158(void);

void func_0023E440(void *a0) {
    long *s = (long *)a0;
    if (*(short *)((char *)func_0023E158() + 6) == 1) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E500);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E6E8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E7D0);

int func_0023EA68(void *a0, int a1) {
    int s0 = a1 & 1;
    int ret;
    func_0023E440((char *)a0 + s0 * 0x28);
    if (!s0) goto zero_path;
    ret = func_0023E6E8((char *)a0 + 0x140);
    goto done;
zero_path:
    ret = func_0023E6E8((char *)a0 + 0x50);
done:
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EAC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EB60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023EE78);

int func_0023EF88(long long *a0, int a1) {
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

void func_0023FE08(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x10($5)\n"
        "lqc2 $vf6, 0x20($5)\n"
        "lqc2 $vf7, 0x30($5)\n"
        "addiu $7, $0, 0x4\n"
        "1:\n"
        "lqc2 $vf8, 0x0($6)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf9, $vf7, $vf8w\n"
        "sqc2 $vf9, 0x0($4)\n"
        "addi $7, $7, -0x1\n"
        "addi $6, $6, 0x10\n"
        "bne $0, $7, 1b\n"
        "addi $4, $4, 0x10\n"
        ".set reorder\n"
        ::: "$7", "memory");
}

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

void func_0023FED0(void *a0, void *a1) {
    VU0_LSGP(lq, 8, 0x0, 5);
    VU0_LSGP(lq, 9, 0x10, 5);
    VU0_LSGP(lq, 10, 0x20, 5);
    VU0_LSGP(lq, 11, 0x30, 5);
    VU0_REG("pextlw $12, $9, $8");
    VU0_REG("pextuw $13, $9, $8");
    VU0_REG("pextlw $14, $11, $10");
    VU0_REG("pextuw $15, $11, $10");
    VU0_REG("pcpyld $8, $14, $12");
    VU0_REG("pcpyud $9, $12, $14");
    VU0_REG("pcpyld $10, $15, $13");
    VU0_REG("pcpyud $11, $13, $15");
    VU0_LSGP(sq, 8, 0x0, 4);
    VU0_LSGP(sq, 9, 0x10, 4);
    VU0_LSGP(sq, 10, 0x20, 4);
    VU0_LSGP(sq, 11, 0x30, 4);
}

/* func_0023FF18: handwritten VU0/MMI matrix transpose + transform — packs three
 * qwords via pextlw/pextuw/pcpyld/pcpyud into VU regs, runs a vmulax/vmadda/
 * vmaddz chain, and subtracts. In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .align 3\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0023FF18\n"
    "    .type func_0023FF18, @function\n"
    "func_0023FF18:\n"
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
    "    vmulax.xyz $ACC, $vf6, $vf5x\n"
    "    vmadday.xyz $ACC, $vf7, $vf5y\n"
    "    vmaddz.xyz $vf4, $vf8, $vf5z\n"
    "    vsub.xyz $vf4, $vf9, $vf4\n"
    "    sq    $8, 0x0($4)\n"
    "    sq    $9, 0x10($4)\n"
    "    sq    $10, 0x20($4)\n"
    "    jr    $31\n"
    "    sqc2  $vf4, 0x30($4)\n"
    "    .size func_0023FF18, . - func_0023FF18\n"
    "    .set reorder\n"
    "    .set at\n"
);

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

/* func_00240120: handwritten VU0 macro-mode math kernel — polynomial evaluation
 * with a vsqrt (emitted raw as .word, no gas mnemonic) and a vaddq/vsubq branch
 * selected by $a3. Coefficients from D_0054A9A0. Handwritten per maintainer
 * exception (VU0 macro ops + raw COP2 word). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00240120\n"
    "    .type func_00240120, @function\n"
    "    .align 3\n"
    "func_00240120:\n"
    "    lui   $8, %hi(D_0054A9A0)\n"
    "    addiu $8, $8, %lo(D_0054A9A0)\n"
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
    "    vaddq.x $vf7, $vf0, $Q\n"
    "    b     2f\n"
    "    vaddx.x $vf4, $vf5, $vf7x\n"
    "1:\n"
    "    vsubx.x $vf4, $vf5, $vf7x\n"
    "2:\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00240120, . - func_00240120\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00240198: handwritten VU0 axis-rotation builder. Adjusts the angle into a
 * quadrant (PI/2 +/- a, sign in $7), evaluates sin/cos via func_00240120, builds a
 * rotation matrix in $vf6-$vf9 and transforms 4 vectors. Internal alternate entry
 * func_002401C8 takes the pre-adjusted angle. Handwritten per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00240198\n"
    "    .type func_00240198, @function\n"
    "    .align 3\n"
    "func_00240198:\n"
    "    mtc1  $0, $f0\n"
    "    c.lt.s $f12, $f0\n"
    "    lui   $1, 0x3FC9\n"
    "    ori   $1, $1, 0x0FDB\n"
    "    mtc1  $1, $f0\n"
    "    bc1f  1f\n"
    "    nop\n"
    "    add.s $f12, $f0, $f12\n"
    "    j     func_002401C8\n"
    "    addiu $7, $0, 0x1\n"
    "1:\n"
    "    sub.s $f12, $f0, $f12\n"
    "    daddu $7, $0, $0\n"
    "    .align 3\n"
    "func_002401C8:\n"
    "    mfc1  $8, $f12\n"
    "    qmtc2.ni $8, $vf6\n"
    "    daddu $6, $31, $0\n"
    "    jal   func_00240120\n"
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
    "    vmulax.xyzw $ACC, $vf6, $vf4x\n"
    "    vmadday.xyzw $ACC, $vf7, $vf4y\n"
    "    vmaddaz.xyzw $ACC, $vf8, $vf4z\n"
    "    vmaddw.xyzw $vf5, $vf9, $vf4w\n"
    "    sqc2  $vf5, 0x0($4)\n"
    "    addi  $7, $7, -0x1\n"
    "    addi  $5, $5, 0x10\n"
    "    bne   $0, $7, 2b\n"
    "    addi  $4, $4, 0x10\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00240198, . - func_00240198\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00240240: handwritten VU0 axis-rotation builder (sibling of func_00240198,
 * different axis). Internal alternate entry func_00240270. Handwritten exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00240240\n"
    "    .type func_00240240, @function\n"
    "    .align 3\n"
    "func_00240240:\n"
    "    mtc1  $0, $f0\n"
    "    c.lt.s $f12, $f0\n"
    "    lui   $1, 0x3FC9\n"
    "    ori   $1, $1, 0x0FDB\n"
    "    mtc1  $1, $f0\n"
    "    bc1f  1f\n"
    "    nop\n"
    "    add.s $f12, $f0, $f12\n"
    "    j     func_00240270\n"
    "    addiu $7, $0, 0x1\n"
    "1:\n"
    "    sub.s $f12, $f0, $f12\n"
    "    daddu $7, $0, $0\n"
    "    .align 3\n"
    "func_00240270:\n"
    "    mfc1  $8, $f12\n"
    "    qmtc2.ni $8, $vf6\n"
    "    daddu $6, $31, $0\n"
    "    jal   func_00240120\n"
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
    "    vmulax.xyzw $ACC, $vf6, $vf4x\n"
    "    vmadday.xyzw $ACC, $vf7, $vf4y\n"
    "    vmaddaz.xyzw $ACC, $vf8, $vf4z\n"
    "    vmaddw.xyzw $vf5, $vf9, $vf4w\n"
    "    sqc2  $vf5, 0x0($4)\n"
    "    addi  $7, $7, -0x1\n"
    "    addi  $5, $5, 0x10\n"
    "    bne   $0, $7, 2b\n"
    "    addi  $4, $4, 0x10\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_00240240, . - func_00240240\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002402E8: handwritten VU0 axis-rotation builder (sibling of func_00240198,
 * different axis). Internal alternate entry func_00240318. Handwritten exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_002402E8\n"
    "    .type func_002402E8, @function\n"
    "    .align 3\n"
    "func_002402E8:\n"
    "    mtc1  $0, $f0\n"
    "    c.lt.s $f12, $f0\n"
    "    lui   $1, 0x3FC9\n"
    "    ori   $1, $1, 0x0FDB\n"
    "    mtc1  $1, $f0\n"
    "    bc1f  1f\n"
    "    nop\n"
    "    add.s $f12, $f0, $f12\n"
    "    j     func_00240318\n"
    "    addiu $7, $0, 0x1\n"
    "1:\n"
    "    sub.s $f12, $f0, $f12\n"
    "    daddu $7, $0, $0\n"
    "    .align 3\n"
    "func_00240318:\n"
    "    mfc1  $8, $f12\n"
    "    qmtc2.ni $8, $vf6\n"
    "    daddu $6, $31, $0\n"
    "    jal   func_00240120\n"
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
    "    vmulax.xyzw $ACC, $vf6, $vf4x\n"
    "    vmadday.xyzw $ACC, $vf7, $vf4y\n"
    "    vmaddaz.xyzw $ACC, $vf8, $vf4z\n"
    "    vmaddw.xyzw $vf5, $vf9, $vf4w\n"
    "    sqc2  $vf5, 0x0($4)\n"
    "    addi  $7, $7, -0x1\n"
    "    addi  $5, $5, 0x10\n"
    "    bne   $0, $7, 2b\n"
    "    addi  $4, $4, 0x10\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_002402E8, . - func_002402E8\n"
    "    .set reorder\n"
    "    .set at\n"
);

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

extern void func_0023FF18(void *a0, void *a1);

void func_00240408(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x50];
    func_002400F8(buf);
    func_0023FE50(buf + 0x40, a3, a2);
    func_0023FE98(buf, buf + 0x40);
    func_0023FE98(buf + 0x20, a2);
    func_0023FE50(buf + 0x10, buf + 0x20, buf);
    func_00240050(buf, buf, a1);
    func_0023FF18(a0, buf);
}

void func_002404B8(void *a0, void *a1, void *a2, void *a3) {
    float buf[4];
    func_00240038(buf, a1, -1.0f);
    func_0023FE98(a0, buf);
    func_00240038(buf, a2, -1.0f);
    func_0023FE98((char *)a0 + 0x10, buf);
    func_00240038(buf, a3, -1.0f);
    func_0023FE98((char *)a0 + 0x20, buf);
    {
        float fzero = 0.0f;
        *(float *)((char *)a0 + 0x38) = fzero;
        *(float *)((char *)a0 + 0x3C) = 1.0f;
        *(float *)((char *)a0 + 0x34) = fzero;
        *(float *)((char *)a0 + 0x30) = fzero;
    }
    func_0023FED0(a0, a0);
}


void func_00240578(void *a0, void *a1, void *a2, void *a3, void *a4) {
    func_00240080(a0, a1);
    func_00240080((char *)a0 + 0x10, a2);
    func_00240080((char *)a0 + 0x20, a3);
    func_00240080((char *)a0 + 0x30, a4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002405E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002406E8);

void func_00240878(void *a0, void *a1, void *a2, int a3, int a4) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x10($5)\n"
        "lqc2 $vf6, 0x20($5)\n"
        "lqc2 $vf7, 0x30($5)\n"
        "1:\n"
        "lqc2 $vf8, 0x0($6)\n"
        "vmulax.xyzw $ACC, $vf4, $vf8x\n"
        "vmadday.xyzw $ACC, $vf5, $vf8y\n"
        "vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
        "vmaddw.xyzw $vf9, $vf7, $vf8w\n"
        "vdiv $Q, $vf0w, $vf9w\n"
        "vwaitq\n"
        "vmulq.xyz $vf9, $vf9, $Q\n"
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

void func_002408D0(void *a0, void *a1, void *a2, int a3) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x10, 5);
    VU0_LSV(lqc2, 6, 0x20, 5);
    VU0_LSV(lqc2, 7, 0x30, 5);
    VU0_LSV(lqc2, 8, 0x0, 6);
    VU0_V3OP_ACC_BC(vmulax.xyzw, 4, 8, x);
    VU0_V3OP_ACC_BC(vmadday.xyzw, 5, 8, y);
    VU0_V3OP_ACC_BC(vmaddaz.xyzw, 6, 8, z);
    VU0_V3OP_BC(vmaddw.xyzw, 9, 7, 8, w);
    VU0_REG("vdiv $Q, $vf0w, $vf9w");
    VU0_WAIT();
    VU0_REG("vmulq.xyz $vf9, $vf9, $Q");
    VU0_REG("vftoi4.xyzw $vf10, $vf9");
    if (a3) {
        VU0_REG("vftoi0.zw $vf10, $vf9");
    }
    VU0_LSV(sqc2, 10, 0x0, 4);
}

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

int func_00240980(void *a0) {
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

int func_002409C8(void *a0, void *a1, void *a2) {
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

/* func_00240A28: handwritten VU0 transform + clip-test loop — matrix-multiply
 * each vertex, perspective-multiply two extents, and read the VU0 clip flags
 * (cfc2 $vi16) to early-out. Handwritten per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00240A28\n"
    "    .type func_00240A28, @function\n"
    "    .align 3\n"
    "func_00240A28:\n"
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
    "    vmulax.xyzw $ACC, $vf4, $vf8x\n"
    "    vmadday.xyzw $ACC, $vf5, $vf8y\n"
    "    vmaddaz.xyzw $ACC, $vf6, $vf8z\n"
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
    "    .size func_00240A28, . - func_00240A28\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_0054A9B0[];

void func_00240AB8(void) {
    typedef unsigned int u128 __attribute__((mode(TI)));
    register int v __asm__("$8");

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
        : "=r"(v) : : "memory"
    );

    {
        volatile u128 *dst = (volatile u128 *)0x10004000;
        u128 *src = (u128 *)D_0054A9B0;
        *dst = src[0];
        *dst = src[1];
    }
}

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

void func_00241640(int *a1, unsigned int a2) {
    int *a0;
    int s0;
    int v0;
    v0 = func_002415E8(a1);
    a0 = (int *)a1[0];
    do { s0 = a2 | 0x10000000; } while (0);
    a1[2] = v0;
    a0[0] = s0;
    a0++;
    a1[3] = 0;
    a1[0] = (int)(a0 + 1);
    a0[0] = 0;
}

void func_00241698(int *a1, unsigned int a2) {
    int *a0;
    int s0;
    int v0;
    v0 = func_002415E8(a1);
    a0 = (int *)a1[0];
    do { s0 = a2 | 0x70000000; } while (0);
    a1[2] = v0;
    a0[0] = s0;
    a0++;
    a1[3] = 0;
    a1[0] = (int)(a0 + 1);
    a0[0] = 0;
}

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

/* func_00241AC8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00241AC8\n"
    ".type func_00241AC8, @function\n"
    "    .align 3\n"
    "func_00241AC8:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd $31, 0x30($29)\n"
    "    sd $18, 0x20($29)\n"
    "    sd $17, 0x10($29)\n"
    "    sd $16, 0x0($29)\n"
    "    mfc0 $17, $12\n"
    "    lui $2, (0x10000 >> 16)\n"
    "    and $17, $17, $2\n"
    "    beqz $17, .L00241B14\n"
    "    lui $18, %hi(D_0054AA94)\n"
    ".L00241AF0:\n"
    "    di\n"
    "    sync.p\n"
    "    mfc0 $2, $12\n"
    "    lui $3, (0x10000 >> 16)\n"
    "    and $2, $2, $3\n"
    "    bnez $2, .L00241AF0\n"
    "    nop\n"
    "    b .L00241B18\n"
    "    lw $2, %lo(D_0054AA94)($18)\n"
    ".L00241B14:\n"
    "    lw $2, %lo(D_0054AA94)($18)\n"
    ".L00241B18:\n"
    "    jal func_00100500\n"
    "    addu $16, $2, $4\n"
    "    sltu $2, $2, $16\n"
    "    beqz $2, .L00241B50\n"
    "    lw $2, %lo(D_0054AA94)($18)\n"
    "    jal func_002603E0\n"
    "    nop\n"
    "    addiu $3, $0, 0xC\n"
    "    beqz $17, .L00241B44\n"
    "    sw $3, 0x0($2)\n"
    "    ei\n"
    ".L00241B44:\n"
    "    lui $2, (0xFFFFFFFF >> 16)\n"
    "    b .L00241B5C\n"
    "    ori $2, $2, (0xFFFFFFFF & 0xFFFF)\n"
    ".L00241B50:\n"
    "    beqz $17, .L00241B5C\n"
    "    sw $16, %lo(D_0054AA94)($18)\n"
    "    ei\n"
    ".L00241B5C:\n"
    "    ld $31, 0x30($29)\n"
    "    ld $18, 0x20($29)\n"
    "    ld $17, 0x10($29)\n"
    "    ld $16, 0x0($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x40\n"
    "    nop\n"
    ".size func_00241AC8, . - func_00241AC8\n"
    "    .set reorder\n"
    "    .set at\n"
);

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

void func_002424F0(int *a0, int *a1) {
    int *ret = (int *)func_002423C8(a1);
    int f14 = a0[5], f1c = a0[7];
    ret[5] = f14;
    ret[7] = f1c;
    ret[8] = 0x8000000C;
    func_00248290(0x80000008, (int)ret, 0x40, a0[8], a0[9], a0[10]);
}

int func_00242550(void *a0, int a1, int a2, int a3, int a4) {
    extern void *func_00242300(void *a0);
    extern int func_00100520(int *a0);
    extern int func_00248250(int a0, int a1, int a2, int a3, int a4, int a5);
    extern int func_00100530(int a0);
    extern void func_00100560(int a0);
    extern int D_0070E240[];
    void *obj;
    int buf[8];

    obj = func_00242300(D_0070E240);
    if (obj == 0) {
        return -1;
    }
    *(void **)((char *)a0 + 0) = obj;
    *(int *)((char *)a0 + 4) = *(int *)((char *)obj + 0x18);
    *(int *)((char *)obj + 0x20) = a1;
    *(int *)((char *)obj + 0x24) = a2;
    *(int *)((char *)obj + 0x28) = a3;
    *(void **)((char *)obj + 0x14) = obj;
    *(void **)((char *)obj + 0x1C) = a0;
    if ((a4 & 1) == 0) {
        int r;
        buf[1] = 1;
        buf[2] = 0;
        r = func_00100520(buf);
        *(int *)((char *)a0 + 8) = r;
        if (r < 0) {
            func_002423A8(obj);
            return -3;
        }
        if (func_00248250(0x8000000C, (int)obj, 0x40, 0, 0, 0) == 0) {
            func_002423A8(obj);
            func_00100530(*(int *)((char *)a0 + 8));
            return -2;
        }
        func_00100560(*(int *)((char *)a0 + 8));
        func_00100530(*(int *)((char *)a0 + 8));
        return 0;
    } else {
        *(int *)((char *)a0 + 8) = -1;
        if (func_00248250(0x8000000C, (int)obj, 0x40, 0, 0, 0) != 0) {
            return 0;
        }
        func_002423A8(obj);
        return -2;
    }
}


void *func_002426A8(int a0, void *a1) {
    void *n5;
    void *n3;
    for (n5 = *(void **)((char *)a1 + 0x28); n5 != 0; n5 = *(void **)((char *)n5 + 0x14)) {
        for (n3 = *(void **)((char *)n5 + 0x8); n3 != 0; n3 = *(void **)((char *)n3 + 0x38)) {
            if (*(int *)n3 == a0) {
                return n3;
            }
        }
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002426F8);

int func_002427A8(void *a0, int a1, int a2) {
    extern void *func_00242300(void *a0);
    extern int func_00100520(int *a0);
    extern int func_00248250(int a0, int a1, int a2, int a3, int a4, int a5);
    extern int func_00100530(int a0);
    extern void func_00100560(int a0);
    extern int D_0070E240[];
    void *obj;
    int buf[8];

    *(int *)((char *)a0 + 0x10) = 0;
    *(int *)((char *)a0 + 0x24) = 0;
    obj = func_00242300(D_0070E240);
    if (obj == 0) {
        return -1;
    }
    *(void **)((char *)a0 + 0) = obj;
    *(int *)((char *)a0 + 4) = *(int *)((char *)obj + 0x18);
    *(int *)((char *)obj + 0x20) = a1;
    *(void **)((char *)obj + 0x14) = obj;
    *(void **)((char *)obj + 0x1C) = a0;
    if ((a2 & 1) == 0) {
        int r;
        buf[1] = 1;
        buf[2] = 0;
        r = func_00100520(buf);
        *(int *)((char *)a0 + 8) = r;
        if (r < 0) {
            func_002423A8(obj);
            return -3;
        }
        if (func_00248250(0x80000009, (int)obj, 0x40, 0, 0, 0) == 0) {
            func_002423A8(obj);
            func_00100530(*(int *)((char *)a0 + 8));
            return -2;
        }
        func_00100560(*(int *)((char *)a0 + 8));
        func_00100530(*(int *)((char *)a0 + 8));
        return 0;
    } else {
        *(int *)((char *)a0 + 8) = -1;
        if (func_00248250(0x80000009, (int)obj, 0x40, 0, 0, 0) != 0) {
            return 0;
        }
        func_002423A8(obj);
        return -2;
    }
}


void func_002428E8(int *a0) {
    int *a5 = (int *)a0[13];
    int *a6 = (int *)a5[16];
    int *a2 = (int *)a6[3];
    if (a2 == 0) {
        a6[3] = (int)a5;
    } else {
        ((int *)a6[4])[15] = (int)a5;
    }
    a6[4] = (int)a5;
    {
        int t5 = a0[5], t7 = a0[7];
        a5[8] = t5;
        a5[7] = t7;
    }
    a5[9] = a0[8];
    a5[3] = a0[9];
    a5[10] = a0[10];
    a5[11] = a0[11];
    a5[12] = a0[12];
    a5[13] = a0[4];
    if ((int)a6[0] < 0) {
        return;
    }
    if (a6[1] != 0) {
        return;
    }
    func_00100F18(a6[0]);
}

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

extern int D_0070E240[];

int func_00242DA8(int *a0) {
    int *node;
    func_00101A40(a0);
    node = (int *)D_0070E240[0x28 / 4];
    if (node == a0) {
        D_0070E240[0x28 / 4] = a0[0x14 / 4];
    } else if (node != 0) {
        if (node[0x14 / 4] == (int)a0) {
            node[0x14 / 4] = a0[0x14 / 4];
        } else {
            do {
                node = (int *)node[0x14 / 4];
                if (node == 0) {
                    goto done;
                }
            } while (node[0x14 / 4] != (int)a0);
            node[0x14 / 4] = a0[0x14 / 4];
        }
    }
done:
    func_00101A88();
    return (int)node;
}

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

extern int func_00100520(int *self);
extern int D_0054AB28[];
extern int D_0054AB2C[];

void func_00243098(void) {
    int self[8];
    if (D_0054AB28[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_0054AB28[0] = func_00100520(self);
        D_0054AB2C[0] = func_00100520(self);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002430F8);

extern char D_0070F380[];

void *func_00243180(unsigned int a0) {
    void *result;
    func_00243098();
    func_00100560(D_0054AB28[0]);
    if (a0 >= 0x20) {
        func_00100540(D_0054AB28[0]);
        return 0;
    }
    result = &D_0070F380[a0 * 16];
    func_00100540(D_0054AB28[0]);
    return result;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002431F0);

extern int D_0054AB24[];
extern int func_00100520(int *self);

void func_002435A8(void) {
    int self[8];
    if (D_0054AB24[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_0054AB24[0] = func_00100520(self);
    }
}

extern void func_002435A8(void);
extern void func_00100560(int a0);
extern int D_0054AB24[];

int func_002435F8(int arg) {
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

extern char D_00270A8C[];
extern char D_0070F5A8[];
extern int D_0054AB30[];

int func_002437D8(void) {
    char *s3 = D_00270A8C;
    char *s1 = D_0070F5A8;
    int s2 = 0;
    int v0;
    v0 = func_00260424(s1, s3, 4);
    if (v0 == 0) goto done;
    v0 = func_00260424(s1, (char *)D_0054AB30[0], 4);
    if (v0 == 0) goto done;
    v0 = func_00260424(s3, (char *)D_0054AB30[0], 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}

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

/* m2c scaffold from asm/aug6/nonmatchings/common/src/PObj/func_00244F40.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern int func_00100530(int a0);
extern int func_00242978();
extern void func_00243638(void);
extern int D_0070E2C0[];
extern int D_0070EF00[];
extern int D_0070F580[];

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244F40);


int func_00245060(void *a0) {
    return func_00244938(a0, 0x10);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245080);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245120);

int func_00245288(unsigned int a0, int a1) {
    extern int func_00100520(int *a0);
    extern void func_00100560(int a0);
    int *g = D_0070E2C0;
    void *obj;
    int f0;
    int uv;
    int rc;
    int result;
    int buf[8];

    obj = func_00243180(a0);
    func_002435F8(0xB);
    if (D_0054AB20[0] == 0) {
        func_00243628();
        return -1;
    }
    if (obj == 0 || ((int *)obj)[1] == 0) {
        func_00243628();
        return -9;
    }
    f0 = ((int *)obj)[0];
    g[4] = a1;
    g[3] = f0;
    buf[1] = 1;
    buf[2] = 0;
    buf[5] = 0;
    D_0070E2C0[0] = a1 = func_00100520(buf);
    *(void **)(g + 1) = &result;
    g[2] = 4;
    rc = func_00242978(D_0070F580, 0xB, 0, g, 0x20, D_0070EF00, 4, 0, 0);
    if (rc < 0) {
        func_00100560(a1);
        func_00243628();
        return -0xB;
    }
    uv = *(int *)((int)D_0070EF00 | 0x20000000);
    func_00243628();
    if (uv == 0) {
        func_00100530(a1);
        return -0xB;
    }
    func_00100560(a1);
    func_00100530(a1);
    return result;
}


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

extern char D_FFFFF[];
extern int D_0070F600[];
extern int D_0054AB34[];

int func_00246608(void)
{
    int i;
    int ret;
    int val;
    goto no_delay;
again:
    __asm__ volatile ("lui %0,%%hi(D_FFFFF)" : "=r"(i));
    do {
        __asm__ volatile ("addiu %0,%0,%%lo(D_FFFFF)" : "+r"(i));
    } while (i != -1);
no_delay:
    ret = func_002427A8(D_0070F600, 0x80000003, 0);
    if (ret < 0) return -1;
    val = D_0070F600[0x24 / 4];
    if (val == 0) goto again;
    D_0054AB34[0] = 0;
    __asm__ volatile ("");
    return 0;
}

extern int D_0054AB34[];
extern int D_0070F600[];
extern int D_0070F640[];
extern int D_0070F680[];

int func_00246690(int a0) {
    int ret = D_0054AB34[0];
    if (ret < 0) return 0;
    D_0070F680[0] = a0;
    ret = func_00242978(D_0070F600, 1, 0, D_0070F680, 4, D_0070F640, 4, 0, 0);
    if (ret >= 0) return D_0070F640[0];
    return 0;
}

extern int D_0070F6C0[];

int func_00246700(int a0) {
    int v2 = D_0054AB34[0];
    if (v2 < 0) return 0;
    D_0070F6C0[0] = a0;
    v2 = func_00242978(D_0070F600, 2, 0, D_0070F6C0, 4, D_0070F640, 4, 0, 0);
    if (v2 < 0) return -1;
    return D_0070F640[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246778);

extern int D_0054AB38[];
extern char D_0070FA00[];
extern char D_0070F800[];
extern char D_0070FA28[];

int func_00246868(void) {
    int i;
    int r;
    int val;
    if (D_0054AB38[0] >= 0) goto ret0;
loop:
    r = func_002427A8(D_0070FA00, 0x80000006, 0);
    if (r < 0) return -1;
    val = *(int *)(D_0070FA00 + 0x24);
    if (val == 0) goto delay;
    D_0054AB38[0] = 0;
    r = func_00242978(D_0070FA00, 0xFF, 0, 0, 0, D_0070F800, 4, 0, 0);
    if (r < 0) return 0xFFFEFFFF;
    __builtin_memcpy(D_0070FA28, D_0070F800, 4);
    return 0;
delay:
    __asm__ volatile ("lui %0,%%hi(D_FFFFF)" : "=r"(i));
    do {
        __asm__ volatile ("addiu %0,%0,%%lo(D_FFFFF)" : "+r"(i));
    } while (i != -1);
    goto loop;
ret0:
    return 0;
}


extern int D_0054AB3C[];
extern char D_0070FA28[];

int func_00246968(void) {
    void *s3 = D_00270A8C;
    void *s1 = D_0070FA28;
    int s2 = 0;
    int v;
    if (func_00260424(s1, (int)s3, 4) == 0) goto done;
    v = D_0054AB3C[0];
    if (func_00260424(s1, v, 4) == 0) goto done;
    v = D_0054AB3C[0];
    s2 = (0 < (unsigned int)func_00260424(s3, v, 4));
done:
    return s2;
}

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

extern int func_00246868(void);
extern int func_00246968(void);
extern int func_00242978();
extern void func_00261900(char *a0, char *a1, int a2);
extern char D_0070F808[];
extern char D_0070FA00[];

int func_00246EE0(void *a0, int a1, int a2, int a3) {
    char *buf;
    int r;

    if (func_00246868() < 0) {
        return 0xFFFF0000;
    }
    if (func_00246968() != 0) {
        return 0xFFFEFFFC;
    }
    func_00261900(D_0070F808, a0, 0xFC);
    buf = D_0070F808 - 8;
    buf[0x103] = 0;
    func_00261900(D_0070F808 + 0xFC, (char *)a1, 0xFC);
    buf[0x1FF] = 0;
    r = func_00242978(D_0070FA00, a3, 0, buf, 0x200, buf, 0x10, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (*(int *)buf == 0) {
        return 0xFFFEFFFD;
    }
    *(int *)a2 = *(int *)buf;
    *(int *)(a2 + 4) = *(int *)(buf + 4);
    return 0;
}

extern int func_00246EE0(void *a0, int a1, int a2, int a3);

int func_00246FE8(void *a0, int a1, int a2) {
    return func_00246EE0(a0, a1, a2, 1);
}

extern char D_00628838[];

int func_00247008(void *a0, int a1) {
    return func_00246EE0(a0, (int)D_00628838, a1, 1);
}

extern int func_00246868(void);
extern int func_00242978();
extern char D_0070F800[];
extern char D_0070FA00[];

int func_00247030(int a0, void *a1, int a2) {
    int r;
    if (func_00246868() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_0070F800 + 0) = a0;
    *(int *)(D_0070F800 + 4) = a2;
    r = func_00242978(D_0070FA00, 3, 0, D_0070F800, 0x20, D_0070F800, 0x20, 0, 0);
    if (r < 0) {
        return 0xFFFEFFFF;
    }
    if (a2 == 0) {
        *(unsigned char *)a1 = *(unsigned char *)D_0070F800;
    } else if (a2 == 1) {
        *(unsigned short *)a1 = *(unsigned short *)D_0070F800;
    } else if (a2 == 2) {
        *(int *)a1 = *(int *)D_0070F800;
    } else {
        return 0xFFFEFFFE;
    }
    return 0;
}

extern int func_00246868(void);
extern int func_00242978();
extern char D_0070F800[];
extern char D_0070FA00[];

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247120);


extern void func_001007F0(void);
extern int func_00100930(int a0);
extern void func_002483F8(void *a0, int a1);
extern int func_001008E0(void *a0, int a1);
extern void func_00100920(int a0, int a1);
typedef struct { union { long long q; struct { int lo; int hi; } w; } tag; int f8; int fc; int f10; int f14; unsigned char name[0x50]; } PObjPkt;
extern PObjPkt D_0070FA40;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247200);



extern int func_00100930(int a0);

int func_00247330(void) {
    int t = func_00100930(4) & 0x10000;
    return t != 0;
}

extern void func_00100920(int a0, int a1);

int func_00247358(void) {
    if (func_00100930(4) & 0x40000) {
        func_00100920(4, 0x40000);
        ((void (*)(void))func_002418E0)();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002473A0);

/* func_002474B0: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002474B0\n"
    ".type func_002474B0, @function\n"
    "    .align 3\n"
    "func_002474B0:\n"
    "    addiu $29, $29, -0x50\n"
    "    sd $31, 0x40($29)\n"
    "    sd $19, 0x30($29)\n"
    "    sd $18, 0x20($29)\n"
    "    sd $17, 0x10($29)\n"
    "    sd $16, 0x0($29)\n"
    "    mfc0 $17, $6\n"
    "    lui $19, %hi(D_00628870)\n"
    "    lui $18, %hi(D_006288B0)\n"
    "    daddu $16, $0, $0\n"
    "    addiu $4, $19, %lo(D_00628870)\n"
    "    nop\n"
    ".L002474E0:\n"
    "    bne $16, $17, .L002474F0\n"
    "    daddu $5, $16, $0\n"
    "    jal func_001019E0\n"
    "    nop\n"
    ".L002474F0:\n"
    "    mtc0 $16, $0\n"
    "    sync.p\n"
    "    tlbr\n"
    "    sync.p\n"
    "    mfc0 $8, $2\n"
    "    mfc0 $9, $3\n"
    "    mfc0 $6, $5\n"
    "    mfc0 $7, $10\n"
    "    daddu $5, $16, $0\n"
    "    jal func_001019E0\n"
    "    addiu $4, $18, %lo(D_006288B0)\n"
    "    addiu $16, $16, 0x1\n"
    "    slti $2, $16, 0x30\n"
    "    bnel $2, $0, .L002474E0\n"
    "    addiu $4, $19, %lo(D_00628870)\n"
    "    ld $31, 0x40($29)\n"
    "    ld $19, 0x30($29)\n"
    "    ld $18, 0x20($29)\n"
    "    ld $17, 0x10($29)\n"
    "    ld $16, 0x0($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x50\n"
    ".size func_002474B0, . - func_002474B0\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247548: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00247548\n"
    ".type func_00247548, @function\n"
    "    .align 3\n"
    "func_00247548:\n"
    "    srl $3, $5, 24\n"
    "    addiu $2, $0, 0x30\n"
    "    beq $3, $2, .L002475BC\n"
    "    sltiu $2, $3, 0x31\n"
    "    beqz $2, .L00247590\n"
    "    addiu $2, $0, 0x10\n"
    "    beq $3, $2, .L002475CC\n"
    "    sltiu $2, $3, 0x11\n"
    "    beqz $2, .L00247580\n"
    "    addiu $2, $0, 0x20\n"
    "    beqz $3, .L002475C0\n"
    "    andi $2, $3, 0xF\n"
    "    b .L002475D4\n"
    "    nop\n"
    ".L00247580:\n"
    "    beq $3, $2, .L002475C0\n"
    "    andi $2, $3, 0xF\n"
    "    b .L002475D4\n"
    "    nop\n"
    ".L00247590:\n"
    "    addiu $2, $0, 0x50\n"
    "    beq $3, $2, .L002475CC\n"
    "    sltiu $2, $3, 0x51\n"
    "    bnez $2, .L002475D4\n"
    "    addiu $2, $0, 0x60\n"
    "    beq $3, $2, .L002475CC\n"
    "    addiu $2, $0, 0x70\n"
    "    beq $3, $2, .L002475CC\n"
    "    nop\n"
    "    b .L002475D4\n"
    "    nop\n"
    ".L002475BC:\n"
    "    andi $2, $3, 0xF\n"
    ".L002475C0:\n"
    "    sltiu $2, $2, 0x8\n"
    "    beqz $2, .L002475D4\n"
    "    nop\n"
    ".L002475CC:\n"
    "    jr $31\n"
    "    addiu $2, $0, -0x1\n"
    ".L002475D4:\n"
    "    mtc0 $4, $5\n"
    "    mtc0 $5, $10\n"
    "    mtc0 $6, $2\n"
    "    mtc0 $7, $3\n"
    "    sync.p\n"
    "    tlbwr\n"
    "    sync.p\n"
    "    tlbp\n"
    "    sync.p\n"
    "    mfc0 $2, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00247548, . - func_00247548\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00247608: handwritten TLB-write routine (mfc0/mtc0/tlbwi/sync.p).
 * C-inexpressible: privileged COP0 TLB ops have no ee-gcc 2.9 / r5900.h
 * intrinsic, and the mtc0 sources must stay in the arg regs $4-$8. Written
 * as in-file handwritten asm per maintainer exception (cf. func_002484AC). */
__asm__(
    ".section .text
"
    "    .set noat
"
    "    .set noreorder
"
    "    .global func_00247608
"
    "    .type func_00247608, @function
"
    "    .align 3\n"
    "func_00247608:
"
    "    mfc0  $2, $6
"
    "    slt   $2, $4, $2
"
    "    bnez  $2, 1f
"
    "    slti  $2, $4, 0x30
"
    "    bnez  $2, 2f
"
    "    nop
"
    "1:
"
    "    jr    $31
"
    "    addiu $2, $0, -0x1
"
    "2:
"
    "    mtc0  $4, $0
"
    "    mtc0  $5, $5
"
    "    mtc0  $6, $10
"
    "    mtc0  $7, $2
"
    "    mtc0  $8, $3
"
    "    sync.p
"
    "    tlbwi
"
    "    sync.p
"
    "    jr    $31
"
    "    daddu $2, $4, $0
"
    "    .size func_00247608, . - func_00247608
"
    "    .set reorder
"
    "    .set at
"
);

/* func_00247650: handwritten TLB-read routine (mtc0/tlbr/mfc0/sync.p).
 * C-inexpressible privileged COP0 ops; in-file handwritten asm per maintainer
 * exception (cf. func_00247608, func_002484AC). */
__asm__(
    ".section .text
"
    "    .set noat
"
    "    .set noreorder
"
    "    .global func_00247650
"
    "    .type func_00247650, @function
"
    "    .align 3\n"
    "func_00247650:
"
    "    sltiu $2, $4, 0x30
"
    "    bnez  $2, 1f
"
    "    nop
"
    "    jr    $31
"
    "    addiu $2, $0, -0x1
"
    "1:
"
    "    mtc0  $4, $0
"
    "    sync.p
"
    "    tlbr
"
    "    sync.p
"
    "    mfc0  $2, $5
"
    "    sw    $2, 0x0($5)
"
    "    mfc0  $3, $10
"
    "    sw    $3, 0x0($6)
"
    "    mfc0  $2, $2
"
    "    sw    $2, 0x0($7)
"
    "    mfc0  $3, $3
"
    "    sw    $3, 0x0($8)
"
    "    jr    $31
"
    "    daddu $2, $4, $0
"
    "    .size func_00247650, . - func_00247650
"
    "    .set reorder
"
    "    .set at
"
);

/* func_002476A0: handwritten TLB-probe routine (mtc0/tlbp/tlbr/mfc0/sync.p).
 * C-inexpressible privileged COP0 ops; in-file handwritten asm per maintainer
 * exception (cf. func_00247608, func_00247650). */
__asm__(
    ".section .text
"
    "    .set noat
"
    "    .set noreorder
"
    "    .global func_002476A0
"
    "    .type func_002476A0, @function
"
    "    .align 3\n"
    "func_002476A0:
"
    "    mtc0  $4, $10
"
    "    sync.p
"
    "    tlbp
"
    "    sync.p
"
    "    mfc0  $4, $0
"
    "    bgez  $4, 1f
"
    "    nop
"
    "    b     2f
"
    "    addiu $4, $0, -0x1
"
    "1:
"
    "    tlbr
"
    "    sync.p
"
    "    mfc0  $2, $5
"
    "    sw    $2, 0x0($5)
"
    "    mfc0  $3, $2
"
    "    sw    $3, 0x0($6)
"
    "    mfc0  $2, $3
"
    "    sw    $2, 0x0($7)
"
    "2:
"
    "    jr    $31
"
    "    daddu $2, $4, $0
"
    "    .size func_002476A0, . - func_002476A0
"
    "    .set reorder
"
    "    .set at
"
);

/* func_002476F0: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002476F0\n"
    ".type func_002476F0, @function\n"
    "    .align 3\n"
    "func_002476F0:\n"
    "    addiu $29, $29, -0x30\n"
    "    sd $16, 0x10($29)\n"
    "    daddu $16, $4, $0\n"
    "    andi $2, $16, 0xFFF\n"
    "    bnez $2, .L00247720\n"
    "    sd $31, 0x20($29)\n"
    "    lui $2, (0xFFFFE >> 16)\n"
    "    addiu $3, $16, -0x1\n"
    "    ori $2, $2, (0xFFFFE & 0xFFFF)\n"
    "    sltu $2, $2, $3\n"
    "    bnez $2, .L00247728\n"
    "    lui $4, (0x70004000 >> 16)\n"
    ".L00247720:\n"
    "    b .L00247810\n"
    "    addiu $2, $0, -0x1\n"
    ".L00247728:\n"
    "    daddu $5, $29, $0\n"
    "    ori $4, $4, (0x70004000 & 0xFFFF)\n"
    "    ori $6, $29, 0x4\n"
    "    jal func_002476A0\n"
    "    ori $7, $29, 0x8\n"
    "    daddu $5, $2, $0\n"
    "    bgez $5, .L00247768\n"
    "    nop\n"
    "    beqz $16, .L00247810\n"
    "    daddu $2, $0, $0\n"
    "    mfc0 $5, $6\n"
    "    addiu $2, $5, 0x1\n"
    "    mtc0 $2, $6\n"
    "    sync.p\n"
    "    b .L002477B0\n"
    "    nop\n"
    ".L00247768:\n"
    "    bnez $16, .L002477B0\n"
    "    addiu $2, $5, -0x1\n"
    "    lui $3, (0xE0010000 >> 16)\n"
    "    sll $2, $2, 13\n"
    "    addu $6, $2, $3\n"
    "    mfc0 $2, $6\n"
    "    addiu $2, $2, -0x1\n"
    "    mtc0 $2, $6\n"
    "    mtc0 $5, $0\n"
    "    mtc0 $0, $5\n"
    "    mtc0 $6, $10\n"
    "    mtc0 $0, $2\n"
    "    mtc0 $0, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    b .L00247810\n"
    "    daddu $2, $0, $0\n"
    ".L002477B0:\n"
    "    lui $2, (0xFFFFF000 >> 16)\n"
    "    addiu $4, $16, 0x1000\n"
    "    ori $2, $2, (0xFFFFF000 & 0xFFFF)\n"
    "    lui $6, (0x70004000 >> 16)\n"
    "    and $4, $4, $2\n"
    "    sw $0, 0x0($29)\n"
    "    and $2, $16, $2\n"
    "    srl $4, $4, 6\n"
    "    srl $2, $2, 6\n"
    "    ori $4, $4, 0x1F\n"
    "    ori $2, $2, 0x1F\n"
    "    ori $6, $6, (0x70004000 & 0xFFFF)\n"
    "    sw $2, 0x4($29)\n"
    "    sw $4, 0x8($29)\n"
    "    mtc0 $5, $0\n"
    "    daddu $3, $0, $0\n"
    "    mtc0 $3, $5\n"
    "    mtc0 $6, $10\n"
    "    mtc0 $2, $2\n"
    "    mtc0 $4, $3\n"
    "    sync.p\n"
    "    tlbwi\n"
    "    sync.p\n"
    "    daddu $2, $5, $0\n"
    ".L00247810:\n"
    "    ld $31, 0x20($29)\n"
    "    ld $16, 0x10($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x30\n"
    ".size func_002476F0, . - func_002476F0\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_0054AB40[];
extern void func_00247A00(void);

void *func_00247820(void *a0) {
    D_0054AB40[0] = (int)a0;
    func_001001D0(1, func_00247A00);
    func_001001D0(2, func_00247A00);
    func_001001D0(3, func_00247A00);
    return a0;
}

extern int D_0054AB48[];
extern char D_00247C40[];

int func_00247880(int a0, int a1) {
    int old;
    int orig = a0;
    unsigned int err = 0xFFFFFFFF;
    if ((unsigned)(a0 - 1) >= 13) {
        return (int)err;
    }
    old = D_0054AB48[orig];
    D_0054AB48[orig] = a1;
    if ((unsigned)(a0 - 1) < 3) {
        func_001001D0(orig, (void *)D_00247C40);
    } else {
        func_001001E0(orig, (void *)D_00247C40);
    }
    return old;
}

/* func_00247908 — hand-written PS2 EE syscall stub: syscall number in $v1,
 * then `syscall 0`. .set noreorder keeps the bare nop in the jr delay slot.
 * The leading nop is func_00247880's trailing 16-align padding (dropped by gcc
 * when that function is C). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "    nop\n"
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

extern void func_002483F8(void *a0, int a1);
extern int func_001008E0(void *a0, int a1);
extern int func_001008F0(void *a0, int a1);
extern int D_00710DE0[];

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

/* func_002482D0: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002482D0\n"
    ".type func_002482D0, @function\n"
    "    .align 3\n"
    "func_002482D0:\n"
    "    addiu $29, $29, -0x90\n"
    "    sd $16, 0x70($29)\n"
    "    sd $31, 0x80($29)\n"
    "    jal func_00101A88\n"
    "    nop\n"
    "    lui $3, %hi(D_00710DD8)\n"
    "    lw $7, %lo(D_00710DD8)($3)\n"
    "    addiu $16, $3, %lo(D_00710DD8)\n"
    "    lbu $2, 0x0($7)\n"
    "    andi $5, $2, 0xFF\n"
    "    beqz $5, .L002483E8\n"
    "    daddu $2, $0, $0\n"
    "    addiu $2, $5, 0xF\n"
    "    addiu $3, $0, -0x1\n"
    "    addiu $4, $5, 0x1E\n"
    "    slt $3, $3, $2\n"
    "    movn $4, $2, $3\n"
    "    daddu $6, $7, $0\n"
    "    sra $5, $4, 4\n"
    "    sb $0, 0x0($7)\n"
    "    blez $5, .L0024834C\n"
    "    daddu $4, $5, $0\n"
    "    daddu $3, $29, $0\n"
    "    nop\n"
    ".L00248330:\n"
    "    lq $2, 0x0($6)\n"
    "    addiu $4, $4, -0x1\n"
    "    addiu $6, $6, 0x10\n"
    "    sq $2, 0x0($3)\n"
    "    addiu $3, $3, 0x10\n"
    "    bnez $4, .L00248330\n"
    "    nop\n"
    ".L0024834C:\n"
    "    jal func_00100910\n"
    "    nop\n"
    "    lw $3, 0x8($29)\n"
    "    bgez $3, .L002483A8\n"
    "    nop\n"
    "    lw $2, 0x8($29)\n"
    "    lui $3, (0x7FFFFFFF >> 16)\n"
    "    ori $3, $3, (0x7FFFFFFF & 0xFFFF)\n"
    "    lw $4, 0x10($16)\n"
    "    and $5, $2, $3\n"
    "    slt $4, $5, $4\n"
    "    beqz $4, .L002483DC\n"
    "    sll $2, $5, 3\n"
    "    lw $3, 0xC($16)\n"
    "    addu $2, $2, $3\n"
    "    lw $6, 0x0($2)\n"
    "    beqz $6, .L002483DC\n"
    "    nop\n"
    "    lw $5, 0x4($2)\n"
    "    jalr $6\n"
    "    daddu $4, $29, $0\n"
    "    b .L002483DC\n"
    "    nop\n"
    ".L002483A8:\n"
    "    lw $5, 0x8($29)\n"
    "    lw $2, 0x18($16)\n"
    "    slt $2, $5, $2\n"
    "    beqz $2, .L002483DC\n"
    "    sll $2, $5, 3\n"
    "    lw $3, 0x14($16)\n"
    "    addu $2, $2, $3\n"
    "    lw $6, 0x0($2)\n"
    "    beqz $6, .L002483DC\n"
    "    nop\n"
    "    lw $5, 0x4($2)\n"
    "    jalr $6\n"
    "    daddu $4, $29, $0\n"
    ".L002483DC:\n"
    "    sync\n"
    "    ei\n"
    "    daddu $2, $0, $0\n"
    ".L002483E8:\n"
    "    ld $31, 0x80($29)\n"
    "    ld $16, 0x70($29)\n"
    "    jr $31\n"
    "    addiu $29, $29, 0x90\n"
    ".size func_002482D0, . - func_002482D0\n"
    "    .set reorder\n"
    "    .set at\n"
);

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
/* func_002483F8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002483F8\n"
    ".type func_002483F8, @function\n"
    "    .align 3\n"
    "func_002483F8:\n"
    "    lui $25, (0xFFFFFFC0 >> 16)\n"
    "    ori $25, $25, (0xFFFFFFC0 & 0xFFFF)\n"
    "    blez $5, .L0024849C\n"
    "    addu $10, $4, $5\n"
    "    and $8, $4, $25\n"
    "    addiu $10, $10, -0x1\n"
    "    and $9, $10, $25\n"
    "    subu $10, $9, $8\n"
    "    srl $11, $10, 6\n"
    "    addiu $11, $11, 0x1\n"
    "    andi $9, $11, 0x7\n"
    "    beqz $9, .L00248448\n"
    "    srl $10, $11, 3\n"
    ".L0024842C:\n"
    "    sync\n"
    "    cache 0x18, 0x0($8)\n"
    "    sync\n"
    "    addiu $9, $9, -0x1\n"
    "    nop\n"
    "    bgtz $9, .L0024842C\n"
    "    addiu $8, $8, 0x40\n"
    ".L00248448:\n"
    "    beqz $10, .L0024849C\n"
    ".L0024844C:\n"
    "    addiu $10, $10, -0x1\n"
    "    sync\n"
    "    cache 0x18, 0x0($8)\n"
    "    sync\n"
    "    cache 0x18, 0x40($8)\n"
    "    sync\n"
    "    cache 0x18, 0x80($8)\n"
    "    sync\n"
    "    cache 0x18, 0xC0($8)\n"
    "    sync\n"
    "    cache 0x18, 0x100($8)\n"
    "    sync\n"
    "    cache 0x18, 0x140($8)\n"
    "    sync\n"
    "    cache 0x18, 0x180($8)\n"
    "    sync\n"
    "    cache 0x18, 0x1C0($8)\n"
    "    sync\n"
    "    bgtz $10, .L0024844C\n"
    "    addiu $8, $8, 0x200\n"
    ".L0024849C:\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_002483F8, . - func_002483F8\n"
    "    .set reorder\n"
    "    .set at\n"
);

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

extern int D_0054AC40[];
extern int D_0054BD90[];
extern int D_0054ABE8[];

int func_00249028(void) {
    if (func_00248EB8(2) == 0) {
        return 0;
    }
    {
        int *base = D_0054AC40;
        int r = func_00242978(D_0054BD90, 0xE, 0, 0, 0, base, 4, 0, 0);
        if (r < 0) {
            func_00100540(D_0054ABE8[0]);
            return 0;
        }
        {
            int val = *(int *)((int)base | 0x20000000);
            func_00100540(D_0054ABE8[0]);
            return val;
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002490C0);

extern int D_0054ABD0[];
extern char D_006289E8[];
extern char D_0054C608[];

int func_00249160(int a0) {
    if (!a0) {
        if (D_0054ABD0[0] > 0) func_001019E0(D_006289E8);
        while (func_00242B68(D_0054C608)) {
            func_002484D0(0x3C);
        }
        return 0;
    }
    return func_00242B68(D_0054C608);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002491D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249340);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249620);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249818);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002498E0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00249AC0);

extern int D_0054BDC0[];
extern char D_0054C608[];
extern int D_0054ABEC[];

int func_00249C18(void) {
    if (func_002491D0(1) == 0) {
        return 0;
    }
    {
        int *base = D_0054BDC0;
        int r = func_00242978(D_0054C608, 3, 0, 0, 0, base, 4, 0, 0);
        if (r < 0) {
            func_00100540(D_0054ABEC[0]);
            return 0;
        }
        {
            int val = *(int *)((int)base | 0x20000000);
            func_00100540(D_0054ABEC[0]);
            return val;
        }
    }
}

extern int D_0054BDC0[];
extern char D_0054C608[];
extern int D_0054ABEC[];

int func_00249CB0(void) {
    if (func_002491D0(3) == 0) {
        return 0xFFFFFFFF;
    }
    {
        int *base = D_0054BDC0;
        int r = func_00242978(D_0054C608, 4, 0, 0, 0, base, 4, 0, 0);
        if (r < 0) {
            func_00100540(D_0054ABEC[0]);
            return 0xFFFFFFFF;
        }
        {
            int val = *(int *)((int)base | 0x20000000);
            func_00100540(D_0054ABEC[0]);
            return val;
        }
    }
}

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

extern int D_0054ABD0[];
extern char D_00628B80[];

int func_00249FD0(void) {
    D_0054C630[0] = 0;
    if (D_0054ABD0[0] > 0) {
        func_001019E0(D_00628B80);
    }
    return func_0024A0C0(0, 0, 0, 7, D_00711258);
}

extern char D_00628B98[];

int func_0024A020(void) {
    D_0054C630[0] = 1;
    if (D_0054ABD0[0] > 0) {
        func_001019E0(D_00628B98);
    }
    return func_0024A0C0(0, 0, 0, 8, D_00711258);
}

extern int D_00628BB0[];

int func_0024A078(void) {
    if (D_0054ABD0[0] > 0) {
        func_001019E0(D_00628BB0);
    }
    return func_0024A0C0(0, 0, 0, 6, D_00711258);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A0C0);

typedef struct { int f0; int *f4; int f8; int fC; int f10; char pad14[0x8]; } PObjA8B8Ent; /* 0x1C */
extern PObjA8B8Ent D_007112D0[][4];
extern int func_001008C0(int a0);
extern void func_0026B730(void *a0, void *a1);
extern void func_00260668(void *a0, ...);
extern char D_00628C08[];
extern int D_0054C64C[];

void func_0024A228(int a0, int a1) {
    struct { int *f0; int f4; int f8; int fC; char rest[0xF0]; } buf;
    int *p17 = D_007112D0[a0][a1].f4;
    int ret = func_001008C0(D_007112D0[a0][a1].fC);

    if (ret >= 0) {
        if (D_0054C64C[0] != 0) {
            func_00260668(D_00628C08);
        }
    } else {
        int n = *p17 + 1;
        int v = D_007112D0[a0][a1].f8 + ((n & 1) << 5);
        int r;
        *p17 = n;
        func_0026B730(p17, (char *) p17 + 0x20);
        buf.f0 = p17;
        buf.f4 = v;
        buf.f8 = 0x20;
        buf.fC = 0;
        r = func_001008E0(&buf, 1);
        if (r == 0) {
            if (D_0054C64C[0] != 0) {
                func_00260668(D_00628C08);
            }
        }
        D_007112D0[a0][a1].fC = r;
    }
}


extern char D_FFFF[];
extern int D_00711280[];
extern int D_0054C648[];
extern int D_0054C64C[];
extern char D_00628C50[];
extern char D_00628C78[];
extern int func_002427A8();
extern int func_0024B500(void);
extern int func_0024A498(int a0);

typedef struct GEnt { char pad0[0x24]; int f24; } GEnt;
extern GEnt D_00711280g[] __asm__("D_00711280");

int func_0024A358(int a0) {
    char *p;
    char *q;
    int i;
    int v;
    int hi;

    *(volatile int *)D_0054C648 = 1;
    for (;;) {
        p = (char *)D_00711280;
        func_002427A8(p, 0x80000100, 0);
        if (*(int *)(p + 0x24) != 0) {
            break;
        }
        i = 0x10000;
        do {
            __asm__ volatile ("addiu %0,%0,%%lo(D_FFFF)" : "+r"(i));
        } while (i != -1);
    }
    {
        char *t = p + 0x28;
        q = p;
        p = t;
    }
    for (;;) {
        func_002427A8(p, 0x80000101, 0);
        if (*(int *)(q + 0x4C) != 0) {
            break;
        }
        i = 0x10000;
        do {
            __asm__ volatile ("addiu %0,%0,%%lo(D_FFFF)" : "+r"(i));
        } while (i != -1);
    }
    v = func_0024B500();
    hi = v >> 8;
    if (hi != 4) {
        if (D_0054C64C[0] != 0) {
            func_00260668(D_00628C50);
            func_00260668(D_00628C78, 4, 0, hi, v & 0xFF);
        }
        return 0;
    }
    return func_0024A498(a0);
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A498);

extern int D_007115C0[];
extern int D_00711280[];
extern int D_0054C648[];

int func_0024A538(void) {
    int ret;
    int val;
    D_007115C0[0] = 0xF;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_007115C0[3];
    if (val == 1) {
        D_0054C648[0] = 0;
    }
    return val;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A5B8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024A7A0);


int func_0024A858(int a0, int a1) {
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_007112D0 + a1 * 0x1C + a0 * 0x70);
    func_0026B730((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}

int func_0024A8B8(int a0, int a1) {
    int ret = 0;
    if (D_007112D0[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(func_0024A858(a0, a1) + 0x58);
}

int func_0024A908(int a0, int a1, int a2) {
    int s0;
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    s0 = func_0024A858(a0, a1);
    func_002604B8(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}

int func_0024A988(int a0, int a1) {
    unsigned char *p;
    if (D_007112D0[a0][a1].f10 == 0) return 0x63;
    p = (unsigned char *)func_0024A858(a0, a1);
    if (p[0x70] != 6) return p[0x70];
    if (p[0x71] == 2) return 5;
    return p[0x70];
}

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

int func_0024AAA0(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return ((unsigned char *)func_0024A858(a0, a1))[0x71];
}

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


int func_0024AD68(int a0, int a1, int a2, int a3) {
    int q;
    int t72;
    int v;

    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    q = func_0024A858(a0, a1);
    t72 = *(unsigned char *)(q + 0x72);
    if (t72 == 1 && *(unsigned char *)(q + 0x71) != 2) {
    if (a2 == 2) {
        goto case2;
    }
    if (a2 >= 3) {
        goto ge3;
    }
    if (a2 == t72) {
        goto case1;
    }
    return 0;
ge3:
    if (a2 == 3) {
        goto case3;
    }
    if (a2 == 4) {
        goto case4;
    }
    return 0;
case1:
    v = *(unsigned char *)(q + 0x65);
    if (v == 0xF3) {
        return 0;
    }
    return v >> 4;
case2:
    if (*(unsigned char *)(q + 0x64) == t72) {
        return 0;
    }
    return *(unsigned short *)(q + (*(unsigned char *)(q + 0x69) << 1) + 0x50);
case3:
    if (*(unsigned char *)(q + 0x64) == t72) {
        return 0;
    }
    return *(unsigned char *)(q + 0x69);
case4:
    if (*(unsigned char *)(q + 0x64) == t72) {
        return 0;
    }
    if (a3 == -1) {
        return *(unsigned char *)(q + 0x68);
    }
    if (a3 >= (int)*(unsigned char *)(q + 0x68)) {
        return 0;
    }
    return *(unsigned short *)(q + (a3 << 1) + 0x50);
    }
    return 0;
}


int func_0024AEA0(int a0, int a1, int a2, int a3) {
    int *s0 = D_007115C0;
    int local = 0;
    int ret;
    int s;
    D_007115C0[0] = 6;
    s0[1] = a0;
    s0[2] = a1;
    s0[3] = a2;
    s0[4] = a3;
    ret = func_00242978((int)D_00711280, 1, 0, (int)s0, 0x80, (int)s0, 0x80, 0, local);
    if (ret < 0) {
        return 0;
    }
    s = s0[5];
    if (s == 1) {
        func_0024AA38(a0, a1, 2);
        s = s0[5];
    }
    return s;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024AF58);

extern int func_0024AA38(int a0, int a1, int a2);

int func_0024B010(int a0, int a1, char *a2)
{
    int *s0 = D_007115C0;
    int i;
    int val;
    int *new_var;
    int ret;
    char *dst;
    D_007115C0[0] = 8;
    new_var = D_007115C0;
    s0[1] = a0;
    s0[2] = a1;
    dst = (char *)s0 + 0xC;
    for (i = 0; i < 6; i++) {
        dst[i] = a2[i];
    }
    ret = func_00242978(D_00711280, 1, 0, new_var, 0x80, new_var, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        func_0024AA38(a0, a1, 2);
        val = s0[5];
    }
    return val;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B0E8);

extern int D_007115C0[];
extern int D_00711280[];

int func_0024B1A0(int a0, int a1, int a2) {
    int ret;
    D_007115C0[3] = a2;
    D_007115C0[0] = 0xA;
    D_007115C0[1] = a0;
    D_007115C0[2] = a1;
    if (func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0) < 0) {
        return 0;
    }
    ret = D_007115C0[4];
    if (ret == 1) {
        func_0024AA38(a0, a1, 2);
        ret = D_007115C0[4];
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B250);

int func_0024B2B0(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return func_0024B1A0(a0, a1, 0xFFF);
}

int func_0024B308(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return func_0024B1A0(a0, a1, 0);
}

struct S12 { char b[12]; };
extern int D_007115C0[];
extern int D_00711280[];
extern int func_00242978();
extern int func_0024AA38(int a0, int a1, int a2);

int func_0024B360(int a0, int a1, void *a2) {
    int r;
    D_007115C0[1] = a0;
    D_007115C0[0] = 0xB;
    D_007115C0[2] = a1;
    *(struct S12 *)((char *)D_007115C0 + 0xC) = *(struct S12 *)a2;
    r = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    if (D_007115C0[7] == 1) {
        func_0024AA38(a0, a1, 2);
    }
    return D_007115C0[7];
}

int func_0024B430(void) {
    int ret;
    D_007115C0[0] = 0xC;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}

int func_0024B498(int a0) {
    int ret;
    D_007115C0[0] = 0xD;
    D_007115C0[1] = a0;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}

int func_0024B500(void) {
    int ret;
    D_007115C0[0] = 0x12;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}

int func_0024B568(int a0) {
    int ret;
    D_007115C0[0] = 0x14;
    D_007115C0[1] = a0;
    ret = func_00242978(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[2];
}

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

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024B7B8(void *a0) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[5] = (int)a0;
    r = func_00242978(obj, 0x14, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x14;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024B870(void *a0) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[1] = (int)a0;
    r = func_00242978(obj, 0x15, 0, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r != 0) {
        func_00100540(D_0054C694[0]);
        return r;
    }
    func_00100540(D_0054C694[0]);
    return ((int *)D_00712C00)[0];
}

extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();
extern void func_00261900(char *a0, char *a1, int a2);
extern char D_0054C690[];
extern int D_0054C694[];
extern char D_00711640[];
extern char D_00711704[];
extern char D_00712C00[];

typedef struct { int unk0; int unk4; int unk8; char _C[0x407]; char unk413; } SomeBlk;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B930);




extern int func_0024B930(int a0, int a1, int a2, int a3);

int func_0024BA68(int a0, int a1, int a2) {
    int ret = func_0024B930(a0, a1, a2, 0x40);
    if (ret == 0) {
        *(int *)D_0054C690 = 0xB;
    }
    return ret;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024BAA0(void *a0) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    r = func_00242978(obj, 3, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 3;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024BB58(void *a0, int a1, int a2) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    D_007116C0[4] = a1;
    D_007116C0[5] = a2;
    r = func_00242978(obj, 4, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 4;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BC30);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern char D_00711B40[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern void func_002483F8(void *a0, int a1);
extern int func_0024BC30();
extern int func_00242978();

int func_0024BCC0(void *a0, int a1, int a2) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    D_007116C0[7] = (int)D_00711B40;
    D_007116C0[6] = a1;
    D_007116C0[3] = a2;
    func_002483F8((void *)a1, a2);
    func_002483F8(D_00711B40, 0xC0);
    r = func_00242978(obj, 5, 1, D_007116C0, 0x30, D_00712C00, 4, func_0024BC30, D_00711B40);
    if (r == 0) {
        *(int *)D_0054C690 = 5;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BDE0);

extern void func_00100F18(int a0);

void func_0024BF60(int a0, int a1, int a2) {
    func_00100F18(a2);
    SYNC();
    EI();
}

extern int func_00100410(void);
extern int func_001002A0(int a0, void *a1, int a2);

void func_0024BF88(int a0) {
    func_001002A0(a0 & 0xFFFF, func_0024BF60, func_00100410());
    func_00100440();
}

extern char D_0054C690[];
extern char D_00711640[];
extern char D_00712C00[];
extern int D_0054C694[];
extern int func_00242B68(char *a0);
extern void func_0024BF88(int a0);
extern void func_00100540(int a0);

int func_0024BFD0(int a0, int *a1, int *a2) {
    int r;
    if (*(int *)D_0054C690 == 0) {
        return 0xFFFFFFFF;
    }
    r = func_00242B68(D_00711640);
    if (a0 != 0) goto L050;
    if (r == 0) goto L050;
    while (func_00242B68(D_00711640) != 0) {
        func_0024BF88(0x3C);
    }
    r = 0;
L050:
    r = (r == 0);
    if (a1 != 0) {
        *a1 = *(int *)D_0054C690;
    }
    if (r != 0) {
        *(int *)D_0054C690 = 0;
        if (a2 != 0) {
            *a2 = *(int *)D_00712C00;
        }
        func_00100540(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C0B0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C108);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C290);

extern int func_0026160C(char *a0);
extern int func_002604B8(char *a0, char *a1, int a2);
extern char D_00711C00[];

void func_0024C3E8(char *a0) {
    int n;
    if (a0 != 0) {
        if ((unsigned int)func_0026160C((char *)((int)D_00711C00 | 0x20000000)) < 0x400) {
            n = func_0026160C((char *)((int)D_00711C00 | 0x20000000));
        } else {
            n = 0x3FF;
        }
        func_002604B8(a0, (char *)((int)D_00711C00 | 0x20000000), n);
        a0[n] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C470);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024C5C0(void *a0, int a1) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[2] = a1;
    D_007116C0[1] = (int)a0;
    r = func_00242978(obj, 0x10, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x10;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C688);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024C7B0(void *a0) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    r = func_00242978(obj, 0xA, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0xA;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024CA40);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern int func_00242978();

int func_0024CBA8(void *a0, int a1) {
    int *obj;
    int r;
    r = func_00100570(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    D_007116C0[2] = a1;
    D_007116C0[1] = (int)a0;
    r = func_00242978(obj, 0x11, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x11;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116F0[];
extern int func_00100570(int a0);
extern void func_00100540(int a0);
extern void func_00261900(char *a0, char *a1, int a2);
extern int func_00242978();

int func_0024CC70(void *a0, int a1, char *a2) {
    int *obj;
    int r;
    if (func_00100570(D_0054C694[0]) < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        func_00100540(D_0054C694[0]);
        return -100;
    }
    if (a2 == 0 || a2[0] == 0) {
        func_00100540(D_0054C694[0]);
        return -210;
    }
    D_007116F0[0] = (int)a0;
    D_007116F0[1] = a1;
    func_00261900((char *)D_007116F0 + 0x14, a2, 0x3FF);
    *((char *)D_007116F0 + 0x413) = 0;
    r = func_00242978(D_00711640, 0x12, 1, D_007116F0, 0x414, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x12;
    } else {
        func_00100540(D_0054C694[0]);
    }
    return r;
}

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

extern int func_00254898(int *bs, int nbits);
extern int func_002548E8(int *bs);
extern int func_002547E0(void *a0, int a1);
extern int func_0024D568();

typedef struct { int unk0, unk4, unk8, unkC; } P24D418;

int func_0024D418(int *bs, P24D418 *pkt) {
    unsigned int i = 0;
    unsigned int a, b, c, n;
    int last;

    func_00254898(bs, 0x22);
    a = func_00254898(bs, 0x3);
    func_002548E8(bs);
    b = func_00254898(bs, 0xF);
    func_002548E8(bs);
    c = func_00254898(bs, 0xF);
    func_002548E8(bs);
    pkt->unk0 = func_00254898(bs, 0x9);
    func_00254898(bs, 0x1E);
    n = func_00254898(bs, 0x3);
    pkt->unk8 = (a >> 2) & 1;
    pkt->unk4 = (a << 30) | (b << 15) | c;
    for (i = 0; i < n; i++) {
        func_00254898(bs, 0x8);
    }
    last = func_002547E0(bs, 0x20);
    if (last != 0x1BB) goto unset;
    pkt->unkC = 1;
    func_0024D568(bs, pkt);
    goto end;
unset:
    pkt->unkC = 0;
end:
    return 1;
}


int func_0024D568(int *a0) {
    func_00254898(a0, 0x38);
    func_00254898(a0, 0x28);
    while (func_002547E0(a0, 1) == 1) {
        func_00254898(a0, 0x18);
    }
    return 1;
}

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

int func_0024DE80(int *a0, unsigned int a1, int a2) {
    int *p = (int *)a0[0x40/4];
    a1 = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xB0/4] = 1;
    p[0xD8/4] = a1;
    p[0xE4/4] = a2;
    p[0xE0/4] = 0;
    p[0xDC/4] = 0;
    return func_0024E260((int)a0);
}

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

extern int D_0054C780[];
extern int D_0054C784[];
extern int D_0054C78C[];
extern int D_0054C790[];
extern int D_0054C798[];
extern int D_0054C79C[];

int func_0024DFF8(void) {
    if (D_0054C780[0] != 0) *(int *)(D_0054C780[0] + 0x28) = 0;
    if (D_0054C78C[0] != 0) *(int *)(D_0054C78C[0] + 0x28) = 0;
    if (D_0054C798[0] != 0) *(int *)(D_0054C798[0] + 0x28) = 0;
    if (D_0054C784[0] != 0) *(int *)(D_0054C784[0] + 0x28) = 0;
    if (D_0054C790[0] != 0) *(int *)(D_0054C790[0] + 0x28) = 0;
    if (D_0054C79C[0] != 0) *(int *)(D_0054C79C[0] + 0x28) = 0;
    return 1;
}

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

/* func_0024E088 — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
/* func_0024E088 — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
/* func_0024E088 — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
/* func_0024E088 — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E088);





extern void *func_0024E088(void *a0, void *a1);

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

extern void func_0024E920(void *a0);
extern int D_00628E28[];

int func_0024E1E0(unsigned int *a0, int a1, unsigned int a2) {
    unsigned int rounded;
    unsigned int total;
    rounded = ((a0[2] + a2 - 1) / a2) * a2;
    total = rounded + a1;
    if (a0[0] + a0[1] >= total) {
        a0[2] = total;
        return rounded;
    }
    func_0024E920(D_00628E28);
    return 0;
}

int func_0024E248(int *a0) {
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E260);

extern int func_00253570(int a0);
extern int func_002533D8(int a0, int a1);
extern void func_002534B8(int a0, int a1);
extern void func_0024E0D8(void *a0);
extern int D_0054C884[];
extern int D_0054C89C[];
extern int D_0054C92C[];

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E3E8);


extern int D_0054C92C[];
extern int func_0024E3E8(int a0, int a1, int a2);
extern int func_0024E550(int a0, int a1, int a2);

int func_0024E510(int a0, int a1, int a2) {
    if (D_0054C92C[0] != 3) {
        return func_0024E550(a0, a1, a2);
    }
    return func_0024E3E8(a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E550);

extern void func_0024E740(int a0);
extern int D_0054C884[];

int func_0024E6C0(int *self) {
    int *p = (int *)self[0x40 / 4];
    int ret = 0;
    if (p[1] != 0 && p[2] != 0) {
        func_0024E740(D_0054C884[0]);
        self[2] = D_0054C884[0] - p[0xAC / 4];
        p[1] = 0;
        ret = 1;
    }
    return ret;
}

extern int D_0054D030_alias[] __asm__("D_0054D030");
extern void func_00251088(int a0);

void func_0024E730(void) {
    D_0054D030_alias[0] = 0;
    func_00251088(1);
}

extern int D_0054C784[];
extern int D_0054C790[];
extern int D_0054C79C[];
extern int D_0054C89C[];
extern int D_0054C92C[];
extern char D_00628EA8[];

void func_0024E740(int a0) {
    int t;
    int d;
    int c;
    if (D_0054C89C[0]) {
        func_0024E920(D_00628EA8);
        D_0054C89C[0] = 0;
        return;
    }
    t = D_0054C92C[0];
    if (t == 3) {
        func_00253DB0(D_0054C784[0], a0 - 1);
    } else {
        func_00253EC8(D_0054C790[0], D_0054C79C[0], a0 - 1);
    }
    D_0054C89C[0] = 0;
}

extern void func_00251088(int a0);
extern int D_0054C758[];
extern int D_0054CD78[];

extern void func_00251088(int a0);
extern int D_0054C758[];
extern int D_0054CD78[];

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E7C8);



INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024E818);

extern int D_00628EC8_alias[] __asm__("D_00628EC8");
extern void func_00260668(void *a0, ...);

void func_0024E8E0(int a0) {
    func_00260668(D_00628EC8_alias, a0);
}

extern void func_00261188(void *a0, int a1, ...);
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

extern void *D_0054C764[];
extern void *func_0024E088(void *a0, void *a1);
extern void func_00252310(void);
extern void func_002522E0(unsigned int a0);

void func_0024EFF8(void *a0, int a1) {
    int local[8];
    local[0] = 2;
    func_0024E088(D_0054C764[0], local);
    func_00252310();
    *(volatile int *)0x10002000 = 0;
    func_00252310();
    *(volatile int *)0x1000B410 = a1 & 0x0FFFFFFF;
    *(volatile int *)0x1000B420 = 4;
    *(volatile int *)0x1000B400 = 0x101;
    func_002522E0((unsigned int)a0);
    func_00252310();
    local[0] = 3;
    func_0024E088(D_0054C764[0], local);
}

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

/* func_002502B8: handwritten MMI unaligned-copy/unpack loop — qfsrv funnel shift
 * (shift amount from mtsab) then pextlb/pextub byte-unpack, double-buffered.
 * In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_002502B8\n"
    "    .type func_002502B8, @function\n"
    "    .align 3\n"
    "func_002502B8:\n"
    "    lw    $5, 0x14($4)\n"
    "    lw    $6, 0x18($4)\n"
    "    lw    $7, 0x8($4)\n"
    "    lw    $14, 0x0($4)\n"
    "    lw    $13, 0x4($4)\n"
    "    lw    $12, 0x10($4)\n"
    "    sll   $11, $12, 1\n"
    "    addiu $15, $0, -0x1\n"
    "    mtsab $13, 0x0\n"
    "1:\n"
    "    lq    $8, 0x0($5)\n"
    "    addi  $7, $7, -0x1\n"
    "    lq    $9, 0x0($6)\n"
    "    addu  $5, $5, $12\n"
    "    qfsrv $10, $9, $8\n"
    "    pextlb $8, $0, $10\n"
    "    pextub $9, $0, $10\n"
    "    sq    $8, 0x0($14)\n"
    "    addu  $6, $6, $12\n"
    "    sq    $9, 0x10($14)\n"
    "    bgtz  $7, 1b\n"
    "    addu  $14, $14, $11\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw    $7, 0xC($4)\n"
    "    and   $10, $15, $7\n"
    "    bnez  $10, 1b\n"
    "    daddu $15, $0, $0\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_002502B8, . - func_002502B8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250330: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250330\n"
    ".type func_00250330, @function\n"
    "    .align 3\n"
    "func_00250330:\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    sll $11, $12, 1\n"
    "    mtsab $13, 0x0\n"
    "    addiu $24, $0, -0x1\n"
    ".L00250350:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $15, $0, -0x1\n"
    ".L00250358:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $9, $8, $8\n"
    "    pextlb $8, $0, $9\n"
    "    sq $8, 0x0($14)\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $12\n"
    "    addu $14, $14, $11\n"
    "    bgtz $7, .L00250358\n"
    "    addu $6, $6, $12\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $15, $7\n"
    "    bnez $10, .L00250358\n"
    "    daddu $15, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $24, .L00250350\n"
    "    daddu $24, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250330, . - func_00250330\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002503C8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002503C8\n"
    ".type func_002503C8, @function\n"
    "    .align 3\n"
    "func_002503C8:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $24, 0x10($4)\n"
    "    lq $8, 0x0($5)\n"
    "    sll $12, $24, 1\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    pextlb $8, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    beqz $7, .L0025045C\n"
    "    pextub $9, $0, $10\n"
    ".L0025040C:\n"
    "    addu $5, $5, $24\n"
    "    addu $6, $6, $24\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    qfsrv $2, $15, $10\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L0025040C\n"
    "    addu $14, $14, $12\n"
    ".L0025045C:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L0025040C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_002503C8, . - func_002503C8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250480: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250480\n"
    ".type func_00250480, @function\n"
    "    .align 3\n"
    "func_00250480:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $11, $0, 0x1\n"
    "    sll $24, $12, 1\n"
    "    mtsab $13, 0x0\n"
    ".L002504A8:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    ori $11, $11, 0x8000\n"
    "    beqz $7, .L00250504\n"
    "    pextlb $15, $0, $8\n"
    ".L002504C8:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $10, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L002504C8\n"
    "    addu $14, $14, $24\n"
    ".L00250504:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L002504C8\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L002504A8\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250480, . - func_00250480\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250550: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250550\n"
    ".type func_00250550, @function\n"
    "    .align 3\n"
    "func_00250550:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    lw $9, 0x10($4)\n"
    "    sll $8, $9, 1\n"
    "    addiu $11, $0, -0x1\n"
    ".L0025057C:\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $10, $25\n"
    "    paddh $3, $15, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    addu $5, $5, $9\n"
    "    addu $6, $6, $9\n"
    "    bgtz $7, .L0025057C\n"
    "    addu $14, $14, $8\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $12, $11, $7\n"
    "    bnez $12, .L0025057C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250550, . - func_00250550\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250600: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250600\n"
    ".type func_00250600, @function\n"
    "    .align 3\n"
    "func_00250600:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $12, $0, -0x1\n"
    "    lw $3, 0x10($4)\n"
    "    sll $2, $3, 1\n"
    ".L00250628:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250630:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $3\n"
    "    addu $6, $6, $3\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $10, $10, $25\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250630\n"
    "    addu $14, $14, $2\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250630\n"
    "    daddu $11, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $12, .L00250628\n"
    "    daddu $12, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00250600, . - func_00250600\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002506B8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002506B8\n"
    ".type func_002506B8, @function\n"
    "    .align 3\n"
    "func_002506B8:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    lq $8, 0x0($5)\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    qfsrv $15, $8, $9\n"
    "    pextlb $8, $0, $10\n"
    "    pextub $9, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $15, $15, $10\n"
    "    pextlb $10, $0, $15\n"
    "    pextub $15, $0, $15\n"
    "    paddh $8, $8, $10\n"
    "    beqz $7, .L00250790\n"
    "    paddh $9, $9, $15\n"
    ".L0025071C:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 2\n"
    "    psrlh $3, $3, 2\n"
    "    sq $2, 0x0($14)\n"
    "    sll $10, $12, 1\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L0025071C\n"
    "    addu $14, $14, $10\n"
    ".L00250790:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L0025071C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_002506B8, . - func_002506B8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002507B0: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_002507B0\n"
    ".type func_002507B0, @function\n"
    "    .align 3\n"
    "func_002507B0:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $11, $0, 0x1\n"
    ".L002507D8:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addu $5, $5, $12\n"
    "    ori $11, $11, 0x8000\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    beqz $7, .L00250864\n"
    "    paddh $15, $9, $8\n"
    ".L00250810:\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $12\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    sll $8, $12, 1\n"
    "    psrlh $10, $10, 2\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250810\n"
    "    addu $14, $14, $8\n"
    ".L00250864:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L00250810\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L002507D8\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_002507B0, . - func_002507B0\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_002508B0: handwritten MMI averaging loop — qfsrv funnel shift + pextlb/pextub
 * byte-unpack, paddh accumulate, then signed round-half (pcgth/psrlh/paddh/psrlh) to
 * divide by 2. Double-buffered. In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_002508B0\n"
    "    .type func_002508B0, @function\n"
    "    .align 3\n"
    "func_002508B0:\n"
    "    lw    $5, 0x14($4)\n"
    "    lw    $6, 0x18($4)\n"
    "    lw    $7, 0x8($4)\n"
    "    lw    $14, 0x0($4)\n"
    "    lw    $13, 0x4($4)\n"
    "    lw    $9, 0x10($4)\n"
    "    sll   $8, $9, 1\n"
    "    addiu $11, $0, -0x1\n"
    "    mtsab $13, 0x0\n"
    "1:\n"
    "    lq    $10, 0x0($5)\n"
    "    lq    $15, 0x0($6)\n"
    "    qfsrv $2, $15, $10\n"
    "    pextlb $10, $0, $2\n"
    "    pextub $15, $0, $2\n"
    "    lq    $2, 0x0($14)\n"
    "    lq    $3, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq    $2, 0x0($14)\n"
    "    sq    $3, 0x10($14)\n"
    "    addi  $7, $7, -0x1\n"
    "    addu  $5, $5, $9\n"
    "    addu  $14, $14, $8\n"
    "    bgtz  $7, 1b\n"
    "    addu  $6, $6, $9\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw    $7, 0xC($4)\n"
    "    and   $12, $11, $7\n"
    "    bnez  $12, 1b\n"
    "    daddu $11, $0, $0\n"
    "    jr    $31\n"
    "    nop\n"
    "    .size func_002508B0, . - func_002508B0\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250958: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250958\n"
    ".type func_00250958, @function\n"
    "    .align 3\n"
    "func_00250958:\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $12, $0, -0x1\n"
    "    lw $3, 0x10($4)\n"
    "    sll $2, $3, 1\n"
    "    mtsab $13, 0x0\n"
    ".L00250978:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250980:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $3\n"
    "    addu $6, $6, $3\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $9, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250980\n"
    "    addu $14, $14, $2\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250980\n"
    "    daddu $11, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $12, .L00250978\n"
    "    daddu $12, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250958, . - func_00250958\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250A08: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250A08\n"
    ".type func_00250A08, @function\n"
    "    .align 3\n"
    "func_00250A08:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    lq $8, 0x0($5)\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    sll $24, $12, 1\n"
    "    pextlb $8, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    beqz $7, .L00250ACC\n"
    "    pextub $9, $0, $10\n"
    ".L00250A4C:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    qfsrv $2, $15, $10\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    lq $10, 0x0($14)\n"
    "    lq $15, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L00250A4C\n"
    "    addu $14, $14, $24\n"
    ".L00250ACC:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250A4C\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250A08, . - func_00250A08\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250AF0: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250AF0\n"
    ".type func_00250AF0, @function\n"
    "    .align 3\n"
    "func_00250AF0:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $11, $0, 0x1\n"
    "    sll $24, $12, 1\n"
    "    mtsab $13, 0x0\n"
    ".L00250B18:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    ori $11, $11, 0x8000\n"
    "    beqz $7, .L00250B8C\n"
    "    pextlb $15, $0, $8\n"
    ".L00250B38:\n"
    "    addu $5, $5, $12\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $10, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    psrlh $10, $10, 1\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $10, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250B38\n"
    "    addu $14, $14, $24\n"
    ".L00250B8C:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L00250B38\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L00250B18\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250AF0, . - func_00250AF0\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250BD8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250BD8\n"
    ".type func_00250BD8, @function\n"
    "    .align 3\n"
    "func_00250BD8:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    lw $9, 0x10($4)\n"
    "    sll $8, $9, 1\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250C04:\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $10, $25\n"
    "    paddh $3, $15, $25\n"
    "    psrlh $2, $2, 1\n"
    "    psrlh $3, $3, 1\n"
    "    lq $10, 0x0($14)\n"
    "    lq $15, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sq $3, 0x10($14)\n"
    "    addu $5, $5, $9\n"
    "    addu $6, $6, $9\n"
    "    bgtz $7, .L00250C04\n"
    "    addu $14, $14, $8\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $12, $11, $7\n"
    "    bnez $12, .L00250C04\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250BD8, . - func_00250BD8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250CB8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250CB8\n"
    ".type func_00250CB8, @function\n"
    "    .align 3\n"
    "func_00250CB8:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $12, $0, -0x1\n"
    "    lw $3, 0x10($4)\n"
    "    sll $2, $3, 1\n"
    ".L00250CE0:\n"
    "    lw $7, 0x8($4)\n"
    "    addiu $11, $0, -0x1\n"
    ".L00250CE8:\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $3\n"
    "    addu $6, $6, $3\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $10, $10, $25\n"
    "    psrlh $10, $10, 1\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $10, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250CE8\n"
    "    addu $14, $14, $2\n"
    "    addiu $5, $5, 0x140\n"
    "    addiu $6, $6, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250CE8\n"
    "    daddu $11, $0, $0\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    bnez $12, .L00250CE0\n"
    "    daddu $12, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00250CB8, . - func_00250CB8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250D88: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250D88\n"
    ".type func_00250D88, @function\n"
    "    .align 3\n"
    "func_00250D88:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $7, 0x8($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $24, 0x10($4)\n"
    "    addiu $12, $0, 0x1\n"
    "    lq $8, 0x0($5)\n"
    "    lq $9, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $10, $9, $8\n"
    "    qfsrv $15, $8, $9\n"
    "    pextlb $8, $0, $10\n"
    "    pextub $9, $0, $10\n"
    "    addiu $11, $0, -0x1\n"
    "    mtsab $12, 0x0\n"
    "    qfsrv $15, $15, $10\n"
    "    pextlb $10, $0, $15\n"
    "    pextub $15, $0, $15\n"
    "    paddh $8, $8, $10\n"
    "    beqz $7, .L00250E90\n"
    "    paddh $9, $9, $15\n"
    ".L00250DEC:\n"
    "    addu $5, $5, $24\n"
    "    addu $6, $6, $24\n"
    "    lq $10, 0x0($5)\n"
    "    lq $15, 0x0($6)\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $2, $15, $10\n"
    "    qfsrv $3, $10, $15\n"
    "    pextlb $10, $0, $2\n"
    "    addi $7, $7, -0x1\n"
    "    pextub $15, $0, $2\n"
    "    mtsab $12, 0x0\n"
    "    qfsrv $3, $3, $2\n"
    "    pextlb $2, $0, $3\n"
    "    pextub $3, $0, $3\n"
    "    paddh $10, $10, $2\n"
    "    paddh $15, $15, $3\n"
    "    paddh $2, $8, $10\n"
    "    paddh $3, $9, $15\n"
    "    por $8, $10, $0\n"
    "    por $9, $15, $0\n"
    "    paddh $2, $2, $25\n"
    "    paddh $3, $3, $25\n"
    "    psrlh $2, $2, 2\n"
    "    psrlh $3, $3, 2\n"
    "    lq $10, 0x0($14)\n"
    "    lq $15, 0x10($14)\n"
    "    paddh $2, $2, $10\n"
    "    paddh $3, $3, $15\n"
    "    pcgth $10, $2, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $2, $10\n"
    "    psrlh $2, $10, 1\n"
    "    pcgth $10, $3, $0\n"
    "    psrlh $10, $10, 15\n"
    "    paddh $10, $3, $10\n"
    "    psrlh $3, $10, 1\n"
    "    sq $2, 0x0($14)\n"
    "    sll $10, $24, 1\n"
    "    sq $3, 0x10($14)\n"
    "    bgtz $7, .L00250DEC\n"
    "    addu $14, $14, $10\n"
    ".L00250E90:\n"
    "    addiu $5, $5, 0x80\n"
    "    addiu $6, $6, 0x80\n"
    "    lw $7, 0xC($4)\n"
    "    and $10, $11, $7\n"
    "    bnez $10, .L00250DEC\n"
    "    daddu $11, $0, $0\n"
    "    jr $31\n"
    "    nop\n"
    ".size func_00250D88, . - func_00250D88\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_00250EB0: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00250EB0\n"
    ".type func_00250EB0, @function\n"
    "    .align 3\n"
    "func_00250EB0:\n"
    "    pnor $25, $0, $0\n"
    "    psrlh $25, $25, 15\n"
    "    psllh $25, $25, 1\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    lw $13, 0x4($4)\n"
    "    lw $12, 0x10($4)\n"
    "    addiu $24, $0, 0x1\n"
    "    addiu $11, $0, 0x1\n"
    ".L00250ED8:\n"
    "    lw $7, 0x8($4)\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addu $5, $5, $12\n"
    "    ori $11, $11, 0x8000\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    beqz $7, .L00250F7C\n"
    "    paddh $15, $9, $8\n"
    ".L00250F10:\n"
    "    addu $6, $6, $12\n"
    "    ld $8, 0x0($5)\n"
    "    ld $9, 0x0($6)\n"
    "    pcpyld $8, $9, $8\n"
    "    mtsab $13, 0x0\n"
    "    qfsrv $8, $8, $8\n"
    "    pextlb $9, $0, $8\n"
    "    addi $7, $7, -0x1\n"
    "    addu $5, $5, $12\n"
    "    mtsab $24, 0x0\n"
    "    qfsrv $10, $0, $8\n"
    "    pextlb $8, $0, $10\n"
    "    paddh $10, $9, $8\n"
    "    paddh $9, $10, $15\n"
    "    por $15, $10, $0\n"
    "    paddh $10, $9, $25\n"
    "    psrlh $10, $10, 2\n"
    "    lq $8, 0x0($14)\n"
    "    paddh $10, $10, $8\n"
    "    pcgth $9, $10, $0\n"
    "    psrlh $9, $9, 15\n"
    "    paddh $10, $10, $9\n"
    "    sll $8, $12, 1\n"
    "    psrlh $10, $10, 1\n"
    "    sq $10, 0x0($14)\n"
    "    bgtz $7, .L00250F10\n"
    "    addu $14, $14, $8\n"
    ".L00250F7C:\n"
    "    psrah $10, $11, 15\n"
    "    addiu $5, $5, 0x140\n"
    "    lw $7, 0xC($4)\n"
    "    addiu $6, $6, 0x140\n"
    "    and $10, $10, $7\n"
    "    bnez $10, .L00250F10\n"
    "    andi $11, $11, 0x7FFF\n"
    "    lw $5, 0x14($4)\n"
    "    lw $6, 0x18($4)\n"
    "    lw $14, 0x0($4)\n"
    "    addiu $5, $5, 0x40\n"
    "    addiu $6, $6, 0x40\n"
    "    addiu $14, $14, 0x80\n"
    "    andi $10, $11, 0x1\n"
    "    bnez $10, .L00250ED8\n"
    "    andi $11, $11, 0xFFFE\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_00250EB0, . - func_00250EB0\n"
    "    .set reorder\n"
    "    .set at\n"
);

void func_00250FC8(void *a0, void *a1, void *a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "addiu $12, $0, 0x18\n"
        "lui $10, %%hi(D_00251070)\n"
        "addiu $10, $10, %%lo(D_00251070)\n"
        "lq $11, 0x0($10)\n"
        "1:\n"
        "lq $8, 0x0($5)\n"
        "addi $12, $12, -0x1\n"
        "lq $13, 0x0($6)\n"
        "addiu $4, $4, 0x10\n"
        "lq $9, 0x10($5)\n"
        "paddh $8, $8, $13\n"
        "lq $2, 0x10($6)\n"
        "pminh $8, $8, $11\n"
        "paddh $9, $9, $2\n"
        "pmaxh $8, $8, $0\n"
        "pminh $9, $9, $11\n"
        "addiu $5, $5, 0x20\n"
        "pmaxh $9, $9, $0\n"
        "addiu $6, $6, 0x20\n"
        "ppacb $10, $9, $8\n"
        "bnez $12, 1b\n"
        "sq $10, -0x10($4)\n"
        ".set reorder\n"
        ::: "$2","$8","$9","$10","$11","$12","$13","memory");
}

/* func_00251028: handwritten MMI byte-clamp/pack loop (pminh/pmaxh/ppacb) with
 * an inline 0x00FF00FF clamp mask (D_00251070) loaded via an absolute %hi/%lo
 * address; in-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00251028\n"
    "    .type func_00251028, @function\n"
    "    .align 3\n"
    "func_00251028:\n"
    "    .word 0x240C0018\n"
    "    .word 0x3C0A0025\n"
    "    .word 0x254A1070\n"
    "    .word 0x794B0000\n"
    "    .word 0x78A80000\n"
    "    .word 0x218CFFFF\n"
    "    .word 0x710B41E8\n"
    "    .word 0x78A90010\n"
    "    .word 0x710041C8\n"
    "    .word 0x712B49E8\n"
    "    .word 0x24A50020\n"
    "    .word 0x712049C8\n"
    "    .word 0x24840010\n"
    "    .word 0x712856C8\n"
    "    .word 0x1580FFF5\n"
    "    .word 0x7C8AFFF0\n"
    "    .word 0x00000000\n"
    "    .word 0x00000000\n"
    "    .global D_00251070\n"
    "    .type D_00251070, @object\n"
    "D_00251070:\n"
    "    .word 0x00FF00FF\n"
    "    .word 0x00FF00FF\n"
    "    .word 0x00FF00FF\n"
    "    .word 0x00FF00FF\n"
    "    .size D_00251070, . - D_00251070\n"
    "    .word 0x03E00008\n"
    "    .word 0x00000000\n"
    "    .size func_00251028, . - func_00251028\n"
    "    .set reorder\n"
    "    .set at\n"
);

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

extern int func_00252620(int a0);
extern void func_00252758(int a0);
extern int D_0054C888[];
extern int D_0054D030[];
extern int D_006290B0[];

int func_00251440(void) {
    int cont;
    int sum;
    unsigned int v;

    sum = 0;
    do {
        v = func_00252468(0);
        switch (v) {
        case 0x22:
            cont = 1;
            break;
        case 0x23:
            cont = 1;
            sum += 0x21;
            break;
        case 0:
            {
                int r = func_00252620(0xB);
                if ((D_0054D030[0] != 0) && (r == 0xF)) {
                    func_00252758(0xB);
                    cont = 1;
                } else {
                    func_0024E8F0((int) D_006290B0, v);
                    D_0054C888[0] = 1;
                    return 1;
                }
            }
            break;
        default:
            sum += v;
            cont = 0;
            break;
        }
    } while (cont);
    return sum;
}


/* func_00251550 */
extern int D_0054C8A8[], D_0054C8AC[];
extern char D_006290E8[];
extern int func_002517A0(int a0, int a1);
extern void func_00252310(void);
extern int func_002510B0(void);
extern void func_00250128(int a0);
extern void func_0024E920(void *a0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251550);


extern void func_002529D8(void);
extern int func_00252620(int a0);
extern void func_00252758(int a0);
extern int func_00252A40(void);
extern int func_00251440(void);
extern void func_0024E920(void *a0);
extern int D_0054C888[];
extern int D_0054C8A8[];
extern int D_0054C9BC[];
extern int D_00629108[];
extern int D_00629130[];

int func_00251678(int a0, int *a1, int *a2, int *a3) {
    int id;
    int m;
    int n;

    D_0054C888[0] = 0;
    func_002529D8();
    id = func_00252620(0x20);
    if ((unsigned int) (id - 0x101) >= 0xAF) {
        func_0024E8F0((int) D_00629108, id);
        return 2;
    }
    func_00252758(0x20);
    m = func_00252A40();
    n = func_00251440();
    *a2 = n;
    if (D_0054C888[0] != 0) {
        func_0024E920(D_00629130);
        return 1;
    }
    *a1 = ((((m << 7) + (id & 0xFF)) - 1) * D_0054C8A8[0] + n) - 1;
    *a2 = 1;
    D_0054C9BC[0] = 1;
    a3[5] = 0;
    a3[4] = 0;
    a3[1] = 0;
    a3[0] = 0;
    a3[7] = 0;
    a3[6] = 0;
    a3[3] = 0;
    a3[2] = 0;
    return 0;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002517A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002519A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251A70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00251F98);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252020);

extern int func_00252468();
extern int func_00252870();
extern void func_00251F98();
extern int func_00251298(void);

void func_002521A0(char *a0, char *a1, void *a2, void *a3, int a4, int a5, int a6) {
    void *r;
    int r2;

    r = (void *)func_00252468(2);
    if (a2 == 0) goto c1z;
    if (r == 0) { r2 = 0; goto c1c; }
    r2 = func_00252870(a2);
    goto c1c;
c1z:
    r2 = 0;
c1c:
    func_00251F98(a0, a2, r, r2, a6);
    if (a4 != 0) {
        *(int *)a1 = func_00251298();
    }
    r = (void *)func_00252468(2);
    if (a3 == 0) goto c2z;
    if (r == 0) { r2 = 0; goto c2c; }
    r2 = func_00252870(a3);
    goto c2c;
c2z:
    r2 = 0;
c2c:
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) >> 1;
    }
    func_00251F98(a0 + 4, a3, r, r2, a6);
    if (a5 != 0) {
        *(int *)(a0 + 4) = *(int *)(a0 + 4) * 2;
    }
    if (a4 != 0) {
        *(int *)(a1 + 4) = func_00251298();
    }
}


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

extern void func_00252310(void);
void func_002529D8(void) {
    int v;
    func_00252310();
    v = (-(*(volatile int *)0x10002020 & 7)) & 7;
    if (v) func_00252758(v);
    while (func_00252620(0x18) != 1) {
        func_00252758(8);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252A40);

/* m2c scaffold from asm/aug6/nonmatchings/common/src/PObj/func_00252AB0.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern int func_00252870(int a0);
extern void func_0024EA70(void);
extern void func_00252BD8(void);
extern void func_002530A0(void);
extern int D_0054C8FC[];
extern long long D_0054D008[];
extern long long D_0054D010[];

int func_00252AB0(void) {
    struct { int f0; long long f8; long long f10; } local;

    while (1) {
        func_002529D8();
        switch ((unsigned int) func_00252870(0x20)) {
        case 0x1B3:
            func_0024EA70();
            break;
        case 0x1B8:
            func_002530A0();
            break;
        case 0x100:
            func_00252BD8();
            local.f0 = 5;
            local.f8 = -1;
            local.f10 = -1;
            func_0024E088(D_0054C764[0], &local);
            D_0054D008[0] = local.f8;
            D_0054D010[0] = local.f10;
            return D_0054C8FC[0];
        case 0x1B7:
            return 0;
        }
    }
}


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

extern char D_00629258[];

int func_00253950(char *p) {
    char *c = *(char **)((char *)D_0054C764[0] + 0x40);
    int e0 = *(int *)(c + 0xE0);
    int flag;
    if (e0 != 0) {
        flag = *(int *)(c + 0xDC) >= *(int *)(p + 0x4) && e0 >= *(int *)(p + 0x8);
    } else {
        flag = *(int *)(c + 0xE4) >= *(int *)(p + 0xC) * *(int *)(p + 0x10);
    }
    if (flag == 0) {
        char buf[0x100];
        func_00261188(buf, (int)D_00629258, *(int *)(p + 0x4), *(int *)(p + 0x8));
        func_0024E920(buf);
    }
    return flag;
}


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

extern void func_002522E0(unsigned int a0);
extern void *func_0024E088(void *a0, void *a1);
extern void *D_0054C764[];

void func_00254088(int a0, int a1) {
    int local[8];
    while (*(volatile int *)0x10002010 < 0) {
    }
    *(volatile int *)0x1000B010 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000B020 = a1 << 6;
    *(volatile int *)0x1000B000 = 0x100;
    func_002522E0(a1 | 0x70000000);
    local[0] = 4;
    func_0024E088(D_0054C764[0], local);
    while ((*(volatile unsigned int *)0x1000B000 >> 8) & 1) {
    }
    while (*(volatile int *)0x10002010 < 0) {
    }
}

/* func_00254170: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_00254170\n"
    ".type func_00254170, @function\n"
    "    .align 3\n"
    "func_00254170:\n"
    "    lui $2, (0x1000E010 >> 16)\n"
    "    addiu $3, $0, 0x8\n"
    "    ori $2, $2, (0x1000E010 & 0xFFFF)\n"
    "    lui $5, %hi(D_0054D140)\n"
    "    sw $3, 0x0($2)\n"
    "    lui $4, (0x1000B020 >> 16)\n"
    "    ori $4, $4, (0x1000B020 & 0xFFFF)\n"
    "    lw $2, %lo(D_0054D140)($5)\n"
    "    addiu $2, $2, 0x1\n"
    "    sw $2, %lo(D_0054D140)($5)\n"
    "    lw $3, 0x0($4)\n"
    "    bnez $3, .L002541BC\n"
    "    addiu $2, $0, 0x1\n"
    "    lui $2, (0x1000B000 >> 16)\n"
    "    ori $2, $2, (0x1000B000 & 0xFFFF)\n"
    "    lw $3, 0x0($2)\n"
    "    andi $3, $3, 0x100\n"
    "    beqz $3, .L002541CC\n"
    "    addiu $2, $0, 0x1\n"
    ".L002541BC:\n"
    "    lui $3, %hi(D_0054D138)\n"
    "    sw $2, %lo(D_0054D138)($3)\n"
    "    jr $31\n"
    "    daddu $2, $0, $0\n"
    ".L002541CC:\n"
    "    lui $2, %hi(D_00713658)\n"
    "    lw $3, %lo(D_0054D140)($5)\n"
    "    lw $4, %lo(D_00713658)($2)\n"
    "    addiu $4, $4, -0x1\n"
    "    slt $3, $3, $4\n"
    "    beqz $3, .L00254244\n"
    "    lui $8, %hi(D_00713654)\n"
    "    lui $2, (0x1000B010 >> 16)\n"
    "    lw $6, %lo(D_00713654)($8)\n"
    "    ori $2, $2, (0x1000B010 & 0xFFFF)\n"
    "    ori $4, $0, 0xFFC0\n"
    "    lui $3, (0xFFC00 >> 16)\n"
    "    sw $6, 0x0($2)\n"
    "    addiu $7, $0, 0x100\n"
    "    lui $1, (0x10010000 >> 16)\n"
    "    sw $4, -0x4FE0($1)\n"
    "    lui $5, (0x10002000 >> 16)\n"
    "    lui $4, (0x700003FF >> 16)\n"
    "    ori $3, $3, (0xFFC00 & 0xFFFF)\n"
    "    lui $2, (0xFFFFFFF >> 16)\n"
    "    addu $6, $6, $3\n"
    "    lui $1, (0x10010000 >> 16)\n"
    "    sw $7, -0x5000($1)\n"
    "    ori $5, $5, (0x10002000 & 0xFFFF)\n"
    "    ori $4, $4, (0x700003FF & 0xFFFF)\n"
    "    ori $2, $2, (0xFFFFFFF & 0xFFFF)\n"
    "    sw $4, 0x0($5)\n"
    "    and $6, $6, $2\n"
    "    b .L002542A8\n"
    "    sw $6, %lo(D_00713654)($8)\n"
    ".L00254244:\n"
    "    lw $2, %lo(D_0054D140)($5)\n"
    "    bne $2, $4, .L002542A8\n"
    "    lui $3, %hi(D_00713654)\n"
    "    lw $5, %lo(D_0054D140)($5)\n"
    "    lui $6, %hi(D_00713650)\n"
    "    lw $4, %lo(D_00713650)($6)\n"
    "    sll $2, $5, 10\n"
    "    lw $7, %lo(D_00713654)($3)\n"
    "    subu $2, $2, $5\n"
    "    lui $3, (0x1000B010 >> 16)\n"
    "    subu $4, $4, $2\n"
    "    ori $3, $3, (0x1000B010 & 0xFFFF)\n"
    "    sw $4, %lo(D_00713650)($6)\n"
    "    sll $5, $4, 6\n"
    "    sw $7, 0x0($3)\n"
    "    addiu $6, $0, 0x100\n"
    "    lui $1, (0x10010000 >> 16)\n"
    "    sw $5, -0x4FE0($1)\n"
    "    lui $2, (0x10002000 >> 16)\n"
    "    lui $3, (0x70000000 >> 16)\n"
    "    lui $1, (0x10010000 >> 16)\n"
    "    sw $6, -0x5000($1)\n"
    "    or $4, $4, $3\n"
    "    ori $2, $2, (0x10002000 & 0xFFFF)\n"
    "    sw $4, 0x0($2)\n"
    ".L002542A8:\n"
    "    sync\n"
    "    ei\n"
    "    jr $31\n"
    "    daddu $2, $0, $0\n"
    ".size func_00254170, . - func_00254170\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002542B8);

extern int D_0071365C[];
extern int D_00713660[];
extern int D_00713664[];

int func_00254478(void) {
    int rem;
    *(volatile int *)0x1000E010 = 0x10;
    rem = D_00713660[0];
    D_0071365C[0] = D_0071365C[0] + 1;
    if (rem == 0) {
        return 1;
    }
    if ((unsigned int)rem > 0xFFFF) {
        int addr = D_00713664[0];
        *(volatile int *)0x1000B410 = addr;
        *(volatile int *)0x1000B420 = 0xFFFF;
        *(volatile int *)0x1000B400 = 0x101;
        D_00713664[0] = (addr + 0xFFFF0) & 0x0FFFFFFF;
        D_00713660[0] = rem - 0xFFFF;
    } else {
        *(volatile int *)0x1000B410 = D_00713664[0];
        *(volatile int *)0x1000B420 = rem;
        *(volatile int *)0x1000B400 = 0x101;
        D_00713660[0] = 0;
    }
    return 0;
}

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

int func_002548E8(int *self)
{
    int ret = func_002547E0(self, 1);
    func_00254800(self, 1);
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254930);

int func_00254988(int *a0, int a1) {
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

void func_002549B8(int *a0) {
    func_00101A40(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B000 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    func_00101A88();
}

void func_00254A20(int *a0) {
    func_00101A40(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    func_00101A88();
}

extern void func_00254A20(int *a0);
extern void func_002549B8(int *a0);

void func_00254A88(void *a0) {
    func_00254A20((int *)1);
    ((int *)a0)[0] = *(volatile int *)0x1000B410;
    ((int *)a0)[1] = *(volatile int *)0x1000B430;
    ((int *)a0)[2] = *(volatile int *)0x1000B420;
    ((int *)a0)[3] = *(volatile int *)0x1000B400;
    while (*(volatile int *)0x10002010 & 0xF0) {
    }
    func_002549B8((int *)0);
    ((int *)a0)[4] = *(volatile int *)0x1000B010;
    ((int *)a0)[5] = *(volatile int *)0x1000B020;
    ((int *)a0)[6] = *(volatile int *)0x1000B000;
    ((int *)a0)[7] = *(volatile int *)0x10002020;
    ((int *)a0)[8] = *(volatile int *)0x10002010;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254B70);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00254CC0);

void func_00254D28(int *a0) {
    func_00101A40(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    func_00101A88();
}

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

int func_00256960(void) {
    int *mgr = func_00254FF8();
    int best_idx = -1;
    int best_val = -1;
    int i;
    int idx;
    unsigned char *obj;
    int divisor;
    int one;

    i = 0;
    do {
        idx = (unsigned int)mgr[0xC] % 0x30;
        obj = func_00254FC8(idx);
        if ((*(int *)obj & 0x100) == 0 && obj[0x51] == 0) {
            return idx;
        }
        mgr[0xC]++;
    } while (++i < 0x30);
    divisor = 0x30;
    one = 1;
    i = 0x2F;
    do {
        idx = (unsigned int)mgr[0xC] % divisor;
        obj = func_00254FC8(idx);
        if ((*(int *)obj & 0x100) == 0 && obj[0x51] == one) {
            int v = *(int *)(obj + 4);
            if ((unsigned int)v < (unsigned int)best_val) {
                best_idx = idx;
                best_val = v;
            }
        }
        mgr[0xC]++;
    } while (--i >= 0);
    return best_idx;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256A98);

extern void *func_00254FF8(void);
extern void *func_00255060(void);
extern void *func_00254FC8(int a0);

int func_00256CD0(char *a0) {
    long long mask16 = 0;
    long long mask19 = 0;
    char *p18 = (char *)func_00254FF8();
    char *p20 = (char *)func_00255060();
    char *elem = (char *)func_00254FC8(0);
    int i;
    for (i = 0; i < 0x30; i++, elem += 0x58) {
        char *q;
        if (*(unsigned char *)(elem + 0x51) != 2) {
            continue;
        }
        if (!(*(int *)elem & 4)) {
            continue;
        }
        q = *(char **)(p20 + 0x10);
        if (*(unsigned short *)(elem + 0x2C) != *(unsigned char *)(q + 3)) {
            continue;
        }
        if (*(unsigned char *)(elem + 0x4E) != *(unsigned char *)(q + 1)) {
            continue;
        }
        if (*(unsigned char *)(elem + 0x54) != *(unsigned short *)(a0 + 0x18)) {
            continue;
        }
        if (*(unsigned char *)(elem + 0x50) == *(unsigned short *)(a0 + 0x4C)) {
            mask16 |= (1LL << i);
        } else {
            mask19 |= (1LL << i);
        }
    }
    if (mask16 == 0) {
        mask16 = mask19;
    }
    for (i = 0; i < 0x30; i++) {
        if ((mask16 >> i) & 1) {
            *(long long *)(p18 + 0x28) |= (1LL << i);
        }
    }
    *(int *)(a0 + 4) += 4;
    return 0;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256E18);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256F20);

extern void func_00255580(int a0, int a1, int a2, int a3);

int func_00256FA8(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    func_00255580(4, a0, (a1 << 24) | (a2 << 16) | ((a3 & 0xFF) << 8) | a4,
                  (a5 << 24) | a6);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00256FF0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257190);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257220);

extern void *func_00254FF8(void);

void func_002572F0(int *a0) {
    unsigned char *p = (unsigned char *)(a0[2] + a0[1]);
    void *q = func_00254FF8();
    *(unsigned short *)((char *)a0 + 0x1E) = p[2] | (p[3] << 8);
    *(int *)((char *)a0 + 0x10) =
        ((((int)*(unsigned short *)((char *)a0 + 0x20)
           * *(unsigned short *)((char *)a0 + 0x1E)) << 12)
         / *(unsigned short *)((char *)q + 0x3A)) / 0x3C;
    a0[1] += 4;
}

void func_00257380(int *a0)
{
  int *p;
  unsigned short idx;
  char *base;
  char *v2;
  if ((*(a0 + 0)) & 2)
  {
    p = (int *) func_00255060();
    idx = *((unsigned short *) (((char *) a0) + 0x4E));
    v2 = (char *) (*((int *) (((char *) p) + 0x10)));
    ;
    *((((char *) (*((int *) (((char *) p) + 8)))) + (idx << 4)) + 0x12) = *((unsigned char *) (v2 + 1));
    idx = *((unsigned short *) (((char *) a0) + 0x4E));
    base = ((char *) (*((int *) (((char *) p) + 8)))) + (idx << 4);
    *(base + 0x1A) = 0x40;
    idx = *((unsigned short *) (((char *) a0) + 0x4E));
    base = ((char *) (*((int *) (((char *) p) + 8)))) + (idx << 4);
    *(base + 0x1B) = 0x40;
  }
  *(a0 + 1) += 2;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257570);

extern void *func_00254FC8(int a0);
extern void *func_00254FF8(void);
extern void *func_00255060(void);

void func_002576E8(char *a0)
{
    char *p;
    char *mgr;
    char *ctx;
    char *s;
    int i;
    int n;
    int v;
    int two;

    p = (char *)func_00254FC8(0);
    mgr = (char *)func_00254FF8();
    ctx = (char *)func_00255060();
    two = 2;
    n = 0xF;
    i = 0x2F;
    do {
        if (*(unsigned char *)(p + 0x51) == two &&
            *(unsigned char *)(p + 0x54) == *(unsigned short *)(a0 + 0x18)) {
            s = *(char **)(ctx + 0x10);
            if (*(unsigned short *)(p + 0x2C) == *(unsigned char *)(s + 0x4) &&
                *(unsigned char *)(p + 0x4E) == *(unsigned char *)(s + 0x5) &&
                *(unsigned char *)(p + 0x50) == *(unsigned short *)(a0 + 0x4C)) {
                *(int *)p |= 0x20;
                v = (*(unsigned short *)(mgr + 0x3A) * *(unsigned char *)(s + 0x2)) / n;
                *(short *)(p + 0x4C) = (short)v;
                if (*(unsigned char *)(s + 0x3) & 0x80) {
                    *(float *)(p + 0x44) = (float)*(signed char *)(s + 0x3) / (float)(short)v;
                } else {
                    *(float *)(p + 0x44) = (float)*(unsigned char *)(s + 0x3) / (float)(short)v;
                }
            }
        }
        i -= 1;
        p += 0x58;
    } while (i >= 0);
    *(int *)(a0 + 0x4) += 6;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257838);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002579F0);

extern void *func_00254FC8(int a0);
extern void *func_00254FF8(void);
extern void *func_00255060(void);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257C10);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257D28);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00257DE8);

void func_00258168(void *a0) {
    void *s0 = a0;
    void *p = func_00255060();
    int t = *(unsigned short *)((char *)s0 + 0x28);
    int val;
    int pval;
    if (t == 1) goto case1;
    if (t >= 2) goto ge2;
    if (t == 0) goto case0;
    goto done;
ge2:
    if (t == 2) goto case12;
    goto done;
case0: {
    int q0 = *(int *)((char *)p + 0x10);
    int b0 = *(unsigned char *)((char *)q0 + 0x2);
    *(short *)((char *)s0 + 0x2A) = 0;
    *(short *)((char *)s0 + 0x26) = b0;
    goto done;
}
case1:
case12: {
    int q12 = *(int *)((char *)p + 0x10);
    int b12 = *(unsigned char *)((char *)q12 + 0x2);
    *(short *)((char *)s0 + 0x2A) = b12;
}
done:
    val = *(int *)((char *)s0 + 0x4);
    *(int *)((char *)s0 + 0x4) = val + 3;
}

extern void *func_00255060(void);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002581F0);



INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258328);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258438);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258490);

int func_00258650(int a0, int a1, int a2, int a3) {
    return ((a0 & 0xFF) + ((a1 & 0xFF) - (a0 & 0xFF)) * (a3 & 0xFF) / (a2 & 0xFF)) & 0xFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258688);

extern char D_007181C0[];

int func_00258820(int a0, int a1, int a2, int a3, int a4, int a5) {
    return func_00242978(D_007181C0, a0, a1, a2, a4, a3, a5, 0, 0);
}

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

extern int func_00258BF8(int *a0, int a1);

int func_00258B88(int a0, int *a1, int a2) {
    int r;
    r = func_00258BF8(a1, a2);
    if (r != -1) {
        func_00258A10(a0, (void *)a2, (void *)a1[1]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258BF8);

int func_00258CF0(int a0) {
    void *t;
    char *p;
    int i;
    int rv = -1;

    if ((unsigned int)(a0 - 1) < 0x7F) {
        t = func_00255008(a0);
        if (*(int *)((char *)t + 8) != 0) {
            p = (char *)func_00254FC8(0);
            for (i = 0; i < 0x30; i++, p += 0x58) {
                if (*(unsigned char *)(p + 0x54) == a0 &&
                    (unsigned int)*(unsigned char *)(p + 0x50) < 0x30 &&
                    *(unsigned char *)(p + 0x51) != 3) {
                    int *obj = (int *)func_00254FE0(*(unsigned char *)(p + 0x50));
                    int *q = (int *)func_00254FF8();
                    *(long long *)((char *)q + 0x28) |= (long long)1 << i;
                    *obj |= 0x2000;
                    func_00260568((char *)obj + 4, 0, 0x50);
                    *obj = 0;
                    *(int *)p |= 0x100;
                    func_00260568(p + 4, 0, 0x54);
                    *(unsigned char *)(p + 0x50) = 0xFF;
                    *(unsigned char *)(p + 0x56) = 0xFF;
                    *(unsigned char *)(p + 0x55) = 0xFF;
                    *(unsigned char *)(p + 0x54) = 0xFF;
                    *(int *)p = 0;
                }
            }
        }
        func_00260568(t, 0, 0xC);
        rv = 0;
    }
    return rv;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00258E50);

int func_00258FB8(int a0) {
    volatile int *p;
    int ret = -1;
    if ((unsigned int)a0 < 0x30) {
        p = (volatile int *)func_00254FE0(a0);
        p[0] |= 0x2000;
        if ((p[0] & 3) == 1) {
            func_00260568((char *)p + 4, 0, 0x50);
            p[0] = 0;
            ret = 0;
        }
        p[0] &= 0xFFFFDFFF;
    }
    return ret;
}

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

extern void *func_00254FE0(int a0);

int func_00259220(unsigned int a0, int a1, int a2) {
    int ret = -1;
    if (a0 < 0x30 && a1 >= 0 && a1 < 0x80) {
        int *p = (int *)func_00254FE0(a0);
        *(volatile int *)p |= 0x2000;
        if (a2 == 0xFFFF) {
            ret = p[0x34 / 4];
            p[0x30 / 4] = a2;
            p[0x34 / 4] = a1;
        } else {
            p[0x38 / 4] = a2;
            ret = 0;
            p[0x3C / 4] = a1;
        }
        *(volatile int *)p |= 0x200;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
    return ret;
}

int func_002592C8(int a0, int a1) {
    int ret = -1;
    if ((unsigned int)(a0 - 1) < 0x7F && a1 >= 0) {
        if (a1 < 0x80) {
            int *p = (int *)func_00255008(a0);
            if (p[2] != 0) {
                ret = func_00255038(a0) & 0x7F;
                func_00255020(a0, a1 | 0x80);
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259350);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002593F8);

extern void *func_00254FE0(int a0);
extern void *func_00254FF8(void);

void func_00259668(unsigned int a0, int a1) {
    if (a0 < 0x30 && a1 >= 0 && a1 < 0x3C0) {
        int *p = (int *)func_00254FE0(a0);
        void *q = func_00254FF8();
        *(short *)((char *)p + 0x1E) = a1;
        *(volatile int *)p |= 0x2000;
        *(int *)((char *)p + 0x10) =
            ((((int)*(unsigned short *)((char *)p + 0x20)
               * *(unsigned short *)((char *)p + 0x1E)) << 12)
             / *(unsigned short *)((char *)q + 0x3A)) / 0x3C;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
}

int func_00259710(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        void *r = func_00254FE0(a0);
        ret = *(unsigned short *)((char *)r + 0x1E);
    }
    return ret;
}

int func_00259740(int a0) {
    volatile int *p;
    int ret = -1;
    if ((unsigned int)a0 < 0x30) {
        p = (volatile int *)func_00254FE0(a0);
        p[0] |= 0x2000;
        if (p[0] & 1) {
            ret = (p[0] >> 1) & 1;
            if (p[0] & 0x20) {
                ret |= 2;
            }
        }
        p[0] &= 0xFFFFDFFF;
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002597C8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259878);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00259958);

typedef struct { char _0[0x50]; unsigned char f50; unsigned char f51; char _52[6]; } P16Ent;

void func_00259B80(int a0) {
    unsigned int idx = a0 & 0x7FFF;
    if (idx < 0x30) {
        volatile int *p17 = func_00254FE0(idx);
        *p17 |= 0x2000;
        if (*p17 & 0x4) {
            int mask8000 = a0 & 0x8000;
            P16Ent *p16 = func_00254FC8(0);
            char *p19 = func_00254FF8();
            int i;
            *p17 &= 0xFFFFFF77;
            *p17 |= 0x40;
            for (i = 0; i < 0x30; i++, p16++) {
                if (p16->f51 != 2) continue;
                if (p16->f50 != idx) continue;
                if (mask8000) {
                    func_00255580(2, i, 0, 0);
                }
                *(long long *) (p19 + 0x28) |= 1LL << i;
            }
        }
        *p17 &= 0xFFFFDFFF;
    }
}


extern void *func_00254FE0(int a0);
extern void func_00259B80(int a0);

void func_00259CB0(int a0) {
    int i;
    volatile int *p = (volatile int *)func_00254FE0(0);
    for (i = 0; i < 0x30; i++) {
        p[0] |= 0x2000;
        if ((p[0] & 5) == 4) {
            func_00259B80(i | (a0 << 15));
        }
        p[0] &= 0xFFFFDFFF;
        p = (volatile int *)((char *)p + 0x54);
    }
}

extern void *func_00254FE0(int a0);

void func_00259D58(unsigned int a0, int a1, int a2) {
    if (a0 < 0x30 &&
        a1 >= -0x1000 && a1 < 0x1001 &&
        a2 >= -0x1000 && a2 < 0x1001) {
        int *p = (int *)func_00254FE0(a0);
        p[0x44 / 4] = a1;
        p[0x48 / 4] = a2;
        *(volatile int *)p |= 0x2000;
        *(volatile int *)p |= 0x800;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
}

void func_00259DF8(unsigned int a0, int a1) {
    volatile int *p;
    int v, v2, v3;
    if (a0 >= 0x30) return;
    if (a1 < 0) return;
    if (a1 >= 0x4000) return;
    p = (volatile int *)func_00254FE0(a0);
    v = p[0];
    *(int *)((char *)p + 0x40) = a1;
    v |= 0x2000;
    p[0] = v;
    v2 = p[0];
    v2 |= 0x400;
    p[0] = v2;
    v3 = p[0];
    v3 = (int)((unsigned int)v3 & 0xFFFFDFFFU);
    p[0] = v3;
}

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

extern int func_00255070(void);

int func_0025A340(int a0) {
    int ret = 0;
    if ((unsigned int)a0 < 0x30) {
        int base = func_00255070();
        ret = *(int *)(base + (a0 % 0x18) * 4 + (a0 / 0x18) * 0x60 + 0xC0);
    }
    return ret;
}

void func_0025A3B0(void) {
    func_00255580(0x46, 0, 0, 0);
}

void func_0025A3C8(void) {
    func_00255580(0x47, 0, 0, 0);
}

int func_0025A3E0(int *a0) {
    unsigned int n1, n2;
    int v, v2, ret;
    ret = -1;
    n1 = a0[2];
    if ((unsigned int)0x1FFFFF < n1) goto done;
    n2 = a0[3];
    if ((unsigned int)0x1FFFFF < n2) goto done;
    v = a0[0];
    if (v < 0) goto done;
    if (v < 0x10) {
        v2 = a0[1];
        func_00255580(0x48, (v << 24) | v2, n1, n2);
        ret = 0;
    }
    done:
    return ret;
}

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

extern void func_00255580(int a0, int a1, int a2, int a3);

int func_0025A610(int a0, long a1, int a2) {
    int ret;
    ret = -1;
    if ((unsigned int)a0 < 2 && (unsigned int)a2 <= 0x1FFFFF && (a1 & 0xFF000000) == 0) {
        func_00255580(0x4F, a1, a2, a0);
        ret = 0;
    }
    return ret;
}

#include "math_private.h"

extern float func_0025C898(float x, float y, int iy);
extern float func_0025BDF0(float x, float y);
extern int func_0025B8D8(float x, float *y);

float func_0025A678(float x) {
    float y[2];
    int n;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;

    if (ix <= 0x3f490fd8) {
        return func_0025C898(x, 0.0f, 0);
    } else if (ix >= 0x7f800000) {
        return x - x;
    } else {
        n = func_0025B8D8(x, y);
        switch (n & 3) {
        case 0:
            return func_0025C898(y[0], y[1], 1);
        case 1:
            return func_0025BDF0(y[0], y[1]);
        case 2:
            return -func_0025C898(y[0], y[1], 1);
        default:
            return -func_0025BDF0(y[0], y[1]);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A768);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A868);

extern float func_0025B3A0(float, float);
extern int func_0025CD78(float);
extern int func_0025C9A0(void *);
extern int func_00260340(float);
extern int D_00629490[];
extern int D_00629998[];

typedef struct {
    int f0;
    void *f4;
    long long f8;
    long long f10;
    long long f18;
    int f20;
} S0025A968;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A968);


/* m2c scaffold from asm/aug6/nonmatchings/common/src/PObj/func_0025AA90.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern int D_00629998[];

float func_0025AA90(float a, float b) {
    extern float func_0025B688(float a0, float a1);
    extern float func_0025F748(long a0);
    extern int D_00629498[];
    extern long D_006294A0[];
    struct {
        int f0;
        void *f4;
        long f8;
        long f10;
        long f18;
        int f20;
    } buf;
    float f22;
    int s0;

    f22 = func_0025B688(a, b);
    s0 = D_00629998[0];
    if (s0 == -1) {
        goto early;
    }
    if (func_0025CD78(b)) {
        goto early;
    }
    if (func_0025CD78(a)) {
        goto early;
    }
    if (b != 0.0f) {
        goto early;
    }
    buf.f0 = 1;
    buf.f4 = D_00629498;
    buf.f20 = 0;
    buf.f8 = func_00260340(a);
    buf.f10 = func_00260340(b);
    if (s0 == 0) {
        buf.f18 = func_00260340(a);
    } else {
        buf.f18 = D_006294A0[0];
    }
    if (D_00629998[0] == 2 || func_0025C9A0(&buf) == 0) {
        *(int *)func_002603E0() = 0x21;
    }
    if (buf.f20 != 0) {
        *(int *)func_002603E0() = buf.f20;
    }
    return func_0025F748(buf.f18);
early:
    return f22;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025ABD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B000);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B3A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B688);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025B8D8);

float func_0025BCB8(float x) {
    int ix, s, q, m, t, i;
    unsigned int r;
    float z;

    GET_FLOAT_WORD(ix, x);
    if ((ix & 0x7F800000) == 0x7F800000) {
        return x * x + x;
    }
    m = ix >> 23;
    if (ix <= 0) {
        if ((ix & 0x7FFFFFFF) == 0) {
            return x;
        }
        if (ix < 0) {
            return (x - x) / (x - x);
        }
    }
    if (m == 0) {
        for (i = 0; (ix & 0x800000) == 0; i++) {
            ix <<= 1;
        }
        m -= i - 1;
    }
    m -= 0x7F;
    ix = (ix & 0x7FFFFF) | 0x800000;
    ix <<= (m & 1);
    m >>= 1;
    ix <<= 1;
    q = s = 0;
    r = 0x1000000;
    do {
        t = s + r;
        if (t <= ix) {
            s = t + r;
            ix -= t;
            q += r;
        }
        r >>= 1;
        ix <<= 1;
    } while (r != 0);
    if (ix != 0) {
        q += q & 1;
    }
    ix = (q >> 1) + 0x3F000000;
    ix += m << 23;
    SET_FLOAT_WORD(z, ix);
    return z;
}


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

extern void *func_0025EC78(void *a, void *b, void *c);
extern long long func_0025EAA8(void *s);

void func_0025EEB8(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    func_0025EBD8(&a0, &x);
    func_0025EBD8(&a1, &y);
    func_0025EAA8(func_0025EC78(&x, &y, &z));
}

void func_0025EF10(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    func_0025EBD8(&a0, &x);
    func_0025EBD8(&a1, &y);
    y.b ^= 1;
    func_0025EAA8(func_0025EC78(&x, &y, &z));
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025EF78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F220);

typedef struct { unsigned int type; int f4; int f8; int fC; unsigned long long f10; } PCmpV2;

int func_0025F388(PCmpV2 *a, PCmpV2 *b) {
    unsigned int at = a->type;
    unsigned int bt;
    if (at < 2) {
        return 1;
    }
    bt = b->type;
    if (bt < 2) {
        return 1;
    }
    if ((at ^ 4) == 0) {
        if ((bt ^ 4) == 0) {
            return b->f4 - a->f4;
        }
        return a->f4 ? -1 : 1;
    }
    if ((bt ^ 4) == 0) {
        if (b->f4 == 0) {
            return -1;
        }
        return 1;
    }
    if ((at ^ 2) == 0) {
        if ((bt ^ 2) == 0) {
            return 0;
        }
        if (b->f4 != 0) {
            return 1;
        }
        return -1;
    }
    if ((bt ^ 2) == 0) {
        return a->f4 ? -1 : 1;
    }
    {
        int af4 = a->f4;
        int bf4 = b->f4;
        if (af4 != bf4) {
            return af4 ? -1 : 1;
        }
        {
            int af8 = a->f8;
            int bf8 = b->f8;
            if (bf8 < af8) {
                return af4 ? -1 : 1;
            }
            if (af8 < bf8) {
                return af4 ? 1 : -1;
            }
            {
                unsigned long long af10 = a->f10;
                unsigned long long bf10 = b->f10;
                if (bf10 < af10) {
                    return af4 ? -1 : 1;
                }
                if (af10 < bf10) {
                    return af4 ? 1 : -1;
                }
                return 0;
            }
        }
    }
}


extern void func_0025EBD8(void *in, void *out);
extern int func_0025F388(PCmpV2 *a, PCmpV2 *b);

void func_0025F4A0(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y;
    func_0025EBD8(&a0, &x);
    func_0025EBD8(&a1, &y);
    func_0025F388(&x, &y);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F4F0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F5A8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F640);

extern void func_0025EBD8(void *in, void *out);
extern long long func_0025EAA8(void *s);

void func_0025F6E0(long long a0) {
    struct { int a, b, c, pad; long long d; } s;
    long long t = a0;
    func_0025EBD8(&t, &s);
    s.b = (s.b == 0);
    func_0025EAA8(&s);
}

extern long long func_0025EAA8(void *s);

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

int func_0025FB78(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    func_0025F8B0(buf + 0x30, buf);
    func_0025F8B0(buf + 0x34, buf + 0x10);
    ret = func_0025F940(buf, buf + 0x10, buf + 0x20);
    return func_0025F7A0(ret);
}

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

typedef struct { unsigned int type; int f4; int f8; int fC; } PCmpV;

int func_0025FF90(PCmpV *a, PCmpV *b) {
    unsigned int at = a->type;
    unsigned int bt;
    if (at < 2) {
        return 1;
    }
    bt = b->type;
    if (bt < 2) {
        return 1;
    }
    if ((at ^ 4) == 0) {
        if ((bt ^ 4) == 0) {
            return b->f4 - a->f4;
        }
        return a->f4 ? -1 : 1;
    }
    if ((bt ^ 4) == 0) {
        if (b->f4 == 0) {
            return -1;
        }
        return 1;
    }
    if ((at ^ 2) == 0) {
        if ((bt ^ 2) == 0) {
            return 0;
        }
        if (b->f4 != 0) {
            return 1;
        }
        return -1;
    }
    if ((bt ^ 2) == 0) {
        return a->f4 ? -1 : 1;
    }
    {
        int af4 = a->f4;
        int bf4 = b->f4;
        if (af4 != bf4) {
            return af4 ? -1 : 1;
        }
        {
            int af8 = a->f8;
            int bf8 = b->f8;
            if (bf8 < af8) {
                return af4 ? -1 : 1;
            }
            if (af8 < bf8) {
                return af4 ? 1 : -1;
            }
            {
                unsigned int afC = a->fC;
                unsigned int bfC = b->fC;
                if (bfC < afC) {
                    return af4 ? -1 : 1;
                }
                if (afC < bfC) {
                    return af4 ? 1 : -1;
                }
                return 0;
            }
        }
    }
}


extern void func_0025F8B0(void *in, void *out);
extern int func_0025FF90(PCmpV *a, PCmpV *b);

int func_002600A8(float a0, float a1) {
    char buf[0x30];
    *(float *)(buf + 0x20) = a0;
    *(float *)(buf + 0x24) = a1;
    func_0025F8B0(buf + 0x20, buf);
    func_0025F8B0(buf + 0x24, buf + 0x10);
    return func_0025FF90(buf, buf + 0x10);
}

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

void func_00260668(void *a0, ...) {
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    int s = D_0054D504[0];
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    func_00262D00(*(int *)(s + 8), a0, args);
}

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

void func_00261188(void *a0, int a1, ...) {
    char buf[0x60];
    char *va = (char *)__builtin_next_arg(a1) - 48;
    *(int *)(buf + 0x0) = (int)a0;
    *(int *)(buf + 0x8) = 0x7FFFFFFF;
    *(short *)(buf + 0xC) = 0x208;
    *(int *)(buf + 0x10) = (int)a0;
    *(int *)(buf + 0x14) = 0x7FFFFFFF;
    *(int *)(buf + 0x54) = D_0054D504[0];
    func_00262D00(buf, a1, va);
    *(char *)(*(int *)(buf + 0x0)) = 0;
}

int func_002611F8(void) {
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261200);

/* func_00261288: hand-vectorized string-end finder — a 128-bit MMI zero-byte
 * scan (lq/pcpyld/psubb/pnor/pand/pcpyud haszero) for 16-aligned input, a 64-bit
 * (ld/dsubu/nor/and) scan for 8-aligned, and a trailing byte scan, then
 * func_002614F8(end, a1) and returns the original pointer. In-file handwritten
 * asm per maintainer exception: the MMI byte-parallel ops have no C/intrinsic
 * form and ee-gcc spills vector_size types — matched MMI siblings in this TU
 * (e.g. func_0023E168) use the same whole-function asm pattern. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_00261288\n"
    "    .type func_00261288, @function\n"
    "    .align 3\n"
    "func_00261288:\n"
    "    addiu  $29, $29, -0x20\n"
    "    sq     $16, 0x0($29)\n"
    "    daddu  $16, $4, $0\n"
    "    andi   $2, $16, 0x7\n"
    "    bnez   $2, .L0026137C\n"
    "    sq     $31, 0x10($29)\n"
    "    andi   $2, $16, 0xF\n"
    "    lui    $3, 0x101\n"
    "    ori    $3, $3, 0x101\n"
    "    dsll   $3, $3, 16\n"
    "    ori    $3, $3, 0x101\n"
    "    dsll   $3, $3, 16\n"
    "    ori    $3, $3, 0x101\n"
    "    lui    $4, 0x8080\n"
    "    ori    $4, $4, 0x8080\n"
    "    dsll   $4, $4, 16\n"
    "    ori    $4, $4, 0x8080\n"
    "    dsll   $4, $4, 16\n"
    "    ori    $4, $4, 0x8080\n"
    "    bnez   $2, .L00261338\n"
    "    ld     $6, 0x0($16)\n"
    "    lq     $2, 0x0($16)\n"
    "    pcpyld $7, $3, $3\n"
    "    pcpyld $8, $4, $4\n"
    "    psubb  $3, $2, $7\n"
    "    pnor   $2, $0, $2\n"
    "    pand   $3, $3, $2\n"
    "    pand   $3, $3, $8\n"
    "    pcpyud $2, $3, $3\n"
    "    or     $3, $2, $3\n"
    "    bnez   $3, .L0026137C\n"
    "    daddu  $4, $16, $0\n"
    "    addiu  $6, $4, 0x10\n"
    "    .align 2\n"
    ".L0026130C:\n"
    "    lq     $2, 0x0($6)\n"
    "    pnor   $3, $0, $2\n"
    "    psubb  $2, $2, $7\n"
    "    pand   $2, $2, $3\n"
    "    pand   $2, $2, $8\n"
    "    pcpyud $3, $2, $2\n"
    "    or     $2, $2, $3\n"
    "    beql   $2, $0, .L0026130C\n"
    "    addiu  $6, $6, 0x10\n"
    "    b      .L0026137C\n"
    "    daddu  $4, $6, $0\n"
    "    .align 2\n"
    ".L00261338:\n"
    "    daddu  $7, $3, $0\n"
    "    daddu  $8, $4, $0\n"
    "    dsubu  $3, $6, $3\n"
    "    nor    $2, $0, $6\n"
    "    and    $3, $3, $2\n"
    "    and    $3, $3, $4\n"
    "    bnez   $3, .L0026137C\n"
    "    daddu  $4, $16, $0\n"
    "    addiu  $6, $16, 0x8\n"
    "    .align 2\n"
    ".L0026135C:\n"
    "    ld     $2, 0x0($6)\n"
    "    nor    $3, $0, $2\n"
    "    dsubu  $2, $2, $7\n"
    "    and    $2, $2, $3\n"
    "    and    $2, $2, $8\n"
    "    beql   $2, $0, .L0026135C\n"
    "    addiu  $6, $6, 0x8\n"
    "    daddu  $4, $6, $0\n"
    "    .align 2\n"
    ".L0026137C:\n"
    "    lb     $2, 0x0($4)\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    nop\n"
    "    bnel   $2, $0, .L0026137C\n"
    "    addiu  $4, $4, 0x1\n"
    "    jal    func_002614F8\n"
    "    nop\n"
    "    daddu  $2, $16, $0\n"
    "    lq     $31, 0x10($29)\n"
    "    lq     $16, 0x0($29)\n"
    "    jr     $31\n"
    "    addiu  $29, $29, 0x20\n"
    "    .size func_00261288, . - func_00261288\n"
    "    .set reorder\n"
    "    .set at\n"
);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002613B4);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002614F8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0026160C);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261748);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261900);

char *func_00261AC0(char *s, char c) {
    char *last = 0;
    while (*s != 0) {
        if (*s == c) {
            last = s;
        }
        s++;
    }
    return (*s == c) ? s : last;
}

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

int func_00261EB8(int a0, int *a1) {
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = func_00266FD0(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261F00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00261FB8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262030);

int func_00262C00(int a0, int *a1) {
    int ret;
    if (a1[2] == 0) {
        a1[1] = 0;
        return 0;
    }
    ret = func_00266FD0(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264290);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264440);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00264520);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00265028);

extern int D_0054D504[];

void func_00265130(void *out, void *a1, void *a2) {
    char s[0x60];
    *(void **)(s + 0x0) = out;
    *(int *)(s + 0x8) = 0x7FFFFFFF;
    *(short *)(s + 0xC) = 0x208;
    *(void **)(s + 0x10) = out;
    *(int *)(s + 0x14) = 0x7FFFFFFF;
    *(int *)(s + 0x54) = D_0054D504[0];
    func_00262D00(s, a1, a2);
    *(char *)(*(void **)(s + 0x0)) = 0;
}

typedef struct { char pad38[0x38]; int field_38; } P54;

typedef struct {
    int field_0;
    int field_4;
    int field_8;
    unsigned short field_C;
    unsigned short field_E;
    int field_10;
    int field_14;
    int field_18;
    int pad_1C[5];
    void *field_30;
    int pad_34[3];
    int field_40[5];
    P54 *field_54;
} PObj265;

extern int D_0054D504[];
extern void func_00266990(char *a0);
extern void func_00266B40(P54 *p);
extern void func_00267530(PObj265 *s);

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

extern int func_002698E8();
extern long func_00269950(void *a0, int a1, int a2);
extern void func_002699D0(void);
extern int func_00269A38(void *a0);

void func_002667C8(char *a0, short a1, short a2, int a3) {
    *(int *)(a0 + 0x54) = a3;
    *(short *)(a0 + 0xC) = a1;
    *(short *)(a0 + 0xE) = a2;
    *(void **)(a0 + 0x20) = (void *)func_002698E8;
    *(void **)(a0 + 0x24) = (void *)func_00269950;
    *(void **)(a0 + 0x28) = (void *)func_002699D0;
    *(void **)(a0 + 0x2C) = (void *)func_00269A38;
    *(int *)(a0 + 0x4) = 0;
    *(int *)(a0 + 0x8) = 0;
    *(int *)(a0 + 0x10) = 0;
    *(int *)(a0 + 0x18) = 0;
    *(char **)(a0 + 0x1C) = a0;
    *(int *)(a0 + 0x0) = 0;
}

extern void *func_002678D8(void *a0, int a1);

void *func_00266820(void *a0, int a1) {
    int sz;
    char *p;
    char *body;
    sz = a1 * 0x58;
    p = (char *)func_002678D8(a0, sz + 0xC);
    if (p == 0) {
        return 0;
    }
    body = p + 0xC;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x8) = (int)body;
    func_00260568(body, 0, sz);
    return p;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266890);

extern int func_002666C0(void);
extern void func_002673A8(int a0, void *a1);

void func_00266970(int a0) {
    func_002673A8(a0, func_002666C0);
}

void func_00266980(void) {
    func_00266970(D_0054D504[0]);
}

extern void func_00266970(int a0);

void func_00266990(char *a0) {
    char *p = a0 + 0x1E4;
    *(void **)(a0 + 0x3C) = (void *)func_00266970;
    *(int *)(a0 + 0x38) = 1;
    func_002667C8(p, 4, 0, (int)a0);
    func_002667C8(a0 + 0x23C, 9, 1, (int)a0);
    func_002667C8(a0 + 0x294, 0xA, 2, (int)a0);
    *(char **)(a0 + 0x1E0) = p;
    *(int *)(a0 + 0x1DC) = 3;
    *(int *)(a0 + 0x1D8) = 0;
}

typedef struct {
    char *pos;   /* 0x0 */
    int len;     /* 0x4 */
} StreamBuf;

extern int func_002604B8(char *dst, char *src, int n);
extern int func_002692C0(StreamBuf *s);

int func_00266A20(char *dst, int size, int count, StreamBuf *s) {
    unsigned int total = count * size;
    int len;
    unsigned int avail;
    unsigned int total_orig;
    char *p;

    if (total == 0) {
        return 0;
    }
    len = s->len;
    if (len < 0) {
        s->len = 0;
        len = 0;
    }
    avail = len;
    total_orig = total;
    p = dst;
    if (avail < total) {
        do {
            func_002604B8(p, s->pos, avail);
            total -= avail;
            p += avail;
            s->pos += avail;
            if (func_002692C0(s) != 0) {
                return (total_orig - total) / size;
            }
            avail = s->len;
        } while (avail < total);
    }
    func_002604B8(p, s->pos, total);
    s->len -= total;
    s->pos += total;
    return count;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266B40);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266E60);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00266FD0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002673A8);

extern int D_0062A858[];
extern int D_0062A848[];

int func_00267440(void *a0, int a1, int a2) {
    if (a2 == 0) goto no_check;
    if (func_002613B4(a2, D_0062A858) == 0) goto found;
    if (func_002613B4(a2, D_0062A848) != 0) return 0;
found:
    *(int *)((char *)a0 + 0x30) = a1;
    *(int *)((char *)a0 + 0x34) = a2;
no_check:
    return (int)D_0062A858;
}

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

extern int func_0026AFF8(int *self, int a1, int a2);

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

extern int *func_00268358(void *a0, int *a1, int a2, int a3);
extern int *func_00268280(void *a0, int a1);

int func_00268470(void *a0, char *a1, int a2, int a3, int a4)
{
    int n3 = (a3 + 8) / 9;
    int p = 1;
    int five = 0;
    int i18;
    int *r5;
    int i17;

    if (p < n3) {
        do {
            p <<= 1;
            five++;
        } while (p < n3);
    }
    i18 = a2 < 10;
    r5 = func_00268280(a0, five);
    i17 = 9;
    r5[5] = a4;
    r5[4] = 1;
    if (i18 == 0) {
        a1 += 9;
        do {
            i17++;
            r5 = func_00268358(a0, r5, 10, a1[0] - 0x30);
            a1++;
        } while (i17 < a2);
        a1++;
    } else {
        a1 += 10;
    }
    if (i17 < a3) {
        i17 = a3 - i17;
        do {
            r5 = func_00268358(a0, r5, 10, a1[0] - 0x30);
            a1++;
            i17--;
        } while (i17 != 0);
    }
    return (int)r5;
}


int func_002685B8(unsigned int a0) {
    int n = 0;
    if ((a0 & 0xFFFF0000) == 0) { n = 16; a0 <<= 16; }
    if ((a0 & 0xFF000000) == 0) { n += 8; a0 <<= 8; }
    if ((a0 & 0xF0000000) == 0) { n += 4; a0 <<= 4; }
    if ((a0 & 0xC0000000) == 0) { n += 2; a0 <<= 2; }
    if ((int)a0 >= 0) {
        n += 1;
        if ((a0 & 0x40000000) == 0) {
            return 0x20;
        }
    }
    return n;
}

int func_00268640(int *p) {
    unsigned int v = *p;
    int n;
    if (v & 7) {
        if (v & 1) {
            return 0;
        }
        if (v & 2) {
            *p = v >> 1;
            return 1;
        }
        *p = v >> 2;
        return 2;
    }
    n = 0;
    if ((v & 0xFFFF) == 0) {
        n = 0x10;
        v >>= 16;
    }
    if ((v & 0xFF) == 0) {
        n += 8;
        v >>= 8;
    }
    if ((v & 0xF) == 0) {
        n += 4;
        v >>= 4;
    }
    if ((v & 3) == 0) {
        n += 2;
        v >>= 2;
    }
    if (v & 1) {
        *p = v;
    } else {
        v >>= 1;
        n += 1;
        if (v == 0) {
            return 0x20;
        }
        *p = v;
    }
    return n;
}

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

extern long func_0025EF78(long a, long b);
extern long D_0062A870[];

long func_00269230(int n) {
    long acc = (long)0xFFC0 << 46;
    if (n < 0x18) {
        return D_0062A870[n];
    }
    while (n > 0) {
        acc = func_0025EF78(acc, (long)0x8048 << 47);
        n--;
    }
    return acc;
}

int func_002692A0(void) {
    return func_002666C0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002692C0);

int func_00269438(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int)(((unsigned int)(hx | (-hx))) >> 31);
}

int func_00269480(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    do { return ((unsigned int)hx) >> 31; } while (0);
}

extern int D_0062E170[];
extern unsigned int func_00241AC8(int a0);

int func_002694B8(int *self, int a1)
{
    unsigned int ret;
    D_0062E170[0] = 0;
    ret = func_00241AC8(a1);
    if (ret == 0xFFFFFFFF) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269518);

extern void *func_00269518(int a0);

unsigned int func_00269588(void *a0, int a1, int a2) {
    unsigned int *base;
    unsigned int old;
    if ((unsigned int)a1 >= 0x20) {
        *(int *)a0 = 0x16;
        return 0xFFFFFFFFU;
    }
    if (*(int *)((char *)a0 + 0x1D4) == 0) {
        if (func_00269518((int)a0) != 0) {
            return 0xFFFFFFFFU;
        }
    }
    base = *(unsigned int **)((char *)a0 + 0x1D4);
    old = base[a1];
    base[a1] = a2;
    return old;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269618);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00269708);

extern int func_00269618(int a0, int a1);

int func_002697C0(int a0) {
    return func_00269618(D_0054D504[0], a0);
}

extern unsigned int func_00269588(void *a0, int a1, int a2);

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

long func_00269950(void *a0, int a1, int a2) {
    unsigned short flag = *(unsigned short *)((char *)a0 + 0xC);
    if (flag & 0x100) {
        func_0026B058((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), 0, 2);
    }
    flag = *(unsigned short *)((char *)a0 + 0xC) & 0xEFFF;
    *(unsigned short *)((char *)a0 + 0xC) = flag;
    {
        unsigned long r = (unsigned long)func_0026AE80((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE), a1, a2);
        return (int)r;
    }
}

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

/* func_0026B688: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0026B688\n"
    ".type func_0026B688, @function\n"
    "    .align 3\n"
    "func_0026B688:\n"
    "    lui $7, (0xFFFFF000 >> 16)\n"
    "    daddu $6, $0, $0\n"
    "    ori $7, $7, (0xFFFFF000 & 0xFFFF)\n"
    "    nop\n"
    ".L0026B698:\n"
    "    sync\n"
    "    cache 0x10, 0x0($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B6D4\n"
    "    nop\n"
    "    bnez $3, .L0026B6D4\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x14, 0x0($6)\n"
    "    sync\n"
    ".L0026B6D4:\n"
    "    sync\n"
    "    cache 0x10, 0x1($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B710\n"
    "    nop\n"
    "    bnez $3, .L0026B710\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x14, 0x1($6)\n"
    "    sync\n"
    ".L0026B710:\n"
    "    sync\n"
    "    addiu $6, $6, 0x40\n"
    "    slti $2, $6, 0x1000\n"
    "    bnez $2, .L0026B698\n"
    "    nop\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_0026B688, . - func_0026B688\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_0026B730: handwritten critical-section wrapper — reads CP0 Status ($12),
 * and if interrupts are enabled (bit 16) brackets the func_0026B688 call with
 * func_00101A40 (disable) / func_00101A88 (enable, tail). Handwritten per
 * maintainer exception (inline privileged mfc0). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0026B730\n"
    "    .type func_0026B730, @function\n"
    "    .align 3\n"
    "func_0026B730:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd    $18, 0x20($29)\n"
    "    sd    $17, 0x10($29)\n"
    "    daddu $18, $4, $0\n"
    "    sd    $31, 0x30($29)\n"
    "    daddu $17, $5, $0\n"
    "    sd    $16, 0x0($29)\n"
    "    mfc0  $16, $12\n"
    "    lui   $2, 0x1\n"
    "    and   $16, $16, $2\n"
    "    beqz  $16, 1f\n"
    "    nop\n"
    "    jal   func_00101A40\n"
    "    nop\n"
    "1:\n"
    "    lui   $4, 0xFFFF\n"
    "    ori   $4, $4, 0xFFC0\n"
    "    and   $5, $17, $4\n"
    "    jal   func_0026B688\n"
    "    and   $4, $18, $4\n"
    "    beqz  $16, 2f\n"
    "    ld    $31, 0x30($29)\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    j     func_00101A88\n"
    "    addiu $29, $29, 0x40\n"
    "2:\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    jr    $31\n"
    "    addiu $29, $29, 0x40\n"
    "    .size func_0026B730, . - func_0026B730\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern void func_0026B688(int a0, int a1);

void func_0026B7B0(int a0, int a1) {
    func_0026B688(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

/* func_0026B7C8: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global func_0026B7C8\n"
    ".type func_0026B7C8, @function\n"
    "    .align 3\n"
    "func_0026B7C8:\n"
    "    lui $7, (0xFFFFF000 >> 16)\n"
    "    daddu $6, $0, $0\n"
    "    ori $7, $7, (0xFFFFF000 & 0xFFFF)\n"
    "    nop\n"
    ".L0026B7D8:\n"
    "    sync\n"
    "    cache 0x10, 0x0($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B814\n"
    "    nop\n"
    "    bnez $3, .L0026B814\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x16, 0x0($6)\n"
    "    sync\n"
    ".L0026B814:\n"
    "    sync\n"
    "    cache 0x10, 0x1($6)\n"
    "    sync\n"
    "    mfc0 $2, $28\n"
    "    and $2, $2, $7\n"
    "    addu $2, $2, $6\n"
    "    sltu $3, $5, $2\n"
    "    sltu $2, $2, $4\n"
    "    bnez $2, .L0026B850\n"
    "    nop\n"
    "    bnez $3, .L0026B850\n"
    "    nop\n"
    "    sync\n"
    "    cache 0x16, 0x1($6)\n"
    "    sync\n"
    ".L0026B850:\n"
    "    sync\n"
    "    addiu $6, $6, 0x40\n"
    "    slti $2, $6, 0x1000\n"
    "    bnez $2, .L0026B7D8\n"
    "    nop\n"
    "    jr $31\n"
    "    nop\n"
    "    nop\n"
    ".size func_0026B7C8, . - func_0026B7C8\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_0026B870: handwritten critical-section wrapper — reads CP0 Status ($12),
 * and if interrupts are enabled (bit 16) brackets the func_0026B7C8 call with
 * func_00101A40 (disable) / func_00101A88 (enable, tail). Handwritten per
 * maintainer exception (inline privileged mfc0). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global func_0026B870\n"
    "    .type func_0026B870, @function\n"
    "    .align 3\n"
    "func_0026B870:\n"
    "    addiu $29, $29, -0x40\n"
    "    sd    $18, 0x20($29)\n"
    "    sd    $17, 0x10($29)\n"
    "    daddu $18, $4, $0\n"
    "    sd    $31, 0x30($29)\n"
    "    daddu $17, $5, $0\n"
    "    sd    $16, 0x0($29)\n"
    "    mfc0  $16, $12\n"
    "    lui   $2, 0x1\n"
    "    and   $16, $16, $2\n"
    "    beqz  $16, 1f\n"
    "    nop\n"
    "    jal   func_00101A40\n"
    "    nop\n"
    "1:\n"
    "    lui   $4, 0xFFFF\n"
    "    ori   $4, $4, 0xFFC0\n"
    "    and   $5, $17, $4\n"
    "    jal   func_0026B7C8\n"
    "    and   $4, $18, $4\n"
    "    beqz  $16, 2f\n"
    "    ld    $31, 0x30($29)\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    j     func_00101A88\n"
    "    addiu $29, $29, 0x40\n"
    "2:\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    jr    $31\n"
    "    addiu $29, $29, 0x40\n"
    "    .size func_0026B870, . - func_0026B870\n"
    "    .set reorder\n"
    "    .set at\n"
);

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
