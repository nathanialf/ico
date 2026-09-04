#include "common.h"

extern void gif_SetAlpha();
extern void gif_StartPacketPri();

void before_DrawPolygon(void)
{
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 2, 0x40);
}
extern void gif_EndPacket();

void after_DrawPolygon(int a0, int a1, int a2, int a3)
{
    gif_EndPacket(a0, a1, a2, a3);
}
INCLUDE_ASM("asm/nonmatchings/src/poly-flat", _IsInScreen2);
extern void CopyMatrix(void *dst, void *src);
extern int D_002A6030[];

void before_DrawLine(int a0)
{
    CopyMatrix(D_002A6030, a0);
    gif_StartPacketPri(0xB);
}
void after_DrawLine(int a0, int a1, int a2, int a3)
{
    gif_EndPacket(a0, a1, a2, a3);
}
extern void _InitCurrentMatrix(void);
extern void _SetCurrentMatrix(void *a0);
extern void gif_DrawPolyF4(void *a0, void *a1, void *a2, void *a3, int b0, int b1, int b2, int b3, int last);

void DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5) {
    _InitCurrentMatrix();
    _SetCurrentMatrix(a5);
    gif_DrawPolyF4(a0, a1, a2, a3, a4[0], a4[1], a4[2], a4[3], 1);
}
INCLUDE_ASM("asm/nonmatchings/src/poly-flat", do_DrawLine);
extern char *D_00639CF0;
extern void _IsInScreen2(void *a0);
extern void func_0025D440(void *a0, void *a1, void *a2);
extern void func_0025DF08(void *a0, void *a1, void *a2, int a3);
extern void sceVu0UnitMatrix(void *a0);

void IsPointIsInScreen(void *a0, void *a1) {
    float buf[16];
    sceVu0UnitMatrix(buf);
    func_0025D440(buf, D_00639CF0 + 0x80, buf);
    func_0025D440(buf, D_00639CF0 + 0xC0, buf);
    func_0025DF08(a0, buf, a1, 1);
    _IsInScreen2(a0);
}
