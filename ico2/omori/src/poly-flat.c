#include "Matrix.h"
#include "matrixDrive.h"
#include "GsBase.h"
#include "main.h"

/* the world-space matrix before_DrawLine copies the caller's into and every
   line transform reads back */
float drawline_ws_matrix[16] = {0};

#include "poly-flat.h"
#include <libvu0.h>
#include "GifPacket.h"

static inline unsigned char DrawLineTrans(int *dst, void *src) /* derived name */
{
    sceVu0RotTransPers(dst, drawline_ws_matrix, src, 1);
    return _IsInScreen(dst);
}

static inline void DrawLineOffset(int *p) /* derived name */
{
    p[0] -= 0x8000;
    p[1] -= 0x8000;
}

void before_DrawPolygon(void)
{
    gif_StartPacketPri(11);
    gif_SetAlpha(1, 2, 0x40);
}

void after_DrawPolygon(void)
{
    gif_EndPacket();
}

inline void DrawPolygon(void *a, void *b, void *c, void *d, unsigned char *col, void *mtx)
{
    _InitCurrentMatrix();
    _SetCurrentMatrix(mtx);
    gif_DrawPolyF4(a, b, c, d, col[0], col[1], col[2], col[3], 1);
}

static float _IsInScreen2(int *p)
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

inline float IsPointIsInScreen(void *out, void *pos)
{
    float buf[16];
    sceVu0UnitMatrix(buf);
    sceVu0MulMatrix(buf, matrixptr + 0x80, buf);
    sceVu0MulMatrix(buf, matrixptr + 0xC0, buf);
    sceVu0RotTransPers(out, buf, pos, 1);
    return _IsInScreen2(out);
}

void before_DrawLine(void *m)
{
    CopyMatrix(drawline_ws_matrix, m);
    gif_StartPacketPri(11);
}

void after_DrawLine(void)
{
    gif_EndPacket();
}

inline void do_DrawLine(void *from, void *to, unsigned int *c, int unused)
{
    unsigned char col[4] = {c[0], c[1], c[2], c[3]};
    int v0[4];
    int v1[4];

    if (DrawLineTrans(v0, from) == 0)
        return;
    if (DrawLineTrans(v1, to) == 0)
        return;

    DrawLineOffset(v0);
    DrawLineOffset(v1);

    gif_MakeLine2D(v0, v1, v0[2], v1[2], col, 1);
}
