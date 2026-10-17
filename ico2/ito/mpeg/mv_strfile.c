/* no mv_defs.h here: the demo's mv_strfile.o has no .rodata, so it does not
   carry alloc_zeroed's file name and assert text as the other mpeg files do */
#include "mv_strfile.h"
#include "cdvd.h"
#include "include_asm.h"

INCLUDE_ASM(strFileOpen);

int strFileClose(char *self)
{
    iosCdvdDirectStClose((struct IosCdvdHandle *)self);
    return 1;
}

int strFileRead(char *self, void *buf, int n, int *eof)
{
    return iosCdvdDirectStRead((struct IosCdvdHandle *)self, buf, n, eof);
}
