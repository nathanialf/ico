/*
 * ico2/seki/include/DisplayFont.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what DisplayFont.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef DISPLAYFONT_H
#define DISPLAYFONT_H

int font_CheckAlign(unsigned char *col, unsigned char *str);
int font_GetHeight(void);
void font_Init(void);

#endif /* DISPLAYFONT_H */
