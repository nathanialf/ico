/*
 * ico2/omori/include/gv.h
 *
 * The declarations of what gv.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GV_H
#define GV_H

int AlignDegGV(int a0);
void GetMatrixDirectionToZ(float *out, float *dir);
int RoundDegGV(int a0);
void SwapGV(float *a, float *b);
int _AbsRotyGV(void *a0, void *a1);
void _ApplyRyGV(float *a0, float a1);
float _DistGV(void *a0, void *a1);
float _DistSqGV(void *a0, void *a1);
float _DistxzGV(void *a0, void *a1);
float _DistxzSqGV(void *a0, void *a1);
float _GetDirection(float *a0);
void _InterGV(float *dst, float *a, float *b, float ta, float tb);
float _MoveGV(float *a0, float *a1, float *a2, float a3);
void _OrientGV(float *dst, float *a, float *b);
void _OrientXZGV(float *dst, float *a, float *b);
float _RotGVF(float *a0, float *a1);
int _RotyGV(float *a0, float *a1);

#endif /* GV_H */
