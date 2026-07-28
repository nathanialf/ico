#include "common.h"


extern void backStageProcessMain(void);
extern void _ACTWait();
extern void func_0017B258(int bit_idx);
INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022ED40);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022ED98);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EE68);

typedef struct GObjBB_17b {
    char pad[0xC4];
    void **unkC4;
} GObjBB_17b;

extern int D_006325B4;
extern void BoxBarSoundOn(int a0, int a1);
extern void _ACTWait__bb17b(int a0) __asm__("_ACTWait");

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EE98);

void func_0022EEF0(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EF00);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EF78);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F130);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F218);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F360);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F560);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F600);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F698);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F710);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F7B8);

extern void *D_004D3280[];extern void lt_fade_status(int a0);
extern void func_0022EF78(volatile int a0);

void func_0022F7E8(volatile int a0) {
    GObjBB_17b *gobj = *(GObjBB_17b **)(a0 + 0x164);
    *(int *)((char *)gobj + 0xC0) = 0;
    lt_fade_status(0x33);
    D_006325B4 = 1;
    D_004D3280[1] = (void *)func_0022EF78;
    gobj->unkC4 = D_004D3280;
    BoxBarSoundOn(a0, 0x18D);
    _ACTWait__bb17b(0);
}

void func_0022F850(int a0)
{
    volatile int local = a0;
    _ACTWait(1);
    backStageProcessMain();
    func_0017B258(0x12A);
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F880);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F930);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F9E0);

