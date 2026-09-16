/*
 * ico2/fumi/include/fuzio.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what fuzio.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef FUZIO_H
#define FUZIO_H

float fzMagnitude2fv(float *p0, float *p1);
float fzMagnitudeByLineSeg(float *p0, float *p1, float *p2);
float fzMagnitudefv(int v);
void fzShowV(float *p);

#endif /* FUZIO_H */
