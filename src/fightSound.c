#include "common.h"

INCLUDE_ASM("asm/nonmatchings/src/fightSound", fightSoundProcessMain);
INCLUDE_ASM("asm/nonmatchings/src/fightSound", fightSoundProcess);
extern int D_0063ABE8;

void fightSoundProcessRequestPause(void)
{
    D_0063ABE8 = 1;
}
extern int D_006E6D60[];
extern void soundDataClose();

void fightSoundClose(void)
{
    if (D_006E6D60[0] != 0) {
        soundDataClose(D_006E6D60[0]);
        D_006E6D60[0] = 0;
    }
}
void fightSoundProcessRequestStart(void) {
    D_0063ABE8 = 0;
}
int fightSoundProcessRequestStatus(void) {
    return D_0063ABE8;
}
int fightSoundPlayChk(void) {
    return D_006E6D60[0];
}
