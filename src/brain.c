#include "common.h"

typedef struct { char _0[4]; float f4; char _8[8]; float f10; } EdS;

extern int D_002A5584[];
extern void brainAddLevel();

extern void *D_002A5584__pn[] __asm__("D_002A5584");
extern void brainAddLevel__pn(void *a0) __asm__("brainAddLevel");
void brainAddLevelGirl(void)
{
    if (D_002A5584[0] != 0) {
        brainAddLevel(D_002A5584[0]);
    }
}
INCLUDE_ASM("asm/nonmatchings/src/brain", brainInit);
INCLUDE_ASM("asm/nonmatchings/src/brain", OverrideBrainStatusByGObj);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainStatusDefaultSet);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainLevelProcess);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainGetTarget);
void brainStatusDel(char *self) {
    *(int *)(self + 0x0) = 0;
}
float brainGetLevel(void *a0, void *a1)
{
    if (*(void **)((char *)a0 + 4) == a1) {
        return *(float *)((char *)a1 + 4) + *(float *)((char *)a0 + 0x14);
    }
    return *(float *)((char *)a1 + 4);
}
INCLUDE_ASM("asm/nonmatchings/src/brain", brainClsTargetLevel);
extern void ACTGameView_Add(void *a0, int a1);
extern int D_002A5580[];

void brainInitGirlSet(void *a0, int a1) {
    int *base = D_002A5580;
    int *p = (int *)((char *)base + 0x28);
    int key;
    int t;
    D_002A5580[0] = (int)a0;
    key = *p;
    if (key == 0) {
        return;
    }
    do {
        if (key == a1) {
            base[1] = (int)p;
        }
        ACTGameView_Add(a0, *p);
        p = (int *)((char *)p + 0x1C);
        t = *p;
        key = t;
    } while (t != 0);
}
INCLUDE_ASM("asm/nonmatchings/src/brain", brainAddLevelGirlDetail);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainAddLevelGop);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainSubLevelGop);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainSetLevelGop);
INCLUDE_ASM("asm/nonmatchings/src/brain", brainDecTargetTimer);
extern int D_002A558C[];

void brainSetSpMode(void) {
    D_002A558C[0] = 1;
}
extern int D_002A5588[];

void brainLockGirl(void) {
    D_002A5588[0] = 1;
}
extern int D_002A5588[];

void brainUnlockGirl(void) {
    D_002A5588[0] = 0;
}
INCLUDE_ASM("asm/nonmatchings/src/brain", brainAddLevel);
extern int ACTGameView_Check();

void brainSetLevel(int *a0, EdS *a1, float f12) {
    int cond;
    if (*(unsigned char *)((char *)a1 + 0x19) != 0) {
        cond = 1;
    } else {
        cond = ACTGameView_Check(*a0, *(int *)a1) != 0;
    }
    if (cond) {
        float r;
        a1->f4 = f12;
        if (a1->f4 < 0.0f) {
            r = 0.0f;
        } else if (a1->f4 > 20.0f) {
            r = 20.0f;
        } else {
            r = a1->f4;
        }
        a1->f4 = r;
    }
}
int brainCheckView(int *a0, int *a1)
{
    if (((unsigned char *)a1)[0x19] != 0) {
        return 1;
    }
    return ACTGameView_Check(*a0, a1[0]) != 0;
}
