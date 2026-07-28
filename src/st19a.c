#include "common.h"

typedef struct ActB4Obj {
    char pad[0xC4];
    int *unkB4;
} ActB4Obj;



extern int D_0061C0D0[];
extern void debug_assertMessage();
extern void func_0017B258(int bit_idx);
extern void AddWayPointTop();
extern int func_0017B230(int a0);
extern void BoxBarSoundOn(int a0, int a1);
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);
extern int D_004D3420[];
void actSt19aChain(volatile int a0);

void actSt19aOriDown(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0xE) == 0) {
        stage_KillPlayBgAnimation(0x22, 0, 0);
        D_004D3420[1] = (int)actSt19aChain;
        gobj->unkB4 = D_004D3420;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x22, 0, -1);
    }
}

extern int D_00631B14;
extern void gflagOff(int a0, int a1);
extern int actSt25aQueenDeadChk(int a0);

void actSt19aHaguruma(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    if (D_00631B14 == 0x2E) {
        gflagOff(actSt25aQueenDeadChk(0x8D0), 0x2FB);
        *(int *)(actSt25aQueenDeadChk(0x8D0) + 0x16C) = 1;
    }
}

extern void BoxBarSoundOn(int a0, int a1);
extern int D_004D3460[];
extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void func_002318D0();

void actSt19aHagurumaChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    D_004D3460[1] = (int)func_002318D0;
    gobj->unkB4 = D_004D3460;
    BoxBarSoundOn((int)a0, 0x18D);
    _ACTWait(0);
}

extern int D_004D34E0[];
extern void func_00231958();
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt19aPipeChk(volatile int a0) {
    int x = a0;
    ActB4Obj *gobj = (ActB4Obj *)actInitialize(a0);
    _ACTWait(1);
    if (func_0017B230(0x10) == 0) {
        stage_KillPlayBgAnimation(0x28, 0, 0);
        D_004D34E0[1] = (int)func_00231958;
        gobj->unkB4 = D_004D34E0;
        BoxBarSoundOn((int)a0, 0x18D);
        _ACTWait(0);
    } else {
        stage_KillPlayBgAnimation(0x28, 0, -1);
    }
}

extern void _ACTWait(int a0);
extern int actInitialize(int a0);
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

void actSt19aChainDown(volatile int a0){ int x=a0; actInitialize(a0); _ACTWait(1);
stage_KillPlayBgAnimation(0x1F,0,-1); stage_KillPlayBgAnimation(0x19,0,0); stage_KillPlayBgAnimation(0x22,0,0); stage_KillPlayBgAnimation(0x23,0,0); stage_KillPlayBgAnimation(0x25,0,0); }

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChainUp);

void actSt19aOri(int x) {
    volatile int local = x;
}

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aOriXL);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231690);

INCLUDE_ASM("asm/nonmatchings/src/st19a", actSt19aChain);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231818);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_002318D0);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231958);

extern int D_004D3520[];
extern int D_006325B4;
extern int func_0012AA80(int a0);
extern void lt_fade_status(int a0);
extern void soundSeDefPlayWithVolumeRate(int a0, int a1, int a2, int a3);

void actSt19aChainMain(volatile int a0) {
    lt_fade_status(0x33);
    func_0017B258(0x10);
    _ACTWait(0x3C);
    stage_KillPlayBgAnimation(0x28, 1, 0);
    soundSeDefPlayWithVolumeRate(0x4AD, 0, (int)D_004D3520, 1);
    _ACTWait(0x1E);
    soundSeDefPlayWithVolumeRate(0x4AE, 0, (int)D_004D3520, 1);
    while (func_0012AA80(0x28) == 0) { _ACTWait(1); }
    _ACTWait(1);
    D_006325B4 = 0;
    lt_fade_status(0x32);
}

extern void Generator_Mask(int a0);
extern void Generator_ResetCount(int a0);

void actSt19aChainSwitch(volatile int a0) {
    Generator_Mask(a0);
    Generator_ResetCount(a0);
}

void actSt19bIntroChk(void)
{
    if (func_0017B230(0x14) != 0) {
        AddWayPointTop(9, 0);
    }
}

void func_00231AF8(void)
{
    if (func_0017B230(0x1D) != 0) {
        return;
    }
    debug_assertMessage(D_0061C0D0);
    func_0017B258(0x165);
}

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231B38);

INCLUDE_ASM("asm/nonmatchings/src/st19a", func_00231C58);

