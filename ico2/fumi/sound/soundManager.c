#include "common.h"
#include "typedef.h"
#include "debug.h"
#include "adpcm_init.h"
#include "Matrix.h"

/* kept local: this TU's uses of soundDataSegAllClose do not fit the prototype in s_init.h */
extern void soundDataSegAllClose(int a0, int a1);
/* kept local: this TU's uses of soundDataSegNextStageNotUseClose do not fit the prototype in s_init.h */
extern void soundDataSegNextStageNotUseClose();
/* kept local: this TU's uses of soundSeEnvNotUseClose do not fit the prototype in s_init.h */
extern void soundSeEnvNotUseClose();
/* kept local: this TU's uses of soundSePlayModeStop do not fit the prototype in s_init.h */
extern void soundSePlayModeStop(int arg);
/* kept local: this TU's uses of soundDataSegNextStageNotUseClose do not fit the prototype in s_init.h */
extern void soundDataSegNextStageNotUseClose(int x, int *p);
/* kept local: this TU's uses of soundSeEnvNotUseClose do not fit the prototype in s_init.h */
extern void soundSeEnvNotUseClose(int *a, int *b);
extern StgPre D_005F5D50[];
/* kept local: this TU's uses of soundReverbDepthSet do not fit the prototype in s_init.h */
extern void soundReverbDepthSet(int a0);
/* kept local: this TU's uses of soundSeKindBuild do not fit the prototype in s_init.h */
extern void soundSeKindBuild(int idx);
extern int IosStgMgrLock;
extern int mpegPlay;
/* kept local: this TU's uses of iosThreadCancelWakeup do not fit the prototype in thread.h */
extern void iosThreadCancelWakeup(int mode);
/* kept local: this TU's uses of iosThreadSleep do not fit the prototype in thread.h */
extern void iosThreadSleep();
extern int SgSndn2RemoteSync();
extern void SgCalledTickProc();
/* kept local: this TU's uses of soundVBlank do not fit the prototype in s_init.h */
extern void soundVBlank();
/* kept local: this TU's uses of soundOutputModeGet do not fit the prototype in s_init.h */
extern int soundOutputModeGet();

#include "soundManager.h"

inline void sndManager(void)
{
    int mode;

    mode = -1;
    debug_StdPrintfDummy("sound manager in\n");
    debug_StdPrintfDummy("IosSndLock %d\n", IosStgMgrLock);
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

void sndInit(int idx)
{
    short attrOff;
    soundSeKindBuild(idx);
    adpcmPauseRequest(0);
    attrOff = 0x18C;
    soundReverbDepthSet(*(unsigned short *)((char *)&D_005F5D50[idx] + attrOff));
}
