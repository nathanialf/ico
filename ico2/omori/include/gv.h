/*
 * ico2/omori/include/gv.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gv.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GV_H
#define GV_H

int AlignDegGV(int a0);
void GetMatrixDirectionToZ(float *out, float *dir);
int RoundDegGV(int a0);
void SwapGV(float *a, float *b);
int _AbsRotyGV(void *a0, void *a1);
void _ApplyRyGV(float *a0, float a1);
void _DistGV(void *a0, void *a1);
void _DistSqGV(void *a0, void *a1);
void _DistxzGV(void *a0, void *a1);
void _DistxzSqGV(void *a0, void *a1);
float _GetDirection(float *a0);
void _InterGV(float *dst, float *a, float *b, float ta, float tb);
float _MoveGV(float *a0, float *a1, float *a2, float a3);
void _OrientGV(int a0);
void _OrientXZGV(int a0);
float _RotGVF(float *a0, float *a1);
int _RotyGV(float *a0, float *a1);

#endif /* GV_H */
