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

int CheckPoolHasGridMesh(char *a0);
void DispLimitedPoolReflactionMesh(int *a0);
void GetPoolGlobalDrainVector(void *dst, char *a0);
float GetPoolGlobalHeight(char *a0);
float GetPoolGlobalHeightDetail(char *a0, float *pos);
void InitLimitedPoolReflactionMesh(char *a0);
void SetFallDownSplash(int pool, void *self);
void SetLimitedPoolReflactionMesh(char *a0, char *a1, char *a2);
void copyToWork(int pri);
void dispPool(char *self);
void updatePoolGeo(char *self);

#endif /* POOL_H */
