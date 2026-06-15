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

extern void _SetCurrentMatrix(int a0, void *a1);
extern int D_004C2250[];

void subWork1ToCurrentFB(int a0) {
    _SetCurrentMatrix(a0, D_004C2250);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", auraInspireAfter);

extern float D_006296BC;
extern int D_00629C70;
extern int D_004C2230[];
extern int D_004C2240[];
extern int D_004C2250[];
extern int D_004C2260[];
extern void _SetCurrentMatrix(int a0, void *a1);
extern void _InverseCurrentMatrix(void *a0, void *a1, float f);
extern void func_00118A70(void *a0, int a1, void *a2);
extern void _PushVu0Registers(void *a0, void *a1, float f);
extern void _RotTransPersCurrentMatrix(void *a0, void *a1, void *a2);
extern void mc_SetMicroCode(void *a0, void *a1);

void cleanUpFB(void) {
    float buf[4];
    _SetCurrentMatrix((int)buf, D_004C2250);
    _InverseCurrentMatrix(buf, buf, D_006296BC);
    buf[3] = 1.0f;
    func_00118A70(buf, D_00629C70 + 0x100, buf);
    _PushVu0Registers(buf, buf, 1.0f / buf[3]);
    _RotTransPersCurrentMatrix(buf, buf, D_004C2260);
    mc_SetMicroCode(D_004C2230, buf);
    func_00118A70(D_004C2240, D_00629C70 + 0x80, D_004C2250);
}

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", fillWork2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", dispSun);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", pasteBackLightShadowToFB);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", makeMaskPatternToWork2);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", makeFullScreenFlareBefore);

INCLUDE_ASM("asm/aug6/nonmatchings/sugipon/src/staticBlur", reduceWork2ToWork0);


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
