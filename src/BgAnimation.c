#include "common.h"

/* .data — carved VMA 0x4EE5B0..0x4EE5F0, bytes verified against
   baserom/pal/baseelf.rom.  D_004EE5B0 is the 0x30-byte default record
   bga_InitData block-copies into its mallocseki() allocation (two
   (0,0,0,1.0f) vectors then four words); D_004EE5E0 is the (0,0,0,1.0f)
   position vector bga_ApplyDObject hands to
   SetParticleEffectActiveSensing. */
unsigned int D_004EE5B0[12] = {
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
    0x00000000, 0xFFFFFFFF, 0x00000001, 0x00000000,
};
float D_004EE5E0[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_InitData);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_initLightEnvelope);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_ApplyDObject);
ASM_LIT4_SLOT(D_00639724, 1.2075409f);
ASM_LIT4_SLOT(D_00639728, 182.04445f);
ASM_LIT4_SLOT(D_0063972C, 182.04445f);
ASM_LIT4_SLOT(D_00639730, 0.1f);
ASM_LIT4_SLOT(D_00639734, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotion);
ASM_LIT4_SLOT(D_00639738, 1.2075409f);
ASM_LIT4_SLOT(D_0063973C, 182.04445f);
ASM_LIT4_SLOT(D_00639740, 182.04445f);
ASM_LIT4_SLOT(D_00639744, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotionParticle);
ASM_LIT4_SLOT(D_00639748, 1.2075409f);
ASM_LIT4_SLOT(D_0063974C, 182.04445f);
ASM_LIT4_SLOT(D_00639750, 182.04445f);
ASM_LIT4_SLOT(D_00639754, 0.1f);
ASM_LIT4_SLOT(D_00639758, 182.04445f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetMotionLightning);
ASM_LIT4_SLOT(D_0063975C, 1.2075409f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetExtMotion);
ASM_LIT4_SLOT(D_00639760, 1.2075409f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_GetGizmoMotion);
ASM_LIT4_SLOT(D_00639764, 0.82812935f);
ASM_LIT4_SLOT(D_00639768, 2.66f);
ASM_LIT4_SLOT(D_0063976C, 0.82812935f);
ASM_LIT4_SLOT(D_00639770, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_calcEnvelope);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", _RotTransCurrentMatrixYXZ);
ASM_LIT4_SLOT(D_00639774, 0.41406468f);
ASM_LIT4_SLOT(D_00639778, 0.82812935f);
ASM_LIT4_SLOT(D_0063977C, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcObject);
ASM_LIT4_SLOT(D_00639780, 0.82812935f);
ASM_LIT4_SLOT(D_00639784, 0.82812935f);
ASM_LIT4_SLOT(D_00639788, 0.82812935f);
ASM_LIT4_SLOT(D_0063978C, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_resetObjectCounter);
ASM_LIT4_SLOT(D_00639790, 0.82812935f);
ASM_LIT4_SLOT(D_00639794, 0.82812935f);
ASM_LIT4_SLOT(D_00639798, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_SetFrame);
ASM_LIT4_SLOT(D_0063979C, 0.82812935f);
ASM_LIT4_SLOT(D_006397A0, 0.82812935f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcAnimation);
ASM_LIT4_SLOT(D_006397A4, 0.82812935f);
ASM_LIT4_SLOT(D_006397A8, 0.82812935f);
ASM_LIT4_SLOT(D_006397AC, 1.2075409f);
ASM_LIT4_SLOT(D_006397B0, 1.2075409f);
ASM_LIT4_SLOT(D_006397B4, 182.04445f);
ASM_LIT4_SLOT(D_006397B8, 3.1415927f);
ASM_LIT4_SLOT(D_006397BC, 10430.378f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_CalcSdfCamera);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_addLightning);
ASM_LIT4_SLOT(D_006397C0, 0.01f);
INCLUDE_ASM("asm/nonmatchings/src/BgAnimation", bga_DispLightning);
extern int D_0063C4B4;

void bga_ResetCamera(void) {
    D_0063C4B4 = 0;
}
extern int D_0063BCC0;
extern int D_0063BCC8;
extern int D_0063C4B4;
extern int D_007281F0[];
extern void _CopyMatrix(void *dst, void *src);

int bga_GetCameraMatrix(void *p)
{
    int v = D_0063C4B4;
    if (v != 0) {
        _CopyMatrix(p, D_007281F0);
        v = D_0063C4B4;
    } else {
        D_0063BCC0 = 0;
    }
    return v != 0 && D_0063BCC8 == 0;
}
extern char D_0063BCE0[];
extern char D_006215D8[];
extern char D_00621598[];
extern char D_0063BCD8[];
char *bga_InitSdfCamera(char *a0) {
    if (strncmp(a0, D_0063BCE0, 3) != 0) {
        debug_StdPrintfDummy(D_006215D8);
        debug_assert(D_00621598, 0x415);
        __assert(D_00621598, 0x415, D_0063BCD8);
    }
    return a0;
}
extern int D_0028F4C0[];
extern int D_0063C4B4;
extern int D_0063BCB8;
extern int GlobalTimer;
extern float D_00728230[];
extern float D_00728220[];
extern void _CopyVector(void *dst, void *src);

static inline float bga_palFrame(float f)
{
    if (D_0028F4C0[0]) {
        f *= 0.82812935f;
    }
    return f;
}

void bga_SetCamFrame(char *p, int frame, int mode)
{
    *(int *)(p + 0xC) = mode;
    D_0063C4B4 = 1;
    if (mode == 1) {
        GlobalTimer = mode;
        D_0063BCB8 = mode;
        _CopyVector(D_00728230, D_00728220);
    }
    if (frame == -1) {
        *(float *)(p + 8) = bga_palFrame(*(int *)(p + 4));
    } else {
        *(float *)(p + 8) = bga_palFrame(frame);
    }
}

int bga_CheckAnimationFinish(char *p)
{
    float f = *(float *)(p + 0x18);
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0]) {
        if (f * 0.82812935f <= t || p[0xA] != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p[0xA] != 1) {
            r = 1;
        }
    }
    return r;
}

int bga_CheckAnimationFrame(char *p, int frame, int reset)
{
    float f = frame;
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0]) {
        if (f * 0.82812935f <= t || p[0xA] != 1) {
            r = 1;
        }
    } else {
        if (f <= t || p[0xA] != 1) {
            r = 1;
        }
    }
    if (r && reset) {
        p[0xA] = 0;
    }
    return r;
}
int bga_CheckAnimationFrameIn(char *p, int in, int out)
{
    float a = in;
    float t = *(float *)(p + 0x20);
    int r = 0;

    if (D_0028F4C0[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (D_0028F4C0[0] ? t < b * 0.82812935f : t < b) {
            r = p[0xA] == 1;
        }
    }
    return r;
}

int bga_CheckSdfCameraFinish(char *p)
{
    float f = *(int *)(p + 4);
    float t = *(float *)(p + 8);

    if (D_0028F4C0[0]) {
        return f * 0.82812935f <= t;
    }
    return f <= t;
}

int bga_CheckSdfCameraFrame(char *p, int frame, int reset)
{
    float f = frame;
    float t = *(float *)(p + 8);
    int r;

    if (D_0028F4C0[0]) {
        r = f * 0.82812935f <= t;
    } else {
        r = f <= t;
    }
    if (r && reset) {
        *(int *)(p + 0xC) = 0;
    }
    return r;
}
int bga_CheckSdfCameraFrameIn(char *p, int in, int out)
{
    float t = *(float *)(p + 8);
    float a = in;
    int r = 0;

    if (D_0028F4C0[0] ? a * 0.82812935f <= t : a <= t) {
        float b = out;

        if (D_0028F4C0[0] ? t < b * 0.82812935f : t < b) {
            r = 1;
        }
    }
    return r;
}
void bga_SetCameraForceOff(void) {
    D_0063BCC8 = 1;
}
extern int D_0063BCCC;

void bga_InitBGA(void)
{
    D_0063BCC8 = 0;
    D_0063BCCC = 0;
}
extern int D_0063BCC4;

void bga_SetUniqAnimationFlag(int val) {
    D_0063BCC4 = val;
}
extern int D_0028F4D4[];
extern void freeseki(void *p);

void bga_ResetAnimation(void) {
    void *p;
    D_0063C4B4 = 0;
    if (D_0028F4D4[0] != 0) {
        return;
    }
    p = (void *)D_0063BCCC;
    D_0063BCCC = 0;
    if (p == 0) {
        return;
    }
    do {
        void *next = *(void **)((char *)p + 0x154);
        freeseki(p);
        p = next;
    } while (p != 0);
}
extern float D_0063BCC0__pn __asm__("D_0063BCC0");

float bga_GetZoom(void)
{
    return D_0063BCC0__pn;
}
