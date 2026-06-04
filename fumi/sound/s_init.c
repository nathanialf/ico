#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundOutputModeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundReverbDepthSet);

extern int D_0062A4FC;
extern void func_002590B8(int a0);

void soundAllocIopHeap(int a0) {
    D_0062A4FC = a0;
    func_002590B8(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundAllocIopFree);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataOpenChk);

extern void func_00246700(int a0);
extern int D_0062A528;

void soundBufAlloc(void) {
    func_00246700(D_0062A528);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundBufSegFree);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundBDDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataOpenSync);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataClose);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataSegAllClose);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeVolSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", debug_DispSEInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", sound3DParamSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", _soundSeDefPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", _soundSeDefStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefStopNoRelease);

extern void soundSeDefStopNoRelease(int a0, int a1);

void soundSeDefPitchSet(int a0) {
    soundSeDefStopNoRelease(a0, 0);
}

void soundReqTickProc(int a0) {
    soundSeDefStopNoRelease(a0, 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeEnvPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeEnvNotUseClose);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataSegNextStageNotUseClose);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", Ee2Iop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundOutputModeGet);

extern int D_0062A4FC;
extern int D_0062A4F0;

int soundReverbDepthGet(void) {
    return D_0062A4FC;
}

int soundBufAdpcmChAlloc(void) {
    return D_0062A4F0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundBufAdpcmFree);

extern unsigned long long D_0062BFC8;

void soundDataAreaSearch(void *a0) {
    unsigned long long *p = (unsigned long long *)((char *)a0 + 0x18);
    D_0062BFC8 &= ~*p;
    *p = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataAreaGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundHDDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSQDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefPlayWithVolumeRate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefVolumeRateGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefVolumeRateSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeGroupStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeGroupGet);

extern int D_0062A524;

int soundSePlayModeStop(void) {
    return D_0062A524 = ((D_0062A524 + 1) & 0x0FFFFFFF) | 0x10000000;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundVBlank);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeKindBuild);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeSemiCommonLoadChk);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeEnvDefaultSet);

extern int D_0062A500;

int debug_req(void) {
    return D_0062A500;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned int       f_4;  /* 0x04 */
    short              f_10;  /* 0x10 */
    unsigned int       f_30;  /* 0x30 */
} S_006A3370;  /* stride 0x40 */

typedef struct {
    unsigned int       f_60;  /* 0x60 */
} S_005E1C00;  /* stride 0x64 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
    unsigned short     f_2;  /* 0x02 */
} S_006A3070;

typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_002E2A10;  /* stride 0x2 */

typedef struct {
    unsigned short     f_0;  /* 0x00 */
} S_005E44A0;  /* stride 0x8 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00551F30;  /* stride 0x4 */

/* end struct shapes */
