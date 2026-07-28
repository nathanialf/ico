#include "common.h"



extern int D_00633FDC;
extern int D_00633B88;
#include "r5900.h"
extern char D_0028CA30[];
extern int  D_00633B8C;
extern void allocObjectData(int *p);
void func_0023EFB0(void) {}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufCreate);

int viBufReset(void)
{
    if (D_00633B8C != 0) {
        allocObjectData(D_0028CA30);
        D_00633B8C = 0;
    }
    SYNC();
    EI();
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufBeginPut);

void viBufEndPut(void) {
    D_00633B88 = 0;
    D_00633FDC = 0;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufAddDMA);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufStopDMA);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufRestartDMA);

char *viBufFlush(char *p) {
    *(int *)(p + 0) = 0;
    *(int *)(p + 8) = 0x3F;
    *(int *)(p + 4) = 0;
    *(int *)(p + 0xC) = 0;
    return p + 0x10;
}

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufModifyPts);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufGetTs);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufDelete);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufCount);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", viBufPutTs);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F400);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F450);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F4B0);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F540);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F598);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F5D0);

INCLUDE_ASM("asm/nonmatchings/ito/mpeg/mv_vibuf", func_0023F600);

