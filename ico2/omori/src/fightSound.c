#include "common.h"
#include "fightSound.h"
#include "adpcm_init.h"
#include "s_init.h"
#include "act-game.h"

extern int D_0063ABE8;

/* .bss, owned by fightSound.o and reached only from this file (MAIN.MAP names
   no symbol in the run): the fight loop's ADPCM handle at [0], its volume at
   [1] and the open request at [2]. */
static int fightSnd[8];

extern int D_0063ABEC;
extern int D_0028F4C0[];
extern int D_0063ABF0;
extern int D_00639EA4;
extern int D_00639EA8;
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
        if (D_0063ABE8 == 1) {
            return;
        }
    }
    if (D_0028F4C0[6] != 0) {
        return;
    }
    if (D_0028F4C0[5] == 0 && D_0063ABE8 != 1) {
        if (D_00639EA4 != 0) {
            cond = 0;
            if (_ACTCharStatus_Check(D_00639EA4, 17) != 0) {
                cond = 1;
            }
        }
        if (D_0028F4C0[6] == 0) {
            D_0063ABF0 = 0;
            if ((D_00639EA8 != 0 && _ACTCharStatus_Check(D_00639EA8, 9) != 0) ||
                gamesysAnotherStageTsuresari != 0) {
                D_0063ABF0 = 1;
            }
        }
    } else {
        D_0063ABF0 = 0;
        cond = 0;
    }
    if (fightSnd[0] == 0) {
        if (cond != 0 || D_0063ABF0 != 0) {
            if (D_0028F4C0[6] == 0) {
                soundDataOpen(&fightSnd[2], 2, 1, 2, 0);
                if (fightSnd[5] != 0) {
                    D_0063ABEC = 1;
                }
            }
        }
    }
    if (fightSnd[0] == 0) {
        return;
    }
    step = 96;
    if (D_0063ABE8 == 1) {
        step = 1024;
    }
    if (cond == 0 && D_0063ABF0 == 0) {
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
        D_0063ABEC = 2;
    }
}

extern char D_0063ABF8[];
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);

void fightSoundProcess(void)
{
    int *h;

    switch (D_0063ABEC) {
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
            D_0063ABEC = 0;
        }
        break;
    case 2:
        if (fightSnd[0] != 0) {
            soundDataClose(fightSnd[0]);
        }
        fightSnd[0] = 0;
        D_0063ABEC = 0;
        break;
    default:
        debug_assert("src/fightSound.c", 255);
        __assert("src/fightSound.c", 255, D_0063ABF8);
    }
}

void fightSoundProcessRequestPause(void)
{
    D_0063ABE8 = 1;
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
    D_0063ABE8 = 0;
}

int fightSoundProcessRequestStatus(void)
{
    return D_0063ABE8;
}

int fightSoundPlayChk(void)
{
    return fightSnd[0];
}
