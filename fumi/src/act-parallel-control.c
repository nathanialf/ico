#include "common.h"

/* act-parallel-control 0x164 actor-state view (local) */
typedef struct { char _0[0x54]; int f_54; float f_58; } APCBrain670;
typedef struct { char _0[0x334]; float f_334; } APCSub678;
typedef struct { char _0[0x80]; int f_80; char _pad84[0x5EC]; APCBrain670 *p_670; char _pad674[4]; APCSub678 *p_678; } APCState;

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_MakeTbl);

INCLUDE_ASM("asm/aug6/nonmatchings/fumi/src/act-parallel-control", ActPara_InitSystem);

void ActPara_GetDefTbl(void *a0, int a1) {
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    p->f_80 |= 1 << a1;
}

int ActPara_StatusToFlag(void *a0, int a1) {
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    return (p->f_80 >> a1) & 1;
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
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    APCSub678 *q = p->p_678;
    q->f_334 = a1;
}

void func_00149CD8(void *a0, unsigned int a1, float f) {
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    APCBrain670 *q = p->p_670;
    if (a1 >= (unsigned int)q->f_54) {
        q->f_58 = f;
        q->f_54 = a1;
    }
}

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
