#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", blur);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", auraInspireBefore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", reduceCopyAlphaChannelOfWork1ToWork0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", copyAlphaChannelOfWork0ToFeedBackArea);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", copyCurrentFBToFeedBackArea);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", blendWork0ToWork1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", parallelAddFeedBackAreaToWork0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", blurBlendFeedBackAreaToWork1);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", testAA);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", subWork1ToCurrentFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", auraInspireAfter);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", cleanUpFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", fillWork2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", dispSun);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", pasteBackLightShadowToFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", makeMaskPatternToWork2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", makeFullScreenFlareBefore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", reduceWork2ToWork0);
