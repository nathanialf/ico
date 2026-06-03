#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/ito/src/lightning", set_vertex);

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
