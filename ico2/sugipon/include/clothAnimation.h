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
/* RECONSTRUCTION.  One row of the table InitCloth4D's third argument points at:
 * the skeleton node a piece of cloth hangs from and the offsets the init
 * scales by the actor's own scale.  Only enable, node and f0C have a reader in
 * C (InitCloth4D itself); the rest are read by the cloth step, which is still
 * assembled, so those names are positional.  The layout is read off the ROM's
 * own tables in boy.o, girl.o and queen.o. */
typedef struct {
    int enable; /* 0x00, -1 ends the table */
    float f04;  /* 0x04, scaled by the actor scale at init */
    float f08;  /* 0x08, likewise */
    float f0C;  /* 0x0C, likewise; the init also stores 1 / (f0C + f0C) at 0x34 */
    int node;   /* 0x10, the argument GetSkeltonFocusNode is called with */
    char pad14[0x20 - 0x14];
    float f20; /* 0x20 */
    float f24; /* 0x24 */
    char pad28[0x2C - 0x28];
    float f2C; /* 0x2C */
    float f30; /* 0x30 */
    char pad34[0x40 - 0x34];
} ClothHangCfg;

int InitCloth4D(char *g, void *a1, void *a2);
int InitClothes(char *p);
int SetChainExtendedWeight(int *a0, int idx, float w0, float w1);
void TestDispChainAnimation(int *a0);
void getCloth4D(void *a0, int **rows);
void getCloth4D_preProcess(void *a0, int tight, void *a6, void *a7, float x, float y, float z, float w);

#endif /* CLOTHANIMATION_H */
