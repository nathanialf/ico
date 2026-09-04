#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsResetGraph);
extern int D_0054A2B0[];

void *sceGsGetGParam(void) {
    return D_0054A2B0;
}
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
    "    lui   $5, %hi(D_0054A2C0)\n"
    "    lui   $6, 0x1000\n"
    "    addiu $5, $5, %lo(D_0054A2C0)\n"
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefDispEnv);
extern void *sceGsGetGParam(void);

void sceGsPutDispEnv(void *a0) {
    long *s = (long *)a0;
    if (*(short *)((char *)sceGsGetGParam() + 6) == 1) {
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefDrawEnv);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsPutDrawEnv);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefDBuff);
extern int sceGsPutDispEnv__pn() __asm__("sceGsPutDispEnv");
extern int sceGsPutDrawEnv();

int sceGsSwapDBuff(void *a0, int a1) {
    int s0 = a1 & 1;
    int ret;
    sceGsPutDispEnv__pn((char *)a0 + s0 * 0x28);
    if (!s0) goto zero_path;
    ret = sceGsPutDrawEnv((char *)a0 + 0x140);
    goto done;
zero_path:
    ret = sceGsPutDrawEnv((char *)a0 + 0x50);
done:
    return ret;
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSyncV);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSyncPath);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefTexEnv);
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
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefLoadImage);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefStoreImage);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsExecLoadImage);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsExecStoreImage);
extern int GsGetIMR(void);
extern void GsPutIMR(void *a0);

int sceGsPutIMR(void *a0) {
    int r = GsGetIMR();
    GsPutIMR(a0);
    return r;
}
void sceGsSetHalfOffset(void *a0, short a1, short a2, short a3) {
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
void sceGsGetIMR(void) {
    do {
        GsGetIMR();
    } while (0);
}
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGszbufaddr);
INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_25B680", sceGsSetDefClear);
