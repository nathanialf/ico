/*
 * ico2/sugipon/include/clothAnimation.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what clothAnimation.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef CLOTHANIMATION_H
#define CLOTHANIMATION_H

extern void DispCloth4D(int *a0, void *a1, void *a2);
extern void DispCloth4DWithAdd(int *a0, void *a1, void *a2);
extern void DispClothMesh(int *a0, void *a1, void *a2);
extern void DispMeshWire(int *rows, int nx, int ny);
extern void GetChainAnimation(void *chain, int a, void *m);
extern float GetChainCollision(int *a0, void *pos, float r);
extern float GetChainNodeID(int a0, float f);
extern void GetCloth4D(void *a0, float x, float y);
extern void GetCloth4DWithTight(void *a0, float x, float y, float z, float w, void *a1, void *a2);
extern void GetClothAnimation(void *a0, void *a1, int a2, void *m, int a4, int a5, void *a6, int a7);
extern void GetClothAnimationFix4Points(void *a0, void *a1, int a2, void *m);
extern void *InitChains(char *a0);
extern int InitCloth4D(char *g, void *a1, void *a2);
extern int InitClothes(char *p);
extern int SetChainExtendedWeight(int *a0, int idx, float w0, float w1);
extern void TestDispChainAnimation(int *a0);
extern void getCloth4D(void *a0, int **rows);
extern void getCloth4D_preProcess(void *a0, int tight, void *a6, void *a7, float x, float y, float z, float w);

#endif /* CLOTHANIMATION_H */
