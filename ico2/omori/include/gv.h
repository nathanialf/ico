/*
 * ico2/omori/include/gv.h
 *
 * The declarations of what gv.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GV_H
#define GV_H

int AlignDegGV(int deg);
float GetCorrectDistance(int deg, float dist);
void GetMatrixDirectionToZ(float *out, float *dir);
int RoundDegGV(int deg);
void SwapGV(float *a, float *b);
int _AbsRotyGV(void *dir, void *base);
void _ApplyRyGV(float *vec, float ang);
float _DistGV(void *a, void *b);
float _DistSqGV(void *a, void *b);
float _DistxzGV(void *a, void *b);
float _DistxzSqGV(void *a, void *b);
int _FrontGV(float *target, float *pos, float *dir, int deg);
float _GetDirection(float *dir);
void _InterGV(float *dst, float *a, float *b, float ta, float tb);
int _InterRotGV(float *dst, float *cur, float *tgt, int step);
float _MoveGV(float *dst, float *from, float *to, float step);
void _OrientGV(float *dst, float *a, float *b);
void _OrientXZGV(float *dst, float *a, float *b);
int _RotGV(float *a, float *b);
float _RotGVF(float *a, float *b);
int _RotyGV(float *dir, float *base);

#endif /* GV_H */
