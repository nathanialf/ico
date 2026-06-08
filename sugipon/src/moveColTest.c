#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/moveColTest", MoveColTestGeo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/moveColTest", MoveColTestDL);

extern void func_0010F048(void *a0);

void InitMoveColTestGeo(void *a0) {
    func_0010F048(a0);
}

extern int D_0062A310;
extern short *iosFree(int handle, int size, char *file, int line);
extern int func_002610F0(void);

extern char D_006126C8[];

short *func_001E3BE8(int a0, int *self)
{
    short *r = iosFree(D_0062A310, 12, (char *)D_006126C8, 0x1C);
    *(int *)r = self[0x30 / 4];
    r[2] = (short)func_002610F0();
    r[3] = (short)func_002610F0();
    r[4] = (short)func_002610F0();
    r[5] = 0;
    return r;
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006126B0;  /* stride 0x4 */

/* end struct shapes */
