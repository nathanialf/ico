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

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", cleanUpFB);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", fillWork2);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", dispSun);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", pasteBackLightShadowToFB);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeMaskPatternToWork2);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", makeFullScreenFlareBefore);

INCLUDE_ASM("asm/nonmatchings/src/staticBlur", reduceWork2ToWork0);

