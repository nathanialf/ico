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

extern int AlignDegGV(int a0);
extern void GetMatrixDirectionToZ(float *out, float *dir);
extern int RoundDegGV(int a0);
extern void SwapGV(float *a, float *b);
extern int _AbsRotyGV(void *a0, void *a1);
extern void _ApplyRyGV(float *a0, float a1);
extern void _DistGV(void *a0, void *a1);
extern void _DistSqGV(void *a0, void *a1);
extern void _DistxzGV(void *a0, void *a1);
extern void _DistxzSqGV(void *a0, void *a1);
extern float _GetDirection(float *a0);
extern void _InterGV(float *dst, float *a, float *b, float ta, float tb);
extern float _MoveGV(float *a0, float *a1, float *a2, float a3);
extern void _OrientGV(int a0);
extern void _OrientXZGV(int a0);
extern float _RotGVF(float *a0, float *a1);
extern int _RotyGV(float *a0, float *a1);

#endif /* GV_H */
