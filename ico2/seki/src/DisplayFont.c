#include "DisplayFont.h"
#include "debug.h"
#include <string.h>
#include "GsBase.h"
#include "Matrix.h"
#include "GifPacket.h"
#include "Texture.h"

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
