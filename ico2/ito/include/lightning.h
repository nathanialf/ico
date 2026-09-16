/*
 * ico2/ito/include/lightning.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what lightning.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef LIGHTNING_H
#define LIGHTNING_H

void DrawLightning2(int n, void *a, void *b, float f0, float f1, float f2, float f3, float f4, float f5, float f6, float f7, float f8, float f9, int c);
void lightning_test(void);

#endif /* LIGHTNING_H */
