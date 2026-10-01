/*
 * ico2/omori/include/poly-flat.h
 *
 * The declarations of what poly-flat.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef POLY_FLAT_H
#define POLY_FLAT_H

void DrawPolygon(void *a0, void *a1, void *a2, void *a3, unsigned char *a4, void *a5);
void do_DrawLine(void *p0, void *p1, int *c, int a3);
float IsPointIsInScreen(void *a0, void *a1);
void after_DrawLine(void);
void after_DrawPolygon(void);
void before_DrawLine(int a0);
void before_DrawPolygon(void);

#endif /* POLY_FLAT_H */
