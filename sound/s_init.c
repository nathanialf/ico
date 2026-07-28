#include "common.h"









extern int D_00632218;
extern void AdpcmStop();
extern char D_006A95B0[];
extern int D_0063223C;
extern long long D_00633CD8;
extern char D_006A98B0[];
extern void func_0025DA68();
extern void func_0024A1E0();
extern int D_00632240;
extern void func_0025CCE0(int a0, int a1, int a2);
extern void func_0025CE78(int a0, int a1, int a2);
extern int D_00632208;
extern void func_0025CD28();
extern int  D_00632214;
INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundReverbDepthSet);

void soundAllocIopHeap(int a0)
{
    D_00632214 = a0;
    func_0025CD28(a0);
}

void soundAllocIopFree(int a0)
{
    int val;
    D_00632208 = a0;
    val = (a0 * 32767) / 100;
    func_0025CCE0(0, val, val);
    func_0025CCE0(1, val, val);
    func_0025CE78(0, 0x3FFF, 0x3FFF);
    func_0025CE78(1, 0x3FFF, 0x3FFF);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenChk);

void soundBufAlloc(void)
{
    func_0024A1E0(D_00632240);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBufSegFree);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBDDataSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpen);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataOpenSync);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataSegAllClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeVolSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", debug_DispSEInfo);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", sound3DParamSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", _soundSeDefPlay);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", _soundSeDefStop);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefStop);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefStopNoRelease);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefPitchSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundReqTickProc);

void soundSeEnvPlay(int a0)
{
    char *entry;
    short id;
    entry = &D_006A98B0[(a0 & 0xFF) * 64];
    id = *(short *)(entry + 0x10);
    if (id < 0) return;
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)entry) return;
    func_0025DA68(id);
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeEnvNotUseClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataSegNextStageNotUseClose);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", Ee2Iop);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundOutputModeGet);

int soundReverbDepthGet(void) {
    return D_00632214;
}

int soundBufAdpcmChAlloc(void) {
    return D_00632208;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundBufAdpcmFree);

void soundDataAreaSearch(char *self) {
    long long mask = ~*(long long *)(self + 0x18);
    D_00633CD8 &= mask;
    *(long long *)(self + 0x18) = 0;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundDataAreaGet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundHDDataSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSQDataSet);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefPlay);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefPlayWithVolumeRate);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeDefVolumeRateGet);

float soundSeDefVolumeRateSet(int a0)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006A98B0 + off;
    if (*(short *)(e + 0x10) >= 0) {
        goto check;
    }
fail:
    return 0.0f;
check:
    a0 = a0 >> 8;
    if (a0 != *(unsigned short *)e) {
        goto fail;
    }
    return *(float *)(D_006A98B0 + off + 0x18);
}

void soundSeGroupStop(int a0, float f)
{
    int off = (a0 & 0xFF) * 64;
    char *e = D_006A98B0 + off;
    if (*(short *)(e + 0x10) >= 0) {
        a0 = a0 >> 8;
        if (a0 == *(unsigned short *)e) {
            *(float *)(D_006A98B0 + off + 0x18) = f;
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeGroupGet);

int soundSePlayModeStop(void)
{
    int next = ((D_0063223C + 1) & 0x0FFFFFFF) | 0x10000000;
    D_0063223C = next;
    return next;
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundVBlank);

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeKindBuild);

void soundSeSemiCommonLoadChk(void)
{
    int i;
    for (i = 0; i < 0x300; i += 0x30) {
        char *p = D_006A95B0 + i;
        if (*(unsigned short *)(p + 2) == 0x11) {
            AdpcmStop(p);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/sound/s_init", soundSeEnvDefaultSet);

int debug_req(void) {
    return D_00632218;
}

