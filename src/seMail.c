#include "common.h"



extern unsigned char D_004CAEC0[];
extern int D_0063385C;
INCLUDE_ASM("asm/nonmatchings/src/seMail", setMailTarget);

INCLUDE_ASM("asm/nonmatchings/src/seMail", seMail);

int seMailTargetDistCheck(void) {
    return D_0063385C;
}

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_00204E98);

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_00204F58);

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_00204FA8);

INCLUDE_ASM("asm/nonmatchings/src/seMail", WayPointWithRangeFromGObj);

int func_00205048(float *a, float *b)
{
    if (a[1] < b[1]) return -1;
    if (b[1] < a[1]) return 1;
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_00205080);

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_002052F8);

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_00205388);

INCLUDE_ASM("asm/nonmatchings/src/seMail", func_00205400);

INCLUDE_ASM("asm/nonmatchings/src/seMail", DeleteWayGroup);

void CloseWayGroup(int idx)
{
    int *node = (int *)((char *)D_004CAEC0 + idx * 0x34);
    int v1 = node[8 / 4];
    int v0 = node[12 / 4];
    node[20 / 4] = 1;
    *(int *)(v1 + 8) = v0;
    *(int *)(v0 + 12) = v1;
}

