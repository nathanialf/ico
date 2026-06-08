#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_SetCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_InitData);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_initLightEnvelope);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_ApplyDObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetExtMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetGizmoMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_setCounter);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_calcEnvelope);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", _RotTransCurrentMatrixYXZ);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_CalcObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_resetObjectCounter);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_SetFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_CalcAnimation);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_CalcSdfCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_addLightning);

extern int D_0062C254;

void bga_DispLightning(void) {
    D_0062C254 = 0;
}

extern int D_0062BA98;
extern int D_0062BAA0;
extern int D_0070A4B0[];
extern void func_001189D0(void *dst, void *src);

int bga_ResetCamera(void *p)
{
    int v = D_0062C254;
    if (v != 0) {
        func_001189D0(p, D_0070A4B0);
        v = D_0062C254;
    } else {
        D_0062BA98 = 0;
    }
    return v != 0 && D_0062BAA0 == 0;
}

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_InitSdfCamera);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_SetCamFrame);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_CheckAnimationFinish);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_CheckAnimationFrame);


/* recovered struct shapes */
typedef struct {
    unsigned long long f_8;  /* 0x08 */
    unsigned long long f_10;  /* 0x10 */
    unsigned long long f_18;  /* 0x18 */
    unsigned long long f_20;  /* 0x20 */
    unsigned long long f_28;  /* 0x28 */
} S_004C3710;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613400;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006134D0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00613530;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_006135C0;  /* stride 0x4 */

/* end struct shapes */
