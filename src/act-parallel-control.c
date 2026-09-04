#include "common.h"

#include "ico/types.h"

INCLUDE_ASM("asm/nonmatchings/src/act-parallel-control", ActPara_MakeTbl);
extern int D_006C0928[];
extern char D_003089C0[];
void ActPara_InitSystem(void) {
    int i;
    for (i = 0; i <= 0x55; i++) {
        D_006C0928[i] = *(int *)(D_003089C0 + i * 0xB0);
    }
}
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
