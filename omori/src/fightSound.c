#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/fightSound", fightSoundProcessMain);

extern int D_0062AA58;

void fightSoundProcess(void) {
    D_0062AA58 = 0;
}

int fightSoundProcessRequestPause(void) {
    return D_0062AA58;
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/fightSound", fightSoundClose);
