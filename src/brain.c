#include "common.h"

typedef struct { int *f0; float f4, f8, fC; char _10[4]; int f14; char _18[4]; } BLElem;
typedef struct { char _0[0x24]; float f24; char _28[0x3C]; } BLevel;


extern int D_0028A89C[];
INCLUDE_ASM("asm/nonmatchings/src/brain", brainAddLevelGirl);

INCLUDE_ASM("asm/nonmatchings/src/brain", brainInit);

void OverrideBrainStatusByGObj(char *self) {
    *(int *)(self + 0x0) = 0;
}

float brainStatusDefaultSet(void *a0, void *a1)
{
    if (*(void **)((char *)a0 + 4) == a1) {
        return *(float *)((char *)a1 + 4) + *(float *)((char *)a0 + 0x14);
    }
    return *(float *)((char *)a1 + 4);
}

extern int D_00274EC0[];
extern BLevel D_002A31B8[];

void brainLevelProcess(void *a0) {
    short idx = *(short *)((char *)a0 + 0x24);
    BLElem *e;
    int result;
    if (idx == -1) return;
    *(short *)((char *)a0 + 0x1C) = 0;
    e = (BLElem *)((char *)a0 + 0x28 + idx * 0x1C);
    e->f4 = 0.0f;
    e->f8 = e->f8 - e->fC;
    if (e->f8 < e->f4) {
        e->f8 = e->f4;
    }
    if (e->f0 != 0) {
        int lvl = (int)D_002A31B8[e->f0[3]].f24;
        result = lvl;
        if (lvl != -1) {
            result = lvl * ((0x3C - D_00274EC0[0] * 0xA) / D_00274EC0[1]);
        }
    } else {
        result = -1;
    }
    e->f14 = result;
}

extern int D_0028A890[];
extern void SetDirectRootPositionWithNodePointLimit(void *a0, int a1);

void brainGetTarget(void *a0, int a1) {
    int *base = D_0028A890;
    int *p = (int *)((char *)base + 0x28);
    int key;
    int t;
    D_0028A890[0] = (int)a0;
    key = *p;
    if (key == 0) {
        return;
    }
    do {
        if (key == a1) {
            base[1] = (int)p;
        }
        SetDirectRootPositionWithNodePointLimit(a0, *p);
        p = (int *)((char *)p + 0x1C);
        t = *p;
        key = t;
    } while (t != 0);
}

extern float saveEditedData(void *a0, float f);

void brainStatusSet(int a0, float f12) {
    int *base = D_0028A890;
    int i;
    for (i = 0; i <= 0x13; i++) {
        int *p = (int *)((char *)base + 0x28 + i * 0x1C);
        if (*p == a0) {
            saveEditedData(p, f12);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/brain", brainStatusDel);

extern int gif_test(int *a0, void *a1, float f12);

void brainGetLevel(int a0, int a1, int a2, float f12) {
    int *base = D_0028A890;
    int i;
    for (i = 0; i <= 0x13; i++) {
        char *p = (char *)base + 0x28 + i * 0x1C;
        if (*(int *)p == a0) {
            p[0x18] = (char)a1;
            p[0x19] = (char)a2;
            gif_test(base, p, f12);
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/brain", brainClsTargetLevel);

void brainInitGirlSet(void) {
    D_0028A89C[0] = 1;
}

