#include "common.h"

extern int D_0063ABE8;
extern int D_006E6D60[];
extern void soundDataClose();
extern int D_0063ABEC;
extern int D_0028F4C0[];
extern int D_0063ABF0;
extern int D_00639EA4;
extern int D_00639EA8;
extern int gamesysAnotherStageTsuresari;
extern int soundDataAreaSearch(void *req);
extern void soundDataOpen(void *a0, int a1, int a2, int a3, int a4);
extern void AdpcmVolumeSet(int handle, int vol);
extern int _ACTCharStatus_Check(int gobj, int status);

void fightSoundProcessMain(void)
{
    int req;
    int cond = 0;
    int step;

    req = 0x110001;
    D_006E6D60[0] = soundDataAreaSearch(&req);
    if (D_006E6D60[0] == 0) {
        D_006E6D60[1] = 0;
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
    if (D_006E6D60[0] == 0) {
        if (cond != 0 || D_0063ABF0 != 0) {
            if (D_0028F4C0[6] == 0) {
                soundDataOpen(&D_006E6D60[2], 2, 1, 2, 0);
                if (D_006E6D60[5] != 0) {
                    D_0063ABEC = 1;
                }
            }
        }
    }
    if (D_006E6D60[0] == 0) {
        return;
    }
    step = 96;
    if (D_0063ABE8 == 1) {
        step = 1024;
    }
    if (cond == 0 && D_0063ABF0 == 0) {
        D_006E6D60[1] -= step;
        if (D_006E6D60[1] < 0) {
            D_006E6D60[1] = 0;
        }
    } else {
        D_006E6D60[1] += step;
        if (D_006E6D60[1] > 6144) {
            D_006E6D60[1] = 6144;
        }
    }
    AdpcmVolumeSet(D_006E6D60[0], D_006E6D60[1]);
    if (D_006E6D60[1] == 0) {
        D_0063ABEC = 2;
    }
}

extern char D_00555628[];
extern char D_0063ABF8[];
extern int *soundDataOpenSync(void *name);
extern void AdpcmPlay(int a0);
extern void debug_assert(char *file, int line);
extern void __assert(char *file, int line, char *expr);
extern void fightSoundProcessMain(void);

void fightSoundProcess(void)
{
    int *h;

    switch (D_0063ABEC) {
    case 0:
        fightSoundProcessMain();
        break;
    case 1:
        h = soundDataOpenSync(&D_006E6D60[2]);
        D_006E6D60[0] = (int)h;
        if (h != (int *)-1) {
            if (h != 0) {
                AdpcmPlay(h[0x2C / 4]);
            }
            D_0063ABEC = 0;
        }
        break;
    case 2:
        if (D_006E6D60[0] != 0) {
            soundDataClose(D_006E6D60[0]);
        }
        D_006E6D60[0] = 0;
        D_0063ABEC = 0;
        break;
    default:
        debug_assert(D_00555628, 0xFF);
        __assert(D_00555628, 0xFF, D_0063ABF8);
    }
}

void fightSoundProcessRequestPause(void)
{
    D_0063ABE8 = 1;
}

void fightSoundClose(void)
{
    if (D_006E6D60[0] != 0) {
        soundDataClose(D_006E6D60[0]);
        D_006E6D60[0] = 0;
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
    return D_006E6D60[0];
}
