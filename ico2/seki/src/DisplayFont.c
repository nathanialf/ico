#include "common.h"
/* .data, carved VMA 0x4EE5F0..0x4EE6F0 (1 symbols), bytes verified against the target ELF */
#include "DisplayFont.h"
#include <string.h>

unsigned int D_004EE5F0[64] = {
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000, 0x00000000,
    0x0B080000, 0x10030C07, 0x11020F04, 0x0C071003, 0x0D070C06, 0x10030F04, 0x0C070B08, 0x0E050B08,
    0x0C070E04, 0x0E050E05, 0x0E050F05, 0x0E050E05, 0x0E050E04, 0x0B080B08, 0x0D060E05, 0x0E050E05,
    0x10031201, 0x10040F04, 0x0E040F03, 0x0F030E04, 0x0B080F04, 0x10040D06, 0x10030F05, 0x10030F04,
    0x10030E04, 0x0F040F04, 0x0F041003, 0x11021003, 0x10031003, 0x0D070F04, 0x0C061003, 0x0E040D05,
    0x0F050000, 0x0E050E04, 0x0E050F05, 0x0F040D06, 0x0B080E05, 0x0E050C06, 0x11020B08, 0x0E050E05,
    0x0E050E05, 0x0E060D06, 0x0E050D06, 0x11020E04, 0x0E040F04, 0x0C060E05, 0x0D070B08, 0x10020F05,
};

extern int ScreenWidth;
extern int D_0063BD00;
extern int D_0063BD04;
extern int D_0063BD08;
extern int D_0063BD0C;
extern int D_0063BD10;

inline int font_GetWidth(void)
{
    return 0x14;
}

inline int font_GetHeight(void)
{
    return (0x3200 / ScreenWidth) / 2;
}

inline void font_Init(void)
{
    D_0063BD00 = 0;
    D_0063BD10 = 0x80;
    D_0063BD0C = 0x80;
    D_0063BD08 = 0x80;
    D_0063BD04 = 0x80;
}

/* SRCFILE places this helper's rows (seki/src/DisplayFont.c:99-103) INSIDE
   font_CheckAlign's own span (def line 95, body 110-143), i.e. it was a
   function-local helper in the 2001 source; it is fully inlined at all
   eight call sites, so the placement emits no bytes of its own. */
static inline int font_HexDigit(char c)
{
    int r = -1;

    if ((unsigned char)(c - '0') < 10)
        r = c - '0';
    else if ((unsigned)(c - 'A') < 6 || (unsigned)(c - 'a') < 6)
        r = (c >= 'a') ? (c - ('a' - 10)) : (c - ('A' - 10));
    return r;
}

int font_CheckAlign(unsigned char *col, unsigned char *str)
{
    unsigned char buf[256];
    unsigned char *p;
    int n;
    int c;

    n = 0;
    p = str;
    while ((c = *p++) != 0) {
        if (c == '{') {
            n = 1;
        } else if (c == '}') {
            buf[n - 1] = 0;
            n = 0;
            switch (buf[0]) {
            case 'L':
                D_0063BD00 = 1;
                break;
            case 'R':
                D_0063BD00 = 2;
                break;
            case 'C':
                D_0063BD00 = 0;
                break;
            case '#':
                if (strlen((const char *)buf) == 9) {
                    D_0063BD04 = font_HexDigit(buf[1]) * 16 + font_HexDigit(buf[2]);
                    D_0063BD08 = font_HexDigit(buf[3]) * 16 + font_HexDigit(buf[4]);
                    D_0063BD0C = font_HexDigit(buf[5]) * 16 + font_HexDigit(buf[6]);
                    D_0063BD10 = font_HexDigit(buf[7]) * 16 + font_HexDigit(buf[8]);
                }
                break;
            }
        } else if (n != 0) {
            buf[n - 1] = c;
            n++;
        }
    }
    col[0] = D_0063BD04;
    col[1] = D_0063BD08;
    col[2] = D_0063BD0C;
    col[3] = D_0063BD10;
    return D_0063BD00;
}

typedef struct {
    unsigned char f[4];
} SprCol;

extern int ScreenHeight;
extern char D_0063BD18[];
extern int D_0063B124;
extern int tex_GetTextureNo(void *name);
extern int tex_TransTexture(int no, int pri);
extern void gif_StartPacketPriPath1(int pri);
extern void gif_EndPacketPath1(void);
extern void gif_SetGsReg(int reg, long long val);
extern void _FTOI4Vector(void *dst, void *src);

void font_Print(unsigned int color, unsigned char *str, float x, float y, int align, SprCol col)
{
    unsigned char buf[256];
    unsigned char *p;
    int r;
    int g;
    int b;
    int a;
    float cx;
    float cy;
    float fw;

    inline float drawOne(float px, float py, int u, int v, int cw, int dp1, int fontw)
    {
        float fcw = (float)cw, fh = (float)(fontw * 640 / ScreenWidth);
        int gsofs = 0x8000;
        int uv[4] = {u * 16, v * 16, (u + dp1 + 1) * 16, (v + 20) * 16}, iv[4];
        float pos[4] = {px, py, fcw, fh};
        int ofs[4] = {-ScreenWidth / 2 * 16, -ScreenHeight / 4 * 16, 0, 0};

        _FTOI4Vector(iv, pos);
        gif_SetGsReg(0, 0x156);
        gif_SetGsReg(3, uv[0] | ((long long)uv[1] << 16));
        /* clang-format off */
        gif_SetGsReg(5, (ofs[0] + (iv[0] + gsofs)) | ((long long)(ofs[1] + (iv[1] + gsofs)) << 16) | ((long long)-1 << 32));
        gif_SetGsReg(3, uv[2] | ((long long)uv[3] << 16));
        gif_SetGsReg(5, (ofs[0] + (iv[0] + gsofs) + iv[2]) | ((long long)(ofs[1] + (iv[1] + gsofs) + iv[3]) << 16) | ((long long)-1 << 32));
        /* clang-format on */
        return px + fcw + 1.0f;
    }

    inline int measure(unsigned char *s, unsigned char *d)
    {
        int brace = 0;
        int width = 0;
        int ch;

        while ((ch = *s++) != 0) {
            if (ch == '{') {
                brace = 1;
            } else if (ch == '}') {
                brace = 0;
            } else if (brace == 0) {
                int ca = ((signed char *)D_004EE5F0)[ch * 2];
                int cb = ((signed char *)D_004EE5F0)[ch * 2 + 1];
                int w = cb - ca;

                int cw = w + 1;

                if (cw < 7) {
                    cw = w + 3;
                }
                if (ca == 0 && cb == 0) {
                    width += 8;
                } else {
                    width += 1 + cw;
                }
                *d++ = ch;
            }
        }
        *d++ = 0;
        return width;
    }

    D_0063B124 += tex_TransTexture(tex_GetTextureNo(D_0063BD18), 12);
    gif_StartPacketPriPath1(12);

    cy = cx = 0.0f;

    r = (color >> 24) * col.f[0] / 255;
    g = ((color >> 16) & 0xFF) * col.f[1] / 255;
    b = ((color >> 8) & 0xFF) * col.f[2] / 255;
    a = ((color & 0xFF) * col.f[3]) >> 7;
    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x42, 0x44);
    gif_SetGsReg(0x14, 0x60);
    gif_SetGsReg(1, r | ((long long)g << 8) | ((long long)b << 16) | ((long long)a << 24) |
                        ((long long)0xFE00 << 46));

    fw = (float)measure(str, buf);
    p = buf;

    switch (align) {
    case 0:
        cy = y;
        cx = x * (float)ScreenWidth / 640.0f + (float)(ScreenWidth / 2) - fw * 0.5f;
        break;
    case 1:
        cy = y;
        cx = x * (float)ScreenWidth / 640.0f + 4.0f;
        break;
    case 2:
        cy = y;
        cx = x * (float)ScreenWidth / 640.0f + (float)ScreenWidth - fw - 4.0f;
        break;
    }

    for (;;) {
        int c = *p++;
        int ca;
        int cb;
        int w;
        int cw;
        int dp1;
        int fontw;
        int u;
        int v;

        /* clang-format off */
        if (c == 0) break;
        /* clang-format on */
        if (c == ' ') {
            cx += 8.0f;
            continue;
        }
        ca = ((signed char *)D_004EE5F0)[c * 2];
        cb = ((signed char *)D_004EE5F0)[c * 2 + 1];
        u = (c - 0x20) % 12 * 20 + ca;
        v = (c - 0x20) / 12 * 20;
        w = cb - ca;
        cw = w + 1;
        fontw = font_GetWidth();
        dp1 = cw;
        if (cw < 7) {
            cx += 1.0f;
            cw = w + 2;
        }
        if (ca == 0 && cb == 0) {
            cx += 8.0f;
        } else {
            cx = drawOne(cx, cy, u, v, cw, dp1, fontw);
        }
    }

    gif_EndPacketPath1();
}
