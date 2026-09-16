/*
 * ico2/sugipon/include/staticBlur.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what staticBlur.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef STATICBLUR_H
#define STATICBLUR_H

void SetAuraInspireParam(float a0);
void SetMotionBlur(int val);
void SetStaticBlur(int x);
void blur(int n, void *col);

#endif /* STATICBLUR_H */
