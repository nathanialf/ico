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

int GetGObjId(int a0) {
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
extern void debug_StdPrintfDummy();
extern char D_0062DD28[];

void PrintGObjID(int a0) {
    int i;
    for (i = 0; i < D_0062BEA0; i++) {
        if (a0 == D_0070C340[i]) {
            debug_StdPrintfDummy(D_0062DD28, i);
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
extern void debug_StdPrintfDummy(void *a0);
void FreePObj(void) {
    do {
        debug_StdPrintfDummy(D_006281F8);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", DrawVObj);

extern void *func_00105078(void);
extern void func_001050A8(int a0);

void SetVObjRT(int a0, void *a1) {
    sceVu0UnitMatrix(func_00105078());
    *(float *)((char *)a1 + 0xC) = 1.0f;
    func_001050A8((int)a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsResetGraph);

extern int D_0054A960[];

void *func_0023E158(void) {
    return D_0054A960;
}

/* sceGsResetPath: handwritten VIF/VU0 init — MMIO register pokes, a cfc2/ctc2
 * read-modify-write of VU0 control reg $vi28, sync barriers, and two qword
 * FIFO copies from D_0054A970. In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global sceGsResetPath\n"
    "    .type sceGsResetPath, @function\n"
    "    .align 3\n"
    "sceGsResetPath:\n"
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
    "    .size sceGsResetPath, . - sceGsResetPath\n"
    "    .set reorder\n"
    "    .set at\n"
);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0023E1D0);

extern void *func_0023E158(void);

void sceGsPutDispEnv(void *a0) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefDrawEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsPutDrawEnv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefDBuff);

int sceGsSwapDBuff(void *a0, int a1) {
    int s0 = a1 & 1;
    int ret;
    sceGsPutDispEnv((char *)a0 + s0 * 0x28);
    if (!s0) goto zero_path;
    ret = sceGsPutDrawEnv((char *)a0 + 0x140);
    goto done;
zero_path:
    ret = sceGsPutDrawEnv((char *)a0 + 0x50);
done:
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSyncV);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSyncPath);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefTexEnv);

int sceGsSetDefAlphaEnv(long long *a0, int a1) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefLoadImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefStoreImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsExecLoadImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsExecStoreImage);

extern int GsGetIMR(void);
extern void GsPutIMR(void *a0);

int sceGsPutIMR(void *a0) {
    int r = GsGetIMR();
    GsPutIMR(a0);
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetHalfOffset);

void func_0023FBE8(void) {
    do {
        GsGetIMR();
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGszbufaddr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGsSetDefClear);

void sceVu0ApplyMatrix(void *a0, void *a1, void *a2) {
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

void sceVu0OuterProduct(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP_ACC(vopmula.xyz, 4, 5);
    VU0_V3OP(vopmsub.xyz, 6, 5, 4);
    VU0_V3OP(vsub.w, 6, 6, 6);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

float sceVu0InnerProduct(void *a0, void *a1) {
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

void sceVu0Normalize(void *a0, void *a1) {
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

void sceVu0TransposeMatrix(void *a0, void *a1) {
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

/* sceVu0InversMatrix: handwritten VU0/MMI matrix transpose + transform — packs three
 * qwords via pextlw/pextuw/pcpyld/pcpyud into VU regs, runs a vmulax/vmadda/
 * vmaddz chain, and subtracts. In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .align 3\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global sceVu0InversMatrix\n"
    "    .type sceVu0InversMatrix, @function\n"
    "sceVu0InversMatrix:\n"
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
    "    .size sceVu0InversMatrix, . - sceVu0InversMatrix\n"
    "    .set reorder\n"
    "    .set at\n"
);

void sceVu0DivVector(void *a0, void *a1, float a2) {
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

void sceVu0DivVectorXYZ(void *a0, void *a1, float a2) {
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

void sceVu0InterVector(void *a0, void *a1, void *a2, float t) {
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

void sceVu0AddVector(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0SubVector(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0MulVector(void *a0, void *a1, void *a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vmul.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0ScaleVector(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyzw, 6, 4, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0TransMatrix(void *a0, void *a1, void *a2) {
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

void sceVu0CopyVector(void *a0, void *a1) {
    QCOPY16_NO_NOP("$a2");
}

void sceVu0CopyMatrix(void *a0, void *a1) {
    QCOPY64_PARALLEL_NO_NOP("$a2", "$a3", "$t0", "$t1");
}

void sceVu0FTOI4Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0FTOI0Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0ITOF4Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0ITOF0Vector(void *a0, void *a1) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0UnitMatrix(void *a0) {
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

void sceVu0RotMatrix(int a0, int a1, float *fa)
{
    func_00240198(a0, a1, fa[2]);
    func_002402E8(a0, a0, fa[1]);
    func_00240240(a0, a0, fa[0]);
}

void sceVu0ClampVector(void *a0, void *a1, float a2, float a3) {
    VU0_MFC1(8, 12);
    VU0_MFC1(9, 13);
    VU0_LSV(lqc2, 6, 0x0, 5);
    VU0_QMTC2_NI(8, 4);
    VU0_QMTC2_NI(9, 5);
    VU0_V3OP_BC(vmaxx.xyzw, 6, 6, 4, x);
    VU0_V3OP_BC(vminix.xyzw, 6, 6, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

extern void sceVu0InversMatrix(void *a0, void *a1);

void sceVu0CameraMatrix(void *a0, void *a1, void *a2, void *a3) {
    char buf[0x50];
    sceVu0UnitMatrix(buf);
    sceVu0OuterProduct(buf + 0x40, a3, a2);
    sceVu0Normalize(buf, buf + 0x40);
    sceVu0Normalize(buf + 0x20, a2);
    sceVu0OuterProduct(buf + 0x10, buf + 0x20, buf);
    sceVu0TransMatrix(buf, buf, a1);
    sceVu0InversMatrix(a0, buf);
}

void sceVu0NormalLightMatrix(void *a0, void *a1, void *a2, void *a3) {
    float buf[4];
    sceVu0ScaleVector(buf, a1, -1.0f);
    sceVu0Normalize(a0, buf);
    sceVu0ScaleVector(buf, a2, -1.0f);
    sceVu0Normalize((char *)a0 + 0x10, buf);
    sceVu0ScaleVector(buf, a3, -1.0f);
    sceVu0Normalize((char *)a0 + 0x20, buf);
    {
        float fzero = 0.0f;
        *(float *)((char *)a0 + 0x38) = fzero;
        *(float *)((char *)a0 + 0x3C) = 1.0f;
        *(float *)((char *)a0 + 0x34) = fzero;
        *(float *)((char *)a0 + 0x30) = fzero;
    }
    sceVu0TransposeMatrix(a0, a0);
}


void sceVu0LightColorMatrix(void *a0, void *a1, void *a2, void *a3, void *a4) {
    sceVu0CopyVector(a0, a1);
    sceVu0CopyVector((char *)a0 + 0x10, a2);
    sceVu0CopyVector((char *)a0 + 0x20, a3);
    sceVu0CopyVector((char *)a0 + 0x30, a4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0ViewScreenMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVu0DropShadowMatrix);

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

void sceVu0CopyVectorXYZ(void *a0, void *a1) {
    ((float *)a0)[0] = ((float *)a1)[0];
    ((float *)a0)[1] = ((float *)a1)[1];
    ((float *)a0)[2] = ((float *)a1)[2];
}

void sceVu0InterVectorXYZ(void *a0, void *a1, void *a2, float a3) {
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

void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2) {
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::: "memory");
    VU0_V3OP_BC(vmulx.xyz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

int sceVu0ClipScreen(void *a0) {
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

int sceVu0ClipScreen3(void *a0, void *a1, void *a2) {
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

void sceVpu0Reset(void) {
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

void memclr(unsigned char *a0, int a1) {
    int i;
    for (i = a1 - 1; i != -1; i--) {
        *a0++ = 0;
    }
}

extern int D_0054A9D0[];

int sceDmaGetChan(unsigned int a0) {
    if (a0 < 0xA) {
        return D_0054A9D0[a0];
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaReset);

extern int D_0054A9F8_alias[] __asm__("D_0054A9F8");

int sceDmaDebug(int a0) {
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

void *sceDmaGetEnv(void *a0) {
    *(struct S_240E40 *)a0 = D_0054AA68;
    return a0;
}

int sceDmaPutStallAddr(unsigned int a0) {
    int old = *(volatile int *)0x1000E060;
    if (a0 != 0xFFFFFFFF) {
        *(volatile int *)0x1000E060 = a0;
    }
    return old;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSend);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSendN);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSendI);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaRecv);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaRecvN);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaRecvI);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDmaWatch);

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

void sceVif1PkInit(int *a0, int a1) {
    a0[1] = a1;
    a0[0] = a1;
    a0[2] = 0;
}

int sceVif1PkReset(int *a0) {
    int v = a0[1];
    a0[2] = 0;
    a0[0] = v;
    return v;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkTerminate);

void func_00241640(int *a1, unsigned int a2) {
    int *a0;
    int s0;
    int v0;
    v0 = sceVif1PkTerminate(a1);
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
    v0 = sceVif1PkTerminate(a1);
    a0 = (int *)a1[0];
    do { s0 = a2 | 0x70000000; } while (0);
    a1[2] = v0;
    a0[0] = s0;
    a0++;
    a1[3] = 0;
    a1[0] = (int)(a0 + 1);
    a0[0] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkOpenDirectCode);

typedef struct { int *end; int pad[2]; int *cur; } Pool241748;

int sceVif1PkCloseDirectCode(Pool241748 *a0) {
    int n = (int)a0->end - 4;
    int *p = a0->cur;
    a0->cur = 0;
    n -= (int)p;
    n = (unsigned)(n >> 2) >> 2;
    *p = *p + n;
    return n;
}

typedef unsigned int u128_241778 __attribute__((mode(TI)));

void sceVif1PkOpenGifTag(void *a0, u128_241778 a1) {
    void **pp = (void **)a0;
    void *p = *pp;
    *(u128_241778 *)p = a1;
    *(void **)((char *)a0 + 0x14) = p;
    *pp = (char *)p + 0x10;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkCloseGifTag);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceVif1PkAlign);

void sceVif1PkAddGsData(int **a0, long long a1) {
    int *p = *a0;
    *p++ = (int)a1;
    *a0 = p + 1;
    *p = (int)(a1 >> 32);
}

extern int D_0054AA90[];
extern void sceTtyInit(int a0);

void func_002418E0(int a0) {
    D_0054AA90[0] = 0;
    sceTtyInit(a0);
}

void VSync(void) {
    volatile int *p = (volatile int *)0x1000F000;
    *p = 4;
    while ((*p & 4) == 0) {
    }
    *p = 4;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", VSync2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", write);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", read);

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

/* sbrk: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global sbrk\n"
    ".type sbrk, @function\n"
    "    .align 3\n"
    "sbrk:\n"
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
    "    jal EndOfHeap\n"
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
    ".size sbrk, . - sbrk\n"
    "    .set reorder\n"
    "    .set at\n"
);

int func_00241B78(void) {
    return 1;
}

int fstat(void *a0, void *a1) {
    *(long long *)((char *)a1 + 0x48) = 0;
    *(int *)((char *)a1 + 0x4) = 0x2000;
    return 0;
}

int func_00241B98(void) {
    return 1;
}

extern void Exit(void *a0);

int kill(int a0, void *a1) {
    if (a0 == 1) {
        Exit(a1);
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

void *QueueInit(int a0) {
    D_0070C680[0] = a0;
    D_0070C680[2] = (int)&D_0070C680[4];
    D_0070C680[1] = 0;
    D_0070C680[3] = (int)&D_0070C680[4];
    return (void *)D_0070C680;
}

void QueuePeekWriteDone(int *q)
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

void QueuePeekReadDone(RingBuf_241C80 *a0) {
    a0->f4--;
    a0->f8++;
    if (a0->f8 == (char *)a0 + (a0->f0 + 0x10)) {
        a0->f8 = (char *)a0 + 0x10;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceTtyHandler);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00241E58);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceTtyRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceTtyInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifInitRpc);

extern void sceSifExitCmd(void);
extern int D_0054AA98[];

void sceSifExitRpc(void) {
    sceSifExitCmd();
    D_0054AA98[0] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceRpcGetPacket);

void _sceRpcFreePacket(void *a0) {
    int *p = (int *)a0;
    p[6] = 0;
    p[4] &= 0xFFFFFFFE;
}

int _sceRpcGetFPacket(int *a0) {
    int rem = a0[9] % a0[6];
    int ret = a0[5] + rem * 64;
    a0[9] = rem + 1;
    return ret;
}

int _sceRpcGetFPacket2(int *a0, int a1) {
    if (a1 < 0) {
        goto err;
    }
    if (a1 < a0[8]) {
        goto elem;
    }
err:
    return _sceRpcGetFPacket(a0);
elem:
    return a0[7] + a1 * 64;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _request_end);

void _request_rdata(int *a0, int *a1) {
    int *ret = (int *)_sceRpcGetFPacket(a1);
    int f14 = a0[5], f1c = a0[7];
    ret[5] = f14;
    ret[7] = f1c;
    ret[8] = 0x8000000C;
    isceSifSendCmd(0x80000008, (int)ret, 0x40, a0[8], a0[9], a0[10]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifGetOtherData);

void *_search_svdata(int a0, void *a1) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _request_bind);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifBindRpc);

void _request_call(int *a0) {
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
    iWakeupThread(a6[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifCallRpc);

int sceSifCheckStatRpc(char *a0) {
    char *p = *(char **)a0;
    if (p == 0) goto ret0;
    if (*(int *)(a0 + 4) != *(int *)(p + 0x18)) goto ret0;
    if (*(int *)(p + 0x10) & 1) goto ret1;
ret0:
    return 0;
ret1:
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifSetRpcQueue);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRegisterRpc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRemoveRpc);

extern int D_0070E240[];

int sceSifRemoveRpcQueue(int *a0) {
    int *node;
    DIntr(a0);
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
    EIntr();
    return (int)node;
}

extern void DIntr(int *self);
extern void EIntr(void);

int *sceSifGetNextRequest(int *self)
{
    int *p;
    int v;
    DIntr(self);
    p = (int *)self[0xC/4];
    if (p == 0) {
        self[0x4/4] = 0;
        goto after;
    }
    v = p[0x3C/4];
    self[0x4/4] = 1;
    self[0xC/4] = v;
after:
    EIntr();
    return p;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifExecRequest);

extern void sceSifExecRequest(int);
extern void SleepThread(void);

void func_00243058(int a0)
{
    for (;;) {
        int v;
        while ((v = sceSifGetNextRequest(a0)) != 0) {
            sceSifExecRequest(v);
        }
        SleepThread();
    }
}

extern int CreateSema(int *self);
extern int D_0054AB28[];
extern int D_0054AB2C[];

void func_00243098(void) {
    int self[8];
    if (D_0054AB28[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_0054AB28[0] = CreateSema(self);
        D_0054AB2C[0] = CreateSema(self);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", new_iob);

extern char D_0070F380[];

void *func_00243180(unsigned int a0) {
    void *result;
    func_00243098();
    WaitSema(D_0054AB28[0]);
    if (a0 >= 0x20) {
        SignalSema(D_0054AB28[0]);
        return 0;
    }
    result = &D_0070F380[a0 * 16];
    SignalSema(D_0054AB28[0]);
    return result;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceFs_Rcv_Intr);

extern int D_0054AB24[];
extern int CreateSema(int *self);

void _sceFsSemInit(void) {
    int self[8];
    if (D_0054AB24[0] == -1) {
        self[0x8 / 4] = 1;
        self[0x4 / 4] = 1;
        self[0x14 / 4] = 0;
        D_0054AB24[0] = CreateSema(self);
    }
}

extern void _sceFsSemInit(void);
extern void WaitSema(int a0);
extern int D_0054AB24[];

int _sceFsWaitS(int arg) {
    _sceFsSemInit();
    WaitSema(D_0054AB24[0]);
    return 0;
}

extern int D_0054AB24[];
extern void SignalSema(int a0);

void func_00243628(void) {
    SignalSema(D_0054AB24[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceFsInit);

extern char D_00270A8C[];
extern char D_0070F5A8[];
extern int D_0054AB30[];

int func_002437D8(void) {
    char *s3 = D_00270A8C;
    char *s1 = D_0070F5A8;
    int s2 = 0;
    int v0;
    v0 = memcmp(s1, s3, 4);
    if (v0 == 0) goto done;
    v0 = memcmp(s1, (char *)D_0054AB30[0], 4);
    if (v0 == 0) goto done;
    v0 = memcmp(s3, (char *)D_0054AB30[0], 4);
    s2 = (unsigned)0 < (unsigned)v0;
done:
    return s2;
}

extern int D_0054AB20[];
extern char D_0070F5A8[];
extern void memset(void *a0, int a1, int a2);

int sceFsReset(void) {
    D_0054AB20[0] = 0;
    memset(D_0070F5A8, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceClose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00243CA8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceRead);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceWrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00244410);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIoctl2);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCallCode);

extern int _sceCallCode(void *a0, int a1);

int sceRemove(void *a0) {
    return _sceCallCode(a0, 6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMkdir);

int sceRmdir(void *a0) {
    return _sceCallCode(a0, 8);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceFormat);

/* m2c scaffold from asm/aug6/nonmatchings/common/src/PObj/sceAddDrv.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern int DeleteSema(int a0);
extern int sceSifCallRpc();
extern void sceFsInit(void);
extern int D_0070E2C0[];
extern int D_0070EF00;
extern int D_0070F580;

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceAddDrv);


int sceDelDrv(void *a0) {
    return _sceCallCode(a0, 0x10);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDopen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDclose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceGetstat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceChstat);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceRename);

int sceChdir(void *a0) {
    return _sceCallCode(a0, 0x12);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSync);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMount);

int sceUmount(void *a0) {
    return _sceCallCode(a0, 0x15);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00245DF8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceDevctl);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSymlink);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceReadlink);

extern char D_FFFFF[];
extern int D_0070F600[];
extern int D_0054AB34[];

int sceSifInitIopHeap(void)
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
    ret = sceSifBindRpc(D_0070F600, 0x80000003, 0);
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

int sceSifAllocIopHeap(int a0) {
    int ret = D_0054AB34[0];
    if (ret < 0) return 0;
    D_0070F680[0] = a0;
    ret = sceSifCallRpc(D_0070F600, 1, 0, D_0070F680, 4, D_0070F640, 4, 0, 0);
    if (ret >= 0) return D_0070F640[0];
    return 0;
}

extern int D_0070F6C0[];

int sceSifFreeIopHeap(int a0) {
    int v2 = D_0054AB34[0];
    if (v2 < 0) return 0;
    D_0070F6C0[0] = a0;
    v2 = sceSifCallRpc(D_0070F600, 2, 0, D_0070F6C0, 4, D_0070F640, 4, 0, 0);
    if (v2 < 0) return -1;
    return D_0070F640[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifLoadIopHeap);

extern int D_0054AB38[];
extern char D_0070FA00[];
extern char D_0070F800[];
extern char D_0070FA28[];

int _lf_bind(void) {
    int i;
    int r;
    int val;
    if (D_0054AB38[0] >= 0) goto ret0;
loop:
    r = sceSifBindRpc(D_0070FA00, 0x80000006, 0);
    if (r < 0) return -1;
    val = *(int *)(D_0070FA00 + 0x24);
    if (val == 0) goto delay;
    D_0054AB38[0] = 0;
    r = sceSifCallRpc(D_0070FA00, 0xFF, 0, 0, 0, D_0070F800, 4, 0, 0);
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
    if (memcmp(s1, (int)s3, 4) == 0) goto done;
    v = D_0054AB3C[0];
    if (memcmp(s1, v, 4) == 0) goto done;
    v = D_0054AB3C[0];
    s2 = (0 < (unsigned int)memcmp(s3, v, 4));
done:
    return s2;
}

extern int D_0054AB38[];
extern char D_0070FA28[];

int sceSifLoadFileReset(void) {
    D_0054AB38[0] = -1;
    memset(D_0070FA28, 0, 4);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246A30);

extern int func_00246A30(void *a0, int a1, int a2, void *a3);

void sceSifLoadModuleBuffer(void *a0, int a1, int a2) {
    int local[4];
    func_00246A30(a0, a1, a2, &local);
}

int func_00246C58(void *a0, int a1, int a2, void *a3) {
    return func_00246A30(a0, a1, a2, a3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00246C78);

extern void func_00246C78(void *a0, int a1, int a2, int a3, int a4);

void sceSifLoadModule(void *a0, int a1, int a2) {
    int local;
    func_00246C78(a0, a1, a2, (int)&local, 0);
}

void sceSifLoadStartModule(void *a0, int a1, int a2, int a3) {
    do {
        func_00246C78(a0, a1, a2, a3, 0);
    } while (0);
}

extern int _lf_bind(void);
extern int func_00246968(void);
extern int sceSifCallRpc();
extern void strncpy(char *a0, char *a1, int a2);
extern char D_0070F808[];
extern char D_0070FA00[];

int func_00246EE0(void *a0, int a1, int a2, int a3) {
    char *buf;
    int r;

    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if (func_00246968() != 0) {
        return 0xFFFEFFFC;
    }
    strncpy(D_0070F808, a0, 0xFC);
    buf = D_0070F808 - 8;
    buf[0x103] = 0;
    strncpy(D_0070F808 + 0xFC, (char *)a1, 0xFC);
    buf[0x1FF] = 0;
    r = sceSifCallRpc(D_0070FA00, a3, 0, buf, 0x200, buf, 0x10, 0, 0);
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

int sceSifLoadElfPart(void *a0, int a1, int a2) {
    return func_00246EE0(a0, a1, a2, 1);
}

extern char D_00628838[];

int sceSifLoadElf(void *a0, int a1) {
    return func_00246EE0(a0, (int)D_00628838, a1, 1);
}

extern int _lf_bind(void);
extern int sceSifCallRpc();
extern char D_0070F800[];
extern char D_0070FA00[];

int sceSifGetIopAddr(int a0, void *a1, int a2) {
    int r;
    if (_lf_bind() < 0) {
        return 0xFFFF0000;
    }
    if ((unsigned int)a2 >= 3) {
        return 0xFFFEFFFE;
    }
    *(int *)(D_0070F800 + 0) = a0;
    *(int *)(D_0070F800 + 4) = a2;
    r = sceSifCallRpc(D_0070FA00, 3, 0, D_0070F800, 0x20, D_0070F800, 0x20, 0, 0);
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

extern int _lf_bind(void);
extern int sceSifCallRpc();
extern char D_0070F800[];
extern char D_0070FA00[];

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifSetIopAddr);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifResetIop);

extern int sceSifGetReg(int a0);

int sceSifIsAliveIop(void) {
    int t = sceSifGetReg(4) & 0x10000;
    return t != 0;
}

extern void sceSifSetReg(int a0, int a1);

int sceSifSyncIop(void) {
    if (sceSifGetReg(4) & 0x40000) {
        sceSifSetReg(4, 0x40000);
        ((void (*)(void))func_002418E0)();
        return 1;
    }
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceSifRebootIop);

/* _DumpTLB: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _DumpTLB\n"
    ".type _DumpTLB, @function\n"
    "    .align 3\n"
    "_DumpTLB:\n"
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
    "    jal scePrintf\n"
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
    "    jal scePrintf\n"
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
    ".size _DumpTLB, . - _DumpTLB\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* kPutTLBEntry: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global kPutTLBEntry\n"
    ".type kPutTLBEntry, @function\n"
    "    .align 3\n"
    "kPutTLBEntry:\n"
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
    ".size kPutTLBEntry, . - kPutTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* kSetTLBEntry: handwritten TLB-write routine (mfc0/mtc0/tlbwi/sync.p).
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
    "    .global kSetTLBEntry
"
    "    .type kSetTLBEntry, @function
"
    "    .align 3\n"
    "kSetTLBEntry:
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
    "    .size kSetTLBEntry, . - kSetTLBEntry
"
    "    .set reorder
"
    "    .set at
"
);

/* kGetTLBEntry: handwritten TLB-read routine (mtc0/tlbr/mfc0/sync.p).
 * C-inexpressible privileged COP0 ops; in-file handwritten asm per maintainer
 * exception (cf. kSetTLBEntry, func_002484AC). */
__asm__(
    ".section .text
"
    "    .set noat
"
    "    .set noreorder
"
    "    .global kGetTLBEntry
"
    "    .type kGetTLBEntry, @function
"
    "    .align 3\n"
    "kGetTLBEntry:
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
    "    .size kGetTLBEntry, . - kGetTLBEntry
"
    "    .set reorder
"
    "    .set at
"
);

/* kProbeTLBEntry: handwritten TLB-probe routine (mtc0/tlbp/tlbr/mfc0/sync.p).
 * C-inexpressible privileged COP0 ops; in-file handwritten asm per maintainer
 * exception (cf. kSetTLBEntry, kGetTLBEntry). */
__asm__(
    ".section .text
"
    "    .set noat
"
    "    .set noreorder
"
    "    .global kProbeTLBEntry
"
    "    .type kProbeTLBEntry, @function
"
    "    .align 3\n"
    "kProbeTLBEntry:
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
    "    .size kProbeTLBEntry, . - kProbeTLBEntry
"
    "    .set reorder
"
    "    .set at
"
);

/* kExpandScratchPad: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global kExpandScratchPad\n"
    ".type kExpandScratchPad, @function\n"
    "    .align 3\n"
    "kExpandScratchPad:\n"
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
    "    jal kProbeTLBEntry\n"
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
    ".size kExpandScratchPad, . - kExpandScratchPad\n"
    "    .set reorder\n"
    "    .set at\n"
);

extern int D_0054AB40[];
extern void func_00247A00(void);

void *SetTLBHandler(void *a0) {
    D_0054AB40[0] = (int)a0;
    SetVTLBRefillHandler(1, func_00247A00);
    SetVTLBRefillHandler(2, func_00247A00);
    SetVTLBRefillHandler(3, func_00247A00);
    return a0;
}

extern int D_0054AB48[];
extern char D_00247C40[];

int SetDebugHandler(int a0, int a1) {
    int old;
    int orig = a0;
    unsigned int err = 0xFFFFFFFF;
    if ((unsigned)(a0 - 1) >= 13) {
        return (int)err;
    }
    old = D_0054AB48[orig];
    D_0054AB48[orig] = a1;
    if ((unsigned)(a0 - 1) < 3) {
        SetVTLBRefillHandler(orig, (void *)D_00247C40);
    } else {
        SetVCommonHandler(orig, (void *)D_00247C40);
    }
    return old;
}

/* func_00247908 — hand-written PS2 EE syscall stub: syscall number in $v1,
 * then `syscall 0`. .set noreorder keeps the bare nop in the jr delay slot.
 * The leading nop is SetDebugHandler's trailing 16-align padding (dropped by gcc
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

void InitTLBFunctions(void)
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

/* PutTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel PutTLBEntry\n"
    "    addiu      $3, $0, 0x55\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel PutTLBEntry\n"
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

/* iSetTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel iSetTLBEntry\n"
    "    addiu      $3, $0, -0x56\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iSetTLBEntry\n"
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

/* iGetTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel iGetTLBEntry\n"
    "    addiu      $3, $0, -0x57\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel iGetTLBEntry\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* ProbeTLBEntry — hand-written PS2 EE syscall stub (syscall number in $v1). */
__asm__(
    ".section .text\n"
    "    .set at\n"
    "    .set noreorder\n"
    "glabel ProbeTLBEntry\n"
    "    addiu      $3, $0, 0x58\n"
    "    syscall    0\n"
    "    jr         $31\n"
    "    nop\n"
    "endlabel ProbeTLBEntry\n"
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

void _change_addr(int *a0, int *a1) {
    a1[2] = a0[4];
}

extern int D_00710F00[];

int func_00247D90(int a0) {
    return D_00710F00[a0];
}

int sceSifSetSreg(int a0, int a1) {
    D_00710F00[a0] = a1;
    return a1;
}

extern int D_00710DD8[];

void *func_00247DC8(void) {
    return D_00710DD8;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00247DD8);

extern int func_00100AD8(int a0);
extern int RemoveDmacHandler(int a0, int a1);
extern int D_00710DD4[];
extern int D_0054ABB8[];

void sceSifExitCmd(void) {
    func_00100AD8(5);
    RemoveDmacHandler(5, D_00710DD4[0]);
    D_0054ABB8[0] = 0;
}

extern int D_00710DD8[];

int sceSifSetCmdBuffer(int a0, int a1) {
    int old = D_00710DD8[5];
    D_00710DD8[5] = a0;
    D_00710DD8[6] = a1;
    return old;
}

int sceSifSetSysCmdBuffer(int a0, int a1) {
    int old = D_00710DD8[3];
    D_00710DD8[3] = a0;
    D_00710DD8[4] = a1;
    return old;
}

extern int D_00710DE4[];
extern int D_00710DEC[];

int sceSifAddCmdHandler(int a0, int a1, int a2) {
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

void sceSifRemoveCmdHandler(int a0) {
    int off = a0 * 8;
    if (a0 < 0) {
        a0 = D_00710DE4[0];
    } else {
        a0 = D_00710DEC[0];
    }
    off += a0;
    *(int *)off = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceSifSendCmd);

int sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = _sceSifSendCmd(a0, 0, a1, a2, a3, t0, t1);
  return v;
  asm __volatile__("" : : : "memory");
}

extern int _sceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1, int t2);

int isceSifSendCmd(int a0, int a1, int a2, int a3, int t0, int t1)
{
  int v = _sceSifSendCmd(a0, 1, a1, a2, a3, t0, t1);
  int new_var;
  new_var = v;
  return new_var;
  asm __volatile__("" : : : "memory");
}

/* _sceSifCmdIntrHdlr: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _sceSifCmdIntrHdlr\n"
    ".type _sceSifCmdIntrHdlr, @function\n"
    "    .align 3\n"
    "_sceSifCmdIntrHdlr:\n"
    "    addiu $29, $29, -0x90\n"
    "    sd $16, 0x70($29)\n"
    "    sd $31, 0x80($29)\n"
    "    jal EIntr\n"
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
    "    jal isceSifSetDChain\n"
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
    ".size _sceSifCmdIntrHdlr, . - _sceSifCmdIntrHdlr\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* Hand-written EE assembly (NOT a C-match target) — a cache / INTC
 * critical-section module:
 *   func_002483F8  DCache hit-writeback-invalidate loop (cache 0x18 / sync).
 *   func_002484A4  + func_002484AC are ONE routine splat over-split: the ISR.
 *                  Its real entry is func_002484A4 + 0x4 (the addiu $sp,-0x10),
 *                  which sceCdDelayThread installs via %hi/%lo(func_002484A4 + 0x4);
 *                  the body ends with `ei` (enable interrupts, COP0).
 *   sceCdDelayThread  installs that ISR and toggles INTC enable.
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
    "    jal   iSignalSema
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdDelayThread);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCd_cd_callback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00248630);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sceCd_cd_read_intr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", cmd_sem_init);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", cdvd_exit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdPOffCallback);

extern void (*D_00710F84[])(int);
extern int D_0054ABE4[];
extern int D_00710F88[];

void _sceCd_Poff_Intr(void) {
    if (D_00710F84[0] != 0 && D_0054ABE4[0] == 0) {
        D_00710F84[0](D_00710F88[0]);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", PowerOffCB);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdSearchFile);

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
        int r = sceSifCallRpc(D_0054BD90, 0xE, 0, 0, 0, base, 4, 0, 0);
        if (r < 0) {
            SignalSema(D_0054ABE8[0]);
            return 0;
        }
        {
            int val = *(int *)((int)base | 0x20000000);
            SignalSema(D_0054ABE8[0]);
            return val;
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdSync);

extern int D_0054ABD0[];
extern char D_006289E8[];
extern char D_0054C608[];

int sceCdSyncS(int a0) {
    if (!a0) {
        if (D_0054ABD0[0] > 0) scePrintf(D_006289E8);
        while (sceSifCheckStatRpc(D_0054C608)) {
            sceCdDelayThread(0x3C);
        }
        return 0;
    }
    return sceSifCheckStatRpc(D_0054C608);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002491D0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdDiskReady);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdMmode);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdRead);

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
        int r = sceSifCallRpc(D_0054C608, 3, 0, 0, 0, base, 4, 0, 0);
        if (r < 0) {
            SignalSema(D_0054ABEC[0]);
            return 0;
        }
        {
            int val = *(int *)((int)base | 0x20000000);
            SignalSema(D_0054ABEC[0]);
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
        int r = sceSifCallRpc(D_0054C608, 4, 0, 0, 0, base, 4, 0, 0);
        if (r < 0) {
            SignalSema(D_0054ABEC[0]);
            return 0xFFFFFFFF;
        }
        {
            int val = *(int *)((int)base | 0x20000000);
            SignalSema(D_0054ABEC[0]);
            return val;
        }
    }
}

extern int D_0054C630[];
extern int D_00711258[];
extern int sceCdStream(int a0, int a1, int a2, int a3, void *a4);

int sceCdStInit(int a0, int a1, int a2) {
    D_0054C630[0] = 0;
    return sceCdStream(a0, a1, a2, 5, D_00711258);
}

int sceCdStStart(int a0, void *a1) {
    D_0054C630[0] = 1;
    return sceCdStream(a0, 0, 0, 1, a1);
}

int sceCdStSeekF(int a0) {
    return sceCdStream(a0, 0, 0, 9, D_00711258);
}

int sceCdStSeek(int a0) {
    return sceCdStream(a0, 0, 0, 4, D_00711258);
}

int sceCdStStop(void) {
    D_0054C630[0] = 0;
    return sceCdStream(0, 0, 0, 3, D_00711258);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStRead);

extern int D_0054ABD0[];
extern char D_00628B80[];

int sceCdStPause(void) {
    D_0054C630[0] = 0;
    if (D_0054ABD0[0] > 0) {
        scePrintf(D_00628B80);
    }
    return sceCdStream(0, 0, 0, 7, D_00711258);
}

extern char D_00628B98[];

int sceCdStResume(void) {
    D_0054C630[0] = 1;
    if (D_0054ABD0[0] > 0) {
        scePrintf(D_00628B98);
    }
    return sceCdStream(0, 0, 0, 8, D_00711258);
}

extern int D_00628BB0[];

int sceCdStStat(void) {
    if (D_0054ABD0[0] > 0) {
        scePrintf(D_00628BB0);
    }
    return sceCdStream(0, 0, 0, 6, D_00711258);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceCdStream);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _send_to_iop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInit2);

extern int D_007115C0[];
extern int D_00711280[];
extern int D_0054C648[];

int scePadEnd(void) {
    int ret;
    int val;
    D_007115C0[0] = 0xF;
    ret = sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = D_007115C0[3];
    if (val == 1) {
        D_0054C648[0] = 0;
    }
    return val;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadPortOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadPortClose);

typedef struct { char pad0[0x10]; int f10; char pad14[0x8]; } PObjA8B8Ent; /* 0x1C */
extern PObjA8B8Ent D_007112D0[][4];

int scePadGetDmaStr(int a0, int a1) {
    int s0;
    int v0, v1, r;
    s0 = *(int *)((char *)D_007112D0 + a1 * 0x1C + a0 * 0x70);
    func_0026B730((char *)s0, (char *)s0 + 0x100);
    v0 = *(int *)(s0 + 0x58);
    v1 = *(int *)(s0 + 0xD8);
    r = (v0 < v1);
    return s0 + (r << 7);
}

int scePadGetFrameCount(int a0, int a1) {
    int ret = 0;
    if (D_007112D0[a0][a1].f10 == 0) {
        return ret;
    }
    return *(int *)(scePadGetDmaStr(a0, a1) + 0x58);
}

int scePadRead(int a0, int a1, int a2) {
    int s0;
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    s0 = scePadGetDmaStr(a0, a1);
    memcpy(a2, s0, *(int *)(s0 + 0x60));
    return *(int *)(s0 + 0x60);
}

int scePadGetState(int a0, int a1) {
    unsigned char *p;
    if (D_007112D0[a0][a1].f10 == 0) return 0x63;
    p = (unsigned char *)scePadGetDmaStr(a0, a1);
    if (p[0x70] != 6) return p[0x70];
    if (p[0x71] == 2) return 5;
    return p[0x70];
}

extern int D_0054C650[];
extern unsigned char D_00628D28[];
extern void strcpy(char *a0, int a1);

void func_0024AA00(int a0, char *a1) {
    if ((unsigned int)a0 < 8) {
        strcpy(a1, D_0054C650[a0]);
    } else {
        *a1 = D_00628D28[0];
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetReqState);

int scePadGetReqState(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return ((unsigned char *)scePadGetDmaStr(a0, a1))[0x71];
}

extern int D_0054C670[];

void func_0024AAF0(int a0, char *a1) {
    if ((unsigned int)a0 < 4) {
        strcpy(a1, D_0054C670[a0]);
    } else {
        *a1 = D_00628D28[0];
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoAct);

int scePadInfoComb(int a0, int a1, int a2, int a3) {
    unsigned char *p;
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    p = (unsigned char *) scePadGetDmaStr(a0, a1);
    if (p[0x72] != 1) {
        return 0;
    }
    if (p[0x64] < 2U) {
        return 0;
    }
    if (a2 == -1) {
        return p[0x6B];
    }
    if (a2 < (int) p[0x6B]) {
        if (a3 == 0) {
            goto l41;
        }
        if (a3 > 0) {
            if (a3 == 1) {
                goto l42;
            }
            if (a3 == 2) {
                goto l43;
            }
            return 0;
        }
        if (a3 == -1) {
            goto l40;
        }
    }
    return 0;
l40:
    return p[a2 * 4 + 0x40];
l41:
    return p[a2 * 4 + 0x41];
l42:
    return p[a2 * 4 + 0x42];
l43:
    return p[a2 * 4 + 0x43];
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoMode);

int scePadSetMainMode(int a0, int a1, int a2, int a3) {
    int *s0 = D_007115C0;
    int local = 0;
    int ret;
    int s;
    D_007115C0[0] = 6;
    s0[1] = a0;
    s0[2] = a1;
    s0[3] = a2;
    s0[4] = a3;
    ret = sceSifCallRpc((int)D_00711280, 1, 0, (int)s0, 0x80, (int)s0, 0x80, 0, local);
    if (ret < 0) {
        return 0;
    }
    s = s0[5];
    if (s == 1) {
        scePadSetReqState(a0, a1, 2);
        s = s0[5];
    }
    return s;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadSetActDirect);

extern int scePadSetReqState(int a0, int a1, int a2);

int scePadSetActAlign(int a0, int a1, char *a2)
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
    ret = sceSifCallRpc(D_00711280, 1, 0, new_var, 0x80, new_var, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    val = s0[5];
    if (val == 1) {
        scePadSetReqState(a0, a1, 2);
        val = s0[5];
    }
    return val;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadGetButtonMask);

extern int D_007115C0[];
extern int D_00711280[];

int scePadSetButtonInfo(int a0, int a1, int a2) {
    int ret;
    D_007115C0[3] = a2;
    D_007115C0[0] = 0xA;
    D_007115C0[1] = a0;
    D_007115C0[2] = a1;
    if (sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0) < 0) {
        return 0;
    }
    ret = D_007115C0[4];
    if (ret == 1) {
        scePadSetReqState(a0, a1, 2);
        ret = D_007115C0[4];
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scePadInfoPressMode);

int scePadEnterPressMode(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0xFFF);
}

int scePadExitPressMode(int a0, int a1) {
    if (D_007112D0[a0][a1].f10 == 0) {
        return 0;
    }
    return scePadSetButtonInfo(a0, a1, 0);
}

struct S12 { char b[12]; };
extern int D_007115C0[];
extern int D_00711280[];
extern int sceSifCallRpc();
extern int scePadSetReqState(int a0, int a1, int a2);

int scePadSetVrefParam(int a0, int a1, void *a2) {
    int r;
    D_007115C0[1] = a0;
    D_007115C0[0] = 0xB;
    D_007115C0[2] = a1;
    *(struct S12 *)((char *)D_007115C0 + 0xC) = *(struct S12 *)a2;
    r = sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (r < 0) {
        return 0;
    }
    if (D_007115C0[7] == 1) {
        scePadSetReqState(a0, a1, 2);
    }
    return D_007115C0[7];
}

int scePadGetPortMax(void) {
    int ret;
    D_007115C0[0] = 0xC;
    ret = sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}

int scePadGetSlotMax(int a0) {
    int ret;
    D_007115C0[0] = 0xD;
    D_007115C0[1] = a0;
    ret = sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}

int scePadGetModVersion(void) {
    int ret;
    D_007115C0[0] = 0x12;
    ret = sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[3];
}

int scePadSetWarningLevel(int a0) {
    int ret;
    D_007115C0[0] = 0x14;
    D_007115C0[1] = a0;
    ret = sceSifCallRpc(D_00711280, 1, 0, D_007115C0, 0x80, D_007115C0, 0x80, 0, 0);
    if (ret < 0) {
        return 0;
    }
    return D_007115C0[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMcInit);

extern char D_00712C00[];
extern char D_0054C690[];
extern int D_0054C694[];
extern char D_00711640[];

void *_lmcGetClientPtr(int *a0, int *a1) {
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
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024B7B8(void *a0) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[5] = (int)a0;
    r = sceSifCallRpc(obj, 0x14, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x14;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern int D_007116C0[];
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024B870(void *a0) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[1] = (int)a0;
    r = sceSifCallRpc(obj, 0x15, 0, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r != 0) {
        SignalSema(D_0054C694[0]);
        return r;
    }
    SignalSema(D_0054C694[0]);
    return ((int *)D_00712C00)[0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024B930);

extern int func_0024B930(int a0, int a1, int a2, int a3);

int sceMcMkdir(int a0, int a1, int a2) {
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
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024BAA0(void *a0) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    r = sceSifCallRpc(obj, 3, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 3;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024BB58(void *a0, int a1, int a2) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    D_007116C0[4] = a1;
    D_007116C0[5] = a2;
    r = sceSifCallRpc(obj, 4, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 4;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", mceIntrReadFixAlign);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern char D_00711B40[];
extern int D_007116C0[];
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern void func_002483F8(void *a0, int a1);
extern int mceIntrReadFixAlign();
extern int sceSifCallRpc();

int func_0024BCC0(void *a0, int a1, int a2) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    D_007116C0[7] = (int)D_00711B40;
    D_007116C0[6] = a1;
    D_007116C0[3] = a2;
    func_002483F8((void *)a1, a2);
    func_002483F8(D_00711B40, 0xC0);
    r = sceSifCallRpc(obj, 5, 1, D_007116C0, 0x30, D_00712C00, 4, mceIntrReadFixAlign, D_00711B40);
    if (r == 0) {
        *(int *)D_0054C690 = 5;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024BDE0);

extern void iWakeupThread(int a0);

void mcHearAlarm(int a0, int a1, int a2) {
    iWakeupThread(a2);
    SYNC();
    EI();
}

extern int GetThreadId(void);
extern int SetAlarm(int a0, void *a1, int a2);

void mcDelayThread(int a0) {
    SetAlarm(a0 & 0xFFFF, mcHearAlarm, GetThreadId());
    SleepThread();
}

extern char D_0054C690[];
extern char D_00711640[];
extern char D_00712C00[];
extern int D_0054C694[];
extern int sceSifCheckStatRpc(char *a0);
extern void mcDelayThread(int a0);
extern void SignalSema(int a0);

int sceMcSync(int a0, int *a1, int *a2) {
    int r;
    if (*(int *)D_0054C690 == 0) {
        return 0xFFFFFFFF;
    }
    r = sceSifCheckStatRpc(D_00711640);
    if (a0 != 0) goto L050;
    if (r == 0) goto L050;
    while (sceSifCheckStatRpc(D_00711640) != 0) {
        mcDelayThread(0x3C);
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
        SignalSema(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", mceGetInfoApdx);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMcGetInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C290);

extern int strlen(char *a0);
extern int memcpy(char *a0, char *a1, int a2);
extern char D_00711C00[];

void mceStorePwd(char *a0) {
    int n;
    if (a0 != 0) {
        if ((unsigned int)strlen((char *)((int)D_00711C00 | 0x20000000)) < 0x400) {
            n = strlen((char *)((int)D_00711C00 | 0x20000000));
        } else {
            n = 0x3FF;
        }
        memcpy(a0, (char *)((int)D_00711C00 | 0x20000000), n);
        a0[n] = 0;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C470);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024C5C0(void *a0, int a1) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[2] = a1;
    D_007116C0[1] = (int)a0;
    r = sceSifCallRpc(obj, 0x10, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x10;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024C688);

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116C0[];
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024C7B0(void *a0) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[0] = (int)a0;
    r = sceSifCallRpc(obj, 0xA, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0xA;
    } else {
        SignalSema(D_0054C694[0]);
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
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern int sceSifCallRpc();

int func_0024CBA8(void *a0, int a1) {
    int *obj;
    int r;
    r = PollSema(D_0054C694[0]);
    if (r < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    D_007116C0[2] = a1;
    D_007116C0[1] = (int)a0;
    r = sceSifCallRpc(obj, 0x11, 1, D_007116C0, 0x30, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x11;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

extern int D_0054C694[];
extern char D_00711640[];
extern char D_00712C00[];
extern char D_0054C690[];
extern int D_007116F0[];
extern int PollSema(int a0);
extern void SignalSema(int a0);
extern void strncpy(char *a0, char *a1, int a2);
extern int sceSifCallRpc();

int func_0024CC70(void *a0, int a1, char *a2) {
    int *obj;
    int r;
    if (PollSema(D_0054C694[0]) < 0) {
        return -200;
    }
    obj = (int *)D_00711640;
    if (obj[9] == 0) {
        SignalSema(D_0054C694[0]);
        return -100;
    }
    if (a2 == 0 || a2[0] == 0) {
        SignalSema(D_0054C694[0]);
        return -210;
    }
    D_007116F0[0] = (int)a0;
    D_007116F0[1] = a1;
    strncpy((char *)D_007116F0 + 0x14, a2, 0x3FF);
    *((char *)D_007116F0 + 0x413) = 0;
    r = sceSifCallRpc(D_00711640, 0x12, 1, D_007116F0, 0x414, D_00712C00, 4, 0, 0);
    if (r == 0) {
        *(int *)D_0054C690 = 0x12;
    } else {
        SignalSema(D_0054C694[0]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _type2id);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _id2type);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegDemuxPssRing);

extern void sceMpegDemuxPssRing(void *a0, int a1, int a2, int a3, int a4);
void sceMpegDemuxPss(void *a0, int a1, int a2) {
    do {
        sceMpegDemuxPssRing(a0, a1, a2, 0, -1);
    } while (0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegAddStrCallback);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pack_header);

int _system_header(int *a0) {
    _sysbitGet(a0, 0x38);
    _sysbitGet(a0, 0x28);
    while (_sysbitNext(a0, 1) == 1) {
        _sysbitGet(a0, 0x18);
    }
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _PES_packet);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegInit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceMpegCreate);

int func_0024DE40(void) {
    return 1;
}

extern int D_0054C768[];
extern int D_0054C880[];
extern void _sendDataToIPU(int a0, int a1);

void sceMpegAddBs(int a0, int a1, int a2) {
    int rounded = (a2 + 0x13) / 16 * 16;
    D_0054C768[0] = a1;
    D_0054C880[0] = rounded;
    _sendDataToIPU(a1, rounded);
}

int sceMpegGetPicture(int *a0, unsigned int a1, int a2) {
    int *p = (int *)a0[0x40/4];
    a1 = (a1 & 0x0FFFFFFF) | 0x20000000;
    p[0xB0/4] = 1;
    p[0xD8/4] = a1;
    p[0xE4/4] = a2;
    p[0xE0/4] = 0;
    p[0xDC/4] = 0;
    return _getpic((int)a0);
}

void sceMpegGetPictureRAW8(int *self, unsigned int a1, int a2, int a3)
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
  _getpic((int) self);
  asm __volatile__("" : : : "memory");
}

extern void _getpic(int self);

void sceMpegGetPictureRAW8xy(int *self, unsigned int a1, int a2, int a3)
{
  int *p = (int *) self[0x40 / 4];
  int prod;
  p[0xE0 / 4] = a3 << 4;
  p[0xD8 / 4] = (a1 & 0x0FFFFFFF) | 0x20000000;
  prod = a2 * a3;
  p[0xE4 / 4] = prod;
  p[0xDC / 4] = a2 << 4;
  p[0xB0 / 4] = 0;
  _getpic((int) self);
  asm __volatile__("" : : : "memory");
}

void sceMpegSetDecodeMode(void *a0, int a1, int a2, int a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x25] = a1;
    p[0x26] = a2;
    p[0x27] = a3;
}

void sceMpegGetDecodeMode(void *a0, int *a1, int *a2, int *a3) {
    int *p = *(int **)((char *)a0 + 0x40);
    *a1 = *(int *)((char *)p + 0x94);
    *a2 = *(int *)((char *)p + 0x98);
    *a3 = *(int *)((char *)p + 0x9C);
}

int sceMpegIsEnd(int **a0) {
    return a0[0x10][0];
}

int sceMpegIsRefBuffEmpty(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    return *(int *)((char *)p + 0x4) == 0;
}

extern void _clearEach(void);
extern void _initSeqAgain(void);
extern int D_0054C884_b[] __asm__("D_0054C884");

void sceMpegReset(int *a0) {
    int *p = (int *)a0[0x10];
    p[0] = 0;
    p[1] = 0;
    p[2] = 0;
    a0[2] = 0;
    p[0x20] = -1;
    p[0x2B] = 0;
    _clearEach();
    D_0054C884_b[0] = 0;
    _initSeqAgain();
}

extern int D_0054C780[];
extern int D_0054C784[];
extern int D_0054C78C[];
extern int D_0054C790[];
extern int D_0054C798[];
extern int D_0054C79C[];

int sceMpegClearRefBuff(void) {
    if (D_0054C780[0] != 0) *(int *)(D_0054C780[0] + 0x28) = 0;
    if (D_0054C78C[0] != 0) *(int *)(D_0054C78C[0] + 0x28) = 0;
    if (D_0054C798[0] != 0) *(int *)(D_0054C798[0] + 0x28) = 0;
    if (D_0054C784[0] != 0) *(int *)(D_0054C784[0] + 0x28) = 0;
    if (D_0054C790[0] != 0) *(int *)(D_0054C790[0] + 0x28) = 0;
    if (D_0054C79C[0] != 0) *(int *)(D_0054C79C[0] + 0x28) = 0;
    return 1;
}

int sceMpegAddCallback(void *a0, int a1, int a2, int a3) {
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

/* _dispatchMpegCallback — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
/* _dispatchMpegCallback — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
/* _dispatchMpegCallback — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
/* _dispatchMpegCallback — PARKED near-miss rc9. vtable dispatch + fn-ptr call.
 * a0->[0x40]=tbl; e=tbl+(*a1<<3); fn=e[0xC]; rv=fn(a0,a1,e[0x10]); else rv=0. */
INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dispatchMpegCallback);





extern void *_dispatchMpegCallback(void *a0, void *a1);

void _dispatchMpegCbNodata(void *a0) {
    int buf[8];
    buf[0] = 1;
    _dispatchMpegCallback(a0, buf);
}

void sceMpegSetDefaultPtsGap(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    p[0x1C] = 1;
    *(long long *)((char *)p + 0x78) = a1;
}

void sceMpegResetDefaultPtsGap(void *a0) {
    void *p = *(void **)((char *)a0 + 0x40);
    *(int *)((char *)p + 0x70) = 0;
    *(long long *)((char *)p + 0x78) = 0;
}

extern void *D_0054C764[];

void sceMpegSetImageBuff(int a0) {
    int *q = *(int **)((char *)D_0054C764[0] + 0x40);
    q[0x36] = a0;
}

int sceMpegDispWidth(int **a0) {
    return a0[0x10][0x33];
}

int sceMpegDispHeight(int **a0) {
    return a0[0x10][0x34];
}

void *func_0024E160(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

void *func_0024E170(int **a0) {
    return (char *)a0[0x10] + 0xB4;
}

int sceSetBrokenLink(void *a0, int a1) {
    void *p = *(void **)((char *)a0 + 0x40);
    int old = *(int *)((char *)p + 0xE8);
    *(int *)((char *)p + 0xE8) = a1;
    return old;
}

void sceSetPtm(void *a0, long long a1) {
    int *p = *(int **)((char *)a0 + 0x40);
    *(long long *)((char *)p + 0xF0) = a1;
    p[0x3E] = 1;
}

void _alalcInit(int *a0, int a1, int a2) {
    a0[0] = a1;
    a0[1] = a2;
    a0[2] = a1;
    a0[3] = a1;
}

void _alalcSetDynamic(int *a0) {
    a0[3] = a0[2];
}

void _alalcFree(int *a0) {
    a0[2] = a0[3];
}

extern void _Error(void *a0);
extern int D_00628E28[];

int _alalcAlloc(unsigned int *a0, int a1, unsigned int a2) {
    unsigned int rounded;
    unsigned int total;
    rounded = ((a0[2] + a2 - 1) / a2) * a2;
    total = rounded + a1;
    if (a0[0] + a0[1] >= total) {
        a0[2] = total;
        return rounded;
    }
    _Error(D_00628E28);
    return 0;
}

int _alalcRest(int *a0) {
    return a0[0] + a0[1] - a0[2];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _getpic);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decodeOrSkipFrame);

extern int D_0054C92C[];
extern int _decodeOrSkipFrame(int a0, int a1, int a2);
extern int _decodeOrSkipField(int a0, int a1, int a2);

int _decodeOrSkip(int a0, int a1, int a2) {
    if (D_0054C92C[0] != 3) {
        return _decodeOrSkipField(a0, a1, a2);
    }
    return _decodeOrSkipFrame(a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decodeOrSkipField);

extern void _lastFrame(int a0);
extern int D_0054C884[];

int _sceMpegFlush(int *self) {
    int *p = (int *)self[0x40 / 4];
    int ret = 0;
    if (p[1] != 0 && p[2] != 0) {
        _lastFrame(D_0054C884[0]);
        self[2] = D_0054C884[0] - p[0xAC / 4];
        p[1] = 0;
        ret = 1;
    }
    return ret;
}

extern int D_0054D030_alias[] __asm__("D_0054D030");
extern void _ipuSetMPEG1(int a0);

void _initSeqAgain(void) {
    D_0054D030_alias[0] = 0;
    _ipuSetMPEG1(1);
}

extern int D_0054C784[];
extern int D_0054C790[];
extern int D_0054C79C[];
extern int D_0054C89C[];
extern int D_0054C92C[];
extern char D_00628EA8[];

void _lastFrame(int a0) {
    int t;
    if (D_0054C89C[0]) {
        _Error(D_00628EA8);
        D_0054C89C[0] = 0;
        return;
    }
    t = D_0054C92C[0];
    if (t == 3) {
        _dispRefImage(D_0054C784[0], a0 - 1);
    } else {
        _dispRefImageField(D_0054C790[0], D_0054C79C[0], a0 - 1);
    }
    D_0054C89C[0] = 0;
}

extern void _ipuSetMPEG1(int a0);
extern int D_0054C758[];
extern int D_0054CD78[];

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _clearOnce);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _clearEach);

extern int D_00628EC8_alias[] __asm__("D_00628EC8");
extern void printf(void *a0, ...);

void func_0024E8E0(int a0) {
    printf(D_00628EC8_alias, a0);
}

extern void sprintf(void *a0, int a1, ...);
extern void _Error(void *a0);

void _Error1(int a0, int a1) {
    char buf[0x100];
    sprintf(buf, a0, a1);
    _Error(buf);
}

void _Error(void *a0)
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
                _dispatchMpegCallback((int)p, local);
                return;
            }
        }
    }
    func_0024E8E0(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sendDataToIPU);

int _RefImageInit(int *a0, int a1, int a2) {
    a0[0x4 / 4] = a1;
    a0[0x8 / 4] = a2;
    a0[0xC / 4] = a1 >> 4;
    a0[0x10 / 4] = a2 >> 4;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sequenceHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024EBC8);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _initRefImages);

extern void *D_0054C764[];
extern void *_dispatchMpegCallback(void *a0, void *a1);
extern void _waitIpuIdle(void);
extern void _sendIpuCommand(unsigned int a0);

void _setDefaultQM(void *a0, int a1) {
    int local[8];
    local[0] = 2;
    _dispatchMpegCallback(D_0054C764[0], local);
    _waitIpuIdle();
    *(volatile int *)0x10002000 = 0;
    _waitIpuIdle();
    *(volatile int *)0x1000B410 = a1 & 0x0FFFFFFF;
    *(volatile int *)0x1000B420 = 4;
    *(volatile int *)0x1000B400 = 0x101;
    _sendIpuCommand((unsigned int)a0);
    _waitIpuIdle();
    local[0] = 3;
    _dispatchMpegCallback(D_0054C764[0], local);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sequenceExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sequenceDisplayExtension);

extern void _Error(void *a0);
extern int D_00628F38[];

void func_0024F2C0(void) {
    _Error(D_00628F38);
}

extern int D_00628F68[];
extern int D_00628F80[];
extern int D_00628FB8[];

void func_0024F2D0(void) {
    _Error(D_00628F68);
}

void func_0024F2E0(void) {
    _Error(D_00628F80);
}

void func_0024F2F0(void) {
    _Error(D_00628FB8);
}

extern void sceIpuStopDMA(void *a0);
extern void sceIpuRestartDMA(void *a0);

void func_0024F300(int **a0) {
    sceIpuStopDMA((char *)a0[0x10] + 0x4C);
}

void func_0024F310(int **a0) {
    sceIpuRestartDMA((char *)a0[0x10] + 0x4C);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F320);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0024F658);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _getRef0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _doMC);

/* _rix_000: handwritten MMI unaligned-copy/unpack loop — qfsrv funnel shift
 * (shift amount from mtsab) then pextlb/pextub byte-unpack, double-buffered.
 * In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global _rix_000\n"
    "    .type _rix_000, @function\n"
    "    .align 3\n"
    "_rix_000:\n"
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
    "    .size _rix_000, . - _rix_000\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_000: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_000\n"
    ".type _ri0_000, @function\n"
    "    .align 3\n"
    "_ri0_000:\n"
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
    ".size _ri0_000, . - _ri0_000\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_001: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _rix_001\n"
    ".type _rix_001, @function\n"
    "    .align 3\n"
    "_rix_001:\n"
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
    ".size _rix_001, . - _rix_001\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_001: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_001\n"
    ".type _ri0_001, @function\n"
    "    .align 3\n"
    "_ri0_001:\n"
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
    ".size _ri0_001, . - _ri0_001\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_010: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _rix_010\n"
    ".type _rix_010, @function\n"
    "    .align 3\n"
    "_rix_010:\n"
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
    ".size _rix_010, . - _rix_010\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_010: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_010\n"
    ".type _ri0_010, @function\n"
    "    .align 3\n"
    "_ri0_010:\n"
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
    ".size _ri0_010, . - _ri0_010\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_011: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _rix_011\n"
    ".type _rix_011, @function\n"
    "    .align 3\n"
    "_rix_011:\n"
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
    ".size _rix_011, . - _rix_011\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_011: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_011\n"
    ".type _ri0_011, @function\n"
    "    .align 3\n"
    "_ri0_011:\n"
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
    ".size _ri0_011, . - _ri0_011\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_100: handwritten MMI averaging loop — qfsrv funnel shift + pextlb/pextub
 * byte-unpack, paddh accumulate, then signed round-half (pcgth/psrlh/paddh/psrlh) to
 * divide by 2. Double-buffered. In-file handwritten asm per maintainer exception. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global _rix_100\n"
    "    .type _rix_100, @function\n"
    "    .align 3\n"
    "_rix_100:\n"
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
    "    .size _rix_100, . - _rix_100\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_100: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_100\n"
    ".type _ri0_100, @function\n"
    "    .align 3\n"
    "_ri0_100:\n"
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
    ".size _ri0_100, . - _ri0_100\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_101: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _rix_101\n"
    ".type _rix_101, @function\n"
    "    .align 3\n"
    "_rix_101:\n"
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
    ".size _rix_101, . - _rix_101\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_101: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_101\n"
    ".type _ri0_101, @function\n"
    "    .align 3\n"
    "_ri0_101:\n"
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
    ".size _ri0_101, . - _ri0_101\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_110: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _rix_110\n"
    ".type _rix_110, @function\n"
    "    .align 3\n"
    "_rix_110:\n"
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
    ".size _rix_110, . - _rix_110\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_110: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_110\n"
    ".type _ri0_110, @function\n"
    "    .align 3\n"
    "_ri0_110:\n"
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
    ".size _ri0_110, . - _ri0_110\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _rix_111: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _rix_111\n"
    ".type _rix_111, @function\n"
    "    .align 3\n"
    "_rix_111:\n"
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
    ".size _rix_111, . - _rix_111\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* _ri0_111: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _ri0_111\n"
    ".type _ri0_111, @function\n"
    "    .align 3\n"
    "_ri0_111:\n"
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
    ".size _ri0_111, . - _ri0_111\n"
    "    .set reorder\n"
    "    .set at\n"
);

void _copyAddRefImage(void *a0, void *a1, void *a2) {
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

void _ipuSetMPEG1(int a0) {
    volatile int *reg = (volatile int *)0x10002010;
    *reg = (*reg & 0xFF7FFFFF) | (a0 << 23);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _waitBdecOut);

extern int _ipuVdec(int a0);

int _dmVector(void) {
    return _ipuVdec(3);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dualPrimeVector);

extern int _peepBit(int a0);
extern void _flushBuf(int a0);
extern int D_0054C888[];
extern int D_0054D030[];
extern int D_006290B0[];

int _mbAddressIncrement(void) {
    int cont;
    int sum;
    unsigned int v;

    sum = 0;
    do {
        v = _ipuVdec(0);
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
                int r = _peepBit(0xB);
                if ((D_0054D030[0] != 0) && (r == 0xF)) {
                    _flushBuf(0xB);
                    cont = 1;
                } else {
                    _Error1((int) D_006290B0, v);
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


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureData0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sliceA0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_002517A0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _skipMB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decMB0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decode_motion_vector);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _motionVectors);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _motionVector);

extern int D_0054D088[];
extern int D_0054C7A4[];

void _sendIpuCommand(unsigned int a0) {
    *(volatile unsigned int *)0x10002000 = a0;
    D_0054C7A4[0] = D_0054D088[a0 >> 28];
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _waitIpuIdle);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _waitIpuIdle64);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ipuVdec);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _peepBit);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _flushBuf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _nextBit);

extern void _waitIpuIdle(void);
void _nextStartCode(void) {
    int v;
    _waitIpuIdle();
    v = (-(*(volatile int *)0x10002020 & 7)) & 7;
    if (v) _flushBuf(v);
    while (_peepBit(0x18) != 1) {
        _flushBuf(8);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sliceB);

/* m2c scaffold from asm/aug6/nonmatchings/common/src/PObj/_nextHeader.s (target mipsel-gcc-c, context-free).
 * NOT a match — reshape into a goto-CFG-mirror + recover intent (see decomp-match skill). */
extern int _nextBit(int a0);
extern void _sequenceHeader(void);
extern void _pictureHeader(void);
extern void _groupOfPicturesHeader(void);
extern int D_0054C8FC[];
extern long long D_0054D008[];
extern long long D_0054D010[];

int _nextHeader(void) {
    struct { int f0; long long f8; long long f10; } local;

    while (1) {
        _nextStartCode();
        switch ((unsigned int) _nextBit(0x20)) {
        case 0x1B3:
            _sequenceHeader();
            break;
        case 0x1B8:
            _groupOfPicturesHeader();
            break;
        case 0x100:
            _pictureHeader();
            local.f0 = 5;
            local.f8 = -1;
            local.f10 = -1;
            _dispatchMpegCallback(D_0054C764[0], &local);
            D_0054D008[0] = local.f8;
            D_0054D010[0] = local.f10;
            return D_0054C8FC[0];
        case 0x1B7:
            return 0;
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _extensionAndUserData);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureCodingExtension);

extern void _flushBuf(int a0);
extern int _nextBit(int a0);

void _extrainfo(void) {
    while (_nextBit(1)) {
        _flushBuf(8);
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00252FC0);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _groupOfPicturesHeader);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _quantMatrixExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pictureDisplayExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _copyrightExtension);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _decPicture);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _outputFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _updateRefImage);

extern char D_00629258[];

int _isOutSizeOK(char *p) {
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
        sprintf(buf, (int)D_00629258, *(int *)(p + 0x4), *(int *)(p + 0x8));
        _Error(buf);
    }
    return flag;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _cpr8);

extern int D_0054C884[];
extern int D_0054D000[];

int _markOutput(void) {
    int *q = *(int **)((char *)D_0054C764[0] + 0x40);
    if (q[2] != 2) {
        int v = D_0054C884[0];
        q[2] = 2;
        q[0x2B] = v;
    }
    D_0054D000[0] = 1;
    return 1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _getPtsDtsFlags);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dispRefImage);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dispRefImageField);

extern void _sendIpuCommand(unsigned int a0);
extern void *_dispatchMpegCallback(void *a0, void *a1);
extern void *D_0054C764[];

void _doCSC(int a0, int a1) {
    int local[8];
    while (*(volatile int *)0x10002010 < 0) {
    }
    *(volatile int *)0x1000B010 = a0 & 0x0FFFFFFF;
    *(volatile int *)0x1000B020 = a1 << 6;
    *(volatile int *)0x1000B000 = 0x100;
    _sendIpuCommand(a1 | 0x70000000);
    local[0] = 4;
    _dispatchMpegCallback(D_0054C764[0], local);
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _doCSC2);

extern int D_0071365C[];
extern int D_00713660[];
extern int D_00713664[];

int _ch4dma(void) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _csc_storeRefImage);

extern void _sysbitFlush(int *a0, int a1);

void _sysbitInit(int *a0, int a1, int a2, int a3) {
    a0[2] = a1;
    a0[3] = a1;
    *(long long *)a0 = 0;
    a0[4] = 0;
    *(long long *)(a0 + 6) = 0;
    a0[8] = a2;
    a0[9] = a2 + a3;
    a0[0xA] = a3;
    _sysbitFlush(a0, 0);
}

int _sysbitNext(void *a0, int a1) {
    unsigned long long v = *(unsigned long long *)a0;
    return v >> (64 - a1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitFlush);

int _sysbitGet(int *self, int a1)
{
    int ret = _sysbitNext(self, a1);
    _sysbitFlush(self, a1);
    return ret;
}

int _sysbitMarker(int *self)
{
    int ret = _sysbitNext(self, 1);
    _sysbitFlush(self, 1);
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sysbitJump);

int _sysbitPtr(int *a0, int a1) {
    int v = a0[2] + (a1 >> 3);
    if ((unsigned int)v >= (unsigned int)a0[9]) {
        v -= a0[10];
    }
    return v;
}

void func_002549B8(int *a0) {
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B000 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}

void func_00254A20(int *a0) {
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}

extern void func_00254A20(int *a0);
extern void func_002549B8(int *a0);

void sceIpuStopDMA(void *a0) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuRestartDMA);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuSync);

void func_00254D28(int *a0) {
    DIntr(a0);
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 | 0x10000;
    *(volatile int *)0x1000B400 = (int)a0;
    *(volatile int *)0x1000F590 = *(volatile int *)0x1000F520 & 0xFFFEFFFF;
    EIntr();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sceIpuInit);

extern unsigned char D_00713C80[];

void *_SgGetSlotContext(int a0) {
    return &D_00713C80[a0 * 0x58];
}

extern unsigned char D_00714D00[];

void *_SgGetSeqContext(int a0) {
    return &D_00714D00[a0 * 0x54];
}

extern int D_00715CC0[];

void *func_00254FF8(void) {
    return D_00715CC0;
}

extern unsigned char D_00713680[];

void *_SgGetVabContext(int a0) {
    return &D_00713680[a0 * 0xC];
}

extern int D_00717F80[];

void _SgSetSeVolValue(int a0, int a1) {
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

void *_SgGetPacketCntext(int a0, int a1) {
    unsigned char *p = &D_00715D40[a1 * 0x10];
    return (void *)(a0 * 0x1000 + (int)p);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgCalledTickProc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSetPkAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeMain);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgBgmMain);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSetRealtimeTickProc);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSetRealtimeVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgTableEnvAdd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqKeyOnSlot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeKeyOnSlot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeKeyOff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqKeyOff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgIntoKeyOn);

extern void _SgSetPkAdd(int a0, int a1, int a2, int a3);

int _SgPitchTableVag(int a0, int a1, int a2, int a3, int a4, int a5, int a6) {
    _SgSetPkAdd(4, a0, (a1 << 24) | (a2 << 16) | ((a3 & 0xFF) << 8) | a4,
                  (a5 << 24) | a6);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqSeVolume);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgPan);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgEndSeq);

extern void *func_00254FF8(void);

void _SgTempoChange(int *a0) {
    unsigned char *p = (unsigned char *)(a0[2] + a0[1]);
    void *q = func_00254FF8();
    *(unsigned short *)((char *)a0 + 0x1E) = p[2] | (p[3] << 8);
    *(int *)((char *)a0 + 0x10) =
        ((((int)*(unsigned short *)((char *)a0 + 0x20)
           * *(unsigned short *)((char *)a0 + 0x1E)) << 12)
         / *(unsigned short *)((char *)q + 0x3A)) / 0x3C;
    a0[1] += 4;
}

void _SgProgChange(int *a0)
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContMod);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContModLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContPolta);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContVol);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContPan);

extern void *_SgGetSlotContext(int a0);
extern void *func_00254FF8(void);
extern void *func_00255060(void);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContDump);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContSeLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContParam);

void _SgContLoopCount(void *a0) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgContLoop);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgBendForm);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgDeltaTime);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgSeqSeRrEnd);

int _SgfadeParam(int a0, int a1, int a2, int a3) {
    return ((a0 & 0xFF) + ((a1 & 0xFF) - (a0 & 0xFF)) * (a3 & 0xFF) / (a2 & 0xFF)) & 0xFF;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgInit);

extern char D_007181C0[];

int _SgSndn2Remote(int a0, int a1, int a2, int a3, int a4, int a5) {
    return sceSifCallRpc(D_007181C0, a0, a1, a2, a4, a3, a5, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSndn2RemoteInit);

extern int sceSifCheckStatRpc(char *p);
extern char D_007181C0[];

int SgSndn2RemoteSync(void)
{
    int ret = 0;
    int *p = func_00254FF8();
    if (p[0x44 / 4] != 0) {
        ret = sceSifCheckStatRpc(D_007181C0);
    }
    return ret;
}

extern void _SgInit(int a0);

void func_00258948(void) {
    _SgInit(0);
}

void func_00258950(void) {
    _SgInit(1);
}

void SgQuit(void)
{
    int i;
    for (i = 0; i < 2; i++) {
        _SgSetPkAdd(0xB, i, 0xFFFFFF, 0);
        _SgSetPkAdd(0x28, i, 0, 0);
    }
    _SgSetPkAdd(0x1F, 0, 0, 0);
}

extern void _SgCalledTickProc(void);

void SgCalledTickProc(void) {
    void *r = func_00254FF8();
    if (*(int *)((char *)r + 0x44)) {
        _SgCalledTickProc();
    }
}

extern void _SgSetPkAdd(int a0, int a1, int a2, int a3);

void SgSetDigitalOutputMode(int a0) {
    _SgSetPkAdd(0x32, 0xA, a0, 0);
}

extern void _SgDmaCommon(int a0, int a1, void *a2, void *a3);

int SgDmaWrite(int a0, void *a1, void *a2) {
    _SgDmaCommon(0x20, a0, a1, a2);
    return 0;
}

extern void _SgDmaCommon(int a0, int a1, void *a2, void *a3);

int SgDmaRead(void *a0, int a1, void *a2) {
    _SgDmaCommon(0x21, a1, a0, a2);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _SgDmaCommon);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetDmaTransferStatus);

extern int SgVabOpenFakeBody(int *a0, int a1);

int SgVabOpen(int a0, int *a1, int a2) {
    int r;
    r = SgVabOpenFakeBody(a1, a2);
    if (r != -1) {
        SgDmaWrite(a0, (void *)a2, (void *)a1[1]);
    }
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgVabOpenFakeBody);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgVabClose);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmOpen);

int SgBgmClose(int a0) {
    volatile int *p;
    int ret = -1;
    if ((unsigned int)a0 < 0x30) {
        p = (volatile int *)_SgGetSeqContext(a0);
        p[0] |= 0x2000;
        if ((p[0] & 3) == 1) {
            memset((char *)p + 4, 0, 0x50);
            p[0] = 0;
            ret = 0;
        }
        p[0] &= 0xFFFFDFFF;
    }
    return ret;
}

void SgSetReverbEndAddr(int a0, int a1) {
    _SgSetPkAdd(0x14, a0, a1, 0);
}

void SgSetReverbType(int a0, int a1) {
    _SgSetPkAdd(0x15, a0, a1, 0);
}

void SgSetReverbDepth(int a0, int a1, int a2) {
    _SgSetPkAdd(0x16, a0, a1, a2);
}

void SgSetReverbDelaytime(int a0, int a1) {
    _SgSetPkAdd(0x17, a0, a1, 0);
}

void SgSetReverbFeedback(int a0, int a1) {
    _SgSetPkAdd(0x18, a0, a1, 0);
}

void SgSetOutputMode(int a0) {
    void *r = func_00254FF8();
    *(short *)((char *)r + 0x38) = a0;
}

void SgSetTickMode(int a0) {
    void *r = func_00254FF8();
    *(short *)((char *)r + 0x3A) = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetSlotStatus);

void SgSetMasterVol(int a0, int a1, int a2) {
    _SgSetPkAdd(0x28, a0, a1, a2);
}

extern void *_SgGetSeqContext(int a0);

int SgSetBgmVol(unsigned int a0, int a1, int a2) {
    int ret = -1;
    if (a0 < 0x30 && a1 >= 0 && a1 < 0x80) {
        int *p = (int *)_SgGetSeqContext(a0);
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

int SgSetSeMasterVol(int a0, int a1) {
    int ret = -1;
    if ((unsigned int)(a0 - 1) < 0x7F && a1 >= 0) {
        if (a1 < 0x80) {
            int *p = (int *)_SgGetVabContext(a0);
            if (p[2] != 0) {
                ret = func_00255038(a0) & 0x7F;
                _SgSetSeVolValue(a0, a1 | 0x80);
            }
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgBgmStop);

extern void *_SgGetSeqContext(int a0);
extern void *func_00254FF8(void);

void SgSetBgmTempo(unsigned int a0, int a1) {
    if (a0 < 0x30 && a1 >= 0 && a1 < 0x3C0) {
        int *p = (int *)_SgGetSeqContext(a0);
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

int SgGetBgmTempo(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        void *r = _SgGetSeqContext(a0);
        ret = *(unsigned short *)((char *)r + 0x1E);
    }
    return ret;
}

int SgGetBgmStatus(int a0) {
    volatile int *p;
    int ret = -1;
    if ((unsigned int)a0 < 0x30) {
        p = (volatile int *)_SgGetSeqContext(a0);
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetBgmChStatus);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSetBgmPanpot);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSePlay);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgSeStop);

extern void *_SgGetSeqContext(int a0);
extern void SgSeStop(int a0);

void SgSeStopAll(int a0) {
    int i;
    volatile int *p = (volatile int *)_SgGetSeqContext(0);
    for (i = 0; i < 0x30; i++) {
        p[0] |= 0x2000;
        if ((p[0] & 5) == 4) {
            SgSeStop(i | (a0 << 15));
        }
        p[0] &= 0xFFFFDFFF;
        p = (volatile int *)((char *)p + 0x54);
    }
}

extern void *_SgGetSeqContext(int a0);

void SgSetSeVolDirect(unsigned int a0, int a1, int a2) {
    if (a0 < 0x30 &&
        a1 >= -0x1000 && a1 < 0x1001 &&
        a2 >= -0x1000 && a2 < 0x1001) {
        int *p = (int *)_SgGetSeqContext(a0);
        p[0x44 / 4] = a1;
        p[0x48 / 4] = a2;
        *(volatile int *)p |= 0x2000;
        *(volatile int *)p |= 0x800;
        *(volatile int *)p &= 0xFFFFDFFF;
    }
}

void SgSetSePitchDirect(unsigned int a0, int a1) {
    volatile int *p;
    int v, v2, v3;
    if (a0 >= 0x30) return;
    if (a1 < 0) return;
    if (a1 >= 0x4000) return;
    p = (volatile int *)_SgGetSeqContext(a0);
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgGetSpuSlotMalloc);

int SgSetSpuSlotFree(unsigned int a0) {
    if (a0 < 0x30) {
        unsigned char *p = (unsigned char *)_SgGetSlotContext(a0);
        if (p[0x51] == 3) {
            p[0x51] = 0;
        }
    }
    return -1;
}

void SgStAdpcmInit(void) {
    _SgSetPkAdd(0x3C, 0, 0, 0);
}

void SgStAdpcmQuit(void) {
    _SgSetPkAdd(0x3D, 0, 0, 0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", SgStAdpcmOpen);

int SgStAdpcmClose(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x30) {
        _SgSetPkAdd(0x3F, a0, 0, 0);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmChannelVolume(unsigned long long a0, unsigned int a1, int a2)
{
    int ret = -1;
    if (a1 < 0x4000 && a2 >= 0 && a2 < 0x4000 && (a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x40, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), (a1 << 16) | a2);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmChannelPitch(unsigned long long a0, int a1)
{
    int ret = -1;
    if (((a0 & 0xFF000000) == 0) && (a1 >= 0) && (a1 <= 0x2EE00)) {
        _SgSetPkAdd(0x41, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), a1);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmPlay(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x42, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}

int SgStAdpcmStop(unsigned long long a0)
{
    int ret = -1;
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x43, (int)(a0 & 0xFFFFFF), (int)((a0 >> 24) & 0xFFFFFF), 0);
        ret = 0;
    }
    return ret;
}

extern int func_00255070(void);

int SgStAdpcmIopReadAddr(int a0) {
    int ret = 0;
    if ((unsigned int)a0 < 0x30) {
        int base = func_00255070();
        ret = *(int *)(base + (a0 % 0x18) * 4 + (a0 / 0x18) * 0x60 + 0xC0);
    }
    return ret;
}

void SgStPcmInit(void) {
    _SgSetPkAdd(0x46, 0, 0, 0);
}

void SgStPcmQuit(void) {
    _SgSetPkAdd(0x47, 0, 0, 0);
}

int SgStPcmOpen(int *a0) {
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
        _SgSetPkAdd(0x48, (v << 24) | v2, n1, n2);
        ret = 0;
    }
    done:
    return ret;
}

int SgStPcmClose(unsigned int a0) {
    int ret = -1;
    if (a0 < 0x10) {
        _SgSetPkAdd(0x49, a0, 0, 0);
        ret = 0;
    }
    return ret;
}

void SgStPcmSetEffect(int a0) {
    _SgSetPkAdd(0x4E, a0, 0, 0);
}

int SgStPcmPlay(unsigned long long a0) {
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x4B, (int)a0, 0, 0);
    }
    return 0;
}

int SgStPcmStop(unsigned long long a0) {
    if ((a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x4C, (int)a0, 0, 0);
    }
    return 0;
}

int SgStPcmLseek(unsigned int a0, unsigned int a1)
{
    int ret = -1;
    if (a0 < 0x10) {
        if (a1 <= 0x1FFFFF) {
            _SgSetPkAdd(0x4D, (int)a0, (int)a1, 0);
            ret = 0;
        }
    }
    return ret;
}

void SgStPcmVolume(unsigned long long a0, unsigned int a1, int a2)
{
    if (a1 <= 0x7FFF && a2 >= 0 && a2 <= 0x7FFF && (a0 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x4A, (int)a0, a1, a2);
    }
}

int SgStPcmIopReadAddr(unsigned int a0)
{
    int ret = 0;
    if (a0 < 0x10) {
        int *p = func_00255070();
        ret = *(int *)((char *)p + (a0 << 2) + 0x180);
    }
    return ret;
}

extern void _SgSetPkAdd(int a0, int a1, int a2, int a3);

int SgStPcmBufMode(int a0, long a1, int a2) {
    int ret;
    ret = -1;
    if ((unsigned int)a0 < 2 && (unsigned int)a2 <= 0x1FFFFF && (a1 & 0xFF000000) == 0) {
        _SgSetPkAdd(0x4F, a1, a2, a0);
        ret = 0;
    }
    return ret;
}

#include "math_private.h"

extern float __kernel_sinf(float x, float y, int iy);
extern float __kernel_cosf(float x, float y);
extern int __ieee754_rem_pio2f(float x, float *y);

float sinf(float x) {
    float y[2];
    int n;
    int ix;

    GET_FLOAT_WORD(ix, x);
    ix &= 0x7fffffff;

    if (ix <= 0x3f490fd8) {
        return __kernel_sinf(x, 0.0f, 0);
    } else if (ix >= 0x7f800000) {
        return x - x;
    } else {
        n = __ieee754_rem_pio2f(x, y);
        switch (n & 3) {
        case 0:
            return __kernel_sinf(y[0], y[1], 1);
        case 1:
            return __kernel_cosf(y[0], y[1]);
        case 2:
            return -__kernel_sinf(y[0], y[1], 1);
        default:
            return -__kernel_cosf(y[0], y[1]);
        }
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A768);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025A868);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", atan2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fmodf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_acosf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_asinf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_atan2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_fmodf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_rem_pio2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __ieee754_sqrtf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __kernel_cosf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __kernel_rem_pio2f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __kernel_sinf);

extern void dpcmp(long a0, long a1);

int matherr(void *a0) {
    long p = *(long *)((char *)a0 + 8);
    dpcmp(p, p);
    return 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", atanf);

/* fabsf(x) via the standard IEEE-754 bit twiddle: clear the sign bit. */
float fabsf(float a0) {
    unsigned int ix;
    GET_FLOAT_WORD(ix, a0);
    SET_FLOAT_WORD(a0, ix & 0x7fffffff);
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", floorf);

/* isnanf(x) via the standard IEEE-754 bit test: NaN iff |x| bits > 0x7F800000 (+inf). */
int isnanf(float x) {
    int hx;
    GET_FLOAT_WORD(hx, x);
    hx &= 0x7fffffff;
    hx = 0x7f800000 - hx;
    return (unsigned)hx >> 31;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", scalbnf);

/* copysignf(x, y): magnitude of x with the sign of y, via IEEE-754 bit twiddle. */
float copysignf(float a0, float a1) {
    unsigned int ix, iy;
    GET_FLOAT_WORD(ix, a0);
    GET_FLOAT_WORD(iy, a1);
    SET_FLOAT_WORD(a0, (ix & 0x7fffffff) | (iy & 0x80000000));
    return a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025CF30);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __do_global_ctors);

/* D_007181E8 is a .bss global splat left as a raw lui/lw (no name); declared in
 * symbol_addrs + defined for the linker in undefined_funcs_extra.aug6.txt so the
 * %hi/%lo base reuses one reg like the ROM. Byte-identical in the link
 * (ninja verify_elf OK); match_diff shows a residual only because the reference
 * .s keeps the raw value rather than %hi(D_007181E8). */
extern int D_007181E8[];
extern void __do_global_ctors(void);
void __main(void) {
    if (D_007181E8[0] == 0) {
        D_007181E8[0] = 1;
        __do_global_ctors();
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __divdi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __fixunsdfdi);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __floatdidf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __moddi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __muldi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __udivdi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __umoddi3);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __pack_d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __unpack_d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _fpadd_parts);

extern void *_fpadd_parts(void *a, void *b, void *c);
extern void __pack_d(void *s);

void dpadd(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    __pack_d(_fpadd_parts(&x, &y, &z));
}

void dpsub(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y, z;
    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    y.b ^= 1;
    __pack_d(_fpadd_parts(&x, &y, &z));
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpmul);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dpdiv);

typedef struct { unsigned int type; int f4; int f8; int fC; unsigned long long f10; } PCmpV2;

int __fpcmp_parts_d(PCmpV2 *a, PCmpV2 *b) {
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


extern void __unpack_d(void *in, void *out);
extern int __fpcmp_parts_d(PCmpV2 *a, PCmpV2 *b);

void dpcmp(long a0, long a1) {
    struct { int a, b, c, pad; long long d; } x, y;
    __unpack_d(&a0, &x);
    __unpack_d(&a1, &y);
    __fpcmp_parts_d(&x, &y);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", litodp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dptoli);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dptoul);

extern void __unpack_d(void *in, void *out);
extern void __pack_d(void *s);

void __negdf2(long long a0) {
    struct { int a, b, c, pad; long long d; } s;
    long long t = a0;
    __unpack_d(&t, &s);
    s.b = (s.b == 0);
    __pack_d(&s);
}

extern void __pack_d(void *s);

int __make_dp(int a0, int a1, int a2, long long a3) {
    struct { int a, b, c, pad; long long d; } s;
    s.a = a0;
    s.b = a1;
    s.c = a2;
    s.d = a3;
    __pack_d(&s);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", dptofp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __pack_f);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __unpack_f);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_0025F940);

int fpadd(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    __unpack_f(buf + 0x30, buf);
    __unpack_f(buf + 0x34, buf + 0x10);
    ret = func_0025F940(buf, buf + 0x10, buf + 0x20);
    return __pack_f(ret);
}

int fpsub(float a0, float a1) {
    char buf[0x40];
    int ret;
    *(float *)(buf + 0x30) = a0;
    *(float *)(buf + 0x34) = a1;
    __unpack_f(buf + 0x30, buf);
    __unpack_f(buf + 0x34, buf + 0x10);
    *(int *)(buf + 0x14) ^= 1;
    ret = func_0025F940(buf, buf + 0x10, buf + 0x20);
    return __pack_f(ret);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpmul);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fpdiv);

typedef struct { unsigned int type; int f4; int f8; int fC; } PCmpV;

int __fpcmp_parts_f(PCmpV *a, PCmpV *b) {
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


extern void __unpack_f(void *in, void *out);
extern int __fpcmp_parts_f(PCmpV *a, PCmpV *b);

int fpcmp(float a0, float a1) {
    char buf[0x30];
    *(float *)(buf + 0x20) = a0;
    *(float *)(buf + 0x24) = a1;
    __unpack_f(buf + 0x20, buf);
    __unpack_f(buf + 0x24, buf + 0x10);
    return __fpcmp_parts_f(buf, buf + 0x10);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sitofp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fptosi);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fptoui);

extern void __unpack_f(void *a0, void *a1);
extern int __pack_f(void *s);

int __negsf2(float f12)
{
    int o[4];
    float in[4];
    in[0] = f12;
    __unpack_f(in, o);
    o[1] = (o[1] == 0);
    return __pack_f(o);
}

void __make_fp(int a0, int a1, int a2, int a3) {
    int buf[4];
    buf[0] = a0;
    buf[1] = a1;
    buf[2] = a2;
    buf[3] = a3;
    __pack_f(buf);
}

int fptodp(float f12)
{
    int local0[4];
    float local1[4];
    long long a3_val;
    local1[0] = f12;
    __unpack_f(local1, local0);
    a3_val = (long long)(unsigned int)local0[3] << 32;
    return __make_dp(local0[0], local0[1], local0[2],
                         (long long)((unsigned long long)a3_val >> 2));
}

extern int D_0054D504[];
extern char D_00629E08[];
extern void fiprintf(int a0, int a1, ...);
extern void func_00265298(void);

void __assert(int a0, int a1, int a2) {
    fiprintf(*(int *)(D_0054D504[0] + 0xC), (int)D_00629E08, a2, a0, a1);
    func_00265298();
}

extern long long func_00261E80(void *a0, int a1, int a2);

int atoi(void *a0) {
    return (int)func_00261E80(a0, 0, 0xA);
}

extern int D_0054D504[];

int func_002603E0(void) {
    return D_0054D504[0];
}

extern void func_00261FB8(int a0, int a1, void *args);

/* printf-style forwarder: va_start points at the homed vararg GP regs
 * (the 6 slots, 6*8 = 48 bytes, just below __builtin_next_arg). */
void fiprintf(int a0, int a1, ...) {
    char *ap = (char *)__builtin_next_arg(a1) - 48;
    func_00261FB8(a0, a1, ap);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memcpy);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memset);

extern int func_00262D78(int *self, int subj, int b, void *args);

int _printf_r(int *self, int b, ...)
{
    void *args = (char *)__builtin_next_arg(b) - 0x30;
    return func_00262D78(self, self[2], b, args);
}

void printf(void *a0, ...) {
    void *args = (char *)__builtin_next_arg(a0) - 0x38;
    int s = D_0054D504[0];
    *(int *)(*(int *)(s + 8) + 0x54) = s;
    func_00262D00(*(int *)(s + 8), a0, args);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", qsort);

extern void *D_0054D504_alias[] __asm__("D_0054D504");

void srand(int a0) {
    char *p = (char *)D_0054D504_alias[0];
    *(int *)(p + 0x58) = a0;
}

int rand(void) {
    char *p = (char *)D_0054D504_alias[0];
    int s = *(int *)(p + 0x58) * 0x41C64E6D + 0x3039;
    *(int *)(p + 0x58) = s;
    return s & 0x7fffffff;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _sprintf_r);

void sprintf(void *a0, int a1, ...) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", sscanf);

/* strcat: hand-vectorized string-end finder — a 128-bit MMI zero-byte
 * scan (lq/pcpyld/psubb/pnor/pand/pcpyud haszero) for 16-aligned input, a 64-bit
 * (ld/dsubu/nor/and) scan for 8-aligned, and a trailing byte scan, then
 * strcpy(end, a1) and returns the original pointer. In-file handwritten
 * asm per maintainer exception: the MMI byte-parallel ops have no C/intrinsic
 * form and ee-gcc spills vector_size types — matched MMI siblings in this TU
 * (e.g. sceGsResetPath) use the same whole-function asm pattern. */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    "    .global strcat\n"
    "    .type strcat, @function\n"
    "    .align 3\n"
    "strcat:\n"
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
    "    jal    strcpy\n"
    "    nop\n"
    "    daddu  $2, $16, $0\n"
    "    lq     $31, 0x10($29)\n"
    "    lq     $16, 0x0($29)\n"
    "    jr     $31\n"
    "    addiu  $29, $29, 0x20\n"
    "    .size strcat, . - strcat\n"
    "    .set reorder\n"
    "    .set at\n"
);


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strcpy);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strlen);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strncmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strncpy);

char *strrchr(char *s, char c) {
    char *last = 0;
    while (*s != 0) {
        if (*s == c) {
            last = s;
        }
        s++;
    }
    return (*s == c) ? s : last;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", strstr);

extern int D_0054D504[];
extern int func_00261BA8(int a0, int a1, int a2);

int strtok(int a0, int a1) {
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
    ret = __sfvwrite(a0, a1);
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
    ret = __sfvwrite(a0, a1);
    a1[2] = 0;
    a1[1] = 0;
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262C48);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D00);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", func_00262D78);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", cvt);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", exponent);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __svfscanf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sccl);

extern int D_0054D504[];

void vsprintf(void *out, void *a1, void *a2) {
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
extern void __sinit(char *a0);
extern void _free_r(P54 *p);
extern void __smakebuf(PObj265 *s);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __swsetup);



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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", quorem);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _dtoa_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", fflush);

extern int __sread();
extern long __swrite(void *a0, int a1, int a2);
extern void __sseek(void);
extern int __sclose(void *a0);

void std(char *a0, short a1, short a2, int a3) {
    *(int *)(a0 + 0x54) = a3;
    *(short *)(a0 + 0xC) = a1;
    *(short *)(a0 + 0xE) = a2;
    *(void **)(a0 + 0x20) = (void *)__sread;
    *(void **)(a0 + 0x24) = (void *)__swrite;
    *(void **)(a0 + 0x28) = (void *)__sseek;
    *(void **)(a0 + 0x2C) = (void *)__sclose;
    *(int *)(a0 + 0x4) = 0;
    *(int *)(a0 + 0x8) = 0;
    *(int *)(a0 + 0x10) = 0;
    *(int *)(a0 + 0x18) = 0;
    *(char **)(a0 + 0x1C) = a0;
    *(int *)(a0 + 0x0) = 0;
}

extern void *_malloc_r(void *a0, int a1);

void *__sfmoreglue(void *a0, int a1) {
    int sz;
    char *p;
    char *body;
    sz = a1 * 0x58;
    p = (char *)_malloc_r(a0, sz + 0xC);
    if (p == 0) {
        return 0;
    }
    body = p + 0xC;
    *(int *)(p + 0x4) = a1;
    *(int *)(p + 0x0) = 0;
    *(int *)(p + 0x8) = (int)body;
    memset(body, 0, sz);
    return p;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sfp);

extern int fflush(void);
extern void _fwalk(int a0, void *a1);

void func_00266970(int a0) {
    _fwalk(a0, fflush);
}

void func_00266980(void) {
    func_00266970(D_0054D504[0]);
}

extern void func_00266970(int a0);

void __sinit(char *a0) {
    char *p = a0 + 0x1E4;
    *(void **)(a0 + 0x3C) = (void *)func_00266970;
    *(int *)(a0 + 0x38) = 1;
    std(p, 4, 0, (int)a0);
    std(a0 + 0x23C, 9, 1, (int)a0);
    std(a0 + 0x294, 0xA, 2, (int)a0);
    *(char **)(a0 + 0x1E0) = p;
    *(int *)(a0 + 0x1DC) = 3;
    *(int *)(a0 + 0x1D8) = 0;
}

typedef struct {
    char *pos;   /* 0x0 */
    int len;     /* 0x4 */
} StreamBuf;

extern int memcpy(char *dst, char *src, int n);
extern int __srefill(StreamBuf *s);

int fread(char *dst, int size, int count, StreamBuf *s) {
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
            memcpy(p, s->pos, avail);
            total -= avail;
            p += avail;
            s->pos += avail;
            if (__srefill(s) != 0) {
                return (total_orig - total) / size;
            }
            avail = s->len;
        } while (avail < total);
    }
    memcpy(p, s->pos, total);
    s->len -= total;
    s->pos += total;
    return count;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _free_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _malloc_trim_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sfvwrite);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _fwalk);

extern int D_0062A858[];
extern int D_0062A848[];

int _setlocale_r(void *a0, int a1, int a2) {
    if (a2 == 0) goto no_check;
    if (strcmp(a2, D_0062A858) == 0) goto found;
    if (strcmp(a2, D_0062A848) != 0) return 0;
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

extern int _setlocale_r(void *a0, int a1, int a2);

int func_002674D8(int a0, int a1) {
    return _setlocale_r(D_0054D504_alias[0], a0, a1);
}

void *func_00267508(void) {
    return func_002674C8(D_0054D504[0]);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __smakebuf);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", malloc_extend_top);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _malloc_r);

int _mbtowc_r(int a0, int *a1, unsigned char *a2, int a3) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memchr);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", memmove);

void func_00268270(void) {
}

void func_00268278(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _Balloc);

void _Bfree(char *a0, int *a1) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _multadd);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _s2b);

int _hi0bits(unsigned int a0) {
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

int _lo0bits(int *p) {
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

extern int *_Balloc(void *a0, int a1);

void *_i2b(void *a0, int a1) {
    int *r = _Balloc(a0, 1);
    r[5] = a1;
    r[4] = 1;
    return r;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _multiply);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _pow5mult);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _lshift);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __mcmp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __mdiff);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ulp);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _b2d);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _d2b);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _ratio);

extern long dpmul(long a, long b);
extern long D_0062A870[];

long _mprec_log10(int n) {
    long acc = (long)0xFFC0 << 46;
    if (n < 0x18) {
        return D_0062A870[n];
    }
    while (n > 0) {
        acc = dpmul(acc, (long)0x8048 << 47);
        n--;
    }
    return acc;
}

int func_002692A0(void) {
    return fflush();
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __srefill);

int isinf(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    return 1 - (int)(((unsigned int)(hx | (-hx))) >> 31);
}

int isnan(long long x)
{
    int lx, hx;
    do { lx = (int)x; hx = (int)(x >> 32); } while (0);
    hx &= 0x7fffffff;
    hx |= ((unsigned int)(lx | (-lx))) >> 31;
    hx = 0x7ff00000 - hx;
    do { return ((unsigned int)hx) >> 31; } while (0);
}

extern int D_0062E170[];
extern unsigned int sbrk(int a0);

int _sbrk_r(int *self, int a1)
{
    unsigned int ret;
    D_0062E170[0] = 0;
    ret = sbrk(a1);
    if (ret == 0xFFFFFFFF) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _init_signal_r);

extern void *_init_signal_r(int a0);

unsigned int _signal_r(void *a0, int a1, int a2) {
    unsigned int *base;
    unsigned int old;
    if ((unsigned int)a1 >= 0x20) {
        *(int *)a0 = 0x16;
        return 0xFFFFFFFFU;
    }
    if (*(int *)((char *)a0 + 0x1D4) == 0) {
        if (_init_signal_r((int)a0) != 0) {
            return 0xFFFFFFFFU;
        }
    }
    base = *(unsigned int **)((char *)a0 + 0x1D4);
    old = base[a1];
    base[a1] = a2;
    return old;
}


INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _raise_r);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sigtramp_r);

extern int _raise_r(int a0, int a1);

int func_002697C0(int a0) {
    return _raise_r(D_0054D504[0], a0);
}

extern unsigned int _signal_r(void *a0, int a1, int a2);

int func_002697E8(int a0, int a1) {
    return _signal_r(D_0054D504_alias[0], a0, a1);
}

extern void *_init_signal_r(int a0);

void *func_00269818(void) {
    return _init_signal_r(D_0054D504[0]);
}

extern int __sigtramp_r(int a0, int a1);

int func_00269840(int a0) {
    return __sigtramp_r(D_0054D504[0], a0);
}

extern int D_0062E170[];

int func_00269868(int *self, int a1, int a2)
{
    int ret;
    D_0062E170[0] = 0;
    ret = kill(a1, a2);
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sread);

long __swrite(void *a0, int a1, int a2) {
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

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __sseek);

extern int _close_r(int *self, int a1);
int __sclose(void *a0) {
    return _close_r((int *)*(int *)((char *)a0 + 0x54), *(short *)((char *)a0 + 0xE));
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _strtod_r);

extern int _strtod_r(void *a0, int a1, int a2);

int func_0026A958(a0, a1)
int a0, a1;
{
    return _strtod_r(D_0054D504_alias[0], a0, a1);
}

extern int dptofp(int a0);

int strtodf(void) {
    return dptofp(func_0026A958());
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _strtoul_r);

extern long long _strtoul_r(void *a0, void *a1, int a2, int a3);

long long func_0026ABD0(void *a0, int a1, int a2) {
    return _strtoul_r((void *)D_0054D504[0], a0, a1, a2);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __submore);

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", ungetc);

extern int write(int a1, int a2, int a3);

int func_0026AE80(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0062E170[0] = 0;
    ret = write(a1, a2, a3);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _calloc_r);

int _close_r(int *self, int a1)
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
    ret = fstat(a1, a2);
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

extern int read(int a1, int a2, int a3);
extern int D_0062E170[];

int func_0026B0B8(int *self, int a1, int a2, int a3)
{
    int ret;
    D_0062E170[0] = 0;
    ret = read(a1, a2, a3);
    if (ret == -1) {
        if (D_0062E170[0] != 0) {
            self[0] = D_0062E170[0];
        }
    }
    return ret;
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", _realloc_r);

/* _sceSDC: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _sceSDC\n"
    ".type _sceSDC, @function\n"
    "    .align 3\n"
    "_sceSDC:\n"
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
    ".size _sceSDC, . - _sceSDC\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_0026B730: handwritten critical-section wrapper — reads CP0 Status ($12),
 * and if interrupts are enabled (bit 16) brackets the _sceSDC call with
 * DIntr (disable) / EIntr (enable, tail). Handwritten per
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
    "    jal   DIntr\n"
    "    nop\n"
    "1:\n"
    "    lui   $4, 0xFFFF\n"
    "    ori   $4, $4, 0xFFC0\n"
    "    and   $5, $17, $4\n"
    "    jal   _sceSDC\n"
    "    and   $4, $18, $4\n"
    "    beqz  $16, 2f\n"
    "    ld    $31, 0x30($29)\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    j     EIntr\n"
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

extern void _sceSDC(int a0, int a1);

void func_0026B7B0(int a0, int a1) {
    _sceSDC(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

/* _sceIDC: handwritten function (CP0/cache/TLB/MMI/VU0). In-file handwritten
 * asm per maintainer exception (C-inexpressible privileged/SIMD ops). */
__asm__(
    ".section .text\n"
    "    .set noat\n"
    "    .set noreorder\n"
    ".global _sceIDC\n"
    ".type _sceIDC, @function\n"
    "    .align 3\n"
    "_sceIDC:\n"
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
    ".size _sceIDC, . - _sceIDC\n"
    "    .set reorder\n"
    "    .set at\n"
);

/* func_0026B870: handwritten critical-section wrapper — reads CP0 Status ($12),
 * and if interrupts are enabled (bit 16) brackets the _sceIDC call with
 * DIntr (disable) / EIntr (enable, tail). Handwritten per
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
    "    jal   DIntr\n"
    "    nop\n"
    "1:\n"
    "    lui   $4, 0xFFFF\n"
    "    ori   $4, $4, 0xFFC0\n"
    "    and   $5, $17, $4\n"
    "    jal   _sceIDC\n"
    "    and   $4, $18, $4\n"
    "    beqz  $16, 2f\n"
    "    ld    $31, 0x30($29)\n"
    "    ld    $18, 0x20($29)\n"
    "    ld    $17, 0x10($29)\n"
    "    ld    $16, 0x0($29)\n"
    "    j     EIntr\n"
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

extern void _sceIDC(int a0, int a1);

void func_0026B8F0(int a0, int a1) {
    _sceIDC(a0 & 0xFFFFFFC0, a1 & 0xFFFFFFC0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/common/src/PObj", __fixdfdi);


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
