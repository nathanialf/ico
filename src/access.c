#include "common.h"

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D3E50[];
extern int D_004D3F10[];
extern int D_006325B4;
extern void _ACTWait(int a0);
extern int func_0017B230(int a0);
extern void lt_fade_status(int a0);
extern void scpDispOnAllWithKind(void);


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

typedef struct KSub_aab8 { char pad[0xC0]; int unkC0; } KSub_aab8;


void func_0023AAB8(volatile int a0) {
    KSub_aab8 *s = *(KSub_aab8 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3E50;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_aae8 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_aae8;

extern int D_004D3E90[];
extern int D_004D3EB0[];
extern void func_00239C58(volatile int a0);
extern void func_00239B50(volatile int a0);

void func_0023AAE8(volatile int a0) {
    KSub_aae8 *s = *(KSub_aae8 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x2C) != 0) {
        D_004D3E90[1] = (int)func_00239C58;
        s->unkC4 = D_004D3E90;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D3EB0[1] = (int)func_00239B50;
    s->unkC4 = D_004D3EB0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023AB90);

INCLUDE_ASM("asm/nonmatchings/src/access", func_0023ABE0);

typedef struct KSub_ac30 { char pad[0xC0]; int unkC0; } KSub_ac30;


void func_0023AC30(volatile int a0) {
    KSub_ac30 *s = *(KSub_ac30 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3F10;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct KSub_ac60 {
    char pad[0xC0];
    int unkC0;
    int *unkC4;
} KSub_ac60;

extern int D_004D3F50[];
extern int D_004D3F70[];
extern void func_00239EB0(volatile int a0);
extern void func_00239DA8(volatile int a0);

void func_0023AC60(volatile int a0) {
    KSub_ac60 *s = *(KSub_ac60 **)(a0 + 0x164);
    s->unkC0 = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    scpDispOnAllWithKind();
    if (func_0017B230(0x2D) != 0) {
        D_004D3F50[1] = (int)func_00239EB0;
        s->unkC4 = D_004D3F50;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
    D_004D3F70[1] = (int)func_00239DA8;
    s->unkC4 = D_004D3F70;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
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

