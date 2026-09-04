#include "common.h"

extern int D_0063C320;
extern void RotateThreadReadyQueue();

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", switchThread);
extern int D_006F2B98[];
extern void audioDecSendToIOP();

void proceedAudio(void)
{
    audioDecSendToIOP(D_006F2B98);
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", readMpeg);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", initAll);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", termAll);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", movie_init);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", movie_end);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", movie_proc);
