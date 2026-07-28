#include "common.h"



extern int D_00632780;
extern void soundSeVolSet();
extern int D_006D0D20[];
void fightSoundProcessMain(void)
{
    if (D_006D0D20[0] != 0) {
        soundSeVolSet(D_006D0D20[0]);
        D_006D0D20[0] = 0;
    }
}

void fightSoundProcess(void) {
    D_00632780 = 0;
}

int fightSoundProcessRequestPause(void) {
    return D_00632780;
}

int fightSoundClose(void) {
    return D_006D0D20[0];
}

