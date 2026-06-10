#include "common.h"

/* act-parallel-control 0x164 actor-state view (local) */
typedef struct { char _0[0x54]; int f_54; float f_58; } APCBrain670;
typedef struct { char _0[0x334]; float f_334; } APCSub678;
typedef struct {
    char _0[0x54];
    int f_54;   /* 0x54 */
    char _58[0x4];
    float f_5C; /* 0x5C */
    float f_60; /* 0x60 */
    float f_64; /* 0x64 */
    int f_68;   /* 0x68 */
    int f_6C;   /* 0x6C */
    int f_70;   /* 0x70 */
    char _74[0x8];
    int f_7C;   /* 0x7C */
    int f_80;   /* 0x80 */
    int f_84;   /* 0x84 */
    int f_88;   /* 0x88 */
    int f_8C;   /* 0x8C */
    int f_90;   /* 0x90 */
    char _pad94[0xC];
    float f_A0; /* 0xA0 */
    float f_A4; /* 0xA4 */
    float f_A8; /* 0xA8 */
    char _padAC[0x5C4];
    APCBrain670 *p_670; /* 0x670 */
    char _pad674[4];
    APCSub678 *p_678;   /* 0x678 */
} APCState;

int ActPara_MakeTbl(void *a0, int a1, float *a2, int a3, int a4) {
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    int ret = 0;
    if (a3 == 6) {
        p->f_88 = 0;
        p->f_90 = 0;
        p->f_8C = 0;
        goto end;
    }
    if (a3 < p->f_8C) goto end;
    p->f_88 = a1;
    if (a2) {
        p->f_A0 = a2[0];
        p->f_A4 = a2[1];
        p->f_A8 = a2[2];
    }
    p->f_90 = a4;
    p->f_8C = a3;
    ret = 1;
end:
    return ret;
}

extern void func_0014A668(void *);
extern void func_001440F0(void *);
extern void func_0014A510(APCSub678 *, int, int);

void ActPara_InitSystem(void *a0) {
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    func_0014A668(a0);
    func_001440F0(a0);
    func_0014A510((*(APCState **)((char *)a0 + 0x164))->p_678, p->f_80, 0);
    p->f_84 = p->f_80;
}

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

void func_00149C20(void *a0, int a1, int a2, float f12) {
    APCState *p = *(APCState **)((char *)a0 + 0x164);
    p->f_54 |= 1 << a1;
    switch (a1) {
    case 8:  p->f_5C = f12; break;
    case 5:  p->f_60 = f12; break;
    case 15: p->f_64 = f12; break;
    case 16: p->f_68 = a2; break;
    case 10: p->f_6C = a2; break;
    case 2:  p->f_70 = a2; break;
    case 11: p->f_7C = a2; break;
    }
}

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
