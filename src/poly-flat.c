#include "common.h"



extern void InitMotionOrient();
extern void func_0010F630();
void before_DrawPolygon(int a0, int a1, int a2, int a3)
{
    func_0010F630(a0, a1, a2, a3);
}

extern void _PopCurrentMatrix(void *a0);
extern void func_00117C40(void);
extern void gif_MakeSpriteOffset(void *a0, void *a1, void *a2, void *a3, int b0, int b1, int b2, int b3, int last);

void after_DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5) {
    func_00117C40();
    _PopCurrentMatrix(a5);
    gif_MakeSpriteOffset(a0, a1, a2, a3, a4[0], a4[1], a4[2], a4[3], 1);
}

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", _IsInScreen2);

extern char *D_00631970;
extern void func_00195238(void *a0);
extern void func_002438E8(void *a0, void *a1, void *a2);
extern void func_00243BD8(void *a0);
extern void func_002443B0(void *a0, void *a1, void *a2, int a3);

void before_DrawLine(void *a0, void *a1) {
    float buf[16];
    func_00243BD8(buf);
    func_002438E8(buf, D_00631970 + 0x80, buf);
    func_002438E8(buf, D_00631970 + 0xC0, buf);
    func_002443B0(a0, buf, a1, 1);
    func_00195238(a0);
}

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", after_DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", DrawPolygon);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", do_DrawLine);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", IsPointIsInScreen);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", func_00196E78);

INCLUDE_ASM("asm/nonmatchings/src/poly-flat", func_00196F78);

void func_00197078(int a0, int a1, int a2, int a3)
{
    InitMotionOrient(a0, a1, a2, a3);
}

