#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", ActPara_MakeTbl);
INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", ActPara_InitSystem);
extern int D_006C0928[];

int *ActPara_GetDefTbl(void) {
    return D_006C0928;
}
int ActPara_StatusToFlag(int a0, int a1)
{
    int v = a0 ? 9 : 1;
    return a1 ? (v | 4) : v;
}
void ActPara_DebugOut(void) {}
