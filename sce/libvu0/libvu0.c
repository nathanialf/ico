/* Vendor SCE library run.  The archive attribution (libvu0.a) comes from
 * MAIN.MAP's symbol table.  The January link carried a different revision of
 * this archive, so its member spans do not tile this run: the per-member
 * partition is NOT verified, and this file is the whole run. */
#include "common.h"

/* VU0 / COP2 macro-mode opcodes, one instruction per __asm__ block.  This
   run's uses stand for a Sony-internal header this tree cannot name: MAIN.MAP
   attests archives and their members, never a header, so the definitions are
   kept here rather than shared with the game tree's copy in
   ico2/common/include/typedef.h.  Operands are unprefixed register numbers;
   the macro builds the asm text by stringify-and-paste. */
#define VU0_MEM(insn) __asm__ __volatile__(insn : : : "memory")
#define VU0_REG(insn) __asm__ __volatile__(insn)
#define VU0_LSV(mnem, vf, off, base) VU0_MEM(#mnem " $vf" #vf ", " #off "($" #base ")")
#define VU0_LSGP(mnem, gp, off, base) VU0_MEM(#mnem " $" #gp ", " #off "($" #base ")")
#define VU0_V2OP(mnem, d, a) VU0_REG(#mnem " $vf" #d ", $vf" #a)
#define VU0_V3OP(mnem, d, a, b) VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b)
#define VU0_V3OP_BC(mnem, d, a, b, bc) VU0_REG(#mnem " $vf" #d ", $vf" #a ", $vf" #b #bc)
#define VU0_V3OP_ACC(mnem, a, b) VU0_REG(#mnem " ACC, $vf" #a ", $vf" #b)
#define VU0_V3OP_ACC_BC(mnem, a, b, bc) VU0_REG(#mnem " ACC, $vf" #a ", $vf" #b #bc)
#define VU0_MFC1(gp, fp) VU0_REG("mfc1 $" #gp ", $f" #fp)
#define VU0_QMTC2_NI(gp, vf) VU0_REG("qmtc2.ni $" #gp ", $vf" #vf)
/* vwaitq: no memory effect, sequences later VU0 ops with prior compute. */
#define VU0_WAIT() __asm__ __volatile__("vwaitq")
/* Several COP2 transfer pairs have a load-delay or Q-pipeline interlock that
   gas's default `.set reorder` fills with a nop the ROM does not carry. */
#define VU0_NOREORDER_BEGIN() __asm__ __volatile__(".set noreorder")
#define VU0_NOREORDER_END() __asm__ __volatile__(".set reorder")

typedef unsigned int u128 __attribute__((mode(TI)));

void sceVu0ApplyMatrix(void *a0, void *a1, void *a2)
{
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

void sceVu0MulMatrix(void *a0, void *a1, void *a2)
{
    __asm__ __volatile__(".set noreorder\n"
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
                         ".set reorder\n" ::
                             : "$7", "memory");
}

void sceVu0OuterProduct(void *a0, void *a1, void *a2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP_ACC(vopmula.xyz, 4, 5);
    VU0_V3OP(vopmsub.xyz, 6, 5, 4);
    VU0_V3OP(vsub.w, 6, 6, 6);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

float sceVu0InnerProduct(void *a0, void *a1)
{
    register float ret __asm__("$f0");
    __asm__ __volatile__(".set noreorder\n"
                         "lqc2 $vf4, 0x0($4)\n"
                         "lqc2 $vf5, 0x0($5)\n"
                         "vmul.xyz $vf5, $vf4, $vf5\n"
                         "vaddy.x $vf5, $vf5, $vf5y\n"
                         "vaddz.x $vf5, $vf5, $vf5z\n"
                         "qmfc2.ni $2, $vf5\n"
                         "mtc1 $2, $f0\n"
                         ".set reorder\n"
                         : "=f"(ret)::"$2");
    return ret;
}

void sceVu0Normalize(void *a0, void *a1)
{
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

__asm__(".section .text\n"
        "    .align 3\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0TransposeMatrix\n"
        "    .type sceVu0TransposeMatrix, @function\n"
        "sceVu0TransposeMatrix:\n"
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
        "    .size sceVu0TransposeMatrix, . - sceVu0TransposeMatrix\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
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
        "    vmulax.xyz ACC, $vf6, $vf5x\n"
        "    vmadday.xyz ACC, $vf7, $vf5y\n"
        "    vmaddz.xyz $vf4, $vf8, $vf5z\n"
        "    vsub.xyz $vf4, $vf9, $vf4\n"
        "    sq    $8, 0x0($4)\n"
        "    sq    $9, 0x10($4)\n"
        "    sq    $10, 0x20($4)\n"
        "    jr    $31\n"
        "    sqc2  $vf4, 0x30($4)\n"
        "    .size sceVu0InversMatrix, . - sceVu0InversMatrix\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

void sceVu0DivVector(void *a0, void *a1, float a2)
{
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

void sceVu0DivVectorXYZ(void *a0, void *a1, float a2)
{
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

void sceVu0InterVector(void *a0, void *a1, void *a2, float t)
{
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

void sceVu0AddVector(void *a0, void *a1, void *a2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vadd.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0SubVector(void *a0, void *a1, void *a2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vsub.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0MulVector(void *a0, void *a1, void *a2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_LSV(lqc2, 5, 0x0, 6);
    VU0_V3OP(vmul.xyzw, 6, 4, 5);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0ScaleVector(void *a0, void *a1, float a2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::
                             : "memory");
    VU0_V3OP_BC(vmulx.xyzw, 6, 4, 5, x);
    VU0_LSV(sqc2, 6, 0x0, 4);
}

void sceVu0TransMatrix(void *a0, void *a1, void *a2)
{
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

__asm__(".section .text\n"
        "    .align 3\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0CopyVector\n"
        "    .type sceVu0CopyVector, @function\n"
        "sceVu0CopyVector:\n"
        "    lq    $6, 0x0($5)\n"
        "    jr    $31\n"
        "    sq    $6, 0x0($4)\n"
        "    .size sceVu0CopyVector, . - sceVu0CopyVector\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .align 3\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0CopyMatrix\n"
        "    .type sceVu0CopyMatrix, @function\n"
        "sceVu0CopyMatrix:\n"
        "    lq    $6, 0x0($5)\n"
        "    lq    $7, 0x10($5)\n"
        "    lq    $8, 0x20($5)\n"
        "    lq    $9, 0x30($5)\n"
        "    sq    $6, 0x0($4)\n"
        "    sq    $7, 0x10($4)\n"
        "    sq    $8, 0x20($4)\n"
        "    jr    $31\n"
        "    sq    $9, 0x30($4)\n"
        "    .size sceVu0CopyMatrix, . - sceVu0CopyMatrix\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

void sceVu0FTOI4Vector(void *a0, void *a1)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0FTOI0Vector(void *a0, void *a1)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vftoi0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0ITOF4Vector(void *a0, void *a1)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof4.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0ITOF0Vector(void *a0, void *a1)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    VU0_V2OP(vitof0.xyzw, 5, 4);
    VU0_LSV(sqc2, 5, 0x0, 4);
}

void sceVu0UnitMatrix(void *a0)
{
    __asm__ __volatile__("vsub.xyzw $vf4, $vf0, $vf0\n"
                         "vadd.w $vf4, $vf4, $vf0\n"
                         "vmr32.xyzw $vf5, $vf4\n"
                         "vmr32.xyzw $vf6, $vf5\n"
                         "vmr32.xyzw $vf7, $vf6\n"
                         "sqc2 $vf4, 0x30($4)\n"
                         "sqc2 $vf5, 0x20($4)\n"
                         "sqc2 $vf6, 0x10($4)\n"
                         "sqc2 $vf7, 0x0($4)\n"
                         :
                         :
                         : "memory");
}

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global _sceVu0ecossin\n"
        "    .type _sceVu0ecossin, @function\n"
        "    .align 3\n"
        "_sceVu0ecossin:\n"
        "    lui   $8, %hi(D_0054A2F0)\n"
        "    addiu $8, $8, %lo(D_0054A2F0)\n"
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
        "    .size _sceVu0ecossin, . - _sceVu0ecossin\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0RotMatrixZ\n"
        "    .type sceVu0RotMatrixZ, @function\n"
        "    .align 3\n"
        "sceVu0RotMatrixZ:\n"
        "    mtc1  $0, $f0\n"
        "    c.lt.s $f12, $f0\n"
        "    lui   $1, 0x3FC9\n"
        "    ori   $1, $1, 0x0FDB\n"
        "    mtc1  $1, $f0\n"
        "    bc1f  1f\n"
        "    nop\n"
        "    add.s $f12, $f0, $f12\n"
        "    j     _RotMatrixZ_02\n"
        "    addiu $7, $0, 0x1\n"
        "1:\n"
        "    sub.s $f12, $f0, $f12\n"
        "    daddu $7, $0, $0\n"
        "    .align 3\n"
        "_RotMatrixZ_02:\n"
        "    mfc1  $8, $f12\n"
        "    qmtc2.ni $8, $vf6\n"
        "    daddu $6, $31, $0\n"
        "    jal   _sceVu0ecossin\n"
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
        "    .size sceVu0RotMatrixZ, . - sceVu0RotMatrixZ\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0RotMatrixX\n"
        "    .type sceVu0RotMatrixX, @function\n"
        "    .align 3\n"
        "sceVu0RotMatrixX:\n"
        "    mtc1  $0, $f0\n"
        "    c.lt.s $f12, $f0\n"
        "    lui   $1, 0x3FC9\n"
        "    ori   $1, $1, 0x0FDB\n"
        "    mtc1  $1, $f0\n"
        "    bc1f  1f\n"
        "    nop\n"
        "    add.s $f12, $f0, $f12\n"
        "    j     _RotMatrixX_02\n"
        "    addiu $7, $0, 0x1\n"
        "1:\n"
        "    sub.s $f12, $f0, $f12\n"
        "    daddu $7, $0, $0\n"
        "    .align 3\n"
        "_RotMatrixX_02:\n"
        "    mfc1  $8, $f12\n"
        "    qmtc2.ni $8, $vf6\n"
        "    daddu $6, $31, $0\n"
        "    jal   _sceVu0ecossin\n"
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
        "    .size sceVu0RotMatrixX, . - sceVu0RotMatrixX\n"
        "    .set reorder\n"
        "    .set at\n");

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0RotMatrixY\n"
        "    .type sceVu0RotMatrixY, @function\n"
        "    .align 3\n"
        "sceVu0RotMatrixY:\n"
        "    mtc1  $0, $f0\n"
        "    c.lt.s $f12, $f0\n"
        "    lui   $1, 0x3FC9\n"
        "    ori   $1, $1, 0x0FDB\n"
        "    mtc1  $1, $f0\n"
        "    bc1f  1f\n"
        "    nop\n"
        "    add.s $f12, $f0, $f12\n"
        "    j     _RotMatrixY_02\n"
        "    addiu $7, $0, 0x1\n"
        "1:\n"
        "    sub.s $f12, $f0, $f12\n"
        "    daddu $7, $0, $0\n"
        "    .align 3\n"
        "_RotMatrixY_02:\n"
        "    mfc1  $8, $f12\n"
        "    qmtc2.ni $8, $vf6\n"
        "    daddu $6, $31, $0\n"
        "    jal   _sceVu0ecossin\n"
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
        "    .size sceVu0RotMatrixY, . - sceVu0RotMatrixY\n"
        "    .set reorder\n"
        "    .set at\n");

extern void sceVu0RotMatrixZ(int a, int b, float f);
extern void sceVu0RotMatrixX(int a, int b, float f);
extern void sceVu0RotMatrixY(int a, int b, float f);

void sceVu0RotMatrix(int a0, int a1, float *fa)
{
    sceVu0RotMatrixZ(a0, a1, fa[2]);
    sceVu0RotMatrixY(a0, a0, fa[1]);
    sceVu0RotMatrixX(a0, a0, fa[0]);
}

void sceVu0ClampVector(void *a0, void *a1, float a2, float a3)
{
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

void sceVu0CameraMatrix(void *a0, void *a1, void *a2, void *a3)
{
    char buf[0x50];
    sceVu0UnitMatrix(buf);
    sceVu0OuterProduct(buf + 0x40, a3, a2);
    sceVu0Normalize(buf, buf + 0x40);
    sceVu0Normalize(buf + 0x20, a2);
    sceVu0OuterProduct(buf + 0x10, buf + 0x20, buf);
    sceVu0TransMatrix(buf, buf, a1);
    sceVu0InversMatrix(a0, buf);
}

extern void sceVu0TransposeMatrix(void *a0, void *a1);

void sceVu0NormalLightMatrix(void *a0, void *a1, void *a2, void *a3)
{
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

extern void sceVu0CopyVector(void *buf, int x);

void sceVu0LightColorMatrix(void *a0, void *a1, void *a2, void *a3, void *a4)
{
    sceVu0CopyVector((void *)a0, a1);
    sceVu0CopyVector((char *)a0 + 0x10, a2);
    sceVu0CopyVector((char *)a0 + 0x20, a3);
    sceVu0CopyVector((char *)a0 + 0x30, a4);
}

void sceVu0ViewScreenMatrix(float *m, float a1, float a2, float a3, float a4, float a5, float a6,
                            float a7, float a8, float a9)
{
    float t[16];
    float p;
    float q;

    q = ((-a7) * a8 + a6 * a9) / (-a8 + a9);
    p = ((a9 * a8) * (-a6 + a7)) / (-a8 + a9);

    sceVu0UnitMatrix(m);
    m[0] = a1;
    m[5] = a1;
    m[10] = 0.0f;
    m[15] = 0.0f;
    m[14] = 1.0f;
    m[11] = 1.0f;

    sceVu0UnitMatrix(t);
    t[0] = a2;
    t[5] = a3;
    t[10] = p;
    t[12] = a4;
    t[13] = a5;
    t[14] = q;
    sceVu0MulMatrix(m, t, m);
}

void sceVu0DropShadowMatrix(float *m, float *p, int para, float lx, float ly, float lz)
{
    if (para != 0) {
        float p0 = p[0];
        float p1 = p[1];
        float p2 = p[2];
        float d;

        d = 1.0f - (lx * p0 + ly * p1 + lz * p2);
        m[0] = lx * p0 + d;
        m[4] = ly * p0;
        m[8] = lz * p0;
        m[12] = -p0;
        m[1] = lx * p1;
        m[5] = ly * p1 + d;
        m[9] = lz * p1;
        m[13] = -p1;
        m[2] = lx * p2;
        m[6] = ly * p2;
        m[10] = lz * p2 + d;
        m[14] = -p2;
        m[3] = lx;
        m[7] = ly;
        m[11] = lz;
        m[15] = d - 1.0f;
    } else {
        float p0 = p[0];
        float p1 = p[1];
        float p2 = p[2];
        float d = lx * p0 + ly * p1 + lz * p2;
        float k = -1.0f / d;
        m[0] = k * (lx * p0 - d);
        m[4] = k * (ly * p0);
        m[8] = k * (lz * p0);
        m[12] = k * (-p0);
        m[1] = k * (lx * p1);
        m[5] = k * (ly * p1 - d);
        m[9] = k * (lz * p1);
        m[13] = k * (-p1);
        m[2] = k * (lx * p2);
        m[6] = k * (ly * p2);
        m[10] = k * (lz * p2 - d);
        m[14] = k * (-p2);
        m[3] = 0.0f;
        m[7] = 0.0f;
        m[11] = 0.0f;
        m[15] = k * (-d);
    }
}

void sceVu0RotTransPersN(void *a0, void *a1, void *a2, int a3, int a4)
{
    __asm__ __volatile__(".set noreorder\n"
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
                         ".set reorder\n" ::
                             : "$7", "memory");
}

void sceVu0RotTransPers(void *a0, void *a1, void *a2, int a3)
{
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

void sceVu0CopyVectorXYZ(void *a0, void *a1)
{
    ((float *)a0)[0] = ((float *)a1)[0];
    ((float *)a0)[1] = ((float *)a1)[1];
    ((float *)a0)[2] = ((float *)a1)[2];
}

void sceVu0InterVectorXYZ(void *a0, void *a1, void *a2, float a3)
{
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

void sceVu0ScaleVectorXYZ(void *a0, void *a1, float a2)
{
    VU0_LSV(lqc2, 4, 0x0, 5);
    __asm__ __volatile__(".set noreorder\n mfc1 $8,$f12\n qmtc2.ni $8,$vf5\n .set reorder" ::
                             : "memory");
    VU0_V3OP_BC(vmulx.xyz, 4, 4, 5, x);
    VU0_LSV(sqc2, 4, 0x0, 4);
}

int sceVu0ClipScreen(void *a0)
{
    register int r __asm__("$2");
    __asm__ __volatile__(".set noreorder\n"
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

int sceVu0ClipScreen3(void *a0, void *a1, void *a2)
{
    register int ret __asm__("$2");
    __asm__ __volatile__(".set noreorder\n"
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

__asm__(".section .text\n"
        "    .set noat\n"
        "    .set noreorder\n"
        "    .global sceVu0ClipAll\n"
        "    .type sceVu0ClipAll, @function\n"
        "    .align 3\n"
        "sceVu0ClipAll:\n"
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
        "    .size sceVu0ClipAll, . - sceVu0ClipAll\n"
        "    nop\n"
        "    .set reorder\n"
        "    .set at\n");

extern int D_0054A300[];

void sceVpu0Reset(void)
{
    *(volatile int *)0x10003830 = 0;
    *(volatile int *)0x10003820 = 0;
    *(volatile int *)0x10003810 = 1;

    __asm__ __volatile__(".set noreorder\n"
                         "cfc2.ni $8, $vi28\n"
                         "ori $8, $8, 0x2\n"
                         "ctc2.ni $8, $vi28\n"
                         "sync.p\n"
                         ".set reorder\n"
                         :
                         :
                         : "memory");

    {
        u128 *fifo = (u128 *)0x10004000;
        u128 *pkt = (u128 *)D_0054A300;

        *(volatile u128 *)fifo = pkt[0];
        *fifo = pkt[1];
    }
}

void memclr(unsigned char *a0, int a1)
{
    int i;
    for (i = a1 - 1; i != -1; i--) {
        *a0++ = 0;
    }
}
