#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundOutputModeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundReverbDepthSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundAllocIopHeap);

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

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataAreaSearch);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundDataAreaGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundHDDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSQDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefPlayWithVolumeRate);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefVolumeRateGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeDefVolumeRateSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeGroupStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeGroupGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSePlayModeStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundVBlank);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeKindBuild);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeSemiCommonLoadChk);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/s_init", soundSeEnvDefaultSet);

extern int D_0062A500;

int debug_req(void) {
    return D_0062A500;
}
