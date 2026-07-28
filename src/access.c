#include "common.h"


extern int actSt25aQueenDeadChk();
INCLUDE_ASM("asm/nonmatchings/src/access", func_0023A978);

void func_0023A9E0(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023A9F0);

void func_0023AA88(int x) {
    volatile int local = x;
}

void func_0023AA98(int x) {
    volatile int local = x;
}

void func_0023AAA8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AAB8);

typedef struct KSub_aae8 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_aae8;

extern int D_006325B4__aae8 __asm__("D_006325B4");
extern int D_004D3E90[];
extern int D_004D3EB0[];
extern void BoxBarSoundOn__aae8(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__aae8(int a0) __asm__("_ACTWait");
extern void lt_fade_status__aae8(int a0) __asm__("lt_fade_status");
extern void scpDispOnAllWithKind__aae8(void) __asm__("scpDispOnAllWithKind");
extern int func_0017B230__aae8(int a0) __asm__("func_0017B230");
extern void func_00239C58(volatile int a0);
extern void func_00239B50(volatile int a0);

void func_0023AAE8(volatile int a0) {
    KSub_aae8 *s = *(KSub_aae8 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status__aae8(0x33);
    D_006325B4__aae8 = 1;
    scpDispOnAllWithKind__aae8();
    if (func_0017B230__aae8(0x2C) != 0) {
        D_004D3E90[1] = (int)func_00239C58;
        s->unkC4 = D_004D3E90;
        BoxBarSoundOn__aae8(a0, 0x18D);
        _ACTWait__aae8(0);
    }
    D_004D3EB0[1] = (int)func_00239B50;
    s->unkC4 = D_004D3EB0;
    BoxBarSoundOn__aae8(a0, 0x18D);
    _ACTWait__aae8(0);
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AB90);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023ABE0);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AC30);

typedef struct KSub_ac60 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_ac60;

extern int D_006325B4__ac60 __asm__("D_006325B4");
extern int D_004D3F50[];
extern int D_004D3F70[];
extern void BoxBarSoundOn__ac60(int a0, int a1) __asm__("BoxBarSoundOn");
extern void _ACTWait__ac60(int a0) __asm__("_ACTWait");
extern void lt_fade_status__ac60(int a0) __asm__("lt_fade_status");
extern void scpDispOnAllWithKind__ac60(void) __asm__("scpDispOnAllWithKind");
extern int func_0017B230__ac60(int a0) __asm__("func_0017B230");
extern void func_00239EB0(volatile int a0);
extern void func_00239DA8(volatile int a0);

void func_0023AC60(volatile int a0) {
    KSub_ac60 *s = *(KSub_ac60 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status__ac60(0x33);
    D_006325B4__ac60 = 1;
    scpDispOnAllWithKind__ac60();
    if (func_0017B230__ac60(0x2D) != 0) {
        D_004D3F50[1] = (int)func_00239EB0;
        s->unkC4 = D_004D3F50;
        BoxBarSoundOn__ac60(a0, 0x18D);
        _ACTWait__ac60(0);
    }
    D_004D3F70[1] = (int)func_00239DA8;
    s->unkC4 = D_004D3F70;
    BoxBarSoundOn__ac60(a0, 0x18D);
    _ACTWait__ac60(0);
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AD08);

void func_0023AD58(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AD68);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AE28);

void func_0023AEA0(int a0)
{
    volatile int local = a0;
    int v0;
    v0 = actSt25aQueenDeadChk(0x1B5);
    *(int *)(v0 + 0x16C) = 1;
    v0 = actSt25aQueenDeadChk(0x1B6);
    *(int *)(v0 + 0x16C) = 0;
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AED8);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AF48);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AFB0);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B018);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B080);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B0E8);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B170);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B1B8);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B200);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B278);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B2E0);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B390);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023B440);

