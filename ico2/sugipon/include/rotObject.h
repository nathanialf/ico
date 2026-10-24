/*
 * ico2/sugipon/include/rotObject.h
 *
 * The declarations of what rotObject.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ROTOBJECT_H
#define ROTOBJECT_H

#include "typedef.h"
#include "backStage.h"

struct GObj;

#ifndef VERSION_NTSC
void GetRotObjectGameSysObjInfoExtData(short *angle, int *turnCount, GamesysObjInfo *info);
#endif
void GetRotObjectGlobalHoldGeometry(void *pos, void *dir, struct GObj *bar, void *holdPos,
                                    void *holdDir);
void GetRotObjectHoldPoint(void *pos, void *dir, WallCfg *wall, struct GObj *holder);
float GetRotObjectRotCount(struct GObj *self);
int GetRotObjectZPlusDirection(struct GObj *gobj);
int MoveRotObjectWithHoldPoint(struct GObj *bar, float *hold, void *self, float *dir, float *up);
#ifndef VERSION_NTSC
void SetRotObjectArmRadius(struct GObj *self, float radius);
#endif
void SetRotObjectLockFlag(struct GObj *self, int lock);

struct RotObjWork;

struct SObjSimpleSetting;

struct GamesysObjInfo;

struct RotObjMemory;

void RotObjectGeo(struct GObj *self);
void ExecRotObjectMoveStartReaction(struct GObj *self);
void ExecRotObjectMoveEndReaction(struct GObj *self);
struct RotObjWork *InitRotObjectGeo(struct GObj *gobj, struct SObjSimpleSetting *src);
void RotObjectDL(struct GObj *gobj);
int RestoreRotObjectGeo(void);
int RestoreRotObjectExtGeo(struct GObj *self, struct GamesysObjInfo *info);
int MemoryRotObject(struct RotObjMemory *mem, struct GObj *self);

#endif /* ROTOBJECT_H */
