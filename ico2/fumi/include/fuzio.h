/*
 * ico2/fumi/include/fuzio.h
 *
 * The declarations of what fuzio.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FUZIO_H
#define FUZIO_H

float fzMagnitude2fv(float *p0, float *p1);
float fzMagnitudeByLineSeg(float *p0, float *p1, float *p2);
float fzMagnitudefv(float *v);
void fzShowV(float *p);

#endif /* FUZIO_H */
