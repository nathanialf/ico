/*
 * ico2/fumi/include/fuzio.h
 *
 * The declarations of what fuzio.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef FUZIO_H
#define FUZIO_H

void fzShowV(float *p);
void fzShowM(float *p);
float fzMagnitude2f(float x, float z);
float fzMagnitude3f(float x, float y, float z);
float fzMagnitudefv(float *v);
float fzMagnitude2fv(float *p0, float *p1);
float fzMagnitudeByLine(float *p0, float *p1, float *p2);
float fzMagnitudeByLineSeg(float *p0, float *p1, float *p2);

#endif /* FUZIO_H */
