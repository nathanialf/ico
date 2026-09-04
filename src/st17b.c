#include "common.h"


extern void CheckPoint(void);
extern void _ACTWait();
extern void func_0017B258(int bit_idx);
extern long long D_0061C0B0[];
extern int D_00631AE8;
extern void _ACTWait(int a0);
extern int D_00631AE4;
extern int func_0017B230(int a0);
extern int actInitialize(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void actSt25aQueenTalkChk(int a0, int a1, int *buf, int a3, float f);

void func_0022ED40(volatile unsigned int a0)
{
    long long buf[2];
    buf[0] = D_0061C0B0[0];
    buf[1] = D_0061C0B0[1];
    actSt25aQueenTalkChk(D_00631AE8, 0, (int *)buf, 0, 100.0f);
    _ACTWait(0);
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022ED98);

extern int D_004D3100[];

void func_0022EE68(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    *(int *)(gobj + 0xC0) = (int)D_004D3100;
    for (;;) {
        _ACTWait(1);
    }
}

typedef struct GObjBB_17b {
    char pad[0xC4];
    void **unkC4;
} GObjBB_17b;

extern int D_006325B4;
extern void BoxBarSoundOn(int a0, int a1);

typedef struct { char pad[0xC0]; void *f_C0; void *unkC4; } GObjC0_17b;
extern int *D_004D3140[];
extern void func_0022DF60(volatile int a0);

void func_0022EE98(volatile int a0) {
    GObjC0_17b *obj = *(GObjC0_17b **)(a0 + 0x164);
    D_006325B4 = 1;
    D_004D3140[1] = (int *)func_0022DF60;
    obj->f_C0 = 0;
    obj->unkC4 = (void *)D_004D3140;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

void func_0022EEF0(int x) {
    volatile int local = x;
}

extern int scpSleepSpiderGroupOne(int a0, int a1);

void func_0022EF00(volatile int a0) {
    if (D_00631AE8 == 0) {
        _ACTWait(0);
    }
    while (scpSleepSpiderGroupOne(D_00631AE8, 0x1000000) == 0 ||
           scpSleepSpiderGroupOne(D_00631AE4, 0x3000000) == 0) {
        _ACTWait(1);
    }
    _ACTWait(1);
    func_0017B258(0x117);
    func_0017B258(0x118);
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022EF78);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F130);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F218);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F360);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F560);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F600);

typedef struct { char pad[0xC4]; int *unkC4; } ActB4_17b;
extern int D_004D32E0[];
extern void func_0022F850(int a0);

void func_0022F698(volatile int a0) {
    int x = a0;
    ActB4_17b *gobj = (ActB4_17b *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x12A) == 0) {
        D_004D32E0[1] = (int)func_0022F850;
        gobj->unkC4 = D_004D32E0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    }
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F710);

extern int D_004D3240[];

void func_0022F7B8(volatile int a0) {
    int gobj = *(int *)(a0 + 0x164);
    *(int *)(gobj + 0xC0) = (int)D_004D3240;
    for (;;) {
        _ACTWait(1);
    }
}

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
    _ACTWait(0);
}

void func_0022F850(int a0)
{
    volatile int local = a0;
    _ACTWait(1);
    CheckPoint();
    func_0017B258(0x12A);
}

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F880);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F930);

INCLUDE_ASM("asm/nonmatchings/src/st17b", func_0022F9E0);

