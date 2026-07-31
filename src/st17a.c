#include "common.h"

extern int D_004D3000[];

typedef struct { char pad[0xC0]; void *f_B0; void *unkB4; } BoxObj_st17a;

extern int D_00631AE4;
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void func_0017B258(int a0);
extern int scpSleepSpiderGroupOne(int a0, int a1);

void actSt17aHasiChk(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (1) {
        if (scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) != 0 && func_0017B230(0x10A) != 0) {
            break;
        }
        if (scpSleepSpiderGroupOne(D_00631AE4, 0x2000000) != 0 && scpSleepSpiderGroupOne(D_00631AE8, 0x2000000) != 0) {
            break;
        }
        _ACTWait(1);
    }
    func_0017B258(0x10B);
}

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022D650);

void actSt17aSekizo(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022D6C0);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022D740);

typedef struct KSub_d7c0 { char pad[0xC0]; int unkC0; } KSub_d7c0;


void func_0022D7C0(volatile int a0) {
    KSub_d7c0 *s = *(KSub_d7c0 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3000;
    for (;;) {
        _ACTWait(1);
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int *D_004D3040[];
extern int D_006325B4;
extern void func_0022C9F0(volatile int a0);

void func_0022D7F0(volatile int a0) {
    BoxObj_st17a *obj = *(BoxObj_st17a **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D3040[1] = (int *)func_0022C9F0;
    obj->f_B0 = 0;
    obj->unkB4 = (void *)D_004D3040;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022D848);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022D8F8);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022D9C0);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022DAC8);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022DBC8);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022DDD8);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022DF60);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E058);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E220);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E398);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E508);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E680);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E7F0);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E868);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E8F0);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E968);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022E9D0);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022EA78);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022EAE0);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022EB58);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022EC00);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022EC70);

INCLUDE_ASM("asm/nonmatchings/src/st17a", func_0022ECF0);

