/*
 * ico2/sugipon/include/pool.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what pool.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef POOL_H
#define POOL_H

extern int CheckPoolHasGridMesh(char *a0);
extern void DispLimitedPoolReflactionMesh(int *a0);
extern void GetPoolGlobalDrainVector(void *dst, char *a0);
extern float GetPoolGlobalHeight(char *a0);
extern float GetPoolGlobalHeightDetail(char *a0, float *pos);
extern void InitLimitedPoolReflactionMesh(char *a0);
extern void SetFallDownSplash(int pool, void *self);
extern void SetLimitedPoolReflactionMesh(char *a0, char *a1, char *a2);
extern void copyToWork(int pri);
extern void dispPool(char *self);
extern void updatePoolGeo(char *self);

#endif /* POOL_H */
