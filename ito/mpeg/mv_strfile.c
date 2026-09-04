#include "common.h"

int strFileOpen(char *a0, char *name) {
    strcpy(a0 + 0x38, name);
    iosCdvdDirectStOpen(a0);
    return 1;
}
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
