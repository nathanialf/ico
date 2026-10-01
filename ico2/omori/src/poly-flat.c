#include "Matrix.h"
#include "matrixDrive.h"
#include "GsBase.h"
#include "main.h"

/* the TU's whole .data run, VMA 0x2A6030..0x2A6070 (0x40, = MAIN.MAP
   poly-flat.o .data 0x40, which names this object at offset 0): the
   world-space matrix before_DrawLine copies the caller's into and every
   line transform reads back. */
float drawline_ws_matrix[16] = {0};

#include "poly-flat.h"
#include <libvu0.h>
#include "GifPacket.h"

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

void after_DrawPolygon(void)
{
    gif_EndPacket();
}

inline void DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5)
{
    _InitCurrentMatrix();
    _SetCurrentMatrix(a5);
    gif_DrawPolyF4(a0, a1, a2, a3, a4[0], a4[1], a4[2], a4[3], 1);
}

float _IsInScreen2(int *p)
{
    int hw;
    int hh;
    float rx;
    float ry;

    if (p[2] < 0) {
        return -1.0f;
    }
    if (0x0FFFFFF0 < p[2]) {
        return -1.0f;
    }
    hw = ScreenWidth / 2;
    if (p[0] < (0x800 - hw) * 16) {
        return -1.0f;
    }
    if ((0x800 + hw) * 16 < p[0]) {
        return -1.0f;
    }
    hh = ScreenHeight / 2;
    if (p[1] < (0x800 - hh) * 16) {
        return -1.0f;
    }
    if ((0x800 + hh) * 16 < p[1]) {
        return -1.0f;
    }

    rx = (float)(p[0] - 0x8000) / (float)((0x800 + hw) * 16 - 0x8000);
    if (rx < 0.0f) {
        rx = -rx;
    }
    ry = (float)(p[2] - 0x8000) / (float)((0x800 + hh) * 16 - 0x8000);
    if (ry < 0.0f) {
        ry = -ry;
    }

    if (ry < rx) {
        ry = rx;
    }

    return ry;
}

inline float IsPointIsInScreen(void *a0, void *a1)
{
    float buf[16];
    sceVu0UnitMatrix(buf);
    sceVu0MulMatrix(buf, matrixptr + 0x80, buf);
    sceVu0MulMatrix(buf, matrixptr + 0xC0, buf);
    sceVu0RotTransPers(a0, buf, a1, 1);
    return _IsInScreen2(a0);
}

void before_DrawLine(int a0)
{
    CopyMatrix(drawline_ws_matrix, a0);
    gif_StartPacketPri(0xB);
}

void after_DrawLine(void)
{
    gif_EndPacket();
}

inline void do_DrawLine(void *p0, void *p1, int *c, int a3)
{
    unsigned char col[4] = {c[0], c[1], c[2], c[3]};
    int v0[4];
    int v1[4];

    if (DrawLineTrans(v0, p0) == 0)
        return;
    if (DrawLineTrans(v1, p1) == 0)
        return;

    DrawLineOffset(v0);
    DrawLineOffset(v1);

    gif_MakeLine2D(v0, v1, v0[2], v1[2], col, 1);
}
