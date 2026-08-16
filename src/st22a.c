#include "common.h"

extern int D_004D3570[];

typedef struct { long long _0; long long _8; } WpData16;

typedef struct GObj__p4 {
    char pad[0xC4];
    int *unkB4;
} GObj__p4;

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D36F0[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void func_002347D8(volatile int a0);

void actSt22aLightningVolime(volatile int a0) {
    int x = a0;
    GObj__p4 *gobj = (GObj__p4 *)actInitialize(a0);
    _ACTWait(1);
    D_004D36F0[1] = (int)func_002347D8;
    gobj->unkB4 = D_004D36F0;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait(0);
}

void actSt22aIntro(int x) {
    volatile int local = x;
}

void actSt22aIntroChk(int x) {
    volatile int local = x;
}

extern void BoySekikaTexScroll(int a0, int a1);
extern void *ContinueCorrectPosition(int a0);
extern WpData16 D_0061C100;
extern void *D_00631AE8;
extern void func_0017B528(void *a0);
extern void func_00243AE8(void *a0, void *a1, void *a2);
extern void gflagChk(int a0, void *a1);
extern int scpSleepEnemyOne(int a0, int a1, float f);

void actSt22aIntroSub(volatile int a0) {
    WpData16 local10, local20;
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepEnemyOne(a0, (int)D_00631AE8, 200.0f) == 0) {
        _ACTWait(1);
    }
    func_0017B528(D_00631AE8);
    _ACTWait(1);
    local10 = D_0061C100;
    func_00243AE8(&local20, &local10, ContinueCorrectPosition((int)D_00631AE8));
    gflagChk((int)D_00631AE8, &local20);
    BoySekikaTexScroll((int)D_00631AE8, 0xFD);
}

typedef struct KSub_42c8 { char pad[0xC0]; int unkC0; } KSub_42c8;


void func_002342C8(volatile int a0) {
    KSub_42c8 *s = *(KSub_42c8 **)(a0 + 0x164);
    s->unkC0 = (int)D_004D3570;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct GObjBB_22a {
    char pad[0xC4];
    void **unkC4;
} GObjBB_22a;

extern int D_006325B4;
extern void *D_004D35B0[];
extern int func_0017B230(int a0);
extern void actSt20aGondolaDown(volatile int a0);

void func_002342F8(volatile int a0) {
    GObjBB_22a *gobj = (GObjBB_22a *)*(int *)(a0 + 0x164);
    D_006325B4 = 1;
    *(int *)((char *)gobj + 0xC0) = 0;
    if (func_0017B230(0x13) == 0) {
        D_004D35B0[1] = (void *)actSt20aGondolaDown;
        gobj->unkC4 = D_004D35B0;
        BoxBarSoundOn(a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234368);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_002343B8);

void func_00234438(int x) {
    volatile int local = x;
}

void func_00234448(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234458);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_002344C8);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234658);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234720);

void func_002347C8(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_002347D8);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234830);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234910);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_002349E0);

void func_00234AB0(void) {}

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234AB8);

INCLUDE_ASM("asm/nonmatchings/src/st22a", func_00234C08);

