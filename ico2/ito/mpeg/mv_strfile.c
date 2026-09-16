#include "common.h"

/* kept local: this TU's uses of iosCdvdDirectStClose do not fit the prototype in cdvd.h */
extern void iosCdvdDirectStClose();
/* kept local: this TU's uses of iosCdvdDirectStRead do not fit the prototype in cdvd.h */
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
