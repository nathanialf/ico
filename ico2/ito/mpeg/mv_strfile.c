#include "mv_defs.h"
#include "mv_strfile.h"
#include "cdvd.h"

int strFileOpen(char *self, char *name)
{
#if defined(VERSION_NTSC) || defined(VERSION_AUG6) || defined(VERSION_JUN26)
    strcpy(self + 0x34, name);
#else
    strcpy(self + 0x38, name);
#endif
    iosCdvdDirectStOpen((struct IosCdvdHandle *)self);
    return 1;
}

int strFileClose(char *self)
{
    iosCdvdDirectStClose((struct IosCdvdHandle *)self);
    return 1;
}

int strFileRead(char *self, void *buf, int n, int *eof)
{
    return iosCdvdDirectStRead((struct IosCdvdHandle *)self, buf, n, eof);
}
