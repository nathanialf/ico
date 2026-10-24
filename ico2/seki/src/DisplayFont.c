#include "DisplayFont.h"
#include "debug.h"
#include <string.h>
#include "GsBase.h"
#include "Matrix.h"
#include "GifPacket.h"
#include "Texture.h"

#if defined(VERSION_NTSC) || defined(VERSION_AUG6)
/* each character's first and last column in its 20-pixel cell of the "font"
   texture, {0, 0} where the font has no glyph */
static signed char fontKerning[128][2] = {
    /* derived name */
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {8, 10}, {7, 10}, {3, 15}, {4, 13}, {2, 15}, {3, 15}, {6, 11},
    {6, 11}, {6, 11}, {3, 13}, {3, 14}, {8, 10}, {6, 11}, {8, 10}, {5, 13}, {4, 13}, {7, 11},
    {4, 13}, {4, 13}, {4, 13}, {4, 13}, {4, 13}, {4, 12}, {4, 13}, {5, 13}, {8, 10}, {7, 10},
    {5, 13}, {5, 12}, {5, 13}, {4, 13}, {2, 15}, {2, 15}, {4, 13}, {3, 14}, {3, 14}, {4, 13},
    {4, 13}, {3, 14}, {4, 14}, {8, 9},  {5, 12}, {3, 14}, {4, 13}, {3, 14}, {3, 14}, {2, 14},
    {4, 13}, {3, 15}, {4, 14}, {4, 13}, {3, 14}, {3, 14}, {3, 14}, {1, 16}, {3, 14}, {3, 14},
    {4, 13}, {6, 11}, {3, 15}, {6, 11}, {5, 12}, {4, 13}, {0, 0},  {4, 13}, {4, 13}, {4, 13},
    {4, 13}, {4, 13}, {5, 12}, {4, 13}, {5, 13}, {8, 10}, {6, 11}, {5, 13}, {8, 9},  {2, 15},
    {5, 13}, {4, 13}, {4, 12}, {5, 13}, {6, 11}, {5, 12}, {6, 12}, {5, 13}, {4, 13}, {2, 16},
    {4, 13}, {4, 13}, {5, 12}, {6, 11}, {8, 9},  {6, 11}, {4, 13}, {0, 0},
};
#else
#ifdef VERSION_JUN26
/* each character's first and last column in its 20-pixel cell of the "font"
   texture, {0, 0} where the font has no glyph */
static signed char fontKerning[128][2] = {
    /* derived name */
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {7, 11}, {9, 11}, {6, 12}, {5, 12}, {3, 14}, {3, 14}, {9, 11},
    {7, 13}, {5, 11}, {8, 12}, {6, 12}, {7, 9},  {7, 11}, {7, 9},  {5, 12}, {5, 13}, {6, 11},
    {4, 12}, {4, 12}, {4, 13}, {4, 13}, {5, 12}, {5, 13}, {4, 13}, {5, 13}, {7, 10}, {7, 10},
    {7, 11}, {6, 12}, {7, 11}, {6, 12}, {4, 14}, {2, 13}, {3, 13}, {4, 14}, {3, 14}, {4, 13},
    {4, 14}, {4, 14}, {2, 15}, {6, 12}, {4, 13}, {3, 15}, {4, 12}, {0, 17}, {2, 15}, {4, 14},
    {4, 14}, {4, 14}, {3, 13}, {5, 13}, {5, 15}, {4, 15}, {5, 16}, {2, 18}, {2, 15}, {5, 15},
    {3, 14}, {6, 13}, {7, 10}, {5, 12}, {6, 11}, {2, 13}, {0, 0},  {4, 13}, {4, 13}, {5, 12},
    {4, 14}, {5, 12}, {6, 14}, {4, 13}, {4, 13}, {7, 11}, {5, 11}, {4, 13}, {7, 11}, {1, 15},
    {4, 13}, {4, 13}, {4, 13}, {4, 13}, {6, 13}, {5, 12}, {6, 13}, {4, 13}, {5, 13}, {2, 16},
    {4, 13}, {3, 13}, {4, 13}, {7, 13}, {4, 11}, {5, 11}, {6, 12}, {0, 0},
};
#else
/* each character's first and last column in its 20-pixel cell of the "font"
   texture, {0, 0} where the font has no glyph */
static signed char fontKerning[128][2] = {
    /* derived name */
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},  {0, 0},
    {0, 0},  {0, 0},  {0, 0},  {8, 11}, {7, 12}, {3, 16}, {4, 15}, {2, 17}, {3, 16}, {7, 12},
    {6, 12}, {7, 13}, {4, 15}, {3, 16}, {8, 11}, {7, 12}, {8, 11}, {5, 14}, {4, 14}, {7, 12},
    {5, 14}, {5, 14}, {5, 15}, {5, 14}, {5, 14}, {5, 14}, {4, 14}, {5, 14}, {8, 11}, {8, 11},
    {5, 14}, {6, 13}, {5, 14}, {5, 14}, {1, 18}, {3, 16}, {4, 15}, {4, 16}, {3, 15}, {4, 14},
    {4, 14}, {3, 15}, {4, 15}, {8, 11}, {6, 13}, {4, 16}, {5, 15}, {3, 16}, {4, 15}, {3, 16},
    {4, 14}, {3, 16}, {4, 15}, {4, 15}, {3, 16}, {4, 15}, {3, 16}, {2, 17}, {3, 16}, {3, 16},
    {4, 15}, {7, 13}, {3, 16}, {6, 12}, {5, 13}, {4, 14}, {0, 0},  {5, 15}, {4, 14}, {5, 14},
    {5, 15}, {5, 14}, {6, 13}, {4, 15}, {5, 14}, {8, 11}, {6, 12}, {5, 14}, {8, 11}, {2, 17},
    {5, 14}, {5, 14}, {5, 14}, {5, 14}, {6, 13}, {6, 14}, {6, 13}, {5, 14}, {4, 14}, {2, 17},
    {4, 15}, {4, 14}, {5, 14}, {6, 12}, {8, 11}, {7, 13}, {5, 15}, {2, 16},
};
#endif
#endif

#ifdef VERSION_JUN26
/* .sbss: raised at the start and after a space or an opening mark: the next
   capital letter stays a capital; any other character drops it, and font_Print
   prints a capital that follows as lower case */
static int fontWordTop; /* derived name */

void font_Print(int x, int y, unsigned int color, unsigned char *str)
{
    float cx;
    float cy;

    void disp(int c, int px, int py, int cw, int fontw, int u, int v)
    {
        int gsofs = 0x8000;
        int uv[4] = {u * 16 + 8, v * 16 + 8, (u + cw) * 16, (v + fontw) * 16};
        int pos[4] = {(px - 320) * 16 - 4, (py - 112) * 16 - 4, cw * 16, fontw * 10};

        gif_SetGsReg(0, 0x156);
        gif_SetGsReg(3, uv[0] | ((long long)uv[1] << 16));
        /* clang-format off */
        gif_SetGsReg(5, (pos[0] * ScreenWidth / 640 + gsofs) | ((long long)(pos[1] * ScreenHeight / 224 + gsofs) << 16) | ((long long)-1 << 32));
        gif_SetGsReg(3, uv[2] | ((long long)uv[3] << 16));
        gif_SetGsReg(5, (pos[0] * ScreenWidth / 640 + (pos[2] * ScreenWidth / 640 + gsofs)) | ((long long)(pos[1] * ScreenHeight / 224 + (pos[3] * ScreenHeight / 224 + gsofs)) << 16) | ((long long)-1 << 32));
        /* clang-format on */
    }

    texturetranssize += tex_TransTexture(tex_GetTextureNo("font"), 12);
    gif_StartPacketPriPath1(12);

    cx = x;
    cy = y;

    gif_SetGsReg(0x4E, 0x300000C0);
    gif_SetGsReg(0x47, 0x30000);
    gif_SetGsReg(0x42, 0x44);
    gif_SetGsReg(0x14, 0x60);
    gif_SetGsReg(1, ((color >> 24) & 0xFF) | ((long long)((color >> 16) & 0xFF) << 8) |
                        ((long long)((color >> 8) & 0xFF) << 16) |
                        ((long long)(color & 0xFF) << 24) | ((long long)0xFE00 << 46));

    fontWordTop = 1;
    for (;;) {
        unsigned char c = *str++;
        int ca;
        int cb;
        int cw;
        int u;
        int v;

        if (!fontWordTop && c >= 'A' && c <= 'Z')
            c += 'a' - 'A';
        if (c == ' ' || c == '&' || c == '(' || c == ',' || c == '-' || c == '<' || c == '[' ||
            c == '{')
            fontWordTop = 1;
        else
            fontWordTop = 0;
        if (c == 0)
            goto end;
        if (c == ' ') {
            cx += 4.0f;
            continue;
        }
        ca = fontKerning[c][0];
        cb = fontKerning[c][1];
        u = (c - ' ') % 12 * 20 + ca;
        v = (c - ' ') / 12 * 20;
        cw = cb - ca + 1;
        if (ca == 0 && cb == 0) {
            cw = 8;
        } else {
            disp(c, cx, cy, cw, 20, u, v);
        }
        cx += cw + 2;
    }

end:
    gif_EndPacketPath1();
}
#else
/* The .sdata run: the alignment a "{L}", "{R}" or "{C}" escape selects and the
   colour a "{#rrggbbaa}" escape sets, then the texture name at its use. */
static int fontAlign = 0; /* derived name */

static int fontColorR = 128; /* derived name */

static int fontColorG = 128; /* derived name */

static int fontColorB = 128; /* derived name */

static int fontColorA = 128; /* derived name */

inline int font_GetWidth(void)
{
    return 20;
}

inline int font_GetHeight(void)
{
    return (12800 / ScreenWidth) / 2;
}

inline void font_Init(void)
{
    fontAlign = 0;
    fontColorA = 128;
    fontColorB = 128;
    fontColorG = 128;
    fontColorR = 128;
}

/* A hex digit's value; inlined at all eight call sites. */
static inline int font_HexDigit(char c) /* derived name */
{
    int r = -1;

    if ((unsigned char)(c - '0') < 10)
        r = c - '0';
    else if ((unsigned)(c - 'A') < 6 || (unsigned)(c - 'a') < 6)
        r = (c >= 'a') ? (c - ('a' - 10)) : (c - ('A' - 10));
    return r;
}

int font_CheckAlign(SprCol *col, unsigned char *str)
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
                fontAlign = 1;
                break;
            case 'R':
                fontAlign = 2;
                break;
            case 'C':
                fontAlign = 0;
                break;
            case '#':
                if (strlen((const char *)buf) == 9) {
                    fontColorR = font_HexDigit(buf[1]) * 16 + font_HexDigit(buf[2]);
                    fontColorG = font_HexDigit(buf[3]) * 16 + font_HexDigit(buf[4]);
                    fontColorB = font_HexDigit(buf[5]) * 16 + font_HexDigit(buf[6]);
                    fontColorA = font_HexDigit(buf[7]) * 16 + font_HexDigit(buf[8]);
                }
                break;
            }
        } else if (n != 0) {
            buf[n - 1] = c;
            n++;
        }
    }
    col->f[0] = fontColorR;
    col->f[1] = fontColorG;
    col->f[2] = fontColorB;
    col->f[3] = fontColorA;
    return fontAlign;
}

#ifdef VERSION_NTSC
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

    float disp(float px, float py, int c, int cw, int fontw, int u, int v)
    {
        float fcw = (float)cw, fh = (float)(fontw * 640 / ScreenWidth);
        int gsofs = 0x8000;
        int uv[4] = {u * 16, v * 16, (u + cw + 1) * 16, (v + fontw) * 16}, iv[4];
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

    inline int measure(unsigned char *s, unsigned char *d) /* derived name */
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
                int ca = fontKerning[ch][0];
                int cb = fontKerning[ch][1];
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

    texturetranssize += tex_TransTexture(tex_GetTextureNo("font"), 12);
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
        ca = fontKerning[c][0];
        cb = fontKerning[c][1];
        u = (c - ' ') % 12 * 20 + ca;
        v = (c - ' ') / 12 * 20;
        w = cb - ca;
        cw = w + 1;
        fontw = font_GetWidth();
        if (cw < 7) {
            cx += 1.0f;
            cw = w + 2;
        }
        if (ca == 0 && cb == 0) {
            cx += 8.0f;
        } else {
            cx = disp(cx, cy, c, cw, fontw, u, v);
        }
    }

    gif_EndPacketPath1();
}
#else
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

#ifdef VERSION_AUG6
    float disp(float px, float py, int c, int cw, int fontw, int u, int v)
    {
        float fcw = (float)cw, fh = (float)(fontw * 640 / ScreenWidth);
        int gsofs = 0x8000;
        int uv[4] = {u * 16, v * 16, (u + cw + 1) * 16, (v + fontw) * 16}, iv[4];
#else
    inline float drawOne(float px, float py, int u, int v, int cw, int dp1,
                         int fontw) /* derived name */
    {
        float fcw = (float)cw, fh = (float)(fontw * 640 / ScreenWidth);
        int gsofs = 0x8000;
        int uv[4] = {u * 16, v * 16, (u + dp1 + 1) * 16, (v + 20) * 16}, iv[4];
#endif
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

    inline int measure(unsigned char *s, unsigned char *d) /* derived name */
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
                int ca = fontKerning[ch][0];
                int cb = fontKerning[ch][1];
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

    texturetranssize += tex_TransTexture(tex_GetTextureNo("font"), 12);
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
#ifndef VERSION_AUG6
        int dp1;
#endif
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
        ca = fontKerning[c][0];
        cb = fontKerning[c][1];
        u = (c - ' ') % 12 * 20 + ca;
        v = (c - ' ') / 12 * 20;
        w = cb - ca;
        cw = w + 1;
        fontw = font_GetWidth();
#ifndef VERSION_AUG6
        dp1 = cw;
#endif
        if (cw < 7) {
            cx += 1.0f;
            cw = w + 2;
        }
        if (ca == 0 && cb == 0) {
            cx += 8.0f;
        } else {
#ifdef VERSION_AUG6
            cx = disp(cx, cy, c, cw, fontw, u, v);
#else
            cx = drawOne(cx, cy, u, v, cw, dp1, fontw);
#endif
        }
    }

    gif_EndPacketPath1();
}
#endif
#endif
