/*
 * ico2/seki/include/DisplayFont.h
 *
 * The declarations of what DisplayFont.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DISPLAYFONT_H
#define DISPLAYFONT_H

/* a colour, {r, g, b, a}, as the sprite calls take it */
typedef struct { /* field names derived */
    unsigned char f[4];
} SprCol; /* derived name */

void font_Print(int x, int y, unsigned int color, unsigned char *str);

#endif /* DISPLAYFONT_H */
