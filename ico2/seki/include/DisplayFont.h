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

int font_CheckAlign(unsigned char *col, unsigned char *str);

#endif /* DISPLAYFONT_H */
