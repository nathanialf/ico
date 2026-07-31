#include "common.h"







extern const char D_00555BF8[];
extern void func_001AD768();
extern int bga_SetCamFrame();
extern const char D_00631D88[];
extern void func_00263FF0(char *file, int line, char *msg);
extern void debug_assertMessage();
extern const char D_00555D78[];
extern int font_CheckAlign();
extern char D_00674058[];
extern int D_00633C54;
extern void font_GetWidth();
extern int *D_00633C58;
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

/* StageAnimation .rodata run 0x555938..0x555E70 -- byte-verified against
 * baseelf; defs interleave with INCLUDE_ASM stubs so .o section order ==
 * VMA order */
const unsigned int D_00555938[0x16] = { 0x00000000, 0x00000001, 0x00000003, 0x00000004, 0x00000005, 0x00000001, 0x00000002, 0x00000000, 0x00000005, 0x00000003, 0x00000003, 0x00000004, 0x00000000, 0x00000001, 0x00000002, 0x00000004, 0x00000005, 0x00000003, 0x00000002, 0x00000000, 0x00000000, 0x00000000 };

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_Init);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_SetAnimation);

/* D_005559E8/F0/F4 hand-assembled as one contiguous block: dlabel (used by
 * INCLUDE_RODATA and gcc -fdata-sections alike) forces .align 3 on every
 * per-symbol section, but D_005559F4 sits at a VMA only 4-aligned (right
 * after the 4-byte D_005559F0) -- no gap in the ROM to absorb an 8-align
 * pad. Emitting the run as one un-aligned block starting from the already
 * 8-aligned D_005559E8 sidesteps it; see include/labels.inc dlabel comment. */
__asm__(
    ".section .rodata.D_005559E8,\"a\",@progbits\n"
    ".globl D_005559E8\n"
    ".type D_005559E8, @object\n"
    "D_005559E8:\n"
    "    .word D_00555B10\n"
    "    .word D_002751CC\n"
    ".size D_005559E8, 8\n"
    ".globl D_005559F0\n"
    ".type D_005559F0, @object\n"
    "D_005559F0:\n"
    "    .word 0x00000000\n"
    ".size D_005559F0, 4\n"
    ".globl D_005559F4\n"
    ".type D_005559F4, @object\n"
    "D_005559F4:\n"
    "    .word 0x00000080\n"
    "    .word D_00555AF8\n"
    "    .word 0x002751E0\n"
    "    .word 0x00000000\n"
    "    .word 0x000000FF\n"
    "    .word D_00555AE0\n"
    "    .word 0x002751E4\n"
    "    .word 0x00000000\n"
    "    .word 0x000000FF\n"
    "    .word D_00555AC8\n"
    "    .word 0x002751E8\n"
    "    .word 0x00000000\n"
    "    .word 0x000000FF\n"
    "    .word D_00555AB0\n"
    "    .word 0x002751D0\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    "    .word D_00555A98\n"
    "    .word 0x002751D4\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    "    .word D_00555A80\n"
    "    .word 0x002751D8\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    "    .word D_00555A68\n"
    "    .word 0x002751DC\n"
    "    .word 0x00000000\n"
    "    .word 0x00000080\n"
    ".size D_005559F4, 116\n"
    ".section .text\n"
);
const char D_00555A68[0x18] = " Shadow Blend 1/64 ";
const char D_00555A80[0x18] = " Shadow Blend 1/16 ";
const char D_00555A98[0x18] = " Shadow Blend 1/4  ";
const char D_00555AB0[0x18] = " Shadow Blend 1/1  ";
const char D_00555AC8[0x18] = " Shadow Color B    ";
const char D_00555AE0[0x18] = " Shadow Color G    ";
const char D_00555AF8[0x18] = " Shadow Color R    ";
const char D_00555B10[0x18] = " Shadow Depth      ";
INCLUDE_RODATA("asm/nonmatchings/src/StageAnimation", D_00555B28);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ContinueAnimation);

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_ResetAnimation);

const unsigned int D_00555B70[0x10] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000 };

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

extern int D_00631D50;

void stage_SetScale(int a0) {
    void *obj;
    D_00631D50 = 0;
    D_00631D54 = 0;
    for (obj = isysGObjRemoveObjDL(a0); obj != 0; obj = func_0013ECF8(obj)) {
        void *node = *(void **)((char *)obj + 0x15C);
        if (node != 0) {
            void *dl = *(void **)((char *)node + 0x820);
            if (dl != 0) {
                void *x = *(void **)((char *)node + 0x824);
                if (x != 0) {
                    *(long long *)((char *)x + 0x30) &= ~0x04000000;
                }
            }
        }
    }
}

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimation);

const char D_00555BF8[0x18] = "src/StageAnimation.c";
const char D_00555C10[0x28] = "Too much Stage Animation Objects.\n";

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_PlayBgAnimationDissolve);

const char D_00555C68[0x30] = "stgBgas が%d有り MAX_ANIM_KIND %dを越えました\n\0\0";
const char D_00555C98[0x30] = "1ステージ中の BgAnimation の種類が多すぎます\n\0\0\0";
const char D_00555CC8[0x30] = "stgBgas が%d有り MAX_ANIM_GOBJ %dを越えました\n\0\0";

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_MakePlayBgAnimation);

const unsigned int D_00555D20[0x16] = { 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x3F800000, 0x3F800000, 0x3F800000, 0x3F800000, 0x00000001, 0x00000000, 0x00000000, 0x00000000, 0x656C6C49, 0x206C6167, 0x756F7247, 0x6F4E2070, 0x6425202E, 0x0000000A };
const char D_00555D78[0x38] = "stage_CheckAnimationFinish:illegal Animation No.\n";
const char D_00555DB0[0x30] = "stage_ContinueAnimation:illegal Animation No.\n";
const char D_00555DE0[0x48] = "指定したIDが存在しないか、アニメーションが読み込まれていません.\n\0\0\0\0\0\0\0\0";
const char D_00555E28[0x48] = "ステージセグメントにメモリが確保できません.(ヒープメモリ不足)\n\0\0\0\0\0\0\0\0\0\0";

INCLUDE_ASM("asm/nonmatchings/src/StageAnimation", stage_KillPlayBgAnimation);

extern int bga_SetCamFrame(int a0);
extern int font_CheckAlign(int a0);
extern void func_001AD768(void *a0, int a1);
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
                    if (bga_SetCamFrame(*(int *)(e + 0x284)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
                case 1:
                    if (font_CheckAlign(*(int *)(e + 0x288)) != 0) {
                        stage_KillPlayBgAnimation(a0, 0, -1);
                        stage_KillPlayBgAnimation(a1, 1, 0);
                        return 1;
                    }
                    return 0;
            }
        }
    }
    debug_assertMessage(D_00555DB0);
    func_001AD768(D_00555BF8, 0x38D);
    func_00263FF0(D_00555BF8, 0x38D, D_00631D88);
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
        D_00633C58 = (int *)node[0x14 / 4];
        node = *self;
    }
    prev = (int *)node[0x14 / 4];
    if (prev != 0) {
        prev[0x10 / 4] = node[0x10 / 4];
    }
    if (D_00633C58 != 0) {
        D_00633C58[0x10 / 4] = 0;
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

