#include "common.h"

extern int D_0063C320;
extern void RotateThreadReadyQueue();
extern void *D_0063C320__pn __asm__("D_0063C320");
extern void RotateThreadReadyQueue__pn(void *a0) __asm__("RotateThreadReadyQueue");
extern int D_006F2B98[];
extern void audioDecSendToIOP();
extern int D_0063AC78;
extern char D_0063AC80[];
extern char D_006F2AD0[];
extern char D_006F2AC0[];
extern char D_006EA900[];
void switchThread(void)
{
    RotateThreadReadyQueue(D_0063C320);
}
void proceedAudio(void)
{
    audioDecSendToIOP(D_006F2B98);
}
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", readMpeg);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", initAll);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", termAll);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", movie_init);
INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_main", movie_end);
int movie_proc(int a0) {
    int r;
    debug_StdPrintfDummy(D_0063AC80, D_0063AC78++);
    r = readMpeg(D_006F2AD0, D_006F2AC0, D_006EA900, a0);
    movie_end();
    return r;
}
