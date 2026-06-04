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

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", DrawLightning2);

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", DrawLightningN);

int apply_m34(int *a0, int *a1) {
    return a0[4] - a1[4];
}

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", DrawLightning);


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
