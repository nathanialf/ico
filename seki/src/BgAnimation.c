#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_SetCameraMatrix);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_InitData);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_initLightEnvelope);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_ApplyDObject);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetExtMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_GetGizmoMotion);

INCLUDE_ASM("asm/aug6/nonmatchings/seki/src/BgAnimation", bga_setCounter);

extern void func_001180D8(void *a0);
extern void _RemakeNormal(int a0);
extern void func_00118118(int a0);
extern int _Sqrt(int a0);

void bga_calcEnvelope(void *a0, short *a1) {
    func_001180D8(a0);
    _RemakeNormal(a1[2]);
    func_00118118(a1[0]);
    _Sqrt(a1[4]);
}

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

extern int func_00261748(void *a0, void *a1, int a2);
extern void debug_assertMessage();
extern void func_001AAD00(char *file, int line);
extern void func_00260380(char *file, int line, void *expr);
extern char D_0062D938[];
extern char D_0062D930[];
extern char D_006133E0[];
extern char D_00613428[];

void *bga_GetCameraMatrix(void *a0) {
    if (func_00261748(a0, D_0062D938, 3) != 0) {
        debug_assertMessage(D_00613428);
        func_001AAD00(D_006133E0, 0x383);
        func_00260380(D_006133E0, 0x383, D_0062D930);
    }
    return a0;
}

extern int D_00629CF0;
extern int D_0062C254;

void bga_InitSdfCamera(int *a0, int a1, int a2) {
    a0[3] = a2;
    D_0062C254 = 1;
    D_00629CF0 = 1;
    if (a1 == -1) {
        *(float *)(a0 + 2) = (float)a0[1];
    } else {
        *(float *)(a0 + 2) = (float)a1;
    }
}

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
