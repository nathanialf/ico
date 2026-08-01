/* Vendor TU: libmpeg.a(csc.o) - 0x2564E0..0x256BF8. */
#include "common.h"

#include "r5900.h"
#include "vu0.h"
#include "math_private.h"
#include "math_private.h"

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", func_002564E0);

extern void func_00255F80(void);

void func_00256648(void) {
    int v;
    func_00255F80();
    v = (-(*(volatile int *)0x10002020 & 7)) & 7;
    if (v) func_002563C8(v);
    while (func_00256290(0x18) != 1) {
        func_002563C8(8);
    }
}

extern int D_00552700[];
extern int D_00552D80[];
extern void func_00256BF8(void);

int func_002566B0(void) {
    int *p = D_00552700;
    *p = func_002564E0(5);
    if (func_002564E0(1)) {
        int *q = D_00552D80;
        *q = func_002564E0(1);
        func_002563C8(7);
        func_00256BF8();
    } else {
        D_00552D80[0] = 0;
    }
    return 0;
}

extern void *D_005524A4[];
extern int D_0055263C[];
extern long long D_00552D48[];
extern long long D_00552D50[];
extern void *func_00251CF8(void *a0, void *a1);
extern void func_002526E0(void);
extern void func_00256848(void);
extern void func_00256D10(void);

int func_00256720(void) {
    struct { int f0; long long f8; long long f10; } local;

    while (1) {
        func_00256648();
        switch ((unsigned int) func_002564E0(0x20)) {
        case 0x1B3:
            func_002526E0();
            break;
        case 0x1B8:
            func_00256D10();
            break;
        case 0x100:
            func_00256848();
            local.f0 = 5;
            local.f8 = -1;
            local.f10 = -1;
            func_00251CF8(D_005524A4[0], &local);
            D_00552D48[0] = local.f8;
            D_00552D50[0] = local.f10;
            return D_0055263C[0];
        case 0x1B7:
            return 0;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", func_00256848);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", func_00256918);

INCLUDE_ASM("asm/nonmatchings/src/cod/vendor_2564E0", func_002569C8);

