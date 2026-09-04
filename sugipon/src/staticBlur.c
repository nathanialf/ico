#include "common.h"

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", blur);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", reduceWork2ToWork0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", reduceCopyAlphaChannelOfWork1ToWork0);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", copyAlphaChannelOfWork0ToFeedBackArea);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", pasteFullScreenFlare);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", copyToWork_233);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", copyToWork2);


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", pasteToFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", testAA);

extern void _NormalizeVector(int a0, void *a1);
extern int D_004C2250[];

void subWork1ToCurrentFB(int a0) {
    _NormalizeVector(a0, D_004C2250);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", auraInspireAfter);

extern float D_006296BC;
extern int D_00629C70;
extern int D_004C2230[];
extern int D_004C2240[];
extern int D_004C2250[];
extern int D_004C2260[];
extern void _NormalizeVector(int a0, void *a1);
extern void _ScaleVector(void *a0, void *a1, float f);
extern void _ApplyMatrix(void *a0, int a1, void *a2);
extern void _ScaleVectorXYZ(void *a0, void *a1, float f);
extern void _AddVectorXYZ(void *a0, void *a1, void *a2);
extern void _FTOI0Vector(void *a0, void *a1);

void calcSun(void) {
    float buf[4];
    _NormalizeVector((int)buf, D_004C2250);
    _ScaleVector(buf, buf, D_006296BC);
    buf[3] = 1.0f;
    _ApplyMatrix(buf, D_00629C70 + 0x100, buf);
    _ScaleVectorXYZ(buf, buf, 1.0f / buf[3]);
    _AddVectorXYZ(buf, buf, D_004C2260);
    _FTOI0Vector(D_004C2230, buf);
    _ApplyMatrix(D_004C2240, D_00629C70 + 0x80, D_004C2250);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", colorSetting);


INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", dispPostInfo);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", pasteBackLightShadowToFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", makeMaskPatternToWork2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", makeFullScreenFlareBefore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", InitStaticBlur);


/* recovered struct shapes */
typedef struct {
    unsigned int       f_4;  /* 0x04 */
    unsigned int       f_8;  /* 0x08 */
    unsigned int       f_C;  /* 0x0C */
} S_004C2220;

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612DE0;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612E20;  /* stride 0x4 */

typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00612E40;  /* stride 0x4 */

/* end struct shapes */
