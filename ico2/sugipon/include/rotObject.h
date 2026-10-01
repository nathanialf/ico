/*
 * ico2/sugipon/include/rotObject.h
 *
 * The declarations of what rotObject.c defines, for the files that use
 * them.  The file name is derived.
 */

#ifndef ROTOBJECT_H
#define ROTOBJECT_H

#include "backStage.h"

struct GObj;

void GetRotObjectGameSysObjInfoExtData(short *a0, int *a1, GamesysObjInfo *a2);
void GetRotObjectGlobalHoldGeometry(void *pos, void *dir, void *gobj, void *posMtx, void *dirMtx);
void GetRotObjectHoldPoint(void *a0, void *a1, void *a2, void *a3);
float GetRotObjectRotCount(struct GObj *a0);
int GetRotObjectZPlusDirection(void *gobj);
int MoveRotObjectWithHoldPoint(struct GObj *bar, void *hold, void *self, void *dir, void *up);
void SetRotObjectArmRadius(struct GObj *a0, float f);
void SetRotObjectLockFlag(struct GObj *a0, int a1);

#endif /* ROTOBJECT_H */
