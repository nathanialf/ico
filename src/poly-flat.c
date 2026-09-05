#include "common.h"

extern void gif_SetAlpha();
extern void gif_StartPacketPri();
extern void gif_SetAlpha__pn(int a0, int a1, int a2) __asm__("gif_SetAlpha");
extern void gif_StartPacketPri__pn(int a0) __asm__("gif_StartPacketPri");
extern void gif_EndPacket();
extern void CopyMatrix(void *dst, void *src);
extern int drawline_ws_matrix[];
extern void _InitCurrentMatrix(void);
extern void _SetCurrentMatrix(void *a0);
extern void gif_DrawPolyF4(void *a0, void *a1, void *a2, void *a3, int b0, int b1, int b2, int b3, int last);
extern int _IsInScreen(int *p);
extern void sceVu0RotTransPers(void *a0, void *a1, void *a2, int a3);
extern void gif_MakeLine2D(int *v0, int *v1, int z0, int z1, unsigned char *col, int n);
extern char *matrixptr;
extern void _IsInScreen2(void *a0);
extern void func_0025D440(void *a0, void *a1, void *a2);
extern void sceVu0UnitMatrix(void *a0);
/* prototypes: their order is the inline tail's emission order */
void DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5);
void do_DrawLine(void *p0, void *p1, int *c);
void IsPointIsInScreen(void *a0, void *a1);
static inline unsigned char DrawLineTrans(int *dst, void *src)
{
    sceVu0RotTransPers(dst, drawline_ws_matrix, src, 1);
    return _IsInScreen(dst);
}
static inline void DrawLineOffset(int *p)
{
    p[0] -= 0x8000;
    p[1] -= 0x8000;
}
void before_DrawPolygon(void)
{
    gif_StartPacketPri(0xB);
    gif_SetAlpha(1, 2, 0x40);
}
void after_DrawPolygon(int a0, int a1, int a2, int a3)
{
    gif_EndPacket(a0, a1, a2, a3);
}
inline void DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5) {
    _InitCurrentMatrix();
    _SetCurrentMatrix(a5);
    gif_DrawPolyF4(a0, a1, a2, a3, a4[0], a4[1], a4[2], a4[3], 1);
}
INCLUDE_ASM("asm/nonmatchings/src/poly-flat", _IsInScreen2);
inline void IsPointIsInScreen(void *a0, void *a1) {
    float buf[16];
    sceVu0UnitMatrix(buf);
    func_0025D440(buf, matrixptr + 0x80, buf);
    func_0025D440(buf, matrixptr + 0xC0, buf);
    sceVu0RotTransPers(a0, buf, a1, 1);
    _IsInScreen2(a0);
}
void before_DrawLine(int a0)
{
    CopyMatrix(drawline_ws_matrix, a0);
    gif_StartPacketPri(0xB);
}
void after_DrawLine(int a0, int a1, int a2, int a3)
{
    gif_EndPacket(a0, a1, a2, a3);
}
inline void do_DrawLine(void *p0, void *p1, int *c)
{
    unsigned char col[4] = { c[0], c[1], c[2], c[3] };
    int v0[4];
    int v1[4];

    if (DrawLineTrans(v0, p0) == 0) return;
    if (DrawLineTrans(v1, p1) == 0) return;

    DrawLineOffset(v0);
    DrawLineOffset(v1);

    gif_MakeLine2D(v0, v1, v0[2], v1[2], col, 1);
}
