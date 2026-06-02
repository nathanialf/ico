#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmStreamInit);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", adpcmTickProc2);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", adpcmDataSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmPlay);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmStop);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmOpen);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmClose);

extern void func_0025A2E0(long long a0);

void AdpcmInterStereoVolumeSet(int a0) {
    func_0025A2E0(*(long long *)(a0 + 0x30));
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmInterLeaveVolumeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmVolumeSet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", adpcmPauseRequest);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmIopBuffAlloc);

extern void AdpcmIopBuffAlloc(int a0, int a1, int a2);

void AdpcmOpenSync(int a0, int a1) {
    AdpcmIopBuffAlloc(a0, 0, a1);
}

extern int D_0062C278;

void AdpcmFadeCloseAll(int a0) {
    D_0062C278 = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmUseAreaGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmFreeAreaGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmInterStereoVolumeSetAll);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmInterLeaveVolumeGet);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/sound/adpcm_init", AdpcmVolumeGet);
