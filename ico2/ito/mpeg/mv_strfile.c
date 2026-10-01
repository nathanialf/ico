#include "mv_defs.h"
#include "mv_strfile.h"
#include "cdvd.h"

int strFileOpen(char *a0, char *name)
{
    strcpy(a0 + 0x38, name);
    iosCdvdDirectStOpen(a0);
    return 1;
}

int strFileClose(char *self)
{
    iosCdvdDirectStClose((int *)self);
    return 1;
}

int strFileRead(char *self, void *buf, int n, int *eof)
{
    return iosCdvdDirectStRead((int)self, (int)buf, n, eof);
}
