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

void prim_DeleteParticle(int a0);
void prim_DispFan2D(int handle, int a);
void prim_DispMesh3D(int a0, void *a1, void *a2, int a3);
void prim_DispParticle(int prim, void *m);
void prim_DispWireBox(float *sz, void *col);
/* radius first: the calls in box, boy and commonact set $f12 ahead of the
   colour and the counts, which only this order gives; every other caller
   compiles the same under either order */
void prim_DispWireSphere(float r, void *col, int nu, int nv);
int prim_InitFan2D(int a, float e, int *b, unsigned int c, int d);
char *prim_InitMesh3D(int a0, int a1, int a2, int a3, unsigned int a4, int a5);
int prim_InitParticle(int a0, int a1, int a2, int a3);

/* reconstruction: the parameter list is Primitive.c's own definition at
   ico2/seki/src/Primitive.c:522, and the ROM's call from particleEffect
   fills $4/$5/$6/$7/$8 and $f12/$f13/$f14 in exactly this order. The
   return type is the definition's PrimParticle *, a type local to
   Primitive.c, so it is declared void * here and cast at the call. */
void *prim_InitParticleByPartition(int num, float x, float y, float z, int a1, char *name, int a3,
                                   void *heap);

void prim_SetFan2D(int handle, float radius, void *pos, unsigned int c0, unsigned int c1);
void prim_UpdateMesh3D(void *mesh, int a1, int a2);

#endif /* PRIMITIVE_H */
