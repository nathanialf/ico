#include "common.h"

extern void func_0010F9D0(void);

void before_DrawPolygon(void) {
    func_0010F9D0();
}

extern void func_00118068(void);
extern void _PopCurrentMatrix(void *a0);
extern void gif_MakeSpriteOffset(void *a0, void *a1, void *a2, void *a3, int b0, int b1, int b2, int b3, int last);

void after_DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5) {
    func_00118068();
    _PopCurrentMatrix(a5);
    gif_MakeSpriteOffset(a0, a1, a2, a3, a4[0], a4[1], a4[2], a4[3], 1);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", _IsInScreen2);

extern void func_002400F8(void *a0);
extern void func_0023FE08(void *a0, void *a1, void *a2);
extern void func_002408D0(void *a0, void *a1, void *a2, int a3);
extern void func_00192A38(void *a0);
extern char *D_00629C70;

void before_DrawLine(void *a0, void *a1) {
    float buf[16];
    func_002400F8(buf);
    func_0023FE08(buf, D_00629C70 + 0x80, buf);
    func_0023FE08(buf, D_00629C70 + 0xC0, buf);
    func_002408D0(a0, buf, a1, 1);
    func_00192A38(a0);
}

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", after_DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", DrawPolygon);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", do_DrawLine);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", IsPointIsInScreen);

INCLUDE_ASM("asm/aug6/nonmatchings/omori/src/poly-flat", func_001945F8);

extern void *D_00629E00;
extern int iosPadStickCameraCoord(void *a0, int a1, int a2, void *a3);
extern void iosPadNormalizeStick(void *a0);
extern void iosPadActRequest(void *a0, void *a1, int a2, int a3, int a4, int a5);
extern void GetOrientOfWallOfGObj(void *a0, void *a1);
extern int actBoyRun(void *a0, void *a1);
extern float D_0062932C;
extern void BeforeFunc2(void *a0, void *a1);
extern void *D_00629E10;

void func_001946F8(void *a0) {
    char *ctrl = *(char **)((char *)a0 + 0x164);
    if (a0 == D_00629E00) {
        char *p2C8 = ctrl + 0x2C8;
        char *p328 = ctrl + 0x328;
        int buf[4];
        iosPadStickCameraCoord(p2C8, 0, 0, ctrl + 0x1D8);
        iosPadNormalizeStick(p2C8);
        iosPadActRequest(p2C8, p328, 0, 2, 2, 0);
        GetOrientOfWallOfGObj(buf, a0);
        *(int *)(ctrl + 0x330) = actBoyRun(buf, p328);
        if (*(float *)(ctrl + 0x33C) > D_0062932C) {
            BeforeFunc2(ctrl + 0x100, p328);
        }
    } else if (a0 == D_00629E10) {
        iosPadStickCameraCoord(ctrl + 0x2C8, 0, 1, ctrl + 0x1D8);
    } else {
        iosPadStickCameraCoord(ctrl + 0x2C8, 0, 1, ctrl + 0x1D8);
    }
}

extern void InitMotionOrient(void);

void func_001947F8(void) {
    InitMotionOrient();
}


/* recovered struct shapes */
typedef struct {
    unsigned int       f_0;  /* 0x00 */
} S_bl_00555170;  /* stride 0x4 */

/* end struct shapes */
