#include "common.h"
#include "vu0.h"

float InitClothTestGeo(void *a0) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($4)\n"
        "vmul.xz $vf4, $vf4, $vf4\n"
        "vaddz.x $vf4, $vf4, $vf4z\n"
        "qmfc2.ni $2, $vf4\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

float ClothTestGeo(void *a0, void *a1, void *a2) {
    register float ret __asm__("$f0");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vsub.xyzw $vf4, $vf1, $vf2\n"
        "vmul.xyz $vf3, $vf4, $vf4\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3x\n"
        "sqc2 $vf4, 0x0($4)\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        ".set reorder\n"
        : "=f"(ret) :: "$2");
    return ret;
}

void ClothTestDL(void *a0, void *a1, void *a2, float a3) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "lqc2 $vf5, 0x0($6)\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "vadd.xyz $vf4, $vf4, $vf5\n"
        "sqc2 $vf4, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void func_001C6148(void *a0, void *a1, float a2) {
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf4, 0x0($5)\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf5\n"
        "vmulx.xz $vf4, $vf4, $vf5x\n"
        "sqc2 $vf4, 0x0($4)\n"
        ".set reorder\n" : : : "memory");
}

void func_001C6168(void *a0, void *a1, void *a2, float a3) {
    int buf[4] __attribute__((aligned(16)));
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vsub.xyzw $vf4, $vf1, $vf2\n"
        "vmul.xyz $vf3, $vf4, $vf4\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3x\n"
        "sqc2 $vf4, 0x0($29)\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        "mul.s $f12, $f12, $f0\n"
        "lqc2 $vf4, 0x0($6)\n"
        "lqc2 $vf5, 0x0($29)\n"
        "mfc1 $8, $f12\n"
        "qmtc2.ni $8, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "vadd.xyz $vf4, $vf4, $vf5\n"
        "sqc2 $vf4, 0x0($4)\n"
        ".set reorder\n"
        : "=m"(buf) : : "$2", "memory");
}

void func_001C61C0(void *a0, void *a1, void *a2, float a3, float a4) {
    int buf[4] __attribute__((aligned(16)));
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($5)\n"
        "lqc2 $vf2, 0x0($6)\n"
        "vsub.xyzw $vf4, $vf1, $vf2\n"
        "vmul.xyz $vf3, $vf4, $vf4\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vrsqrt $Q, $vf0w, $vf3x\n"
        "sqc2 $vf4, 0x0($29)\n"
        "vwaitq\n"
        "cfc2.ni $2, $vi22\n"
        "mtc1 $2, $f0\n"
        "c.lt.s $f0, $f13\n"
        "bc1f 1f\n"
        "nop\n"
        "mul.s $f0, $f12, $f0\n"
        "lqc2 $vf4, 0x0($6)\n"
        "lqc2 $vf5, 0x0($29)\n"
        "mfc1 $8, $f0\n"
        "qmtc2.ni $8, $vf6\n"
        "vmulx.xyz $vf5, $vf5, $vf6x\n"
        "vadd.xyz $vf4, $vf4, $vf5\n"
        "sqc2 $vf4, 0x0($4)\n"
        "1:\n"
        ".set reorder\n"
        : "=m"(buf) : : "$2", "memory");
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6228);

int func_001C62E8(void *a0, void *a1) {
    register int result __asm__("$2");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vmul.xyz $vf3, $vf1, $vf2\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vaddw.x $vf3, $vf3, $vf2w\n"
        "qmfc2.ni $2, $vf3\n"
        "mtc1 $2, $f1\n"
        "mtc1 $0, $f0\n"
        "c.lt.s $f0, $f1\n"
        "nop\n"
        "bc1f 1f\n"
        "daddu $2, $0, $0\n"
        "addiu $2, $0, 0x1\n"
        "1:\n"
        ".set reorder\n"
        : "=r"(result) :: "$f0", "$f1");
    return result;
}

int func_001C6328(void *a0, void *a1) {
    register int result __asm__("$2");
    __asm__ __volatile__(
        ".set noreorder\n"
        "lqc2 $vf1, 0x0($4)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vmul.xyz $vf3, $vf1, $vf2\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vaddw.x $vf3, $vf3, $vf2w\n"
        "qmfc2.ni $2, $vf3\n"
        "mtc1 $2, $f0\n"
        "mtc1 $0, $f1\n"
        "c.le.s $f1, $f0\n"
        "nop\n"
        "bc1f 1f\n"
        "addiu $3, $4, 0x10\n"
        "lqc2 $vf1, 0x0($3)\n"
        "lqc2 $vf2, 0x0($5)\n"
        "vmul.xyz $vf3, $vf1, $vf2\n"
        "vaddy.x $vf3, $vf3, $vf3y\n"
        "vaddz.x $vf3, $vf3, $vf3z\n"
        "vaddw.x $vf3, $vf3, $vf2w\n"
        "qmfc2.ni $2, $vf3\n"
        "mtc1 $2, $f0\n"
        "c.lt.s $f0, $f1\n"
        "nop\n"
        "bc1t 2f\n"
        "addiu $2, $0, 0x1\n"
        "1:\n"
        "daddu $2, $0, $0\n"
        "2:\n"
        ".set reorder\n"
        : "=r"(result) :: "$f0", "$f1", "$3");
    return result;
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6398);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6420);

extern int   D_0062A310;
extern char  D_004BBC40[];
extern int  *iosFree(int handle, int size, char *file, int line);
extern int   calc2(char *p);

extern char D_00611260[];

int *func_001C6548(void)
{
    int *p = iosFree(D_0062A310, 0x290, (char *)D_00611260, 0x41);
    *p = calc2(D_004BBC40);
    return p;
}

void func_001C6598(void) {
}

void func_001C65A0(void) {
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C65A8);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C68B0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/clothTest", func_001C6DA0);
