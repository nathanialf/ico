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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", stage_DispAnimation);

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

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/StageAnimation", func_0012AAB8);

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
