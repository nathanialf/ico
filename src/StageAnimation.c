#include "common.h"







extern const char D_00555BF8[];
extern void func_001AD768();
extern int bga_SetCamFrame();
extern const char D_00631D88[];
extern void func_00263FF0(int a0, int a1, int a2);
extern void debug_assertMessage();
extern const char D_00555D78[];
extern int font_CheckAlign();
extern char D_00674058[];
extern int D_00633C54;
extern void font_GetWidth();
extern int D_00633C58;
extern int resetmallocseki(void *a0);
extern void func_00117768(void);
extern void func_001FAA58();
extern int D_00274ED4[];
extern int D_00631D54;
INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakeGObj);

extern char *D_00631970;
extern void _ClearTransCurrentMatrix(void *a0, void *a1);
extern void _InverseCurrentMatrix(void *a0, void *a1, float a2);
extern void _PopCurrentMatrix(void *a0);
extern void _RotCurrentMatrixY(void);
extern void func_00117C80(void *a0);
extern void func_00117C98(void);
extern void func_00117CE0(void);

void stage_ApplyData(void *a0) {
    func_00117C80(a0);
    _PopCurrentMatrix(D_00631970 + 0x80);
    func_00117CE0();
    _RotCurrentMatrixY();
    _ClearTransCurrentMatrix(a0, D_00631970 + 0xB0);
    _InverseCurrentMatrix(a0, a0, -1.0f);
    *(float *)((char *)a0 + 0xC) = 1.0f;
    func_00117C98();
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_Init);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetAnimation);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ContinueAnimation);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ResetAnimation);

void stage_CalcAnimationNoParent(int val) {
    D_00631D54 = val;
}

extern void *func_0013ECF8(void *obj);
extern void *isysGObjRemoveObjDL(int a0);

void stage_CalcAnimationParent(int a0, int a1) {
    void *obj;
    for (obj = isysGObjRemoveObjDL(a0); obj != 0; obj = func_0013ECF8(obj)) {
        void *node = *(void **)((char *)obj + 0x15C);
        if (node != 0) {
            void *dl = *(void **)((char *)node + 0x820);
            if (dl != 0) {
                void *x = *(void **)((char *)node + 0x824);
                if (x != 0) {
                    if (*(short *)((char *)dl + 0x30) == a0) {
                        *(long long *)((char *)x + 0x30) =
                            (*(long long *)((char *)x + 0x30) & ~0x04000000) |
                            ((long long)(a1 & 1) << 26);
                    }
                }
            }
        }
    }
}

void stage_DispAnimation(char *a0, float f12)
{
    if (f12 > 0.0f) {
        *((float *)(((char *)(*((int *)(a0 + 0x824)))) + 0x3C)) = f12;
        return;
    }
    {
        float src = *((float *)(((char *)(*((int *)(a0 + 0x820)))) + 0x3C));
        *((float *)(((char *)(*((int *)(a0 + 0x824)))) + 0x3C)) = src;
    }
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetScale);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimation);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimationDissolve);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakePlayBgAnimation);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_KillPlayBgAnimation);

extern char D_00555DB0[];
extern int bga_SetCamFrame__p4(int a0) __asm__("bga_SetCamFrame");
extern int font_CheckAlign__p4(int a0) __asm__("font_CheckAlign");
extern void func_001AD768__p4(void *a0, int a1) __asm__("func_001AD768");
extern void func_00263FF0__p4(void *a0, int a1, void *a2) __asm__("func_00263FF0");
extern void stage_KillPlayBgAnimation(int a0, int a1, int a2);

int stage_DispBgAnimation(int a0, int a1) {
    int i;
    char *e = (char *)D_00674058;
    for (i = 0; i < D_00633C54; i++, e += 0x290) {
        int *entry1 = *(int **)(e + 0x280);
        if (a0 == entry1[0x58 / 4]) {
            int mode = *(int *)(e + 0x28C) >> 30;
            switch (mode) {
                case 0:
                    if (bga_SetCamFrame__p4(*(int *)(e + 0x284)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
                case 1:
                    if (font_CheckAlign__p4(*(int *)(e + 0x288)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
            }
        }
    }
    debug_assertMessage(D_00555DB0);
    func_001AD768__p4(D_00555BF8, 0x38D);
    func_00263FF0__p4(D_00555BF8, 0x38D, D_00631D88);
    return 0;
}

void stage_SetCameraForceOff(void)
{
    func_001FAA58();
    if (D_00274ED4[0] != 0) return;
    func_00117768();
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFinish);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFrame);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetLoopFlag);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetFrameStep);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetParentOfGObj);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetParentOfGObjWithLocalRotationFlag);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetLocalizeGeometry);

void stage_KillPlayBgAnimationIfOverMaxCount(int **self)
{
    int *node = *self;
    int *next;
    int *prev;
    if (node == 0) return;
    next = (int *)node[0x10 / 4];
    if (next != 0) {
        next[0x14 / 4] = node[0x14 / 4];
    } else {
        D_00633C58 = node[0x14 / 4];
        __asm__ __volatile__("" ::: "memory");
        node = *(int * volatile *)self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (D_00633C58 != 0) {
        ((int *)D_00633C58)[0x10 / 4] = 0;
    }
    resetmallocseki(*self);
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_CheckAnimationFrameIn);

void func_0012AA78(int a0, int a1, int a2, int a3)
{
    font_GetWidth(a0, a1, a2, a3);
}

int func_0012AA80(int key)
{
    int count = *(volatile int *)&D_00633C54;
    int i = 0;
    char *e = (char *)D_00674058;
    if (count > 0) {
        do {
            int *entry1 = *(int **)(e + 0x280);
            if (key == entry1[0x58 / 4]) {
                int v = *(int *)(e + 0x28C) >> 30;
                switch (v) {
                case 0: return bga_SetCamFrame(*(int *)(e + 0x284));
                case 1: return font_CheckAlign(*(int *)(e + 0x288));
                }
            }
            i++;
            e += 0x290;
        } while (i < count);
    }
    debug_assertMessage(D_00555D78);
    func_001AD768(D_00555BF8, 0x360);
    func_00263FF0(D_00555BF8, 0x360, D_00631D88);
    return 0;
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AB50);

void func_0012ABE0(int key, int a1)
{
    int count = *(volatile int *)&D_00633C54;
    int i;
    char *e = (char *)D_00674058;
    for (i = 0; i < count; i++, e += 0x290) {
        int *p = *(int **)(e + 0x280);
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&D_00633C54)));
            count = *p;
        }
    }
}

void func_0012AC28(int target, int val)
{
    int n = D_00633C54;
    char *p = (char *)D_00674058;
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

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012AC70);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", func_0012ACD8);

