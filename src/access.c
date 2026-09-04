#include "common.h"

typedef struct { char pad[0x194]; } DispBuf;
extern DispBuf D_005F5DD0[];
extern char D_0063C090[];
extern int GetDataFileName2(void *p);
int GetDataFileName(int a0) {
    int buf[0x40];
    void *p;
    if (a0 == -1) {
        p = D_0063C090;
    } else {
        p = (void *)&D_005F5DD0[a0];
    }
    return GetDataFileName2(p);
}
INCLUDE_ASM("asm/nonmatchings/src/access", GetDataFileName2);
