#include "common.h"

/* prototypes: their order is the inline tail's emission order */
void kanbanBootInit(void);
void kanbanBootStart(void);
extern int D_0028F4EC[];
extern int D_0063B4BC;
extern int D_0063B4C4;
extern int D_0063B4D0;
extern int fadeStatus;
inline void kanbanBootInit(void)
{
    D_0063B4BC = 0;
    D_0028F4EC[0] = 0;
    D_0063B4D0 = 0;
    fadeStatus = 0;
    D_0063B4C4 = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", kanbanBootMcCheck);
INCLUDE_ASM("asm/nonmatchings/src/kanbanBoot", kanbanBootMain);
inline void kanbanBootStart(void) {
    D_0063B4C4 = 1;
}
