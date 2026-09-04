#include "common.h"

extern int D_0063C320;
extern void RotateThreadReadyQueue();

extern void *D_0063C320__pn __asm__("D_0063C320");
extern void RotateThreadReadyQueue__pn(void *a0) __asm__("RotateThreadReadyQueue");
void switchThread(void)
{
    RotateThreadReadyQueue(D_0063C320);
}
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
