#include "common.h"

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D2DC0[];
extern int D_004D2E80[];
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022CD58);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022CDD8);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022CE58);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022CED8);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022CF58);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022CFD8);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D058);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D0D8);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D150);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D1C8);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D240);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D2B8);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D340);

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D3C8);

typedef struct KSub_d418 { char pad[0xC0]; int unkC0; } KSub_d418;


void func_0022D418(volatile int a0) {
    KSub_d418 *s = *(KSub_d418 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D2DC0;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_d448 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_d448;

extern int D_004D2E00[];
extern int D_004D2E20[];
extern void func_0022C2D0(volatile int a0);
extern void func_0022C060(volatile int a0);

void func_0022D448(volatile int a0) {
    KSub_d448 *s = *(KSub_d448 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x107) != 0) {
        D_004D2E00[1] = (int)func_0022C2D0;
        s->unkC4 = D_004D2E00;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D2E20[1] = (int)func_0022C060;
    s->unkC4 = D_004D2E20;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

typedef struct KSub_d4f0 { char pad[0xC0]; int unkC0; } KSub_d4f0;


void func_0022D4F0(volatile int a0) {
    KSub_d4f0 *s = *(KSub_d4f0 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D2E80;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_d520 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_d520;

extern int D_004D2EC0[];
extern int D_004D2EE0[];
extern void func_0022C638(volatile int a0);
extern void func_0022C4C0(volatile int a0);

void func_0022D520(volatile int a0) {
    KSub_d520 *s = *(KSub_d520 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x109) != 0) {
        D_004D2EC0[1] = (int)func_0022C638;
        s->unkC4 = D_004D2EC0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D2EE0[1] = (int)func_0022C4C0;
    s->unkC4 = D_004D2EE0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

