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

extern int gamesysGetGirlStageIDAndPosition(int a0);
extern void gamesysMemoryHandlerRead(int *self, int a1, int a2);
extern void gamesysMemoryHandlerWrite(int *self, int n, int a2);
extern void gamesysMemoryLoad(void **tbl, int a1, void *a2);
extern void gamesysMemorySave(int *self, int a1, int a2);
extern int *gamesysObjInfoBaseSet(int *self, int stage);
extern void gamesysObjInfoCls(int kind, int no);
extern void *gamesysObjInfoGet(int a0, int a1);
extern void gamesysObjInfoInit(void);
extern void gamesysObjInfoPosNewStageSet(char *self, char *other, int v, float *tmp_a, float *tmp_b);
extern int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3);
extern void gamesysObjInfoStageInitFlagCls(void);
extern int *gamesysObjInfoUniqDataSet(int a0);
extern void gamesysStageExitTimeSet(int a0);

#endif /* GAMESYS_H */
