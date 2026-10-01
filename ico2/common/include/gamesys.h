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

#include "backStage.h"

/* gamesys.c's .data, MAIN.MAP's gamesys.o globals in its order */
extern char stamp_str[];
extern void *gameSysMemoryFuncList[];
extern int gamesysStageExitTime[];
extern GamesysObjInfo gameSysObjInfo[];
extern char gameSysMainSaveBuff[];
extern int gamesysTimeCount;
extern int gamesysAnotherStageTsuresari;
extern int gamesysVersionDiff;
extern int gamesysObjBuffOver;

int gamesysGetGirlStageIDAndPosition(int *pos);
void gamesysMemoryHandlerRead(int *self, void *dst, int size);
void gamesysMemoryHandlerWrite(int *self, void *src, int size);
void gamesysMemoryLoad(void **tbl, void *a1, void *a2);
void gamesysMemorySave(void **tbl, void *a1, void *a2);
int *gamesysObjInfoBaseSet(int *self, int stage);
void gamesysObjInfoCls(int kind, int no);
GamesysObjInfo *gamesysObjInfoGet(int kind, int no);
void gamesysObjInfoInit(void);
GamesysObjInfo *gamesysObjInfoPosNewStageSet(int no, int kind, int stage, float *pos, float *rot);
int *gamesysObjInfoPosSetStage(int *self, int a1, int a2, int a3);
void gamesysObjInfoStageInitFlagCls(void);
int *gamesysObjInfoUniqDataSet(int a0);
void gamesysStageExitTimeSet(int a0);

void gamesysBackStageProcess(void);
void gamesysNObjInfoInit(void);
void gamesysObjInfoStageInitPosSaveUnlock(void);
int gamesysGirlStageGet(void);

#endif /* GAMESYS_H */
