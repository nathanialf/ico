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

/* PAL's font alignment and colour words are not in this build: the TU's
   .sdata is font_Print's string alone in the demo. */

/* .sbss: the flag font_Print raises at a '{' and drops after the control
   sequence */
static int fontInBrace; /* derived name */

inline int font_GetWidth(void);

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

INCLUDE_ASM(disp_DisplayFont);

INCLUDE_ASM(font_Print);
