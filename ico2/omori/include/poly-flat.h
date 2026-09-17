/*
 * ico2/omori/include/poly-flat.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what poly-flat.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef POLY_FLAT_H
#define POLY_FLAT_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order poly-flat.c's inline tail has. */
void DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5);
void do_DrawLine(void *p0, void *p1, int *c);
void IsPointIsInScreen(void *a0, void *a1);

void after_DrawLine(int a0, int a1, int a2, int a3);
void after_DrawPolygon(int a0, int a1, int a2, int a3);
void before_DrawLine(int a0);
void before_DrawPolygon(void);

#endif /* POLY_FLAT_H */
