#include "matching.h"

extern int D_00632C80;
extern void sceClose(void);

void debugSceClose(int a0)
{
    if (a0 == D_00632C80) {
        D_00632C80 = -1;
    }
    sceClose();
    DEFEAT_TCO();
}
