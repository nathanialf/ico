/*
 * ico2/sugipon/include/wireLetter.h
 *
 * The declarations of what wireLetter.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef WIRELETTER_H
#define WIRELETTER_H

/* The declarations below lead this header because their order is load-bearing:
 * gcc 2.9 emits the deferred out-of-line copy of a plain-inline function in
 * first-declaration order, so this is the order wireLetter.c's inline tail has. */
void ChangeColorWireString(int a0, int a1, int a2);
void Draw2DBox(float x0, float y0, float x1, float y1);
void DispWireString(char *s);
void DefaultColorWireString(void);

#endif /* WIRELETTER_H */
