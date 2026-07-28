#include "common.h"

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

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D418);

typedef struct KSub_d448 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_d448;

extern int D_006325B4__d448 __asm__("D_006325B4");
extern int D_004D2E00[];
extern int D_004D2E20[];
extern void BoxBarSoundOn__d448(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__d448(int a0) __asm__("_ACTWait");
extern void lt_fade_status__d448(int a0) __asm__("lt_fade_status");
extern void scpDispOnAllWithKind__d448(void) __asm__("scpDispOnAllWithKind");
extern int func_0017B230__d448(int a0) __asm__("func_0017B230");
extern void func_0022C2D0(volatile int a0);
extern void func_0022C060(volatile int a0);

void func_0022D448(volatile int a0) {
    KSub_d448 *s = *(KSub_d448 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status__d448(0x33);
    D_006325B4__d448 = 1;
    scpDispOnAllWithKind__d448();
    if (func_0017B230__d448(0x107) != 0) {
        D_004D2E00[1] = (int)func_0022C2D0;
        s->unkC4 = D_004D2E00;
        BoxBarSoundOn__d448(a0, 0x18D);
        _ACTWait__d448(0);
    }
    D_004D2E20[1] = (int)func_0022C060;
    s->unkC4 = D_004D2E20;
    BoxBarSoundOn__d448(a0, 0x18D);
    _ACTWait__d448(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st13d", func_0022D4F0);

typedef struct KSub_d520 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_d520;

extern int D_006325B4__d520 __asm__("D_006325B4");
extern int D_004D2EC0[];
extern int D_004D2EE0[];
extern void BoxBarSoundOn__d520(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__d520(int a0) __asm__("_ACTWait");
extern void lt_fade_status__d520(int a0) __asm__("lt_fade_status");
extern void scpDispOnAllWithKind__d520(void) __asm__("scpDispOnAllWithKind");
extern int func_0017B230__d520(int a0) __asm__("func_0017B230");
extern void func_0022C638(volatile int a0);
extern void func_0022C4C0(volatile int a0);

void func_0022D520(volatile int a0) {
    KSub_d520 *s = *(KSub_d520 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status__d520(0x33);
    D_006325B4__d520 = 1;
    scpDispOnAllWithKind__d520();
    if (func_0017B230__d520(0x109) != 0) {
        D_004D2EC0[1] = (int)func_0022C638;
        s->unkC4 = D_004D2EC0;
        BoxBarSoundOn__d520(a0, 0x18D);
        _ACTWait__d520(0);
    }
    D_004D2EE0[1] = (int)func_0022C4C0;
    s->unkC4 = D_004D2EE0;
    BoxBarSoundOn__d520(a0, 0x18D);
    _ACTWait__d520(0);
}

