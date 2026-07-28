#include "common.h"


extern void _SetCurrentMatrix();
extern int D_004C6160[];
INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blur);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", auraInspireBefore);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceCopyAlphaChannelOfWork1ToWork0);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyAlphaChannelOfWork0ToFeedBackArea);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", copyCurrentFBToFeedBackArea);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blendWork0ToWork1);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", parallelAddFeedBackAreaToWork0);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", blurBlendFeedBackAreaToWork1);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", testAA);

void subWork1ToCurrentFB(int a0)
{
    _SetCurrentMatrix(a0, D_004C6160);
}

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", auraInspireAfter);

extern int D_004C6140[];
extern int D_004C6150[];
extern int D_004C6170[];
extern float D_006313DC;
extern int D_00631970;
extern void _InverseCurrentMatrix(void *a0, void *a1, float f);
extern void _PushVu0Registers(void *a0, void *a1, float f);
extern void _RotTransPersCurrentMatrix(void *a0, void *a1, void *a2);
extern void _SetCurrentMatrix__p4(int a0, void *a1) __asm__("_SetCurrentMatrix");
extern void func_00118648(void *a0, int a1, void *a2);
extern void mc_SetMicroCode(void *a0, void *a1);

void cleanUpFB(void) {
    float buf[4];
    _SetCurrentMatrix__p4((int)buf, D_004C6160);
    _InverseCurrentMatrix(buf, buf, D_006313DC);
    buf[3] = 1.0f;
    func_00118648(buf, D_00631970 + 0x100, buf);
    _PushVu0Registers(buf, buf, 1.0f / buf[3]);
    _RotTransPersCurrentMatrix(buf, buf, D_004C6170);
    mc_SetMicroCode(D_004C6140, buf);
    func_00118648(D_004C6150, D_00631970 + 0x80, D_004C6160);
}

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", fillWork2);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispSun);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteBackLightShadowToFB);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeMaskPatternToWork2);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareBefore);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceWork2ToWork0);

