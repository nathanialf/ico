#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_MakeTbl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_InitSystem);

void ActPara_GetDefTbl(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x164);
    p[0x20] |= 1 << a1;
}

int ActPara_StatusToFlag(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x164);
    return (p[0x20] >> a1) & 1;
}

void ActPara_DebugOut(int **a0) {
    int *p = a0[0x59];
    p[0x15] = 0;
    p[0x16] = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149C20);

int func_00149CA0(void *a0, int a1) {
    int *p = *(int **)((char *)a0 + 0x164);
    int ret = 0;
    if (p) {
        ret = (*(int *)((char *)p + 0x54) >> a1) & 1;
    }
    return ret;
}

void func_00149CC0(void) {
}

void func_00149CC8(void *a0, float a1) {
    int *p = *(int **)((char *)a0 + 0x164);
    int *q = *(int **)((char *)p + 0x678);
    *(float *)((char *)q + 0x334) = a1;
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149CD8);

extern float D_0028E5F0[];

float func_00149D00(int a0) {
    return D_0028E5F0[a0];
}

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149D18);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149DD8);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", func_00149E70);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00552450;  /* stride 0x4 */

/* end struct shapes */
