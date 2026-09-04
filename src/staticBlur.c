#include "common.h"


extern void _NormalizeVector();
extern int D_004C6160[];
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blur);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceWork2ToWork0);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceCopyAlphaChannelOfWork1ToWork0);
ASM_LIT4_SLOT(D_006313D8, 0.9f);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyAlphaChannelOfWork0ToFeedBackArea);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteFullScreenFlare);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyToWork_233);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyToWork2);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteToFB);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", testAA);

void subWork1ToCurrentFB(int a0)
{
    _NormalizeVector(a0, D_004C6160);
}

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", MotionBlur);

extern int D_004C6140[];
extern int D_004C6150[];
extern int D_004C6170[];
extern int D_00631970;
extern void _ScaleVector(void *a0, void *a1, float f);
extern void _ScaleVectorXYZ(void *a0, void *a1, float f);
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);
extern void _NormalizeVector(int a0, void *a1);
extern void _ApplyMatrix(void *a0, int a1, void *a2);
extern void _FTOI0Vector(void *a0, void *a1);

void calcSun(void) {
    float buf[4];
    _NormalizeVector((int)buf, D_004C6160);
    _ScaleVector(buf, buf, 1000000.0f);
    buf[3] = 1.0f;
    _ApplyMatrix(buf, D_00631970 + 0x100, buf);
    _ScaleVectorXYZ(buf, buf, 1.0f / buf[3]);
    _AddVectorXYZ(buf, buf, D_004C6170);
    _FTOI0Vector(D_004C6140, buf);
    _ApplyMatrix(D_004C6150, D_00631970 + 0x80, D_004C6160);
}

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", colorSetting);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispPostInfo);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteBackLightShadowToFB);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeMaskPatternToWork2);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareBefore);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", InitStaticBlur);


/* .data — carved VMA 0X4C61A0..0X4C61F0 (5 symbols), bytes verified against baserom/baseelf.rom */
unsigned int D_004C61A0[4] = {
    0xFFFFF800, 0xFFFFFC00, 0x00001000, 0x00000800,
};
unsigned int D_004C61B0[4] = {
    0xFFFFF800, 0xFFFFFC00, 0x00000400, 0x00000200,
};
unsigned int D_004C61C0[4] = {
    0xFFFFF800, 0xFFFFFC00, 0x00001000, 0x00000800,
};
unsigned int D_004C61D0[4] = {
    0xFFFFF804, 0xFFFFF804, 0x00001000, 0x00001000,
};
unsigned int D_004C61E0[4] = {
    0x00000000, 0x00000000, 0x00000000, 0x3F800000,
};
