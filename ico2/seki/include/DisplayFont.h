/*
 * ico2/seki/include/DisplayFont.h
 *
 * The declarations of what DisplayFont.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef DISPLAYFONT_H
#define DISPLAYFONT_H

/* DisplayFont.c's `inline` functions, in the order of their definitions'
 * out-of-line copies at the end of the object (first-declaration order). */
int font_GetWidth(void);
int font_GetHeight(void);
void font_Init(void);

/* a line's colour, {r, g, b, a}: font_CheckAlign reads it from the line's
 * {#rrggbbaa} tag and font_Print scales the packet colour by it */
typedef struct { /* field names derived */
    unsigned char f[4];
} SprCol; /* derived name */

int font_CheckAlign(SprCol *col, unsigned char *str);
void font_Print(unsigned int color, unsigned char *str, float x, float y, int align, SprCol col);

#endif /* DISPLAYFONT_H */
