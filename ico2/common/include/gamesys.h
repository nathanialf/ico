/*
 * ico2/common/include/gamesys.h
 *
 * The declarations of what gamesys.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef GAMESYS_H
#define GAMESYS_H

#include "backStage.h"
#include "typedef.h"

/* gamesys.c's .data globals */
extern char stamp_str[];
extern void *gameSysMemoryFuncList[];
extern int gamesysStageExitTime[];
extern GamesysObjInfo gameSysObjInfo[];
extern char gameSysMainSaveBuff[];
extern int gamesysTimeCount;
extern int gamesysAnotherStageTsuresari;
extern int gamesysVersionDiff;
extern int gamesysObjBuffOver;
/* the object-kind table (obj-kind-data) and the stage layout objects
   (obj-layout), data members linked with debug.o and gamesys.o */
extern ObjKindEnt objKindData[];
extern GenGeo objLayout[];
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
int *gamesysObjInfoUniqDataSet(GObj *a0);
void gamesysStageExitTimeSet(int a0);
void gamesysBackStageProcess(void);
void gamesysNObjInfoInit(void);
void gamesysObjInfoStageInitPosSaveUnlock(void);
int gamesysGirlStageGet(void);

#endif /* GAMESYS_H */
