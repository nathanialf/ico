#include "typedef.h"
#include "debug.h"
#include "StageManager.h"
#include "adpcm_init.h"
#include "Matrix.h"
#include "main.h"

/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern void soundDataSegAllClose(int a0, int a1);
/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern void soundDataSegNextStageNotUseClose();
/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern void soundSeEnvNotUseClose();
/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern void soundSePlayModeStop(int arg);
/* kept local: void (int, int *) here, void () in s_init.h */
extern void soundDataSegNextStageNotUseClose(int x, int *p);
/* kept local: void (int *, int *) here, void () in s_init.h */
extern void soundSeEnvNotUseClose(int *a, int *b);
extern StgPre stageData[];
/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern void soundReverbDepthSet(int a0);
/* kept local: void (int) here, void (void) in s_init.h */
extern void soundSeKindBuild(int idx);
/* kept local: void (int) here, int (int *) in thread.h */
extern void iosThreadCancelWakeup(int mode);
/* kept local: agrees with thread.h, which this TU does not include (iosThreadCancelWakeup differ) */
extern void iosThreadSleep();
extern int SgSndn2RemoteSync();
extern void SgCalledTickProc();
/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern void soundVBlank();
/* kept local: agrees with s_init.h, which this TU does not include (soundSeKindBuild differ) */
extern int soundOutputModeGet();

#include "soundManager.h"

inline void sndManager(void)
{
    int mode;

    mode = -1;
    debug_StdPrintfDummy("sound manager in\n");
    debug_StdPrintfDummy("IosSndLock %d\n", IosSndLock);
    debug_StdPrintfDummy("SOUND MANAGER START\n");
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

void sndBgmReadyNextStage(int *a, int *b)
{
    soundDataSegNextStageNotUseClose(1, a);
    soundDataSegNextStageNotUseClose(2, a);
    soundSePlayModeStop(1);
    soundDataSegAllClose(1, 0);
    soundSeEnvNotUseClose(a, b);
}

int sndInitBgmCancelFlag;

void sndInit(int idx)
{
    short attrOff;
    soundSeKindBuild(idx);
    adpcmPauseRequest(0);
    attrOff = 0x18C;
    soundReverbDepthSet(*(unsigned short *)((char *)&stageData[idx] + attrOff));
}
