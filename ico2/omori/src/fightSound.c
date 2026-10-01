#include "fightSound.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"
#include "debug_exception.h"
#include "main.h"

/* set while the fight music is paused */
static int fightSoundPause = 0; /* derived name */

/* .bss, owned by fightSound.o and reached only from this file (MAIN.MAP names
   no symbol in the run): the fight loop's ADPCM handle at [0], its volume at
   [1] and the open request at [2]. */
static int fightSnd[8];

/* the fight music's step: 1 once the open is requested, 2 after it */
static int fightSoundState = 0; /* derived name */

/* set while the girl is held (status 9) or taken off the stage */
static int fightSoundGirlTaken = 0; /* derived name */

extern int gamesysAnotherStageTsuresari;

void fightSoundProcessMain(void)
{
    int req;
    int cond = 0;
    int step;

    req = 0x110001;
    fightSnd[0] = soundDataAreaSearch(&req);
    if (fightSnd[0] == 0) {
        fightSnd[1] = 0;
        if (fightSoundPause == 1) {
            return;
        }
    }
    if (systemStatus[6] != 0) {
        return;
    }
    if (systemStatus[5] == 0 && fightSoundPause != 1) {
        if (boyGObj != 0) {
            cond = 0;
            if (_ACTCharStatus_Check(boyGObj, 17) != 0) {
                cond = 1;
            }
        }
        if (systemStatus[6] == 0) {
            fightSoundGirlTaken = 0;
            if ((girlGObj != 0 && _ACTCharStatus_Check(girlGObj, 9) != 0) ||
                gamesysAnotherStageTsuresari != 0) {
                fightSoundGirlTaken = 1;
            }
        }
    } else {
        fightSoundGirlTaken = 0;
        cond = 0;
    }
    if (fightSnd[0] == 0) {
        if (cond != 0 || fightSoundGirlTaken != 0) {
            if (systemStatus[6] == 0) {
                soundDataOpen(&fightSnd[2], 2, 1, 2, 0);
                if (fightSnd[5] != 0) {
                    fightSoundState = 1;
                }
            }
        }
    }
    if (fightSnd[0] == 0) {
        return;
    }
    step = 96;
    if (fightSoundPause == 1) {
        step = 1024;
    }
    if (cond == 0 && fightSoundGirlTaken == 0) {
        fightSnd[1] -= step;
        if (fightSnd[1] < 0) {
            fightSnd[1] = 0;
        }
    } else {
        fightSnd[1] += step;
        if (fightSnd[1] > 6144) {
            fightSnd[1] = 6144;
        }
    }
    AdpcmVolumeSet(fightSnd[0], fightSnd[1]);
    if (fightSnd[1] == 0) {
        fightSoundState = 2;
    }
}

extern void __assert(char *file, int line, char *expr);

void fightSoundProcess(void)
{
    int *h;

    switch (fightSoundState) {
    case 0:
        fightSoundProcessMain();
        break;
    case 1:
        h = soundDataOpenSync(&fightSnd[2]);
        fightSnd[0] = (int)h;
        if (h != (int *)-1) {
            if (h != 0) {
                AdpcmPlay(h[0x2C / 4]);
            }
            fightSoundState = 0;
        }
        break;
    case 2:
        if (fightSnd[0] != 0) {
            soundDataClose(fightSnd[0]);
        }
        fightSnd[0] = 0;
        fightSoundState = 0;
        break;
    default:
        debug_assert("src/fightSound.c", 255);
        __assert("src/fightSound.c", 255, "0");
    }
}

void fightSoundProcessRequestPause(void)
{
    fightSoundPause = 1;
}

void fightSoundClose(void)
{
    if (fightSnd[0] != 0) {
        soundDataClose(fightSnd[0]);
        fightSnd[0] = 0;
    }
}

void fightSoundProcessRequestStart(void)
{
    fightSoundPause = 0;
}

int fightSoundProcessRequestStatus(void)
{
    return fightSoundPause;
}

int fightSoundPlayChk(void)
{
    return fightSnd[0];
}
