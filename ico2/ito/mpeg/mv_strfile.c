#include "mv_defs.h"
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
