#include "common.h"

extern void soundDataSegAllClose(int a0, int a1);
extern void soundDataSegNextStageNotUseClose();
extern void soundSeEnvNotUseClose();
extern void soundSePlayModeStop(int arg);

extern void soundDataSegNextStageNotUseClose__pn(int x, int *p) __asm__("soundDataSegNextStageNotUseClose");
extern void soundSeEnvNotUseClose__pn(int *a, int *b) __asm__("soundSeEnvNotUseClose");

INCLUDE_ASM("asm/nonmatchings/sound/soundManager", sndBgmReadyNextStage);
extern unsigned char D_005F5D50[];
extern void adpcmPauseRequest(int val);
extern void soundReverbDepthSet(int a0);
extern void soundSeKindBuild(int idx);

void sndInit(int idx)
{
    short new_var;
    soundSeKindBuild(idx);
    adpcmPauseRequest(0);
    new_var = 0x18C;
    soundReverbDepthSet(*((unsigned short *) ((((char *) D_005F5D50) + (idx * 0x194)) + new_var)));
}
INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00146C10);
