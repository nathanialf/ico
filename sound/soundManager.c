#include "common.h"

extern void soundDataSegAllClose(int a0, int a1);
extern void soundDataSegNextStageNotUseClose();
extern void soundSeEnvNotUseClose();
extern void soundSePlayModeStop(int arg);

extern void soundDataSegNextStageNotUseClose__pn(int x, int *p) __asm__("soundDataSegNextStageNotUseClose");
extern void soundSeEnvNotUseClose__pn(int *a, int *b) __asm__("soundSeEnvNotUseClose");
void sndBgmReadyNextStage(int *a, int *b)
{
    soundDataSegNextStageNotUseClose(1, a);
    soundDataSegNextStageNotUseClose(2, a);
    soundSePlayModeStop(1);
    soundDataSegAllClose(1, 0);
    soundSeEnvNotUseClose(a, b);
}
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
extern char D_005523A8[];
extern char D_005523C0[];
extern char D_005523D0[];
extern int IosStgMgrLock;
extern int mpegPlay;
extern void debug_StdPrintfDummy();
extern void iosThreadCancelWakeup(int mode);
extern void iosThreadSleep();
extern int SgSndn2RemoteSync();
extern void _PushVu0Registers();
extern void SgCalledTickProc();
extern void soundVBlank();
extern int soundOutputModeGet();
extern void AdpcmInterStereoVolumeSetAll();
extern void _PopVu0Registers();

void sndManager(void)
{
    int mode;

    mode = -1;
    debug_StdPrintfDummy(D_005523A8);
    debug_StdPrintfDummy(D_005523C0, IosStgMgrLock);
    debug_StdPrintfDummy(D_005523D0);
    while (1) {
        iosThreadCancelWakeup(0);
        iosThreadSleep();
        while (SgSndn2RemoteSync() != 0)
            ;
        _PushVu0Registers();
        SgCalledTickProc();
        if (mpegPlay == 0) {
            soundVBlank();
        }
        if (mode != soundOutputModeGet()) {
            mode = soundOutputModeGet();
            AdpcmInterStereoVolumeSetAll();
        }
        _PopVu0Registers();
    }
}
INCLUDE_ASM("asm/nonmatchings/sound/soundManager", func_00146CC0);
