/*
 * ico2/seki/include/Primitive.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what Primitive.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef PRIMITIVE_H
#define PRIMITIVE_H

extern void prim_DeleteParticle(int a0);
extern void prim_DispFan2D(int handle, int a);
extern void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
extern void prim_DispParticle(int prim, void *m);
extern void prim_DispWireBox(float *sz, void *col);
extern void prim_DispWireSphere(void *col, int nu, int nv, float r);
extern int prim_InitFan2D(int a, float e, int *b, unsigned int c, int d);
extern char *prim_InitMesh3D(int a0, int a1, int a2, int a3, unsigned int a4, int a5);
extern int prim_InitParticle(int a0, int a1, int a2, int a3);
extern int prim_InitParticleByPartition();
extern void prim_SetFan2D(int handle, float radius, void *pos, unsigned int c0, unsigned int c1);
extern void prim_UpdateMesh3D(void *mesh, int a1, int a2);

#endif /* PRIMITIVE_H */
