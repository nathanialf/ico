#include "common.h"

/* prototypes: their order is the inline tail's emission order */
short *InitMoveColTestGeo(int a0, int *self);
extern void p2o_DispVU1();
extern char D_00620898[];
extern int D_0063A438;
extern short *iosMallocDebug(int handle, int size, char *file, int line);
extern int rand(void);
inline short *InitMoveColTestGeo(int a0, int *self)
{
    short *r = iosMallocDebug(D_0063A438, 12, (char *)D_00620898, 0x1C);
    *(int *)r = self[0x30 / 4];
    r[2] = (short)rand();
    r[3] = (short)rand();
    r[4] = (short)rand();
    r[5] = 0;
    return r;
}
INCLUDE_ASM("asm/nonmatchings/src/moveColTest", MoveColTestGeo);
void MoveColTestDL(int a0, int a1, int a2, int a3)
{
    p2o_DispVU1(a0, a1, a2, a3);
}
