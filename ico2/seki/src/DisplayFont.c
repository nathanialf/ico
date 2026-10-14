#include "DisplayFont.h"
#include "debug.h"
#include <string.h>
#include "GsBase.h"
#include "Matrix.h"
#include "GifPacket.h"
#include "Texture.h"
#include "include_asm.h"

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

INCLUDE_ASM(func_001FAE98);

INCLUDE_ASM(font_Print);
