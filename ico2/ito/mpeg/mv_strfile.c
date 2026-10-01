#include "mv_defs.h"
#include "mv_strfile.h"

/* kept local: cdvd.h does not compile in this TU (too few arguments to function `iosCdvdDirectStClose') */
extern void iosCdvdDirectStClose();
/* kept local: cdvd.h does not compile in this TU (too few arguments to function `iosCdvdDirectStClose') */
extern int iosCdvdDirectStRead();

int strFileOpen(char *a0, char *name)
{
    strcpy(a0 + 0x38, name);
    iosCdvdDirectStOpen(a0);
    return 1;
}

int strFileClose(void)
{
    iosCdvdDirectStClose();
    return 1;
}

int strFileRead(void)
{
    return iosCdvdDirectStRead();
}
