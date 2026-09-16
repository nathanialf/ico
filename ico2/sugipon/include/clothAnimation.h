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

void DispCloth4D(int *a0, void *a1, void *a2);
void DispCloth4DWithAdd(int *a0, void *a1, void *a2);
void DispClothMesh(int *a0, void *a1, void *a2);
void DispMeshWire(int *rows, int nx, int ny);
void GetChainAnimation(void *chain, int a, void *m);
float GetChainCollision(int *a0, void *pos, float r);
float GetChainNodeID(int a0, float f);
void GetCloth4D(void *a0, float x, float y);
void GetCloth4DWithTight(void *a0, float x, float y, float z, float w, void *a1, void *a2);
void GetClothAnimation(void *a0, void *a1, int a2, void *m, int a4, int a5, void *a6, int a7);
void GetClothAnimationFix4Points(void *a0, void *a1, int a2, void *m);
void *InitChains(char *a0);
int InitCloth4D(char *g, void *a1, void *a2);
int InitClothes(char *p);
int SetChainExtendedWeight(int *a0, int idx, float w0, float w1);
void TestDispChainAnimation(int *a0);
void getCloth4D(void *a0, int **rows);
void getCloth4D_preProcess(void *a0, int tight, void *a6, void *a7, float x, float y, float z, float w);

#endif /* CLOTHANIMATION_H */
