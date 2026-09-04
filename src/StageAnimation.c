#include "common.h"

#include "vu0.h"

typedef struct AnimNode {
    long field0;            /* 0x00 */
    char _pad[0x14 - 0x8];
    struct AnimNode *next;  /* 0x14 */
} AnimNode;

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakeGObj);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ApplyData);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_Init);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetAnimation);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ContinueAnimation);
extern int D_0028F4D4[];
extern void bga_ResetAnimation();
extern void light_KillAllFixLight(void);

void stage_ResetAnimation(void)
{
    bga_ResetAnimation();
    if (D_0028F4D4[0] != 0) return;
    light_KillAllFixLight();
}
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CalcAnimationNoParent);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CalcAnimationParent);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_DispAnimation);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetScale);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimation);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimationDissolve);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakePlayBgAnimation);
extern int *D_0063C15C;
extern int freeseki(void *a0);

void stage_KillPlayBgAnimation(int **self)
{
    int *node = *self;
    int *next;
    int *prev;
    if (node == 0) return;
    next = (int *)node[0x10 / 4];
    if (next != 0) {
        next[0x14 / 4] = node[0x14 / 4];
    } else {
        D_0063C15C = (int *)node[0x14 / 4];
        node = *self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (D_0063C15C != 0) {
        D_0063C15C[0x10 / 4] = 0;
    }
    freeseki(*self);
}
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_DispBgAnimation);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_DispBgAnimationNoFinish);
extern void bga_SetCameraForceOff();

void stage_SetCameraForceOff(int a0, int a1, int a2, int a3)
{
    bga_SetCameraForceOff(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFinish);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFrame);
extern int D_0063C158;
extern char D_0067D098[];

void stage_SetLoopFlag(int key, int a1)
{
    int count = *(volatile int *)&D_0063C158;
    int i;
    char *e = (char *)D_0067D098;
    for (i = 0; i < count; i++, e += 0x290) {
        int *p = *(int **)(e + 0x280);
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&D_0063C158)));
            count = *p;
        }
    }
}
void stage_SetFrameStep(int target, int val)
{
    int n = D_0063C158;
    char *p = (char *)D_0067D098;
    int i;
    if (n <= 0) return;
    i = n;
    do {
        int *entry1 = *(int **)(p + 0x280);
        if (target == entry1[0x58 / 4]) {
            int *entry2 = *(int **)(p + 0x284);
            *(float *)((char *)entry2 + 0x1C) = (float)val;
        }
        p += 0x290;
    } while (--i);
}
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetParentOfGObj);
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetParentOfGObjWithLocalRotationFlag);
extern void CopyQuaternion();
extern void _CopyVector(void *dst, void *src);

void stage_SetLocalizeGeometry(int key, int arg1, int arg2)
{
    int count = *(volatile int *)&D_0063C158;
    int i = 0;
    char *e = (char *)D_0067D098;
    if (count <= 0) return;
    do {
        int *entry1 = *(int **)(e + 0x280);
        if (key == entry1[0x58 / 4]) {
            int *entry2;
            char *target;
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            _CopyVector(target, arg1);
            entry2 = *(int **)(e + 0x284);
            target = *(char **)((char *)entry2 + 0x24);
            CopyQuaternion(target + 0x10, arg2);
            count = *(volatile int *)&D_0063C158;
        }
        i++;
        e += 0x290;
    } while (i < count);
}
extern int D_0063C15C__pn __asm__("D_0063C15C");

void stage_KillPlayBgAnimationIfOverMaxCount(int a0, int a1)
{
    AnimNode *p = (AnimNode *)D_0063C15C__pn;
    int count = 0;
    while (p != 0) {
        long v = p->field0;
        if ((((unsigned short)v << 18) >> 18) == a0) {
            if (!(v & 0x8000)) {
                count++;
                if (a1 < count) {
                    p->field0 = v | 0x8000;
                }
            }
        }
        p = p->next;
    }
}
extern int bga_CheckAnimationFrameIn(int a0, int a1, int a2);
extern int bga_CheckSdfCameraFrameIn(int a0, int a1, int a2);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFrameIn);
