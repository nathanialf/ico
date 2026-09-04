#include "common.h"

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_strfile", strFileOpen);
extern void iosCdvdDirectStClose();

int strFileClose(void) {
    iosCdvdDirectStClose();
    return 1;
}
extern int iosCdvdDirectStRead();

int strFileRead(void)
{
    return iosCdvdDirectStRead();
}
