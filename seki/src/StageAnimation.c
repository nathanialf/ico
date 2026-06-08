#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_MakeGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ApplyData);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_Init);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ContinueAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_ResetAnimation);

extern int D_0062A054;

void stage_CalcAnimationNoParent(int a0) {
    D_0062A054 = a0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CalcAnimationParent);

typedef struct { char _0[0x3C]; float f3C; } AnimNode;
typedef struct { char _0[0x810]; AnimNode *f810; AnimNode *f814; } Stage;

void stage_DispAnimation(Stage *a0, float f) {
    if (f > 0.0f) {
        a0->f814->f3C = f;
    } else {
        a0->f814->f3C = a0->f810->f3C;
    }
}

extern int D_0062A050;

void stage_SetScale(void) {
    D_0062A050 = 0;
    D_0062A054 = 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_PlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_PlayBgAnimationDissolve);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_MakePlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_KillPlayBgAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_DispBgAnimation);

extern void func_001F76C0(void);

void stage_SetCameraForceOff(void) {
    func_001F76C0();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFinish);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetLoopFlag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetFrameStep);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetParentOfGObj);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetParentOfGObjWithLocalRotationFlag);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_SetLocalizeGeometry);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_KillPlayBgAnimationIfOverMaxCount);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_CheckAnimationFrameIn);

extern void font_GetWidth(void);

void func_0012A950(void) {
    font_GetWidth();
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012A958);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AA28);

extern int D_0062BF54;
extern char D_0066DBD8[];

void func_0012AAB8(int key, int a1)
{
    int count = *(volatile int *)&D_0062BF54;
    int i;
    char *e = (char *)D_0066DBD8;
    for (i = 0; i < count; i++, e += 0x290) {
        int *p = *(int **)(e + 0x280);
        if (key == p[0x58 / 4]) {
            p[0x50 / 4] = a1;
            p = &(*((volatile int *)(&D_0062BF54)));
            count = *p;
        }
    }
}


/* parked: needs real matching. See tough_nuts/func_0012AB00/notes.md */
INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AB00);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AB48);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012ABB0);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
    unsigned long long f_30;  /* 0x30 */
    unsigned long long f_38;  /* 0x38 */
} S_0054FF20;

typedef struct {
    unsigned int       f_40;  /* 0x40 */
    unsigned int       f_44;  /* 0x44 */
    unsigned int       f_48;  /* 0x48 */
    unsigned char      f_4C;  /* 0x4C */
    unsigned int       f_54;  /* 0x54 */
} S_005F88A8;  /* stride 0x5C */

typedef struct {
    unsigned int       f_280;  /* 0x280 */
    unsigned int       f_284;  /* 0x284 */
    unsigned int       f_28C;  /* 0x28C */
} S_0066DBD8;  /* stride 0x290 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0066DE58;  /* stride 0x-1 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_002725B0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_0054FDA4;  /* stride 0x10 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054FD40;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_0054FD70;  /* stride 0x4 */

/* end struct shapes */
