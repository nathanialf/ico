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

extern int D_0028F4C0[];
extern int D_0028F4D4[];
extern int D_0028F4D8[];
extern int D_0063B4C0;
extern int *D_0063C3B4;
extern int D_0063C3B8;
extern void isysGObjActiveLink(int a0, int a1);
extern int kanbanBootMcCheck(void);
extern void kanbanReqAllDelFade(void);
extern int *kanbanReqAdd(int a0, int a1);

void kanbanBootMain(void)
{
    switch (D_0063B4BC) {
    case 0:
        isysGObjActiveLink(0, 1);
        D_0028F4D4[0] = 0;
        D_0063B4C0 = 0;
        D_0063B4BC++;
        /* fallthrough */
    case 1:
        if (D_0063B4C4 != 0) {
            D_0063B4BC++;
        }
        break;
    case 2:
        if (kanbanBootMcCheck() == 0) {
            return;
        }
        kanbanReqAllDelFade();
        D_0063C3B4 = kanbanReqAdd(2, 1);
        D_0063B4BC++;
        break;
    case 3:
        D_0063C3B8 = (60 - D_0028F4C0[0] * 10) / D_0028F4C0[1] * 5;
        D_0063B4BC++;
        /* fallthrough */
    case 4:
        D_0063C3B8--;
        if (D_0063C3B8 != -1) {
            break;
        }
        D_0063B4BC++;
        /* fallthrough */
    case 5:
        if (D_0028F4D8[0] != 0) {
            return;
        }
        D_0063B4BC++;
        break;
    case 6:
        kanbanReqAllDelFade();
        D_0063B4BC++;
        break;
    case 7:
        if (D_0063C3B4[0] != 0) {
            return;
        }
        D_0063B4D0 = 1;
        D_0063B4BC++;
        break;
    }
}

inline void kanbanBootStart(void)
{
    D_0063B4C4 = 1;
}
