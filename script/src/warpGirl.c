#include "common.h"

/* warpGirl 0x164 actor-state view (local) */
typedef struct { char _0[0x20]; long f_20; } WarpState;

extern int execNormalMove(void);

int warpGirlOutStage(void) {
    return execNormalMove() != 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", warpGirlInStage);

extern float D_006C9220[];

void warpGirlInit(float *a0) {
    a0[0] = D_006C9220[0];
    a0[1] = D_006C9220[1];
    a0[2] = D_006C9220[2];
}

extern void *D_00629DE4;

void func_0017C0B8(void) {
    void *o = D_00629DE4;
    if (o) {
        WarpState *s = *(WarpState **)((char *)o + 0x164);
        s->f_20 &= -0x201;
    }
}

void func_0017C0E0(void) {
    void *o = D_00629DE4;
    if (o) {
        WarpState *s = *(WarpState **)((char *)o + 0x164);
        s->f_20 |= 0x200;
    }
}

void func_0017C108(void) {
    void *o = D_00629DE4;
    if (o) {
        WarpState *s = *(WarpState **)((char *)o + 0x164);
        s->f_20 &= -0x401;
    }
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C130);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C1B0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C230);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C308);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C3D0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C560);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C658);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017C910);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017CE38);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017D318);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017D560);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DA68);

extern void func_0012FEC8(void *a0, float a1, float a2, float a3, float a4, float a5, float a6, int a7);
extern char D_00554540[];
extern float D_00629198;

void func_0017DC10(void) {
    func_0012FEC8(D_00554540, 0.0f, 0.0f, 0.0f, D_00629198, 0.0f, 0.5f, 1);
}

extern void Generator_Mask(int a0);

void func_0017DC40(volatile int a0) {
    Generator_Mask(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DC68);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DCE0);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DD70);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DDD8);

extern int actInitialize(int a0);
extern void _ACTWait(int a0);
extern void scpTorchLightOn(int a0, int a1);

void func_0017DE40(volatile int a0) {
    int x = a0;
    actInitialize(a0);
    _ACTWait(1);
    scpTorchLightOn(0x76E, 0x1A6);
}

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DE80);

INCLUDE_ASM("asm/aug6/nonmatchings/script/src/warpGirl", func_0017DEE8);
