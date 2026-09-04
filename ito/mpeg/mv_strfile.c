#include "common.h"

extern void iosCdvdDirectStClose();
extern int iosCdvdDirectStRead();
int strFileOpen(char *a0, char *name) {
    strcpy(a0 + 0x38, name);
    iosCdvdDirectStOpen(a0);
    return 1;
}
int strFileClose(void) {
    iosCdvdDirectStClose();
    return 1;
}
int strFileRead(void)
{
    return iosCdvdDirectStRead();
}
