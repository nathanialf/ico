#include "common.h"

extern int D_006CA600[];
extern void soundSeVolSet(int a0);

void fightSoundProcessMain(void)
{
    if (D_006CA600[0] != 0) {
        soundSeVolSet(D_006CA600[0]);
        D_006CA600[0] = 0;
    }
}

extern int D_0062AA58;

void fightSoundProcess(void) {
    D_0062AA58 = 0;
}

int fightSoundProcessRequestPause(void) {
    return D_0062AA58;
}


int fightSoundClose(void) {
    return D_006CA600[0];
}
