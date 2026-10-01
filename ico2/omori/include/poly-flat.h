/*
 * ico2/omori/include/poly-flat.h
 *
 * The declarations of what poly-flat.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef POLY_FLAT_H
#define POLY_FLAT_H

void DrawPolygon(void *a, void *b, void *c, void *d, unsigned char *col, void *mtx);
void do_DrawLine(void *from, void *to, unsigned int *c, int unused);
float IsPointIsInScreen(void *out, void *pos);
void after_DrawLine(void);
void after_DrawPolygon(void);
void before_DrawLine(void *m);
void before_DrawPolygon(void);

#endif /* POLY_FLAT_H */
