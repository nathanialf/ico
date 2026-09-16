/*
 * ico2/common/include/gamesys.h
 *
 * The disc records no file of this name: SRCFILE.TXT attributes no
 * instruction to it, and a header that only declares leaves no rows in the
 * listing at all, so this file is ours and not the developers' own record.
 * It collects the declarations of what gamesys.c defines, in the form its
 * users need them; every type here is read from the ROM's calling convention
 * at the call sites and from the spellings the using TUs already carried.
 */

#ifndef GAMESYS_H
#define GAMESYS_H

int gamesysGetGirlStageIDAndPosition(int a0);
void gamesysMemoryHandlerRead(int *self, int a1, int a2);
void gamesysMemoryHandlerWrite(int *self, int n, int a2);
void gamesysMemoryLoad(void **tbl, int a1, void *a2);
void gamesysMemorySave(int *self, int a1, int a2);
int *gamesysObjInfoBaseSet(int *self, int stage);
void gamesysObjInfoCls(int kind, int no);
void *gamesysObjInfoGet(int a0, int a1);
void gamesysObjInfoInit(void);
void gamesysObjInfoPosNewStageSet(char *self, char *other, int v, float *tmp_a, float *tmp_b);
int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3);
void gamesysObjInfoStageInitFlagCls(void);
int *gamesysObjInfoUniqDataSet(int a0);
void gamesysStageExitTimeSet(int a0);

#endif /* GAMESYS_H */
