#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainAddLevelGirl);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainInit);

void OverrideBrainStatusByGObj(int *p) {
    *p = 0;
}

float brainStatusDefaultSet(void *a0, void *a1) {
    if (*(void **)((char *)a0 + 0x4) == a1) {
        return *(float *)((char *)a1 + 0x4) + *(float *)((char *)a0 + 0x14);
    }
    return *(float *)((char *)a1 + 0x4);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainLevelProcess);

extern int D_00286A90[];
extern void SetDirectRootPositionWithNodePointLimit(void *a0, int a1);

void brainGetTarget(void *a0, int a1) {
    int *base = D_00286A90;
    int *p = (int *)((char *)base + 0x28);
    int key;
    int t;
    D_00286A90[0] = (int)a0;
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
    int *base = D_00286A90;
    int i;
    for (i = 0; i <= 0x13; i++) {
        int *p = (int *)((char *)base + 0x28 + i * 0x1C);
        if (*p == a0) {
            saveEditedData(p, f12);
        }
    }
}


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainStatusDel);

extern int gif_test(int *a0, void *a1, float f12);

void brainGetLevel(int a0, int a1, int a2, float f12) {
    int *base = D_00286A90;
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


INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/brain", brainClsTargetLevel);

extern int D_00286A9C[];

void brainInitGirlSet(void) {
    D_00286A9C[0] = 1;
}
