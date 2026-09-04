#include "common.h"

struct D275 {
    char pad[0xEC];
    int field_EC;
    int field_F0;
    int field_F4;
    int field_F8;
};

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blur);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", auraInspireBefore);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceCopyAlphaChannelOfWork1ToWork0);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyAlphaChannelOfWork0ToFeedBackArea);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyCurrentFBToFeedBackArea);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blendWork0ToWork1);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", parallelAddFeedBackAreaToWork0);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blurBlendFeedBackAreaToWork1);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", testAA);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", subWork1ToCurrentFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", auraInspireAfter);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", cleanUpFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", fillWork2);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispSun);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteBackLightShadowToFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeMaskPatternToWork2);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareBefore);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceWork2ToWork0);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", eyeBlur);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareAfter);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteFullScreenFlare);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyToWork_233);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyToWork2);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteToFB);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", depthField);
extern int D_004ED050[];
extern void _NormalizeVector();

void GetSunWorldPos(int a0)
{
    _NormalizeVector(a0, D_004ED050);
}
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", MotionBlur);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", calcSun);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", colorSetting);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispPostInfo);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispFeedInfo);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", FullScreenEffectBefore);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", FullScreenEffectAfter);
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", InitStaticBlur);
void StaticBlur(void) {}
void StaticBlurDL(void) {}
extern int D_0063BB94;

void SetMotionBlur(int val) {
    D_0063BB94 = val;
}
extern int D_0028F808[];

void SetStaticBlur(int x) {
    D_0028F808[0] = x;
}
extern struct D275 D_0028F720;

void SetDepthFadeParam(float f12, float f13, int a0)
{
    D_0028F720.field_EC = (int)f12;
    D_0028F720.field_F0 = (int)f13;
    D_0028F720.field_F8 = a0;
}
extern float D_0063BB30;

void SetAuraInspireParam(float a0) {
    D_0063BB30 = a0;
}
extern int D_0063BB24;

void InitializeStaticBlur(void) {
    D_0063BB24 = 0;
}
extern int D_0028FF00[];
extern int D_0063BB1C;
extern int D_0063BB20;
extern int prim_InitFan2D(int a, float e, int *b, unsigned int c, int d);

void _initStaticBlur(void)
{
    D_0063BB1C = prim_InitFan2D(0x10, 80.0f, D_0028FF00, 0xFFFFFF80u, 0);
    D_0063BB20 = prim_InitFan2D(0x10, 80.0f, D_0028FF00, 0xFFFFFF80u, 0);
}
void SetAuraEffect(void) {}
